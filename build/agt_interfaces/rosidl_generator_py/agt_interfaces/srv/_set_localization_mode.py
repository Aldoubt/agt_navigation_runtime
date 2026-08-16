# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:srv/SetLocalizationMode.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetLocalizationMode_Request(type):
    """Metaclass of message 'SetLocalizationMode_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'MODE_MANUAL_ONLY': 0,
        'MODE_AUTO_ON_START': 1,
        'MODE_AUTO_RECOVERY': 2,
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
                'agt_interfaces.srv.SetLocalizationMode_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_localization_mode__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_localization_mode__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_localization_mode__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_localization_mode__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_localization_mode__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'MODE_MANUAL_ONLY': cls.__constants['MODE_MANUAL_ONLY'],
            'MODE_AUTO_ON_START': cls.__constants['MODE_AUTO_ON_START'],
            'MODE_AUTO_RECOVERY': cls.__constants['MODE_AUTO_RECOVERY'],
        }

    @property
    def MODE_MANUAL_ONLY(self):
        """Message constant 'MODE_MANUAL_ONLY'."""
        return Metaclass_SetLocalizationMode_Request.__constants['MODE_MANUAL_ONLY']

    @property
    def MODE_AUTO_ON_START(self):
        """Message constant 'MODE_AUTO_ON_START'."""
        return Metaclass_SetLocalizationMode_Request.__constants['MODE_AUTO_ON_START']

    @property
    def MODE_AUTO_RECOVERY(self):
        """Message constant 'MODE_AUTO_RECOVERY'."""
        return Metaclass_SetLocalizationMode_Request.__constants['MODE_AUTO_RECOVERY']


class SetLocalizationMode_Request(metaclass=Metaclass_SetLocalizationMode_Request):
    """
    Message class 'SetLocalizationMode_Request'.

    Constants:
      MODE_MANUAL_ONLY
      MODE_AUTO_ON_START
      MODE_AUTO_RECOVERY
    """

    __slots__ = [
        '_mode',
    ]

    _fields_and_field_types = {
        'mode': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.mode = kwargs.get('mode', int())

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetLocalizationMode_Response(type):
    """Metaclass of message 'SetLocalizationMode_Response'."""

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
                'agt_interfaces.srv.SetLocalizationMode_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_localization_mode__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_localization_mode__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_localization_mode__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_localization_mode__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_localization_mode__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetLocalizationMode_Response(metaclass=Metaclass_SetLocalizationMode_Response):
    """Message class 'SetLocalizationMode_Response'."""

    __slots__ = [
        '_success',
        '_error_code',
        '_active_mode',
        '_attempts',
        '_message',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'active_mode': 'uint8',
        'attempts': 'uint32',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        self.active_mode = kwargs.get('active_mode', int())
        self.attempts = kwargs.get('attempts', int())
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
        if self.active_mode != other.active_mode:
            return False
        if self.attempts != other.attempts:
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
    def active_mode(self):
        """Message field 'active_mode'."""
        return self._active_mode

    @active_mode.setter
    def active_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'active_mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'active_mode' field must be an unsigned integer in [0, 255]"
        self._active_mode = value

    @builtins.property
    def attempts(self):
        """Message field 'attempts'."""
        return self._attempts

    @attempts.setter
    def attempts(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'attempts' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'attempts' field must be an unsigned integer in [0, 4294967295]"
        self._attempts = value

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


class Metaclass_SetLocalizationMode(type):
    """Metaclass of service 'SetLocalizationMode'."""

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
                'agt_interfaces.srv.SetLocalizationMode')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_localization_mode

            from agt_interfaces.srv import _set_localization_mode
            if _set_localization_mode.Metaclass_SetLocalizationMode_Request._TYPE_SUPPORT is None:
                _set_localization_mode.Metaclass_SetLocalizationMode_Request.__import_type_support__()
            if _set_localization_mode.Metaclass_SetLocalizationMode_Response._TYPE_SUPPORT is None:
                _set_localization_mode.Metaclass_SetLocalizationMode_Response.__import_type_support__()


class SetLocalizationMode(metaclass=Metaclass_SetLocalizationMode):
    from agt_interfaces.srv._set_localization_mode import SetLocalizationMode_Request as Request
    from agt_interfaces.srv._set_localization_mode import SetLocalizationMode_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
