// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:action/ExecuteCoverageTask.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__STRUCT_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Goal __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Goal __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteCoverageTask_Goal_
{
  using Type = ExecuteCoverageTask_Goal_<ContainerAllocator>;

  explicit ExecuteCoverageTask_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->semantic_map_uri = "";
      this->field_id = "";
      this->planning_mode = "";
      this->controller_id = "";
      this->allow_repair = false;
    }
  }

  explicit ExecuteCoverageTask_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : semantic_map_uri(_alloc),
    field_id(_alloc),
    planning_mode(_alloc),
    controller_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->semantic_map_uri = "";
      this->field_id = "";
      this->planning_mode = "";
      this->controller_id = "";
      this->allow_repair = false;
    }
  }

  // field types and members
  using _semantic_map_uri_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _semantic_map_uri_type semantic_map_uri;
  using _field_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _field_id_type field_id;
  using _planning_mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _planning_mode_type planning_mode;
  using _controller_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _controller_id_type controller_id;
  using _allow_repair_type =
    bool;
  _allow_repair_type allow_repair;

  // setters for named parameter idiom
  Type & set__semantic_map_uri(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->semantic_map_uri = _arg;
    return *this;
  }
  Type & set__field_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->field_id = _arg;
    return *this;
  }
  Type & set__planning_mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->planning_mode = _arg;
    return *this;
  }
  Type & set__controller_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->controller_id = _arg;
    return *this;
  }
  Type & set__allow_repair(
    const bool & _arg)
  {
    this->allow_repair = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Goal
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Goal
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteCoverageTask_Goal_ & other) const
  {
    if (this->semantic_map_uri != other.semantic_map_uri) {
      return false;
    }
    if (this->field_id != other.field_id) {
      return false;
    }
    if (this->planning_mode != other.planning_mode) {
      return false;
    }
    if (this->controller_id != other.controller_id) {
      return false;
    }
    if (this->allow_repair != other.allow_repair) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteCoverageTask_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteCoverageTask_Goal_

// alias to use template instance with default allocator
using ExecuteCoverageTask_Goal =
  agt_interfaces::action::ExecuteCoverageTask_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Result __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Result __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteCoverageTask_Result_
{
  using Type = ExecuteCoverageTask_Result_<ContainerAllocator>;

  explicit ExecuteCoverageTask_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->message = "";
      this->coverage_rate = 0.0;
      this->overlap_rate = 0.0;
      this->executed_length = 0.0;
      this->repaired_segment_count = 0ul;
    }
  }

  explicit ExecuteCoverageTask_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->message = "";
      this->coverage_rate = 0.0;
      this->overlap_rate = 0.0;
      this->executed_length = 0.0;
      this->repaired_segment_count = 0ul;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _coverage_rate_type =
    double;
  _coverage_rate_type coverage_rate;
  using _overlap_rate_type =
    double;
  _overlap_rate_type overlap_rate;
  using _executed_length_type =
    double;
  _executed_length_type executed_length;
  using _repaired_segment_count_type =
    uint32_t;
  _repaired_segment_count_type repaired_segment_count;

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
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__coverage_rate(
    const double & _arg)
  {
    this->coverage_rate = _arg;
    return *this;
  }
  Type & set__overlap_rate(
    const double & _arg)
  {
    this->overlap_rate = _arg;
    return *this;
  }
  Type & set__executed_length(
    const double & _arg)
  {
    this->executed_length = _arg;
    return *this;
  }
  Type & set__repaired_segment_count(
    const uint32_t & _arg)
  {
    this->repaired_segment_count = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Result
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Result
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteCoverageTask_Result_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->coverage_rate != other.coverage_rate) {
      return false;
    }
    if (this->overlap_rate != other.overlap_rate) {
      return false;
    }
    if (this->executed_length != other.executed_length) {
      return false;
    }
    if (this->repaired_segment_count != other.repaired_segment_count) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteCoverageTask_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteCoverageTask_Result_

