// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/MissionStatus.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/mission_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `mission_id`
// Member `mission_version`
// Member `content_sha256`
// Member `map_id`
// Member `map_version_id`
// Member `map_manifest_sha256`
// Member `current_step_id`
// Member `blocker_codes`
// Member `blocker_messages`
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__msg__MissionStatus__init(agt_interfaces__msg__MissionStatus * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // state
  // mission_id
  if (!rosidl_runtime_c__String__init(&msg->mission_id)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // mission_version
  if (!rosidl_runtime_c__String__init(&msg->mission_version)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // content_sha256
  if (!rosidl_runtime_c__String__init(&msg->content_sha256)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // map_manifest_sha256
  if (!rosidl_runtime_c__String__init(&msg->map_manifest_sha256)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // current_step_index
  // total_steps
  // current_step_id
  if (!rosidl_runtime_c__String__init(&msg->current_step_id)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // current_step_type
  // current_waypoint
  // total_waypoints
  // step_elapsed_s
  // step_remaining_s
  // error_code
  // blocker_codes
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_codes, 0)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // blocker_messages
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_messages, 0)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__msg__MissionStatus__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__MissionStatus__fini(agt_interfaces__msg__MissionStatus * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // state
  // mission_id
  rosidl_runtime_c__String__fini(&msg->mission_id);
  // mission_version
  rosidl_runtime_c__String__fini(&msg->mission_version);
  // content_sha256
  rosidl_runtime_c__String__fini(&msg->content_sha256);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // map_manifest_sha256
  rosidl_runtime_c__String__fini(&msg->map_manifest_sha256);
  // current_step_index
  // total_steps
  // current_step_id
  rosidl_runtime_c__String__fini(&msg->current_step_id);
  // current_step_type
  // current_waypoint
  // total_waypoints
  // step_elapsed_s
  // step_remaining_s
  // error_code
  // blocker_codes
  rosidl_runtime_c__String__Sequence__fini(&msg->blocker_codes);
  // blocker_messages
  rosidl_runtime_c__String__Sequence__fini(&msg->blocker_messages);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
agt_interfaces__msg__MissionStatus__are_equal(const agt_interfaces__msg__MissionStatus * lhs, const agt_interfaces__msg__MissionStatus * rhs)
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
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // mission_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mission_id), &(rhs->mission_id)))
  {
    return false;
  }
  // mission_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mission_version), &(rhs->mission_version)))
  {
    return false;
  }
  // content_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->content_sha256), &(rhs->content_sha256)))
  {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_id), &(rhs->map_id)))
  {
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_version_id), &(rhs->map_version_id)))
  {
    return false;
  }
  // map_manifest_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_manifest_sha256), &(rhs->map_manifest_sha256)))
  {
    return false;
  }
  // current_step_index
  if (lhs->current_step_index != rhs->current_step_index) {
    return false;
  }
  // total_steps
  if (lhs->total_steps != rhs->total_steps) {
    return false;
  }
  // current_step_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->current_step_id), &(rhs->current_step_id)))
  {
    return false;
  }
  // current_step_type
  if (lhs->current_step_type != rhs->current_step_type) {
    return false;
  }
  // current_waypoint
  if (lhs->current_waypoint != rhs->current_waypoint) {
    return false;
  }
  // total_waypoints
  if (lhs->total_waypoints != rhs->total_waypoints) {
    return false;
  }
  // step_elapsed_s
  if (lhs->step_elapsed_s != rhs->step_elapsed_s) {
    return false;
  }
  // step_remaining_s
  if (lhs->step_remaining_s != rhs->step_remaining_s) {
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
agt_interfaces__msg__MissionStatus__copy(
  const agt_interfaces__msg__MissionStatus * input,
  agt_interfaces__msg__MissionStatus * output)
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
  // state
  output->state = input->state;
  // mission_id
  if (!rosidl_runtime_c__String__copy(
      &(input->mission_id), &(output->mission_id)))
  {
    return false;
  }
  // mission_version
  if (!rosidl_runtime_c__String__copy(
      &(input->mission_version), &(output->mission_version)))
  {
    return false;
  }
  // content_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->content_sha256), &(output->content_sha256)))
  {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__copy(
      &(input->map_id), &(output->map_id)))
  {
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__copy(
      &(input->map_version_id), &(output->map_version_id)))
  {
    return false;
  }
  // map_manifest_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->map_manifest_sha256), &(output->map_manifest_sha256)))
  {
    return false;
  }
  // current_step_index
  output->current_step_index = input->current_step_index;
  // total_steps
  output->total_steps = input->total_steps;
  // current_step_id
  if (!rosidl_runtime_c__String__copy(
      &(input->current_step_id), &(output->current_step_id)))
  {
    return false;
  }
  // current_step_type
  output->current_step_type = input->current_step_type;
  // current_waypoint
  output->current_waypoint = input->current_waypoint;
  // total_waypoints
  output->total_waypoints = input->total_waypoints;
  // step_elapsed_s
  output->step_elapsed_s = input->step_elapsed_s;
  // step_remaining_s
  output->step_remaining_s = input->step_remaining_s;
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

agt_interfaces__msg__MissionStatus *
agt_interfaces__msg__MissionStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__MissionStatus * msg = (agt_interfaces__msg__MissionStatus *)allocator.allocate(sizeof(agt_interfaces__msg__MissionStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__MissionStatus));
  bool success = agt_interfaces__msg__MissionStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__MissionStatus__destroy(agt_interfaces__msg__MissionStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__MissionStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__MissionStatus__Sequence__init(agt_interfaces__msg__MissionStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__MissionStatus * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__MissionStatus *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__MissionStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__MissionStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__MissionStatus__fini(&data[i - 1]);
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
agt_interfaces__msg__MissionStatus__Sequence__fini(agt_interfaces__msg__MissionStatus__Sequence * array)
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
      agt_interfaces__msg__MissionStatus__fini(&array->data[i]);
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

agt_interfaces__msg__MissionStatus__Sequence *
agt_interfaces__msg__MissionStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__MissionStatus__Sequence * array = (agt_interfaces__msg__MissionStatus__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__MissionStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__MissionStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__MissionStatus__Sequence__destroy(agt_interfaces__msg__MissionStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__MissionStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__MissionStatus__Sequence__are_equal(const agt_interfaces__msg__MissionStatus__Sequence * lhs, const agt_interfaces__msg__MissionStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__MissionStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__MissionStatus__Sequence__copy(
  const agt_interfaces__msg__MissionStatus__Sequence * input,
  agt_interfaces__msg__MissionStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__MissionStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__MissionStatus * data =
      (agt_interfaces__msg__MissionStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__MissionStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__MissionStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__MissionStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
