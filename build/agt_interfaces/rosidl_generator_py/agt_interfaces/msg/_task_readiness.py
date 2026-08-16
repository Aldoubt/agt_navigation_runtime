# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/TaskReadiness.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TaskReadiness(type):
    """Metaclass of message 'TaskReadiness'."""

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
                'agt_interfaces.msg.TaskReadiness')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__task_readiness
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__task_readiness
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__task_readiness
            cls._TYPE_SUPPORT = module.type_support_msg__msg__task_readiness
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__task_readiness

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class TaskReadiness(metaclass=Metaclass_TaskReadiness):
    """Message class 'TaskReadiness'."""

    __slots__ = [
        '_header',
        '_ready',
        '_active_mode',
        '_map_id',
        '_map_version_id',
        '_localization_state',
        '_health_revision',
        '_blocker_codes',
        '_blocker_messages',
        '_warning_codes',
        '_warning_messages',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'ready': 'boolean',
        'active_mode': 'string',
        'map_id': 'string',
        'map_version_id': 'string',
        'localization_state': 'string',
        'health_revision': 'uint64',
        'blocker_codes': 'sequence<string>',
        'blocker_messages': 'sequence<string>',
        'warning_codes': 'sequence<string>',
        'warning_messages': 'sequence<string>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
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
        self.ready = kwargs.get('ready', bool())
        self.active_mode = kwargs.get('active_mode', str())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.localization_state = kwargs.get('localization_state', str())
        self.health_revision = kwargs.get('health_revision', int())
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
        if self.ready != other.ready:
            return False
        if self.active_mode != other.active_mode:
            return False
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.localization_state != other.localization_state:
            return False
        if self.health_revision != other.health_revision:
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
    def ready(self):
        """Message field 'ready'."""
        return self._ready

    @ready.setter
    def ready(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ready' field must be of type 'bool'"
        self._ready = value

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
    def map_id(self):
        """Message field 'map_id'."""
        return self._map_id

    @map_id.setter
    def map_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_id' field must be of type 'str'"
        self._map_id = value

    @builtins.property
    def map_version_id(self):
        """Message field 'map_version_id'."""
        return self._map_version_id

    @map_version_id.setter
    def map_version_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_version_id' field must be of type 'str'"
        self._map_version_id = value

    @builtins.property
    def localization_state(self):
        """Message field 'localization_state'."""
        return self._localization_state

    @localization_state.setter
    def localization_state(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'localization_state' field must be of type 'str'"
        self._localization_state = value

    @builtins.property
    def health_revision(self):
        """Message field 'health_revision'."""
        return self._health_revision

    @health_revision.setter
    def health_revision(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'health_revision' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'health_revision' field must be an unsigned integer in [0, 18446744073709551615]"
        self._health_revision = value

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
