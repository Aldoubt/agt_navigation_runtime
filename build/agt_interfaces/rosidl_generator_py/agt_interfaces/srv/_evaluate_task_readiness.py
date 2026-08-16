# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:srv/EvaluateTaskReadiness.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_EvaluateTaskReadiness_Request(type):
    """Metaclass of message 'EvaluateTaskReadiness_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'PROFILE_TASK_EXECUTION': 0,
        'PROFILE_RELOCALIZATION': 1,
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('agt_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'agt_interfaces.srv.EvaluateTaskReadiness_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__evaluate_task_readiness__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__evaluate_task_readiness__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__evaluate_task_readiness__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__evaluate_task_readiness__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__evaluate_task_readiness__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'PROFILE_TASK_EXECUTION': cls.__constants['PROFILE_TASK_EXECUTION'],
            'PROFILE_RELOCALIZATION': cls.__constants['PROFILE_RELOCALIZATION'],
        }

    @property
    def PROFILE_TASK_EXECUTION(self):
        """Message constant 'PROFILE_TASK_EXECUTION'."""
        return Metaclass_EvaluateTaskReadiness_Request.__constants['PROFILE_TASK_EXECUTION']

    @property
    def PROFILE_RELOCALIZATION(self):
        """Message constant 'PROFILE_RELOCALIZATION'."""
        return Metaclass_EvaluateTaskReadiness_Request.__constants['PROFILE_RELOCALIZATION']


class EvaluateTaskReadiness_Request(metaclass=Metaclass_EvaluateTaskReadiness_Request):
    """
    Message class 'EvaluateTaskReadiness_Request'.

    Constants:
      PROFILE_TASK_EXECUTION
      PROFILE_RELOCALIZATION
    """

    __slots__ = [
        '_validate_task',
        '_task_id',
        '_gate_profile',
    ]

    _fields_and_field_types = {
        'validate_task': 'boolean',
        'task_id': 'string',
        'gate_profile': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.validate_task = kwargs.get('validate_task', bool())
        self.task_id = kwargs.get('task_id', str())
        self.gate_profile = kwargs.get('gate_profile', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.validate_task != other.validate_task:
            return False
        if self.task_id != other.task_id:
            return False
        if self.gate_profile != other.gate_profile:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def validate_task(self):
        """Message field 'validate_task'."""
        return self._validate_task

    @validate_task.setter
    def validate_task(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'validate_task' field must be of type 'bool'"
        self._validate_task = value

    @builtins.property
    def task_id(self):
        """Message field 'task_id'."""
        return self._task_id

    @task_id.setter
    def task_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'task_id' field must be of type 'str'"
        self._task_id = value

    @builtins.property
    def gate_profile(self):
        """Message field 'gate_profile'."""
        return self._gate_profile

    @gate_profile.setter
    def gate_profile(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'gate_profile' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'gate_profile' field must be an unsigned integer in [0, 255]"
        self._gate_profile = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_EvaluateTaskReadiness_Response(type):
    """Metaclass of message 'EvaluateTaskReadiness_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('agt_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'agt_interfaces.srv.EvaluateTaskReadiness_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__evaluate_task_readiness__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__evaluate_task_readiness__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__evaluate_task_readiness__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__evaluate_task_readiness__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__evaluate_task_readiness__response

            from agt_interfaces.msg import TaskReadiness
            if TaskReadiness.__class__._TYPE_SUPPORT is None:
                TaskReadiness.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class EvaluateTaskReadiness_Response(metaclass=Metaclass_EvaluateTaskReadiness_Response):
    """Message class 'EvaluateTaskReadiness_Response'."""

    __slots__ = [
        '_readiness',
    ]

    _fields_and_field_types = {
        'readiness': 'agt_interfaces/TaskReadiness',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'TaskReadiness'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from agt_interfaces.msg import TaskReadiness
        self.readiness = kwargs.get('readiness', TaskReadiness())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.readiness != other.readiness:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def readiness(self):
        """Message field 'readiness'."""
        return self._readiness

    @readiness.setter
    def readiness(self, value):
        if __debug__:
            from agt_interfaces.msg import TaskReadiness
            assert \
                isinstance(value, TaskReadiness), \
                "The 'readiness' field must be a sub message of type 'TaskReadiness'"
        self._readiness = value


class Metaclass_EvaluateTaskReadiness(type):
    """Metaclass of service 'EvaluateTaskReadiness'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('agt_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'agt_interfaces.srv.EvaluateTaskReadiness')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__evaluate_task_readiness

            from agt_interfaces.srv import _evaluate_task_readiness
            if _evaluate_task_readiness.Metaclass_EvaluateTaskReadiness_Request._TYPE_SUPPORT is None:
                _evaluate_task_readiness.Metaclass_EvaluateTaskReadiness_Request.__import_type_support__()
            if _evaluate_task_readiness.Metaclass_EvaluateTaskReadiness_Response._TYPE_SUPPORT is None:
                _evaluate_task_readiness.Metaclass_EvaluateTaskReadiness_Response.__import_type_support__()


class EvaluateTaskReadiness(metaclass=Metaclass_EvaluateTaskReadiness):
    from agt_interfaces.srv._evaluate_task_readiness import EvaluateTaskReadiness_Request as Request
    from agt_interfaces.srv._evaluate_task_readiness import EvaluateTaskReadiness_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
