#include <cmath>

#include <gtest/gtest.h>

#include "agt_localization/global_correction_core.hpp"

namespace
{

Eigen::Matrix4d pose(double x, double y, double yaw)
{
  Eigen::Matrix4d value = Eigen::Matrix4d::Identity();
  const double c = std::cos(yaw);
  const double s = std::sin(yaw);
  value(0, 0) = c;
  value(0, 1) = -s;
  value(1, 0) = s;
  value(1, 1) = c;
  value(0, 3) = x;
  value(1, 3) = y;
  return value;
}

agt_localization::GlobalCorrectionObservation observation(
  double stamp, const Eigen::Matrix4d & map_from_base,
  const Eigen::Matrix4d & odom_from_base,
  agt_localization::CorrectionTrackingState state =
  agt_localization::CorrectionTrackingState::kTracking)
{
  agt_localization::GlobalCorrectionObservation value;
  value.stamp_s = stamp;
  value.now_s = stamp + 0.05;
  value.map_from_base = map_from_base;
  value.odom_from_base = odom_from_base;
  value.fitness_score = 0.3;
  value.measurement_translation_innovation_m = 0.1;
  value.measurement_yaw_innovation_rad = 0.02;
  value.map_id = "greenhouse_a";
  value.map_hash = "sha256:map-a";
  value.localization_accepted = true;
  value.tracking_state = state;
  return value;
}

}  // namespace

TEST(GlobalCorrectionCore, ComputesMapFromOdomAndInitialGeneration)
{
  agt_localization::GlobalCorrectionCore core;
  core.setExpectedMapIdentity("greenhouse_a", "sha256:map-a");

  const auto result = core.evaluate(observation(10.0, pose(5.0, 2.0, 0.1), pose(4.0, 2.0, 0.1)));

  ASSERT_TRUE(result.accepted);
  EXPECT_EQ(result.generation, 1U);
  EXPECT_NEAR(result.map_from_odom(0, 3), 1.0, 1.0e-9);
  EXPECT_NEAR(result.map_from_odom(1, 3), 0.0, 1.0e-9);
}

TEST(GlobalCorrectionCore, AcceptsSmallTrackingCorrection)
{
  agt_localization::GlobalCorrectionCore core;
  ASSERT_TRUE(core.evaluate(observation(10.0, pose(5.0, 0.0, 0.0), pose(5.0, 0.0, 0.0))).accepted);

  const auto result = core.evaluate(observation(12.0, pose(5.2, 0.0, 0.05), pose(5.0, 0.0, 0.0)));

  EXPECT_TRUE(result.accepted);
  EXPECT_EQ(result.generation, 2U);
  EXPECT_LT(result.delta_translation_m, 0.5);
  EXPECT_LT(result.delta_yaw_rad, 0.2);
}

TEST(GlobalCorrectionCore, RejectsLargeTrackingJump)
{
  agt_localization::GlobalCorrectionCore core;
  ASSERT_TRUE(core.evaluate(observation(10.0, pose(5.0, 0.0, 0.0), pose(5.0, 0.0, 0.0))).accepted);

  const auto result = core.evaluate(observation(12.0, pose(7.0, 0.0, 0.0), pose(5.0, 0.0, 0.0)));

  EXPECT_FALSE(result.accepted);
  EXPECT_EQ(result.code, "TRANSLATION_JUMP_REJECTED");
  EXPECT_EQ(core.generation(), 1U);
}

TEST(GlobalCorrectionCore, AllowsLostStateReanchor)
{
  agt_localization::GlobalCorrectionCore core;
  ASSERT_TRUE(core.evaluate(observation(10.0, pose(5.0, 0.0, 0.0), pose(5.0, 0.0, 0.0))).accepted);

  const auto result = core.evaluate(observation(
    12.0, pose(12.0, 0.0, 1.0), pose(5.0, 0.0, 0.0),
    agt_localization::CorrectionTrackingState::kLost));

  EXPECT_TRUE(result.accepted);
  EXPECT_TRUE(result.reanchor);
  EXPECT_EQ(result.code, "REANCHOR_ACCEPTED");
  EXPECT_EQ(result.generation, 2U);
}

TEST(GlobalCorrectionCore, RejectsWrongMapIdentity)
{
  agt_localization::GlobalCorrectionCore core;
  core.setExpectedMapIdentity("greenhouse_a", "sha256:map-a");
  auto value = observation(10.0, pose(1.0, 0.0, 0.0), pose(1.0, 0.0, 0.0));
  value.map_hash = "sha256:wrong";

  const auto result = core.evaluate(value);

  EXPECT_FALSE(result.accepted);
  EXPECT_EQ(result.code, "MAP_HASH_MISMATCH");
}

TEST(GlobalCorrectionCore, RejectsStaleAndDuplicateCorrections)
{
  agt_localization::GlobalCorrectionCore core;
  auto stale = observation(10.0, pose(1.0, 0.0, 0.0), pose(1.0, 0.0, 0.0));
  stale.now_s = 12.0;
  EXPECT_EQ(core.evaluate(stale).code, "STALE_CORRECTION");

  ASSERT_TRUE(core.evaluate(observation(20.0, pose(1.0, 0.0, 0.0), pose(1.0, 0.0, 0.0))).accepted);
  const auto duplicate_stamp = core.evaluate(
    observation(20.0, pose(1.2, 0.0, 0.0), pose(1.0, 0.0, 0.0)));
  EXPECT_EQ(duplicate_stamp.code, "DUPLICATE_OR_OLD_CORRECTION");
}

TEST(GlobalCorrectionCore, RejectsBadFitnessAndMeasurementInnovation)
{
  agt_localization::GlobalCorrectionCore core;
  auto bad_fitness = observation(10.0, pose(1.0, 0.0, 0.0), pose(1.0, 0.0, 0.0));
  bad_fitness.fitness_score = 5.0;
  EXPECT_EQ(core.evaluate(bad_fitness).code, "FITNESS_REJECTED");

  auto bad_translation = observation(11.0, pose(1.0, 0.0, 0.0), pose(1.0, 0.0, 0.0));
  bad_translation.measurement_translation_innovation_m = 10.0;
  EXPECT_EQ(core.evaluate(bad_translation).code, "MEASUREMENT_TRANSLATION_REJECTED");
}
