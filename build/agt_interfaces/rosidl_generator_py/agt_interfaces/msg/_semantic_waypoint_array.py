# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/SemanticWaypointArray.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SemanticWaypointArray(type):
    """Metaclass of message 'SemanticWaypointArray'."""

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
                'agt_interfaces.msg.SemanticWaypointArray')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__semantic_waypoint_array
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__semantic_waypoint_array
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__semantic_waypoint_array
            cls._TYPE_SUPPORT = module.type_support_msg__msg__semantic_waypoint_array
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__semantic_waypoint_array

            from agt_interfaces.msg import SemanticWaypoint
            if SemanticWaypoint.__class__._TYPE_SUPPORT is None:
                SemanticWaypoint.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SemanticWaypointArray(metaclass=Metaclass_SemanticWaypointArray):
    """Message class 'SemanticWaypointArray'."""

    __slots__ = [
        '_header',
        '_schema_version',
        '_map_id',
        '_base_map_sha256',
        '_waypoints',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'schema_version': 'string',
        'map_id': 'string',
        'base_map_sha256': 'string',
        'waypoints': 'sequence<agt_interfaces/SemanticWaypoint>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'SemanticWaypoint')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.schema_version = kwargs.get('schema_version', str())
        self.map_id = kwargs.get('map_id', str())
        self.base_map_sha256 = kwargs.get('base_map_sha256', str())
        self.waypoints = kwargs.get('waypoints', [])

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
        if self.schema_version != other.schema_version:
            return False
        if self.map_id != other.map_id:
            return False
        if self.base_map_sha256 != other.base_map_sha256:
            return False
        if self.waypoints != other.waypoints:
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
    def schema_version(self):
        """Message field 'schema_version'."""
        return self._schema_version

    @schema_version.setter
    def schema_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'schema_version' field must be of type 'str'"
        self._schema_version = value

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
    def base_map_sha256(self):
        """Message field 'base_map_sha256'."""
        return self._base_map_sha256

    @base_map_sha256.setter
    def base_map_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'base_map_sha256' field must be of type 'str'"
        self._base_map_sha256 = value

    @builtins.property
    def waypoints(self):
        """Message field 'waypoints'."""
        return self._waypoints

    @waypoints.setter
    def waypoints(self, value):
        if __debug__:
            from agt_interfaces.msg import SemanticWaypoint
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
                 all(isinstance(v, SemanticWaypoint) for v in value) and
                 True), \
                "The 'waypoints' field must be a set or sequence and each value of type 'SemanticWaypoint'"
        self._waypoints = value
