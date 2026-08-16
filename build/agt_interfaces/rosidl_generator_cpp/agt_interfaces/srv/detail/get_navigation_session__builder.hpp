// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/GetNavigationSession.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_NAVIGATION_SESSION__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__GET_NAVIGATION_SESSION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/get_navigation_session__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetNavigationSession_Request_client_request_id
{
public:
  explicit Init_GetNavigationSession_Request_client_request_id(::agt_interfaces::srv::GetNavigationSession_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::GetNavigationSession_Request client_request_id(::agt_interfaces::srv::GetNavigationSession_Request::_client_request_id_type arg)
  {
    msg_.client_request_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::GetNavigationSession_Request msg_;
};

class Init_GetNavigationSession_Request_session_id
{
public:
  Init_GetNavigationSession_Request_session_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetNavigationSession_Request_client_request_id session_id(::agt_interfaces::srv::GetNavigationSession_Request::_session_id_type arg)
  {
    msg_.session_id = std::move(arg);
    return Init_GetNavigationSession_Request_client_request_id(msg_);
  }

private:
  ::agt_interfaces::srv::GetNavigationSession_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::GetNavigationSession_Request>()
{
  return agt_interfaces::srv::builder::Init_GetNavigationSession_Request_session_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetNavigationSession_Response_message
{
public:
  explicit Init_GetNavigationSession_Response_message(::agt_interfaces::srv::GetNavigationSession_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::GetNavigationSession_Response message(::agt_interfaces::srv::GetNavigationSession_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::GetNavigationSession_Response msg_;
};

class Init_GetNavigationSession_Response_status
{
public:
  explicit Init_GetNavigationSession_Response_status(::agt_interfaces::srv::GetNavigationSession_Response & msg)
  : msg_(msg)
  {}
  Init_GetNavigationSession_Response_message status(::agt_interfaces::srv::GetNavigationSession_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_GetNavigationSession_Response_message(msg_);
  }

private:
  ::agt_interfaces::srv::GetNavigationSession_Response msg_;
};

class Init_GetNavigationSession_Response_error_code
{
public:
  explicit Init_GetNavigationSession_Response_error_code(::agt_interfaces::srv::GetNavigationSession_Response & msg)
  : msg_(msg)
  {}
  Init_GetNavigationSession_Response_status error_code(::agt_interfaces::srv::GetNavigationSession_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_GetNavigationSession_Response_status(msg_);
  }

private:
  ::agt_interfaces::srv::GetNavigationSession_Response msg_;
};

class Init_GetNavigationSession_Response_success
{
public:
  Init_GetNavigationSession_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetNavigationSession_Response_error_code success(::agt_interfaces::srv::GetNavigationSession_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetNavigationSession_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::GetNavigationSession_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::GetNavigationSession_Response>()
{
  return agt_interfaces::srv::builder::Init_GetNavigationSession_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_NAVIGATION_SESSION__BUILDER_HPP_
