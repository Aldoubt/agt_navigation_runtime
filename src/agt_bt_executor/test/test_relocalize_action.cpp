#include <gtest/gtest.h>
#include <agt_interfaces/action/relocalize.hpp>
#include <behaviortree_cpp/blackboard.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <thread>
#include "agt_bt_executor/relocalize_action.hpp"

TEST(RelocalizeBtAction, FakeServerReceivesGoalAndReturnsResult) {
  using Action = agt_interfaces::action::Relocalize;
  rclcpp::init(0, nullptr); auto node = std::make_shared<rclcpp::Node>("relocalize_bt_test");
  Action::Goal received; bool canceled = false;
  auto server = rclcpp_action::create_server<Action>(node, "/agt/localization/relocalize",
    [&received](const rclcpp_action::GoalUUID &, std::shared_ptr<const Action::Goal> goal) { received = *goal; return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE; },
    [&canceled](std::shared_ptr<rclcpp_action::ServerGoalHandle<Action>>) { canceled = true; return rclcpp_action::CancelResponse::ACCEPT; },
    [](std::shared_ptr<rclcpp_action::ServerGoalHandle<Action>> handle) { std::thread([handle]() { std::this_thread::sleep_for(std::chrono::milliseconds(500)); auto result = std::make_shared<Action::Result>(); result->success = true; handle->succeed(result); }).detach(); });
  rclcpp::executors::SingleThreadedExecutor executor; executor.add_node(node);
  BT::NodeConfiguration config; config.input_ports["mode"] = "0"; config.input_ports["max_candidates"] = "4"; config.input_ports["timeout_s"] = "2.0";
  agt_bt_executor::Relocalize action("relocalize", config, node);
  ASSERT_EQ(action.executeTick(), BT::NodeStatus::RUNNING);
  BT::NodeStatus status = BT::NodeStatus::RUNNING;
  for (int i = 0; i < 300; ++i) { executor.spin_some(); status = action.executeTick(); if (status != BT::NodeStatus::RUNNING) break; std::this_thread::sleep_for(std::chrono::milliseconds(10)); }
  EXPECT_EQ(status, BT::NodeStatus::SUCCESS); EXPECT_EQ(received.mode, 0U); EXPECT_EQ(received.max_candidates, 4U); EXPECT_FALSE(canceled);
  rclcpp::shutdown();
}
