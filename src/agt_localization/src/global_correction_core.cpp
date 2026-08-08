#include "agt_localization/global_correction_core.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace agt_localization
{
namespace
{

bool finiteMatrix(const Eigen::Matrix4d & value)
{
  return value.array().isFinite().all();
}

double normalizeYaw(double yaw)
{
  return std::atan2(std::sin(yaw), std::cos(yaw));
}

double matrixYaw(const Eigen::Matrix4d & value)
{
  return std::atan2(value(1, 0), value(0, 0));
}

double translationNorm(const Eigen::Matrix4d & value)
{
  return value.block<3, 1>(0, 3).norm();
}

const CorrectionLimit & limitFor(
  const GlobalCorrectionPolicy & policy, CorrectionTrackingState state)
{
  switch (state) {
    case CorrectionTrackingState::kRecovering:
      return policy.recovering;
    case CorrectionTrackingState::kLost:
      return policy.lost;
    case CorrectionTrackingState::kTracking:
    default:
      return policy.tracking;
  }
}

GlobalCorrectionDecision reject(
  const std::string & code, const std::string & message,
  std::uint64_t generation, const Eigen::Matrix4d & candidate)
{
  GlobalCorrectionDecision output;
  output.code = code;
  output.message = message;
  output.generation = generation;
  output.map_from_odom = candidate;
  return output;
}

}  // namespace

GlobalCorrectionCore::GlobalCorrectionCore(GlobalCorrectionPolicy policy)
: policy_(std::move(policy))
{
}

void GlobalCorrectionCore::setExpectedMapIdentity(std::string map_id, std::string map_hash)
{
  map_id_ = std::move(map_id);
  map_hash_ = std::move(map_hash);
}

GlobalCorrectionDecision GlobalCorrectionCore::evaluate(
  const GlobalCorrectionObservation & observation)
{
  if (!observation.localization_accepted) {
    return reject(
      "LOCALIZATION_NOT_ACCEPTED", "localization evidence was not accepted",
      generation_, Eigen::Matrix4d::Identity());
  }
  if (!std::isfinite(observation.stamp_s) || observation.stamp_s <= 0.0 ||
    !std::isfinite(observation.now_s))
  {
    return reject(
      "INVALID_TIMESTAMP", "correction timestamp is invalid",
      generation_, Eigen::Matrix4d::Identity());
  }
  const double age_s = observation.now_s - observation.stamp_s;
  if (age_s > policy_.max_age_s || age_s < -policy_.future_tolerance_s) {
    return reject(
      "STALE_CORRECTION", "correction evidence is stale or from the future",
      generation_, Eigen::Matrix4d::Identity());
  }
  if (!finiteMatrix(observation.map_from_base) || !finiteMatrix(observation.odom_from_base)) {
    return reject(
      "NON_FINITE_TRANSFORM", "correction transforms contain a non-finite value",
      generation_, Eigen::Matrix4d::Identity());
  }
  if (!std::isfinite(observation.fitness_score) ||
    observation.fitness_score > policy_.max_fitness_score)
  {
    return reject(
      "FITNESS_REJECTED", "correction fitness exceeds the configured threshold",
      generation_, Eigen::Matrix4d::Identity());
  }
  if (!std::isfinite(observation.measurement_translation_innovation_m) ||
    observation.measurement_translation_innovation_m >
    policy_.max_measurement_translation_innovation_m)
  {
    return reject(
      "MEASUREMENT_TRANSLATION_REJECTED",
      "relocalization translation innovation exceeds the configured threshold",
      generation_, Eigen::Matrix4d::Identity());
  }
  if (!std::isfinite(observation.measurement_yaw_innovation_rad) ||
    std::abs(observation.measurement_yaw_innovation_rad) >
    policy_.max_measurement_yaw_innovation_rad)
  {
    return reject(
      "MEASUREMENT_YAW_REJECTED",
      "relocalization yaw innovation exceeds the configured threshold",
      generation_, Eigen::Matrix4d::Identity());
  }

  if (!map_id_.empty() && observation.map_id != map_id_) {
    return reject(
      "MAP_ID_MISMATCH", "correction map_id does not match the active map",
      generation_, Eigen::Matrix4d::Identity());
  }
  if (!map_hash_.empty() && observation.map_hash != map_hash_) {
    return reject(
      "MAP_HASH_MISMATCH", "correction map_hash does not match the active map",
      generation_, Eigen::Matrix4d::Identity());
  }
  if (initialized_ && observation.stamp_s <= last_accepted_stamp_s_) {
    return reject(
      "DUPLICATE_OR_OLD_CORRECTION",
      "correction timestamp is not newer than the last accepted correction",
      generation_, latest_map_from_odom_);
  }
  if (initialized_ && observation.stamp_s - last_accepted_stamp_s_ < policy_.min_interval_s) {
    return reject(
      "CORRECTION_RATE_LIMITED", "correction arrived before the minimum interval",
      generation_, latest_map_from_odom_);
  }

  const Eigen::Matrix4d candidate =
    observation.map_from_base * observation.odom_from_base.inverse();
  if (!finiteMatrix(candidate)) {
    return reject(
      "NON_FINITE_CORRECTION", "computed map->odom transform is non-finite",
      generation_, candidate);
  }

  double delta_translation = 0.0;
  double delta_yaw = 0.0;
  if (initialized_) {
    const Eigen::Matrix4d delta = latest_map_from_odom_.inverse() * candidate;
    delta_translation = translationNorm(delta);
    delta_yaw = std::abs(normalizeYaw(matrixYaw(candidate) - matrixYaw(latest_map_from_odom_)));

    if (delta_translation <= policy_.duplicate_translation_epsilon_m &&
      delta_yaw <= policy_.duplicate_yaw_epsilon_rad)
    {
      return reject(
        "DUPLICATE_CORRECTION", "correction is equivalent to the current map->odom transform",
        generation_, candidate);
    }

    const auto & limit = limitFor(policy_, observation.tracking_state);
    const bool lost_reanchor =
      observation.tracking_state == CorrectionTrackingState::kLost &&
      policy_.allow_lost_reanchor;
    if (!lost_reanchor && delta_translation > limit.max_translation_m) {
      auto output = reject(
        "TRANSLATION_JUMP_REJECTED",
        "map->odom translation correction exceeds the state-specific threshold",
        generation_, candidate);
      output.delta_translation_m = delta_translation;
      output.delta_yaw_rad = delta_yaw;
      return output;
    }
    if (!lost_reanchor && delta_yaw > limit.max_yaw_rad) {
      auto output = reject(
        "YAW_JUMP_REJECTED",
        "map->odom yaw correction exceeds the state-specific threshold",
        generation_, candidate);
      output.delta_translation_m = delta_translation;
      output.delta_yaw_rad = delta_yaw;
      return output;
    }
  }

  if (map_id_.empty()) {
    map_id_ = observation.map_id;
  }
  if (map_hash_.empty()) {
    map_hash_ = observation.map_hash;
  }
  initialized_ = true;
  latest_map_from_odom_ = candidate;
  last_accepted_stamp_s_ = observation.stamp_s;
  ++generation_;

  GlobalCorrectionDecision output;
  output.accepted = true;
  output.reanchor =
    observation.tracking_state == CorrectionTrackingState::kLost && generation_ > 1U;
  output.code = output.reanchor ? "REANCHOR_ACCEPTED" : "CORRECTION_ACCEPTED";
  output.message = output.reanchor ?
    "lost-state global reanchor accepted" : "sparse global correction accepted";
  output.map_from_odom = candidate;
  output.delta_translation_m = delta_translation;
  output.delta_yaw_rad = delta_yaw;
  output.generation = generation_;
  return output;
}

bool GlobalCorrectionCore::initialized() const noexcept
{
  return initialized_;
}

std::uint64_t GlobalCorrectionCore::generation() const noexcept
{
  return generation_;
}

const Eigen::Matrix4d & GlobalCorrectionCore::latestMapFromOdom() const noexcept
{
  return latest_map_from_odom_;
}

const std::string & GlobalCorrectionCore::mapId() const noexcept
{
  return map_id_;
}

const std::string & GlobalCorrectionCore::mapHash() const noexcept
{
  return map_hash_;
}

}  // namespace agt_localization
