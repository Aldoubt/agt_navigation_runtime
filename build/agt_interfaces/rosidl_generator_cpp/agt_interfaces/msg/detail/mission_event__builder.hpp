// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/MissionEvent.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MISSION_EVENT__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__MISSION_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/mission_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_MissionEvent_metadata_json
{
public:
  explicit Init_MissionEvent_metadata_json(::agt_interfaces::msg::MissionEvent & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::MissionEvent metadata_json(::agt_interfaces::msg::MissionEvent::_metadata_json_type arg)
  {
    msg_.metadata_json = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::MissionEvent msg_;
};

class Init_MissionEvent_mission_id
{
public:
  explicit Init_MissionEvent_mission_id(::agt_interfaces::msg::MissionEvent & msg)
  : msg_(msg)
  {}
  Init_MissionEvent_metadata_json mission_id(::agt_interfaces::msg::MissionEvent::_mission_id_type arg)
  {
    msg_.mission_id = std::move(arg);
    return Init_MissionEvent_metadata_json(msg_);
  }

private:
  ::agt_interfaces::msg::MissionEvent msg_;
};

class Init_MissionEvent_correlation_id
{
public:
  explicit Init_MissionEvent_correlation_id(::agt_interfaces::msg::MissionEvent & msg)
  : msg_(msg)
  {}
  Init_MissionEvent_mission_id correlation_id(::agt_interfaces::msg::MissionEvent::_correlation_id_type arg)
  {
    msg_.correlation_id = std::move(arg);
    return Init_MissionEvent_mission_id(msg_);
  }

private:
  ::agt_interfaces::msg::MissionEvent msg_;
};

class Init_MissionEvent_source
{
public:
  explicit Init_MissionEvent_source(::agt_interfaces::msg::MissionEvent & msg)
  : msg_(msg)
  {}
  Init_MissionEvent_correlation_id source(::agt_interfaces::msg::MissionEvent::_source_type arg)
  {
    msg_.source = std::move(arg);
    return Init_MissionEvent_correlation_id(msg_);
  }

private:
  ::agt_interfaces::msg::MissionEvent msg_;
};

class Init_MissionEvent_event_type
{
public:
  explicit Init_MissionEvent_event_type(::agt_interfaces::msg::MissionEvent & msg)
  : msg_(msg)
  {}
  Init_MissionEvent_source event_type(::agt_interfaces::msg::MissionEvent::_event_type_type arg)
  {
    msg_.event_type = std::move(arg);
    return Init_MissionEvent_source(msg_);
  }

private:
  ::agt_interfaces::msg::MissionEvent msg_;
};

class Init_MissionEvent_header
{
public:
  Init_MissionEvent_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MissionEvent_event_type header(::agt_interfaces::msg::MissionEvent::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MissionEvent_event_type(msg_);
  }

private:
  ::agt_interfaces::msg::MissionEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::MissionEvent>()
{
  return agt_interfaces::msg::builder::Init_MissionEvent_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__MISSION_EVENT__BUILDER_HPP_
