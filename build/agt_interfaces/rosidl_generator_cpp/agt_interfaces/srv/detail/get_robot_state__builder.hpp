// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/GetRobotState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATE__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/get_robot_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetRobotState_Request_include_details
{
public:
  Init_GetRobotState_Request_include_details()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::srv::GetRobotState_Request include_details(::agt_interfaces::srv::GetRobotState_Request::_include_details_type arg)
  {
    msg_.include_details = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::GetRobotState_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::GetRobotState_Request>()
{
  return agt_interfaces::srv::builder::Init_GetRobotState_Request_include_details();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetRobotState_Response_message
{
public:
  explicit Init_GetRobotState_Response_message(::agt_interfaces::srv::GetRobotState_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::GetRobotState_Response message(::agt_interfaces::srv::GetRobotState_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::GetRobotState_Response msg_;
};

class Init_GetRobotState_Response_state
{
public:
  explicit Init_GetRobotState_Response_state(::agt_interfaces::srv::GetRobotState_Response & msg)
  : msg_(msg)
  {}
  Init_GetRobotState_Response_message state(::agt_interfaces::srv::GetRobotState_Response::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_GetRobotState_Response_message(msg_);
  }

private:
  ::agt_interfaces::srv::GetRobotState_Response msg_;
};

class Init_GetRobotState_Response_error_code
{
public:
  explicit Init_GetRobotState_Response_error_code(::agt_interfaces::srv::GetRobotState_Response & msg)
  : msg_(msg)
  {}
  Init_GetRobotState_Response_state error_code(::agt_interfaces::srv::GetRobotState_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_GetRobotState_Response_state(msg_);
  }

private:
  ::agt_interfaces::srv::GetRobotState_Response msg_;
};

class Init_GetRobotState_Response_success
{
public:
  Init_GetRobotState_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetRobotState_Response_error_code success(::agt_interfaces::srv::GetRobotState_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetRobotState_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::GetRobotState_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::GetRobotState_Response>()
{
  return agt_interfaces::srv::builder::Init_GetRobotState_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATE__BUILDER_HPP_
