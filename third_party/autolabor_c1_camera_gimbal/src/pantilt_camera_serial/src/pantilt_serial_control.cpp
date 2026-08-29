#include "pantilt_camera_serial/pantilt_serial_control.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <limits>
#include <sstream>
#include <utility>

namespace autolabor_driver
{

PantiltSerialControl::PantiltSerialControl(const rclcpp::NodeOptions & options)
: Node("pantilt_serial_driver", options)
{
  port_name_ = declare_parameter<std::string>("port_name", "/dev/ttyUSB0");
  baud_rate_ = declare_parameter<int>("baud_rate", 115200);
  query_rate_ = declare_parameter<double>("query_rate", 10.0);
  feedback_timeout_s_ = declare_parameter<double>("feedback_timeout", 1.0);
  write_timeout_s_ = declare_parameter<double>("write_timeout", 0.5);
  default_tolerance_deg_ = declare_parameter<double>("default_tolerance", 1.5);
  max_tolerance_deg_ = declare_parameter<double>("max_tolerance", 10.0);
  default_stable_samples_ = static_cast<std::uint32_t>(
    std::max<int>(1, declare_parameter<int>("default_stable_samples", 3)));
  frame_id_ = declare_parameter<std::string>("frame_id", "gimbal_link");

  if (!std::isfinite(query_rate_) || query_rate_ <= 0.0) {
    RCLCPP_WARN(get_logger(), "query_rate is invalid; using 10 Hz");
    query_rate_ = 10.0;
  }
  if (!std::isfinite(feedback_timeout_s_)) {feedback_timeout_s_ = 1.0;}
  if (!std::isfinite(write_timeout_s_)) {write_timeout_s_ = 0.5;}
  if (!std::isfinite(max_tolerance_deg_) || max_tolerance_deg_ <= 0.0) {max_tolerance_deg_ = 10.0;}
  if (!std::isfinite(default_tolerance_deg_) || default_tolerance_deg_ <= 0.0) {
    default_tolerance_deg_ = 1.5;
  }
  feedback_timeout_s_ = std::max(0.1, feedback_timeout_s_);
  write_timeout_s_ = std::max(0.05, write_timeout_s_);
  default_tolerance_deg_ = std::clamp(default_tolerance_deg_, 0.01, max_tolerance_deg_);

  angle_publisher_ = create_publisher<pantilt_camera_serial::msg::PantiltAngleInfo>(
    "pantilt_angle_info", rclcpp::SensorDataQoS());
  status_publisher_ = create_publisher<pantilt_camera_serial::msg::PantiltStatus>(
    "pantilt_status", rclcpp::QoS(10).reliable());

  twist_subscriber_ = create_subscription<geometry_msgs::msg::Twist>(
    "pantilt_vel", rclcpp::QoS(10),
    std::bind(&PantiltSerialControl::handle_twist_msg, this, std::placeholders::_1));

  command_service_ = create_service<pantilt_camera_serial::srv::PantiltCommand>(
    "send_command",
    std::bind(
      &PantiltSerialControl::handle_send_command, this,
      std::placeholders::_1, std::placeholders::_2));

  move_action_server_ = rclcpp_action::create_server<MovePantilt>(
    this,
    "move_pantilt",
    std::bind(
      &PantiltSerialControl::handle_move_goal, this,
      std::placeholders::_1, std::placeholders::_2),
    std::bind(
      &PantiltSerialControl::handle_move_cancel, this,
      std::placeholders::_1),
    std::bind(
      &PantiltSerialControl::handle_move_accepted, this,
      std::placeholders::_1));

  io_work_guard_ = std::make_unique<WorkGuard>(boost::asio::make_work_guard(io_context_));
  if (initialize_serial_connection()) {
    start_asynchronous_receive();
  }
  io_thread_ = std::thread([this]() {io_context_.run();});

  query_timer_ = create_wall_timer(
    std::chrono::duration_cast<std::chrono::nanoseconds>(
      std::chrono::duration<double>(1.0 / query_rate_)),
    std::bind(&PantiltSerialControl::query_timer_callback, this));
  status_timer_ = create_wall_timer(
    std::chrono::milliseconds(200),
    std::bind(&PantiltSerialControl::status_timer_callback, this));

  RCLCPP_INFO(
    get_logger(), "ROS2 pantilt driver ready: port=%s baud=%d query=%.1f Hz",
    port_name_.c_str(), baud_rate_, query_rate_);
}

PantiltSerialControl::~PantiltSerialControl()
{
  running_.store(false);
  action_reserved_.store(false);
  serial_connected_.store(false);

  // Let the action thread observe shutdown before the serial executor is stopped.
  {
    std::lock_guard<std::mutex> lock(action_thread_mutex_);
    if (action_thread_.joinable()) {
      action_thread_.join();
    }
  }

  // Keep all serial-port operations on the Asio thread; serial_port shared access is not thread-safe.
  if (port_ && io_thread_.joinable()) {
    auto closed = std::make_shared<std::promise<void>>();
    auto closed_future = closed->get_future();
    boost::asio::post(
      io_context_,
      [this, closed]() {
        if (port_) {
          boost::system::error_code ec;
          port_->cancel(ec);
          port_->close(ec);
        }
        closed->set_value();
      });
    (void)closed_future.wait_for(std::chrono::seconds(1));
  }

  if (io_work_guard_) {
    io_work_guard_->reset();
  }
  io_context_.stop();
  if (io_thread_.joinable()) {
    io_thread_.join();
  }
}

bool PantiltSerialControl::initialize_serial_connection()
{
  try {
    port_ = std::make_shared<boost::asio::serial_port>(io_context_);
    boost::system::error_code ec;
    port_->open(port_name_, ec);
    if (ec) {
      serial_connected_.store(false);
      const std::string message = "failed to open serial port " + port_name_ + ": " + ec.message();
      set_last_error(message);
      RCLCPP_ERROR(get_logger(), "%s", message.c_str());
      port_.reset();
      return false;
    }

    port_->set_option(boost::asio::serial_port_base::baud_rate(baud_rate_));
    port_->set_option(boost::asio::serial_port_base::character_size(8));
    port_->set_option(
      boost::asio::serial_port_base::stop_bits(
        boost::asio::serial_port_base::stop_bits::one));
    port_->set_option(
      boost::asio::serial_port_base::parity(
        boost::asio::serial_port_base::parity::none));
    port_->set_option(
      boost::asio::serial_port_base::flow_control(
        boost::asio::serial_port_base::flow_control::none));
    serial_connected_.store(true);
    set_motion_state(
      pantilt_camera_serial::msg::PantiltStatus::STATE_WAITING_FEEDBACK, false, false);
    return true;
  } catch (const std::exception & e) {
    serial_connected_.store(false);
    const std::string message = std::string("serial initialization exception: ") + e.what();
    set_last_error(message);
    RCLCPP_ERROR(get_logger(), "%s", message.c_str());
    port_.reset();
    return false;
  }
}

void PantiltSerialControl::start_asynchronous_receive()
{
  if (!port_ || !port_->is_open() || !running_.load()) {
    return;
  }
  receive_data_.resize(256U);
  port_->async_read_some(
    boost::asio::buffer(receive_data_),
    [this](const boost::system::error_code & error, std::size_t bytes_transferred) {
      handle_receive(error, bytes_transferred);
    });
}

void PantiltSerialControl::handle_receive(
  const boost::system::error_code & error, std::size_t bytes_transferred)
{
  if (!running_.load()) {
    return;
  }
  if (error) {
    if (error != boost::asio::error::operation_aborted) {
      serial_connected_.store(false);
      const std::string message = "serial receive error: " + error.message();
      set_last_error(message);
      RCLCPP_ERROR(get_logger(), "%s", message.c_str());
    }
    return;
  }

  buffer_.insert(
    buffer_.end(), receive_data_.begin(), receive_data_.begin() + bytes_transferred);
  parse_and_process_frames();
  start_asynchronous_receive();
}

void PantiltSerialControl::parse_and_process_frames()
{
  while (current_index_ + 1U < buffer_.size()) {
    if (buffer_[current_index_] != PantiltProtocol::FEEDBACK_HEADER) {
      ++current_index_;
      continue;
    }

    const std::size_t length = buffer_[current_index_ + PantiltProtocol::LENGTH_IDX];
    if (length < 4U || length > 128U) {
      ++current_index_;
      ++protocol_error_count_;
      continue;
    }
    if (current_index_ + length > buffer_.size()) {
      break;
    }

    const auto crc_begin = buffer_.begin() + static_cast<std::ptrdiff_t>(current_index_);
    const auto crc_end = crc_begin + static_cast<std::ptrdiff_t>(length - 1U);
    const std::vector<std::uint8_t> crc_frame(crc_begin, crc_end);
    const std::uint8_t calculated_crc = PantiltUtils::crc8_calculate(crc_frame);
    if (calculated_crc != buffer_[current_index_ + length - 1U]) {
      ++crc_error_count_;
      ++current_index_;
      continue;
    }

    const std::vector<std::uint8_t> frame(
      crc_begin, crc_begin + static_cast<std::ptrdiff_t>(length));
    ++rx_frame_count_;
    handle_valid_frame(frame);
    current_index_ += length;
  }

  if (current_index_ > 0U) {
    buffer_.erase(buffer_.begin(), buffer_.begin() + static_cast<std::ptrdiff_t>(current_index_));
    current_index_ = 0U;
  }
  if (buffer_.size() > 4096U) {
    buffer_.clear();
    ++protocol_error_count_;
    set_last_error("receive buffer overflow protection triggered");
  }
}

void PantiltSerialControl::handle_valid_frame(const std::vector<std::uint8_t> & frame)
{
  const auto check = PantiltUtils::check_frame_error(frame);
  if (!check.first) {
    ++protocol_error_count_;
    set_last_error(check.second);
    RCLCPP_WARN(get_logger(), "gimbal protocol error: %s", check.second.c_str());
    return;
  }

  if (
    frame.size() >= 18U &&
    frame[PantiltProtocol::COMMAND_IDX] == 0x00U &&
    frame[PantiltProtocol::LENGTH_IDX] == 0x12U)
  {
    const auto parsed = PantiltUtils::parse_angles(frame);
    if (!parsed) {
      ++protocol_error_count_;
      set_last_error("angle feedback frame is too short");
      return;
    }

    pantilt_camera_serial::msg::PantiltAngleInfo msg;
    msg.header.stamp = now();
    msg.header.frame_id = frame_id_;
    msg.heading = parsed->ground.heading;
    msg.roll = parsed->ground.roll;
    msg.pitch = parsed->ground.pitch;
    msg.encoder_heading = parsed->encoder.heading;
    msg.encoder_roll = parsed->encoder.roll;
    msg.encoder_pitch = parsed->encoder.pitch;

    {
      std::lock_guard<std::mutex> lock(feedback_mutex_);
      have_feedback_ = true;
      latest_ground_ = parsed->ground;
      latest_encoder_ = parsed->encoder;
      ++feedback_sequence_;
      last_feedback_steady_ = std::chrono::steady_clock::now();
    }
    angle_publisher_->publish(msg);
  }
}

void PantiltSerialControl::handle_twist_msg(const geometry_msgs::msg::Twist::SharedPtr msg)
{
  if (action_reserved_.load()) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), 2000,
      "ignoring pantilt_vel while a MovePantilt action is active");
    return;
  }
  const auto data = PantiltUtils::prepare_speed_data(msg->angular.z, msg->linear.x);
  if (data.empty()) {
    set_last_error("pantilt_vel exceeds +/-2.0 or contains a non-finite value");
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), 2000,
      "rejecting pantilt_vel outside +/-2.0 or with a non-finite value");
    return;
  }
  const auto result = write_command("SetPantiltSpeed", data);
  if (!result.success) {
    set_last_error(result.message);
    return;
  }
  const bool stopped = std::abs(msg->angular.z) < 1e-9 && std::abs(msg->linear.x) < 1e-9;
  set_motion_state(
    stopped ? pantilt_camera_serial::msg::PantiltStatus::STATE_IDLE :
    pantilt_camera_serial::msg::PantiltStatus::STATE_UNVERIFIED,
    false, false);
}

