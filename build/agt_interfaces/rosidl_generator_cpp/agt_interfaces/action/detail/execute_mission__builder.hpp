// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:action/ExecuteMission.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_MISSION__BUILDER_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_MISSION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/action/detail/execute_mission__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_Goal_expected_content_sha256
{
public:
  explicit Init_ExecuteMission_Goal_expected_content_sha256(::agt_interfaces::action::ExecuteMission_Goal & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteMission_Goal expected_content_sha256(::agt_interfaces::action::ExecuteMission_Goal::_expected_content_sha256_type arg)
  {
    msg_.expected_content_sha256 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_Goal msg_;
};

class Init_ExecuteMission_Goal_mission_version
{
public:
  explicit Init_ExecuteMission_Goal_mission_version(::agt_interfaces::action::ExecuteMission_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Goal_expected_content_sha256 mission_version(::agt_interfaces::action::ExecuteMission_Goal::_mission_version_type arg)
  {
    msg_.mission_version = std::move(arg);
    return Init_ExecuteMission_Goal_expected_content_sha256(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_Goal msg_;
};

class Init_ExecuteMission_Goal_mission_id
{
public:
  Init_ExecuteMission_Goal_mission_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_Goal_mission_version mission_id(::agt_interfaces::action::ExecuteMission_Goal::_mission_id_type arg)
  {
    msg_.mission_id = std::move(arg);
    return Init_ExecuteMission_Goal_mission_version(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteMission_Goal>()
{
  return agt_interfaces::action::builder::Init_ExecuteMission_Goal_mission_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_Result_message
{
public:
  explicit Init_ExecuteMission_Result_message(::agt_interfaces::action::ExecuteMission_Result & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteMission_Result message(::agt_interfaces::action::ExecuteMission_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_Result msg_;
};

class Init_ExecuteMission_Result_audit_log_uri
{
public:
  explicit Init_ExecuteMission_Result_audit_log_uri(::agt_interfaces::action::ExecuteMission_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Result_message audit_log_uri(::agt_interfaces::action::ExecuteMission_Result::_audit_log_uri_type arg)
  {
    msg_.audit_log_uri = std::move(arg);
    return Init_ExecuteMission_Result_message(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_Result msg_;
};

class Init_ExecuteMission_Result_final_status
{
public:
  explicit Init_ExecuteMission_Result_final_status(::agt_interfaces::action::ExecuteMission_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Result_audit_log_uri final_status(::agt_interfaces::action::ExecuteMission_Result::_final_status_type arg)
  {
    msg_.final_status = std::move(arg);
    return Init_ExecuteMission_Result_audit_log_uri(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_Result msg_;
};

class Init_ExecuteMission_Result_error_code
{
public:
  explicit Init_ExecuteMission_Result_error_code(::agt_interfaces::action::ExecuteMission_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Result_final_status error_code(::agt_interfaces::action::ExecuteMission_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ExecuteMission_Result_final_status(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_Result msg_;
};

class Init_ExecuteMission_Result_success
{
public:
  Init_ExecuteMission_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_Result_error_code success(::agt_interfaces::action::ExecuteMission_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ExecuteMission_Result_error_code(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteMission_Result>()
{
  return agt_interfaces::action::builder::Init_ExecuteMission_Result_success();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_Feedback_status
{
public:
  Init_ExecuteMission_Feedback_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::action::ExecuteMission_Feedback status(::agt_interfaces::action::ExecuteMission_Feedback::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteMission_Feedback>()
{
  return agt_interfaces::action::builder::Init_ExecuteMission_Feedback_status();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_SendGoal_Request_goal
{
public:
  explicit Init_ExecuteMission_SendGoal_Request_goal(::agt_interfaces::action::ExecuteMission_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteMission_SendGoal_Request goal(::agt_interfaces::action::ExecuteMission_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_SendGoal_Request msg_;
};

class Init_ExecuteMission_SendGoal_Request_goal_id
{
public:
  Init_ExecuteMission_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_SendGoal_Request_goal goal_id(::agt_interfaces::action::ExecuteMission_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteMission_SendGoal_Request_goal(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteMission_SendGoal_Request>()
{
  return agt_interfaces::action::builder::Init_ExecuteMission_SendGoal_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_SendGoal_Response_stamp
{
public:
  explicit Init_ExecuteMission_SendGoal_Response_stamp(::agt_interfaces::action::ExecuteMission_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteMission_SendGoal_Response stamp(::agt_interfaces::action::ExecuteMission_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_SendGoal_Response msg_;
};

class Init_ExecuteMission_SendGoal_Response_accepted
{
public:
  Init_ExecuteMission_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_SendGoal_Response_stamp accepted(::agt_interfaces::action::ExecuteMission_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_ExecuteMission_SendGoal_Response_stamp(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteMission_SendGoal_Response>()
{
  return agt_interfaces::action::builder::Init_ExecuteMission_SendGoal_Response_accepted();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_GetResult_Request_goal_id
{
public:
  Init_ExecuteMission_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::action::ExecuteMission_GetResult_Request goal_id(::agt_interfaces::action::ExecuteMission_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteMission_GetResult_Request>()
{
  return agt_interfaces::action::builder::Init_ExecuteMission_GetResult_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_GetResult_Response_result
{
public:
  explicit Init_ExecuteMission_GetResult_Response_result(::agt_interfaces::action::ExecuteMission_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteMission_GetResult_Response result(::agt_interfaces::action::ExecuteMission_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_GetResult_Response msg_;
};

class Init_ExecuteMission_GetResult_Response_status
{
public:
  Init_ExecuteMission_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_GetResult_Response_result status(::agt_interfaces::action::ExecuteMission_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_ExecuteMission_GetResult_Response_result(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteMission_GetResult_Response>()
{
  return agt_interfaces::action::builder::Init_ExecuteMission_GetResult_Response_status();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_FeedbackMessage_feedback
{
public:
  explicit Init_ExecuteMission_FeedbackMessage_feedback(::agt_interfaces::action::ExecuteMission_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteMission_FeedbackMessage feedback(::agt_interfaces::action::ExecuteMission_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_FeedbackMessage msg_;
};

class Init_ExecuteMission_FeedbackMessage_goal_id
{
public:
  Init_ExecuteMission_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_FeedbackMessage_feedback goal_id(::agt_interfaces::action::ExecuteMission_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteMission_FeedbackMessage_feedback(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteMission_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteMission_FeedbackMessage>()
{
  return agt_interfaces::action::builder::Init_ExecuteMission_FeedbackMessage_goal_id();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_MISSION__BUILDER_HPP_
