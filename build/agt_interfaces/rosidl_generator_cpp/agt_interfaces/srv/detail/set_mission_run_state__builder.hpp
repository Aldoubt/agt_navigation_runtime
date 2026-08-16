// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/SetMissionRunState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__SET_MISSION_RUN_STATE__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__SET_MISSION_RUN_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/set_mission_run_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetMissionRunState_Request_mission_id
{
public:
  explicit Init_SetMissionRunState_Request_mission_id(::agt_interfaces::srv::SetMissionRunState_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::SetMissionRunState_Request mission_id(::agt_interfaces::srv::SetMissionRunState_Request::_mission_id_type arg)
  {
    msg_.mission_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::SetMissionRunState_Request msg_;
};

class Init_SetMissionRunState_Request_command
{
public:
  Init_SetMissionRunState_Request_command()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMissionRunState_Request_mission_id command(::agt_interfaces::srv::SetMissionRunState_Request::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_SetMissionRunState_Request_mission_id(msg_);
  }

private:
  ::agt_interfaces::srv::SetMissionRunState_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::SetMissionRunState_Request>()
{
  return agt_interfaces::srv::builder::Init_SetMissionRunState_Request_command();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetMissionRunState_Response_message
{
public:
  explicit Init_SetMissionRunState_Response_message(::agt_interfaces::srv::SetMissionRunState_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::SetMissionRunState_Response message(::agt_interfaces::srv::SetMissionRunState_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::SetMissionRunState_Response msg_;
};

class Init_SetMissionRunState_Response_status
{
public:
  explicit Init_SetMissionRunState_Response_status(::agt_interfaces::srv::SetMissionRunState_Response & msg)
  : msg_(msg)
  {}
  Init_SetMissionRunState_Response_message status(::agt_interfaces::srv::SetMissionRunState_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_SetMissionRunState_Response_message(msg_);
  }

private:
  ::agt_interfaces::srv::SetMissionRunState_Response msg_;
};

class Init_SetMissionRunState_Response_error_code
{
public:
  explicit Init_SetMissionRunState_Response_error_code(::agt_interfaces::srv::SetMissionRunState_Response & msg)
  : msg_(msg)
  {}
  Init_SetMissionRunState_Response_status error_code(::agt_interfaces::srv::SetMissionRunState_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_SetMissionRunState_Response_status(msg_);
  }

private:
  ::agt_interfaces::srv::SetMissionRunState_Response msg_;
};

class Init_SetMissionRunState_Response_success
{
public:
  Init_SetMissionRunState_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMissionRunState_Response_error_code success(::agt_interfaces::srv::SetMissionRunState_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetMissionRunState_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::SetMissionRunState_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::SetMissionRunState_Response>()
{
  return agt_interfaces::srv::builder::Init_SetMissionRunState_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__SET_MISSION_RUN_STATE__BUILDER_HPP_
