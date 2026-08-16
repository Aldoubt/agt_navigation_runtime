# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:msg/MapVersionSummary.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MapVersionSummary(type):
    """Metaclass of message 'MapVersionSummary'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'STATE_UNKNOWN': 0,
        'STATE_DRAFT': 1,
        'STATE_PROCESSING': 2,
        'STATE_READY': 3,
        'STATE_INVALID': 4,
        'STATE_ARCHIVED': 5,
        'STATE_DELETED': 6,
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
                'agt_interfaces.msg.MapVersionSummary')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__map_version_summary
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__map_version_summary
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__map_version_summary
            cls._TYPE_SUPPORT = module.type_support_msg__msg__map_version_summary
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__map_version_summary

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'STATE_UNKNOWN': cls.__constants['STATE_UNKNOWN'],
            'STATE_DRAFT': cls.__constants['STATE_DRAFT'],
            'STATE_PROCESSING': cls.__constants['STATE_PROCESSING'],
            'STATE_READY': cls.__constants['STATE_READY'],
            'STATE_INVALID': cls.__constants['STATE_INVALID'],
            'STATE_ARCHIVED': cls.__constants['STATE_ARCHIVED'],
            'STATE_DELETED': cls.__constants['STATE_DELETED'],
        }

    @property
    def STATE_UNKNOWN(self):
        """Message constant 'STATE_UNKNOWN'."""
        return Metaclass_MapVersionSummary.__constants['STATE_UNKNOWN']

    @property
    def STATE_DRAFT(self):
        """Message constant 'STATE_DRAFT'."""
        return Metaclass_MapVersionSummary.__constants['STATE_DRAFT']

    @property
    def STATE_PROCESSING(self):
        """Message constant 'STATE_PROCESSING'."""
        return Metaclass_MapVersionSummary.__constants['STATE_PROCESSING']

    @property
    def STATE_READY(self):
        """Message constant 'STATE_READY'."""
        return Metaclass_MapVersionSummary.__constants['STATE_READY']

    @property
    def STATE_INVALID(self):
        """Message constant 'STATE_INVALID'."""
        return Metaclass_MapVersionSummary.__constants['STATE_INVALID']

    @property
    def STATE_ARCHIVED(self):
        """Message constant 'STATE_ARCHIVED'."""
        return Metaclass_MapVersionSummary.__constants['STATE_ARCHIVED']

    @property
    def STATE_DELETED(self):
        """Message constant 'STATE_DELETED'."""
        return Metaclass_MapVersionSummary.__constants['STATE_DELETED']


class MapVersionSummary(metaclass=Metaclass_MapVersionSummary):
    """
    Message class 'MapVersionSummary'.

    Constants:
      STATE_UNKNOWN
      STATE_DRAFT
      STATE_PROCESSING
      STATE_READY
      STATE_INVALID
      STATE_ARCHIVED
      STATE_DELETED
    """

    __slots__ = [
        '_header',
        '_map_id',
        '_map_version_id',
        '_parent_map_version_id',
        '_state',
        '_active',
        '_pinned',
        '_deleted',
        '_valid',
        '_map_hash',
        '_manifest_sha256',
        '_navigation_yaml_sha256',
        '_navigation_image_sha256',
        '_localization_pcd_sha256',
        '_navigation_yaml',
        '_localization_pcd',
        '_processing_record',
        '_tasks_directory',
        '_storage_bytes',
        '_created_at',
        '_validation_errors',
        '_validation_warnings',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'map_id': 'string',
        'map_version_id': 'string',
        'parent_map_version_id': 'string',
        'state': 'uint8',
        'active': 'boolean',
        'pinned': 'boolean',
        'deleted': 'boolean',
        'valid': 'boolean',
        'map_hash': 'string',
        'manifest_sha256': 'string',
        'navigation_yaml_sha256': 'string',
        'navigation_image_sha256': 'string',
        'localization_pcd_sha256': 'string',
        'navigation_yaml': 'string',
        'localization_pcd': 'string',
        'processing_record': 'string',
        'tasks_directory': 'string',
        'storage_bytes': 'uint64',
        'created_at': 'string',
        'validation_errors': 'sequence<string>',
        'validation_warnings': 'sequence<string>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.map_id = kwargs.get('map_id', str())
        self.map_version_id = kwargs.get('map_version_id', str())
        self.parent_map_version_id = kwargs.get('parent_map_version_id', str())
        self.state = kwargs.get('state', int())
        self.active = kwargs.get('active', bool())
        self.pinned = kwargs.get('pinned', bool())
        self.deleted = kwargs.get('deleted', bool())
        self.valid = kwargs.get('valid', bool())
        self.map_hash = kwargs.get('map_hash', str())
        self.manifest_sha256 = kwargs.get('manifest_sha256', str())
        self.navigation_yaml_sha256 = kwargs.get('navigation_yaml_sha256', str())
        self.navigation_image_sha256 = kwargs.get('navigation_image_sha256', str())
        self.localization_pcd_sha256 = kwargs.get('localization_pcd_sha256', str())
        self.navigation_yaml = kwargs.get('navigation_yaml', str())
        self.localization_pcd = kwargs.get('localization_pcd', str())
        self.processing_record = kwargs.get('processing_record', str())
        self.tasks_directory = kwargs.get('tasks_directory', str())
        self.storage_bytes = kwargs.get('storage_bytes', int())
        self.created_at = kwargs.get('created_at', str())
        self.validation_errors = kwargs.get('validation_errors', [])
        self.validation_warnings = kwargs.get('validation_warnings', [])

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
        if self.map_id != other.map_id:
            return False
        if self.map_version_id != other.map_version_id:
            return False
        if self.parent_map_version_id != other.parent_map_version_id:
            return False
        if self.state != other.state:
            return False
        if self.active != other.active:
            return False
        if self.pinned != other.pinned:
            return False
        if self.deleted != other.deleted:
            return False
        if self.valid != other.valid:
            return False
        if self.map_hash != other.map_hash:
            return False
        if self.manifest_sha256 != other.manifest_sha256:
            return False
        if self.navigation_yaml_sha256 != other.navigation_yaml_sha256:
            return False
        if self.navigation_image_sha256 != other.navigation_image_sha256:
            return False
        if self.localization_pcd_sha256 != other.localization_pcd_sha256:
            return False
        if self.navigation_yaml != other.navigation_yaml:
            return False
        if self.localization_pcd != other.localization_pcd:
            return False
        if self.processing_record != other.processing_record:
            return False
        if self.tasks_directory != other.tasks_directory:
            return False
        if self.storage_bytes != other.storage_bytes:
            return False
        if self.created_at != other.created_at:
            return False
        if self.validation_errors != other.validation_errors:
            return False
        if self.validation_warnings != other.validation_warnings:
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

    @builtins.property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'state' field must be an unsigned integer in [0, 255]"
        self._state = value

    @builtins.property
    def active(self):
        """Message field 'active'."""
        return self._active

    @active.setter
    def active(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'active' field must be of type 'bool'"
        self._active = value

    @builtins.property
    def pinned(self):
        """Message field 'pinned'."""
        return self._pinned

    @pinned.setter
    def pinned(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'pinned' field must be of type 'bool'"
        self._pinned = value

    @builtins.property
    def deleted(self):
        """Message field 'deleted'."""
        return self._deleted

    @deleted.setter
    def deleted(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'deleted' field must be of type 'bool'"
        self._deleted = value

    @builtins.property
    def valid(self):
        """Message field 'valid'."""
        return self._valid

    @valid.setter
    def valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'valid' field must be of type 'bool'"
        self._valid = value

    @builtins.property
    def map_hash(self):
        """Message field 'map_hash'."""
        return self._map_hash

    @map_hash.setter
    def map_hash(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_hash' field must be of type 'str'"
        self._map_hash = value

    @builtins.property
    def manifest_sha256(self):
        """Message field 'manifest_sha256'."""
        return self._manifest_sha256

    @manifest_sha256.setter
    def manifest_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'manifest_sha256' field must be of type 'str'"
        self._manifest_sha256 = value

    @builtins.property
    def navigation_yaml_sha256(self):
        """Message field 'navigation_yaml_sha256'."""
        return self._navigation_yaml_sha256

    @navigation_yaml_sha256.setter
    def navigation_yaml_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'navigation_yaml_sha256' field must be of type 'str'"
        self._navigation_yaml_sha256 = value

    @builtins.property
    def navigation_image_sha256(self):
        """Message field 'navigation_image_sha256'."""
        return self._navigation_image_sha256

    @navigation_image_sha256.setter
    def navigation_image_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'navigation_image_sha256' field must be of type 'str'"
        self._navigation_image_sha256 = value

    @builtins.property
    def localization_pcd_sha256(self):
        """Message field 'localization_pcd_sha256'."""
        return self._localization_pcd_sha256

    @localization_pcd_sha256.setter
    def localization_pcd_sha256(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'localization_pcd_sha256' field must be of type 'str'"
        self._localization_pcd_sha256 = value

    @builtins.property
    def navigation_yaml(self):
        """Message field 'navigation_yaml'."""
        return self._navigation_yaml

    @navigation_yaml.setter
    def navigation_yaml(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'navigation_yaml' field must be of type 'str'"
        self._navigation_yaml = value

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
    def storage_bytes(self):
        """Message field 'storage_bytes'."""
        return self._storage_bytes

    @storage_bytes.setter
    def storage_bytes(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'storage_bytes' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'storage_bytes' field must be an unsigned integer in [0, 18446744073709551615]"
        self._storage_bytes = value

    @builtins.property
    def created_at(self):
        """Message field 'created_at'."""
        return self._created_at

    @created_at.setter
    def created_at(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'created_at' field must be of type 'str'"
        self._created_at = value

    @builtins.property
    def validation_errors(self):
        """Message field 'validation_errors'."""
        return self._validation_errors

    @validation_errors.setter
    def validation_errors(self, value):
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
                "The 'validation_errors' field must be a set or sequence and each value of type 'str'"
        self._validation_errors = value

    @builtins.property
    def validation_warnings(self):
        """Message field 'validation_warnings'."""
        return self._validation_warnings

    @validation_warnings.setter
    def validation_warnings(self, value):
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
                "The 'validation_warnings' field must be a set or sequence and each value of type 'str'"
        self._validation_warnings = value
