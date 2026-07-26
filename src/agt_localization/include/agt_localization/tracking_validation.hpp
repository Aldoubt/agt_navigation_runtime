#ifndef AGT_LOCALIZATION__TRACKING_VALIDATION_HPP_
#define AGT_LOCALIZATION__TRACKING_VALIDATION_HPP_

#include <cstdint>
#include <stdexcept>
#include <string>

#include <agt_interfaces/msg/localization_status.hpp>

#include "agt_localization/localization_supervisor.hpp"

namespace agt_localization
{

enum class RunDisposition
{
  kAccepted,
  kRejected,
  kSkipped
};

inline agt_interfaces::msg::LocalizationStatus makeTrackingValidationStatus(
  agt_interfaces::msg::LocalizationStatus status,
  const SupervisorSnapshot & snapshot,
  RunDisposition disposition,
  bool backend_converged,
  std::uint16_t error_code,
  const std::string & failure_reason)
{
  if (disposition == RunDisposition::kSkipped) {
    throw std::invalid_argument("skipped tracking validation must not publish a status");
  }

  const bool accepted = disposition == RunDisposition::kAccepted;
  status.state = static_cast<std::uint8_t>(snapshot.state);
  status.pose_valid = accepted;
  status.localization_accepted = accepted;
  status.has_converged = backend_converged;
  status.error_code = accepted ?
    agt_interfaces::msg::LocalizationStatus::ERROR_NONE : error_code;
  status.consecutive_successes = static_cast<std::uint32_t>(snapshot.consecutive_successes);
  status.consecutive_failures = static_cast<std::uint32_t>(snapshot.consecutive_failures);
  status.message = accepted ?
    "tracking validation accepted" :
    "tracking validation failed: " + failure_reason;
  return status;
}

}  // namespace agt_localization

#endif  // AGT_LOCALIZATION__TRACKING_VALIDATION_HPP_
