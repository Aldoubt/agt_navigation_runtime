// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/SemanticWaypointArray.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT_ARRAY__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/semantic_waypoint_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_SemanticWaypointArray_waypoints
{
public:
  explicit Init_SemanticWaypointArray_waypoints(::agt_interfaces::msg::SemanticWaypointArray & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::SemanticWaypointArray waypoints(::agt_interfaces::msg::SemanticWaypointArray::_waypoints_type arg)
  {
    msg_.waypoints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypointArray msg_;
};

class Init_SemanticWaypointArray_base_map_sha256
{
public:
  explicit Init_SemanticWaypointArray_base_map_sha256(::agt_interfaces::msg::SemanticWaypointArray & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypointArray_waypoints base_map_sha256(::agt_interfaces::msg::SemanticWaypointArray::_base_map_sha256_type arg)
  {
    msg_.base_map_sha256 = std::move(arg);
    return Init_SemanticWaypointArray_waypoints(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypointArray msg_;
};

class Init_SemanticWaypointArray_map_id
{
public:
  explicit Init_SemanticWaypointArray_map_id(::agt_interfaces::msg::SemanticWaypointArray & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypointArray_base_map_sha256 map_id(::agt_interfaces::msg::SemanticWaypointArray::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_SemanticWaypointArray_base_map_sha256(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypointArray msg_;
};

class Init_SemanticWaypointArray_schema_version
{
public:
  explicit Init_SemanticWaypointArray_schema_version(::agt_interfaces::msg::SemanticWaypointArray & msg)
  : msg_(msg)
  {}
  Init_SemanticWaypointArray_map_id schema_version(::agt_interfaces::msg::SemanticWaypointArray::_schema_version_type arg)
  {
    msg_.schema_version = std::move(arg);
    return Init_SemanticWaypointArray_map_id(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypointArray msg_;
};

class Init_SemanticWaypointArray_header
{
public:
  Init_SemanticWaypointArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SemanticWaypointArray_schema_version header(::agt_interfaces::msg::SemanticWaypointArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SemanticWaypointArray_schema_version(msg_);
  }

private:
  ::agt_interfaces::msg::SemanticWaypointArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::SemanticWaypointArray>()
{
  return agt_interfaces::msg::builder::Init_SemanticWaypointArray_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT_ARRAY__BUILDER_HPP_
