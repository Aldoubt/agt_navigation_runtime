#pragma once

#include <cstdint>
#include <limits>
#include <string>

#include <Eigen/Dense>

namespace agt_localization
{

enum class CorrectionTrackingState : std::uint8_t
{
  kTracking = 0,
  kRecovering = 1,
  kLost = 2,
};

struct CorrectionLimit
{
  double max_translation_m{0.5};
  double max_yaw_rad{0.20};
};

struct GlobalCorrectionPolicy
{
  double max_age_s{1.0};
  double future_tolerance_s{0.10};
  double min_interval_s{1.0};
  double max_fitness_score{2.0};
  double max_measurement_translation_innovation_m{5.0};
  double max_measurement_yaw_innovation_rad{1.5707963267948966};
  double duplicate_translation_epsilon_m{1.0e-4};
  double duplicate_yaw_epsilon_rad{1.0e-4};
  CorrectionLimit tracking{0.50, 0.20};
  CorrectionLimit recovering{2.00, 0.70};
  CorrectionLimit lost{20.0, 3.14159265358979323846};
  bool allow_lost_reanchor{true};
};

struct GlobalCorrectionObservation
{
  double stamp_s{0.0};
  double now_s{0.0};
  Eigen::Matrix4d map_from_base{Eigen::Matrix4d::Identity()};
  Eigen::Matrix4d odom_from_base{Eigen::Matrix4d::Identity()};
  double fitness_score{std::numeric_limits<double>::infinity()};
  double measurement_translation_innovation_m{0.0};
  double measurement_yaw_innovation_rad{0.0};
  std::string map_id;
  std::string map_hash;
  bool localization_accepted{false};
  CorrectionTrackingState tracking_state{CorrectionTrackingState::kTracking};
};

struct GlobalCorrectionDecision
{
  bool accepted{false};
  bool reanchor{false};
  std::string code{"UNSET"};
  std::string message;
  Eigen::Matrix4d map_from_odom{Eigen::Matrix4d::Identity()};
  double delta_translation_m{0.0};
  double delta_yaw_rad{0.0};
  std::uint64_t generation{0};
};

class GlobalCorrectionCore
{
public:
  explicit GlobalCorrectionCore(GlobalCorrectionPolicy policy = {});

  void setExpectedMapIdentity(std::string map_id, std::string map_hash);
  GlobalCorrectionDecision evaluate(const GlobalCorrectionObservation & observation);

  bool initialized() const noexcept;
  std::uint64_t generation() const noexcept;
  const Eigen::Matrix4d & latestMapFromOdom() const noexcept;
  const std::string & mapId() const noexcept;
  const std::string & mapHash() const noexcept;

private:
  GlobalCorrectionPolicy policy_;
  bool initialized_{false};
  std::uint64_t generation_{0};
  double last_accepted_stamp_s_{-std::numeric_limits<double>::infinity()};
  Eigen::Matrix4d latest_map_from_odom_{Eigen::Matrix4d::Identity()};
  std::string map_id_;
  std::string map_hash_;
};

}  // namespace agt_localization
