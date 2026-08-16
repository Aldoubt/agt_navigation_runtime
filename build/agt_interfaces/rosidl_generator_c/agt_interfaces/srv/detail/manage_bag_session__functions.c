// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:srv/ManageBagSession.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/srv/detail/manage_bag_session__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `bag_id`
// Member `experiment_id`
// Member `experiment_title`
// Member `objective`
// Member `hypothesis`
// Member `tags_json`
// Member `operator_note`
// Member `profile_id`
// Member `mission_id`
// Member `mission_version`
// Member `mission_sha256`
// Member `map_id`
// Member `map_version_id`
// Member `map_sha256`
// Member `platform_profile`
// Member `calibration_profile`
// Member `nav2_profile`
// Member `launch_profile`
// Member `event_type`
// Member `metadata_json`
// Member `result_status`
// Member `reason`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__srv__ManageBagSession_Request__init(agt_interfaces__srv__ManageBagSession_Request * msg)
{
  if (!msg) {
    return false;
  }
  // operation
  // bag_id
  if (!rosidl_runtime_c__String__init(&msg->bag_id)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // experiment_id
  if (!rosidl_runtime_c__String__init(&msg->experiment_id)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // experiment_title
  if (!rosidl_runtime_c__String__init(&msg->experiment_title)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // objective
  if (!rosidl_runtime_c__String__init(&msg->objective)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // hypothesis
  if (!rosidl_runtime_c__String__init(&msg->hypothesis)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // tags_json
  if (!rosidl_runtime_c__String__init(&msg->tags_json)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // operator_note
  if (!rosidl_runtime_c__String__init(&msg->operator_note)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // profile_id
  if (!rosidl_runtime_c__String__init(&msg->profile_id)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // playback_rate
  // mission_id
  if (!rosidl_runtime_c__String__init(&msg->mission_id)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // mission_version
  if (!rosidl_runtime_c__String__init(&msg->mission_version)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // mission_sha256
  if (!rosidl_runtime_c__String__init(&msg->mission_sha256)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // map_sha256
  if (!rosidl_runtime_c__String__init(&msg->map_sha256)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // platform_profile
  if (!rosidl_runtime_c__String__init(&msg->platform_profile)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // calibration_profile
  if (!rosidl_runtime_c__String__init(&msg->calibration_profile)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // nav2_profile
  if (!rosidl_runtime_c__String__init(&msg->nav2_profile)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // launch_profile
  if (!rosidl_runtime_c__String__init(&msg->launch_profile)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // start_experiment
  // event_type
  if (!rosidl_runtime_c__String__init(&msg->event_type)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // metadata_json
  if (!rosidl_runtime_c__String__init(&msg->metadata_json)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // result_status
  if (!rosidl_runtime_c__String__init(&msg->result_status)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  // reason
  if (!rosidl_runtime_c__String__init(&msg->reason)) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__srv__ManageBagSession_Request__fini(agt_interfaces__srv__ManageBagSession_Request * msg)
{
  if (!msg) {
    return;
  }
  // operation
  // bag_id
  rosidl_runtime_c__String__fini(&msg->bag_id);
  // experiment_id
  rosidl_runtime_c__String__fini(&msg->experiment_id);
  // experiment_title
  rosidl_runtime_c__String__fini(&msg->experiment_title);
  // objective
  rosidl_runtime_c__String__fini(&msg->objective);
  // hypothesis
  rosidl_runtime_c__String__fini(&msg->hypothesis);
  // tags_json
  rosidl_runtime_c__String__fini(&msg->tags_json);
  // operator_note
  rosidl_runtime_c__String__fini(&msg->operator_note);
  // profile_id
  rosidl_runtime_c__String__fini(&msg->profile_id);
  // playback_rate
  // mission_id
  rosidl_runtime_c__String__fini(&msg->mission_id);
  // mission_version
  rosidl_runtime_c__String__fini(&msg->mission_version);
  // mission_sha256
  rosidl_runtime_c__String__fini(&msg->mission_sha256);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // map_sha256
  rosidl_runtime_c__String__fini(&msg->map_sha256);
  // platform_profile
  rosidl_runtime_c__String__fini(&msg->platform_profile);
  // calibration_profile
  rosidl_runtime_c__String__fini(&msg->calibration_profile);
  // nav2_profile
  rosidl_runtime_c__String__fini(&msg->nav2_profile);
  // launch_profile
  rosidl_runtime_c__String__fini(&msg->launch_profile);
  // start_experiment
  // event_type
  rosidl_runtime_c__String__fini(&msg->event_type);
  // metadata_json
  rosidl_runtime_c__String__fini(&msg->metadata_json);
  // result_status
  rosidl_runtime_c__String__fini(&msg->result_status);
  // reason
  rosidl_runtime_c__String__fini(&msg->reason);
}

bool
agt_interfaces__srv__ManageBagSession_Request__are_equal(const agt_interfaces__srv__ManageBagSession_Request * lhs, const agt_interfaces__srv__ManageBagSession_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // operation
  if (lhs->operation != rhs->operation) {
    return false;
  }
  // bag_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->bag_id), &(rhs->bag_id)))
  {
    return false;
  }
  // experiment_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->experiment_id), &(rhs->experiment_id)))
  {
    return false;
  }
  // experiment_title
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->experiment_title), &(rhs->experiment_title)))
  {
    return false;
  }
  // objective
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->objective), &(rhs->objective)))
  {
    return false;
  }
  // hypothesis
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->hypothesis), &(rhs->hypothesis)))
  {
    return false;
  }
  // tags_json
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->tags_json), &(rhs->tags_json)))
  {
    return false;
  }
  // operator_note
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->operator_note), &(rhs->operator_note)))
  {
    return false;
  }
  // profile_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->profile_id), &(rhs->profile_id)))
  {
    return false;
  }
  // playback_rate
  if (lhs->playback_rate != rhs->playback_rate) {
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
  // map_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_sha256), &(rhs->map_sha256)))
  {
    return false;
  }
  // platform_profile
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->platform_profile), &(rhs->platform_profile)))
  {
    return false;
  }
  // calibration_profile
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->calibration_profile), &(rhs->calibration_profile)))
  {
    return false;
  }
  // nav2_profile
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->nav2_profile), &(rhs->nav2_profile)))
  {
    return false;
  }
  // launch_profile
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->launch_profile), &(rhs->launch_profile)))
  {
    return false;
  }
  // start_experiment
  if (lhs->start_experiment != rhs->start_experiment) {
    return false;
  }
  // event_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->event_type), &(rhs->event_type)))
  {
    return false;
  }
  // metadata_json
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->metadata_json), &(rhs->metadata_json)))
  {
    return false;
  }
  // result_status
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->result_status), &(rhs->result_status)))
  {
    return false;
  }
  // reason
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->reason), &(rhs->reason)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__srv__ManageBagSession_Request__copy(
  const agt_interfaces__srv__ManageBagSession_Request * input,
  agt_interfaces__srv__ManageBagSession_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // operation
  output->operation = input->operation;
  // bag_id
  if (!rosidl_runtime_c__String__copy(
      &(input->bag_id), &(output->bag_id)))
  {
    return false;
  }
  // experiment_id
  if (!rosidl_runtime_c__String__copy(
      &(input->experiment_id), &(output->experiment_id)))
  {
    return false;
  }
  // experiment_title
  if (!rosidl_runtime_c__String__copy(
      &(input->experiment_title), &(output->experiment_title)))
  {
    return false;
  }
  // objective
  if (!rosidl_runtime_c__String__copy(
      &(input->objective), &(output->objective)))
  {
    return false;
  }
  // hypothesis
  if (!rosidl_runtime_c__String__copy(
      &(input->hypothesis), &(output->hypothesis)))
  {
    return false;
  }
  // tags_json
  if (!rosidl_runtime_c__String__copy(
      &(input->tags_json), &(output->tags_json)))
  {
    return false;
  }
  // operator_note
  if (!rosidl_runtime_c__String__copy(
      &(input->operator_note), &(output->operator_note)))
  {
    return false;
  }
  // profile_id
  if (!rosidl_runtime_c__String__copy(
      &(input->profile_id), &(output->profile_id)))
  {
    return false;
  }
  // playback_rate
  output->playback_rate = input->playback_rate;
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
  // map_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->map_sha256), &(output->map_sha256)))
  {
    return false;
  }
  // platform_profile
  if (!rosidl_runtime_c__String__copy(
      &(input->platform_profile), &(output->platform_profile)))
  {
    return false;
  }
  // calibration_profile
  if (!rosidl_runtime_c__String__copy(
      &(input->calibration_profile), &(output->calibration_profile)))
  {
    return false;
  }
  // nav2_profile
  if (!rosidl_runtime_c__String__copy(
      &(input->nav2_profile), &(output->nav2_profile)))
  {
    return false;
  }
  // launch_profile
  if (!rosidl_runtime_c__String__copy(
      &(input->launch_profile), &(output->launch_profile)))
  {
    return false;
  }
  // start_experiment
  output->start_experiment = input->start_experiment;
  // event_type
  if (!rosidl_runtime_c__String__copy(
      &(input->event_type), &(output->event_type)))
  {
    return false;
  }
  // metadata_json
  if (!rosidl_runtime_c__String__copy(
      &(input->metadata_json), &(output->metadata_json)))
  {
    return false;
  }
  // result_status
  if (!rosidl_runtime_c__String__copy(
      &(input->result_status), &(output->result_status)))
  {
    return false;
  }
  // reason
  if (!rosidl_runtime_c__String__copy(
      &(input->reason), &(output->reason)))
  {
    return false;
  }
  return true;
}

