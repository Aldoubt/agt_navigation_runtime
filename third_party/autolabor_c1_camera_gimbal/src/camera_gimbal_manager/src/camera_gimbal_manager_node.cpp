#include "camera_gimbal_manager/gimbal_state_estimator.hpp"

#include <camera_gimbal_msgs/msg/gimbal_state.hpp>
#include <pantilt_camera_serial/msg/pantilt_angle_info.hpp>
#include <rclcpp/rclcpp.hpp>

#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <mutex>
#include <string>

namespace camera_gimbal_manager
{

class CameraGimbalManager final : public rclcpp::Node
{
public:
  CameraGimbalManager()
  : Node("camera_gimbal_manager")
  {
    estimator_ = std::make_unique<GimbalStateEstimator>(
      static_cast<std::size_t>(declare_parameter<int>("filter_window_size", 5)),
      static_cast<std::size_t>(declare_parameter<int>("stable_window_size", 10)),
      declare_parameter<double>("stable_threshold_deg", 1.5),
      declare_parameter<double>("stable_duration", 0.5));
    feedback_timeout_s_ = declare_parameter<double>("feedback_timeout", 1.0);
    yaw_min_ = declare_parameter<double>("yaw_min_deg", -180.0);
    yaw_max_ = declare_parameter<double>("yaw_max_deg", 180.0);
    pitch_min_ = declare_parameter<double>("pitch_min_deg", -90.0);
    pitch_max_ = declare_parameter<double>("pitch_max_deg", 90.0);

    state_publisher_ = create_publisher<camera_gimbal_msgs::msg::GimbalState>(
      "/camera_gimbal/state", rclcpp::QoS(10).reliable());
    feedback_subscription_ = create_subscription<pantilt_camera_serial::msg::PantiltAngleInfo>(
      "/pantilt_camera_serial0/pantilt_angle_info", rclcpp::SensorDataQoS(),
      std::bind(&CameraGimbalManager::feedback_callback, this, std::placeholders::_1));
    state_timer_ = create_wall_timer(
      std::chrono::milliseconds(50), std::bind(&CameraGimbalManager::publish_state, this));
  }

private:
  void feedback_callback(const pantilt_camera_serial::msg::PantiltAngleInfo::SharedPtr msg)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    last_message_ = *msg;
    raw_ = {msg->encoder_heading, msg->encoder_roll, msg->encoder_pitch};
    target_ = {msg->heading, msg->roll, msg->pitch};
    estimator_->update(raw_, target_, GimbalStateEstimator::Clock::now());
    last_feedback_ = GimbalStateEstimator::Clock::now();
    have_feedback_ = true;
    range_valid_ = std::isfinite(raw_.heading) && std::isfinite(raw_.pitch) &&
      raw_.heading >= yaw_min_ && raw_.heading <= yaw_max_ &&
      raw_.pitch >= pitch_min_ && raw_.pitch <= pitch_max_;
  }

  bool feedback_alive_locked() const
  {
    return have_feedback_ && std::chrono::duration<double>(
      GimbalStateEstimator::Clock::now() - last_feedback_).count() <= feedback_timeout_s_;
  }

  void publish_state()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    const auto filtered = estimator_->filtered();
    const bool alive = feedback_alive_locked();
    camera_gimbal_msgs::msg::GimbalState state;
    state.stamp = last_message_.header.stamp;
    state.yaw_encoder = static_cast<float>(raw_.heading);
    state.pitch_encoder = static_cast<float>(raw_.pitch);
    state.yaw_filtered = static_cast<float>(filtered.heading);
    state.pitch_filtered = static_cast<float>(filtered.pitch);
    state.ground_roll = static_cast<float>(last_message_.roll);
    state.ground_pitch = static_cast<float>(last_message_.pitch);
    state.ground_yaw = static_cast<float>(last_message_.heading);
    state.stable = alive && range_valid_ && estimator_->stable();
    state.healthy = alive && range_valid_;
    state.status = !have_feedback_ ? "waiting_feedback" :
      !alive ? "feedback_timeout" : !range_valid_ ? "feedback_out_of_range" :
      state.stable ? "stable" : "feedback_received";
    state_publisher_->publish(state);
  }

  std::unique_ptr<GimbalStateEstimator> estimator_;
  pantilt_camera_serial::msg::PantiltAngleInfo last_message_;
  Angles raw_, target_;
  rclcpp::Publisher<camera_gimbal_msgs::msg::GimbalState>::SharedPtr state_publisher_;
  rclcpp::Subscription<pantilt_camera_serial::msg::PantiltAngleInfo>::SharedPtr feedback_subscription_;
  rclcpp::TimerBase::SharedPtr state_timer_;
  mutable std::mutex mutex_;
  GimbalStateEstimator::TimePoint last_feedback_{};
  double feedback_timeout_s_{1.0};
  double yaw_min_{-180.0}, yaw_max_{180.0}, pitch_min_{-90.0}, pitch_max_{90.0};
  bool have_feedback_{false}, range_valid_{false};
};

}  // namespace camera_gimbal_manager

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<camera_gimbal_manager::CameraGimbalManager>());
  rclcpp::shutdown();
  return 0;
}
