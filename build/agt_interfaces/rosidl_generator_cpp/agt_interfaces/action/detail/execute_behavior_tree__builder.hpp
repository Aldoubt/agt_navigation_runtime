// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:action/ExecuteBehaviorTree.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_BEHAVIOR_TREE__BUILDER_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_BEHAVIOR_TREE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteBehaviorTree_Goal_client_request_id
{
public:
  explicit Init_ExecuteBehaviorTree_Goal_client_request_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal client_request_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal::_client_request_id_type arg)
  {
    msg_.client_request_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal msg_;
};

class Init_ExecuteBehaviorTree_Goal_loop_count
{
public:
  explicit Init_ExecuteBehaviorTree_Goal_loop_count(::agt_interfaces::action::ExecuteBehaviorTree_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Goal_client_request_id loop_count(::agt_interfaces::action::ExecuteBehaviorTree_Goal::_loop_count_type arg)
  {
    msg_.loop_count = std::move(arg);
    return Init_ExecuteBehaviorTree_Goal_client_request_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal msg_;
};

class Init_ExecuteBehaviorTree_Goal_expected_content_sha256
{
public:
  explicit Init_ExecuteBehaviorTree_Goal_expected_content_sha256(::agt_interfaces::action::ExecuteBehaviorTree_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Goal_loop_count expected_content_sha256(::agt_interfaces::action::ExecuteBehaviorTree_Goal::_expected_content_sha256_type arg)
  {
    msg_.expected_content_sha256 = std::move(arg);
    return Init_ExecuteBehaviorTree_Goal_loop_count(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal msg_;
};

class Init_ExecuteBehaviorTree_Goal_task_revision
{
public:
  explicit Init_ExecuteBehaviorTree_Goal_task_revision(::agt_interfaces::action::ExecuteBehaviorTree_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Goal_expected_content_sha256 task_revision(::agt_interfaces::action::ExecuteBehaviorTree_Goal::_task_revision_type arg)
  {
    msg_.task_revision = std::move(arg);
    return Init_ExecuteBehaviorTree_Goal_expected_content_sha256(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal msg_;
};

class Init_ExecuteBehaviorTree_Goal_task_group_id
{
public:
  explicit Init_ExecuteBehaviorTree_Goal_task_group_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Goal_task_revision task_group_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal::_task_group_id_type arg)
  {
    msg_.task_group_id = std::move(arg);
    return Init_ExecuteBehaviorTree_Goal_task_revision(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal msg_;
};

class Init_ExecuteBehaviorTree_Goal_map_version_id
{
public:
  explicit Init_ExecuteBehaviorTree_Goal_map_version_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Goal_task_group_id map_version_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ExecuteBehaviorTree_Goal_task_group_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal msg_;
};

class Init_ExecuteBehaviorTree_Goal_map_id
{
public:
  explicit Init_ExecuteBehaviorTree_Goal_map_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Goal_map_version_id map_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ExecuteBehaviorTree_Goal_map_version_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal msg_;
};

class Init_ExecuteBehaviorTree_Goal_execution_id
{
public:
  explicit Init_ExecuteBehaviorTree_Goal_execution_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Goal_map_id execution_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal::_execution_id_type arg)
  {
    msg_.execution_id = std::move(arg);
    return Init_ExecuteBehaviorTree_Goal_map_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal msg_;
};

class Init_ExecuteBehaviorTree_Goal_tree_id
{
public:
  Init_ExecuteBehaviorTree_Goal_tree_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteBehaviorTree_Goal_execution_id tree_id(::agt_interfaces::action::ExecuteBehaviorTree_Goal::_tree_id_type arg)
  {
    msg_.tree_id = std::move(arg);
    return Init_ExecuteBehaviorTree_Goal_execution_id(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteBehaviorTree_Goal>()
{
  return agt_interfaces::action::builder::Init_ExecuteBehaviorTree_Goal_tree_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteBehaviorTree_Result_blocker_message
{
public:
  explicit Init_ExecuteBehaviorTree_Result_blocker_message(::agt_interfaces::action::ExecuteBehaviorTree_Result & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteBehaviorTree_Result blocker_message(::agt_interfaces::action::ExecuteBehaviorTree_Result::_blocker_message_type arg)
  {
    msg_.blocker_message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Result msg_;
};

class Init_ExecuteBehaviorTree_Result_blocker_code
{
public:
  explicit Init_ExecuteBehaviorTree_Result_blocker_code(::agt_interfaces::action::ExecuteBehaviorTree_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Result_blocker_message blocker_code(::agt_interfaces::action::ExecuteBehaviorTree_Result::_blocker_code_type arg)
  {
    msg_.blocker_code = std::move(arg);
    return Init_ExecuteBehaviorTree_Result_blocker_message(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Result msg_;
};

class Init_ExecuteBehaviorTree_Result_message
{
public:
  explicit Init_ExecuteBehaviorTree_Result_message(::agt_interfaces::action::ExecuteBehaviorTree_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Result_blocker_code message(::agt_interfaces::action::ExecuteBehaviorTree_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ExecuteBehaviorTree_Result_blocker_code(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Result msg_;
};

class Init_ExecuteBehaviorTree_Result_error_code
{
public:
  explicit Init_ExecuteBehaviorTree_Result_error_code(::agt_interfaces::action::ExecuteBehaviorTree_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Result_message error_code(::agt_interfaces::action::ExecuteBehaviorTree_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ExecuteBehaviorTree_Result_message(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Result msg_;
};

class Init_ExecuteBehaviorTree_Result_success
{
public:
  Init_ExecuteBehaviorTree_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteBehaviorTree_Result_error_code success(::agt_interfaces::action::ExecuteBehaviorTree_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ExecuteBehaviorTree_Result_error_code(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteBehaviorTree_Result>()
{
  return agt_interfaces::action::builder::Init_ExecuteBehaviorTree_Result_success();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteBehaviorTree_Feedback_total_waypoints
{
public:
  explicit Init_ExecuteBehaviorTree_Feedback_total_waypoints(::agt_interfaces::action::ExecuteBehaviorTree_Feedback & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteBehaviorTree_Feedback total_waypoints(::agt_interfaces::action::ExecuteBehaviorTree_Feedback::_total_waypoints_type arg)
  {
    msg_.total_waypoints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Feedback msg_;
};

class Init_ExecuteBehaviorTree_Feedback_current_waypoint
{
public:
  explicit Init_ExecuteBehaviorTree_Feedback_current_waypoint(::agt_interfaces::action::ExecuteBehaviorTree_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Feedback_total_waypoints current_waypoint(::agt_interfaces::action::ExecuteBehaviorTree_Feedback::_current_waypoint_type arg)
  {
    msg_.current_waypoint = std::move(arg);
    return Init_ExecuteBehaviorTree_Feedback_total_waypoints(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Feedback msg_;
};

class Init_ExecuteBehaviorTree_Feedback_loop_index
{
public:
  explicit Init_ExecuteBehaviorTree_Feedback_loop_index(::agt_interfaces::action::ExecuteBehaviorTree_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Feedback_current_waypoint loop_index(::agt_interfaces::action::ExecuteBehaviorTree_Feedback::_loop_index_type arg)
  {
    msg_.loop_index = std::move(arg);
    return Init_ExecuteBehaviorTree_Feedback_current_waypoint(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Feedback msg_;
};

class Init_ExecuteBehaviorTree_Feedback_active_node
{
public:
  explicit Init_ExecuteBehaviorTree_Feedback_active_node(::agt_interfaces::action::ExecuteBehaviorTree_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteBehaviorTree_Feedback_loop_index active_node(::agt_interfaces::action::ExecuteBehaviorTree_Feedback::_active_node_type arg)
  {
    msg_.active_node = std::move(arg);
    return Init_ExecuteBehaviorTree_Feedback_loop_index(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Feedback msg_;
};

class Init_ExecuteBehaviorTree_Feedback_tree_state
{
public:
  Init_ExecuteBehaviorTree_Feedback_tree_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteBehaviorTree_Feedback_active_node tree_state(::agt_interfaces::action::ExecuteBehaviorTree_Feedback::_tree_state_type arg)
  {
    msg_.tree_state = std::move(arg);
    return Init_ExecuteBehaviorTree_Feedback_active_node(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteBehaviorTree_Feedback>()
{
  return agt_interfaces::action::builder::Init_ExecuteBehaviorTree_Feedback_tree_state();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteBehaviorTree_SendGoal_Request_goal
{
public:
  explicit Init_ExecuteBehaviorTree_SendGoal_Request_goal(::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request goal(::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request msg_;
};

class Init_ExecuteBehaviorTree_SendGoal_Request_goal_id
{
public:
  Init_ExecuteBehaviorTree_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteBehaviorTree_SendGoal_Request_goal goal_id(::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteBehaviorTree_SendGoal_Request_goal(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request>()
{
  return agt_interfaces::action::builder::Init_ExecuteBehaviorTree_SendGoal_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteBehaviorTree_SendGoal_Response_stamp
{
public:
  explicit Init_ExecuteBehaviorTree_SendGoal_Response_stamp(::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response stamp(::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response msg_;
};

class Init_ExecuteBehaviorTree_SendGoal_Response_accepted
{
public:
  Init_ExecuteBehaviorTree_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteBehaviorTree_SendGoal_Response_stamp accepted(::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_ExecuteBehaviorTree_SendGoal_Response_stamp(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response>()
{
  return agt_interfaces::action::builder::Init_ExecuteBehaviorTree_SendGoal_Response_accepted();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteBehaviorTree_GetResult_Request_goal_id
{
public:
  Init_ExecuteBehaviorTree_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request goal_id(::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request>()
{
  return agt_interfaces::action::builder::Init_ExecuteBehaviorTree_GetResult_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteBehaviorTree_GetResult_Response_result
{
public:
  explicit Init_ExecuteBehaviorTree_GetResult_Response_result(::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response result(::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response msg_;
};

class Init_ExecuteBehaviorTree_GetResult_Response_status
{
public:
  Init_ExecuteBehaviorTree_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteBehaviorTree_GetResult_Response_result status(::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_ExecuteBehaviorTree_GetResult_Response_result(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response>()
{
  return agt_interfaces::action::builder::Init_ExecuteBehaviorTree_GetResult_Response_status();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_ExecuteBehaviorTree_FeedbackMessage_feedback
{
public:
  explicit Init_ExecuteBehaviorTree_FeedbackMessage_feedback(::agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage feedback(::agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage msg_;
};

class Init_ExecuteBehaviorTree_FeedbackMessage_goal_id
{
public:
  Init_ExecuteBehaviorTree_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteBehaviorTree_FeedbackMessage_feedback goal_id(::agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteBehaviorTree_FeedbackMessage_feedback(msg_);
  }

private:
  ::agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage>()
{
  return agt_interfaces::action::builder::Init_ExecuteBehaviorTree_FeedbackMessage_goal_id();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_BEHAVIOR_TREE__BUILDER_HPP_
