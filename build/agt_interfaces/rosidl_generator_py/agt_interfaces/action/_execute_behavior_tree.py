# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:action/ExecuteBehaviorTree.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ExecuteBehaviorTree_Goal(type):
    """Metaclass of message 'ExecuteBehaviorTree_Goal'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ERROR_NONE': 0,
        'ERROR_INVALID_REQUEST': 1,
        'ERROR_TREE_NOT_ALLOWED': 2,
        'ERROR_TREE_FAILED': 3,
        'ERROR_CANCELED': 4,
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
                'agt_interfaces.action.ExecuteBehaviorTree_Goal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_behavior_tree__goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_behavior_tree__goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_behavior_tree__goal
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_behavior_tree__goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_behavior_tree__goal

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_INVALID_REQUEST': cls.__constants['ERROR_INVALID_REQUEST'],
            'ERROR_TREE_NOT_ALLOWED': cls.__constants['ERROR_TREE_NOT_ALLOWED'],
            'ERROR_TREE_FAILED': cls.__constants['ERROR_TREE_FAILED'],
            'ERROR_CANCELED': cls.__constants['ERROR_CANCELED'],
            'ERROR_INTERNAL': cls.__constants['ERROR_INTERNAL'],
        }

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_ExecuteBehaviorTree_Goal.__constants['ERROR_NONE']

    @property
    def ERROR_INVALID_REQUEST(self):
        """Message constant 'ERROR_INVALID_REQUEST'."""
        return Metaclass_ExecuteBehaviorTree_Goal.__constants['ERROR_INVALID_REQUEST']

    @property
    def ERROR_TREE_NOT_ALLOWED(self):
        """Message constant 'ERROR_TREE_NOT_ALLOWED'."""
        return Metaclass_ExecuteBehaviorTree_Goal.__constants['ERROR_TREE_NOT_ALLOWED']

    @property
    def ERROR_TREE_FAILED(self):
        """Message constant 'ERROR_TREE_FAILED'."""
        return Metaclass_ExecuteBehaviorTree_Goal.__constants['ERROR_TREE_FAILED']

    @property
    def ERROR_CANCELED(self):
        """Message constant 'ERROR_CANCELED'."""
        return Metaclass_ExecuteBehaviorTree_Goal.__constants['ERROR_CANCELED']

    @property
    def ERROR_INTERNAL(self):
        """Message constant 'ERROR_INTERNAL'."""
        return Metaclass_ExecuteBehaviorTree_Goal.__constants['ERROR_INTERNAL']


class ExecuteBehaviorTree_Goal(metaclass=Metaclass_ExecuteBehaviorTree_Goal):
    """
    Message class 'ExecuteBehaviorTree_Goal'.

    Constants:
      ERROR_NONE
      ERROR_INVALID_REQUEST
      ERROR_TREE_NOT_ALLOWED
      ERROR_TREE_FAILED
      ERROR_CANCELED
      ERROR_INTERNAL
    """

    __slots__ = [
        '_tree_id',
        '_execution_id',
        '_map_id',
        '_map_version_id',
        '_task_group_id',
        '_task_revision',
        '_expected_content_sha256',
        '_loop_count',
        '_client_request_id',
    ]

    _fields_and_field_types = {
        'tree_id': 'string',
        'execution_id': 'string',
        'map_id': 'string',
        'map_version_id': 'string',
        'task_group_id': 'string',
        'task_revision': 'uint32',
        'expected_content_sha256': 'string',
        'loop_count': 'uint32',
        'client_request_id': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.tree_id = kwargs.get('tree_id', str())
        self.execution_id = kwargs.get('execution_id', str())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.task_group_id = kwargs.get('task_group_id', str())
        self.task_revision = kwargs.get('task_revision', int())
        self.expected_content_sha256 = kwargs.get('expected_content_sha256', str())
        self.loop_count = kwargs.get('loop_count', int())
        self.client_request_id = kwargs.get('client_request_id', str())

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
        if self.tree_id != other.tree_id:
            return False
        if self.execution_id != other.execution_id:
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
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def tree_id(self):
        """Message field 'tree_id'."""
        return self._tree_id

    @tree_id.setter
    def tree_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'tree_id' field must be of type 'str'"
        self._tree_id = value

    @builtins.property
    def execution_id(self):
        """Message field 'execution_id'."""
        return self._execution_id

    @execution_id.setter
    def execution_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'execution_id' field must be of type 'str'"
        self._execution_id = value

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteBehaviorTree_Result(type):
    """Metaclass of message 'ExecuteBehaviorTree_Result'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree_Result')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_behavior_tree__result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_behavior_tree__result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_behavior_tree__result
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_behavior_tree__result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_behavior_tree__result

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteBehaviorTree_Result(metaclass=Metaclass_ExecuteBehaviorTree_Result):
    """Message class 'ExecuteBehaviorTree_Result'."""

    __slots__ = [
        '_success',
        '_error_code',
        '_message',
        '_blocker_code',
        '_blocker_message',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'message': 'string',
        'blocker_code': 'string',
        'blocker_message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        self.message = kwargs.get('message', str())
        self.blocker_code = kwargs.get('blocker_code', str())
        self.blocker_message = kwargs.get('blocker_message', str())

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
        if self.blocker_code != other.blocker_code:
            return False
        if self.blocker_message != other.blocker_message:
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
    def blocker_message(self):
        """Message field 'blocker_message'."""
        return self._blocker_message

    @blocker_message.setter
    def blocker_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'blocker_message' field must be of type 'str'"
        self._blocker_message = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteBehaviorTree_Feedback(type):
    """Metaclass of message 'ExecuteBehaviorTree_Feedback'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree_Feedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_behavior_tree__feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_behavior_tree__feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_behavior_tree__feedback
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_behavior_tree__feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_behavior_tree__feedback

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteBehaviorTree_Feedback(metaclass=Metaclass_ExecuteBehaviorTree_Feedback):
    """Message class 'ExecuteBehaviorTree_Feedback'."""

    __slots__ = [
        '_tree_state',
        '_active_node',
        '_loop_index',
        '_current_waypoint',
        '_total_waypoints',
    ]

    _fields_and_field_types = {
        'tree_state': 'string',
        'active_node': 'string',
        'loop_index': 'uint32',
        'current_waypoint': 'uint32',
        'total_waypoints': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.tree_state = kwargs.get('tree_state', str())
        self.active_node = kwargs.get('active_node', str())
        self.loop_index = kwargs.get('loop_index', int())
        self.current_waypoint = kwargs.get('current_waypoint', int())
        self.total_waypoints = kwargs.get('total_waypoints', int())

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
        if self.tree_state != other.tree_state:
            return False
        if self.active_node != other.active_node:
            return False
        if self.loop_index != other.loop_index:
            return False
        if self.current_waypoint != other.current_waypoint:
            return False
        if self.total_waypoints != other.total_waypoints:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def tree_state(self):
        """Message field 'tree_state'."""
        return self._tree_state

    @tree_state.setter
    def tree_state(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'tree_state' field must be of type 'str'"
        self._tree_state = value

    @builtins.property
    def active_node(self):
        """Message field 'active_node'."""
        return self._active_node

    @active_node.setter
    def active_node(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'active_node' field must be of type 'str'"
        self._active_node = value

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteBehaviorTree_SendGoal_Request(type):
    """Metaclass of message 'ExecuteBehaviorTree_SendGoal_Request'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree_SendGoal_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_behavior_tree__send_goal__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_behavior_tree__send_goal__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_behavior_tree__send_goal__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_behavior_tree__send_goal__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_behavior_tree__send_goal__request

            from agt_interfaces.action import ExecuteBehaviorTree
            if ExecuteBehaviorTree.Goal.__class__._TYPE_SUPPORT is None:
                ExecuteBehaviorTree.Goal.__class__.__import_type_support__()

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


class ExecuteBehaviorTree_SendGoal_Request(metaclass=Metaclass_ExecuteBehaviorTree_SendGoal_Request):
    """Message class 'ExecuteBehaviorTree_SendGoal_Request'."""

    __slots__ = [
        '_goal_id',
        '_goal',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'goal': 'agt_interfaces/ExecuteBehaviorTree_Goal',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ExecuteBehaviorTree_Goal'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_Goal
        self.goal = kwargs.get('goal', ExecuteBehaviorTree_Goal())

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
            from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_Goal
            assert \
                isinstance(value, ExecuteBehaviorTree_Goal), \
                "The 'goal' field must be a sub message of type 'ExecuteBehaviorTree_Goal'"
        self._goal = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteBehaviorTree_SendGoal_Response(type):
    """Metaclass of message 'ExecuteBehaviorTree_SendGoal_Response'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree_SendGoal_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_behavior_tree__send_goal__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_behavior_tree__send_goal__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_behavior_tree__send_goal__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_behavior_tree__send_goal__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_behavior_tree__send_goal__response

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


class ExecuteBehaviorTree_SendGoal_Response(metaclass=Metaclass_ExecuteBehaviorTree_SendGoal_Response):
    """Message class 'ExecuteBehaviorTree_SendGoal_Response'."""

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


class Metaclass_ExecuteBehaviorTree_SendGoal(type):
    """Metaclass of service 'ExecuteBehaviorTree_SendGoal'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree_SendGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__execute_behavior_tree__send_goal

            from agt_interfaces.action import _execute_behavior_tree
            if _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_SendGoal_Request._TYPE_SUPPORT is None:
                _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_SendGoal_Request.__import_type_support__()
            if _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_SendGoal_Response._TYPE_SUPPORT is None:
                _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_SendGoal_Response.__import_type_support__()


class ExecuteBehaviorTree_SendGoal(metaclass=Metaclass_ExecuteBehaviorTree_SendGoal):
    from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_SendGoal_Request as Request
    from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_SendGoal_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteBehaviorTree_GetResult_Request(type):
    """Metaclass of message 'ExecuteBehaviorTree_GetResult_Request'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree_GetResult_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_behavior_tree__get_result__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_behavior_tree__get_result__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_behavior_tree__get_result__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_behavior_tree__get_result__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_behavior_tree__get_result__request

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


class ExecuteBehaviorTree_GetResult_Request(metaclass=Metaclass_ExecuteBehaviorTree_GetResult_Request):
    """Message class 'ExecuteBehaviorTree_GetResult_Request'."""

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


class Metaclass_ExecuteBehaviorTree_GetResult_Response(type):
    """Metaclass of message 'ExecuteBehaviorTree_GetResult_Response'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree_GetResult_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_behavior_tree__get_result__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_behavior_tree__get_result__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_behavior_tree__get_result__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_behavior_tree__get_result__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_behavior_tree__get_result__response

            from agt_interfaces.action import ExecuteBehaviorTree
            if ExecuteBehaviorTree.Result.__class__._TYPE_SUPPORT is None:
                ExecuteBehaviorTree.Result.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteBehaviorTree_GetResult_Response(metaclass=Metaclass_ExecuteBehaviorTree_GetResult_Response):
    """Message class 'ExecuteBehaviorTree_GetResult_Response'."""

    __slots__ = [
        '_status',
        '_result',
    ]

    _fields_and_field_types = {
        'status': 'int8',
        'result': 'agt_interfaces/ExecuteBehaviorTree_Result',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ExecuteBehaviorTree_Result'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_Result
        self.result = kwargs.get('result', ExecuteBehaviorTree_Result())

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
            from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_Result
            assert \
                isinstance(value, ExecuteBehaviorTree_Result), \
                "The 'result' field must be a sub message of type 'ExecuteBehaviorTree_Result'"
        self._result = value


class Metaclass_ExecuteBehaviorTree_GetResult(type):
    """Metaclass of service 'ExecuteBehaviorTree_GetResult'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree_GetResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__execute_behavior_tree__get_result

            from agt_interfaces.action import _execute_behavior_tree
            if _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_GetResult_Request._TYPE_SUPPORT is None:
                _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_GetResult_Request.__import_type_support__()
            if _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_GetResult_Response._TYPE_SUPPORT is None:
                _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_GetResult_Response.__import_type_support__()


class ExecuteBehaviorTree_GetResult(metaclass=Metaclass_ExecuteBehaviorTree_GetResult):
    from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_GetResult_Request as Request
    from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_GetResult_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteBehaviorTree_FeedbackMessage(type):
    """Metaclass of message 'ExecuteBehaviorTree_FeedbackMessage'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree_FeedbackMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_behavior_tree__feedback_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_behavior_tree__feedback_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_behavior_tree__feedback_message
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_behavior_tree__feedback_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_behavior_tree__feedback_message

            from agt_interfaces.action import ExecuteBehaviorTree
            if ExecuteBehaviorTree.Feedback.__class__._TYPE_SUPPORT is None:
                ExecuteBehaviorTree.Feedback.__class__.__import_type_support__()

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


class ExecuteBehaviorTree_FeedbackMessage(metaclass=Metaclass_ExecuteBehaviorTree_FeedbackMessage):
    """Message class 'ExecuteBehaviorTree_FeedbackMessage'."""

    __slots__ = [
        '_goal_id',
        '_feedback',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'feedback': 'agt_interfaces/ExecuteBehaviorTree_Feedback',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ExecuteBehaviorTree_Feedback'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_Feedback
        self.feedback = kwargs.get('feedback', ExecuteBehaviorTree_Feedback())

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
            from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_Feedback
            assert \
                isinstance(value, ExecuteBehaviorTree_Feedback), \
                "The 'feedback' field must be a sub message of type 'ExecuteBehaviorTree_Feedback'"
        self._feedback = value


class Metaclass_ExecuteBehaviorTree(type):
    """Metaclass of action 'ExecuteBehaviorTree'."""

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
                'agt_interfaces.action.ExecuteBehaviorTree')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_action__action__execute_behavior_tree

            from action_msgs.msg import _goal_status_array
            if _goal_status_array.Metaclass_GoalStatusArray._TYPE_SUPPORT is None:
                _goal_status_array.Metaclass_GoalStatusArray.__import_type_support__()
            from action_msgs.srv import _cancel_goal
            if _cancel_goal.Metaclass_CancelGoal._TYPE_SUPPORT is None:
                _cancel_goal.Metaclass_CancelGoal.__import_type_support__()

            from agt_interfaces.action import _execute_behavior_tree
            if _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_SendGoal._TYPE_SUPPORT is None:
                _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_SendGoal.__import_type_support__()
            if _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_GetResult._TYPE_SUPPORT is None:
                _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_GetResult.__import_type_support__()
            if _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_FeedbackMessage._TYPE_SUPPORT is None:
                _execute_behavior_tree.Metaclass_ExecuteBehaviorTree_FeedbackMessage.__import_type_support__()


class ExecuteBehaviorTree(metaclass=Metaclass_ExecuteBehaviorTree):

    # The goal message defined in the action definition.
    from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_Goal as Goal
    # The result message defined in the action definition.
    from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_Result as Result
    # The feedback message defined in the action definition.
    from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_Feedback as Feedback

    class Impl:

        # The send_goal service using a wrapped version of the goal message as a request.
        from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_SendGoal as SendGoalService
        # The get_result service using a wrapped version of the result message as a response.
        from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_GetResult as GetResultService
        # The feedback message with generic fields which wraps the feedback message.
        from agt_interfaces.action._execute_behavior_tree import ExecuteBehaviorTree_FeedbackMessage as FeedbackMessage

        # The generic service to cancel a goal.
        from action_msgs.srv._cancel_goal import CancelGoal as CancelGoalService
        # The generic message for get the status of a goal.
        from action_msgs.msg._goal_status_array import GoalStatusArray as GoalStatusMessage

    def __init__(self):
        raise NotImplementedError('Action classes can not be instantiated')
