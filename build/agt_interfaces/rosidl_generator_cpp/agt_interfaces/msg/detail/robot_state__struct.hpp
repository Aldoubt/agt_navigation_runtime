// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/RobotState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__STRUCT_HPP_

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
// Member 'system_health'
#include "agt_interfaces/msg/detail/system_health__struct.hpp"
// Member 'task_readiness'
#include "agt_interfaces/msg/detail/task_readiness__struct.hpp"
// Member 'active_map'
#include "agt_interfaces/msg/detail/map_version_summary__struct.hpp"
// Member 'localization'
#include "agt_interfaces/msg/detail/localization_status__struct.hpp"
// Member 'mission'
#include "agt_interfaces/msg/detail/mission_status__struct.hpp"
// Member 'bag_session'
#include "agt_interfaces/msg/detail/bag_session_summary__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__msg__RobotState __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__RobotState __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotState_
{
  using Type = RobotState_<ContainerAllocator>;

  explicit RobotState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    system_health(_init),
    task_readiness(_init),
    active_map(_init),
    localization(_init),
    mission(_init),
    bag_session(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->revision = 0ull;
      this->system_mode = 0;
      this->active_profile = "";
      this->managed_process_count = 0ul;
      this->running_process_count = 0ul;
      this->system_health_known = false;
      this->system_health_freshness_s = 0.0;
      this->task_readiness_known = false;
      this->task_readiness_freshness_s = 0.0;
      this->active_map_known = false;
      this->active_map_freshness_s = 0.0;
      this->localization_status_known = false;
      this->localization_freshness_s = 0.0;
      this->mission_status_known = false;
      this->mission_freshness_s = 0.0;
      this->nav2_state = 0;
      this->nav2_freshness_s = 0.0;
      this->safety_status_known = false;
      this->safety_motion_enabled = false;
      this->emergency_stop = false;
      this->estop_latched = false;
      this->navigation_ready = false;
      this->safety_freshness_s = 0.0;
      this->chassis_status_known = false;
      this->chassis_connected = false;
      this->chassis_control_mode = 0;
      this->chassis_status_freshness_s = 0.0;
      this->chassis_odometry_freshness_s = 0.0;
      this->bag_status_known = false;
      this->bag_freshness_s = 0.0;
      this->error_code = 0;
      this->message = "";
    }
  }

  explicit RobotState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    active_profile(_alloc),
    system_health(_alloc, _init),
    task_readiness(_alloc, _init),
    active_map(_alloc, _init),
    localization(_alloc, _init),
    mission(_alloc, _init),
    bag_session(_alloc, _init),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->revision = 0ull;
      this->system_mode = 0;
      this->active_profile = "";
      this->managed_process_count = 0ul;
      this->running_process_count = 0ul;
      this->system_health_known = false;
      this->system_health_freshness_s = 0.0;
      this->task_readiness_known = false;
      this->task_readiness_freshness_s = 0.0;
      this->active_map_known = false;
      this->active_map_freshness_s = 0.0;
      this->localization_status_known = false;
      this->localization_freshness_s = 0.0;
      this->mission_status_known = false;
      this->mission_freshness_s = 0.0;
      this->nav2_state = 0;
      this->nav2_freshness_s = 0.0;
      this->safety_status_known = false;
      this->safety_motion_enabled = false;
      this->emergency_stop = false;
      this->estop_latched = false;
      this->navigation_ready = false;
      this->safety_freshness_s = 0.0;
      this->chassis_status_known = false;
      this->chassis_connected = false;
      this->chassis_control_mode = 0;
      this->chassis_status_freshness_s = 0.0;
      this->chassis_odometry_freshness_s = 0.0;
      this->bag_status_known = false;
      this->bag_freshness_s = 0.0;
      this->error_code = 0;
      this->message = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _revision_type =
    uint64_t;
  _revision_type revision;
  using _system_mode_type =
    uint8_t;
  _system_mode_type system_mode;
  using _active_profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _active_profile_type active_profile;
  using _managed_process_count_type =
    uint32_t;
  _managed_process_count_type managed_process_count;
  using _running_process_count_type =
    uint32_t;
  _running_process_count_type running_process_count;
  using _system_health_known_type =
    bool;
  _system_health_known_type system_health_known;
  using _system_health_freshness_s_type =
    double;
  _system_health_freshness_s_type system_health_freshness_s;
  using _system_health_type =
    agt_interfaces::msg::SystemHealth_<ContainerAllocator>;
  _system_health_type system_health;
  using _task_readiness_known_type =
    bool;
  _task_readiness_known_type task_readiness_known;
  using _task_readiness_freshness_s_type =
    double;
  _task_readiness_freshness_s_type task_readiness_freshness_s;
  using _task_readiness_type =
    agt_interfaces::msg::TaskReadiness_<ContainerAllocator>;
  _task_readiness_type task_readiness;
  using _active_map_known_type =
    bool;
  _active_map_known_type active_map_known;
  using _active_map_freshness_s_type =
    double;
  _active_map_freshness_s_type active_map_freshness_s;
  using _active_map_type =
    agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>;
  _active_map_type active_map;
  using _localization_status_known_type =
    bool;
  _localization_status_known_type localization_status_known;
  using _localization_freshness_s_type =
    double;
  _localization_freshness_s_type localization_freshness_s;
  using _localization_type =
    agt_interfaces::msg::LocalizationStatus_<ContainerAllocator>;
  _localization_type localization;
  using _mission_status_known_type =
    bool;
  _mission_status_known_type mission_status_known;
  using _mission_freshness_s_type =
    double;
  _mission_freshness_s_type mission_freshness_s;
  using _mission_type =
    agt_interfaces::msg::MissionStatus_<ContainerAllocator>;
  _mission_type mission;
  using _nav2_state_type =
    uint8_t;
  _nav2_state_type nav2_state;
  using _nav2_freshness_s_type =
    double;
  _nav2_freshness_s_type nav2_freshness_s;
  using _safety_status_known_type =
    bool;
  _safety_status_known_type safety_status_known;
  using _safety_motion_enabled_type =
    bool;
  _safety_motion_enabled_type safety_motion_enabled;
  using _emergency_stop_type =
    bool;
  _emergency_stop_type emergency_stop;
  using _estop_latched_type =
    bool;
  _estop_latched_type estop_latched;
  using _navigation_ready_type =
    bool;
  _navigation_ready_type navigation_ready;
  using _safety_freshness_s_type =
    double;
  _safety_freshness_s_type safety_freshness_s;
  using _chassis_status_known_type =
    bool;
  _chassis_status_known_type chassis_status_known;
  using _chassis_connected_type =
    bool;
  _chassis_connected_type chassis_connected;
  using _chassis_control_mode_type =
    uint8_t;
  _chassis_control_mode_type chassis_control_mode;
  using _chassis_status_freshness_s_type =
    double;
  _chassis_status_freshness_s_type chassis_status_freshness_s;
  using _chassis_odometry_freshness_s_type =
    double;
  _chassis_odometry_freshness_s_type chassis_odometry_freshness_s;
  using _bag_status_known_type =
    bool;
  _bag_status_known_type bag_status_known;
  using _bag_freshness_s_type =
    double;
  _bag_freshness_s_type bag_freshness_s;
  using _bag_session_type =
    agt_interfaces::msg::BagSessionSummary_<ContainerAllocator>;
  _bag_session_type bag_session;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;
  using _blocker_codes_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _blocker_codes_type blocker_codes;
  using _blocker_messages_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _blocker_messages_type blocker_messages;
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
  Type & set__revision(
    const uint64_t & _arg)
  {
    this->revision = _arg;
    return *this;
  }
  Type & set__system_mode(
    const uint8_t & _arg)
  {
    this->system_mode = _arg;
    return *this;
  }
  Type & set__active_profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->active_profile = _arg;
    return *this;
  }
  Type & set__managed_process_count(
    const uint32_t & _arg)
  {
    this->managed_process_count = _arg;
    return *this;
  }
  Type & set__running_process_count(
    const uint32_t & _arg)
  {
    this->running_process_count = _arg;
    return *this;
  }
  Type & set__system_health_known(
    const bool & _arg)
  {
    this->system_health_known = _arg;
    return *this;
  }
  Type & set__system_health_freshness_s(
    const double & _arg)
  {
    this->system_health_freshness_s = _arg;
    return *this;
  }
  Type & set__system_health(
    const agt_interfaces::msg::SystemHealth_<ContainerAllocator> & _arg)
  {
    this->system_health = _arg;
    return *this;
  }
  Type & set__task_readiness_known(
    const bool & _arg)
  {
    this->task_readiness_known = _arg;
    return *this;
  }
  Type & set__task_readiness_freshness_s(
    const double & _arg)
  {
    this->task_readiness_freshness_s = _arg;
    return *this;
  }
  Type & set__task_readiness(
    const agt_interfaces::msg::TaskReadiness_<ContainerAllocator> & _arg)
  {
    this->task_readiness = _arg;
    return *this;
  }
  Type & set__active_map_known(
    const bool & _arg)
  {
    this->active_map_known = _arg;
    return *this;
  }
  Type & set__active_map_freshness_s(
    const double & _arg)
  {
    this->active_map_freshness_s = _arg;
    return *this;
  }
  Type & set__active_map(
    const agt_interfaces::msg::MapVersionSummary_<ContainerAllocator> & _arg)
  {
    this->active_map = _arg;
    return *this;
  }
  Type & set__localization_status_known(
    const bool & _arg)
  {
    this->localization_status_known = _arg;
    return *this;
  }
  Type & set__localization_freshness_s(
    const double & _arg)
  {
    this->localization_freshness_s = _arg;
    return *this;
  }
  Type & set__localization(
    const agt_interfaces::msg::LocalizationStatus_<ContainerAllocator> & _arg)
  {
    this->localization = _arg;
    return *this;
  }
  Type & set__mission_status_known(
    const bool & _arg)
  {
    this->mission_status_known = _arg;
    return *this;
  }
  Type & set__mission_freshness_s(
    const double & _arg)
  {
    this->mission_freshness_s = _arg;
    return *this;
  }
  Type & set__mission(
    const agt_interfaces::msg::MissionStatus_<ContainerAllocator> & _arg)
  {
    this->mission = _arg;
    return *this;
  }
  Type & set__nav2_state(
    const uint8_t & _arg)
  {
    this->nav2_state = _arg;
    return *this;
  }
  Type & set__nav2_freshness_s(
    const double & _arg)
  {
    this->nav2_freshness_s = _arg;
    return *this;
  }
  Type & set__safety_status_known(
    const bool & _arg)
  {
    this->safety_status_known = _arg;
    return *this;
  }
  Type & set__safety_motion_enabled(
    const bool & _arg)
  {
    this->safety_motion_enabled = _arg;
    return *this;
  }
  Type & set__emergency_stop(
    const bool & _arg)
  {
    this->emergency_stop = _arg;
    return *this;
  }
  Type & set__estop_latched(
    const bool & _arg)
  {
    this->estop_latched = _arg;
    return *this;
  }
  Type & set__navigation_ready(
    const bool & _arg)
  {
    this->navigation_ready = _arg;
    return *this;
  }
  Type & set__safety_freshness_s(
    const double & _arg)
  {
    this->safety_freshness_s = _arg;
    return *this;
  }
  Type & set__chassis_status_known(
    const bool & _arg)
  {
    this->chassis_status_known = _arg;
    return *this;
  }
  Type & set__chassis_connected(
    const bool & _arg)
  {
    this->chassis_connected = _arg;
    return *this;
  }
  Type & set__chassis_control_mode(
    const uint8_t & _arg)
  {
    this->chassis_control_mode = _arg;
    return *this;
  }
  Type & set__chassis_status_freshness_s(
    const double & _arg)
  {
    this->chassis_status_freshness_s = _arg;
    return *this;
  }
  Type & set__chassis_odometry_freshness_s(
    const double & _arg)
  {
    this->chassis_odometry_freshness_s = _arg;
    return *this;
  }
  Type & set__bag_status_known(
    const bool & _arg)
  {
    this->bag_status_known = _arg;
    return *this;
  }
  Type & set__bag_freshness_s(
    const double & _arg)
  {
    this->bag_freshness_s = _arg;
    return *this;
  }
  Type & set__bag_session(
    const agt_interfaces::msg::BagSessionSummary_<ContainerAllocator> & _arg)
  {
    this->bag_session = _arg;
    return *this;
  }
  Type & set__error_code(
    const uint16_t & _arg)
  {
    this->error_code = _arg;
    return *this;
  }
  Type & set__blocker_codes(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->blocker_codes = _arg;
    return *this;
  }
  Type & set__blocker_messages(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->blocker_messages = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MODE_UNKNOWN =
    0u;
  static constexpr uint8_t MODE_IDLE =
    1u;
  static constexpr uint8_t MODE_SENSOR_ONLY =
    2u;
  static constexpr uint8_t MODE_MAPPING =
    3u;
  static constexpr uint8_t MODE_LOCALIZATION_DEBUG =
    4u;
  static constexpr uint8_t MODE_NAVIGATION =
    5u;
  static constexpr uint8_t MODE_ERROR =
    6u;
  static constexpr uint8_t NAV2_UNKNOWN =
    0u;
  static constexpr uint8_t NAV2_INACTIVE =
    1u;
  static constexpr uint8_t NAV2_ACTIVE =
    2u;
  static constexpr uint8_t NAV2_ERROR =
    3u;
  static constexpr uint8_t CHASSIS_MODE_UNKNOWN =
    0u;
  static constexpr uint8_t CHASSIS_MODE_MONITOR =
    1u;
  static constexpr uint8_t CHASSIS_MODE_CONTROL =
    2u;

  // pointer types
  using RawPtr =
    agt_interfaces::msg::RobotState_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::RobotState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::RobotState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::RobotState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::RobotState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::RobotState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::RobotState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::RobotState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::RobotState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::RobotState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__RobotState
    std::shared_ptr<agt_interfaces::msg::RobotState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__RobotState
    std::shared_ptr<agt_interfaces::msg::RobotState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->revision != other.revision) {
      return false;
    }
    if (this->system_mode != other.system_mode) {
      return false;
    }
    if (this->active_profile != other.active_profile) {
      return false;
    }
    if (this->managed_process_count != other.managed_process_count) {
      return false;
    }
    if (this->running_process_count != other.running_process_count) {
      return false;
    }
    if (this->system_health_known != other.system_health_known) {
      return false;
    }
    if (this->system_health_freshness_s != other.system_health_freshness_s) {
      return false;
    }
    if (this->system_health != other.system_health) {
      return false;
    }
    if (this->task_readiness_known != other.task_readiness_known) {
      return false;
    }
    if (this->task_readiness_freshness_s != other.task_readiness_freshness_s) {
      return false;
    }
    if (this->task_readiness != other.task_readiness) {
      return false;
    }
    if (this->active_map_known != other.active_map_known) {
      return false;
    }
    if (this->active_map_freshness_s != other.active_map_freshness_s) {
      return false;
    }
    if (this->active_map != other.active_map) {
      return false;
    }
    if (this->localization_status_known != other.localization_status_known) {
      return false;
    }
    if (this->localization_freshness_s != other.localization_freshness_s) {
      return false;
    }
    if (this->localization != other.localization) {
      return false;
    }
    if (this->mission_status_known != other.mission_status_known) {
      return false;
    }
    if (this->mission_freshness_s != other.mission_freshness_s) {
      return false;
    }
    if (this->mission != other.mission) {
      return false;
    }
    if (this->nav2_state != other.nav2_state) {
      return false;
    }
    if (this->nav2_freshness_s != other.nav2_freshness_s) {
      return false;
    }
    if (this->safety_status_known != other.safety_status_known) {
      return false;
    }
    if (this->safety_motion_enabled != other.safety_motion_enabled) {
      return false;
    }
    if (this->emergency_stop != other.emergency_stop) {
      return false;
    }
    if (this->estop_latched != other.estop_latched) {
      return false;
    }
    if (this->navigation_ready != other.navigation_ready) {
      return false;
    }
    if (this->safety_freshness_s != other.safety_freshness_s) {
      return false;
    }
    if (this->chassis_status_known != other.chassis_status_known) {
      return false;
    }
    if (this->chassis_connected != other.chassis_connected) {
      return false;
    }
    if (this->chassis_control_mode != other.chassis_control_mode) {
      return false;
    }
    if (this->chassis_status_freshness_s != other.chassis_status_freshness_s) {
      return false;
    }
    if (this->chassis_odometry_freshness_s != other.chassis_odometry_freshness_s) {
      return false;
    }
    if (this->bag_status_known != other.bag_status_known) {
      return false;
    }
    if (this->bag_freshness_s != other.bag_freshness_s) {
      return false;
    }
    if (this->bag_session != other.bag_session) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->blocker_codes != other.blocker_codes) {
      return false;
    }
    if (this->blocker_messages != other.blocker_messages) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotState_

// alias to use template instance with default allocator
using RobotState =
  agt_interfaces::msg::RobotState_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::MODE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::MODE_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::MODE_SENSOR_ONLY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::MODE_MAPPING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::MODE_LOCALIZATION_DEBUG;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::MODE_NAVIGATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::MODE_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::NAV2_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::NAV2_INACTIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::NAV2_ACTIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::NAV2_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::CHASSIS_MODE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::CHASSIS_MODE_MONITOR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t RobotState_<ContainerAllocator>::CHASSIS_MODE_CONTROL;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__STRUCT_HPP_
