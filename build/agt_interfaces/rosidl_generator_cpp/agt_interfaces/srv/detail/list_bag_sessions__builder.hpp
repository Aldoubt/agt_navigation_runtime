// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/ListBagSessions.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_BAG_SESSIONS__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__LIST_BAG_SESSIONS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/list_bag_sessions__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListBagSessions_Request_experiment_id
{
public:
  explicit Init_ListBagSessions_Request_experiment_id(::agt_interfaces::srv::ListBagSessions_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ListBagSessions_Request experiment_id(::agt_interfaces::srv::ListBagSessions_Request::_experiment_id_type arg)
  {
    msg_.experiment_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ListBagSessions_Request msg_;
};

class Init_ListBagSessions_Request_state
{
public:
  Init_ListBagSessions_Request_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListBagSessions_Request_experiment_id state(::agt_interfaces::srv::ListBagSessions_Request::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ListBagSessions_Request_experiment_id(msg_);
  }

private:
  ::agt_interfaces::srv::ListBagSessions_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ListBagSessions_Request>()
{
  return agt_interfaces::srv::builder::Init_ListBagSessions_Request_state();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListBagSessions_Response_message
{
public:
  explicit Init_ListBagSessions_Response_message(::agt_interfaces::srv::ListBagSessions_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ListBagSessions_Response message(::agt_interfaces::srv::ListBagSessions_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ListBagSessions_Response msg_;
};

class Init_ListBagSessions_Response_sessions
{
public:
  explicit Init_ListBagSessions_Response_sessions(::agt_interfaces::srv::ListBagSessions_Response & msg)
  : msg_(msg)
  {}
  Init_ListBagSessions_Response_message sessions(::agt_interfaces::srv::ListBagSessions_Response::_sessions_type arg)
  {
    msg_.sessions = std::move(arg);
    return Init_ListBagSessions_Response_message(msg_);
  }

private:
  ::agt_interfaces::srv::ListBagSessions_Response msg_;
};

class Init_ListBagSessions_Response_error_code
{
public:
  explicit Init_ListBagSessions_Response_error_code(::agt_interfaces::srv::ListBagSessions_Response & msg)
  : msg_(msg)
  {}
  Init_ListBagSessions_Response_sessions error_code(::agt_interfaces::srv::ListBagSessions_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ListBagSessions_Response_sessions(msg_);
  }

private:
  ::agt_interfaces::srv::ListBagSessions_Response msg_;
};

class Init_ListBagSessions_Response_success
{
public:
  Init_ListBagSessions_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListBagSessions_Response_error_code success(::agt_interfaces::srv::ListBagSessions_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ListBagSessions_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::ListBagSessions_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ListBagSessions_Response>()
{
  return agt_interfaces::srv::builder::Init_ListBagSessions_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_BAG_SESSIONS__BUILDER_HPP_
