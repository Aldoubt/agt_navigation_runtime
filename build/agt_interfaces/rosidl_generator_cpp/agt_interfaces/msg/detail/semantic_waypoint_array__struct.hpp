// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/SemanticWaypointArray.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT_ARRAY__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'waypoints'
#include "agt_interfaces/msg/detail/semantic_waypoint__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__msg__SemanticWaypointArray __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__SemanticWaypointArray __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SemanticWaypointArray_
{
  using Type = SemanticWaypointArray_<ContainerAllocator>;

  explicit SemanticWaypointArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->schema_version = "";
      this->map_id = "";
      this->base_map_sha256 = "";
    }
  }

  explicit SemanticWaypointArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    schema_version(_alloc),
    map_id(_alloc),
    base_map_sha256(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->schema_version = "";
      this->map_id = "";
      this->base_map_sha256 = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _schema_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _schema_version_type schema_version;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _base_map_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _base_map_sha256_type base_map_sha256;
  using _waypoints_type =
    std::vector<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>>>;
  _waypoints_type waypoints;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__schema_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->schema_version = _arg;
    return *this;
  }
  Type & set__map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_id = _arg;
    return *this;
  }
  Type & set__base_map_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->base_map_sha256 = _arg;
    return *this;
  }
  Type & set__waypoints(
    const std::vector<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>>> & _arg)
  {
    this->waypoints = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__SemanticWaypointArray
    std::shared_ptr<agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__SemanticWaypointArray
    std::shared_ptr<agt_interfaces::msg::SemanticWaypointArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SemanticWaypointArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->schema_version != other.schema_version) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->base_map_sha256 != other.base_map_sha256) {
      return false;
    }
    if (this->waypoints != other.waypoints) {
      return false;
    }
    return true;
  }
  bool operator!=(const SemanticWaypointArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SemanticWaypointArray_

// alias to use template instance with default allocator
using SemanticWaypointArray =
  agt_interfaces::msg::SemanticWaypointArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT_ARRAY__STRUCT_HPP_
