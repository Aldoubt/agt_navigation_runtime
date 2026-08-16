// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/ComponentHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/component_health__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_ComponentHealth_detail
{
public:
  explicit Init_ComponentHealth_detail(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::ComponentHealth detail(::agt_interfaces::msg::ComponentHealth::_detail_type arg)
  {
    msg_.detail = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_errors
{
public:
  explicit Init_ComponentHealth_errors(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_detail errors(::agt_interfaces::msg::ComponentHealth::_errors_type arg)
  {
    msg_.errors = std::move(arg);
    return Init_ComponentHealth_detail(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_warnings
{
public:
  explicit Init_ComponentHealth_warnings(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_errors warnings(::agt_interfaces::msg::ComponentHealth::_warnings_type arg)
  {
    msg_.warnings = std::move(arg);
    return Init_ComponentHealth_errors(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_condition_failures
{
public:
  explicit Init_ComponentHealth_condition_failures(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_warnings condition_failures(::agt_interfaces::msg::ComponentHealth::_condition_failures_type arg)
  {
    msg_.condition_failures = std::move(arg);
    return Init_ComponentHealth_warnings(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_lifecycle_failures
{
public:
  explicit Init_ComponentHealth_lifecycle_failures(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_condition_failures lifecycle_failures(::agt_interfaces::msg::ComponentHealth::_lifecycle_failures_type arg)
  {
    msg_.lifecycle_failures = std::move(arg);
    return Init_ComponentHealth_condition_failures(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_missing_nodes
{
public:
  explicit Init_ComponentHealth_missing_nodes(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_lifecycle_failures missing_nodes(::agt_interfaces::msg::ComponentHealth::_missing_nodes_type arg)
  {
    msg_.missing_nodes = std::move(arg);
    return Init_ComponentHealth_lifecycle_failures(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_missing_frames
{
public:
  explicit Init_ComponentHealth_missing_frames(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_missing_nodes missing_frames(::agt_interfaces::msg::ComponentHealth::_missing_frames_type arg)
  {
    msg_.missing_frames = std::move(arg);
    return Init_ComponentHealth_missing_nodes(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_missing_topics
{
public:
  explicit Init_ComponentHealth_missing_topics(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_missing_frames missing_topics(::agt_interfaces::msg::ComponentHealth::_missing_topics_type arg)
  {
    msg_.missing_topics = std::move(arg);
    return Init_ComponentHealth_missing_frames(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_message_count
{
public:
  explicit Init_ComponentHealth_message_count(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_missing_topics message_count(::agt_interfaces::msg::ComponentHealth::_message_count_type arg)
  {
    msg_.message_count = std::move(arg);
    return Init_ComponentHealth_missing_topics(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_message_age_sec
{
public:
  explicit Init_ComponentHealth_message_age_sec(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_message_count message_age_sec(::agt_interfaces::msg::ComponentHealth::_message_age_sec_type arg)
  {
    msg_.message_age_sec = std::move(arg);
    return Init_ComponentHealth_message_count(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_observed_rate_hz
{
public:
  explicit Init_ComponentHealth_observed_rate_hz(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_message_age_sec observed_rate_hz(::agt_interfaces::msg::ComponentHealth::_observed_rate_hz_type arg)
  {
    msg_.observed_rate_hz = std::move(arg);
    return Init_ComponentHealth_message_age_sec(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_present
{
public:
  explicit Init_ComponentHealth_present(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_observed_rate_hz present(::agt_interfaces::msg::ComponentHealth::_present_type arg)
  {
    msg_.present = std::move(arg);
    return Init_ComponentHealth_observed_rate_hz(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_required
{
public:
  explicit Init_ComponentHealth_required(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_present required(::agt_interfaces::msg::ComponentHealth::_required_type arg)
  {
    msg_.required = std::move(arg);
    return Init_ComponentHealth_present(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_state
{
public:
  explicit Init_ComponentHealth_state(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_required state(::agt_interfaces::msg::ComponentHealth::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ComponentHealth_required(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_display_name
{
public:
  explicit Init_ComponentHealth_display_name(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_state display_name(::agt_interfaces::msg::ComponentHealth::_display_name_type arg)
  {
    msg_.display_name = std::move(arg);
    return Init_ComponentHealth_state(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_component_id
{
public:
  explicit Init_ComponentHealth_component_id(::agt_interfaces::msg::ComponentHealth & msg)
  : msg_(msg)
  {}
  Init_ComponentHealth_display_name component_id(::agt_interfaces::msg::ComponentHealth::_component_id_type arg)
  {
    msg_.component_id = std::move(arg);
    return Init_ComponentHealth_display_name(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

class Init_ComponentHealth_header
{
public:
  Init_ComponentHealth_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ComponentHealth_component_id header(::agt_interfaces::msg::ComponentHealth::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ComponentHealth_component_id(msg_);
  }

private:
  ::agt_interfaces::msg::ComponentHealth msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::ComponentHealth>()
{
  return agt_interfaces::msg::builder::Init_ComponentHealth_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__BUILDER_HPP_
