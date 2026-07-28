#include <gtest/gtest.h>

#include "agt_interfaces/action/change_system_mode.hpp"
#include "agt_interfaces/action/manage_mapping_session.hpp"
#include "agt_interfaces/action/execute_mission.hpp"
#include "agt_interfaces/action/optimize_map.hpp"
#include "agt_interfaces/msg/system_health.hpp"
#include "agt_interfaces/msg/experiment_summary.hpp"
#include "agt_interfaces/msg/robot_state.hpp"
#include "agt_interfaces/msg/mission_status.hpp"
#include "agt_interfaces/msg/map_version_summary.hpp"
#include "agt_interfaces/msg/task_readiness.hpp"
#include "agt_interfaces/srv/set_localization_mode.hpp"
#include "agt_interfaces/srv/manage_map_version.hpp"
#include "agt_interfaces/srv/manage_bag_session.hpp"
#include "agt_interfaces/srv/list_experiments.hpp"

TEST(SystemInterfaces, DefaultsAndConstantsAreGenerated)
{
  agt_interfaces::action::ChangeSystemMode::Goal goal;
  goal.argument_keys = {"map"};
  goal.argument_values = {"map.yaml"};
  EXPECT_EQ(goal.argument_keys.size(), 1U);
  EXPECT_EQ(agt_interfaces::action::ChangeSystemMode::Goal::MODE_NAVIGATION, 4U);
  agt_interfaces::action::ManageMappingSession::Goal mapping_goal;
  mapping_goal.operation =
    agt_interfaces::action::ManageMappingSession::Goal::OP_START;
  mapping_goal.map_id = "greenhouse_01";
  EXPECT_EQ(
    agt_interfaces::action::ManageMappingSession::Goal::OP_FINALIZE_CAPTURE,
    2U);
  EXPECT_EQ(
    agt_interfaces::action::ManageMappingSession::Result::ERROR_GRID_SAVE_FAILED,
    4U);
  EXPECT_EQ(mapping_goal.map_id, "greenhouse_01");
  EXPECT_EQ(agt_interfaces::msg::SystemHealth::STATE_UNKNOWN, 0U);
  EXPECT_FALSE(agt_interfaces::msg::TaskReadiness().ready);
  EXPECT_EQ(agt_interfaces::srv::SetLocalizationMode::Request::MODE_MANUAL_ONLY, 0U);
  EXPECT_TRUE(agt_interfaces::action::OptimizeMap::Goal().backend.empty());
  EXPECT_TRUE(agt_interfaces::action::ExecuteMission::Goal().mission_id.empty());
  EXPECT_EQ(agt_interfaces::msg::RobotState::MODE_UNKNOWN, 0U);
  EXPECT_FALSE(agt_interfaces::msg::RobotState().mission_status_known);
  EXPECT_FALSE(agt_interfaces::msg::RobotState().active_map_known);
  EXPECT_EQ(agt_interfaces::msg::MissionStatus::STATE_INTERRUPTED, 12U);
  EXPECT_EQ(agt_interfaces::msg::MissionStatus::STEP_WAYPOINT_TASK, 1U);
  EXPECT_EQ(agt_interfaces::msg::MissionStatus::STEP_WAIT_EVENT, 3U);
  EXPECT_EQ(agt_interfaces::msg::MapVersionSummary::STATE_READY, 3U);
  EXPECT_EQ(agt_interfaces::srv::ManageMapVersion::Request::OP_PURGE, 7U);
  EXPECT_EQ(
    agt_interfaces::srv::ManageMapVersion::Request::OP_IMPORT_CANDIDATE,
    8U);
  EXPECT_TRUE(
    agt_interfaces::srv::ManageMapVersion::Request().candidate_map_yaml.empty());
  EXPECT_EQ(
    agt_interfaces::srv::ManageMapVersion::Response::ERROR_CONFIRMATION_REQUIRED,
    5U);
  EXPECT_EQ(
    agt_interfaces::srv::ManageBagSession::Request::OP_INTERRUPT_EXPERIMENT,
    7U);
  EXPECT_EQ(
    agt_interfaces::srv::ManageBagSession::Response::ERROR_PROFILE_INVALID,
    4U);
  EXPECT_TRUE(
    agt_interfaces::srv::ManageBagSession::Request().experiment_title.empty());
  EXPECT_TRUE(
    agt_interfaces::srv::ManageBagSession::Request().tags_json.empty());
  EXPECT_EQ(
    agt_interfaces::srv::ManageBagSession::Request::OP_ADD_EXPERIMENT_EVENT,
    10U);
  EXPECT_EQ(agt_interfaces::msg::ExperimentSummary::STATE_INTERRUPTED, 4U);
  EXPECT_TRUE(agt_interfaces::srv::ListExperiments::Response().experiments.empty());
}
