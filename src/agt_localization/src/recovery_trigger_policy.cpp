#include "agt_localization/recovery_trigger_policy.hpp"

#include <cmath>
#include <utility>

namespace agt_localization
{

RecoveryTriggerPolicy::RecoveryTriggerPolicy(
  std::uint8_t tracking_state,
  std::uint8_t recovering_state,
  std::uint8_t lost_state,
  RecoveryTriggerConfig config)
: tracking_state_(tracking_state),
  recovering_state_(recovering_state),
  lost_state_(lost_state),
  config_(std::move(config))
{
}

RecoveryTriggerDecision RecoveryTriggerPolicy::evaluate(
  const RecoveryTriggerInput & input)
{
  RecoveryTriggerDecision output;
  if (!std::isfinite(input.now_s)) {
    output.reason = "invalid current time";
    return output;
  }
  if (input.request_in_flight) {
    output.reason = "relocalization request already in flight";
    last_state_ = input.localization_state;
    has_last_state_ = true;
    return output;
  }

  const bool state_changed = !has_last_state_ || input.localization_state != last_state_;
  last_state_ = input.localization_state;
  has_last_state_ = true;

  if (input.localization_state == tracking_state_) {
    output.reason = "tracking state does not require recovery action";
    return output;
  }

  const bool cooldown_elapsed = input.now_s - last_trigger_s_ >= config_.cooldown_s;
  if (!state_changed && !cooldown_elapsed) {
    output.reason = "recovery trigger cooldown active";
    return output;
  }

  if (input.localization_state == recovering_state_ && config_.trigger_recovering) {
    output.trigger = true;
    output.mode = RecoveryTriggerMode::kLocalCandidates;
    output.reason = "recovering state requests local candidate relocalization";
    last_trigger_s_ = input.now_s;
    return output;
  }

  if (input.localization_state == lost_state_ && config_.trigger_lost) {
    output.trigger = true;
    output.mode = RecoveryTriggerMode::kAutoSearch;
    output.reason = "lost state requests broader automatic relocalization";
    last_trigger_s_ = input.now_s;
    return output;
  }

  output.reason = "localization state does not request recovery action";
  return output;
}

void RecoveryTriggerPolicy::noteRequestFinished() noexcept
{
  // The ROS owner keeps the in-flight state. This hook deliberately exists so
  // later policy revisions can account for result disposition without changing
  // the trigger-manager API.
}

}  // namespace agt_localization
