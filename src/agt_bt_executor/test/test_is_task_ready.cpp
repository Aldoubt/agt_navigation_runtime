#include <gtest/gtest.h>
#include <agt_interfaces/srv/evaluate_task_readiness.hpp>
#include <behaviortree_cpp/blackboard.h>
#include <rclcpp/rclcpp.hpp>
#include <thread>
#include "agt_bt_executor/is_task_ready.hpp"

TEST(IsTaskReady, FakeServiceReadyAndBlockedAcrossRepeatedExecutions) {
  rclcpp::init(0, nullptr);
  auto node = std::make_shared<rclcpp::Node>("is_task_ready_test");
  bool ready = true;
  using Service = agt_interfaces::srv::EvaluateTaskReadiness;
  auto service = node->create_service<agt_interfaces::srv::EvaluateTaskReadiness>(
    "/agt/system/evaluate_task_readiness",
    [&ready](std::shared_ptr<Service::Request>, std::shared_ptr<Service::Response> response) {
      response->readiness.ready = ready;
      response->readiness.blocker_codes = {"LOCALIZATION_LOST"};
      response->readiness.blocker_messages = {"localization is not accepted"};
    });
  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(node);
  BT::NodeConfiguration config;
  config.input_ports["timeout_s"] = "1.0";
  agt_bt_executor::IsTaskReady condition("ready", config, node);

  ASSERT_EQ(condition.executeTick(), BT::NodeStatus::RUNNING);
  BT::NodeStatus status = BT::NodeStatus::RUNNING;
  for (int i = 0; i < 20; ++i) {
    executor.spin_some();
    status = condition.executeTick();
    if (status != BT::NodeStatus::RUNNING) break;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  EXPECT_EQ(status, BT::NodeStatus::SUCCESS);

  ready = false;
  EXPECT_EQ(condition.executeTick(), BT::NodeStatus::RUNNING);
  for (int i = 0; i < 20; ++i) {
    executor.spin_some();
    status = condition.executeTick();
    if (status != BT::NodeStatus::RUNNING) break;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  EXPECT_EQ(status, BT::NodeStatus::FAILURE);
  rclcpp::shutdown();
}
