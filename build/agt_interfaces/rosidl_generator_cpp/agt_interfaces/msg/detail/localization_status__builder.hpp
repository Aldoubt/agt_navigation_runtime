// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/LocalizationStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/localization_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_LocalizationStatus_message
{
public:
  explicit Init_LocalizationStatus_message(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::LocalizationStatus message(::agt_interfaces::msg::LocalizationStatus::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_consecutive_failures
{
public:
  explicit Init_LocalizationStatus_consecutive_failures(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_message consecutive_failures(::agt_interfaces::msg::LocalizationStatus::_consecutive_failures_type arg)
  {
    msg_.consecutive_failures = std::move(arg);
    return Init_LocalizationStatus_message(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_consecutive_successes
{
public:
  explicit Init_LocalizationStatus_consecutive_successes(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_consecutive_failures consecutive_successes(::agt_interfaces::msg::LocalizationStatus::_consecutive_successes_type arg)
  {
    msg_.consecutive_successes = std::move(arg);
    return Init_LocalizationStatus_consecutive_failures(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_total_candidates
{
public:
  explicit Init_LocalizationStatus_total_candidates(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_consecutive_successes total_candidates(::agt_interfaces::msg::LocalizationStatus::_total_candidates_type arg)
  {
    msg_.total_candidates = std::move(arg);
    return Init_LocalizationStatus_consecutive_successes(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_tested_candidates
{
public:
  explicit Init_LocalizationStatus_tested_candidates(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_total_candidates tested_candidates(::agt_interfaces::msg::LocalizationStatus::_tested_candidates_type arg)
  {
    msg_.tested_candidates = std::move(arg);
    return Init_LocalizationStatus_total_candidates(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_runtime_ms
{
public:
  explicit Init_LocalizationStatus_runtime_ms(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_tested_candidates runtime_ms(::agt_interfaces::msg::LocalizationStatus::_runtime_ms_type arg)
  {
    msg_.runtime_ms = std::move(arg);
    return Init_LocalizationStatus_tested_candidates(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_yaw_innovation
{
public:
  explicit Init_LocalizationStatus_yaw_innovation(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_runtime_ms yaw_innovation(::agt_interfaces::msg::LocalizationStatus::_yaw_innovation_type arg)
  {
    msg_.yaw_innovation = std::move(arg);
    return Init_LocalizationStatus_runtime_ms(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_translation_innovation
{
public:
  explicit Init_LocalizationStatus_translation_innovation(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_yaw_innovation translation_innovation(::agt_interfaces::msg::LocalizationStatus::_translation_innovation_type arg)
  {
    msg_.translation_innovation = std::move(arg);
    return Init_LocalizationStatus_yaw_innovation(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_ambiguity_score
{
public:
  explicit Init_LocalizationStatus_ambiguity_score(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_translation_innovation ambiguity_score(::agt_interfaces::msg::LocalizationStatus::_ambiguity_score_type arg)
  {
    msg_.ambiguity_score = std::move(arg);
    return Init_LocalizationStatus_translation_innovation(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_inlier_ratio
{
public:
  explicit Init_LocalizationStatus_inlier_ratio(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_ambiguity_score inlier_ratio(::agt_interfaces::msg::LocalizationStatus::_inlier_ratio_type arg)
  {
    msg_.inlier_ratio = std::move(arg);
    return Init_LocalizationStatus_ambiguity_score(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_overlap_ratio
{
public:
  explicit Init_LocalizationStatus_overlap_ratio(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_inlier_ratio overlap_ratio(::agt_interfaces::msg::LocalizationStatus::_overlap_ratio_type arg)
  {
    msg_.overlap_ratio = std::move(arg);
    return Init_LocalizationStatus_inlier_ratio(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_fitness_score
{
public:
  explicit Init_LocalizationStatus_fitness_score(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_overlap_ratio fitness_score(::agt_interfaces::msg::LocalizationStatus::_fitness_score_type arg)
  {
    msg_.fitness_score = std::move(arg);
    return Init_LocalizationStatus_overlap_ratio(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_global_pose
{
public:
  explicit Init_LocalizationStatus_global_pose(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_fitness_score global_pose(::agt_interfaces::msg::LocalizationStatus::_global_pose_type arg)
  {
    msg_.global_pose = std::move(arg);
    return Init_LocalizationStatus_fitness_score(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_correction_generation
{
public:
  explicit Init_LocalizationStatus_correction_generation(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_global_pose correction_generation(::agt_interfaces::msg::LocalizationStatus::_correction_generation_type arg)
  {
    msg_.correction_generation = std::move(arg);
    return Init_LocalizationStatus_global_pose(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_map_hash
{
public:
  explicit Init_LocalizationStatus_map_hash(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_correction_generation map_hash(::agt_interfaces::msg::LocalizationStatus::_map_hash_type arg)
  {
    msg_.map_hash = std::move(arg);
    return Init_LocalizationStatus_correction_generation(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_map_id
{
public:
  explicit Init_LocalizationStatus_map_id(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_map_hash map_id(::agt_interfaces::msg::LocalizationStatus::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_LocalizationStatus_map_hash(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_candidate_id
{
public:
  explicit Init_LocalizationStatus_candidate_id(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_map_id candidate_id(::agt_interfaces::msg::LocalizationStatus::_candidate_id_type arg)
  {
    msg_.candidate_id = std::move(arg);
    return Init_LocalizationStatus_map_id(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_candidate_source
{
public:
  explicit Init_LocalizationStatus_candidate_source(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_candidate_id candidate_source(::agt_interfaces::msg::LocalizationStatus::_candidate_source_type arg)
  {
    msg_.candidate_source = std::move(arg);
    return Init_LocalizationStatus_candidate_id(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_backend
{
public:
  explicit Init_LocalizationStatus_backend(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_candidate_source backend(::agt_interfaces::msg::LocalizationStatus::_backend_type arg)
  {
    msg_.backend = std::move(arg);
    return Init_LocalizationStatus_candidate_source(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_error_code
{
public:
  explicit Init_LocalizationStatus_error_code(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_backend error_code(::agt_interfaces::msg::LocalizationStatus::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_LocalizationStatus_backend(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_status_stale
{
public:
  explicit Init_LocalizationStatus_status_stale(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_error_code status_stale(::agt_interfaces::msg::LocalizationStatus::_status_stale_type arg)
  {
    msg_.status_stale = std::move(arg);
    return Init_LocalizationStatus_error_code(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_ambiguous_result
{
public:
  explicit Init_LocalizationStatus_ambiguous_result(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_status_stale ambiguous_result(::agt_interfaces::msg::LocalizationStatus::_ambiguous_result_type arg)
  {
    msg_.ambiguous_result = std::move(arg);
    return Init_LocalizationStatus_status_stale(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_has_converged
{
public:
  explicit Init_LocalizationStatus_has_converged(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_ambiguous_result has_converged(::agt_interfaces::msg::LocalizationStatus::_has_converged_type arg)
  {
    msg_.has_converged = std::move(arg);
    return Init_LocalizationStatus_ambiguous_result(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_localization_accepted
{
public:
  explicit Init_LocalizationStatus_localization_accepted(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_has_converged localization_accepted(::agt_interfaces::msg::LocalizationStatus::_localization_accepted_type arg)
  {
    msg_.localization_accepted = std::move(arg);
    return Init_LocalizationStatus_has_converged(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_pose_valid
{
public:
  explicit Init_LocalizationStatus_pose_valid(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_localization_accepted pose_valid(::agt_interfaces::msg::LocalizationStatus::_pose_valid_type arg)
  {
    msg_.pose_valid = std::move(arg);
    return Init_LocalizationStatus_localization_accepted(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_state
{
public:
  explicit Init_LocalizationStatus_state(::agt_interfaces::msg::LocalizationStatus & msg)
  : msg_(msg)
  {}
  Init_LocalizationStatus_pose_valid state(::agt_interfaces::msg::LocalizationStatus::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_LocalizationStatus_pose_valid(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

class Init_LocalizationStatus_header
{
public:
  Init_LocalizationStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocalizationStatus_state header(::agt_interfaces::msg::LocalizationStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LocalizationStatus_state(msg_);
  }

private:
  ::agt_interfaces::msg::LocalizationStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::LocalizationStatus>()
{
  return agt_interfaces::msg::builder::Init_LocalizationStatus_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__BUILDER_HPP_
