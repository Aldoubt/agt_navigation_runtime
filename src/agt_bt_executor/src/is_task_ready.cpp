#include "agt_bt_executor/is_task_ready.hpp"

namespace agt_bt_executor {

IsTaskReady::IsTaskReady(
  const std::string & name, const BT::NodeConfiguration & config,
  rclcpp::Node::SharedPtr node)
: StatefulActionNode(name, config), node_(std::move(node)) {}

BT::PortsList IsTaskReady::providedPorts()
{
  return {
    BT::InputPort<std::string>("task_id", "", "optional project task identity"),
    BT::InputPort<std::string>("gate_profile", "task_execution", "system-manager readiness profile"),
    BT::InputPort<double>("timeout_s", 3.0, "service timeout in seconds"),
    BT::OutputPort<std::string>("last_blocker_code"),
    BT::OutputPort<std::string>("last_blocker_message")};
}

BT::NodeStatus IsTaskReady::executeTick()
{
  // Readiness is a repeatable query capability. A later tree execution must
  // not reuse a terminal result from an earlier execution.
  if (status() != BT::NodeStatus::IDLE && status() != BT::NodeStatus::RUNNING) {
    resetStatus();
  }
  return StatefulActionNode::executeTick();
}

BT::NodeStatus IsTaskReady::onStart()
{
  future_ = {};
  client_ = node_->create_client<agt_interfaces::srv::EvaluateTaskReadiness>(
    "/agt/system/evaluate_task_readiness");
  if (!client_->wait_for_service(std::chrono::milliseconds(50))) {
    RCLCPP_ERROR(node_->get_logger(), "Task readiness service unavailable");
    return BT::NodeStatus::FAILURE;
  }

  auto request = std::make_shared<agt_interfaces::srv::EvaluateTaskReadiness::Request>();
  getInput("task_id", request->task_id);
  request->validate_task = true;
  std::string profile = "task_execution";
  getInput("gate_profile", profile);
  request->gate_profile = profile == "relocalization" ?
    agt_interfaces::srv::EvaluateTaskReadiness::Request::PROFILE_RELOCALIZATION :
    agt_interfaces::srv::EvaluateTaskReadiness::Request::PROFILE_TASK_EXECUTION;
  future_ = client_->async_send_request(request).future.share();
  started_ = std::chrono::steady_clock::now();
  return BT::NodeStatus::RUNNING;
}

BT::NodeStatus IsTaskReady::onRunning()
{
  if (!future_.valid()) {
    return BT::NodeStatus::FAILURE;
  }

  if (future_.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
    double timeout = 3.0;
    getInput("timeout_s", timeout);
    if (std::chrono::duration<double>(std::chrono::steady_clock::now() - started_).count() > timeout) {
      RCLCPP_ERROR(node_->get_logger(), "Task readiness service timed out");
      future_ = {};
      return BT::NodeStatus::FAILURE;
    }
    return BT::NodeStatus::RUNNING;
  }

  auto response = future_.get();
  future_ = {};
  if (!response || !response->readiness.ready) {
    if (response) {
      const auto & codes = response->readiness.blocker_codes;
      const auto & messages = response->readiness.blocker_messages;
      setOutput("last_blocker_code", codes.empty() ? std::string{} : codes.front());
      setOutput("last_blocker_message", messages.empty() ? std::string{} : messages.front());
      RCLCPP_WARN(
        node_->get_logger(), "Task readiness blocked: %s",
        messages.empty() ? "unspecified" : messages.front().c_str());
    }
    return BT::NodeStatus::FAILURE;
  }

  setOutput("last_blocker_code", std::string{});
  setOutput("last_blocker_message", std::string{});
  return BT::NodeStatus::SUCCESS;
}

void IsTaskReady::onHalted()
{
  // EvaluateTaskReadiness is read-only. The ROS service request itself cannot be
  // canceled, but dropping the future guarantees a late reply cannot affect a
  // later BT execution of this node.
  future_ = {};
}

}  // namespace agt_bt_executor
