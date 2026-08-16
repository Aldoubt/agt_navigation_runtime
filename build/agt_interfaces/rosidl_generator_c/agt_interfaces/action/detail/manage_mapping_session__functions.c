// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:action/ManageMappingSession.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/action/detail/manage_mapping_session__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `map_id`
// Member `session_id`
// Member `argument_keys`
// Member `argument_values`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__action__ManageMappingSession_Goal__init(agt_interfaces__action__ManageMappingSession_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // operation
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__action__ManageMappingSession_Goal__fini(msg);
    return false;
  }
  // session_id
  if (!rosidl_runtime_c__String__init(&msg->session_id)) {
    agt_interfaces__action__ManageMappingSession_Goal__fini(msg);
    return false;
  }
  // argument_keys
  if (!rosidl_runtime_c__String__Sequence__init(&msg->argument_keys, 0)) {
    agt_interfaces__action__ManageMappingSession_Goal__fini(msg);
    return false;
  }
  // argument_values
  if (!rosidl_runtime_c__String__Sequence__init(&msg->argument_values, 0)) {
    agt_interfaces__action__ManageMappingSession_Goal__fini(msg);
    return false;
  }
  // activate_after_commit
  // timeout_s
  return true;
}

void
agt_interfaces__action__ManageMappingSession_Goal__fini(agt_interfaces__action__ManageMappingSession_Goal * msg)
{
  if (!msg) {
    return;
  }
  // operation
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // session_id
  rosidl_runtime_c__String__fini(&msg->session_id);
  // argument_keys
  rosidl_runtime_c__String__Sequence__fini(&msg->argument_keys);
  // argument_values
  rosidl_runtime_c__String__Sequence__fini(&msg->argument_values);
  // activate_after_commit
  // timeout_s
}

bool
agt_interfaces__action__ManageMappingSession_Goal__are_equal(const agt_interfaces__action__ManageMappingSession_Goal * lhs, const agt_interfaces__action__ManageMappingSession_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // operation
  if (lhs->operation != rhs->operation) {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_id), &(rhs->map_id)))
  {
    return false;
  }
  // session_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->session_id), &(rhs->session_id)))
  {
    return false;
  }
  // argument_keys
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->argument_keys), &(rhs->argument_keys)))
  {
    return false;
  }
  // argument_values
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->argument_values), &(rhs->argument_values)))
  {
    return false;
  }
  // activate_after_commit
  if (lhs->activate_after_commit != rhs->activate_after_commit) {
    return false;
  }
  // timeout_s
  if (lhs->timeout_s != rhs->timeout_s) {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_Goal__copy(
  const agt_interfaces__action__ManageMappingSession_Goal * input,
  agt_interfaces__action__ManageMappingSession_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // operation
  output->operation = input->operation;
  // map_id
  if (!rosidl_runtime_c__String__copy(
      &(input->map_id), &(output->map_id)))
  {
    return false;
  }
  // session_id
  if (!rosidl_runtime_c__String__copy(
      &(input->session_id), &(output->session_id)))
  {
    return false;
  }
  // argument_keys
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->argument_keys), &(output->argument_keys)))
  {
    return false;
  }
  // argument_values
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->argument_values), &(output->argument_values)))
  {
    return false;
  }
  // activate_after_commit
  output->activate_after_commit = input->activate_after_commit;
  // timeout_s
  output->timeout_s = input->timeout_s;
  return true;
}

