# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:srv/ManageBagSession.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ManageBagSession_Request(type):
    """Metaclass of message 'ManageBagSession_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'OP_STATUS': 0,
        'OP_START_RECORDING': 1,
        'OP_STOP_RECORDING': 2,
        'OP_START_PLAYBACK': 3,
        'OP_STOP_PLAYBACK': 4,
        'OP_CREATE_EXPERIMENT': 5,
        'OP_COMPLETE_EXPERIMENT': 6,
        'OP_INTERRUPT_EXPERIMENT': 7,
        'OP_START_EXPERIMENT': 8,
        'OP_MARK_EXPERIMENT_INVALID': 9,
        'OP_ADD_EXPERIMENT_EVENT': 10,
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
                'agt_interfaces.srv.ManageBagSession_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__manage_bag_session__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__manage_bag_session__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__manage_bag_session__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__manage_bag_session__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__manage_bag_session__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'OP_STATUS': cls.__constants['OP_STATUS'],
            'OP_START_RECORDING': cls.__constants['OP_START_RECORDING'],
            'OP_STOP_RECORDING': cls.__constants['OP_STOP_RECORDING'],
            'OP_START_PLAYBACK': cls.__constants['OP_START_PLAYBACK'],
            'OP_STOP_PLAYBACK': cls.__constants['OP_STOP_PLAYBACK'],
            'OP_CREATE_EXPERIMENT': cls.__constants['OP_CREATE_EXPERIMENT'],
            'OP_COMPLETE_EXPERIMENT': cls.__constants['OP_COMPLETE_EXPERIMENT'],
            'OP_INTERRUPT_EXPERIMENT': cls.__constants['OP_INTERRUPT_EXPERIMENT'],
            'OP_START_EXPERIMENT': cls.__constants['OP_START_EXPERIMENT'],
            'OP_MARK_EXPERIMENT_INVALID': cls.__constants['OP_MARK_EXPERIMENT_INVALID'],
            'OP_ADD_EXPERIMENT_EVENT': cls.__constants['OP_ADD_EXPERIMENT_EVENT'],
        }

    @property
    def OP_STATUS(self):
        """Message constant 'OP_STATUS'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_STATUS']

    @property
    def OP_START_RECORDING(self):
        """Message constant 'OP_START_RECORDING'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_START_RECORDING']

    @property
    def OP_STOP_RECORDING(self):
        """Message constant 'OP_STOP_RECORDING'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_STOP_RECORDING']

    @property
    def OP_START_PLAYBACK(self):
        """Message constant 'OP_START_PLAYBACK'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_START_PLAYBACK']

    @property
    def OP_STOP_PLAYBACK(self):
        """Message constant 'OP_STOP_PLAYBACK'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_STOP_PLAYBACK']

    @property
    def OP_CREATE_EXPERIMENT(self):
        """Message constant 'OP_CREATE_EXPERIMENT'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_CREATE_EXPERIMENT']

    @property
    def OP_COMPLETE_EXPERIMENT(self):
        """Message constant 'OP_COMPLETE_EXPERIMENT'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_COMPLETE_EXPERIMENT']

    @property
    def OP_INTERRUPT_EXPERIMENT(self):
        """Message constant 'OP_INTERRUPT_EXPERIMENT'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_INTERRUPT_EXPERIMENT']

    @property
    def OP_START_EXPERIMENT(self):
        """Message constant 'OP_START_EXPERIMENT'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_START_EXPERIMENT']

    @property
    def OP_MARK_EXPERIMENT_INVALID(self):
        """Message constant 'OP_MARK_EXPERIMENT_INVALID'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_MARK_EXPERIMENT_INVALID']

    @property
    def OP_ADD_EXPERIMENT_EVENT(self):
        """Message constant 'OP_ADD_EXPERIMENT_EVENT'."""
        return Metaclass_ManageBagSession_Request.__constants['OP_ADD_EXPERIMENT_EVENT']


class ManageBagSession_Request(metaclass=Metaclass_ManageBagSession_Request):
    """
    Message class 'ManageBagSession_Request'.

    Constants:
      OP_STATUS
      OP_START_RECORDING
      OP_STOP_RECORDING
      OP_START_PLAYBACK
      OP_STOP_PLAYBACK
      OP_CREATE_EXPERIMENT
      OP_COMPLETE_EXPERIMENT
      OP_INTERRUPT_EXPERIMENT
      OP_START_EXPERIMENT
      OP_MARK_EXPERIMENT_INVALID
      OP_ADD_EXPERIMENT_EVENT
    """

    __slots__ = [
        '_operation',
        '_bag_id',
        '_experiment_id',
        '_experiment_title',
        '_objective',
        '_hypothesis',
        '_tags_json',
        '_operator_note',
        '_profile_id',
        '_playback_rate',
        '_mission_id',
        '_mission_version',
        '_mission_sha256',
        '_map_id',
        '_map_version_id',
        '_map_sha256',
        '_platform_profile',
        '_calibration_profile',
        '_nav2_profile',
        '_launch_profile',
        '_start_experiment',
        '_event_type',
        '_metadata_json',
        '_result_status',
        '_reason',
    ]

    _fields_and_field_types = {
        'operation': 'uint8',
        'bag_id': 'string',
        'experiment_id': 'string',
        'experiment_title': 'string',
        'objective': 'string',
        'hypothesis': 'string',
        'tags_json': 'string',
        'operator_note': 'string',
        'profile_id': 'string',
        'playback_rate': 'double',
        'mission_id': 'string',
        'mission_version': 'string',
        'mission_sha256': 'string',
        'map_id': 'string',
        'map_version_id': 'string',
        'map_sha256': 'string',
        'platform_profile': 'string',
        'calibration_profile': 'string',
        'nav2_profile': 'string',
        'launch_profile': 'string',
        'start_experiment': 'boolean',
        'event_type': 'string',
        'metadata_json': 'string',
        'result_status': 'string',
        'reason': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.operation = kwargs.get('operation', int())
        self.bag_id = kwargs.get('bag_id', str())
        self.experiment_id = kwargs.get('experiment_id', str())
        self.experiment_title = kwargs.get('experiment_title', str())
        self.objective = kwargs.get('objective', str())
        self.hypothesis = kwargs.get('hypothesis', str())
        self.tags_json = kwargs.get('tags_json', str())
        self.operator_note = kwargs.get('operator_note', str())
        self.profile_id = kwargs.get('profile_id', str())
        self.playback_rate = kwargs.get('playback_rate', float())
        self.mission_id = kwargs.get('mission_id', str())
        self.mission_version = kwargs.get('mission_version', str())
        self.mission_sha256 = kwargs.get('mission_sha256', str())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.map_sha256 = kwargs.get('map_sha256', str())
        self.platform_profile = kwargs.get('platform_profile', str())
        self.calibration_profile = kwargs.get('calibration_profile', str())
        self.nav2_profile = kwargs.get('nav2_profile', str())
        self.launch_profile = kwargs.get('launch_profile', str())
        self.start_experiment = kwargs.get('start_experiment', bool())
        self.event_type = kwargs.get('event_type', str())
        self.metadata_json = kwargs.get('metadata_json', str())
        self.result_status = kwargs.get('result_status', str())
        self.reason = kwargs.get('reason', str())

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
        if self.operation != other.operation:
            return False
        if self.bag_id != other.bag_id:
            return False
        if self.experiment_id != other.experiment_id:
            return False
        if self.experiment_title != other.experiment_title:
            return False
        if self.objective != other.objective:
            return False
        if self.hypothesis != other.hypothesis:
            return False
        if self.tags_json != other.tags_json:
            return False
        if self.operator_note != other.operator_note:
            return False
        if self.profile_id != other.profile_id:
            return False
        if self.playback_rate != other.playback_rate:
            return False
        if self.mission_id != other.mission_id:
            return False
        if self.mission_version != other.mission_version:
            return False
        if self.mission_sha256 != other.mission_sha256:
            return False
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.map_sha256 != other.map_sha256:
            return False
        if self.platform_profile != other.platform_profile:
            return False
        if self.calibration_profile != other.calibration_profile:
            return False
        if self.nav2_profile != other.nav2_profile:
            return False
        if self.launch_profile != other.launch_profile:
            return False
        if self.start_experiment != other.start_experiment:
            return False
        if self.event_type != other.event_type:
            return False
        if self.metadata_json != other.metadata_json:
            return False
        if self.result_status != other.result_status:
            return False
        if self.reason != other.reason:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def operation(self):
        """Message field 'operation'."""
        return self._operation

    @operation.setter
    def operation(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'operation' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'operation' field must be an unsigned integer in [0, 255]"
        self._operation = value

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
    def experiment_title(self):
        """Message field 'experiment_title'."""
        return self._experiment_title

    @experiment_title.setter
    def experiment_title(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'experiment_title' field must be of type 'str'"
        self._experiment_title = value

    @builtins.property
    def objective(self):
        """Message field 'objective'."""
        return self._objective

    @objective.setter
    def objective(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'objective' field must be of type 'str'"
        self._objective = value

    @builtins.property
    def hypothesis(self):
        """Message field 'hypothesis'."""
        return self._hypothesis

    @hypothesis.setter
    def hypothesis(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'hypothesis' field must be of type 'str'"
        self._hypothesis = value

    @builtins.property
    def tags_json(self):
        """Message field 'tags_json'."""
        return self._tags_json

    @tags_json.setter
    def tags_json(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'tags_json' field must be of type 'str'"
        self._tags_json = value

    @builtins.property
    def operator_note(self):
        """Message field 'operator_note'."""
        return self._operator_note

    @operator_note.setter
    def operator_note(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'operator_note' field must be of type 'str'"
        self._operator_note = value

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
    def mission_sha256(self):
        """Message field 'mission_sha256'."""
        return self._mission_sha256

    @mission_sha256.setter
    def mission_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'mission_sha256' field must be of type 'str'"
        self._mission_sha256 = value

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
    def map_sha256(self):
        """Message field 'map_sha256'."""
        return self._map_sha256

    @map_sha256.setter
    def map_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_sha256' field must be of type 'str'"
        self._map_sha256 = value

    @builtins.property
    def platform_profile(self):
        """Message field 'platform_profile'."""
        return self._platform_profile

    @platform_profile.setter
    def platform_profile(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'platform_profile' field must be of type 'str'"
        self._platform_profile = value

    @builtins.property
    def calibration_profile(self):
        """Message field 'calibration_profile'."""
        return self._calibration_profile

    @calibration_profile.setter
    def calibration_profile(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'calibration_profile' field must be of type 'str'"
        self._calibration_profile = value

    @builtins.property
    def nav2_profile(self):
        """Message field 'nav2_profile'."""
        return self._nav2_profile

    @nav2_profile.setter
    def nav2_profile(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'nav2_profile' field must be of type 'str'"
        self._nav2_profile = value

    @builtins.property
    def launch_profile(self):
        """Message field 'launch_profile'."""
        return self._launch_profile

    @launch_profile.setter
    def launch_profile(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'launch_profile' field must be of type 'str'"
        self._launch_profile = value

    @builtins.property
    def start_experiment(self):
        """Message field 'start_experiment'."""
        return self._start_experiment

    @start_experiment.setter
    def start_experiment(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'start_experiment' field must be of type 'bool'"
        self._start_experiment = value

    @builtins.property
    def event_type(self):
        """Message field 'event_type'."""
        return self._event_type

    @event_type.setter
    def event_type(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'event_type' field must be of type 'str'"
        self._event_type = value

    @builtins.property
    def metadata_json(self):
        """Message field 'metadata_json'."""
        return self._metadata_json

    @metadata_json.setter
    def metadata_json(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'metadata_json' field must be of type 'str'"
        self._metadata_json = value

    @builtins.property
    def result_status(self):
        """Message field 'result_status'."""
        return self._result_status

    @result_status.setter
    def result_status(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'result_status' field must be of type 'str'"
        self._result_status = value

    @builtins.property
    def reason(self):
        """Message field 'reason'."""
        return self._reason

    @reason.setter
    def reason(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'reason' field must be of type 'str'"
        self._reason = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ManageBagSession_Response(type):
    """Metaclass of message 'ManageBagSession_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ERROR_NONE': 0,
        'ERROR_NOT_FOUND': 1,
        'ERROR_INVALID_REQUEST': 2,
        'ERROR_CONFLICT': 3,
        'ERROR_PROFILE_INVALID': 4,
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
                'agt_interfaces.srv.ManageBagSession_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__manage_bag_session__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__manage_bag_session__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__manage_bag_session__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__manage_bag_session__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__manage_bag_session__response

            from agt_interfaces.msg import BagSessionSummary
            if BagSessionSummary.__class__._TYPE_SUPPORT is None:
                BagSessionSummary.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_NOT_FOUND': cls.__constants['ERROR_NOT_FOUND'],
            'ERROR_INVALID_REQUEST': cls.__constants['ERROR_INVALID_REQUEST'],
            'ERROR_CONFLICT': cls.__constants['ERROR_CONFLICT'],
            'ERROR_PROFILE_INVALID': cls.__constants['ERROR_PROFILE_INVALID'],
            'ERROR_INTERNAL': cls.__constants['ERROR_INTERNAL'],
        }

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_ManageBagSession_Response.__constants['ERROR_NONE']

    @property
    def ERROR_NOT_FOUND(self):
        """Message constant 'ERROR_NOT_FOUND'."""
        return Metaclass_ManageBagSession_Response.__constants['ERROR_NOT_FOUND']

    @property
    def ERROR_INVALID_REQUEST(self):
        """Message constant 'ERROR_INVALID_REQUEST'."""
        return Metaclass_ManageBagSession_Response.__constants['ERROR_INVALID_REQUEST']

    @property
    def ERROR_CONFLICT(self):
        """Message constant 'ERROR_CONFLICT'."""
        return Metaclass_ManageBagSession_Response.__constants['ERROR_CONFLICT']

    @property
    def ERROR_PROFILE_INVALID(self):
        """Message constant 'ERROR_PROFILE_INVALID'."""
        return Metaclass_ManageBagSession_Response.__constants['ERROR_PROFILE_INVALID']

    @property
    def ERROR_INTERNAL(self):
        """Message constant 'ERROR_INTERNAL'."""
        return Metaclass_ManageBagSession_Response.__constants['ERROR_INTERNAL']


