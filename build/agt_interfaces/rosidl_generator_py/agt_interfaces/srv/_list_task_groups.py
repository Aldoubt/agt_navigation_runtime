# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:srv/ListTaskGroups.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ListTaskGroups_Request(type):
    """Metaclass of message 'ListTaskGroups_Request'."""

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
                'agt_interfaces.srv.ListTaskGroups_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__list_task_groups__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__list_task_groups__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__list_task_groups__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__list_task_groups__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__list_task_groups__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ListTaskGroups_Request(metaclass=Metaclass_ListTaskGroups_Request):
    """Message class 'ListTaskGroups_Request'."""

    __slots__ = [
        '_map_id',
        '_map_version_id',
    ]

    _fields_and_field_types = {
        'map_id': 'string',
        'map_version_id': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())

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


# Import statements for member types

# Member 'revisions'
# Member 'enabled_point_counts'
import array  # noqa: E402, I100

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ListTaskGroups_Response(type):
    """Metaclass of message 'ListTaskGroups_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ERROR_NONE': 0,
        'ERROR_INVALID_REQUEST': 1,
        'ERROR_MAP_NOT_READY': 2,
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
                'agt_interfaces.srv.ListTaskGroups_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__list_task_groups__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__list_task_groups__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__list_task_groups__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__list_task_groups__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__list_task_groups__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_INVALID_REQUEST': cls.__constants['ERROR_INVALID_REQUEST'],
            'ERROR_MAP_NOT_READY': cls.__constants['ERROR_MAP_NOT_READY'],
            'ERROR_INTERNAL': cls.__constants['ERROR_INTERNAL'],
        }

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_ListTaskGroups_Response.__constants['ERROR_NONE']

    @property
    def ERROR_INVALID_REQUEST(self):
        """Message constant 'ERROR_INVALID_REQUEST'."""
        return Metaclass_ListTaskGroups_Response.__constants['ERROR_INVALID_REQUEST']

    @property
    def ERROR_MAP_NOT_READY(self):
        """Message constant 'ERROR_MAP_NOT_READY'."""
        return Metaclass_ListTaskGroups_Response.__constants['ERROR_MAP_NOT_READY']

    @property
    def ERROR_INTERNAL(self):
        """Message constant 'ERROR_INTERNAL'."""
        return Metaclass_ListTaskGroups_Response.__constants['ERROR_INTERNAL']


class ListTaskGroups_Response(metaclass=Metaclass_ListTaskGroups_Response):
    """
    Message class 'ListTaskGroups_Response'.

    Constants:
      ERROR_NONE
      ERROR_INVALID_REQUEST
      ERROR_MAP_NOT_READY
      ERROR_INTERNAL
    """

    __slots__ = [
        '_success',
        '_error_code',
        '_blocker_code',
        '_operator_message',
        '_technical_message',
        '_map_id',
        '_map_version_id',
        '_task_group_ids',
        '_names',
        '_revisions',
        '_content_sha256',
        '_enabled_point_counts',
        '_updated_at',
        '_validation_states',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'blocker_code': 'string',
        'operator_message': 'string',
        'technical_message': 'string',
        'map_id': 'string',
        'map_version_id': 'string',
        'task_group_ids': 'sequence<string>',
        'names': 'sequence<string>',
        'revisions': 'sequence<uint32>',
        'content_sha256': 'sequence<string>',
        'enabled_point_counts': 'sequence<uint32>',
        'updated_at': 'sequence<string>',
        'validation_states': 'sequence<string>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('uint32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('uint32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
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
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.task_group_ids = kwargs.get('task_group_ids', [])
        self.names = kwargs.get('names', [])
        self.revisions = array.array('I', kwargs.get('revisions', []))
        self.content_sha256 = kwargs.get('content_sha256', [])
        self.enabled_point_counts = array.array('I', kwargs.get('enabled_point_counts', []))
        self.updated_at = kwargs.get('updated_at', [])
        self.validation_states = kwargs.get('validation_states', [])

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
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.task_group_ids != other.task_group_ids:
            return False
        if self.names != other.names:
            return False
        if self.revisions != other.revisions:
            return False
        if self.content_sha256 != other.content_sha256:
            return False
        if self.enabled_point_counts != other.enabled_point_counts:
            return False
        if self.updated_at != other.updated_at:
            return False
        if self.validation_states != other.validation_states:
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
    def task_group_ids(self):
        """Message field 'task_group_ids'."""
        return self._task_group_ids

    @task_group_ids.setter
    def task_group_ids(self, value):
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
                "The 'task_group_ids' field must be a set or sequence and each value of type 'str'"
        self._task_group_ids = value

    @builtins.property
    def names(self):
        """Message field 'names'."""
        return self._names

    @names.setter
    def names(self, value):
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
                "The 'names' field must be a set or sequence and each value of type 'str'"
        self._names = value

    @builtins.property
    def revisions(self):
        """Message field 'revisions'."""
        return self._revisions

    @revisions.setter
    def revisions(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'I', \
                "The 'revisions' array.array() must have the type code of 'I'"
            self._revisions = value
            return
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 4294967296 for val in value)), \
                "The 'revisions' field must be a set or sequence and each value of type 'int' and each unsigned integer in [0, 4294967295]"
        self._revisions = array.array('I', value)

    @builtins.property
    def content_sha256(self):
        """Message field 'content_sha256'."""
        return self._content_sha256

    @content_sha256.setter
    def content_sha256(self, value):
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
                "The 'content_sha256' field must be a set or sequence and each value of type 'str'"
        self._content_sha256 = value

    @builtins.property
    def enabled_point_counts(self):
        """Message field 'enabled_point_counts'."""
        return self._enabled_point_counts

    @enabled_point_counts.setter
    def enabled_point_counts(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'I', \
                "The 'enabled_point_counts' array.array() must have the type code of 'I'"
            self._enabled_point_counts = value
            return
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 4294967296 for val in value)), \
                "The 'enabled_point_counts' field must be a set or sequence and each value of type 'int' and each unsigned integer in [0, 4294967295]"
        self._enabled_point_counts = array.array('I', value)

    @builtins.property
    def updated_at(self):
        """Message field 'updated_at'."""
        return self._updated_at

    @updated_at.setter
    def updated_at(self, value):
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
                "The 'updated_at' field must be a set or sequence and each value of type 'str'"
        self._updated_at = value

    @builtins.property
    def validation_states(self):
        """Message field 'validation_states'."""
        return self._validation_states

    @validation_states.setter
    def validation_states(self, value):
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
                "The 'validation_states' field must be a set or sequence and each value of type 'str'"
        self._validation_states = value


class Metaclass_ListTaskGroups(type):
    """Metaclass of service 'ListTaskGroups'."""

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
                'agt_interfaces.srv.ListTaskGroups')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__list_task_groups

            from agt_interfaces.srv import _list_task_groups
            if _list_task_groups.Metaclass_ListTaskGroups_Request._TYPE_SUPPORT is None:
                _list_task_groups.Metaclass_ListTaskGroups_Request.__import_type_support__()
            if _list_task_groups.Metaclass_ListTaskGroups_Response._TYPE_SUPPORT is None:
                _list_task_groups.Metaclass_ListTaskGroups_Response.__import_type_support__()


class ListTaskGroups(metaclass=Metaclass_ListTaskGroups):
    from agt_interfaces.srv._list_task_groups import ListTaskGroups_Request as Request
    from agt_interfaces.srv._list_task_groups import ListTaskGroups_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
