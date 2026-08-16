// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/ExperimentSummary.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/experiment_summary__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `experiment_id`
// Member `title`
// Member `created_at`
// Member `start_time`
// Member `end_time`
// Member `platform_profile`
// Member `map_id`
// Member `map_version_id`
// Member `map_hash`
// Member `mission_id`
// Member `mission_version`
// Member `mission_sha256`
// Member `launch_profile`
// Member `result_status`
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__msg__ExperimentSummary__init(agt_interfaces__msg__ExperimentSummary * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // experiment_id
  if (!rosidl_runtime_c__String__init(&msg->experiment_id)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // title
  if (!rosidl_runtime_c__String__init(&msg->title)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // state
  // created_at
  if (!rosidl_runtime_c__String__init(&msg->created_at)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // start_time
  if (!rosidl_runtime_c__String__init(&msg->start_time)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // end_time
  if (!rosidl_runtime_c__String__init(&msg->end_time)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // platform_profile
  if (!rosidl_runtime_c__String__init(&msg->platform_profile)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // map_hash
  if (!rosidl_runtime_c__String__init(&msg->map_hash)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // mission_id
  if (!rosidl_runtime_c__String__init(&msg->mission_id)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // mission_version
  if (!rosidl_runtime_c__String__init(&msg->mission_version)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // mission_sha256
  if (!rosidl_runtime_c__String__init(&msg->mission_sha256)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // launch_profile
  if (!rosidl_runtime_c__String__init(&msg->launch_profile)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // result_status
  if (!rosidl_runtime_c__String__init(&msg->result_status)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  // config_snapshot_count
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__ExperimentSummary__fini(agt_interfaces__msg__ExperimentSummary * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // experiment_id
  rosidl_runtime_c__String__fini(&msg->experiment_id);
  // title
  rosidl_runtime_c__String__fini(&msg->title);
  // state
  // created_at
  rosidl_runtime_c__String__fini(&msg->created_at);
  // start_time
  rosidl_runtime_c__String__fini(&msg->start_time);
  // end_time
  rosidl_runtime_c__String__fini(&msg->end_time);
  // platform_profile
  rosidl_runtime_c__String__fini(&msg->platform_profile);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // map_hash
  rosidl_runtime_c__String__fini(&msg->map_hash);
  // mission_id
  rosidl_runtime_c__String__fini(&msg->mission_id);
  // mission_version
  rosidl_runtime_c__String__fini(&msg->mission_version);
  // mission_sha256
  rosidl_runtime_c__String__fini(&msg->mission_sha256);
  // launch_profile
  rosidl_runtime_c__String__fini(&msg->launch_profile);
  // result_status
  rosidl_runtime_c__String__fini(&msg->result_status);
  // config_snapshot_count
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
agt_interfaces__msg__ExperimentSummary__are_equal(const agt_interfaces__msg__ExperimentSummary * lhs, const agt_interfaces__msg__ExperimentSummary * rhs)
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
  // experiment_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->experiment_id), &(rhs->experiment_id)))
  {
    return false;
  }
  // title
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->title), &(rhs->title)))
  {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // created_at
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->created_at), &(rhs->created_at)))
  {
    return false;
  }
  // start_time
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->start_time), &(rhs->start_time)))
  {
    return false;
  }
  // end_time
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->end_time), &(rhs->end_time)))
  {
    return false;
  }
  // platform_profile
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->platform_profile), &(rhs->platform_profile)))
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
  // map_hash
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_hash), &(rhs->map_hash)))
  {
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
  // mission_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mission_sha256), &(rhs->mission_sha256)))
  {
    return false;
  }
  // launch_profile
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->launch_profile), &(rhs->launch_profile)))
  {
    return false;
  }
  // result_status
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->result_status), &(rhs->result_status)))
  {
    return false;
  }
  // config_snapshot_count
  if (lhs->config_snapshot_count != rhs->config_snapshot_count) {
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
agt_interfaces__msg__ExperimentSummary__copy(
  const agt_interfaces__msg__ExperimentSummary * input,
  agt_interfaces__msg__ExperimentSummary * output)
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
  // experiment_id
  if (!rosidl_runtime_c__String__copy(
      &(input->experiment_id), &(output->experiment_id)))
  {
    return false;
  }
  // title
  if (!rosidl_runtime_c__String__copy(
      &(input->title), &(output->title)))
  {
    return false;
  }
  // state
  output->state = input->state;
  // created_at
  if (!rosidl_runtime_c__String__copy(
      &(input->created_at), &(output->created_at)))
  {
    return false;
  }
  // start_time
  if (!rosidl_runtime_c__String__copy(
      &(input->start_time), &(output->start_time)))
  {
    return false;
  }
  // end_time
  if (!rosidl_runtime_c__String__copy(
      &(input->end_time), &(output->end_time)))
  {
    return false;
  }
  // platform_profile
  if (!rosidl_runtime_c__String__copy(
      &(input->platform_profile), &(output->platform_profile)))
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
  // map_hash
  if (!rosidl_runtime_c__String__copy(
      &(input->map_hash), &(output->map_hash)))
  {
    return false;
  }
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
  // mission_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->mission_sha256), &(output->mission_sha256)))
  {
    return false;
  }
  // launch_profile
  if (!rosidl_runtime_c__String__copy(
      &(input->launch_profile), &(output->launch_profile)))
  {
    return false;
  }
  // result_status
  if (!rosidl_runtime_c__String__copy(
      &(input->result_status), &(output->result_status)))
  {
    return false;
  }
  // config_snapshot_count
  output->config_snapshot_count = input->config_snapshot_count;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

agt_interfaces__msg__ExperimentSummary *
agt_interfaces__msg__ExperimentSummary__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__ExperimentSummary * msg = (agt_interfaces__msg__ExperimentSummary *)allocator.allocate(sizeof(agt_interfaces__msg__ExperimentSummary), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__ExperimentSummary));
  bool success = agt_interfaces__msg__ExperimentSummary__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__ExperimentSummary__destroy(agt_interfaces__msg__ExperimentSummary * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__ExperimentSummary__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__ExperimentSummary__Sequence__init(agt_interfaces__msg__ExperimentSummary__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__ExperimentSummary * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__ExperimentSummary *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__ExperimentSummary), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__ExperimentSummary__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__ExperimentSummary__fini(&data[i - 1]);
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
agt_interfaces__msg__ExperimentSummary__Sequence__fini(agt_interfaces__msg__ExperimentSummary__Sequence * array)
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
      agt_interfaces__msg__ExperimentSummary__fini(&array->data[i]);
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

agt_interfaces__msg__ExperimentSummary__Sequence *
agt_interfaces__msg__ExperimentSummary__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__ExperimentSummary__Sequence * array = (agt_interfaces__msg__ExperimentSummary__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__ExperimentSummary__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__ExperimentSummary__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__ExperimentSummary__Sequence__destroy(agt_interfaces__msg__ExperimentSummary__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__ExperimentSummary__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__ExperimentSummary__Sequence__are_equal(const agt_interfaces__msg__ExperimentSummary__Sequence * lhs, const agt_interfaces__msg__ExperimentSummary__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__ExperimentSummary__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__ExperimentSummary__Sequence__copy(
  const agt_interfaces__msg__ExperimentSummary__Sequence * input,
  agt_interfaces__msg__ExperimentSummary__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__ExperimentSummary);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__ExperimentSummary * data =
      (agt_interfaces__msg__ExperimentSummary *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__ExperimentSummary__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__ExperimentSummary__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__ExperimentSummary__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
