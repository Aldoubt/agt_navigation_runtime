#pragma once

#include "bt_factory.hpp"
#include <agt_interfaces/action/execute_behavior_tree.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <atomic>
#include <mutex>
#include <thread>

namespace agt_bt_executor {
class BtExecutorNode {
public:
  explicit BtExecutorNode(rclcpp::Node::SharedPtr node);
  ~BtExecutorNode();
  void start();
private:
  using Action = agt_interfaces::action::ExecuteBehaviorTree;
  using GoalHandle = rclcpp_action::ServerGoalHandle<Action>;
  rclcpp::Node::SharedPtr node_;
  rclcpp_action::Server<Action>::SharedPtr server_;
  std::thread worker_;
  std::mutex mutex_;
  bool active_{false};
  std::shared_ptr<GoalHandle> active_goal_;
  std::atomic_bool cancel_requested_{false};
  rclcpp_action::GoalResponse onGoal(const rclcpp_action::GoalUUID &, std::shared_ptr<const Action::Goal>);
  rclcpp_action::CancelResponse onCancel(const std::shared_ptr<GoalHandle>);
  void onAccepted(const std::shared_ptr<GoalHandle>);
  void run(std::shared_ptr<GoalHandle>);
};
}