agt_interfaces__srv__ManageBagSession_Request *
agt_interfaces__srv__ManageBagSession_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ManageBagSession_Request * msg = (agt_interfaces__srv__ManageBagSession_Request *)allocator.allocate(sizeof(agt_interfaces__srv__ManageBagSession_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__srv__ManageBagSession_Request));
  bool success = agt_interfaces__srv__ManageBagSession_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__srv__ManageBagSession_Request__destroy(agt_interfaces__srv__ManageBagSession_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__srv__ManageBagSession_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__srv__ManageBagSession_Request__Sequence__init(agt_interfaces__srv__ManageBagSession_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ManageBagSession_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__srv__ManageBagSession_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__srv__ManageBagSession_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__srv__ManageBagSession_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__srv__ManageBagSession_Request__fini(&data[i - 1]);
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
agt_interfaces__srv__ManageBagSession_Request__Sequence__fini(agt_interfaces__srv__ManageBagSession_Request__Sequence * array)
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
      agt_interfaces__srv__ManageBagSession_Request__fini(&array->data[i]);
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

agt_interfaces__srv__ManageBagSession_Request__Sequence *
agt_interfaces__srv__ManageBagSession_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ManageBagSession_Request__Sequence * array = (agt_interfaces__srv__ManageBagSession_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__srv__ManageBagSession_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__srv__ManageBagSession_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__srv__ManageBagSession_Request__Sequence__destroy(agt_interfaces__srv__ManageBagSession_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__srv__ManageBagSession_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__srv__ManageBagSession_Request__Sequence__are_equal(const agt_interfaces__srv__ManageBagSession_Request__Sequence * lhs, const agt_interfaces__srv__ManageBagSession_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__srv__ManageBagSession_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__srv__ManageBagSession_Request__Sequence__copy(
  const agt_interfaces__srv__ManageBagSession_Request__Sequence * input,
  agt_interfaces__srv__ManageBagSession_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__srv__ManageBagSession_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__srv__ManageBagSession_Request * data =
      (agt_interfaces__srv__ManageBagSession_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__srv__ManageBagSession_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__srv__ManageBagSession_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__srv__ManageBagSession_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `session`
#include "agt_interfaces/msg/detail/bag_session_summary__functions.h"
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__srv__ManageBagSession_Response__init(agt_interfaces__srv__ManageBagSession_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_code
  // session
  if (!agt_interfaces__msg__BagSessionSummary__init(&msg->session)) {
    agt_interfaces__srv__ManageBagSession_Response__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__srv__ManageBagSession_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__srv__ManageBagSession_Response__fini(agt_interfaces__srv__ManageBagSession_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_code
  // session
  agt_interfaces__msg__BagSessionSummary__fini(&msg->session);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
agt_interfaces__srv__ManageBagSession_Response__are_equal(const agt_interfaces__srv__ManageBagSession_Response * lhs, const agt_interfaces__srv__ManageBagSession_Response * rhs)
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
  // session
  if (!agt_interfaces__msg__BagSessionSummary__are_equal(
      &(lhs->session), &(rhs->session)))
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
agt_interfaces__srv__ManageBagSession_Response__copy(
  const agt_interfaces__srv__ManageBagSession_Response * input,
  agt_interfaces__srv__ManageBagSession_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // error_code
  output->error_code = input->error_code;
  // session
  if (!agt_interfaces__msg__BagSessionSummary__copy(
      &(input->session), &(output->session)))
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

agt_interfaces__srv__ManageBagSession_Response *
agt_interfaces__srv__ManageBagSession_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ManageBagSession_Response * msg = (agt_interfaces__srv__ManageBagSession_Response *)allocator.allocate(sizeof(agt_interfaces__srv__ManageBagSession_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__srv__ManageBagSession_Response));
  bool success = agt_interfaces__srv__ManageBagSession_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__srv__ManageBagSession_Response__destroy(agt_interfaces__srv__ManageBagSession_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__srv__ManageBagSession_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__srv__ManageBagSession_Response__Sequence__init(agt_interfaces__srv__ManageBagSession_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ManageBagSession_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__srv__ManageBagSession_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__srv__ManageBagSession_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__srv__ManageBagSession_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__srv__ManageBagSession_Response__fini(&data[i - 1]);
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
agt_interfaces__srv__ManageBagSession_Response__Sequence__fini(agt_interfaces__srv__ManageBagSession_Response__Sequence * array)
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
      agt_interfaces__srv__ManageBagSession_Response__fini(&array->data[i]);
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

agt_interfaces__srv__ManageBagSession_Response__Sequence *
agt_interfaces__srv__ManageBagSession_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ManageBagSession_Response__Sequence * array = (agt_interfaces__srv__ManageBagSession_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__srv__ManageBagSession_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__srv__ManageBagSession_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__srv__ManageBagSession_Response__Sequence__destroy(agt_interfaces__srv__ManageBagSession_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__srv__ManageBagSession_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__srv__ManageBagSession_Response__Sequence__are_equal(const agt_interfaces__srv__ManageBagSession_Response__Sequence * lhs, const agt_interfaces__srv__ManageBagSession_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__srv__ManageBagSession_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__srv__ManageBagSession_Response__Sequence__copy(
  const agt_interfaces__srv__ManageBagSession_Response__Sequence * input,
  agt_interfaces__srv__ManageBagSession_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__srv__ManageBagSession_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__srv__ManageBagSession_Response * data =
      (agt_interfaces__srv__ManageBagSession_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__srv__ManageBagSession_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__srv__ManageBagSession_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__srv__ManageBagSession_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
