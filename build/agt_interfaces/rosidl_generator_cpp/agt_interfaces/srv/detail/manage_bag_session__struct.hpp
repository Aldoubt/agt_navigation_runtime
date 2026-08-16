// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:srv/ManageBagSession.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__STRUCT_HPP_
#define AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__ManageBagSession_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__ManageBagSession_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ManageBagSession_Request_
{
  using Type = ManageBagSession_Request_<ContainerAllocator>;

  explicit ManageBagSession_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->operation = 0;
      this->bag_id = "";
      this->experiment_id = "";
      this->experiment_title = "";
      this->objective = "";
      this->hypothesis = "";
      this->tags_json = "";
      this->operator_note = "";
      this->profile_id = "";
      this->playback_rate = 0.0;
      this->mission_id = "";
      this->mission_version = "";
      this->mission_sha256 = "";
      this->map_id = "";
      this->map_version_id = "";
      this->map_sha256 = "";
      this->platform_profile = "";
      this->calibration_profile = "";
      this->nav2_profile = "";
      this->launch_profile = "";
      this->start_experiment = false;
      this->event_type = "";
      this->metadata_json = "";
      this->result_status = "";
      this->reason = "";
    }
  }

  explicit ManageBagSession_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : bag_id(_alloc),
    experiment_id(_alloc),
    experiment_title(_alloc),
    objective(_alloc),
    hypothesis(_alloc),
    tags_json(_alloc),
    operator_note(_alloc),
    profile_id(_alloc),
    mission_id(_alloc),
    mission_version(_alloc),
    mission_sha256(_alloc),
    map_id(_alloc),
    map_version_id(_alloc),
    map_sha256(_alloc),
    platform_profile(_alloc),
    calibration_profile(_alloc),
    nav2_profile(_alloc),
    launch_profile(_alloc),
    event_type(_alloc),
    metadata_json(_alloc),
    result_status(_alloc),
    reason(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->operation = 0;
      this->bag_id = "";
      this->experiment_id = "";
      this->experiment_title = "";
      this->objective = "";
      this->hypothesis = "";
      this->tags_json = "";
      this->operator_note = "";
      this->profile_id = "";
      this->playback_rate = 0.0;
      this->mission_id = "";
      this->mission_version = "";
      this->mission_sha256 = "";
      this->map_id = "";
      this->map_version_id = "";
      this->map_sha256 = "";
      this->platform_profile = "";
      this->calibration_profile = "";
      this->nav2_profile = "";
      this->launch_profile = "";
      this->start_experiment = false;
      this->event_type = "";
      this->metadata_json = "";
      this->result_status = "";
      this->reason = "";
    }
  }

  // field types and members
  using _operation_type =
    uint8_t;
  _operation_type operation;
  using _bag_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _bag_id_type bag_id;
  using _experiment_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _experiment_id_type experiment_id;
  using _experiment_title_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _experiment_title_type experiment_title;
  using _objective_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _objective_type objective;
  using _hypothesis_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _hypothesis_type hypothesis;
  using _tags_json_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tags_json_type tags_json;
  using _operator_note_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _operator_note_type operator_note;
  using _profile_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _profile_id_type profile_id;
  using _playback_rate_type =
    double;
  _playback_rate_type playback_rate;
  using _mission_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_id_type mission_id;
  using _mission_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_version_type mission_version;
  using _mission_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_sha256_type mission_sha256;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_version_id_type map_version_id;
  using _map_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_sha256_type map_sha256;
  using _platform_profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _platform_profile_type platform_profile;
  using _calibration_profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _calibration_profile_type calibration_profile;
  using _nav2_profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _nav2_profile_type nav2_profile;
  using _launch_profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _launch_profile_type launch_profile;
  using _start_experiment_type =
    bool;
  _start_experiment_type start_experiment;
  using _event_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _event_type_type event_type;
  using _metadata_json_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _metadata_json_type metadata_json;
  using _result_status_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _result_status_type result_status;
  using _reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reason_type reason;

  // setters for named parameter idiom
  Type & set__operation(
    const uint8_t & _arg)
  {
    this->operation = _arg;
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
  Type & set__experiment_title(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->experiment_title = _arg;
    return *this;
  }
  Type & set__objective(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->objective = _arg;
    return *this;
  }
  Type & set__hypothesis(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->hypothesis = _arg;
    return *this;
  }
  Type & set__tags_json(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tags_json = _arg;
    return *this;
  }
  Type & set__operator_note(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->operator_note = _arg;
    return *this;
  }
  Type & set__profile_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->profile_id = _arg;
    return *this;
  }
  Type & set__playback_rate(
    const double & _arg)
  {
    this->playback_rate = _arg;
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
  Type & set__map_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_sha256 = _arg;
    return *this;
  }
  Type & set__platform_profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->platform_profile = _arg;
    return *this;
  }
  Type & set__calibration_profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->calibration_profile = _arg;
    return *this;
  }
  Type & set__nav2_profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->nav2_profile = _arg;
    return *this;
  }
  Type & set__launch_profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->launch_profile = _arg;
    return *this;
  }
  Type & set__start_experiment(
    const bool & _arg)
  {
    this->start_experiment = _arg;
    return *this;
  }
  Type & set__event_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->event_type = _arg;
    return *this;
  }
  Type & set__metadata_json(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->metadata_json = _arg;
    return *this;
  }
  Type & set__result_status(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->result_status = _arg;
    return *this;
  }
  Type & set__reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reason = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t OP_STATUS =
    0u;
  static constexpr uint8_t OP_START_RECORDING =
    1u;
  static constexpr uint8_t OP_STOP_RECORDING =
    2u;
  static constexpr uint8_t OP_START_PLAYBACK =
    3u;
  static constexpr uint8_t OP_STOP_PLAYBACK =
    4u;
  static constexpr uint8_t OP_CREATE_EXPERIMENT =
    5u;
  static constexpr uint8_t OP_COMPLETE_EXPERIMENT =
    6u;
  static constexpr uint8_t OP_INTERRUPT_EXPERIMENT =
    7u;
  static constexpr uint8_t OP_START_EXPERIMENT =
    8u;
  static constexpr uint8_t OP_MARK_EXPERIMENT_INVALID =
    9u;
  static constexpr uint8_t OP_ADD_EXPERIMENT_EVENT =
    10u;

  // pointer types
  using RawPtr =
    agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__ManageBagSession_Request
    std::shared_ptr<agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__ManageBagSession_Request
    std::shared_ptr<agt_interfaces::srv::ManageBagSession_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ManageBagSession_Request_ & other) const
  {
    if (this->operation != other.operation) {
      return false;
    }
    if (this->bag_id != other.bag_id) {
      return false;
    }
    if (this->experiment_id != other.experiment_id) {
      return false;
    }
    if (this->experiment_title != other.experiment_title) {
      return false;
    }
    if (this->objective != other.objective) {
      return false;
    }
    if (this->hypothesis != other.hypothesis) {
      return false;
    }
    if (this->tags_json != other.tags_json) {
      return false;
    }
    if (this->operator_note != other.operator_note) {
      return false;
    }
    if (this->profile_id != other.profile_id) {
      return false;
    }
    if (this->playback_rate != other.playback_rate) {
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
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->map_version_id != other.map_version_id) {
      return false;
    }
    if (this->map_sha256 != other.map_sha256) {
      return false;
    }
    if (this->platform_profile != other.platform_profile) {
      return false;
    }
    if (this->calibration_profile != other.calibration_profile) {
      return false;
    }
    if (this->nav2_profile != other.nav2_profile) {
      return false;
    }
    if (this->launch_profile != other.launch_profile) {
      return false;
    }
    if (this->start_experiment != other.start_experiment) {
      return false;
    }
    if (this->event_type != other.event_type) {
      return false;
    }
    if (this->metadata_json != other.metadata_json) {
      return false;
    }
    if (this->result_status != other.result_status) {
      return false;
    }
    if (this->reason != other.reason) {
      return false;
    }
    return true;
  }
  bool operator!=(const ManageBagSession_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ManageBagSession_Request_

// alias to use template instance with default allocator
using ManageBagSession_Request =
  agt_interfaces::srv::ManageBagSession_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_STATUS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_START_RECORDING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_STOP_RECORDING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_START_PLAYBACK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_STOP_PLAYBACK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_CREATE_EXPERIMENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_COMPLETE_EXPERIMENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_INTERRUPT_EXPERIMENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_START_EXPERIMENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_MARK_EXPERIMENT_INVALID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageBagSession_Request_<ContainerAllocator>::OP_ADD_EXPERIMENT_EVENT;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace agt_interfaces


// Include directives for member types
// Member 'session'
#include "agt_interfaces/msg/detail/bag_session_summary__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__ManageBagSession_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__ManageBagSession_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ManageBagSession_Response_
{
  using Type = ManageBagSession_Response_<ContainerAllocator>;

  explicit ManageBagSession_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : session(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->message = "";
    }
  }

  explicit ManageBagSession_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : session(_alloc, _init),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
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
  using _session_type =
    agt_interfaces::msg::BagSessionSummary_<ContainerAllocator>;
  _session_type session;
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
  Type & set__session(
    const agt_interfaces::msg::BagSessionSummary_<ContainerAllocator> & _arg)
  {
    this->session = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t ERROR_NONE =
    0u;
  static constexpr uint16_t ERROR_NOT_FOUND =
    1u;
  static constexpr uint16_t ERROR_INVALID_REQUEST =
    2u;
  static constexpr uint16_t ERROR_CONFLICT =
    3u;
  static constexpr uint16_t ERROR_PROFILE_INVALID =
    4u;
  static constexpr uint16_t ERROR_INTERNAL =
    255u;

  // pointer types
  using RawPtr =
    agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__ManageBagSession_Response
    std::shared_ptr<agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__ManageBagSession_Response
    std::shared_ptr<agt_interfaces::srv::ManageBagSession_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ManageBagSession_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->session != other.session) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ManageBagSession_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ManageBagSession_Response_

// alias to use template instance with default allocator
using ManageBagSession_Response =
  agt_interfaces::srv::ManageBagSession_Response_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageBagSession_Response_<ContainerAllocator>::ERROR_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageBagSession_Response_<ContainerAllocator>::ERROR_NOT_FOUND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageBagSession_Response_<ContainerAllocator>::ERROR_INVALID_REQUEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageBagSession_Response_<ContainerAllocator>::ERROR_CONFLICT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageBagSession_Response_<ContainerAllocator>::ERROR_PROFILE_INVALID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageBagSession_Response_<ContainerAllocator>::ERROR_INTERNAL;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace srv
{

struct ManageBagSession
{
  using Request = agt_interfaces::srv::ManageBagSession_Request;
  using Response = agt_interfaces::srv::ManageBagSession_Response;
};

}  // namespace srv

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__STRUCT_HPP_
