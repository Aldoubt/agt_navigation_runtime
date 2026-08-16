# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/RobotState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RobotState(type):
    """Metaclass of message 'RobotState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'MODE_UNKNOWN': 0,
        'MODE_IDLE': 1,
        'MODE_SENSOR_ONLY': 2,
        'MODE_MAPPING': 3,
        'MODE_LOCALIZATION_DEBUG': 4,
        'MODE_NAVIGATION': 5,
        'MODE_ERROR': 6,
        'NAV2_UNKNOWN': 0,
        'NAV2_INACTIVE': 1,
        'NAV2_ACTIVE': 2,
        'NAV2_ERROR': 3,
        'CHASSIS_MODE_UNKNOWN': 0,
        'CHASSIS_MODE_MONITOR': 1,
        'CHASSIS_MODE_CONTROL': 2,
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
                'agt_interfaces.msg.RobotState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__robot_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__robot_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__robot_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__robot_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__robot_state

            from agt_interfaces.msg import BagSessionSummary
            if BagSessionSummary.__class__._TYPE_SUPPORT is None:
                BagSessionSummary.__class__.__import_type_support__()

            from agt_interfaces.msg import LocalizationStatus
            if LocalizationStatus.__class__._TYPE_SUPPORT is None:
                LocalizationStatus.__class__.__import_type_support__()

            from agt_interfaces.msg import MapVersionSummary
            if MapVersionSummary.__class__._TYPE_SUPPORT is None:
                MapVersionSummary.__class__.__import_type_support__()

            from agt_interfaces.msg import MissionStatus
            if MissionStatus.__class__._TYPE_SUPPORT is None:
                MissionStatus.__class__.__import_type_support__()

            from agt_interfaces.msg import SystemHealth
            if SystemHealth.__class__._TYPE_SUPPORT is None:
                SystemHealth.__class__.__import_type_support__()

            from agt_interfaces.msg import TaskReadiness
            if TaskReadiness.__class__._TYPE_SUPPORT is None:
                TaskReadiness.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'MODE_UNKNOWN': cls.__constants['MODE_UNKNOWN'],
            'MODE_IDLE': cls.__constants['MODE_IDLE'],
            'MODE_SENSOR_ONLY': cls.__constants['MODE_SENSOR_ONLY'],
            'MODE_MAPPING': cls.__constants['MODE_MAPPING'],
            'MODE_LOCALIZATION_DEBUG': cls.__constants['MODE_LOCALIZATION_DEBUG'],
            'MODE_NAVIGATION': cls.__constants['MODE_NAVIGATION'],
            'MODE_ERROR': cls.__constants['MODE_ERROR'],
            'NAV2_UNKNOWN': cls.__constants['NAV2_UNKNOWN'],
            'NAV2_INACTIVE': cls.__constants['NAV2_INACTIVE'],
            'NAV2_ACTIVE': cls.__constants['NAV2_ACTIVE'],
            'NAV2_ERROR': cls.__constants['NAV2_ERROR'],
            'CHASSIS_MODE_UNKNOWN': cls.__constants['CHASSIS_MODE_UNKNOWN'],
            'CHASSIS_MODE_MONITOR': cls.__constants['CHASSIS_MODE_MONITOR'],
            'CHASSIS_MODE_CONTROL': cls.__constants['CHASSIS_MODE_CONTROL'],
        }

    @property
    def MODE_UNKNOWN(self):
        """Message constant 'MODE_UNKNOWN'."""
        return Metaclass_RobotState.__constants['MODE_UNKNOWN']

    @property
    def MODE_IDLE(self):
        """Message constant 'MODE_IDLE'."""
        return Metaclass_RobotState.__constants['MODE_IDLE']

    @property
    def MODE_SENSOR_ONLY(self):
        """Message constant 'MODE_SENSOR_ONLY'."""
        return Metaclass_RobotState.__constants['MODE_SENSOR_ONLY']

    @property
    def MODE_MAPPING(self):
        """Message constant 'MODE_MAPPING'."""
        return Metaclass_RobotState.__constants['MODE_MAPPING']

    @property
    def MODE_LOCALIZATION_DEBUG(self):
        """Message constant 'MODE_LOCALIZATION_DEBUG'."""
        return Metaclass_RobotState.__constants['MODE_LOCALIZATION_DEBUG']

    @property
    def MODE_NAVIGATION(self):
        """Message constant 'MODE_NAVIGATION'."""
        return Metaclass_RobotState.__constants['MODE_NAVIGATION']

    @property
    def MODE_ERROR(self):
        """Message constant 'MODE_ERROR'."""
        return Metaclass_RobotState.__constants['MODE_ERROR']

    @property
    def NAV2_UNKNOWN(self):
        """Message constant 'NAV2_UNKNOWN'."""
        return Metaclass_RobotState.__constants['NAV2_UNKNOWN']

    @property
    def NAV2_INACTIVE(self):
        """Message constant 'NAV2_INACTIVE'."""
        return Metaclass_RobotState.__constants['NAV2_INACTIVE']

    @property
    def NAV2_ACTIVE(self):
        """Message constant 'NAV2_ACTIVE'."""
        return Metaclass_RobotState.__constants['NAV2_ACTIVE']

    @property
    def NAV2_ERROR(self):
        """Message constant 'NAV2_ERROR'."""
        return Metaclass_RobotState.__constants['NAV2_ERROR']

    @property
    def CHASSIS_MODE_UNKNOWN(self):
        """Message constant 'CHASSIS_MODE_UNKNOWN'."""
        return Metaclass_RobotState.__constants['CHASSIS_MODE_UNKNOWN']

    @property
    def CHASSIS_MODE_MONITOR(self):
        """Message constant 'CHASSIS_MODE_MONITOR'."""
        return Metaclass_RobotState.__constants['CHASSIS_MODE_MONITOR']

    @property
    def CHASSIS_MODE_CONTROL(self):
        """Message constant 'CHASSIS_MODE_CONTROL'."""
        return Metaclass_RobotState.__constants['CHASSIS_MODE_CONTROL']


class RobotState(metaclass=Metaclass_RobotState):
    """
    Message class 'RobotState'.

    Constants:
      MODE_UNKNOWN
      MODE_IDLE
      MODE_SENSOR_ONLY
      MODE_MAPPING
      MODE_LOCALIZATION_DEBUG
      MODE_NAVIGATION
      MODE_ERROR
      NAV2_UNKNOWN
      NAV2_INACTIVE
      NAV2_ACTIVE
      NAV2_ERROR
      CHASSIS_MODE_UNKNOWN
      CHASSIS_MODE_MONITOR
      CHASSIS_MODE_CONTROL
    """

    __slots__ = [
        '_header',
        '_revision',
        '_system_mode',
        '_active_profile',
        '_managed_process_count',
        '_running_process_count',
        '_system_health_known',
        '_system_health_freshness_s',
        '_system_health',
        '_task_readiness_known',
        '_task_readiness_freshness_s',
        '_task_readiness',
        '_active_map_known',
        '_active_map_freshness_s',
        '_active_map',
        '_localization_status_known',
        '_localization_freshness_s',
        '_localization',
        '_mission_status_known',
        '_mission_freshness_s',
        '_mission',
        '_nav2_state',
        '_nav2_freshness_s',
        '_safety_status_known',
        '_safety_motion_enabled',
        '_emergency_stop',
        '_estop_latched',
        '_navigation_ready',
        '_safety_freshness_s',
        '_chassis_status_known',
        '_chassis_connected',
        '_chassis_control_mode',
        '_chassis_status_freshness_s',
        '_chassis_odometry_freshness_s',
        '_bag_status_known',
        '_bag_freshness_s',
        '_bag_session',
        '_error_code',
        '_blocker_codes',
        '_blocker_messages',
        '_message',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'revision': 'uint64',
        'system_mode': 'uint8',
        'active_profile': 'string',
        'managed_process_count': 'uint32',
        'running_process_count': 'uint32',
        'system_health_known': 'boolean',
        'system_health_freshness_s': 'double',
        'system_health': 'agt_interfaces/SystemHealth',
        'task_readiness_known': 'boolean',
        'task_readiness_freshness_s': 'double',
        'task_readiness': 'agt_interfaces/TaskReadiness',
        'active_map_known': 'boolean',
        'active_map_freshness_s': 'double',
        'active_map': 'agt_interfaces/MapVersionSummary',
        'localization_status_known': 'boolean',
        'localization_freshness_s': 'double',
        'localization': 'agt_interfaces/LocalizationStatus',
        'mission_status_known': 'boolean',
        'mission_freshness_s': 'double',
        'mission': 'agt_interfaces/MissionStatus',
        'nav2_state': 'uint8',
        'nav2_freshness_s': 'double',
        'safety_status_known': 'boolean',
        'safety_motion_enabled': 'boolean',
        'emergency_stop': 'boolean',
        'estop_latched': 'boolean',
        'navigation_ready': 'boolean',
        'safety_freshness_s': 'double',
        'chassis_status_known': 'boolean',
        'chassis_connected': 'boolean',
        'chassis_control_mode': 'uint8',
        'chassis_status_freshness_s': 'double',
        'chassis_odometry_freshness_s': 'double',
        'bag_status_known': 'boolean',
        'bag_freshness_s': 'double',
        'bag_session': 'agt_interfaces/BagSessionSummary',
        'error_code': 'uint16',
        'blocker_codes': 'sequence<string>',
        'blocker_messages': 'sequence<string>',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'SystemHealth'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'TaskReadiness'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'MapVersionSummary'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'LocalizationStatus'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'MissionStatus'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'BagSessionSummary'),  # noqa: E501
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
        self.revision = kwargs.get('revision', int())
        self.system_mode = kwargs.get('system_mode', int())
        self.active_profile = kwargs.get('active_profile', str())
        self.managed_process_count = kwargs.get('managed_process_count', int())
        self.running_process_count = kwargs.get('running_process_count', int())
        self.system_health_known = kwargs.get('system_health_known', bool())
        self.system_health_freshness_s = kwargs.get('system_health_freshness_s', float())
        from agt_interfaces.msg import SystemHealth
        self.system_health = kwargs.get('system_health', SystemHealth())
        self.task_readiness_known = kwargs.get('task_readiness_known', bool())
        self.task_readiness_freshness_s = kwargs.get('task_readiness_freshness_s', float())
        from agt_interfaces.msg import TaskReadiness
        self.task_readiness = kwargs.get('task_readiness', TaskReadiness())
        self.active_map_known = kwargs.get('active_map_known', bool())
        self.active_map_freshness_s = kwargs.get('active_map_freshness_s', float())
        from agt_interfaces.msg import MapVersionSummary
        self.active_map = kwargs.get('active_map', MapVersionSummary())
        self.localization_status_known = kwargs.get('localization_status_known', bool())
        self.localization_freshness_s = kwargs.get('localization_freshness_s', float())
        from agt_interfaces.msg import LocalizationStatus
        self.localization = kwargs.get('localization', LocalizationStatus())
        self.mission_status_known = kwargs.get('mission_status_known', bool())
        self.mission_freshness_s = kwargs.get('mission_freshness_s', float())
        from agt_interfaces.msg import MissionStatus
        self.mission = kwargs.get('mission', MissionStatus())
        self.nav2_state = kwargs.get('nav2_state', int())
        self.nav2_freshness_s = kwargs.get('nav2_freshness_s', float())
        self.safety_status_known = kwargs.get('safety_status_known', bool())
        self.safety_motion_enabled = kwargs.get('safety_motion_enabled', bool())
        self.emergency_stop = kwargs.get('emergency_stop', bool())
        self.estop_latched = kwargs.get('estop_latched', bool())
        self.navigation_ready = kwargs.get('navigation_ready', bool())
        self.safety_freshness_s = kwargs.get('safety_freshness_s', float())
        self.chassis_status_known = kwargs.get('chassis_status_known', bool())
        self.chassis_connected = kwargs.get('chassis_connected', bool())
        self.chassis_control_mode = kwargs.get('chassis_control_mode', int())
        self.chassis_status_freshness_s = kwargs.get('chassis_status_freshness_s', float())
        self.chassis_odometry_freshness_s = kwargs.get('chassis_odometry_freshness_s', float())
        self.bag_status_known = kwargs.get('bag_status_known', bool())
        self.bag_freshness_s = kwargs.get('bag_freshness_s', float())
        from agt_interfaces.msg import BagSessionSummary
        self.bag_session = kwargs.get('bag_session', BagSessionSummary())
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
        if self.revision != other.revision:
            return False
        if self.system_mode != other.system_mode:
            return False
        if self.active_profile != other.active_profile:
            return False
        if self.managed_process_count != other.managed_process_count:
            return False
        if self.running_process_count != other.running_process_count:
            return False
        if self.system_health_known != other.system_health_known:
            return False
        if self.system_health_freshness_s != other.system_health_freshness_s:
            return False
        if self.system_health != other.system_health:
            return False
        if self.task_readiness_known != other.task_readiness_known:
            return False
        if self.task_readiness_freshness_s != other.task_readiness_freshness_s:
            return False
        if self.task_readiness != other.task_readiness:
            return False
        if self.active_map_known != other.active_map_known:
            return False
        if self.active_map_freshness_s != other.active_map_freshness_s:
            return False
        if self.active_map != other.active_map:
            return False
        if self.localization_status_known != other.localization_status_known:
            return False
        if self.localization_freshness_s != other.localization_freshness_s:
            return False
        if self.localization != other.localization:
            return False
        if self.mission_status_known != other.mission_status_known:
            return False
        if self.mission_freshness_s != other.mission_freshness_s:
            return False
        if self.mission != other.mission:
            return False
        if self.nav2_state != other.nav2_state:
            return False
        if self.nav2_freshness_s != other.nav2_freshness_s:
            return False
        if self.safety_status_known != other.safety_status_known:
            return False
        if self.safety_motion_enabled != other.safety_motion_enabled:
            return False
        if self.emergency_stop != other.emergency_stop:
            return False
        if self.estop_latched != other.estop_latched:
            return False
        if self.navigation_ready != other.navigation_ready:
            return False
        if self.safety_freshness_s != other.safety_freshness_s:
            return False
        if self.chassis_status_known != other.chassis_status_known:
            return False
        if self.chassis_connected != other.chassis_connected:
            return False
        if self.chassis_control_mode != other.chassis_control_mode:
            return False
        if self.chassis_status_freshness_s != other.chassis_status_freshness_s:
            return False
        if self.chassis_odometry_freshness_s != other.chassis_odometry_freshness_s:
            return False
        if self.bag_status_known != other.bag_status_known:
            return False
        if self.bag_freshness_s != other.bag_freshness_s:
            return False
        if self.bag_session != other.bag_session:
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
    def revision(self):
        """Message field 'revision'."""
        return self._revision

    @revision.setter
    def revision(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'revision' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'revision' field must be an unsigned integer in [0, 18446744073709551615]"
        self._revision = value

    @builtins.property
    def system_mode(self):
        """Message field 'system_mode'."""
        return self._system_mode

    @system_mode.setter
    def system_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'system_mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'system_mode' field must be an unsigned integer in [0, 255]"
        self._system_mode = value

    @builtins.property
    def active_profile(self):
        """Message field 'active_profile'."""
        return self._active_profile

    @active_profile.setter
    def active_profile(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'active_profile' field must be of type 'str'"
        self._active_profile = value

    @builtins.property
    def managed_process_count(self):
        """Message field 'managed_process_count'."""
        return self._managed_process_count

    @managed_process_count.setter
    def managed_process_count(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'managed_process_count' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'managed_process_count' field must be an unsigned integer in [0, 4294967295]"
        self._managed_process_count = value

    @builtins.property
    def running_process_count(self):
        """Message field 'running_process_count'."""
        return self._running_process_count

    @running_process_count.setter
    def running_process_count(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'running_process_count' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'running_process_count' field must be an unsigned integer in [0, 4294967295]"
        self._running_process_count = value

    @builtins.property
    def system_health_known(self):
        """Message field 'system_health_known'."""
        return self._system_health_known

    @system_health_known.setter
    def system_health_known(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'system_health_known' field must be of type 'bool'"
        self._system_health_known = value

    @builtins.property
    def system_health_freshness_s(self):
        """Message field 'system_health_freshness_s'."""
        return self._system_health_freshness_s

    @system_health_freshness_s.setter
    def system_health_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'system_health_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'system_health_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._system_health_freshness_s = value

    @builtins.property
    def system_health(self):
        """Message field 'system_health'."""
        return self._system_health

    @system_health.setter
    def system_health(self, value):
        if __debug__:
            from agt_interfaces.msg import SystemHealth
            assert \
                isinstance(value, SystemHealth), \
                "The 'system_health' field must be a sub message of type 'SystemHealth'"
        self._system_health = value

    @builtins.property
    def task_readiness_known(self):
        """Message field 'task_readiness_known'."""
        return self._task_readiness_known

    @task_readiness_known.setter
    def task_readiness_known(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'task_readiness_known' field must be of type 'bool'"
        self._task_readiness_known = value

    @builtins.property
    def task_readiness_freshness_s(self):
        """Message field 'task_readiness_freshness_s'."""
        return self._task_readiness_freshness_s

    @task_readiness_freshness_s.setter
    def task_readiness_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'task_readiness_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'task_readiness_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._task_readiness_freshness_s = value

    @builtins.property
    def task_readiness(self):
        """Message field 'task_readiness'."""
        return self._task_readiness

    @task_readiness.setter
    def task_readiness(self, value):
        if __debug__:
            from agt_interfaces.msg import TaskReadiness
            assert \
                isinstance(value, TaskReadiness), \
                "The 'task_readiness' field must be a sub message of type 'TaskReadiness'"
        self._task_readiness = value

    @builtins.property
    def active_map_known(self):
        """Message field 'active_map_known'."""
        return self._active_map_known

    @active_map_known.setter
    def active_map_known(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'active_map_known' field must be of type 'bool'"
        self._active_map_known = value

    @builtins.property
    def active_map_freshness_s(self):
        """Message field 'active_map_freshness_s'."""
        return self._active_map_freshness_s

    @active_map_freshness_s.setter
    def active_map_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'active_map_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'active_map_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._active_map_freshness_s = value

    @builtins.property
    def active_map(self):
        """Message field 'active_map'."""
        return self._active_map

    @active_map.setter
    def active_map(self, value):
        if __debug__:
            from agt_interfaces.msg import MapVersionSummary
            assert \
                isinstance(value, MapVersionSummary), \
                "The 'active_map' field must be a sub message of type 'MapVersionSummary'"
        self._active_map = value

    @builtins.property
    def localization_status_known(self):
        """Message field 'localization_status_known'."""
        return self._localization_status_known

    @localization_status_known.setter
    def localization_status_known(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'localization_status_known' field must be of type 'bool'"
        self._localization_status_known = value

    @builtins.property
    def localization_freshness_s(self):
        """Message field 'localization_freshness_s'."""
        return self._localization_freshness_s

    @localization_freshness_s.setter
    def localization_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'localization_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'localization_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._localization_freshness_s = value

    @builtins.property
    def localization(self):
        """Message field 'localization'."""
        return self._localization

    @localization.setter
    def localization(self, value):
        if __debug__:
            from agt_interfaces.msg import LocalizationStatus
            assert \
                isinstance(value, LocalizationStatus), \
                "The 'localization' field must be a sub message of type 'LocalizationStatus'"
        self._localization = value

    @builtins.property
    def mission_status_known(self):
        """Message field 'mission_status_known'."""
        return self._mission_status_known

    @mission_status_known.setter
    def mission_status_known(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'mission_status_known' field must be of type 'bool'"
        self._mission_status_known = value

    @builtins.property
    def mission_freshness_s(self):
        """Message field 'mission_freshness_s'."""
        return self._mission_freshness_s

    @mission_freshness_s.setter
    def mission_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mission_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mission_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mission_freshness_s = value

    @builtins.property
    def mission(self):
        """Message field 'mission'."""
        return self._mission

    @mission.setter
    def mission(self, value):
        if __debug__:
            from agt_interfaces.msg import MissionStatus
            assert \
                isinstance(value, MissionStatus), \
                "The 'mission' field must be a sub message of type 'MissionStatus'"
        self._mission = value

    @builtins.property
    def nav2_state(self):
        """Message field 'nav2_state'."""
        return self._nav2_state

    @nav2_state.setter
    def nav2_state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'nav2_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'nav2_state' field must be an unsigned integer in [0, 255]"
        self._nav2_state = value

    @builtins.property
    def nav2_freshness_s(self):
        """Message field 'nav2_freshness_s'."""
        return self._nav2_freshness_s

    @nav2_freshness_s.setter
    def nav2_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'nav2_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'nav2_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._nav2_freshness_s = value

    @builtins.property
    def safety_status_known(self):
        """Message field 'safety_status_known'."""
        return self._safety_status_known

    @safety_status_known.setter
    def safety_status_known(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'safety_status_known' field must be of type 'bool'"
        self._safety_status_known = value

    @builtins.property
    def safety_motion_enabled(self):
        """Message field 'safety_motion_enabled'."""
        return self._safety_motion_enabled

    @safety_motion_enabled.setter
    def safety_motion_enabled(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'safety_motion_enabled' field must be of type 'bool'"
        self._safety_motion_enabled = value

    @builtins.property
    def emergency_stop(self):
        """Message field 'emergency_stop'."""
        return self._emergency_stop

    @emergency_stop.setter
    def emergency_stop(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'emergency_stop' field must be of type 'bool'"
        self._emergency_stop = value

    @builtins.property
    def estop_latched(self):
        """Message field 'estop_latched'."""
        return self._estop_latched

    @estop_latched.setter
    def estop_latched(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'estop_latched' field must be of type 'bool'"
        self._estop_latched = value

    @builtins.property
    def navigation_ready(self):
        """Message field 'navigation_ready'."""
        return self._navigation_ready

    @navigation_ready.setter
    def navigation_ready(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'navigation_ready' field must be of type 'bool'"
        self._navigation_ready = value

    @builtins.property
    def safety_freshness_s(self):
        """Message field 'safety_freshness_s'."""
        return self._safety_freshness_s

    @safety_freshness_s.setter
    def safety_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'safety_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'safety_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._safety_freshness_s = value

    @builtins.property
    def chassis_status_known(self):
        """Message field 'chassis_status_known'."""
        return self._chassis_status_known

    @chassis_status_known.setter
    def chassis_status_known(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'chassis_status_known' field must be of type 'bool'"
        self._chassis_status_known = value

    @builtins.property
    def chassis_connected(self):
        """Message field 'chassis_connected'."""
        return self._chassis_connected

    @chassis_connected.setter
    def chassis_connected(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'chassis_connected' field must be of type 'bool'"
        self._chassis_connected = value

    @builtins.property
    def chassis_control_mode(self):
        """Message field 'chassis_control_mode'."""
        return self._chassis_control_mode

    @chassis_control_mode.setter
    def chassis_control_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'chassis_control_mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'chassis_control_mode' field must be an unsigned integer in [0, 255]"
        self._chassis_control_mode = value

    @builtins.property
    def chassis_status_freshness_s(self):
        """Message field 'chassis_status_freshness_s'."""
        return self._chassis_status_freshness_s

    @chassis_status_freshness_s.setter
    def chassis_status_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'chassis_status_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'chassis_status_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._chassis_status_freshness_s = value

    @builtins.property
    def chassis_odometry_freshness_s(self):
        """Message field 'chassis_odometry_freshness_s'."""
        return self._chassis_odometry_freshness_s

    @chassis_odometry_freshness_s.setter
    def chassis_odometry_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'chassis_odometry_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'chassis_odometry_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._chassis_odometry_freshness_s = value

    @builtins.property
    def bag_status_known(self):
        """Message field 'bag_status_known'."""
        return self._bag_status_known

    @bag_status_known.setter
    def bag_status_known(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'bag_status_known' field must be of type 'bool'"
        self._bag_status_known = value

    @builtins.property
    def bag_freshness_s(self):
        """Message field 'bag_freshness_s'."""
        return self._bag_freshness_s

    @bag_freshness_s.setter
    def bag_freshness_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bag_freshness_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'bag_freshness_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._bag_freshness_s = value

    @builtins.property
    def bag_session(self):
        """Message field 'bag_session'."""
        return self._bag_session

    @bag_session.setter
    def bag_session(self, value):
        if __debug__:
            from agt_interfaces.msg import BagSessionSummary
            assert \
                isinstance(value, BagSessionSummary), \
                "The 'bag_session' field must be a sub message of type 'BagSessionSummary'"
        self._bag_session = value

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
