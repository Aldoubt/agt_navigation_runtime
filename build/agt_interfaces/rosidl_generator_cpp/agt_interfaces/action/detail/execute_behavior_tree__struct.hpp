// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:action/ExecuteBehaviorTree.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_BEHAVIOR_TREE__STRUCT_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_BEHAVIOR_TREE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Goal __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Goal __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteBehaviorTree_Goal_
{
  using Type = ExecuteBehaviorTree_Goal_<ContainerAllocator>;

  explicit ExecuteBehaviorTree_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tree_id = "";
      this->execution_id = "";
      this->map_id = "";
      this->map_version_id = "";
      this->task_group_id = "";
      this->task_revision = 0ul;
      this->expected_content_sha256 = "";
      this->loop_count = 0ul;
      this->client_request_id = "";
    }
  }

  explicit ExecuteBehaviorTree_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : tree_id(_alloc),
    execution_id(_alloc),
    map_id(_alloc),
    map_version_id(_alloc),
    task_group_id(_alloc),
    expected_content_sha256(_alloc),
    client_request_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tree_id = "";
      this->execution_id = "";
      this->map_id = "";
      this->map_version_id = "";
      this->task_group_id = "";
      this->task_revision = 0ul;
      this->expected_content_sha256 = "";
      this->loop_count = 0ul;
      this->client_request_id = "";
    }
  }

  // field types and members
  using _tree_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tree_id_type tree_id;
  using _execution_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _execution_id_type execution_id;
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
  using _expected_content_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _expected_content_sha256_type expected_content_sha256;
  using _loop_count_type =
    uint32_t;
  _loop_count_type loop_count;
  using _client_request_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _client_request_id_type client_request_id;

  // setters for named parameter idiom
  Type & set__tree_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tree_id = _arg;
    return *this;
  }
  Type & set__execution_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->execution_id = _arg;
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
  Type & set__expected_content_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->expected_content_sha256 = _arg;
    return *this;
  }
  Type & set__loop_count(
    const uint32_t & _arg)
  {
    this->loop_count = _arg;
    return *this;
  }
  Type & set__client_request_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->client_request_id = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t ERROR_NONE =
    0u;
  static constexpr uint16_t ERROR_INVALID_REQUEST =
    1u;
  static constexpr uint16_t ERROR_TREE_NOT_ALLOWED =
    2u;
  static constexpr uint16_t ERROR_TREE_FAILED =
    3u;
  static constexpr uint16_t ERROR_CANCELED =
    4u;
  static constexpr uint16_t ERROR_INTERNAL =
    255u;

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Goal
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Goal
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteBehaviorTree_Goal_ & other) const
  {
    if (this->tree_id != other.tree_id) {
      return false;
    }
    if (this->execution_id != other.execution_id) {
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
    if (this->expected_content_sha256 != other.expected_content_sha256) {
      return false;
    }
    if (this->loop_count != other.loop_count) {
      return false;
    }
    if (this->client_request_id != other.client_request_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteBehaviorTree_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteBehaviorTree_Goal_

// alias to use template instance with default allocator
using ExecuteBehaviorTree_Goal =
  agt_interfaces::action::ExecuteBehaviorTree_Goal_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ExecuteBehaviorTree_Goal_<ContainerAllocator>::ERROR_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ExecuteBehaviorTree_Goal_<ContainerAllocator>::ERROR_INVALID_REQUEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ExecuteBehaviorTree_Goal_<ContainerAllocator>::ERROR_TREE_NOT_ALLOWED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ExecuteBehaviorTree_Goal_<ContainerAllocator>::ERROR_TREE_FAILED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ExecuteBehaviorTree_Goal_<ContainerAllocator>::ERROR_CANCELED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ExecuteBehaviorTree_Goal_<ContainerAllocator>::ERROR_INTERNAL;
#endif  // __cplusplus < 201703L

}  // namespace action

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Result __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Result __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteBehaviorTree_Result_
{
  using Type = ExecuteBehaviorTree_Result_<ContainerAllocator>;

  explicit ExecuteBehaviorTree_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->message = "";
      this->blocker_code = "";
      this->blocker_message = "";
    }
  }

  explicit ExecuteBehaviorTree_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc),
    blocker_code(_alloc),
    blocker_message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->message = "";
      this->blocker_code = "";
      this->blocker_message = "";
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
  using _blocker_code_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _blocker_code_type blocker_code;
  using _blocker_message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _blocker_message_type blocker_message;

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
  Type & set__blocker_code(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->blocker_code = _arg;
    return *this;
  }
  Type & set__blocker_message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->blocker_message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Result
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Result
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteBehaviorTree_Result_ & other) const
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
    if (this->blocker_code != other.blocker_code) {
      return false;
    }
    if (this->blocker_message != other.blocker_message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteBehaviorTree_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteBehaviorTree_Result_

// alias to use template instance with default allocator
using ExecuteBehaviorTree_Result =
  agt_interfaces::action::ExecuteBehaviorTree_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Feedback __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteBehaviorTree_Feedback_
{
  using Type = ExecuteBehaviorTree_Feedback_<ContainerAllocator>;

  explicit ExecuteBehaviorTree_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tree_state = "";
      this->active_node = "";
      this->loop_index = 0ul;
      this->current_waypoint = 0ul;
      this->total_waypoints = 0ul;
    }
  }

  explicit ExecuteBehaviorTree_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : tree_state(_alloc),
    active_node(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tree_state = "";
      this->active_node = "";
      this->loop_index = 0ul;
      this->current_waypoint = 0ul;
      this->total_waypoints = 0ul;
    }
  }

  // field types and members
  using _tree_state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tree_state_type tree_state;
  using _active_node_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _active_node_type active_node;
  using _loop_index_type =
    uint32_t;
  _loop_index_type loop_index;
  using _current_waypoint_type =
    uint32_t;
  _current_waypoint_type current_waypoint;
  using _total_waypoints_type =
    uint32_t;
  _total_waypoints_type total_waypoints;

  // setters for named parameter idiom
  Type & set__tree_state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tree_state = _arg;
    return *this;
  }
  Type & set__active_node(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->active_node = _arg;
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

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Feedback
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_Feedback
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteBehaviorTree_Feedback_ & other) const
  {
    if (this->tree_state != other.tree_state) {
      return false;
    }
    if (this->active_node != other.active_node) {
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
    return true;
  }
  bool operator!=(const ExecuteBehaviorTree_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteBehaviorTree_Feedback_

// alias to use template instance with default allocator
using ExecuteBehaviorTree_Feedback =
  agt_interfaces::action::ExecuteBehaviorTree_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteBehaviorTree_SendGoal_Request_
{
  using Type = ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator>;

  explicit ExecuteBehaviorTree_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit ExecuteBehaviorTree_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const agt_interfaces::action::ExecuteBehaviorTree_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteBehaviorTree_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteBehaviorTree_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteBehaviorTree_SendGoal_Request_

// alias to use template instance with default allocator
using ExecuteBehaviorTree_SendGoal_Request =
  agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteBehaviorTree_SendGoal_Response_
{
  using Type = ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator>;

  explicit ExecuteBehaviorTree_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit ExecuteBehaviorTree_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteBehaviorTree_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteBehaviorTree_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteBehaviorTree_SendGoal_Response_

// alias to use template instance with default allocator
using ExecuteBehaviorTree_SendGoal_Response =
  agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct ExecuteBehaviorTree_SendGoal
{
  using Request = agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request;
  using Response = agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteBehaviorTree_GetResult_Request_
{
  using Type = ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator>;

  explicit ExecuteBehaviorTree_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit ExecuteBehaviorTree_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteBehaviorTree_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteBehaviorTree_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteBehaviorTree_GetResult_Request_

// alias to use template instance with default allocator
using ExecuteBehaviorTree_GetResult_Request =
  agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteBehaviorTree_GetResult_Response_
{
  using Type = ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator>;

  explicit ExecuteBehaviorTree_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit ExecuteBehaviorTree_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const agt_interfaces::action::ExecuteBehaviorTree_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteBehaviorTree_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteBehaviorTree_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteBehaviorTree_GetResult_Response_

// alias to use template instance with default allocator
using ExecuteBehaviorTree_GetResult_Response =
  agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct ExecuteBehaviorTree_GetResult
{
  using Request = agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request;
  using Response = agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteBehaviorTree_FeedbackMessage_
{
  using Type = ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator>;

  explicit ExecuteBehaviorTree_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit ExecuteBehaviorTree_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const agt_interfaces::action::ExecuteBehaviorTree_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteBehaviorTree_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteBehaviorTree_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteBehaviorTree_FeedbackMessage_

// alias to use template instance with default allocator
using ExecuteBehaviorTree_FeedbackMessage =
  agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage_<std::allocator<void>>;

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

struct ExecuteBehaviorTree
{
  /// The goal message defined in the action definition.
  using Goal = agt_interfaces::action::ExecuteBehaviorTree_Goal;
  /// The result message defined in the action definition.
  using Result = agt_interfaces::action::ExecuteBehaviorTree_Result;
  /// The feedback message defined in the action definition.
  using Feedback = agt_interfaces::action::ExecuteBehaviorTree_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = agt_interfaces::action::ExecuteBehaviorTree_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = agt_interfaces::action::ExecuteBehaviorTree_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct ExecuteBehaviorTree ExecuteBehaviorTree;

}  // namespace action

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_BEHAVIOR_TREE__STRUCT_HPP_
