// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/SetMissionRunState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__SET_MISSION_RUN_STATE__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__SET_MISSION_RUN_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'COMMAND_PAUSE'.
enum
{
  agt_interfaces__srv__SetMissionRunState_Request__COMMAND_PAUSE = 1
};

/// Constant 'COMMAND_RESUME'.
enum
{
  agt_interfaces__srv__SetMissionRunState_Request__COMMAND_RESUME = 2
};

// Include directives for member types
// Member 'mission_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetMissionRunState in the package agt_interfaces.
typedef struct agt_interfaces__srv__SetMissionRunState_Request
{
  uint8_t command;
  rosidl_runtime_c__String mission_id;
} agt_interfaces__srv__SetMissionRunState_Request;

// Struct for a sequence of agt_interfaces__srv__SetMissionRunState_Request.
typedef struct agt_interfaces__srv__SetMissionRunState_Request__Sequence
{
  agt_interfaces__srv__SetMissionRunState_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__SetMissionRunState_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'status'
#include "agt_interfaces/msg/detail/mission_status__struct.h"
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetMissionRunState in the package agt_interfaces.
typedef struct agt_interfaces__srv__SetMissionRunState_Response
{
  bool success;
  uint16_t error_code;
  agt_interfaces__msg__MissionStatus status;
  rosidl_runtime_c__String message;
} agt_interfaces__srv__SetMissionRunState_Response;

// Struct for a sequence of agt_interfaces__srv__SetMissionRunState_Response.
typedef struct agt_interfaces__srv__SetMissionRunState_Response__Sequence
{
  agt_interfaces__srv__SetMissionRunState_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__SetMissionRunState_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__SET_MISSION_RUN_STATE__STRUCT_H_
