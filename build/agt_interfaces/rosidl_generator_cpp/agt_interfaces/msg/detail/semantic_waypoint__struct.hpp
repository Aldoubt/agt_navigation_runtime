// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/SemanticWaypoint.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__msg__SemanticWaypoint __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__SemanticWaypoint __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SemanticWaypoint_
{
  using Type = SemanticWaypoint_<ContainerAllocator>;

  explicit SemanticWaypoint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->name = "";
      this->role = "";
      this->position_tolerance = 0.0f;
      this->yaw_tolerance = 0.0f;
      this->preferred_speed = 0.0f;
      this->enabled = false;
    }
  }

  explicit SemanticWaypoint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : id(_alloc),
    name(_alloc),
    role(_alloc),
    pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->name = "";
      this->role = "";
      this->position_tolerance = 0.0f;
      this->yaw_tolerance = 0.0f;
      this->preferred_speed = 0.0f;
      this->enabled = false;
    }
  }

  // field types and members
  using _id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _id_type id;
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _role_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _role_type role;
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;
  using _position_tolerance_type =
    float;
  _position_tolerance_type position_tolerance;
  using _yaw_tolerance_type =
    float;
  _yaw_tolerance_type yaw_tolerance;
  using _preferred_speed_type =
    float;
  _preferred_speed_type preferred_speed;
  using _tags_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _tags_type tags;
  using _enabled_type =
    bool;
  _enabled_type enabled;

  // setters for named parameter idiom
  Type & set__id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__role(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->role = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__position_tolerance(
    const float & _arg)
  {
    this->position_tolerance = _arg;
    return *this;
  }
  Type & set__yaw_tolerance(
    const float & _arg)
  {
    this->yaw_tolerance = _arg;
    return *this;
  }
  Type & set__preferred_speed(
    const float & _arg)
  {
    this->preferred_speed = _arg;
    return *this;
  }
  Type & set__tags(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->tags = _arg;
    return *this;
  }
  Type & set__enabled(
    const bool & _arg)
  {
    this->enabled = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__SemanticWaypoint
    std::shared_ptr<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__SemanticWaypoint
    std::shared_ptr<agt_interfaces::msg::SemanticWaypoint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SemanticWaypoint_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->name != other.name) {
      return false;
    }
    if (this->role != other.role) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->position_tolerance != other.position_tolerance) {
      return false;
    }
    if (this->yaw_tolerance != other.yaw_tolerance) {
      return false;
    }
    if (this->preferred_speed != other.preferred_speed) {
      return false;
    }
    if (this->tags != other.tags) {
      return false;
    }
    if (this->enabled != other.enabled) {
      return false;
    }
    return true;
  }
  bool operator!=(const SemanticWaypoint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SemanticWaypoint_

// alias to use template instance with default allocator
using SemanticWaypoint =
  agt_interfaces::msg::SemanticWaypoint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__STRUCT_HPP_
