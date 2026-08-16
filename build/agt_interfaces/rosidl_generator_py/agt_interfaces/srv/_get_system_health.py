# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:srv/GetSystemHealth.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetSystemHealth_Request(type):
    """Metaclass of message 'GetSystemHealth_Request'."""

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
                'agt_interfaces.srv.GetSystemHealth_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_system_health__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_system_health__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_system_health__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_system_health__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_system_health__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetSystemHealth_Request(metaclass=Metaclass_GetSystemHealth_Request):
    """Message class 'GetSystemHealth_Request'."""

    __slots__ = [
        '_include_optional',
    ]

    _fields_and_field_types = {
        'include_optional': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.include_optional = kwargs.get('include_optional', bool())

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
        if self.include_optional != other.include_optional:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def include_optional(self):
        """Message field 'include_optional'."""
        return self._include_optional

    @include_optional.setter
    def include_optional(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'include_optional' field must be of type 'bool'"
        self._include_optional = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_GetSystemHealth_Response(type):
    """Metaclass of message 'GetSystemHealth_Response'."""

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
                'agt_interfaces.srv.GetSystemHealth_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_system_health__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_system_health__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_system_health__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_system_health__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_system_health__response

            from agt_interfaces.msg import SystemHealth
            if SystemHealth.__class__._TYPE_SUPPORT is None:
                SystemHealth.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetSystemHealth_Response(metaclass=Metaclass_GetSystemHealth_Response):
    """Message class 'GetSystemHealth_Response'."""

    __slots__ = [
        '_health',
    ]

    _fields_and_field_types = {
        'health': 'agt_interfaces/SystemHealth',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'SystemHealth'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from agt_interfaces.msg import SystemHealth
        self.health = kwargs.get('health', SystemHealth())

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
        if self.health != other.health:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def health(self):
        """Message field 'health'."""
        return self._health

    @health.setter
    def health(self, value):
        if __debug__:
            from agt_interfaces.msg import SystemHealth
            assert \
                isinstance(value, SystemHealth), \
                "The 'health' field must be a sub message of type 'SystemHealth'"
        self._health = value


class Metaclass_GetSystemHealth(type):
    """Metaclass of service 'GetSystemHealth'."""

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
                'agt_interfaces.srv.GetSystemHealth')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_system_health

            from agt_interfaces.srv import _get_system_health
            if _get_system_health.Metaclass_GetSystemHealth_Request._TYPE_SUPPORT is None:
                _get_system_health.Metaclass_GetSystemHealth_Request.__import_type_support__()
            if _get_system_health.Metaclass_GetSystemHealth_Response._TYPE_SUPPORT is None:
                _get_system_health.Metaclass_GetSystemHealth_Response.__import_type_support__()


class GetSystemHealth(metaclass=Metaclass_GetSystemHealth):
    from agt_interfaces.srv._get_system_health import GetSystemHealth_Request as Request
    from agt_interfaces.srv._get_system_health import GetSystemHealth_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
