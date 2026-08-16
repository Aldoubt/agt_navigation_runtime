// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/ComponentHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__STRUCT_HPP_

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
# define DEPRECATED__agt_interfaces__msg__ComponentHealth __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__ComponentHealth __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ComponentHealth_
{
  using Type = ComponentHealth_<ContainerAllocator>;

  explicit ComponentHealth_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->component_id = "";
      this->display_name = "";
      this->state = 0;
      this->required = false;
      this->present = false;
      this->observed_rate_hz = 0.0;
      this->message_age_sec = 0.0;
      this->message_count = 0ull;
      this->detail = "";
    }
  }

  explicit ComponentHealth_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    component_id(_alloc),
    display_name(_alloc),
    detail(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->component_id = "";
      this->display_name = "";
      this->state = 0;
      this->required = false;
      this->present = false;
      this->observed_rate_hz = 0.0;
      this->message_age_sec = 0.0;
      this->message_count = 0ull;
      this->detail = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _component_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _component_id_type component_id;
  using _display_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _display_name_type display_name;
  using _state_type =
    uint8_t;
  _state_type state;
  using _required_type =
    bool;
  _required_type required;
  using _present_type =
    bool;
  _present_type present;
  using _observed_rate_hz_type =
    double;
  _observed_rate_hz_type observed_rate_hz;
  using _message_age_sec_type =
    double;
  _message_age_sec_type message_age_sec;
  using _message_count_type =
    uint64_t;
  _message_count_type message_count;
  using _missing_topics_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _missing_topics_type missing_topics;
  using _missing_frames_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _missing_frames_type missing_frames;
  using _missing_nodes_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _missing_nodes_type missing_nodes;
  using _lifecycle_failures_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _lifecycle_failures_type lifecycle_failures;
  using _condition_failures_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _condition_failures_type condition_failures;
  using _warnings_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _warnings_type warnings;
  using _errors_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _errors_type errors;
  using _detail_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _detail_type detail;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__component_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->component_id = _arg;
    return *this;
  }
  Type & set__display_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->display_name = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__required(
    const bool & _arg)
  {
    this->required = _arg;
    return *this;
  }
  Type & set__present(
    const bool & _arg)
  {
    this->present = _arg;
    return *this;
  }
  Type & set__observed_rate_hz(
    const double & _arg)
  {
    this->observed_rate_hz = _arg;
    return *this;
  }
  Type & set__message_age_sec(
    const double & _arg)
  {
    this->message_age_sec = _arg;
    return *this;
  }
  Type & set__message_count(
    const uint64_t & _arg)
  {
    this->message_count = _arg;
    return *this;
  }
  Type & set__missing_topics(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->missing_topics = _arg;
    return *this;
  }
  Type & set__missing_frames(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->missing_frames = _arg;
    return *this;
  }
  Type & set__missing_nodes(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->missing_nodes = _arg;
    return *this;
  }
  Type & set__lifecycle_failures(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->lifecycle_failures = _arg;
    return *this;
  }
  Type & set__condition_failures(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->condition_failures = _arg;
    return *this;
  }
  Type & set__warnings(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->warnings = _arg;
    return *this;
  }
  Type & set__errors(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->errors = _arg;
    return *this;
  }
  Type & set__detail(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->detail = _arg;
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
    agt_interfaces::msg::ComponentHealth_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::ComponentHealth_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::ComponentHealth_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::ComponentHealth_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::ComponentHealth_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::ComponentHealth_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::ComponentHealth_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::ComponentHealth_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::ComponentHealth_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::ComponentHealth_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__ComponentHealth
    std::shared_ptr<agt_interfaces::msg::ComponentHealth_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__ComponentHealth
    std::shared_ptr<agt_interfaces::msg::ComponentHealth_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ComponentHealth_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->component_id != other.component_id) {
      return false;
    }
    if (this->display_name != other.display_name) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->required != other.required) {
      return false;
    }
    if (this->present != other.present) {
      return false;
    }
    if (this->observed_rate_hz != other.observed_rate_hz) {
      return false;
    }
    if (this->message_age_sec != other.message_age_sec) {
      return false;
    }
    if (this->message_count != other.message_count) {
      return false;
    }
    if (this->missing_topics != other.missing_topics) {
      return false;
    }
    if (this->missing_frames != other.missing_frames) {
      return false;
    }
    if (this->missing_nodes != other.missing_nodes) {
      return false;
    }
    if (this->lifecycle_failures != other.lifecycle_failures) {
      return false;
    }
    if (this->condition_failures != other.condition_failures) {
      return false;
    }
    if (this->warnings != other.warnings) {
      return false;
    }
    if (this->errors != other.errors) {
      return false;
    }
    if (this->detail != other.detail) {
      return false;
    }
    return true;
  }
  bool operator!=(const ComponentHealth_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ComponentHealth_

// alias to use template instance with default allocator
using ComponentHealth =
  agt_interfaces::msg::ComponentHealth_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ComponentHealth_<ContainerAllocator>::STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ComponentHealth_<ContainerAllocator>::STATE_OK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ComponentHealth_<ContainerAllocator>::STATE_WARN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ComponentHealth_<ContainerAllocator>::STATE_ERROR;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__STRUCT_HPP_
