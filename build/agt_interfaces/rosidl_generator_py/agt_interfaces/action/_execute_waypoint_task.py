# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:action/ExecuteWaypointTask.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ExecuteWaypointTask_Goal(type):
    """Metaclass of message 'ExecuteWaypointTask_Goal'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_Goal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_waypoint_task__goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_waypoint_task__goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_waypoint_task__goal
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_waypoint_task__goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_waypoint_task__goal

            from geometry_msgs.msg import PoseStamped
            if PoseStamped.__class__._TYPE_SUPPORT is None:
                PoseStamped.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteWaypointTask_Goal(metaclass=Metaclass_ExecuteWaypointTask_Goal):
    """Message class 'ExecuteWaypointTask_Goal'."""

    __slots__ = [
        '_map_id',
        '_map_version_id',
        '_task_group_id',
        '_task_revision',
        '_expected_content_sha256',
        '_loop_count',
        '_client_request_id',
        '_task_file',
        '_poses',
        '_loop',
    ]

    _fields_and_field_types = {
        'map_id': 'string',
        'map_version_id': 'string',
        'task_group_id': 'string',
        'task_revision': 'uint32',
        'expected_content_sha256': 'string',
        'loop_count': 'uint32',
        'client_request_id': 'string',
        'task_file': 'string',
        'poses': 'sequence<geometry_msgs/PoseStamped>',
        'loop': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PoseStamped')),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.task_group_id = kwargs.get('task_group_id', str())
        self.task_revision = kwargs.get('task_revision', int())
        self.expected_content_sha256 = kwargs.get('expected_content_sha256', str())
        self.loop_count = kwargs.get('loop_count', int())
        self.client_request_id = kwargs.get('client_request_id', str())
        self.task_file = kwargs.get('task_file', str())
        self.poses = kwargs.get('poses', [])
        self.loop = kwargs.get('loop', bool())

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
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.task_group_id != other.task_group_id:
            return False
        if self.task_revision != other.task_revision:
            return False
        if self.expected_content_sha256 != other.expected_content_sha256:
            return False
        if self.loop_count != other.loop_count:
            return False
        if self.client_request_id != other.client_request_id:
            return False
        if self.task_file != other.task_file:
            return False
        if self.poses != other.poses:
            return False
        if self.loop != other.loop:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

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
    def expected_content_sha256(self):
        """Message field 'expected_content_sha256'."""
        return self._expected_content_sha256

    @expected_content_sha256.setter
    def expected_content_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'expected_content_sha256' field must be of type 'str'"
        self._expected_content_sha256 = value

    @builtins.property
    def loop_count(self):
        """Message field 'loop_count'."""
        return self._loop_count

    @loop_count.setter
    def loop_count(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'loop_count' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'loop_count' field must be an unsigned integer in [0, 4294967295]"
        self._loop_count = value

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
    def task_file(self):
        """Message field 'task_file'."""
        return self._task_file

    @task_file.setter
    def task_file(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'task_file' field must be of type 'str'"
        self._task_file = value

    @builtins.property
    def poses(self):
        """Message field 'poses'."""
        return self._poses

    @poses.setter
    def poses(self, value):
        if __debug__:
            from geometry_msgs.msg import PoseStamped
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
                 all(isinstance(v, PoseStamped) for v in value) and
                 True), \
                "The 'poses' field must be a set or sequence and each value of type 'PoseStamped'"
        self._poses = value

    @builtins.property
    def loop(self):
        """Message field 'loop'."""
        return self._loop

    @loop.setter
    def loop(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'loop' field must be of type 'bool'"
        self._loop = value


# Import statements for member types

# Member 'missed_waypoints'
import array  # noqa: E402, I100

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteWaypointTask_Result(type):
    """Metaclass of message 'ExecuteWaypointTask_Result'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_Result')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_waypoint_task__result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_waypoint_task__result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_waypoint_task__result
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_waypoint_task__result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_waypoint_task__result

            from agt_interfaces.msg import NavigationSessionStatus
            if NavigationSessionStatus.__class__._TYPE_SUPPORT is None:
                NavigationSessionStatus.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteWaypointTask_Result(metaclass=Metaclass_ExecuteWaypointTask_Result):
    """Message class 'ExecuteWaypointTask_Result'."""

    __slots__ = [
        '_success',
        '_error_code',
        '_message',
        '_session_id',
        '_blocker_code',
        '_operator_message',
        '_technical_message',
        '_duplicate_request',
        '_missed_waypoints',
        '_final_status',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'message': 'string',
        'session_id': 'string',
        'blocker_code': 'string',
        'operator_message': 'string',
        'technical_message': 'string',
        'duplicate_request': 'boolean',
        'missed_waypoints': 'sequence<int32>',
        'final_status': 'agt_interfaces/NavigationSessionStatus',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'NavigationSessionStatus'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        self.message = kwargs.get('message', str())
        self.session_id = kwargs.get('session_id', str())
        self.blocker_code = kwargs.get('blocker_code', str())
        self.operator_message = kwargs.get('operator_message', str())
        self.technical_message = kwargs.get('technical_message', str())
        self.duplicate_request = kwargs.get('duplicate_request', bool())
        self.missed_waypoints = array.array('i', kwargs.get('missed_waypoints', []))
        from agt_interfaces.msg import NavigationSessionStatus
        self.final_status = kwargs.get('final_status', NavigationSessionStatus())

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
        if self.message != other.message:
            return False
        if self.session_id != other.session_id:
            return False
        if self.blocker_code != other.blocker_code:
            return False
        if self.operator_message != other.operator_message:
            return False
        if self.technical_message != other.technical_message:
            return False
        if self.duplicate_request != other.duplicate_request:
            return False
        if self.missed_waypoints != other.missed_waypoints:
            return False
        if self.final_status != other.final_status:
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
    def duplicate_request(self):
        """Message field 'duplicate_request'."""
        return self._duplicate_request

    @duplicate_request.setter
    def duplicate_request(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'duplicate_request' field must be of type 'bool'"
        self._duplicate_request = value

    @builtins.property
    def missed_waypoints(self):
        """Message field 'missed_waypoints'."""
        return self._missed_waypoints

    @missed_waypoints.setter
    def missed_waypoints(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'i', \
                "The 'missed_waypoints' array.array() must have the type code of 'i'"
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
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'missed_waypoints' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._missed_waypoints = array.array('i', value)

    @builtins.property
    def final_status(self):
        """Message field 'final_status'."""
        return self._final_status

    @final_status.setter
    def final_status(self, value):
        if __debug__:
            from agt_interfaces.msg import NavigationSessionStatus
            assert \
                isinstance(value, NavigationSessionStatus), \
                "The 'final_status' field must be a sub message of type 'NavigationSessionStatus'"
        self._final_status = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteWaypointTask_Feedback(type):
    """Metaclass of message 'ExecuteWaypointTask_Feedback'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_Feedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_waypoint_task__feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_waypoint_task__feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_waypoint_task__feedback
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_waypoint_task__feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_waypoint_task__feedback

            from agt_interfaces.msg import NavigationSessionStatus
            if NavigationSessionStatus.__class__._TYPE_SUPPORT is None:
                NavigationSessionStatus.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteWaypointTask_Feedback(metaclass=Metaclass_ExecuteWaypointTask_Feedback):
    """Message class 'ExecuteWaypointTask_Feedback'."""

    __slots__ = [
        '_state',
        '_loop_index',
        '_current_waypoint',
        '_total_waypoints',
        '_status',
    ]

    _fields_and_field_types = {
        'state': 'string',
        'loop_index': 'uint32',
        'current_waypoint': 'uint32',
        'total_waypoints': 'uint32',
        'status': 'agt_interfaces/NavigationSessionStatus',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'NavigationSessionStatus'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.state = kwargs.get('state', str())
        self.loop_index = kwargs.get('loop_index', int())
        self.current_waypoint = kwargs.get('current_waypoint', int())
        self.total_waypoints = kwargs.get('total_waypoints', int())
        from agt_interfaces.msg import NavigationSessionStatus
        self.status = kwargs.get('status', NavigationSessionStatus())

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
        if self.loop_index != other.loop_index:
            return False
        if self.current_waypoint != other.current_waypoint:
            return False
        if self.total_waypoints != other.total_waypoints:
            return False
        if self.status != other.status:
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
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            from agt_interfaces.msg import NavigationSessionStatus
            assert \
                isinstance(value, NavigationSessionStatus), \
                "The 'status' field must be a sub message of type 'NavigationSessionStatus'"
        self._status = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteWaypointTask_SendGoal_Request(type):
    """Metaclass of message 'ExecuteWaypointTask_SendGoal_Request'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_SendGoal_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_waypoint_task__send_goal__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_waypoint_task__send_goal__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_waypoint_task__send_goal__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_waypoint_task__send_goal__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_waypoint_task__send_goal__request

            from agt_interfaces.action import ExecuteWaypointTask
            if ExecuteWaypointTask.Goal.__class__._TYPE_SUPPORT is None:
                ExecuteWaypointTask.Goal.__class__.__import_type_support__()

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


class ExecuteWaypointTask_SendGoal_Request(metaclass=Metaclass_ExecuteWaypointTask_SendGoal_Request):
    """Message class 'ExecuteWaypointTask_SendGoal_Request'."""

    __slots__ = [
        '_goal_id',
        '_goal',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'goal': 'agt_interfaces/ExecuteWaypointTask_Goal',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ExecuteWaypointTask_Goal'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_Goal
        self.goal = kwargs.get('goal', ExecuteWaypointTask_Goal())

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
            from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_Goal
            assert \
                isinstance(value, ExecuteWaypointTask_Goal), \
                "The 'goal' field must be a sub message of type 'ExecuteWaypointTask_Goal'"
        self._goal = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteWaypointTask_SendGoal_Response(type):
    """Metaclass of message 'ExecuteWaypointTask_SendGoal_Response'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_SendGoal_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_waypoint_task__send_goal__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_waypoint_task__send_goal__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_waypoint_task__send_goal__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_waypoint_task__send_goal__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_waypoint_task__send_goal__response

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


class ExecuteWaypointTask_SendGoal_Response(metaclass=Metaclass_ExecuteWaypointTask_SendGoal_Response):
    """Message class 'ExecuteWaypointTask_SendGoal_Response'."""

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


class Metaclass_ExecuteWaypointTask_SendGoal(type):
    """Metaclass of service 'ExecuteWaypointTask_SendGoal'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_SendGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__execute_waypoint_task__send_goal

            from agt_interfaces.action import _execute_waypoint_task
            if _execute_waypoint_task.Metaclass_ExecuteWaypointTask_SendGoal_Request._TYPE_SUPPORT is None:
                _execute_waypoint_task.Metaclass_ExecuteWaypointTask_SendGoal_Request.__import_type_support__()
            if _execute_waypoint_task.Metaclass_ExecuteWaypointTask_SendGoal_Response._TYPE_SUPPORT is None:
                _execute_waypoint_task.Metaclass_ExecuteWaypointTask_SendGoal_Response.__import_type_support__()


class ExecuteWaypointTask_SendGoal(metaclass=Metaclass_ExecuteWaypointTask_SendGoal):
    from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_SendGoal_Request as Request
    from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_SendGoal_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteWaypointTask_GetResult_Request(type):
    """Metaclass of message 'ExecuteWaypointTask_GetResult_Request'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_GetResult_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_waypoint_task__get_result__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_waypoint_task__get_result__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_waypoint_task__get_result__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_waypoint_task__get_result__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_waypoint_task__get_result__request

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


class ExecuteWaypointTask_GetResult_Request(metaclass=Metaclass_ExecuteWaypointTask_GetResult_Request):
    """Message class 'ExecuteWaypointTask_GetResult_Request'."""

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


class Metaclass_ExecuteWaypointTask_GetResult_Response(type):
    """Metaclass of message 'ExecuteWaypointTask_GetResult_Response'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_GetResult_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_waypoint_task__get_result__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_waypoint_task__get_result__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_waypoint_task__get_result__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_waypoint_task__get_result__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_waypoint_task__get_result__response

            from agt_interfaces.action import ExecuteWaypointTask
            if ExecuteWaypointTask.Result.__class__._TYPE_SUPPORT is None:
                ExecuteWaypointTask.Result.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteWaypointTask_GetResult_Response(metaclass=Metaclass_ExecuteWaypointTask_GetResult_Response):
    """Message class 'ExecuteWaypointTask_GetResult_Response'."""

    __slots__ = [
        '_status',
        '_result',
    ]

    _fields_and_field_types = {
        'status': 'int8',
        'result': 'agt_interfaces/ExecuteWaypointTask_Result',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ExecuteWaypointTask_Result'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_Result
        self.result = kwargs.get('result', ExecuteWaypointTask_Result())

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
            from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_Result
            assert \
                isinstance(value, ExecuteWaypointTask_Result), \
                "The 'result' field must be a sub message of type 'ExecuteWaypointTask_Result'"
        self._result = value


class Metaclass_ExecuteWaypointTask_GetResult(type):
    """Metaclass of service 'ExecuteWaypointTask_GetResult'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_GetResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__execute_waypoint_task__get_result

            from agt_interfaces.action import _execute_waypoint_task
            if _execute_waypoint_task.Metaclass_ExecuteWaypointTask_GetResult_Request._TYPE_SUPPORT is None:
                _execute_waypoint_task.Metaclass_ExecuteWaypointTask_GetResult_Request.__import_type_support__()
            if _execute_waypoint_task.Metaclass_ExecuteWaypointTask_GetResult_Response._TYPE_SUPPORT is None:
                _execute_waypoint_task.Metaclass_ExecuteWaypointTask_GetResult_Response.__import_type_support__()


class ExecuteWaypointTask_GetResult(metaclass=Metaclass_ExecuteWaypointTask_GetResult):
    from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_GetResult_Request as Request
    from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_GetResult_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteWaypointTask_FeedbackMessage(type):
    """Metaclass of message 'ExecuteWaypointTask_FeedbackMessage'."""

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
                'agt_interfaces.action.ExecuteWaypointTask_FeedbackMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_waypoint_task__feedback_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_waypoint_task__feedback_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_waypoint_task__feedback_message
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_waypoint_task__feedback_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_waypoint_task__feedback_message

            from agt_interfaces.action import ExecuteWaypointTask
            if ExecuteWaypointTask.Feedback.__class__._TYPE_SUPPORT is None:
                ExecuteWaypointTask.Feedback.__class__.__import_type_support__()

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


class ExecuteWaypointTask_FeedbackMessage(metaclass=Metaclass_ExecuteWaypointTask_FeedbackMessage):
    """Message class 'ExecuteWaypointTask_FeedbackMessage'."""

    __slots__ = [
        '_goal_id',
        '_feedback',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'feedback': 'agt_interfaces/ExecuteWaypointTask_Feedback',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ExecuteWaypointTask_Feedback'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_Feedback
        self.feedback = kwargs.get('feedback', ExecuteWaypointTask_Feedback())

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
            from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_Feedback
            assert \
                isinstance(value, ExecuteWaypointTask_Feedback), \
                "The 'feedback' field must be a sub message of type 'ExecuteWaypointTask_Feedback'"
        self._feedback = value


class Metaclass_ExecuteWaypointTask(type):
    """Metaclass of action 'ExecuteWaypointTask'."""

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
                'agt_interfaces.action.ExecuteWaypointTask')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_action__action__execute_waypoint_task

            from action_msgs.msg import _goal_status_array
            if _goal_status_array.Metaclass_GoalStatusArray._TYPE_SUPPORT is None:
                _goal_status_array.Metaclass_GoalStatusArray.__import_type_support__()
            from action_msgs.srv import _cancel_goal
            if _cancel_goal.Metaclass_CancelGoal._TYPE_SUPPORT is None:
                _cancel_goal.Metaclass_CancelGoal.__import_type_support__()

            from agt_interfaces.action import _execute_waypoint_task
            if _execute_waypoint_task.Metaclass_ExecuteWaypointTask_SendGoal._TYPE_SUPPORT is None:
                _execute_waypoint_task.Metaclass_ExecuteWaypointTask_SendGoal.__import_type_support__()
            if _execute_waypoint_task.Metaclass_ExecuteWaypointTask_GetResult._TYPE_SUPPORT is None:
                _execute_waypoint_task.Metaclass_ExecuteWaypointTask_GetResult.__import_type_support__()
            if _execute_waypoint_task.Metaclass_ExecuteWaypointTask_FeedbackMessage._TYPE_SUPPORT is None:
                _execute_waypoint_task.Metaclass_ExecuteWaypointTask_FeedbackMessage.__import_type_support__()


class ExecuteWaypointTask(metaclass=Metaclass_ExecuteWaypointTask):

    # The goal message defined in the action definition.
    from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_Goal as Goal
    # The result message defined in the action definition.
    from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_Result as Result
    # The feedback message defined in the action definition.
    from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_Feedback as Feedback

    class Impl:

        # The send_goal service using a wrapped version of the goal message as a request.
        from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_SendGoal as SendGoalService
        # The get_result service using a wrapped version of the result message as a response.
        from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_GetResult as GetResultService
        # The feedback message with generic fields which wraps the feedback message.
        from agt_interfaces.action._execute_waypoint_task import ExecuteWaypointTask_FeedbackMessage as FeedbackMessage

        # The generic service to cancel a goal.
        from action_msgs.srv._cancel_goal import CancelGoal as CancelGoalService
        # The generic message for get the status of a goal.
        from action_msgs.msg._goal_status_array import GoalStatusArray as GoalStatusMessage

    def __init__(self):
        raise NotImplementedError('Action classes can not be instantiated')
