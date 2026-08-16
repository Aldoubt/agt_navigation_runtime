# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/LocalizationStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_LocalizationStatus(type):
    """Metaclass of message 'LocalizationStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'STATE_UNINITIALIZED': 0,
        'STATE_SEARCHING': 1,
        'STATE_VERIFYING': 2,
        'STATE_TRACKING': 3,
        'STATE_DEGRADED': 4,
        'STATE_RECOVERING': 5,
        'STATE_LOST': 6,
        'STATE_ERROR': 7,
        'ERROR_NONE': 0,
        'ERROR_MAP_NOT_READY': 100,
        'ERROR_SCAN_TOO_SMALL': 101,
        'ERROR_BACKEND_FAILED': 102,
        'ERROR_FITNESS_REJECTED': 103,
        'ERROR_INVALID_INITIAL_GUESS': 104,
        'ERROR_INVALID_REQUEST': 105,
        'ERROR_TIMEOUT': 106,
        'ERROR_CANCELED': 107,
        'ERROR_AMBIGUOUS_RESULT': 108,
        'ERROR_STALE_STATUS': 109,
        'ERROR_TF_UNAVAILABLE': 110,
        'ERROR_MAP_HASH_MISMATCH': 111,
        'ERROR_NO_CANDIDATES': 112,
        'ERROR_STALE_SCAN': 113,
        'ERROR_INVALID_SCAN_TIMESTAMP': 114,
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
                'agt_interfaces.msg.LocalizationStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__localization_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__localization_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__localization_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__localization_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__localization_status

            from geometry_msgs.msg import PoseWithCovarianceStamped
            if PoseWithCovarianceStamped.__class__._TYPE_SUPPORT is None:
                PoseWithCovarianceStamped.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'STATE_UNINITIALIZED': cls.__constants['STATE_UNINITIALIZED'],
            'STATE_SEARCHING': cls.__constants['STATE_SEARCHING'],
            'STATE_VERIFYING': cls.__constants['STATE_VERIFYING'],
            'STATE_TRACKING': cls.__constants['STATE_TRACKING'],
            'STATE_DEGRADED': cls.__constants['STATE_DEGRADED'],
            'STATE_RECOVERING': cls.__constants['STATE_RECOVERING'],
            'STATE_LOST': cls.__constants['STATE_LOST'],
            'STATE_ERROR': cls.__constants['STATE_ERROR'],
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_MAP_NOT_READY': cls.__constants['ERROR_MAP_NOT_READY'],
            'ERROR_SCAN_TOO_SMALL': cls.__constants['ERROR_SCAN_TOO_SMALL'],
            'ERROR_BACKEND_FAILED': cls.__constants['ERROR_BACKEND_FAILED'],
            'ERROR_FITNESS_REJECTED': cls.__constants['ERROR_FITNESS_REJECTED'],
            'ERROR_INVALID_INITIAL_GUESS': cls.__constants['ERROR_INVALID_INITIAL_GUESS'],
            'ERROR_INVALID_REQUEST': cls.__constants['ERROR_INVALID_REQUEST'],
            'ERROR_TIMEOUT': cls.__constants['ERROR_TIMEOUT'],
            'ERROR_CANCELED': cls.__constants['ERROR_CANCELED'],
            'ERROR_AMBIGUOUS_RESULT': cls.__constants['ERROR_AMBIGUOUS_RESULT'],
            'ERROR_STALE_STATUS': cls.__constants['ERROR_STALE_STATUS'],
            'ERROR_TF_UNAVAILABLE': cls.__constants['ERROR_TF_UNAVAILABLE'],
            'ERROR_MAP_HASH_MISMATCH': cls.__constants['ERROR_MAP_HASH_MISMATCH'],
            'ERROR_NO_CANDIDATES': cls.__constants['ERROR_NO_CANDIDATES'],
            'ERROR_STALE_SCAN': cls.__constants['ERROR_STALE_SCAN'],
            'ERROR_INVALID_SCAN_TIMESTAMP': cls.__constants['ERROR_INVALID_SCAN_TIMESTAMP'],
        }

    @property
    def STATE_UNINITIALIZED(self):
        """Message constant 'STATE_UNINITIALIZED'."""
        return Metaclass_LocalizationStatus.__constants['STATE_UNINITIALIZED']

    @property
    def STATE_SEARCHING(self):
        """Message constant 'STATE_SEARCHING'."""
        return Metaclass_LocalizationStatus.__constants['STATE_SEARCHING']

    @property
    def STATE_VERIFYING(self):
        """Message constant 'STATE_VERIFYING'."""
        return Metaclass_LocalizationStatus.__constants['STATE_VERIFYING']

    @property
    def STATE_TRACKING(self):
        """Message constant 'STATE_TRACKING'."""
        return Metaclass_LocalizationStatus.__constants['STATE_TRACKING']

    @property
    def STATE_DEGRADED(self):
        """Message constant 'STATE_DEGRADED'."""
        return Metaclass_LocalizationStatus.__constants['STATE_DEGRADED']

    @property
    def STATE_RECOVERING(self):
        """Message constant 'STATE_RECOVERING'."""
        return Metaclass_LocalizationStatus.__constants['STATE_RECOVERING']

    @property
    def STATE_LOST(self):
        """Message constant 'STATE_LOST'."""
        return Metaclass_LocalizationStatus.__constants['STATE_LOST']

    @property
    def STATE_ERROR(self):
        """Message constant 'STATE_ERROR'."""
        return Metaclass_LocalizationStatus.__constants['STATE_ERROR']

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_NONE']

    @property
    def ERROR_MAP_NOT_READY(self):
        """Message constant 'ERROR_MAP_NOT_READY'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_MAP_NOT_READY']

    @property
    def ERROR_SCAN_TOO_SMALL(self):
        """Message constant 'ERROR_SCAN_TOO_SMALL'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_SCAN_TOO_SMALL']

    @property
    def ERROR_BACKEND_FAILED(self):
        """Message constant 'ERROR_BACKEND_FAILED'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_BACKEND_FAILED']

    @property
    def ERROR_FITNESS_REJECTED(self):
        """Message constant 'ERROR_FITNESS_REJECTED'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_FITNESS_REJECTED']

    @property
    def ERROR_INVALID_INITIAL_GUESS(self):
        """Message constant 'ERROR_INVALID_INITIAL_GUESS'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_INVALID_INITIAL_GUESS']

    @property
    def ERROR_INVALID_REQUEST(self):
        """Message constant 'ERROR_INVALID_REQUEST'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_INVALID_REQUEST']

    @property
    def ERROR_TIMEOUT(self):
        """Message constant 'ERROR_TIMEOUT'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_TIMEOUT']

    @property
    def ERROR_CANCELED(self):
        """Message constant 'ERROR_CANCELED'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_CANCELED']

    @property
    def ERROR_AMBIGUOUS_RESULT(self):
        """Message constant 'ERROR_AMBIGUOUS_RESULT'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_AMBIGUOUS_RESULT']

    @property
    def ERROR_STALE_STATUS(self):
        """Message constant 'ERROR_STALE_STATUS'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_STALE_STATUS']

    @property
    def ERROR_TF_UNAVAILABLE(self):
        """Message constant 'ERROR_TF_UNAVAILABLE'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_TF_UNAVAILABLE']

    @property
    def ERROR_MAP_HASH_MISMATCH(self):
        """Message constant 'ERROR_MAP_HASH_MISMATCH'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_MAP_HASH_MISMATCH']

    @property
    def ERROR_NO_CANDIDATES(self):
        """Message constant 'ERROR_NO_CANDIDATES'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_NO_CANDIDATES']

    @property
    def ERROR_STALE_SCAN(self):
        """Message constant 'ERROR_STALE_SCAN'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_STALE_SCAN']

    @property
    def ERROR_INVALID_SCAN_TIMESTAMP(self):
        """Message constant 'ERROR_INVALID_SCAN_TIMESTAMP'."""
        return Metaclass_LocalizationStatus.__constants['ERROR_INVALID_SCAN_TIMESTAMP']


class LocalizationStatus(metaclass=Metaclass_LocalizationStatus):
    """
    Message class 'LocalizationStatus'.

    Constants:
      STATE_UNINITIALIZED
      STATE_SEARCHING
      STATE_VERIFYING
      STATE_TRACKING
      STATE_DEGRADED
      STATE_RECOVERING
      STATE_LOST
      STATE_ERROR
      ERROR_NONE
      ERROR_MAP_NOT_READY
      ERROR_SCAN_TOO_SMALL
      ERROR_BACKEND_FAILED
      ERROR_FITNESS_REJECTED
      ERROR_INVALID_INITIAL_GUESS
      ERROR_INVALID_REQUEST
      ERROR_TIMEOUT
      ERROR_CANCELED
      ERROR_AMBIGUOUS_RESULT
      ERROR_STALE_STATUS
      ERROR_TF_UNAVAILABLE
      ERROR_MAP_HASH_MISMATCH
      ERROR_NO_CANDIDATES
      ERROR_STALE_SCAN
      ERROR_INVALID_SCAN_TIMESTAMP
    """

    __slots__ = [
        '_header',
        '_state',
        '_pose_valid',
        '_localization_accepted',
        '_has_converged',
        '_ambiguous_result',
        '_status_stale',
        '_error_code',
        '_backend',
        '_candidate_source',
        '_candidate_id',
        '_map_id',
        '_map_hash',
        '_correction_generation',
        '_global_pose',
        '_fitness_score',
        '_overlap_ratio',
        '_inlier_ratio',
        '_ambiguity_score',
        '_translation_innovation',
        '_yaw_innovation',
        '_runtime_ms',
        '_tested_candidates',
        '_total_candidates',
        '_consecutive_successes',
        '_consecutive_failures',
        '_message',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'state': 'uint8',
        'pose_valid': 'boolean',
        'localization_accepted': 'boolean',
        'has_converged': 'boolean',
        'ambiguous_result': 'boolean',
        'status_stale': 'boolean',
        'error_code': 'uint16',
        'backend': 'string',
        'candidate_source': 'string',
        'candidate_id': 'string',
        'map_id': 'string',
        'map_hash': 'string',
        'correction_generation': 'uint64',
        'global_pose': 'geometry_msgs/PoseWithCovarianceStamped',
        'fitness_score': 'double',
        'overlap_ratio': 'double',
        'inlier_ratio': 'double',
        'ambiguity_score': 'double',
        'translation_innovation': 'double',
        'yaw_innovation': 'double',
        'runtime_ms': 'double',
        'tested_candidates': 'uint32',
        'total_candidates': 'uint32',
        'consecutive_successes': 'uint32',
        'consecutive_failures': 'uint32',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PoseWithCovarianceStamped'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.state = kwargs.get('state', int())
        self.pose_valid = kwargs.get('pose_valid', bool())
        self.localization_accepted = kwargs.get('localization_accepted', bool())
        self.has_converged = kwargs.get('has_converged', bool())
        self.ambiguous_result = kwargs.get('ambiguous_result', bool())
        self.status_stale = kwargs.get('status_stale', bool())
        self.error_code = kwargs.get('error_code', int())
        self.backend = kwargs.get('backend', str())
        self.candidate_source = kwargs.get('candidate_source', str())
        self.candidate_id = kwargs.get('candidate_id', str())
        self.map_id = kwargs.get('map_id', str())
        self.map_hash = kwargs.get('map_hash', str())
        self.correction_generation = kwargs.get('correction_generation', int())
        from geometry_msgs.msg import PoseWithCovarianceStamped
        self.global_pose = kwargs.get('global_pose', PoseWithCovarianceStamped())
        self.fitness_score = kwargs.get('fitness_score', float())
        self.overlap_ratio = kwargs.get('overlap_ratio', float())
        self.inlier_ratio = kwargs.get('inlier_ratio', float())
        self.ambiguity_score = kwargs.get('ambiguity_score', float())
        self.translation_innovation = kwargs.get('translation_innovation', float())
        self.yaw_innovation = kwargs.get('yaw_innovation', float())
        self.runtime_ms = kwargs.get('runtime_ms', float())
        self.tested_candidates = kwargs.get('tested_candidates', int())
        self.total_candidates = kwargs.get('total_candidates', int())
        self.consecutive_successes = kwargs.get('consecutive_successes', int())
        self.consecutive_failures = kwargs.get('consecutive_failures', int())
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
        if self.pose_valid != other.pose_valid:
            return False
        if self.localization_accepted != other.localization_accepted:
            return False
        if self.has_converged != other.has_converged:
            return False
        if self.ambiguous_result != other.ambiguous_result:
            return False
        if self.status_stale != other.status_stale:
            return False
        if self.error_code != other.error_code:
            return False
        if self.backend != other.backend:
            return False
        if self.candidate_source != other.candidate_source:
            return False
        if self.candidate_id != other.candidate_id:
            return False
        if self.map_id != other.map_id:
            return False
        if self.map_hash != other.map_hash:
            return False
        if self.correction_generation != other.correction_generation:
            return False
        if self.global_pose != other.global_pose:
            return False
        if self.fitness_score != other.fitness_score:
            return False
        if self.overlap_ratio != other.overlap_ratio:
            return False
        if self.inlier_ratio != other.inlier_ratio:
            return False
        if self.ambiguity_score != other.ambiguity_score:
            return False
        if self.translation_innovation != other.translation_innovation:
            return False
        if self.yaw_innovation != other.yaw_innovation:
            return False
        if self.runtime_ms != other.runtime_ms:
            return False
        if self.tested_candidates != other.tested_candidates:
            return False
        if self.total_candidates != other.total_candidates:
            return False
        if self.consecutive_successes != other.consecutive_successes:
            return False
        if self.consecutive_failures != other.consecutive_failures:
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
    def pose_valid(self):
        """Message field 'pose_valid'."""
        return self._pose_valid

    @pose_valid.setter
    def pose_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'pose_valid' field must be of type 'bool'"
        self._pose_valid = value

    @builtins.property
    def localization_accepted(self):
        """Message field 'localization_accepted'."""
        return self._localization_accepted

    @localization_accepted.setter
    def localization_accepted(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'localization_accepted' field must be of type 'bool'"
        self._localization_accepted = value

    @builtins.property
    def has_converged(self):
        """Message field 'has_converged'."""
        return self._has_converged

    @has_converged.setter
    def has_converged(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'has_converged' field must be of type 'bool'"
        self._has_converged = value

    @builtins.property
    def ambiguous_result(self):
        """Message field 'ambiguous_result'."""
        return self._ambiguous_result

    @ambiguous_result.setter
    def ambiguous_result(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ambiguous_result' field must be of type 'bool'"
        self._ambiguous_result = value

    @builtins.property
    def status_stale(self):
        """Message field 'status_stale'."""
        return self._status_stale

    @status_stale.setter
    def status_stale(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'status_stale' field must be of type 'bool'"
        self._status_stale = value

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
    def backend(self):
        """Message field 'backend'."""
        return self._backend

    @backend.setter
    def backend(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'backend' field must be of type 'str'"
        self._backend = value

    @builtins.property
    def candidate_source(self):
        """Message field 'candidate_source'."""
        return self._candidate_source

    @candidate_source.setter
    def candidate_source(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'candidate_source' field must be of type 'str'"
        self._candidate_source = value

    @builtins.property
    def candidate_id(self):
        """Message field 'candidate_id'."""
        return self._candidate_id

    @candidate_id.setter
    def candidate_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'candidate_id' field must be of type 'str'"
        self._candidate_id = value

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
    def map_hash(self):
        """Message field 'map_hash'."""
        return self._map_hash

    @map_hash.setter
    def map_hash(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_hash' field must be of type 'str'"
        self._map_hash = value

    @builtins.property
    def correction_generation(self):
        """Message field 'correction_generation'."""
        return self._correction_generation

    @correction_generation.setter
    def correction_generation(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'correction_generation' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'correction_generation' field must be an unsigned integer in [0, 18446744073709551615]"
        self._correction_generation = value

    @builtins.property
    def global_pose(self):
        """Message field 'global_pose'."""
        return self._global_pose

    @global_pose.setter
    def global_pose(self, value):
        if __debug__:
            from geometry_msgs.msg import PoseWithCovarianceStamped
            assert \
                isinstance(value, PoseWithCovarianceStamped), \
                "The 'global_pose' field must be a sub message of type 'PoseWithCovarianceStamped'"
        self._global_pose = value

    @builtins.property
    def fitness_score(self):
        """Message field 'fitness_score'."""
        return self._fitness_score

    @fitness_score.setter
    def fitness_score(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'fitness_score' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'fitness_score' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._fitness_score = value

    @builtins.property
    def overlap_ratio(self):
        """Message field 'overlap_ratio'."""
        return self._overlap_ratio

    @overlap_ratio.setter
    def overlap_ratio(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'overlap_ratio' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'overlap_ratio' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._overlap_ratio = value

    @builtins.property
    def inlier_ratio(self):
        """Message field 'inlier_ratio'."""
        return self._inlier_ratio

    @inlier_ratio.setter
    def inlier_ratio(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'inlier_ratio' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'inlier_ratio' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._inlier_ratio = value

    @builtins.property
    def ambiguity_score(self):
        """Message field 'ambiguity_score'."""
        return self._ambiguity_score

    @ambiguity_score.setter
    def ambiguity_score(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ambiguity_score' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ambiguity_score' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ambiguity_score = value

    @builtins.property
    def translation_innovation(self):
        """Message field 'translation_innovation'."""
        return self._translation_innovation

    @translation_innovation.setter
    def translation_innovation(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'translation_innovation' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'translation_innovation' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._translation_innovation = value

    @builtins.property
    def yaw_innovation(self):
        """Message field 'yaw_innovation'."""
        return self._yaw_innovation

    @yaw_innovation.setter
    def yaw_innovation(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yaw_innovation' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'yaw_innovation' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._yaw_innovation = value

    @builtins.property
    def runtime_ms(self):
        """Message field 'runtime_ms'."""
        return self._runtime_ms

    @runtime_ms.setter
    def runtime_ms(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'runtime_ms' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'runtime_ms' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._runtime_ms = value

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
    def consecutive_successes(self):
        """Message field 'consecutive_successes'."""
        return self._consecutive_successes

    @consecutive_successes.setter
    def consecutive_successes(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'consecutive_successes' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'consecutive_successes' field must be an unsigned integer in [0, 4294967295]"
        self._consecutive_successes = value

    @builtins.property
    def consecutive_failures(self):
        """Message field 'consecutive_failures'."""
        return self._consecutive_failures

    @consecutive_failures.setter
    def consecutive_failures(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'consecutive_failures' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'consecutive_failures' field must be an unsigned integer in [0, 4294967295]"
        self._consecutive_failures = value

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
