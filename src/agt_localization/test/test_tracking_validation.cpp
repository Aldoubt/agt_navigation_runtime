#include <stdexcept>

#include <gtest/gtest.h>

#include "agt_localization/localization_supervisor.hpp"
#include "agt_localization/localization_timing.hpp"
#include "agt_localization/tracking_validation.hpp"

using agt_localization::LocalizationSupervisor;
using agt_localization::RunDisposition;
using agt_localization::SupervisorState;
using LocalizationStatus = agt_interfaces::msg::LocalizationStatus;

TEST(TrackingValidationTest, AcceptedResultProducesReadyTrackingStatus)
{
  LocalizationSupervisor supervisor;
  supervisor.beginSearch();
  const auto snapshot = supervisor.acceptSearchResult();

  LocalizationStatus run_status;
  run_status.state = LocalizationStatus::STATE_VERIFYING;
  run_status.pose_valid = false;
  run_status.localization_accepted = false;
  const auto status = agt_localization::makeTrackingValidationStatus(
    run_status, snapshot, RunDisposition::kAccepted, true,
    LocalizationStatus::ERROR_BACKEND_FAILED, "ignored");

  EXPECT_EQ(status.state, LocalizationStatus::STATE_TRACKING);
  EXPECT_TRUE(status.pose_valid);
  EXPECT_TRUE(status.localization_accepted);
  EXPECT_TRUE(status.has_converged);
  EXPECT_EQ(status.error_code, LocalizationStatus::ERROR_NONE);
  EXPECT_EQ(status.consecutive_failures, 0U);
  EXPECT_EQ(status.message, "tracking validation accepted");
}

TEST(TrackingValidationTest, StaleDuplicateFailuresReachLostOncePerValidation)
{
  agt_localization::CloudTimeConfig time_config;
  const auto cloud_time = agt_localization::validateCloudTimestamp(11.0, 10.0, time_config);
  ASSERT_EQ(
    agt_localization::decideTrackingCloudDisposition(
      cloud_time, agt_localization::CloudSequenceStatus::kDuplicate),
    agt_localization::TrackingCloudDisposition::kReject);

  LocalizationSupervisor supervisor;
  supervisor.beginSearch();
  supervisor.acceptSearchResult();

  const auto first = supervisor.trackingValidation(false);
  EXPECT_EQ(first.state, SupervisorState::kDegraded);
  EXPECT_EQ(first.consecutive_failures, 1U);
  const auto second = supervisor.trackingValidation(false);
  EXPECT_EQ(second.state, SupervisorState::kRecovering);
  EXPECT_EQ(second.consecutive_failures, 2U);
  const auto third = supervisor.trackingValidation(false);
  EXPECT_EQ(third.state, SupervisorState::kLost);
  EXPECT_EQ(third.consecutive_failures, 3U);
}

TEST(TrackingValidationTest, PreservesBackendConvergenceWhenQualityRejects)
{
  LocalizationSupervisor supervisor;
  supervisor.beginSearch();
  supervisor.acceptSearchResult();
  const auto snapshot = supervisor.trackingValidation(false);

  LocalizationStatus run_status;
  run_status.fitness_score = 3.0;
  const auto status = agt_localization::makeTrackingValidationStatus(
    run_status, snapshot, RunDisposition::kRejected, true,
    LocalizationStatus::ERROR_FITNESS_REJECTED, "fitness exceeds threshold");

  EXPECT_EQ(status.state, LocalizationStatus::STATE_DEGRADED);
  EXPECT_FALSE(status.pose_valid);
  EXPECT_FALSE(status.localization_accepted);
  EXPECT_TRUE(status.has_converged);
  EXPECT_EQ(status.error_code, LocalizationStatus::ERROR_FITNESS_REJECTED);
  EXPECT_EQ(status.consecutive_failures, 1U);
}

TEST(TrackingValidationTest, SkippedResultCannotProduceAuthoritativeStatus)
{
  LocalizationStatus run_status;
  agt_localization::SupervisorSnapshot snapshot;
  EXPECT_THROW(
    (void)agt_localization::makeTrackingValidationStatus(
      run_status, snapshot, RunDisposition::kSkipped, false,
      LocalizationStatus::ERROR_NONE, "fresh duplicate"),
    std::invalid_argument);
}
