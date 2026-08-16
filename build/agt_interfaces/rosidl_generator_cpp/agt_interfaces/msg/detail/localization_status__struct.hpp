// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/LocalizationStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__STRUCT_HPP_

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
// Member 'global_pose'
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__msg__LocalizationStatus __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__LocalizationStatus __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LocalizationStatus_
{
  using Type = LocalizationStatus_<ContainerAllocator>;

  explicit LocalizationStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    global_pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->pose_valid = false;
      this->localization_accepted = false;
      this->has_converged = false;
      this->ambiguous_result = false;
      this->status_stale = false;
      this->error_code = 0;
      this->backend = "";
      this->candidate_source = "";
      this->candidate_id = "";
      this->map_id = "";
      this->map_hash = "";
      this->correction_generation = 0ull;
      this->fitness_score = 0.0;
      this->overlap_ratio = 0.0;
      this->inlier_ratio = 0.0;
      this->ambiguity_score = 0.0;
      this->translation_innovation = 0.0;
      this->yaw_innovation = 0.0;
      this->runtime_ms = 0.0;
      this->tested_candidates = 0ul;
      this->total_candidates = 0ul;
      this->consecutive_successes = 0ul;
      this->consecutive_failures = 0ul;
      this->message = "";
    }
  }

  explicit LocalizationStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    backend(_alloc),
    candidate_source(_alloc),
    candidate_id(_alloc),
    map_id(_alloc),
    map_hash(_alloc),
    global_pose(_alloc, _init),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->pose_valid = false;
      this->localization_accepted = false;
      this->has_converged = false;
      this->ambiguous_result = false;
      this->status_stale = false;
      this->error_code = 0;
      this->backend = "";
      this->candidate_source = "";
      this->candidate_id = "";
      this->map_id = "";
      this->map_hash = "";
      this->correction_generation = 0ull;
      this->fitness_score = 0.0;
      this->overlap_ratio = 0.0;
      this->inlier_ratio = 0.0;
      this->ambiguity_score = 0.0;
      this->translation_innovation = 0.0;
      this->yaw_innovation = 0.0;
      this->runtime_ms = 0.0;
      this->tested_candidates = 0ul;
      this->total_candidates = 0ul;
      this->consecutive_successes = 0ul;
      this->consecutive_failures = 0ul;
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
  using _pose_valid_type =
    bool;
  _pose_valid_type pose_valid;
  using _localization_accepted_type =
    bool;
  _localization_accepted_type localization_accepted;
  using _has_converged_type =
    bool;
  _has_converged_type has_converged;
  using _ambiguous_result_type =
    bool;
  _ambiguous_result_type ambiguous_result;
  using _status_stale_type =
    bool;
  _status_stale_type status_stale;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;
  using _backend_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _backend_type backend;
  using _candidate_source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _candidate_source_type candidate_source;
  using _candidate_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _candidate_id_type candidate_id;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _map_hash_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_hash_type map_hash;
  using _correction_generation_type =
    uint64_t;
  _correction_generation_type correction_generation;
  using _global_pose_type =
    geometry_msgs::msg::PoseWithCovarianceStamped_<ContainerAllocator>;
  _global_pose_type global_pose;
  using _fitness_score_type =
    double;
  _fitness_score_type fitness_score;
  using _overlap_ratio_type =
    double;
  _overlap_ratio_type overlap_ratio;
  using _inlier_ratio_type =
    double;
  _inlier_ratio_type inlier_ratio;
  using _ambiguity_score_type =
    double;
  _ambiguity_score_type ambiguity_score;
  using _translation_innovation_type =
    double;
  _translation_innovation_type translation_innovation;
  using _yaw_innovation_type =
    double;
  _yaw_innovation_type yaw_innovation;
  using _runtime_ms_type =
    double;
  _runtime_ms_type runtime_ms;
  using _tested_candidates_type =
    uint32_t;
  _tested_candidates_type tested_candidates;
  using _total_candidates_type =
    uint32_t;
  _total_candidates_type total_candidates;
  using _consecutive_successes_type =
    uint32_t;
  _consecutive_successes_type consecutive_successes;
  using _consecutive_failures_type =
    uint32_t;
  _consecutive_failures_type consecutive_failures;
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
  Type & set__pose_valid(
    const bool & _arg)
  {
    this->pose_valid = _arg;
    return *this;
  }
  Type & set__localization_accepted(
    const bool & _arg)
  {
    this->localization_accepted = _arg;
    return *this;
  }
  Type & set__has_converged(
    const bool & _arg)
  {
    this->has_converged = _arg;
    return *this;
  }
  Type & set__ambiguous_result(
    const bool & _arg)
  {
    this->ambiguous_result = _arg;
    return *this;
  }
  Type & set__status_stale(
    const bool & _arg)
  {
    this->status_stale = _arg;
    return *this;
  }
  Type & set__error_code(
    const uint16_t & _arg)
  {
    this->error_code = _arg;
    return *this;
  }
  Type & set__backend(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->backend = _arg;
    return *this;
  }
  Type & set__candidate_source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->candidate_source = _arg;
    return *this;
  }
  Type & set__candidate_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->candidate_id = _arg;
    return *this;
  }
  Type & set__map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_id = _arg;
    return *this;
  }
  Type & set__map_hash(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_hash = _arg;
    return *this;
  }
  Type & set__correction_generation(
    const uint64_t & _arg)
  {
    this->correction_generation = _arg;
    return *this;
  }
  Type & set__global_pose(
    const geometry_msgs::msg::PoseWithCovarianceStamped_<ContainerAllocator> & _arg)
  {
    this->global_pose = _arg;
    return *this;
  }
  Type & set__fitness_score(
    const double & _arg)
  {
    this->fitness_score = _arg;
    return *this;
  }
  Type & set__overlap_ratio(
    const double & _arg)
  {
    this->overlap_ratio = _arg;
    return *this;
  }
  Type & set__inlier_ratio(
    const double & _arg)
  {
    this->inlier_ratio = _arg;
    return *this;
  }
  Type & set__ambiguity_score(
    const double & _arg)
  {
    this->ambiguity_score = _arg;
    return *this;
  }
  Type & set__translation_innovation(
    const double & _arg)
  {
    this->translation_innovation = _arg;
    return *this;
  }
  Type & set__yaw_innovation(
    const double & _arg)
  {
    this->yaw_innovation = _arg;
    return *this;
  }
  Type & set__runtime_ms(
    const double & _arg)
  {
    this->runtime_ms = _arg;
    return *this;
  }
  Type & set__tested_candidates(
    const uint32_t & _arg)
  {
    this->tested_candidates = _arg;
    return *this;
  }
  Type & set__total_candidates(
    const uint32_t & _arg)
  {
    this->total_candidates = _arg;
    return *this;
  }
  Type & set__consecutive_successes(
    const uint32_t & _arg)
  {
    this->consecutive_successes = _arg;
    return *this;
  }
  Type & set__consecutive_failures(
    const uint32_t & _arg)
  {
    this->consecutive_failures = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t STATE_UNINITIALIZED =
    0u;
  static constexpr uint8_t STATE_SEARCHING =
    1u;
  static constexpr uint8_t STATE_VERIFYING =
    2u;
  static constexpr uint8_t STATE_TRACKING =
    3u;
  static constexpr uint8_t STATE_DEGRADED =
    4u;
  static constexpr uint8_t STATE_RECOVERING =
    5u;
  static constexpr uint8_t STATE_LOST =
    6u;
  static constexpr uint8_t STATE_ERROR =
    7u;
  static constexpr uint16_t ERROR_NONE =
    0u;
  static constexpr uint16_t ERROR_MAP_NOT_READY =
    100u;
  static constexpr uint16_t ERROR_SCAN_TOO_SMALL =
    101u;
  static constexpr uint16_t ERROR_BACKEND_FAILED =
    102u;
  static constexpr uint16_t ERROR_FITNESS_REJECTED =
    103u;
  static constexpr uint16_t ERROR_INVALID_INITIAL_GUESS =
    104u;
  static constexpr uint16_t ERROR_INVALID_REQUEST =
    105u;
  static constexpr uint16_t ERROR_TIMEOUT =
    106u;
  static constexpr uint16_t ERROR_CANCELED =
    107u;
  static constexpr uint16_t ERROR_AMBIGUOUS_RESULT =
    108u;
  static constexpr uint16_t ERROR_STALE_STATUS =
    109u;
  static constexpr uint16_t ERROR_TF_UNAVAILABLE =
    110u;
  static constexpr uint16_t ERROR_MAP_HASH_MISMATCH =
    111u;
  static constexpr uint16_t ERROR_NO_CANDIDATES =
    112u;
  static constexpr uint16_t ERROR_STALE_SCAN =
    113u;
  static constexpr uint16_t ERROR_INVALID_SCAN_TIMESTAMP =
    114u;

  // pointer types
  using RawPtr =
    agt_interfaces::msg::LocalizationStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::LocalizationStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::LocalizationStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::LocalizationStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::LocalizationStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::LocalizationStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::LocalizationStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::LocalizationStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::LocalizationStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::LocalizationStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__LocalizationStatus
    std::shared_ptr<agt_interfaces::msg::LocalizationStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__LocalizationStatus
    std::shared_ptr<agt_interfaces::msg::LocalizationStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LocalizationStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->pose_valid != other.pose_valid) {
      return false;
    }
    if (this->localization_accepted != other.localization_accepted) {
      return false;
    }
    if (this->has_converged != other.has_converged) {
      return false;
    }
    if (this->ambiguous_result != other.ambiguous_result) {
      return false;
    }
    if (this->status_stale != other.status_stale) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->backend != other.backend) {
      return false;
    }
    if (this->candidate_source != other.candidate_source) {
      return false;
    }
    if (this->candidate_id != other.candidate_id) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->map_hash != other.map_hash) {
      return false;
    }
    if (this->correction_generation != other.correction_generation) {
      return false;
    }
    if (this->global_pose != other.global_pose) {
      return false;
    }
    if (this->fitness_score != other.fitness_score) {
      return false;
    }
    if (this->overlap_ratio != other.overlap_ratio) {
      return false;
    }
    if (this->inlier_ratio != other.inlier_ratio) {
      return false;
    }
    if (this->ambiguity_score != other.ambiguity_score) {
      return false;
    }
    if (this->translation_innovation != other.translation_innovation) {
      return false;
    }
    if (this->yaw_innovation != other.yaw_innovation) {
      return false;
    }
    if (this->runtime_ms != other.runtime_ms) {
      return false;
    }
    if (this->tested_candidates != other.tested_candidates) {
      return false;
    }
    if (this->total_candidates != other.total_candidates) {
      return false;
    }
    if (this->consecutive_successes != other.consecutive_successes) {
      return false;
    }
    if (this->consecutive_failures != other.consecutive_failures) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const LocalizationStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LocalizationStatus_

// alias to use template instance with default allocator
using LocalizationStatus =
  agt_interfaces::msg::LocalizationStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationStatus_<ContainerAllocator>::STATE_UNINITIALIZED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationStatus_<ContainerAllocator>::STATE_SEARCHING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationStatus_<ContainerAllocator>::STATE_VERIFYING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationStatus_<ContainerAllocator>::STATE_TRACKING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationStatus_<ContainerAllocator>::STATE_DEGRADED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationStatus_<ContainerAllocator>::STATE_RECOVERING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationStatus_<ContainerAllocator>::STATE_LOST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationStatus_<ContainerAllocator>::STATE_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_MAP_NOT_READY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_SCAN_TOO_SMALL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_BACKEND_FAILED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_FITNESS_REJECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_INVALID_INITIAL_GUESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_INVALID_REQUEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_TIMEOUT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_CANCELED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_AMBIGUOUS_RESULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_STALE_STATUS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_TF_UNAVAILABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_MAP_HASH_MISMATCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_NO_CANDIDATES;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_STALE_SCAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LocalizationStatus_<ContainerAllocator>::ERROR_INVALID_SCAN_TIMESTAMP;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__STRUCT_HPP_
