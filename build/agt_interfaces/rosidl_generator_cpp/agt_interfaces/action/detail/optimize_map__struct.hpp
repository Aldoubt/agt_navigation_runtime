// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:action/OptimizeMap.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__STRUCT_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__OptimizeMap_Goal __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__OptimizeMap_Goal __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct OptimizeMap_Goal_
{
  using Type = OptimizeMap_Goal_<ContainerAllocator>;

  explicit OptimizeMap_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source_map_id = "";
      this->source_map_version_id = "";
      this->backend = "";
      this->options_yaml = "";
      this->activate_on_success = false;
    }
  }

  explicit OptimizeMap_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : source_map_id(_alloc),
    source_map_version_id(_alloc),
    backend(_alloc),
    options_yaml(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source_map_id = "";
      this->source_map_version_id = "";
      this->backend = "";
      this->options_yaml = "";
      this->activate_on_success = false;
    }
  }

  // field types and members
  using _source_map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_map_id_type source_map_id;
  using _source_map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_map_version_id_type source_map_version_id;
  using _source_experiment_ids_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _source_experiment_ids_type source_experiment_ids;
  using _backend_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _backend_type backend;
  using _options_yaml_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _options_yaml_type options_yaml;
  using _activate_on_success_type =
    bool;
  _activate_on_success_type activate_on_success;

  // setters for named parameter idiom
  Type & set__source_map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source_map_id = _arg;
    return *this;
  }
  Type & set__source_map_version_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source_map_version_id = _arg;
    return *this;
  }
  Type & set__source_experiment_ids(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->source_experiment_ids = _arg;
    return *this;
  }
  Type & set__backend(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->backend = _arg;
    return *this;
  }
  Type & set__options_yaml(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->options_yaml = _arg;
    return *this;
  }
  Type & set__activate_on_success(
    const bool & _arg)
  {
    this->activate_on_success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_Goal
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_Goal
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OptimizeMap_Goal_ & other) const
  {
    if (this->source_map_id != other.source_map_id) {
      return false;
    }
    if (this->source_map_version_id != other.source_map_version_id) {
      return false;
    }
    if (this->source_experiment_ids != other.source_experiment_ids) {
      return false;
    }
    if (this->backend != other.backend) {
      return false;
    }
    if (this->options_yaml != other.options_yaml) {
      return false;
    }
    if (this->activate_on_success != other.activate_on_success) {
      return false;
    }
    return true;
  }
  bool operator!=(const OptimizeMap_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OptimizeMap_Goal_

// alias to use template instance with default allocator
using OptimizeMap_Goal =
  agt_interfaces::action::OptimizeMap_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__OptimizeMap_Result __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__OptimizeMap_Result __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct OptimizeMap_Result_
{
  using Type = OptimizeMap_Result_<ContainerAllocator>;

  explicit OptimizeMap_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->new_map_version_id = "";
      this->trajectory_path = "";
      this->optimized_pcd_path = "";
      this->report_path = "";
      this->message = "";
    }
  }

  explicit OptimizeMap_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : new_map_version_id(_alloc),
    trajectory_path(_alloc),
    optimized_pcd_path(_alloc),
    report_path(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->new_map_version_id = "";
      this->trajectory_path = "";
      this->optimized_pcd_path = "";
      this->report_path = "";
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
  using _new_map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _new_map_version_id_type new_map_version_id;
  using _trajectory_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _trajectory_path_type trajectory_path;
  using _optimized_pcd_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _optimized_pcd_path_type optimized_pcd_path;
  using _report_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _report_path_type report_path;
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
  Type & set__new_map_version_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->new_map_version_id = _arg;
    return *this;
  }
  Type & set__trajectory_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->trajectory_path = _arg;
    return *this;
  }
  Type & set__optimized_pcd_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->optimized_pcd_path = _arg;
    return *this;
  }
  Type & set__report_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->report_path = _arg;
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
    agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_Result
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_Result
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OptimizeMap_Result_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->new_map_version_id != other.new_map_version_id) {
      return false;
    }
    if (this->trajectory_path != other.trajectory_path) {
      return false;
    }
    if (this->optimized_pcd_path != other.optimized_pcd_path) {
      return false;
    }
    if (this->report_path != other.report_path) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const OptimizeMap_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OptimizeMap_Result_

