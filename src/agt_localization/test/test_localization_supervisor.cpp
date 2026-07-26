#include <gtest/gtest.h>

#include "agt_localization/localization_supervisor.hpp"

using agt_localization::LocalizationSupervisor;
using agt_localization::SupervisorConfig;
using agt_localization::SupervisorState;

TEST(LocalizationSupervisorTest, RequiresConfiguredConsecutiveConfirmations)
{
  SupervisorConfig config;
  config.confirmations_required = 2U;
  LocalizationSupervisor supervisor(config);

  EXPECT_EQ(supervisor.beginSearch().state, SupervisorState::kSearching);
  EXPECT_EQ(supervisor.beginVerification().state, SupervisorState::kVerifying);
  EXPECT_EQ(supervisor.acceptSearchResult().state, SupervisorState::kVerifying);
  EXPECT_FALSE(supervisor.snapshot().navigation_allowed);
  EXPECT_EQ(supervisor.acceptSearchResult().state, SupervisorState::kTracking);
  EXPECT_TRUE(supervisor.snapshot().navigation_allowed);
}

TEST(LocalizationSupervisorTest, FollowsDegradedRecoveringLostSequence)
{
  SupervisorConfig config;
  config.failures_to_recover = 2U;
  config.failures_to_lost = 3U;
  LocalizationSupervisor supervisor(config);

  supervisor.beginSearch();
  supervisor.acceptSearchResult();
  EXPECT_EQ(supervisor.snapshot().state, SupervisorState::kTracking);

  const auto first_failure = supervisor.trackingValidation(false);
  EXPECT_EQ(first_failure.state, SupervisorState::kDegraded);
  EXPECT_EQ(first_failure.consecutive_failures, 1U);

  const auto second_failure = supervisor.trackingValidation(false);
  EXPECT_EQ(second_failure.state, SupervisorState::kRecovering);
  EXPECT_EQ(second_failure.consecutive_failures, 2U);

  const auto third_failure = supervisor.trackingValidation(false);
  EXPECT_EQ(third_failure.state, SupervisorState::kLost);
  EXPECT_EQ(third_failure.consecutive_failures, 3U);
  EXPECT_FALSE(third_failure.navigation_allowed);
}

TEST(LocalizationSupervisorTest, AcceptedValidationClearsTrackingFailures)
{
  SupervisorConfig config;
  config.failures_to_recover = 2U;
  config.failures_to_lost = 3U;
  LocalizationSupervisor supervisor(config);

  supervisor.beginSearch();
  supervisor.acceptSearchResult();
  supervisor.trackingValidation(false);
  EXPECT_EQ(supervisor.trackingValidation(false).state, SupervisorState::kRecovering);

  const auto recovered = supervisor.trackingValidation(true);
  EXPECT_EQ(recovered.state, SupervisorState::kTracking);
  EXPECT_EQ(recovered.consecutive_failures, 0U);
  EXPECT_TRUE(recovered.navigation_allowed);
}

TEST(LocalizationSupervisorTest, AcceptedValidationRecoversOnlyAfterConfirmation)
{
  SupervisorConfig config;
  config.confirmations_required = 2U;
  LocalizationSupervisor supervisor(config);

  supervisor.beginSearch();
  supervisor.acceptSearchResult();
  EXPECT_EQ(supervisor.snapshot().state, SupervisorState::kVerifying);
  EXPECT_EQ(supervisor.trackingValidation(false).state, SupervisorState::kVerifying);
  EXPECT_EQ(supervisor.trackingValidation(true).state, SupervisorState::kVerifying);
  EXPECT_EQ(supervisor.trackingValidation(true).state, SupervisorState::kTracking);
}

TEST(LocalizationSupervisorTest, CancelAndTimeoutCloseNavigation)
{
  LocalizationSupervisor supervisor;
  supervisor.beginSearch();
  supervisor.acceptSearchResult();
  EXPECT_TRUE(supervisor.snapshot().navigation_allowed);

  EXPECT_EQ(supervisor.cancel().state, SupervisorState::kRecovering);
  EXPECT_FALSE(supervisor.snapshot().navigation_allowed);
  EXPECT_EQ(supervisor.timeout().state, SupervisorState::kLost);
}

TEST(LocalizationSupervisorTest, RejectsInvalidThresholds)
{
  SupervisorConfig config;
  config.confirmations_required = 0U;
  EXPECT_THROW({LocalizationSupervisor supervisor(config);}, std::invalid_argument);

  config.confirmations_required = 1U;
  config.failures_to_recover = 3U;
  config.failures_to_lost = 2U;
  EXPECT_THROW({LocalizationSupervisor supervisor(config);}, std::invalid_argument);
}
