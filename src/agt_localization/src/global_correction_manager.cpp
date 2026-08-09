#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>

#include <Eigen/Core>
#include <agt_interfaces/msg/localization_status.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <tf2/exceptions.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>

#include "agt_localization/global_correction_core.hpp"
#include "agt_localization/ros_conversions.hpp"

namespace
{

using LocalizationStatus = agt_interfaces::msg::LocalizationStatus;

bool isHealthState(std::uint8_t state)
{
  return state == LocalizationStatus::STATE_TRACKING ||
         state == LocalizationStatus::STATE_DEGRADED ||
         state == LocalizationStatus::STATE_RECOVERING ||
         state == LocalizationStatus::STATE_LOST;
}

agt_localization::CorrectionTrackingState correctionState(std::uint8_t state)
{
  if (state == LocalizationStatus::STATE_LOST) {
    return agt_localization::CorrectionTrackingState::kLost;
  }
  if (state == LocalizationStatus::STATE_RECOVERING ||
    state == LocalizationStatus::STATE_DEGRADED)
  {
    return agt_localization::CorrectionTrackingState::kRecovering;
  }
  return agt_localization::CorrectionTrackingState::kTracking;
}

std::string jsonEscape(const std::string & value)
{
  std::string output;
  output.reserve(value.size());
  for (const char character : value) {
    switch (character) {
      case '\\': output += "\\\\"; break;
      case '"': output += "\\\""; break;
      case '\n': output += "\\n"; break;
      case '\r': output += "\\r"; break;
      case '\t': output += "\\t"; break;
      default: output += character; break;
    }
  }
  return output;
}

}  // namespace

