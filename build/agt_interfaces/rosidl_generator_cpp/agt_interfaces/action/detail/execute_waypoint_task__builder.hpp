// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:action/ExecuteWaypointTask.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_WAYPOINT_TASK__BUILDER_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_WAYPOINT_TASK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/action/detail/execute_waypoint_task__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteWaypointTask_Goal_loop
{
public:
  explicit Init_ExecuteWaypointTask_Goal_loop(::agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteWaypointTask_Goal loop(::agt_interfaces::action::ExecuteWaypointTask_Goal::_loop_type arg)
  {
    msg_.loop = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

class Init_ExecuteWaypointTask_Goal_poses
{
public:
  explicit Init_ExecuteWaypointTask_Goal_poses(::agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Goal_loop poses(::agt_interfaces::action::ExecuteWaypointTask_Goal::_poses_type arg)
  {
    msg_.poses = std::move(arg);
    return Init_ExecuteWaypointTask_Goal_loop(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

class Init_ExecuteWaypointTask_Goal_task_file
{
public:
  explicit Init_ExecuteWaypointTask_Goal_task_file(::agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Goal_poses task_file(::agt_interfaces::action::ExecuteWaypointTask_Goal::_task_file_type arg)
  {
    msg_.task_file = std::move(arg);
    return Init_ExecuteWaypointTask_Goal_poses(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

class Init_ExecuteWaypointTask_Goal_client_request_id
{
public:
  explicit Init_ExecuteWaypointTask_Goal_client_request_id(::agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Goal_task_file client_request_id(::agt_interfaces::action::ExecuteWaypointTask_Goal::_client_request_id_type arg)
  {
    msg_.client_request_id = std::move(arg);
    return Init_ExecuteWaypointTask_Goal_task_file(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

class Init_ExecuteWaypointTask_Goal_loop_count
{
public:
  explicit Init_ExecuteWaypointTask_Goal_loop_count(::agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Goal_client_request_id loop_count(::agt_interfaces::action::ExecuteWaypointTask_Goal::_loop_count_type arg)
  {
    msg_.loop_count = std::move(arg);
    return Init_ExecuteWaypointTask_Goal_client_request_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

class Init_ExecuteWaypointTask_Goal_expected_content_sha256
{
public:
  explicit Init_ExecuteWaypointTask_Goal_expected_content_sha256(::agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Goal_loop_count expected_content_sha256(::agt_interfaces::action::ExecuteWaypointTask_Goal::_expected_content_sha256_type arg)
  {
    msg_.expected_content_sha256 = std::move(arg);
    return Init_ExecuteWaypointTask_Goal_loop_count(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

class Init_ExecuteWaypointTask_Goal_task_revision
{
public:
  explicit Init_ExecuteWaypointTask_Goal_task_revision(::agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Goal_expected_content_sha256 task_revision(::agt_interfaces::action::ExecuteWaypointTask_Goal::_task_revision_type arg)
  {
    msg_.task_revision = std::move(arg);
    return Init_ExecuteWaypointTask_Goal_expected_content_sha256(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

class Init_ExecuteWaypointTask_Goal_task_group_id
{
public:
  explicit Init_ExecuteWaypointTask_Goal_task_group_id(::agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Goal_task_revision task_group_id(::agt_interfaces::action::ExecuteWaypointTask_Goal::_task_group_id_type arg)
  {
    msg_.task_group_id = std::move(arg);
    return Init_ExecuteWaypointTask_Goal_task_revision(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

class Init_ExecuteWaypointTask_Goal_map_version_id
{
public:
  explicit Init_ExecuteWaypointTask_Goal_map_version_id(::agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Goal_task_group_id map_version_id(::agt_interfaces::action::ExecuteWaypointTask_Goal::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ExecuteWaypointTask_Goal_task_group_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

class Init_ExecuteWaypointTask_Goal_map_id
{
public:
  Init_ExecuteWaypointTask_Goal_map_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteWaypointTask_Goal_map_version_id map_id(::agt_interfaces::action::ExecuteWaypointTask_Goal::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ExecuteWaypointTask_Goal_map_version_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteWaypointTask_Goal>()
{
  return agt_interfaces::action::builder::Init_ExecuteWaypointTask_Goal_map_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteWaypointTask_Result_final_status
{
public:
  explicit Init_ExecuteWaypointTask_Result_final_status(::agt_interfaces::action::ExecuteWaypointTask_Result & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteWaypointTask_Result final_status(::agt_interfaces::action::ExecuteWaypointTask_Result::_final_status_type arg)
  {
    msg_.final_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

class Init_ExecuteWaypointTask_Result_missed_waypoints
{
public:
  explicit Init_ExecuteWaypointTask_Result_missed_waypoints(::agt_interfaces::action::ExecuteWaypointTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Result_final_status missed_waypoints(::agt_interfaces::action::ExecuteWaypointTask_Result::_missed_waypoints_type arg)
  {
    msg_.missed_waypoints = std::move(arg);
    return Init_ExecuteWaypointTask_Result_final_status(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

class Init_ExecuteWaypointTask_Result_duplicate_request
{
public:
  explicit Init_ExecuteWaypointTask_Result_duplicate_request(::agt_interfaces::action::ExecuteWaypointTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Result_missed_waypoints duplicate_request(::agt_interfaces::action::ExecuteWaypointTask_Result::_duplicate_request_type arg)
  {
    msg_.duplicate_request = std::move(arg);
    return Init_ExecuteWaypointTask_Result_missed_waypoints(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

class Init_ExecuteWaypointTask_Result_technical_message
{
public:
  explicit Init_ExecuteWaypointTask_Result_technical_message(::agt_interfaces::action::ExecuteWaypointTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Result_duplicate_request technical_message(::agt_interfaces::action::ExecuteWaypointTask_Result::_technical_message_type arg)
  {
    msg_.technical_message = std::move(arg);
    return Init_ExecuteWaypointTask_Result_duplicate_request(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

class Init_ExecuteWaypointTask_Result_operator_message
{
public:
  explicit Init_ExecuteWaypointTask_Result_operator_message(::agt_interfaces::action::ExecuteWaypointTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Result_technical_message operator_message(::agt_interfaces::action::ExecuteWaypointTask_Result::_operator_message_type arg)
  {
    msg_.operator_message = std::move(arg);
    return Init_ExecuteWaypointTask_Result_technical_message(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

class Init_ExecuteWaypointTask_Result_blocker_code
{
public:
  explicit Init_ExecuteWaypointTask_Result_blocker_code(::agt_interfaces::action::ExecuteWaypointTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Result_operator_message blocker_code(::agt_interfaces::action::ExecuteWaypointTask_Result::_blocker_code_type arg)
  {
    msg_.blocker_code = std::move(arg);
    return Init_ExecuteWaypointTask_Result_operator_message(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

class Init_ExecuteWaypointTask_Result_session_id
{
public:
  explicit Init_ExecuteWaypointTask_Result_session_id(::agt_interfaces::action::ExecuteWaypointTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Result_blocker_code session_id(::agt_interfaces::action::ExecuteWaypointTask_Result::_session_id_type arg)
  {
    msg_.session_id = std::move(arg);
    return Init_ExecuteWaypointTask_Result_blocker_code(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

class Init_ExecuteWaypointTask_Result_message
{
public:
  explicit Init_ExecuteWaypointTask_Result_message(::agt_interfaces::action::ExecuteWaypointTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Result_session_id message(::agt_interfaces::action::ExecuteWaypointTask_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ExecuteWaypointTask_Result_session_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

class Init_ExecuteWaypointTask_Result_error_code
{
public:
  explicit Init_ExecuteWaypointTask_Result_error_code(::agt_interfaces::action::ExecuteWaypointTask_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Result_message error_code(::agt_interfaces::action::ExecuteWaypointTask_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ExecuteWaypointTask_Result_message(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

class Init_ExecuteWaypointTask_Result_success
{
public:
  Init_ExecuteWaypointTask_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteWaypointTask_Result_error_code success(::agt_interfaces::action::ExecuteWaypointTask_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ExecuteWaypointTask_Result_error_code(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteWaypointTask_Result>()
{
  return agt_interfaces::action::builder::Init_ExecuteWaypointTask_Result_success();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteWaypointTask_Feedback_status
{
public:
  explicit Init_ExecuteWaypointTask_Feedback_status(::agt_interfaces::action::ExecuteWaypointTask_Feedback & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteWaypointTask_Feedback status(::agt_interfaces::action::ExecuteWaypointTask_Feedback::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Feedback msg_;
};

class Init_ExecuteWaypointTask_Feedback_total_waypoints
{
public:
  explicit Init_ExecuteWaypointTask_Feedback_total_waypoints(::agt_interfaces::action::ExecuteWaypointTask_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Feedback_status total_waypoints(::agt_interfaces::action::ExecuteWaypointTask_Feedback::_total_waypoints_type arg)
  {
    msg_.total_waypoints = std::move(arg);
    return Init_ExecuteWaypointTask_Feedback_status(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Feedback msg_;
};

class Init_ExecuteWaypointTask_Feedback_current_waypoint
{
public:
  explicit Init_ExecuteWaypointTask_Feedback_current_waypoint(::agt_interfaces::action::ExecuteWaypointTask_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Feedback_total_waypoints current_waypoint(::agt_interfaces::action::ExecuteWaypointTask_Feedback::_current_waypoint_type arg)
  {
    msg_.current_waypoint = std::move(arg);
    return Init_ExecuteWaypointTask_Feedback_total_waypoints(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Feedback msg_;
};

class Init_ExecuteWaypointTask_Feedback_loop_index
{
public:
  explicit Init_ExecuteWaypointTask_Feedback_loop_index(::agt_interfaces::action::ExecuteWaypointTask_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteWaypointTask_Feedback_current_waypoint loop_index(::agt_interfaces::action::ExecuteWaypointTask_Feedback::_loop_index_type arg)
  {
    msg_.loop_index = std::move(arg);
    return Init_ExecuteWaypointTask_Feedback_current_waypoint(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Feedback msg_;
};

class Init_ExecuteWaypointTask_Feedback_state
{
public:
  Init_ExecuteWaypointTask_Feedback_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteWaypointTask_Feedback_loop_index state(::agt_interfaces::action::ExecuteWaypointTask_Feedback::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ExecuteWaypointTask_Feedback_loop_index(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteWaypointTask_Feedback>()
{
  return agt_interfaces::action::builder::Init_ExecuteWaypointTask_Feedback_state();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteWaypointTask_SendGoal_Request_goal
{
public:
  explicit Init_ExecuteWaypointTask_SendGoal_Request_goal(::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request goal(::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request msg_;
};

class Init_ExecuteWaypointTask_SendGoal_Request_goal_id
{
public:
  Init_ExecuteWaypointTask_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteWaypointTask_SendGoal_Request_goal goal_id(::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteWaypointTask_SendGoal_Request_goal(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request>()
{
  return agt_interfaces::action::builder::Init_ExecuteWaypointTask_SendGoal_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteWaypointTask_SendGoal_Response_stamp
{
public:
  explicit Init_ExecuteWaypointTask_SendGoal_Response_stamp(::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response stamp(::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response msg_;
};

class Init_ExecuteWaypointTask_SendGoal_Response_accepted
{
public:
  Init_ExecuteWaypointTask_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteWaypointTask_SendGoal_Response_stamp accepted(::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_ExecuteWaypointTask_SendGoal_Response_stamp(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response>()
{
  return agt_interfaces::action::builder::Init_ExecuteWaypointTask_SendGoal_Response_accepted();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteWaypointTask_GetResult_Request_goal_id
{
public:
  Init_ExecuteWaypointTask_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::action::ExecuteWaypointTask_GetResult_Request goal_id(::agt_interfaces::action::ExecuteWaypointTask_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteWaypointTask_GetResult_Request>()
{
  return agt_interfaces::action::builder::Init_ExecuteWaypointTask_GetResult_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteWaypointTask_GetResult_Response_result
{
public:
  explicit Init_ExecuteWaypointTask_GetResult_Response_result(::agt_interfaces::action::ExecuteWaypointTask_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteWaypointTask_GetResult_Response result(::agt_interfaces::action::ExecuteWaypointTask_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_GetResult_Response msg_;
};

class Init_ExecuteWaypointTask_GetResult_Response_status
{
public:
  Init_ExecuteWaypointTask_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteWaypointTask_GetResult_Response_result status(::agt_interfaces::action::ExecuteWaypointTask_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_ExecuteWaypointTask_GetResult_Response_result(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteWaypointTask_GetResult_Response>()
{
  return agt_interfaces::action::builder::Init_ExecuteWaypointTask_GetResult_Response_status();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteWaypointTask_FeedbackMessage_feedback
{
public:
  explicit Init_ExecuteWaypointTask_FeedbackMessage_feedback(::agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage feedback(::agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage msg_;
};

class Init_ExecuteWaypointTask_FeedbackMessage_goal_id
{
public:
  Init_ExecuteWaypointTask_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteWaypointTask_FeedbackMessage_feedback goal_id(::agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteWaypointTask_FeedbackMessage_feedback(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage>()
{
  return agt_interfaces::action::builder::Init_ExecuteWaypointTask_FeedbackMessage_goal_id();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_WAYPOINT_TASK__BUILDER_HPP_
