#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include <agt_interfaces/action/relocalize.hpp>
#include <agt_interfaces/msg/localization_status.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include "agt_localization/recovery_trigger_policy.hpp"

class RecoveryTriggerManager : public rclcpp::Node
{
public:
  using Relocalize = agt_interfaces::action::Relocalize;
  using GoalHandleRelocalize = rclcpp_action::ClientGoalHandle<Relocalize>;
  using LocalizationStatus = agt_interfaces::msg::LocalizationStatus;

  RecoveryTriggerManager()
  : Node("recovery_trigger_manager")
  {
    enabled_ = declare_parameter<bool>("enabled", true);
    action_name_ = declare_parameter<std::string>(
      "relocalize_action_name", "/agt/localization/relocalize");
    max_candidates_ = declare_parameter<int>("max_candidates", 64);
    request_timeout_s_ = declare_parameter<double>("request_timeout_s", 15.0);
    use_last_valid_pose_ = declare_parameter<bool>("use_last_valid_pose", true);
    use_configured_candidates_ = declare_parameter<bool>("use_configured_candidates", true);
    use_external_coarse_pose_ = declare_parameter<bool>("use_external_coarse_pose", true);

    agt_localization::RecoveryTriggerConfig config;
    config.cooldown_s = declare_parameter<double>("cooldown_s", 5.0);
    config.trigger_recovering = declare_parameter<bool>("trigger_recovering", true);
    config.trigger_lost = declare_parameter<bool>("trigger_lost", true);
    if (max_candidates_ <= 0 || request_timeout_s_ <= 0.0 || config.cooldown_s < 0.0) {
      throw std::runtime_error("recovery trigger limits must be valid");
    }

    policy_ = std::make_unique<agt_localization::RecoveryTriggerPolicy>(
      LocalizationStatus::STATE_TRACKING,
      LocalizationStatus::STATE_RECOVERING,
      LocalizationStatus::STATE_LOST,
      config);
    client_ = rclcpp_action::create_client<Relocalize>(this, action_name_);
    status_sub_ = create_subscription<LocalizationStatus>(
      "/agt/localization/status", 10,
      std::bind(&RecoveryTriggerManager::statusCallback, this, std::placeholders::_1));

    RCLCPP_INFO(
      get_logger(),
      "Recovery trigger manager ready. enabled=%s action=%s",
      enabled_ ? "true" : "false", action_name_.c_str());
  }

private:
  void statusCallback(const LocalizationStatus::SharedPtr status)
  {
    if (!enabled_ || !status || !policy_) {
      return;
    }
    agt_localization::RecoveryTriggerInput input;
    input.localization_state = status->state;
    input.now_s = now().seconds();
    input.request_in_flight = request_in_flight_.load();
    const auto decision = policy_->evaluate(input);
    if (!decision.trigger) {
      return;
    }
    if (!client_->wait_for_action_server(std::chrono::seconds(0))) {
      RCLCPP_WARN_THROTTLE(
        get_logger(), *get_clock(), 3000,
        "Recovery trigger skipped because Relocalize action server is unavailable");
      return;
    }

    Relocalize::Goal goal;
    goal.mode = decision.mode == agt_localization::RecoveryTriggerMode::kAutoSearch ?
      Relocalize::Goal::MODE_AUTO_SEARCH : Relocalize::Goal::MODE_LOCAL_CANDIDATES;
    goal.use_initial_pose = false;
    goal.use_last_valid_pose = use_last_valid_pose_;
    goal.use_configured_candidates = use_configured_candidates_;
    goal.use_external_coarse_pose = use_external_coarse_pose_;
    goal.max_candidates = static_cast<std::uint32_t>(max_candidates_);
    goal.publish_debug = false;
    goal.timeout_s = request_timeout_s_;

    request_in_flight_.store(true);
    auto options = rclcpp_action::Client<Relocalize>::SendGoalOptions();
    options.goal_response_callback =
      [this](const GoalHandleRelocalize::SharedPtr & handle) {
        if (!handle) {
          request_in_flight_.store(false);
          RCLCPP_WARN(get_logger(), "Automatic relocalization request was rejected");
        }
      };
    options.result_callback =
      [this](const GoalHandleRelocalize::WrappedResult & result) {
        request_in_flight_.store(false);
        if (policy_) {
          policy_->noteRequestFinished();
        }
        if (result.code == rclcpp_action::ResultCode::SUCCEEDED &&
          result.result && result.result->success)
        {
          RCLCPP_INFO(get_logger(), "Automatic relocalization request succeeded");
        } else {
          const std::string reason =
            result.result ? result.result->failure_reason : "no action result";
          RCLCPP_WARN(
            get_logger(), "Automatic relocalization request finished without acceptance: %s",
            reason.c_str());
        }
      };
    client_->async_send_goal(goal, options);

    RCLCPP_WARN(
      get_logger(), "Triggered automatic relocalization mode=%u reason=%s",
      static_cast<unsigned int>(goal.mode), decision.reason.c_str());
  }

  bool enabled_{true};
  std::string action_name_;
  int max_candidates_{64};
  double request_timeout_s_{15.0};
  bool use_last_valid_pose_{true};
  bool use_configured_candidates_{true};
  bool use_external_coarse_pose_{true};
  std::atomic<bool> request_in_flight_{false};

  std::unique_ptr<agt_localization::RecoveryTriggerPolicy> policy_;
  rclcpp_action::Client<Relocalize>::SharedPtr client_;
  rclcpp::Subscription<LocalizationStatus>::SharedPtr status_sub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  int result = 0;
  try {
    rclcpp::spin(std::make_shared<RecoveryTriggerManager>());
  } catch (const std::exception & error) {
    RCLCPP_FATAL(
      rclcpp::get_logger("recovery_trigger_manager"),
      "Failed to start recovery trigger manager: %s", error.what());
    result = 1;
  }
  rclcpp::shutdown();
  return result;
}
