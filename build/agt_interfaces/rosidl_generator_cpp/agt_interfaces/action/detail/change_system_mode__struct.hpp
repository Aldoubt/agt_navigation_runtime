// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:action/ChangeSystemMode.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__STRUCT_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_Goal __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_Goal __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ChangeSystemMode_Goal_
{
  using Type = ChangeSystemMode_Goal_<ContainerAllocator>;

  explicit ChangeSystemMode_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->profile = "";
      this->wait_for_health = false;
      this->startup_timeout_s = 0.0;
    }
  }

  explicit ChangeSystemMode_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : profile(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->profile = "";
      this->wait_for_health = false;
      this->startup_timeout_s = 0.0;
    }
  }

  // field types and members
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _profile_type profile;
  using _argument_keys_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _argument_keys_type argument_keys;
  using _argument_values_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _argument_values_type argument_values;
  using _wait_for_health_type =
    bool;
  _wait_for_health_type wait_for_health;
  using _startup_timeout_s_type =
    double;
  _startup_timeout_s_type startup_timeout_s;

  // setters for named parameter idiom
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->profile = _arg;
    return *this;
  }
  Type & set__argument_keys(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->argument_keys = _arg;
    return *this;
  }
  Type & set__argument_values(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->argument_values = _arg;
    return *this;
  }
  Type & set__wait_for_health(
    const bool & _arg)
  {
    this->wait_for_health = _arg;
    return *this;
  }
  Type & set__startup_timeout_s(
    const double & _arg)
  {
    this->startup_timeout_s = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MODE_IDLE =
    0u;
  static constexpr uint8_t MODE_SENSOR_ONLY =
    1u;
  static constexpr uint8_t MODE_MAPPING =
    2u;
  static constexpr uint8_t MODE_LOCALIZATION_DEBUG =
    3u;
  static constexpr uint8_t MODE_NAVIGATION =
    4u;
  static constexpr uint8_t MODE_ERROR =
    5u;

  // pointer types
  using RawPtr =
    agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_Goal
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_Goal
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChangeSystemMode_Goal_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    if (this->profile != other.profile) {
      return false;
    }
    if (this->argument_keys != other.argument_keys) {
      return false;
    }
    if (this->argument_values != other.argument_values) {
      return false;
    }
    if (this->wait_for_health != other.wait_for_health) {
      return false;
    }
    if (this->startup_timeout_s != other.startup_timeout_s) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChangeSystemMode_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChangeSystemMode_Goal_

// alias to use template instance with default allocator
using ChangeSystemMode_Goal =
  agt_interfaces::action::ChangeSystemMode_Goal_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ChangeSystemMode_Goal_<ContainerAllocator>::MODE_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ChangeSystemMode_Goal_<ContainerAllocator>::MODE_SENSOR_ONLY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ChangeSystemMode_Goal_<ContainerAllocator>::MODE_MAPPING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ChangeSystemMode_Goal_<ContainerAllocator>::MODE_LOCALIZATION_DEBUG;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ChangeSystemMode_Goal_<ContainerAllocator>::MODE_NAVIGATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ChangeSystemMode_Goal_<ContainerAllocator>::MODE_ERROR;
#endif  // __cplusplus < 201703L

}  // namespace action

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_Result __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_Result __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ChangeSystemMode_Result_
{
  using Type = ChangeSystemMode_Result_<ContainerAllocator>;

  explicit ChangeSystemMode_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->active_mode = "";
      this->profile = "";
      this->message = "";
    }
  }

  explicit ChangeSystemMode_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : active_mode(_alloc),
    profile(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->active_mode = "";
      this->profile = "";
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;
  using _active_mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _active_mode_type active_mode;
  using _profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _profile_type profile;
  using _process_ids_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _process_ids_type process_ids;
  using _log_paths_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _log_paths_type log_paths;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

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
  Type & set__active_mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->active_mode = _arg;
    return *this;
  }
  Type & set__profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->profile = _arg;
    return *this;
  }
  Type & set__process_ids(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->process_ids = _arg;
    return *this;
  }
  Type & set__log_paths(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->log_paths = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_Result
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_Result
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChangeSystemMode_Result_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->active_mode != other.active_mode) {
      return false;
    }
    if (this->profile != other.profile) {
      return false;
    }
    if (this->process_ids != other.process_ids) {
      return false;
    }
    if (this->log_paths != other.log_paths) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChangeSystemMode_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChangeSystemMode_Result_