agt_interfaces__action__ManageMappingSession_Goal *
agt_interfaces__action__ManageMappingSession_Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_Goal * msg = (agt_interfaces__action__ManageMappingSession_Goal *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ManageMappingSession_Goal));
  bool success = agt_interfaces__action__ManageMappingSession_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ManageMappingSession_Goal__destroy(agt_interfaces__action__ManageMappingSession_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ManageMappingSession_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ManageMappingSession_Goal__Sequence__init(agt_interfaces__action__ManageMappingSession_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_Goal * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ManageMappingSession_Goal *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ManageMappingSession_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ManageMappingSession_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ManageMappingSession_Goal__fini(&data[i - 1]);
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
agt_interfaces__action__ManageMappingSession_Goal__Sequence__fini(agt_interfaces__action__ManageMappingSession_Goal__Sequence * array)
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
      agt_interfaces__action__ManageMappingSession_Goal__fini(&array->data[i]);
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

agt_interfaces__action__ManageMappingSession_Goal__Sequence *
agt_interfaces__action__ManageMappingSession_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_Goal__Sequence * array = (agt_interfaces__action__ManageMappingSession_Goal__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ManageMappingSession_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ManageMappingSession_Goal__Sequence__destroy(agt_interfaces__action__ManageMappingSession_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ManageMappingSession_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ManageMappingSession_Goal__Sequence__are_equal(const agt_interfaces__action__ManageMappingSession_Goal__Sequence * lhs, const agt_interfaces__action__ManageMappingSession_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_Goal__Sequence__copy(
  const agt_interfaces__action__ManageMappingSession_Goal__Sequence * input,
  agt_interfaces__action__ManageMappingSession_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ManageMappingSession_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ManageMappingSession_Goal * data =
      (agt_interfaces__action__ManageMappingSession_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ManageMappingSession_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ManageMappingSession_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `state`
// Member `session_id`
// Member `map_id`
// Member `map_version_id`
// Member `session_file`
// Member `candidate_map_yaml`
// Member `candidate_map_image`
// Member `localization_pcd`
// Member `processing_record`
// Member `bag_directory`
// Member `registered_map_yaml`
// Member `tasks_directory`
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__action__ManageMappingSession_Result__init(agt_interfaces__action__ManageMappingSession_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_code
  // state
  if (!rosidl_runtime_c__String__init(&msg->state)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // session_id
  if (!rosidl_runtime_c__String__init(&msg->session_id)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // session_file
  if (!rosidl_runtime_c__String__init(&msg->session_file)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // candidate_map_yaml
  if (!rosidl_runtime_c__String__init(&msg->candidate_map_yaml)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // candidate_map_image
  if (!rosidl_runtime_c__String__init(&msg->candidate_map_image)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // localization_pcd
  if (!rosidl_runtime_c__String__init(&msg->localization_pcd)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // processing_record
  if (!rosidl_runtime_c__String__init(&msg->processing_record)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // bag_directory
  if (!rosidl_runtime_c__String__init(&msg->bag_directory)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // registered_map_yaml
  if (!rosidl_runtime_c__String__init(&msg->registered_map_yaml)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // tasks_directory
  if (!rosidl_runtime_c__String__init(&msg->tasks_directory)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ManageMappingSession_Result__fini(agt_interfaces__action__ManageMappingSession_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_code
  // state
  rosidl_runtime_c__String__fini(&msg->state);
  // session_id
  rosidl_runtime_c__String__fini(&msg->session_id);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // session_file
  rosidl_runtime_c__String__fini(&msg->session_file);
  // candidate_map_yaml
  rosidl_runtime_c__String__fini(&msg->candidate_map_yaml);
  // candidate_map_image
  rosidl_runtime_c__String__fini(&msg->candidate_map_image);
  // localization_pcd
  rosidl_runtime_c__String__fini(&msg->localization_pcd);
  // processing_record
  rosidl_runtime_c__String__fini(&msg->processing_record);
  // bag_directory
  rosidl_runtime_c__String__fini(&msg->bag_directory);
  // registered_map_yaml
  rosidl_runtime_c__String__fini(&msg->registered_map_yaml);
  // tasks_directory
  rosidl_runtime_c__String__fini(&msg->tasks_directory);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
agt_interfaces__action__ManageMappingSession_Result__are_equal(const agt_interfaces__action__ManageMappingSession_Result * lhs, const agt_interfaces__action__ManageMappingSession_Result * rhs)
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
  // state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->state), &(rhs->state)))
  {
    return false;
  }
  // session_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->session_id), &(rhs->session_id)))
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
  // session_file
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->session_file), &(rhs->session_file)))
  {
    return false;
  }
  // candidate_map_yaml
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->candidate_map_yaml), &(rhs->candidate_map_yaml)))
  {
    return false;
  }
  // candidate_map_image
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->candidate_map_image), &(rhs->candidate_map_image)))
  {
    return false;
  }
  // localization_pcd
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->localization_pcd), &(rhs->localization_pcd)))
  {
    return false;
  }
  // processing_record
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->processing_record), &(rhs->processing_record)))
  {
    return false;
  }
  // bag_directory
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->bag_directory), &(rhs->bag_directory)))
  {
    return false;
  }
  // registered_map_yaml
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->registered_map_yaml), &(rhs->registered_map_yaml)))
  {
    return false;
  }
  // tasks_directory
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->tasks_directory), &(rhs->tasks_directory)))
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
agt_interfaces__action__ManageMappingSession_Result__copy(
  const agt_interfaces__action__ManageMappingSession_Result * input,
  agt_interfaces__action__ManageMappingSession_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // error_code
  output->error_code = input->error_code;
  // state
  if (!rosidl_runtime_c__String__copy(
      &(input->state), &(output->state)))
  {
    return false;
  }
  // session_id
  if (!rosidl_runtime_c__String__copy(
      &(input->session_id), &(output->session_id)))
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
  // session_file
  if (!rosidl_runtime_c__String__copy(
      &(input->session_file), &(output->session_file)))
  {
    return false;
  }
  // candidate_map_yaml
  if (!rosidl_runtime_c__String__copy(
      &(input->candidate_map_yaml), &(output->candidate_map_yaml)))
  {
    return false;
  }
  // candidate_map_image
  if (!rosidl_runtime_c__String__copy(
      &(input->candidate_map_image), &(output->candidate_map_image)))
  {
    return false;
  }
  // localization_pcd
  if (!rosidl_runtime_c__String__copy(
      &(input->localization_pcd), &(output->localization_pcd)))
  {
    return false;
  }
  // processing_record
  if (!rosidl_runtime_c__String__copy(
      &(input->processing_record), &(output->processing_record)))
  {
    return false;
  }
  // bag_directory
  if (!rosidl_runtime_c__String__copy(
      &(input->bag_directory), &(output->bag_directory)))
  {
    return false;
  }
  // registered_map_yaml
  if (!rosidl_runtime_c__String__copy(
      &(input->registered_map_yaml), &(output->registered_map_yaml)))
  {
    return false;
  }
  // tasks_directory
  if (!rosidl_runtime_c__String__copy(
      &(input->tasks_directory), &(output->tasks_directory)))
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

agt_interfaces__action__ManageMappingSession_Result *
agt_interfaces__action__ManageMappingSession_Result__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_Result * msg = (agt_interfaces__action__ManageMappingSession_Result *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ManageMappingSession_Result));
  bool success = agt_interfaces__action__ManageMappingSession_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ManageMappingSession_Result__destroy(agt_interfaces__action__ManageMappingSession_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ManageMappingSession_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ManageMappingSession_Result__Sequence__init(agt_interfaces__action__ManageMappingSession_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_Result * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ManageMappingSession_Result *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ManageMappingSession_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ManageMappingSession_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ManageMappingSession_Result__fini(&data[i - 1]);
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
agt_interfaces__action__ManageMappingSession_Result__Sequence__fini(agt_interfaces__action__ManageMappingSession_Result__Sequence * array)
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
      agt_interfaces__action__ManageMappingSession_Result__fini(&array->data[i]);
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

agt_interfaces__action__ManageMappingSession_Result__Sequence *
agt_interfaces__action__ManageMappingSession_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_Result__Sequence * array = (agt_interfaces__action__ManageMappingSession_Result__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ManageMappingSession_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ManageMappingSession_Result__Sequence__destroy(agt_interfaces__action__ManageMappingSession_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ManageMappingSession_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ManageMappingSession_Result__Sequence__are_equal(const agt_interfaces__action__ManageMappingSession_Result__Sequence * lhs, const agt_interfaces__action__ManageMappingSession_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_Result__Sequence__copy(
  const agt_interfaces__action__ManageMappingSession_Result__Sequence * input,
  agt_interfaces__action__ManageMappingSession_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ManageMappingSession_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ManageMappingSession_Result * data =
      (agt_interfaces__action__ManageMappingSession_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ManageMappingSession_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ManageMappingSession_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `state`
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__action__ManageMappingSession_Feedback__init(agt_interfaces__action__ManageMappingSession_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__init(&msg->state)) {
    agt_interfaces__action__ManageMappingSession_Feedback__fini(msg);
    return false;
  }
  // progress
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__action__ManageMappingSession_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ManageMappingSession_Feedback__fini(agt_interfaces__action__ManageMappingSession_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // state
  rosidl_runtime_c__String__fini(&msg->state);
  // progress
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
agt_interfaces__action__ManageMappingSession_Feedback__are_equal(const agt_interfaces__action__ManageMappingSession_Feedback * lhs, const agt_interfaces__action__ManageMappingSession_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->state), &(rhs->state)))
  {
    return false;
  }
  // progress
  if (lhs->progress != rhs->progress) {
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
agt_interfaces__action__ManageMappingSession_Feedback__copy(
  const agt_interfaces__action__ManageMappingSession_Feedback * input,
  agt_interfaces__action__ManageMappingSession_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__copy(
      &(input->state), &(output->state)))
  {
    return false;
  }
  // progress
  output->progress = input->progress;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ManageMappingSession_Feedback *
agt_interfaces__action__ManageMappingSession_Feedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_Feedback * msg = (agt_interfaces__action__ManageMappingSession_Feedback *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ManageMappingSession_Feedback));
  bool success = agt_interfaces__action__ManageMappingSession_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ManageMappingSession_Feedback__destroy(agt_interfaces__action__ManageMappingSession_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ManageMappingSession_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ManageMappingSession_Feedback__Sequence__init(agt_interfaces__action__ManageMappingSession_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_Feedback * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ManageMappingSession_Feedback *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ManageMappingSession_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ManageMappingSession_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ManageMappingSession_Feedback__fini(&data[i - 1]);
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
agt_interfaces__action__ManageMappingSession_Feedback__Sequence__fini(agt_interfaces__action__ManageMappingSession_Feedback__Sequence * array)
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
      agt_interfaces__action__ManageMappingSession_Feedback__fini(&array->data[i]);
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

agt_interfaces__action__ManageMappingSession_Feedback__Sequence *
agt_interfaces__action__ManageMappingSession_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_Feedback__Sequence * array = (agt_interfaces__action__ManageMappingSession_Feedback__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ManageMappingSession_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ManageMappingSession_Feedback__Sequence__destroy(agt_interfaces__action__ManageMappingSession_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ManageMappingSession_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ManageMappingSession_Feedback__Sequence__are_equal(const agt_interfaces__action__ManageMappingSession_Feedback__Sequence * lhs, const agt_interfaces__action__ManageMappingSession_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_Feedback__Sequence__copy(
  const agt_interfaces__action__ManageMappingSession_Feedback__Sequence * input,
  agt_interfaces__action__ManageMappingSession_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ManageMappingSession_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ManageMappingSession_Feedback * data =
      (agt_interfaces__action__ManageMappingSession_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ManageMappingSession_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ManageMappingSession_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_Feedback__copy(
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
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"

bool
agt_interfaces__action__ManageMappingSession_SendGoal_Request__init(agt_interfaces__action__ManageMappingSession_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    agt_interfaces__action__ManageMappingSession_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!agt_interfaces__action__ManageMappingSession_Goal__init(&msg->goal)) {
    agt_interfaces__action__ManageMappingSession_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ManageMappingSession_SendGoal_Request__fini(agt_interfaces__action__ManageMappingSession_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  agt_interfaces__action__ManageMappingSession_Goal__fini(&msg->goal);
}

bool
agt_interfaces__action__ManageMappingSession_SendGoal_Request__are_equal(const agt_interfaces__action__ManageMappingSession_SendGoal_Request * lhs, const agt_interfaces__action__ManageMappingSession_SendGoal_Request * rhs)
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
  if (!agt_interfaces__action__ManageMappingSession_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_SendGoal_Request__copy(
  const agt_interfaces__action__ManageMappingSession_SendGoal_Request * input,
  agt_interfaces__action__ManageMappingSession_SendGoal_Request * output)
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
  if (!agt_interfaces__action__ManageMappingSession_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ManageMappingSession_SendGoal_Request *
agt_interfaces__action__ManageMappingSession_SendGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_SendGoal_Request * msg = (agt_interfaces__action__ManageMappingSession_SendGoal_Request *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Request));
  bool success = agt_interfaces__action__ManageMappingSession_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ManageMappingSession_SendGoal_Request__destroy(agt_interfaces__action__ManageMappingSession_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ManageMappingSession_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__init(agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_SendGoal_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ManageMappingSession_SendGoal_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ManageMappingSession_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ManageMappingSession_SendGoal_Request__fini(&data[i - 1]);
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
agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__fini(agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence * array)
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
      agt_interfaces__action__ManageMappingSession_SendGoal_Request__fini(&array->data[i]);
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

agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence *
agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence * array = (agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__destroy(agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__are_equal(const agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence * lhs, const agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__copy(
  const agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence * input,
  agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ManageMappingSession_SendGoal_Request * data =
      (agt_interfaces__action__ManageMappingSession_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ManageMappingSession_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ManageMappingSession_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_SendGoal_Request__copy(
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
agt_interfaces__action__ManageMappingSession_SendGoal_Response__init(agt_interfaces__action__ManageMappingSession_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    agt_interfaces__action__ManageMappingSession_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ManageMappingSession_SendGoal_Response__fini(agt_interfaces__action__ManageMappingSession_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
agt_interfaces__action__ManageMappingSession_SendGoal_Response__are_equal(const agt_interfaces__action__ManageMappingSession_SendGoal_Response * lhs, const agt_interfaces__action__ManageMappingSession_SendGoal_Response * rhs)
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
agt_interfaces__action__ManageMappingSession_SendGoal_Response__copy(
  const agt_interfaces__action__ManageMappingSession_SendGoal_Response * input,
  agt_interfaces__action__ManageMappingSession_SendGoal_Response * output)
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

agt_interfaces__action__ManageMappingSession_SendGoal_Response *
agt_interfaces__action__ManageMappingSession_SendGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_SendGoal_Response * msg = (agt_interfaces__action__ManageMappingSession_SendGoal_Response *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Response));
  bool success = agt_interfaces__action__ManageMappingSession_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ManageMappingSession_SendGoal_Response__destroy(agt_interfaces__action__ManageMappingSession_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ManageMappingSession_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__init(agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_SendGoal_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ManageMappingSession_SendGoal_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ManageMappingSession_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ManageMappingSession_SendGoal_Response__fini(&data[i - 1]);
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
agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__fini(agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence * array)
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
      agt_interfaces__action__ManageMappingSession_SendGoal_Response__fini(&array->data[i]);
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

agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence *
agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence * array = (agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__destroy(agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__are_equal(const agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence * lhs, const agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__copy(
  const agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence * input,
  agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ManageMappingSession_SendGoal_Response * data =
      (agt_interfaces__action__ManageMappingSession_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ManageMappingSession_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ManageMappingSession_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_SendGoal_Response__copy(
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
agt_interfaces__action__ManageMappingSession_GetResult_Request__init(agt_interfaces__action__ManageMappingSession_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    agt_interfaces__action__ManageMappingSession_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ManageMappingSession_GetResult_Request__fini(agt_interfaces__action__ManageMappingSession_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
agt_interfaces__action__ManageMappingSession_GetResult_Request__are_equal(const agt_interfaces__action__ManageMappingSession_GetResult_Request * lhs, const agt_interfaces__action__ManageMappingSession_GetResult_Request * rhs)
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
agt_interfaces__action__ManageMappingSession_GetResult_Request__copy(
  const agt_interfaces__action__ManageMappingSession_GetResult_Request * input,
  agt_interfaces__action__ManageMappingSession_GetResult_Request * output)
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

agt_interfaces__action__ManageMappingSession_GetResult_Request *
agt_interfaces__action__ManageMappingSession_GetResult_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_GetResult_Request * msg = (agt_interfaces__action__ManageMappingSession_GetResult_Request *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Request));
  bool success = agt_interfaces__action__ManageMappingSession_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ManageMappingSession_GetResult_Request__destroy(agt_interfaces__action__ManageMappingSession_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ManageMappingSession_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__init(agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_GetResult_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ManageMappingSession_GetResult_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ManageMappingSession_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ManageMappingSession_GetResult_Request__fini(&data[i - 1]);
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
agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__fini(agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence * array)
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
      agt_interfaces__action__ManageMappingSession_GetResult_Request__fini(&array->data[i]);
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

agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence *
agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence * array = (agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__destroy(agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__are_equal(const agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence * lhs, const agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__copy(
  const agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence * input,
  agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ManageMappingSession_GetResult_Request * data =
      (agt_interfaces__action__ManageMappingSession_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ManageMappingSession_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ManageMappingSession_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_GetResult_Request__copy(
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
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"

bool
agt_interfaces__action__ManageMappingSession_GetResult_Response__init(agt_interfaces__action__ManageMappingSession_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!agt_interfaces__action__ManageMappingSession_Result__init(&msg->result)) {
    agt_interfaces__action__ManageMappingSession_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ManageMappingSession_GetResult_Response__fini(agt_interfaces__action__ManageMappingSession_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  agt_interfaces__action__ManageMappingSession_Result__fini(&msg->result);
}

bool
agt_interfaces__action__ManageMappingSession_GetResult_Response__are_equal(const agt_interfaces__action__ManageMappingSession_GetResult_Response * lhs, const agt_interfaces__action__ManageMappingSession_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!agt_interfaces__action__ManageMappingSession_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_GetResult_Response__copy(
  const agt_interfaces__action__ManageMappingSession_GetResult_Response * input,
  agt_interfaces__action__ManageMappingSession_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!agt_interfaces__action__ManageMappingSession_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ManageMappingSession_GetResult_Response *
agt_interfaces__action__ManageMappingSession_GetResult_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_GetResult_Response * msg = (agt_interfaces__action__ManageMappingSession_GetResult_Response *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Response));
  bool success = agt_interfaces__action__ManageMappingSession_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ManageMappingSession_GetResult_Response__destroy(agt_interfaces__action__ManageMappingSession_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ManageMappingSession_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__init(agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_GetResult_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ManageMappingSession_GetResult_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ManageMappingSession_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ManageMappingSession_GetResult_Response__fini(&data[i - 1]);
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
agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__fini(agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence * array)
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
      agt_interfaces__action__ManageMappingSession_GetResult_Response__fini(&array->data[i]);
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

agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence *
agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence * array = (agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__destroy(agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__are_equal(const agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence * lhs, const agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__copy(
  const agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence * input,
  agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ManageMappingSession_GetResult_Response * data =
      (agt_interfaces__action__ManageMappingSession_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ManageMappingSession_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ManageMappingSession_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_GetResult_Response__copy(
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
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"

bool
agt_interfaces__action__ManageMappingSession_FeedbackMessage__init(agt_interfaces__action__ManageMappingSession_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    agt_interfaces__action__ManageMappingSession_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!agt_interfaces__action__ManageMappingSession_Feedback__init(&msg->feedback)) {
    agt_interfaces__action__ManageMappingSession_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__ManageMappingSession_FeedbackMessage__fini(agt_interfaces__action__ManageMappingSession_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  agt_interfaces__action__ManageMappingSession_Feedback__fini(&msg->feedback);
}

bool
agt_interfaces__action__ManageMappingSession_FeedbackMessage__are_equal(const agt_interfaces__action__ManageMappingSession_FeedbackMessage * lhs, const agt_interfaces__action__ManageMappingSession_FeedbackMessage * rhs)
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
  if (!agt_interfaces__action__ManageMappingSession_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_FeedbackMessage__copy(
  const agt_interfaces__action__ManageMappingSession_FeedbackMessage * input,
  agt_interfaces__action__ManageMappingSession_FeedbackMessage * output)
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
  if (!agt_interfaces__action__ManageMappingSession_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__ManageMappingSession_FeedbackMessage *
agt_interfaces__action__ManageMappingSession_FeedbackMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_FeedbackMessage * msg = (agt_interfaces__action__ManageMappingSession_FeedbackMessage *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__ManageMappingSession_FeedbackMessage));
  bool success = agt_interfaces__action__ManageMappingSession_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__ManageMappingSession_FeedbackMessage__destroy(agt_interfaces__action__ManageMappingSession_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__ManageMappingSession_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__init(agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_FeedbackMessage * data = NULL;

  if (size) {
    data = (agt_interfaces__action__ManageMappingSession_FeedbackMessage *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__ManageMappingSession_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__ManageMappingSession_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__ManageMappingSession_FeedbackMessage__fini(&data[i - 1]);
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
agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__fini(agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence * array)
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
      agt_interfaces__action__ManageMappingSession_FeedbackMessage__fini(&array->data[i]);
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

agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence *
agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence * array = (agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__destroy(agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__are_equal(const agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence * lhs, const agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__copy(
  const agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence * input,
  agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__ManageMappingSession_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__ManageMappingSession_FeedbackMessage * data =
      (agt_interfaces__action__ManageMappingSession_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__ManageMappingSession_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__ManageMappingSession_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__ManageMappingSession_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
