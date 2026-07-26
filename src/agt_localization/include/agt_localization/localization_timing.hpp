#ifndef AGT_LOCALIZATION__LOCALIZATION_TIMING_HPP_
#define AGT_LOCALIZATION__LOCALIZATION_TIMING_HPP_

#include <cmath>
#include <string>

#include <Eigen/Geometry>

namespace agt_localization
{

struct CloudTimeConfig
{
  double max_age_s{0.5};
  double future_tolerance_s{0.1};
  bool require_nonzero_stamp{true};
};

struct CloudTimeDecision
{
  bool accepted{false};
  double age_s{0.0};
  std::string message;
};

inline CloudTimeDecision validateCloudTimestamp(
  double now_sec,
  double stamp_sec,
  const CloudTimeConfig & config)
{
  CloudTimeDecision decision;
  if (!std::isfinite(now_sec) || !std::isfinite(stamp_sec) ||
    !std::isfinite(config.max_age_s) || config.max_age_s <= 0.0 ||
    !std::isfinite(config.future_tolerance_s) || config.future_tolerance_s < 0.0)
  {
    decision.message = "cloud timestamp or freshness configuration is invalid";
    return decision;
  }

  decision.age_s = now_sec - stamp_sec;
  if (config.require_nonzero_stamp && stamp_sec == 0.0) {
    decision.message = "latest point cloud has a zero timestamp";
    return decision;
  }
  if (decision.age_s < -config.future_tolerance_s) {
    decision.message = "latest point cloud timestamp is in the future";
    return decision;
  }
  if (decision.age_s > config.max_age_s) {
    decision.message = "latest point cloud is stale";
    return decision;
  }

  decision.accepted = true;
  decision.message = "latest point cloud timestamp is fresh";
  return decision;
}

// All matrices use T_parent_child semantics, matching TransformStamped.
inline Eigen::Matrix4f predictMapFromTracking(
  const Eigen::Matrix4f & map_from_odom,
  const Eigen::Matrix4f & odom_from_tracking)
{
  return map_from_odom * odom_from_tracking;
}

}  // namespace agt_localization

#endif  // AGT_LOCALIZATION__LOCALIZATION_TIMING_HPP_