void PantiltSerialControl::handle_send_command(
  const std::shared_ptr<pantilt_camera_serial::srv::PantiltCommand::Request> request,
  std::shared_ptr<pantilt_camera_serial::srv::PantiltCommand::Response> response)
{
  using Service = pantilt_camera_serial::srv::PantiltCommand;
  response->success = false;

  if (!PantiltUtils::is_known_command(request->command_name)) {
    response->status_code = Service::Response::STATUS_UNKNOWN_COMMAND;
    response->message = "unknown command: " + request->command_name;
    return;
  }

  const bool is_mutating_command = PantiltUtils::is_mutating_command(request->command_name);
  if (is_mutating_command && action_reserved_.load()) {
    response->status_code = Service::Response::STATUS_BUSY;
    response->message = "MovePantilt action is active; mutating command rejected";
    return;
  }

  std::vector<std::uint8_t> data;
  if (request->command_name == "SetPantiltAngle") {
    if (request->data.size() != 3U) {
      response->status_code = Service::Response::STATUS_INVALID_ARGUMENT;
      response->message = "SetPantiltAngle requires exactly [heading, roll, pitch]";
      return;
    }
    data = PantiltUtils::prepare_motion_data(
      request->data[0], request->data[1], request->data[2]);
    if (data.empty()) {
      response->status_code = Service::Response::STATUS_INVALID_ARGUMENT;
      response->message = "SetPantiltAngle target is outside mechanical limits";
      return;
    }
  } else if (request->command_name == "SetPantiltSpeed") {
    if (request->data.size() != 2U) {
      response->status_code = Service::Response::STATUS_INVALID_ARGUMENT;
      response->message = "SetPantiltSpeed requires exactly [heading_speed, pitch_speed]";
      return;
    }
    data = PantiltUtils::prepare_speed_data(request->data[0], request->data[1]);
    if (data.empty()) {
      response->status_code = Service::Response::STATUS_INVALID_ARGUMENT;
      response->message = "SetPantiltSpeed values must be finite and within +/-2.0";
      return;
    }
  } else if (!request->data.empty()) {
    response->status_code = Service::Response::STATUS_INVALID_ARGUMENT;
    response->message = request->command_name + " does not accept data";
    return;
  }

  if (!serial_connected_.load()) {
    response->status_code = Service::Response::STATUS_SERIAL_DISCONNECTED;
    response->message = "serial port is disconnected";
    return;
  }

  const auto result = write_command(request->command_name, data);
  if (!result.success) {
    response->status_code = Service::Response::STATUS_SERIAL_WRITE_FAILED;
    response->message = result.message;
    set_last_error(result.message);
    return;
  }

  if (is_mutating_command) {
    const bool stopped_speed = request->command_name == "SetPantiltSpeed" &&
      std::abs(request->data[0]) < 1e-9 && std::abs(request->data[1]) < 1e-9;
    set_motion_state(
      stopped_speed ? pantilt_camera_serial::msg::PantiltStatus::STATE_IDLE :
      pantilt_camera_serial::msg::PantiltStatus::STATE_UNVERIFIED,
      false, false);
  }
  response->success = true;
  response->status_code = Service::Response::STATUS_OK;
  response->message = is_mutating_command ?
    "command validated and written to serial; resulting motion/state is UNVERIFIED unless MovePantilt Action is used" :
    "command validated and written to serial";
}

