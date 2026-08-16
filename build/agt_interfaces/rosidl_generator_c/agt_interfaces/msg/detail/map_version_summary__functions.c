// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/MapVersionSummary.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/map_version_summary__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `map_id`
// Member `map_version_id`
// Member `parent_map_version_id`
// Member `map_hash`
// Member `manifest_sha256`
// Member `navigation_yaml_sha256`
// Member `navigation_image_sha256`
// Member `localization_pcd_sha256`
// Member `navigation_yaml`
// Member `localization_pcd`
// Member `processing_record`
// Member `tasks_directory`
// Member `created_at`
// Member `validation_errors`
// Member `validation_warnings`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__msg__MapVersionSummary__init(agt_interfaces__msg__MapVersionSummary * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // parent_map_version_id
  if (!rosidl_runtime_c__String__init(&msg->parent_map_version_id)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // state
  // active
  // pinned
  // deleted
  // valid
  // map_hash
  if (!rosidl_runtime_c__String__init(&msg->map_hash)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // manifest_sha256
  if (!rosidl_runtime_c__String__init(&msg->manifest_sha256)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // navigation_yaml_sha256
  if (!rosidl_runtime_c__String__init(&msg->navigation_yaml_sha256)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // navigation_image_sha256
  if (!rosidl_runtime_c__String__init(&msg->navigation_image_sha256)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // localization_pcd_sha256
  if (!rosidl_runtime_c__String__init(&msg->localization_pcd_sha256)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // navigation_yaml
  if (!rosidl_runtime_c__String__init(&msg->navigation_yaml)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // localization_pcd
  if (!rosidl_runtime_c__String__init(&msg->localization_pcd)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // processing_record
  if (!rosidl_runtime_c__String__init(&msg->processing_record)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // tasks_directory
  if (!rosidl_runtime_c__String__init(&msg->tasks_directory)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // storage_bytes
  // created_at
  if (!rosidl_runtime_c__String__init(&msg->created_at)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // validation_errors
  if (!rosidl_runtime_c__String__Sequence__init(&msg->validation_errors, 0)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  // validation_warnings
  if (!rosidl_runtime_c__String__Sequence__init(&msg->validation_warnings, 0)) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__MapVersionSummary__fini(agt_interfaces__msg__MapVersionSummary * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // parent_map_version_id
  rosidl_runtime_c__String__fini(&msg->parent_map_version_id);
  // state
  // active
  // pinned
  // deleted
  // valid
  // map_hash
  rosidl_runtime_c__String__fini(&msg->map_hash);
  // manifest_sha256
  rosidl_runtime_c__String__fini(&msg->manifest_sha256);
  // navigation_yaml_sha256
  rosidl_runtime_c__String__fini(&msg->navigation_yaml_sha256);
  // navigation_image_sha256
  rosidl_runtime_c__String__fini(&msg->navigation_image_sha256);
  // localization_pcd_sha256
  rosidl_runtime_c__String__fini(&msg->localization_pcd_sha256);
  // navigation_yaml
  rosidl_runtime_c__String__fini(&msg->navigation_yaml);
  // localization_pcd
  rosidl_runtime_c__String__fini(&msg->localization_pcd);
  // processing_record
  rosidl_runtime_c__String__fini(&msg->processing_record);
  // tasks_directory
  rosidl_runtime_c__String__fini(&msg->tasks_directory);
  // storage_bytes
  // created_at
  rosidl_runtime_c__String__fini(&msg->created_at);
  // validation_errors
  rosidl_runtime_c__String__Sequence__fini(&msg->validation_errors);
  // validation_warnings
  rosidl_runtime_c__String__Sequence__fini(&msg->validation_warnings);
}

bool
agt_interfaces__msg__MapVersionSummary__are_equal(const agt_interfaces__msg__MapVersionSummary * lhs, const agt_interfaces__msg__MapVersionSummary * rhs)
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
  // parent_map_version_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->parent_map_version_id), &(rhs->parent_map_version_id)))
  {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // active
  if (lhs->active != rhs->active) {
    return false;
  }
  // pinned
  if (lhs->pinned != rhs->pinned) {
    return false;
  }
  // deleted
  if (lhs->deleted != rhs->deleted) {
    return false;
  }
  // valid
  if (lhs->valid != rhs->valid) {
    return false;
  }
  // map_hash
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_hash), &(rhs->map_hash)))
  {
    return false;
  }
  // manifest_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->manifest_sha256), &(rhs->manifest_sha256)))
  {
    return false;
  }
  // navigation_yaml_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->navigation_yaml_sha256), &(rhs->navigation_yaml_sha256)))
  {
    return false;
  }
  // navigation_image_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->navigation_image_sha256), &(rhs->navigation_image_sha256)))
  {
    return false;
  }
  // localization_pcd_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->localization_pcd_sha256), &(rhs->localization_pcd_sha256)))
  {
    return false;
  }
  // navigation_yaml
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->navigation_yaml), &(rhs->navigation_yaml)))
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
  // tasks_directory
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->tasks_directory), &(rhs->tasks_directory)))
  {
    return false;
  }
  // storage_bytes
  if (lhs->storage_bytes != rhs->storage_bytes) {
    return false;
  }
  // created_at
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->created_at), &(rhs->created_at)))
  {
    return false;
  }
  // validation_errors
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->validation_errors), &(rhs->validation_errors)))
  {
    return false;
  }
  // validation_warnings
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->validation_warnings), &(rhs->validation_warnings)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__msg__MapVersionSummary__copy(
  const agt_interfaces__msg__MapVersionSummary * input,
  agt_interfaces__msg__MapVersionSummary * output)
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
  // parent_map_version_id
  if (!rosidl_runtime_c__String__copy(
      &(input->parent_map_version_id), &(output->parent_map_version_id)))
  {
    return false;
  }
  // state
  output->state = input->state;
  // active
  output->active = input->active;
  // pinned
  output->pinned = input->pinned;
  // deleted
  output->deleted = input->deleted;
  // valid
  output->valid = input->valid;
  // map_hash
  if (!rosidl_runtime_c__String__copy(
      &(input->map_hash), &(output->map_hash)))
  {
    return false;
  }
  // manifest_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->manifest_sha256), &(output->manifest_sha256)))
  {
    return false;
  }
  // navigation_yaml_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->navigation_yaml_sha256), &(output->navigation_yaml_sha256)))
  {
    return false;
  }
  // navigation_image_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->navigation_image_sha256), &(output->navigation_image_sha256)))
  {
    return false;
  }
  // localization_pcd_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->localization_pcd_sha256), &(output->localization_pcd_sha256)))
  {
    return false;
  }
  // navigation_yaml
  if (!rosidl_runtime_c__String__copy(
      &(input->navigation_yaml), &(output->navigation_yaml)))
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
  // tasks_directory
  if (!rosidl_runtime_c__String__copy(
      &(input->tasks_directory), &(output->tasks_directory)))
  {
    return false;
  }
  // storage_bytes
  output->storage_bytes = input->storage_bytes;
  // created_at
  if (!rosidl_runtime_c__String__copy(
      &(input->created_at), &(output->created_at)))
  {
    return false;
  }
  // validation_errors
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->validation_errors), &(output->validation_errors)))
  {
    return false;
  }
  // validation_warnings
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->validation_warnings), &(output->validation_warnings)))
  {
    return false;
  }
  return true;
}

