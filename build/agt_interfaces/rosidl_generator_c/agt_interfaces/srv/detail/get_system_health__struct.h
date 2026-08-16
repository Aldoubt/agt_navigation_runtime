// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/GetSystemHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_SYSTEM_HEALTH__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__GET_SYSTEM_HEALTH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetSystemHealth in the package agt_interfaces.
typedef struct agt_interfaces__srv__GetSystemHealth_Request
{
  bool include_optional;
} agt_interfaces__srv__GetSystemHealth_Request;

// Struct for a sequence of agt_interfaces__srv__GetSystemHealth_Request.
typedef struct agt_interfaces__srv__GetSystemHealth_Request__Sequence
{
  agt_interfaces__srv__GetSystemHealth_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__GetSystemHealth_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'health'
#include "agt_interfaces/msg/detail/system_health__struct.h"

/// Struct defined in srv/GetSystemHealth in the package agt_interfaces.
typedef struct agt_interfaces__srv__GetSystemHealth_Response
{
  agt_interfaces__msg__SystemHealth health;
} agt_interfaces__srv__GetSystemHealth_Response;

// Struct for a sequence of agt_interfaces__srv__GetSystemHealth_Response.
typedef struct agt_interfaces__srv__GetSystemHealth_Response__Sequence
{
  agt_interfaces__srv__GetSystemHealth_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__GetSystemHealth_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_SYSTEM_HEALTH__STRUCT_H_
