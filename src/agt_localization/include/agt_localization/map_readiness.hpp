#ifndef AGT_LOCALIZATION__MAP_READINESS_HPP_
#define AGT_LOCALIZATION__MAP_READINESS_HPP_

#include <filesystem>
#include <string>

namespace agt_localization
{

struct MapReadinessResult
{
  bool ready{false};
  bool record_hash_verified{false};
  std::string map_hash;
  std::string message;
};

// Returns the content identity used by localization candidates and last-pose records.
// The returned form is always "sha256:<64 lowercase hexadecimal characters>".
bool computeFileSha256(
  const std::filesystem::path & path,
  std::string * digest,
  std::string * error = nullptr);

MapReadinessResult validateMapProcessingRecord(
  const std::filesystem::path & record_path,
  const std::filesystem::path & pcd_path,
  const std::string & expected_map_id = "",
  const std::string & expected_map_hash = "");

}  // namespace agt_localization

#endif  // AGT_LOCALIZATION__MAP_READINESS_HPP_
