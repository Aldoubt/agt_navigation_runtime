#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "agt_sensor_adapters/self_filter_geometry.hpp"
#include "diagnostic_msgs/msg/diagnostic_array.hpp"
#include "diagnostic_msgs/msg/diagnostic_status.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "livox_ros_driver2/msg/custom_msg.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/point_cloud2_iterator.hpp"
#include "tf2/convert.h"
#include "tf2/transform_datatypes.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2/time.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "visualization_msgs/msg/marker_array.hpp"

namespace
{

using CustomMsg = livox_ros_driver2::msg::CustomMsg;

class LivoxCustomSelfFilter final : public rclcpp::Node
{
public:
  LivoxCustomSelfFilter()
  : Node("agt_livox_self_filter"), tf_buffer_(get_clock()), tf_listener_(tf_buffer_)
  {
    input_topic_ = declare_parameter<std::string>("input_topic", "/agt/sensors/lidar/custom");
    output_topic_ = declare_parameter<std::string>(
      "output_topic", "/agt/sensors/lidar/custom_filtered");
    const auto profile_path = declare_parameter<std::string>("platform_profile", "");
    enabled_parameter_ = declare_parameter<bool>("enabled", true);
    transform_timeout_sec_ = declare_parameter<double>("transform_timeout_sec", 0.10);
    zero_point_epsilon_ = declare_parameter<double>("zero_point_epsilon", 1.0e-6);
    fail_open_on_tf_error_ = declare_parameter<bool>("fail_open_on_tf_error", false);
    publish_removed_points_ = declare_parameter<bool>("publish_removed_points", false);
    removed_points_topic_ = declare_parameter<std::string>(
      "removed_points_topic", "/agt/sensors/lidar/self_filter/removed_points");
    publish_filter_boxes_ = declare_parameter<bool>("publish_filter_boxes", true);
    filter_boxes_topic_ = declare_parameter<std::string>(
      "filter_boxes_topic", "/agt/sensors/lidar/self_filter/boxes");
    diagnostics_topic_ = declare_parameter<std::string>("diagnostics_topic", "/diagnostics");
    const auto queue_depth = declare_parameter<int>("queue_depth", 200000);
    if (queue_depth <= 0) {
      throw std::runtime_error("queue_depth must be a positive integer");
    }
    if (!std::isfinite(transform_timeout_sec_) || transform_timeout_sec_ < 0.0) {
      throw std::runtime_error("transform_timeout_sec must be finite and >= 0");
    }
    if (!std::isfinite(zero_point_epsilon_) || zero_point_epsilon_ < 0.0) {
      throw std::runtime_error("zero_point_epsilon must be finite and >= 0");
    }

    try {
      geometry_ = agt_sensor_adapters::load_self_filter_geometry(profile_path);
    } catch (const std::exception & error) {
      RCLCPP_FATAL(get_logger(), "self-filter profile validation failed: %s", error.what());
      throw;
    }
    expanded_boxes_ = geometry_.expanded_boxes();
    filtering_enabled_ = enabled_parameter_ && geometry_.enabled;

    diagnostics_publisher_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>(
      diagnostics_topic_, rclcpp::QoS(10));
    if (publish_filter_boxes_) {
      boxes_publisher_ = create_publisher<visualization_msgs::msg::MarkerArray>(
        filter_boxes_topic_, rclcpp::QoS(1).reliable().transient_local());
    }
    if (publish_removed_points_) {
      removed_points_publisher_ = create_publisher<sensor_msgs::msg::PointCloud2>(
        removed_points_topic_, rclcpp::SensorDataQoS());
    }

    // A best-effort input subscription accepts both live sensor and rosbag QoS.
    // FAST-LIVO2 receives a reliable output because its native subscription is reliable.
    const auto input_qos = rclcpp::SensorDataQoS().keep_last(queue_depth);
    const auto output_qos = rclcpp::QoS(rclcpp::KeepLast(queue_depth)).reliable();
    publisher_ = create_publisher<CustomMsg>(output_topic_, output_qos);
    subscription_ = create_subscription<CustomMsg>(
      input_topic_, input_qos,
      std::bind(&LivoxCustomSelfFilter::filter_callback, this, std::placeholders::_1));

    if (boxes_publisher_) {
      publish_filter_boxes();
    }
    RCLCPP_INFO(
      get_logger(), "loaded self-filter profile; enabled=%s, frame=%s, boxes=%zu, padding=%.3f m",
      filtering_enabled_ ? "true" : "false", geometry_.frame.c_str(), expanded_boxes_.size(),
      geometry_.padding);
  }

private:
  bool lookup_transform(
    const std::string & source_frame, const builtin_interfaces::msg::Time & stamp,
    tf2::Transform & transform, std::string & error)
  {
    if (source_frame.empty()) {
      error = "input header.frame_id is empty";
      return false;
    }
    if (source_frame == geometry_.frame) {
      transform.setIdentity();
      return true;
    }
    const auto cached = transform_cache_.find(source_frame);
    if (cached != transform_cache_.end()) {
      transform = cached->second;
      return true;
    }

    try {
      const auto transform_message = tf_buffer_.lookupTransform(
        geometry_.frame, source_frame, rclcpp::Time(stamp),
        tf2::durationFromSec(transform_timeout_sec_));
      tf2::fromMsg(transform_message.transform, transform);
      transform_cache_.emplace(source_frame, transform);
      return true;
    } catch (const tf2::TransformException & exception) {
      error = exception.what();
      return false;
    }
  }

