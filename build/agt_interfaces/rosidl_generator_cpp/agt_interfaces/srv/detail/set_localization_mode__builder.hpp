// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/SetLocalizationMode.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__SET_LOCALIZATION_MODE__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__SET_LOCALIZATION_MODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/set_localization_mode__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetLocalizationMode_Request_mode
{
public:
  Init_SetLocalizationMode_Request_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::srv::SetLocalizationMode_Request mode(::agt_interfaces::srv::SetLocalizationMode_Request::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::SetLocalizationMode_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::SetLocalizationMode_Request>()
{
  return agt_interfaces::srv::builder::Init_SetLocalizationMode_Request_mode();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetLocalizationMode_Response_message
{
public:
  explicit Init_SetLocalizationMode_Response_message(::agt_interfaces::srv::SetLocalizationMode_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::SetLocalizationMode_Response message(::agt_interfaces::srv::SetLocalizationMode_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::SetLocalizationMode_Response msg_;
};

class Init_SetLocalizationMode_Response_attempts
{
public:
  explicit Init_SetLocalizationMode_Response_attempts(::agt_interfaces::srv::SetLocalizationMode_Response & msg)
  : msg_(msg)
  {}
  Init_SetLocalizationMode_Response_message attempts(::agt_interfaces::srv::SetLocalizationMode_Response::_attempts_type arg)
  {
    msg_.attempts = std::move(arg);
    return Init_SetLocalizationMode_Response_message(msg_);
  }

private:
  ::agt_interfaces::srv::SetLocalizationMode_Response msg_;
};

class Init_SetLocalizationMode_Response_active_mode
{
public:
  explicit Init_SetLocalizationMode_Response_active_mode(::agt_interfaces::srv::SetLocalizationMode_Response & msg)
  : msg_(msg)
  {}
  Init_SetLocalizationMode_Response_attempts active_mode(::agt_interfaces::srv::SetLocalizationMode_Response::_active_mode_type arg)
  {
    msg_.active_mode = std::move(arg);
    return Init_SetLocalizationMode_Response_attempts(msg_);
  }

private:
  ::agt_interfaces::srv::SetLocalizationMode_Response msg_;
};

class Init_SetLocalizationMode_Response_error_code
{
public:
  explicit Init_SetLocalizationMode_Response_error_code(::agt_interfaces::srv::SetLocalizationMode_Response & msg)
  : msg_(msg)
  {}
  Init_SetLocalizationMode_Response_active_mode error_code(::agt_interfaces::srv::SetLocalizationMode_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_SetLocalizationMode_Response_active_mode(msg_);
  }

private:
  ::agt_interfaces::srv::SetLocalizationMode_Response msg_;
};

class Init_SetLocalizationMode_Response_success
{
public:
  Init_SetLocalizationMode_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetLocalizationMode_Response_error_code success(::agt_interfaces::srv::SetLocalizationMode_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetLocalizationMode_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::SetLocalizationMode_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::SetLocalizationMode_Response>()
{
  return agt_interfaces::srv::builder::Init_SetLocalizationMode_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__SET_LOCALIZATION_MODE__BUILDER_HPP_
