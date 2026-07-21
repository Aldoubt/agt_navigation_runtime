#ifndef AGT_LOCALIZATION__LOCALIZATION_SUPERVISOR_HPP_
#define AGT_LOCALIZATION__LOCALIZATION_SUPERVISOR_HPP_

#include <cstddef>
#include <cstdint>

namespace agt_localization
{

enum class SupervisorState : std::uint8_t
{
  kUninitialized = 0,
  kSearching = 1,
  kVerifying = 2,
  kTracking = 3,
  kDegraded = 4,
  kRecovering = 5,
  kLost = 6,
  kError = 7
};

struct SupervisorConfig
{
  std::size_t confirmations_required{1U};
  std::size_t failures_to_recover{2U};
  std::size_t failures_to_lost{3U};
};

struct SupervisorSnapshot
{
  SupervisorState state{SupervisorState::kUninitialized};
  std::size_t consecutive_successes{0U};
  std::size_t consecutive_failures{0U};
  bool navigation_allowed{false};
};

class LocalizationSupervisor
{
public:
  explicit LocalizationSupervisor(const SupervisorConfig & config = SupervisorConfig{});

  const SupervisorConfig & config() const;
  void setConfig(const SupervisorConfig & config);
  SupervisorSnapshot snapshot() const;

  // These methods are intentionally small and deterministic. The caller serializes events.
  SupervisorSnapshot beginSearch();
  SupervisorSnapshot beginVerification();
  SupervisorSnapshot acceptSearchResult();
  SupervisorSnapshot rejectSearchResult();
  SupervisorSnapshot trackingValidation(bool accepted);
  SupervisorSnapshot cancel();
  SupervisorSnapshot timeout();

private:
  SupervisorSnapshot makeSnapshot() const;
  void resetSuccesses();
  void resetFailures();

  SupervisorConfig config_;
  SupervisorState state_{SupervisorState::kUninitialized};
  std::size_t consecutive_successes_{0U};
  std::size_t consecutive_failures_{0U};
};

}  // namespace agt_localization

#endif  // AGT_LOCALIZATION__LOCALIZATION_SUPERVISOR_HPP_
