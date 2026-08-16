// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/ListExperiments.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_EXPERIMENTS__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__LIST_EXPERIMENTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/ListExperiments in the package agt_interfaces.
typedef struct agt_interfaces__srv__ListExperiments_Request
{
  uint8_t state;
} agt_interfaces__srv__ListExperiments_Request;

// Struct for a sequence of agt_interfaces__srv__ListExperiments_Request.
typedef struct agt_interfaces__srv__ListExperiments_Request__Sequence
{
  agt_interfaces__srv__ListExperiments_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ListExperiments_Request__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__srv__ListExperiments_Response__ERROR_NONE = 0
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__srv__ListExperiments_Response__ERROR_INVALID_REQUEST = 1
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__srv__ListExperiments_Response__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'experiments'
#include "agt_interfaces/msg/detail/experiment_summary__struct.h"
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ListExperiments in the package agt_interfaces.
typedef struct agt_interfaces__srv__ListExperiments_Response
{
  bool success;
  uint16_t error_code;
  agt_interfaces__msg__ExperimentSummary__Sequence experiments;
  rosidl_runtime_c__String message;
} agt_interfaces__srv__ListExperiments_Response;

// Struct for a sequence of agt_interfaces__srv__ListExperiments_Response.
typedef struct agt_interfaces__srv__ListExperiments_Response__Sequence
{
  agt_interfaces__srv__ListExperiments_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ListExperiments_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_EXPERIMENTS__STRUCT_H_