class GlobalCorrectionManager : public rclcpp::Node
{
public:
  GlobalCorrectionManager()
  : Node("global_correction_manager"),
    tf_buffer_(this->get_clock()),
    tf_listener_(tf_buffer_),
    tf_broadcaster_(std::make_unique<tf2_ros::TransformBroadcaster>(*this))
  {
    global_frame_ = declare_parameter<std::string>("global_frame", "map");
    odom_frame_ = declare_parameter<std::string>("odom_frame", "odom");
    base_frame_ = declare_parameter<std::string>("base_frame", "base_footprint");
    evidence_status_topic_ = declare_parameter<std::string>(
      "evidence_status_topic", "/agt/localization/evidence_status");
    canonical_status_topic_ = declare_parameter<std::string>(
      "canonical_status_topic", "/agt/localization/status");
    expected_map_id_ = declare_parameter<std::string>("map_id", "");
    expected_map_hash_ = declare_parameter<std::string>("map_hash", "");
    tf_publish_rate_hz_ = declare_parameter<double>("tf_publish_rate_hz", 20.0);
    tf_lookup_timeout_s_ = declare_parameter<double>("tf_lookup_timeout_s", 0.20);
    correction_rejections_to_lost_ = declare_parameter<int>(
      "correction_rejections_to_lost", 3);

    agt_localization::GlobalCorrectionPolicy policy;
    policy.max_age_s = declare_parameter<double>("max_age_s", 1.0);
    policy.future_tolerance_s = declare_parameter<double>("future_tolerance_s", 0.10);
    policy.min_interval_s = declare_parameter<double>("min_interval_s", 1.0);
    policy.max_fitness_score = declare_parameter<double>("max_fitness_score", 2.0);
    policy.max_measurement_translation_innovation_m =
      declare_parameter<double>("max_measurement_translation_innovation_m", 5.0);
    policy.max_measurement_yaw_innovation_rad =
      declare_parameter<double>("max_measurement_yaw_innovation_rad", 1.5707963267948966);
    policy.tracking.max_translation_m =
      declare_parameter<double>("tracking_max_translation_m", 0.50);
    policy.tracking.max_yaw_rad =
      declare_parameter<double>("tracking_max_yaw_rad", 0.20);
    policy.recovering.max_translation_m =
      declare_parameter<double>("recovering_max_translation_m", 2.0);
    policy.recovering.max_yaw_rad =
      declare_parameter<double>("recovering_max_yaw_rad", 0.70);
    policy.lost.max_translation_m =
      declare_parameter<double>("lost_max_translation_m", 20.0);
    policy.lost.max_yaw_rad =
      declare_parameter<double>("lost_max_yaw_rad", 3.14159265358979323846);
    policy.allow_lost_reanchor = declare_parameter<bool>("allow_lost_reanchor", true);

    if (!std::isfinite(tf_publish_rate_hz_) || tf_publish_rate_hz_ <= 0.0 ||
      !std::isfinite(tf_lookup_timeout_s_) || tf_lookup_timeout_s_ <= 0.0 ||
      correction_rejections_to_lost_ <= 0)
    {
      throw std::runtime_error("global correction manager limits must be positive");
    }

    core_ = std::make_unique<agt_localization::GlobalCorrectionCore>(policy);
    core_->setExpectedMapIdentity(expected_map_id_, expected_map_hash_);

    correction_status_pub_ = create_publisher<std_msgs::msg::String>(
      "/agt/localization/global_correction_status", 10);
    canonical_status_pub_ = create_publisher<LocalizationStatus>(canonical_status_topic_, 10);
    evidence_status_sub_ = create_subscription<LocalizationStatus>(
      evidence_status_topic_, 10,
      std::bind(&GlobalCorrectionManager::localizationEvidenceCallback, this, std::placeholders::_1));

    const auto period = std::chrono::duration<double>(1.0 / tf_publish_rate_hz_);
    tf_timer_ = create_wall_timer(
      std::chrono::duration_cast<std::chrono::nanoseconds>(period),
      std::bind(&GlobalCorrectionManager::publishTf, this));

    RCLCPP_INFO(
      get_logger(),
      "Global correction manager ready as canonical localization + map->odom authority. evidence=%s canonical=%s map_id=%s",
      evidence_status_topic_.c_str(), canonical_status_topic_.c_str(), expected_map_id_.c_str());
  }

private:
  void localizationEvidenceCallback(const LocalizationStatus::SharedPtr status)
  {
    if (!status) {
      return;
    }

    agt_localization::CorrectionTrackingState evidence_state;
    {
      std::lock_guard<std::mutex> lock(state_mutex_);
      evidence_state = policy_state_;
    }

    const bool accepted_evidence =
      status->localization_accepted && status->pose_valid &&
      status->error_code == LocalizationStatus::ERROR_NONE;
    if (!accepted_evidence) {
      if (isHealthState(status->state)) {
        std::lock_guard<std::mutex> lock(state_mutex_);
        policy_state_ = correctionState(status->state);
        if (status->state == LocalizationStatus::STATE_TRACKING) {
          consecutive_correction_rejections_ = 0;
        }
      }
      LocalizationStatus evidence = *status;
      evidence.correction_generation = 0U;
      canonical_status_pub_->publish(evidence);
      return;
    }

    const auto & global_pose = status->global_pose;
    if (global_pose.header.frame_id != global_frame_) {
      publishDecision(false, "GLOBAL_POSE_FRAME_MISMATCH", core_->generation(), 0.0, 0.0);
      publishRejectedCanonical(*status, evidence_state, "GLOBAL_POSE_FRAME_MISMATCH");
      return;
    }
    const rclcpp::Time pose_stamp(global_pose.header.stamp);
    if (pose_stamp.nanoseconds() <= 0) {
      publishDecision(false, "GLOBAL_POSE_TIMESTAMP_INVALID", core_->generation(), 0.0, 0.0);
      publishRejectedCanonical(*status, evidence_state, "GLOBAL_POSE_TIMESTAMP_INVALID");
      return;
    }

    geometry_msgs::msg::TransformStamped odom_from_base_msg;
    try {
      odom_from_base_msg = tf_buffer_.lookupTransform(
        odom_frame_, base_frame_, pose_stamp,
        rclcpp::Duration::from_seconds(tf_lookup_timeout_s_));
    } catch (const tf2::TransformException & error) {
      RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 2000,
        "Correction evidence rejected because odom->base TF is unavailable at pose stamp: %s",
        error.what());
      publishDecision(false, "ODOM_BASE_TF_UNAVAILABLE", core_->generation(), 0.0, 0.0);
      publishRejectedCanonical(*status, evidence_state, "ODOM_BASE_TF_UNAVAILABLE");
      return;
    }

    agt_localization::GlobalCorrectionObservation observation;
    observation.stamp_s = pose_stamp.seconds();
    observation.now_s = now().seconds();
    observation.map_from_base =
      agt_localization::poseMsgToEigen(global_pose.pose.pose).cast<double>();
    observation.odom_from_base =
      agt_localization::transformMsgToEigen(odom_from_base_msg).cast<double>();
    observation.fitness_score = status->fitness_score;
    observation.measurement_translation_innovation_m = status->translation_innovation;
    observation.measurement_yaw_innovation_rad = status->yaw_innovation;
    observation.map_id = status->map_id;
    observation.map_hash = status->map_hash;
    observation.localization_accepted = true;
    observation.tracking_state = evidence_state;

    const auto decision = core_->evaluate(observation);
    publishDecision(
      decision.accepted, decision.code, decision.generation,
      decision.delta_translation_m, decision.delta_yaw_rad);