PantiltSerialControl::WriteResult PantiltSerialControl::write_command(
  const std::string & command_name, const std::vector<std::uint8_t> & data)
{
  const auto command = PantiltUtils::build_command(command_name, data);
  if (command.empty()) {
    return {false, "command build failed for: " + command_name};
  }
  if (!serial_connected_.load()) {
    return {false, "serial port is disconnected"};
  }

  auto promise = std::make_shared<std::promise<WriteResult>>();
  auto future = promise->get_future();
  boost::asio::post(
    io_context_,
    [this, command, command_name, promise]() {
      WriteResult result;
      if (!running_.load() || !port_ || !port_->is_open()) {
        result.message = "serial port is disconnected";
        promise->set_value(result);
        return;
      }
      boost::system::error_code ec;
      const auto bytes_written = boost::asio::write(*port_, boost::asio::buffer(command), ec);
      if (ec || bytes_written != command.size()) {
        serial_connected_.store(false);
        result.message = "serial write failed for " + command_name + ": " +
          (ec ? ec.message() : "short write");
        promise->set_value(result);
        return;
      }
      result.success = true;
      result.message = "ok";
      promise->set_value(result);
    });

  if (future.wait_for(std::chrono::duration<double>(write_timeout_s_)) != std::future_status::ready) {
    return {false, "serial write timed out for: " + command_name};
  }
  return future.get();
}

