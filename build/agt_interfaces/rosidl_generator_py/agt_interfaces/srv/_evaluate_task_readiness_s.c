// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from agt_interfaces:srv/EvaluateTaskReadiness.idl
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
#include "agt_interfaces/srv/detail/evaluate_task_readiness__struct.h"
#include "agt_interfaces/srv/detail/evaluate_task_readiness__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool agt_interfaces__srv__evaluate_task_readiness__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[74];
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
    assert(strncmp("agt_interfaces.srv._evaluate_task_readiness.EvaluateTaskReadiness_Request", full_classname_dest, 73) == 0);
  }
  agt_interfaces__srv__EvaluateTaskReadiness_Request * ros_message = _ros_message;
  {  // validate_task
    PyObject * field = PyObject_GetAttrString(_pymsg, "validate_task");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->validate_task = (Py_True == field);
    Py_DECREF(field);
  }
  {  // task_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "task_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->task_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // gate_profile
    PyObject * field = PyObject_GetAttrString(_pymsg, "gate_profile");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->gate_profile = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * agt_interfaces__srv__evaluate_task_readiness__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of EvaluateTaskReadiness_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agt_interfaces.srv._evaluate_task_readiness");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "EvaluateTaskReadiness_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agt_interfaces__srv__EvaluateTaskReadiness_Request * ros_message = (agt_interfaces__srv__EvaluateTaskReadiness_Request *)raw_ros_message;
  {  // validate_task
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->validate_task ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "validate_task", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // task_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->task_id.data,
      strlen(ros_message->task_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "task_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gate_profile
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->gate_profile);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gate_profile", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "agt_interfaces/srv/detail/evaluate_task_readiness__struct.h"
// already included above
// #include "agt_interfaces/srv/detail/evaluate_task_readiness__functions.h"

bool agt_interfaces__msg__task_readiness__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * agt_interfaces__msg__task_readiness__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool agt_interfaces__srv__evaluate_task_readiness__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[75];
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
    assert(strncmp("agt_interfaces.srv._evaluate_task_readiness.EvaluateTaskReadiness_Response", full_classname_dest, 74) == 0);
  }
  agt_interfaces__srv__EvaluateTaskReadiness_Response * ros_message = _ros_message;
  {  // readiness
    PyObject * field = PyObject_GetAttrString(_pymsg, "readiness");
    if (!field) {
      return false;
    }
    if (!agt_interfaces__msg__task_readiness__convert_from_py(field, &ros_message->readiness)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * agt_interfaces__srv__evaluate_task_readiness__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of EvaluateTaskReadiness_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agt_interfaces.srv._evaluate_task_readiness");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "EvaluateTaskReadiness_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agt_interfaces__srv__EvaluateTaskReadiness_Response * ros_message = (agt_interfaces__srv__EvaluateTaskReadiness_Response *)raw_ros_message;
  {  // readiness
    PyObject * field = NULL;
    field = agt_interfaces__msg__task_readiness__convert_to_py(&ros_message->readiness);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "readiness", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
