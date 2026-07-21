#ifndef AGT_LOCALIZATION__QUALITY_VALIDATOR_HPP_
#define AGT_LOCALIZATION__QUALITY_VALIDATOR_HPP_

#include <cstddef>
#include <cstdint>
#include <string>

namespace agt_localization
{

enum QualityErrorCode : std::uint16_t
{
  kQualityErrorNone = 0,
  kQualityErrorScanTooSmall = 101,
  kQualityErrorBackendFailed = 102,
  kQualityErrorFitnessRejected = 103,
  kQualityErrorInvalidInitialGuess = 104,
  kQualityErrorAmbiguousResult = 108
};

struct QualityConfig
{
  double max_fitness_score{2.0};
  std::size_t min_scan_points{200};
  double max_translation_innovation{5.0};
  double max_yaw_innovation{1.5707963267948966};
  double min_overlap_ratio{0.0};
  double min_inlier_ratio{0.0};
  bool require_geometry_metrics{false};
};

struct QualityObservation
{
  bool backend_success{false};
  bool has_converged{false};
  double fitness_score{0.0};
  std::size_t scan_points{0U};
  double initial_x{0.0};
  double initial_y{0.0};
  double initial_z{0.0};
  double initial_yaw{0.0};
  double estimated_x{0.0};
  double estimated_y{0.0};
  double estimated_z{0.0};
  double estimated_yaw{0.0};
  double overlap_ratio{0.0};
  double inlier_ratio{0.0};
  bool geometry_metrics_available{false};
  double runtime_ms{0.0};
};

struct QualityDecision
{
  bool accepted{false};
  bool ambiguous{false};
  std::uint16_t error_code{kQualityErrorBackendFailed};
  double translation_innovation{0.0};
  double yaw_innovation{0.0};
  std::string message;
};

QualityDecision validateQuality(
  const QualityObservation & observation,
  const QualityConfig & config);

bool isAmbiguousScore(
  double best_fitness_score,
  double second_fitness_score,
  double ambiguity_ratio);

}  // namespace agt_localization

#endif  // AGT_LOCALIZATION__QUALITY_VALIDATOR_HPP_
