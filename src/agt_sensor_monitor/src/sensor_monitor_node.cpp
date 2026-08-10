#include "agt_sensor_monitor/sensor_monitor_node.hpp"

#include <chrono>
#include <limits>
#include <stdexcept>
#include <utility>

#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include <rclcpp/qos.hpp>

namespace agt_sensor_monitor
{
namespace
{
using Status = diagnostic_msgs::msg::DiagnosticStatus;
double stamp_of(const builtin_interfaces::msg::Time & stamp) { return rclcpp::Time(stamp).seconds(); }
}

SensorMonitorNode::SensorMonitorNode()
: Node("agt_sensor_monitor"), window_size_(static_cast<std::size_t>(declare_parameter("rate_window_size", 50))),
  startup_grace_sec_(declare_parameter("startup_grace_sec", 3.0)),
  rollback_tolerance_sec_(declare_parameter("timestamp_rollback_tolerance_sec", 1e-6)),
  start_ros_(get_clock()->now()), start_steady_(std::chrono::steady_clock::now())
{
  declare_parameter("publish_rate_hz", 2.0);
  const auto add = [this](const std::string & key) { add_stream(key, key); };
  add("lidar");
  add("filtered_lidar");
  add("imu");
  add("camera");
  add("camera_info");
  add("gnss");
  publisher_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/diagnostics", 10);

  auto find = [this](const std::string & key) -> StreamMonitor * {
    for (auto & item : streams_) if (item.first == key) return item.second.get();
    return nullptr;
  };
  auto qos = rclcpp::SensorDataQoS();

  add_lidar_subscription("lidar");
  add_lidar_subscription("filtered_lidar");

  if (auto * m = find("imu"); m && m->config().enabled) subscriptions_.push_back(
    create_subscription<sensor_msgs::msg::Imu>(m->config().topic, qos,
      [m](sensor_msgs::msg::Imu::ConstSharedPtr msg) { m->observe(stamp_of(msg->header.stamp), rclcpp::Clock(RCL_STEADY_TIME).now().seconds()); }));
  if (auto * m = find("camera"); m && m->config().enabled) subscriptions_.push_back(
    create_subscription<sensor_msgs::msg::Image>(m->config().topic, qos,
      [m](sensor_msgs::msg::Image::ConstSharedPtr msg) { m->observe(stamp_of(msg->header.stamp), rclcpp::Clock(RCL_STEADY_TIME).now().seconds()); }));
  if (auto * m = find("camera_info"); m && m->config().enabled) subscriptions_.push_back(
    create_subscription<sensor_msgs::msg::CameraInfo>(m->config().topic, qos,
      [m](sensor_msgs::msg::CameraInfo::ConstSharedPtr msg) { m->observe(stamp_of(msg->header.stamp), rclcpp::Clock(RCL_STEADY_TIME).now().seconds()); }));
  if (auto * m = find("gnss"); m && m->config().enabled) subscriptions_.push_back(
    create_subscription<sensor_msgs::msg::NavSatFix>(m->config().topic, qos,
      [m](sensor_msgs::msg::NavSatFix::ConstSharedPtr msg) { m->observe(stamp_of(msg->header.stamp), rclcpp::Clock(RCL_STEADY_TIME).now().seconds()); }));
  const double rate = get_parameter("publish_rate_hz").as_double();
  if (rate <= 0.0) throw std::invalid_argument("publish_rate_hz must be positive");
  timer_ = create_wall_timer(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(1.0 / rate)),
    std::bind(&SensorMonitorNode::publish_diagnostics, this));
}

void SensorMonitorNode::add_stream(const std::string & key, const std::string & parameter)
{
  const std::string prefix = parameter + ".";
  StreamConfig config;
  config.name = key;
  config.enabled = declare_parameter(prefix + "enabled", key == "lidar" || key == "filtered_lidar" || key == "imu");
  config.required = declare_parameter(prefix + "required", key == "lidar" || key == "filtered_lidar" || key == "imu");
  config.topic = declare_parameter(prefix + "topic", std::string("/agt/sensors/") + key);
  config.min_rate_hz = declare_parameter(prefix + "min_rate_hz", 0.0);
  config.max_stale_sec = declare_parameter(prefix + "max_stale_sec", 1.0);
  config.max_message_age_sec = declare_parameter(prefix + "max_message_age_sec", 1.0);
  config.duplicate_fatal = declare_parameter(prefix + "duplicate_fatal", false);
  config.rollback_fatal = declare_parameter(prefix + "rollback_fatal", true);
  streams_.emplace_back(key, std::make_unique<StreamMonitor>(config, window_size_, rollback_tolerance_sec_));
}

