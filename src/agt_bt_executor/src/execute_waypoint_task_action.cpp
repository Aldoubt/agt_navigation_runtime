#include "agt_bt_executor/execute_waypoint_task_action.hpp"
namespace agt_bt_executor {
ExecuteWaypointTask::ExecuteWaypointTask(const std::string & name, const BT::NodeConfiguration & config, rclcpp::Node::SharedPtr node)
: RosActionBtNode(name, config, std::move(node), "/agt/navigation/execute_waypoint_task") {}
BT::PortsList ExecuteWaypointTask::providedPorts() {
  auto ports = RosActionBtNode::commonPorts(); ports.insert(BT::InputPort<std::string>("map_id")); ports.insert(BT::InputPort<std::string>("map_version_id")); ports.insert(BT::InputPort<std::string>("task_group_id")); ports.insert(BT::InputPort<unsigned>("task_revision")); ports.insert(BT::InputPort<std::string>("expected_content_sha256")); ports.insert(BT::InputPort<unsigned>("loop_count", 1U, "finite task loop count")); ports.insert(BT::InputPort<std::string>("client_request_id")); return ports;
}
bool ExecuteWaypointTask::makeGoal(Goal & goal) { getInput("map_id", goal.map_id); getInput("map_version_id", goal.map_version_id); getInput("task_group_id", goal.task_group_id); getInput("task_revision", goal.task_revision); getInput("expected_content_sha256", goal.expected_content_sha256); getInput("loop_count", goal.loop_count); getInput("client_request_id", goal.client_request_id); return true; }
bool ExecuteWaypointTask::resultSuccess(const Result & result) const { RCLCPP_INFO(node_->get_logger(), "ExecuteWaypointTask success=%s error=%u message=%s", result.success ? "true" : "false", result.error_code, result.message.c_str()); return result.success; }
void ExecuteWaypointTask::onFeedback(const Feedback & feedback) { RCLCPP_DEBUG(node_->get_logger(), "Waypoint state=%s loop=%u waypoint=%u/%u", feedback.state.c_str(), feedback.loop_index, feedback.current_waypoint, feedback.total_waypoints); }
}
