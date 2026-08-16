# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:action/ExecuteCoverageTask.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ExecuteCoverageTask_Goal(type):
    """Metaclass of message 'ExecuteCoverageTask_Goal'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_Goal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_coverage_task__goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_coverage_task__goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_coverage_task__goal
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_coverage_task__goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_coverage_task__goal

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteCoverageTask_Goal(metaclass=Metaclass_ExecuteCoverageTask_Goal):
    """Message class 'ExecuteCoverageTask_Goal'."""

    __slots__ = [
        '_semantic_map_uri',
        '_field_id',
        '_planning_mode',
        '_controller_id',
        '_allow_repair',
    ]

    _fields_and_field_types = {
        'semantic_map_uri': 'string',
        'field_id': 'string',
        'planning_mode': 'string',
        'controller_id': 'string',
        'allow_repair': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.semantic_map_uri = kwargs.get('semantic_map_uri', str())
        self.field_id = kwargs.get('field_id', str())
        self.planning_mode = kwargs.get('planning_mode', str())
        self.controller_id = kwargs.get('controller_id', str())
        self.allow_repair = kwargs.get('allow_repair', bool())

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
        if self.semantic_map_uri != other.semantic_map_uri:
            return False
        if self.field_id != other.field_id:
            return False
        if self.planning_mode != other.planning_mode:
            return False
        if self.controller_id != other.controller_id:
            return False
        if self.allow_repair != other.allow_repair:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def semantic_map_uri(self):
        """Message field 'semantic_map_uri'."""
        return self._semantic_map_uri

    @semantic_map_uri.setter
    def semantic_map_uri(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'semantic_map_uri' field must be of type 'str'"
        self._semantic_map_uri = value

    @builtins.property
    def field_id(self):
        """Message field 'field_id'."""
        return self._field_id

    @field_id.setter
    def field_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'field_id' field must be of type 'str'"
        self._field_id = value

    @builtins.property
    def planning_mode(self):
        """Message field 'planning_mode'."""
        return self._planning_mode

    @planning_mode.setter
    def planning_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'planning_mode' field must be of type 'str'"
        self._planning_mode = value

    @builtins.property
    def controller_id(self):
        """Message field 'controller_id'."""
        return self._controller_id

    @controller_id.setter
    def controller_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'controller_id' field must be of type 'str'"
        self._controller_id = value

    @builtins.property
    def allow_repair(self):
        """Message field 'allow_repair'."""
        return self._allow_repair

    @allow_repair.setter
    def allow_repair(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'allow_repair' field must be of type 'bool'"
        self._allow_repair = value


# Import statements for member types

# already imported above
# import builtins

import math  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteCoverageTask_Result(type):
    """Metaclass of message 'ExecuteCoverageTask_Result'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_Result')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_coverage_task__result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_coverage_task__result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_coverage_task__result
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_coverage_task__result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_coverage_task__result

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteCoverageTask_Result(metaclass=Metaclass_ExecuteCoverageTask_Result):
    """Message class 'ExecuteCoverageTask_Result'."""

    __slots__ = [
        '_success',
        '_error_code',
        '_message',
        '_coverage_rate',
        '_overlap_rate',
        '_executed_length',
        '_repaired_segment_count',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'message': 'string',
        'coverage_rate': 'double',
        'overlap_rate': 'double',
        'executed_length': 'double',
        'repaired_segment_count': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        self.message = kwargs.get('message', str())
        self.coverage_rate = kwargs.get('coverage_rate', float())
        self.overlap_rate = kwargs.get('overlap_rate', float())
        self.executed_length = kwargs.get('executed_length', float())
        self.repaired_segment_count = kwargs.get('repaired_segment_count', int())

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
        if self.coverage_rate != other.coverage_rate:
            return False
        if self.overlap_rate != other.overlap_rate:
            return False
        if self.executed_length != other.executed_length:
            return False
        if self.repaired_segment_count != other.repaired_segment_count:
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
    def coverage_rate(self):
        """Message field 'coverage_rate'."""
        return self._coverage_rate

    @coverage_rate.setter
    def coverage_rate(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'coverage_rate' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'coverage_rate' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._coverage_rate = value

    @builtins.property
    def overlap_rate(self):
        """Message field 'overlap_rate'."""
        return self._overlap_rate

    @overlap_rate.setter
    def overlap_rate(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'overlap_rate' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'overlap_rate' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._overlap_rate = value

    @builtins.property
    def executed_length(self):
        """Message field 'executed_length'."""
        return self._executed_length

    @executed_length.setter
    def executed_length(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'executed_length' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'executed_length' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._executed_length = value

    @builtins.property
    def repaired_segment_count(self):
        """Message field 'repaired_segment_count'."""
        return self._repaired_segment_count

    @repaired_segment_count.setter
    def repaired_segment_count(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'repaired_segment_count' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'repaired_segment_count' field must be an unsigned integer in [0, 4294967295]"
        self._repaired_segment_count = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import math

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteCoverageTask_Feedback(type):
    """Metaclass of message 'ExecuteCoverageTask_Feedback'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_Feedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_coverage_task__feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_coverage_task__feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_coverage_task__feedback
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_coverage_task__feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_coverage_task__feedback

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteCoverageTask_Feedback(metaclass=Metaclass_ExecuteCoverageTask_Feedback):
    """Message class 'ExecuteCoverageTask_Feedback'."""

    __slots__ = [
        '_current_stage',
        '_current_swath_index',
        '_total_swaths',
        '_distance_remaining',
    ]

    _fields_and_field_types = {
        'current_stage': 'string',
        'current_swath_index': 'uint32',
        'total_swaths': 'uint32',
        'distance_remaining': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.current_stage = kwargs.get('current_stage', str())
        self.current_swath_index = kwargs.get('current_swath_index', int())
        self.total_swaths = kwargs.get('total_swaths', int())
        self.distance_remaining = kwargs.get('distance_remaining', float())

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
        if self.current_stage != other.current_stage:
            return False
        if self.current_swath_index != other.current_swath_index:
            return False
        if self.total_swaths != other.total_swaths:
            return False
        if self.distance_remaining != other.distance_remaining:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def current_stage(self):
        """Message field 'current_stage'."""
        return self._current_stage

    @current_stage.setter
    def current_stage(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'current_stage' field must be of type 'str'"
        self._current_stage = value

    @builtins.property
    def current_swath_index(self):
        """Message field 'current_swath_index'."""
        return self._current_swath_index

    @current_swath_index.setter
    def current_swath_index(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'current_swath_index' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'current_swath_index' field must be an unsigned integer in [0, 4294967295]"
        self._current_swath_index = value

    @builtins.property
    def total_swaths(self):
        """Message field 'total_swaths'."""
        return self._total_swaths

    @total_swaths.setter
    def total_swaths(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'total_swaths' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'total_swaths' field must be an unsigned integer in [0, 4294967295]"
        self._total_swaths = value

    @builtins.property
    def distance_remaining(self):
        """Message field 'distance_remaining'."""
        return self._distance_remaining

    @distance_remaining.setter
    def distance_remaining(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'distance_remaining' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'distance_remaining' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._distance_remaining = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteCoverageTask_SendGoal_Request(type):
    """Metaclass of message 'ExecuteCoverageTask_SendGoal_Request'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_SendGoal_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_coverage_task__send_goal__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_coverage_task__send_goal__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_coverage_task__send_goal__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_coverage_task__send_goal__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_coverage_task__send_goal__request

            from agt_interfaces.action import ExecuteCoverageTask
            if ExecuteCoverageTask.Goal.__class__._TYPE_SUPPORT is None:
                ExecuteCoverageTask.Goal.__class__.__import_type_support__()

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


class ExecuteCoverageTask_SendGoal_Request(metaclass=Metaclass_ExecuteCoverageTask_SendGoal_Request):
    """Message class 'ExecuteCoverageTask_SendGoal_Request'."""

    __slots__ = [
        '_goal_id',
        '_goal',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'goal': 'agt_interfaces/ExecuteCoverageTask_Goal',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ExecuteCoverageTask_Goal'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_Goal
        self.goal = kwargs.get('goal', ExecuteCoverageTask_Goal())

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
            from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_Goal
            assert \
                isinstance(value, ExecuteCoverageTask_Goal), \
                "The 'goal' field must be a sub message of type 'ExecuteCoverageTask_Goal'"
        self._goal = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteCoverageTask_SendGoal_Response(type):
    """Metaclass of message 'ExecuteCoverageTask_SendGoal_Response'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_SendGoal_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_coverage_task__send_goal__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_coverage_task__send_goal__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_coverage_task__send_goal__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_coverage_task__send_goal__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_coverage_task__send_goal__response

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


class ExecuteCoverageTask_SendGoal_Response(metaclass=Metaclass_ExecuteCoverageTask_SendGoal_Response):
    """Message class 'ExecuteCoverageTask_SendGoal_Response'."""

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


class Metaclass_ExecuteCoverageTask_SendGoal(type):
    """Metaclass of service 'ExecuteCoverageTask_SendGoal'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_SendGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__execute_coverage_task__send_goal

            from agt_interfaces.action import _execute_coverage_task
            if _execute_coverage_task.Metaclass_ExecuteCoverageTask_SendGoal_Request._TYPE_SUPPORT is None:
                _execute_coverage_task.Metaclass_ExecuteCoverageTask_SendGoal_Request.__import_type_support__()
            if _execute_coverage_task.Metaclass_ExecuteCoverageTask_SendGoal_Response._TYPE_SUPPORT is None:
                _execute_coverage_task.Metaclass_ExecuteCoverageTask_SendGoal_Response.__import_type_support__()


class ExecuteCoverageTask_SendGoal(metaclass=Metaclass_ExecuteCoverageTask_SendGoal):
    from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_SendGoal_Request as Request
    from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_SendGoal_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteCoverageTask_GetResult_Request(type):
    """Metaclass of message 'ExecuteCoverageTask_GetResult_Request'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_GetResult_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_coverage_task__get_result__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_coverage_task__get_result__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_coverage_task__get_result__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_coverage_task__get_result__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_coverage_task__get_result__request

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


class ExecuteCoverageTask_GetResult_Request(metaclass=Metaclass_ExecuteCoverageTask_GetResult_Request):
    """Message class 'ExecuteCoverageTask_GetResult_Request'."""

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


class Metaclass_ExecuteCoverageTask_GetResult_Response(type):
    """Metaclass of message 'ExecuteCoverageTask_GetResult_Response'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_GetResult_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_coverage_task__get_result__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_coverage_task__get_result__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_coverage_task__get_result__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_coverage_task__get_result__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_coverage_task__get_result__response

            from agt_interfaces.action import ExecuteCoverageTask
            if ExecuteCoverageTask.Result.__class__._TYPE_SUPPORT is None:
                ExecuteCoverageTask.Result.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteCoverageTask_GetResult_Response(metaclass=Metaclass_ExecuteCoverageTask_GetResult_Response):
    """Message class 'ExecuteCoverageTask_GetResult_Response'."""

    __slots__ = [
        '_status',
        '_result',
    ]

    _fields_and_field_types = {
        'status': 'int8',
        'result': 'agt_interfaces/ExecuteCoverageTask_Result',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ExecuteCoverageTask_Result'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_Result
        self.result = kwargs.get('result', ExecuteCoverageTask_Result())

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
            from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_Result
            assert \
                isinstance(value, ExecuteCoverageTask_Result), \
                "The 'result' field must be a sub message of type 'ExecuteCoverageTask_Result'"
        self._result = value


class Metaclass_ExecuteCoverageTask_GetResult(type):
    """Metaclass of service 'ExecuteCoverageTask_GetResult'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_GetResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__execute_coverage_task__get_result

            from agt_interfaces.action import _execute_coverage_task
            if _execute_coverage_task.Metaclass_ExecuteCoverageTask_GetResult_Request._TYPE_SUPPORT is None:
                _execute_coverage_task.Metaclass_ExecuteCoverageTask_GetResult_Request.__import_type_support__()
            if _execute_coverage_task.Metaclass_ExecuteCoverageTask_GetResult_Response._TYPE_SUPPORT is None:
                _execute_coverage_task.Metaclass_ExecuteCoverageTask_GetResult_Response.__import_type_support__()


class ExecuteCoverageTask_GetResult(metaclass=Metaclass_ExecuteCoverageTask_GetResult):
    from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_GetResult_Request as Request
    from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_GetResult_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteCoverageTask_FeedbackMessage(type):
    """Metaclass of message 'ExecuteCoverageTask_FeedbackMessage'."""

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
                'agt_interfaces.action.ExecuteCoverageTask_FeedbackMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_coverage_task__feedback_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_coverage_task__feedback_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_coverage_task__feedback_message
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_coverage_task__feedback_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_coverage_task__feedback_message

            from agt_interfaces.action import ExecuteCoverageTask
            if ExecuteCoverageTask.Feedback.__class__._TYPE_SUPPORT is None:
                ExecuteCoverageTask.Feedback.__class__.__import_type_support__()

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


class ExecuteCoverageTask_FeedbackMessage(metaclass=Metaclass_ExecuteCoverageTask_FeedbackMessage):
    """Message class 'ExecuteCoverageTask_FeedbackMessage'."""

    __slots__ = [
        '_goal_id',
        '_feedback',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'feedback': 'agt_interfaces/ExecuteCoverageTask_Feedback',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ExecuteCoverageTask_Feedback'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_Feedback
        self.feedback = kwargs.get('feedback', ExecuteCoverageTask_Feedback())

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
            from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_Feedback
            assert \
                isinstance(value, ExecuteCoverageTask_Feedback), \
                "The 'feedback' field must be a sub message of type 'ExecuteCoverageTask_Feedback'"
        self._feedback = value


class Metaclass_ExecuteCoverageTask(type):
    """Metaclass of action 'ExecuteCoverageTask'."""

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
                'agt_interfaces.action.ExecuteCoverageTask')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_action__action__execute_coverage_task

            from action_msgs.msg import _goal_status_array
            if _goal_status_array.Metaclass_GoalStatusArray._TYPE_SUPPORT is None:
                _goal_status_array.Metaclass_GoalStatusArray.__import_type_support__()
            from action_msgs.srv import _cancel_goal
            if _cancel_goal.Metaclass_CancelGoal._TYPE_SUPPORT is None:
                _cancel_goal.Metaclass_CancelGoal.__import_type_support__()

            from agt_interfaces.action import _execute_coverage_task
            if _execute_coverage_task.Metaclass_ExecuteCoverageTask_SendGoal._TYPE_SUPPORT is None:
                _execute_coverage_task.Metaclass_ExecuteCoverageTask_SendGoal.__import_type_support__()
            if _execute_coverage_task.Metaclass_ExecuteCoverageTask_GetResult._TYPE_SUPPORT is None:
                _execute_coverage_task.Metaclass_ExecuteCoverageTask_GetResult.__import_type_support__()
            if _execute_coverage_task.Metaclass_ExecuteCoverageTask_FeedbackMessage._TYPE_SUPPORT is None:
                _execute_coverage_task.Metaclass_ExecuteCoverageTask_FeedbackMessage.__import_type_support__()


class ExecuteCoverageTask(metaclass=Metaclass_ExecuteCoverageTask):

    # The goal message defined in the action definition.
    from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_Goal as Goal
    # The result message defined in the action definition.
    from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_Result as Result
    # The feedback message defined in the action definition.
    from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_Feedback as Feedback

    class Impl:

        # The send_goal service using a wrapped version of the goal message as a request.
        from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_SendGoal as SendGoalService
        # The get_result service using a wrapped version of the result message as a response.
        from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_GetResult as GetResultService
        # The feedback message with generic fields which wraps the feedback message.
        from agt_interfaces.action._execute_coverage_task import ExecuteCoverageTask_FeedbackMessage as FeedbackMessage

        # The generic service to cancel a goal.
        from action_msgs.srv._cancel_goal import CancelGoal as CancelGoalService
        # The generic message for get the status of a goal.
        from action_msgs.msg._goal_status_array import GoalStatusArray as GoalStatusMessage

    def __init__(self):
        raise NotImplementedError('Action classes can not be instantiated')
