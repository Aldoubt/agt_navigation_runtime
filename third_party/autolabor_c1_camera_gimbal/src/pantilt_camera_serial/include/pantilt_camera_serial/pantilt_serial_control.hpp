#ifndef PANTILT_CAMERA_SERIAL__PANTILT_SERIAL_CONTROL_HPP_
#define PANTILT_CAMERA_SERIAL__PANTILT_SERIAL_CONTROL_HPP_

#include <atomic>
#include <chrono>
#include <cstdint>
#include <future>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include "pantilt_camera_serial/action/move_pantilt.hpp"
#include "pantilt_camera_serial/arrival_judge.hpp"
#include "pantilt_camera_serial/msg/pantilt_angle_info.hpp"
#include "pantilt_camera_serial/msg/pantilt_status.hpp"
#include "pantilt_camera_serial/serial_protocol.hpp"
#include "pantilt_camera_serial/srv/pantilt_command.hpp"

namespace autolabor_driver
{

class PantiltSerialControl : public rclcpp::Node
{
public:
  using MovePantilt = pantilt_camera_serial::action::MovePantilt;
  using GoalHandleMovePantilt = rclcpp_action::ServerGoalHandle<MovePantilt>;

  explicit PantiltSerialControl(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~PantiltSerialControl() override;

private:
  struct WriteResult
  {
    bool success{false};
    std::string message;
  };

  bool initialize_serial_connection();
  void start_asynchronous_receive();
  void handle_receive(const boost::system::error_code & error, std::size_t bytes_transferred);
  void parse_and_process_frames();
  void handle_valid_frame(const std::vector<std::uint8_t> & frame);
  void handle_twist_msg(const geometry_msgs::msg::Twist::SharedPtr msg);
  void handle_send_command(
    const std::shared_ptr<pantilt_camera_serial::srv::PantiltCommand::Request> request,
    std::shared_ptr<pantilt_camera_serial::srv::PantiltCommand::Response> response);
  WriteResult write_command(const std::string & command_name, const std::vector<std::uint8_t> & data);
  WriteResult best_effort_hold_current();
  void query_timer_callback();
  void status_timer_callback();

  rclcpp_action::GoalResponse handle_move_goal(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const MovePantilt::Goal> goal);
  rclcpp_action::CancelResponse handle_move_cancel(
    const std::shared_ptr<GoalHandleMovePantilt> goal_handle);
  void handle_move_accepted(const std::shared_ptr<GoalHandleMovePantilt> goal_handle);
  void execute_move(const std::shared_ptr<GoalHandleMovePantilt> goal_handle);

  void set_last_error(const std::string & error);
  void set_motion_state(std::uint8_t state, bool target_active, bool target_reached);
  bool feedback_snapshot(Angles & encoder, std::uint64_t & sequence, double & age_seconds) const;
  static std::string hex_string(const std::vector<std::uint8_t> & data);

  std::string port_name_;
  std::string frame_id_;
  int baud_rate_{115200};
  double query_rate_{10.0};
  double feedback_timeout_s_{1.0};
  double write_timeout_s_{0.5};
  double default_tolerance_deg_{1.5};
  double max_tolerance_deg_{10.0};
  std::uint32_t default_stable_samples_{3U};

  boost::asio::io_context io_context_;
  using WorkGuard = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;
  std::unique_ptr<WorkGuard> io_work_guard_;
  std::shared_ptr<boost::asio::serial_port> port_;
  std::thread io_thread_;
  std::atomic<bool> running_{true};
  std::atomic<bool> serial_connected_{false};

  std::vector<std::uint8_t> receive_data_;
  std::vector<std::uint8_t> buffer_;
  std::size_t current_index_{0U};

  mutable std::mutex feedback_mutex_;
  bool have_feedback_{false};
  Angles latest_ground_{};
  Angles latest_encoder_{};
  std::uint64_t feedback_sequence_{0U};
  std::chrono::steady_clock::time_point last_feedback_steady_{};

  mutable std::mutex status_mutex_;
  std::uint8_t motion_state_{pantilt_camera_serial::msg::PantiltStatus::STATE_WAITING_FEEDBACK};
  bool target_active_{false};
  bool target_reached_{false};
  Angles target_{};
  double max_error_{0.0};
  std::uint32_t stable_count_{0U};
  std::string last_error_;
  std::atomic<std::uint32_t> rx_frame_count_{0U};
  std::atomic<std::uint32_t> crc_error_count_{0U};
  std::atomic<std::uint32_t> protocol_error_count_{0U};

  std::atomic<bool> action_reserved_{false};
  std::mutex action_thread_mutex_;
  std::thread action_thread_;

  rclcpp::Publisher<pantilt_camera_serial::msg::PantiltAngleInfo>::SharedPtr angle_publisher_;
  rclcpp::Publisher<pantilt_camera_serial::msg::PantiltStatus>::SharedPtr status_publisher_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_subscriber_;
  rclcpp::Service<pantilt_camera_serial::srv::PantiltCommand>::SharedPtr command_service_;
  rclcpp_action::Server<MovePantilt>::SharedPtr move_action_server_;
  rclcpp::TimerBase::SharedPtr query_timer_;
  rclcpp::TimerBase::SharedPtr status_timer_;
};

}  // namespace autolabor_driver

#endif  // PANTILT_CAMERA_SERIAL__PANTILT_SERIAL_CONTROL_HPP_
