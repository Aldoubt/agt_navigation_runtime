# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/SemanticWaypoint.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SemanticWaypoint(type):
    """Metaclass of message 'SemanticWaypoint'."""

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
                'agt_interfaces.msg.SemanticWaypoint')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__semantic_waypoint
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__semantic_waypoint
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__semantic_waypoint
            cls._TYPE_SUPPORT = module.type_support_msg__msg__semantic_waypoint
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__semantic_waypoint

            from geometry_msgs.msg import Pose
            if Pose.__class__._TYPE_SUPPORT is None:
                Pose.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SemanticWaypoint(metaclass=Metaclass_SemanticWaypoint):
    """Message class 'SemanticWaypoint'."""

    __slots__ = [
        '_id',
        '_name',
        '_role',
        '_pose',
        '_position_tolerance',
        '_yaw_tolerance',
        '_preferred_speed',
        '_tags',
        '_enabled',
    ]

    _fields_and_field_types = {
        'id': 'string',
        'name': 'string',
        'role': 'string',
        'pose': 'geometry_msgs/Pose',
        'position_tolerance': 'float',
        'yaw_tolerance': 'float',
        'preferred_speed': 'float',
        'tags': 'sequence<string>',
        'enabled': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Pose'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.id = kwargs.get('id', str())
        self.name = kwargs.get('name', str())
        self.role = kwargs.get('role', str())
        from geometry_msgs.msg import Pose
        self.pose = kwargs.get('pose', Pose())
        self.position_tolerance = kwargs.get('position_tolerance', float())
        self.yaw_tolerance = kwargs.get('yaw_tolerance', float())
        self.preferred_speed = kwargs.get('preferred_speed', float())
        self.tags = kwargs.get('tags', [])
        self.enabled = kwargs.get('enabled', bool())

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
        if self.id != other.id:
            return False
        if self.name != other.name:
            return False
        if self.role != other.role:
            return False
        if self.pose != other.pose:
            return False
        if self.position_tolerance != other.position_tolerance:
            return False
        if self.yaw_tolerance != other.yaw_tolerance:
            return False
        if self.preferred_speed != other.preferred_speed:
            return False
        if self.tags != other.tags:
            return False
        if self.enabled != other.enabled:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property  # noqa: A003
    def id(self):  # noqa: A003
        """Message field 'id'."""
        return self._id

    @id.setter  # noqa: A003
    def id(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'id' field must be of type 'str'"
        self._id = value

    @builtins.property
    def name(self):
        """Message field 'name'."""
        return self._name

    @name.setter
    def name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'name' field must be of type 'str'"
        self._name = value

    @builtins.property
    def role(self):
        """Message field 'role'."""
        return self._role

    @role.setter
    def role(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'role' field must be of type 'str'"
        self._role = value

    @builtins.property
    def pose(self):
        """Message field 'pose'."""
        return self._pose

    @pose.setter
    def pose(self, value):
        if __debug__:
            from geometry_msgs.msg import Pose
            assert \
                isinstance(value, Pose), \
                "The 'pose' field must be a sub message of type 'Pose'"
        self._pose = value

    @builtins.property
    def position_tolerance(self):
        """Message field 'position_tolerance'."""
        return self._position_tolerance

    @position_tolerance.setter
    def position_tolerance(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'position_tolerance' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'position_tolerance' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._position_tolerance = value

    @builtins.property
    def yaw_tolerance(self):
        """Message field 'yaw_tolerance'."""
        return self._yaw_tolerance

    @yaw_tolerance.setter
    def yaw_tolerance(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yaw_tolerance' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'yaw_tolerance' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._yaw_tolerance = value

    @builtins.property
    def preferred_speed(self):
        """Message field 'preferred_speed'."""
        return self._preferred_speed

    @preferred_speed.setter
    def preferred_speed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'preferred_speed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'preferred_speed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._preferred_speed = value

    @builtins.property
    def tags(self):
        """Message field 'tags'."""
        return self._tags

    @tags.setter
    def tags(self, value):
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
                "The 'tags' field must be a set or sequence and each value of type 'str'"
        self._tags = value

    @builtins.property
    def enabled(self):
        """Message field 'enabled'."""
        return self._enabled

    @enabled.setter
    def enabled(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'enabled' field must be of type 'bool'"
        self._enabled = value
