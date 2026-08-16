// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/SetLocalizationMode.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__SET_LOCALIZATION_MODE__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__SET_LOCALIZATION_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MODE_MANUAL_ONLY'.
enum
{
  agt_interfaces__srv__SetLocalizationMode_Request__MODE_MANUAL_ONLY = 0
};

/// Constant 'MODE_AUTO_ON_START'.
enum
{
  agt_interfaces__srv__SetLocalizationMode_Request__MODE_AUTO_ON_START = 1
};

/// Constant 'MODE_AUTO_RECOVERY'.
enum
{
  agt_interfaces__srv__SetLocalizationMode_Request__MODE_AUTO_RECOVERY = 2
};

/// Struct defined in srv/SetLocalizationMode in the package agt_interfaces.
typedef struct agt_interfaces__srv__SetLocalizationMode_Request
{
  uint8_t mode;
} agt_interfaces__srv__SetLocalizationMode_Request;

// Struct for a sequence of agt_interfaces__srv__SetLocalizationMode_Request.
typedef struct agt_interfaces__srv__SetLocalizationMode_Request__Sequence
{
  agt_interfaces__srv__SetLocalizationMode_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__SetLocalizationMode_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetLocalizationMode in the package agt_interfaces.
typedef struct agt_interfaces__srv__SetLocalizationMode_Response
{
  bool success;
  uint16_t error_code;
  uint8_t active_mode;
  uint32_t attempts;
  rosidl_runtime_c__String message;
} agt_interfaces__srv__SetLocalizationMode_Response;

// Struct for a sequence of agt_interfaces__srv__SetLocalizationMode_Response.
typedef struct agt_interfaces__srv__SetLocalizationMode_Response__Sequence
{
  agt_interfaces__srv__SetLocalizationMode_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__SetLocalizationMode_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__SET_LOCALIZATION_MODE__STRUCT_H_
