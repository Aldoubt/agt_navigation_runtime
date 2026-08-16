# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/ComponentHealth.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ComponentHealth(type):
    """Metaclass of message 'ComponentHealth'."""

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
                'agt_interfaces.msg.ComponentHealth')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__component_health
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__component_health
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__component_health
            cls._TYPE_SUPPORT = module.type_support_msg__msg__component_health
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__component_health

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
        return Metaclass_ComponentHealth.__constants['STATE_UNKNOWN']

    @property
    def STATE_OK(self):
        """Message constant 'STATE_OK'."""
        return Metaclass_ComponentHealth.__constants['STATE_OK']

    @property
    def STATE_WARN(self):
        """Message constant 'STATE_WARN'."""
        return Metaclass_ComponentHealth.__constants['STATE_WARN']

    @property
    def STATE_ERROR(self):
        """Message constant 'STATE_ERROR'."""
        return Metaclass_ComponentHealth.__constants['STATE_ERROR']


class ComponentHealth(metaclass=Metaclass_ComponentHealth):
    """
    Message class 'ComponentHealth'.

    Constants:
      STATE_UNKNOWN
      STATE_OK
      STATE_WARN
      STATE_ERROR
    """

    __slots__ = [
        '_header',
        '_component_id',
        '_display_name',
        '_state',
        '_required',
        '_present',
        '_observed_rate_hz',
        '_message_age_sec',
        '_message_count',
        '_missing_topics',
        '_missing_frames',
        '_missing_nodes',
        '_lifecycle_failures',
        '_condition_failures',
        '_warnings',
        '_errors',
        '_detail',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'component_id': 'string',
        'display_name': 'string',
        'state': 'uint8',
        'required': 'boolean',
        'present': 'boolean',
        'observed_rate_hz': 'double',
        'message_age_sec': 'double',
        'message_count': 'uint64',
        'missing_topics': 'sequence<string>',
        'missing_frames': 'sequence<string>',
        'missing_nodes': 'sequence<string>',
        'lifecycle_failures': 'sequence<string>',
        'condition_failures': 'sequence<string>',
        'warnings': 'sequence<string>',
        'errors': 'sequence<string>',
        'detail': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.component_id = kwargs.get('component_id', str())
        self.display_name = kwargs.get('display_name', str())
        self.state = kwargs.get('state', int())
        self.required = kwargs.get('required', bool())
        self.present = kwargs.get('present', bool())
        self.observed_rate_hz = kwargs.get('observed_rate_hz', float())
        self.message_age_sec = kwargs.get('message_age_sec', float())
        self.message_count = kwargs.get('message_count', int())
        self.missing_topics = kwargs.get('missing_topics', [])
        self.missing_frames = kwargs.get('missing_frames', [])
        self.missing_nodes = kwargs.get('missing_nodes', [])
        self.lifecycle_failures = kwargs.get('lifecycle_failures', [])
        self.condition_failures = kwargs.get('condition_failures', [])
        self.warnings = kwargs.get('warnings', [])
        self.errors = kwargs.get('errors', [])
        self.detail = kwargs.get('detail', str())

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
        if self.component_id != other.component_id:
            return False
        if self.display_name != other.display_name:
            return False
        if self.state != other.state:
            return False
        if self.required != other.required:
            return False
        if self.present != other.present:
            return False
        if self.observed_rate_hz != other.observed_rate_hz:
            return False
        if self.message_age_sec != other.message_age_sec:
            return False
        if self.message_count != other.message_count:
            return False
        if self.missing_topics != other.missing_topics:
            return False
        if self.missing_frames != other.missing_frames:
            return False
        if self.missing_nodes != other.missing_nodes:
            return False
        if self.lifecycle_failures != other.lifecycle_failures:
            return False
        if self.condition_failures != other.condition_failures:
            return False
        if self.warnings != other.warnings:
            return False
        if self.errors != other.errors:
            return False
        if self.detail != other.detail:
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
    def component_id(self):
        """Message field 'component_id'."""
        return self._component_id

    @component_id.setter
    def component_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'component_id' field must be of type 'str'"
        self._component_id = value

    @builtins.property
    def display_name(self):
        """Message field 'display_name'."""
        return self._display_name

    @display_name.setter
    def display_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'display_name' field must be of type 'str'"
        self._display_name = value

    @builtins.property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'state' field must be an unsigned integer in [0, 255]"
        self._state = value

    @builtins.property
    def required(self):
        """Message field 'required'."""
        return self._required

    @required.setter
    def required(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'required' field must be of type 'bool'"
        self._required = value

    @builtins.property
    def present(self):
        """Message field 'present'."""
        return self._present

    @present.setter
    def present(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'present' field must be of type 'bool'"
        self._present = value

    @builtins.property
    def observed_rate_hz(self):
        """Message field 'observed_rate_hz'."""
        return self._observed_rate_hz

    @observed_rate_hz.setter
    def observed_rate_hz(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'observed_rate_hz' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'observed_rate_hz' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._observed_rate_hz = value

    @builtins.property
    def message_age_sec(self):
        """Message field 'message_age_sec'."""
        return self._message_age_sec

    @message_age_sec.setter
    def message_age_sec(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'message_age_sec' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'message_age_sec' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._message_age_sec = value

    @builtins.property
    def message_count(self):
        """Message field 'message_count'."""
        return self._message_count

    @message_count.setter
    def message_count(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'message_count' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'message_count' field must be an unsigned integer in [0, 18446744073709551615]"
        self._message_count = value

    @builtins.property
    def missing_topics(self):
        """Message field 'missing_topics'."""
        return self._missing_topics

    @missing_topics.setter
    def missing_topics(self, value):
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
                "The 'missing_topics' field must be a set or sequence and each value of type 'str'"
        self._missing_topics = value

    @builtins.property
    def missing_frames(self):
        """Message field 'missing_frames'."""
        return self._missing_frames

    @missing_frames.setter
    def missing_frames(self, value):
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
                "The 'missing_frames' field must be a set or sequence and each value of type 'str'"
        self._missing_frames = value

    @builtins.property
    def missing_nodes(self):
        """Message field 'missing_nodes'."""
        return self._missing_nodes

    @missing_nodes.setter
    def missing_nodes(self, value):
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
                "The 'missing_nodes' field must be a set or sequence and each value of type 'str'"
        self._missing_nodes = value

    @builtins.property
    def lifecycle_failures(self):
        """Message field 'lifecycle_failures'."""
        return self._lifecycle_failures

    @lifecycle_failures.setter
    def lifecycle_failures(self, value):
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
                "The 'lifecycle_failures' field must be a set or sequence and each value of type 'str'"
        self._lifecycle_failures = value

    @builtins.property
    def condition_failures(self):
        """Message field 'condition_failures'."""
        return self._condition_failures

    @condition_failures.setter
    def condition_failures(self, value):
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
                "The 'condition_failures' field must be a set or sequence and each value of type 'str'"
        self._condition_failures = value

    @builtins.property
    def warnings(self):
        """Message field 'warnings'."""
        return self._warnings

    @warnings.setter
    def warnings(self, value):
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
                "The 'warnings' field must be a set or sequence and each value of type 'str'"
        self._warnings = value

    @builtins.property
    def errors(self):
        """Message field 'errors'."""
        return self._errors

    @errors.setter
    def errors(self, value):
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
                "The 'errors' field must be a set or sequence and each value of type 'str'"
        self._errors = value

    @builtins.property
    def detail(self):
        """Message field 'detail'."""
        return self._detail

    @detail.setter
    def detail(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'detail' field must be of type 'str'"
        self._detail = value
