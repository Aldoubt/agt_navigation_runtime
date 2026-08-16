// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/RobotState.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/robot_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `active_profile`
// Member `blocker_codes`
// Member `blocker_messages`
// Member `message`
#include "rosidl_runtime_c/string_functions.h"
// Member `system_health`
#include "agt_interfaces/msg/detail/system_health__functions.h"
// Member `task_readiness`
#include "agt_interfaces/msg/detail/task_readiness__functions.h"
// Member `active_map`
#include "agt_interfaces/msg/detail/map_version_summary__functions.h"
// Member `localization`
#include "agt_interfaces/msg/detail/localization_status__functions.h"
// Member `mission`
#include "agt_interfaces/msg/detail/mission_status__functions.h"
// Member `bag_session`
#include "agt_interfaces/msg/detail/bag_session_summary__functions.h"

bool
agt_interfaces__msg__RobotState__init(agt_interfaces__msg__RobotState * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // revision
  // system_mode
  // active_profile
  if (!rosidl_runtime_c__String__init(&msg->active_profile)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // managed_process_count
  // running_process_count
  // system_health_known
  // system_health_freshness_s
  // system_health
  if (!agt_interfaces__msg__SystemHealth__init(&msg->system_health)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // task_readiness_known
  // task_readiness_freshness_s
  // task_readiness
  if (!agt_interfaces__msg__TaskReadiness__init(&msg->task_readiness)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // active_map_known
  // active_map_freshness_s
  // active_map
  if (!agt_interfaces__msg__MapVersionSummary__init(&msg->active_map)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // localization_status_known
  // localization_freshness_s
  // localization
  if (!agt_interfaces__msg__LocalizationStatus__init(&msg->localization)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // mission_status_known
  // mission_freshness_s
  // mission
  if (!agt_interfaces__msg__MissionStatus__init(&msg->mission)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // nav2_state
  // nav2_freshness_s
  // safety_status_known
  // safety_motion_enabled
  // emergency_stop
  // estop_latched
  // navigation_ready
  // safety_freshness_s
  // chassis_status_known
  // chassis_connected
  // chassis_control_mode
  // chassis_status_freshness_s
  // chassis_odometry_freshness_s
  // bag_status_known
  // bag_freshness_s
  // bag_session
  if (!agt_interfaces__msg__BagSessionSummary__init(&msg->bag_session)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // error_code
  // blocker_codes
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_codes, 0)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // blocker_messages
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_messages, 0)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__msg__RobotState__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__RobotState__fini(agt_interfaces__msg__RobotState * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // revision
  // system_mode
  // active_profile
  rosidl_runtime_c__String__fini(&msg->active_profile);
  // managed_process_count
  // running_process_count
  // system_health_known
  // system_health_freshness_s
  // system_health
  agt_interfaces__msg__SystemHealth__fini(&msg->system_health);
  // task_readiness_known
  // task_readiness_freshness_s
  // task_readiness
  agt_interfaces__msg__TaskReadiness__fini(&msg->task_readiness);
  // active_map_known
  // active_map_freshness_s
  // active_map
  agt_interfaces__msg__MapVersionSummary__fini(&msg->active_map);
  // localization_status_known
  // localization_freshness_s
  // localization
  agt_interfaces__msg__LocalizationStatus__fini(&msg->localization);
  // mission_status_known
  // mission_freshness_s
  // mission
  agt_interfaces__msg__MissionStatus__fini(&msg->mission);
  // nav2_state
  // nav2_freshness_s
  // safety_status_known
  // safety_motion_enabled
  // emergency_stop
  // estop_latched
  // navigation_ready
  // safety_freshness_s
  // chassis_status_known
  // chassis_connected
  // chassis_control_mode
  // chassis_status_freshness_s
  // chassis_odometry_freshness_s
  // bag_status_known
  // bag_freshness_s
  // bag_session
  agt_interfaces__msg__BagSessionSummary__fini(&msg->bag_session);
  // error_code
  // blocker_codes
  rosidl_runtime_c__String__Sequence__fini(&msg->blocker_codes);
  // blocker_messages
  rosidl_runtime_c__String__Sequence__fini(&msg->blocker_messages);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
agt_interfaces__msg__RobotState__are_equal(const agt_interfaces__msg__RobotState * lhs, const agt_interfaces__msg__RobotState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // revision
  if (lhs->revision != rhs->revision) {
    return false;
  }
  // system_mode
  if (lhs->system_mode != rhs->system_mode) {
    return false;
  }
  // active_profile
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->active_profile), &(rhs->active_profile)))
  {
    return false;
  }
  // managed_process_count
  if (lhs->managed_process_count != rhs->managed_process_count) {
    return false;
  }
  // running_process_count
  if (lhs->running_process_count != rhs->running_process_count) {
    return false;
  }
  // system_health_known
  if (lhs->system_health_known != rhs->system_health_known) {
    return false;
  }
  // system_health_freshness_s
  if (lhs->system_health_freshness_s != rhs->system_health_freshness_s) {
    return false;
  }
  // system_health
  if (!agt_interfaces__msg__SystemHealth__are_equal(
      &(lhs->system_health), &(rhs->system_health)))
  {
    return false;
  }
  // task_readiness_known
  if (lhs->task_readiness_known != rhs->task_readiness_known) {
    return false;
  }
  // task_readiness_freshness_s
  if (lhs->task_readiness_freshness_s != rhs->task_readiness_freshness_s) {
    return false;
  }
  // task_readiness
  if (!agt_interfaces__msg__TaskReadiness__are_equal(
      &(lhs->task_readiness), &(rhs->task_readiness)))
  {
    return false;
  }
  // active_map_known
  if (lhs->active_map_known != rhs->active_map_known) {
    return false;
  }
  // active_map_freshness_s
  if (lhs->active_map_freshness_s != rhs->active_map_freshness_s) {
    return false;
  }
  // active_map
  if (!agt_interfaces__msg__MapVersionSummary__are_equal(
      &(lhs->active_map), &(rhs->active_map)))
  {
    return false;
  }
  // localization_status_known
  if (lhs->localization_status_known != rhs->localization_status_known) {
    return false;
  }
  // localization_freshness_s
  if (lhs->localization_freshness_s != rhs->localization_freshness_s) {
    return false;
  }
  // localization
  if (!agt_interfaces__msg__LocalizationStatus__are_equal(
      &(lhs->localization), &(rhs->localization)))
  {
    return false;
  }
  // mission_status_known
  if (lhs->mission_status_known != rhs->mission_status_known) {
    return false;
  }
  // mission_freshness_s
  if (lhs->mission_freshness_s != rhs->mission_freshness_s) {
    return false;
  }
  // mission
  if (!agt_interfaces__msg__MissionStatus__are_equal(
      &(lhs->mission), &(rhs->mission)))
  {
    return false;
  }
  // nav2_state
  if (lhs->nav2_state != rhs->nav2_state) {
    return false;
  }
  // nav2_freshness_s
  if (lhs->nav2_freshness_s != rhs->nav2_freshness_s) {
    return false;
  }
  // safety_status_known
  if (lhs->safety_status_known != rhs->safety_status_known) {
    return false;
  }
  // safety_motion_enabled
  if (lhs->safety_motion_enabled != rhs->safety_motion_enabled) {
    return false;
  }
  // emergency_stop
  if (lhs->emergency_stop != rhs->emergency_stop) {
    return false;
  }
  // estop_latched
  if (lhs->estop_latched != rhs->estop_latched) {
    return false;
  }
  // navigation_ready
  if (lhs->navigation_ready != rhs->navigation_ready) {
    return false;
  }
  // safety_freshness_s
  if (lhs->safety_freshness_s != rhs->safety_freshness_s) {
    return false;
  }
  // chassis_status_known
  if (lhs->chassis_status_known != rhs->chassis_status_known) {
    return false;
  }
  // chassis_connected
  if (lhs->chassis_connected != rhs->chassis_connected) {
    return false;
  }
  // chassis_control_mode
  if (lhs->chassis_control_mode != rhs->chassis_control_mode) {
    return false;
  }
  // chassis_status_freshness_s
  if (lhs->chassis_status_freshness_s != rhs->chassis_status_freshness_s) {
    return false;
  }
  // chassis_odometry_freshness_s
  if (lhs->chassis_odometry_freshness_s != rhs->chassis_odometry_freshness_s) {
    return false;
  }
  // bag_status_known
  if (lhs->bag_status_known != rhs->bag_status_known) {
    return false;
  }
  // bag_freshness_s
  if (lhs->bag_freshness_s != rhs->bag_freshness_s) {
    return false;
  }
  // bag_session
  if (!agt_interfaces__msg__BagSessionSummary__are_equal(
      &(lhs->bag_session), &(rhs->bag_session)))
  {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  // blocker_codes
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->blocker_codes), &(rhs->blocker_codes)))
  {
    return false;
  }
  // blocker_messages
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->blocker_messages), &(rhs->blocker_messages)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__msg__RobotState__copy(
  const agt_interfaces__msg__RobotState * input,
  agt_interfaces__msg__RobotState * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // revision
  output->revision = input->revision;
  // system_mode
  output->system_mode = input->system_mode;
  // active_profile
  if (!rosidl_runtime_c__String__copy(
      &(input->active_profile), &(output->active_profile)))
  {
    return false;
  }
  // managed_process_count
  output->managed_process_count = input->managed_process_count;
  // running_process_count
  output->running_process_count = input->running_process_count;
  // system_health_known
  output->system_health_known = input->system_health_known;
  // system_health_freshness_s
  output->system_health_freshness_s = input->system_health_freshness_s;
  // system_health
  if (!agt_interfaces__msg__SystemHealth__copy(
      &(input->system_health), &(output->system_health)))
  {
    return false;
  }
  // task_readiness_known
  output->task_readiness_known = input->task_readiness_known;
  // task_readiness_freshness_s
  output->task_readiness_freshness_s = input->task_readiness_freshness_s;
  // task_readiness
  if (!agt_interfaces__msg__TaskReadiness__copy(
      &(input->task_readiness), &(output->task_readiness)))
  {
    return false;
  }
  // active_map_known
  output->active_map_known = input->active_map_known;
  // active_map_freshness_s
  output->active_map_freshness_s = input->active_map_freshness_s;
  // active_map
  if (!agt_interfaces__msg__MapVersionSummary__copy(
      &(input->active_map), &(output->active_map)))
  {
    return false;
  }
  // localization_status_known
  output->localization_status_known = input->localization_status_known;
  // localization_freshness_s
  output->localization_freshness_s = input->localization_freshness_s;
  // localization
  if (!agt_interfaces__msg__LocalizationStatus__copy(
      &(input->localization), &(output->localization)))
  {
    return false;
  }
  // mission_status_known
  output->mission_status_known = input->mission_status_known;
  // mission_freshness_s
  output->mission_freshness_s = input->mission_freshness_s;
  // mission
  if (!agt_interfaces__msg__MissionStatus__copy(
      &(input->mission), &(output->mission)))
  {
    return false;
  }
  // nav2_state
  output->nav2_state = input->nav2_state;
  // nav2_freshness_s
  output->nav2_freshness_s = input->nav2_freshness_s;
  // safety_status_known
  output->safety_status_known = input->safety_status_known;
  // safety_motion_enabled
  output->safety_motion_enabled = input->safety_motion_enabled;
  // emergency_stop
  output->emergency_stop = input->emergency_stop;
  // estop_latched
  output->estop_latched = input->estop_latched;
  // navigation_ready
  output->navigation_ready = input->navigation_ready;
  // safety_freshness_s
  output->safety_freshness_s = input->safety_freshness_s;
  // chassis_status_known
  output->chassis_status_known = input->chassis_status_known;
  // chassis_connected
  output->chassis_connected = input->chassis_connected;
  // chassis_control_mode
  output->chassis_control_mode = input->chassis_control_mode;
  // chassis_status_freshness_s
  output->chassis_status_freshness_s = input->chassis_status_freshness_s;
  // chassis_odometry_freshness_s
  output->chassis_odometry_freshness_s = input->chassis_odometry_freshness_s;
  // bag_status_known
  output->bag_status_known = input->bag_status_known;
  // bag_freshness_s
  output->bag_freshness_s = input->bag_freshness_s;
  // bag_session
  if (!agt_interfaces__msg__BagSessionSummary__copy(
      &(input->bag_session), &(output->bag_session)))
  {
    return false;
  }
  // error_code
  output->error_code = input->error_code;
  // blocker_codes
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->blocker_codes), &(output->blocker_codes)))
  {
    return false;
  }
  // blocker_messages
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->blocker_messages), &(output->blocker_messages)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