agt_interfaces__msg__MapVersionSummary *
agt_interfaces__msg__MapVersionSummary__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__MapVersionSummary * msg = (agt_interfaces__msg__MapVersionSummary *)allocator.allocate(sizeof(agt_interfaces__msg__MapVersionSummary), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__MapVersionSummary));
  bool success = agt_interfaces__msg__MapVersionSummary__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__MapVersionSummary__destroy(agt_interfaces__msg__MapVersionSummary * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__MapVersionSummary__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__MapVersionSummary__Sequence__init(agt_interfaces__msg__MapVersionSummary__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__MapVersionSummary * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__MapVersionSummary *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__MapVersionSummary), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__MapVersionSummary__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__MapVersionSummary__fini(&data[i - 1]);
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
agt_interfaces__msg__MapVersionSummary__Sequence__fini(agt_interfaces__msg__MapVersionSummary__Sequence * array)
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
      agt_interfaces__msg__MapVersionSummary__fini(&array->data[i]);
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

agt_interfaces__msg__MapVersionSummary__Sequence *
agt_interfaces__msg__MapVersionSummary__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__MapVersionSummary__Sequence * array = (agt_interfaces__msg__MapVersionSummary__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__MapVersionSummary__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__MapVersionSummary__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__MapVersionSummary__Sequence__destroy(agt_interfaces__msg__MapVersionSummary__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__MapVersionSummary__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__MapVersionSummary__Sequence__are_equal(const agt_interfaces__msg__MapVersionSummary__Sequence * lhs, const agt_interfaces__msg__MapVersionSummary__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__MapVersionSummary__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__MapVersionSummary__Sequence__copy(
  const agt_interfaces__msg__MapVersionSummary__Sequence * input,
  agt_interfaces__msg__MapVersionSummary__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__MapVersionSummary);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__MapVersionSummary * data =
      (agt_interfaces__msg__MapVersionSummary *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__MapVersionSummary__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__MapVersionSummary__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__MapVersionSummary__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
