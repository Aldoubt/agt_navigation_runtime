// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:action/Relocalize.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__BUILDER_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/action/detail/relocalize__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_Relocalize_Goal_timeout_s
{
public:
  explicit Init_Relocalize_Goal_timeout_s(::agt_interfaces::action::Relocalize_Goal & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::Relocalize_Goal timeout_s(::agt_interfaces::action::Relocalize_Goal::_timeout_s_type arg)
  {
    msg_.timeout_s = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Goal msg_;
};

class Init_Relocalize_Goal_publish_debug
{
public:
  explicit Init_Relocalize_Goal_publish_debug(::agt_interfaces::action::Relocalize_Goal & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Goal_timeout_s publish_debug(::agt_interfaces::action::Relocalize_Goal::_publish_debug_type arg)
  {
    msg_.publish_debug = std::move(arg);
    return Init_Relocalize_Goal_timeout_s(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Goal msg_;
};

class Init_Relocalize_Goal_max_candidates
{
public:
  explicit Init_Relocalize_Goal_max_candidates(::agt_interfaces::action::Relocalize_Goal & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Goal_publish_debug max_candidates(::agt_interfaces::action::Relocalize_Goal::_max_candidates_type arg)
  {
    msg_.max_candidates = std::move(arg);
    return Init_Relocalize_Goal_publish_debug(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Goal msg_;
};

class Init_Relocalize_Goal_use_external_coarse_pose
{
public:
  explicit Init_Relocalize_Goal_use_external_coarse_pose(::agt_interfaces::action::Relocalize_Goal & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Goal_max_candidates use_external_coarse_pose(::agt_interfaces::action::Relocalize_Goal::_use_external_coarse_pose_type arg)
  {
    msg_.use_external_coarse_pose = std::move(arg);
    return Init_Relocalize_Goal_max_candidates(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Goal msg_;
};

class Init_Relocalize_Goal_use_configured_candidates
{
public:
  explicit Init_Relocalize_Goal_use_configured_candidates(::agt_interfaces::action::Relocalize_Goal & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Goal_use_external_coarse_pose use_configured_candidates(::agt_interfaces::action::Relocalize_Goal::_use_configured_candidates_type arg)
  {
    msg_.use_configured_candidates = std::move(arg);
    return Init_Relocalize_Goal_use_external_coarse_pose(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Goal msg_;
};

class Init_Relocalize_Goal_use_last_valid_pose
{
public:
  explicit Init_Relocalize_Goal_use_last_valid_pose(::agt_interfaces::action::Relocalize_Goal & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Goal_use_configured_candidates use_last_valid_pose(::agt_interfaces::action::Relocalize_Goal::_use_last_valid_pose_type arg)
  {
    msg_.use_last_valid_pose = std::move(arg);
    return Init_Relocalize_Goal_use_configured_candidates(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Goal msg_;
};

class Init_Relocalize_Goal_initial_pose
{
public:
  explicit Init_Relocalize_Goal_initial_pose(::agt_interfaces::action::Relocalize_Goal & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Goal_use_last_valid_pose initial_pose(::agt_interfaces::action::Relocalize_Goal::_initial_pose_type arg)
  {
    msg_.initial_pose = std::move(arg);
    return Init_Relocalize_Goal_use_last_valid_pose(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Goal msg_;
};

class Init_Relocalize_Goal_use_initial_pose
{
public:
  explicit Init_Relocalize_Goal_use_initial_pose(::agt_interfaces::action::Relocalize_Goal & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Goal_initial_pose use_initial_pose(::agt_interfaces::action::Relocalize_Goal::_use_initial_pose_type arg)
  {
    msg_.use_initial_pose = std::move(arg);
    return Init_Relocalize_Goal_initial_pose(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Goal msg_;
};

class Init_Relocalize_Goal_mode
{
public:
  Init_Relocalize_Goal_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Relocalize_Goal_use_initial_pose mode(::agt_interfaces::action::Relocalize_Goal::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_Relocalize_Goal_use_initial_pose(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::Relocalize_Goal>()
{
  return agt_interfaces::action::builder::Init_Relocalize_Goal_mode();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_Relocalize_Result_failure_reason
{
public:
  explicit Init_Relocalize_Result_failure_reason(::agt_interfaces::action::Relocalize_Result & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::Relocalize_Result failure_reason(::agt_interfaces::action::Relocalize_Result::_failure_reason_type arg)
  {
    msg_.failure_reason = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Result msg_;
};

class Init_Relocalize_Result_final_status
{
public:
  explicit Init_Relocalize_Result_final_status(::agt_interfaces::action::Relocalize_Result & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Result_failure_reason final_status(::agt_interfaces::action::Relocalize_Result::_final_status_type arg)
  {
    msg_.final_status = std::move(arg);
    return Init_Relocalize_Result_failure_reason(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Result msg_;
};

class Init_Relocalize_Result_final_pose
{
public:
  explicit Init_Relocalize_Result_final_pose(::agt_interfaces::action::Relocalize_Result & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Result_final_status final_pose(::agt_interfaces::action::Relocalize_Result::_final_pose_type arg)
  {
    msg_.final_pose = std::move(arg);
    return Init_Relocalize_Result_final_status(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Result msg_;
};

class Init_Relocalize_Result_error_code
{
public:
  explicit Init_Relocalize_Result_error_code(::agt_interfaces::action::Relocalize_Result & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Result_final_pose error_code(::agt_interfaces::action::Relocalize_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_Relocalize_Result_final_pose(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Result msg_;
};

class Init_Relocalize_Result_success
{
public:
  Init_Relocalize_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Relocalize_Result_error_code success(::agt_interfaces::action::Relocalize_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_Relocalize_Result_error_code(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::Relocalize_Result>()
{
  return agt_interfaces::action::builder::Init_Relocalize_Result_success();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_Relocalize_Feedback_elapsed_s
{
public:
  explicit Init_Relocalize_Feedback_elapsed_s(::agt_interfaces::action::Relocalize_Feedback & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::Relocalize_Feedback elapsed_s(::agt_interfaces::action::Relocalize_Feedback::_elapsed_s_type arg)
  {
    msg_.elapsed_s = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Feedback msg_;
};

class Init_Relocalize_Feedback_best_candidate_source
{
public:
  explicit Init_Relocalize_Feedback_best_candidate_source(::agt_interfaces::action::Relocalize_Feedback & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Feedback_elapsed_s best_candidate_source(::agt_interfaces::action::Relocalize_Feedback::_best_candidate_source_type arg)
  {
    msg_.best_candidate_source = std::move(arg);
    return Init_Relocalize_Feedback_elapsed_s(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Feedback msg_;
};

class Init_Relocalize_Feedback_best_fitness_score
{
public:
  explicit Init_Relocalize_Feedback_best_fitness_score(::agt_interfaces::action::Relocalize_Feedback & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Feedback_best_candidate_source best_fitness_score(::agt_interfaces::action::Relocalize_Feedback::_best_fitness_score_type arg)
  {
    msg_.best_fitness_score = std::move(arg);
    return Init_Relocalize_Feedback_best_candidate_source(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Feedback msg_;
};

class Init_Relocalize_Feedback_tested_candidates
{
public:
  explicit Init_Relocalize_Feedback_tested_candidates(::agt_interfaces::action::Relocalize_Feedback & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Feedback_best_fitness_score tested_candidates(::agt_interfaces::action::Relocalize_Feedback::_tested_candidates_type arg)
  {
    msg_.tested_candidates = std::move(arg);
    return Init_Relocalize_Feedback_best_fitness_score(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Feedback msg_;
};

class Init_Relocalize_Feedback_total_candidates
{
public:
  explicit Init_Relocalize_Feedback_total_candidates(::agt_interfaces::action::Relocalize_Feedback & msg)
  : msg_(msg)
  {}
  Init_Relocalize_Feedback_tested_candidates total_candidates(::agt_interfaces::action::Relocalize_Feedback::_total_candidates_type arg)
  {
    msg_.total_candidates = std::move(arg);
    return Init_Relocalize_Feedback_tested_candidates(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Feedback msg_;
};

class Init_Relocalize_Feedback_state
{
public:
  Init_Relocalize_Feedback_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Relocalize_Feedback_total_candidates state(::agt_interfaces::action::Relocalize_Feedback::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_Relocalize_Feedback_total_candidates(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::Relocalize_Feedback>()
{
  return agt_interfaces::action::builder::Init_Relocalize_Feedback_state();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_Relocalize_SendGoal_Request_goal
{
public:
  explicit Init_Relocalize_SendGoal_Request_goal(::agt_interfaces::action::Relocalize_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::Relocalize_SendGoal_Request goal(::agt_interfaces::action::Relocalize_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_SendGoal_Request msg_;
};

class Init_Relocalize_SendGoal_Request_goal_id
{
public:
  Init_Relocalize_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Relocalize_SendGoal_Request_goal goal_id(::agt_interfaces::action::Relocalize_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Relocalize_SendGoal_Request_goal(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::Relocalize_SendGoal_Request>()
{
  return agt_interfaces::action::builder::Init_Relocalize_SendGoal_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_Relocalize_SendGoal_Response_stamp
{
public:
  explicit Init_Relocalize_SendGoal_Response_stamp(::agt_interfaces::action::Relocalize_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::Relocalize_SendGoal_Response stamp(::agt_interfaces::action::Relocalize_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_SendGoal_Response msg_;
};

class Init_Relocalize_SendGoal_Response_accepted
{
public:
  Init_Relocalize_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Relocalize_SendGoal_Response_stamp accepted(::agt_interfaces::action::Relocalize_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_Relocalize_SendGoal_Response_stamp(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::Relocalize_SendGoal_Response>()
{
  return agt_interfaces::action::builder::Init_Relocalize_SendGoal_Response_accepted();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_Relocalize_GetResult_Request_goal_id
{
public:
  Init_Relocalize_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::action::Relocalize_GetResult_Request goal_id(::agt_interfaces::action::Relocalize_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::Relocalize_GetResult_Request>()
{
  return agt_interfaces::action::builder::Init_Relocalize_GetResult_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_Relocalize_GetResult_Response_result
{
public:
  explicit Init_Relocalize_GetResult_Response_result(::agt_interfaces::action::Relocalize_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::Relocalize_GetResult_Response result(::agt_interfaces::action::Relocalize_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_GetResult_Response msg_;
};

class Init_Relocalize_GetResult_Response_status
{
public:
  Init_Relocalize_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Relocalize_GetResult_Response_result status(::agt_interfaces::action::Relocalize_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Relocalize_GetResult_Response_result(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::Relocalize_GetResult_Response>()
{
  return agt_interfaces::action::builder::Init_Relocalize_GetResult_Response_status();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_Relocalize_FeedbackMessage_feedback
{
public:
  explicit Init_Relocalize_FeedbackMessage_feedback(::agt_interfaces::action::Relocalize_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::Relocalize_FeedbackMessage feedback(::agt_interfaces::action::Relocalize_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_FeedbackMessage msg_;
};

class Init_Relocalize_FeedbackMessage_goal_id
{
public:
  Init_Relocalize_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Relocalize_FeedbackMessage_feedback goal_id(::agt_interfaces::action::Relocalize_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Relocalize_FeedbackMessage_feedback(msg_);
  }

private:
  ::agt_interfaces::action::Relocalize_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::Relocalize_FeedbackMessage>()
{
  return agt_interfaces::action::builder::Init_Relocalize_FeedbackMessage_goal_id();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__BUILDER_HPP_