PantiltSerialControl::WriteResult PantiltSerialControl::best_effort_hold_current()
{
  Angles encoder;
  std::uint64_t sequence = 0U;
  double age_seconds = std::numeric_limits<double>::infinity();
  if (!feedback_snapshot(encoder, sequence, age_seconds) || age_seconds > feedback_timeout_s_) {
    return {false, "hold current position failed: no fresh encoder feedback"};
  }
  (void)sequence;
  const auto data = PantiltUtils::prepare_motion_data(
    encoder.heading, encoder.roll, encoder.pitch);
  if (data.empty()) {
    return {false, "hold current position failed: current encoder pose is outside command limits"};
  }
  auto result = write_command("SetPantiltAngle", data);
  if (!result.success) {
    result.message = "hold current position failed: " + result.message;
  } else {
    result.message = "hold current position command written";
  }
  return result;
}

void PantiltSerialControl::query_timer_callback()
{
  if (!serial_connected_.load()) {
    return;
  }
  const auto result = write_command("GetPantiltPose", {});
  if (!result.success) {
    set_last_error(result.message);
  }
}

void PantiltSerialControl::status_timer_callback()
{
  pantilt_camera_serial::msg::PantiltStatus msg;
  msg.header.stamp = now();
  msg.header.frame_id = frame_id_;
  msg.serial_connected = serial_connected_.load();

  Angles encoder;
  std::uint64_t sequence = 0U;
  double feedback_age = std::numeric_limits<double>::infinity();
  const bool have = feedback_snapshot(encoder, sequence, feedback_age);
  (void)sequence;
  msg.feedback_alive = have && feedback_age <= feedback_timeout_s_;

  {
    std::lock_guard<std::mutex> lock(status_mutex_);
    msg.state = motion_state_;
    if (!msg.serial_connected) {
      msg.state = pantilt_camera_serial::msg::PantiltStatus::STATE_DISCONNECTED;
      target_reached_ = false;
    } else if (!msg.feedback_alive) {
      msg.state = pantilt_camera_serial::msg::PantiltStatus::STATE_WAITING_FEEDBACK;
      target_reached_ = false;
      if (!target_active_) {
        motion_state_ = msg.state;
      }
    } else if (
      !target_active_ &&
      motion_state_ == pantilt_camera_serial::msg::PantiltStatus::STATE_WAITING_FEEDBACK)
    {
      msg.state = pantilt_camera_serial::msg::PantiltStatus::STATE_IDLE;
      motion_state_ = msg.state;
    }
    msg.target_active = target_active_;
    msg.target_reached = target_reached_;
    msg.target_heading = target_.heading;
    msg.target_roll = target_.roll;
    msg.target_pitch = target_.pitch;
    msg.max_error = max_error_;
    msg.stable_count = stable_count_;
    msg.rx_frame_count = rx_frame_count_.load();
    msg.crc_error_count = crc_error_count_.load();
    msg.protocol_error_count = protocol_error_count_.load();
    msg.last_error = last_error_;
  }
  status_publisher_->publish(msg);
}

