#pragma once

#include <cstdint>
#include <string>

namespace agt_localization
{

enum class RecoveryTriggerMode : std::uint8_t
{
  kNone = 0,
  kLocalCandidates = 1,
  kAutoSearch = 2,
};

struct RecoveryTriggerConfig
{
  double cooldown_s{5.0};
  bool trigger_recovering{true};
  bool trigger_lost{true};
};

struct RecoveryTriggerInput
{
  std::uint8_t localization_state{0};
  double now_s{0.0};
  bool request_in_flight{false};
};

struct RecoveryTriggerDecision
{
  RecoveryTriggerMode mode{RecoveryTriggerMode::kNone};
  bool trigger{false};
  std::string reason;
};

class RecoveryTriggerPolicy
{
public:
  RecoveryTriggerPolicy(
    std::uint8_t tracking_state,
    std::uint8_t recovering_state,
    std::uint8_t lost_state,
    RecoveryTriggerConfig config = {});

  RecoveryTriggerDecision evaluate(const RecoveryTriggerInput & input);
  void noteRequestFinished() noexcept;

private:
  std::uint8_t tracking_state_{0};
  std::uint8_t recovering_state_{0};
  std::uint8_t lost_state_{0};
  RecoveryTriggerConfig config_;
  std::uint8_t last_state_{0};
  bool has_last_state_{false};
  double last_trigger_s_{-1.0e100};
};

}  // namespace agt_localization