// alias to use template instance with default allocator
using OptimizeMap_Result =
  agt_interfaces::action::OptimizeMap_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__OptimizeMap_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__OptimizeMap_Feedback __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct OptimizeMap_Feedback_
{
  using Type = OptimizeMap_Feedback_<ContainerAllocator>;

  explicit OptimizeMap_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stage = "";
      this->progress = 0.0f;
      this->message = "";
    }
  }

  explicit OptimizeMap_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stage(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stage = "";
      this->progress = 0.0f;
      this->message = "";
    }
  }

  // field types and members
  using _stage_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _stage_type stage;
  using _progress_type =
    float;
  _progress_type progress;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__stage(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->stage = _arg;
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
    agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_Feedback
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_Feedback
    std::shared_ptr<agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OptimizeMap_Feedback_ & other) const
  {
    if (this->stage != other.stage) {
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
  bool operator!=(const OptimizeMap_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OptimizeMap_Feedback_

// alias to use template instance with default allocator
using OptimizeMap_Feedback =
  agt_interfaces::action::OptimizeMap_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/optimize_map__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__OptimizeMap_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__OptimizeMap_SendGoal_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct OptimizeMap_SendGoal_Request_
{
  using Type = OptimizeMap_SendGoal_Request_<ContainerAllocator>;

  explicit OptimizeMap_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit OptimizeMap_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const agt_interfaces::action::OptimizeMap_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_SendGoal_Request
    std::shared_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OptimizeMap_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const OptimizeMap_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OptimizeMap_SendGoal_Request_

// alias to use template instance with default allocator
using OptimizeMap_SendGoal_Request =
  agt_interfaces::action::OptimizeMap_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__OptimizeMap_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__OptimizeMap_SendGoal_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct OptimizeMap_SendGoal_Response_
{
  using Type = OptimizeMap_SendGoal_Response_<ContainerAllocator>;

  explicit OptimizeMap_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit OptimizeMap_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_SendGoal_Response
    std::shared_ptr<agt_interfaces::action::OptimizeMap_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OptimizeMap_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const OptimizeMap_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OptimizeMap_SendGoal_Response_

// alias to use template instance with default allocator
using OptimizeMap_SendGoal_Response =
  agt_interfaces::action::OptimizeMap_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct OptimizeMap_SendGoal
{
  using Request = agt_interfaces::action::OptimizeMap_SendGoal_Request;
  using Response = agt_interfaces::action::OptimizeMap_SendGoal_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__OptimizeMap_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__OptimizeMap_GetResult_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct OptimizeMap_GetResult_Request_
{
  using Type = OptimizeMap_GetResult_Request_<ContainerAllocator>;

  explicit OptimizeMap_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit OptimizeMap_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_GetResult_Request
    std::shared_ptr<agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_GetResult_Request
    std::shared_ptr<agt_interfaces::action::OptimizeMap_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OptimizeMap_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const OptimizeMap_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OptimizeMap_GetResult_Request_

// alias to use template instance with default allocator
using OptimizeMap_GetResult_Request =
  agt_interfaces::action::OptimizeMap_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__OptimizeMap_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__OptimizeMap_GetResult_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct OptimizeMap_GetResult_Response_
{
  using Type = OptimizeMap_GetResult_Response_<ContainerAllocator>;

  explicit OptimizeMap_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit OptimizeMap_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const agt_interfaces::action::OptimizeMap_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_GetResult_Response
    std::shared_ptr<agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_GetResult_Response
    std::shared_ptr<agt_interfaces::action::OptimizeMap_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OptimizeMap_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const OptimizeMap_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OptimizeMap_GetResult_Response_

// alias to use template instance with default allocator
using OptimizeMap_GetResult_Response =
  agt_interfaces::action::OptimizeMap_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace action
{

struct OptimizeMap_GetResult
{
  using Request = agt_interfaces::action::OptimizeMap_GetResult_Request;
  using Response = agt_interfaces::action::OptimizeMap_GetResult_Response;
};

}  // namespace action

}  // namespace agt_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__action__OptimizeMap_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__action__OptimizeMap_FeedbackMessage __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct OptimizeMap_FeedbackMessage_
{
  using Type = OptimizeMap_FeedbackMessage_<ContainerAllocator>;

  explicit OptimizeMap_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit OptimizeMap_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const agt_interfaces::action::OptimizeMap_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__action__OptimizeMap_FeedbackMessage
    std::shared_ptr<agt_interfaces::action::OptimizeMap_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OptimizeMap_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const OptimizeMap_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OptimizeMap_FeedbackMessage_

// alias to use template instance with default allocator
using OptimizeMap_FeedbackMessage =
  agt_interfaces::action::OptimizeMap_FeedbackMessage_<std::allocator<void>>;

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

struct OptimizeMap
{
  /// The goal message defined in the action definition.
  using Goal = agt_interfaces::action::OptimizeMap_Goal;
  /// The result message defined in the action definition.
  using Result = agt_interfaces::action::OptimizeMap_Result;
  /// The feedback message defined in the action definition.
  using Feedback = agt_interfaces::action::OptimizeMap_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = agt_interfaces::action::OptimizeMap_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = agt_interfaces::action::OptimizeMap_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = agt_interfaces::action::OptimizeMap_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct OptimizeMap OptimizeMap;

}  // namespace action

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__STRUCT_HPP_
