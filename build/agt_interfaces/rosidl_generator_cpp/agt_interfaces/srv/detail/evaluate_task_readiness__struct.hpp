// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:srv/EvaluateTaskReadiness.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__STRUCT_HPP_
#define AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__EvaluateTaskReadiness_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__EvaluateTaskReadiness_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct EvaluateTaskReadiness_Request_
{
  using Type = EvaluateTaskReadiness_Request_<ContainerAllocator>;

  explicit EvaluateTaskReadiness_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->validate_task = false;
      this->task_id = "";
      this->gate_profile = 0;
    }
  }

  explicit EvaluateTaskReadiness_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : task_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->validate_task = false;
      this->task_id = "";
      this->gate_profile = 0;
    }
  }

  // field types and members
  using _validate_task_type =
    bool;
  _validate_task_type validate_task;
  using _task_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _task_id_type task_id;
  using _gate_profile_type =
    uint8_t;
  _gate_profile_type gate_profile;

  // setters for named parameter idiom
  Type & set__validate_task(
    const bool & _arg)
  {
    this->validate_task = _arg;
    return *this;
  }
  Type & set__task_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->task_id = _arg;
    return *this;
  }
  Type & set__gate_profile(
    const uint8_t & _arg)
  {
    this->gate_profile = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t PROFILE_TASK_EXECUTION =
    0u;
  static constexpr uint8_t PROFILE_RELOCALIZATION =
    1u;

  // pointer types
  using RawPtr =
    agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__EvaluateTaskReadiness_Request
    std::shared_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__EvaluateTaskReadiness_Request
    std::shared_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EvaluateTaskReadiness_Request_ & other) const
  {
    if (this->validate_task != other.validate_task) {
      return false;
    }
    if (this->task_id != other.task_id) {
      return false;
    }
    if (this->gate_profile != other.gate_profile) {
      return false;
    }
    return true;
  }
  bool operator!=(const EvaluateTaskReadiness_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EvaluateTaskReadiness_Request_

// alias to use template instance with default allocator
using EvaluateTaskReadiness_Request =
  agt_interfaces::srv::EvaluateTaskReadiness_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t EvaluateTaskReadiness_Request_<ContainerAllocator>::PROFILE_TASK_EXECUTION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t EvaluateTaskReadiness_Request_<ContainerAllocator>::PROFILE_RELOCALIZATION;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace agt_interfaces


// Include directives for member types
// Member 'readiness'
#include "agt_interfaces/msg/detail/task_readiness__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__EvaluateTaskReadiness_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__EvaluateTaskReadiness_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct EvaluateTaskReadiness_Response_
{
  using Type = EvaluateTaskReadiness_Response_<ContainerAllocator>;

  explicit EvaluateTaskReadiness_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : readiness(_init)
  {
    (void)_init;
  }

  explicit EvaluateTaskReadiness_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : readiness(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _readiness_type =
    agt_interfaces::msg::TaskReadiness_<ContainerAllocator>;
  _readiness_type readiness;

  // setters for named parameter idiom
  Type & set__readiness(
    const agt_interfaces::msg::TaskReadiness_<ContainerAllocator> & _arg)
  {
    this->readiness = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__EvaluateTaskReadiness_Response
    std::shared_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__EvaluateTaskReadiness_Response
    std::shared_ptr<agt_interfaces::srv::EvaluateTaskReadiness_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EvaluateTaskReadiness_Response_ & other) const
  {
    if (this->readiness != other.readiness) {
      return false;
    }
    return true;
  }
  bool operator!=(const EvaluateTaskReadiness_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EvaluateTaskReadiness_Response_

// alias to use template instance with default allocator
using EvaluateTaskReadiness_Response =
  agt_interfaces::srv::EvaluateTaskReadiness_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace srv
{

struct EvaluateTaskReadiness
{
  using Request = agt_interfaces::srv::EvaluateTaskReadiness_Request;
  using Response = agt_interfaces::srv::EvaluateTaskReadiness_Response;
};

}  // namespace srv

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__STRUCT_HPP_
