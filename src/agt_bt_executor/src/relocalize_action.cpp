#include "agt_bt_executor/relocalize_action.hpp"
namespace agt_bt_executor {
Relocalize::Relocalize(const std::string & name, const BT::NodeConfiguration & config, rclcpp::Node::SharedPtr node)
: RosActionBtNode(name, config, std::move(node), "/agt/localization/relocalize") {}
BT::PortsList Relocalize::providedPorts() {
  auto ports = RosActionBtNode::commonPorts(); ports.insert(BT::InputPort<int>("mode", 0, "Relocalize mode")); ports.insert(BT::InputPort<int>("max_candidates", 0, "candidate limit"));
  ports.insert(BT::InputPort<bool>("use_last_valid_pose", true, "use last valid pose")); ports.insert(BT::InputPort<bool>("use_configured_candidates", true, "use configured candidates")); ports.insert(BT::InputPort<bool>("publish_debug", false, "publish diagnostic output")); ports.insert(BT::OutputPort<std::string>("last_blocker_code")); ports.insert(BT::OutputPort<std::string>("last_blocker_message")); ports.insert(BT::OutputPort<unsigned>("relocalize_error_code")); ports.insert(BT::OutputPort<std::string>("relocalize_failure_reason")); return ports;
}
BT::NodeStatus Relocalize::onStart() {
  // The preceding TaskExecution readiness probe may have written a blocker to
  // this shared blackboard. It is no longer authoritative once relocalization
  // becomes the active failure source.
  setOutput("last_blocker_code", std::string{});
  setOutput("last_blocker_message", std::string{});
  setOutput("relocalize_error_code", 0U);
  setOutput("relocalize_failure_reason", std::string{});
  return RosActionBtNode::onStart();
}
bool Relocalize::makeGoal(Goal & goal) {
  int mode = 0, candidates = 0; getInput("mode", mode); getInput("max_candidates", candidates); goal.mode = static_cast<uint8_t>(mode); goal.max_candidates = static_cast<uint32_t>(candidates);
  getInput("use_last_valid_pose", goal.use_last_valid_pose); getInput("use_configured_candidates", goal.use_configured_candidates); getInput("publish_debug", goal.publish_debug); getInput("timeout_s", goal.timeout_s); return true;
}
bool Relocalize::resultSuccess(const Result & result) { setOutput("relocalize_error_code", static_cast<unsigned>(result.error_code)); setOutput("relocalize_failure_reason", result.failure_reason); RCLCPP_INFO(node_->get_logger(), "Relocalize result success=%s error=%u reason=%s fitness=%.3f", result.success ? "true" : "false", result.error_code, result.failure_reason.c_str(), result.final_status.fitness_score); return result.success; }
void Relocalize::onFeedback(const Feedback & feedback) { RCLCPP_DEBUG(node_->get_logger(), "Relocalize tested=%u/%u fitness=%.3f", feedback.tested_candidates, feedback.total_candidates, feedback.best_fitness_score); }
}
