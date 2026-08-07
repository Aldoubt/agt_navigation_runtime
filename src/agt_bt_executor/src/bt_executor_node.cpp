#include "agt_bt_executor/bt_executor_node.hpp"
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace agt_bt_executor {
BtExecutorNode::BtExecutorNode(rclcpp::Node::SharedPtr node) : node_(std::move(node)) {
  node_->declare_parameter("tick_rate_hz", 20.0);
  node_->declare_parameter("relocalize_timeout_s", 15.0);
  node_->declare_parameter("relocalize_max_candidates", 20);
  node_->declare_parameter("waypoint_timeout_s", 3600.0);
  if (node_->get_parameter("tick_rate_hz").as_double() <= 0.0 ||
    node_->get_parameter("relocalize_timeout_s").as_double() <= 0.0 ||
    node_->get_parameter("relocalize_max_candidates").as_int() <= 0 ||
    node_->get_parameter("waypoint_timeout_s").as_double() <= 0.0)
  {
    throw std::invalid_argument("BT executor timeout and rate parameters must be positive");
  }
}
BtExecutorNode::~BtExecutorNode() { cancel_requested_ = true; if (worker_.joinable()) worker_.join(); }
void BtExecutorNode::start() {
  server_ = rclcpp_action::create_server<Action>(node_, "/agt/internal/bt/execute",
    std::bind(&BtExecutorNode::onGoal, this, std::placeholders::_1, std::placeholders::_2),
    std::bind(&BtExecutorNode::onCancel, this, std::placeholders::_1),
    std::bind(&BtExecutorNode::onAccepted, this, std::placeholders::_1));
}
rclcpp_action::GoalResponse BtExecutorNode::onGoal(const rclcpp_action::GoalUUID &, std::shared_ptr<const Action::Goal> goal) {
  if (!goal || (goal->tree_id != "v25_06_waypoint_mission" && goal->tree_id != "v25_05_smoke")) return rclcpp_action::GoalResponse::REJECT;
  if (goal->tree_id == "v25_06_waypoint_mission") {
    const auto valid_component = [](const std::string & value) {
        if (value.empty() || value.size() > 128U) return false;
        for (const auto ch : value) {
          if (!(std::isalnum(static_cast<unsigned char>(ch)) || ch == '.' || ch == '_' || ch == '-')) return false;
        }
        return true;
    };
    const auto valid_hash = [](const std::string & value) {
        if (value.size() != 71U || value.rfind("sha256:", 0) != 0) return false;
        return std::all_of(value.begin() + 7, value.end(), [](const char ch) {
          return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f');
        });
    };
    if (!valid_component(goal->execution_id) || !valid_component(goal->map_id) ||
      !valid_component(goal->map_version_id) || !valid_component(goal->task_group_id) ||
      !valid_component(goal->client_request_id) || goal->task_revision == 0U ||
      goal->loop_count == 0U || goal->loop_count > 10000U || !valid_hash(goal->expected_content_sha256))
    {
      RCLCPP_WARN(node_->get_logger(), "Rejecting invalid v25_06_waypoint_mission goal");
      return rclcpp_action::GoalResponse::REJECT;
    }
  }
  std::lock_guard<std::mutex> lock(mutex_);
  return active_ ? rclcpp_action::GoalResponse::REJECT : rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}
rclcpp_action::CancelResponse BtExecutorNode::onCancel(const std::shared_ptr<GoalHandle> goal) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (active_goal_ == goal) cancel_requested_ = true;
  return rclcpp_action::CancelResponse::ACCEPT;
}
void BtExecutorNode::onAccepted(const std::shared_ptr<GoalHandle> goal) {
  std::lock_guard<std::mutex> lock(mutex_);
  active_ = true; active_goal_ = goal; cancel_requested_ = false;
  if (worker_.joinable()) worker_.join();
  worker_ = std::thread(&BtExecutorNode::run, this, goal);
}
void BtExecutorNode::run(std::shared_ptr<GoalHandle> goal) {
  auto result = std::make_shared<Action::Result>();
  try {
    BT::BehaviorTreeFactory factory; registerAgtBtNodes(factory, node_);
    auto tree = createAllowlistedTree(factory, goal->get_goal()->tree_id);
    auto bb = tree.rootBlackboard();
    const auto & g = *goal->get_goal();
    bb->set("map_id", g.map_id); bb->set("map_version_id", g.map_version_id);
    bb->set("task_group_id", g.task_group_id); bb->set("task_revision", g.task_revision);
    bb->set("task_content_sha256", g.expected_content_sha256); bb->set("loop_count", g.loop_count);
    bb->set("client_request_id", g.client_request_id);
    bb->set("relocalize_timeout_s", node_->get_parameter("relocalize_timeout_s").as_double());
    bb->set("relocalize_max_candidates", static_cast<unsigned>(node_->get_parameter("relocalize_max_candidates").as_int()));
    bb->set("waypoint_timeout_s", node_->get_parameter("waypoint_timeout_s").as_double());
    const auto period = std::chrono::duration<double>(1.0 / node_->get_parameter("tick_rate_hz").as_double());
    auto status = BT::NodeStatus::IDLE;
    while (rclcpp::ok() && (status == BT::NodeStatus::IDLE || status == BT::NodeStatus::RUNNING)) {
      if (cancel_requested_ || goal->is_canceling()) { tree.haltTree(); result->success = false; result->error_code = Action::Goal::ERROR_CANCELED; result->message = "behavior tree canceled"; goal->canceled(result); std::lock_guard<std::mutex> lock(mutex_); active_ = false; active_goal_.reset(); return; }
      status = tree.tickOnce();
      auto feedback = std::make_shared<Action::Feedback>();
      feedback->tree_state = status == BT::NodeStatus::RUNNING ? "RUNNING" : (status == BT::NodeStatus::SUCCESS ? "SUCCESS" : "FAILURE");
      feedback->active_node = tree.rootNode()->name();
      (void)bb->get("loop_index", feedback->loop_index); (void)bb->get("current_waypoint", feedback->current_waypoint); (void)bb->get("total_waypoints", feedback->total_waypoints);
      goal->publish_feedback(feedback);
      if (status != BT::NodeStatus::RUNNING) break;
      std::this_thread::sleep_for(period);
    }
    result->success = status == BT::NodeStatus::SUCCESS;
    (void)bb->get("last_blocker_code", result->blocker_code);
    (void)bb->get("last_blocker_message", result->blocker_message);
    std::string relocalize_failure_reason;
    if (!result->success && bb->get("relocalize_failure_reason", relocalize_failure_reason) && !relocalize_failure_reason.empty()) {
      result->message = "relocalize failed: " + relocalize_failure_reason;
    }
    result->error_code = result->success ? Action::Goal::ERROR_NONE : Action::Goal::ERROR_TREE_FAILED;
    if (result->success) result->message = "behavior tree succeeded";
    else if (result->message.empty()) result->message = "behavior tree failed";
    if (result->success) goal->succeed(result); else goal->abort(result);
  } catch (const std::exception & e) {
    result->success = false; result->error_code = Action::Goal::ERROR_INTERNAL; result->message = e.what(); goal->abort(result);
  }
done:
  std::lock_guard<std::mutex> lock(mutex_); active_ = false; active_goal_.reset();
}
}

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("agt_bt_executor");
  agt_bt_executor::BtExecutorNode server(node); server.start(); rclcpp::spin(node); rclcpp::shutdown(); return 0;
}