// alias to use template instance with default allocator
using ExecuteCoverageTask_Result =
  agt_interfaces::action::ExecuteCoverageTask_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Feedback __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteCoverageTask_Feedback_
{
  using Type = ExecuteCoverageTask_Feedback_<ContainerAllocator>;

  explicit ExecuteCoverageTask_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_stage = "";
      this->current_swath_index = 0ul;
      this->total_swaths = 0ul;
      this->distance_remaining = 0.0;
    }
  }

  explicit ExecuteCoverageTask_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : current_stage(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_stage = "";
      this->current_swath_index = 0ul;
      this->total_swaths = 0ul;
      this->distance_remaining = 0.0;
    }
  }

  // field types and members
  using _current_stage_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _current_stage_type current_stage;
  using _current_swath_index_type =
    uint32_t;
  _current_swath_index_type current_swath_index;
  using _total_swaths_type =
    uint32_t;
  _total_swaths_type total_swaths;
  using _distance_remaining_type =
    double;
  _distance_remaining_type distance_remaining;

  // setters for named parameter idiom
  Type & set__current_stage(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->current_stage = _arg;
    return *this;
  }
  Type & set__current_swath_index(
    const uint32_t & _arg)
  {
    this->current_swath_index = _arg;
    return *this;
  }
  Type & set__total_swaths(
    const uint32_t & _arg)
  {
    this->total_swaths = _arg;
    return *this;
  }
  Type & set__distance_remaining(
    const double & _arg)
  {
    this->distance_remaining = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Feedback
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_Feedback
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteCoverageTask_Feedback_ & other) const
  {
    if (this->current_stage != other.current_stage) {
      return false;
    }
    if (this->current_swath_index != other.current_swath_index) {
      return false;
    }
    if (this->total_swaths != other.total_swaths) {
      return false;
    }
    if (this->distance_remaining != other.distance_remaining) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteCoverageTask_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteCoverageTask_Feedback_

// alias to use template instance with default allocator
using ExecuteCoverageTask_Feedback =
  agt_interfaces::action::ExecuteCoverageTask_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/execute_coverage_task__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteCoverageTask_SendGoal_Request_
{
  using Type = ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator>;

  explicit ExecuteCoverageTask_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit ExecuteCoverageTask_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const agt_interfaces::action::ExecuteCoverageTask_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteCoverageTask_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteCoverageTask_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteCoverageTask_SendGoal_Request_

// alias to use template instance with default allocator
using ExecuteCoverageTask_SendGoal_Request =
  agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteCoverageTask_SendGoal_Response_
{
  using Type = ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator>;

  explicit ExecuteCoverageTask_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit ExecuteCoverageTask_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteCoverageTask_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteCoverageTask_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteCoverageTask_SendGoal_Response_

// alias to use template instance with default allocator
using ExecuteCoverageTask_SendGoal_Response =
  agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct ExecuteCoverageTask_SendGoal
{
  using Request = agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request;
  using Response = agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_GetResult_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteCoverageTask_GetResult_Request_
{
  using Type = ExecuteCoverageTask_GetResult_Request_<ContainerAllocator>;

  explicit ExecuteCoverageTask_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit ExecuteCoverageTask_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_GetResult_Request
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_GetResult_Request
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteCoverageTask_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteCoverageTask_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteCoverageTask_GetResult_Request_

// alias to use template instance with default allocator
using ExecuteCoverageTask_GetResult_Request =
  agt_interfaces::action::ExecuteCoverageTask_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/execute_coverage_task__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_GetResult_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteCoverageTask_GetResult_Response_
{
  using Type = ExecuteCoverageTask_GetResult_Response_<ContainerAllocator>;

  explicit ExecuteCoverageTask_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit ExecuteCoverageTask_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const agt_interfaces::action::ExecuteCoverageTask_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_GetResult_Response
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_GetResult_Response
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteCoverageTask_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteCoverageTask_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteCoverageTask_GetResult_Response_

// alias to use template instance with default allocator
using ExecuteCoverageTask_GetResult_Response =
  agt_interfaces::action::ExecuteCoverageTask_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct ExecuteCoverageTask_GetResult
{
  using Request = agt_interfaces::action::ExecuteCoverageTask_GetResult_Request;
  using Response = agt_interfaces::action::ExecuteCoverageTask_GetResult_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/execute_coverage_task__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteCoverageTask_FeedbackMessage_
{
  using Type = ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator>;

  explicit ExecuteCoverageTask_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit ExecuteCoverageTask_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const agt_interfaces::action::ExecuteCoverageTask_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteCoverageTask_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteCoverageTask_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteCoverageTask_FeedbackMessage_

// alias to use template instance with default allocator
using ExecuteCoverageTask_FeedbackMessage =
  agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage_<std::allocator<void>>;

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

struct ExecuteCoverageTask
{
  /// The goal message defined in the action definition.
  using Goal = agt_interfaces::action::ExecuteCoverageTask_Goal;
  /// The result message defined in the action definition.
  using Result = agt_interfaces::action::ExecuteCoverageTask_Result;
  /// The feedback message defined in the action definition.
  using Feedback = agt_interfaces::action::ExecuteCoverageTask_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = agt_interfaces::action::ExecuteCoverageTask_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = agt_interfaces::action::ExecuteCoverageTask_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct ExecuteCoverageTask ExecuteCoverageTask;

}  // namespace action

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__STRUCT_HPP_
