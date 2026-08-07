#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "agt_sensor_adapters/self_filter_geometry.hpp"
#include "agt_sensor_adapters/urdf_self_filter_geometry.hpp"
#include "diagnostic_msgs/msg/diagnostic_array.hpp"
#include "diagnostic_msgs/msg/diagnostic_status.hpp"
#include "livox_ros_driver2/msg/custom_msg.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/point_cloud2_iterator.hpp"
#include "std_msgs/msg/string.hpp"
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

struct PreparedPrimitive
{
  const agt_sensor_adapters::UrdfCollisionPrimitive * primitive{nullptr};
  tf2::Transform geometry_from_reference;
};

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
    geometry_source_ = declare_parameter<std::string>("geometry_source", "urdf");
    urdf_reference_frame_ = declare_parameter<std::string>("urdf_reference_frame", "base_link");
    robot_description_topic_ = declare_parameter<std::string>(
      "robot_description_topic", "/robot_description");
    enabled_parameter_ = declare_parameter<bool>("enabled", true);
    transform_timeout_sec_ = declare_parameter<double>("transform_timeout_sec", 0.10);
    zero_point_epsilon_ = declare_parameter<double>("zero_point_epsilon", 1.0e-6);
    fail_open_on_tf_error_ = declare_parameter<bool>("fail_open_on_tf_error", false);
    publish_removed_points_ = declare_parameter<bool>("publish_removed_points", false);
    removed_points_topic_ = declare_parameter<std::string>(
      "removed_points_topic", "/agt/sensors/lidar/self_filter/removed_points");
    publish_filter_geometry_ = declare_parameter<bool>("publish_filter_geometry", true);
    filter_geometry_topic_ = declare_parameter<std::string>(
      "filter_geometry_topic", "/agt/sensors/lidar/self_filter/geometry");
    diagnostics_topic_ = declare_parameter<std::string>("diagnostics_topic", "/diagnostics");
    const auto queue_depth = declare_parameter<int>("queue_depth", 200000);

    if (geometry_source_ != "urdf" && geometry_source_ != "profile") {
      throw std::runtime_error("geometry_source must be either 'urdf' or 'profile'");
    }
    if (urdf_reference_frame_.empty()) {
      throw std::runtime_error("urdf_reference_frame must be non-empty");
    }
    if (robot_description_topic_.empty()) {
      throw std::runtime_error("robot_description_topic must be non-empty");
    }
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
      profile_geometry_ = agt_sensor_adapters::load_self_filter_geometry(profile_path);
    } catch (const std::exception & error) {
      RCLCPP_FATAL(get_logger(), "self-filter profile validation failed: %s", error.what());
      throw;
    }
    expanded_profile_boxes_ = profile_geometry_.expanded_boxes();
    supplemental_boxes_ = profile_geometry_.expanded_supplemental_boxes();
    filtering_enabled_ = enabled_parameter_ && profile_geometry_.enabled;

    diagnostics_publisher_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>(
      diagnostics_topic_, rclcpp::QoS(10));
    if (publish_filter_geometry_) {
      geometry_publisher_ = create_publisher<visualization_msgs::msg::MarkerArray>(
        filter_geometry_topic_, rclcpp::QoS(1).reliable().transient_local());
    }
    if (publish_removed_points_) {
      removed_points_publisher_ = create_publisher<sensor_msgs::msg::PointCloud2>(
        removed_points_topic_, rclcpp::SensorDataQoS());
    }

    if (geometry_source_ == "urdf") {
      robot_description_subscription_ = create_subscription<std_msgs::msg::String>(
        robot_description_topic_, rclcpp::QoS(1).reliable().transient_local(),
        std::bind(&LivoxCustomSelfFilter::robot_description_callback, this, std::placeholders::_1));
    }

    // A best-effort input subscription accepts both live sensor and rosbag QoS.
    // FAST-LIVO2 receives a reliable output because its native subscription is reliable.
    const auto input_qos = rclcpp::SensorDataQoS().keep_last(queue_depth);
    const auto output_qos = rclcpp::QoS(rclcpp::KeepLast(queue_depth)).reliable();
    publisher_ = create_publisher<CustomMsg>(output_topic_, output_qos);
    subscription_ = create_subscription<CustomMsg>(
      input_topic_, input_qos,
      std::bind(&LivoxCustomSelfFilter::filter_callback, this, std::placeholders::_1));

    if (geometry_source_ == "profile" && geometry_publisher_) {
      publish_filter_geometry();
    }

    RCLCPP_INFO(
      get_logger(),
      "self-filter configured; enabled=%s, geometry_source=%s, profile_frame=%s, "
      "profile_boxes=%zu, supplemental_boxes=%zu, padding=%.3f m",
      filtering_enabled_ ? "true" : "false", geometry_source_.c_str(),
      profile_geometry_.frame.c_str(), expanded_profile_boxes_.size(), supplemental_boxes_.size(),
      profile_geometry_.padding);
  }

