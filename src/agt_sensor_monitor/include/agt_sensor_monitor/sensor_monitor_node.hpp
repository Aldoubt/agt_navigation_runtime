#pragma once

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>

#ifdef AGT_SENSOR_MONITOR_HAS_LIVOX
#include <livox_ros_driver2/msg/custom_msg.hpp>
#endif

#include "agt_sensor_monitor/stream_monitor.hpp"

namespace agt_sensor_monitor
{
class SensorMonitorNode : public rclcpp::Node
{
public:
  SensorMonitorNode();

private:
  void publish_diagnostics();
  template<typename MessageT> void observe(const MessageT & message, StreamMonitor & monitor)
  {
    monitor.observe(rclcpp::Time(message.header.stamp).seconds(), steady_now());
  }
  double steady_now() const;
  double startup_elapsed() const;
  void add_stream(const std::string & key, const std::string & parameter);
  void add_lidar_subscription(const std::string & key);

  std::vector<std::pair<std::string, std::unique_ptr<StreamMonitor>>> streams_;
  std::vector<rclcpp::SubscriptionBase::SharedPtr> subscriptions_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::size_t window_size_;
  double startup_grace_sec_;
  double rollback_tolerance_sec_;
  rclcpp::Time start_ros_;
  std::chrono::steady_clock::time_point start_steady_;
};
}  // namespace agt_sensor_monitor