rclcpp_action::GoalResponse PantiltSerialControl::handle_move_goal(
  const rclcpp_action::GoalUUID &,
  std::shared_ptr<const MovePantilt::Goal> goal)
{
  if (!PantiltUtils::angles_in_range(goal->heading, goal->roll, goal->pitch)) {
    RCLCPP_WARN(get_logger(), "rejecting MovePantilt goal outside mechanical limits");
    return rclcpp_action::GoalResponse::REJECT;
  }
  if (!std::isfinite(goal->tolerance) || !std::isfinite(goal->timeout) ||
    goal->tolerance < 0.0 || goal->timeout < 0.0 || goal->tolerance > max_tolerance_deg_)
  {
    RCLCPP_WARN(
      get_logger(), "rejecting MovePantilt goal: tolerance must be 0..%.2f and timeout must be finite/non-negative",
      max_tolerance_deg_);
    return rclcpp_action::GoalResponse::REJECT;
  }
  if (!serial_connected_.load()) {
    RCLCPP_WARN(get_logger(), "rejecting MovePantilt goal because serial is disconnected");
    return rclcpp_action::GoalResponse::REJECT;
  }

  bool expected = false;
  if (!action_reserved_.compare_exchange_strong(expected, true)) {
    RCLCPP_WARN(get_logger(), "rejecting MovePantilt goal because another goal is active");
    return rclcpp_action::GoalResponse::REJECT;
  }
  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse PantiltSerialControl::handle_move_cancel(
  const std::shared_ptr<GoalHandleMovePantilt>)
{
  return rclcpp_action::CancelResponse::ACCEPT;
}

void PantiltSerialControl::handle_move_accepted(
  const std::shared_ptr<GoalHandleMovePantilt> goal_handle)
{
  std::lock_guard<std::mutex> lock(action_thread_mutex_);
  if (action_thread_.joinable()) {
    action_thread_.join();
  }
  action_thread_ = std::thread(&PantiltSerialControl::execute_move, this, goal_handle);
}

void PantiltSerialControl::execute_move(
  const std::shared_ptr<GoalHandleMovePantilt> goal_handle)
{
  const auto goal = goal_handle->get_goal();
  const Angles target{goal->heading, goal->roll, goal->pitch};
  const double tolerance = goal->tolerance > 0.0 ? goal->tolerance : default_tolerance_deg_;
  const double timeout_s = goal->timeout > 0.0 ? goal->timeout : 8.0;
  const std::uint32_t stable_samples =
    goal->stable_samples > 0U ? goal->stable_samples : default_stable_samples_;
  ArrivalJudge judge(target, tolerance, stable_samples);

  {
    std::lock_guard<std::mutex> lock(status_mutex_);
    target_ = target;
    target_active_ = true;
    target_reached_ = false;
    max_error_ = 0.0;
    stable_count_ = 0U;
    motion_state_ = pantilt_camera_serial::msg::PantiltStatus::STATE_MOVING;
    last_error_.clear();
  }

  auto result = std::make_shared<MovePantilt::Result>();
  auto finalize = [this, &result](bool success, std::uint8_t code, const std::string & message) {
      result->success = success;
      result->result_code = code;
      result->message = message;
      Angles encoder;
      std::uint64_t sequence = 0U;
      double age = 0.0;
      if (feedback_snapshot(encoder, sequence, age)) {
        result->final_heading = encoder.heading;
        result->final_roll = encoder.roll;
        result->final_pitch = encoder.pitch;
      }
      {
        std::lock_guard<std::mutex> lock(status_mutex_);
        target_active_ = false;
        target_reached_ = success;
        motion_state_ = success ?
          pantilt_camera_serial::msg::PantiltStatus::STATE_REACHED :
          pantilt_camera_serial::msg::PantiltStatus::STATE_ERROR;
        if (!success) {
          last_error_ = message;
        }
      }
      action_reserved_.store(false);
    };

  const auto data = PantiltUtils::prepare_motion_data(target.heading, target.roll, target.pitch);
  if (data.empty()) {
    finalize(false, MovePantilt::Result::RESULT_INVALID_GOAL, "invalid target angles");
    goal_handle->abort(result);
    return;
  }

  const auto write = write_command("SetPantiltAngle", data);
  if (!write.success) {
    finalize(false, MovePantilt::Result::RESULT_SERIAL_ERROR, write.message);
    goal_handle->abort(result);
    return;
  }

  const auto start = std::chrono::steady_clock::now();
  std::uint64_t last_observed_sequence = 0U;
  {
    Angles encoder;
    double age = 0.0;
    feedback_snapshot(encoder, last_observed_sequence, age);
  }

  while (rclcpp::ok() && running_.load()) {
    if (goal_handle->is_canceling()) {
      const auto hold = best_effort_hold_current();
      const std::string message = hold.success ?
        "MovePantilt goal canceled; hold-current command written" :
        "MovePantilt goal canceled; " + hold.message;
      finalize(false, MovePantilt::Result::RESULT_CANCELED, message);
      goal_handle->canceled(result);
      return;
    }
    if (!serial_connected_.load()) {
      finalize(false, MovePantilt::Result::RESULT_SERIAL_ERROR, "serial disconnected during motion");
      goal_handle->abort(result);
      return;
    }

    Angles encoder;
    std::uint64_t sequence = 0U;
    double feedback_age = std::numeric_limits<double>::infinity();
    const bool have = feedback_snapshot(encoder, sequence, feedback_age);
    const auto elapsed = std::chrono::duration<double>(
      std::chrono::steady_clock::now() - start).count();

    if ((!have || sequence == last_observed_sequence) && elapsed > feedback_timeout_s_ &&
      (!have || feedback_age > feedback_timeout_s_))
    {
      finalize(false, MovePantilt::Result::RESULT_FEEDBACK_TIMEOUT, "no fresh gimbal feedback");
      goal_handle->abort(result);
      return;
    }
    if (have && feedback_age > feedback_timeout_s_) {
      finalize(false, MovePantilt::Result::RESULT_FEEDBACK_TIMEOUT, "gimbal feedback became stale");
      goal_handle->abort(result);
      return;
    }

    if (have && sequence != last_observed_sequence) {
      last_observed_sequence = sequence;
      const bool reached = judge.observe(encoder);
      const double error = judge.max_error(encoder);
      {
        std::lock_guard<std::mutex> lock(status_mutex_);
        stable_count_ = judge.stable_count();
        max_error_ = error;
        motion_state_ = judge.stable_count() > 0U ?
          pantilt_camera_serial::msg::PantiltStatus::STATE_STABILIZING :
          pantilt_camera_serial::msg::PantiltStatus::STATE_MOVING;
      }

      auto feedback = std::make_shared<MovePantilt::Feedback>();
      feedback->current_heading = encoder.heading;
      feedback->current_roll = encoder.roll;
      feedback->current_pitch = encoder.pitch;
      feedback->max_error = error;
      feedback->stable_count = judge.stable_count();
      feedback->state = judge.stable_count() > 0U ?
        MovePantilt::Feedback::STATE_STABILIZING : MovePantilt::Feedback::STATE_MOVING;
      goal_handle->publish_feedback(feedback);

      if (reached) {
        finalize(true, MovePantilt::Result::RESULT_OK, "target reached and stable");
        goal_handle->succeed(result);
        return;
      }
    }

    if (elapsed >= timeout_s) {
      const auto hold = best_effort_hold_current();
      std::ostringstream oss;
      oss << "motion timeout after " << std::fixed << std::setprecision(2) << elapsed << " s";
      if (hold.success) {
        oss << "; hold-current command written";
      } else {
        oss << "; " << hold.message;
      }
      finalize(false, MovePantilt::Result::RESULT_MOTION_TIMEOUT, oss.str());
      goal_handle->abort(result);
      return;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  finalize(false, MovePantilt::Result::RESULT_CANCELED, "driver shutting down");
  if (rclcpp::ok()) {
    goal_handle->abort(result);
  }
}

void PantiltSerialControl::set_last_error(const std::string & error)
{
  std::lock_guard<std::mutex> lock(status_mutex_);
  last_error_ = error;
}

void PantiltSerialControl::set_motion_state(
  std::uint8_t state, bool target_active, bool target_reached)
{
  std::lock_guard<std::mutex> lock(status_mutex_);
  motion_state_ = state;
  target_active_ = target_active;
  target_reached_ = target_reached;
}

bool PantiltSerialControl::feedback_snapshot(
  Angles & encoder, std::uint64_t & sequence, double & age_seconds) const
{
  std::lock_guard<std::mutex> lock(feedback_mutex_);
  if (!have_feedback_) {
    return false;
  }
  encoder = latest_encoder_;
  sequence = feedback_sequence_;
  age_seconds = std::chrono::duration<double>(
    std::chrono::steady_clock::now() - last_feedback_steady_).count();
  return true;
}

std::string PantiltSerialControl::hex_string(const std::vector<std::uint8_t> & data)
{
  std::ostringstream stream;
  stream << std::hex << std::uppercase << std::setfill('0');
  for (const auto value : data) {
    stream << std::setw(2) << static_cast<int>(value) << ' ';
  }
  return stream.str();
}

}  // namespace autolabor_driver

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<autolabor_driver::PantiltSerialControl>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