    if (!decision.accepted) {
      RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 2000,
        "Rejected global correction code=%s message=%s",
        decision.code.c_str(), decision.message.c_str());
      publishRejectedCanonical(*status, evidence_state, decision.code);
      return;
    }

    {
      std::lock_guard<std::mutex> lock(transform_mutex_);
      latest_map_from_odom_ = decision.map_from_odom;
      has_transform_ = true;
    }
    tf_broadcaster_->sendTransform(
      agt_localization::eigenToTransformMsg(
        decision.map_from_odom.cast<float>(), now(), global_frame_, odom_frame_));
    {
      std::lock_guard<std::mutex> lock(state_mutex_);
      policy_state_ = correctionState(status->state);
      consecutive_correction_rejections_ = 0;
    }
    LocalizationStatus canonical = *status;
    canonical.correction_generation = decision.generation;
    canonical.localization_accepted = true;
    canonical.pose_valid = true;
    canonical_status_pub_->publish(canonical);
    RCLCPP_INFO(
      get_logger(),
      "Accepted global correction generation=%llu reanchor=%s delta_translation=%.3f delta_yaw=%.3f",
      static_cast<unsigned long long>(decision.generation),
      decision.reanchor ? "true" : "false",
      decision.delta_translation_m, decision.delta_yaw_rad);
  }

  void publishRejectedCanonical(
    const LocalizationStatus & evidence,
    agt_localization::CorrectionTrackingState previous_state,
    const std::string & code)
  {
    LocalizationStatus rejected = evidence;
    rejected.localization_accepted = false;
    rejected.pose_valid = false;
    rejected.error_code = LocalizationStatus::ERROR_BACKEND_FAILED;
    rejected.correction_generation = core_->generation();

    int rejection_count = 0;
    {
      std::lock_guard<std::mutex> lock(state_mutex_);
      ++consecutive_correction_rejections_;
      rejection_count = consecutive_correction_rejections_;
      const bool force_lost =
        previous_state == agt_localization::CorrectionTrackingState::kLost ||
        consecutive_correction_rejections_ >= correction_rejections_to_lost_;
      rejected.state = force_lost ?
        LocalizationStatus::STATE_LOST : LocalizationStatus::STATE_RECOVERING;
      policy_state_ = correctionState(rejected.state);
    }
    rejected.consecutive_failures = std::max(
      rejected.consecutive_failures, static_cast<std::uint32_t>(rejection_count));
    rejected.message = "global correction rejected: " + code;
    canonical_status_pub_->publish(rejected);
  }

  void publishDecision(
    bool accepted, const std::string & code, std::uint64_t generation,
    double delta_translation_m, double delta_yaw_rad)
  {
    std_msgs::msg::String message;
    std::ostringstream stream;
    stream << "{\"accepted\":" << (accepted ? "true" : "false")
           << ",\"code\":\"" << jsonEscape(code) << "\""
           << ",\"generation\":" << generation
           << ",\"delta_translation_m\":" << delta_translation_m
           << ",\"delta_yaw_rad\":" << delta_yaw_rad
           << "}";
    message.data = stream.str();
    correction_status_pub_->publish(message);
  }

  void publishTf()
  {
    Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
    {
      std::lock_guard<std::mutex> lock(transform_mutex_);
      if (!has_transform_) {
        return;
      }
      transform = latest_map_from_odom_;
    }
    tf_broadcaster_->sendTransform(
      agt_localization::eigenToTransformMsg(
        transform.cast<float>(), now(), global_frame_, odom_frame_));
  }

  std::string global_frame_;
  std::string odom_frame_;
  std::string base_frame_;
  std::string evidence_status_topic_;
  std::string canonical_status_topic_;
  std::string expected_map_id_;
  std::string expected_map_hash_;
  double tf_publish_rate_hz_{20.0};
  double tf_lookup_timeout_s_{0.20};
  int correction_rejections_to_lost_{3};

  std::unique_ptr<agt_localization::GlobalCorrectionCore> core_;
  Eigen::Matrix4d latest_map_from_odom_{Eigen::Matrix4d::Identity()};
  bool has_transform_{false};
  std::mutex transform_mutex_;
  agt_localization::CorrectionTrackingState policy_state_{
    agt_localization::CorrectionTrackingState::kTracking};
  int consecutive_correction_rejections_{0};
  std::mutex state_mutex_;

  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr tf_timer_;
  rclcpp::Subscription<LocalizationStatus>::SharedPtr evidence_status_sub_;
  rclcpp::Publisher<LocalizationStatus>::SharedPtr canonical_status_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr correction_status_pub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  int result = 0;
  try {
    rclcpp::spin(std::make_shared<GlobalCorrectionManager>());
  } catch (const std::exception & error) {
    RCLCPP_FATAL(
      rclcpp::get_logger("global_correction_manager"),
      "Failed to start global correction manager: %s", error.what());
    result = 1;
  }
  rclcpp::shutdown();
  return result;
}