class ManageBagSession_Response(metaclass=Metaclass_ManageBagSession_Response):
    """
    Message class 'ManageBagSession_Response'.

    Constants:
      ERROR_NONE
      ERROR_NOT_FOUND
      ERROR_INVALID_REQUEST
      ERROR_CONFLICT
      ERROR_PROFILE_INVALID
      ERROR_INTERNAL
    """

    __slots__ = [
        '_success',
        '_error_code',
        '_session',
        '_message',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'session': 'agt_interfaces/BagSessionSummary',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'BagSessionSummary'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        from agt_interfaces.msg import BagSessionSummary
        self.session = kwargs.get('session', BagSessionSummary())
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
        if self.success != other.success:
            return False
        if self.error_code != other.error_code:
            return False
        if self.session != other.session:
            return False
        if self.message != other.message:
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
    def session(self):
        """Message field 'session'."""
        return self._session

    @session.setter
    def session(self, value):
        if __debug__:
            from agt_interfaces.msg import BagSessionSummary
            assert \
                isinstance(value, BagSessionSummary), \
                "The 'session' field must be a sub message of type 'BagSessionSummary'"
        self._session = value

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


class Metaclass_ManageBagSession(type):
    """Metaclass of service 'ManageBagSession'."""

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
                'agt_interfaces.srv.ManageBagSession')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__manage_bag_session

            from agt_interfaces.srv import _manage_bag_session
            if _manage_bag_session.Metaclass_ManageBagSession_Request._TYPE_SUPPORT is None:
                _manage_bag_session.Metaclass_ManageBagSession_Request.__import_type_support__()
            if _manage_bag_session.Metaclass_ManageBagSession_Response._TYPE_SUPPORT is None:
                _manage_bag_session.Metaclass_ManageBagSession_Response.__import_type_support__()


class ManageBagSession(metaclass=Metaclass_ManageBagSession):
    from agt_interfaces.srv._manage_bag_session import ManageBagSession_Request as Request
    from agt_interfaces.srv._manage_bag_session import ManageBagSession_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
