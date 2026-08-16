// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:srv/ActivateMapVersion.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/srv/detail/activate_map_version__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `map_id`
// Member `map_version_id`
// Member `client_request_id`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__srv__ActivateMapVersion_Request__init(agt_interfaces__srv__ActivateMapVersion_Request * msg)
{
  if (!msg) {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__srv__ActivateMapVersion_Request__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__srv__ActivateMapVersion_Request__fini(msg);
    return false;
  }
  // client_request_id
  if (!rosidl_runtime_c__String__init(&msg->client_request_id)) {
    agt_interfaces__srv__ActivateMapVersion_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__srv__ActivateMapVersion_Request__fini(agt_interfaces__srv__ActivateMapVersion_Request * msg)
{
  if (!msg) {
    return;
  }
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // client_request_id
  rosidl_runtime_c__String__fini(&msg->client_request_id);
}

bool
agt_interfaces__srv__ActivateMapVersion_Request__are_equal(const agt_interfaces__srv__ActivateMapVersion_Request * lhs, const agt_interfaces__srv__ActivateMapVersion_Request * rhs)
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
  // client_request_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->client_request_id), &(rhs->client_request_id)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__srv__ActivateMapVersion_Request__copy(
  const agt_interfaces__srv__ActivateMapVersion_Request * input,
  agt_interfaces__srv__ActivateMapVersion_Request * output)
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
  // client_request_id
  if (!rosidl_runtime_c__String__copy(
      &(input->client_request_id), &(output->client_request_id)))
  {
    return false;
  }
  return true;
}

agt_interfaces__srv__ActivateMapVersion_Request *
agt_interfaces__srv__ActivateMapVersion_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ActivateMapVersion_Request * msg = (agt_interfaces__srv__ActivateMapVersion_Request *)allocator.allocate(sizeof(agt_interfaces__srv__ActivateMapVersion_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__srv__ActivateMapVersion_Request));
  bool success = agt_interfaces__srv__ActivateMapVersion_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__srv__ActivateMapVersion_Request__destroy(agt_interfaces__srv__ActivateMapVersion_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__srv__ActivateMapVersion_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__srv__ActivateMapVersion_Request__Sequence__init(agt_interfaces__srv__ActivateMapVersion_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ActivateMapVersion_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__srv__ActivateMapVersion_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__srv__ActivateMapVersion_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__srv__ActivateMapVersion_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__srv__ActivateMapVersion_Request__fini(&data[i - 1]);
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
agt_interfaces__srv__ActivateMapVersion_Request__Sequence__fini(agt_interfaces__srv__ActivateMapVersion_Request__Sequence * array)
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
      agt_interfaces__srv__ActivateMapVersion_Request__fini(&array->data[i]);
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

agt_interfaces__srv__ActivateMapVersion_Request__Sequence *
agt_interfaces__srv__ActivateMapVersion_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ActivateMapVersion_Request__Sequence * array = (agt_interfaces__srv__ActivateMapVersion_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__srv__ActivateMapVersion_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__srv__ActivateMapVersion_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__srv__ActivateMapVersion_Request__Sequence__destroy(agt_interfaces__srv__ActivateMapVersion_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__srv__ActivateMapVersion_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__srv__ActivateMapVersion_Request__Sequence__are_equal(const agt_interfaces__srv__ActivateMapVersion_Request__Sequence * lhs, const agt_interfaces__srv__ActivateMapVersion_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__srv__ActivateMapVersion_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__srv__ActivateMapVersion_Request__Sequence__copy(
  const agt_interfaces__srv__ActivateMapVersion_Request__Sequence * input,
  agt_interfaces__srv__ActivateMapVersion_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__srv__ActivateMapVersion_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__srv__ActivateMapVersion_Request * data =
      (agt_interfaces__srv__ActivateMapVersion_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__srv__ActivateMapVersion_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__srv__ActivateMapVersion_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__srv__ActivateMapVersion_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `map_id`
// Member `map_version_id`
// Member `state`
// Member `blocker_codes`
// Member `blocker_messages`
// Member `operator_messages`
// Member `technical_messages`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `version`
#include "agt_interfaces/msg/detail/map_version_summary__functions.h"

bool
agt_interfaces__srv__ActivateMapVersion_Response__init(agt_interfaces__srv__ActivateMapVersion_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_code
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__srv__ActivateMapVersion_Response__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__srv__ActivateMapVersion_Response__fini(msg);
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__init(&msg->state)) {
    agt_interfaces__srv__ActivateMapVersion_Response__fini(msg);
    return false;
  }
  // blocker_codes
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_codes, 0)) {
    agt_interfaces__srv__ActivateMapVersion_Response__fini(msg);
    return false;
  }
  // blocker_messages
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_messages, 0)) {
    agt_interfaces__srv__ActivateMapVersion_Response__fini(msg);
    return false;
  }
  // operator_messages
  if (!rosidl_runtime_c__String__Sequence__init(&msg->operator_messages, 0)) {
    agt_interfaces__srv__ActivateMapVersion_Response__fini(msg);
    return false;
  }
  // technical_messages
  if (!rosidl_runtime_c__String__Sequence__init(&msg->technical_messages, 0)) {
    agt_interfaces__srv__ActivateMapVersion_Response__fini(msg);
    return false;
  }
  // version
  if (!agt_interfaces__msg__MapVersionSummary__init(&msg->version)) {
    agt_interfaces__srv__ActivateMapVersion_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__srv__ActivateMapVersion_Response__fini(agt_interfaces__srv__ActivateMapVersion_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_code
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // state
  rosidl_runtime_c__String__fini(&msg->state);
  // blocker_codes
  rosidl_runtime_c__String__Sequence__fini(&msg->blocker_codes);
  // blocker_messages
  rosidl_runtime_c__String__Sequence__fini(&msg->blocker_messages);
  // operator_messages
  rosidl_runtime_c__String__Sequence__fini(&msg->operator_messages);
  // technical_messages
  rosidl_runtime_c__String__Sequence__fini(&msg->technical_messages);
  // version
  agt_interfaces__msg__MapVersionSummary__fini(&msg->version);
}

bool
agt_interfaces__srv__ActivateMapVersion_Response__are_equal(const agt_interfaces__srv__ActivateMapVersion_Response * lhs, const agt_interfaces__srv__ActivateMapVersion_Response * rhs)
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
  // state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->state), &(rhs->state)))
  {
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
  // operator_messages
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->operator_messages), &(rhs->operator_messages)))
  {
    return false;
  }
  // technical_messages
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->technical_messages), &(rhs->technical_messages)))
  {
    return false;
  }
  // version
  if (!agt_interfaces__msg__MapVersionSummary__are_equal(
      &(lhs->version), &(rhs->version)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__srv__ActivateMapVersion_Response__copy(
  const agt_interfaces__srv__ActivateMapVersion_Response * input,
  agt_interfaces__srv__ActivateMapVersion_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // error_code
  output->error_code = input->error_code;
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
  // state
  if (!rosidl_runtime_c__String__copy(
      &(input->state), &(output->state)))
  {
    return false;
  }
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
  // operator_messages
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->operator_messages), &(output->operator_messages)))
  {
    return false;
  }
  // technical_messages
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->technical_messages), &(output->technical_messages)))
  {
    return false;
  }
  // version
  if (!agt_interfaces__msg__MapVersionSummary__copy(
      &(input->version), &(output->version)))
  {
    return false;
  }
  return true;
}

