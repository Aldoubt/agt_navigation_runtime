// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from agt_interfaces:msg/RobotState.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/robot_state__rosidl_typesupport_fastrtps_cpp.hpp"
#include "agt_interfaces/msg/detail/robot_state__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace std_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  std_msgs::msg::Header &);
size_t get_serialized_size(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace std_msgs

namespace agt_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const agt_interfaces::msg::SystemHealth &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  agt_interfaces::msg::SystemHealth &);
size_t get_serialized_size(
  const agt_interfaces::msg::SystemHealth &,
  size_t current_alignment);
size_t
max_serialized_size_SystemHealth(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace agt_interfaces

namespace agt_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const agt_interfaces::msg::TaskReadiness &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  agt_interfaces::msg::TaskReadiness &);
size_t get_serialized_size(
  const agt_interfaces::msg::TaskReadiness &,
  size_t current_alignment);
size_t
max_serialized_size_TaskReadiness(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace agt_interfaces

namespace agt_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const agt_interfaces::msg::MapVersionSummary &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  agt_interfaces::msg::MapVersionSummary &);
size_t get_serialized_size(
  const agt_interfaces::msg::MapVersionSummary &,
  size_t current_alignment);
size_t
max_serialized_size_MapVersionSummary(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace agt_interfaces

namespace agt_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const agt_interfaces::msg::LocalizationStatus &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  agt_interfaces::msg::LocalizationStatus &);
size_t get_serialized_size(
  const agt_interfaces::msg::LocalizationStatus &,
  size_t current_alignment);
size_t
max_serialized_size_LocalizationStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace agt_interfaces

namespace agt_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const agt_interfaces::msg::MissionStatus &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  agt_interfaces::msg::MissionStatus &);
size_t get_serialized_size(
  const agt_interfaces::msg::MissionStatus &,
  size_t current_alignment);
size_t
max_serialized_size_MissionStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace agt_interfaces

namespace agt_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const agt_interfaces::msg::BagSessionSummary &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  agt_interfaces::msg::BagSessionSummary &);
size_t get_serialized_size(
  const agt_interfaces::msg::BagSessionSummary &,
  size_t current_alignment);
