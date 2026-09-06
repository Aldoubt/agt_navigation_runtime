#include <camera_gimbal_msgs/action/acquire_view.hpp>
#include <camera_gimbal_msgs/msg/gimbal_state.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgcodecs.hpp>
#include <pantilt_camera_serial/action/move_pantilt.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <sensor_msgs/msg/image.hpp>

#include <chrono>
#include <cmath>
#include <ctime>
#include <filesystem>
#include <functional>
#include <iomanip>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

namespace camera_capture_manager
{
using AcquireView = camera_gimbal_msgs::action::AcquireView;
using MovePantilt = pantilt_camera_serial::action::MovePantilt;
using GoalHandle = rclcpp_action::ServerGoalHandle<AcquireView>;

class Node final : public rclcpp::Node
{
public:
  Node()
  : rclcpp::Node("camera_capture_manager")
  {
    motion_timeout_ = declare_parameter<double>("motion_timeout", 8.0);
    image_timeout_ = declare_parameter<double>("image_timeout", 3.0);
    state_timeout_ = declare_parameter<double>("state_timeout", 1.0);
    move_client_ = rclcpp_action::create_client<MovePantilt>(this, "/pantilt_camera_serial0/move_pantilt");
    state_sub_ = create_subscription<camera_gimbal_msgs::msg::GimbalState>(
      "/camera_gimbal/state", rclcpp::QoS(10).reliable(),
      std::bind(&Node::state_callback, this, std::placeholders::_1));
    image_sub_ = create_subscription<sensor_msgs::msg::Image>(
      "/cv_camera0/image_raw", rclcpp::SensorDataQoS(),
      std::bind(&Node::image_callback, this, std::placeholders::_1));
    server_ = rclcpp_action::create_server<AcquireView>(
      this, "/camera_gimbal/acquire_view",
      std::bind(&Node::goal_callback, this, std::placeholders::_1, std::placeholders::_2),
      std::bind(&Node::cancel_callback, this, std::placeholders::_1),
      std::bind(&Node::accepted_callback, this, std::placeholders::_1));
  }

private:
  rclcpp_action::GoalResponse goal_callback(
    const rclcpp_action::GoalUUID &, std::shared_ptr<const AcquireView::Goal> goal)
  {
    if (!std::isfinite(goal->yaw) || !std::isfinite(goal->pitch) || goal->settle_timeout < 0.0) {
      return rclcpp_action::GoalResponse::REJECT;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    return active_ ? rclcpp_action::GoalResponse::REJECT :
      rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse cancel_callback(const std::shared_ptr<GoalHandle>)
  {
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void accepted_callback(const std::shared_ptr<GoalHandle> handle)
  {
    std::thread([this, handle]() {execute(handle);}).detach();
  }

  void state_callback(const camera_gimbal_msgs::msg::GimbalState::SharedPtr msg)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    state_ = *msg;
    last_state_receive_ = std::chrono::steady_clock::now();
    have_state_ = true;
  }

  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    last_image_ = msg;
  }

  void feedback(const std::shared_ptr<GoalHandle> & handle, const std::string & phase, bool stable)
  {
    auto message = std::make_shared<AcquireView::Feedback>();
    message->state = phase;
    message->stable = stable;
    std::lock_guard<std::mutex> lock(mutex_);
    message->current_yaw = state_.yaw_filtered;
    message->current_pitch = state_.pitch_filtered;
    handle->publish_feedback(message);
  }

  bool state_alive_locked() const
  {
    return have_state_ && std::chrono::duration<double>(
      std::chrono::steady_clock::now() - last_state_receive_).count() <= state_timeout_;
  }

  void finish(const std::shared_ptr<GoalHandle> & handle,
    const std::shared_ptr<AcquireView::Result> & result, bool success, const std::string & message)
  {
    result->success = success;
    result->message = message;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      result->yaw = state_.yaw_filtered;
      result->pitch = state_.pitch_filtered;
      active_ = false;
    }
    if (success) handle->succeed(result); else handle->abort(result);
  }

  static std::string angle_text(float value)
  {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(0) << value;
    return stream.str();
  }

