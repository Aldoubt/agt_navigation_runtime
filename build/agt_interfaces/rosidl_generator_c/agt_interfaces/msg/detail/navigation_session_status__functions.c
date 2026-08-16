// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/NavigationSessionStatus.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/navigation_session_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `session_id`
// Member `client_request_id`
// Member `map_id`
// Member `map_version_id`
// Member `task_group_id`
// Member `task_content_sha256`
// Member `blocker_code`
// Member `operator_message`
// Member `technical_message`
#include "rosidl_runtime_c/string_functions.h"
// Member `missed_waypoints`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `started_at`
// Member `updated_at`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
agt_interfaces__msg__NavigationSessionStatus__init(agt_interfaces__msg__NavigationSessionStatus * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // session_id
  if (!rosidl_runtime_c__String__init(&msg->session_id)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // client_request_id
  if (!rosidl_runtime_c__String__init(&msg->client_request_id)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // task_group_id
  if (!rosidl_runtime_c__String__init(&msg->task_group_id)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // task_revision
  // task_content_sha256
  if (!rosidl_runtime_c__String__init(&msg->task_content_sha256)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // state
  // loop_index
  // current_waypoint
  // total_waypoints
  // missed_waypoints
  if (!rosidl_runtime_c__uint32__Sequence__init(&msg->missed_waypoints, 0)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // error_code
  // blocker_code
  if (!rosidl_runtime_c__String__init(&msg->blocker_code)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // operator_message
  if (!rosidl_runtime_c__String__init(&msg->operator_message)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // technical_message
  if (!rosidl_runtime_c__String__init(&msg->technical_message)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // started_at
  if (!builtin_interfaces__msg__Time__init(&msg->started_at)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // updated_at
  if (!builtin_interfaces__msg__Time__init(&msg->updated_at)) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
    return false;
  }
  // terminal
  // success
  return true;
}

void
agt_interfaces__msg__NavigationSessionStatus__fini(agt_interfaces__msg__NavigationSessionStatus * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // session_id
  rosidl_runtime_c__String__fini(&msg->session_id);
  // client_request_id
  rosidl_runtime_c__String__fini(&msg->client_request_id);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // task_group_id
  rosidl_runtime_c__String__fini(&msg->task_group_id);
  // task_revision
  // task_content_sha256
  rosidl_runtime_c__String__fini(&msg->task_content_sha256);
  // state
  // loop_index
  // current_waypoint
  // total_waypoints
  // missed_waypoints
  rosidl_runtime_c__uint32__Sequence__fini(&msg->missed_waypoints);
  // error_code
  // blocker_code
  rosidl_runtime_c__String__fini(&msg->blocker_code);
  // operator_message
  rosidl_runtime_c__String__fini(&msg->operator_message);
  // technical_message
  rosidl_runtime_c__String__fini(&msg->technical_message);
  // started_at
  builtin_interfaces__msg__Time__fini(&msg->started_at);
  // updated_at
  builtin_interfaces__msg__Time__fini(&msg->updated_at);
  // terminal
  // success
}

bool
agt_interfaces__msg__NavigationSessionStatus__are_equal(const agt_interfaces__msg__NavigationSessionStatus * lhs, const agt_interfaces__msg__NavigationSessionStatus * rhs)
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
  // session_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->session_id), &(rhs->session_id)))
  {
    return false;
  }
  // client_request_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->client_request_id), &(rhs->client_request_id)))
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
  // task_group_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->task_group_id), &(rhs->task_group_id)))
  {
    return false;
  }
  // task_revision
  if (lhs->task_revision != rhs->task_revision) {
    return false;
  }
  // task_content_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->task_content_sha256), &(rhs->task_content_sha256)))
  {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // loop_index
  if (lhs->loop_index != rhs->loop_index) {
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
  // missed_waypoints
  if (!rosidl_runtime_c__uint32__Sequence__are_equal(
      &(lhs->missed_waypoints), &(rhs->missed_waypoints)))
  {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  // blocker_code
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->blocker_code), &(rhs->blocker_code)))
  {
    return false;
  }
  // operator_message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->operator_message), &(rhs->operator_message)))
  {
    return false;
  }
  // technical_message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->technical_message), &(rhs->technical_message)))
  {
    return false;
  }
  // started_at
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->started_at), &(rhs->started_at)))
  {
    return false;
  }
  // updated_at
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->updated_at), &(rhs->updated_at)))
  {
    return false;
  }
  // terminal
  if (lhs->terminal != rhs->terminal) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
agt_interfaces__msg__NavigationSessionStatus__copy(
  const agt_interfaces__msg__NavigationSessionStatus * input,
  agt_interfaces__msg__NavigationSessionStatus * output)
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
  // session_id
  if (!rosidl_runtime_c__String__copy(
      &(input->session_id), &(output->session_id)))
  {
    return false;
  }
  // client_request_id
  if (!rosidl_runtime_c__String__copy(
      &(input->client_request_id), &(output->client_request_id)))
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
  // task_group_id
  if (!rosidl_runtime_c__String__copy(
      &(input->task_group_id), &(output->task_group_id)))
  {
    return false;
  }
  // task_revision
  output->task_revision = input->task_revision;
  // task_content_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->task_content_sha256), &(output->task_content_sha256)))
  {
    return false;
  }
  // state
  output->state = input->state;
  // loop_index
  output->loop_index = input->loop_index;
  // current_waypoint
  output->current_waypoint = input->current_waypoint;
  // total_waypoints
  output->total_waypoints = input->total_waypoints;
  // missed_waypoints
  if (!rosidl_runtime_c__uint32__Sequence__copy(
      &(input->missed_waypoints), &(output->missed_waypoints)))
  {
    return false;
  }
  // error_code
  output->error_code = input->error_code;
  // blocker_code
  if (!rosidl_runtime_c__String__copy(
      &(input->blocker_code), &(output->blocker_code)))
  {
    return false;
  }
  // operator_message
  if (!rosidl_runtime_c__String__copy(
      &(input->operator_message), &(output->operator_message)))
  {
    return false;
  }
  // technical_message
  if (!rosidl_runtime_c__String__copy(
      &(input->technical_message), &(output->technical_message)))
  {
    return false;
  }
  // started_at
  if (!builtin_interfaces__msg__Time__copy(
      &(input->started_at), &(output->started_at)))
  {
    return false;
  }
  // updated_at
  if (!builtin_interfaces__msg__Time__copy(
      &(input->updated_at), &(output->updated_at)))
  {
    return false;
  }
  // terminal
  output->terminal = input->terminal;
  // success
  output->success = input->success;
  return true;
}

agt_interfaces__msg__NavigationSessionStatus *
agt_interfaces__msg__NavigationSessionStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__NavigationSessionStatus * msg = (agt_interfaces__msg__NavigationSessionStatus *)allocator.allocate(sizeof(agt_interfaces__msg__NavigationSessionStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__NavigationSessionStatus));
  bool success = agt_interfaces__msg__NavigationSessionStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__NavigationSessionStatus__destroy(agt_interfaces__msg__NavigationSessionStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__NavigationSessionStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__NavigationSessionStatus__Sequence__init(agt_interfaces__msg__NavigationSessionStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__NavigationSessionStatus * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__NavigationSessionStatus *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__NavigationSessionStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__NavigationSessionStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__NavigationSessionStatus__fini(&data[i - 1]);
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
agt_interfaces__msg__NavigationSessionStatus__Sequence__fini(agt_interfaces__msg__NavigationSessionStatus__Sequence * array)
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
      agt_interfaces__msg__NavigationSessionStatus__fini(&array->data[i]);
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

agt_interfaces__msg__NavigationSessionStatus__Sequence *
agt_interfaces__msg__NavigationSessionStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__NavigationSessionStatus__Sequence * array = (agt_interfaces__msg__NavigationSessionStatus__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__NavigationSessionStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__NavigationSessionStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__NavigationSessionStatus__Sequence__destroy(agt_interfaces__msg__NavigationSessionStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__NavigationSessionStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__NavigationSessionStatus__Sequence__are_equal(const agt_interfaces__msg__NavigationSessionStatus__Sequence * lhs, const agt_interfaces__msg__NavigationSessionStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__NavigationSessionStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__NavigationSessionStatus__Sequence__copy(
  const agt_interfaces__msg__NavigationSessionStatus__Sequence * input,
  agt_interfaces__msg__NavigationSessionStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__NavigationSessionStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__NavigationSessionStatus * data =
      (agt_interfaces__msg__NavigationSessionStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__NavigationSessionStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__NavigationSessionStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__NavigationSessionStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
