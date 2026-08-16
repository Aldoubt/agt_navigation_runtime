// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/GetRobotState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATE__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetRobotState in the package agt_interfaces.
typedef struct agt_interfaces__srv__GetRobotState_Request
{
  bool include_details;
} agt_interfaces__srv__GetRobotState_Request;

// Struct for a sequence of agt_interfaces__srv__GetRobotState_Request.
typedef struct agt_interfaces__srv__GetRobotState_Request__Sequence
{
  agt_interfaces__srv__GetRobotState_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__GetRobotState_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'state'
#include "agt_interfaces/msg/detail/robot_state__struct.h"
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetRobotState in the package agt_interfaces.
typedef struct agt_interfaces__srv__GetRobotState_Response
{
  bool success;
  uint16_t error_code;
  agt_interfaces__msg__RobotState state;
  rosidl_runtime_c__String message;
} agt_interfaces__srv__GetRobotState_Response;

// Struct for a sequence of agt_interfaces__srv__GetRobotState_Response.
typedef struct agt_interfaces__srv__GetRobotState_Response__Sequence
{
  agt_interfaces__srv__GetRobotState_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__GetRobotState_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATE__STRUCT_H_
