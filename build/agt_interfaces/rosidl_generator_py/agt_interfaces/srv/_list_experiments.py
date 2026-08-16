# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agt_interfaces:srv/ListExperiments.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ListExperiments_Request(type):
    """Metaclass of message 'ListExperiments_Request'."""

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
                'agt_interfaces.srv.ListExperiments_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__list_experiments__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__list_experiments__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__list_experiments__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__list_experiments__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__list_experiments__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ListExperiments_Request(metaclass=Metaclass_ListExperiments_Request):
    """Message class 'ListExperiments_Request'."""

    __slots__ = [
        '_state',
    ]

    _fields_and_field_types = {
        'state': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.state = kwargs.get('state', int())

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
                isinstance(value, int), \
                "The 'state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'state' field must be an unsigned integer in [0, 255]"
        self._state = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ListExperiments_Response(type):
    """Metaclass of message 'ListExperiments_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ERROR_NONE': 0,
        'ERROR_INVALID_REQUEST': 1,
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
                'agt_interfaces.srv.ListExperiments_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__list_experiments__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__list_experiments__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__list_experiments__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__list_experiments__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__list_experiments__response

            from agt_interfaces.msg import ExperimentSummary
            if ExperimentSummary.__class__._TYPE_SUPPORT is None:
                ExperimentSummary.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_INVALID_REQUEST': cls.__constants['ERROR_INVALID_REQUEST'],
            'ERROR_INTERNAL': cls.__constants['ERROR_INTERNAL'],
        }

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_ListExperiments_Response.__constants['ERROR_NONE']

    @property
    def ERROR_INVALID_REQUEST(self):
        """Message constant 'ERROR_INVALID_REQUEST'."""
        return Metaclass_ListExperiments_Response.__constants['ERROR_INVALID_REQUEST']

    @property
    def ERROR_INTERNAL(self):
        """Message constant 'ERROR_INTERNAL'."""
        return Metaclass_ListExperiments_Response.__constants['ERROR_INTERNAL']


class ListExperiments_Response(metaclass=Metaclass_ListExperiments_Response):
    """
    Message class 'ListExperiments_Response'.

    Constants:
      ERROR_NONE
      ERROR_INVALID_REQUEST
      ERROR_INTERNAL
    """

    __slots__ = [
        '_success',
        '_error_code',
        '_experiments',
        '_message',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'error_code': 'uint16',
        'experiments': 'sequence<agt_interfaces/ExperimentSummary>',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['agt_interfaces', 'msg'], 'ExperimentSummary')),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.error_code = kwargs.get('error_code', int())
        self.experiments = kwargs.get('experiments', [])
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
        if self.experiments != other.experiments:
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
    def experiments(self):
        """Message field 'experiments'."""
        return self._experiments

    @experiments.setter
    def experiments(self, value):
        if __debug__:
            from agt_interfaces.msg import ExperimentSummary
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
                 all(isinstance(v, ExperimentSummary) for v in value) and
                 True), \
                "The 'experiments' field must be a set or sequence and each value of type 'ExperimentSummary'"
        self._experiments = value

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


class Metaclass_ListExperiments(type):
    """Metaclass of service 'ListExperiments'."""

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
                'agt_interfaces.srv.ListExperiments')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__list_experiments

            from agt_interfaces.srv import _list_experiments
            if _list_experiments.Metaclass_ListExperiments_Request._TYPE_SUPPORT is None:
                _list_experiments.Metaclass_ListExperiments_Request.__import_type_support__()
            if _list_experiments.Metaclass_ListExperiments_Response._TYPE_SUPPORT is None:
                _list_experiments.Metaclass_ListExperiments_Response.__import_type_support__()


class ListExperiments(metaclass=Metaclass_ListExperiments):
    from agt_interfaces.srv._list_experiments import ListExperiments_Request as Request
    from agt_interfaces.srv._list_experiments import ListExperiments_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