  void filter_callback(const CustomMsg::ConstSharedPtr message)
  {
    const auto started = std::chrono::steady_clock::now();
    const std::size_t input_count = message->points.size();

    if (!filtering_enabled_) {
      publisher_->publish(*message);
      publish_diagnostics(
        message->header.frame_id, input_count, input_count, 0, 0, 0, 0.0, true,
        "disabled passthrough");
      return;
    }

    tf2::Transform transform;
    std::string tf_error;
    if (!lookup_transform(message->header.frame_id, message->header.stamp, transform, tf_error)) {
      ++tf_failure_count_;
      RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 5000,
        "dropping CustomMsg because %s <- %s TF is unavailable: %s",
        geometry_.frame.c_str(), message->header.frame_id.c_str(), tf_error.c_str());
      if (fail_open_on_tf_error_) {
        publisher_->publish(*message);
      }
      const auto elapsed = std::chrono::duration<double, std::milli>(
        std::chrono::steady_clock::now() - started).count();
      publish_diagnostics(
        message->header.frame_id, input_count, fail_open_on_tf_error_ ? input_count : 0, 0, 0,
        0, elapsed, false, fail_open_on_tf_error_ ? "TF failure; fail-open passthrough" :
        "TF failure; frame dropped");
      return;
    }

    CustomMsg filtered = *message;
    filtered.points.clear();
    filtered.points.reserve(message->points.size());
    std::vector<tf2::Vector3> removed_points;
    if (publish_removed_points_) {
      removed_points.reserve(message->points.size());
    }
    std::size_t removed_self = 0;
    std::size_t removed_non_finite = 0;
    std::size_t removed_invalid = 0;
    std::vector<std::size_t> kept_indices;
    kept_indices.reserve(message->points.size());
    for (std::size_t index = 0; index < message->points.size(); ++index) {
      const auto & point = message->points[index];
      const std::array<double, 3> source_point{
        static_cast<double>(point.x), static_cast<double>(point.y), static_cast<double>(point.z)};
      if (!std::isfinite(source_point[0]) || !std::isfinite(source_point[1]) ||
        !std::isfinite(source_point[2]))
      {
        ++removed_non_finite;
        continue;
      }
      if (std::abs(source_point[0]) <= zero_point_epsilon_ &&
        std::abs(source_point[1]) <= zero_point_epsilon_ &&
        std::abs(source_point[2]) <= zero_point_epsilon_)
      {
        ++removed_invalid;
        continue;
      }
      const auto base_point = transform * tf2::Vector3(
        source_point[0], source_point[1], source_point[2]);
      const std::array<double, 3> transformed_point{
        base_point.x(), base_point.y(), base_point.z()};
      if (!std::isfinite(transformed_point[0]) || !std::isfinite(transformed_point[1]) ||
        !std::isfinite(transformed_point[2]))
      {
        ++removed_non_finite;
        continue;
      }
      const bool inside_filter_box = std::any_of(
        expanded_boxes_.begin(), expanded_boxes_.end(),
        [&transformed_point](const auto & box) { return box.contains(transformed_point); });
      if (inside_filter_box) {
        ++removed_self;
        if (publish_removed_points_) {
          removed_points.push_back(base_point);
        }
        continue;
      }
      kept_indices.push_back(index);
    }
    filtered.points = agt_sensor_adapters::copy_points_in_order(message->points, kept_indices);
    filtered.point_num = static_cast<uint32_t>(filtered.points.size());
    publisher_->publish(filtered);

    if (publish_removed_points_ && removed_points_publisher_) {
      publish_removed_cloud(message->header.stamp, removed_points);
    }
    const auto elapsed = std::chrono::duration<double, std::milli>(
      std::chrono::steady_clock::now() - started).count();
    publish_diagnostics(
      message->header.frame_id, input_count, filtered.points.size(), removed_self,
      removed_non_finite, removed_invalid, elapsed, true, "filtering active");
  }

  void publish_removed_cloud(
    const builtin_interfaces::msg::Time & stamp, const std::vector<tf2::Vector3> & points)
  {
    sensor_msgs::msg::PointCloud2 cloud;
    cloud.header.stamp = stamp;
    cloud.header.frame_id = geometry_.frame;
    sensor_msgs::PointCloud2Modifier modifier(cloud);
    modifier.setPointCloud2FieldsByString(1, "xyz");
    modifier.resize(points.size());
    sensor_msgs::PointCloud2Iterator<float> x(cloud, "x");
    sensor_msgs::PointCloud2Iterator<float> y(cloud, "y");
    sensor_msgs::PointCloud2Iterator<float> z(cloud, "z");
    for (const auto & point : points) {
      *x = static_cast<float>(point.x());
      *y = static_cast<float>(point.y());
      *z = static_cast<float>(point.z());
      ++x;
      ++y;
      ++z;
    }
    removed_points_publisher_->publish(cloud);
  }

