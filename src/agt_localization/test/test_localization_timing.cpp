#include <cmath>
#include <cstdint>
#include <limits>
#include <optional>

#include <Eigen/Geometry>
#include <gtest/gtest.h>

#include "agt_localization/localization_timing.hpp"
#include "agt_localization/quality_validator.hpp"

namespace
{

Eigen::Matrix4f makeTransform(float x, float y, float yaw)
{
  Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
  transform.block<3, 3>(0, 0) =
    Eigen::AngleAxisf(yaw, Eigen::Vector3f::UnitZ()).toRotationMatrix();
  transform(0, 3) = x;
  transform(1, 3) = y;
  return transform;
}

}  // namespace

TEST(LocalizationTimingTest, AcceptsFreshCloudTimestamp)
{
  agt_localization::CloudTimeConfig config;
  const auto decision = agt_localization::validateCloudTimestamp(10.0, 9.7, config);
  EXPECT_TRUE(decision.accepted);
  EXPECT_NEAR(decision.age_s, 0.3, 1.0e-9);
}

TEST(LocalizationTimingTest, RejectsZeroTimestampWhenRequired)
{
  agt_localization::CloudTimeConfig config;
  const auto decision = agt_localization::validateCloudTimestamp(0.0, 0.0, config);
  EXPECT_FALSE(decision.accepted);
  EXPECT_NE(decision.message.find("zero"), std::string::npos);
}

TEST(LocalizationTimingTest, RejectsStaleTimestamp)
{
  agt_localization::CloudTimeConfig config;
  const auto decision = agt_localization::validateCloudTimestamp(10.0, 9.4, config);
  EXPECT_FALSE(decision.accepted);
  EXPECT_NE(decision.message.find("stale"), std::string::npos);
  EXPECT_NEAR(decision.age_s, 0.6, 1.0e-9);
}

TEST(LocalizationTimingTest, HandlesFutureTolerance)
{
  agt_localization::CloudTimeConfig config;
  EXPECT_TRUE(agt_localization::validateCloudTimestamp(10.0, 10.05, config).accepted);
  const auto decision = agt_localization::validateCloudTimestamp(10.0, 10.2, config);
  EXPECT_FALSE(decision.accepted);
  EXPECT_NE(decision.message.find("future"), std::string::npos);
}

TEST(LocalizationTimingTest, RejectsNonFiniteTimestamp)
{
  agt_localization::CloudTimeConfig config;
  const auto decision = agt_localization::validateCloudTimestamp(
    10.0, std::numeric_limits<double>::quiet_NaN(), config);
  EXPECT_FALSE(decision.accepted);
  EXPECT_NE(decision.message.find("invalid"), std::string::npos);
}

TEST(LocalizationTimingTest, ClassifiesExactCloudStampSequence)
{
  using agt_localization::CloudSequenceStatus;
  using agt_localization::classifyCloudSequence;

  EXPECT_EQ(classifyCloudSequence(std::nullopt, 100), CloudSequenceStatus::kNew);
  EXPECT_EQ(
    classifyCloudSequence(std::optional<std::int64_t>{100}, 101),
    CloudSequenceStatus::kNew);
  EXPECT_EQ(
    classifyCloudSequence(std::optional<std::int64_t>{100}, 100),
    CloudSequenceStatus::kDuplicate);
  EXPECT_EQ(
    classifyCloudSequence(std::optional<std::int64_t>{100}, 99),
    CloudSequenceStatus::kTimeMovedBackward);
  EXPECT_EQ(
    classifyCloudSequence(std::optional<std::int64_t>{1000000000}, 1000000001),
    CloudSequenceStatus::kNew);
}

TEST(LocalizationTimingTest, BackwardStampRequiresAFollowingNewCloud)
{
  using agt_localization::CloudSequenceStatus;
  using agt_localization::classifyCloudSequence;

  std::optional<std::int64_t> baseline_ns{100000000000};
  constexpr std::int64_t reset_stamp_ns = 10000000000;
  EXPECT_EQ(
    classifyCloudSequence(baseline_ns, reset_stamp_ns),
    CloudSequenceStatus::kTimeMovedBackward);

  baseline_ns = reset_stamp_ns;
  EXPECT_EQ(
    classifyCloudSequence(baseline_ns, reset_stamp_ns),
    CloudSequenceStatus::kDuplicate);
  EXPECT_EQ(
    classifyCloudSequence(baseline_ns, reset_stamp_ns + 1),
    CloudSequenceStatus::kNew);
}

TEST(LocalizationTimingTest, UsesProvidedClockInsteadOfWallClock)
{
  agt_localization::CloudTimeConfig config;
  EXPECT_TRUE(agt_localization::validateCloudTimestamp(100.0, 99.8, config).accepted);
  EXPECT_FALSE(agt_localization::validateCloudTimestamp(100.0, 98.0, config).accepted);
}

TEST(LocalizationTimingTest, PropagatesTranslationAndRotationInParentFrame)
{
  const auto map_from_odom = makeTransform(10.0F, 2.0F, 0.5F);
  const auto odom_from_tracking = makeTransform(1.0F, -0.25F, -0.2F);
  const auto map_from_tracking = agt_localization::predictMapFromTracking(
    map_from_odom, odom_from_tracking);
  const auto expected = map_from_odom * odom_from_tracking;
  EXPECT_TRUE(map_from_tracking.isApprox(expected, 1.0e-6F));
  EXPECT_NEAR(
    std::atan2(map_from_tracking(1, 0), map_from_tracking(0, 0)), 0.3, 1.0e-6);
}

TEST(LocalizationTimingTest, IncludesNonZeroTrackingExtrinsicInInnovationReference)
{
  const auto map_from_odom = makeTransform(1.0F, 0.0F, 0.0F);
  const auto odom_from_tracking = makeTransform(0.0F, 0.0F, 0.0F);
  const auto map_from_tracking = agt_localization::predictMapFromTracking(
    map_from_odom, odom_from_tracking);
  const auto tracking_from_base = makeTransform(0.4F, -0.1F, 0.15F);
  const auto predicted_map_from_base = map_from_tracking * tracking_from_base;
  EXPECT_NEAR(predicted_map_from_base(0, 3), 1.4, 1.0e-6);
  EXPECT_NEAR(predicted_map_from_base(1, 3), -0.1, 1.0e-6);
}

TEST(LocalizationTimingTest, InnovationIsMeasuredAgainstCurrentPrediction)
{
  constexpr double kPi = 3.14159265358979323846;
  agt_localization::QualityObservation observation;
  observation.backend_success = true;
  observation.has_converged = true;
  observation.fitness_score = 0.1;
  observation.scan_points = 500;
  observation.initial_x = 1.0;
  observation.estimated_x = 1.02;
  observation.initial_yaw = 40.0 * kPi / 180.0;
  observation.estimated_yaw = 42.0 * kPi / 180.0;
  observation.runtime_ms = 1.0;

  agt_localization::QualityConfig config;
  config.max_translation_innovation = 1.0;
  config.max_yaw_innovation = 1.0;
  const auto decision = agt_localization::validateQuality(observation, config);
  EXPECT_TRUE(decision.accepted);
  EXPECT_NEAR(decision.translation_innovation, 0.02, 1.0e-6);
  EXPECT_NEAR(decision.yaw_innovation, 2.0 * kPi / 180.0, 1.0e-6);
}