private:
  bool geometry_ready() const
  {
    return geometry_source_ == "profile" || urdf_geometry_ready_;
  }

  std::string filter_reference_frame() const
  {
    return geometry_source_ == "urdf" ? urdf_reference_frame_ : profile_geometry_.frame;
  }

  bool lookup_transform(
    const std::string & target_frame, const std::string & source_frame,
    const builtin_interfaces::msg::Time & stamp, tf2::Transform & transform, std::string & error)
  {
    if (target_frame.empty() || source_frame.empty()) {
      error = "target/source frame must be non-empty";
      return false;
    }
    if (source_frame == target_frame) {
      transform.setIdentity();
      return true;
    }

    try {
      const auto transform_message = tf_buffer_.lookupTransform(
        target_frame, source_frame, rclcpp::Time(stamp),
        tf2::durationFromSec(transform_timeout_sec_));
      tf2::fromMsg(transform_message.transform, transform);
      return true;
    } catch (const tf2::TransformException & exception) {
      error = exception.what();
      return false;
    }
  }

  bool prepare_urdf_primitives(
    const builtin_interfaces::msg::Time & stamp, std::vector<PreparedPrimitive> & prepared,
    std::string & error)
  {
    prepared.clear();
    prepared.reserve(urdf_geometry_.primitives.size());
    std::unordered_map<std::string, tf2::Transform> reference_from_link;

    for (const auto & primitive : urdf_geometry_.primitives) {
      auto transform_it = reference_from_link.find(primitive.link_name);
      if (transform_it == reference_from_link.end()) {
        tf2::Transform transform;
        if (!lookup_transform(
            urdf_reference_frame_, primitive.link_name, stamp, transform, error))
        {
          error = "URDF link TF unavailable for " + primitive.link_name + ": " + error;
          return false;
        }
        transform_it = reference_from_link.emplace(primitive.link_name, transform).first;
      }

      tf2::Transform link_from_geometry;
      link_from_geometry.setOrigin(tf2::Vector3(
        primitive.origin_xyz[0], primitive.origin_xyz[1], primitive.origin_xyz[2]));
      link_from_geometry.setRotation(tf2::Quaternion(
        primitive.origin_xyzw[0], primitive.origin_xyzw[1], primitive.origin_xyzw[2],
        primitive.origin_xyzw[3]));

      const tf2::Transform reference_from_geometry =
        transform_it->second * link_from_geometry;
      prepared.push_back({&primitive, reference_from_geometry.inverse()});
    }
    return true;
  }

  void robot_description_callback(const std_msgs::msg::String::ConstSharedPtr message)
  {
    try {
      const auto parsed = agt_sensor_adapters::parse_urdf_self_filter_geometry(message->data);
      urdf_geometry_ = parsed;
      urdf_geometry_ready_ = true;
      urdf_geometry_error_.clear();
      if (geometry_publisher_) {
        publish_filter_geometry();
      }
      RCLCPP_INFO(
        get_logger(), "loaded %zu URDF collision primitives from %s",
        urdf_geometry_.primitives.size(), robot_description_topic_.c_str());
    } catch (const std::exception & error) {
      urdf_geometry_ready_ = false;
      urdf_geometry_error_ = error.what();
      ++geometry_failure_count_;
      RCLCPP_ERROR(
        get_logger(), "rejecting robot_description for self-filter: %s", error.what());
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

    if (!geometry_ready()) {
      ++geometry_failure_count_;
      const std::string reason = urdf_geometry_error_.empty() ?
        "waiting for valid robot_description" : urdf_geometry_error_;
      RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 5000,
        "self-filter geometry unavailable; %s", reason.c_str());
      if (fail_open_on_tf_error_) {
        publisher_->publish(*message);
      }
      const auto elapsed = std::chrono::duration<double, std::milli>(
        std::chrono::steady_clock::now() - started).count();
      publish_diagnostics(
        message->header.frame_id, input_count, fail_open_on_tf_error_ ? input_count : 0,
        0, 0, 0, elapsed, false,
        fail_open_on_tf_error_ ? "geometry unavailable; fail-open passthrough" :
        "geometry unavailable; frame dropped");
      return;
    }

    const std::string reference_frame = filter_reference_frame();
    tf2::Transform reference_from_source;
    std::string tf_error;
    if (!lookup_transform(
        reference_frame, message->header.frame_id, message->header.stamp,
        reference_from_source, tf_error))
    {
      ++tf_failure_count_;
      RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 5000,
        "dropping CustomMsg because %s <- %s TF is unavailable: %s",
        reference_frame.c_str(), message->header.frame_id.c_str(), tf_error.c_str());
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

    std::vector<PreparedPrimitive> prepared_primitives;
    if (geometry_source_ == "urdf" &&
      !prepare_urdf_primitives(message->header.stamp, prepared_primitives, tf_error))
    {
      ++tf_failure_count_;
      RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 5000, "dropping CustomMsg: %s", tf_error.c_str());
      if (fail_open_on_tf_error_) {
        publisher_->publish(*message);
      }
      const auto elapsed = std::chrono::duration<double, std::milli>(
        std::chrono::steady_clock::now() - started).count();
      publish_diagnostics(
        message->header.frame_id, input_count, fail_open_on_tf_error_ ? input_count : 0, 0, 0,
        0, elapsed, false, fail_open_on_tf_error_ ? "URDF TF failure; fail-open passthrough" :
        "URDF TF failure; frame dropped");
      return;
    }

    tf2::Transform profile_from_reference;
    profile_from_reference.setIdentity();
    if (geometry_source_ == "urdf" && !supplemental_boxes_.empty() &&
      profile_geometry_.frame != reference_frame)
    {
      if (!lookup_transform(
          profile_geometry_.frame, reference_frame, message->header.stamp,
          profile_from_reference, tf_error))
      {
        ++tf_failure_count_;
        RCLCPP_WARN_THROTTLE(
          get_logger(), *get_clock(), 5000,
          "dropping CustomMsg because supplemental geometry TF is unavailable: %s",
          tf_error.c_str());
        if (fail_open_on_tf_error_) {
          publisher_->publish(*message);
        }
        const auto elapsed = std::chrono::duration<double, std::milli>(
          std::chrono::steady_clock::now() - started).count();
        publish_diagnostics(
          message->header.frame_id, input_count, fail_open_on_tf_error_ ? input_count : 0,
          0, 0, 0, elapsed, false,
          fail_open_on_tf_error_ ? "supplemental TF failure; fail-open passthrough" :
          "supplemental TF failure; frame dropped");
        return;
      }
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

      const auto reference_point = reference_from_source * tf2::Vector3(
        source_point[0], source_point[1], source_point[2]);
      if (!std::isfinite(reference_point.x()) || !std::isfinite(reference_point.y()) ||
        !std::isfinite(reference_point.z()))
      {
        ++removed_non_finite;
        continue;
      }

      bool inside_self_geometry = false;
      if (geometry_source_ == "profile") {
        const std::array<double, 3> transformed_point{
          reference_point.x(), reference_point.y(), reference_point.z()};
        inside_self_geometry = std::any_of(
          expanded_profile_boxes_.begin(), expanded_profile_boxes_.end(),
          [&transformed_point](const auto & box) { return box.contains(transformed_point); });
      } else {
        for (const auto & prepared : prepared_primitives) {
          const auto local_point = prepared.geometry_from_reference * reference_point;
          if (prepared.primitive->contains_local(
              {local_point.x(), local_point.y(), local_point.z()}, profile_geometry_.padding))
          {
            inside_self_geometry = true;
            break;
          }
        }
        if (!inside_self_geometry && !supplemental_boxes_.empty()) {
          const auto profile_point = profile_from_reference * reference_point;
          const std::array<double, 3> transformed_profile_point{
            profile_point.x(), profile_point.y(), profile_point.z()};
          inside_self_geometry = std::any_of(
            supplemental_boxes_.begin(), supplemental_boxes_.end(),
            [&transformed_profile_point](const auto & box) {
              return box.contains(transformed_profile_point);
            });
        }
      }

      if (inside_self_geometry) {
        ++removed_self;
        if (publish_removed_points_) {
          removed_points.push_back(reference_point);
        }
        continue;
      }
      kept_indices.push_back(index);
    }

    // Preserve the original Livox coordinates and all per-point timing/tag fields.
    filtered.points = agt_sensor_adapters::copy_points_in_order(message->points, kept_indices);
    filtered.point_num = static_cast<uint32_t>(filtered.points.size());
    publisher_->publish(filtered);

    if (publish_removed_points_ && removed_points_publisher_) {
      publish_removed_cloud(message->header.stamp, reference_frame, removed_points);
    }
    const auto elapsed = std::chrono::duration<double, std::milli>(
      std::chrono::steady_clock::now() - started).count();
    publish_diagnostics(
      message->header.frame_id, input_count, filtered.points.size(), removed_self,
      removed_non_finite, removed_invalid, elapsed, true, "filtering active");
  }

  void publish_removed_cloud(
    const builtin_interfaces::msg::Time & stamp, const std::string & frame,
    const std::vector<tf2::Vector3> & points)
  {
    sensor_msgs::msg::PointCloud2 cloud;
    cloud.header.stamp = stamp;
    cloud.header.frame_id = frame;
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

  visualization_msgs::msg::Marker make_box_marker(
    const agt_sensor_adapters::AxisAlignedBox & box, int marker_id) const
  {
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = profile_geometry_.frame;
    marker.header.stamp = now();
    marker.ns = "agt_livox_self_filter_profile";
    marker.id = marker_id;
    marker.type = visualization_msgs::msg::Marker::CUBE;
    marker.action = visualization_msgs::msg::Marker::ADD;
    marker.pose.orientation.w = 1.0;
    marker.pose.position.x = (box.min[0] + box.max[0]) / 2.0;
    marker.pose.position.y = (box.min[1] + box.max[1]) / 2.0;
    marker.pose.position.z = (box.min[2] + box.max[2]) / 2.0;
    marker.scale.x = box.max[0] - box.min[0];
    marker.scale.y = box.max[1] - box.min[1];
    marker.scale.z = box.max[2] - box.min[2];
    marker.color.a = 0.25F;
    marker.color.r = box.generated_from_platform_body ? 0.1F : 1.0F;
    marker.color.g = box.generated_from_platform_body ? 0.9F : 0.55F;
    marker.color.b = box.generated_from_platform_body ? 0.2F : 0.05F;
    return marker;
  }

  visualization_msgs::msg::Marker make_urdf_marker(
    const agt_sensor_adapters::UrdfCollisionPrimitive & primitive, int marker_id) const
  {
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = primitive.link_name;
    marker.header.stamp = now();
    marker.ns = "agt_livox_self_filter_urdf";
    marker.id = marker_id;
    marker.action = visualization_msgs::msg::Marker::ADD;
    marker.pose.position.x = primitive.origin_xyz[0];
    marker.pose.position.y = primitive.origin_xyz[1];
    marker.pose.position.z = primitive.origin_xyz[2];
    marker.pose.orientation.x = primitive.origin_xyzw[0];
    marker.pose.orientation.y = primitive.origin_xyzw[1];
    marker.pose.orientation.z = primitive.origin_xyzw[2];
    marker.pose.orientation.w = primitive.origin_xyzw[3];
    marker.color.a = 0.25F;
    marker.color.r = 0.1F;
    marker.color.g = 0.9F;
    marker.color.b = 0.2F;

    switch (primitive.type) {
      case agt_sensor_adapters::UrdfPrimitiveType::BOX:
        marker.type = visualization_msgs::msg::Marker::CUBE;
        marker.scale.x = primitive.dimensions[0] + 2.0 * profile_geometry_.padding;
        marker.scale.y = primitive.dimensions[1] + 2.0 * profile_geometry_.padding;
        marker.scale.z = primitive.dimensions[2] + 2.0 * profile_geometry_.padding;
        break;
      case agt_sensor_adapters::UrdfPrimitiveType::SPHERE:
        marker.type = visualization_msgs::msg::Marker::SPHERE;
        marker.scale.x = 2.0 * (primitive.dimensions[0] + profile_geometry_.padding);
        marker.scale.y = marker.scale.x;
        marker.scale.z = marker.scale.x;
        break;
      case agt_sensor_adapters::UrdfPrimitiveType::CYLINDER:
        marker.type = visualization_msgs::msg::Marker::CYLINDER;
        marker.scale.x = 2.0 * (primitive.dimensions[0] + profile_geometry_.padding);
        marker.scale.y = marker.scale.x;
        marker.scale.z = primitive.dimensions[1] + 2.0 * profile_geometry_.padding;
        break;
    }
    return marker;
  }

  void publish_filter_geometry()
  {
    if (!geometry_publisher_) {
      return;
    }

    visualization_msgs::msg::MarkerArray markers;
    visualization_msgs::msg::Marker clear;
    clear.header.frame_id = filter_reference_frame();
    clear.header.stamp = now();
    clear.ns = "agt_livox_self_filter";
    clear.id = 0;
    clear.action = visualization_msgs::msg::Marker::DELETEALL;
    markers.markers.push_back(clear);

    int marker_id = 1;
    if (geometry_source_ == "profile") {
      for (const auto & box : expanded_profile_boxes_) {
        markers.markers.push_back(make_box_marker(box, marker_id++));
      }
    } else if (urdf_geometry_ready_) {
      for (const auto & primitive : urdf_geometry_.primitives) {
        markers.markers.push_back(make_urdf_marker(primitive, marker_id++));
      }
      for (const auto & box : supplemental_boxes_) {
        markers.markers.push_back(make_box_marker(box, marker_id++));
      }
    }
    geometry_publisher_->publish(markers);
  }

  void publish_diagnostics(
    const std::string & input_frame, std::size_t input_count, std::size_t output_count,
    std::size_t removed_self, std::size_t removed_non_finite, std::size_t removed_invalid,
    double elapsed_ms, bool healthy, const std::string & message)
  {
    diagnostic_msgs::msg::DiagnosticArray array;
    array.header.stamp = now();
    diagnostic_msgs::msg::DiagnosticStatus status;
    status.name = "agt_livox_self_filter";
    status.hardware_id = "self_filter";
    status.level = healthy ? diagnostic_msgs::msg::DiagnosticStatus::OK :
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

    add("geometry_source", geometry_source_);
    add("geometry_ready", geometry_ready() ? "true" : "false");
    add("filter_reference_frame", filter_reference_frame());
    add("profile_frame", profile_geometry_.frame);
    add("input_frame", input_frame);
    add("output_message_frame", input_frame);
    add("urdf_primitive_count", std::to_string(urdf_geometry_.primitives.size()));
    add("supplemental_box_count", std::to_string(supplemental_boxes_.size()));
    add("input_point_count", std::to_string(input_count));
    add("output_point_count", std::to_string(output_count));
    add("removed_self_point_count", std::to_string(removed_self));
    add("removed_non_finite_count", std::to_string(removed_non_finite));
    add("removed_invalid_point_count", std::to_string(removed_invalid));
    add("removal_ratio", std::to_string(removal_ratio));
    add("tf_failure_count", std::to_string(tf_failure_count_));
    add("geometry_failure_count", std::to_string(geometry_failure_count_));
    add("filter_time_ms", std::to_string(elapsed_ms));
    add("has_unverified_supplemental_geometry",
      profile_geometry_.has_unverified_box() ? "true" : "false");
    add("filtering_enabled", filtering_enabled_ ? "true" : "false");
    if (!urdf_geometry_error_.empty()) {
      add("urdf_geometry_error", urdf_geometry_error_);
    }
    array.status.push_back(status);
    diagnostics_publisher_->publish(array);
  }

  std::string input_topic_;
  std::string output_topic_;
  std::string geometry_source_;
  std::string urdf_reference_frame_;
  std::string robot_description_topic_;
  std::string removed_points_topic_;
  std::string filter_geometry_topic_;
  std::string diagnostics_topic_;
  std::string urdf_geometry_error_;
  bool enabled_parameter_{true};
  bool filtering_enabled_{false};
  bool urdf_geometry_ready_{false};
  bool fail_open_on_tf_error_{false};
  bool publish_removed_points_{false};
  bool publish_filter_geometry_{true};
  double transform_timeout_sec_{0.10};
  double zero_point_epsilon_{1.0e-6};
  std::size_t tf_failure_count_{0};
  std::size_t geometry_failure_count_{0};
  agt_sensor_adapters::SelfFilterGeometry profile_geometry_;
  agt_sensor_adapters::UrdfSelfFilterGeometry urdf_geometry_;
  std::vector<agt_sensor_adapters::AxisAlignedBox> expanded_profile_boxes_;
  std::vector<agt_sensor_adapters::AxisAlignedBox> supplemental_boxes_;
  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;
  rclcpp::Publisher<CustomMsg>::SharedPtr publisher_;
  rclcpp::Subscription<CustomMsg>::SharedPtr subscription_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr robot_description_subscription_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr removed_points_publisher_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr geometry_publisher_;
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