  void execute(const std::shared_ptr<GoalHandle> & handle)
  {
    const auto goal = handle->get_goal();
    auto result = std::make_shared<AcquireView::Result>();
    {std::lock_guard<std::mutex> lock(mutex_); active_ = true;}
    feedback(handle, "MOVING", false);
    if (!move_client_->wait_for_action_server(std::chrono::duration<double>(motion_timeout_))) {
      finish(handle, result, false, "MovePantilt action unavailable"); return;
    }
    MovePantilt::Goal move;
    move.heading = goal->yaw; move.pitch = goal->pitch; move.roll = 0.0;
    move.timeout = motion_timeout_; move.tolerance = 1.5; move.stable_samples = 3;
    auto send = move_client_->async_send_goal(move);
    if (send.wait_for(std::chrono::duration<double>(motion_timeout_)) != std::future_status::ready) {
      finish(handle, result, false, "MovePantilt goal timeout"); return;
    }
    auto move_handle = send.get();
    if (!move_handle) {finish(handle, result, false, "MovePantilt goal rejected"); return;}
    auto move_result = move_client_->async_get_result(move_handle);
    if (move_result.wait_for(std::chrono::duration<double>(motion_timeout_)) != std::future_status::ready) {
      finish(handle, result, false, "gimbal motion timeout"); return;
    }
    if (!move_result.get().result->success) {finish(handle, result, false, "gimbal motion failed"); return;}

    feedback(handle, "SETTLING", false);
    const double settle = goal->settle_timeout > 0.0 ? goal->settle_timeout : 0.5;
    std::this_thread::sleep_for(std::chrono::duration<double>(settle));
    const auto stable_deadline = std::chrono::steady_clock::now() + std::chrono::duration<double>(motion_timeout_);
    rclcpp::Time stable_stamp;
    bool stable = false;
    while (std::chrono::steady_clock::now() < stable_deadline && rclcpp::ok()) {
      {std::lock_guard<std::mutex> lock(mutex_);
        stable = state_alive_locked() && state_.stable &&
          std::abs(state_.yaw_filtered - goal->yaw) < 1.5 &&
          std::abs(state_.pitch_filtered - goal->pitch) < 1.5;
        if (stable) stable_stamp = now();}
      feedback(handle, "STABLE_CHECK", stable);
      if (stable) break;
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    if (!stable) {finish(handle, result, false, "gimbal did not become stable"); return;}

    feedback(handle, "WAITING_IMAGE", true);
    const auto image_deadline = std::chrono::steady_clock::now() + std::chrono::duration<double>(image_timeout_);
    sensor_msgs::msg::Image::SharedPtr image;
    while (std::chrono::steady_clock::now() < image_deadline && rclcpp::ok()) {
      {std::lock_guard<std::mutex> lock(mutex_); image = last_image_;}
      if (image && rclcpp::Time(image->header.stamp) > stable_stamp) break;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    if (!image || rclcpp::Time(image->header.stamp) <= stable_stamp) {
      finish(handle, result, false, "no image newer than stable timestamp"); return;
    }
    try {
      std::filesystem::create_directories(goal->save_dir);
      const auto stamp = image->header.stamp;
      std::time_t seconds = static_cast<std::time_t>(stamp.sec);
      std::tm local_stamp{};
      localtime_r(&seconds, &local_stamp);
      std::ostringstream filename;
      filename << goal->save_dir << "/capture_" << std::put_time(&local_stamp, "%Y%m%d_%H%M%S")
        << "_yaw" << angle_text(goal->yaw)
        << "_pitch" << angle_text(goal->pitch) << ".jpg";
      if (!cv::imwrite(filename.str(), cv_bridge::toCvCopy(image, "bgr8")->image)) {
        throw std::runtime_error("cv::imwrite failed");
      }
      result->image_path = filename.str(); result->image_stamp = image->header.stamp;
    } catch (const std::exception & error) {
      finish(handle, result, false, error.what()); return;
    }
    finish(handle, result, true, "view captured");
  }

  std::shared_ptr<GoalHandle> active_handle_;
  camera_gimbal_msgs::msg::GimbalState state_;
  sensor_msgs::msg::Image::SharedPtr last_image_;
  rclcpp_action::Client<MovePantilt>::SharedPtr move_client_;
  rclcpp_action::Server<AcquireView>::SharedPtr server_;
  rclcpp::Subscription<camera_gimbal_msgs::msg::GimbalState>::SharedPtr state_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
  mutable std::mutex mutex_;
  std::chrono::steady_clock::time_point last_state_receive_{};
  double motion_timeout_{8.0}, image_timeout_{3.0}, state_timeout_{1.0};
  bool have_state_{false}, active_{false};
};
}  // namespace camera_capture_manager

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<camera_capture_manager::Node>());
  rclcpp::shutdown();
  return 0;
}
