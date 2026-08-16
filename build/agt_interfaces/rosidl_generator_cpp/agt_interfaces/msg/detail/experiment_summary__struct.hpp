// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/ExperimentSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__STRUCT_HPP_

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
# define DEPRECATED__agt_interfaces__msg__ExperimentSummary __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__ExperimentSummary __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ExperimentSummary_
{
  using Type = ExperimentSummary_<ContainerAllocator>;

  explicit ExperimentSummary_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->experiment_id = "";
      this->title = "";
      this->state = 0;
      this->created_at = "";
      this->start_time = "";
      this->end_time = "";
      this->platform_profile = "";
      this->map_id = "";
      this->map_version_id = "";
      this->map_hash = "";
      this->mission_id = "";
      this->mission_version = "";
      this->mission_sha256 = "";
      this->launch_profile = "";
      this->result_status = "";
      this->config_snapshot_count = 0ul;
      this->message = "";
    }
  }

  explicit ExperimentSummary_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    experiment_id(_alloc),
    title(_alloc),
    created_at(_alloc),
    start_time(_alloc),
    end_time(_alloc),
    platform_profile(_alloc),
    map_id(_alloc),
    map_version_id(_alloc),
    map_hash(_alloc),
    mission_id(_alloc),
    mission_version(_alloc),
    mission_sha256(_alloc),
    launch_profile(_alloc),
    result_status(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->experiment_id = "";
      this->title = "";
      this->state = 0;
      this->created_at = "";
      this->start_time = "";
      this->end_time = "";
      this->platform_profile = "";
      this->map_id = "";
      this->map_version_id = "";
      this->map_hash = "";
      this->mission_id = "";
      this->mission_version = "";
      this->mission_sha256 = "";
      this->launch_profile = "";
      this->result_status = "";
      this->config_snapshot_count = 0ul;
      this->message = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _experiment_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _experiment_id_type experiment_id;
  using _title_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _title_type title;
  using _state_type =
    uint8_t;
  _state_type state;
  using _created_at_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _created_at_type created_at;
  using _start_time_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _start_time_type start_time;
  using _end_time_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _end_time_type end_time;
  using _platform_profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _platform_profile_type platform_profile;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_version_id_type map_version_id;
  using _map_hash_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_hash_type map_hash;
  using _mission_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_id_type mission_id;
  using _mission_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_version_type mission_version;
  using _mission_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_sha256_type mission_sha256;
  using _launch_profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _launch_profile_type launch_profile;
  using _result_status_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _result_status_type result_status;
  using _config_snapshot_count_type =
    uint32_t;
  _config_snapshot_count_type config_snapshot_count;
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
  Type & set__experiment_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->experiment_id = _arg;
    return *this;
  }
  Type & set__title(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->title = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__created_at(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->created_at = _arg;
    return *this;
  }
  Type & set__start_time(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->start_time = _arg;
    return *this;
  }
  Type & set__end_time(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->end_time = _arg;
    return *this;
  }
  Type & set__platform_profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->platform_profile = _arg;
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
  Type & set__map_hash(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_hash = _arg;
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
  Type & set__mission_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mission_sha256 = _arg;
    return *this;
  }
  Type & set__launch_profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->launch_profile = _arg;
    return *this;
  }
  Type & set__result_status(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->result_status = _arg;
    return *this;
  }
  Type & set__config_snapshot_count(
    const uint32_t & _arg)
  {
    this->config_snapshot_count = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t STATE_UNKNOWN =
    0u;
  static constexpr uint8_t STATE_CREATED =
    1u;
  static constexpr uint8_t STATE_RUNNING =
    2u;
  static constexpr uint8_t STATE_COMPLETED =
    3u;
  static constexpr uint8_t STATE_INTERRUPTED =
    4u;
  static constexpr uint8_t STATE_INVALID =
    5u;

  // pointer types
  using RawPtr =
    agt_interfaces::msg::ExperimentSummary_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::ExperimentSummary_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::ExperimentSummary_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::ExperimentSummary_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::ExperimentSummary_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::ExperimentSummary_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::ExperimentSummary_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::ExperimentSummary_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::ExperimentSummary_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::ExperimentSummary_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__ExperimentSummary
    std::shared_ptr<agt_interfaces::msg::ExperimentSummary_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__ExperimentSummary
    std::shared_ptr<agt_interfaces::msg::ExperimentSummary_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExperimentSummary_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->experiment_id != other.experiment_id) {
      return false;
    }
    if (this->title != other.title) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->created_at != other.created_at) {
      return false;
    }
    if (this->start_time != other.start_time) {
      return false;
    }
    if (this->end_time != other.end_time) {
      return false;
    }
    if (this->platform_profile != other.platform_profile) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->map_version_id != other.map_version_id) {
      return false;
    }
    if (this->map_hash != other.map_hash) {
      return false;
    }
    if (this->mission_id != other.mission_id) {
      return false;
    }
    if (this->mission_version != other.mission_version) {
      return false;
    }
    if (this->mission_sha256 != other.mission_sha256) {
      return false;
    }
    if (this->launch_profile != other.launch_profile) {
      return false;
    }
    if (this->result_status != other.result_status) {
      return false;
    }
    if (this->config_snapshot_count != other.config_snapshot_count) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExperimentSummary_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExperimentSummary_

// alias to use template instance with default allocator
using ExperimentSummary =
  agt_interfaces::msg::ExperimentSummary_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ExperimentSummary_<ContainerAllocator>::STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ExperimentSummary_<ContainerAllocator>::STATE_CREATED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ExperimentSummary_<ContainerAllocator>::STATE_RUNNING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ExperimentSummary_<ContainerAllocator>::STATE_COMPLETED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ExperimentSummary_<ContainerAllocator>::STATE_INTERRUPTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ExperimentSummary_<ContainerAllocator>::STATE_INVALID;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__STRUCT_HPP_