void SensorMonitorNode::add_lidar_subscription(const std::string & key)
{
  StreamMonitor * monitor = nullptr;
  for (auto & item : streams_) {
    if (item.first == key) {
      monitor = item.second.get();
      break;
    }
  }
  if (monitor == nullptr || !monitor->config().enabled) {
    return;
  }

  const std::string message_type = declare_parameter<std::string>(
    key + ".message_type", "livox_custom");
  auto qos = rclcpp::SensorDataQoS();
  if (message_type == "laser_scan") {
    subscriptions_.push_back(
      create_subscription<sensor_msgs::msg::LaserScan>(
        monitor->config().topic, qos,
        [monitor](sensor_msgs::msg::LaserScan::ConstSharedPtr msg) {
          monitor->observe(
            stamp_of(msg->header.stamp),
            rclcpp::Clock(RCL_STEADY_TIME).now().seconds());
        }));
    RCLCPP_INFO(
      get_logger(), "Monitoring %s as sensor_msgs/LaserScan on %s",
      key.c_str(), monitor->config().topic.c_str());
    return;
  }

  if (message_type == "livox_custom") {
#ifdef AGT_SENSOR_MONITOR_HAS_LIVOX
    subscriptions_.push_back(
      create_subscription<livox_ros_driver2::msg::CustomMsg>(
        monitor->config().topic, qos,
        [monitor](livox_ros_driver2::msg::CustomMsg::ConstSharedPtr msg) {
          monitor->observe(
            stamp_of(msg->header.stamp),
            rclcpp::Clock(RCL_STEADY_TIME).now().seconds());
        }));
    RCLCPP_INFO(
      get_logger(), "Monitoring %s as livox_ros_driver2/CustomMsg on %s",
      key.c_str(), monitor->config().topic.c_str());
    return;
#else
    throw std::runtime_error(
      key + ".message_type=livox_custom requested but agt_sensor_monitor was built "
      "without livox_ros_driver2; install/source the Livox driver or select laser_scan");
#endif
  }

  throw std::invalid_argument(
    key + ".message_type must be one of: livox_custom, laser_scan");
}

double SensorMonitorNode::steady_now() const { return rclcpp::Clock(RCL_STEADY_TIME).now().seconds(); }
double SensorMonitorNode::startup_elapsed() const { return std::chrono::duration<double>(std::chrono::steady_clock::now() - start_steady_).count(); }

void SensorMonitorNode::publish_diagnostics()
{
  const auto ros_now = get_clock()->now();
  const double elapsed = startup_elapsed();
  diagnostic_msgs::msg::DiagnosticArray array;
  array.header.stamp = ros_now;
  int worst = Status::OK;
  for (const auto & item : streams_) {
    const auto result = item.second->status(ros_now.seconds(), steady_now(), elapsed, startup_grace_sec_);
    Status status;
    status.name = "agt_sensor_monitor/" + item.first;
    status.level = !result.enabled ? Status::OK : (result.healthy ? Status::OK :
      (elapsed < startup_grace_sec_ ? Status::WARN : (result.required ? Status::ERROR : Status::WARN)));
    worst = std::max(worst, static_cast<int>(status.level));
    auto add = [&status](const std::string & key, const std::string & value) { diagnostic_msgs::msg::KeyValue kv; kv.key = key; kv.value = value; status.values.push_back(kv); };
    auto number = [&add](const std::string & key, double value) { add(key, std::to_string(value)); };
    auto boolean = [&add](const std::string & key, bool value) { add(key, value ? "true" : "false"); };
    boolean("enabled", result.enabled); boolean("required", result.required); boolean("received_once", result.received_once);
    add("received_count", std::to_string(result.received_count)); number("rate_hz", result.estimated_rate_hz);
    number("min_rate_hz", item.second->config().min_rate_hz); boolean("rate_ok", result.rate_ok);
    number("message_age_sec", result.message_age_sec); number("receive_age_sec", result.receive_age_sec);
    number("max_stale_sec", item.second->config().max_stale_sec); boolean("stale", result.stale);
    boolean("timestamp_monotonic", result.timestamp_monotonic); add("rollback_count", std::to_string(result.rollback_count));
    add("duplicate_stamp_count", std::to_string(result.duplicate_stamp_count)); boolean("healthy", result.healthy);
    status.message = !result.enabled ? "disabled" : (result.healthy ? "healthy" : "stream unhealthy");
    array.status.push_back(status);
  }
  Status summary; summary.name = "agt_sensor_monitor/summary"; summary.level = static_cast<std::uint8_t>(worst);
  summary.message = worst == Status::OK ? "OK" : worst == Status::WARN ? "WARN" : "ERROR";
  diagnostic_msgs::msg::KeyValue kv; kv.key = "required_streams_healthy"; kv.value = worst < Status::ERROR ? "true" : "false"; summary.values.push_back(kv);
  array.status.push_back(summary);
  publisher_->publish(array);
}
}  // namespace agt_sensor_monitor

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<agt_sensor_monitor::SensorMonitorNode>());
  rclcpp::shutdown();
  return 0;
}
