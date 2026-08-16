// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:action/ExecuteBehaviorTree.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `tree_id`
// Member `execution_id`
// Member `map_id`
// Member `map_version_id`
// Member `task_group_id`
// Member `expected_content_sha256`
// Member `client_request_id`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__action__ExecuteBehaviorTree_Goal__init(agt_interfaces__action__ExecuteBehaviorTree_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // tree_id
  if (!rosidl_runtime_c__String__init(&msg->tree_id)) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(msg);
    return false;
  }
  // execution_id
  if (!rosidl_runtime_c__String__init(&msg->execution_id)) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(msg);
    return false;
  }
  // task_group_id
  if (!rosidl_runtime_c__String__init(&msg->task_group_id)) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(msg);
    return false;
  }
  // task_revision
  // expected_content_sha256
  if (!rosidl_runtime_c__String__init(&msg->expected_content_sha256)) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(msg);
    return false;
  }
  // loop_count
  // client_request_id
  if (!rosidl_runtime_c__String__init(&msg->client_request_id)) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(agt_interfaces__action__ExecuteBehaviorTree_Goal * msg)
{
  if (!msg) {
    return;
  }
  // tree_id
  rosidl_runtime_c__String__fini(&msg->tree_id);
  // execution_id
  rosidl_runtime_c__String__fini(&msg->execution_id);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // task_group_id
  rosidl_runtime_c__String__fini(&msg->task_group_id);
  // task_revision
  // expected_content_sha256
  rosidl_runtime_c__String__fini(&msg->expected_content_sha256);
  // loop_count
  // client_request_id
  rosidl_runtime_c__String__fini(&msg->client_request_id);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Goal__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_Goal * lhs, const agt_interfaces__action__ExecuteBehaviorTree_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // tree_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->tree_id), &(rhs->tree_id)))
  {
    return false;
  }
  // execution_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->execution_id), &(rhs->execution_id)))
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
  // expected_content_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->expected_content_sha256), &(rhs->expected_content_sha256)))
  {
    return false;
  }
  // loop_count
  if (lhs->loop_count != rhs->loop_count) {
    return false;
  }
  // client_request_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->client_request_id), &(rhs->client_request_id)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Goal__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_Goal * input,
  agt_interfaces__action__ExecuteBehaviorTree_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // tree_id
  if (!rosidl_runtime_c__String__copy(
      &(input->tree_id), &(output->tree_id)))
  {
    return false;
  }
  // execution_id
  if (!rosidl_runtime_c__String__copy(
      &(input->execution_id), &(output->execution_id)))
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
  // expected_content_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->expected_content_sha256), &(output->expected_content_sha256)))
  {
    return false;
  }
  // loop_count
  output->loop_count = input->loop_count;
  // client_request_id
  if (!rosidl_runtime_c__String__copy(
      &(input->client_request_id), &(output->client_request_id)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ExecuteBehaviorTree_Goal *
agt_interfaces__action__ExecuteBehaviorTree_Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_Goal * msg = (agt_interfaces__action__ExecuteBehaviorTree_Goal *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ExecuteBehaviorTree_Goal));
  bool success = agt_interfaces__action__ExecuteBehaviorTree_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ExecuteBehaviorTree_Goal__destroy(agt_interfaces__action__ExecuteBehaviorTree_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__init(agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_Goal * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ExecuteBehaviorTree_Goal *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ExecuteBehaviorTree_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ExecuteBehaviorTree_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(&data[i - 1]);
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
agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__fini(agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence * array)
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
      agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(&array->data[i]);
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

agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence *
agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence * array = (agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__destroy(agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence * lhs, const agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence * input,
  agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ExecuteBehaviorTree_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ExecuteBehaviorTree_Goal * data =
      (agt_interfaces__action__ExecuteBehaviorTree_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ExecuteBehaviorTree_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// Member `blocker_code`
// Member `blocker_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__action__ExecuteBehaviorTree_Result__init(agt_interfaces__action__ExecuteBehaviorTree_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_code
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__action__ExecuteBehaviorTree_Result__fini(msg);
    return false;
  }
  // blocker_code
  if (!rosidl_runtime_c__String__init(&msg->blocker_code)) {
    agt_interfaces__action__ExecuteBehaviorTree_Result__fini(msg);
    return false;
  }
  // blocker_message
  if (!rosidl_runtime_c__String__init(&msg->blocker_message)) {
    agt_interfaces__action__ExecuteBehaviorTree_Result__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ExecuteBehaviorTree_Result__fini(agt_interfaces__action__ExecuteBehaviorTree_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_code
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // blocker_code
  rosidl_runtime_c__String__fini(&msg->blocker_code);
  // blocker_message
  rosidl_runtime_c__String__fini(&msg->blocker_message);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Result__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_Result * lhs, const agt_interfaces__action__ExecuteBehaviorTree_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // blocker_code
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->blocker_code), &(rhs->blocker_code)))
  {
    return false;
  }
  // blocker_message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->blocker_message), &(rhs->blocker_message)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Result__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_Result * input,
  agt_interfaces__action__ExecuteBehaviorTree_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // error_code
  output->error_code = input->error_code;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // blocker_code
  if (!rosidl_runtime_c__String__copy(
      &(input->blocker_code), &(output->blocker_code)))
  {
    return false;
  }
  // blocker_message
  if (!rosidl_runtime_c__String__copy(
      &(input->blocker_message), &(output->blocker_message)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ExecuteBehaviorTree_Result *
agt_interfaces__action__ExecuteBehaviorTree_Result__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_Result * msg = (agt_interfaces__action__ExecuteBehaviorTree_Result *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ExecuteBehaviorTree_Result));
  bool success = agt_interfaces__action__ExecuteBehaviorTree_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ExecuteBehaviorTree_Result__destroy(agt_interfaces__action__ExecuteBehaviorTree_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ExecuteBehaviorTree_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__init(agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_Result * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ExecuteBehaviorTree_Result *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ExecuteBehaviorTree_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ExecuteBehaviorTree_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ExecuteBehaviorTree_Result__fini(&data[i - 1]);
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
agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__fini(agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence * array)
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
      agt_interfaces__action__ExecuteBehaviorTree_Result__fini(&array->data[i]);
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

agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence *
agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence * array = (agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__destroy(agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence * lhs, const agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence * input,
  agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ExecuteBehaviorTree_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ExecuteBehaviorTree_Result * data =
      (agt_interfaces__action__ExecuteBehaviorTree_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ExecuteBehaviorTree_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ExecuteBehaviorTree_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `tree_state`
// Member `active_node`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__action__ExecuteBehaviorTree_Feedback__init(agt_interfaces__action__ExecuteBehaviorTree_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // tree_state
  if (!rosidl_runtime_c__String__init(&msg->tree_state)) {
    agt_interfaces__action__ExecuteBehaviorTree_Feedback__fini(msg);
    return false;
  }
  // active_node
  if (!rosidl_runtime_c__String__init(&msg->active_node)) {
    agt_interfaces__action__ExecuteBehaviorTree_Feedback__fini(msg);
    return false;
  }
  // loop_index
  // current_waypoint
  // total_waypoints
  return true;
}

void
agt_interfaces__action__ExecuteBehaviorTree_Feedback__fini(agt_interfaces__action__ExecuteBehaviorTree_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // tree_state
  rosidl_runtime_c__String__fini(&msg->tree_state);
  // active_node
  rosidl_runtime_c__String__fini(&msg->active_node);
  // loop_index
  // current_waypoint
  // total_waypoints
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Feedback__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_Feedback * lhs, const agt_interfaces__action__ExecuteBehaviorTree_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // tree_state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->tree_state), &(rhs->tree_state)))
  {
    return false;
  }
  // active_node
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->active_node), &(rhs->active_node)))
  {
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
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Feedback__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_Feedback * input,
  agt_interfaces__action__ExecuteBehaviorTree_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // tree_state
  if (!rosidl_runtime_c__String__copy(
      &(input->tree_state), &(output->tree_state)))
  {
    return false;
  }
  // active_node
  if (!rosidl_runtime_c__String__copy(
      &(input->active_node), &(output->active_node)))
  {
    return false;
  }
  // loop_index
  output->loop_index = input->loop_index;
  // current_waypoint
  output->current_waypoint = input->current_waypoint;
  // total_waypoints
  output->total_waypoints = input->total_waypoints;
  return true;
}

agt_interfaces__action__ExecuteBehaviorTree_Feedback *
agt_interfaces__action__ExecuteBehaviorTree_Feedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_Feedback * msg = (agt_interfaces__action__ExecuteBehaviorTree_Feedback *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ExecuteBehaviorTree_Feedback));
  bool success = agt_interfaces__action__ExecuteBehaviorTree_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ExecuteBehaviorTree_Feedback__destroy(agt_interfaces__action__ExecuteBehaviorTree_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ExecuteBehaviorTree_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__init(agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_Feedback * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ExecuteBehaviorTree_Feedback *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ExecuteBehaviorTree_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ExecuteBehaviorTree_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ExecuteBehaviorTree_Feedback__fini(&data[i - 1]);
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
agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__fini(agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence * array)
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
      agt_interfaces__action__ExecuteBehaviorTree_Feedback__fini(&array->data[i]);
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

agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence *
agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence * array = (agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__destroy(agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence * lhs, const agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence * input,
  agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ExecuteBehaviorTree_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ExecuteBehaviorTree_Feedback * data =
      (agt_interfaces__action__ExecuteBehaviorTree_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ExecuteBehaviorTree_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ExecuteBehaviorTree_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__init(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!agt_interfaces__action__ExecuteBehaviorTree_Goal__init(&msg->goal)) {
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__fini(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(&msg->goal);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * lhs, const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!agt_interfaces__action__ExecuteBehaviorTree_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * input,
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!agt_interfaces__action__ExecuteBehaviorTree_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request *
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * msg = (agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request));
  bool success = agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__destroy(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__init(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__fini(&data[i - 1]);
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
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__fini(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence * array)
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
      agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__fini(&array->data[i]);
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

agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence *
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence * array = (agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__destroy(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence * lhs, const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence * input,
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * data =
      (agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__init(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__fini(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * lhs, const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * input,
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response *
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * msg = (agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response));
  bool success = agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__destroy(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__init(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__fini(&data[i - 1]);
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
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__fini(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence * array)
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
      agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__fini(&array->data[i]);
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

agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence *
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence * array = (agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__destroy(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence * lhs, const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence * input,
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * data =
      (agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__init(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__fini(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * lhs, const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * input,
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request *
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * msg = (agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request));
  bool success = agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__destroy(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__init(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__fini(&data[i - 1]);
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
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__fini(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence * array)
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
      agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__fini(&array->data[i]);
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

agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence *
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence * array = (agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__destroy(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence * lhs, const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence * input,
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * data =
      (agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__init(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!agt_interfaces__action__ExecuteBehaviorTree_Result__init(&msg->result)) {
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__fini(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  agt_interfaces__action__ExecuteBehaviorTree_Result__fini(&msg->result);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * lhs, const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!agt_interfaces__action__ExecuteBehaviorTree_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * input,
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!agt_interfaces__action__ExecuteBehaviorTree_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response *
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * msg = (agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response));
  bool success = agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__destroy(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__init(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__fini(&data[i - 1]);
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
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__fini(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence * array)
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
      agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__fini(&array->data[i]);
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

agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence *
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence * array = (agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__destroy(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence * lhs, const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence * input,
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * data =
      (agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"

bool
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__init(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!agt_interfaces__action__ExecuteBehaviorTree_Feedback__init(&msg->feedback)) {
    agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__fini(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  agt_interfaces__action__ExecuteBehaviorTree_Feedback__fini(&msg->feedback);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * lhs, const agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!agt_interfaces__action__ExecuteBehaviorTree_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * input,
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!agt_interfaces__action__ExecuteBehaviorTree_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage *
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * msg = (agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage));
  bool success = agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__destroy(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__init(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__fini(&data[i - 1]);
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
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__fini(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence * array)
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
      agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__fini(&array->data[i]);
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

agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence *
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence * array = (agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__destroy(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__are_equal(const agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence * lhs, const agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__copy(
  const agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence * input,
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * data =
      (agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