agt_interfaces__msg__RobotState *
agt_interfaces__msg__RobotState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__RobotState * msg = (agt_interfaces__msg__RobotState *)allocator.allocate(sizeof(agt_interfaces__msg__RobotState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__RobotState));
  bool success = agt_interfaces__msg__RobotState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__RobotState__destroy(agt_interfaces__msg__RobotState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__RobotState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__RobotState__Sequence__init(agt_interfaces__msg__RobotState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__RobotState * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__RobotState *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__RobotState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__RobotState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__RobotState__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
agt_interfaces__msg__RobotState__Sequence__fini(agt_interfaces__msg__RobotState__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      agt_interfaces__msg__RobotState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

agt_interfaces__msg__RobotState__Sequence *
agt_interfaces__msg__RobotState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__RobotState__Sequence * array = (agt_interfaces__msg__RobotState__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__RobotState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__RobotState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__RobotState__Sequence__destroy(agt_interfaces__msg__RobotState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__RobotState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__RobotState__Sequence__are_equal(const agt_interfaces__msg__RobotState__Sequence * lhs, const agt_interfaces__msg__RobotState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__RobotState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__RobotState__Sequence__copy(
  const agt_interfaces__msg__RobotState__Sequence * input,
  agt_interfaces__msg__RobotState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__RobotState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__RobotState * data =
      (agt_interfaces__msg__RobotState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__RobotState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__RobotState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__RobotState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