  void publish_filter_boxes()
  {
    visualization_msgs::msg::MarkerArray markers;
    markers.markers.reserve(expanded_boxes_.size());
    int marker_id = 0;
    for (const auto & box : expanded_boxes_) {
      visualization_msgs::msg::Marker marker;
      marker.header.frame_id = geometry_.frame;
      marker.header.stamp = now();
      marker.ns = "agt_livox_self_filter";
      marker.id = marker_id++;
      marker.type = visualization_msgs::msg::Marker::CUBE;
      marker.action = visualization_msgs::msg::Marker::ADD;
      marker.pose.orientation.w = 1.0;
      marker.pose.position.x = (box.min[0] + box.max[0]) / 2.0;
      marker.pose.position.y = (box.min[1] + box.max[1]) / 2.0;
      marker.pose.position.z = (box.min[2] + box.max[2]) / 2.0;
      marker.scale.x = box.max[0] - box.min[0];
      marker.scale.y = box.max[1] - box.min[1];
      marker.scale.z = box.max[2] - box.min[2];
      marker.color.a = 0.25;
      if (box.name == "chassis_body") {
        marker.color.r = 0.1F;
        marker.color.g = 0.9F;
        marker.color.b = 0.2F;
      } else {
        marker.color.r = 1.0F;
        marker.color.g = 0.55F;
        marker.color.b = 0.05F;
      }
      markers.markers.push_back(marker);
    }
    boxes_publisher_->publish(markers);
  }

  void publish_diagnostics(
    const std::string & input_frame, std::size_t input_count, std::size_t output_count,
    std::size_t removed_self, std::size_t removed_non_finite, std::size_t removed_invalid,
    double elapsed_ms, bool tf_ok, const std::string & message)
  {
    diagnostic_msgs::msg::DiagnosticArray array;
    array.header.stamp = now();
    diagnostic_msgs::msg::DiagnosticStatus status;
    status.name = "agt_livox_self_filter";
    status.hardware_id = "platform_self_filter";
    status.level = tf_ok ? diagnostic_msgs::msg::DiagnosticStatus::OK :
      (fail_open_on_tf_error_ ? diagnostic_msgs::msg::DiagnosticStatus::WARN :
      diagnostic_msgs::msg::DiagnosticStatus::ERROR);
    status.message = message;
    auto add = [&status](const std::string & key, const std::string & value) {
        diagnostic_msgs::msg::KeyValue item;
        item.key = key;
        item.value = value;
        status.values.push_back(item);
      };
    const double removal_ratio = input_count == 0 ? 0.0 :
      static_cast<double>(removed_self + removed_non_finite + removed_invalid) /
      static_cast<double>(input_count);
    add("profile", "loaded");
    add("profile_frame", geometry_.frame);
    add("input_frame", input_frame);
    add("output_frame", geometry_.frame);
    add("input_point_count", std::to_string(input_count));
    add("output_point_count", std::to_string(output_count));
    add("removed_self_point_count", std::to_string(removed_self));
    add("removed_non_finite_count", std::to_string(removed_non_finite));
    add("removed_invalid_point_count", std::to_string(removed_invalid));
    add("removal_ratio", std::to_string(removal_ratio));
    add("tf_failure_count", std::to_string(tf_failure_count_));
    add("filter_time_ms", std::to_string(elapsed_ms));
    add("has_unverified_geometry", geometry_.has_unverified_box() ? "true" : "false");
    add("filtering_enabled", filtering_enabled_ ? "true" : "false");
    array.status.push_back(status);
    diagnostics_publisher_->publish(array);
  }

  std::string input_topic_;
  std::string output_topic_;
  std::string removed_points_topic_;
  std::string filter_boxes_topic_;
  std::string diagnostics_topic_;
  bool enabled_parameter_{true};
  bool filtering_enabled_{false};
  bool fail_open_on_tf_error_{false};
  bool publish_removed_points_{false};
  bool publish_filter_boxes_{true};
  double transform_timeout_sec_{0.10};
  double zero_point_epsilon_{1.0e-6};
  std::size_t tf_failure_count_{0};
  agt_sensor_adapters::SelfFilterGeometry geometry_;
  std::vector<agt_sensor_adapters::AxisAlignedBox> expanded_boxes_;
  std::unordered_map<std::string, tf2::Transform> transform_cache_;
  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;
  rclcpp::Publisher<CustomMsg>::SharedPtr publisher_;
  rclcpp::Subscription<CustomMsg>::SharedPtr subscription_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr removed_points_publisher_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr boxes_publisher_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr diagnostics_publisher_;
};

}  // namespace

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LivoxCustomSelfFilter>());
  rclcpp::shutdown();
  return 0;
}
