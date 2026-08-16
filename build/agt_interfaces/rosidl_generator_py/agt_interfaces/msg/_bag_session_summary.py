# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/BagSessionSummary.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_BagSessionSummary(type):
    """Metaclass of message 'BagSessionSummary'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'STATE_UNKNOWN': 0,
        'STATE_IDLE': 1,
        'STATE_RECORDING': 2,
        'STATE_PLAYING': 3,
        'STATE_COMPLETED': 4,
        'STATE_INTERRUPTED': 5,
        'STATE_ERROR': 6,
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
                'agt_interfaces.msg.BagSessionSummary')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__bag_session_summary
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__bag_session_summary
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__bag_session_summary
            cls._TYPE_SUPPORT = module.type_support_msg__msg__bag_session_summary
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__bag_session_summary

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
            'STATE_IDLE': cls.__constants['STATE_IDLE'],
            'STATE_RECORDING': cls.__constants['STATE_RECORDING'],
            'STATE_PLAYING': cls.__constants['STATE_PLAYING'],
            'STATE_COMPLETED': cls.__constants['STATE_COMPLETED'],
            'STATE_INTERRUPTED': cls.__constants['STATE_INTERRUPTED'],
            'STATE_ERROR': cls.__constants['STATE_ERROR'],
        }

    @property
    def STATE_UNKNOWN(self):
        """Message constant 'STATE_UNKNOWN'."""
        return Metaclass_BagSessionSummary.__constants['STATE_UNKNOWN']

    @property
    def STATE_IDLE(self):
        """Message constant 'STATE_IDLE'."""
        return Metaclass_BagSessionSummary.__constants['STATE_IDLE']

    @property
    def STATE_RECORDING(self):
        """Message constant 'STATE_RECORDING'."""
        return Metaclass_BagSessionSummary.__constants['STATE_RECORDING']

    @property
    def STATE_PLAYING(self):
        """Message constant 'STATE_PLAYING'."""
        return Metaclass_BagSessionSummary.__constants['STATE_PLAYING']

    @property
    def STATE_COMPLETED(self):
        """Message constant 'STATE_COMPLETED'."""
        return Metaclass_BagSessionSummary.__constants['STATE_COMPLETED']

    @property
    def STATE_INTERRUPTED(self):
        """Message constant 'STATE_INTERRUPTED'."""
        return Metaclass_BagSessionSummary.__constants['STATE_INTERRUPTED']

    @property
    def STATE_ERROR(self):
        """Message constant 'STATE_ERROR'."""
        return Metaclass_BagSessionSummary.__constants['STATE_ERROR']


class BagSessionSummary(metaclass=Metaclass_BagSessionSummary):
    """
    Message class 'BagSessionSummary'.

    Constants:
      STATE_UNKNOWN
      STATE_IDLE
      STATE_RECORDING
      STATE_PLAYING
      STATE_COMPLETED
      STATE_INTERRUPTED
      STATE_ERROR
    """

    __slots__ = [
        '_header',
        '_state',
        '_bag_id',
        '_experiment_id',
        '_profile_id',
        '_relative_uri',
        '_complete',
        '_simulation',
        '_playback_rate',
        '_storage_bytes',
        '_started_at',
        '_updated_at',
        '_message',
        '_process_id',
        '_message_count',
        '_storage_identifier',
        '_mapping_input_ready',
        '_contains_mapping_outputs',
        '_contains_navigation_outputs',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'state': 'uint8',
        'bag_id': 'string',
        'experiment_id': 'string',
        'profile_id': 'string',
        'relative_uri': 'string',
        'complete': 'boolean',
        'simulation': 'boolean',
        'playback_rate': 'double',
        'storage_bytes': 'uint64',
        'started_at': 'string',
        'updated_at': 'string',
        'message': 'string',
        'process_id': 'int64',
        'message_count': 'uint64',
        'storage_identifier': 'string',
        'mapping_input_ready': 'boolean',
        'contains_mapping_outputs': 'boolean',
        'contains_navigation_outputs': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.state = kwargs.get('state', int())
        self.bag_id = kwargs.get('bag_id', str())
        self.experiment_id = kwargs.get('experiment_id', str())
        self.profile_id = kwargs.get('profile_id', str())
        self.relative_uri = kwargs.get('relative_uri', str())
        self.complete = kwargs.get('complete', bool())
        self.simulation = kwargs.get('simulation', bool())
        self.playback_rate = kwargs.get('playback_rate', float())
        self.storage_bytes = kwargs.get('storage_bytes', int())
        self.started_at = kwargs.get('started_at', str())
        self.updated_at = kwargs.get('updated_at', str())
        self.message = kwargs.get('message', str())
        self.process_id = kwargs.get('process_id', int())
        self.message_count = kwargs.get('message_count', int())
        self.storage_identifier = kwargs.get('storage_identifier', str())
        self.mapping_input_ready = kwargs.get('mapping_input_ready', bool())
        self.contains_mapping_outputs = kwargs.get('contains_mapping_outputs', bool())
        self.contains_navigation_outputs = kwargs.get('contains_navigation_outputs', bool())

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
        if self.state != other.state:
            return False
        if self.bag_id != other.bag_id:
            return False
        if self.experiment_id != other.experiment_id:
            return False
        if self.profile_id != other.profile_id:
            return False
        if self.relative_uri != other.relative_uri:
            return False
        if self.complete != other.complete:
            return False
        if self.simulation != other.simulation:
            return False
        if self.playback_rate != other.playback_rate:
            return False
        if self.storage_bytes != other.storage_bytes:
            return False
        if self.started_at != other.started_at:
            return False
        if self.updated_at != other.updated_at:
            return False
        if self.message != other.message:
            return False
        if self.process_id != other.process_id:
            return False
        if self.message_count != other.message_count:
            return False
        if self.storage_identifier != other.storage_identifier:
            return False
        if self.mapping_input_ready != other.mapping_input_ready:
            return False
        if self.contains_mapping_outputs != other.contains_mapping_outputs:
            return False
        if self.contains_navigation_outputs != other.contains_navigation_outputs:
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
    def bag_id(self):
        """Message field 'bag_id'."""
        return self._bag_id

    @bag_id.setter
    def bag_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'bag_id' field must be of type 'str'"
        self._bag_id = value

    @builtins.property
    def experiment_id(self):
        """Message field 'experiment_id'."""
        return self._experiment_id

    @experiment_id.setter
    def experiment_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'experiment_id' field must be of type 'str'"
        self._experiment_id = value

    @builtins.property
    def profile_id(self):
        """Message field 'profile_id'."""
        return self._profile_id

    @profile_id.setter
    def profile_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'profile_id' field must be of type 'str'"
        self._profile_id = value

    @builtins.property
    def relative_uri(self):
        """Message field 'relative_uri'."""
        return self._relative_uri

    @relative_uri.setter
    def relative_uri(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'relative_uri' field must be of type 'str'"
        self._relative_uri = value

    @builtins.property
    def complete(self):
        """Message field 'complete'."""
        return self._complete

    @complete.setter
    def complete(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'complete' field must be of type 'bool'"
        self._complete = value

    @builtins.property
    def simulation(self):
        """Message field 'simulation'."""
        return self._simulation

    @simulation.setter
    def simulation(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'simulation' field must be of type 'bool'"
        self._simulation = value

    @builtins.property
    def playback_rate(self):
        """Message field 'playback_rate'."""
        return self._playback_rate

    @playback_rate.setter
    def playback_rate(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'playback_rate' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'playback_rate' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._playback_rate = value

    @builtins.property
    def storage_bytes(self):
        """Message field 'storage_bytes'."""
        return self._storage_bytes

    @storage_bytes.setter
    def storage_bytes(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'storage_bytes' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'storage_bytes' field must be an unsigned integer in [0, 18446744073709551615]"
        self._storage_bytes = value

    @builtins.property
    def started_at(self):
        """Message field 'started_at'."""
        return self._started_at

    @started_at.setter
    def started_at(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'started_at' field must be of type 'str'"
        self._started_at = value

    @builtins.property
    def updated_at(self):
        """Message field 'updated_at'."""
        return self._updated_at

    @updated_at.setter
    def updated_at(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'updated_at' field must be of type 'str'"
        self._updated_at = value

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

    @builtins.property
    def process_id(self):
        """Message field 'process_id'."""
        return self._process_id

    @process_id.setter
    def process_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'process_id' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'process_id' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._process_id = value

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
    def storage_identifier(self):
        """Message field 'storage_identifier'."""
        return self._storage_identifier

    @storage_identifier.setter
    def storage_identifier(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'storage_identifier' field must be of type 'str'"
        self._storage_identifier = value

    @builtins.property
    def mapping_input_ready(self):
        """Message field 'mapping_input_ready'."""
        return self._mapping_input_ready

    @mapping_input_ready.setter
    def mapping_input_ready(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'mapping_input_ready' field must be of type 'bool'"
        self._mapping_input_ready = value

    @builtins.property
    def contains_mapping_outputs(self):
        """Message field 'contains_mapping_outputs'."""
        return self._contains_mapping_outputs

    @contains_mapping_outputs.setter
    def contains_mapping_outputs(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'contains_mapping_outputs' field must be of type 'bool'"
        self._contains_mapping_outputs = value

    @builtins.property
    def contains_navigation_outputs(self):
        """Message field 'contains_navigation_outputs'."""
        return self._contains_navigation_outputs

    @contains_navigation_outputs.setter
    def contains_navigation_outputs(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'contains_navigation_outputs' field must be of type 'bool'"
        self._contains_navigation_outputs = value
