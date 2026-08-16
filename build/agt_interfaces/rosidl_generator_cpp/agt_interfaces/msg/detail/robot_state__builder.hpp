// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/RobotState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/robot_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_RobotState_message
{
public:
  explicit Init_RobotState_message(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::RobotState message(::agt_interfaces::msg::RobotState::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_blocker_messages
{
public:
  explicit Init_RobotState_blocker_messages(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_message blocker_messages(::agt_interfaces::msg::RobotState::_blocker_messages_type arg)
  {
    msg_.blocker_messages = std::move(arg);
    return Init_RobotState_message(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_blocker_codes
{
public:
  explicit Init_RobotState_blocker_codes(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_blocker_messages blocker_codes(::agt_interfaces::msg::RobotState::_blocker_codes_type arg)
  {
    msg_.blocker_codes = std::move(arg);
    return Init_RobotState_blocker_messages(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_error_code
{
public:
  explicit Init_RobotState_error_code(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_blocker_codes error_code(::agt_interfaces::msg::RobotState::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_RobotState_blocker_codes(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_bag_session
{
public:
  explicit Init_RobotState_bag_session(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_error_code bag_session(::agt_interfaces::msg::RobotState::_bag_session_type arg)
  {
    msg_.bag_session = std::move(arg);
    return Init_RobotState_error_code(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_bag_freshness_s
{
public:
  explicit Init_RobotState_bag_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_bag_session bag_freshness_s(::agt_interfaces::msg::RobotState::_bag_freshness_s_type arg)
  {
    msg_.bag_freshness_s = std::move(arg);
    return Init_RobotState_bag_session(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_bag_status_known
{
public:
  explicit Init_RobotState_bag_status_known(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_bag_freshness_s bag_status_known(::agt_interfaces::msg::RobotState::_bag_status_known_type arg)
  {
    msg_.bag_status_known = std::move(arg);
    return Init_RobotState_bag_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_chassis_odometry_freshness_s
{
public:
  explicit Init_RobotState_chassis_odometry_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_bag_status_known chassis_odometry_freshness_s(::agt_interfaces::msg::RobotState::_chassis_odometry_freshness_s_type arg)
  {
    msg_.chassis_odometry_freshness_s = std::move(arg);
    return Init_RobotState_bag_status_known(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_chassis_status_freshness_s
{
public:
  explicit Init_RobotState_chassis_status_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_chassis_odometry_freshness_s chassis_status_freshness_s(::agt_interfaces::msg::RobotState::_chassis_status_freshness_s_type arg)
  {
    msg_.chassis_status_freshness_s = std::move(arg);
    return Init_RobotState_chassis_odometry_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_chassis_control_mode
{
public:
  explicit Init_RobotState_chassis_control_mode(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_chassis_status_freshness_s chassis_control_mode(::agt_interfaces::msg::RobotState::_chassis_control_mode_type arg)
  {
    msg_.chassis_control_mode = std::move(arg);
    return Init_RobotState_chassis_status_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_chassis_connected
{
public:
  explicit Init_RobotState_chassis_connected(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_chassis_control_mode chassis_connected(::agt_interfaces::msg::RobotState::_chassis_connected_type arg)
  {
    msg_.chassis_connected = std::move(arg);
    return Init_RobotState_chassis_control_mode(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_chassis_status_known
{
public:
  explicit Init_RobotState_chassis_status_known(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_chassis_connected chassis_status_known(::agt_interfaces::msg::RobotState::_chassis_status_known_type arg)
  {
    msg_.chassis_status_known = std::move(arg);
    return Init_RobotState_chassis_connected(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_safety_freshness_s
{
public:
  explicit Init_RobotState_safety_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_chassis_status_known safety_freshness_s(::agt_interfaces::msg::RobotState::_safety_freshness_s_type arg)
  {
    msg_.safety_freshness_s = std::move(arg);
    return Init_RobotState_chassis_status_known(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_navigation_ready
{
public:
  explicit Init_RobotState_navigation_ready(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_safety_freshness_s navigation_ready(::agt_interfaces::msg::RobotState::_navigation_ready_type arg)
  {
    msg_.navigation_ready = std::move(arg);
    return Init_RobotState_safety_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_estop_latched
{
public:
  explicit Init_RobotState_estop_latched(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_navigation_ready estop_latched(::agt_interfaces::msg::RobotState::_estop_latched_type arg)
  {
    msg_.estop_latched = std::move(arg);
    return Init_RobotState_navigation_ready(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_emergency_stop
{
public:
  explicit Init_RobotState_emergency_stop(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_estop_latched emergency_stop(::agt_interfaces::msg::RobotState::_emergency_stop_type arg)
  {
    msg_.emergency_stop = std::move(arg);
    return Init_RobotState_estop_latched(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_safety_motion_enabled
{
public:
  explicit Init_RobotState_safety_motion_enabled(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_emergency_stop safety_motion_enabled(::agt_interfaces::msg::RobotState::_safety_motion_enabled_type arg)
  {
    msg_.safety_motion_enabled = std::move(arg);
    return Init_RobotState_emergency_stop(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_safety_status_known
{
public:
  explicit Init_RobotState_safety_status_known(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_safety_motion_enabled safety_status_known(::agt_interfaces::msg::RobotState::_safety_status_known_type arg)
  {
    msg_.safety_status_known = std::move(arg);
    return Init_RobotState_safety_motion_enabled(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_nav2_freshness_s
{
public:
  explicit Init_RobotState_nav2_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_safety_status_known nav2_freshness_s(::agt_interfaces::msg::RobotState::_nav2_freshness_s_type arg)
  {
    msg_.nav2_freshness_s = std::move(arg);
    return Init_RobotState_safety_status_known(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_nav2_state
{
public:
  explicit Init_RobotState_nav2_state(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_nav2_freshness_s nav2_state(::agt_interfaces::msg::RobotState::_nav2_state_type arg)
  {
    msg_.nav2_state = std::move(arg);
    return Init_RobotState_nav2_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_mission
{
public:
  explicit Init_RobotState_mission(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_nav2_state mission(::agt_interfaces::msg::RobotState::_mission_type arg)
  {
    msg_.mission = std::move(arg);
    return Init_RobotState_nav2_state(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_mission_freshness_s
{
public:
  explicit Init_RobotState_mission_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_mission mission_freshness_s(::agt_interfaces::msg::RobotState::_mission_freshness_s_type arg)
  {
    msg_.mission_freshness_s = std::move(arg);
    return Init_RobotState_mission(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_mission_status_known
{
public:
  explicit Init_RobotState_mission_status_known(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_mission_freshness_s mission_status_known(::agt_interfaces::msg::RobotState::_mission_status_known_type arg)
  {
    msg_.mission_status_known = std::move(arg);
    return Init_RobotState_mission_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_localization
{
public:
  explicit Init_RobotState_localization(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_mission_status_known localization(::agt_interfaces::msg::RobotState::_localization_type arg)
  {
    msg_.localization = std::move(arg);
    return Init_RobotState_mission_status_known(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_localization_freshness_s
{
public:
  explicit Init_RobotState_localization_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_localization localization_freshness_s(::agt_interfaces::msg::RobotState::_localization_freshness_s_type arg)
  {
    msg_.localization_freshness_s = std::move(arg);
    return Init_RobotState_localization(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_localization_status_known
{
public:
  explicit Init_RobotState_localization_status_known(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_localization_freshness_s localization_status_known(::agt_interfaces::msg::RobotState::_localization_status_known_type arg)
  {
    msg_.localization_status_known = std::move(arg);
    return Init_RobotState_localization_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_active_map
{
public:
  explicit Init_RobotState_active_map(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_localization_status_known active_map(::agt_interfaces::msg::RobotState::_active_map_type arg)
  {
    msg_.active_map = std::move(arg);
    return Init_RobotState_localization_status_known(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_active_map_freshness_s
{
public:
  explicit Init_RobotState_active_map_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_active_map active_map_freshness_s(::agt_interfaces::msg::RobotState::_active_map_freshness_s_type arg)
  {
    msg_.active_map_freshness_s = std::move(arg);
    return Init_RobotState_active_map(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_active_map_known
{
public:
  explicit Init_RobotState_active_map_known(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_active_map_freshness_s active_map_known(::agt_interfaces::msg::RobotState::_active_map_known_type arg)
  {
    msg_.active_map_known = std::move(arg);
    return Init_RobotState_active_map_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_task_readiness
{
public:
  explicit Init_RobotState_task_readiness(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_active_map_known task_readiness(::agt_interfaces::msg::RobotState::_task_readiness_type arg)
  {
    msg_.task_readiness = std::move(arg);
    return Init_RobotState_active_map_known(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_task_readiness_freshness_s
{
public:
  explicit Init_RobotState_task_readiness_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_task_readiness task_readiness_freshness_s(::agt_interfaces::msg::RobotState::_task_readiness_freshness_s_type arg)
  {
    msg_.task_readiness_freshness_s = std::move(arg);
    return Init_RobotState_task_readiness(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_task_readiness_known
{
public:
  explicit Init_RobotState_task_readiness_known(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_task_readiness_freshness_s task_readiness_known(::agt_interfaces::msg::RobotState::_task_readiness_known_type arg)
  {
    msg_.task_readiness_known = std::move(arg);
    return Init_RobotState_task_readiness_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_system_health
{
public:
  explicit Init_RobotState_system_health(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_task_readiness_known system_health(::agt_interfaces::msg::RobotState::_system_health_type arg)
  {
    msg_.system_health = std::move(arg);
    return Init_RobotState_task_readiness_known(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_system_health_freshness_s
{
public:
  explicit Init_RobotState_system_health_freshness_s(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_system_health system_health_freshness_s(::agt_interfaces::msg::RobotState::_system_health_freshness_s_type arg)
  {
    msg_.system_health_freshness_s = std::move(arg);
    return Init_RobotState_system_health(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_system_health_known
{
public:
  explicit Init_RobotState_system_health_known(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_system_health_freshness_s system_health_known(::agt_interfaces::msg::RobotState::_system_health_known_type arg)
  {
    msg_.system_health_known = std::move(arg);
    return Init_RobotState_system_health_freshness_s(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_running_process_count
{
public:
  explicit Init_RobotState_running_process_count(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_system_health_known running_process_count(::agt_interfaces::msg::RobotState::_running_process_count_type arg)
  {
    msg_.running_process_count = std::move(arg);
    return Init_RobotState_system_health_known(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_managed_process_count
{
public:
  explicit Init_RobotState_managed_process_count(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_running_process_count managed_process_count(::agt_interfaces::msg::RobotState::_managed_process_count_type arg)
  {
    msg_.managed_process_count = std::move(arg);
    return Init_RobotState_running_process_count(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_active_profile
{
public:
  explicit Init_RobotState_active_profile(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_managed_process_count active_profile(::agt_interfaces::msg::RobotState::_active_profile_type arg)
  {
    msg_.active_profile = std::move(arg);
    return Init_RobotState_managed_process_count(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_system_mode
{
public:
  explicit Init_RobotState_system_mode(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_active_profile system_mode(::agt_interfaces::msg::RobotState::_system_mode_type arg)
  {
    msg_.system_mode = std::move(arg);
    return Init_RobotState_active_profile(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_revision
{
public:
  explicit Init_RobotState_revision(::agt_interfaces::msg::RobotState & msg)
  : msg_(msg)
  {}
  Init_RobotState_system_mode revision(::agt_interfaces::msg::RobotState::_revision_type arg)
  {
    msg_.revision = std::move(arg);
    return Init_RobotState_system_mode(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

class Init_RobotState_header
{
public:
  Init_RobotState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotState_revision header(::agt_interfaces::msg::RobotState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RobotState_revision(msg_);
  }

private:
  ::agt_interfaces::msg::RobotState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::RobotState>()
{
  return agt_interfaces::msg::builder::Init_RobotState_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__BUILDER_HPP_
