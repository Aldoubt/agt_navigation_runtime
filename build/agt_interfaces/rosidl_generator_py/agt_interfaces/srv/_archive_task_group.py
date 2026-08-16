# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:srv/ArchiveTaskGroup.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ArchiveTaskGroup_Request(type):
    """Metaclass of message 'ArchiveTaskGroup_Request'."""

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
                'agt_interfaces.srv.ArchiveTaskGroup_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__archive_task_group__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__archive_task_group__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__archive_task_group__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__archive_task_group__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__archive_task_group__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ArchiveTaskGroup_Request(metaclass=Metaclass_ArchiveTaskGroup_Request):
    """Message class 'ArchiveTaskGroup_Request'."""

    __slots__ = [
        '_map_id',
        '_map_version_id',
        '_task_group_id',
        '_expected_revision',
        '_client_request_id',
    ]

    _fields_and_field_types = {
        'map_id': 'string',
        'map_version_id': 'string',
        'task_group_id': 'string',
        'expected_revision': 'uint32',
        'client_request_id': 'string',
    }

    SLOT_TYPES = (
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
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.task_group_id = kwargs.get('task_group_id', str())
        self.expected_revision = kwargs.get('expected_revision', int())
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
        if self.task_group_id != other.task_group_id:
            return False
        if self.expected_revision != other.expected_revision:
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
    def task_group_id(self):
        """Message field 'task_group_id'."""
        return self._task_group_id

    @task_group_id.setter
    def task_group_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'task_group_id' field must be of type 'str'"
        self._task_group_id = value

    @builtins.property
    def expected_revision(self):
        """Message field 'expected_revision'."""
        return self._expected_revision

    @expected_revision.setter
    def expected_revision(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'expected_revision' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'expected_revision' field must be an unsigned integer in [0, 4294967295]"
        self._expected_revision = value

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


class Metaclass_ArchiveTaskGroup_Response(type):
    """Metaclass of message 'ArchiveTaskGroup_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ERROR_NONE': 0,
        'ERROR_INVALID_REQUEST': 1,
        'ERROR_NOT_FOUND': 2,
        'ERROR_REVISION_CONFLICT': 3,
        'ERROR_MAP_NOT_READY': 4,
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
                'agt_interfaces.srv.ArchiveTaskGroup_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__archive_task_group__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__archive_task_group__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__archive_task_group__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__archive_task_group__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__archive_task_group__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_INVALID_REQUEST': cls.__constants['ERROR_INVALID_REQUEST'],
            'ERROR_NOT_FOUND': cls.__constants['ERROR_NOT_FOUND'],
            'ERROR_REVISION_CONFLICT': cls.__constants['ERROR_REVISION_CONFLICT'],
            'ERROR_MAP_NOT_READY': cls.__constants['ERROR_MAP_NOT_READY'],
            'ERROR_INTERNAL': cls.__constants['ERROR_INTERNAL'],
        }

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_ArchiveTaskGroup_Response.__constants['ERROR_NONE']

    @property
    def ERROR_INVALID_REQUEST(self):
        """Message constant 'ERROR_INVALID_REQUEST'."""
        return Metaclass_ArchiveTaskGroup_Response.__constants['ERROR_INVALID_REQUEST']

    @property
    def ERROR_NOT_FOUND(self):
        """Message constant 'ERROR_NOT_FOUND'."""
        return Metaclass_ArchiveTaskGroup_Response.__constants['ERROR_NOT_FOUND']

    @property
    def ERROR_REVISION_CONFLICT(self):
        """Message constant 'ERROR_REVISION_CONFLICT'."""
        return Metaclass_ArchiveTaskGroup_Response.__constants['ERROR_REVISION_CONFLICT']

    @property
    def ERROR_MAP_NOT_READY(self):
        """Message constant 'ERROR_MAP_NOT_READY'."""
        return Metaclass_ArchiveTaskGroup_Response.__constants['ERROR_MAP_NOT_READY']

    @property
    def ERROR_INTERNAL(self):
        """Message constant 'ERROR_INTERNAL'."""
        return Metaclass_ArchiveTaskGroup_Response.__constants['ERROR_INTERNAL']


class ArchiveTaskGroup_Response(metaclass=Metaclass_ArchiveTaskGroup_Response):
    """
    Message class 'ArchiveTaskGroup_Response'.

    Constants:
      ERROR_NONE
      ERROR_INVALID_REQUEST
      ERROR_NOT_FOUND
      ERROR_REVISION_CONFLICT
      ERROR_MAP_NOT_READY
      ERROR_INTERNAL
    """

    __slots__ = [
        '_success',
        '_error_code',
        '_blocker_code',
        '_operator_message',
        '_technical_message',
        '_duplicate_request',
        '_map_id',
        '_map_version_id',
        '_task_group_id',
        '_archived_revision',
        '_archived_relative_path',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'blocker_code': 'string',
        'operator_message': 'string',
        'technical_message': 'string',
        'duplicate_request': 'boolean',
        'map_id': 'string',
        'map_version_id': 'string',
        'task_group_id': 'string',
        'archived_revision': 'uint32',
        'archived_relative_path': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
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
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        self.blocker_code = kwargs.get('blocker_code', str())
        self.operator_message = kwargs.get('operator_message', str())
        self.technical_message = kwargs.get('technical_message', str())
        self.duplicate_request = kwargs.get('duplicate_request', bool())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.task_group_id = kwargs.get('task_group_id', str())
        self.archived_revision = kwargs.get('archived_revision', int())
        self.archived_relative_path = kwargs.get('archived_relative_path', str())

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
        if self.blocker_code != other.blocker_code:
            return False
        if self.operator_message != other.operator_message:
            return False
        if self.technical_message != other.technical_message:
            return False
        if self.duplicate_request != other.duplicate_request:
            return False
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.task_group_id != other.task_group_id:
            return False
        if self.archived_revision != other.archived_revision:
            return False
        if self.archived_relative_path != other.archived_relative_path:
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
    def blocker_code(self):
        """Message field 'blocker_code'."""
        return self._blocker_code

    @blocker_code.setter
    def blocker_code(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'blocker_code' field must be of type 'str'"
        self._blocker_code = value

    @builtins.property
    def operator_message(self):
        """Message field 'operator_message'."""
        return self._operator_message

    @operator_message.setter
    def operator_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'operator_message' field must be of type 'str'"
        self._operator_message = value

    @builtins.property
    def technical_message(self):
        """Message field 'technical_message'."""
        return self._technical_message

    @technical_message.setter
    def technical_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'technical_message' field must be of type 'str'"
        self._technical_message = value

    @builtins.property
    def duplicate_request(self):
        """Message field 'duplicate_request'."""
        return self._duplicate_request

    @duplicate_request.setter
    def duplicate_request(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'duplicate_request' field must be of type 'bool'"
        self._duplicate_request = value

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
    def task_group_id(self):
        """Message field 'task_group_id'."""
        return self._task_group_id

    @task_group_id.setter
    def task_group_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'task_group_id' field must be of type 'str'"
        self._task_group_id = value

    @builtins.property
    def archived_revision(self):
        """Message field 'archived_revision'."""
        return self._archived_revision

    @archived_revision.setter
    def archived_revision(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'archived_revision' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'archived_revision' field must be an unsigned integer in [0, 4294967295]"
        self._archived_revision = value

    @builtins.property
    def archived_relative_path(self):
        """Message field 'archived_relative_path'."""
        return self._archived_relative_path

    @archived_relative_path.setter
    def archived_relative_path(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'archived_relative_path' field must be of type 'str'"
        self._archived_relative_path = value


class Metaclass_ArchiveTaskGroup(type):
    """Metaclass of service 'ArchiveTaskGroup'."""

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
                'agt_interfaces.srv.ArchiveTaskGroup')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__archive_task_group

            from agt_interfaces.srv import _archive_task_group
            if _archive_task_group.Metaclass_ArchiveTaskGroup_Request._TYPE_SUPPORT is None:
                _archive_task_group.Metaclass_ArchiveTaskGroup_Request.__import_type_support__()
            if _archive_task_group.Metaclass_ArchiveTaskGroup_Response._TYPE_SUPPORT is None:
                _archive_task_group.Metaclass_ArchiveTaskGroup_Response.__import_type_support__()


class ArchiveTaskGroup(metaclass=Metaclass_ArchiveTaskGroup):
    from agt_interfaces.srv._archive_task_group import ArchiveTaskGroup_Request as Request
    from agt_interfaces.srv._archive_task_group import ArchiveTaskGroup_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
