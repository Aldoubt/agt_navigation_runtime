// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/TaskReadiness.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__TASK_READINESS__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__TASK_READINESS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/task_readiness__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_TaskReadiness_warning_messages
{
public:
  explicit Init_TaskReadiness_warning_messages(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::TaskReadiness warning_messages(::agt_interfaces::msg::TaskReadiness::_warning_messages_type arg)
  {
    msg_.warning_messages = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_warning_codes
{
public:
  explicit Init_TaskReadiness_warning_codes(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  Init_TaskReadiness_warning_messages warning_codes(::agt_interfaces::msg::TaskReadiness::_warning_codes_type arg)
  {
    msg_.warning_codes = std::move(arg);
    return Init_TaskReadiness_warning_messages(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_blocker_messages
{
public:
  explicit Init_TaskReadiness_blocker_messages(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  Init_TaskReadiness_warning_codes blocker_messages(::agt_interfaces::msg::TaskReadiness::_blocker_messages_type arg)
  {
    msg_.blocker_messages = std::move(arg);
    return Init_TaskReadiness_warning_codes(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_blocker_codes
{
public:
  explicit Init_TaskReadiness_blocker_codes(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  Init_TaskReadiness_blocker_messages blocker_codes(::agt_interfaces::msg::TaskReadiness::_blocker_codes_type arg)
  {
    msg_.blocker_codes = std::move(arg);
    return Init_TaskReadiness_blocker_messages(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_health_revision
{
public:
  explicit Init_TaskReadiness_health_revision(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  Init_TaskReadiness_blocker_codes health_revision(::agt_interfaces::msg::TaskReadiness::_health_revision_type arg)
  {
    msg_.health_revision = std::move(arg);
    return Init_TaskReadiness_blocker_codes(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_localization_state
{
public:
  explicit Init_TaskReadiness_localization_state(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  Init_TaskReadiness_health_revision localization_state(::agt_interfaces::msg::TaskReadiness::_localization_state_type arg)
  {
    msg_.localization_state = std::move(arg);
    return Init_TaskReadiness_health_revision(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_map_version_id
{
public:
  explicit Init_TaskReadiness_map_version_id(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  Init_TaskReadiness_localization_state map_version_id(::agt_interfaces::msg::TaskReadiness::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_TaskReadiness_localization_state(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_map_id
{
public:
  explicit Init_TaskReadiness_map_id(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  Init_TaskReadiness_map_version_id map_id(::agt_interfaces::msg::TaskReadiness::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_TaskReadiness_map_version_id(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_active_mode
{
public:
  explicit Init_TaskReadiness_active_mode(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  Init_TaskReadiness_map_id active_mode(::agt_interfaces::msg::TaskReadiness::_active_mode_type arg)
  {
    msg_.active_mode = std::move(arg);
    return Init_TaskReadiness_map_id(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_ready
{
public:
  explicit Init_TaskReadiness_ready(::agt_interfaces::msg::TaskReadiness & msg)
  : msg_(msg)
  {}
  Init_TaskReadiness_active_mode ready(::agt_interfaces::msg::TaskReadiness::_ready_type arg)
  {
    msg_.ready = std::move(arg);
    return Init_TaskReadiness_active_mode(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

class Init_TaskReadiness_header
{
public:
  Init_TaskReadiness_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TaskReadiness_ready header(::agt_interfaces::msg::TaskReadiness::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_TaskReadiness_ready(msg_);
  }

private:
  ::agt_interfaces::msg::TaskReadiness msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::TaskReadiness>()
{
  return agt_interfaces::msg::builder::Init_TaskReadiness_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__TASK_READINESS__BUILDER_HPP_
