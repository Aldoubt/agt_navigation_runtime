// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/MissionStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/mission_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_MissionStatus_message
{
public:
  explicit Init_MissionStatus_message(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::MissionStatus message(::agt_interfaces::msg::MissionStatus::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_blocker_messages
{
public:
  explicit Init_MissionStatus_blocker_messages(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_message blocker_messages(::agt_interfaces::msg::MissionStatus::_blocker_messages_type arg)
  {
    msg_.blocker_messages = std::move(arg);
    return Init_MissionStatus_message(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_blocker_codes
{
public:
  explicit Init_MissionStatus_blocker_codes(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_blocker_messages blocker_codes(::agt_interfaces::msg::MissionStatus::_blocker_codes_type arg)
  {
    msg_.blocker_codes = std::move(arg);
    return Init_MissionStatus_blocker_messages(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_error_code
{
public:
  explicit Init_MissionStatus_error_code(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_blocker_codes error_code(::agt_interfaces::msg::MissionStatus::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_MissionStatus_blocker_codes(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_step_remaining_s
{
public:
  explicit Init_MissionStatus_step_remaining_s(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_error_code step_remaining_s(::agt_interfaces::msg::MissionStatus::_step_remaining_s_type arg)
  {
    msg_.step_remaining_s = std::move(arg);
    return Init_MissionStatus_error_code(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_step_elapsed_s
{
public:
  explicit Init_MissionStatus_step_elapsed_s(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_step_remaining_s step_elapsed_s(::agt_interfaces::msg::MissionStatus::_step_elapsed_s_type arg)
  {
    msg_.step_elapsed_s = std::move(arg);
    return Init_MissionStatus_step_remaining_s(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_total_waypoints
{
public:
  explicit Init_MissionStatus_total_waypoints(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_step_elapsed_s total_waypoints(::agt_interfaces::msg::MissionStatus::_total_waypoints_type arg)
  {
    msg_.total_waypoints = std::move(arg);
    return Init_MissionStatus_step_elapsed_s(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_current_waypoint
{
public:
  explicit Init_MissionStatus_current_waypoint(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_total_waypoints current_waypoint(::agt_interfaces::msg::MissionStatus::_current_waypoint_type arg)
  {
    msg_.current_waypoint = std::move(arg);
    return Init_MissionStatus_total_waypoints(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_current_step_type
{
public:
  explicit Init_MissionStatus_current_step_type(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_current_waypoint current_step_type(::agt_interfaces::msg::MissionStatus::_current_step_type_type arg)
  {
    msg_.current_step_type = std::move(arg);
    return Init_MissionStatus_current_waypoint(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_current_step_id
{
public:
  explicit Init_MissionStatus_current_step_id(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_current_step_type current_step_id(::agt_interfaces::msg::MissionStatus::_current_step_id_type arg)
  {
    msg_.current_step_id = std::move(arg);
    return Init_MissionStatus_current_step_type(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_total_steps
{
public:
  explicit Init_MissionStatus_total_steps(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_current_step_id total_steps(::agt_interfaces::msg::MissionStatus::_total_steps_type arg)
  {
    msg_.total_steps = std::move(arg);
    return Init_MissionStatus_current_step_id(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_current_step_index
{
public:
  explicit Init_MissionStatus_current_step_index(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_total_steps current_step_index(::agt_interfaces::msg::MissionStatus::_current_step_index_type arg)
  {
    msg_.current_step_index = std::move(arg);
    return Init_MissionStatus_total_steps(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_map_manifest_sha256
{
public:
  explicit Init_MissionStatus_map_manifest_sha256(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_current_step_index map_manifest_sha256(::agt_interfaces::msg::MissionStatus::_map_manifest_sha256_type arg)
  {
    msg_.map_manifest_sha256 = std::move(arg);
    return Init_MissionStatus_current_step_index(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_map_version_id
{
public:
  explicit Init_MissionStatus_map_version_id(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_map_manifest_sha256 map_version_id(::agt_interfaces::msg::MissionStatus::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_MissionStatus_map_manifest_sha256(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_map_id
{
public:
  explicit Init_MissionStatus_map_id(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_map_version_id map_id(::agt_interfaces::msg::MissionStatus::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_MissionStatus_map_version_id(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_content_sha256
{
public:
  explicit Init_MissionStatus_content_sha256(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_map_id content_sha256(::agt_interfaces::msg::MissionStatus::_content_sha256_type arg)
  {
    msg_.content_sha256 = std::move(arg);
    return Init_MissionStatus_map_id(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_mission_version
{
public:
  explicit Init_MissionStatus_mission_version(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_content_sha256 mission_version(::agt_interfaces::msg::MissionStatus::_mission_version_type arg)
  {
    msg_.mission_version = std::move(arg);
    return Init_MissionStatus_content_sha256(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_mission_id
{
public:
  explicit Init_MissionStatus_mission_id(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_mission_version mission_id(::agt_interfaces::msg::MissionStatus::_mission_id_type arg)
  {
    msg_.mission_id = std::move(arg);
    return Init_MissionStatus_mission_version(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_state
{
public:
  explicit Init_MissionStatus_state(::agt_interfaces::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_mission_id state(::agt_interfaces::msg::MissionStatus::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_MissionStatus_mission_id(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

class Init_MissionStatus_header
{
public:
  Init_MissionStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MissionStatus_state header(::agt_interfaces::msg::MissionStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MissionStatus_state(msg_);
  }

private:
  ::agt_interfaces::msg::MissionStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::MissionStatus>()
{
  return agt_interfaces::msg::builder::Init_MissionStatus_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__BUILDER_HPP_
