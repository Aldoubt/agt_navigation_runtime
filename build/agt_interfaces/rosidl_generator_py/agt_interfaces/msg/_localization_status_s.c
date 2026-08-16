// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from agt_interfaces:msg/LocalizationStatus.idl
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
#include "agt_interfaces/msg/detail/localization_status__struct.h"
#include "agt_interfaces/msg/detail/localization_status__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__pose_with_covariance_stamped__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__pose_with_covariance_stamped__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool agt_interfaces__msg__localization_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[59];
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
    assert(strncmp("agt_interfaces.msg._localization_status.LocalizationStatus", full_classname_dest, 58) == 0);
  }
  agt_interfaces__msg__LocalizationStatus * ros_message = _ros_message;
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
  {  // state
    PyObject * field = PyObject_GetAttrString(_pymsg, "state");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->state = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // pose_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "pose_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->pose_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // localization_accepted
    PyObject * field = PyObject_GetAttrString(_pymsg, "localization_accepted");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->localization_accepted = (Py_True == field);
    Py_DECREF(field);
  }
  {  // has_converged
    PyObject * field = PyObject_GetAttrString(_pymsg, "has_converged");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->has_converged = (Py_True == field);
    Py_DECREF(field);
  }
  {  // ambiguous_result
    PyObject * field = PyObject_GetAttrString(_pymsg, "ambiguous_result");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->ambiguous_result = (Py_True == field);
    Py_DECREF(field);
  }
  {  // status_stale
    PyObject * field = PyObject_GetAttrString(_pymsg, "status_stale");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->status_stale = (Py_True == field);
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
  {  // backend
    PyObject * field = PyObject_GetAttrString(_pymsg, "backend");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->backend, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // candidate_source
    PyObject * field = PyObject_GetAttrString(_pymsg, "candidate_source");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->candidate_source, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // candidate_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "candidate_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->candidate_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // map_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "map_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->map_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // map_hash
    PyObject * field = PyObject_GetAttrString(_pymsg, "map_hash");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->map_hash, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // correction_generation
    PyObject * field = PyObject_GetAttrString(_pymsg, "correction_generation");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->correction_generation = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // global_pose
    PyObject * field = PyObject_GetAttrString(_pymsg, "global_pose");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__pose_with_covariance_stamped__convert_from_py(field, &ros_message->global_pose)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // fitness_score
    PyObject * field = PyObject_GetAttrString(_pymsg, "fitness_score");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->fitness_score = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // overlap_ratio
    PyObject * field = PyObject_GetAttrString(_pymsg, "overlap_ratio");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->overlap_ratio = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // inlier_ratio
    PyObject * field = PyObject_GetAttrString(_pymsg, "inlier_ratio");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->inlier_ratio = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ambiguity_score
    PyObject * field = PyObject_GetAttrString(_pymsg, "ambiguity_score");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ambiguity_score = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // translation_innovation
    PyObject * field = PyObject_GetAttrString(_pymsg, "translation_innovation");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->translation_innovation = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // yaw_innovation
    PyObject * field = PyObject_GetAttrString(_pymsg, "yaw_innovation");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->yaw_innovation = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // runtime_ms
    PyObject * field = PyObject_GetAttrString(_pymsg, "runtime_ms");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->runtime_ms = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // tested_candidates
    PyObject * field = PyObject_GetAttrString(_pymsg, "tested_candidates");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->tested_candidates = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // total_candidates
    PyObject * field = PyObject_GetAttrString(_pymsg, "total_candidates");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->total_candidates = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // consecutive_successes
    PyObject * field = PyObject_GetAttrString(_pymsg, "consecutive_successes");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->consecutive_successes = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // consecutive_failures
    PyObject * field = PyObject_GetAttrString(_pymsg, "consecutive_failures");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->consecutive_failures = PyLong_AsUnsignedLong(field);
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
PyObject * agt_interfaces__msg__localization_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of LocalizationStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agt_interfaces.msg._localization_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "LocalizationStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agt_interfaces__msg__LocalizationStatus * ros_message = (agt_interfaces__msg__LocalizationStatus *)raw_ros_message;
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
  {  // state
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->state);
    {
      int rc = PyObject_SetAttrString(_pymessage, "state", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pose_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->pose_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pose_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // localization_accepted
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->localization_accepted ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "localization_accepted", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // has_converged
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->has_converged ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "has_converged", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ambiguous_result
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->ambiguous_result ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ambiguous_result", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // status_stale
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->status_stale ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "status_stale", field);
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
  {  // backend
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->backend.data,
      strlen(ros_message->backend.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "backend", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // candidate_source
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->candidate_source.data,
      strlen(ros_message->candidate_source.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "candidate_source", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // candidate_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->candidate_id.data,
      strlen(ros_message->candidate_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "candidate_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // map_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->map_id.data,
      strlen(ros_message->map_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "map_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // map_hash
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->map_hash.data,
      strlen(ros_message->map_hash.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "map_hash", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // correction_generation
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->correction_generation);
    {
      int rc = PyObject_SetAttrString(_pymessage, "correction_generation", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // global_pose
    PyObject * field = NULL;
    field = geometry_msgs__msg__pose_with_covariance_stamped__convert_to_py(&ros_message->global_pose);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "global_pose", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fitness_score
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->fitness_score);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fitness_score", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // overlap_ratio
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->overlap_ratio);
    {
      int rc = PyObject_SetAttrString(_pymessage, "overlap_ratio", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // inlier_ratio
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->inlier_ratio);
    {
      int rc = PyObject_SetAttrString(_pymessage, "inlier_ratio", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ambiguity_score
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ambiguity_score);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ambiguity_score", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // translation_innovation
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->translation_innovation);
    {
      int rc = PyObject_SetAttrString(_pymessage, "translation_innovation", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // yaw_innovation
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->yaw_innovation);
    {
      int rc = PyObject_SetAttrString(_pymessage, "yaw_innovation", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // runtime_ms
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->runtime_ms);
    {
      int rc = PyObject_SetAttrString(_pymessage, "runtime_ms", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // tested_candidates
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->tested_candidates);
    {
      int rc = PyObject_SetAttrString(_pymessage, "tested_candidates", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // total_candidates
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->total_candidates);
    {
      int rc = PyObject_SetAttrString(_pymessage, "total_candidates", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // consecutive_successes
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->consecutive_successes);
    {
      int rc = PyObject_SetAttrString(_pymessage, "consecutive_successes", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // consecutive_failures
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->consecutive_failures);
    {
      int rc = PyObject_SetAttrString(_pymessage, "consecutive_failures", field);
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
