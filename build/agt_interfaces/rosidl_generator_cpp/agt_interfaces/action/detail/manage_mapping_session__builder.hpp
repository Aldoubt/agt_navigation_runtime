// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:action/ManageMappingSession.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__MANAGE_MAPPING_SESSION__BUILDER_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__MANAGE_MAPPING_SESSION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/action/detail/manage_mapping_session__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ManageMappingSession_Goal_timeout_s
{
public:
  explicit Init_ManageMappingSession_Goal_timeout_s(::agt_interfaces::action::ManageMappingSession_Goal & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ManageMappingSession_Goal timeout_s(::agt_interfaces::action::ManageMappingSession_Goal::_timeout_s_type arg)
  {
    msg_.timeout_s = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Goal msg_;
};

class Init_ManageMappingSession_Goal_activate_after_commit
{
public:
  explicit Init_ManageMappingSession_Goal_activate_after_commit(::agt_interfaces::action::ManageMappingSession_Goal & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Goal_timeout_s activate_after_commit(::agt_interfaces::action::ManageMappingSession_Goal::_activate_after_commit_type arg)
  {
    msg_.activate_after_commit = std::move(arg);
    return Init_ManageMappingSession_Goal_timeout_s(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Goal msg_;
};

class Init_ManageMappingSession_Goal_argument_values
{
public:
  explicit Init_ManageMappingSession_Goal_argument_values(::agt_interfaces::action::ManageMappingSession_Goal & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Goal_activate_after_commit argument_values(::agt_interfaces::action::ManageMappingSession_Goal::_argument_values_type arg)
  {
    msg_.argument_values = std::move(arg);
    return Init_ManageMappingSession_Goal_activate_after_commit(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Goal msg_;
};

class Init_ManageMappingSession_Goal_argument_keys
{
public:
  explicit Init_ManageMappingSession_Goal_argument_keys(::agt_interfaces::action::ManageMappingSession_Goal & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Goal_argument_values argument_keys(::agt_interfaces::action::ManageMappingSession_Goal::_argument_keys_type arg)
  {
    msg_.argument_keys = std::move(arg);
    return Init_ManageMappingSession_Goal_argument_values(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Goal msg_;
};

class Init_ManageMappingSession_Goal_session_id
{
public:
  explicit Init_ManageMappingSession_Goal_session_id(::agt_interfaces::action::ManageMappingSession_Goal & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Goal_argument_keys session_id(::agt_interfaces::action::ManageMappingSession_Goal::_session_id_type arg)
  {
    msg_.session_id = std::move(arg);
    return Init_ManageMappingSession_Goal_argument_keys(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Goal msg_;
};

class Init_ManageMappingSession_Goal_map_id
{
public:
  explicit Init_ManageMappingSession_Goal_map_id(::agt_interfaces::action::ManageMappingSession_Goal & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Goal_session_id map_id(::agt_interfaces::action::ManageMappingSession_Goal::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ManageMappingSession_Goal_session_id(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Goal msg_;
};

class Init_ManageMappingSession_Goal_operation
{
public:
  Init_ManageMappingSession_Goal_operation()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageMappingSession_Goal_map_id operation(::agt_interfaces::action::ManageMappingSession_Goal::_operation_type arg)
  {
    msg_.operation = std::move(arg);
    return Init_ManageMappingSession_Goal_map_id(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ManageMappingSession_Goal>()
{
  return agt_interfaces::action::builder::Init_ManageMappingSession_Goal_operation();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ManageMappingSession_Result_message
{
public:
  explicit Init_ManageMappingSession_Result_message(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ManageMappingSession_Result message(::agt_interfaces::action::ManageMappingSession_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_tasks_directory
{
public:
  explicit Init_ManageMappingSession_Result_tasks_directory(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_message tasks_directory(::agt_interfaces::action::ManageMappingSession_Result::_tasks_directory_type arg)
  {
    msg_.tasks_directory = std::move(arg);
    return Init_ManageMappingSession_Result_message(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_registered_map_yaml
{
public:
  explicit Init_ManageMappingSession_Result_registered_map_yaml(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_tasks_directory registered_map_yaml(::agt_interfaces::action::ManageMappingSession_Result::_registered_map_yaml_type arg)
  {
    msg_.registered_map_yaml = std::move(arg);
    return Init_ManageMappingSession_Result_tasks_directory(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_bag_directory
{
public:
  explicit Init_ManageMappingSession_Result_bag_directory(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_registered_map_yaml bag_directory(::agt_interfaces::action::ManageMappingSession_Result::_bag_directory_type arg)
  {
    msg_.bag_directory = std::move(arg);
    return Init_ManageMappingSession_Result_registered_map_yaml(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_processing_record
{
public:
  explicit Init_ManageMappingSession_Result_processing_record(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_bag_directory processing_record(::agt_interfaces::action::ManageMappingSession_Result::_processing_record_type arg)
  {
    msg_.processing_record = std::move(arg);
    return Init_ManageMappingSession_Result_bag_directory(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_localization_pcd
{
public:
  explicit Init_ManageMappingSession_Result_localization_pcd(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_processing_record localization_pcd(::agt_interfaces::action::ManageMappingSession_Result::_localization_pcd_type arg)
  {
    msg_.localization_pcd = std::move(arg);
    return Init_ManageMappingSession_Result_processing_record(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_candidate_map_image
{
public:
  explicit Init_ManageMappingSession_Result_candidate_map_image(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_localization_pcd candidate_map_image(::agt_interfaces::action::ManageMappingSession_Result::_candidate_map_image_type arg)
  {
    msg_.candidate_map_image = std::move(arg);
    return Init_ManageMappingSession_Result_localization_pcd(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_candidate_map_yaml
{
public:
  explicit Init_ManageMappingSession_Result_candidate_map_yaml(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_candidate_map_image candidate_map_yaml(::agt_interfaces::action::ManageMappingSession_Result::_candidate_map_yaml_type arg)
  {
    msg_.candidate_map_yaml = std::move(arg);
    return Init_ManageMappingSession_Result_candidate_map_image(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_session_file
{
public:
  explicit Init_ManageMappingSession_Result_session_file(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_candidate_map_yaml session_file(::agt_interfaces::action::ManageMappingSession_Result::_session_file_type arg)
  {
    msg_.session_file = std::move(arg);
    return Init_ManageMappingSession_Result_candidate_map_yaml(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_map_version_id
{
public:
  explicit Init_ManageMappingSession_Result_map_version_id(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_session_file map_version_id(::agt_interfaces::action::ManageMappingSession_Result::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ManageMappingSession_Result_session_file(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_map_id
{
public:
  explicit Init_ManageMappingSession_Result_map_id(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_map_version_id map_id(::agt_interfaces::action::ManageMappingSession_Result::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ManageMappingSession_Result_map_version_id(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_session_id
{
public:
  explicit Init_ManageMappingSession_Result_session_id(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_map_id session_id(::agt_interfaces::action::ManageMappingSession_Result::_session_id_type arg)
  {
    msg_.session_id = std::move(arg);
    return Init_ManageMappingSession_Result_map_id(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_state
{
public:
  explicit Init_ManageMappingSession_Result_state(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_session_id state(::agt_interfaces::action::ManageMappingSession_Result::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ManageMappingSession_Result_session_id(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_error_code
{
public:
  explicit Init_ManageMappingSession_Result_error_code(::agt_interfaces::action::ManageMappingSession_Result & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Result_state error_code(::agt_interfaces::action::ManageMappingSession_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ManageMappingSession_Result_state(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

class Init_ManageMappingSession_Result_success
{
public:
  Init_ManageMappingSession_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageMappingSession_Result_error_code success(::agt_interfaces::action::ManageMappingSession_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ManageMappingSession_Result_error_code(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ManageMappingSession_Result>()
{
  return agt_interfaces::action::builder::Init_ManageMappingSession_Result_success();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ManageMappingSession_Feedback_message
{
public:
  explicit Init_ManageMappingSession_Feedback_message(::agt_interfaces::action::ManageMappingSession_Feedback & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ManageMappingSession_Feedback message(::agt_interfaces::action::ManageMappingSession_Feedback::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Feedback msg_;
};

class Init_ManageMappingSession_Feedback_progress
{
public:
  explicit Init_ManageMappingSession_Feedback_progress(::agt_interfaces::action::ManageMappingSession_Feedback & msg)
  : msg_(msg)
  {}
  Init_ManageMappingSession_Feedback_message progress(::agt_interfaces::action::ManageMappingSession_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_ManageMappingSession_Feedback_message(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Feedback msg_;
};

class Init_ManageMappingSession_Feedback_state
{
public:
  Init_ManageMappingSession_Feedback_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageMappingSession_Feedback_progress state(::agt_interfaces::action::ManageMappingSession_Feedback::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ManageMappingSession_Feedback_progress(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ManageMappingSession_Feedback>()
{
  return agt_interfaces::action::builder::Init_ManageMappingSession_Feedback_state();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ManageMappingSession_SendGoal_Request_goal
{
public:
  explicit Init_ManageMappingSession_SendGoal_Request_goal(::agt_interfaces::action::ManageMappingSession_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ManageMappingSession_SendGoal_Request goal(::agt_interfaces::action::ManageMappingSession_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_SendGoal_Request msg_;
};

class Init_ManageMappingSession_SendGoal_Request_goal_id
{
public:
  Init_ManageMappingSession_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageMappingSession_SendGoal_Request_goal goal_id(::agt_interfaces::action::ManageMappingSession_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ManageMappingSession_SendGoal_Request_goal(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ManageMappingSession_SendGoal_Request>()
{
  return agt_interfaces::action::builder::Init_ManageMappingSession_SendGoal_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ManageMappingSession_SendGoal_Response_stamp
{
public:
  explicit Init_ManageMappingSession_SendGoal_Response_stamp(::agt_interfaces::action::ManageMappingSession_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ManageMappingSession_SendGoal_Response stamp(::agt_interfaces::action::ManageMappingSession_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_SendGoal_Response msg_;
};

class Init_ManageMappingSession_SendGoal_Response_accepted
{
public:
  Init_ManageMappingSession_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageMappingSession_SendGoal_Response_stamp accepted(::agt_interfaces::action::ManageMappingSession_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_ManageMappingSession_SendGoal_Response_stamp(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ManageMappingSession_SendGoal_Response>()
{
  return agt_interfaces::action::builder::Init_ManageMappingSession_SendGoal_Response_accepted();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ManageMappingSession_GetResult_Request_goal_id
{
public:
  Init_ManageMappingSession_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::action::ManageMappingSession_GetResult_Request goal_id(::agt_interfaces::action::ManageMappingSession_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ManageMappingSession_GetResult_Request>()
{
  return agt_interfaces::action::builder::Init_ManageMappingSession_GetResult_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ManageMappingSession_GetResult_Response_result
{
public:
  explicit Init_ManageMappingSession_GetResult_Response_result(::agt_interfaces::action::ManageMappingSession_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ManageMappingSession_GetResult_Response result(::agt_interfaces::action::ManageMappingSession_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_GetResult_Response msg_;
};

class Init_ManageMappingSession_GetResult_Response_status
{
public:
  Init_ManageMappingSession_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageMappingSession_GetResult_Response_result status(::agt_interfaces::action::ManageMappingSession_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_ManageMappingSession_GetResult_Response_result(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ManageMappingSession_GetResult_Response>()
{
  return agt_interfaces::action::builder::Init_ManageMappingSession_GetResult_Response_status();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ManageMappingSession_FeedbackMessage_feedback
{
public:
  explicit Init_ManageMappingSession_FeedbackMessage_feedback(::agt_interfaces::action::ManageMappingSession_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ManageMappingSession_FeedbackMessage feedback(::agt_interfaces::action::ManageMappingSession_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_FeedbackMessage msg_;
};

class Init_ManageMappingSession_FeedbackMessage_goal_id
{
public:
  Init_ManageMappingSession_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageMappingSession_FeedbackMessage_feedback goal_id(::agt_interfaces::action::ManageMappingSession_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ManageMappingSession_FeedbackMessage_feedback(msg_);
  }

private:
  ::agt_interfaces::action::ManageMappingSession_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ManageMappingSession_FeedbackMessage>()
{
  return agt_interfaces::action::builder::Init_ManageMappingSession_FeedbackMessage_goal_id();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__MANAGE_MAPPING_SESSION__BUILDER_HPP_
