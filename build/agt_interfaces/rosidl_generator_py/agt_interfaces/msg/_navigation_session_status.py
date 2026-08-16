# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/NavigationSessionStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'missed_waypoints'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_NavigationSessionStatus(type):
    """Metaclass of message 'NavigationSessionStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'STATE_IDLE': 0,
        'STATE_VALIDATING': 1,
        'STATE_REJECTED': 2,
        'STATE_ACCEPTED': 3,
        'STATE_RUNNING': 4,
        'STATE_CANCELING': 5,
        'STATE_SUCCEEDED': 6,
        'STATE_FAILED': 7,
        'STATE_CANCELED': 8,
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
                'agt_interfaces.msg.NavigationSessionStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__navigation_session_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__navigation_session_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__navigation_session_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__navigation_session_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__navigation_session_status

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

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
            'STATE_REJECTED': cls.__constants['STATE_REJECTED'],
            'STATE_ACCEPTED': cls.__constants['STATE_ACCEPTED'],
            'STATE_RUNNING': cls.__constants['STATE_RUNNING'],
            'STATE_CANCELING': cls.__constants['STATE_CANCELING'],
            'STATE_SUCCEEDED': cls.__constants['STATE_SUCCEEDED'],
            'STATE_FAILED': cls.__constants['STATE_FAILED'],
            'STATE_CANCELED': cls.__constants['STATE_CANCELED'],
        }

    @property
    def STATE_IDLE(self):
        """Message constant 'STATE_IDLE'."""
        return Metaclass_NavigationSessionStatus.__constants['STATE_IDLE']

    @property
    def STATE_VALIDATING(self):
        """Message constant 'STATE_VALIDATING'."""
        return Metaclass_NavigationSessionStatus.__constants['STATE_VALIDATING']

    @property
    def STATE_REJECTED(self):
        """Message constant 'STATE_REJECTED'."""
        return Metaclass_NavigationSessionStatus.__constants['STATE_REJECTED']

    @property
    def STATE_ACCEPTED(self):
        """Message constant 'STATE_ACCEPTED'."""
        return Metaclass_NavigationSessionStatus.__constants['STATE_ACCEPTED']

    @property
    def STATE_RUNNING(self):
        """Message constant 'STATE_RUNNING'."""
        return Metaclass_NavigationSessionStatus.__constants['STATE_RUNNING']

    @property
    def STATE_CANCELING(self):
        """Message constant 'STATE_CANCELING'."""
        return Metaclass_NavigationSessionStatus.__constants['STATE_CANCELING']

    @property
    def STATE_SUCCEEDED(self):
        """Message constant 'STATE_SUCCEEDED'."""
        return Metaclass_NavigationSessionStatus.__constants['STATE_SUCCEEDED']

    @property
    def STATE_FAILED(self):
        """Message constant 'STATE_FAILED'."""
        return Metaclass_NavigationSessionStatus.__constants['STATE_FAILED']

    @property
    def STATE_CANCELED(self):
        """Message constant 'STATE_CANCELED'."""
        return Metaclass_NavigationSessionStatus.__constants['STATE_CANCELED']


class NavigationSessionStatus(metaclass=Metaclass_NavigationSessionStatus):
    """
    Message class 'NavigationSessionStatus'.

    Constants:
      STATE_IDLE
      STATE_VALIDATING
      STATE_REJECTED
      STATE_ACCEPTED
      STATE_RUNNING
      STATE_CANCELING
      STATE_SUCCEEDED
      STATE_FAILED
      STATE_CANCELED
    """

    __slots__ = [
        '_header',
        '_session_id',
        '_client_request_id',
        '_map_id',
        '_map_version_id',
        '_task_group_id',
        '_task_revision',
        '_task_content_sha256',
        '_state',
        '_loop_index',
        '_current_waypoint',
        '_total_waypoints',
        '_missed_waypoints',
        '_error_code',
        '_blocker_code',
        '_operator_message',
        '_technical_message',
        '_started_at',
        '_updated_at',
        '_terminal',
        '_success',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'session_id': 'string',
        'client_request_id': 'string',
        'map_id': 'string',
        'map_version_id': 'string',
        'task_group_id': 'string',
        'task_revision': 'uint32',
        'task_content_sha256': 'string',
        'state': 'uint8',
        'loop_index': 'uint32',
        'current_waypoint': 'uint32',
        'total_waypoints': 'uint32',
        'missed_waypoints': 'sequence<uint32>',
        'error_code': 'uint16',
        'blocker_code': 'string',
        'operator_message': 'string',
        'technical_message': 'string',
        'started_at': 'builtin_interfaces/Time',
        'updated_at': 'builtin_interfaces/Time',
        'terminal': 'boolean',
        'success': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('uint32')),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.session_id = kwargs.get('session_id', str())
        self.client_request_id = kwargs.get('client_request_id', str())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.task_group_id = kwargs.get('task_group_id', str())
        self.task_revision = kwargs.get('task_revision', int())
        self.task_content_sha256 = kwargs.get('task_content_sha256', str())
        self.state = kwargs.get('state', int())
        self.loop_index = kwargs.get('loop_index', int())
        self.current_waypoint = kwargs.get('current_waypoint', int())
        self.total_waypoints = kwargs.get('total_waypoints', int())
        self.missed_waypoints = array.array('I', kwargs.get('missed_waypoints', []))
        self.error_code = kwargs.get('error_code', int())
        self.blocker_code = kwargs.get('blocker_code', str())
        self.operator_message = kwargs.get('operator_message', str())
        self.technical_message = kwargs.get('technical_message', str())
        from builtin_interfaces.msg import Time
        self.started_at = kwargs.get('started_at', Time())
        from builtin_interfaces.msg import Time
        self.updated_at = kwargs.get('updated_at', Time())
        self.terminal = kwargs.get('terminal', bool())
        self.success = kwargs.get('success', bool())

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
        if self.session_id != other.session_id:
            return False
        if self.client_request_id != other.client_request_id:
            return False
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.task_group_id != other.task_group_id:
            return False
        if self.task_revision != other.task_revision:
            return False
        if self.task_content_sha256 != other.task_content_sha256:
            return False
        if self.state != other.state:
            return False
        if self.loop_index != other.loop_index:
            return False
        if self.current_waypoint != other.current_waypoint:
            return False
        if self.total_waypoints != other.total_waypoints:
            return False
        if self.missed_waypoints != other.missed_waypoints:
            return False
        if self.error_code != other.error_code:
            return False
        if self.blocker_code != other.blocker_code:
            return False
        if self.operator_message != other.operator_message:
            return False
        if self.technical_message != other.technical_message:
            return False
        if self.started_at != other.started_at:
            return False
        if self.updated_at != other.updated_at:
            return False
        if self.terminal != other.terminal:
            return False
        if self.success != other.success:
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
    def session_id(self):
        """Message field 'session_id'."""
        return self._session_id

    @session_id.setter
    def session_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'session_id' field must be of type 'str'"
        self._session_id = value

    @builtins.property
    def client_request_id(self):
        """Message field 'client_request_id'."""
        return self._client_request_id

    @client_request_id.setter
    def client_request_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'client_request_id' field must be of type 'str'"
        self._client_request_id = value

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
    def task_group_id(self):
        """Message field 'task_group_id'."""
        return self._task_group_id

    @task_group_id.setter
    def task_group_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'task_group_id' field must be of type 'str'"
        self._task_group_id = value

    @builtins.property
    def task_revision(self):
        """Message field 'task_revision'."""
        return self._task_revision

    @task_revision.setter
    def task_revision(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'task_revision' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'task_revision' field must be an unsigned integer in [0, 4294967295]"
        self._task_revision = value

    @builtins.property
    def task_content_sha256(self):
        """Message field 'task_content_sha256'."""
        return self._task_content_sha256

    @task_content_sha256.setter
    def task_content_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'task_content_sha256' field must be of type 'str'"
        self._task_content_sha256 = value

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
    def loop_index(self):
        """Message field 'loop_index'."""
        return self._loop_index

    @loop_index.setter
    def loop_index(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'loop_index' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'loop_index' field must be an unsigned integer in [0, 4294967295]"
        self._loop_index = value

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
    def missed_waypoints(self):
        """Message field 'missed_waypoints'."""
        return self._missed_waypoints

    @missed_waypoints.setter
    def missed_waypoints(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'I', \
                "The 'missed_waypoints' array.array() must have the type code of 'I'"
            self._missed_waypoints = value
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
                 all(val >= 0 and val < 4294967296 for val in value)), \
                "The 'missed_waypoints' field must be a set or sequence and each value of type 'int' and each unsigned integer in [0, 4294967295]"
        self._missed_waypoints = array.array('I', value)

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
    def blocker_code(self):
        """Message field 'blocker_code'."""
        return self._blocker_code

    @blocker_code.setter
    def blocker_code(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'blocker_code' field must be of type 'str'"
        self._blocker_code = value

    @builtins.property
    def operator_message(self):
        """Message field 'operator_message'."""
        return self._operator_message

    @operator_message.setter
    def operator_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'operator_message' field must be of type 'str'"
        self._operator_message = value

    @builtins.property
    def technical_message(self):
        """Message field 'technical_message'."""
        return self._technical_message

    @technical_message.setter
    def technical_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'technical_message' field must be of type 'str'"
        self._technical_message = value

    @builtins.property
    def started_at(self):
        """Message field 'started_at'."""
        return self._started_at

    @started_at.setter
    def started_at(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'started_at' field must be a sub message of type 'Time'"
        self._started_at = value

    @builtins.property
    def updated_at(self):
        """Message field 'updated_at'."""
        return self._updated_at

    @updated_at.setter
    def updated_at(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'updated_at' field must be a sub message of type 'Time'"
        self._updated_at = value

    @builtins.property
    def terminal(self):
        """Message field 'terminal'."""
        return self._terminal

    @terminal.setter
    def terminal(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'terminal' field must be of type 'bool'"
        self._terminal = value

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
