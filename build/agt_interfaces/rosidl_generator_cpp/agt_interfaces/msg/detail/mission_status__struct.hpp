// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/MissionStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__STRUCT_HPP_

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
# define DEPRECATED__agt_interfaces__msg__MissionStatus __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__MissionStatus __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MissionStatus_
{
  using Type = MissionStatus_<ContainerAllocator>;

  explicit MissionStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->mission_id = "";
      this->mission_version = "";
      this->content_sha256 = "";
      this->map_id = "";
      this->map_version_id = "";
      this->map_manifest_sha256 = "";
      this->current_step_index = 0ul;
      this->total_steps = 0ul;
      this->current_step_id = "";
      this->current_step_type = 0;
      this->current_waypoint = 0ul;
      this->total_waypoints = 0ul;
      this->step_elapsed_s = 0.0;
      this->step_remaining_s = 0.0;
      this->error_code = 0;
      this->message = "";
    }
  }

  explicit MissionStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    mission_id(_alloc),
    mission_version(_alloc),
    content_sha256(_alloc),
    map_id(_alloc),
    map_version_id(_alloc),
    map_manifest_sha256(_alloc),
    current_step_id(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->mission_id = "";
      this->mission_version = "";
      this->content_sha256 = "";
      this->map_id = "";
      this->map_version_id = "";
      this->map_manifest_sha256 = "";
      this->current_step_index = 0ul;
      this->total_steps = 0ul;
      this->current_step_id = "";
      this->current_step_type = 0;
      this->current_waypoint = 0ul;
      this->total_waypoints = 0ul;
      this->step_elapsed_s = 0.0;
      this->step_remaining_s = 0.0;
      this->error_code = 0;
      this->message = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _state_type =
    uint8_t;
  _state_type state;
  using _mission_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_id_type mission_id;
  using _mission_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_version_type mission_version;
  using _content_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _content_sha256_type content_sha256;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_version_id_type map_version_id;
  using _map_manifest_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_manifest_sha256_type map_manifest_sha256;
  using _current_step_index_type =
    uint32_t;
  _current_step_index_type current_step_index;
  using _total_steps_type =
    uint32_t;
  _total_steps_type total_steps;
  using _current_step_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _current_step_id_type current_step_id;
  using _current_step_type_type =
    uint8_t;
  _current_step_type_type current_step_type;
  using _current_waypoint_type =
    uint32_t;
  _current_waypoint_type current_waypoint;
  using _total_waypoints_type =
    uint32_t;
  _total_waypoints_type total_waypoints;
  using _step_elapsed_s_type =
    double;
  _step_elapsed_s_type step_elapsed_s;
  using _step_remaining_s_type =
    double;
  _step_remaining_s_type step_remaining_s;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;
  using _blocker_codes_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _blocker_codes_type blocker_codes;
  using _blocker_messages_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _blocker_messages_type blocker_messages;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__mission_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mission_id = _arg;
    return *this;
  }
  Type & set__mission_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mission_version = _arg;
    return *this;
  }
  Type & set__content_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->content_sha256 = _arg;
    return *this;
  }
  Type & set__map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_id = _arg;
    return *this;
  }
  Type & set__map_version_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_version_id = _arg;
    return *this;
  }
  Type & set__map_manifest_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_manifest_sha256 = _arg;
    return *this;
  }
  Type & set__current_step_index(
    const uint32_t & _arg)
  {
    this->current_step_index = _arg;
    return *this;
  }
  Type & set__total_steps(
    const uint32_t & _arg)
  {
    this->total_steps = _arg;
    return *this;
  }
  Type & set__current_step_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->current_step_id = _arg;
    return *this;
  }
  Type & set__current_step_type(
    const uint8_t & _arg)
  {
    this->current_step_type = _arg;
    return *this;
  }
  Type & set__current_waypoint(
    const uint32_t & _arg)
  {
    this->current_waypoint = _arg;
    return *this;
  }
  Type & set__total_waypoints(
    const uint32_t & _arg)
  {
    this->total_waypoints = _arg;
    return *this;
  }
  Type & set__step_elapsed_s(
    const double & _arg)
  {
    this->step_elapsed_s = _arg;
    return *this;
  }
  Type & set__step_remaining_s(
    const double & _arg)
  {
    this->step_remaining_s = _arg;
    return *this;
  }
  Type & set__error_code(
    const uint16_t & _arg)
  {
    this->error_code = _arg;
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
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t STATE_IDLE =
    0u;
  static constexpr uint8_t STATE_VALIDATING =
    1u;
  static constexpr uint8_t STATE_RUNNING =
    2u;
  static constexpr uint8_t STATE_WAITING_DURATION =
    3u;
  static constexpr uint8_t STATE_WAITING_EVENT =
    4u;
  static constexpr uint8_t STATE_PAUSING =
    5u;
  static constexpr uint8_t STATE_PAUSED =
    6u;
  static constexpr uint8_t STATE_RESUMING =
    7u;
  static constexpr uint8_t STATE_CANCELING =
    8u;
  static constexpr uint8_t STATE_SUCCEEDED =
    9u;
  static constexpr uint8_t STATE_FAILED =
    10u;
  static constexpr uint8_t STATE_CANCELED =
    11u;
  static constexpr uint8_t STATE_INTERRUPTED =
    12u;
  static constexpr uint8_t STEP_UNKNOWN =
    0u;
  static constexpr uint8_t STEP_WAYPOINT_TASK =
    1u;
  static constexpr uint8_t STEP_WAIT_DURATION =
    2u;
  static constexpr uint8_t STEP_WAIT_EVENT =
    3u;
  static constexpr uint16_t ERROR_NONE =
    0u;
  static constexpr uint16_t ERROR_INVALID_MISSION =
    1u;
  static constexpr uint16_t ERROR_MAP_MISMATCH =
    2u;
  static constexpr uint16_t ERROR_READINESS_LOST =
    3u;
  static constexpr uint16_t ERROR_LOCALIZATION_LOST =
    4u;
  static constexpr uint16_t ERROR_CHILD_REJECTED =
    5u;
  static constexpr uint16_t ERROR_CHILD_FAILED =
    6u;
  static constexpr uint16_t ERROR_EVENT_TIMEOUT =
    7u;
  static constexpr uint16_t ERROR_CANCELED =
    8u;
  static constexpr uint16_t ERROR_RESUME_BLOCKED =
    9u;
  static constexpr uint16_t ERROR_INTERNAL =
    255u;

  // pointer types
  using RawPtr =
    agt_interfaces::msg::MissionStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::MissionStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::MissionStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::MissionStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::MissionStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::MissionStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::MissionStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::MissionStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::MissionStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::MissionStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__MissionStatus
    std::shared_ptr<agt_interfaces::msg::MissionStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__MissionStatus
    std::shared_ptr<agt_interfaces::msg::MissionStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MissionStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->mission_id != other.mission_id) {
      return false;
    }
    if (this->mission_version != other.mission_version) {
      return false;
    }
    if (this->content_sha256 != other.content_sha256) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->map_version_id != other.map_version_id) {
      return false;
    }
    if (this->map_manifest_sha256 != other.map_manifest_sha256) {
      return false;
    }
    if (this->current_step_index != other.current_step_index) {
      return false;
    }
    if (this->total_steps != other.total_steps) {
      return false;
    }
    if (this->current_step_id != other.current_step_id) {
      return false;
    }
    if (this->current_step_type != other.current_step_type) {
      return false;
    }
    if (this->current_waypoint != other.current_waypoint) {
      return false;
    }
    if (this->total_waypoints != other.total_waypoints) {
      return false;
    }
    if (this->step_elapsed_s != other.step_elapsed_s) {
      return false;
    }
    if (this->step_remaining_s != other.step_remaining_s) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->blocker_codes != other.blocker_codes) {
      return false;
    }
    if (this->blocker_messages != other.blocker_messages) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const MissionStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MissionStatus_

// alias to use template instance with default allocator
using MissionStatus =
  agt_interfaces::msg::MissionStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_VALIDATING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_RUNNING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_WAITING_DURATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_WAITING_EVENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_PAUSING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_PAUSED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_RESUMING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_CANCELING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_SUCCEEDED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_FAILED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_CANCELED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STATE_INTERRUPTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STEP_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STEP_WAYPOINT_TASK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STEP_WAIT_DURATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::STEP_WAIT_EVENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_INVALID_MISSION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_MAP_MISMATCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_READINESS_LOST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_LOCALIZATION_LOST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_CHILD_REJECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_CHILD_FAILED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_EVENT_TIMEOUT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_CANCELED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_RESUME_BLOCKED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MissionStatus_<ContainerAllocator>::ERROR_INTERNAL;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__STRUCT_HPP_
