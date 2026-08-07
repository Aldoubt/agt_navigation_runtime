#pragma once
#include "ros_action_node.hpp"
#include <agt_interfaces/action/relocalize.hpp>
namespace agt_bt_executor {
class Relocalize final : public RosActionBtNode<agt_interfaces::action::Relocalize> {
public:
  Relocalize(const std::string &, const BT::NodeConfiguration &, rclcpp::Node::SharedPtr);
  static BT::PortsList providedPorts();
protected:
  bool makeGoal(Goal & goal) override; bool resultSuccess(const Result &) override;
  void onFeedback(const Feedback &) override;
};
}
