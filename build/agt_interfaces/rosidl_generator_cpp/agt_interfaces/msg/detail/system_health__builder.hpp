// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/SystemHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/system_health__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_SystemHealth_warning_messages
{
public:
  explicit Init_SystemHealth_warning_messages(::agt_interfaces::msg::SystemHealth & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::SystemHealth warning_messages(::agt_interfaces::msg::SystemHealth::_warning_messages_type arg)
  {
    msg_.warning_messages = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::SystemHealth msg_;
};

class Init_SystemHealth_warning_codes
{
public:
  explicit Init_SystemHealth_warning_codes(::agt_interfaces::msg::SystemHealth & msg)
  : msg_(msg)
  {}
  Init_SystemHealth_warning_messages warning_codes(::agt_interfaces::msg::SystemHealth::_warning_codes_type arg)
  {
    msg_.warning_codes = std::move(arg);
    return Init_SystemHealth_warning_messages(msg_);
  }

private:
  ::agt_interfaces::msg::SystemHealth msg_;
};

class Init_SystemHealth_blocker_messages
{
public:
  explicit Init_SystemHealth_blocker_messages(::agt_interfaces::msg::SystemHealth & msg)
  : msg_(msg)
  {}
  Init_SystemHealth_warning_codes blocker_messages(::agt_interfaces::msg::SystemHealth::_blocker_messages_type arg)
  {
    msg_.blocker_messages = std::move(arg);
    return Init_SystemHealth_warning_codes(msg_);
  }

private:
  ::agt_interfaces::msg::SystemHealth msg_;
};

class Init_SystemHealth_blocker_codes
{
public:
  explicit Init_SystemHealth_blocker_codes(::agt_interfaces::msg::SystemHealth & msg)
  : msg_(msg)
  {}
  Init_SystemHealth_blocker_messages blocker_codes(::agt_interfaces::msg::SystemHealth::_blocker_codes_type arg)
  {
    msg_.blocker_codes = std::move(arg);
    return Init_SystemHealth_blocker_messages(msg_);
  }

private:
  ::agt_interfaces::msg::SystemHealth msg_;
};

class Init_SystemHealth_components
{
public:
  explicit Init_SystemHealth_components(::agt_interfaces::msg::SystemHealth & msg)
  : msg_(msg)
  {}
  Init_SystemHealth_blocker_codes components(::agt_interfaces::msg::SystemHealth::_components_type arg)
  {
    msg_.components = std::move(arg);
    return Init_SystemHealth_blocker_codes(msg_);
  }

private:
  ::agt_interfaces::msg::SystemHealth msg_;
};

class Init_SystemHealth_revision
{
public:
  explicit Init_SystemHealth_revision(::agt_interfaces::msg::SystemHealth & msg)
  : msg_(msg)
  {}
  Init_SystemHealth_components revision(::agt_interfaces::msg::SystemHealth::_revision_type arg)
  {
    msg_.revision = std::move(arg);
    return Init_SystemHealth_components(msg_);
  }

private:
  ::agt_interfaces::msg::SystemHealth msg_;
};

class Init_SystemHealth_overall_state
{
public:
  explicit Init_SystemHealth_overall_state(::agt_interfaces::msg::SystemHealth & msg)
  : msg_(msg)
  {}
  Init_SystemHealth_revision overall_state(::agt_interfaces::msg::SystemHealth::_overall_state_type arg)
  {
    msg_.overall_state = std::move(arg);
    return Init_SystemHealth_revision(msg_);
  }

private:
  ::agt_interfaces::msg::SystemHealth msg_;
};

class Init_SystemHealth_header
{
public:
  Init_SystemHealth_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SystemHealth_overall_state header(::agt_interfaces::msg::SystemHealth::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SystemHealth_overall_state(msg_);
  }

private:
  ::agt_interfaces::msg::SystemHealth msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::SystemHealth>()
{
  return agt_interfaces::msg::builder::Init_SystemHealth_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__BUILDER_HPP_
