#ifndef AGT_LOCALIZATION__CANDIDATE_PROVIDER_HPP_
#define AGT_LOCALIZATION__CANDIDATE_PROVIDER_HPP_

#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace agt_localization
{

struct CandidateSeed
{
  std::string id;
  std::string source{"configured"};
  std::string map_id;
  std::string map_hash;
  double x{0.0};
  double y{0.0};
  double z{0.0};
  double yaw{0.0};
  double position_search_radius{0.0};
  double yaw_search_radius{0.0};
  double position_step{0.5};
  double yaw_step{0.17453292519943295};
  double covariance_score{0.0};
  int priority{0};
};

struct Candidate
{
  std::string id;
  std::string source;
  std::string map_id;
  std::string map_hash;
  std::size_t expansion_index{0};
  double x{0.0};
  double y{0.0};
  double z{0.0};
  double yaw{0.0};
  double distance_from_seed{0.0};
  double covariance_score{0.0};
  int priority{0};
};

struct CandidateExpansionConfig
{
  std::size_t max_candidates{128};
  std::size_t max_expanded_candidates{4096};
  double position_dedup_tolerance{1.0e-3};
  double yaw_dedup_tolerance{1.0e-3};
};

struct ConfiguredCandidateDocument
{
  int schema_version{1};
  std::string map_id;
  std::string map_hash;
  std::vector<CandidateSeed> seeds;
};

struct LastPoseRecord
{
  int schema_version{1};
  std::string map_id;
  std::string map_hash;
  double timestamp_sec{0.0};
  std::string frame_id{"map"};
  double x{0.0};
  double y{0.0};
  double z{0.0};
  double yaw{0.0};
  double fitness_score{0.0};
  double overlap_ratio{0.0};
  double inlier_ratio{0.0};
};

bool loadConfiguredCandidates(
  const std::filesystem::path & path,
  ConfiguredCandidateDocument * document,
  std::string * error);

std::vector<Candidate> expandCandidates(
  const ConfiguredCandidateDocument & document,
  const CandidateExpansionConfig & config,
  std::string * error);

bool saveLastPoseAtomic(
  const std::filesystem::path & path,
  const LastPoseRecord & record,
  std::string * error);

std::optional<LastPoseRecord> loadLastPose(
  const std::filesystem::path & path,
  const std::string & expected_map_id,
  const std::string & expected_map_hash,
  std::string * error);

}  // namespace agt_localization

#endif  // AGT_LOCALIZATION__CANDIDATE_PROVIDER_HPP_
