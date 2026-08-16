// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/GetSystemHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_SYSTEM_HEALTH__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__GET_SYSTEM_HEALTH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/get_system_health__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetSystemHealth_Request_include_optional
{
public:
  Init_GetSystemHealth_Request_include_optional()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::srv::GetSystemHealth_Request include_optional(::agt_interfaces::srv::GetSystemHealth_Request::_include_optional_type arg)
  {
    msg_.include_optional = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::GetSystemHealth_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::GetSystemHealth_Request>()
{
  return agt_interfaces::srv::builder::Init_GetSystemHealth_Request_include_optional();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetSystemHealth_Response_health
{
public:
  Init_GetSystemHealth_Response_health()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::srv::GetSystemHealth_Response health(::agt_interfaces::srv::GetSystemHealth_Response::_health_type arg)
  {
    msg_.health = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::GetSystemHealth_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::GetSystemHealth_Response>()
{
  return agt_interfaces::srv::builder::Init_GetSystemHealth_Response_health();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_SYSTEM_HEALTH__BUILDER_HPP_