agt_interfaces__srv__ActivateMapVersion_Response *
agt_interfaces__srv__ActivateMapVersion_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ActivateMapVersion_Response * msg = (agt_interfaces__srv__ActivateMapVersion_Response *)allocator.allocate(sizeof(agt_interfaces__srv__ActivateMapVersion_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__srv__ActivateMapVersion_Response));
  bool success = agt_interfaces__srv__ActivateMapVersion_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__srv__ActivateMapVersion_Response__destroy(agt_interfaces__srv__ActivateMapVersion_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__srv__ActivateMapVersion_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__srv__ActivateMapVersion_Response__Sequence__init(agt_interfaces__srv__ActivateMapVersion_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ActivateMapVersion_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__srv__ActivateMapVersion_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__srv__ActivateMapVersion_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__srv__ActivateMapVersion_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__srv__ActivateMapVersion_Response__fini(&data[i - 1]);
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
agt_interfaces__srv__ActivateMapVersion_Response__Sequence__fini(agt_interfaces__srv__ActivateMapVersion_Response__Sequence * array)
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
      agt_interfaces__srv__ActivateMapVersion_Response__fini(&array->data[i]);
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

agt_interfaces__srv__ActivateMapVersion_Response__Sequence *
agt_interfaces__srv__ActivateMapVersion_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ActivateMapVersion_Response__Sequence * array = (agt_interfaces__srv__ActivateMapVersion_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__srv__ActivateMapVersion_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__srv__ActivateMapVersion_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__srv__ActivateMapVersion_Response__Sequence__destroy(agt_interfaces__srv__ActivateMapVersion_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__srv__ActivateMapVersion_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__srv__ActivateMapVersion_Response__Sequence__are_equal(const agt_interfaces__srv__ActivateMapVersion_Response__Sequence * lhs, const agt_interfaces__srv__ActivateMapVersion_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__srv__ActivateMapVersion_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__srv__ActivateMapVersion_Response__Sequence__copy(
  const agt_interfaces__srv__ActivateMapVersion_Response__Sequence * input,
  agt_interfaces__srv__ActivateMapVersion_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__srv__ActivateMapVersion_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__srv__ActivateMapVersion_Response * data =
      (agt_interfaces__srv__ActivateMapVersion_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__srv__ActivateMapVersion_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__srv__ActivateMapVersion_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__srv__ActivateMapVersion_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
