# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:action/Relocalize.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Relocalize_Goal(type):
    """Metaclass of message 'Relocalize_Goal'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'MODE_AUTO_SEARCH': 0,
        'MODE_SINGLE_INITIAL_POSE': 1,
        'MODE_LOCAL_CANDIDATES': 2,
        'MODE_EXTERNAL_COARSE_POSE': 3,
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
                'agt_interfaces.action.Relocalize_Goal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__relocalize__goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__relocalize__goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__relocalize__goal
            cls._TYPE_SUPPORT = module.type_support_msg__action__relocalize__goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__relocalize__goal

            from geometry_msgs.msg import PoseWithCovarianceStamped
            if PoseWithCovarianceStamped.__class__._TYPE_SUPPORT is None:
                PoseWithCovarianceStamped.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'MODE_AUTO_SEARCH': cls.__constants['MODE_AUTO_SEARCH'],
            'MODE_SINGLE_INITIAL_POSE': cls.__constants['MODE_SINGLE_INITIAL_POSE'],
            'MODE_LOCAL_CANDIDATES': cls.__constants['MODE_LOCAL_CANDIDATES'],
            'MODE_EXTERNAL_COARSE_POSE': cls.__constants['MODE_EXTERNAL_COARSE_POSE'],
        }

    @property
    def MODE_AUTO_SEARCH(self):
        """Message constant 'MODE_AUTO_SEARCH'."""
        return Metaclass_Relocalize_Goal.__constants['MODE_AUTO_SEARCH']

    @property
    def MODE_SINGLE_INITIAL_POSE(self):
        """Message constant 'MODE_SINGLE_INITIAL_POSE'."""
        return Metaclass_Relocalize_Goal.__constants['MODE_SINGLE_INITIAL_POSE']

    @property
    def MODE_LOCAL_CANDIDATES(self):
        """Message constant 'MODE_LOCAL_CANDIDATES'."""
        return Metaclass_Relocalize_Goal.__constants['MODE_LOCAL_CANDIDATES']

    @property
    def MODE_EXTERNAL_COARSE_POSE(self):
        """Message constant 'MODE_EXTERNAL_COARSE_POSE'."""
        return Metaclass_Relocalize_Goal.__constants['MODE_EXTERNAL_COARSE_POSE']


class Relocalize_Goal(metaclass=Metaclass_Relocalize_Goal):
    """
    Message class 'Relocalize_Goal'.

    Constants:
      MODE_AUTO_SEARCH
      MODE_SINGLE_INITIAL_POSE
      MODE_LOCAL_CANDIDATES
      MODE_EXTERNAL_COARSE_POSE
    """

    __slots__ = [
        '_mode',
        '_use_initial_pose',
        '_initial_pose',
        '_use_last_valid_pose',
        '_use_configured_candidates',
        '_use_external_coarse_pose',
        '_max_candidates',
        '_publish_debug',
        '_timeout_s',
    ]

    _fields_and_field_types = {
        'mode': 'uint8',
        'use_initial_pose': 'boolean',
        'initial_pose': 'geometry_msgs/PoseWithCovarianceStamped',
        'use_last_valid_pose': 'boolean',
        'use_configured_candidates': 'boolean',
        'use_external_coarse_pose': 'boolean',
        'max_candidates': 'uint32',
        'publish_debug': 'boolean',
        'timeout_s': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PoseWithCovarianceStamped'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.mode = kwargs.get('mode', int())
        self.use_initial_pose = kwargs.get('use_initial_pose', bool())
        from geometry_msgs.msg import PoseWithCovarianceStamped
        self.initial_pose = kwargs.get('initial_pose', PoseWithCovarianceStamped())
        self.use_last_valid_pose = kwargs.get('use_last_valid_pose', bool())
        self.use_configured_candidates = kwargs.get('use_configured_candidates', bool())
        self.use_external_coarse_pose = kwargs.get('use_external_coarse_pose', bool())
        self.max_candidates = kwargs.get('max_candidates', int())
        self.publish_debug = kwargs.get('publish_debug', bool())
        self.timeout_s = kwargs.get('timeout_s', float())

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
        if self.use_initial_pose != other.use_initial_pose:
            return False
        if self.initial_pose != other.initial_pose:
            return False
        if self.use_last_valid_pose != other.use_last_valid_pose:
            return False
        if self.use_configured_candidates != other.use_configured_candidates:
            return False
        if self.use_external_coarse_pose != other.use_external_coarse_pose:
            return False
        if self.max_candidates != other.max_candidates:
            return False
        if self.publish_debug != other.publish_debug:
            return False
        if self.timeout_s != other.timeout_s:
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
    def use_initial_pose(self):
        """Message field 'use_initial_pose'."""
        return self._use_initial_pose

    @use_initial_pose.setter
    def use_initial_pose(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'use_initial_pose' field must be of type 'bool'"
        self._use_initial_pose = value

    @builtins.property
    def initial_pose(self):
        """Message field 'initial_pose'."""
        return self._initial_pose

    @initial_pose.setter
    def initial_pose(self, value):
        if __debug__:
            from geometry_msgs.msg import PoseWithCovarianceStamped
            assert \
                isinstance(value, PoseWithCovarianceStamped), \
                "The 'initial_pose' field must be a sub message of type 'PoseWithCovarianceStamped'"
        self._initial_pose = value

    @builtins.property
    def use_last_valid_pose(self):
        """Message field 'use_last_valid_pose'."""
        return self._use_last_valid_pose

    @use_last_valid_pose.setter
    def use_last_valid_pose(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'use_last_valid_pose' field must be of type 'bool'"
        self._use_last_valid_pose = value

    @builtins.property
    def use_configured_candidates(self):
        """Message field 'use_configured_candidates'."""
        return self._use_configured_candidates

    @use_configured_candidates.setter
    def use_configured_candidates(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'use_configured_candidates' field must be of type 'bool'"
        self._use_configured_candidates = value

    @builtins.property
    def use_external_coarse_pose(self):
        """Message field 'use_external_coarse_pose'."""
        return self._use_external_coarse_pose

    @use_external_coarse_pose.setter
    def use_external_coarse_pose(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'use_external_coarse_pose' field must be of type 'bool'"
        self._use_external_coarse_pose = value

    @builtins.property
    def max_candidates(self):
        """Message field 'max_candidates'."""
        return self._max_candidates

    @max_candidates.setter
    def max_candidates(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'max_candidates' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'max_candidates' field must be an unsigned integer in [0, 4294967295]"
        self._max_candidates = value

    @builtins.property
    def publish_debug(self):
        """Message field 'publish_debug'."""
        return self._publish_debug

    @publish_debug.setter
    def publish_debug(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'publish_debug' field must be of type 'bool'"
        self._publish_debug = value

    @builtins.property
    def timeout_s(self):
        """Message field 'timeout_s'."""
        return self._timeout_s

    @timeout_s.setter
    def timeout_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'timeout_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'timeout_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._timeout_s = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Relocalize_Result(type):
    """Metaclass of message 'Relocalize_Result'."""

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
                'agt_interfaces.action.Relocalize_Result')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__relocalize__result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__relocalize__result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__relocalize__result
            cls._TYPE_SUPPORT = module.type_support_msg__action__relocalize__result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__relocalize__result

            from agt_interfaces.msg import LocalizationStatus
            if LocalizationStatus.__class__._TYPE_SUPPORT is None:
                LocalizationStatus.__class__.__import_type_support__()

            from geometry_msgs.msg import PoseWithCovarianceStamped
            if PoseWithCovarianceStamped.__class__._TYPE_SUPPORT is None:
                PoseWithCovarianceStamped.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Relocalize_Result(metaclass=Metaclass_Relocalize_Result):
    """Message class 'Relocalize_Result'."""

    __slots__ = [
        '_success',
        '_error_code',
        '_final_pose',
        '_final_status',
        '_failure_reason',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'final_pose': 'geometry_msgs/PoseWithCovarianceStamped',
        'final_status': 'agt_interfaces/LocalizationStatus',
        'failure_reason': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PoseWithCovarianceStamped'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'LocalizationStatus'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        from geometry_msgs.msg import PoseWithCovarianceStamped
        self.final_pose = kwargs.get('final_pose', PoseWithCovarianceStamped())
        from agt_interfaces.msg import LocalizationStatus
        self.final_status = kwargs.get('final_status', LocalizationStatus())
        self.failure_reason = kwargs.get('failure_reason', str())

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
        if self.final_pose != other.final_pose:
            return False
        if self.final_status != other.final_status:
            return False
        if self.failure_reason != other.failure_reason:
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
    def final_pose(self):
        """Message field 'final_pose'."""
        return self._final_pose

    @final_pose.setter
    def final_pose(self, value):
        if __debug__:
            from geometry_msgs.msg import PoseWithCovarianceStamped
            assert \
                isinstance(value, PoseWithCovarianceStamped), \
                "The 'final_pose' field must be a sub message of type 'PoseWithCovarianceStamped'"
        self._final_pose = value

    @builtins.property
    def final_status(self):
        """Message field 'final_status'."""
        return self._final_status

    @final_status.setter
    def final_status(self, value):
        if __debug__:
            from agt_interfaces.msg import LocalizationStatus
            assert \
                isinstance(value, LocalizationStatus), \
                "The 'final_status' field must be a sub message of type 'LocalizationStatus'"
        self._final_status = value

    @builtins.property
    def failure_reason(self):
        """Message field 'failure_reason'."""
        return self._failure_reason

    @failure_reason.setter
    def failure_reason(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'failure_reason' field must be of type 'str'"
        self._failure_reason = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import math

# already imported above
# import rosidl_parser.definition


class Metaclass_Relocalize_Feedback(type):
    """Metaclass of message 'Relocalize_Feedback'."""

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
                'agt_interfaces.action.Relocalize_Feedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__relocalize__feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__relocalize__feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__relocalize__feedback
            cls._TYPE_SUPPORT = module.type_support_msg__action__relocalize__feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__relocalize__feedback

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Relocalize_Feedback(metaclass=Metaclass_Relocalize_Feedback):
    """Message class 'Relocalize_Feedback'."""

    __slots__ = [
        '_state',
        '_total_candidates',
        '_tested_candidates',
        '_best_fitness_score',
        '_best_candidate_source',
        '_elapsed_s',
    ]

    _fields_and_field_types = {
        'state': 'uint8',
        'total_candidates': 'uint32',
        'tested_candidates': 'uint32',
        'best_fitness_score': 'double',
        'best_candidate_source': 'string',
        'elapsed_s': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.state = kwargs.get('state', int())
        self.total_candidates = kwargs.get('total_candidates', int())
        self.tested_candidates = kwargs.get('tested_candidates', int())
        self.best_fitness_score = kwargs.get('best_fitness_score', float())
        self.best_candidate_source = kwargs.get('best_candidate_source', str())
        self.elapsed_s = kwargs.get('elapsed_s', float())

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
        if self.total_candidates != other.total_candidates:
            return False
        if self.tested_candidates != other.tested_candidates:
            return False
        if self.best_fitness_score != other.best_fitness_score:
            return False
        if self.best_candidate_source != other.best_candidate_source:
            return False
        if self.elapsed_s != other.elapsed_s:
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
                isinstance(value, int), \
                "The 'state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'state' field must be an unsigned integer in [0, 255]"
        self._state = value

    @builtins.property
    def total_candidates(self):
        """Message field 'total_candidates'."""
        return self._total_candidates

    @total_candidates.setter
    def total_candidates(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'total_candidates' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'total_candidates' field must be an unsigned integer in [0, 4294967295]"
        self._total_candidates = value

    @builtins.property
    def tested_candidates(self):
        """Message field 'tested_candidates'."""
        return self._tested_candidates

    @tested_candidates.setter
    def tested_candidates(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'tested_candidates' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'tested_candidates' field must be an unsigned integer in [0, 4294967295]"
        self._tested_candidates = value

    @builtins.property
    def best_fitness_score(self):
        """Message field 'best_fitness_score'."""
        return self._best_fitness_score

    @best_fitness_score.setter
    def best_fitness_score(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'best_fitness_score' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'best_fitness_score' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._best_fitness_score = value

    @builtins.property
    def best_candidate_source(self):
        """Message field 'best_candidate_source'."""
        return self._best_candidate_source

    @best_candidate_source.setter
    def best_candidate_source(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'best_candidate_source' field must be of type 'str'"
        self._best_candidate_source = value

    @builtins.property
    def elapsed_s(self):
        """Message field 'elapsed_s'."""
        return self._elapsed_s

    @elapsed_s.setter
    def elapsed_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'elapsed_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'elapsed_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._elapsed_s = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Relocalize_SendGoal_Request(type):
    """Metaclass of message 'Relocalize_SendGoal_Request'."""

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
                'agt_interfaces.action.Relocalize_SendGoal_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__relocalize__send_goal__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__relocalize__send_goal__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__relocalize__send_goal__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__relocalize__send_goal__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__relocalize__send_goal__request

            from agt_interfaces.action import Relocalize
            if Relocalize.Goal.__class__._TYPE_SUPPORT is None:
                Relocalize.Goal.__class__.__import_type_support__()

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


class Relocalize_SendGoal_Request(metaclass=Metaclass_Relocalize_SendGoal_Request):
    """Message class 'Relocalize_SendGoal_Request'."""

    __slots__ = [
        '_goal_id',
        '_goal',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'goal': 'agt_interfaces/Relocalize_Goal',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'Relocalize_Goal'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._relocalize import Relocalize_Goal
        self.goal = kwargs.get('goal', Relocalize_Goal())

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
            from agt_interfaces.action._relocalize import Relocalize_Goal
            assert \
                isinstance(value, Relocalize_Goal), \
                "The 'goal' field must be a sub message of type 'Relocalize_Goal'"
        self._goal = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Relocalize_SendGoal_Response(type):
    """Metaclass of message 'Relocalize_SendGoal_Response'."""

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
                'agt_interfaces.action.Relocalize_SendGoal_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__relocalize__send_goal__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__relocalize__send_goal__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__relocalize__send_goal__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__relocalize__send_goal__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__relocalize__send_goal__response

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


class Relocalize_SendGoal_Response(metaclass=Metaclass_Relocalize_SendGoal_Response):
    """Message class 'Relocalize_SendGoal_Response'."""

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


class Metaclass_Relocalize_SendGoal(type):
    """Metaclass of service 'Relocalize_SendGoal'."""

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
                'agt_interfaces.action.Relocalize_SendGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__relocalize__send_goal

            from agt_interfaces.action import _relocalize
            if _relocalize.Metaclass_Relocalize_SendGoal_Request._TYPE_SUPPORT is None:
                _relocalize.Metaclass_Relocalize_SendGoal_Request.__import_type_support__()
            if _relocalize.Metaclass_Relocalize_SendGoal_Response._TYPE_SUPPORT is None:
                _relocalize.Metaclass_Relocalize_SendGoal_Response.__import_type_support__()


class Relocalize_SendGoal(metaclass=Metaclass_Relocalize_SendGoal):
    from agt_interfaces.action._relocalize import Relocalize_SendGoal_Request as Request
    from agt_interfaces.action._relocalize import Relocalize_SendGoal_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Relocalize_GetResult_Request(type):
    """Metaclass of message 'Relocalize_GetResult_Request'."""

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
                'agt_interfaces.action.Relocalize_GetResult_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__relocalize__get_result__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__relocalize__get_result__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__relocalize__get_result__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__relocalize__get_result__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__relocalize__get_result__request

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


class Relocalize_GetResult_Request(metaclass=Metaclass_Relocalize_GetResult_Request):
    """Message class 'Relocalize_GetResult_Request'."""

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


class Metaclass_Relocalize_GetResult_Response(type):
    """Metaclass of message 'Relocalize_GetResult_Response'."""

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
                'agt_interfaces.action.Relocalize_GetResult_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__relocalize__get_result__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__relocalize__get_result__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__relocalize__get_result__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__relocalize__get_result__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__relocalize__get_result__response

            from agt_interfaces.action import Relocalize
            if Relocalize.Result.__class__._TYPE_SUPPORT is None:
                Relocalize.Result.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Relocalize_GetResult_Response(metaclass=Metaclass_Relocalize_GetResult_Response):
    """Message class 'Relocalize_GetResult_Response'."""

    __slots__ = [
        '_status',
        '_result',
    ]

    _fields_and_field_types = {
        'status': 'int8',
        'result': 'agt_interfaces/Relocalize_Result',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'Relocalize_Result'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        from agt_interfaces.action._relocalize import Relocalize_Result
        self.result = kwargs.get('result', Relocalize_Result())

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
            from agt_interfaces.action._relocalize import Relocalize_Result
            assert \
                isinstance(value, Relocalize_Result), \
                "The 'result' field must be a sub message of type 'Relocalize_Result'"
        self._result = value


class Metaclass_Relocalize_GetResult(type):
    """Metaclass of service 'Relocalize_GetResult'."""

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
                'agt_interfaces.action.Relocalize_GetResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__relocalize__get_result

            from agt_interfaces.action import _relocalize
            if _relocalize.Metaclass_Relocalize_GetResult_Request._TYPE_SUPPORT is None:
                _relocalize.Metaclass_Relocalize_GetResult_Request.__import_type_support__()
            if _relocalize.Metaclass_Relocalize_GetResult_Response._TYPE_SUPPORT is None:
                _relocalize.Metaclass_Relocalize_GetResult_Response.__import_type_support__()


class Relocalize_GetResult(metaclass=Metaclass_Relocalize_GetResult):
    from agt_interfaces.action._relocalize import Relocalize_GetResult_Request as Request
    from agt_interfaces.action._relocalize import Relocalize_GetResult_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Relocalize_FeedbackMessage(type):
    """Metaclass of message 'Relocalize_FeedbackMessage'."""

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
                'agt_interfaces.action.Relocalize_FeedbackMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__relocalize__feedback_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__relocalize__feedback_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__relocalize__feedback_message
            cls._TYPE_SUPPORT = module.type_support_msg__action__relocalize__feedback_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__relocalize__feedback_message

            from agt_interfaces.action import Relocalize
            if Relocalize.Feedback.__class__._TYPE_SUPPORT is None:
                Relocalize.Feedback.__class__.__import_type_support__()

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


class Relocalize_FeedbackMessage(metaclass=Metaclass_Relocalize_FeedbackMessage):
    """Message class 'Relocalize_FeedbackMessage'."""

    __slots__ = [
        '_goal_id',
        '_feedback',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'feedback': 'agt_interfaces/Relocalize_Feedback',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'Relocalize_Feedback'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._relocalize import Relocalize_Feedback
        self.feedback = kwargs.get('feedback', Relocalize_Feedback())

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
            from agt_interfaces.action._relocalize import Relocalize_Feedback
            assert \
                isinstance(value, Relocalize_Feedback), \
                "The 'feedback' field must be a sub message of type 'Relocalize_Feedback'"
        self._feedback = value


class Metaclass_Relocalize(type):
    """Metaclass of action 'Relocalize'."""

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
                'agt_interfaces.action.Relocalize')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_action__action__relocalize

            from action_msgs.msg import _goal_status_array
            if _goal_status_array.Metaclass_GoalStatusArray._TYPE_SUPPORT is None:
                _goal_status_array.Metaclass_GoalStatusArray.__import_type_support__()
            from action_msgs.srv import _cancel_goal
            if _cancel_goal.Metaclass_CancelGoal._TYPE_SUPPORT is None:
                _cancel_goal.Metaclass_CancelGoal.__import_type_support__()

            from agt_interfaces.action import _relocalize
            if _relocalize.Metaclass_Relocalize_SendGoal._TYPE_SUPPORT is None:
                _relocalize.Metaclass_Relocalize_SendGoal.__import_type_support__()
            if _relocalize.Metaclass_Relocalize_GetResult._TYPE_SUPPORT is None:
                _relocalize.Metaclass_Relocalize_GetResult.__import_type_support__()
            if _relocalize.Metaclass_Relocalize_FeedbackMessage._TYPE_SUPPORT is None:
                _relocalize.Metaclass_Relocalize_FeedbackMessage.__import_type_support__()


class Relocalize(metaclass=Metaclass_Relocalize):

    # The goal message defined in the action definition.
    from agt_interfaces.action._relocalize import Relocalize_Goal as Goal
    # The result message defined in the action definition.
    from agt_interfaces.action._relocalize import Relocalize_Result as Result
    # The feedback message defined in the action definition.
    from agt_interfaces.action._relocalize import Relocalize_Feedback as Feedback

    class Impl:

        # The send_goal service using a wrapped version of the goal message as a request.
        from agt_interfaces.action._relocalize import Relocalize_SendGoal as SendGoalService
        # The get_result service using a wrapped version of the result message as a response.
        from agt_interfaces.action._relocalize import Relocalize_GetResult as GetResultService
        # The feedback message with generic fields which wraps the feedback message.
        from agt_interfaces.action._relocalize import Relocalize_FeedbackMessage as FeedbackMessage

        # The generic service to cancel a goal.
        from action_msgs.srv._cancel_goal import CancelGoal as CancelGoalService
        # The generic message for get the status of a goal.
        from action_msgs.msg._goal_status_array import GoalStatusArray as GoalStatusMessage

    def __init__(self):
        raise NotImplementedError('Action classes can not be instantiated')
