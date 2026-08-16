// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:action/ExecuteCoverageTask.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__BUILDER_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/action/detail/execute_coverage_task__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteCoverageTask_Goal_allow_repair
{
public:
  explicit Init_ExecuteCoverageTask_Goal_allow_repair(::agt_interfaces::action::ExecuteCoverageTask_Goal & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteCoverageTask_Goal allow_repair(::agt_interfaces::action::ExecuteCoverageTask_Goal::_allow_repair_type arg)
  {
    msg_.allow_repair = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Goal msg_;
};

class Init_ExecuteCoverageTask_Goal_controller_id
{
public:
  explicit Init_ExecuteCoverageTask_Goal_controller_id(::agt_interfaces::action::ExecuteCoverageTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Goal_allow_repair controller_id(::agt_interfaces::action::ExecuteCoverageTask_Goal::_controller_id_type arg)
  {
    msg_.controller_id = std::move(arg);
    return Init_ExecuteCoverageTask_Goal_allow_repair(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Goal msg_;
};

class Init_ExecuteCoverageTask_Goal_planning_mode
{
public:
  explicit Init_ExecuteCoverageTask_Goal_planning_mode(::agt_interfaces::action::ExecuteCoverageTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Goal_controller_id planning_mode(::agt_interfaces::action::ExecuteCoverageTask_Goal::_planning_mode_type arg)
  {
    msg_.planning_mode = std::move(arg);
    return Init_ExecuteCoverageTask_Goal_controller_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Goal msg_;
};

class Init_ExecuteCoverageTask_Goal_field_id
{
public:
  explicit Init_ExecuteCoverageTask_Goal_field_id(::agt_interfaces::action::ExecuteCoverageTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Goal_planning_mode field_id(::agt_interfaces::action::ExecuteCoverageTask_Goal::_field_id_type arg)
  {
    msg_.field_id = std::move(arg);
    return Init_ExecuteCoverageTask_Goal_planning_mode(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Goal msg_;
};

class Init_ExecuteCoverageTask_Goal_semantic_map_uri
{
public:
  Init_ExecuteCoverageTask_Goal_semantic_map_uri()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteCoverageTask_Goal_field_id semantic_map_uri(::agt_interfaces::action::ExecuteCoverageTask_Goal::_semantic_map_uri_type arg)
  {
    msg_.semantic_map_uri = std::move(arg);
    return Init_ExecuteCoverageTask_Goal_field_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteCoverageTask_Goal>()
{
  return agt_interfaces::action::builder::Init_ExecuteCoverageTask_Goal_semantic_map_uri();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteCoverageTask_Result_repaired_segment_count
{
public:
  explicit Init_ExecuteCoverageTask_Result_repaired_segment_count(::agt_interfaces::action::ExecuteCoverageTask_Result & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteCoverageTask_Result repaired_segment_count(::agt_interfaces::action::ExecuteCoverageTask_Result::_repaired_segment_count_type arg)
  {
    msg_.repaired_segment_count = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Result msg_;
};

class Init_ExecuteCoverageTask_Result_executed_length
{
public:
  explicit Init_ExecuteCoverageTask_Result_executed_length(::agt_interfaces::action::ExecuteCoverageTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Result_repaired_segment_count executed_length(::agt_interfaces::action::ExecuteCoverageTask_Result::_executed_length_type arg)
  {
    msg_.executed_length = std::move(arg);
    return Init_ExecuteCoverageTask_Result_repaired_segment_count(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Result msg_;
};

class Init_ExecuteCoverageTask_Result_overlap_rate
{
public:
  explicit Init_ExecuteCoverageTask_Result_overlap_rate(::agt_interfaces::action::ExecuteCoverageTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Result_executed_length overlap_rate(::agt_interfaces::action::ExecuteCoverageTask_Result::_overlap_rate_type arg)
  {
    msg_.overlap_rate = std::move(arg);
    return Init_ExecuteCoverageTask_Result_executed_length(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Result msg_;
};

class Init_ExecuteCoverageTask_Result_coverage_rate
{
public:
  explicit Init_ExecuteCoverageTask_Result_coverage_rate(::agt_interfaces::action::ExecuteCoverageTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Result_overlap_rate coverage_rate(::agt_interfaces::action::ExecuteCoverageTask_Result::_coverage_rate_type arg)
  {
    msg_.coverage_rate = std::move(arg);
    return Init_ExecuteCoverageTask_Result_overlap_rate(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Result msg_;
};

class Init_ExecuteCoverageTask_Result_message
{
public:
  explicit Init_ExecuteCoverageTask_Result_message(::agt_interfaces::action::ExecuteCoverageTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Result_coverage_rate message(::agt_interfaces::action::ExecuteCoverageTask_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ExecuteCoverageTask_Result_coverage_rate(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Result msg_;
};

class Init_ExecuteCoverageTask_Result_error_code
{
public:
  explicit Init_ExecuteCoverageTask_Result_error_code(::agt_interfaces::action::ExecuteCoverageTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Result_message error_code(::agt_interfaces::action::ExecuteCoverageTask_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ExecuteCoverageTask_Result_message(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Result msg_;
};

class Init_ExecuteCoverageTask_Result_success
{
public:
  Init_ExecuteCoverageTask_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteCoverageTask_Result_error_code success(::agt_interfaces::action::ExecuteCoverageTask_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ExecuteCoverageTask_Result_error_code(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteCoverageTask_Result>()
{
  return agt_interfaces::action::builder::Init_ExecuteCoverageTask_Result_success();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteCoverageTask_Feedback_distance_remaining
{
public:
  explicit Init_ExecuteCoverageTask_Feedback_distance_remaining(::agt_interfaces::action::ExecuteCoverageTask_Feedback & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteCoverageTask_Feedback distance_remaining(::agt_interfaces::action::ExecuteCoverageTask_Feedback::_distance_remaining_type arg)
  {
    msg_.distance_remaining = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Feedback msg_;
};

class Init_ExecuteCoverageTask_Feedback_total_swaths
{
public:
  explicit Init_ExecuteCoverageTask_Feedback_total_swaths(::agt_interfaces::action::ExecuteCoverageTask_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Feedback_distance_remaining total_swaths(::agt_interfaces::action::ExecuteCoverageTask_Feedback::_total_swaths_type arg)
  {
    msg_.total_swaths = std::move(arg);
    return Init_ExecuteCoverageTask_Feedback_distance_remaining(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Feedback msg_;
};

class Init_ExecuteCoverageTask_Feedback_current_swath_index
{
public:
  explicit Init_ExecuteCoverageTask_Feedback_current_swath_index(::agt_interfaces::action::ExecuteCoverageTask_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteCoverageTask_Feedback_total_swaths current_swath_index(::agt_interfaces::action::ExecuteCoverageTask_Feedback::_current_swath_index_type arg)
  {
    msg_.current_swath_index = std::move(arg);
    return Init_ExecuteCoverageTask_Feedback_total_swaths(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Feedback msg_;
};

class Init_ExecuteCoverageTask_Feedback_current_stage
{
public:
  Init_ExecuteCoverageTask_Feedback_current_stage()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteCoverageTask_Feedback_current_swath_index current_stage(::agt_interfaces::action::ExecuteCoverageTask_Feedback::_current_stage_type arg)
  {
    msg_.current_stage = std::move(arg);
    return Init_ExecuteCoverageTask_Feedback_current_swath_index(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteCoverageTask_Feedback>()
{
  return agt_interfaces::action::builder::Init_ExecuteCoverageTask_Feedback_current_stage();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteCoverageTask_SendGoal_Request_goal
{
public:
  explicit Init_ExecuteCoverageTask_SendGoal_Request_goal(::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request goal(::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request msg_;
};

class Init_ExecuteCoverageTask_SendGoal_Request_goal_id
{
public:
  Init_ExecuteCoverageTask_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteCoverageTask_SendGoal_Request_goal goal_id(::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteCoverageTask_SendGoal_Request_goal(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request>()
{
  return agt_interfaces::action::builder::Init_ExecuteCoverageTask_SendGoal_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteCoverageTask_SendGoal_Response_stamp
{
public:
  explicit Init_ExecuteCoverageTask_SendGoal_Response_stamp(::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response stamp(::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response msg_;
};

class Init_ExecuteCoverageTask_SendGoal_Response_accepted
{
public:
  Init_ExecuteCoverageTask_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteCoverageTask_SendGoal_Response_stamp accepted(::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_ExecuteCoverageTask_SendGoal_Response_stamp(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response>()
{
  return agt_interfaces::action::builder::Init_ExecuteCoverageTask_SendGoal_Response_accepted();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteCoverageTask_GetResult_Request_goal_id
{
public:
  Init_ExecuteCoverageTask_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::action::ExecuteCoverageTask_GetResult_Request goal_id(::agt_interfaces::action::ExecuteCoverageTask_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteCoverageTask_GetResult_Request>()
{
  return agt_interfaces::action::builder::Init_ExecuteCoverageTask_GetResult_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteCoverageTask_GetResult_Response_result
{
public:
  explicit Init_ExecuteCoverageTask_GetResult_Response_result(::agt_interfaces::action::ExecuteCoverageTask_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteCoverageTask_GetResult_Response result(::agt_interfaces::action::ExecuteCoverageTask_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_GetResult_Response msg_;
};

class Init_ExecuteCoverageTask_GetResult_Response_status
{
public:
  Init_ExecuteCoverageTask_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteCoverageTask_GetResult_Response_result status(::agt_interfaces::action::ExecuteCoverageTask_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_ExecuteCoverageTask_GetResult_Response_result(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteCoverageTask_GetResult_Response>()
{
  return agt_interfaces::action::builder::Init_ExecuteCoverageTask_GetResult_Response_status();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteCoverageTask_FeedbackMessage_feedback
{
public:
  explicit Init_ExecuteCoverageTask_FeedbackMessage_feedback(::agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage feedback(::agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage msg_;
};

class Init_ExecuteCoverageTask_FeedbackMessage_goal_id
{
public:
  Init_ExecuteCoverageTask_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteCoverageTask_FeedbackMessage_feedback goal_id(::agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteCoverageTask_FeedbackMessage_feedback(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage>()
{
  return agt_interfaces::action::builder::Init_ExecuteCoverageTask_FeedbackMessage_goal_id();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__BUILDER_HPP_
