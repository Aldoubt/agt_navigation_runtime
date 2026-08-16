// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:action/Relocalize.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__STRUCT_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'initial_pose'
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__Relocalize_Goal __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__Relocalize_Goal __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Relocalize_Goal_
{
  using Type = Relocalize_Goal_<ContainerAllocator>;

  explicit Relocalize_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : initial_pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->use_initial_pose = false;
      this->use_last_valid_pose = false;
      this->use_configured_candidates = false;
      this->use_external_coarse_pose = false;
      this->max_candidates = 0ul;
      this->publish_debug = false;
      this->timeout_s = 0.0;
    }
  }

  explicit Relocalize_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : initial_pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->use_initial_pose = false;
      this->use_last_valid_pose = false;
      this->use_configured_candidates = false;
      this->use_external_coarse_pose = false;
      this->max_candidates = 0ul;
      this->publish_debug = false;
      this->timeout_s = 0.0;
    }
  }

  // field types and members
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _use_initial_pose_type =
    bool;
  _use_initial_pose_type use_initial_pose;
  using _initial_pose_type =
    geometry_msgs::msg::PoseWithCovarianceStamped_<ContainerAllocator>;
  _initial_pose_type initial_pose;
  using _use_last_valid_pose_type =
    bool;
  _use_last_valid_pose_type use_last_valid_pose;
  using _use_configured_candidates_type =
    bool;
  _use_configured_candidates_type use_configured_candidates;
  using _use_external_coarse_pose_type =
    bool;
  _use_external_coarse_pose_type use_external_coarse_pose;
  using _max_candidates_type =
    uint32_t;
  _max_candidates_type max_candidates;
  using _publish_debug_type =
    bool;
  _publish_debug_type publish_debug;
  using _timeout_s_type =
    double;
  _timeout_s_type timeout_s;

  // setters for named parameter idiom
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__use_initial_pose(
    const bool & _arg)
  {
    this->use_initial_pose = _arg;
    return *this;
  }
  Type & set__initial_pose(
    const geometry_msgs::msg::PoseWithCovarianceStamped_<ContainerAllocator> & _arg)
  {
    this->initial_pose = _arg;
    return *this;
  }
  Type & set__use_last_valid_pose(
    const bool & _arg)
  {
    this->use_last_valid_pose = _arg;
    return *this;
  }
  Type & set__use_configured_candidates(
    const bool & _arg)
  {
    this->use_configured_candidates = _arg;
    return *this;
  }
  Type & set__use_external_coarse_pose(
    const bool & _arg)
  {
    this->use_external_coarse_pose = _arg;
    return *this;
  }
  Type & set__max_candidates(
    const uint32_t & _arg)
  {
    this->max_candidates = _arg;
    return *this;
  }
  Type & set__publish_debug(
    const bool & _arg)
  {
    this->publish_debug = _arg;
    return *this;
  }
  Type & set__timeout_s(
    const double & _arg)
  {
    this->timeout_s = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MODE_AUTO_SEARCH =
    0u;
  static constexpr uint8_t MODE_SINGLE_INITIAL_POSE =
    1u;
  static constexpr uint8_t MODE_LOCAL_CANDIDATES =
    2u;
  static constexpr uint8_t MODE_EXTERNAL_COARSE_POSE =
    3u;

  // pointer types
  using RawPtr =
    agt_interfaces::action::Relocalize_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::Relocalize_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__Relocalize_Goal
    std::shared_ptr<agt_interfaces::action::Relocalize_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__Relocalize_Goal
    std::shared_ptr<agt_interfaces::action::Relocalize_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Relocalize_Goal_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    if (this->use_initial_pose != other.use_initial_pose) {
      return false;
    }
    if (this->initial_pose != other.initial_pose) {
      return false;
    }
    if (this->use_last_valid_pose != other.use_last_valid_pose) {
      return false;
    }
    if (this->use_configured_candidates != other.use_configured_candidates) {
      return false;
    }
    if (this->use_external_coarse_pose != other.use_external_coarse_pose) {
      return false;
    }
    if (this->max_candidates != other.max_candidates) {
      return false;
    }
    if (this->publish_debug != other.publish_debug) {
      return false;
    }
    if (this->timeout_s != other.timeout_s) {
      return false;
    }
    return true;
  }
  bool operator!=(const Relocalize_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Relocalize_Goal_

// alias to use template instance with default allocator
using Relocalize_Goal =
  agt_interfaces::action::Relocalize_Goal_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Relocalize_Goal_<ContainerAllocator>::MODE_AUTO_SEARCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Relocalize_Goal_<ContainerAllocator>::MODE_SINGLE_INITIAL_POSE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Relocalize_Goal_<ContainerAllocator>::MODE_LOCAL_CANDIDATES;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Relocalize_Goal_<ContainerAllocator>::MODE_EXTERNAL_COARSE_POSE;
#endif  // __cplusplus < 201703L

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'final_pose'
// already included above
// #include "geometry_msgs/msg/detail/pose_with_covariance_stamped__struct.hpp"
// Member 'final_status'
#include "agt_interfaces/msg/detail/localization_status__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__Relocalize_Result __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__Relocalize_Result __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Relocalize_Result_
{
  using Type = Relocalize_Result_<ContainerAllocator>;

  explicit Relocalize_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : final_pose(_init),
    final_status(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->failure_reason = "";
    }
  }

  explicit Relocalize_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : final_pose(_alloc, _init),
    final_status(_alloc, _init),
    failure_reason(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->failure_reason = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;
  using _final_pose_type =
    geometry_msgs::msg::PoseWithCovarianceStamped_<ContainerAllocator>;
  _final_pose_type final_pose;
  using _final_status_type =
    agt_interfaces::msg::LocalizationStatus_<ContainerAllocator>;
  _final_status_type final_status;
  using _failure_reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _failure_reason_type failure_reason;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__error_code(
    const uint16_t & _arg)
  {
    this->error_code = _arg;
    return *this;
  }
  Type & set__final_pose(
    const geometry_msgs::msg::PoseWithCovarianceStamped_<ContainerAllocator> & _arg)
  {
    this->final_pose = _arg;
    return *this;
  }
  Type & set__final_status(
    const agt_interfaces::msg::LocalizationStatus_<ContainerAllocator> & _arg)
  {
    this->final_status = _arg;
    return *this;
  }
  Type & set__failure_reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->failure_reason = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::Relocalize_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::Relocalize_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__Relocalize_Result
    std::shared_ptr<agt_interfaces::action::Relocalize_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__Relocalize_Result
    std::shared_ptr<agt_interfaces::action::Relocalize_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Relocalize_Result_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->final_pose != other.final_pose) {
      return false;
    }
    if (this->final_status != other.final_status) {
      return false;
    }
    if (this->failure_reason != other.failure_reason) {
      return false;
    }
    return true;
  }
  bool operator!=(const Relocalize_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Relocalize_Result_

// alias to use template instance with default allocator
using Relocalize_Result =
  agt_interfaces::action::Relocalize_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__Relocalize_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__Relocalize_Feedback __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Relocalize_Feedback_
{
  using Type = Relocalize_Feedback_<ContainerAllocator>;

  explicit Relocalize_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->total_candidates = 0ul;
      this->tested_candidates = 0ul;
      this->best_fitness_score = 0.0;
      this->best_candidate_source = "";
      this->elapsed_s = 0.0;
    }
  }

  explicit Relocalize_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : best_candidate_source(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->total_candidates = 0ul;
      this->tested_candidates = 0ul;
      this->best_fitness_score = 0.0;
      this->best_candidate_source = "";
      this->elapsed_s = 0.0;
    }
  }

  // field types and members
  using _state_type =
    uint8_t;
  _state_type state;
  using _total_candidates_type =
    uint32_t;
  _total_candidates_type total_candidates;
  using _tested_candidates_type =
    uint32_t;
  _tested_candidates_type tested_candidates;
  using _best_fitness_score_type =
    double;
  _best_fitness_score_type best_fitness_score;
  using _best_candidate_source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _best_candidate_source_type best_candidate_source;
  using _elapsed_s_type =
    double;
  _elapsed_s_type elapsed_s;

  // setters for named parameter idiom
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__total_candidates(
    const uint32_t & _arg)
  {
    this->total_candidates = _arg;
    return *this;
  }
  Type & set__tested_candidates(
    const uint32_t & _arg)
  {
    this->tested_candidates = _arg;
    return *this;
  }
  Type & set__best_fitness_score(
    const double & _arg)
  {
    this->best_fitness_score = _arg;
    return *this;
  }
  Type & set__best_candidate_source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->best_candidate_source = _arg;
    return *this;
  }
  Type & set__elapsed_s(
    const double & _arg)
  {
    this->elapsed_s = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__Relocalize_Feedback
    std::shared_ptr<agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__Relocalize_Feedback
    std::shared_ptr<agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Relocalize_Feedback_ & other) const
  {
    if (this->state != other.state) {
      return false;
    }
    if (this->total_candidates != other.total_candidates) {
      return false;
    }
    if (this->tested_candidates != other.tested_candidates) {
      return false;
    }
    if (this->best_fitness_score != other.best_fitness_score) {
      return false;
    }
    if (this->best_candidate_source != other.best_candidate_source) {
      return false;
    }
    if (this->elapsed_s != other.elapsed_s) {
      return false;
    }
    return true;
  }
  bool operator!=(const Relocalize_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Relocalize_Feedback_

// alias to use template instance with default allocator
using Relocalize_Feedback =
  agt_interfaces::action::Relocalize_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/relocalize__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__Relocalize_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__Relocalize_SendGoal_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Relocalize_SendGoal_Request_
{
  using Type = Relocalize_SendGoal_Request_<ContainerAllocator>;

  explicit Relocalize_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit Relocalize_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    agt_interfaces::action::Relocalize_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const agt_interfaces::action::Relocalize_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__Relocalize_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__Relocalize_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::Relocalize_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Relocalize_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const Relocalize_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Relocalize_SendGoal_Request_

// alias to use template instance with default allocator
using Relocalize_SendGoal_Request =
  agt_interfaces::action::Relocalize_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__Relocalize_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__Relocalize_SendGoal_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Relocalize_SendGoal_Response_
{
  using Type = Relocalize_SendGoal_Response_<ContainerAllocator>;

  explicit Relocalize_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit Relocalize_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__Relocalize_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__Relocalize_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::Relocalize_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Relocalize_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const Relocalize_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Relocalize_SendGoal_Response_

// alias to use template instance with default allocator
using Relocalize_SendGoal_Response =
  agt_interfaces::action::Relocalize_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct Relocalize_SendGoal
{
  using Request = agt_interfaces::action::Relocalize_SendGoal_Request;
  using Response = agt_interfaces::action::Relocalize_SendGoal_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__Relocalize_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__Relocalize_GetResult_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Relocalize_GetResult_Request_
{
  using Type = Relocalize_GetResult_Request_<ContainerAllocator>;

  explicit Relocalize_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit Relocalize_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__Relocalize_GetResult_Request
    std::shared_ptr<agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__Relocalize_GetResult_Request
    std::shared_ptr<agt_interfaces::action::Relocalize_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Relocalize_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const Relocalize_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Relocalize_GetResult_Request_

// alias to use template instance with default allocator
using Relocalize_GetResult_Request =
  agt_interfaces::action::Relocalize_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/relocalize__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__Relocalize_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__Relocalize_GetResult_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Relocalize_GetResult_Response_
{
  using Type = Relocalize_GetResult_Response_<ContainerAllocator>;

  explicit Relocalize_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit Relocalize_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    agt_interfaces::action::Relocalize_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const agt_interfaces::action::Relocalize_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__Relocalize_GetResult_Response
    std::shared_ptr<agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__Relocalize_GetResult_Response
    std::shared_ptr<agt_interfaces::action::Relocalize_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Relocalize_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const Relocalize_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Relocalize_GetResult_Response_

// alias to use template instance with default allocator
using Relocalize_GetResult_Response =
  agt_interfaces::action::Relocalize_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct Relocalize_GetResult
{
  using Request = agt_interfaces::action::Relocalize_GetResult_Request;
  using Response = agt_interfaces::action::Relocalize_GetResult_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/relocalize__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__Relocalize_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__Relocalize_FeedbackMessage __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Relocalize_FeedbackMessage_
{
  using Type = Relocalize_FeedbackMessage_<ContainerAllocator>;

  explicit Relocalize_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit Relocalize_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const agt_interfaces::action::Relocalize_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__Relocalize_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__Relocalize_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::Relocalize_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Relocalize_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const Relocalize_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Relocalize_FeedbackMessage_

// alias to use template instance with default allocator
using Relocalize_FeedbackMessage =
  agt_interfaces::action::Relocalize_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace agt_interfaces
{

namespace action
{

struct Relocalize
{
  /// The goal message defined in the action definition.
  using Goal = agt_interfaces::action::Relocalize_Goal;
  /// The result message defined in the action definition.
  using Result = agt_interfaces::action::Relocalize_Result;
  /// The feedback message defined in the action definition.
  using Feedback = agt_interfaces::action::Relocalize_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = agt_interfaces::action::Relocalize_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = agt_interfaces::action::Relocalize_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = agt_interfaces::action::Relocalize_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct Relocalize Relocalize;

}  // namespace action

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__STRUCT_HPP_
