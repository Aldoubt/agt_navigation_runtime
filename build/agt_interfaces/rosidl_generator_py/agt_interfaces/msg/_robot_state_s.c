// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from agt_interfaces:msg/RobotState.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "agt_interfaces/msg/detail/robot_state__struct.h"
#include "agt_interfaces/msg/detail/robot_state__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
bool agt_interfaces__msg__system_health__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * agt_interfaces__msg__system_health__convert_to_py(void * raw_ros_message);
bool agt_interfaces__msg__task_readiness__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * agt_interfaces__msg__task_readiness__convert_to_py(void * raw_ros_message);
bool agt_interfaces__msg__map_version_summary__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * agt_interfaces__msg__map_version_summary__convert_to_py(void * raw_ros_message);
bool agt_interfaces__msg__localization_status__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * agt_interfaces__msg__localization_status__convert_to_py(void * raw_ros_message);
bool agt_interfaces__msg__mission_status__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * agt_interfaces__msg__mission_status__convert_to_py(void * raw_ros_message);
bool agt_interfaces__msg__bag_session_summary__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * agt_interfaces__msg__bag_session_summary__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool agt_interfaces__msg__robot_state__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[43];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("agt_interfaces.msg._robot_state.RobotState", full_classname_dest, 42) == 0);
  }
  agt_interfaces__msg__RobotState * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // revision
    PyObject * field = PyObject_GetAttrString(_pymsg, "revision");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->revision = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // system_mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "system_mode");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->system_mode = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // active_profile
    PyObject * field = PyObject_GetAttrString(_pymsg, "active_profile");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->active_profile, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // managed_process_count
    PyObject * field = PyObject_GetAttrString(_pymsg, "managed_process_count");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->managed_process_count = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // running_process_count
    PyObject * field = PyObject_GetAttrString(_pymsg, "running_process_count");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->running_process_count = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // system_health_known
    PyObject * field = PyObject_GetAttrString(_pymsg, "system_health_known");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->system_health_known = (Py_True == field);
    Py_DECREF(field);
  }
  {  // system_health_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "system_health_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->system_health_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // system_health
    PyObject * field = PyObject_GetAttrString(_pymsg, "system_health");
    if (!field) {
      return false;
    }
    if (!agt_interfaces__msg__system_health__convert_from_py(field, &ros_message->system_health)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // task_readiness_known
    PyObject * field = PyObject_GetAttrString(_pymsg, "task_readiness_known");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->task_readiness_known = (Py_True == field);
    Py_DECREF(field);
  }
  {  // task_readiness_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "task_readiness_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->task_readiness_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // task_readiness
    PyObject * field = PyObject_GetAttrString(_pymsg, "task_readiness");
    if (!field) {
      return false;
    }
    if (!agt_interfaces__msg__task_readiness__convert_from_py(field, &ros_message->task_readiness)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // active_map_known
    PyObject * field = PyObject_GetAttrString(_pymsg, "active_map_known");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->active_map_known = (Py_True == field);
    Py_DECREF(field);
  }
  {  // active_map_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "active_map_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->active_map_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // active_map
    PyObject * field = PyObject_GetAttrString(_pymsg, "active_map");
    if (!field) {
      return false;
    }
    if (!agt_interfaces__msg__map_version_summary__convert_from_py(field, &ros_message->active_map)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // localization_status_known
    PyObject * field = PyObject_GetAttrString(_pymsg, "localization_status_known");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->localization_status_known = (Py_True == field);
    Py_DECREF(field);
  }
  {  // localization_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "localization_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->localization_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // localization
    PyObject * field = PyObject_GetAttrString(_pymsg, "localization");
    if (!field) {
      return false;
    }
    if (!agt_interfaces__msg__localization_status__convert_from_py(field, &ros_message->localization)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // mission_status_known
    PyObject * field = PyObject_GetAttrString(_pymsg, "mission_status_known");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->mission_status_known = (Py_True == field);
    Py_DECREF(field);
  }
  {  // mission_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "mission_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mission_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mission
    PyObject * field = PyObject_GetAttrString(_pymsg, "mission");
    if (!field) {
      return false;
    }
    if (!agt_interfaces__msg__mission_status__convert_from_py(field, &ros_message->mission)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // nav2_state
    PyObject * field = PyObject_GetAttrString(_pymsg, "nav2_state");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->nav2_state = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // nav2_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "nav2_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->nav2_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // safety_status_known
    PyObject * field = PyObject_GetAttrString(_pymsg, "safety_status_known");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->safety_status_known = (Py_True == field);
    Py_DECREF(field);
  }
  {  // safety_motion_enabled
    PyObject * field = PyObject_GetAttrString(_pymsg, "safety_motion_enabled");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->safety_motion_enabled = (Py_True == field);
    Py_DECREF(field);
  }
  {  // emergency_stop
    PyObject * field = PyObject_GetAttrString(_pymsg, "emergency_stop");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->emergency_stop = (Py_True == field);
    Py_DECREF(field);
  }
  {  // estop_latched
    PyObject * field = PyObject_GetAttrString(_pymsg, "estop_latched");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->estop_latched = (Py_True == field);
    Py_DECREF(field);
  }
  {  // navigation_ready
    PyObject * field = PyObject_GetAttrString(_pymsg, "navigation_ready");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->navigation_ready = (Py_True == field);
    Py_DECREF(field);
  }
  {  // safety_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "safety_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->safety_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // chassis_status_known
    PyObject * field = PyObject_GetAttrString(_pymsg, "chassis_status_known");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->chassis_status_known = (Py_True == field);
    Py_DECREF(field);
  }
  {  // chassis_connected
    PyObject * field = PyObject_GetAttrString(_pymsg, "chassis_connected");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->chassis_connected = (Py_True == field);
    Py_DECREF(field);
  }
  {  // chassis_control_mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "chassis_control_mode");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->chassis_control_mode = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // chassis_status_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "chassis_status_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->chassis_status_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // chassis_odometry_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "chassis_odometry_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->chassis_odometry_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bag_status_known
    PyObject * field = PyObject_GetAttrString(_pymsg, "bag_status_known");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->bag_status_known = (Py_True == field);
    Py_DECREF(field);
  }
  {  // bag_freshness_s
    PyObject * field = PyObject_GetAttrString(_pymsg, "bag_freshness_s");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->bag_freshness_s = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bag_session
    PyObject * field = PyObject_GetAttrString(_pymsg, "bag_session");
    if (!field) {
      return false;
    }
    if (!agt_interfaces__msg__bag_session_summary__convert_from_py(field, &ros_message->bag_session)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // error_code
    PyObject * field = PyObject_GetAttrString(_pymsg, "error_code");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->error_code = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // blocker_codes
    PyObject * field = PyObject_GetAttrString(_pymsg, "blocker_codes");
    if (!field) {
      return false;
    }
    {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'blocker_codes'");
      if (!seq_field) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = PySequence_Size(field);
      if (-1 == size) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      if (!rosidl_runtime_c__String__Sequence__init(&(ros_message->blocker_codes), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create String__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      rosidl_runtime_c__String * dest = ros_message->blocker_codes.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyUnicode_Check(item));
        PyObject * encoded_item = PyUnicode_AsUTF8String(item);
        if (!encoded_item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        rosidl_runtime_c__String__assign(&dest[i], PyBytes_AS_STRING(encoded_item));
        Py_DECREF(encoded_item);
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }
  {  // blocker_messages
    PyObject * field = PyObject_GetAttrString(_pymsg, "blocker_messages");
    if (!field) {
      return false;
    }
    {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'blocker_messages'");
      if (!seq_field) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = PySequence_Size(field);
      if (-1 == size) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      if (!rosidl_runtime_c__String__Sequence__init(&(ros_message->blocker_messages), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create String__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      rosidl_runtime_c__String * dest = ros_message->blocker_messages.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyUnicode_Check(item));
        PyObject * encoded_item = PyUnicode_AsUTF8String(item);
        if (!encoded_item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        rosidl_runtime_c__String__assign(&dest[i], PyBytes_AS_STRING(encoded_item));
        Py_DECREF(encoded_item);
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }
  {  // message
    PyObject * field = PyObject_GetAttrString(_pymsg, "message");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->message, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * agt_interfaces__msg__robot_state__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of RobotState */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agt_interfaces.msg._robot_state");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "RobotState");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agt_interfaces__msg__RobotState * ros_message = (agt_interfaces__msg__RobotState *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // revision
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->revision);
    {
      int rc = PyObject_SetAttrString(_pymessage, "revision", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // system_mode
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->system_mode);
    {
      int rc = PyObject_SetAttrString(_pymessage, "system_mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // active_profile
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->active_profile.data,
      strlen(ros_message->active_profile.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "active_profile", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // managed_process_count
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->managed_process_count);
    {
      int rc = PyObject_SetAttrString(_pymessage, "managed_process_count", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // running_process_count
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->running_process_count);
    {
      int rc = PyObject_SetAttrString(_pymessage, "running_process_count", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // system_health_known
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->system_health_known ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "system_health_known", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // system_health_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->system_health_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "system_health_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // system_health
    PyObject * field = NULL;
    field = agt_interfaces__msg__system_health__convert_to_py(&ros_message->system_health);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "system_health", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // task_readiness_known
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->task_readiness_known ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "task_readiness_known", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // task_readiness_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->task_readiness_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "task_readiness_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // task_readiness
    PyObject * field = NULL;
    field = agt_interfaces__msg__task_readiness__convert_to_py(&ros_message->task_readiness);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "task_readiness", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // active_map_known
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->active_map_known ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "active_map_known", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // active_map_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->active_map_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "active_map_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // active_map
    PyObject * field = NULL;
    field = agt_interfaces__msg__map_version_summary__convert_to_py(&ros_message->active_map);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "active_map", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // localization_status_known
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->localization_status_known ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "localization_status_known", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // localization_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->localization_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "localization_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // localization
    PyObject * field = NULL;
    field = agt_interfaces__msg__localization_status__convert_to_py(&ros_message->localization);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "localization", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mission_status_known
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->mission_status_known ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mission_status_known", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mission_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mission_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mission_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mission
    PyObject * field = NULL;
    field = agt_interfaces__msg__mission_status__convert_to_py(&ros_message->mission);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "mission", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // nav2_state
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->nav2_state);
    {
      int rc = PyObject_SetAttrString(_pymessage, "nav2_state", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // nav2_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->nav2_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "nav2_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // safety_status_known
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->safety_status_known ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "safety_status_known", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // safety_motion_enabled
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->safety_motion_enabled ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "safety_motion_enabled", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // emergency_stop
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->emergency_stop ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "emergency_stop", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // estop_latched
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->estop_latched ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "estop_latched", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // navigation_ready
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->navigation_ready ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "navigation_ready", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // safety_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->safety_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "safety_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // chassis_status_known
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->chassis_status_known ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "chassis_status_known", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // chassis_connected
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->chassis_connected ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "chassis_connected", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // chassis_control_mode
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->chassis_control_mode);
    {
      int rc = PyObject_SetAttrString(_pymessage, "chassis_control_mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // chassis_status_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->chassis_status_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "chassis_status_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // chassis_odometry_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->chassis_odometry_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "chassis_odometry_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bag_status_known
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->bag_status_known ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bag_status_known", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bag_freshness_s
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->bag_freshness_s);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bag_freshness_s", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bag_session
    PyObject * field = NULL;
    field = agt_interfaces__msg__bag_session_summary__convert_to_py(&ros_message->bag_session);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "bag_session", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // error_code
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->error_code);
    {
      int rc = PyObject_SetAttrString(_pymessage, "error_code", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // blocker_codes
    PyObject * field = NULL;
    size_t size = ros_message->blocker_codes.size;
    rosidl_runtime_c__String * src = ros_message->blocker_codes.data;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    for (size_t i = 0; i < size; ++i) {
      PyObject * decoded_item = PyUnicode_DecodeUTF8(src[i].data, strlen(src[i].data), "replace");
      if (!decoded_item) {
        return NULL;
      }
      int rc = PyList_SetItem(field, i, decoded_item);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "blocker_codes", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // blocker_messages
    PyObject * field = NULL;
    size_t size = ros_message->blocker_messages.size;
    rosidl_runtime_c__String * src = ros_message->blocker_messages.data;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    for (size_t i = 0; i < size; ++i) {
      PyObject * decoded_item = PyUnicode_DecodeUTF8(src[i].data, strlen(src[i].data), "replace");
      if (!decoded_item) {
        return NULL;
      }
      int rc = PyList_SetItem(field, i, decoded_item);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "blocker_messages", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // message
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->message.data,
      strlen(ros_message->message.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "message", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
