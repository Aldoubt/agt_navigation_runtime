// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/MissionEvent.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MISSION_EVENT__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__MISSION_EVENT__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__msg__MissionEvent __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__MissionEvent __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MissionEvent_
{
  using Type = MissionEvent_<ContainerAllocator>;

  explicit MissionEvent_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->event_type = "";
      this->source = "";
      this->correlation_id = "";
      this->mission_id = "";
      this->metadata_json = "";
    }
  }

  explicit MissionEvent_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    event_type(_alloc),
    source(_alloc),
    correlation_id(_alloc),
    mission_id(_alloc),
    metadata_json(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->event_type = "";
      this->source = "";
      this->correlation_id = "";
      this->mission_id = "";
      this->metadata_json = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _event_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _event_type_type event_type;
  using _source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_type source;
  using _correlation_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _correlation_id_type correlation_id;
  using _mission_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_id_type mission_id;
  using _metadata_json_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _metadata_json_type metadata_json;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__event_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->event_type = _arg;
    return *this;
  }
  Type & set__source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source = _arg;
    return *this;
  }
  Type & set__correlation_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->correlation_id = _arg;
    return *this;
  }
  Type & set__mission_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mission_id = _arg;
    return *this;
  }
  Type & set__metadata_json(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->metadata_json = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::msg::MissionEvent_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::MissionEvent_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::MissionEvent_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::MissionEvent_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::MissionEvent_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::MissionEvent_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::MissionEvent_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::MissionEvent_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::MissionEvent_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::MissionEvent_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__MissionEvent
    std::shared_ptr<agt_interfaces::msg::MissionEvent_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__MissionEvent
    std::shared_ptr<agt_interfaces::msg::MissionEvent_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MissionEvent_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->event_type != other.event_type) {
      return false;
    }
    if (this->source != other.source) {
      return false;
    }
    if (this->correlation_id != other.correlation_id) {
      return false;
    }
    if (this->mission_id != other.mission_id) {
      return false;
    }
    if (this->metadata_json != other.metadata_json) {
      return false;
    }
    return true;
  }
  bool operator!=(const MissionEvent_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MissionEvent_

// alias to use template instance with default allocator
using MissionEvent =
  agt_interfaces::msg::MissionEvent_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__MISSION_EVENT__STRUCT_HPP_
