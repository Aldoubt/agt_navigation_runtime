#include <gtest/gtest.h>

#include <agt_interfaces/action/relocalize.hpp>
#include <agt_interfaces/msg/localization_status.hpp>

TEST(LocalizationStatusInterface, ConstantsAndFieldsAreUsable)
{
  agt_interfaces::msg::LocalizationStatus status;
  status.state = agt_interfaces::msg::LocalizationStatus::STATE_SEARCHING;
  status.error_code = agt_interfaces::msg::LocalizationStatus::ERROR_NONE;
  status.pose_valid = false;
  status.status_stale = false;
  status.message = "searching";

  EXPECT_EQ(status.state, 1U);
  EXPECT_EQ(status.error_code, 0U);
  EXPECT_FALSE(status.pose_valid);
  EXPECT_EQ(status.message, "searching");
}

TEST(RelocalizeInterface, GeneratedGoalFeedbackAndResultAreUsable)
{
  agt_interfaces::action::Relocalize::Goal goal;
  goal.mode = agt_interfaces::action::Relocalize::Goal::MODE_AUTO_SEARCH;
  goal.max_candidates = 8U;
  goal.timeout_s = 10.0;

  agt_interfaces::action::Relocalize::Feedback feedback;
  feedback.state = agt_interfaces::msg::LocalizationStatus::STATE_VERIFYING;
  feedback.tested_candidates = 2U;

  agt_interfaces::action::Relocalize::Result result;
  result.success = true;
  result.error_code = agt_interfaces::msg::LocalizationStatus::ERROR_NONE;
  result.final_status.state = agt_interfaces::msg::LocalizationStatus::STATE_TRACKING;

  EXPECT_EQ(goal.mode, 0U);
  EXPECT_EQ(goal.max_candidates, 8U);
  EXPECT_DOUBLE_EQ(goal.timeout_s, 10.0);
  EXPECT_EQ(feedback.state, 2U);
  EXPECT_EQ(feedback.tested_candidates, 2U);
  EXPECT_TRUE(result.success);
  EXPECT_EQ(result.final_status.state, 3U);
}
