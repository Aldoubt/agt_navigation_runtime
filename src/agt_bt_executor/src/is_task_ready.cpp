#include "agt_bt_executor/is_task_ready.hpp"
namespace agt_bt_executor {
IsTaskReady::IsTaskReady(const std::string & name, const BT::NodeConfiguration & config, rclcpp::Node::SharedPtr node)
: ConditionNode(name, config), node_(std::move(node)) {}
BT::PortsList IsTaskReady::providedPorts() {
  return {BT::InputPort<std::string>("task_id", "", "optional project task identity"), BT::InputPort<double>("timeout_s", 3.0, "service timeout in seconds"),
          BT::OutputPort<std::string>("last_blocker_code"), BT::OutputPort<std::string>("last_blocker_message")};
}
BT::NodeStatus IsTaskReady::tick() {
  if (!future_.valid()) {
    client_ = node_->create_client<agt_interfaces::srv::EvaluateTaskReadiness>("/agt/system/evaluate_task_readiness");
    if (!client_->wait_for_service(std::chrono::milliseconds(1))) return BT::NodeStatus::FAILURE;
    auto request = std::make_shared<agt_interfaces::srv::EvaluateTaskReadiness::Request>();
    getInput("task_id", request->task_id); request->validate_task = true;
    future_ = client_->async_send_request(request).future.share(); started_ = node_->now(); return BT::NodeStatus::RUNNING;
  }
  if (future_.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
    double timeout = 3.0; getInput("timeout_s", timeout);
    return (node_->now() - started_).seconds() > timeout ? BT::NodeStatus::FAILURE : BT::NodeStatus::RUNNING;
  }
  auto response = future_.get(); future_ = {};
  if (!response->readiness.ready) {
    const auto & codes = response->readiness.blocker_codes; const auto & messages = response->readiness.blocker_messages;
    if (!codes.empty()) setOutput("last_blocker_code", codes.front());
    if (!messages.empty()) setOutput("last_blocker_message", messages.front());
    RCLCPP_WARN(node_->get_logger(), "Task readiness blocked: %s", messages.empty() ? "unspecified" : messages.front().c_str());
    return BT::NodeStatus::FAILURE;
  }
  return BT::NodeStatus::SUCCESS;
}
}
