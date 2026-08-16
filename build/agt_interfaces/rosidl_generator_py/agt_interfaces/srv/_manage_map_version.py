# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:srv/ManageMapVersion.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ManageMapVersion_Request(type):
    """Metaclass of message 'ManageMapVersion_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'OP_GET_ACTIVE': 0,
        'OP_VALIDATE': 1,
        'OP_ACTIVATE': 2,
        'OP_PIN': 3,
        'OP_UNPIN': 4,
        'OP_ARCHIVE': 5,
        'OP_SOFT_DELETE': 6,
        'OP_PURGE': 7,
        'OP_IMPORT_CANDIDATE': 8,
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
                'agt_interfaces.srv.ManageMapVersion_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__manage_map_version__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__manage_map_version__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__manage_map_version__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__manage_map_version__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__manage_map_version__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'OP_GET_ACTIVE': cls.__constants['OP_GET_ACTIVE'],
            'OP_VALIDATE': cls.__constants['OP_VALIDATE'],
            'OP_ACTIVATE': cls.__constants['OP_ACTIVATE'],
            'OP_PIN': cls.__constants['OP_PIN'],
            'OP_UNPIN': cls.__constants['OP_UNPIN'],
            'OP_ARCHIVE': cls.__constants['OP_ARCHIVE'],
            'OP_SOFT_DELETE': cls.__constants['OP_SOFT_DELETE'],
            'OP_PURGE': cls.__constants['OP_PURGE'],
            'OP_IMPORT_CANDIDATE': cls.__constants['OP_IMPORT_CANDIDATE'],
        }

    @property
    def OP_GET_ACTIVE(self):
        """Message constant 'OP_GET_ACTIVE'."""
        return Metaclass_ManageMapVersion_Request.__constants['OP_GET_ACTIVE']

    @property
    def OP_VALIDATE(self):
        """Message constant 'OP_VALIDATE'."""
        return Metaclass_ManageMapVersion_Request.__constants['OP_VALIDATE']

    @property
    def OP_ACTIVATE(self):
        """Message constant 'OP_ACTIVATE'."""
        return Metaclass_ManageMapVersion_Request.__constants['OP_ACTIVATE']

    @property
    def OP_PIN(self):
        """Message constant 'OP_PIN'."""
        return Metaclass_ManageMapVersion_Request.__constants['OP_PIN']

    @property
    def OP_UNPIN(self):
        """Message constant 'OP_UNPIN'."""
        return Metaclass_ManageMapVersion_Request.__constants['OP_UNPIN']

    @property
    def OP_ARCHIVE(self):
        """Message constant 'OP_ARCHIVE'."""
        return Metaclass_ManageMapVersion_Request.__constants['OP_ARCHIVE']

    @property
    def OP_SOFT_DELETE(self):
        """Message constant 'OP_SOFT_DELETE'."""
        return Metaclass_ManageMapVersion_Request.__constants['OP_SOFT_DELETE']

    @property
    def OP_PURGE(self):
        """Message constant 'OP_PURGE'."""
        return Metaclass_ManageMapVersion_Request.__constants['OP_PURGE']

    @property
    def OP_IMPORT_CANDIDATE(self):
        """Message constant 'OP_IMPORT_CANDIDATE'."""
        return Metaclass_ManageMapVersion_Request.__constants['OP_IMPORT_CANDIDATE']


class ManageMapVersion_Request(metaclass=Metaclass_ManageMapVersion_Request):
    """
    Message class 'ManageMapVersion_Request'.

    Constants:
      OP_GET_ACTIVE
      OP_VALIDATE
      OP_ACTIVATE
      OP_PIN
      OP_UNPIN
      OP_ARCHIVE
      OP_SOFT_DELETE
      OP_PURGE
      OP_IMPORT_CANDIDATE
    """

    __slots__ = [
        '_operation',
        '_map_version_id',
        '_confirm_destructive',
        '_map_id',
        '_candidate_map_yaml',
        '_localization_pcd',
        '_processing_record',
        '_platform_profile',
        '_parent_map_version_id',
    ]

    _fields_and_field_types = {
        'operation': 'uint8',
        'map_version_id': 'string',
        'confirm_destructive': 'boolean',
        'map_id': 'string',
        'candidate_map_yaml': 'string',
        'localization_pcd': 'string',
        'processing_record': 'string',
        'platform_profile': 'string',
        'parent_map_version_id': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
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
        self.map_version_id = kwargs.get('map_version_id', str())
        self.confirm_destructive = kwargs.get('confirm_destructive', bool())
        self.map_id = kwargs.get('map_id', str())
        self.candidate_map_yaml = kwargs.get('candidate_map_yaml', str())
        self.localization_pcd = kwargs.get('localization_pcd', str())
        self.processing_record = kwargs.get('processing_record', str())
        self.platform_profile = kwargs.get('platform_profile', str())
        self.parent_map_version_id = kwargs.get('parent_map_version_id', str())

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
        if self.map_version_id != other.map_version_id:
            return False
        if self.confirm_destructive != other.confirm_destructive:
            return False
        if self.map_id != other.map_id:
            return False
        if self.candidate_map_yaml != other.candidate_map_yaml:
            return False
        if self.localization_pcd != other.localization_pcd:
            return False
        if self.processing_record != other.processing_record:
            return False
        if self.platform_profile != other.platform_profile:
            return False
        if self.parent_map_version_id != other.parent_map_version_id:
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
    def confirm_destructive(self):
        """Message field 'confirm_destructive'."""
        return self._confirm_destructive

    @confirm_destructive.setter
    def confirm_destructive(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'confirm_destructive' field must be of type 'bool'"
        self._confirm_destructive = value

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
    def candidate_map_yaml(self):
        """Message field 'candidate_map_yaml'."""
        return self._candidate_map_yaml

    @candidate_map_yaml.setter
    def candidate_map_yaml(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'candidate_map_yaml' field must be of type 'str'"
        self._candidate_map_yaml = value

    @builtins.property
    def localization_pcd(self):
        """Message field 'localization_pcd'."""
        return self._localization_pcd

    @localization_pcd.setter
    def localization_pcd(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'localization_pcd' field must be of type 'str'"
        self._localization_pcd = value

    @builtins.property
    def processing_record(self):
        """Message field 'processing_record'."""
        return self._processing_record

    @processing_record.setter
    def processing_record(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'processing_record' field must be of type 'str'"
        self._processing_record = value

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
    def parent_map_version_id(self):
        """Message field 'parent_map_version_id'."""
        return self._parent_map_version_id

    @parent_map_version_id.setter
    def parent_map_version_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'parent_map_version_id' field must be of type 'str'"
        self._parent_map_version_id = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ManageMapVersion_Response(type):
    """Metaclass of message 'ManageMapVersion_Response'."""

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
        'ERROR_VALIDATION_FAILED': 4,
        'ERROR_CONFIRMATION_REQUIRED': 5,
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
                'agt_interfaces.srv.ManageMapVersion_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__manage_map_version__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__manage_map_version__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__manage_map_version__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__manage_map_version__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__manage_map_version__response

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
            'ERROR_NOT_FOUND': cls.__constants['ERROR_NOT_FOUND'],
            'ERROR_INVALID_REQUEST': cls.__constants['ERROR_INVALID_REQUEST'],
            'ERROR_CONFLICT': cls.__constants['ERROR_CONFLICT'],
            'ERROR_VALIDATION_FAILED': cls.__constants['ERROR_VALIDATION_FAILED'],
            'ERROR_CONFIRMATION_REQUIRED': cls.__constants['ERROR_CONFIRMATION_REQUIRED'],
            'ERROR_INTERNAL': cls.__constants['ERROR_INTERNAL'],
        }

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_ManageMapVersion_Response.__constants['ERROR_NONE']

    @property
    def ERROR_NOT_FOUND(self):
        """Message constant 'ERROR_NOT_FOUND'."""
        return Metaclass_ManageMapVersion_Response.__constants['ERROR_NOT_FOUND']

    @property
    def ERROR_INVALID_REQUEST(self):
        """Message constant 'ERROR_INVALID_REQUEST'."""
        return Metaclass_ManageMapVersion_Response.__constants['ERROR_INVALID_REQUEST']

    @property
    def ERROR_CONFLICT(self):
        """Message constant 'ERROR_CONFLICT'."""
        return Metaclass_ManageMapVersion_Response.__constants['ERROR_CONFLICT']

    @property
    def ERROR_VALIDATION_FAILED(self):
        """Message constant 'ERROR_VALIDATION_FAILED'."""
        return Metaclass_ManageMapVersion_Response.__constants['ERROR_VALIDATION_FAILED']

    @property
    def ERROR_CONFIRMATION_REQUIRED(self):
        """Message constant 'ERROR_CONFIRMATION_REQUIRED'."""
        return Metaclass_ManageMapVersion_Response.__constants['ERROR_CONFIRMATION_REQUIRED']

    @property
    def ERROR_INTERNAL(self):
        """Message constant 'ERROR_INTERNAL'."""
        return Metaclass_ManageMapVersion_Response.__constants['ERROR_INTERNAL']


class ManageMapVersion_Response(metaclass=Metaclass_ManageMapVersion_Response):
    """
    Message class 'ManageMapVersion_Response'.

    Constants:
      ERROR_NONE
      ERROR_NOT_FOUND
      ERROR_INVALID_REQUEST
      ERROR_CONFLICT
      ERROR_VALIDATION_FAILED
      ERROR_CONFIRMATION_REQUIRED
      ERROR_INTERNAL
    """

    __slots__ = [
        '_success',
        '_error_code',
        '_version',
        '_message',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'version': 'agt_interfaces/MapVersionSummary',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'MapVersionSummary'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        from agt_interfaces.msg import MapVersionSummary
        self.version = kwargs.get('version', MapVersionSummary())
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
        if self.version != other.version:
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


class Metaclass_ManageMapVersion(type):
    """Metaclass of service 'ManageMapVersion'."""

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
                'agt_interfaces.srv.ManageMapVersion')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__manage_map_version

            from agt_interfaces.srv import _manage_map_version
            if _manage_map_version.Metaclass_ManageMapVersion_Request._TYPE_SUPPORT is None:
                _manage_map_version.Metaclass_ManageMapVersion_Request.__import_type_support__()
            if _manage_map_version.Metaclass_ManageMapVersion_Response._TYPE_SUPPORT is None:
                _manage_map_version.Metaclass_ManageMapVersion_Response.__import_type_support__()


class ManageMapVersion(metaclass=Metaclass_ManageMapVersion):
    from agt_interfaces.srv._manage_map_version import ManageMapVersion_Request as Request
    from agt_interfaces.srv._manage_map_version import ManageMapVersion_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