// alias to use template instance with default allocator
using ChangeSystemMode_Result =
  agt_interfaces::action::ChangeSystemMode_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_Feedback __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ChangeSystemMode_Feedback_
{
  using Type = ChangeSystemMode_Feedback_<ContainerAllocator>;

  explicit ChangeSystemMode_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = "";
      this->progress = 0.0f;
      this->message = "";
    }
  }

  explicit ChangeSystemMode_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = "";
      this->progress = 0.0f;
      this->message = "";
    }
  }

  // field types and members
  using _state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _state_type state;
  using _progress_type =
    float;
  _progress_type progress;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__progress(
    const float & _arg)
  {
    this->progress = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_Feedback
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_Feedback
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChangeSystemMode_Feedback_ & other) const
  {
    if (this->state != other.state) {
      return false;
    }
    if (this->progress != other.progress) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChangeSystemMode_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChangeSystemMode_Feedback_

// alias to use template instance with default allocator
using ChangeSystemMode_Feedback =
  agt_interfaces::action::ChangeSystemMode_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/change_system_mode__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_SendGoal_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ChangeSystemMode_SendGoal_Request_
{
  using Type = ChangeSystemMode_SendGoal_Request_<ContainerAllocator>;

  explicit ChangeSystemMode_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit ChangeSystemMode_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const agt_interfaces::action::ChangeSystemMode_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChangeSystemMode_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChangeSystemMode_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChangeSystemMode_SendGoal_Request_

// alias to use template instance with default allocator
using ChangeSystemMode_SendGoal_Request =
  agt_interfaces::action::ChangeSystemMode_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_SendGoal_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ChangeSystemMode_SendGoal_Response_
{
  using Type = ChangeSystemMode_SendGoal_Response_<ContainerAllocator>;

  explicit ChangeSystemMode_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit ChangeSystemMode_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChangeSystemMode_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChangeSystemMode_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChangeSystemMode_SendGoal_Response_

// alias to use template instance with default allocator
using ChangeSystemMode_SendGoal_Response =
  agt_interfaces::action::ChangeSystemMode_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct ChangeSystemMode_SendGoal
{
  using Request = agt_interfaces::action::ChangeSystemMode_SendGoal_Request;
  using Response = agt_interfaces::action::ChangeSystemMode_SendGoal_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_GetResult_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ChangeSystemMode_GetResult_Request_
{
  using Type = ChangeSystemMode_GetResult_Request_<ContainerAllocator>;

  explicit ChangeSystemMode_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit ChangeSystemMode_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_GetResult_Request
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_GetResult_Request
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChangeSystemMode_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChangeSystemMode_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChangeSystemMode_GetResult_Request_

// alias to use template instance with default allocator
using ChangeSystemMode_GetResult_Request =
  agt_interfaces::action::ChangeSystemMode_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/change_system_mode__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_GetResult_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ChangeSystemMode_GetResult_Response_
{
  using Type = ChangeSystemMode_GetResult_Response_<ContainerAllocator>;

  explicit ChangeSystemMode_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit ChangeSystemMode_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const agt_interfaces::action::ChangeSystemMode_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_GetResult_Response
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_GetResult_Response
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChangeSystemMode_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChangeSystemMode_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChangeSystemMode_GetResult_Response_

// alias to use template instance with default allocator
using ChangeSystemMode_GetResult_Response =
  agt_interfaces::action::ChangeSystemMode_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct ChangeSystemMode_GetResult
{
  using Request = agt_interfaces::action::ChangeSystemMode_GetResult_Request;
  using Response = agt_interfaces::action::ChangeSystemMode_GetResult_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/change_system_mode__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__ChangeSystemMode_FeedbackMessage __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ChangeSystemMode_FeedbackMessage_
{
  using Type = ChangeSystemMode_FeedbackMessage_<ContainerAllocator>;

  explicit ChangeSystemMode_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit ChangeSystemMode_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const agt_interfaces::action::ChangeSystemMode_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__ChangeSystemMode_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChangeSystemMode_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChangeSystemMode_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChangeSystemMode_FeedbackMessage_

// alias to use template instance with default allocator
using ChangeSystemMode_FeedbackMessage =
  agt_interfaces::action::ChangeSystemMode_FeedbackMessage_<std::allocator<void>>;

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

struct ChangeSystemMode
{
  /// The goal message defined in the action definition.
  using Goal = agt_interfaces::action::ChangeSystemMode_Goal;
  /// The result message defined in the action definition.
  using Result = agt_interfaces::action::ChangeSystemMode_Result;
  /// The feedback message defined in the action definition.
  using Feedback = agt_interfaces::action::ChangeSystemMode_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = agt_interfaces::action::ChangeSystemMode_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = agt_interfaces::action::ChangeSystemMode_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = agt_interfaces::action::ChangeSystemMode_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct ChangeSystemMode ChangeSystemMode;

}  // namespace action

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__STRUCT_HPP_
