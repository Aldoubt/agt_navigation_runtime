#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "agt_interfaces/action/execute_coverage_task.hpp"
#include "agt_interfaces/action/execute_waypoint_task.hpp"

TEST(ExecuteCoverageTaskInterface, GeneratedTypesAreUsable)
{
  agt_interfaces::action::ExecuteCoverageTask::Goal goal;
  goal.semantic_map_uri = "semantic_map.geojson";
  goal.field_id = "field_001";
  goal.planning_mode = "polygon";
  goal.controller_id = "FollowPath";
  goal.allow_repair = true;

  agt_interfaces::action::ExecuteCoverageTask::Result result;
  result.success = true;
  result.error_code = 0U;
  result.repaired_segment_count = 1U;

  agt_interfaces::action::ExecuteCoverageTask::Feedback feedback;
  feedback.current_stage = "READY";
  feedback.current_swath_index = 0U;
  feedback.total_swaths = 8U;

  EXPECT_EQ(goal.field_id, std::string("field_001"));
  EXPECT_TRUE(goal.allow_repair);
  EXPECT_TRUE(result.success);
  EXPECT_EQ(result.error_code, static_cast<std::uint16_t>(0U));
  EXPECT_EQ(result.repaired_segment_count, static_cast<std::uint32_t>(1U));
  EXPECT_EQ(feedback.current_stage, std::string("READY"));
  EXPECT_EQ(feedback.total_swaths, static_cast<std::uint32_t>(8U));
}

TEST(ExecuteWaypointTaskInterface, GeneratedTypesAreUsable)
{
  agt_interfaces::action::ExecuteWaypointTask::Goal goal;
  goal.map_id = "demo";
  goal.map_version_id = "map_20260729_120000_abcdef12";
  goal.task_group_id = "inspection_v01";
  goal.task_revision = 3U;
  goal.expected_content_sha256 = std::string("sha256:") + std::string(64U, 'a');
  goal.client_request_id = "11111111-1111-4111-8111-111111111111";
  goal.poses.resize(0U);
  goal.loop = false;
  goal.loop_count = 1U;

  agt_interfaces::action::ExecuteWaypointTask::Result result;
  result.success = false;
  result.error_code = 42U;
  result.session_id = "session-1";
  result.blocker_code = "NAV2_FAILED";
  result.missed_waypoints = {1, 3};

  agt_interfaces::action::ExecuteWaypointTask::Feedback feedback;
  feedback.state = "RUNNING";
  feedback.current_waypoint = 1U;
  feedback.total_waypoints = 4U;

  EXPECT_EQ(goal.loop_count, static_cast<std::uint32_t>(1U));
  EXPECT_EQ(goal.task_group_id, std::string("inspection_v01"));
  EXPECT_EQ(result.error_code, static_cast<std::uint16_t>(42U));
  EXPECT_EQ(result.blocker_code, std::string("NAV2_FAILED"));
  EXPECT_EQ(result.missed_waypoints.size(), 2U);
  EXPECT_EQ(feedback.state, std::string("RUNNING"));
}
