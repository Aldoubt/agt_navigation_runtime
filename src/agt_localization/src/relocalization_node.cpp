#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <exception>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <Eigen/Geometry>
#include <pcl/common/transforms.h>
#include <pcl_conversions/pcl_conversions.h>

#include <agt_interfaces/action/relocalize.hpp>
#include <agt_interfaces/msg/localization_status.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <rcl_interfaces/msg/integer_range.hpp>
#include <rcl_interfaces/msg/parameter_descriptor.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <std_msgs/msg/string.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>

#include "agt_localization/candidate_provider.hpp"
#include "agt_localization/localization_timing.hpp"
#include "agt_localization/map_readiness.hpp"
#include "agt_localization/localization_supervisor.hpp"
#include "agt_localization/quality_validator.hpp"
#include "agt_localization/ros_conversions.hpp"
#include "agt_localization/tracking_validation.hpp"
#include "relocalization_core/relocalizer.hpp"

namespace
{

using Relocalize = agt_interfaces::action::Relocalize;
using GoalHandleRelocalize = rclcpp_action::ServerGoalHandle<Relocalize>;
using LocalizationStatus = agt_interfaces::msg::LocalizationStatus;
using Candidate = agt_localization::Candidate;
using CloudT = relocalization_core::CloudT;

const rcl_interfaces::msg::ParameterDescriptor & ndtNumThreadsDescriptor()
{
  static const auto descriptor = []() {
      rcl_interfaces::msg::ParameterDescriptor value;
      value.description = "NDT-OMP worker threads; must be at least 1";
      rcl_interfaces::msg::IntegerRange range;
      range.from_value = 1;
      range.to_value = std::numeric_limits<int>::max();
      range.step = 1;
      value.integer_range.push_back(range);
      return value;
    }();
  return descriptor;
}

bool isFinite(double value)
{
  return std::isfinite(value);
}

bool poseIsValid(const geometry_msgs::msg::Pose & pose)
{
  return isFinite(pose.position.x) && isFinite(pose.position.y) &&
    isFinite(pose.position.z) && isFinite(pose.orientation.x) &&
    isFinite(pose.orientation.y) && isFinite(pose.orientation.z) &&
    isFinite(pose.orientation.w) &&
    std::sqrt(
    pose.orientation.x * pose.orientation.x +
    pose.orientation.y * pose.orientation.y +
    pose.orientation.z * pose.orientation.z +
    pose.orientation.w * pose.orientation.w) > 1.0e-6;
}

double normalizeYaw(double yaw)
{
  constexpr double pi = 3.14159265358979323846;
  constexpr double two_pi = 2.0 * pi;
  while (yaw > pi) {
    yaw -= two_pi;
  }
  while (yaw < -pi) {
    yaw += two_pi;
  }
  return yaw;
}

double matrixYaw(const Eigen::Matrix4f & transform)
{
  return std::atan2(
    static_cast<double>(transform(1, 0)), static_cast<double>(transform(0, 0)));
}

Eigen::Matrix4f candidateToPose(const Candidate & candidate)
{
  Eigen::Matrix4f pose = Eigen::Matrix4f::Identity();
  pose.block<3, 3>(0, 0) =
    Eigen::AngleAxisf(static_cast<float>(candidate.yaw), Eigen::Vector3f::UnitZ()).toRotationMatrix();
  pose(0, 3) = static_cast<float>(candidate.x);
  pose(1, 3) = static_cast<float>(candidate.y);
  pose(2, 3) = static_cast<float>(candidate.z);
  return pose;
}

geometry_msgs::msg::Pose poseFromEigen(const Eigen::Matrix4f & transform)
{
  geometry_msgs::msg::Pose pose;
  const Eigen::Quaternionf quaternion(transform.block<3, 3>(0, 0));
  pose.position.x = transform(0, 3);
  pose.position.y = transform(1, 3);
  pose.position.z = transform(2, 3);
  pose.orientation.x = quaternion.x();
  pose.orientation.y = quaternion.y();
  pose.orientation.z = quaternion.z();
  pose.orientation.w = quaternion.w();
  return pose;
}

Candidate candidateFromPose(
  const geometry_msgs::msg::Pose & pose,
  const std::string & id,
  const std::string & source,
  const std::string & map_id,
  const std::string & map_hash,
  int priority = 0,
  double covariance_score = 0.0)
{
  Candidate candidate;
  const auto transform = agt_localization::poseMsgToEigen(pose);
  candidate.id = id;
  candidate.source = source;
  candidate.map_id = map_id;
  candidate.map_hash = map_hash;
  candidate.x = transform(0, 3);
  candidate.y = transform(1, 3);
  candidate.z = transform(2, 3);
  candidate.yaw = matrixYaw(transform);
  candidate.priority = priority;
  candidate.covariance_score = covariance_score;
  return candidate;
}

std::uint16_t coreErrorCode(const relocalization_core::RelocalizationResult & result)
{
  using StatusCode = relocalization_core::RelocalizationStatusCode;
  switch (result.status_code) {
    case StatusCode::kMapNotReady:
      return LocalizationStatus::ERROR_MAP_NOT_READY;
    case StatusCode::kScanTooSmall:
      return LocalizationStatus::ERROR_SCAN_TOO_SMALL;
    case StatusCode::kFitnessRejected:
      return LocalizationStatus::ERROR_FITNESS_REJECTED;
    case StatusCode::kInvalidInitialGuess:
      return LocalizationStatus::ERROR_INVALID_INITIAL_GUESS;
    case StatusCode::kBackendFailed:
      return LocalizationStatus::ERROR_BACKEND_FAILED;
    case StatusCode::kOk:
      return LocalizationStatus::ERROR_NONE;
    default:
      return LocalizationStatus::ERROR_BACKEND_FAILED;
  }
}

std::string statusText(const LocalizationStatus & status)
{
  return
    "state=" + std::to_string(status.state) +
    " error=" + std::to_string(status.error_code) +
    " accepted=" + std::string(status.localization_accepted ? "true" : "false") +
    " candidate=" + status.candidate_id +
    " fitness=" + std::to_string(status.fitness_score) +
    " message=" + status.message;
}

std::uint8_t toLocalizationState(agt_localization::SupervisorState state)
{
  return static_cast<std::uint8_t>(state);
}

}  // namespace

