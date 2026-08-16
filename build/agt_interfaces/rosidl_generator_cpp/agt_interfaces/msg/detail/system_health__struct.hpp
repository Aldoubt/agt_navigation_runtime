// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/SystemHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__STRUCT_HPP_

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
// Member 'components'
#include "agt_interfaces/msg/detail/component_health__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__msg__SystemHealth __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__SystemHealth __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SystemHealth_
{
  using Type = SystemHealth_<ContainerAllocator>;

  explicit SystemHealth_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->overall_state = 0;
      this->revision = 0ull;
    }
  }

  explicit SystemHealth_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->overall_state = 0;
      this->revision = 0ull;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _overall_state_type =
    uint8_t;
  _overall_state_type overall_state;
  using _revision_type =
    uint64_t;
  _revision_type revision;
  using _components_type =
    std::vector<agt_interfaces::msg::ComponentHealth_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<agt_interfaces::msg::ComponentHealth_<ContainerAllocator>>>;
  _components_type components;
  using _blocker_codes_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _blocker_codes_type blocker_codes;
  using _blocker_messages_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _blocker_messages_type blocker_messages;
  using _warning_codes_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _warning_codes_type warning_codes;
  using _warning_messages_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _warning_messages_type warning_messages;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__overall_state(
    const uint8_t & _arg)
  {
    this->overall_state = _arg;
    return *this;
  }
  Type & set__revision(
    const uint64_t & _arg)
  {
    this->revision = _arg;
    return *this;
  }
  Type & set__components(
    const std::vector<agt_interfaces::msg::ComponentHealth_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<agt_interfaces::msg::ComponentHealth_<ContainerAllocator>>> & _arg)
  {
    this->components = _arg;
    return *this;
  }
  Type & set__blocker_codes(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->blocker_codes = _arg;
    return *this;
  }
  Type & set__blocker_messages(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->blocker_messages = _arg;
    return *this;
  }
  Type & set__warning_codes(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->warning_codes = _arg;
    return *this;
  }
  Type & set__warning_messages(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->warning_messages = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t STATE_UNKNOWN =
    0u;
  static constexpr uint8_t STATE_OK =
    1u;
  static constexpr uint8_t STATE_WARN =
    2u;
  static constexpr uint8_t STATE_ERROR =
    3u;

  // pointer types
  using RawPtr =
    agt_interfaces::msg::SystemHealth_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::SystemHealth_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::SystemHealth_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::SystemHealth_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::SystemHealth_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::SystemHealth_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::SystemHealth_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::SystemHealth_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::SystemHealth_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::SystemHealth_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__SystemHealth
    std::shared_ptr<agt_interfaces::msg::SystemHealth_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__SystemHealth
    std::shared_ptr<agt_interfaces::msg::SystemHealth_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SystemHealth_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->overall_state != other.overall_state) {
      return false;
    }
    if (this->revision != other.revision) {
      return false;
    }
    if (this->components != other.components) {
      return false;
    }
    if (this->blocker_codes != other.blocker_codes) {
      return false;
    }
    if (this->blocker_messages != other.blocker_messages) {
      return false;
    }
    if (this->warning_codes != other.warning_codes) {
      return false;
    }
    if (this->warning_messages != other.warning_messages) {
      return false;
    }
    return true;
  }
  bool operator!=(const SystemHealth_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SystemHealth_

// alias to use template instance with default allocator
using SystemHealth =
  agt_interfaces::msg::SystemHealth_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SystemHealth_<ContainerAllocator>::STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SystemHealth_<ContainerAllocator>::STATE_OK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SystemHealth_<ContainerAllocator>::STATE_WARN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SystemHealth_<ContainerAllocator>::STATE_ERROR;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__STRUCT_HPP_
