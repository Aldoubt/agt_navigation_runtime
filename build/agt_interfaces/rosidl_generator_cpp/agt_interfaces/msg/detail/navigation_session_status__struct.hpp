// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/NavigationSessionStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__STRUCT_HPP_

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
// Member 'started_at'
// Member 'updated_at'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__msg__NavigationSessionStatus __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__NavigationSessionStatus __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct NavigationSessionStatus_
{
  using Type = NavigationSessionStatus_<ContainerAllocator>;

  explicit NavigationSessionStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    started_at(_init),
    updated_at(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->session_id = "";
      this->client_request_id = "";
      this->map_id = "";
      this->map_version_id = "";
      this->task_group_id = "";
      this->task_revision = 0ul;
      this->task_content_sha256 = "";
      this->state = 0;
      this->loop_index = 0ul;
      this->current_waypoint = 0ul;
      this->total_waypoints = 0ul;
      this->error_code = 0;
      this->blocker_code = "";
      this->operator_message = "";
      this->technical_message = "";
      this->terminal = false;
      this->success = false;
    }
  }

  explicit NavigationSessionStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    session_id(_alloc),
    client_request_id(_alloc),
    map_id(_alloc),
    map_version_id(_alloc),
    task_group_id(_alloc),
    task_content_sha256(_alloc),
    blocker_code(_alloc),
    operator_message(_alloc),
    technical_message(_alloc),
    started_at(_alloc, _init),
    updated_at(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->session_id = "";
      this->client_request_id = "";
      this->map_id = "";
      this->map_version_id = "";
      this->task_group_id = "";
      this->task_revision = 0ul;
      this->task_content_sha256 = "";
      this->state = 0;
      this->loop_index = 0ul;
      this->current_waypoint = 0ul;
      this->total_waypoints = 0ul;
      this->error_code = 0;
      this->blocker_code = "";
      this->operator_message = "";
      this->technical_message = "";
      this->terminal = false;
      this->success = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _session_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _session_id_type session_id;
  using _client_request_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _client_request_id_type client_request_id;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_version_id_type map_version_id;
  using _task_group_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _task_group_id_type task_group_id;
  using _task_revision_type =
    uint32_t;
  _task_revision_type task_revision;
  using _task_content_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _task_content_sha256_type task_content_sha256;
  using _state_type =
    uint8_t;
  _state_type state;
  using _loop_index_type =
    uint32_t;
  _loop_index_type loop_index;
  using _current_waypoint_type =
    uint32_t;
  _current_waypoint_type current_waypoint;
  using _total_waypoints_type =
    uint32_t;
  _total_waypoints_type total_waypoints;
  using _missed_waypoints_type =
    std::vector<uint32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint32_t>>;
  _missed_waypoints_type missed_waypoints;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;
  using _blocker_code_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _blocker_code_type blocker_code;
  using _operator_message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _operator_message_type operator_message;
  using _technical_message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _technical_message_type technical_message;
  using _started_at_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _started_at_type started_at;
  using _updated_at_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _updated_at_type updated_at;
  using _terminal_type =
    bool;
  _terminal_type terminal;
  using _success_type =
    bool;
  _success_type success;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__session_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->session_id = _arg;
    return *this;
  }
  Type & set__client_request_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->client_request_id = _arg;
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
  Type & set__task_group_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->task_group_id = _arg;
    return *this;
  }
  Type & set__task_revision(
    const uint32_t & _arg)
  {
    this->task_revision = _arg;
    return *this;
  }
  Type & set__task_content_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->task_content_sha256 = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__loop_index(
    const uint32_t & _arg)
  {
    this->loop_index = _arg;
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
  Type & set__missed_waypoints(
    const std::vector<uint32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint32_t>> & _arg)
  {
    this->missed_waypoints = _arg;
    return *this;
  }
  Type & set__error_code(
    const uint16_t & _arg)
  {
    this->error_code = _arg;
    return *this;
  }
  Type & set__blocker_code(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->blocker_code = _arg;
    return *this;
  }
  Type & set__operator_message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->operator_message = _arg;
    return *this;
  }
  Type & set__technical_message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->technical_message = _arg;
    return *this;
  }
  Type & set__started_at(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->started_at = _arg;
    return *this;
  }
  Type & set__updated_at(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->updated_at = _arg;
    return *this;
  }
  Type & set__terminal(
    const bool & _arg)
  {
    this->terminal = _arg;
    return *this;
  }
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t STATE_IDLE =
    0u;
  static constexpr uint8_t STATE_VALIDATING =
    1u;
  static constexpr uint8_t STATE_REJECTED =
    2u;
  static constexpr uint8_t STATE_ACCEPTED =
    3u;
  static constexpr uint8_t STATE_RUNNING =
    4u;
  static constexpr uint8_t STATE_CANCELING =
    5u;
  static constexpr uint8_t STATE_SUCCEEDED =
    6u;
  static constexpr uint8_t STATE_FAILED =
    7u;
  static constexpr uint8_t STATE_CANCELED =
    8u;

  // pointer types
  using RawPtr =
    agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__NavigationSessionStatus
    std::shared_ptr<agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__NavigationSessionStatus
    std::shared_ptr<agt_interfaces::msg::NavigationSessionStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NavigationSessionStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->session_id != other.session_id) {
      return false;
    }
    if (this->client_request_id != other.client_request_id) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->map_version_id != other.map_version_id) {
      return false;
    }
    if (this->task_group_id != other.task_group_id) {
      return false;
    }
    if (this->task_revision != other.task_revision) {
      return false;
    }
    if (this->task_content_sha256 != other.task_content_sha256) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->loop_index != other.loop_index) {
      return false;
    }
    if (this->current_waypoint != other.current_waypoint) {
      return false;
    }
    if (this->total_waypoints != other.total_waypoints) {
      return false;
    }
    if (this->missed_waypoints != other.missed_waypoints) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->blocker_code != other.blocker_code) {
      return false;
    }
    if (this->operator_message != other.operator_message) {
      return false;
    }
    if (this->technical_message != other.technical_message) {
      return false;
    }
    if (this->started_at != other.started_at) {
      return false;
    }
    if (this->updated_at != other.updated_at) {
      return false;
    }
    if (this->terminal != other.terminal) {
      return false;
    }
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const NavigationSessionStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NavigationSessionStatus_

// alias to use template instance with default allocator
using NavigationSessionStatus =
  agt_interfaces::msg::NavigationSessionStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationSessionStatus_<ContainerAllocator>::STATE_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationSessionStatus_<ContainerAllocator>::STATE_VALIDATING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationSessionStatus_<ContainerAllocator>::STATE_REJECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationSessionStatus_<ContainerAllocator>::STATE_ACCEPTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationSessionStatus_<ContainerAllocator>::STATE_RUNNING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationSessionStatus_<ContainerAllocator>::STATE_CANCELING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationSessionStatus_<ContainerAllocator>::STATE_SUCCEEDED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationSessionStatus_<ContainerAllocator>::STATE_FAILED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t NavigationSessionStatus_<ContainerAllocator>::STATE_CANCELED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__STRUCT_HPP_
