#include <memory>
#include <stdexcept>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>

#include "agt_sensor_adapters/navsat_fix_adapter_core.hpp"

namespace agt_sensor_adapters
{

class NavSatFixAdapter : public rclcpp::Node
{
public:
  NavSatFixAdapter()
  : Node("agt_navsat_fix_adapter")
  {
    input_topic_ = declare_parameter<std::string>("input_topic", "");
    output_topic_ = declare_parameter<std::string>(
      "output_topic", "/agt/sensors/gnss/fix");
    frame_id_ = declare_parameter<std::string>("frame_id", "gps_link");

    validateNavSatTopics(input_topic_, output_topic_);
    if (frame_id_.empty()) {
      throw std::invalid_argument("frame_id must not be empty");
    }

    const auto qos = rclcpp::SensorDataQoS();
    publisher_ = create_publisher<sensor_msgs::msg::NavSatFix>(output_topic_, qos);
    subscription_ = create_subscription<sensor_msgs::msg::NavSatFix>(
      input_topic_, qos,
      [this](sensor_msgs::msg::NavSatFix::ConstSharedPtr message) {
        publisher_->publish(normalizeNavSatFix(*message, frame_id_));
      });

    RCLCPP_INFO(
      get_logger(), "Canonical GNSS adapter: %s -> %s (frame=%s)",
      input_topic_.c_str(), output_topic_.c_str(), frame_id_.c_str());
  }

private:
  std::string input_topic_;
  std::string output_topic_;
  std::string frame_id_;
  rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr subscription_;
};

}  // namespace agt_sensor_adapters

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  try {
    rclcpp::spin(std::make_shared<agt_sensor_adapters::NavSatFixAdapter>());
  } catch (const std::exception & error) {
    auto logger = rclcpp::get_logger("agt_navsat_fix_adapter");
    RCLCPP_FATAL(logger, "%s", error.what());
    rclcpp::shutdown();
    return 2;
  }
  rclcpp::shutdown();
  return 0;
}
