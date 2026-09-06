#include "camera_gimbal_manager/gimbal_state_estimator.hpp"

#include <gtest/gtest.h>

using camera_gimbal_manager::Angles;
using camera_gimbal_manager::GimbalStateEstimator;

TEST(GimbalStateEstimator, MedianFilterRejectsPeriodicJump)
{
  GimbalStateEstimator estimator(5, 1, 1.5, 0.0);
  const auto start = GimbalStateEstimator::Clock::now();
  for (double value : {-10.2, -10.1, -7.7, -10.2, -10.1}) {
    estimator.update({value, 0.0, 0.0}, {value, 0.0, 0.0}, start);
  }
  EXPECT_NEAR(estimator.filtered().heading, -10.1, 1e-9);
}

TEST(GimbalStateEstimator, C1PitchJumpDoesNotBecomeFilteredOutput)
{
  GimbalStateEstimator estimator(5, 1, 1.5, 0.0);
  const auto now = GimbalStateEstimator::Clock::now();
  estimator.update({0.0, 0.0, -10.2}, {0.0, 0.0, -10.2}, now);
  estimator.update({0.0, 0.0, -7.7}, {0.0, 0.0, -7.7}, now);
  estimator.update({0.0, 0.0, -10.2}, {0.0, 0.0, -10.2}, now);
  EXPECT_NEAR(estimator.filtered().pitch, -10.2, 1e-6);
  EXPECT_LT(std::abs(estimator.filtered().pitch - (-10.2)), 0.1);
}

TEST(GimbalStateEstimator, StableWindowPasses)
{
  GimbalStateEstimator estimator(1, 4, 1.5, 0.5);
  const auto start = GimbalStateEstimator::Clock::now();
  for (std::size_t i = 0; i < 4; ++i) {
    estimator.update({10.0 + (i == 1 ? 0.1 : i == 2 ? -0.1 : 0.0), 0.0, 0.0},
      {10.0, 0.0, 0.0}, start + std::chrono::milliseconds(static_cast<int>(i) * 200));
  }
  EXPECT_TRUE(estimator.stable());
}

TEST(GimbalStateEstimator, JumpFailsStableWindow)
{
  GimbalStateEstimator estimator(1, 4, 1.5, 0.5);
  const auto start = GimbalStateEstimator::Clock::now();
  for (std::size_t i = 0; i < 4; ++i) {
    const double value = (i % 2 == 0) ? 10.0 : (i == 1 ? 7.5 : 7.6);
    estimator.update({value, 0.0, 0.0}, {10.0, 0.0, 0.0}, start + std::chrono::milliseconds(static_cast<int>(i) * 200));
  }
  EXPECT_FALSE(estimator.stable());
}
