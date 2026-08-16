// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/EvaluateTaskReadiness.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'PROFILE_TASK_EXECUTION'.
enum
{
  agt_interfaces__srv__EvaluateTaskReadiness_Request__PROFILE_TASK_EXECUTION = 0
};

/// Constant 'PROFILE_RELOCALIZATION'.
enum
{
  agt_interfaces__srv__EvaluateTaskReadiness_Request__PROFILE_RELOCALIZATION = 1
};

// Include directives for member types
// Member 'task_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/EvaluateTaskReadiness in the package agt_interfaces.
typedef struct agt_interfaces__srv__EvaluateTaskReadiness_Request
{
  bool validate_task;
  rosidl_runtime_c__String task_id;
  uint8_t gate_profile;
} agt_interfaces__srv__EvaluateTaskReadiness_Request;

// Struct for a sequence of agt_interfaces__srv__EvaluateTaskReadiness_Request.
typedef struct agt_interfaces__srv__EvaluateTaskReadiness_Request__Sequence
{
  agt_interfaces__srv__EvaluateTaskReadiness_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__EvaluateTaskReadiness_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'readiness'
#include "agt_interfaces/msg/detail/task_readiness__struct.h"

/// Struct defined in srv/EvaluateTaskReadiness in the package agt_interfaces.
typedef struct agt_interfaces__srv__EvaluateTaskReadiness_Response
{
  agt_interfaces__msg__TaskReadiness readiness;
} agt_interfaces__srv__EvaluateTaskReadiness_Response;

// Struct for a sequence of agt_interfaces__srv__EvaluateTaskReadiness_Response.
typedef struct agt_interfaces__srv__EvaluateTaskReadiness_Response__Sequence
{
  agt_interfaces__srv__EvaluateTaskReadiness_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__EvaluateTaskReadiness_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__STRUCT_H_
