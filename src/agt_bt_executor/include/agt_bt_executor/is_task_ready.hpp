#pragma once

#include <behaviortree_cpp/action_node.h>
#include <agt_interfaces/srv/evaluate_task_readiness.hpp>
#include <rclcpp/rclcpp.hpp>

#include <chrono>

namespace agt_bt_executor {

class IsTaskReady final : public BT::StatefulActionNode
{
public:
  IsTaskReady(
    const std::string &, const BT::NodeConfiguration &, rclcpp::Node::SharedPtr);

  static BT::PortsList providedPorts();
  BT::NodeStatus onStart() override;
  BT::NodeStatus onRunning() override;
  void onHalted() override;

private:
  rclcpp::Node::SharedPtr node_;
  rclcpp::Client<agt_interfaces::srv::EvaluateTaskReadiness>::SharedPtr client_;
  rclcpp::Client<agt_interfaces::srv::EvaluateTaskReadiness>::SharedFuture future_;
  std::chrono::steady_clock::time_point started_{};
};

}  // namespace agt_bt_executor
