// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/BagSessionSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/bag_session_summary__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_BagSessionSummary_contains_navigation_outputs
{
public:
  explicit Init_BagSessionSummary_contains_navigation_outputs(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::BagSessionSummary contains_navigation_outputs(::agt_interfaces::msg::BagSessionSummary::_contains_navigation_outputs_type arg)
  {
    msg_.contains_navigation_outputs = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_contains_mapping_outputs
{
public:
  explicit Init_BagSessionSummary_contains_mapping_outputs(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_contains_navigation_outputs contains_mapping_outputs(::agt_interfaces::msg::BagSessionSummary::_contains_mapping_outputs_type arg)
  {
    msg_.contains_mapping_outputs = std::move(arg);
    return Init_BagSessionSummary_contains_navigation_outputs(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_mapping_input_ready
{
public:
  explicit Init_BagSessionSummary_mapping_input_ready(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_contains_mapping_outputs mapping_input_ready(::agt_interfaces::msg::BagSessionSummary::_mapping_input_ready_type arg)
  {
    msg_.mapping_input_ready = std::move(arg);
    return Init_BagSessionSummary_contains_mapping_outputs(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_storage_identifier
{
public:
  explicit Init_BagSessionSummary_storage_identifier(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_mapping_input_ready storage_identifier(::agt_interfaces::msg::BagSessionSummary::_storage_identifier_type arg)
  {
    msg_.storage_identifier = std::move(arg);
    return Init_BagSessionSummary_mapping_input_ready(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_message_count
{
public:
  explicit Init_BagSessionSummary_message_count(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_storage_identifier message_count(::agt_interfaces::msg::BagSessionSummary::_message_count_type arg)
  {
    msg_.message_count = std::move(arg);
    return Init_BagSessionSummary_storage_identifier(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_process_id
{
public:
  explicit Init_BagSessionSummary_process_id(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_message_count process_id(::agt_interfaces::msg::BagSessionSummary::_process_id_type arg)
  {
    msg_.process_id = std::move(arg);
    return Init_BagSessionSummary_message_count(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_message
{
public:
  explicit Init_BagSessionSummary_message(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_process_id message(::agt_interfaces::msg::BagSessionSummary::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_BagSessionSummary_process_id(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_updated_at
{
public:
  explicit Init_BagSessionSummary_updated_at(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_message updated_at(::agt_interfaces::msg::BagSessionSummary::_updated_at_type arg)
  {
    msg_.updated_at = std::move(arg);
    return Init_BagSessionSummary_message(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_started_at
{
public:
  explicit Init_BagSessionSummary_started_at(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_updated_at started_at(::agt_interfaces::msg::BagSessionSummary::_started_at_type arg)
  {
    msg_.started_at = std::move(arg);
    return Init_BagSessionSummary_updated_at(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_storage_bytes
{
public:
  explicit Init_BagSessionSummary_storage_bytes(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_started_at storage_bytes(::agt_interfaces::msg::BagSessionSummary::_storage_bytes_type arg)
  {
    msg_.storage_bytes = std::move(arg);
    return Init_BagSessionSummary_started_at(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_playback_rate
{
public:
  explicit Init_BagSessionSummary_playback_rate(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_storage_bytes playback_rate(::agt_interfaces::msg::BagSessionSummary::_playback_rate_type arg)
  {
    msg_.playback_rate = std::move(arg);
    return Init_BagSessionSummary_storage_bytes(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_simulation
{
public:
  explicit Init_BagSessionSummary_simulation(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_playback_rate simulation(::agt_interfaces::msg::BagSessionSummary::_simulation_type arg)
  {
    msg_.simulation = std::move(arg);
    return Init_BagSessionSummary_playback_rate(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_complete
{
public:
  explicit Init_BagSessionSummary_complete(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_simulation complete(::agt_interfaces::msg::BagSessionSummary::_complete_type arg)
  {
    msg_.complete = std::move(arg);
    return Init_BagSessionSummary_simulation(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_relative_uri
{
public:
  explicit Init_BagSessionSummary_relative_uri(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_complete relative_uri(::agt_interfaces::msg::BagSessionSummary::_relative_uri_type arg)
  {
    msg_.relative_uri = std::move(arg);
    return Init_BagSessionSummary_complete(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_profile_id
{
public:
  explicit Init_BagSessionSummary_profile_id(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_relative_uri profile_id(::agt_interfaces::msg::BagSessionSummary::_profile_id_type arg)
  {
    msg_.profile_id = std::move(arg);
    return Init_BagSessionSummary_relative_uri(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_experiment_id
{
public:
  explicit Init_BagSessionSummary_experiment_id(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_profile_id experiment_id(::agt_interfaces::msg::BagSessionSummary::_experiment_id_type arg)
  {
    msg_.experiment_id = std::move(arg);
    return Init_BagSessionSummary_profile_id(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_bag_id
{
public:
  explicit Init_BagSessionSummary_bag_id(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_experiment_id bag_id(::agt_interfaces::msg::BagSessionSummary::_bag_id_type arg)
  {
    msg_.bag_id = std::move(arg);
    return Init_BagSessionSummary_experiment_id(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_state
{
public:
  explicit Init_BagSessionSummary_state(::agt_interfaces::msg::BagSessionSummary & msg)
  : msg_(msg)
  {}
  Init_BagSessionSummary_bag_id state(::agt_interfaces::msg::BagSessionSummary::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_BagSessionSummary_bag_id(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

class Init_BagSessionSummary_header
{
public:
  Init_BagSessionSummary_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BagSessionSummary_state header(::agt_interfaces::msg::BagSessionSummary::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_BagSessionSummary_state(msg_);
  }

private:
  ::agt_interfaces::msg::BagSessionSummary msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::BagSessionSummary>()
{
  return agt_interfaces::msg::builder::Init_BagSessionSummary_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__BUILDER_HPP_
