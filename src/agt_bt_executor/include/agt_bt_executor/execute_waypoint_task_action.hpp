#pragma once
#include "ros_action_node.hpp"
#include <agt_interfaces/action/execute_waypoint_task.hpp>
namespace agt_bt_executor {
class ExecuteWaypointTask final : public RosActionBtNode<agt_interfaces::action::ExecuteWaypointTask> {
public:
  ExecuteWaypointTask(const std::string &, const BT::NodeConfiguration &, rclcpp::Node::SharedPtr);
  static BT::PortsList providedPorts();
protected:
  bool makeGoal(Goal & goal) override; bool resultSuccess(const Result &) const override;
  void onFeedback(const Feedback &) override;
};
}
