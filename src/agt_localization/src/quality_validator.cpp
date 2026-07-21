#include "agt_localization/quality_validator.hpp"

#include <algorithm>
#include <cmath>

namespace agt_localization
{
namespace
{

constexpr double kPi = 3.14159265358979323846;
constexpr double kTwoPi = 2.0 * kPi;

bool finite(double value)
{
  return std::isfinite(value);
}

double normalizeYaw(double yaw)
{
  while (yaw > kPi) {
    yaw -= kTwoPi;
  }
  while (yaw < -kPi) {
    yaw += kTwoPi;
  }
  return yaw;
}

}  // namespace

QualityDecision validateQuality(
  const QualityObservation & observation,
  const QualityConfig & config)
{
  QualityDecision decision;
  decision.translation_innovation = std::sqrt(
    std::pow(observation.estimated_x - observation.initial_x, 2.0) +
    std::pow(observation.estimated_y - observation.initial_y, 2.0) +
    std::pow(observation.estimated_z - observation.initial_z, 2.0));
  decision.yaw_innovation =
    std::abs(normalizeYaw(observation.estimated_yaw - observation.initial_yaw));

  if (config.min_scan_points == 0U || observation.scan_points < config.min_scan_points) {
    decision.error_code = kQualityErrorScanTooSmall;
    decision.message = "scan has too few usable points";
    return decision;
  }
  if (!observation.backend_success || !observation.has_converged) {
    decision.error_code = kQualityErrorBackendFailed;
    decision.message = "registration backend did not converge";
    return decision;
  }
  if (!finite(observation.fitness_score) || observation.fitness_score > config.max_fitness_score) {
    decision.error_code = kQualityErrorFitnessRejected;
    decision.message = "fitness score exceeds acceptance threshold";
    return decision;
  }
  if (!finite(decision.translation_innovation) ||
    decision.translation_innovation > config.max_translation_innovation ||
    !finite(decision.yaw_innovation) || decision.yaw_innovation > config.max_yaw_innovation)
  {
    decision.error_code = kQualityErrorInvalidInitialGuess;
    decision.message = "registration innovation exceeds the configured bound";
    return decision;
  }
  if (!finite(observation.runtime_ms) || observation.runtime_ms < 0.0) {
    decision.error_code = kQualityErrorBackendFailed;
    decision.message = "registration runtime is invalid";
    return decision;
  }
  if (config.require_geometry_metrics && !observation.geometry_metrics_available) {
    decision.error_code = kQualityErrorBackendFailed;
    decision.message = "required geometry quality metrics are unavailable";
    return decision;
  }
  if (observation.geometry_metrics_available) {
    if (!finite(observation.overlap_ratio) || !finite(observation.inlier_ratio) ||
      observation.overlap_ratio < config.min_overlap_ratio ||
      observation.inlier_ratio < config.min_inlier_ratio)
    {
      decision.error_code = kQualityErrorFitnessRejected;
      decision.message = "geometric quality metrics are below the acceptance threshold";
      return decision;
    }
  }

  decision.accepted = true;
  decision.error_code = kQualityErrorNone;
  decision.message = "registration accepted";
  return decision;
}

bool isAmbiguousScore(
  double best_fitness_score,
  double second_fitness_score,
  double ambiguity_ratio)
{
  if (!finite(best_fitness_score) || !finite(second_fitness_score) ||
    !finite(ambiguity_ratio) || ambiguity_ratio < 0.0 ||
    best_fitness_score < 0.0 || second_fitness_score < 0.0)
  {
    return true;
  }
  const double tolerance = std::max(1.0e-6, best_fitness_score * ambiguity_ratio);
  return second_fitness_score <= best_fitness_score + tolerance;
}

}  // namespace agt_localization
