# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:action/ManageMappingSession.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ManageMappingSession_Goal(type):
    """Metaclass of message 'ManageMappingSession_Goal'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'OP_STATUS': 0,
        'OP_START': 1,
        'OP_FINALIZE_CAPTURE': 2,
        'OP_COMMIT': 3,
        'OP_DISCARD': 4,
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
                'agt_interfaces.action.ManageMappingSession_Goal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__manage_mapping_session__goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__manage_mapping_session__goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__manage_mapping_session__goal
            cls._TYPE_SUPPORT = module.type_support_msg__action__manage_mapping_session__goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__manage_mapping_session__goal

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'OP_STATUS': cls.__constants['OP_STATUS'],
            'OP_START': cls.__constants['OP_START'],
            'OP_FINALIZE_CAPTURE': cls.__constants['OP_FINALIZE_CAPTURE'],
            'OP_COMMIT': cls.__constants['OP_COMMIT'],
            'OP_DISCARD': cls.__constants['OP_DISCARD'],
        }

    @property
    def OP_STATUS(self):
        """Message constant 'OP_STATUS'."""
        return Metaclass_ManageMappingSession_Goal.__constants['OP_STATUS']

    @property
    def OP_START(self):
        """Message constant 'OP_START'."""
        return Metaclass_ManageMappingSession_Goal.__constants['OP_START']

    @property
    def OP_FINALIZE_CAPTURE(self):
        """Message constant 'OP_FINALIZE_CAPTURE'."""
        return Metaclass_ManageMappingSession_Goal.__constants['OP_FINALIZE_CAPTURE']

    @property
    def OP_COMMIT(self):
        """Message constant 'OP_COMMIT'."""
        return Metaclass_ManageMappingSession_Goal.__constants['OP_COMMIT']

    @property
    def OP_DISCARD(self):
        """Message constant 'OP_DISCARD'."""
        return Metaclass_ManageMappingSession_Goal.__constants['OP_DISCARD']


class ManageMappingSession_Goal(metaclass=Metaclass_ManageMappingSession_Goal):
    """
    Message class 'ManageMappingSession_Goal'.

    Constants:
      OP_STATUS
      OP_START
      OP_FINALIZE_CAPTURE
      OP_COMMIT
      OP_DISCARD
    """

    __slots__ = [
        '_operation',
        '_map_id',
        '_session_id',
        '_argument_keys',
        '_argument_values',
        '_activate_after_commit',
        '_timeout_s',
    ]

    _fields_and_field_types = {
        'operation': 'uint8',
        'map_id': 'string',
        'session_id': 'string',
        'argument_keys': 'sequence<string>',
        'argument_values': 'sequence<string>',
        'activate_after_commit': 'boolean',
        'timeout_s': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.operation = kwargs.get('operation', int())
        self.map_id = kwargs.get('map_id', str())
        self.session_id = kwargs.get('session_id', str())
        self.argument_keys = kwargs.get('argument_keys', [])
        self.argument_values = kwargs.get('argument_values', [])
        self.activate_after_commit = kwargs.get('activate_after_commit', bool())
        self.timeout_s = kwargs.get('timeout_s', float())

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
        if self.map_id != other.map_id:
            return False
        if self.session_id != other.session_id:
            return False
        if self.argument_keys != other.argument_keys:
            return False
        if self.argument_values != other.argument_values:
            return False
        if self.activate_after_commit != other.activate_after_commit:
            return False
        if self.timeout_s != other.timeout_s:
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
    def session_id(self):
        """Message field 'session_id'."""
        return self._session_id

    @session_id.setter
    def session_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'session_id' field must be of type 'str'"
        self._session_id = value

    @builtins.property
    def argument_keys(self):
        """Message field 'argument_keys'."""
        return self._argument_keys

    @argument_keys.setter
    def argument_keys(self, value):
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
                "The 'argument_keys' field must be a set or sequence and each value of type 'str'"
        self._argument_keys = value

    @builtins.property
    def argument_values(self):
        """Message field 'argument_values'."""
        return self._argument_values

    @argument_values.setter
    def argument_values(self, value):
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
                "The 'argument_values' field must be a set or sequence and each value of type 'str'"
        self._argument_values = value

    @builtins.property
    def activate_after_commit(self):
        """Message field 'activate_after_commit'."""
        return self._activate_after_commit

    @activate_after_commit.setter
    def activate_after_commit(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'activate_after_commit' field must be of type 'bool'"
        self._activate_after_commit = value

    @builtins.property
    def timeout_s(self):
        """Message field 'timeout_s'."""
        return self._timeout_s

    @timeout_s.setter
    def timeout_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'timeout_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'timeout_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._timeout_s = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ManageMappingSession_Result(type):
    """Metaclass of message 'ManageMappingSession_Result'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ERROR_NONE': 0,
        'ERROR_INVALID_REQUEST': 1,
        'ERROR_SERVER_UNAVAILABLE': 2,
        'ERROR_START_FAILED': 3,
        'ERROR_GRID_SAVE_FAILED': 4,
        'ERROR_STOP_FAILED': 5,
        'ERROR_ASSET_TIMEOUT': 6,
        'ERROR_COMMIT_FAILED': 7,
        'ERROR_INVALID_STATE': 8,
        'ERROR_NOT_FOUND': 9,
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
                'agt_interfaces.action.ManageMappingSession_Result')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__manage_mapping_session__result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__manage_mapping_session__result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__manage_mapping_session__result
            cls._TYPE_SUPPORT = module.type_support_msg__action__manage_mapping_session__result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__manage_mapping_session__result

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_INVALID_REQUEST': cls.__constants['ERROR_INVALID_REQUEST'],
            'ERROR_SERVER_UNAVAILABLE': cls.__constants['ERROR_SERVER_UNAVAILABLE'],
            'ERROR_START_FAILED': cls.__constants['ERROR_START_FAILED'],
            'ERROR_GRID_SAVE_FAILED': cls.__constants['ERROR_GRID_SAVE_FAILED'],
            'ERROR_STOP_FAILED': cls.__constants['ERROR_STOP_FAILED'],
            'ERROR_ASSET_TIMEOUT': cls.__constants['ERROR_ASSET_TIMEOUT'],
            'ERROR_COMMIT_FAILED': cls.__constants['ERROR_COMMIT_FAILED'],
            'ERROR_INVALID_STATE': cls.__constants['ERROR_INVALID_STATE'],
            'ERROR_NOT_FOUND': cls.__constants['ERROR_NOT_FOUND'],
            'ERROR_INTERNAL': cls.__constants['ERROR_INTERNAL'],
        }

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_NONE']

    @property
    def ERROR_INVALID_REQUEST(self):
        """Message constant 'ERROR_INVALID_REQUEST'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_INVALID_REQUEST']

    @property
    def ERROR_SERVER_UNAVAILABLE(self):
        """Message constant 'ERROR_SERVER_UNAVAILABLE'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_SERVER_UNAVAILABLE']

    @property
    def ERROR_START_FAILED(self):
        """Message constant 'ERROR_START_FAILED'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_START_FAILED']

    @property
    def ERROR_GRID_SAVE_FAILED(self):
        """Message constant 'ERROR_GRID_SAVE_FAILED'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_GRID_SAVE_FAILED']

    @property
    def ERROR_STOP_FAILED(self):
        """Message constant 'ERROR_STOP_FAILED'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_STOP_FAILED']

    @property
    def ERROR_ASSET_TIMEOUT(self):
        """Message constant 'ERROR_ASSET_TIMEOUT'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_ASSET_TIMEOUT']

    @property
    def ERROR_COMMIT_FAILED(self):
        """Message constant 'ERROR_COMMIT_FAILED'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_COMMIT_FAILED']

    @property
    def ERROR_INVALID_STATE(self):
        """Message constant 'ERROR_INVALID_STATE'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_INVALID_STATE']

    @property
    def ERROR_NOT_FOUND(self):
        """Message constant 'ERROR_NOT_FOUND'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_NOT_FOUND']

    @property
    def ERROR_INTERNAL(self):
        """Message constant 'ERROR_INTERNAL'."""
        return Metaclass_ManageMappingSession_Result.__constants['ERROR_INTERNAL']


class ManageMappingSession_Result(metaclass=Metaclass_ManageMappingSession_Result):
    """
    Message class 'ManageMappingSession_Result'.

    Constants:
      ERROR_NONE
      ERROR_INVALID_REQUEST
      ERROR_SERVER_UNAVAILABLE
      ERROR_START_FAILED
      ERROR_GRID_SAVE_FAILED
      ERROR_STOP_FAILED
      ERROR_ASSET_TIMEOUT
      ERROR_COMMIT_FAILED
      ERROR_INVALID_STATE
      ERROR_NOT_FOUND
      ERROR_INTERNAL
    """

    __slots__ = [
        '_success',
        '_error_code',
        '_state',
        '_session_id',
        '_map_id',
        '_map_version_id',
        '_session_file',
        '_candidate_map_yaml',
        '_candidate_map_image',
        '_localization_pcd',
        '_processing_record',
        '_bag_directory',
        '_registered_map_yaml',
        '_tasks_directory',
        '_message',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'state': 'string',
        'session_id': 'string',
        'map_id': 'string',
        'map_version_id': 'string',
        'session_file': 'string',
        'candidate_map_yaml': 'string',
        'candidate_map_image': 'string',
        'localization_pcd': 'string',
        'processing_record': 'string',
        'bag_directory': 'string',
        'registered_map_yaml': 'string',
        'tasks_directory': 'string',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
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
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        self.state = kwargs.get('state', str())
        self.session_id = kwargs.get('session_id', str())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.session_file = kwargs.get('session_file', str())
        self.candidate_map_yaml = kwargs.get('candidate_map_yaml', str())
        self.candidate_map_image = kwargs.get('candidate_map_image', str())
        self.localization_pcd = kwargs.get('localization_pcd', str())
        self.processing_record = kwargs.get('processing_record', str())
        self.bag_directory = kwargs.get('bag_directory', str())
        self.registered_map_yaml = kwargs.get('registered_map_yaml', str())
        self.tasks_directory = kwargs.get('tasks_directory', str())
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
        if self.state != other.state:
            return False
        if self.session_id != other.session_id:
            return False
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.session_file != other.session_file:
            return False
        if self.candidate_map_yaml != other.candidate_map_yaml:
            return False
        if self.candidate_map_image != other.candidate_map_image:
            return False
        if self.localization_pcd != other.localization_pcd:
            return False
        if self.processing_record != other.processing_record:
            return False
        if self.bag_directory != other.bag_directory:
            return False
        if self.registered_map_yaml != other.registered_map_yaml:
            return False
        if self.tasks_directory != other.tasks_directory:
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
    def session_id(self):
        """Message field 'session_id'."""
        return self._session_id

    @session_id.setter
    def session_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'session_id' field must be of type 'str'"
        self._session_id = value

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
    def session_file(self):
        """Message field 'session_file'."""
        return self._session_file

    @session_file.setter
    def session_file(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'session_file' field must be of type 'str'"
        self._session_file = value

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
    def candidate_map_image(self):
        """Message field 'candidate_map_image'."""
        return self._candidate_map_image

    @candidate_map_image.setter
    def candidate_map_image(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'candidate_map_image' field must be of type 'str'"
        self._candidate_map_image = value

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
    def bag_directory(self):
        """Message field 'bag_directory'."""
        return self._bag_directory

    @bag_directory.setter
    def bag_directory(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'bag_directory' field must be of type 'str'"
        self._bag_directory = value

    @builtins.property
    def registered_map_yaml(self):
        """Message field 'registered_map_yaml'."""
        return self._registered_map_yaml

    @registered_map_yaml.setter
    def registered_map_yaml(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'registered_map_yaml' field must be of type 'str'"
        self._registered_map_yaml = value

    @builtins.property
    def tasks_directory(self):
        """Message field 'tasks_directory'."""
        return self._tasks_directory

    @tasks_directory.setter
    def tasks_directory(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'tasks_directory' field must be of type 'str'"
        self._tasks_directory = value

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import math

# already imported above
# import rosidl_parser.definition


class Metaclass_ManageMappingSession_Feedback(type):
    """Metaclass of message 'ManageMappingSession_Feedback'."""

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
                'agt_interfaces.action.ManageMappingSession_Feedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__manage_mapping_session__feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__manage_mapping_session__feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__manage_mapping_session__feedback
            cls._TYPE_SUPPORT = module.type_support_msg__action__manage_mapping_session__feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__manage_mapping_session__feedback

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ManageMappingSession_Feedback(metaclass=Metaclass_ManageMappingSession_Feedback):
    """Message class 'ManageMappingSession_Feedback'."""

    __slots__ = [
        '_state',
        '_progress',
        '_message',
    ]

    _fields_and_field_types = {
        'state': 'string',
        'progress': 'float',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.state = kwargs.get('state', str())
        self.progress = kwargs.get('progress', float())
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
        if self.state != other.state:
            return False
        if self.progress != other.progress:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

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
    def progress(self):
        """Message field 'progress'."""
        return self._progress

    @progress.setter
    def progress(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'progress' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'progress' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._progress = value

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ManageMappingSession_SendGoal_Request(type):
    """Metaclass of message 'ManageMappingSession_SendGoal_Request'."""

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
                'agt_interfaces.action.ManageMappingSession_SendGoal_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__manage_mapping_session__send_goal__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__manage_mapping_session__send_goal__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__manage_mapping_session__send_goal__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__manage_mapping_session__send_goal__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__manage_mapping_session__send_goal__request

            from agt_interfaces.action import ManageMappingSession
            if ManageMappingSession.Goal.__class__._TYPE_SUPPORT is None:
                ManageMappingSession.Goal.__class__.__import_type_support__()

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ManageMappingSession_SendGoal_Request(metaclass=Metaclass_ManageMappingSession_SendGoal_Request):
    """Message class 'ManageMappingSession_SendGoal_Request'."""

    __slots__ = [
        '_goal_id',
        '_goal',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'goal': 'agt_interfaces/ManageMappingSession_Goal',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ManageMappingSession_Goal'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._manage_mapping_session import ManageMappingSession_Goal
        self.goal = kwargs.get('goal', ManageMappingSession_Goal())

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
        if self.goal_id != other.goal_id:
            return False
        if self.goal != other.goal:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def goal(self):
        """Message field 'goal'."""
        return self._goal

    @goal.setter
    def goal(self, value):
        if __debug__:
            from agt_interfaces.action._manage_mapping_session import ManageMappingSession_Goal
            assert \
                isinstance(value, ManageMappingSession_Goal), \
                "The 'goal' field must be a sub message of type 'ManageMappingSession_Goal'"
        self._goal = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ManageMappingSession_SendGoal_Response(type):
    """Metaclass of message 'ManageMappingSession_SendGoal_Response'."""

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
                'agt_interfaces.action.ManageMappingSession_SendGoal_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__manage_mapping_session__send_goal__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__manage_mapping_session__send_goal__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__manage_mapping_session__send_goal__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__manage_mapping_session__send_goal__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__manage_mapping_session__send_goal__response

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ManageMappingSession_SendGoal_Response(metaclass=Metaclass_ManageMappingSession_SendGoal_Response):
    """Message class 'ManageMappingSession_SendGoal_Response'."""

    __slots__ = [
        '_accepted',
        '_stamp',
    ]

    _fields_and_field_types = {
        'accepted': 'boolean',
        'stamp': 'builtin_interfaces/Time',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.accepted = kwargs.get('accepted', bool())
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())

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
        if self.accepted != other.accepted:
            return False
        if self.stamp != other.stamp:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def accepted(self):
        """Message field 'accepted'."""
        return self._accepted

    @accepted.setter
    def accepted(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'accepted' field must be of type 'bool'"
        self._accepted = value

    @builtins.property
    def stamp(self):
        """Message field 'stamp'."""
        return self._stamp

    @stamp.setter
    def stamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'stamp' field must be a sub message of type 'Time'"
        self._stamp = value


class Metaclass_ManageMappingSession_SendGoal(type):
    """Metaclass of service 'ManageMappingSession_SendGoal'."""

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
                'agt_interfaces.action.ManageMappingSession_SendGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__manage_mapping_session__send_goal

            from agt_interfaces.action import _manage_mapping_session
            if _manage_mapping_session.Metaclass_ManageMappingSession_SendGoal_Request._TYPE_SUPPORT is None:
                _manage_mapping_session.Metaclass_ManageMappingSession_SendGoal_Request.__import_type_support__()
            if _manage_mapping_session.Metaclass_ManageMappingSession_SendGoal_Response._TYPE_SUPPORT is None:
                _manage_mapping_session.Metaclass_ManageMappingSession_SendGoal_Response.__import_type_support__()


class ManageMappingSession_SendGoal(metaclass=Metaclass_ManageMappingSession_SendGoal):
    from agt_interfaces.action._manage_mapping_session import ManageMappingSession_SendGoal_Request as Request
    from agt_interfaces.action._manage_mapping_session import ManageMappingSession_SendGoal_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ManageMappingSession_GetResult_Request(type):
    """Metaclass of message 'ManageMappingSession_GetResult_Request'."""

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
                'agt_interfaces.action.ManageMappingSession_GetResult_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__manage_mapping_session__get_result__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__manage_mapping_session__get_result__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__manage_mapping_session__get_result__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__manage_mapping_session__get_result__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__manage_mapping_session__get_result__request

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ManageMappingSession_GetResult_Request(metaclass=Metaclass_ManageMappingSession_GetResult_Request):
    """Message class 'ManageMappingSession_GetResult_Request'."""

    __slots__ = [
        '_goal_id',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())

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
        if self.goal_id != other.goal_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ManageMappingSession_GetResult_Response(type):
    """Metaclass of message 'ManageMappingSession_GetResult_Response'."""

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
                'agt_interfaces.action.ManageMappingSession_GetResult_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__manage_mapping_session__get_result__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__manage_mapping_session__get_result__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__manage_mapping_session__get_result__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__manage_mapping_session__get_result__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__manage_mapping_session__get_result__response

            from agt_interfaces.action import ManageMappingSession
            if ManageMappingSession.Result.__class__._TYPE_SUPPORT is None:
                ManageMappingSession.Result.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ManageMappingSession_GetResult_Response(metaclass=Metaclass_ManageMappingSession_GetResult_Response):
    """Message class 'ManageMappingSession_GetResult_Response'."""

    __slots__ = [
        '_status',
        '_result',
    ]

    _fields_and_field_types = {
        'status': 'int8',
        'result': 'agt_interfaces/ManageMappingSession_Result',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ManageMappingSession_Result'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        from agt_interfaces.action._manage_mapping_session import ManageMappingSession_Result
        self.result = kwargs.get('result', ManageMappingSession_Result())

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
        if self.status != other.status:
            return False
        if self.result != other.result:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'status' field must be an integer in [-128, 127]"
        self._status = value

    @builtins.property
    def result(self):
        """Message field 'result'."""
        return self._result

    @result.setter
    def result(self, value):
        if __debug__:
            from agt_interfaces.action._manage_mapping_session import ManageMappingSession_Result
            assert \
                isinstance(value, ManageMappingSession_Result), \
                "The 'result' field must be a sub message of type 'ManageMappingSession_Result'"
        self._result = value


class Metaclass_ManageMappingSession_GetResult(type):
    """Metaclass of service 'ManageMappingSession_GetResult'."""

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
                'agt_interfaces.action.ManageMappingSession_GetResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__manage_mapping_session__get_result

            from agt_interfaces.action import _manage_mapping_session
            if _manage_mapping_session.Metaclass_ManageMappingSession_GetResult_Request._TYPE_SUPPORT is None:
                _manage_mapping_session.Metaclass_ManageMappingSession_GetResult_Request.__import_type_support__()
            if _manage_mapping_session.Metaclass_ManageMappingSession_GetResult_Response._TYPE_SUPPORT is None:
                _manage_mapping_session.Metaclass_ManageMappingSession_GetResult_Response.__import_type_support__()


class ManageMappingSession_GetResult(metaclass=Metaclass_ManageMappingSession_GetResult):
    from agt_interfaces.action._manage_mapping_session import ManageMappingSession_GetResult_Request as Request
    from agt_interfaces.action._manage_mapping_session import ManageMappingSession_GetResult_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ManageMappingSession_FeedbackMessage(type):
    """Metaclass of message 'ManageMappingSession_FeedbackMessage'."""

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
                'agt_interfaces.action.ManageMappingSession_FeedbackMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__manage_mapping_session__feedback_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__manage_mapping_session__feedback_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__manage_mapping_session__feedback_message
            cls._TYPE_SUPPORT = module.type_support_msg__action__manage_mapping_session__feedback_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__manage_mapping_session__feedback_message

            from agt_interfaces.action import ManageMappingSession
            if ManageMappingSession.Feedback.__class__._TYPE_SUPPORT is None:
                ManageMappingSession.Feedback.__class__.__import_type_support__()

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ManageMappingSession_FeedbackMessage(metaclass=Metaclass_ManageMappingSession_FeedbackMessage):
    """Message class 'ManageMappingSession_FeedbackMessage'."""

    __slots__ = [
        '_goal_id',
        '_feedback',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'feedback': 'agt_interfaces/ManageMappingSession_Feedback',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['agt_interfaces', 'action'], 'ManageMappingSession_Feedback'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from agt_interfaces.action._manage_mapping_session import ManageMappingSession_Feedback
        self.feedback = kwargs.get('feedback', ManageMappingSession_Feedback())

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
        if self.goal_id != other.goal_id:
            return False
        if self.feedback != other.feedback:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def feedback(self):
        """Message field 'feedback'."""
        return self._feedback

    @feedback.setter
    def feedback(self, value):
        if __debug__:
            from agt_interfaces.action._manage_mapping_session import ManageMappingSession_Feedback
            assert \
                isinstance(value, ManageMappingSession_Feedback), \
                "The 'feedback' field must be a sub message of type 'ManageMappingSession_Feedback'"
        self._feedback = value


class Metaclass_ManageMappingSession(type):
    """Metaclass of action 'ManageMappingSession'."""

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
                'agt_interfaces.action.ManageMappingSession')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_action__action__manage_mapping_session

            from action_msgs.msg import _goal_status_array
            if _goal_status_array.Metaclass_GoalStatusArray._TYPE_SUPPORT is None:
                _goal_status_array.Metaclass_GoalStatusArray.__import_type_support__()
            from action_msgs.srv import _cancel_goal
            if _cancel_goal.Metaclass_CancelGoal._TYPE_SUPPORT is None:
                _cancel_goal.Metaclass_CancelGoal.__import_type_support__()

            from agt_interfaces.action import _manage_mapping_session
            if _manage_mapping_session.Metaclass_ManageMappingSession_SendGoal._TYPE_SUPPORT is None:
                _manage_mapping_session.Metaclass_ManageMappingSession_SendGoal.__import_type_support__()
            if _manage_mapping_session.Metaclass_ManageMappingSession_GetResult._TYPE_SUPPORT is None:
                _manage_mapping_session.Metaclass_ManageMappingSession_GetResult.__import_type_support__()
            if _manage_mapping_session.Metaclass_ManageMappingSession_FeedbackMessage._TYPE_SUPPORT is None:
                _manage_mapping_session.Metaclass_ManageMappingSession_FeedbackMessage.__import_type_support__()


class ManageMappingSession(metaclass=Metaclass_ManageMappingSession):

    # The goal message defined in the action definition.
    from agt_interfaces.action._manage_mapping_session import ManageMappingSession_Goal as Goal
    # The result message defined in the action definition.
    from agt_interfaces.action._manage_mapping_session import ManageMappingSession_Result as Result
    # The feedback message defined in the action definition.
    from agt_interfaces.action._manage_mapping_session import ManageMappingSession_Feedback as Feedback

    class Impl:

        # The send_goal service using a wrapped version of the goal message as a request.
        from agt_interfaces.action._manage_mapping_session import ManageMappingSession_SendGoal as SendGoalService
        # The get_result service using a wrapped version of the result message as a response.
        from agt_interfaces.action._manage_mapping_session import ManageMappingSession_GetResult as GetResultService
        # The feedback message with generic fields which wraps the feedback message.
        from agt_interfaces.action._manage_mapping_session import ManageMappingSession_FeedbackMessage as FeedbackMessage

        # The generic service to cancel a goal.
        from action_msgs.srv._cancel_goal import CancelGoal as CancelGoalService
        # The generic message for get the status of a goal.
        from action_msgs.msg._goal_status_array import GoalStatusArray as GoalStatusMessage

    def __init__(self):
        raise NotImplementedError('Action classes can not be instantiated')
