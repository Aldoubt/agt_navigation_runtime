#include <gtest/gtest.h>

#include "agt_localization/recovery_trigger_policy.hpp"

namespace
{
constexpr std::uint8_t kTracking = 3;
constexpr std::uint8_t kRecovering = 5;
constexpr std::uint8_t kLost = 6;
}  // namespace

TEST(RecoveryTriggerPolicy, TrackingDoesNotTrigger)
{
  agt_localization::RecoveryTriggerPolicy policy(kTracking, kRecovering, kLost);
  const auto decision = policy.evaluate({kTracking, 1.0, false});
  EXPECT_FALSE(decision.trigger);
  EXPECT_EQ(decision.mode, agt_localization::RecoveryTriggerMode::kNone);
}

TEST(RecoveryTriggerPolicy, RecoveringTriggersLocalCandidates)
{
  agt_localization::RecoveryTriggerPolicy policy(kTracking, kRecovering, kLost);
  const auto decision = policy.evaluate({kRecovering, 1.0, false});
  EXPECT_TRUE(decision.trigger);
  EXPECT_EQ(decision.mode, agt_localization::RecoveryTriggerMode::kLocalCandidates);
}

TEST(RecoveryTriggerPolicy, LostTriggersAutoSearch)
{
  agt_localization::RecoveryTriggerPolicy policy(kTracking, kRecovering, kLost);
  const auto decision = policy.evaluate({kLost, 1.0, false});
  EXPECT_TRUE(decision.trigger);
  EXPECT_EQ(decision.mode, agt_localization::RecoveryTriggerMode::kAutoSearch);
}

TEST(RecoveryTriggerPolicy, InFlightRequestSuppressesTrigger)
{
  agt_localization::RecoveryTriggerPolicy policy(kTracking, kRecovering, kLost);
  const auto decision = policy.evaluate({kRecovering, 1.0, true});
  EXPECT_FALSE(decision.trigger);
}

TEST(RecoveryTriggerPolicy, RepeatedStateIsRateLimited)
{
  agt_localization::RecoveryTriggerPolicy policy(kTracking, kRecovering, kLost);
  ASSERT_TRUE(policy.evaluate({kRecovering, 1.0, false}).trigger);
  EXPECT_FALSE(policy.evaluate({kRecovering, 2.0, false}).trigger);
  EXPECT_TRUE(policy.evaluate({kRecovering, 7.0, false}).trigger);
}

TEST(RecoveryTriggerPolicy, EscalationToLostTriggersImmediately)
{
  agt_localization::RecoveryTriggerPolicy policy(kTracking, kRecovering, kLost);
  ASSERT_TRUE(policy.evaluate({kRecovering, 1.0, false}).trigger);
  const auto decision = policy.evaluate({kLost, 2.0, false});
  EXPECT_TRUE(decision.trigger);
  EXPECT_EQ(decision.mode, agt_localization::RecoveryTriggerMode::kAutoSearch);
}
