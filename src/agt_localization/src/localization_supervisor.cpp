#include "agt_localization/localization_supervisor.hpp"

#include <algorithm>
#include <stdexcept>

namespace agt_localization
{

LocalizationSupervisor::LocalizationSupervisor(const SupervisorConfig & config)
: config_(config)
{
  if (config_.confirmations_required == 0U || config_.failures_to_recover == 0U ||
    config_.failures_to_lost == 0U || config_.failures_to_recover > config_.failures_to_lost)
  {
    throw std::invalid_argument("invalid localization supervisor thresholds");
  }
}

const SupervisorConfig & LocalizationSupervisor::config() const
{
  return config_;
}

void LocalizationSupervisor::setConfig(const SupervisorConfig & config)
{
  if (config.confirmations_required == 0U || config.failures_to_recover == 0U ||
    config.failures_to_lost == 0U || config.failures_to_recover > config.failures_to_lost)
  {
    throw std::invalid_argument("invalid localization supervisor thresholds");
  }
  config_ = config;
}

SupervisorSnapshot LocalizationSupervisor::snapshot() const
{
  return makeSnapshot();
}

SupervisorSnapshot LocalizationSupervisor::beginSearch()
{
  state_ = SupervisorState::kSearching;
  resetSuccesses();
  resetFailures();
  return makeSnapshot();
}

SupervisorSnapshot LocalizationSupervisor::beginVerification()
{
  if (state_ == SupervisorState::kSearching || state_ == SupervisorState::kVerifying) {
    state_ = SupervisorState::kVerifying;
  }
  return makeSnapshot();
}

SupervisorSnapshot LocalizationSupervisor::acceptSearchResult()
{
  if (state_ != SupervisorState::kSearching && state_ != SupervisorState::kVerifying &&
    state_ != SupervisorState::kDegraded && state_ != SupervisorState::kRecovering)
  {
    return makeSnapshot();
  }

  ++consecutive_successes_;
  resetFailures();
  if (consecutive_successes_ >= config_.confirmations_required) {
    state_ = SupervisorState::kTracking;
  } else {
    state_ = SupervisorState::kVerifying;
  }
  return makeSnapshot();
}

SupervisorSnapshot LocalizationSupervisor::rejectSearchResult()
{
  resetSuccesses();
  ++consecutive_failures_;
  state_ = SupervisorState::kLost;
  return makeSnapshot();
}

SupervisorSnapshot LocalizationSupervisor::trackingValidation(bool accepted)
{
  if (accepted) {
    return acceptSearchResult();
  }

  resetSuccesses();
  ++consecutive_failures_;
  if (state_ == SupervisorState::kTracking) {
    state_ = SupervisorState::kDegraded;
  } else if (state_ == SupervisorState::kDegraded &&
    consecutive_failures_ >= config_.failures_to_recover)
  {
    state_ = SupervisorState::kRecovering;
  } else if (state_ == SupervisorState::kRecovering &&
    consecutive_failures_ >= config_.failures_to_lost)
  {
    state_ = SupervisorState::kLost;
  }
  return makeSnapshot();
}

SupervisorSnapshot LocalizationSupervisor::cancel()
{
  resetSuccesses();
  state_ = SupervisorState::kRecovering;
  return makeSnapshot();
}

SupervisorSnapshot LocalizationSupervisor::timeout()
{
  resetSuccesses();
  ++consecutive_failures_;
  state_ = SupervisorState::kLost;
  return makeSnapshot();
}

SupervisorSnapshot LocalizationSupervisor::makeSnapshot() const
{
  SupervisorSnapshot snapshot;
  snapshot.state = state_;
  snapshot.consecutive_successes = consecutive_successes_;
  snapshot.consecutive_failures = consecutive_failures_;
  snapshot.navigation_allowed = state_ == SupervisorState::kTracking;
  return snapshot;
}

void LocalizationSupervisor::resetSuccesses()
{
  consecutive_successes_ = 0U;
}

void LocalizationSupervisor::resetFailures()
{
  consecutive_failures_ = 0U;
}

}  // namespace agt_localization