class RelocalizationNode : public rclcpp::Node
{
public:
  RelocalizationNode()
  : Node("relocalization_node"),
    tf_buffer_(this->get_clock()),
    tf_listener_(tf_buffer_)
  {
    global_map_pcd_ = declare_parameter<std::string>("global_map_pcd", "");
    global_map_processing_record_ = declare_parameter<std::string>(
      "global_map_processing_record", "");
    global_frame_ = declare_parameter<std::string>("global_frame", "map");
    odom_frame_ = declare_parameter<std::string>("odom_frame", "odom");
    base_frame_ = declare_parameter<std::string>("base_frame", "base_link");
    tracking_frame_ = declare_parameter<std::string>("tracking_frame", "lidar_link");
    cloud_topic_ = declare_parameter<std::string>(
      "cloud_topic", "/agt/mapping/registered_points");
    initialpose_topic_ = declare_parameter<std::string>("initialpose_topic", "/initialpose");
    relocalize_action_name_ = declare_parameter<std::string>(
      "relocalize_action_name", "/agt/localization/relocalize");
    configured_candidates_yaml_ = declare_parameter<std::string>(
      "configured_candidates_yaml", "");
    last_valid_pose_path_ = declare_parameter<std::string>("last_valid_pose_path", "");
    external_coarse_pose_topic_ = declare_parameter<std::string>(
      "external_coarse_pose_topic", "/agt/localization/coarse_pose");
    manual_initialpose_enabled_ = declare_parameter<bool>(
      "manual_initialpose_enabled", true);
    map_id_ = declare_parameter<std::string>("map_id", "");
    map_hash_ = declare_parameter<std::string>("map_hash", "");
    publish_tf_ = declare_parameter<bool>("publish_tf", true);
    publish_aligned_cloud_ = declare_parameter<bool>("publish_aligned_cloud", true);
    candidate_max_ = declare_parameter<int>("candidate_max", 128);
    max_expanded_candidates_ = declare_parameter<int>("max_expanded_candidates", 4096);
    candidate_position_dedup_tolerance_ =
      declare_parameter<double>("candidate_position_dedup_tolerance", 1.0e-3);
    candidate_yaw_dedup_tolerance_ =
      declare_parameter<double>("candidate_yaw_dedup_tolerance", 1.0e-3);
    ambiguity_ratio_ = declare_parameter<double>("ambiguity_ratio", 0.10);
    action_timeout_s_ = declare_parameter<double>("action_timeout_s", 30.0);
    external_coarse_max_age_s_ = declare_parameter<double>(
      "external_coarse_max_age_s", 2.0);
    external_coarse_future_tolerance_s_ = declare_parameter<double>(
      "external_coarse_future_tolerance_s", 0.5);
    max_cloud_age_s_ = declare_parameter<double>("max_cloud_age_s", 0.5);
    max_cloud_future_tolerance_s_ = declare_parameter<double>(
      "max_cloud_future_tolerance_s", 0.1);
    require_nonzero_cloud_stamp_ = declare_parameter<bool>(
      "require_nonzero_cloud_stamp", true);
    max_translation_innovation_ =
      declare_parameter<double>("max_translation_innovation", 5.0);
    max_yaw_innovation_ =
      declare_parameter<double>("max_yaw_innovation", 1.5707963267948966);
    tracking_validation_enabled_ = declare_parameter<bool>(
      "tracking_validation_enabled", true);
    tracking_validation_period_s_ = declare_parameter<double>(
      "tracking_validation_period_s", 5.0);
    tracking_validation_timeout_s_ = declare_parameter<double>(
      "tracking_validation_timeout_s", 3.0);
    const auto tracking_confirmations_required = declare_parameter<int>(
      "tracking_confirmations_required", 1);
    const auto tracking_failures_to_recover = declare_parameter<int>(
      "tracking_failures_to_recover", 2);
    const auto tracking_failures_to_lost = declare_parameter<int>(
      "tracking_failures_to_lost", 3);

    if (candidate_max_ <= 0 || max_expanded_candidates_ <= 0 ||
      candidate_max_ > max_expanded_candidates_)
    {
      throw std::runtime_error(
              "candidate_max and max_expanded_candidates must be positive and ordered");
    }
    if (!isFinite(action_timeout_s_) || action_timeout_s_ <= 0.0 ||
      !isFinite(ambiguity_ratio_) || ambiguity_ratio_ < 0.0 ||
      !isFinite(external_coarse_max_age_s_) || external_coarse_max_age_s_ <= 0.0 ||
      !isFinite(external_coarse_future_tolerance_s_) ||
      external_coarse_future_tolerance_s_ < 0.0 ||
      !isFinite(max_cloud_age_s_) || max_cloud_age_s_ <= 0.0 ||
      !isFinite(max_cloud_future_tolerance_s_) || max_cloud_future_tolerance_s_ < 0.0)
    {
      throw std::runtime_error("action timeout and ambiguity ratio must be valid");
    }
    if (tracking_confirmations_required != 1) {
      throw std::runtime_error(
              "tracking_confirmations_required currently supports only 1; "
              "multi-frame bootstrap confirmation is not implemented");
    }
    if (!isFinite(tracking_validation_period_s_) || tracking_validation_period_s_ <= 0.0 ||
      !isFinite(tracking_validation_timeout_s_) || tracking_validation_timeout_s_ <= 0.0 ||
      tracking_failures_to_recover <= 0 ||
      tracking_failures_to_lost <= 0 || tracking_failures_to_recover > tracking_failures_to_lost)
    {
      throw std::runtime_error("tracking validation configuration is invalid");
    }
    agt_localization::SupervisorConfig supervisor_config;
    supervisor_config.confirmations_required =
      static_cast<std::size_t>(tracking_confirmations_required);
    supervisor_config.failures_to_recover =
      static_cast<std::size_t>(tracking_failures_to_recover);
    supervisor_config.failures_to_lost =
      static_cast<std::size_t>(tracking_failures_to_lost);
    supervisor_.setConfig(supervisor_config);

    relocalization_core::RelocalizerConfig config;
    config.backend = parseBackend(
      declare_parameter<std::string>("backend", "ndt"));
    config.map_voxel_leaf_size = declare_parameter<double>("map_voxel_leaf_size", 0.25);
    config.scan_voxel_leaf_size = declare_parameter<double>("scan_voxel_leaf_size", 0.25);
    config.min_scan_points = declare_parameter<int>("min_scan_points", 200);
    config.fitness_score_threshold = declare_parameter<double>("fitness_score_threshold", 2.0);
    config.max_iterations = declare_parameter<int>("max_iterations", 100);
    config.transform_epsilon = declare_parameter<double>("transform_epsilon", 1e-6);
    config.euclidean_fitness_epsilon =
      declare_parameter<double>("euclidean_fitness_epsilon", 1e-6);
    config.max_correspondence_distance =
      declare_parameter<double>("max_correspondence_distance", 3.0);
    config.crop_box.enabled = declare_parameter<bool>("crop_box_enabled", true);
    config.crop_box.frame_mode = parseCropMode(
      declare_parameter<std::string>("crop_box_frame_mode", "scan_local"));
    config.crop_box.x_min = declare_parameter<double>("crop_x_min", 0.0);
    config.crop_box.x_max = declare_parameter<double>("crop_x_max", 30.0);
    config.crop_box.y_min = declare_parameter<double>("crop_y_min", -15.0);
    config.crop_box.y_max = declare_parameter<double>("crop_y_max", 15.0);
    config.crop_box.z_min = declare_parameter<double>("crop_z_min", -2.0);
    config.crop_box.z_max = declare_parameter<double>("crop_z_max", 2.0);
    config.ndt.resolution = declare_parameter<double>("ndt_resolution", 1.0);
    config.ndt.step_size = declare_parameter<double>("ndt_step_size", 0.1);
    config.ndt.num_threads = declare_parameter<int>(
      "ndt_num_threads", relocalization_core::kDefaultNdtNumThreads,
      ndtNumThreadsDescriptor());
    if (config.ndt.num_threads <= 0) {
      throw std::runtime_error("ndt_num_threads must be positive");
    }
    config.ndt.search_method = parseNdtSearchMethod(
      declare_parameter<std::string>("ndt_search_method", "DIRECT7"));
    relocalizer_.setConfig(config);

    quality_config_.max_fitness_score = config.fitness_score_threshold;
    quality_config_.min_scan_points =
      static_cast<std::size_t>(std::max(config.min_scan_points, 1));
    quality_config_.max_translation_innovation = max_translation_innovation_;
    quality_config_.max_yaw_innovation = max_yaw_innovation_;

    if (!global_map_pcd_.empty()) {
      const auto readiness = agt_localization::validateMapProcessingRecord(
        global_map_processing_record_, global_map_pcd_, map_id_, map_hash_);
      if (!readiness.ready) {
        RCLCPP_WARN(
          get_logger(), "Global localization PCD rejected before load: %s",
          readiness.message.c_str());
      } else {
        if (map_hash_.empty()) {
          map_hash_ = readiness.map_hash;
        }
        if (!readiness.record_hash_verified) {
          RCLCPP_WARN(
            get_logger(),
            "Localization PCD hash was computed as %s, but processing record has no verified hash",
            readiness.map_hash.c_str());
        }
        if (!relocalizer_.setGlobalMapFromPcd(global_map_pcd_, global_frame_)) {
          RCLCPP_WARN(
            get_logger(), "Failed to load global_map_pcd=%s at startup",
            global_map_pcd_.c_str());
        }
      }
    }
    loadConfiguredCandidates();

    status_pub_ = create_publisher<LocalizationStatus>("/agt/localization/status", 10);
    legacy_status_pub_ =
      create_publisher<std_msgs::msg::String>("/agt/localization/status_text", 10);
    global_pose_pub_ =
      create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(
      "/agt/localization/global_pose", 10);
    coarse_pose_pub_ =
      create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(
      "/agt/localization/candidate_pose", 10);
    aligned_cloud_pub_ =
      create_publisher<sensor_msgs::msg::PointCloud2>(
      "/agt/localization/aligned_points", rclcpp::SensorDataQoS());
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    tf_timer_ = create_wall_timer(
      std::chrono::milliseconds(50), std::bind(&RelocalizationNode::publishLatestTf, this));
    tracking_validation_timer_ = create_wall_timer(
      std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::duration<double>(tracking_validation_period_s_)),
      std::bind(&RelocalizationNode::maybeStartTrackingValidation, this));

    cloud_sub_ = create_subscription<sensor_msgs::msg::PointCloud2>(
      cloud_topic_, rclcpp::SensorDataQoS(),
      std::bind(&RelocalizationNode::cloudCallback, this, std::placeholders::_1));
    initialpose_sub_ = create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
      initialpose_topic_, 10,
      std::bind(&RelocalizationNode::initialPoseCallback, this, std::placeholders::_1));
    external_coarse_pose_sub_ =
      create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
      external_coarse_pose_topic_, 10,
      std::bind(
        &RelocalizationNode::externalCoarsePoseCallback, this, std::placeholders::_1));
    action_server_ = rclcpp_action::create_server<Relocalize>(
      this,
      relocalize_action_name_,
      std::bind(
        &RelocalizationNode::handleGoal, this, std::placeholders::_1, std::placeholders::_2),
      std::bind(
        &RelocalizationNode::handleCancel, this, std::placeholders::_1),
      std::bind(
        &RelocalizationNode::handleAccepted, this, std::placeholders::_1));

    RCLCPP_INFO(
      get_logger(),
      "Relocalization node ready. backend=%s ndt_num_threads=%d cloud_topic=%s "
      "initialpose_topic=%s action=%s map_pcd=%s candidates=%s",
      relocalization_core::toString(relocalizer_.config().backend).c_str(),
      relocalizer_.config().ndt.num_threads,
      cloud_topic_.c_str(), initialpose_topic_.c_str(), relocalize_action_name_.c_str(),
      global_map_pcd_.c_str(), configured_candidates_yaml_.c_str());
  }

  ~RelocalizationNode() override
  {
    cancel_requested_.store(true);
    std::lock_guard<std::mutex> lock(worker_mutex_);
    if (worker_thread_.joinable()) {
      worker_thread_.join();
    }
  }

