// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/SemanticWaypoint.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/semantic_waypoint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_SemanticWaypoint_enabled
{
public:
  explicit Init_SemanticWaypoint_enabled(::agt_interfaces::msg::SemanticWaypoint & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::SemanticWaypoint enabled(::agt_interfaces::msg::SemanticWaypoint::_enabled_type arg)
  {
    msg_.enabled = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypoint msg_;
};

class Init_SemanticWaypoint_tags
{
public:
  explicit Init_SemanticWaypoint_tags(::agt_interfaces::msg::SemanticWaypoint & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypoint_enabled tags(::agt_interfaces::msg::SemanticWaypoint::_tags_type arg)
  {
    msg_.tags = std::move(arg);
    return Init_SemanticWaypoint_enabled(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypoint msg_;
};

class Init_SemanticWaypoint_preferred_speed
{
public:
  explicit Init_SemanticWaypoint_preferred_speed(::agt_interfaces::msg::SemanticWaypoint & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypoint_tags preferred_speed(::agt_interfaces::msg::SemanticWaypoint::_preferred_speed_type arg)
  {
    msg_.preferred_speed = std::move(arg);
    return Init_SemanticWaypoint_tags(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypoint msg_;
};

class Init_SemanticWaypoint_yaw_tolerance
{
public:
  explicit Init_SemanticWaypoint_yaw_tolerance(::agt_interfaces::msg::SemanticWaypoint & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypoint_preferred_speed yaw_tolerance(::agt_interfaces::msg::SemanticWaypoint::_yaw_tolerance_type arg)
  {
    msg_.yaw_tolerance = std::move(arg);
    return Init_SemanticWaypoint_preferred_speed(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypoint msg_;
};

class Init_SemanticWaypoint_position_tolerance
{
public:
  explicit Init_SemanticWaypoint_position_tolerance(::agt_interfaces::msg::SemanticWaypoint & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypoint_yaw_tolerance position_tolerance(::agt_interfaces::msg::SemanticWaypoint::_position_tolerance_type arg)
  {
    msg_.position_tolerance = std::move(arg);
    return Init_SemanticWaypoint_yaw_tolerance(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypoint msg_;
};

class Init_SemanticWaypoint_pose
{
public:
  explicit Init_SemanticWaypoint_pose(::agt_interfaces::msg::SemanticWaypoint & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypoint_position_tolerance pose(::agt_interfaces::msg::SemanticWaypoint::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_SemanticWaypoint_position_tolerance(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypoint msg_;
};

class Init_SemanticWaypoint_role
{
public:
  explicit Init_SemanticWaypoint_role(::agt_interfaces::msg::SemanticWaypoint & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypoint_pose role(::agt_interfaces::msg::SemanticWaypoint::_role_type arg)
  {
    msg_.role = std::move(arg);
    return Init_SemanticWaypoint_pose(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypoint msg_;
};

class Init_SemanticWaypoint_name
{
public:
  explicit Init_SemanticWaypoint_name(::agt_interfaces::msg::SemanticWaypoint & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypoint_role name(::agt_interfaces::msg::SemanticWaypoint::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_SemanticWaypoint_role(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypoint msg_;
};

class Init_SemanticWaypoint_id
{
public:
  Init_SemanticWaypoint_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SemanticWaypoint_name id(::agt_interfaces::msg::SemanticWaypoint::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_SemanticWaypoint_name(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::SemanticWaypoint>()
{
  return agt_interfaces::msg::builder::Init_SemanticWaypoint_id();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__BUILDER_HPP_
