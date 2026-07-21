#include <gtest/gtest.h>

#include "agt_localization/quality_validator.hpp"

TEST(QualityValidatorTest, AcceptsConvergedRegistrationWithinBounds)
{
  agt_localization::QualityObservation observation;
  observation.backend_success = true;
  observation.has_converged = true;
  observation.fitness_score = 0.4;
  observation.scan_points = 500;
  observation.estimated_x = 1.0;
  observation.initial_x = 0.5;
  observation.runtime_ms = 10.0;

  agt_localization::QualityConfig config;
  config.max_translation_innovation = 1.0;
  const auto decision = agt_localization::validateQuality(observation, config);
  EXPECT_TRUE(decision.accepted);
  EXPECT_EQ(decision.error_code, agt_localization::kQualityErrorNone);
  EXPECT_NEAR(decision.translation_innovation, 0.5, 1.0e-9);
}

TEST(QualityValidatorTest, RejectsFitnessAndSmallScan)
{
  agt_localization::QualityObservation observation;
  observation.backend_success = true;
  observation.has_converged = true;
  observation.fitness_score = 3.0;
  observation.scan_points = 500;
  agt_localization::QualityConfig config;
  config.max_fitness_score = 2.0;
  auto decision = agt_localization::validateQuality(observation, config);
  EXPECT_FALSE(decision.accepted);
  EXPECT_EQ(decision.error_code, agt_localization::kQualityErrorFitnessRejected);

  observation.fitness_score = 0.1;
  observation.scan_points = 10;
  decision = agt_localization::validateQuality(observation, config);
  EXPECT_FALSE(decision.accepted);
  EXPECT_EQ(decision.error_code, agt_localization::kQualityErrorScanTooSmall);
}

TEST(QualityValidatorTest, RejectsMissingRequiredMetricsAndInnovation)
{
  agt_localization::QualityObservation observation;
  observation.backend_success = true;
  observation.has_converged = true;
  observation.fitness_score = 0.1;
  observation.scan_points = 500;
  observation.estimated_x = 4.0;
  observation.runtime_ms = 3.0;
  agt_localization::QualityConfig config;
  config.max_translation_innovation = 1.0;
  auto decision = agt_localization::validateQuality(observation, config);
  EXPECT_FALSE(decision.accepted);
  EXPECT_EQ(decision.error_code, agt_localization::kQualityErrorInvalidInitialGuess);

  observation.estimated_x = 0.0;
  config.require_geometry_metrics = true;
  decision = agt_localization::validateQuality(observation, config);
  EXPECT_FALSE(decision.accepted);
  EXPECT_EQ(decision.error_code, agt_localization::kQualityErrorBackendFailed);
}

TEST(QualityValidatorTest, DetectsNearTieAsAmbiguous)
{
  EXPECT_TRUE(agt_localization::isAmbiguousScore(1.0, 1.05, 0.1));
  EXPECT_FALSE(agt_localization::isAmbiguousScore(1.0, 1.5, 0.1));
  EXPECT_TRUE(agt_localization::isAmbiguousScore(0.0, 0.0000005, 0.1));
  EXPECT_FALSE(agt_localization::isAmbiguousScore(0.0, 0.01, 0.1));
}
