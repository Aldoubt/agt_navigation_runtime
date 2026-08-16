# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/MissionStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MissionStatus(type):
    """Metaclass of message 'MissionStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'STATE_IDLE': 0,
        'STATE_VALIDATING': 1,
        'STATE_RUNNING': 2,
        'STATE_WAITING_DURATION': 3,
        'STATE_WAITING_EVENT': 4,
        'STATE_PAUSING': 5,
        'STATE_PAUSED': 6,
        'STATE_RESUMING': 7,
        'STATE_CANCELING': 8,
        'STATE_SUCCEEDED': 9,
        'STATE_FAILED': 10,
        'STATE_CANCELED': 11,
        'STATE_INTERRUPTED': 12,
        'STEP_UNKNOWN': 0,
        'STEP_WAYPOINT_TASK': 1,
        'STEP_WAIT_DURATION': 2,
        'STEP_WAIT_EVENT': 3,
        'ERROR_NONE': 0,
        'ERROR_INVALID_MISSION': 1,
        'ERROR_MAP_MISMATCH': 2,
        'ERROR_READINESS_LOST': 3,
        'ERROR_LOCALIZATION_LOST': 4,
        'ERROR_CHILD_REJECTED': 5,
        'ERROR_CHILD_FAILED': 6,
        'ERROR_EVENT_TIMEOUT': 7,
        'ERROR_CANCELED': 8,
        'ERROR_RESUME_BLOCKED': 9,
        'ERROR_INTERNAL': 255,
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
                'agt_interfaces.msg.MissionStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__mission_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__mission_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__mission_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__mission_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__mission_status

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'STATE_IDLE': cls.__constants['STATE_IDLE'],
            'STATE_VALIDATING': cls.__constants['STATE_VALIDATING'],
            'STATE_RUNNING': cls.__constants['STATE_RUNNING'],
            'STATE_WAITING_DURATION': cls.__constants['STATE_WAITING_DURATION'],
            'STATE_WAITING_EVENT': cls.__constants['STATE_WAITING_EVENT'],
            'STATE_PAUSING': cls.__constants['STATE_PAUSING'],
            'STATE_PAUSED': cls.__constants['STATE_PAUSED'],
            'STATE_RESUMING': cls.__constants['STATE_RESUMING'],
            'STATE_CANCELING': cls.__constants['STATE_CANCELING'],
            'STATE_SUCCEEDED': cls.__constants['STATE_SUCCEEDED'],
            'STATE_FAILED': cls.__constants['STATE_FAILED'],
            'STATE_CANCELED': cls.__constants['STATE_CANCELED'],
            'STATE_INTERRUPTED': cls.__constants['STATE_INTERRUPTED'],
            'STEP_UNKNOWN': cls.__constants['STEP_UNKNOWN'],
            'STEP_WAYPOINT_TASK': cls.__constants['STEP_WAYPOINT_TASK'],
            'STEP_WAIT_DURATION': cls.__constants['STEP_WAIT_DURATION'],
            'STEP_WAIT_EVENT': cls.__constants['STEP_WAIT_EVENT'],
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_INVALID_MISSION': cls.__constants['ERROR_INVALID_MISSION'],
            'ERROR_MAP_MISMATCH': cls.__constants['ERROR_MAP_MISMATCH'],
            'ERROR_READINESS_LOST': cls.__constants['ERROR_READINESS_LOST'],
            'ERROR_LOCALIZATION_LOST': cls.__constants['ERROR_LOCALIZATION_LOST'],
            'ERROR_CHILD_REJECTED': cls.__constants['ERROR_CHILD_REJECTED'],
            'ERROR_CHILD_FAILED': cls.__constants['ERROR_CHILD_FAILED'],
            'ERROR_EVENT_TIMEOUT': cls.__constants['ERROR_EVENT_TIMEOUT'],
            'ERROR_CANCELED': cls.__constants['ERROR_CANCELED'],
            'ERROR_RESUME_BLOCKED': cls.__constants['ERROR_RESUME_BLOCKED'],
            'ERROR_INTERNAL': cls.__constants['ERROR_INTERNAL'],
        }

    @property
    def STATE_IDLE(self):
        """Message constant 'STATE_IDLE'."""
        return Metaclass_MissionStatus.__constants['STATE_IDLE']

    @property
    def STATE_VALIDATING(self):
        """Message constant 'STATE_VALIDATING'."""
        return Metaclass_MissionStatus.__constants['STATE_VALIDATING']

    @property
    def STATE_RUNNING(self):
        """Message constant 'STATE_RUNNING'."""
        return Metaclass_MissionStatus.__constants['STATE_RUNNING']

    @property
    def STATE_WAITING_DURATION(self):
        """Message constant 'STATE_WAITING_DURATION'."""
        return Metaclass_MissionStatus.__constants['STATE_WAITING_DURATION']

    @property
    def STATE_WAITING_EVENT(self):
        """Message constant 'STATE_WAITING_EVENT'."""
        return Metaclass_MissionStatus.__constants['STATE_WAITING_EVENT']

    @property
    def STATE_PAUSING(self):
        """Message constant 'STATE_PAUSING'."""
        return Metaclass_MissionStatus.__constants['STATE_PAUSING']

    @property
    def STATE_PAUSED(self):
        """Message constant 'STATE_PAUSED'."""
        return Metaclass_MissionStatus.__constants['STATE_PAUSED']

    @property
    def STATE_RESUMING(self):
        """Message constant 'STATE_RESUMING'."""
        return Metaclass_MissionStatus.__constants['STATE_RESUMING']

    @property
    def STATE_CANCELING(self):
        """Message constant 'STATE_CANCELING'."""
        return Metaclass_MissionStatus.__constants['STATE_CANCELING']

    @property
    def STATE_SUCCEEDED(self):
        """Message constant 'STATE_SUCCEEDED'."""
        return Metaclass_MissionStatus.__constants['STATE_SUCCEEDED']

    @property
    def STATE_FAILED(self):
        """Message constant 'STATE_FAILED'."""
        return Metaclass_MissionStatus.__constants['STATE_FAILED']

    @property
    def STATE_CANCELED(self):
        """Message constant 'STATE_CANCELED'."""
        return Metaclass_MissionStatus.__constants['STATE_CANCELED']

    @property
    def STATE_INTERRUPTED(self):
        """Message constant 'STATE_INTERRUPTED'."""
        return Metaclass_MissionStatus.__constants['STATE_INTERRUPTED']

    @property
    def STEP_UNKNOWN(self):
        """Message constant 'STEP_UNKNOWN'."""
        return Metaclass_MissionStatus.__constants['STEP_UNKNOWN']

    @property
    def STEP_WAYPOINT_TASK(self):
        """Message constant 'STEP_WAYPOINT_TASK'."""
        return Metaclass_MissionStatus.__constants['STEP_WAYPOINT_TASK']

    @property
    def STEP_WAIT_DURATION(self):
        """Message constant 'STEP_WAIT_DURATION'."""
        return Metaclass_MissionStatus.__constants['STEP_WAIT_DURATION']

    @property
    def STEP_WAIT_EVENT(self):
        """Message constant 'STEP_WAIT_EVENT'."""
        return Metaclass_MissionStatus.__constants['STEP_WAIT_EVENT']

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_MissionStatus.__constants['ERROR_NONE']

    @property
    def ERROR_INVALID_MISSION(self):
        """Message constant 'ERROR_INVALID_MISSION'."""
        return Metaclass_MissionStatus.__constants['ERROR_INVALID_MISSION']

    @property
    def ERROR_MAP_MISMATCH(self):
        """Message constant 'ERROR_MAP_MISMATCH'."""
        return Metaclass_MissionStatus.__constants['ERROR_MAP_MISMATCH']

    @property
    def ERROR_READINESS_LOST(self):
        """Message constant 'ERROR_READINESS_LOST'."""
        return Metaclass_MissionStatus.__constants['ERROR_READINESS_LOST']

    @property
    def ERROR_LOCALIZATION_LOST(self):
        """Message constant 'ERROR_LOCALIZATION_LOST'."""
        return Metaclass_MissionStatus.__constants['ERROR_LOCALIZATION_LOST']

    @property
    def ERROR_CHILD_REJECTED(self):
        """Message constant 'ERROR_CHILD_REJECTED'."""
        return Metaclass_MissionStatus.__constants['ERROR_CHILD_REJECTED']

    @property
    def ERROR_CHILD_FAILED(self):
        """Message constant 'ERROR_CHILD_FAILED'."""
        return Metaclass_MissionStatus.__constants['ERROR_CHILD_FAILED']

    @property
    def ERROR_EVENT_TIMEOUT(self):
        """Message constant 'ERROR_EVENT_TIMEOUT'."""
        return Metaclass_MissionStatus.__constants['ERROR_EVENT_TIMEOUT']

    @property
    def ERROR_CANCELED(self):
        """Message constant 'ERROR_CANCELED'."""
        return Metaclass_MissionStatus.__constants['ERROR_CANCELED']

    @property
    def ERROR_RESUME_BLOCKED(self):
        """Message constant 'ERROR_RESUME_BLOCKED'."""
        return Metaclass_MissionStatus.__constants['ERROR_RESUME_BLOCKED']

    @property
    def ERROR_INTERNAL(self):
        """Message constant 'ERROR_INTERNAL'."""
        return Metaclass_MissionStatus.__constants['ERROR_INTERNAL']


class MissionStatus(metaclass=Metaclass_MissionStatus):
    """
    Message class 'MissionStatus'.

    Constants:
      STATE_IDLE
      STATE_VALIDATING
      STATE_RUNNING
      STATE_WAITING_DURATION
      STATE_WAITING_EVENT
      STATE_PAUSING
      STATE_PAUSED
      STATE_RESUMING
      STATE_CANCELING
      STATE_SUCCEEDED
      STATE_FAILED
      STATE_CANCELED
      STATE_INTERRUPTED
      STEP_UNKNOWN
      STEP_WAYPOINT_TASK
      STEP_WAIT_DURATION
      STEP_WAIT_EVENT
      ERROR_NONE
      ERROR_INVALID_MISSION
      ERROR_MAP_MISMATCH
      ERROR_READINESS_LOST
      ERROR_LOCALIZATION_LOST
      ERROR_CHILD_REJECTED
      ERROR_CHILD_FAILED
      ERROR_EVENT_TIMEOUT
      ERROR_CANCELED
      ERROR_RESUME_BLOCKED
      ERROR_INTERNAL
    """

    __slots__ = [
        '_header',
        '_state',
        '_mission_id',
        '_mission_version',
        '_content_sha256',
        '_map_id',
        '_map_version_id',
        '_map_manifest_sha256',
        '_current_step_index',
        '_total_steps',
        '_current_step_id',
        '_current_step_type',
        '_current_waypoint',
        '_total_waypoints',
        '_step_elapsed_s',
        '_step_remaining_s',
        '_error_code',
        '_blocker_codes',
        '_blocker_messages',
        '_message',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'state': 'uint8',
        'mission_id': 'string',
        'mission_version': 'string',
        'content_sha256': 'string',
        'map_id': 'string',
        'map_version_id': 'string',
        'map_manifest_sha256': 'string',
        'current_step_index': 'uint32',
        'total_steps': 'uint32',
        'current_step_id': 'string',
        'current_step_type': 'uint8',
        'current_waypoint': 'uint32',
        'total_waypoints': 'uint32',
        'step_elapsed_s': 'double',
        'step_remaining_s': 'double',
        'error_code': 'uint16',
        'blocker_codes': 'sequence<string>',
        'blocker_messages': 'sequence<string>',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
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
        self.state = kwargs.get('state', int())
        self.mission_id = kwargs.get('mission_id', str())
        self.mission_version = kwargs.get('mission_version', str())
        self.content_sha256 = kwargs.get('content_sha256', str())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.map_manifest_sha256 = kwargs.get('map_manifest_sha256', str())
        self.current_step_index = kwargs.get('current_step_index', int())
        self.total_steps = kwargs.get('total_steps', int())
        self.current_step_id = kwargs.get('current_step_id', str())
        self.current_step_type = kwargs.get('current_step_type', int())
        self.current_waypoint = kwargs.get('current_waypoint', int())
        self.total_waypoints = kwargs.get('total_waypoints', int())
        self.step_elapsed_s = kwargs.get('step_elapsed_s', float())
        self.step_remaining_s = kwargs.get('step_remaining_s', float())
        self.error_code = kwargs.get('error_code', int())
        self.blocker_codes = kwargs.get('blocker_codes', [])
        self.blocker_messages = kwargs.get('blocker_messages', [])
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
        if self.header != other.header:
            return False
        if self.state != other.state:
            return False
        if self.mission_id != other.mission_id:
            return False
        if self.mission_version != other.mission_version:
            return False
        if self.content_sha256 != other.content_sha256:
            return False
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.map_manifest_sha256 != other.map_manifest_sha256:
            return False
        if self.current_step_index != other.current_step_index:
            return False
        if self.total_steps != other.total_steps:
            return False
        if self.current_step_id != other.current_step_id:
            return False
        if self.current_step_type != other.current_step_type:
            return False
        if self.current_waypoint != other.current_waypoint:
            return False
        if self.total_waypoints != other.total_waypoints:
            return False
        if self.step_elapsed_s != other.step_elapsed_s:
            return False
        if self.step_remaining_s != other.step_remaining_s:
            return False
        if self.error_code != other.error_code:
            return False
        if self.blocker_codes != other.blocker_codes:
            return False
        if self.blocker_messages != other.blocker_messages:
            return False
        if self.message != other.message:
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
    def mission_id(self):
        """Message field 'mission_id'."""
        return self._mission_id

    @mission_id.setter
    def mission_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'mission_id' field must be of type 'str'"
        self._mission_id = value

    @builtins.property
    def mission_version(self):
        """Message field 'mission_version'."""
        return self._mission_version

    @mission_version.setter
    def mission_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'mission_version' field must be of type 'str'"
        self._mission_version = value

    @builtins.property
    def content_sha256(self):
        """Message field 'content_sha256'."""
        return self._content_sha256

    @content_sha256.setter
    def content_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'content_sha256' field must be of type 'str'"
        self._content_sha256 = value

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
    def map_manifest_sha256(self):
        """Message field 'map_manifest_sha256'."""
        return self._map_manifest_sha256

    @map_manifest_sha256.setter
    def map_manifest_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_manifest_sha256' field must be of type 'str'"
        self._map_manifest_sha256 = value

    @builtins.property
    def current_step_index(self):
        """Message field 'current_step_index'."""
        return self._current_step_index

    @current_step_index.setter
    def current_step_index(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'current_step_index' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'current_step_index' field must be an unsigned integer in [0, 4294967295]"
        self._current_step_index = value

    @builtins.property
    def total_steps(self):
        """Message field 'total_steps'."""
        return self._total_steps

    @total_steps.setter
    def total_steps(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'total_steps' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'total_steps' field must be an unsigned integer in [0, 4294967295]"
        self._total_steps = value

    @builtins.property
    def current_step_id(self):
        """Message field 'current_step_id'."""
        return self._current_step_id

    @current_step_id.setter
    def current_step_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'current_step_id' field must be of type 'str'"
        self._current_step_id = value

    @builtins.property
    def current_step_type(self):
        """Message field 'current_step_type'."""
        return self._current_step_type

    @current_step_type.setter
    def current_step_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'current_step_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'current_step_type' field must be an unsigned integer in [0, 255]"
        self._current_step_type = value

    @builtins.property
    def current_waypoint(self):
        """Message field 'current_waypoint'."""
        return self._current_waypoint

    @current_waypoint.setter
    def current_waypoint(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'current_waypoint' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'current_waypoint' field must be an unsigned integer in [0, 4294967295]"
        self._current_waypoint = value

    @builtins.property
    def total_waypoints(self):
        """Message field 'total_waypoints'."""
        return self._total_waypoints

    @total_waypoints.setter
    def total_waypoints(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'total_waypoints' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'total_waypoints' field must be an unsigned integer in [0, 4294967295]"
        self._total_waypoints = value

    @builtins.property
    def step_elapsed_s(self):
        """Message field 'step_elapsed_s'."""
        return self._step_elapsed_s

    @step_elapsed_s.setter
    def step_elapsed_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'step_elapsed_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'step_elapsed_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._step_elapsed_s = value

    @builtins.property
    def step_remaining_s(self):
        """Message field 'step_remaining_s'."""
        return self._step_remaining_s

    @step_remaining_s.setter
    def step_remaining_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'step_remaining_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'step_remaining_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._step_remaining_s = value

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
