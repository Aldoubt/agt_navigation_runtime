// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:action/ChangeSystemMode.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__BUILDER_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/action/detail/change_system_mode__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ChangeSystemMode_Goal_startup_timeout_s
{
public:
  explicit Init_ChangeSystemMode_Goal_startup_timeout_s(::agt_interfaces::action::ChangeSystemMode_Goal & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ChangeSystemMode_Goal startup_timeout_s(::agt_interfaces::action::ChangeSystemMode_Goal::_startup_timeout_s_type arg)
  {
    msg_.startup_timeout_s = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Goal msg_;
};

class Init_ChangeSystemMode_Goal_wait_for_health
{
public:
  explicit Init_ChangeSystemMode_Goal_wait_for_health(::agt_interfaces::action::ChangeSystemMode_Goal & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Goal_startup_timeout_s wait_for_health(::agt_interfaces::action::ChangeSystemMode_Goal::_wait_for_health_type arg)
  {
    msg_.wait_for_health = std::move(arg);
    return Init_ChangeSystemMode_Goal_startup_timeout_s(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Goal msg_;
};

class Init_ChangeSystemMode_Goal_argument_values
{
public:
  explicit Init_ChangeSystemMode_Goal_argument_values(::agt_interfaces::action::ChangeSystemMode_Goal & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Goal_wait_for_health argument_values(::agt_interfaces::action::ChangeSystemMode_Goal::_argument_values_type arg)
  {
    msg_.argument_values = std::move(arg);
    return Init_ChangeSystemMode_Goal_wait_for_health(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Goal msg_;
};

class Init_ChangeSystemMode_Goal_argument_keys
{
public:
  explicit Init_ChangeSystemMode_Goal_argument_keys(::agt_interfaces::action::ChangeSystemMode_Goal & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Goal_argument_values argument_keys(::agt_interfaces::action::ChangeSystemMode_Goal::_argument_keys_type arg)
  {
    msg_.argument_keys = std::move(arg);
    return Init_ChangeSystemMode_Goal_argument_values(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Goal msg_;
};

class Init_ChangeSystemMode_Goal_profile
{
public:
  explicit Init_ChangeSystemMode_Goal_profile(::agt_interfaces::action::ChangeSystemMode_Goal & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Goal_argument_keys profile(::agt_interfaces::action::ChangeSystemMode_Goal::_profile_type arg)
  {
    msg_.profile = std::move(arg);
    return Init_ChangeSystemMode_Goal_argument_keys(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Goal msg_;
};

class Init_ChangeSystemMode_Goal_mode
{
public:
  Init_ChangeSystemMode_Goal_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChangeSystemMode_Goal_profile mode(::agt_interfaces::action::ChangeSystemMode_Goal::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_ChangeSystemMode_Goal_profile(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ChangeSystemMode_Goal>()
{
  return agt_interfaces::action::builder::Init_ChangeSystemMode_Goal_mode();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ChangeSystemMode_Result_message
{
public:
  explicit Init_ChangeSystemMode_Result_message(::agt_interfaces::action::ChangeSystemMode_Result & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ChangeSystemMode_Result message(::agt_interfaces::action::ChangeSystemMode_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Result msg_;
};

class Init_ChangeSystemMode_Result_log_paths
{
public:
  explicit Init_ChangeSystemMode_Result_log_paths(::agt_interfaces::action::ChangeSystemMode_Result & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Result_message log_paths(::agt_interfaces::action::ChangeSystemMode_Result::_log_paths_type arg)
  {
    msg_.log_paths = std::move(arg);
    return Init_ChangeSystemMode_Result_message(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Result msg_;
};

class Init_ChangeSystemMode_Result_process_ids
{
public:
  explicit Init_ChangeSystemMode_Result_process_ids(::agt_interfaces::action::ChangeSystemMode_Result & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Result_log_paths process_ids(::agt_interfaces::action::ChangeSystemMode_Result::_process_ids_type arg)
  {
    msg_.process_ids = std::move(arg);
    return Init_ChangeSystemMode_Result_log_paths(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Result msg_;
};

class Init_ChangeSystemMode_Result_profile
{
public:
  explicit Init_ChangeSystemMode_Result_profile(::agt_interfaces::action::ChangeSystemMode_Result & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Result_process_ids profile(::agt_interfaces::action::ChangeSystemMode_Result::_profile_type arg)
  {
    msg_.profile = std::move(arg);
    return Init_ChangeSystemMode_Result_process_ids(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Result msg_;
};

class Init_ChangeSystemMode_Result_active_mode
{
public:
  explicit Init_ChangeSystemMode_Result_active_mode(::agt_interfaces::action::ChangeSystemMode_Result & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Result_profile active_mode(::agt_interfaces::action::ChangeSystemMode_Result::_active_mode_type arg)
  {
    msg_.active_mode = std::move(arg);
    return Init_ChangeSystemMode_Result_profile(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Result msg_;
};

class Init_ChangeSystemMode_Result_error_code
{
public:
  explicit Init_ChangeSystemMode_Result_error_code(::agt_interfaces::action::ChangeSystemMode_Result & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Result_active_mode error_code(::agt_interfaces::action::ChangeSystemMode_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ChangeSystemMode_Result_active_mode(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Result msg_;
};

class Init_ChangeSystemMode_Result_success
{
public:
  Init_ChangeSystemMode_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChangeSystemMode_Result_error_code success(::agt_interfaces::action::ChangeSystemMode_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ChangeSystemMode_Result_error_code(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ChangeSystemMode_Result>()
{
  return agt_interfaces::action::builder::Init_ChangeSystemMode_Result_success();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ChangeSystemMode_Feedback_message
{
public:
  explicit Init_ChangeSystemMode_Feedback_message(::agt_interfaces::action::ChangeSystemMode_Feedback & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ChangeSystemMode_Feedback message(::agt_interfaces::action::ChangeSystemMode_Feedback::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Feedback msg_;
};

class Init_ChangeSystemMode_Feedback_progress
{
public:
  explicit Init_ChangeSystemMode_Feedback_progress(::agt_interfaces::action::ChangeSystemMode_Feedback & msg)
  : msg_(msg)
  {}
  Init_ChangeSystemMode_Feedback_message progress(::agt_interfaces::action::ChangeSystemMode_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_ChangeSystemMode_Feedback_message(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Feedback msg_;
};

class Init_ChangeSystemMode_Feedback_state
{
public:
  Init_ChangeSystemMode_Feedback_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChangeSystemMode_Feedback_progress state(::agt_interfaces::action::ChangeSystemMode_Feedback::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ChangeSystemMode_Feedback_progress(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ChangeSystemMode_Feedback>()
{
  return agt_interfaces::action::builder::Init_ChangeSystemMode_Feedback_state();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ChangeSystemMode_SendGoal_Request_goal
{
public:
  explicit Init_ChangeSystemMode_SendGoal_Request_goal(::agt_interfaces::action::ChangeSystemMode_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ChangeSystemMode_SendGoal_Request goal(::agt_interfaces::action::ChangeSystemMode_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_SendGoal_Request msg_;
};

class Init_ChangeSystemMode_SendGoal_Request_goal_id
{
public:
  Init_ChangeSystemMode_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChangeSystemMode_SendGoal_Request_goal goal_id(::agt_interfaces::action::ChangeSystemMode_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ChangeSystemMode_SendGoal_Request_goal(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ChangeSystemMode_SendGoal_Request>()
{
  return agt_interfaces::action::builder::Init_ChangeSystemMode_SendGoal_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ChangeSystemMode_SendGoal_Response_stamp
{
public:
  explicit Init_ChangeSystemMode_SendGoal_Response_stamp(::agt_interfaces::action::ChangeSystemMode_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ChangeSystemMode_SendGoal_Response stamp(::agt_interfaces::action::ChangeSystemMode_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_SendGoal_Response msg_;
};

class Init_ChangeSystemMode_SendGoal_Response_accepted
{
public:
  Init_ChangeSystemMode_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChangeSystemMode_SendGoal_Response_stamp accepted(::agt_interfaces::action::ChangeSystemMode_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_ChangeSystemMode_SendGoal_Response_stamp(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ChangeSystemMode_SendGoal_Response>()
{
  return agt_interfaces::action::builder::Init_ChangeSystemMode_SendGoal_Response_accepted();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ChangeSystemMode_GetResult_Request_goal_id
{
public:
  Init_ChangeSystemMode_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::action::ChangeSystemMode_GetResult_Request goal_id(::agt_interfaces::action::ChangeSystemMode_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ChangeSystemMode_GetResult_Request>()
{
  return agt_interfaces::action::builder::Init_ChangeSystemMode_GetResult_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ChangeSystemMode_GetResult_Response_result
{
public:
  explicit Init_ChangeSystemMode_GetResult_Response_result(::agt_interfaces::action::ChangeSystemMode_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ChangeSystemMode_GetResult_Response result(::agt_interfaces::action::ChangeSystemMode_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_GetResult_Response msg_;
};

class Init_ChangeSystemMode_GetResult_Response_status
{
public:
  Init_ChangeSystemMode_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChangeSystemMode_GetResult_Response_result status(::agt_interfaces::action::ChangeSystemMode_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_ChangeSystemMode_GetResult_Response_result(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ChangeSystemMode_GetResult_Response>()
{
  return agt_interfaces::action::builder::Init_ChangeSystemMode_GetResult_Response_status();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ChangeSystemMode_FeedbackMessage_feedback
{
public:
  explicit Init_ChangeSystemMode_FeedbackMessage_feedback(::agt_interfaces::action::ChangeSystemMode_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ChangeSystemMode_FeedbackMessage feedback(::agt_interfaces::action::ChangeSystemMode_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_FeedbackMessage msg_;
};

class Init_ChangeSystemMode_FeedbackMessage_goal_id
{
public:
  Init_ChangeSystemMode_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChangeSystemMode_FeedbackMessage_feedback goal_id(::agt_interfaces::action::ChangeSystemMode_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ChangeSystemMode_FeedbackMessage_feedback(msg_);
  }

private:
  ::agt_interfaces::action::ChangeSystemMode_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ChangeSystemMode_FeedbackMessage>()
{
  return agt_interfaces::action::builder::Init_ChangeSystemMode_FeedbackMessage_goal_id();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__BUILDER_HPP_
