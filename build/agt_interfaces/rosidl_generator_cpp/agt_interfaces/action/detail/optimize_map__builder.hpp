// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:action/OptimizeMap.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__BUILDER_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/action/detail/optimize_map__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_OptimizeMap_Goal_activate_on_success
{
public:
  explicit Init_OptimizeMap_Goal_activate_on_success(::agt_interfaces::action::OptimizeMap_Goal & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::OptimizeMap_Goal activate_on_success(::agt_interfaces::action::OptimizeMap_Goal::_activate_on_success_type arg)
  {
    msg_.activate_on_success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Goal msg_;
};

class Init_OptimizeMap_Goal_options_yaml
{
public:
  explicit Init_OptimizeMap_Goal_options_yaml(::agt_interfaces::action::OptimizeMap_Goal & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Goal_activate_on_success options_yaml(::agt_interfaces::action::OptimizeMap_Goal::_options_yaml_type arg)
  {
    msg_.options_yaml = std::move(arg);
    return Init_OptimizeMap_Goal_activate_on_success(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Goal msg_;
};

class Init_OptimizeMap_Goal_backend
{
public:
  explicit Init_OptimizeMap_Goal_backend(::agt_interfaces::action::OptimizeMap_Goal & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Goal_options_yaml backend(::agt_interfaces::action::OptimizeMap_Goal::_backend_type arg)
  {
    msg_.backend = std::move(arg);
    return Init_OptimizeMap_Goal_options_yaml(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Goal msg_;
};

class Init_OptimizeMap_Goal_source_experiment_ids
{
public:
  explicit Init_OptimizeMap_Goal_source_experiment_ids(::agt_interfaces::action::OptimizeMap_Goal & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Goal_backend source_experiment_ids(::agt_interfaces::action::OptimizeMap_Goal::_source_experiment_ids_type arg)
  {
    msg_.source_experiment_ids = std::move(arg);
    return Init_OptimizeMap_Goal_backend(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Goal msg_;
};

class Init_OptimizeMap_Goal_source_map_version_id
{
public:
  explicit Init_OptimizeMap_Goal_source_map_version_id(::agt_interfaces::action::OptimizeMap_Goal & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Goal_source_experiment_ids source_map_version_id(::agt_interfaces::action::OptimizeMap_Goal::_source_map_version_id_type arg)
  {
    msg_.source_map_version_id = std::move(arg);
    return Init_OptimizeMap_Goal_source_experiment_ids(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Goal msg_;
};

class Init_OptimizeMap_Goal_source_map_id
{
public:
  Init_OptimizeMap_Goal_source_map_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OptimizeMap_Goal_source_map_version_id source_map_id(::agt_interfaces::action::OptimizeMap_Goal::_source_map_id_type arg)
  {
    msg_.source_map_id = std::move(arg);
    return Init_OptimizeMap_Goal_source_map_version_id(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::OptimizeMap_Goal>()
{
  return agt_interfaces::action::builder::Init_OptimizeMap_Goal_source_map_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_OptimizeMap_Result_message
{
public:
  explicit Init_OptimizeMap_Result_message(::agt_interfaces::action::OptimizeMap_Result & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::OptimizeMap_Result message(::agt_interfaces::action::OptimizeMap_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Result msg_;
};

class Init_OptimizeMap_Result_report_path
{
public:
  explicit Init_OptimizeMap_Result_report_path(::agt_interfaces::action::OptimizeMap_Result & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Result_message report_path(::agt_interfaces::action::OptimizeMap_Result::_report_path_type arg)
  {
    msg_.report_path = std::move(arg);
    return Init_OptimizeMap_Result_message(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Result msg_;
};

class Init_OptimizeMap_Result_optimized_pcd_path
{
public:
  explicit Init_OptimizeMap_Result_optimized_pcd_path(::agt_interfaces::action::OptimizeMap_Result & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Result_report_path optimized_pcd_path(::agt_interfaces::action::OptimizeMap_Result::_optimized_pcd_path_type arg)
  {
    msg_.optimized_pcd_path = std::move(arg);
    return Init_OptimizeMap_Result_report_path(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Result msg_;
};

class Init_OptimizeMap_Result_trajectory_path
{
public:
  explicit Init_OptimizeMap_Result_trajectory_path(::agt_interfaces::action::OptimizeMap_Result & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Result_optimized_pcd_path trajectory_path(::agt_interfaces::action::OptimizeMap_Result::_trajectory_path_type arg)
  {
    msg_.trajectory_path = std::move(arg);
    return Init_OptimizeMap_Result_optimized_pcd_path(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Result msg_;
};

class Init_OptimizeMap_Result_new_map_version_id
{
public:
  explicit Init_OptimizeMap_Result_new_map_version_id(::agt_interfaces::action::OptimizeMap_Result & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Result_trajectory_path new_map_version_id(::agt_interfaces::action::OptimizeMap_Result::_new_map_version_id_type arg)
  {
    msg_.new_map_version_id = std::move(arg);
    return Init_OptimizeMap_Result_trajectory_path(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Result msg_;
};

class Init_OptimizeMap_Result_error_code
{
public:
  explicit Init_OptimizeMap_Result_error_code(::agt_interfaces::action::OptimizeMap_Result & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Result_new_map_version_id error_code(::agt_interfaces::action::OptimizeMap_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_OptimizeMap_Result_new_map_version_id(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Result msg_;
};

class Init_OptimizeMap_Result_success
{
public:
  Init_OptimizeMap_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OptimizeMap_Result_error_code success(::agt_interfaces::action::OptimizeMap_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_OptimizeMap_Result_error_code(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::OptimizeMap_Result>()
{
  return agt_interfaces::action::builder::Init_OptimizeMap_Result_success();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_OptimizeMap_Feedback_message
{
public:
  explicit Init_OptimizeMap_Feedback_message(::agt_interfaces::action::OptimizeMap_Feedback & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::OptimizeMap_Feedback message(::agt_interfaces::action::OptimizeMap_Feedback::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Feedback msg_;
};

class Init_OptimizeMap_Feedback_progress
{
public:
  explicit Init_OptimizeMap_Feedback_progress(::agt_interfaces::action::OptimizeMap_Feedback & msg)
  : msg_(msg)
  {}
  Init_OptimizeMap_Feedback_message progress(::agt_interfaces::action::OptimizeMap_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_OptimizeMap_Feedback_message(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Feedback msg_;
};

class Init_OptimizeMap_Feedback_stage
{
public:
  Init_OptimizeMap_Feedback_stage()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OptimizeMap_Feedback_progress stage(::agt_interfaces::action::OptimizeMap_Feedback::_stage_type arg)
  {
    msg_.stage = std::move(arg);
    return Init_OptimizeMap_Feedback_progress(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::OptimizeMap_Feedback>()
{
  return agt_interfaces::action::builder::Init_OptimizeMap_Feedback_stage();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_OptimizeMap_SendGoal_Request_goal
{
public:
  explicit Init_OptimizeMap_SendGoal_Request_goal(::agt_interfaces::action::OptimizeMap_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::OptimizeMap_SendGoal_Request goal(::agt_interfaces::action::OptimizeMap_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_SendGoal_Request msg_;
};

class Init_OptimizeMap_SendGoal_Request_goal_id
{
public:
  Init_OptimizeMap_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OptimizeMap_SendGoal_Request_goal goal_id(::agt_interfaces::action::OptimizeMap_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_OptimizeMap_SendGoal_Request_goal(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::OptimizeMap_SendGoal_Request>()
{
  return agt_interfaces::action::builder::Init_OptimizeMap_SendGoal_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_OptimizeMap_SendGoal_Response_stamp
{
public:
  explicit Init_OptimizeMap_SendGoal_Response_stamp(::agt_interfaces::action::OptimizeMap_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::OptimizeMap_SendGoal_Response stamp(::agt_interfaces::action::OptimizeMap_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_SendGoal_Response msg_;
};

class Init_OptimizeMap_SendGoal_Response_accepted
{
public:
  Init_OptimizeMap_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OptimizeMap_SendGoal_Response_stamp accepted(::agt_interfaces::action::OptimizeMap_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_OptimizeMap_SendGoal_Response_stamp(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::OptimizeMap_SendGoal_Response>()
{
  return agt_interfaces::action::builder::Init_OptimizeMap_SendGoal_Response_accepted();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_OptimizeMap_GetResult_Request_goal_id
{
public:
  Init_OptimizeMap_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::agt_interfaces::action::OptimizeMap_GetResult_Request goal_id(::agt_interfaces::action::OptimizeMap_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::OptimizeMap_GetResult_Request>()
{
  return agt_interfaces::action::builder::Init_OptimizeMap_GetResult_Request_goal_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_OptimizeMap_GetResult_Response_result
{
public:
  explicit Init_OptimizeMap_GetResult_Response_result(::agt_interfaces::action::OptimizeMap_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::OptimizeMap_GetResult_Response result(::agt_interfaces::action::OptimizeMap_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_GetResult_Response msg_;
};

class Init_OptimizeMap_GetResult_Response_status
{
public:
  Init_OptimizeMap_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OptimizeMap_GetResult_Response_result status(::agt_interfaces::action::OptimizeMap_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_OptimizeMap_GetResult_Response_result(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::OptimizeMap_GetResult_Response>()
{
  return agt_interfaces::action::builder::Init_OptimizeMap_GetResult_Response_status();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace action
{

namespace builder
{

class Init_OptimizeMap_FeedbackMessage_feedback
{
public:
  explicit Init_OptimizeMap_FeedbackMessage_feedback(::agt_interfaces::action::OptimizeMap_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::action::OptimizeMap_FeedbackMessage feedback(::agt_interfaces::action::OptimizeMap_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_FeedbackMessage msg_;
};

class Init_OptimizeMap_FeedbackMessage_goal_id
{
public:
  Init_OptimizeMap_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OptimizeMap_FeedbackMessage_feedback goal_id(::agt_interfaces::action::OptimizeMap_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_OptimizeMap_FeedbackMessage_feedback(msg_);
  }

private:
  ::agt_interfaces::action::OptimizeMap_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::action::OptimizeMap_FeedbackMessage>()
{
  return agt_interfaces::action::builder::Init_OptimizeMap_FeedbackMessage_goal_id();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__BUILDER_HPP_
