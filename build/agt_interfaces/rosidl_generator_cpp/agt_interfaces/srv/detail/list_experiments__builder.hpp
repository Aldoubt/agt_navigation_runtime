// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/ListExperiments.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_EXPERIMENTS__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__LIST_EXPERIMENTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/list_experiments__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListExperiments_Request_state
{
public:
  Init_ListExperiments_Request_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::srv::ListExperiments_Request state(::agt_interfaces::srv::ListExperiments_Request::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ListExperiments_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ListExperiments_Request>()
{
  return agt_interfaces::srv::builder::Init_ListExperiments_Request_state();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListExperiments_Response_message
{
public:
  explicit Init_ListExperiments_Response_message(::agt_interfaces::srv::ListExperiments_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ListExperiments_Response message(::agt_interfaces::srv::ListExperiments_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ListExperiments_Response msg_;
};

class Init_ListExperiments_Response_experiments
{
public:
  explicit Init_ListExperiments_Response_experiments(::agt_interfaces::srv::ListExperiments_Response & msg)
  : msg_(msg)
  {}
  Init_ListExperiments_Response_message experiments(::agt_interfaces::srv::ListExperiments_Response::_experiments_type arg)
  {
    msg_.experiments = std::move(arg);
    return Init_ListExperiments_Response_message(msg_);
  }

private:
  ::agt_interfaces::srv::ListExperiments_Response msg_;
};

class Init_ListExperiments_Response_error_code
{
public:
  explicit Init_ListExperiments_Response_error_code(::agt_interfaces::srv::ListExperiments_Response & msg)
  : msg_(msg)
  {}
  Init_ListExperiments_Response_experiments error_code(::agt_interfaces::srv::ListExperiments_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ListExperiments_Response_experiments(msg_);
  }

private:
  ::agt_interfaces::srv::ListExperiments_Response msg_;
};

class Init_ListExperiments_Response_success
{
public:
  Init_ListExperiments_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListExperiments_Response_error_code success(::agt_interfaces::srv::ListExperiments_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ListExperiments_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::ListExperiments_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ListExperiments_Response>()
{
  return agt_interfaces::srv::builder::Init_ListExperiments_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_EXPERIMENTS__BUILDER_HPP_
