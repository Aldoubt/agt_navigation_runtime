// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from agt_interfaces:msg/BagSessionSummary.idl
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
#include "agt_interfaces/msg/detail/bag_session_summary__struct.h"
#include "agt_interfaces/msg/detail/bag_session_summary__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool agt_interfaces__msg__bag_session_summary__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[58];
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
    assert(strncmp("agt_interfaces.msg._bag_session_summary.BagSessionSummary", full_classname_dest, 57) == 0);
  }
  agt_interfaces__msg__BagSessionSummary * ros_message = _ros_message;
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
  {  // bag_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "bag_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->bag_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // experiment_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "experiment_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->experiment_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // profile_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "profile_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->profile_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // relative_uri
    PyObject * field = PyObject_GetAttrString(_pymsg, "relative_uri");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->relative_uri, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // complete
    PyObject * field = PyObject_GetAttrString(_pymsg, "complete");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->complete = (Py_True == field);
    Py_DECREF(field);
  }
  {  // simulation
    PyObject * field = PyObject_GetAttrString(_pymsg, "simulation");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->simulation = (Py_True == field);
    Py_DECREF(field);
  }
  {  // playback_rate
    PyObject * field = PyObject_GetAttrString(_pymsg, "playback_rate");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->playback_rate = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // storage_bytes
    PyObject * field = PyObject_GetAttrString(_pymsg, "storage_bytes");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->storage_bytes = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // started_at
    PyObject * field = PyObject_GetAttrString(_pymsg, "started_at");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->started_at, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // updated_at
    PyObject * field = PyObject_GetAttrString(_pymsg, "updated_at");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->updated_at, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
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
  {  // process_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "process_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->process_id = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // message_count
    PyObject * field = PyObject_GetAttrString(_pymsg, "message_count");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->message_count = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // storage_identifier
    PyObject * field = PyObject_GetAttrString(_pymsg, "storage_identifier");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->storage_identifier, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // mapping_input_ready
    PyObject * field = PyObject_GetAttrString(_pymsg, "mapping_input_ready");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->mapping_input_ready = (Py_True == field);
    Py_DECREF(field);
  }
  {  // contains_mapping_outputs
    PyObject * field = PyObject_GetAttrString(_pymsg, "contains_mapping_outputs");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->contains_mapping_outputs = (Py_True == field);
    Py_DECREF(field);
  }
  {  // contains_navigation_outputs
    PyObject * field = PyObject_GetAttrString(_pymsg, "contains_navigation_outputs");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->contains_navigation_outputs = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * agt_interfaces__msg__bag_session_summary__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of BagSessionSummary */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agt_interfaces.msg._bag_session_summary");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "BagSessionSummary");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agt_interfaces__msg__BagSessionSummary * ros_message = (agt_interfaces__msg__BagSessionSummary *)raw_ros_message;
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
  {  // bag_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->bag_id.data,
      strlen(ros_message->bag_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "bag_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // experiment_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->experiment_id.data,
      strlen(ros_message->experiment_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "experiment_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // profile_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->profile_id.data,
      strlen(ros_message->profile_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "profile_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // relative_uri
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->relative_uri.data,
      strlen(ros_message->relative_uri.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "relative_uri", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // complete
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->complete ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "complete", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // simulation
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->simulation ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "simulation", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // playback_rate
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->playback_rate);
    {
      int rc = PyObject_SetAttrString(_pymessage, "playback_rate", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // storage_bytes
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->storage_bytes);
    {
      int rc = PyObject_SetAttrString(_pymessage, "storage_bytes", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // started_at
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->started_at.data,
      strlen(ros_message->started_at.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "started_at", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // updated_at
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->updated_at.data,
      strlen(ros_message->updated_at.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "updated_at", field);
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
  {  // process_id
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->process_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "process_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // message_count
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->message_count);
    {
      int rc = PyObject_SetAttrString(_pymessage, "message_count", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // storage_identifier
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->storage_identifier.data,
      strlen(ros_message->storage_identifier.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "storage_identifier", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mapping_input_ready
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->mapping_input_ready ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mapping_input_ready", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // contains_mapping_outputs
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->contains_mapping_outputs ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "contains_mapping_outputs", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // contains_navigation_outputs
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->contains_navigation_outputs ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "contains_navigation_outputs", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
