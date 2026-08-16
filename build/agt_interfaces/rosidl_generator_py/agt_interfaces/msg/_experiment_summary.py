# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/ExperimentSummary.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ExperimentSummary(type):
    """Metaclass of message 'ExperimentSummary'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'STATE_UNKNOWN': 0,
        'STATE_CREATED': 1,
        'STATE_RUNNING': 2,
        'STATE_COMPLETED': 3,
        'STATE_INTERRUPTED': 4,
        'STATE_INVALID': 5,
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
                'agt_interfaces.msg.ExperimentSummary')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__experiment_summary
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__experiment_summary
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__experiment_summary
            cls._TYPE_SUPPORT = module.type_support_msg__msg__experiment_summary
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__experiment_summary

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
            'STATE_CREATED': cls.__constants['STATE_CREATED'],
            'STATE_RUNNING': cls.__constants['STATE_RUNNING'],
            'STATE_COMPLETED': cls.__constants['STATE_COMPLETED'],
            'STATE_INTERRUPTED': cls.__constants['STATE_INTERRUPTED'],
            'STATE_INVALID': cls.__constants['STATE_INVALID'],
        }

    @property
    def STATE_UNKNOWN(self):
        """Message constant 'STATE_UNKNOWN'."""
        return Metaclass_ExperimentSummary.__constants['STATE_UNKNOWN']

    @property
    def STATE_CREATED(self):
        """Message constant 'STATE_CREATED'."""
        return Metaclass_ExperimentSummary.__constants['STATE_CREATED']

    @property
    def STATE_RUNNING(self):
        """Message constant 'STATE_RUNNING'."""
        return Metaclass_ExperimentSummary.__constants['STATE_RUNNING']

    @property
    def STATE_COMPLETED(self):
        """Message constant 'STATE_COMPLETED'."""
        return Metaclass_ExperimentSummary.__constants['STATE_COMPLETED']

    @property
    def STATE_INTERRUPTED(self):
        """Message constant 'STATE_INTERRUPTED'."""
        return Metaclass_ExperimentSummary.__constants['STATE_INTERRUPTED']

    @property
    def STATE_INVALID(self):
        """Message constant 'STATE_INVALID'."""
        return Metaclass_ExperimentSummary.__constants['STATE_INVALID']


class ExperimentSummary(metaclass=Metaclass_ExperimentSummary):
    """
    Message class 'ExperimentSummary'.

    Constants:
      STATE_UNKNOWN
      STATE_CREATED
      STATE_RUNNING
      STATE_COMPLETED
      STATE_INTERRUPTED
      STATE_INVALID
    """

    __slots__ = [
        '_header',
        '_experiment_id',
        '_title',
        '_state',
        '_created_at',
        '_start_time',
        '_end_time',
        '_platform_profile',
        '_map_id',
        '_map_version_id',
        '_map_hash',
        '_mission_id',
        '_mission_version',
        '_mission_sha256',
        '_launch_profile',
        '_result_status',
        '_config_snapshot_count',
        '_message',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'experiment_id': 'string',
        'title': 'string',
        'state': 'uint8',
        'created_at': 'string',
        'start_time': 'string',
        'end_time': 'string',
        'platform_profile': 'string',
        'map_id': 'string',
        'map_version_id': 'string',
        'map_hash': 'string',
        'mission_id': 'string',
        'mission_version': 'string',
        'mission_sha256': 'string',
        'launch_profile': 'string',
        'result_status': 'string',
        'config_snapshot_count': 'uint32',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
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
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.experiment_id = kwargs.get('experiment_id', str())
        self.title = kwargs.get('title', str())
        self.state = kwargs.get('state', int())
        self.created_at = kwargs.get('created_at', str())
        self.start_time = kwargs.get('start_time', str())
        self.end_time = kwargs.get('end_time', str())
        self.platform_profile = kwargs.get('platform_profile', str())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.map_hash = kwargs.get('map_hash', str())
        self.mission_id = kwargs.get('mission_id', str())
        self.mission_version = kwargs.get('mission_version', str())
        self.mission_sha256 = kwargs.get('mission_sha256', str())
        self.launch_profile = kwargs.get('launch_profile', str())
        self.result_status = kwargs.get('result_status', str())
        self.config_snapshot_count = kwargs.get('config_snapshot_count', int())
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
        if self.experiment_id != other.experiment_id:
            return False
        if self.title != other.title:
            return False
        if self.state != other.state:
            return False
        if self.created_at != other.created_at:
            return False
        if self.start_time != other.start_time:
            return False
        if self.end_time != other.end_time:
            return False
        if self.platform_profile != other.platform_profile:
            return False
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.map_hash != other.map_hash:
            return False
        if self.mission_id != other.mission_id:
            return False
        if self.mission_version != other.mission_version:
            return False
        if self.mission_sha256 != other.mission_sha256:
            return False
        if self.launch_profile != other.launch_profile:
            return False
        if self.result_status != other.result_status:
            return False
        if self.config_snapshot_count != other.config_snapshot_count:
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
    def title(self):
        """Message field 'title'."""
        return self._title

    @title.setter
    def title(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'title' field must be of type 'str'"
        self._title = value

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
    def created_at(self):
        """Message field 'created_at'."""
        return self._created_at

    @created_at.setter
    def created_at(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'created_at' field must be of type 'str'"
        self._created_at = value

    @builtins.property
    def start_time(self):
        """Message field 'start_time'."""
        return self._start_time

    @start_time.setter
    def start_time(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'start_time' field must be of type 'str'"
        self._start_time = value

    @builtins.property
    def end_time(self):
        """Message field 'end_time'."""
        return self._end_time

    @end_time.setter
    def end_time(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'end_time' field must be of type 'str'"
        self._end_time = value

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
    def config_snapshot_count(self):
        """Message field 'config_snapshot_count'."""
        return self._config_snapshot_count

    @config_snapshot_count.setter
    def config_snapshot_count(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'config_snapshot_count' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'config_snapshot_count' field must be an unsigned integer in [0, 4294967295]"
        self._config_snapshot_count = value

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
