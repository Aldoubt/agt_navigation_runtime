#pragma once
#include <behaviortree_cpp/condition_node.h>
#include <agt_interfaces/srv/evaluate_task_readiness.hpp>
#include <rclcpp/rclcpp.hpp>
namespace agt_bt_executor {
class IsTaskReady final : public BT::ConditionNode {
public:
  IsTaskReady(const std::string &, const BT::NodeConfiguration &, rclcpp::Node::SharedPtr);
  static BT::PortsList providedPorts();
  BT::NodeStatus tick() override;
private: rclcpp::Node::SharedPtr node_; rclcpp::Client<agt_interfaces::srv::EvaluateTaskReadiness>::SharedPtr client_;
  rclcpp::Client<agt_interfaces::srv::EvaluateTaskReadiness>::SharedFuture future_;
  rclcpp::Time started_;
};
}