private:
  struct Attempt
  {
    Candidate candidate;
    relocalization_core::RelocalizationResult result;
    relocalization_core::RelocalizationDebugInfo debug;
    agt_localization::QualityDecision quality;
    Eigen::Matrix4f map_to_base{Eigen::Matrix4f::Identity()};
  };

  struct GoalRunResult
  {
    agt_localization::RunDisposition disposition{
      agt_localization::RunDisposition::kRejected};
    std::uint16_t error_code{LocalizationStatus::ERROR_BACKEND_FAILED};
    geometry_msgs::msg::PoseWithCovarianceStamped final_pose;
    LocalizationStatus final_status;
    std::string failure_reason;
    bool backend_converged{false};
  };

  struct TrackingCloudReservation
  {
    agt_localization::CloudSequenceStatus status{
      agt_localization::CloudSequenceStatus::kNew};
    std::optional<std::int64_t> previous_stamp_ns;
  };

  rclcpp_action::GoalResponse handleGoal(
    const rclcpp_action::GoalUUID &,
    std::shared_ptr<const Relocalize::Goal> goal)
  {
    if (execution_running_.load()) {
      RCLCPP_WARN(get_logger(), "Rejecting relocalization goal while another request is active");
      return rclcpp_action::GoalResponse::REJECT;
    }
    if (!goal || goal->mode > Relocalize::Goal::MODE_EXTERNAL_COARSE_POSE ||
      !isFinite(goal->timeout_s) || goal->timeout_s < 0.0)
    {
      return rclcpp_action::GoalResponse::REJECT;
    }
    if (goal->mode == Relocalize::Goal::MODE_SINGLE_INITIAL_POSE &&
      !goal->use_initial_pose)
    {
      return rclcpp_action::GoalResponse::REJECT;
    }
    if (goal->mode == Relocalize::Goal::MODE_LOCAL_CANDIDATES &&
      !goal->use_initial_pose && !goal->use_last_valid_pose &&
      !goal->use_configured_candidates && !goal->use_external_coarse_pose)
    {
      return rclcpp_action::GoalResponse::REJECT;
    }
    if (goal->mode == Relocalize::Goal::MODE_EXTERNAL_COARSE_POSE &&
      !goal->use_external_coarse_pose && !goal->use_initial_pose)
    {
      return rclcpp_action::GoalResponse::REJECT;
    }
    bool expected = false;
    if (!execution_running_.compare_exchange_strong(expected, true)) {
      return rclcpp_action::GoalResponse::REJECT;
    }
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse handleCancel(
    const std::shared_ptr<GoalHandleRelocalize>)
  {
    cancel_requested_.store(true);
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void handleAccepted(const std::shared_ptr<GoalHandleRelocalize> goal_handle)
  {
    std::lock_guard<std::mutex> lock(worker_mutex_);
    if (worker_thread_.joinable()) {
      worker_thread_.join();
    }
    cancel_requested_.store(false);
    worker_thread_ = std::thread(
      [this, goal_handle]() {
        executeGoal(goal_handle);
      });
  }

  void executeGoal(const std::shared_ptr<GoalHandleRelocalize> & goal_handle)
  {
    const auto result = runGoal(goal_handle);
    const bool accepted = result.disposition == agt_localization::RunDisposition::kAccepted;
    auto action_result = std::make_shared<Relocalize::Result>();
    action_result->success = accepted;
    action_result->error_code = result.error_code;
    action_result->final_pose = result.final_pose;
    action_result->final_status = result.final_status;
    action_result->failure_reason = result.failure_reason;
    if (goal_handle->is_canceling() || cancel_requested_.load()) {
      action_result->success = false;
      action_result->error_code = LocalizationStatus::ERROR_CANCELED;
      action_result->failure_reason = "relocalization canceled";
      action_result->final_status.error_code = LocalizationStatus::ERROR_CANCELED;
      goal_handle->canceled(action_result);
    } else if (accepted) {
      goal_handle->succeed(action_result);
    } else {
      goal_handle->abort(action_result);
    }
    execution_running_.store(false);
  }

  GoalRunResult runGoal(const std::shared_ptr<GoalHandleRelocalize> & goal_handle)
  {
    const auto goal = goal_handle->get_goal();
    GoalRunResult output;
    std::string error;
    std::uint16_t candidate_error_code = LocalizationStatus::ERROR_NO_CANDIDATES;
    const auto candidates = buildCandidates(*goal, &error, &candidate_error_code);
    if (candidates.empty()) {
      publishTerminalStatus(
        LocalizationStatus::STATE_LOST, candidate_error_code,
        nullptr, 0U, 0U, error);
      output.error_code = candidate_error_code;
      output.failure_reason = error;
      output.final_status = lastStatus();
      return output;
    }

    const double timeout_s = goal->timeout_s > 0.0 ? goal->timeout_s : action_timeout_s_;
    return runCandidates(candidates, timeout_s, goal->publish_debug, goal_handle);
  }

  void initialPoseCallback(
    const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
  {
    if (!manual_initialpose_enabled_) {
      publishTerminalStatus(
        LocalizationStatus::STATE_ERROR, LocalizationStatus::ERROR_INVALID_REQUEST,
        nullptr, 0U, 0U, "manual initialpose comparison path is disabled");
      return;
    }
    if (!msg || (!msg->header.frame_id.empty() && msg->header.frame_id != global_frame_)) {
      publishTerminalStatus(
        LocalizationStatus::STATE_ERROR, LocalizationStatus::ERROR_INVALID_REQUEST,
        nullptr, 0U, 0U, "initial pose must be expressed in the global frame");
      return;
    }
    const auto pose_matrix = agt_localization::poseMsgToEigen(msg->pose.pose);
    if (!poseIsValid(msg->pose.pose) ||
      !isFinite(pose_matrix(0, 3)) || !isFinite(pose_matrix(1, 3)) ||
      !isFinite(pose_matrix(2, 3))) {
      publishTerminalStatus(
        LocalizationStatus::STATE_ERROR, LocalizationStatus::ERROR_INVALID_REQUEST,
        nullptr, 0U, 0U, "initial pose contains a non-finite coordinate");
      return;
    }
    bool expected = false;
    if (!execution_running_.compare_exchange_strong(expected, true)) {
      RCLCPP_WARN(get_logger(), "Ignoring initial pose while relocalization is active");
      return;
    }
    cancel_requested_.store(false);
    const auto pose = msg->pose.pose;
    std::lock_guard<std::mutex> lock(worker_mutex_);
    if (worker_thread_.joinable()) {
      worker_thread_.join();
    }
    worker_thread_ = std::thread(
      [this, pose]() {
        Candidate candidate = candidateFromPose(
          pose, "manual_initialpose", "manual_initialpose", map_id_, map_hash_, 400);
        const auto result = runCandidates(
          {candidate}, action_timeout_s_, publish_aligned_cloud_, nullptr);
        if (result.disposition != agt_localization::RunDisposition::kAccepted) {
          RCLCPP_WARN(
            get_logger(), "Manual initialpose relocalization failed: %s",
            result.failure_reason.c_str());
        }
        execution_running_.store(false);
      });
  }

  std::vector<Candidate> buildCandidates(
    const Relocalize::Goal & goal,
    std::string * error,
    std::uint16_t * error_code)
  {
    bool use_initial = goal.use_initial_pose;
    bool use_last = goal.use_last_valid_pose;
    bool use_configured = goal.use_configured_candidates;
    bool use_external = goal.use_external_coarse_pose;
    if (goal.mode == Relocalize::Goal::MODE_AUTO_SEARCH &&
      !use_initial && !use_last && !use_configured)
    {
      use_last = true;
      use_configured = true;
      use_external = true;
    }

    std::vector<Candidate> candidates;
    const std::size_t requested_max = goal.max_candidates == 0U ?
      static_cast<std::size_t>(candidate_max_) :
      std::min(
      static_cast<std::size_t>(goal.max_candidates),
      static_cast<std::size_t>(candidate_max_));

    if (use_initial) {
      if ((goal.initial_pose.header.frame_id.empty() ||
        goal.initial_pose.header.frame_id == global_frame_) &&
        poseIsValid(goal.initial_pose.pose.pose))
      {
        candidates.push_back(candidateFromPose(
          goal.initial_pose.pose.pose, "action_initial_pose", "action_initial_pose", map_id_, map_hash_, 400));
      } else {
        if (error != nullptr) {
          *error = "initial pose must be valid and expressed in the global frame";
        }
        if (error_code != nullptr) {
          *error_code = LocalizationStatus::ERROR_INVALID_REQUEST;
        }
        return {};
      }
    }

    if (use_external) {
      std::optional<geometry_msgs::msg::PoseWithCovarianceStamped> coarse_pose;
      {
        std::lock_guard<std::mutex> lock(external_coarse_pose_mutex_);
        if (latest_external_coarse_pose_) {
          coarse_pose = *latest_external_coarse_pose_;
        }
      }
      if (coarse_pose.has_value()) {
        std::string validation_error;
        const auto candidate = externalCandidate(*coarse_pose, &validation_error);
        if (candidate.has_value()) {
          candidates.push_back(*candidate);
        } else if (error != nullptr && error->empty()) {
          *error = validation_error;
          if (error_code != nullptr) {
            *error_code = LocalizationStatus::ERROR_INVALID_REQUEST;
          }
        }
      } else if (error != nullptr && error->empty()) {
        *error = "no fresh external coarse pose is available";
        if (error_code != nullptr) {
          *error_code = LocalizationStatus::ERROR_NO_CANDIDATES;
        }
      }
    }

    if (use_last) {
      std::optional<Candidate> last_candidate;
      if (map_id_.empty() || map_hash_.empty()) {
        if (error != nullptr && error->empty()) {
          *error = "last valid pose requires active map_id and map_hash";
          if (error_code != nullptr) {
            *error_code = LocalizationStatus::ERROR_MAP_HASH_MISMATCH;
          }
        }
      } else if (!last_valid_pose_path_.empty()) {
        std::string load_error;
        const auto record = agt_localization::loadLastPose(
          last_valid_pose_path_, map_id_, map_hash_, &load_error);
        if (record.has_value()) {
          Candidate candidate;
          candidate.id = "last_valid_pose";
          candidate.source = "last_valid_pose";
          candidate.map_id = record->map_id;
          candidate.map_hash = record->map_hash;
          candidate.x = record->x;
          candidate.y = record->y;
          candidate.z = record->z;
          candidate.yaw = record->yaw;
          candidate.priority = 200;
          last_candidate = candidate;
        } else {
          RCLCPP_WARN(get_logger(), "Ignoring last_valid_pose: %s", load_error.c_str());
        }
      } else {
        std::lock_guard<std::mutex> lock(last_pose_mutex_);
        last_candidate = last_valid_candidate_;
      }
      if (last_candidate.has_value()) {
        candidates.push_back(*last_candidate);
      }
    }

    if (use_configured) {
      if (!configured_candidate_document_.has_value()) {
        RCLCPP_WARN(get_logger(), "Configured candidate source requested but is unavailable");
      } else {
        agt_localization::CandidateExpansionConfig config;
        config.max_candidates = requested_max;
        config.max_expanded_candidates =
          static_cast<std::size_t>(max_expanded_candidates_);
        config.position_dedup_tolerance = candidate_position_dedup_tolerance_;
        config.yaw_dedup_tolerance = candidate_yaw_dedup_tolerance_;
        std::string expansion_error;
        auto configured = agt_localization::expandCandidates(
          *configured_candidate_document_, config, &expansion_error);
        if (!expansion_error.empty()) {
          if (error != nullptr) {
            *error = expansion_error;
          }
          return {};
        }
        candidates.insert(candidates.end(), configured.begin(), configured.end());
      }
    }

    std::stable_sort(
      candidates.begin(), candidates.end(),
      [](const Candidate & first, const Candidate & second) {
        if (first.priority != second.priority) {
          return first.priority > second.priority;
        }
        if (first.covariance_score != second.covariance_score) {
          return first.covariance_score < second.covariance_score;
        }
        if (first.distance_from_seed != second.distance_from_seed) {
          return first.distance_from_seed < second.distance_from_seed;
        }
        return first.id < second.id;
      });
    std::vector<Candidate> deduplicated;
    deduplicated.reserve(candidates.size());
    for (const auto & candidate : candidates) {
      const bool duplicate = std::any_of(
        deduplicated.begin(), deduplicated.end(),
        [this, &candidate](const Candidate & existing) {
          const double dx = existing.x - candidate.x;
          const double dy = existing.y - candidate.y;
          const double dz = existing.z - candidate.z;
          return std::sqrt(dx * dx + dy * dy + dz * dz) <=
            candidate_position_dedup_tolerance_ &&
            std::abs(normalizeYaw(existing.yaw - candidate.yaw)) <=
            candidate_yaw_dedup_tolerance_;
        });
      if (!duplicate) {
        deduplicated.push_back(candidate);
      }
    }
    candidates = std::move(deduplicated);
    if (candidates.size() > requested_max) {
      candidates.resize(requested_max);
    }
    if (candidates.empty() && error != nullptr && error->empty()) {
      *error = "no valid relocalization candidates are available";
    }
    return candidates;
  }

  std::optional<Candidate> externalCandidate(
    const geometry_msgs::msg::PoseWithCovarianceStamped & msg,
    std::string * error) const
  {
    if (msg.header.frame_id != global_frame_ || !poseIsValid(msg.pose.pose)) {
      if (error != nullptr) {
        *error = "external coarse pose must be valid and expressed in the global frame";
      }
      return std::nullopt;
    }
    const rclcpp::Time stamp(msg.header.stamp);
    const double age = (now() - stamp).seconds();
    if (stamp.nanoseconds() == 0 || age < -external_coarse_future_tolerance_s_ ||
      age > external_coarse_max_age_s_)
    {
      if (error != nullptr) {
        *error = "external coarse pose is stale or timestamp is invalid";
      }
      return std::nullopt;
    }
    double covariance_score = 0.0;
    for (const double value : msg.pose.covariance) {
      if (!isFinite(value) || value < 0.0) {
        if (error != nullptr) {
          *error = "external coarse pose covariance is invalid";
        }
        return std::nullopt;
      }
      covariance_score += value;
    }
    return candidateFromPose(
      msg.pose.pose, "external_coarse_pose", "external_coarse_pose", map_id_, map_hash_,
      300, covariance_score);
  }

  GoalRunResult runCandidates(
    const std::vector<Candidate> & candidates,
    double timeout_s,
    bool publish_debug,
    const std::shared_ptr<GoalHandleRelocalize> & goal_handle,
    bool update_tf = true,
    bool tracking_validation = false)
  {
    GoalRunResult output;
    const auto start = std::chrono::steady_clock::now();
    std::vector<Attempt> successful;
    std::optional<Attempt> best_failed;
    sensor_msgs::msg::PointCloud2::SharedPtr cloud_msg;
    {
      std::lock_guard<std::mutex> lock(cloud_mutex_);
      cloud_msg = latest_cloud_msg_;
    }

    if (!ensureMap()) {
      output.final_status = makeRunStatus(
        tracking_validation,
        LocalizationStatus::STATE_LOST, LocalizationStatus::ERROR_MAP_NOT_READY,
        nullptr, false, false, false, 0U, static_cast<std::uint32_t>(candidates.size()),
        "global localization map is not ready");
      output.error_code = LocalizationStatus::ERROR_MAP_NOT_READY;
      output.failure_reason = "global localization map is not ready";
      return output;
    }
    if (!cloud_msg) {
      output.final_status = makeRunStatus(
        tracking_validation,
        LocalizationStatus::STATE_LOST, LocalizationStatus::ERROR_SCAN_TOO_SMALL,
        nullptr, false, false, false, 0U, static_cast<std::uint32_t>(candidates.size()),
        "no latest registered lidar cloud is available");
      output.error_code = LocalizationStatus::ERROR_SCAN_TOO_SMALL;
      output.failure_reason = "no latest registered lidar cloud is available";
      return output;
    }

    const rclcpp::Time cloud_stamp(cloud_msg->header.stamp);
    const agt_localization::CloudTimeConfig cloud_time_config{
      max_cloud_age_s_, max_cloud_future_tolerance_s_, require_nonzero_cloud_stamp_};
    const auto cloud_time = agt_localization::validateCloudTimestamp(
      now().seconds(), cloud_stamp.seconds(), cloud_time_config);
    std::optional<TrackingCloudReservation> tracking_cloud_reservation;
    if (tracking_validation) {
      tracking_cloud_reservation = evaluateTrackingValidationCloudStamp(
        cloud_stamp, cloud_time.accepted);
      const auto cloud_disposition = agt_localization::decideTrackingCloudDisposition(
        cloud_time, tracking_cloud_reservation->status);
      if (cloud_disposition == agt_localization::TrackingCloudDisposition::kSkipDuplicate) {
        RCLCPP_DEBUG_THROTTLE(
          get_logger(), *get_clock(), 5000,
          "Tracking validation skipped fresh duplicate cloud stamp=%lld age=%.3f",
          static_cast<long long>(cloud_stamp.nanoseconds()), cloud_time.age_s);
        output.disposition = agt_localization::RunDisposition::kSkipped;
        output.error_code = LocalizationStatus::ERROR_NONE;
        output.failure_reason =
          "fresh duplicate tracking validation cloud; waiting for a newer scan";
        output.final_status = lastStatus();
        return output;
      }
    }
    if (!cloud_time.accepted) {
      const bool invalid_timestamp = !std::isfinite(cloud_stamp.seconds()) ||
        (require_nonzero_cloud_stamp_ && cloud_stamp.nanoseconds() == 0);
      const auto error_code = invalid_timestamp ?
        LocalizationStatus::ERROR_INVALID_SCAN_TIMESTAMP : LocalizationStatus::ERROR_STALE_SCAN;
      const std::string reason = cloud_time.message +
        ": stamp=" + std::to_string(cloud_stamp.seconds()) +
        "s age=" + std::to_string(cloud_time.age_s) + "s";
      const auto state = tracking_validation ?
        toLocalizationState(supervisor_.snapshot().state) : LocalizationStatus::STATE_LOST;
      output.final_status = makeRunStatus(
        tracking_validation, state, error_code, nullptr, false, false, false,
        0U, static_cast<std::uint32_t>(candidates.size()), reason);
      output.error_code = error_code;
      output.failure_reason = reason;
      return output;
    }

    if (tracking_cloud_reservation.has_value()) {
      if (tracking_cloud_reservation->status ==
        agt_localization::CloudSequenceStatus::kTimeMovedBackward)
      {
        RCLCPP_WARN_THROTTLE(
          get_logger(), *get_clock(), 5000,
          "Tracking validation cloud time moved backwards: previous=%lld current=%lld; "
          "duplicate-scan guard reset",
          static_cast<long long>(tracking_cloud_reservation->previous_stamp_ns.value_or(0)),
          static_cast<long long>(cloud_stamp.nanoseconds()));
        output.disposition = agt_localization::RunDisposition::kSkipped;
        output.error_code = LocalizationStatus::ERROR_NONE;
        output.failure_reason =
          "tracking validation cloud time moved backwards; waiting for a newer scan";
        output.final_status = lastStatus();
        return output;
      }
    }

    RCLCPP_DEBUG(
      get_logger(),
      "Relocalization frame cloud_stamp=%.9f cloud_age_s=%.3f tracking_validation=%s",
      cloud_stamp.seconds(), cloud_time.age_s, tracking_validation ? "true" : "false");

    relocalization_core::CloudPtr scan_cloud;
    try {
      scan_cloud = cloudFromMsgInTrackingFrame(*cloud_msg);
    } catch (const tf2::TransformException & exception) {
      const std::string reason =
        "failed to transform cloud at stamp=" + std::to_string(cloud_stamp.seconds()) +
        "s target_frame=" + tracking_frame_ + " source_frame=" + cloud_msg->header.frame_id +
        ": " + exception.what();
      output.final_status = makeRunStatus(
        tracking_validation,
        LocalizationStatus::STATE_ERROR, LocalizationStatus::ERROR_TF_UNAVAILABLE,
        nullptr, false, false, false, 0U,
        static_cast<std::uint32_t>(candidates.size()), reason);
      output.error_code = LocalizationStatus::ERROR_TF_UNAVAILABLE;
      output.failure_reason = reason;
      return output;
    }

    Eigen::Matrix4f base_from_tracking = Eigen::Matrix4f::Identity();
    try {
      const auto transform = tf_buffer_.lookupTransform(
        base_frame_, tracking_frame_, tf2::TimePointZero, std::chrono::milliseconds(200));
      base_from_tracking = agt_localization::transformMsgToEigen(transform);
    } catch (const tf2::TransformException & exception) {
      const std::string reason =
        "failed to lookup static transform target_frame=" + base_frame_ +
        " source_frame=" + tracking_frame_ + ": " + exception.what();
      output.final_status = makeRunStatus(
        tracking_validation,
        LocalizationStatus::STATE_ERROR, LocalizationStatus::ERROR_TF_UNAVAILABLE,
        nullptr, false, false, false, 0U,
        static_cast<std::uint32_t>(candidates.size()), reason);
      output.error_code = LocalizationStatus::ERROR_TF_UNAVAILABLE;
      output.failure_reason = reason;
      return output;
    }

    // lookupTransform(target, source) returns T_target_source. This query is
    // deliberately made once at the cloud timestamp and shared by every candidate.
    Eigen::Matrix4f odom_from_tracking = Eigen::Matrix4f::Identity();
    try {
      const auto transform = tf_buffer_.lookupTransform(
        odom_frame_, tracking_frame_, cloud_stamp, std::chrono::milliseconds(200));
      odom_from_tracking = agt_localization::transformMsgToEigen(transform);
    } catch (const tf2::TransformException & exception) {
      const std::string reason =
        "failed to lookup TF at cloud_stamp=" + std::to_string(cloud_stamp.seconds()) +
        "s target_frame=" + odom_frame_ + " source_frame=" + tracking_frame_ +
        ": " + exception.what();
      output.final_status = makeRunStatus(
        tracking_validation,
        tracking_validation ? toLocalizationState(supervisor_.snapshot().state) :
        LocalizationStatus::STATE_ERROR,
        LocalizationStatus::ERROR_TF_UNAVAILABLE, nullptr, false, false, false, 0U,
        static_cast<std::uint32_t>(candidates.size()), reason);
      output.error_code = LocalizationStatus::ERROR_TF_UNAVAILABLE;
      output.failure_reason = reason;
      return output;
    }

    const Eigen::Matrix4f tracking_from_base = base_from_tracking.inverse();
    std::optional<Eigen::Matrix4f> predicted_map_from_tracking;
    if (tracking_validation) {
      Eigen::Matrix4f map_from_odom = Eigen::Matrix4f::Identity();
      bool has_latest_map_from_odom = false;
      {
        std::lock_guard<std::mutex> lock(tf_mutex_);
        if (has_latest_tf_) {
          has_latest_map_from_odom = true;
          map_from_odom = latest_map_to_odom_;
        }
      }
      if (!has_latest_map_from_odom) {
        const std::string reason =
          "tracking validation has no accepted map -> odom transform for cloud_stamp=" +
          std::to_string(cloud_stamp.seconds()) + "s";
        output.final_status = makeRunStatus(
          tracking_validation,
          toLocalizationState(supervisor_.snapshot().state),
          LocalizationStatus::ERROR_TF_UNAVAILABLE, nullptr, false, false, false, 0U,
          static_cast<std::uint32_t>(candidates.size()), reason);
        output.error_code = LocalizationStatus::ERROR_TF_UNAVAILABLE;
        output.failure_reason = reason;
        return output;
      }
      // map_from_tracking = map_from_odom * odom_from_tracking at cloud_stamp.
      predicted_map_from_tracking = agt_localization::predictMapFromTracking(
        map_from_odom, odom_from_tracking);
    }

    if (!tracking_validation) {
      supervisor_.beginSearch();
      (void)makeRunStatus(
        tracking_validation,
        toLocalizationState(supervisor_.snapshot().state), LocalizationStatus::ERROR_NONE,
        nullptr, false, false, false, 0U, static_cast<std::uint32_t>(candidates.size()),
        "searching relocalization candidates");
    }

    for (std::size_t index = 0; index < candidates.size(); ++index) {
      if (cancel_requested_.load() ||
        (goal_handle && goal_handle->is_canceling()))
      {
        const auto snapshot = tracking_validation ?
          supervisor_.snapshot() : supervisor_.cancel();
        const std::string reason = tracking_validation ?
          "tracking validation canceled" : "relocalization canceled";
        output.final_status = makeRunStatus(
          tracking_validation,
          toLocalizationState(snapshot.state), LocalizationStatus::ERROR_CANCELED,
          nullptr, false, false, false, static_cast<std::uint32_t>(index),
          static_cast<std::uint32_t>(candidates.size()), reason);
        output.error_code = LocalizationStatus::ERROR_CANCELED;
        output.failure_reason = reason;
        return output;
      }
      const double elapsed_s = std::chrono::duration<double>(
        std::chrono::steady_clock::now() - start).count();
      if (elapsed_s > timeout_s) {
        const auto snapshot = tracking_validation ?
          supervisor_.snapshot() : supervisor_.timeout();
        const std::string reason = tracking_validation ?
          "tracking validation timed out" : "relocalization timed out";
        output.final_status = makeRunStatus(
          tracking_validation,
          toLocalizationState(snapshot.state), LocalizationStatus::ERROR_TIMEOUT,
          nullptr, false, false, false, static_cast<std::uint32_t>(index),
          static_cast<std::uint32_t>(candidates.size()), reason);
        output.error_code = LocalizationStatus::ERROR_TIMEOUT;
        output.failure_reason = reason;
        return output;
      }

      const Candidate & candidate = candidates[index];
      const Eigen::Matrix4f initial_map_from_base = tracking_validation ?
        (*predicted_map_from_tracking * tracking_from_base) : candidateToPose(candidate);
      if (tracking_validation) {
        coarse_pose_pub_->publish(poseStampedFromEigen(initial_map_from_base, cloud_stamp));
      } else {
        publishCoarsePose(candidate);
      }
      if (!tracking_validation) {
        supervisor_.beginVerification();
      }
      (void)makeRunStatus(
        tracking_validation,
        toLocalizationState(supervisor_.snapshot().state), LocalizationStatus::ERROR_NONE,
        &candidate, false, false, false, static_cast<std::uint32_t>(index),
        static_cast<std::uint32_t>(candidates.size()), "verifying candidate");

      Attempt attempt;
      attempt.candidate = candidate;
      relocalization_core::RelocalizationRequest request;
      request.source_cloud = scan_cloud;
      request.source_frame_id = tracking_frame_;
      request.target_frame_id = global_frame_;
      request.initial_guess = tracking_validation ? *predicted_map_from_tracking :
        candidateToPose(candidate) * base_from_tracking;
      request.request_time_sec = cloud_stamp.seconds();
      request.enable_debug_outputs = publish_debug;
      RCLCPP_DEBUG(
        get_logger(),
        "Relocalization candidate source=%s tracking_validation=%s initial_guess_source=%s",
        candidate.source.c_str(), tracking_validation ? "true" : "false",
        tracking_validation ? "odom_propagated_tracking_prediction" : candidate.source.c_str());
      attempt.result = relocalizer_.relocalize(request);
      attempt.debug = relocalizer_.latestDebugInfo();
      attempt.map_to_base = attempt.result.estimated_pose * tracking_from_base;

      agt_localization::QualityObservation observation;
      observation.backend_success =
        attempt.result.status_code == relocalization_core::RelocalizationStatusCode::kOk ||
        attempt.result.status_code == relocalization_core::RelocalizationStatusCode::kFitnessRejected;
      observation.has_converged = attempt.result.has_converged;
      observation.fitness_score = attempt.result.fitness_score;
      observation.scan_points = attempt.debug.cropped_scan_size > 0U ?
        attempt.debug.cropped_scan_size : attempt.debug.filtered_scan_size;
      observation.initial_x = initial_map_from_base(0, 3);
      observation.initial_y = initial_map_from_base(1, 3);
      observation.initial_z = initial_map_from_base(2, 3);
      observation.initial_yaw = matrixYaw(initial_map_from_base);
      observation.estimated_x = attempt.map_to_base(0, 3);
      observation.estimated_y = attempt.map_to_base(1, 3);
      observation.estimated_z = attempt.map_to_base(2, 3);
      observation.estimated_yaw = matrixYaw(attempt.map_to_base);
      observation.runtime_ms = attempt.debug.backend_runtime_ms;
      attempt.quality = agt_localization::validateQuality(observation, quality_config_);
      if (tracking_validation) {
        RCLCPP_DEBUG(
          get_logger(),
          "Tracking validation predicted=(%.3f, %.3f, %.3f) estimated=(%.3f, %.3f, %.3f) "
          "translation_innovation=%.3f yaw_innovation=%.3f fitness=%.6f",
          observation.initial_x, observation.initial_y, observation.initial_yaw,
          observation.estimated_x, observation.estimated_y, observation.estimated_yaw,
          attempt.quality.translation_innovation, attempt.quality.yaw_innovation,
          attempt.result.fitness_score);
      }
      if (attempt.result.status_code != relocalization_core::RelocalizationStatusCode::kOk &&
        attempt.result.status_code != relocalization_core::RelocalizationStatusCode::kFitnessRejected)
      {
        attempt.quality.accepted = false;
        attempt.quality.error_code = coreErrorCode(attempt.result);
        attempt.quality.message = attempt.result.status_message;
      }

      (void)makeRunStatus(
        tracking_validation,
        attempt.quality.accepted ? LocalizationStatus::STATE_VERIFYING :
        LocalizationStatus::STATE_DEGRADED,
        attempt.quality.accepted ? LocalizationStatus::ERROR_NONE :
        attempt.quality.error_code, &candidate, false, attempt.result.has_converged,
        false, static_cast<std::uint32_t>(index + 1U),
        static_cast<std::uint32_t>(candidates.size()), attempt.quality.message,
        attempt.result.fitness_score, attempt.quality.translation_innovation,
        attempt.quality.yaw_innovation, attempt.debug.backend_runtime_ms);

      if (attempt.quality.accepted) {
        successful.push_back(attempt);
        std::sort(
          successful.begin(), successful.end(),
          [](const Attempt & first, const Attempt & second) {
            return first.result.fitness_score < second.result.fitness_score;
          });
      } else if (!best_failed.has_value() ||
        attempt.result.fitness_score < best_failed->result.fitness_score)
      {
        best_failed = attempt;
      }

      if (goal_handle) {
        auto feedback = std::make_shared<Relocalize::Feedback>();
        feedback->state = LocalizationStatus::STATE_VERIFYING;
        feedback->total_candidates = static_cast<std::uint32_t>(candidates.size());
        feedback->tested_candidates = static_cast<std::uint32_t>(index + 1U);
        feedback->best_fitness_score =
          successful.empty() ? 0.0 : successful.front().result.fitness_score;
        feedback->best_candidate_source =
          successful.empty() ? std::string() : successful.front().candidate.source;
        feedback->elapsed_s = elapsed_s;
        goal_handle->publish_feedback(feedback);
      }
    }

    if (successful.empty()) {
      const auto snapshot = tracking_validation ?
        supervisor_.snapshot() : supervisor_.rejectSearchResult();
      const auto error_code = best_failed.has_value() ?
        best_failed->quality.error_code : LocalizationStatus::ERROR_NO_CANDIDATES;
      const std::string reason = best_failed.has_value() ?
        best_failed->quality.message : "all relocalization candidates failed";
      output.backend_converged = best_failed.has_value() && best_failed->result.has_converged;
      output.final_status = makeRunStatus(
        tracking_validation,
        toLocalizationState(snapshot.state), error_code,
        best_failed.has_value() ? &best_failed->candidate : nullptr,
        false, output.backend_converged, false,
        static_cast<std::uint32_t>(candidates.size()),
        static_cast<std::uint32_t>(candidates.size()), reason,
        best_failed.has_value() ? best_failed->result.fitness_score : 0.0,
        best_failed.has_value() ? best_failed->quality.translation_innovation : 0.0,
        best_failed.has_value() ? best_failed->quality.yaw_innovation : 0.0,
        best_failed.has_value() ? best_failed->debug.backend_runtime_ms : 0.0);
      output.error_code = error_code;
      output.failure_reason = reason;
      return output;
    }
    if (successful.size() > 1U &&
      agt_localization::isAmbiguousScore(
        successful[0].result.fitness_score,
        successful[1].result.fitness_score, ambiguity_ratio_))
    {
      const auto snapshot = tracking_validation ?
        supervisor_.snapshot() : supervisor_.rejectSearchResult();
      output.backend_converged = successful.front().result.has_converged;
      output.final_status = makeRunStatus(
        tracking_validation,
        toLocalizationState(snapshot.state), LocalizationStatus::ERROR_AMBIGUOUS_RESULT,
        &successful.front().candidate, false, output.backend_converged, true,
        static_cast<std::uint32_t>(candidates.size()),
        static_cast<std::uint32_t>(candidates.size()),
        "multiple candidates have indistinguishable registration quality",
        successful.front().result.fitness_score,
        successful.front().quality.translation_innovation,
        successful.front().quality.yaw_innovation,
        successful.front().debug.backend_runtime_ms);
      output.error_code = LocalizationStatus::ERROR_AMBIGUOUS_RESULT;
      output.failure_reason = "multiple candidates have indistinguishable registration quality";
      return output;
    }

    Attempt & best = successful.front();
    const Eigen::Matrix4f tracking_from_odom = odom_from_tracking.inverse();
    const Eigen::Matrix4f map_from_odom = best.result.estimated_pose * tracking_from_odom;
    const auto snapshot = tracking_validation ?
      supervisor_.snapshot() : supervisor_.acceptSearchResult();
    if (update_tf && snapshot.navigation_allowed) {
      {
        std::lock_guard<std::mutex> lock(tf_mutex_);
        latest_map_to_odom_ = map_from_odom;
        has_latest_tf_ = true;
      }
      if (publish_tf_) {
        tf_broadcaster_->sendTransform(
          agt_localization::eigenToTransformMsg(
            map_from_odom, now(), global_frame_, odom_frame_));
      }
    }
    if (publish_debug && best.result.aligned_cloud) {
      sensor_msgs::msg::PointCloud2 aligned_msg;
      pcl::toROSMsg(*best.result.aligned_cloud, aligned_msg);
      aligned_msg.header.stamp = cloud_stamp;
      aligned_msg.header.frame_id = global_frame_;
      aligned_cloud_pub_->publish(aligned_msg);
    }

    const auto final_pose = poseStampedFromEigen(best.map_to_base, cloud_stamp);
    global_pose_pub_->publish(final_pose);
    if (!tracking_validation) {
      Candidate accepted_candidate = best.candidate;
      accepted_candidate.x = best.map_to_base(0, 3);
      accepted_candidate.y = best.map_to_base(1, 3);
      accepted_candidate.z = best.map_to_base(2, 3);
      accepted_candidate.yaw = matrixYaw(best.map_to_base);
      accepted_candidate.distance_from_seed = 0.0;
      {
        std::lock_guard<std::mutex> lock(last_pose_mutex_);
        last_valid_candidate_ = std::move(accepted_candidate);
      }
      if (!last_valid_pose_path_.empty() && !map_id_.empty() && !map_hash_.empty()) {
        agt_localization::LastPoseRecord record;
        record.map_id = map_id_;
        record.map_hash = map_hash_;
        record.timestamp_sec = cloud_stamp.seconds();
        record.frame_id = global_frame_;
        record.x = best.map_to_base(0, 3);
        record.y = best.map_to_base(1, 3);
        record.z = best.map_to_base(2, 3);
        record.yaw = matrixYaw(best.map_to_base);
        record.fitness_score = best.result.fitness_score;
        std::string save_error;
        if (!agt_localization::saveLastPoseAtomic(
            last_valid_pose_path_, record, &save_error))
        {
          RCLCPP_WARN(get_logger(), "Failed to persist last valid pose: %s", save_error.c_str());
        }
      }
    }

    output.disposition = tracking_validation || snapshot.navigation_allowed ?
      agt_localization::RunDisposition::kAccepted :
      agt_localization::RunDisposition::kRejected;
    output.backend_converged = best.result.has_converged;
    const bool accepted = output.disposition == agt_localization::RunDisposition::kAccepted;
    output.error_code = accepted ?
      LocalizationStatus::ERROR_NONE : LocalizationStatus::ERROR_BACKEND_FAILED;
    output.final_pose = final_pose;
    if (!accepted) {
      output.failure_reason = "registration accepted but tracking confirmation is incomplete";
    }
    output.final_status = makeRunStatus(
      tracking_validation, toLocalizationState(snapshot.state), output.error_code,
      &best.candidate, accepted, output.backend_converged, false,
      static_cast<std::uint32_t>(candidates.size()),
      static_cast<std::uint32_t>(candidates.size()),
      accepted ? "relocalization accepted" : output.failure_reason,
      best.result.fitness_score, best.quality.translation_innovation,
      best.quality.yaw_innovation, best.debug.backend_runtime_ms, final_pose);
    return output;
  }

  relocalization_core::RegistrationBackendType parseBackend(
    const std::string & backend) const
  {
    return backend == "icp" ?
      relocalization_core::RegistrationBackendType::kIcp :
      relocalization_core::RegistrationBackendType::kNdt;
  }

  relocalization_core::CropBoxFrameMode parseCropMode(
    const std::string & mode) const
  {
    return mode == "disabled" ?
      relocalization_core::CropBoxFrameMode::kDisabled :
      relocalization_core::CropBoxFrameMode::kScanLocal;
  }

  int parseNdtSearchMethod(const std::string & method) const
  {
    if (method == "KDTREE") {
      return 0;
    }
    if (method == "DIRECT26") {
      return 1;
    }
    if (method == "DIRECT1") {
      return 3;
    }
    return 2;
  }

  void loadConfiguredCandidates()
  {
    if (configured_candidates_yaml_.empty()) {
      return;
    }
    agt_localization::ConfiguredCandidateDocument document;
    std::string error;
    if (!agt_localization::loadConfiguredCandidates(
        configured_candidates_yaml_, &document, &error))
    {
      RCLCPP_ERROR(get_logger(), "Configured candidates rejected: %s", error.c_str());
      return;
    }
    if (!map_id_.empty() && map_id_ != document.map_id) {
      RCLCPP_ERROR(get_logger(), "Configured candidates map_id does not match map_id parameter");
      return;
    }
    if (!map_hash_.empty() && map_hash_ != document.map_hash) {
      RCLCPP_ERROR(get_logger(), "Configured candidates map_hash does not match map_hash parameter");
      return;
    }
    if (map_id_.empty()) {
      map_id_ = document.map_id;
    }
    if (map_hash_.empty()) {
      map_hash_ = document.map_hash;
    }
    configured_candidate_document_ = document;
  }

  bool ensureMap()
  {
    if (global_map_pcd_.empty()) {
      return false;
    }
    const auto readiness = agt_localization::validateMapProcessingRecord(
      global_map_processing_record_, global_map_pcd_, map_id_, map_hash_);
    if (!readiness.ready) {
      RCLCPP_ERROR_THROTTLE(
        get_logger(), *get_clock(), 5000,
        "Global localization PCD is not ready: %s", readiness.message.c_str());
      return false;
    }
    if (relocalizer_.hasMap()) {
      return true;
    }
    return relocalizer_.setGlobalMapFromPcd(global_map_pcd_, global_frame_);
  }

  relocalization_core::CloudPtr cloudFromMsgInTrackingFrame(
    const sensor_msgs::msg::PointCloud2 & msg)
  {
    relocalization_core::CloudPtr cloud(new CloudT());
    pcl::fromROSMsg(msg, *cloud);
    if (msg.header.frame_id.empty() || msg.header.frame_id == tracking_frame_) {
      return cloud;
    }
    const auto tracking_from_cloud_msg = tf_buffer_.lookupTransform(
      tracking_frame_, msg.header.frame_id, rclcpp::Time(msg.header.stamp),
      std::chrono::milliseconds(200));
    const Eigen::Matrix4f tracking_from_cloud =
      agt_localization::transformMsgToEigen(tracking_from_cloud_msg);
    relocalization_core::CloudPtr transformed(new CloudT());
    pcl::transformPointCloud(*cloud, *transformed, tracking_from_cloud);
    return transformed;
  }

  geometry_msgs::msg::PoseWithCovarianceStamped poseStampedFromEigen(
    const Eigen::Matrix4f & pose,
    const rclcpp::Time & stamp) const
  {
    geometry_msgs::msg::PoseWithCovarianceStamped msg;
    msg.header.stamp = stamp;
    msg.header.frame_id = global_frame_;
    msg.pose.pose = poseFromEigen(pose);
    return msg;
  }

  void publishCoarsePose(const Candidate & candidate)
  {
    const auto msg = poseStampedFromEigen(candidateToPose(candidate), now());
    coarse_pose_pub_->publish(msg);
  }

  LocalizationStatus makeStatus(
    std::uint8_t state,
    std::uint16_t error_code,
    const Candidate * candidate,
    std::uint32_t tested,
    std::uint32_t total,
    const std::string & message,
    double fitness_score = 0.0,
    double translation_innovation = 0.0,
    double yaw_innovation = 0.0,
    double runtime_ms = 0.0) const
  {
    LocalizationStatus status;
    status.header.stamp = now();
    status.header.frame_id = global_frame_;
    status.state = state;
    status.error_code = error_code;
    status.tested_candidates = tested;
    status.total_candidates = total;
    status.backend = relocalization_core::toString(relocalizer_.config().backend);
    status.map_id = map_id_;
    status.map_hash = map_hash_;
    status.fitness_score = fitness_score;
    status.translation_innovation = translation_innovation;
    status.yaw_innovation = yaw_innovation;
    status.runtime_ms = runtime_ms;
    const auto supervisor_snapshot = supervisor_.snapshot();
    status.consecutive_successes = static_cast<std::uint32_t>(
      supervisor_snapshot.consecutive_successes);
    status.consecutive_failures = static_cast<std::uint32_t>(
      supervisor_snapshot.consecutive_failures);
    status.message = message;
    if (candidate != nullptr) {
      status.candidate_id = candidate->id;
      status.candidate_source = candidate->source;
    }
    return status;
  }

  LocalizationStatus makeRunStatus(
    bool tracking_validation,
    std::uint8_t state,
    std::uint16_t error_code,
    const Candidate * candidate,
    bool pose_valid,
    bool has_converged,
    bool ambiguous,
    std::uint32_t tested,
    std::uint32_t total,
    const std::string & message,
    double fitness_score = 0.0,
    double translation_innovation = 0.0,
    double yaw_innovation = 0.0,
    double runtime_ms = 0.0,
    const std::optional<geometry_msgs::msg::PoseWithCovarianceStamped> & pose = std::nullopt)
  {
    auto status = makeStatus(
      state, error_code, candidate, tested, total, message, fitness_score,
      translation_innovation, yaw_innovation, runtime_ms);
    status.pose_valid = pose_valid;
    status.localization_accepted = pose_valid && error_code == LocalizationStatus::ERROR_NONE;
    status.has_converged = has_converged;
    status.ambiguous_result = ambiguous;
    if (pose.has_value()) {
      status.global_pose = *pose;
    }
    if (!tracking_validation) {
      publishStatus(status);
    }
    return status;
  }

  void publishTerminalStatus(
    std::uint8_t state,
    std::uint16_t error_code,
    const Candidate * candidate,
    std::uint32_t tested,
    std::uint32_t total,
    const std::string & message,
    double fitness_score = 0.0)
  {
    (void)makeRunStatus(
      false, state, error_code, candidate, false, false,
      error_code == LocalizationStatus::ERROR_AMBIGUOUS_RESULT,
      tested, total, message, fitness_score);
  }

  void publishStatus(const LocalizationStatus & status)
  {
    status_pub_->publish(status);
    std_msgs::msg::String legacy;
    legacy.data = statusText(status);
    legacy_status_pub_->publish(legacy);
    std::lock_guard<std::mutex> lock(status_mutex_);
    last_status_ = status;
  }

  LocalizationStatus lastStatus()
  {
    std::lock_guard<std::mutex> lock(status_mutex_);
    return last_status_;
  }

  void cloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
  {
    std::lock_guard<std::mutex> lock(cloud_mutex_);
    latest_cloud_msg_ = msg;
  }

  TrackingCloudReservation evaluateTrackingValidationCloudStamp(
    const rclcpp::Time & cloud_stamp,
    bool timestamp_accepted)
  {
    std::lock_guard<std::mutex> lock(tracking_validation_stamp_mutex_);
    TrackingCloudReservation reservation;
    if (last_tracking_validation_cloud_stamp_.has_value()) {
      reservation.previous_stamp_ns =
        last_tracking_validation_cloud_stamp_->nanoseconds();
    }
    reservation.status = agt_localization::classifyCloudSequence(
      reservation.previous_stamp_ns, cloud_stamp.nanoseconds());
    if (timestamp_accepted &&
      reservation.status != agt_localization::CloudSequenceStatus::kDuplicate)
    {
      // A backward stamp becomes the new baseline, but this invocation is skipped.
      // The next validation still needs a strictly newer cloud before doing NDT.
      last_tracking_validation_cloud_stamp_ = cloud_stamp;
    }
    return reservation;
  }

  void externalCoarsePoseCallback(
    const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
  {
    if (!msg) {
      return;
    }
    std::string error;
    if (!externalCandidate(*msg, &error).has_value()) {
      RCLCPP_WARN(get_logger(), "Ignoring external coarse pose: %s", error.c_str());
      return;
    }
    std::lock_guard<std::mutex> lock(external_coarse_pose_mutex_);
    latest_external_coarse_pose_ =
      std::make_shared<geometry_msgs::msg::PoseWithCovarianceStamped>(*msg);
  }

  void publishLatestTf()
  {
    if (!publish_tf_) {
      return;
    }
    Eigen::Matrix4f map_to_odom = Eigen::Matrix4f::Identity();
    {
      std::lock_guard<std::mutex> lock(tf_mutex_);
      if (!has_latest_tf_) {
        return;
      }
      map_to_odom = latest_map_to_odom_;
    }
    tf_broadcaster_->sendTransform(
      agt_localization::eigenToTransformMsg(map_to_odom, now(), global_frame_, odom_frame_));
  }

  void maybeStartTrackingValidation()
  {
    const auto supervisor_snapshot = supervisor_.snapshot();
    const bool validation_state = supervisor_snapshot.state ==
      agt_localization::SupervisorState::kTracking ||
      supervisor_snapshot.state == agt_localization::SupervisorState::kDegraded ||
      supervisor_snapshot.state == agt_localization::SupervisorState::kRecovering;
    if (!tracking_validation_enabled_ || !validation_state || execution_running_.load())
    {
      return;
    }

    Candidate candidate;
    {
      std::lock_guard<std::mutex> lock(last_pose_mutex_);
      if (!last_valid_candidate_.has_value()) {
        return;
      }
      // Keep the prior candidate only as validation/status identity. Its pose
      // must not become the tracking validation initial guess.
      candidate.id = last_valid_candidate_->id;
      candidate.source = last_valid_candidate_->source;
      candidate.map_id = last_valid_candidate_->map_id;
      candidate.map_hash = last_valid_candidate_->map_hash;
    }

    bool expected = false;
    if (!execution_running_.compare_exchange_strong(expected, true)) {
      return;
    }
    cancel_requested_.store(false);
    std::lock_guard<std::mutex> lock(worker_mutex_);
    if (worker_thread_.joinable()) {
      worker_thread_.join();
    }
    worker_thread_ = std::thread(
      [this, candidate]() {
        const auto result = runCandidates(
          {candidate}, tracking_validation_timeout_s_, false, nullptr, false, true);
        if (result.disposition == agt_localization::RunDisposition::kSkipped) {
          execution_running_.store(false);
          return;
        }
        const bool accepted =
        result.disposition == agt_localization::RunDisposition::kAccepted;
        const auto snapshot = supervisor_.trackingValidation(accepted);
        auto status = agt_localization::makeTrackingValidationStatus(
          result.final_status, snapshot, result.disposition, result.backend_converged,
          result.error_code, result.failure_reason);
        status.header.stamp = now();
        status.header.frame_id = global_frame_;
        if (!accepted) {
          RCLCPP_WARN(
            get_logger(), "Tracking validation failed once: state=%u failures=%u reason=%s",
            static_cast<unsigned int>(status.state),
            status.consecutive_failures, result.failure_reason.c_str());
        }
        publishStatus(status);
        execution_running_.store(false);
      });
  }

  relocalization_core::Relocalizer relocalizer_;
  agt_localization::QualityConfig quality_config_;
  agt_localization::LocalizationSupervisor supervisor_;
  std::string global_map_pcd_;
  std::string global_map_processing_record_;
  std::string global_frame_;
  std::string odom_frame_;
  std::string base_frame_;
  std::string tracking_frame_;
  std::string cloud_topic_;
  std::string initialpose_topic_;
  std::string relocalize_action_name_;
  std::string configured_candidates_yaml_;
  std::string last_valid_pose_path_;
  std::string external_coarse_pose_topic_;
  std::string map_id_;
  std::string map_hash_;
  bool publish_tf_{true};
  bool publish_aligned_cloud_{true};
  bool manual_initialpose_enabled_{true};
  int candidate_max_{128};
  int max_expanded_candidates_{4096};
  double candidate_position_dedup_tolerance_{1.0e-3};
  double candidate_yaw_dedup_tolerance_{1.0e-3};
  double ambiguity_ratio_{0.10};
  double action_timeout_s_{30.0};
  double external_coarse_max_age_s_{2.0};
  double external_coarse_future_tolerance_s_{0.5};
  double max_cloud_age_s_{0.5};
  double max_cloud_future_tolerance_s_{0.1};
  bool require_nonzero_cloud_stamp_{true};
  double max_translation_innovation_{5.0};
  double max_yaw_innovation_{1.5707963267948966};
  bool tracking_validation_enabled_{true};
  double tracking_validation_period_s_{5.0};
  double tracking_validation_timeout_s_{3.0};

  std::optional<agt_localization::ConfiguredCandidateDocument>
    configured_candidate_document_;
  std::optional<Candidate> last_valid_candidate_;
  std::mutex last_pose_mutex_;
  geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr latest_external_coarse_pose_;
  std::mutex external_coarse_pose_mutex_;
  sensor_msgs::msg::PointCloud2::SharedPtr latest_cloud_msg_;
  std::mutex cloud_mutex_;
  std::optional<rclcpp::Time> last_tracking_validation_cloud_stamp_;
  std::mutex tracking_validation_stamp_mutex_;

  Eigen::Matrix4f latest_map_to_odom_{Eigen::Matrix4f::Identity()};
  bool has_latest_tf_{false};
  std::mutex tf_mutex_;
  LocalizationStatus last_status_;
  std::mutex status_mutex_;

  std::atomic<bool> execution_running_{false};
  std::atomic<bool> cancel_requested_{false};
  std::mutex worker_mutex_;
  std::thread worker_thread_;

  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr tf_timer_;
  rclcpp::TimerBase::SharedPtr tracking_validation_timer_;
  rclcpp_action::Server<Relocalize>::SharedPtr action_server_;
  rclcpp::Publisher<LocalizationStatus>::SharedPtr status_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr legacy_status_pub_;
  rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr global_pose_pub_;
  rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr coarse_pose_pub_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr aligned_cloud_pub_;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr initialpose_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr
    external_coarse_pose_sub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  int result = 0;
  try {
    rclcpp::spin(std::make_shared<RelocalizationNode>());
  } catch (const std::exception & error) {
    RCLCPP_FATAL(
      rclcpp::get_logger("relocalization_node"), "Failed to start relocalization: %s",
      error.what());
    result = 1;
  }
  rclcpp::shutdown();
  return result;
}
