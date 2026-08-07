#include <gtest/gtest.h>
#include <agt_interfaces/action/execute_waypoint_task.hpp>
#include <behaviortree_cpp/blackboard.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <thread>
#include "agt_bt_executor/execute_waypoint_task_action.hpp"

TEST(ExecuteWaypointTaskBtAction, FakeServerReceivesTypedGoal) {
  using Action = agt_interfaces::action::ExecuteWaypointTask;
  rclcpp::init(0, nullptr); auto node = std::make_shared<rclcpp::Node>("waypoint_bt_test"); Action::Goal received;
  auto server = rclcpp_action::create_server<Action>(node, "/agt/navigation/execute_waypoint_task",
    [&received](const rclcpp_action::GoalUUID &, std::shared_ptr<const Action::Goal> goal) { received = *goal; return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE; },
    [](std::shared_ptr<rclcpp_action::ServerGoalHandle<Action>>) { return rclcpp_action::CancelResponse::ACCEPT; },
    [](std::shared_ptr<rclcpp_action::ServerGoalHandle<Action>> handle) { std::thread([handle]() { std::this_thread::sleep_for(std::chrono::milliseconds(500)); auto result = std::make_shared<Action::Result>(); result->success = true; handle->succeed(result); }).detach(); });
  rclcpp::executors::SingleThreadedExecutor executor; executor.add_node(node);
  BT::NodeConfiguration config; config.input_ports["map_id"] = "map"; config.input_ports["map_version_id"] = "v1"; config.input_ports["task_group_id"] = "rows"; config.input_ports["task_revision"] = "7"; config.input_ports["expected_content_sha256"] = "sha256:abc"; config.input_ports["loop_count"] = "2"; config.input_ports["client_request_id"] = "req-1"; config.input_ports["timeout_s"] = "2.0";
  agt_bt_executor::ExecuteWaypointTask action("waypoint", config, node); ASSERT_EQ(action.executeTick(), BT::NodeStatus::RUNNING);
  BT::NodeStatus status = BT::NodeStatus::RUNNING;
  for (int i = 0; i < 300; ++i) { executor.spin_some(); status = action.executeTick(); if (status != BT::NodeStatus::RUNNING) break; std::this_thread::sleep_for(std::chrono::milliseconds(10)); }
  EXPECT_EQ(status, BT::NodeStatus::SUCCESS); EXPECT_EQ(received.map_id, "map"); EXPECT_EQ(received.task_revision, 7U); EXPECT_EQ(received.loop_count, 2U); EXPECT_TRUE(received.task_file.empty()); EXPECT_TRUE(received.poses.empty());
  rclcpp::shutdown();
}