size_t
max_serialized_size_BagSessionSummary(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_agt_interfaces
cdr_serialize(
  const agt_interfaces::msg::RobotState & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.header,
    cdr);
  // Member: revision
  cdr << ros_message.revision;
  // Member: system_mode
  cdr << ros_message.system_mode;
  // Member: active_profile
  cdr << ros_message.active_profile;
  // Member: managed_process_count
  cdr << ros_message.managed_process_count;
  // Member: running_process_count
  cdr << ros_message.running_process_count;
  // Member: system_health_known
  cdr << (ros_message.system_health_known ? true : false);
  // Member: system_health_freshness_s
  cdr << ros_message.system_health_freshness_s;
  // Member: system_health
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.system_health,
    cdr);
  // Member: task_readiness_known
  cdr << (ros_message.task_readiness_known ? true : false);
  // Member: task_readiness_freshness_s
  cdr << ros_message.task_readiness_freshness_s;
  // Member: task_readiness
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.task_readiness,
    cdr);
  // Member: active_map_known
  cdr << (ros_message.active_map_known ? true : false);
  // Member: active_map_freshness_s
  cdr << ros_message.active_map_freshness_s;
  // Member: active_map
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.active_map,
    cdr);
  // Member: localization_status_known
  cdr << (ros_message.localization_status_known ? true : false);
  // Member: localization_freshness_s
  cdr << ros_message.localization_freshness_s;
  // Member: localization
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.localization,
    cdr);
  // Member: mission_status_known
  cdr << (ros_message.mission_status_known ? true : false);
  // Member: mission_freshness_s
  cdr << ros_message.mission_freshness_s;
  // Member: mission
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.mission,
    cdr);
  // Member: nav2_state
  cdr << ros_message.nav2_state;
  // Member: nav2_freshness_s
  cdr << ros_message.nav2_freshness_s;
  // Member: safety_status_known
  cdr << (ros_message.safety_status_known ? true : false);
  // Member: safety_motion_enabled
  cdr << (ros_message.safety_motion_enabled ? true : false);
  // Member: emergency_stop
  cdr << (ros_message.emergency_stop ? true : false);
  // Member: estop_latched
  cdr << (ros_message.estop_latched ? true : false);
  // Member: navigation_ready
  cdr << (ros_message.navigation_ready ? true : false);
  // Member: safety_freshness_s
  cdr << ros_message.safety_freshness_s;
  // Member: chassis_status_known
  cdr << (ros_message.chassis_status_known ? true : false);
  // Member: chassis_connected
  cdr << (ros_message.chassis_connected ? true : false);
  // Member: chassis_control_mode
  cdr << ros_message.chassis_control_mode;
  // Member: chassis_status_freshness_s
  cdr << ros_message.chassis_status_freshness_s;
  // Member: chassis_odometry_freshness_s
  cdr << ros_message.chassis_odometry_freshness_s;
  // Member: bag_status_known
  cdr << (ros_message.bag_status_known ? true : false);
  // Member: bag_freshness_s
  cdr << ros_message.bag_freshness_s;
  // Member: bag_session
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.bag_session,
    cdr);
  // Member: error_code
  cdr << ros_message.error_code;
  // Member: blocker_codes
  {
    cdr << ros_message.blocker_codes;
  }
  // Member: blocker_messages
  {
    cdr << ros_message.blocker_messages;
  }
  // Member: message
  cdr << ros_message.message;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_agt_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  agt_interfaces::msg::RobotState & ros_message)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.header);

  // Member: revision
  cdr >> ros_message.revision;

  // Member: system_mode
  cdr >> ros_message.system_mode;

  // Member: active_profile
  cdr >> ros_message.active_profile;

  // Member: managed_process_count
  cdr >> ros_message.managed_process_count;

  // Member: running_process_count
  cdr >> ros_message.running_process_count;

  // Member: system_health_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.system_health_known = tmp ? true : false;
  }

  // Member: system_health_freshness_s
  cdr >> ros_message.system_health_freshness_s;

  // Member: system_health
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.system_health);

  // Member: task_readiness_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.task_readiness_known = tmp ? true : false;
  }

  // Member: task_readiness_freshness_s
  cdr >> ros_message.task_readiness_freshness_s;

  // Member: task_readiness
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.task_readiness);

  // Member: active_map_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.active_map_known = tmp ? true : false;
  }

  // Member: active_map_freshness_s
  cdr >> ros_message.active_map_freshness_s;

  // Member: active_map
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.active_map);

  // Member: localization_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.localization_status_known = tmp ? true : false;
  }

  // Member: localization_freshness_s
  cdr >> ros_message.localization_freshness_s;

  // Member: localization
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.localization);

  // Member: mission_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.mission_status_known = tmp ? true : false;
  }

  // Member: mission_freshness_s
  cdr >> ros_message.mission_freshness_s;

  // Member: mission
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.mission);

  // Member: nav2_state
  cdr >> ros_message.nav2_state;

  // Member: nav2_freshness_s
  cdr >> ros_message.nav2_freshness_s;

  // Member: safety_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.safety_status_known = tmp ? true : false;
  }

  // Member: safety_motion_enabled
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.safety_motion_enabled = tmp ? true : false;
  }

  // Member: emergency_stop
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.emergency_stop = tmp ? true : false;
  }

  // Member: estop_latched
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.estop_latched = tmp ? true : false;
  }

  // Member: navigation_ready
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.navigation_ready = tmp ? true : false;
  }

  // Member: safety_freshness_s
  cdr >> ros_message.safety_freshness_s;

  // Member: chassis_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.chassis_status_known = tmp ? true : false;
  }

  // Member: chassis_connected
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.chassis_connected = tmp ? true : false;
  }

  // Member: chassis_control_mode
  cdr >> ros_message.chassis_control_mode;

  // Member: chassis_status_freshness_s
  cdr >> ros_message.chassis_status_freshness_s;

  // Member: chassis_odometry_freshness_s
  cdr >> ros_message.chassis_odometry_freshness_s;

  // Member: bag_status_known
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.bag_status_known = tmp ? true : false;
  }

  // Member: bag_freshness_s
  cdr >> ros_message.bag_freshness_s;

  // Member: bag_session
  agt_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.bag_session);

  // Member: error_code
  cdr >> ros_message.error_code;

  // Member: blocker_codes
  {
    cdr >> ros_message.blocker_codes;
  }

  // Member: blocker_messages
  {
    cdr >> ros_message.blocker_messages;
  }

  // Member: message
  cdr >> ros_message.message;

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_agt_interfaces
get_serialized_size(
  const agt_interfaces::msg::RobotState & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header

  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.header, current_alignment);
  // Member: revision
  {
    size_t item_size = sizeof(ros_message.revision);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: system_mode
  {
    size_t item_size = sizeof(ros_message.system_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: active_profile
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.active_profile.size() + 1);
  // Member: managed_process_count
  {
    size_t item_size = sizeof(ros_message.managed_process_count);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: running_process_count
  {
    size_t item_size = sizeof(ros_message.running_process_count);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: system_health_known
  {
    size_t item_size = sizeof(ros_message.system_health_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: system_health_freshness_s
  {
    size_t item_size = sizeof(ros_message.system_health_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: system_health

  current_alignment +=
    agt_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.system_health, current_alignment);
  // Member: task_readiness_known
  {
    size_t item_size = sizeof(ros_message.task_readiness_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: task_readiness_freshness_s
  {
    size_t item_size = sizeof(ros_message.task_readiness_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: task_readiness

  current_alignment +=
    agt_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.task_readiness, current_alignment);
  // Member: active_map_known
  {
    size_t item_size = sizeof(ros_message.active_map_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: active_map_freshness_s
  {
    size_t item_size = sizeof(ros_message.active_map_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: active_map

  current_alignment +=
    agt_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.active_map, current_alignment);
  // Member: localization_status_known
  {
    size_t item_size = sizeof(ros_message.localization_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: localization_freshness_s
  {
    size_t item_size = sizeof(ros_message.localization_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: localization

  current_alignment +=
    agt_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.localization, current_alignment);
  // Member: mission_status_known
  {
    size_t item_size = sizeof(ros_message.mission_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: mission_freshness_s
  {
    size_t item_size = sizeof(ros_message.mission_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: mission

  current_alignment +=
    agt_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.mission, current_alignment);
  // Member: nav2_state
  {
    size_t item_size = sizeof(ros_message.nav2_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: nav2_freshness_s
  {
    size_t item_size = sizeof(ros_message.nav2_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: safety_status_known
  {
    size_t item_size = sizeof(ros_message.safety_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: safety_motion_enabled
  {
    size_t item_size = sizeof(ros_message.safety_motion_enabled);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: emergency_stop
  {
    size_t item_size = sizeof(ros_message.emergency_stop);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: estop_latched
  {
    size_t item_size = sizeof(ros_message.estop_latched);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: navigation_ready
  {
    size_t item_size = sizeof(ros_message.navigation_ready);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: safety_freshness_s
  {
    size_t item_size = sizeof(ros_message.safety_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: chassis_status_known
  {
    size_t item_size = sizeof(ros_message.chassis_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: chassis_connected
  {
    size_t item_size = sizeof(ros_message.chassis_connected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: chassis_control_mode
  {
    size_t item_size = sizeof(ros_message.chassis_control_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: chassis_status_freshness_s
  {
    size_t item_size = sizeof(ros_message.chassis_status_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: chassis_odometry_freshness_s
  {
    size_t item_size = sizeof(ros_message.chassis_odometry_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: bag_status_known
  {
    size_t item_size = sizeof(ros_message.bag_status_known);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: bag_freshness_s
  {
    size_t item_size = sizeof(ros_message.bag_freshness_s);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: bag_session

  current_alignment +=
    agt_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.bag_session, current_alignment);
  // Member: error_code
  {
    size_t item_size = sizeof(ros_message.error_code);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: blocker_codes
  {
    size_t array_size = ros_message.blocker_codes.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (ros_message.blocker_codes[index].size() + 1);
    }
  }
  // Member: blocker_messages
  {
    size_t array_size = ros_message.blocker_messages.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (ros_message.blocker_messages[index].size() + 1);
    }
  }
  // Member: message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.message.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_agt_interfaces
max_serialized_size_RobotState(
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


  // Member: header
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: revision
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: system_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: active_profile
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

  // Member: managed_process_count
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: running_process_count
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: system_health_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: system_health_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: system_health
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        agt_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_SystemHealth(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: task_readiness_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: task_readiness_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: task_readiness
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        agt_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_TaskReadiness(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: active_map_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: active_map_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: active_map
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        agt_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_MapVersionSummary(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: localization_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: localization_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: localization
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        agt_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_LocalizationStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: mission_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: mission_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: mission
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        agt_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_MissionStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: nav2_state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: nav2_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: safety_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: safety_motion_enabled
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: emergency_stop
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: estop_latched
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: navigation_ready
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: safety_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: chassis_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: chassis_connected
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: chassis_control_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: chassis_status_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: chassis_odometry_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: bag_status_known
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: bag_freshness_s
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: bag_session
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        agt_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_BagSessionSummary(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: error_code
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: blocker_codes
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

  // Member: blocker_messages
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

  // Member: message
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
    using DataType = agt_interfaces::msg::RobotState;
    is_plain =
      (
      offsetof(DataType, message) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _RobotState__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const agt_interfaces::msg::RobotState *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _RobotState__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<agt_interfaces::msg::RobotState *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _RobotState__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const agt_interfaces::msg::RobotState *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _RobotState__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_RobotState(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _RobotState__callbacks = {
  "agt_interfaces::msg",
  "RobotState",
  _RobotState__cdr_serialize,
  _RobotState__cdr_deserialize,
  _RobotState__get_serialized_size,
  _RobotState__max_serialized_size
};

static rosidl_message_type_support_t _RobotState__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_RobotState__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace agt_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::msg::RobotState>()
{
  return &agt_interfaces::msg::typesupport_fastrtps_cpp::_RobotState__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, msg, RobotState)() {
  return &agt_interfaces::msg::typesupport_fastrtps_cpp::_RobotState__handle;
}

#ifdef __cplusplus
}
#endif
