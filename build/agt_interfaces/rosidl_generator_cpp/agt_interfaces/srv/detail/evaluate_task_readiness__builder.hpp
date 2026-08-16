// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/EvaluateTaskReadiness.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/evaluate_task_readiness__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_EvaluateTaskReadiness_Request_gate_profile
{
public:
  explicit Init_EvaluateTaskReadiness_Request_gate_profile(::agt_interfaces::srv::EvaluateTaskReadiness_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::EvaluateTaskReadiness_Request gate_profile(::agt_interfaces::srv::EvaluateTaskReadiness_Request::_gate_profile_type arg)
  {
    msg_.gate_profile = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::EvaluateTaskReadiness_Request msg_;
};

class Init_EvaluateTaskReadiness_Request_task_id
{
public:
  explicit Init_EvaluateTaskReadiness_Request_task_id(::agt_interfaces::srv::EvaluateTaskReadiness_Request & msg)
  : msg_(msg)
  {}
  Init_EvaluateTaskReadiness_Request_gate_profile task_id(::agt_interfaces::srv::EvaluateTaskReadiness_Request::_task_id_type arg)
  {
    msg_.task_id = std::move(arg);
    return Init_EvaluateTaskReadiness_Request_gate_profile(msg_);
  }

private:
  ::agt_interfaces::srv::EvaluateTaskReadiness_Request msg_;
};

class Init_EvaluateTaskReadiness_Request_validate_task
{
public:
  Init_EvaluateTaskReadiness_Request_validate_task()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EvaluateTaskReadiness_Request_task_id validate_task(::agt_interfaces::srv::EvaluateTaskReadiness_Request::_validate_task_type arg)
  {
    msg_.validate_task = std::move(arg);
    return Init_EvaluateTaskReadiness_Request_task_id(msg_);
  }

private:
  ::agt_interfaces::srv::EvaluateTaskReadiness_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::EvaluateTaskReadiness_Request>()
{
  return agt_interfaces::srv::builder::Init_EvaluateTaskReadiness_Request_validate_task();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_EvaluateTaskReadiness_Response_readiness
{
public:
  Init_EvaluateTaskReadiness_Response_readiness()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::srv::EvaluateTaskReadiness_Response readiness(::agt_interfaces::srv::EvaluateTaskReadiness_Response::_readiness_type arg)
  {
    msg_.readiness = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::EvaluateTaskReadiness_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::EvaluateTaskReadiness_Response>()
{
  return agt_interfaces::srv::builder::Init_EvaluateTaskReadiness_Response_readiness();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__BUILDER_HPP_
