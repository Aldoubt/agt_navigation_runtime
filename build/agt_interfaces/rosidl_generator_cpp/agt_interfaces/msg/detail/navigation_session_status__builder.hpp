// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/NavigationSessionStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/navigation_session_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_NavigationSessionStatus_success
{
public:
  explicit Init_NavigationSessionStatus_success(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::NavigationSessionStatus success(::agt_interfaces::msg::NavigationSessionStatus::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_terminal
{
public:
  explicit Init_NavigationSessionStatus_terminal(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_success terminal(::agt_interfaces::msg::NavigationSessionStatus::_terminal_type arg)
  {
    msg_.terminal = std::move(arg);
    return Init_NavigationSessionStatus_success(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_updated_at
{
public:
  explicit Init_NavigationSessionStatus_updated_at(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_terminal updated_at(::agt_interfaces::msg::NavigationSessionStatus::_updated_at_type arg)
  {
    msg_.updated_at = std::move(arg);
    return Init_NavigationSessionStatus_terminal(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_started_at
{
public:
  explicit Init_NavigationSessionStatus_started_at(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_updated_at started_at(::agt_interfaces::msg::NavigationSessionStatus::_started_at_type arg)
  {
    msg_.started_at = std::move(arg);
    return Init_NavigationSessionStatus_updated_at(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_technical_message
{
public:
  explicit Init_NavigationSessionStatus_technical_message(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_started_at technical_message(::agt_interfaces::msg::NavigationSessionStatus::_technical_message_type arg)
  {
    msg_.technical_message = std::move(arg);
    return Init_NavigationSessionStatus_started_at(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_operator_message
{
public:
  explicit Init_NavigationSessionStatus_operator_message(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_technical_message operator_message(::agt_interfaces::msg::NavigationSessionStatus::_operator_message_type arg)
  {
    msg_.operator_message = std::move(arg);
    return Init_NavigationSessionStatus_technical_message(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_blocker_code
{
public:
  explicit Init_NavigationSessionStatus_blocker_code(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_operator_message blocker_code(::agt_interfaces::msg::NavigationSessionStatus::_blocker_code_type arg)
  {
    msg_.blocker_code = std::move(arg);
    return Init_NavigationSessionStatus_operator_message(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_error_code
{
public:
  explicit Init_NavigationSessionStatus_error_code(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_blocker_code error_code(::agt_interfaces::msg::NavigationSessionStatus::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_NavigationSessionStatus_blocker_code(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_missed_waypoints
{
public:
  explicit Init_NavigationSessionStatus_missed_waypoints(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_error_code missed_waypoints(::agt_interfaces::msg::NavigationSessionStatus::_missed_waypoints_type arg)
  {
    msg_.missed_waypoints = std::move(arg);
    return Init_NavigationSessionStatus_error_code(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_total_waypoints
{
public:
  explicit Init_NavigationSessionStatus_total_waypoints(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_missed_waypoints total_waypoints(::agt_interfaces::msg::NavigationSessionStatus::_total_waypoints_type arg)
  {
    msg_.total_waypoints = std::move(arg);
    return Init_NavigationSessionStatus_missed_waypoints(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_current_waypoint
{
public:
  explicit Init_NavigationSessionStatus_current_waypoint(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_total_waypoints current_waypoint(::agt_interfaces::msg::NavigationSessionStatus::_current_waypoint_type arg)
  {
    msg_.current_waypoint = std::move(arg);
    return Init_NavigationSessionStatus_total_waypoints(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_loop_index
{
public:
  explicit Init_NavigationSessionStatus_loop_index(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_current_waypoint loop_index(::agt_interfaces::msg::NavigationSessionStatus::_loop_index_type arg)
  {
    msg_.loop_index = std::move(arg);
    return Init_NavigationSessionStatus_current_waypoint(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_state
{
public:
  explicit Init_NavigationSessionStatus_state(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_loop_index state(::agt_interfaces::msg::NavigationSessionStatus::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_NavigationSessionStatus_loop_index(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_task_content_sha256
{
public:
  explicit Init_NavigationSessionStatus_task_content_sha256(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_state task_content_sha256(::agt_interfaces::msg::NavigationSessionStatus::_task_content_sha256_type arg)
  {
    msg_.task_content_sha256 = std::move(arg);
    return Init_NavigationSessionStatus_state(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_task_revision
{
public:
  explicit Init_NavigationSessionStatus_task_revision(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_task_content_sha256 task_revision(::agt_interfaces::msg::NavigationSessionStatus::_task_revision_type arg)
  {
    msg_.task_revision = std::move(arg);
    return Init_NavigationSessionStatus_task_content_sha256(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_task_group_id
{
public:
  explicit Init_NavigationSessionStatus_task_group_id(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_task_revision task_group_id(::agt_interfaces::msg::NavigationSessionStatus::_task_group_id_type arg)
  {
    msg_.task_group_id = std::move(arg);
    return Init_NavigationSessionStatus_task_revision(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_map_version_id
{
public:
  explicit Init_NavigationSessionStatus_map_version_id(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_task_group_id map_version_id(::agt_interfaces::msg::NavigationSessionStatus::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_NavigationSessionStatus_task_group_id(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_map_id
{
public:
  explicit Init_NavigationSessionStatus_map_id(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_map_version_id map_id(::agt_interfaces::msg::NavigationSessionStatus::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_NavigationSessionStatus_map_version_id(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_client_request_id
{
public:
  explicit Init_NavigationSessionStatus_client_request_id(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_map_id client_request_id(::agt_interfaces::msg::NavigationSessionStatus::_client_request_id_type arg)
  {
    msg_.client_request_id = std::move(arg);
    return Init_NavigationSessionStatus_map_id(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_session_id
{
public:
  explicit Init_NavigationSessionStatus_session_id(::agt_interfaces::msg::NavigationSessionStatus & msg)
  : msg_(msg)
  {}
  Init_NavigationSessionStatus_client_request_id session_id(::agt_interfaces::msg::NavigationSessionStatus::_session_id_type arg)
  {
    msg_.session_id = std::move(arg);
    return Init_NavigationSessionStatus_client_request_id(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

class Init_NavigationSessionStatus_header
{
public:
  Init_NavigationSessionStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavigationSessionStatus_session_id header(::agt_interfaces::msg::NavigationSessionStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_NavigationSessionStatus_session_id(msg_);
  }

private:
  ::agt_interfaces::msg::NavigationSessionStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::NavigationSessionStatus>()
{
  return agt_interfaces::msg::builder::Init_NavigationSessionStatus_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__BUILDER_HPP_
