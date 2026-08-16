# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:action/ChangeSystemMode.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ChangeSystemMode_Goal(type):
    """Metaclass of message 'ChangeSystemMode_Goal'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'MODE_IDLE': 0,
        'MODE_SENSOR_ONLY': 1,
        'MODE_MAPPING': 2,
        'MODE_LOCALIZATION_DEBUG': 3,
        'MODE_NAVIGATION': 4,
        'MODE_ERROR': 5,
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
                'agt_interfaces.action.ChangeSystemMode_Goal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__change_system_mode__goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__change_system_mode__goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__change_system_mode__goal
            cls._TYPE_SUPPORT = module.type_support_msg__action__change_system_mode__goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__change_system_mode__goal

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'MODE_IDLE': cls.__constants['MODE_IDLE'],
            'MODE_SENSOR_ONLY': cls.__constants['MODE_SENSOR_ONLY'],
            'MODE_MAPPING': cls.__constants['MODE_MAPPING'],
            'MODE_LOCALIZATION_DEBUG': cls.__constants['MODE_LOCALIZATION_DEBUG'],
            'MODE_NAVIGATION': cls.__constants['MODE_NAVIGATION'],
            'MODE_ERROR': cls.__constants['MODE_ERROR'],
        }

    @property
    def MODE_IDLE(self):
        """Message constant 'MODE_IDLE'."""
        return Metaclass_ChangeSystemMode_Goal.__constants['MODE_IDLE']

    @property
    def MODE_SENSOR_ONLY(self):
        """Message constant 'MODE_SENSOR_ONLY'."""
        return Metaclass_ChangeSystemMode_Goal.__constants['MODE_SENSOR_ONLY']

    @property
    def MODE_MAPPING(self):
        """Message constant 'MODE_MAPPING'."""
        return Metaclass_ChangeSystemMode_Goal.__constants['MODE_MAPPING']

    @property
    def MODE_LOCALIZATION_DEBUG(self):
        """Message constant 'MODE_LOCALIZATION_DEBUG'."""
        return Metaclass_ChangeSystemMode_Goal.__constants['MODE_LOCALIZATION_DEBUG']

    @property
    def MODE_NAVIGATION(self):
        """Message constant 'MODE_NAVIGATION'."""
        return Metaclass_ChangeSystemMode_Goal.__constants['MODE_NAVIGATION']

    @property
    def MODE_ERROR(self):
        """Message constant 'MODE_ERROR'."""
        return Metaclass_ChangeSystemMode_Goal.__constants['MODE_ERROR']


class ChangeSystemMode_Goal(metaclass=Metaclass_ChangeSystemMode_Goal):
    """
    Message class 'ChangeSystemMode_Goal'.

    Constants:
      MODE_IDLE
      MODE_SENSOR_ONLY
      MODE_MAPPING
      MODE_LOCALIZATION_DEBUG
      MODE_NAVIGATION
      MODE_ERROR
    """

    __slots__ = [
        '_mode',
        '_profile',
        '_argument_keys',
        '_argument_values',
        '_wait_for_health',
        '_startup_timeout_s',
    ]

    _fields_and_field_types = {
        'mode': 'uint8',
        'profile': 'string',
        'argument_keys': 'sequence<string>',
        'argument_values': 'sequence<string>',
        'wait_for_health': 'boolean',
        'startup_timeout_s': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.mode = kwargs.get('mode', int())
        self.profile = kwargs.get('profile', str())
        self.argument_keys = kwargs.get('argument_keys', [])
        self.argument_values = kwargs.get('argument_values', [])
        self.wait_for_health = kwargs.get('wait_for_health', bool())
        self.startup_timeout_s = kwargs.get('startup_timeout_s', float())

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
        if self.mode != other.mode:
            return False
        if self.profile != other.profile:
            return False
        if self.argument_keys != other.argument_keys:
            return False
        if self.argument_values != other.argument_values:
            return False
        if self.wait_for_health != other.wait_for_health:
            return False
        if self.startup_timeout_s != other.startup_timeout_s:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def mode(self):
        """Message field 'mode'."""
        return self._mode

    @mode.setter
    def mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mode' field must be an unsigned integer in [0, 255]"
        self._mode = value

    @builtins.property
    def profile(self):
        """Message field 'profile'."""
        return self._profile

    @profile.setter
    def profile(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'profile' field must be of type 'str'"
        self._profile = value

    @builtins.property
    def argument_keys(self):
        """Message field 'argument_keys'."""
        return self._argument_keys

    @argument_keys.setter
    def argument_keys(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'argument_keys' field must be a set or sequence and each value of type 'str'"
        self._argument_keys = value

    @builtins.property
    def argument_values(self):
        """Message field 'argument_values'."""
        return self._argument_values

    @argument_values.setter
    def argument_values(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'argument_values' field must be a set or sequence and each value of type 'str'"
        self._argument_values = value

    @builtins.property
    def wait_for_health(self):
        """Message field 'wait_for_health'."""
        return self._wait_for_health

    @wait_for_health.setter
    def wait_for_health(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'wait_for_health' field must be of type 'bool'"
        self._wait_for_health = value

    @builtins.property
    def startup_timeout_s(self):
        """Message field 'startup_timeout_s'."""
        return self._startup_timeout_s

    @startup_timeout_s.setter
    def startup_timeout_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'startup_timeout_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'startup_timeout_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._startup_timeout_s = value


# Import statements for member types

# Member 'process_ids'
import array  # noqa: E402, I100

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ChangeSystemMode_Result(type):
    """Metaclass of message 'ChangeSystemMode_Result'."""

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
                'agt_interfaces.action.ChangeSystemMode_Result')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__change_system_mode__result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__change_system_mode__result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__change_system_mode__result
            cls._TYPE_SUPPORT = module.type_support_msg__action__change_system_mode__result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__change_system_mode__result

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ChangeSystemMode_Result(metaclass=Metaclass_ChangeSystemMode_Result):
    """Message class 'ChangeSystemMode_Result'."""

    __slots__ = [
        '_success',
        '_error_code',
        '_active_mode',
        '_profile',
        '_process_ids',
        '_log_paths',
        '_message',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'active_mode': 'string',
        'profile': 'string',
        'process_ids': 'sequence<int32>',
        'log_paths': 'sequence<string>',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        self.active_mode = kwargs.get('active_mode', str())
        self.profile = kwargs.get('profile', str())
        self.process_ids = array.array('i', kwargs.get('process_ids', []))
        self.log_paths = kwargs.get('log_paths', [])
        self.message = kwargs.get('message', str())

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
        if self.success != other.success:
            return False
        if self.error_code != other.error_code:
            return False
        if self.active_mode != other.active_mode:
            return False
        if self.profile != other.profile:
            return False
        if self.process_ids != other.process_ids:
            return False
        if self.log_paths != other.log_paths:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def error_code(self):
        """Message field 'error_code'."""
        return self._error_code

    @error_code.setter
    def error_code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'error_code' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'error_code' field must be an unsigned integer in [0, 65535]"
        self._error_code = value

    @builtins.property
    def active_mode(self):
        """Message field 'active_mode'."""
        return self._active_mode

    @active_mode.setter
    def active_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'active_mode' field must be of type 'str'"
        self._active_mode = value

    @builtins.property
    def profile(self):
        """Message field 'profile'."""
        return self._profile

    @profile.setter
    def profile(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'profile' field must be of type 'str'"
        self._profile = value

    @builtins.property
    def process_ids(self):
        """Message field 'process_ids'."""
        return self._process_ids

    @process_ids.setter
    def process_ids(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'i', \
                "The 'process_ids' array.array() must have the type code of 'i'"
            self._process_ids = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'process_ids' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._process_ids = array.array('i', value)

    @builtins.property
    def log_paths(self):
        """Message field 'log_paths'."""
        return self._log_paths

    @log_paths.setter
    def log_paths(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'log_paths' field must be a set or sequence and each value of type 'str'"
        self._log_paths = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import math

# already imported above
# import rosidl_parser.definition


class Metaclass_ChangeSystemMode_Feedback(type):
    """Metaclass of message 'ChangeSystemMode_Feedback'."""

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
                'agt_interfaces.action.ChangeSystemMode_Feedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__change_system_mode__feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__change_system_mode__feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__change_system_mode__feedback
            cls._TYPE_SUPPORT = module.type_support_msg__action__change_system_mode__feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__change_system_mode__feedback

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ChangeSystemMode_Feedback(metaclass=Metaclass_ChangeSystemMode_Feedback):
    """Message class 'ChangeSystemMode_Feedback'."""

    __slots__ = [
        '_state',
        '_progress',
        '_message',
    ]

    _fields_and_field_types = {
        'state': 'string',
        'progress': 'float',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.state = kwargs.get('state', str())
        self.progress = kwargs.get('progress', float())
        self.message = kwargs.get('message', str())

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
        if self.state != other.state:
            return False
        if self.progress != other.progress:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'state' field must be of type 'str'"
        self._state = value

    @builtins.property
    def progress(self):
        """Message field 'progress'."""
        return self._progress

    @progress.setter
    def progress(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'progress' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'progress' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._progress = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ChangeSystemMode_SendGoal_Request(type):
    """Metaclass of message 'ChangeSystemMode_SendGoal_Request'."""

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
                'agt_interfaces.action.ChangeSystemMode_SendGoal_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__change_system_mode__send_goal__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__change_system_mode__send_goal__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__change_system_mode__send_goal__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__change_system_mode__send_goal__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__change_system_mode__send_goal__request

            from agt_interfaces.action import ChangeSystemMode
            if ChangeSystemMode.Goal.__class__._TYPE_SUPPORT is None:
                ChangeSystemMode.Goal.__class__.__import_type_support__()

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ChangeSystemMode_SendGoal_Request(metaclass=Metaclass_ChangeSystemMode_SendGoal_Request):
    """Message class 'ChangeSystemMode_SendGoal_Request'."""

    __slots__ = [
        '_goal_id',
        '_goal',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'goal': 'agt_interfaces/ChangeSystemMode_Goal',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ChangeSystemMode_Goal'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._change_system_mode import ChangeSystemMode_Goal
        self.goal = kwargs.get('goal', ChangeSystemMode_Goal())

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
        if self.goal_id != other.goal_id:
            return False
        if self.goal != other.goal:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def goal(self):
        """Message field 'goal'."""
        return self._goal

    @goal.setter
    def goal(self, value):
        if __debug__:
            from agt_interfaces.action._change_system_mode import ChangeSystemMode_Goal
            assert \
                isinstance(value, ChangeSystemMode_Goal), \
                "The 'goal' field must be a sub message of type 'ChangeSystemMode_Goal'"
        self._goal = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ChangeSystemMode_SendGoal_Response(type):
    """Metaclass of message 'ChangeSystemMode_SendGoal_Response'."""

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
                'agt_interfaces.action.ChangeSystemMode_SendGoal_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__change_system_mode__send_goal__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__change_system_mode__send_goal__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__change_system_mode__send_goal__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__change_system_mode__send_goal__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__change_system_mode__send_goal__response

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ChangeSystemMode_SendGoal_Response(metaclass=Metaclass_ChangeSystemMode_SendGoal_Response):
    """Message class 'ChangeSystemMode_SendGoal_Response'."""

    __slots__ = [
        '_accepted',
        '_stamp',
    ]

    _fields_and_field_types = {
        'accepted': 'boolean',
        'stamp': 'builtin_interfaces/Time',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.accepted = kwargs.get('accepted', bool())
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())

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
        if self.accepted != other.accepted:
            return False
        if self.stamp != other.stamp:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def accepted(self):
        """Message field 'accepted'."""
        return self._accepted

    @accepted.setter
    def accepted(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'accepted' field must be of type 'bool'"
        self._accepted = value

    @builtins.property
    def stamp(self):
        """Message field 'stamp'."""
        return self._stamp

    @stamp.setter
    def stamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'stamp' field must be a sub message of type 'Time'"
        self._stamp = value


class Metaclass_ChangeSystemMode_SendGoal(type):
    """Metaclass of service 'ChangeSystemMode_SendGoal'."""

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
                'agt_interfaces.action.ChangeSystemMode_SendGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__change_system_mode__send_goal

            from agt_interfaces.action import _change_system_mode
            if _change_system_mode.Metaclass_ChangeSystemMode_SendGoal_Request._TYPE_SUPPORT is None:
                _change_system_mode.Metaclass_ChangeSystemMode_SendGoal_Request.__import_type_support__()
            if _change_system_mode.Metaclass_ChangeSystemMode_SendGoal_Response._TYPE_SUPPORT is None:
                _change_system_mode.Metaclass_ChangeSystemMode_SendGoal_Response.__import_type_support__()


class ChangeSystemMode_SendGoal(metaclass=Metaclass_ChangeSystemMode_SendGoal):
    from agt_interfaces.action._change_system_mode import ChangeSystemMode_SendGoal_Request as Request
    from agt_interfaces.action._change_system_mode import ChangeSystemMode_SendGoal_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ChangeSystemMode_GetResult_Request(type):
    """Metaclass of message 'ChangeSystemMode_GetResult_Request'."""

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
                'agt_interfaces.action.ChangeSystemMode_GetResult_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__change_system_mode__get_result__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__change_system_mode__get_result__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__change_system_mode__get_result__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__change_system_mode__get_result__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__change_system_mode__get_result__request

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ChangeSystemMode_GetResult_Request(metaclass=Metaclass_ChangeSystemMode_GetResult_Request):
    """Message class 'ChangeSystemMode_GetResult_Request'."""

    __slots__ = [
        '_goal_id',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())

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
        if self.goal_id != other.goal_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ChangeSystemMode_GetResult_Response(type):
    """Metaclass of message 'ChangeSystemMode_GetResult_Response'."""

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
                'agt_interfaces.action.ChangeSystemMode_GetResult_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__change_system_mode__get_result__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__change_system_mode__get_result__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__change_system_mode__get_result__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__change_system_mode__get_result__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__change_system_mode__get_result__response

            from agt_interfaces.action import ChangeSystemMode
            if ChangeSystemMode.Result.__class__._TYPE_SUPPORT is None:
                ChangeSystemMode.Result.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ChangeSystemMode_GetResult_Response(metaclass=Metaclass_ChangeSystemMode_GetResult_Response):
    """Message class 'ChangeSystemMode_GetResult_Response'."""

    __slots__ = [
        '_status',
        '_result',
    ]

    _fields_and_field_types = {
        'status': 'int8',
        'result': 'agt_interfaces/ChangeSystemMode_Result',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ChangeSystemMode_Result'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        from agt_interfaces.action._change_system_mode import ChangeSystemMode_Result
        self.result = kwargs.get('result', ChangeSystemMode_Result())

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
        if self.status != other.status:
            return False
        if self.result != other.result:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'status' field must be an integer in [-128, 127]"
        self._status = value

    @builtins.property
    def result(self):
        """Message field 'result'."""
        return self._result

    @result.setter
    def result(self, value):
        if __debug__:
            from agt_interfaces.action._change_system_mode import ChangeSystemMode_Result
            assert \
                isinstance(value, ChangeSystemMode_Result), \
                "The 'result' field must be a sub message of type 'ChangeSystemMode_Result'"
        self._result = value


class Metaclass_ChangeSystemMode_GetResult(type):
    """Metaclass of service 'ChangeSystemMode_GetResult'."""

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
                'agt_interfaces.action.ChangeSystemMode_GetResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__change_system_mode__get_result

            from agt_interfaces.action import _change_system_mode
            if _change_system_mode.Metaclass_ChangeSystemMode_GetResult_Request._TYPE_SUPPORT is None:
                _change_system_mode.Metaclass_ChangeSystemMode_GetResult_Request.__import_type_support__()
            if _change_system_mode.Metaclass_ChangeSystemMode_GetResult_Response._TYPE_SUPPORT is None:
                _change_system_mode.Metaclass_ChangeSystemMode_GetResult_Response.__import_type_support__()


class ChangeSystemMode_GetResult(metaclass=Metaclass_ChangeSystemMode_GetResult):
    from agt_interfaces.action._change_system_mode import ChangeSystemMode_GetResult_Request as Request
    from agt_interfaces.action._change_system_mode import ChangeSystemMode_GetResult_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ChangeSystemMode_FeedbackMessage(type):
    """Metaclass of message 'ChangeSystemMode_FeedbackMessage'."""

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
                'agt_interfaces.action.ChangeSystemMode_FeedbackMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__change_system_mode__feedback_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__change_system_mode__feedback_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__change_system_mode__feedback_message
            cls._TYPE_SUPPORT = module.type_support_msg__action__change_system_mode__feedback_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__change_system_mode__feedback_message

            from agt_interfaces.action import ChangeSystemMode
            if ChangeSystemMode.Feedback.__class__._TYPE_SUPPORT is None:
                ChangeSystemMode.Feedback.__class__.__import_type_support__()

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ChangeSystemMode_FeedbackMessage(metaclass=Metaclass_ChangeSystemMode_FeedbackMessage):
    """Message class 'ChangeSystemMode_FeedbackMessage'."""

    __slots__ = [
        '_goal_id',
        '_feedback',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'feedback': 'agt_interfaces/ChangeSystemMode_Feedback',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ChangeSystemMode_Feedback'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._change_system_mode import ChangeSystemMode_Feedback
        self.feedback = kwargs.get('feedback', ChangeSystemMode_Feedback())

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
        if self.goal_id != other.goal_id:
            return False
        if self.feedback != other.feedback:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def feedback(self):
        """Message field 'feedback'."""
        return self._feedback

    @feedback.setter
    def feedback(self, value):
        if __debug__:
            from agt_interfaces.action._change_system_mode import ChangeSystemMode_Feedback
            assert \
                isinstance(value, ChangeSystemMode_Feedback), \
                "The 'feedback' field must be a sub message of type 'ChangeSystemMode_Feedback'"
        self._feedback = value


class Metaclass_ChangeSystemMode(type):
    """Metaclass of action 'ChangeSystemMode'."""

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
                'agt_interfaces.action.ChangeSystemMode')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_action__action__change_system_mode

            from action_msgs.msg import _goal_status_array
            if _goal_status_array.Metaclass_GoalStatusArray._TYPE_SUPPORT is None:
                _goal_status_array.Metaclass_GoalStatusArray.__import_type_support__()
            from action_msgs.srv import _cancel_goal
            if _cancel_goal.Metaclass_CancelGoal._TYPE_SUPPORT is None:
                _cancel_goal.Metaclass_CancelGoal.__import_type_support__()

            from agt_interfaces.action import _change_system_mode
            if _change_system_mode.Metaclass_ChangeSystemMode_SendGoal._TYPE_SUPPORT is None:
                _change_system_mode.Metaclass_ChangeSystemMode_SendGoal.__import_type_support__()
            if _change_system_mode.Metaclass_ChangeSystemMode_GetResult._TYPE_SUPPORT is None:
                _change_system_mode.Metaclass_ChangeSystemMode_GetResult.__import_type_support__()
            if _change_system_mode.Metaclass_ChangeSystemMode_FeedbackMessage._TYPE_SUPPORT is None:
                _change_system_mode.Metaclass_ChangeSystemMode_FeedbackMessage.__import_type_support__()


class ChangeSystemMode(metaclass=Metaclass_ChangeSystemMode):

    # The goal message defined in the action definition.
    from agt_interfaces.action._change_system_mode import ChangeSystemMode_Goal as Goal
    # The result message defined in the action definition.
    from agt_interfaces.action._change_system_mode import ChangeSystemMode_Result as Result
    # The feedback message defined in the action definition.
    from agt_interfaces.action._change_system_mode import ChangeSystemMode_Feedback as Feedback

    class Impl:

        # The send_goal service using a wrapped version of the goal message as a request.
        from agt_interfaces.action._change_system_mode import ChangeSystemMode_SendGoal as SendGoalService
        # The get_result service using a wrapped version of the result message as a response.
        from agt_interfaces.action._change_system_mode import ChangeSystemMode_GetResult as GetResultService
        # The feedback message with generic fields which wraps the feedback message.
        from agt_interfaces.action._change_system_mode import ChangeSystemMode_FeedbackMessage as FeedbackMessage

        # The generic service to cancel a goal.
        from action_msgs.srv._cancel_goal import CancelGoal as CancelGoalService
        # The generic message for get the status of a goal.
        from action_msgs.msg._goal_status_array import GoalStatusArray as GoalStatusMessage

    def __init__(self):
        raise NotImplementedError('Action classes can not be instantiated')
