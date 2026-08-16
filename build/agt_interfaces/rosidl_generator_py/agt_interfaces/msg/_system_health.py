# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/SystemHealth.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SystemHealth(type):
    """Metaclass of message 'SystemHealth'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'STATE_UNKNOWN': 0,
        'STATE_OK': 1,
        'STATE_WARN': 2,
        'STATE_ERROR': 3,
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
                'agt_interfaces.msg.SystemHealth')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__system_health
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__system_health
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__system_health
            cls._TYPE_SUPPORT = module.type_support_msg__msg__system_health
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__system_health

            from agt_interfaces.msg import ComponentHealth
            if ComponentHealth.__class__._TYPE_SUPPORT is None:
                ComponentHealth.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'STATE_UNKNOWN': cls.__constants['STATE_UNKNOWN'],
            'STATE_OK': cls.__constants['STATE_OK'],
            'STATE_WARN': cls.__constants['STATE_WARN'],
            'STATE_ERROR': cls.__constants['STATE_ERROR'],
        }

    @property
    def STATE_UNKNOWN(self):
        """Message constant 'STATE_UNKNOWN'."""
        return Metaclass_SystemHealth.__constants['STATE_UNKNOWN']

    @property
    def STATE_OK(self):
        """Message constant 'STATE_OK'."""
        return Metaclass_SystemHealth.__constants['STATE_OK']

    @property
    def STATE_WARN(self):
        """Message constant 'STATE_WARN'."""
        return Metaclass_SystemHealth.__constants['STATE_WARN']

    @property
    def STATE_ERROR(self):
        """Message constant 'STATE_ERROR'."""
        return Metaclass_SystemHealth.__constants['STATE_ERROR']


class SystemHealth(metaclass=Metaclass_SystemHealth):
    """
    Message class 'SystemHealth'.

    Constants:
      STATE_UNKNOWN
      STATE_OK
      STATE_WARN
      STATE_ERROR
    """

    __slots__ = [
        '_header',
        '_overall_state',
        '_revision',
        '_components',
        '_blocker_codes',
        '_blocker_messages',
        '_warning_codes',
        '_warning_messages',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'overall_state': 'uint8',
        'revision': 'uint64',
        'components': 'sequence<agt_interfaces/ComponentHealth>',
        'blocker_codes': 'sequence<string>',
        'blocker_messages': 'sequence<string>',
        'warning_codes': 'sequence<string>',
        'warning_messages': 'sequence<string>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'ComponentHealth')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.overall_state = kwargs.get('overall_state', int())
        self.revision = kwargs.get('revision', int())
        self.components = kwargs.get('components', [])
        self.blocker_codes = kwargs.get('blocker_codes', [])
        self.blocker_messages = kwargs.get('blocker_messages', [])
        self.warning_codes = kwargs.get('warning_codes', [])
        self.warning_messages = kwargs.get('warning_messages', [])

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
        if self.header != other.header:
            return False
        if self.overall_state != other.overall_state:
            return False
        if self.revision != other.revision:
            return False
        if self.components != other.components:
            return False
        if self.blocker_codes != other.blocker_codes:
            return False
        if self.blocker_messages != other.blocker_messages:
            return False
        if self.warning_codes != other.warning_codes:
            return False
        if self.warning_messages != other.warning_messages:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def overall_state(self):
        """Message field 'overall_state'."""
        return self._overall_state

    @overall_state.setter
    def overall_state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'overall_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'overall_state' field must be an unsigned integer in [0, 255]"
        self._overall_state = value

    @builtins.property
    def revision(self):
        """Message field 'revision'."""
        return self._revision

    @revision.setter
    def revision(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'revision' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'revision' field must be an unsigned integer in [0, 18446744073709551615]"
        self._revision = value

    @builtins.property
    def components(self):
        """Message field 'components'."""
        return self._components

    @components.setter
    def components(self, value):
        if __debug__:
            from agt_interfaces.msg import ComponentHealth
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
                 all(isinstance(v, ComponentHealth) for v in value) and
                 True), \
                "The 'components' field must be a set or sequence and each value of type 'ComponentHealth'"
        self._components = value

    @builtins.property
    def blocker_codes(self):
        """Message field 'blocker_codes'."""
        return self._blocker_codes

    @blocker_codes.setter
    def blocker_codes(self, value):
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
                "The 'blocker_codes' field must be a set or sequence and each value of type 'str'"
        self._blocker_codes = value

    @builtins.property
    def blocker_messages(self):
        """Message field 'blocker_messages'."""
        return self._blocker_messages

    @blocker_messages.setter
    def blocker_messages(self, value):
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
                "The 'blocker_messages' field must be a set or sequence and each value of type 'str'"
        self._blocker_messages = value

    @builtins.property
    def warning_codes(self):
        """Message field 'warning_codes'."""
        return self._warning_codes

    @warning_codes.setter
    def warning_codes(self, value):
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
                "The 'warning_codes' field must be a set or sequence and each value of type 'str'"
        self._warning_codes = value

    @builtins.property
    def warning_messages(self):
        """Message field 'warning_messages'."""
        return self._warning_messages

    @warning_messages.setter
    def warning_messages(self, value):
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
                "The 'warning_messages' field must be a set or sequence and each value of type 'str'"
        self._warning_messages = value
