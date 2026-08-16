// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:srv/ArchiveTaskGroup.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/srv/detail/archive_task_group__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `map_id`
// Member `map_version_id`
// Member `task_group_id`
// Member `client_request_id`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__srv__ArchiveTaskGroup_Request__init(agt_interfaces__srv__ArchiveTaskGroup_Request * msg)
{
  if (!msg) {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__srv__ArchiveTaskGroup_Request__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__srv__ArchiveTaskGroup_Request__fini(msg);
    return false;
  }
  // task_group_id
  if (!rosidl_runtime_c__String__init(&msg->task_group_id)) {
    agt_interfaces__srv__ArchiveTaskGroup_Request__fini(msg);
    return false;
  }
  // expected_revision
  // client_request_id
  if (!rosidl_runtime_c__String__init(&msg->client_request_id)) {
    agt_interfaces__srv__ArchiveTaskGroup_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__srv__ArchiveTaskGroup_Request__fini(agt_interfaces__srv__ArchiveTaskGroup_Request * msg)
{
  if (!msg) {
    return;
  }
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // task_group_id
  rosidl_runtime_c__String__fini(&msg->task_group_id);
  // expected_revision
  // client_request_id
  rosidl_runtime_c__String__fini(&msg->client_request_id);
}

bool
agt_interfaces__srv__ArchiveTaskGroup_Request__are_equal(const agt_interfaces__srv__ArchiveTaskGroup_Request * lhs, const agt_interfaces__srv__ArchiveTaskGroup_Request * rhs)
{
  if (!lhs || !rhs) {
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
  // expected_revision
  if (lhs->expected_revision != rhs->expected_revision) {
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
agt_interfaces__srv__ArchiveTaskGroup_Request__copy(
  const agt_interfaces__srv__ArchiveTaskGroup_Request * input,
  agt_interfaces__srv__ArchiveTaskGroup_Request * output)
{
  if (!input || !output) {
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
  // expected_revision
  output->expected_revision = input->expected_revision;
  // client_request_id
  if (!rosidl_runtime_c__String__copy(
      &(input->client_request_id), &(output->client_request_id)))
  {
    return false;
  }
  return true;
}

agt_interfaces__srv__ArchiveTaskGroup_Request *
agt_interfaces__srv__ArchiveTaskGroup_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ArchiveTaskGroup_Request * msg = (agt_interfaces__srv__ArchiveTaskGroup_Request *)allocator.allocate(sizeof(agt_interfaces__srv__ArchiveTaskGroup_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__srv__ArchiveTaskGroup_Request));
  bool success = agt_interfaces__srv__ArchiveTaskGroup_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__srv__ArchiveTaskGroup_Request__destroy(agt_interfaces__srv__ArchiveTaskGroup_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__srv__ArchiveTaskGroup_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__init(agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ArchiveTaskGroup_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__srv__ArchiveTaskGroup_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__srv__ArchiveTaskGroup_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__srv__ArchiveTaskGroup_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__srv__ArchiveTaskGroup_Request__fini(&data[i - 1]);
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
agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__fini(agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence * array)
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
      agt_interfaces__srv__ArchiveTaskGroup_Request__fini(&array->data[i]);
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

agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence *
agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence * array = (agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__destroy(agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__are_equal(const agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence * lhs, const agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__srv__ArchiveTaskGroup_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__copy(
  const agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence * input,
  agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__srv__ArchiveTaskGroup_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__srv__ArchiveTaskGroup_Request * data =
      (agt_interfaces__srv__ArchiveTaskGroup_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__srv__ArchiveTaskGroup_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__srv__ArchiveTaskGroup_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__srv__ArchiveTaskGroup_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `blocker_code`
// Member `operator_message`
// Member `technical_message`
// Member `map_id`
// Member `map_version_id`
// Member `task_group_id`
// Member `archived_relative_path`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__srv__ArchiveTaskGroup_Response__init(agt_interfaces__srv__ArchiveTaskGroup_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_code
  // blocker_code
  if (!rosidl_runtime_c__String__init(&msg->blocker_code)) {
    agt_interfaces__srv__ArchiveTaskGroup_Response__fini(msg);
    return false;
  }
  // operator_message
  if (!rosidl_runtime_c__String__init(&msg->operator_message)) {
    agt_interfaces__srv__ArchiveTaskGroup_Response__fini(msg);
    return false;
  }
  // technical_message
  if (!rosidl_runtime_c__String__init(&msg->technical_message)) {
    agt_interfaces__srv__ArchiveTaskGroup_Response__fini(msg);
    return false;
  }
  // duplicate_request
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__srv__ArchiveTaskGroup_Response__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__srv__ArchiveTaskGroup_Response__fini(msg);
    return false;
  }
  // task_group_id
  if (!rosidl_runtime_c__String__init(&msg->task_group_id)) {
    agt_interfaces__srv__ArchiveTaskGroup_Response__fini(msg);
    return false;
  }
  // archived_revision
  // archived_relative_path
  if (!rosidl_runtime_c__String__init(&msg->archived_relative_path)) {
    agt_interfaces__srv__ArchiveTaskGroup_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__srv__ArchiveTaskGroup_Response__fini(agt_interfaces__srv__ArchiveTaskGroup_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_code
  // blocker_code
  rosidl_runtime_c__String__fini(&msg->blocker_code);
  // operator_message
  rosidl_runtime_c__String__fini(&msg->operator_message);
  // technical_message
  rosidl_runtime_c__String__fini(&msg->technical_message);
  // duplicate_request
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // task_group_id
  rosidl_runtime_c__String__fini(&msg->task_group_id);
  // archived_revision
  // archived_relative_path
  rosidl_runtime_c__String__fini(&msg->archived_relative_path);
}

bool
agt_interfaces__srv__ArchiveTaskGroup_Response__are_equal(const agt_interfaces__srv__ArchiveTaskGroup_Response * lhs, const agt_interfaces__srv__ArchiveTaskGroup_Response * rhs)
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
  // duplicate_request
  if (lhs->duplicate_request != rhs->duplicate_request) {
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
  // archived_revision
  if (lhs->archived_revision != rhs->archived_revision) {
    return false;
  }
  // archived_relative_path
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->archived_relative_path), &(rhs->archived_relative_path)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__srv__ArchiveTaskGroup_Response__copy(
  const agt_interfaces__srv__ArchiveTaskGroup_Response * input,
  agt_interfaces__srv__ArchiveTaskGroup_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
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
  // duplicate_request
  output->duplicate_request = input->duplicate_request;
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
  // archived_revision
  output->archived_revision = input->archived_revision;
  // archived_relative_path
  if (!rosidl_runtime_c__String__copy(
      &(input->archived_relative_path), &(output->archived_relative_path)))
  {
    return false;
  }
  return true;
}

agt_interfaces__srv__ArchiveTaskGroup_Response *
agt_interfaces__srv__ArchiveTaskGroup_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ArchiveTaskGroup_Response * msg = (agt_interfaces__srv__ArchiveTaskGroup_Response *)allocator.allocate(sizeof(agt_interfaces__srv__ArchiveTaskGroup_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__srv__ArchiveTaskGroup_Response));
  bool success = agt_interfaces__srv__ArchiveTaskGroup_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__srv__ArchiveTaskGroup_Response__destroy(agt_interfaces__srv__ArchiveTaskGroup_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__srv__ArchiveTaskGroup_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__init(agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ArchiveTaskGroup_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__srv__ArchiveTaskGroup_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__srv__ArchiveTaskGroup_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__srv__ArchiveTaskGroup_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__srv__ArchiveTaskGroup_Response__fini(&data[i - 1]);
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
agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__fini(agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence * array)
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
      agt_interfaces__srv__ArchiveTaskGroup_Response__fini(&array->data[i]);
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

agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence *
agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence * array = (agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__destroy(agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__are_equal(const agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence * lhs, const agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__srv__ArchiveTaskGroup_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__copy(
  const agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence * input,
  agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__srv__ArchiveTaskGroup_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__srv__ArchiveTaskGroup_Response * data =
      (agt_interfaces__srv__ArchiveTaskGroup_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__srv__ArchiveTaskGroup_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__srv__ArchiveTaskGroup_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__srv__ArchiveTaskGroup_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
