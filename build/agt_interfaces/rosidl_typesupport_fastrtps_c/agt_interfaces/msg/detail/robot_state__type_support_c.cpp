// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from agt_interfaces:msg/RobotState.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/robot_state__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "agt_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "agt_interfaces/msg/detail/robot_state__struct.h"
#include "agt_interfaces/msg/detail/robot_state__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "agt_interfaces/msg/detail/bag_session_summary__functions.h"  // bag_session
#include "agt_interfaces/msg/detail/localization_status__functions.h"  // localization
#include "agt_interfaces/msg/detail/map_version_summary__functions.h"  // active_map
#include "agt_interfaces/msg/detail/mission_status__functions.h"  // mission
#include "agt_interfaces/msg/detail/system_health__functions.h"  // system_health
#include "agt_interfaces/msg/detail/task_readiness__functions.h"  // task_readiness
#include "rosidl_runtime_c/string.h"  // active_profile, blocker_codes, blocker_messages, message
#include "rosidl_runtime_c/string_functions.h"  // active_profile, blocker_codes, blocker_messages, message
#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions
size_t get_serialized_size_agt_interfaces__msg__BagSessionSummary(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_agt_interfaces__msg__BagSessionSummary(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, BagSessionSummary)();
size_t get_serialized_size_agt_interfaces__msg__LocalizationStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_agt_interfaces__msg__LocalizationStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, LocalizationStatus)();
size_t get_serialized_size_agt_interfaces__msg__MapVersionSummary(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_agt_interfaces__msg__MapVersionSummary(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, MapVersionSummary)();
size_t get_serialized_size_agt_interfaces__msg__MissionStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_agt_interfaces__msg__MissionStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, MissionStatus)();
size_t get_serialized_size_agt_interfaces__msg__SystemHealth(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_agt_interfaces__msg__SystemHealth(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, SystemHealth)();
size_t get_serialized_size_agt_interfaces__msg__TaskReadiness(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_agt_interfaces__msg__TaskReadiness(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, TaskReadiness)();
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_agt_interfaces
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_agt_interfaces
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_agt_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _RobotState__ros_msg_type = agt_interfaces__msg__RobotState;

static bool _RobotState__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _RobotState__ros_msg_type * ros_message = static_cast<const _RobotState__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: revision
  {
    cdr << ros_message->revision;
  }

  // Field name: system_mode
  {
    cdr << ros_message->system_mode;
  }

  // Field name: active_profile
  {
    const rosidl_runtime_c__String * str = &ros_message->active_profile;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: managed_process_count
  {
    cdr << ros_message->managed_process_count;
  }

  // Field name: running_process_count
  {
    cdr << ros_message->running_process_count;
  }

  // Field name: system_health_known
  {
    cdr << (ros_message->system_health_known ? true : false);
  }

  // Field name: system_health_freshness_s
  {
    cdr << ros_message->system_health_freshness_s;
  }

  // Field name: system_health
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, SystemHealth
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->system_health, cdr))
    {
      return false;
    }
  }

  // Field name: task_readiness_known
  {
    cdr << (ros_message->task_readiness_known ? true : false);
  }

  // Field name: task_readiness_freshness_s
  {
    cdr << ros_message->task_readiness_freshness_s;
  }

  // Field name: task_readiness
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, TaskReadiness
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->task_readiness, cdr))
    {
      return false;
    }
  }

  // Field name: active_map_known
  {
    cdr << (ros_message->active_map_known ? true : false);
  }

  // Field name: active_map_freshness_s
  {
    cdr << ros_message->active_map_freshness_s;
  }

  // Field name: active_map
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, MapVersionSummary
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->active_map, cdr))
    {
      return false;
    }
  }

  // Field name: localization_status_known
  {
    cdr << (ros_message->localization_status_known ? true : false);
  }

  // Field name: localization_freshness_s
  {
    cdr << ros_message->localization_freshness_s;
  }

  // Field name: localization
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, LocalizationStatus
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->localization, cdr))
    {
      return false;
    }
  }

  // Field name: mission_status_known
  {
    cdr << (ros_message->mission_status_known ? true : false);
  }

  // Field name: mission_freshness_s
  {
    cdr << ros_message->mission_freshness_s;
  }

  // Field name: mission
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, MissionStatus
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->mission, cdr))
    {
      return false;
    }
  }

  // Field name: nav2_state
  {
    cdr << ros_message->nav2_state;
  }

  // Field name: nav2_freshness_s
  {
    cdr << ros_message->nav2_freshness_s;
  }

  // Field name: safety_status_known
  {
    cdr << (ros_message->safety_status_known ? true : false);
  }

  // Field name: safety_motion_enabled
  {
    cdr << (ros_message->safety_motion_enabled ? true : false);
  }

  // Field name: emergency_stop
  {
    cdr << (ros_message->emergency_stop ? true : false);
  }

  // Field name: estop_latched
  {
    cdr << (ros_message->estop_latched ? true : false);
  }

  // Field name: navigation_ready
  {
    cdr << (ros_message->navigation_ready ? true : false);
  }

  // Field name: safety_freshness_s
  {
    cdr << ros_message->safety_freshness_s;
  }

  // Field name: chassis_status_known
  {
    cdr << (ros_message->chassis_status_known ? true : false);
  }

  // Field name: chassis_connected
  {
    cdr << (ros_message->chassis_connected ? true : false);
  }

  // Field name: chassis_control_mode
  {
    cdr << ros_message->chassis_control_mode;
  }

  // Field name: chassis_status_freshness_s
  {
    cdr << ros_message->chassis_status_freshness_s;
  }

  // Field name: chassis_odometry_freshness_s
  {
    cdr << ros_message->chassis_odometry_freshness_s;
  }

  // Field name: bag_status_known
  {
    cdr << (ros_message->bag_status_known ? true : false);
  }

  // Field name: bag_freshness_s
  {
    cdr << ros_message->bag_freshness_s;
  }

  // Field name: bag_session
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, BagSessionSummary
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->bag_session, cdr))
    {
      return false;
    }
  }

  // Field name: error_code
  {
    cdr << ros_message->error_code;
  }

  // Field name: blocker_codes
  {
    size_t size = ros_message->blocker_codes.size;
    auto array_ptr = ros_message->blocker_codes.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
      if (str->capacity == 0 || str->capacity <= str->size) {
        fprintf(stderr, "string capacity not greater than size\n");
        return false;
      }
      if (str->data[str->size] != '\0') {
        fprintf(stderr, "string not null-terminated\n");
        return false;
      }
      cdr << str->data;
    }
  }

  // Field name: blocker_messages
  {
    size_t size = ros_message->blocker_messages.size;
    auto array_ptr = ros_message->blocker_messages.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
      if (str->capacity == 0 || str->capacity <= str->size) {
        fprintf(stderr, "string capacity not greater than size\n");
        return false;
      }
      if (str->data[str->size] != '\0') {
        fprintf(stderr, "string not null-terminated\n");
        return false;
      }
      cdr << str->data;
    }
  }

  // Field name: message
  {
    const rosidl_runtime_c__String * str = &ros_message->message;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _RobotState__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _RobotState__ros_msg_type * ros_message = static_cast<_RobotState__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: revision
  {
    cdr >> ros_message->revision;
  }

  // Field name: system_mode
  {
    cdr >> ros_message->system_mode;
  }

  // Field name: active_profile
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->active_profile.data) {
      rosidl_runtime_c__String__init(&ros_message->active_profile);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->active_profile,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'active_profile'\n");
      return false;
    }
  }

  // Field name: managed_process_count
  {
    cdr >> ros_message->managed_process_count;
  }

  // Field name: running_process_count
  {
    cdr >> ros_message->running_process_count;
  }

  // Field name: system_health_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->system_health_known = tmp ? true : false;
  }

  // Field name: system_health_freshness_s
  {
    cdr >> ros_message->system_health_freshness_s;
  }

  // Field name: system_health
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, SystemHealth
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->system_health))
    {
      return false;
    }
  }

  // Field name: task_readiness_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->task_readiness_known = tmp ? true : false;
  }

  // Field name: task_readiness_freshness_s
  {
    cdr >> ros_message->task_readiness_freshness_s;
  }

  // Field name: task_readiness
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, TaskReadiness
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->task_readiness))
    {
      return false;
    }
  }

  // Field name: active_map_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->active_map_known = tmp ? true : false;
  }

  // Field name: active_map_freshness_s
  {
    cdr >> ros_message->active_map_freshness_s;
  }

  // Field name: active_map
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, MapVersionSummary
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->active_map))
    {
      return false;
    }
  }

  // Field name: localization_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->localization_status_known = tmp ? true : false;
  }

  // Field name: localization_freshness_s
  {
    cdr >> ros_message->localization_freshness_s;
  }

  // Field name: localization
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, LocalizationStatus
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->localization))
    {
      return false;
    }
  }

  // Field name: mission_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->mission_status_known = tmp ? true : false;
  }

  // Field name: mission_freshness_s
  {
    cdr >> ros_message->mission_freshness_s;
  }

  // Field name: mission
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, MissionStatus
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->mission))
    {
      return false;
    }
  }

  // Field name: nav2_state
  {
    cdr >> ros_message->nav2_state;
  }

  // Field name: nav2_freshness_s
  {
    cdr >> ros_message->nav2_freshness_s;
  }

  // Field name: safety_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->safety_status_known = tmp ? true : false;
  }

  // Field name: safety_motion_enabled
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->safety_motion_enabled = tmp ? true : false;
  }

  // Field name: emergency_stop
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->emergency_stop = tmp ? true : false;
  }

  // Field name: estop_latched
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->estop_latched = tmp ? true : false;
  }

  // Field name: navigation_ready
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->navigation_ready = tmp ? true : false;
  }

  // Field name: safety_freshness_s
  {
    cdr >> ros_message->safety_freshness_s;
  }

  // Field name: chassis_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->chassis_status_known = tmp ? true : false;
  }

  // Field name: chassis_connected
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->chassis_connected = tmp ? true : false;
  }

  // Field name: chassis_control_mode
  {
    cdr >> ros_message->chassis_control_mode;
  }

  // Field name: chassis_status_freshness_s
  {
    cdr >> ros_message->chassis_status_freshness_s;
  }

  // Field name: chassis_odometry_freshness_s
  {
    cdr >> ros_message->chassis_odometry_freshness_s;
  }

  // Field name: bag_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->bag_status_known = tmp ? true : false;
  }

  // Field name: bag_freshness_s
  {
    cdr >> ros_message->bag_freshness_s;
  }

  // Field name: bag_session
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, BagSessionSummary
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->bag_session))
    {
      return false;
    }
  }

  // Field name: error_code
  {
    cdr >> ros_message->error_code;
  }

  // Field name: blocker_codes
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->blocker_codes.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->blocker_codes);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->blocker_codes, size)) {
      fprintf(stderr, "failed to create array for field 'blocker_codes'");
      return false;
    }
    auto array_ptr = ros_message->blocker_codes.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'blocker_codes'\n");
        return false;
      }
    }
  }

  // Field name: blocker_messages
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->blocker_messages.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->blocker_messages);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->blocker_messages, size)) {
      fprintf(stderr, "failed to create array for field 'blocker_messages'");
      return false;
    }
    auto array_ptr = ros_message->blocker_messages.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'blocker_messages'\n");
        return false;
      }
    }
  }

  // Field name: message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->message.data) {
      rosidl_runtime_c__String__init(&ros_message->message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'message'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t get_serialized_size_agt_interfaces__msg__RobotState(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _RobotState__ros_msg_type * ros_message = static_cast<const _RobotState__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name revision
  {
    size_t item_size = sizeof(ros_message->revision);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name system_mode
  {
    size_t item_size = sizeof(ros_message->system_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name active_profile
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->active_profile.size + 1);
  // field.name managed_process_count
  {
    size_t item_size = sizeof(ros_message->managed_process_count);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name running_process_count
  {
    size_t item_size = sizeof(ros_message->running_process_count);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name system_health_known
  {
    size_t item_size = sizeof(ros_message->system_health_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name system_health_freshness_s
  {
    size_t item_size = sizeof(ros_message->system_health_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name system_health

  current_alignment += get_serialized_size_agt_interfaces__msg__SystemHealth(
    &(ros_message->system_health), current_alignment);
  // field.name task_readiness_known
  {
    size_t item_size = sizeof(ros_message->task_readiness_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name task_readiness_freshness_s
  {
    size_t item_size = sizeof(ros_message->task_readiness_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name task_readiness

  current_alignment += get_serialized_size_agt_interfaces__msg__TaskReadiness(
    &(ros_message->task_readiness), current_alignment);
  // field.name active_map_known
  {
    size_t item_size = sizeof(ros_message->active_map_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name active_map_freshness_s
  {
    size_t item_size = sizeof(ros_message->active_map_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name active_map

  current_alignment += get_serialized_size_agt_interfaces__msg__MapVersionSummary(
    &(ros_message->active_map), current_alignment);
  // field.name localization_status_known
  {
    size_t item_size = sizeof(ros_message->localization_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name localization_freshness_s
  {
    size_t item_size = sizeof(ros_message->localization_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name localization

  current_alignment += get_serialized_size_agt_interfaces__msg__LocalizationStatus(
    &(ros_message->localization), current_alignment);
  // field.name mission_status_known
  {
    size_t item_size = sizeof(ros_message->mission_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mission_freshness_s
  {
    size_t item_size = sizeof(ros_message->mission_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mission

  current_alignment += get_serialized_size_agt_interfaces__msg__MissionStatus(
    &(ros_message->mission), current_alignment);
  // field.name nav2_state
  {
    size_t item_size = sizeof(ros_message->nav2_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name nav2_freshness_s
  {
    size_t item_size = sizeof(ros_message->nav2_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name safety_status_known
  {
    size_t item_size = sizeof(ros_message->safety_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name safety_motion_enabled
  {
    size_t item_size = sizeof(ros_message->safety_motion_enabled);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name emergency_stop
  {
    size_t item_size = sizeof(ros_message->emergency_stop);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name estop_latched
  {
    size_t item_size = sizeof(ros_message->estop_latched);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name navigation_ready
  {
    size_t item_size = sizeof(ros_message->navigation_ready);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name safety_freshness_s
  {
    size_t item_size = sizeof(ros_message->safety_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name chassis_status_known
  {
    size_t item_size = sizeof(ros_message->chassis_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name chassis_connected
  {
    size_t item_size = sizeof(ros_message->chassis_connected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name chassis_control_mode
  {
    size_t item_size = sizeof(ros_message->chassis_control_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name chassis_status_freshness_s
  {
    size_t item_size = sizeof(ros_message->chassis_status_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name chassis_odometry_freshness_s
  {
    size_t item_size = sizeof(ros_message->chassis_odometry_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name bag_status_known
  {
    size_t item_size = sizeof(ros_message->bag_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name bag_freshness_s
  {
    size_t item_size = sizeof(ros_message->bag_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name bag_session

  current_alignment += get_serialized_size_agt_interfaces__msg__BagSessionSummary(
    &(ros_message->bag_session), current_alignment);
  // field.name error_code
  {
    size_t item_size = sizeof(ros_message->error_code);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name blocker_codes
  {
    size_t array_size = ros_message->blocker_codes.size;
    auto array_ptr = ros_message->blocker_codes.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }
  // field.name blocker_messages
  {
    size_t array_size = ros_message->blocker_messages.size;
    auto array_ptr = ros_message->blocker_messages.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }
  // field.name message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->message.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _RobotState__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_agt_interfaces__msg__RobotState(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t max_serialized_size_agt_interfaces__msg__RobotState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: header
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: revision
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: system_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: active_profile
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: managed_process_count
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: running_process_count
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: system_health_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: system_health_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: system_health
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_agt_interfaces__msg__SystemHealth(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: task_readiness_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: task_readiness_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: task_readiness
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_agt_interfaces__msg__TaskReadiness(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: active_map_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: active_map_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: active_map
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_agt_interfaces__msg__MapVersionSummary(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: localization_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: localization_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: localization
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_agt_interfaces__msg__LocalizationStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: mission_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: mission_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: mission
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_agt_interfaces__msg__MissionStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: nav2_state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: nav2_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: safety_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: safety_motion_enabled
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: emergency_stop
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: estop_latched
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: navigation_ready
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: safety_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: chassis_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: chassis_connected
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: chassis_control_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: chassis_status_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: chassis_odometry_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: bag_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: bag_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: bag_session
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_agt_interfaces__msg__BagSessionSummary(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: error_code
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: blocker_codes
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: blocker_messages
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: message
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = agt_interfaces__msg__RobotState;
    is_plain =
      (
      offsetof(DataType, message) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _RobotState__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_agt_interfaces__msg__RobotState(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_RobotState = {
  "agt_interfaces::msg",
  "RobotState",
  _RobotState__cdr_serialize,
  _RobotState__cdr_deserialize,
  _RobotState__get_serialized_size,
  _RobotState__max_serialized_size
};

static rosidl_message_type_support_t _RobotState__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_RobotState,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, RobotState)() {
  return &_RobotState__type_support;
}

#if defined(__cplusplus)
}
#endif
