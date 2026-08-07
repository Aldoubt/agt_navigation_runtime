#pragma once

#include <behaviortree_cpp/action_node.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <chrono>
#include <memory>
#include <mutex>

namespace agt_bt_executor {

template<class ActionT>
class RosActionBtNode : public BT::StatefulActionNode
{
public:
  using Goal = typename ActionT::Goal;
  using Result = typename ActionT::Result;
  using Feedback = typename ActionT::Feedback;
  using Client = rclcpp_action::Client<ActionT>;
  using GoalHandle = rclcpp_action::ClientGoalHandle<ActionT>;
  using WrappedResult = typename GoalHandle::WrappedResult;
  RosActionBtNode(const std::string & name, const BT::NodeConfiguration & config,
                  rclcpp::Node::SharedPtr node, std::string action_name)
  : StatefulActionNode(name, config), node_(std::move(node)), action_name_(std::move(action_name)) {}

  static BT::PortsList commonPorts() { return {BT::InputPort<double>("timeout_s", 10.0, "bounded action timeout in seconds")}; }
  BT::NodeStatus onStart() override {
    client_ = rclcpp_action::create_client<ActionT>(node_, action_name_);
    if (!client_->wait_for_action_server(std::chrono::milliseconds(1))) {
      RCLCPP_ERROR(node_->get_logger(), "%s action server unavailable: %s", name().c_str(), action_name_.c_str());
      return BT::NodeStatus::FAILURE;
    }
    auto goal = std::make_shared<typename ActionT::Goal>();
    if (!makeGoal(*goal)) return BT::NodeStatus::FAILURE;
    typename Client::SendGoalOptions options;
    options.feedback_callback = [this](std::shared_ptr<GoalHandle>,
      const std::shared_ptr<const Feedback> feedback) { onFeedback(*feedback); };
    options.goal_response_callback = [this](std::shared_ptr<GoalHandle> handle) {
      if (cancel_requested_ && handle) {
        RCLCPP_WARN(node_->get_logger(), "%s accepted a goal after halt; canceling it", name().c_str());
        requestCancel(handle, false);
      }
    };
    options.result_callback = [this](const WrappedResult & wrapped) {
      std::lock_guard<std::mutex> lock(result_mutex_);
      result_ = wrapped;
      result_ready_ = true;
    };
    send_future_ = client_->async_send_goal(*goal, options);
    started_ = node_->now();
    return BT::NodeStatus::RUNNING;
  }
  BT::NodeStatus onRunning() override {
    if (send_future_.valid() && send_future_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
      goal_handle_ = send_future_.get();
      if (!goal_handle_) { RCLCPP_ERROR(node_->get_logger(), "%s goal rejected", name().c_str()); return BT::NodeStatus::FAILURE; }
    }
    {
      std::lock_guard<std::mutex> lock(result_mutex_);
      if (result_ready_) return resultSuccess(*result_.result) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    }
    double timeout = 10.0; getInput("timeout_s", timeout);
    if ((node_->now() - started_).seconds() > timeout) {
      RCLCPP_ERROR(node_->get_logger(), "%s timed out", name().c_str());
      cancelActive(); return BT::NodeStatus::FAILURE;
    }
    return BT::NodeStatus::RUNNING;
  }
  void onHalted() override { cancelActive(); }

protected:
  virtual bool makeGoal(typename ActionT::Goal &) = 0;
  virtual bool resultSuccess(const typename ActionT::Result &) const = 0;
  virtual void onFeedback(const typename ActionT::Feedback &) {}
  void cancelActive() {
    cancel_requested_ = true;
    if (!goal_handle_ && send_future_.valid() &&
      send_future_.wait_for(std::chrono::milliseconds(250)) == std::future_status::ready) {
      goal_handle_ = send_future_.get();
    }
    if (goal_handle_) requestCancel(goal_handle_, true);
  }
  void requestCancel(const typename GoalHandle::SharedPtr & handle, bool wait_for_confirmation) {
    auto future = client_->async_cancel_goal(handle);
    if (wait_for_confirmation && future.wait_for(std::chrono::milliseconds(250)) != std::future_status::ready)
      RCLCPP_ERROR(node_->get_logger(), "%s cancel confirmation timed out", name().c_str());
    if (goal_handle_ == handle) {
      goal_handle_.reset();
    }
  }
  rclcpp::Node::SharedPtr node_;
  std::string action_name_;
  typename Client::SharedPtr client_;
  std::shared_future<typename GoalHandle::SharedPtr> send_future_;
  typename GoalHandle::SharedPtr goal_handle_;
  rclcpp::Time started_;
  bool cancel_requested_{false};
  WrappedResult result_;
  bool result_ready_{false};
  std::mutex result_mutex_;
};
}
