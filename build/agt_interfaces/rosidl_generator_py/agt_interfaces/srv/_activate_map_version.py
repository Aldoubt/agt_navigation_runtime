# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:srv/ActivateMapVersion.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ActivateMapVersion_Request(type):
    """Metaclass of message 'ActivateMapVersion_Request'."""

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
                'agt_interfaces.srv.ActivateMapVersion_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__activate_map_version__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__activate_map_version__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__activate_map_version__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__activate_map_version__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__activate_map_version__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ActivateMapVersion_Request(metaclass=Metaclass_ActivateMapVersion_Request):
    """Message class 'ActivateMapVersion_Request'."""

    __slots__ = [
        '_map_id',
        '_map_version_id',
        '_client_request_id',
    ]

    _fields_and_field_types = {
        'map_id': 'string',
        'map_version_id': 'string',
        'client_request_id': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.client_request_id = kwargs.get('client_request_id', str())

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
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.client_request_id != other.client_request_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

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
    def client_request_id(self):
        """Message field 'client_request_id'."""
        return self._client_request_id

    @client_request_id.setter
    def client_request_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'client_request_id' field must be of type 'str'"
        self._client_request_id = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ActivateMapVersion_Response(type):
    """Metaclass of message 'ActivateMapVersion_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ERROR_NONE': 0,
        'ERROR_INVALID_REQUEST': 1,
        'ERROR_NOT_FOUND': 2,
        'ERROR_VALIDATION_FAILED': 3,
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
                'agt_interfaces.srv.ActivateMapVersion_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__activate_map_version__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__activate_map_version__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__activate_map_version__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__activate_map_version__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__activate_map_version__response

            from agt_interfaces.msg import MapVersionSummary
            if MapVersionSummary.__class__._TYPE_SUPPORT is None:
                MapVersionSummary.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_INVALID_REQUEST': cls.__constants['ERROR_INVALID_REQUEST'],
            'ERROR_NOT_FOUND': cls.__constants['ERROR_NOT_FOUND'],
            'ERROR_VALIDATION_FAILED': cls.__constants['ERROR_VALIDATION_FAILED'],
            'ERROR_INTERNAL': cls.__constants['ERROR_INTERNAL'],
        }

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_ActivateMapVersion_Response.__constants['ERROR_NONE']

    @property
    def ERROR_INVALID_REQUEST(self):
        """Message constant 'ERROR_INVALID_REQUEST'."""
        return Metaclass_ActivateMapVersion_Response.__constants['ERROR_INVALID_REQUEST']

    @property
    def ERROR_NOT_FOUND(self):
        """Message constant 'ERROR_NOT_FOUND'."""
        return Metaclass_ActivateMapVersion_Response.__constants['ERROR_NOT_FOUND']

    @property
    def ERROR_VALIDATION_FAILED(self):
        """Message constant 'ERROR_VALIDATION_FAILED'."""
        return Metaclass_ActivateMapVersion_Response.__constants['ERROR_VALIDATION_FAILED']

    @property
    def ERROR_INTERNAL(self):
        """Message constant 'ERROR_INTERNAL'."""
        return Metaclass_ActivateMapVersion_Response.__constants['ERROR_INTERNAL']


class ActivateMapVersion_Response(metaclass=Metaclass_ActivateMapVersion_Response):
    """
    Message class 'ActivateMapVersion_Response'.

    Constants:
      ERROR_NONE
      ERROR_INVALID_REQUEST
      ERROR_NOT_FOUND
      ERROR_VALIDATION_FAILED
      ERROR_INTERNAL
    """

    __slots__ = [
        '_success',
        '_error_code',
        '_map_id',
        '_map_version_id',
        '_state',
        '_blocker_codes',
        '_blocker_messages',
        '_operator_messages',
        '_technical_messages',
        '_version',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'map_id': 'string',
        'map_version_id': 'string',
        'state': 'string',
        'blocker_codes': 'sequence<string>',
        'blocker_messages': 'sequence<string>',
        'operator_messages': 'sequence<string>',
        'technical_messages': 'sequence<string>',
        'version': 'agt_interfaces/MapVersionSummary',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'MapVersionSummary'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.state = kwargs.get('state', str())
        self.blocker_codes = kwargs.get('blocker_codes', [])
        self.blocker_messages = kwargs.get('blocker_messages', [])
        self.operator_messages = kwargs.get('operator_messages', [])
        self.technical_messages = kwargs.get('technical_messages', [])
        from agt_interfaces.msg import MapVersionSummary
        self.version = kwargs.get('version', MapVersionSummary())

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
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.state != other.state:
            return False
        if self.blocker_codes != other.blocker_codes:
            return False
        if self.blocker_messages != other.blocker_messages:
            return False
        if self.operator_messages != other.operator_messages:
            return False
        if self.technical_messages != other.technical_messages:
            return False
        if self.version != other.version:
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
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'state' field must be of type 'str'"
        self._state = value

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
    def operator_messages(self):
        """Message field 'operator_messages'."""
        return self._operator_messages

    @operator_messages.setter
    def operator_messages(self, value):
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
                "The 'operator_messages' field must be a set or sequence and each value of type 'str'"
        self._operator_messages = value

    @builtins.property
    def technical_messages(self):
        """Message field 'technical_messages'."""
        return self._technical_messages

    @technical_messages.setter
    def technical_messages(self, value):
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
                "The 'technical_messages' field must be a set or sequence and each value of type 'str'"
        self._technical_messages = value

    @builtins.property
    def version(self):
        """Message field 'version'."""
        return self._version

    @version.setter
    def version(self, value):
        if __debug__:
            from agt_interfaces.msg import MapVersionSummary
            assert \
                isinstance(value, MapVersionSummary), \
                "The 'version' field must be a sub message of type 'MapVersionSummary'"
        self._version = value


class Metaclass_ActivateMapVersion(type):
    """Metaclass of service 'ActivateMapVersion'."""

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
                'agt_interfaces.srv.ActivateMapVersion')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__activate_map_version

            from agt_interfaces.srv import _activate_map_version
            if _activate_map_version.Metaclass_ActivateMapVersion_Request._TYPE_SUPPORT is None:
                _activate_map_version.Metaclass_ActivateMapVersion_Request.__import_type_support__()
            if _activate_map_version.Metaclass_ActivateMapVersion_Response._TYPE_SUPPORT is None:
                _activate_map_version.Metaclass_ActivateMapVersion_Response.__import_type_support__()


class ActivateMapVersion(metaclass=Metaclass_ActivateMapVersion):
    from agt_interfaces.srv._activate_map_version import ActivateMapVersion_Request as Request
    from agt_interfaces.srv._activate_map_version import ActivateMapVersion_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
