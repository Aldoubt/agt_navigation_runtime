// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/BagSessionSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__STRUCT_HPP_

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
# define DEPRECATED__agt_interfaces__msg__BagSessionSummary __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__BagSessionSummary __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BagSessionSummary_
{
  using Type = BagSessionSummary_<ContainerAllocator>;

  explicit BagSessionSummary_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->bag_id = "";
      this->experiment_id = "";
      this->profile_id = "";
      this->relative_uri = "";
      this->complete = false;
      this->simulation = false;
      this->playback_rate = 0.0;
      this->storage_bytes = 0ull;
      this->started_at = "";
      this->updated_at = "";
      this->message = "";
      this->process_id = 0ll;
      this->message_count = 0ull;
      this->storage_identifier = "";
      this->mapping_input_ready = false;
      this->contains_mapping_outputs = false;
      this->contains_navigation_outputs = false;
    }
  }

  explicit BagSessionSummary_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    bag_id(_alloc),
    experiment_id(_alloc),
    profile_id(_alloc),
    relative_uri(_alloc),
    started_at(_alloc),
    updated_at(_alloc),
    message(_alloc),
    storage_identifier(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->bag_id = "";
      this->experiment_id = "";
      this->profile_id = "";
      this->relative_uri = "";
      this->complete = false;
      this->simulation = false;
      this->playback_rate = 0.0;
      this->storage_bytes = 0ull;
      this->started_at = "";
      this->updated_at = "";
      this->message = "";
      this->process_id = 0ll;
      this->message_count = 0ull;
      this->storage_identifier = "";
      this->mapping_input_ready = false;
      this->contains_mapping_outputs = false;
      this->contains_navigation_outputs = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _state_type =
    uint8_t;
  _state_type state;
  using _bag_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _bag_id_type bag_id;
  using _experiment_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _experiment_id_type experiment_id;
  using _profile_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _profile_id_type profile_id;
  using _relative_uri_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _relative_uri_type relative_uri;
  using _complete_type =
    bool;
  _complete_type complete;
  using _simulation_type =
    bool;
  _simulation_type simulation;
  using _playback_rate_type =
    double;
  _playback_rate_type playback_rate;
  using _storage_bytes_type =
    uint64_t;
  _storage_bytes_type storage_bytes;
  using _started_at_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _started_at_type started_at;
  using _updated_at_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _updated_at_type updated_at;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _process_id_type =
    int64_t;
  _process_id_type process_id;
  using _message_count_type =
    uint64_t;
  _message_count_type message_count;
  using _storage_identifier_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _storage_identifier_type storage_identifier;
  using _mapping_input_ready_type =
    bool;
  _mapping_input_ready_type mapping_input_ready;
  using _contains_mapping_outputs_type =
    bool;
  _contains_mapping_outputs_type contains_mapping_outputs;
  using _contains_navigation_outputs_type =
    bool;
  _contains_navigation_outputs_type contains_navigation_outputs;

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
  Type & set__bag_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->bag_id = _arg;
    return *this;
  }
  Type & set__experiment_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->experiment_id = _arg;
    return *this;
  }
  Type & set__profile_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->profile_id = _arg;
    return *this;
  }
  Type & set__relative_uri(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->relative_uri = _arg;
    return *this;
  }
  Type & set__complete(
    const bool & _arg)
  {
    this->complete = _arg;
    return *this;
  }
  Type & set__simulation(
    const bool & _arg)
  {
    this->simulation = _arg;
    return *this;
  }
  Type & set__playback_rate(
    const double & _arg)
  {
    this->playback_rate = _arg;
    return *this;
  }
  Type & set__storage_bytes(
    const uint64_t & _arg)
  {
    this->storage_bytes = _arg;
    return *this;
  }
  Type & set__started_at(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->started_at = _arg;
    return *this;
  }
  Type & set__updated_at(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->updated_at = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__process_id(
    const int64_t & _arg)
  {
    this->process_id = _arg;
    return *this;
  }
  Type & set__message_count(
    const uint64_t & _arg)
  {
    this->message_count = _arg;
    return *this;
  }
  Type & set__storage_identifier(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->storage_identifier = _arg;
    return *this;
  }
  Type & set__mapping_input_ready(
    const bool & _arg)
  {
    this->mapping_input_ready = _arg;
    return *this;
  }
  Type & set__contains_mapping_outputs(
    const bool & _arg)
  {
    this->contains_mapping_outputs = _arg;
    return *this;
  }
  Type & set__contains_navigation_outputs(
    const bool & _arg)
  {
    this->contains_navigation_outputs = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t STATE_UNKNOWN =
    0u;
  static constexpr uint8_t STATE_IDLE =
    1u;
  static constexpr uint8_t STATE_RECORDING =
    2u;
  static constexpr uint8_t STATE_PLAYING =
    3u;
  static constexpr uint8_t STATE_COMPLETED =
    4u;
  static constexpr uint8_t STATE_INTERRUPTED =
    5u;
  static constexpr uint8_t STATE_ERROR =
    6u;

  // pointer types
  using RawPtr =
    agt_interfaces::msg::BagSessionSummary_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::BagSessionSummary_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::BagSessionSummary_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::BagSessionSummary_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::BagSessionSummary_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::BagSessionSummary_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::BagSessionSummary_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::BagSessionSummary_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::BagSessionSummary_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::BagSessionSummary_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__BagSessionSummary
    std::shared_ptr<agt_interfaces::msg::BagSessionSummary_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__BagSessionSummary
    std::shared_ptr<agt_interfaces::msg::BagSessionSummary_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BagSessionSummary_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->bag_id != other.bag_id) {
      return false;
    }
    if (this->experiment_id != other.experiment_id) {
      return false;
    }
    if (this->profile_id != other.profile_id) {
      return false;
    }
    if (this->relative_uri != other.relative_uri) {
      return false;
    }
    if (this->complete != other.complete) {
      return false;
    }
    if (this->simulation != other.simulation) {
      return false;
    }
    if (this->playback_rate != other.playback_rate) {
      return false;
    }
    if (this->storage_bytes != other.storage_bytes) {
      return false;
    }
    if (this->started_at != other.started_at) {
      return false;
    }
    if (this->updated_at != other.updated_at) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->process_id != other.process_id) {
      return false;
    }
    if (this->message_count != other.message_count) {
      return false;
    }
    if (this->storage_identifier != other.storage_identifier) {
      return false;
    }
    if (this->mapping_input_ready != other.mapping_input_ready) {
      return false;
    }
    if (this->contains_mapping_outputs != other.contains_mapping_outputs) {
      return false;
    }
    if (this->contains_navigation_outputs != other.contains_navigation_outputs) {
      return false;
    }
    return true;
  }
  bool operator!=(const BagSessionSummary_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BagSessionSummary_

// alias to use template instance with default allocator
using BagSessionSummary =
  agt_interfaces::msg::BagSessionSummary_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BagSessionSummary_<ContainerAllocator>::STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BagSessionSummary_<ContainerAllocator>::STATE_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BagSessionSummary_<ContainerAllocator>::STATE_RECORDING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BagSessionSummary_<ContainerAllocator>::STATE_PLAYING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BagSessionSummary_<ContainerAllocator>::STATE_COMPLETED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BagSessionSummary_<ContainerAllocator>::STATE_INTERRUPTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BagSessionSummary_<ContainerAllocator>::STATE_ERROR;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__STRUCT_HPP_
