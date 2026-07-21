#include "agt_localization/candidate_provider.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <limits>
#include <string>
#include <utility>

#include <yaml-cpp/yaml.h>

namespace agt_localization
{
namespace
{

constexpr int kSchemaVersion = 1;
constexpr double kTwoPi = 6.28318530717958647692;

void setError(std::string * error, const std::string & message)
{
  if (error != nullptr) {
    *error = message;
  }
}

bool finite(double value)
{
  return std::isfinite(value);
}

bool finiteSeed(const CandidateSeed & seed)
{
  return finite(seed.x) && finite(seed.y) && finite(seed.z) && finite(seed.yaw) &&
    finite(seed.position_search_radius) && finite(seed.yaw_search_radius) &&
    finite(seed.position_step) && finite(seed.yaw_step) && finite(seed.covariance_score);
}

double normalizeYaw(double yaw)
{
  while (yaw > 3.14159265358979323846) {
    yaw -= kTwoPi;
  }
  while (yaw < -3.14159265358979323846) {
    yaw += kTwoPi;
  }
  return yaw;
}

double yawDistance(double first, double second)
{
  return std::abs(normalizeYaw(first - second));
}

std::vector<double> makeOffsets(double radius, double step)
{
  if (radius <= std::numeric_limits<double>::epsilon()) {
    return {0.0};
  }

  const auto count = static_cast<std::size_t>(std::floor(radius / step));
  std::vector<double> offsets;
  offsets.reserve(2 * count + 1);
  offsets.push_back(0.0);
  for (std::size_t index = 1; index <= count; ++index) {
    const double offset = static_cast<double>(index) * step;
    offsets.push_back(-offset);
    offsets.push_back(offset);
  }
  return offsets;
}

bool productExceeds(
  std::size_t first,
  std::size_t second,
  std::size_t third,
  std::size_t limit)
{
  if (first != 0 && second > limit / first) {
    return true;
  }
  const std::size_t first_product = first * second;
  return third != 0 && third > limit / first_product;
}

bool sameCandidate(
  const Candidate & first,
  const Candidate & second,
  const CandidateExpansionConfig & config)
{
  const double dx = first.x - second.x;
  const double dy = first.y - second.y;
  const double dz = first.z - second.z;
  const double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
  return distance <= config.position_dedup_tolerance &&
    yawDistance(first.yaw, second.yaw) <= config.yaw_dedup_tolerance;
}

template<typename T>
bool readRequired(
  const YAML::Node & node,
  const char * key,
  T * value,
  std::string * error)
{
  if (!node[key]) {
    setError(error, std::string("missing required field: ") + key);
    return false;
  }
  try {
    *value = node[key].as<T>();
  } catch (const YAML::Exception & exception) {
    setError(error, std::string("invalid field ") + key + ": " + exception.what());
    return false;
  }
  return true;
}

bool readFinite(
  const YAML::Node & node,
  const char * key,
  double * value,
  std::string * error)
{
  if (!readRequired(node, key, value, error) || !finite(*value)) {
    setError(error, std::string("field must be finite: ") + key);
    return false;
  }
  return true;
}

bool validatePoseRecord(const LastPoseRecord & record, std::string * error)
{
  if (record.schema_version != kSchemaVersion) {
    setError(error, "unsupported last pose schema_version");
    return false;
  }
  if (record.map_id.empty() || record.map_hash.empty() || record.frame_id.empty()) {
    setError(error, "last pose map identity and frame_id are required");
    return false;
  }
  if (!finite(record.timestamp_sec) || !finite(record.x) || !finite(record.y) ||
    !finite(record.z) || !finite(record.yaw) || !finite(record.fitness_score) ||
    !finite(record.overlap_ratio) || !finite(record.inlier_ratio))
  {
    setError(error, "last pose contains a non-finite value");
    return false;
  }
  return true;
}

}  // namespace

bool loadConfiguredCandidates(
  const std::filesystem::path & path,
  ConfiguredCandidateDocument * document,
  std::string * error)
{
  if (document == nullptr) {
    setError(error, "document output is null");
    return false;
  }

  try {
    const YAML::Node root = YAML::LoadFile(path.string());
    int schema_version = 0;
    if (!readRequired(root, "schema_version", &schema_version, error) ||
      schema_version != kSchemaVersion)
    {
      setError(error, "unsupported candidate schema_version");
      return false;
    }
    if (!readRequired(root, "map_id", &document->map_id, error) ||
      !readRequired(root, "map_hash", &document->map_hash, error))
    {
      return false;
    }
    if (document->map_id.empty() || document->map_hash.empty()) {
      setError(error, "candidate map_id and map_hash are required");
      return false;
    }
    if (!root["candidates"] || !root["candidates"].IsSequence()) {
      setError(error, "candidates must be a sequence");
      return false;
    }

    std::vector<CandidateSeed> seeds;
    seeds.reserve(root["candidates"].size());
    for (const auto & node : root["candidates"]) {
      CandidateSeed seed;
      if (!readRequired(node, "id", &seed.id, error) ||
        !readFinite(node, "x", &seed.x, error) ||
        !readFinite(node, "y", &seed.y, error) ||
        !readFinite(node, "z", &seed.z, error) ||
        !readFinite(node, "yaw", &seed.yaw, error))
      {
        return false;
      }
      try {
        if (node["source"]) {
          seed.source = node["source"].as<std::string>();
        }
        if (node["position_search_radius"]) {
          seed.position_search_radius = node["position_search_radius"].as<double>();
        }
        if (node["yaw_search_radius"]) {
          seed.yaw_search_radius = node["yaw_search_radius"].as<double>();
        }
        if (node["position_step"]) {
          seed.position_step = node["position_step"].as<double>();
        }
        if (node["yaw_step"]) {
          seed.yaw_step = node["yaw_step"].as<double>();
        }
        if (node["covariance_score"]) {
          seed.covariance_score = node["covariance_score"].as<double>();
        }
        if (node["priority"]) {
          seed.priority = node["priority"].as<int>();
        }
      } catch (const YAML::Exception & exception) {
        setError(error, std::string("invalid candidate field: ") + exception.what());
        return false;
      }
      seed.map_id = document->map_id;
      seed.map_hash = document->map_hash;
      if (seed.id.empty() || seed.source.empty() || !finiteSeed(seed) ||
        seed.position_search_radius < 0.0 || seed.yaw_search_radius < 0.0 ||
        seed.position_step <= 0.0 || seed.yaw_step <= 0.0)
      {
        setError(error, "candidate has invalid identity, range, step, or numeric value");
        return false;
      }
      seeds.push_back(std::move(seed));
    }
    document->schema_version = schema_version;
    document->seeds = std::move(seeds);
    return true;
  } catch (const YAML::Exception & exception) {
    setError(error, std::string("failed to parse candidates: ") + exception.what());
    return false;
  } catch (const std::exception & exception) {
    setError(error, std::string("failed to load candidates: ") + exception.what());
    return false;
  }
}

std::vector<Candidate> expandCandidates(
  const ConfiguredCandidateDocument & document,
  const CandidateExpansionConfig & config,
  std::string * error)
{
  std::vector<Candidate> expanded;
  if (config.max_candidates == 0 || config.max_expanded_candidates == 0) {
    setError(error, "candidate limits must be positive");
    return expanded;
  }
  if (config.max_candidates > config.max_expanded_candidates) {
    setError(error, "max_candidates cannot exceed max_expanded_candidates");
    return expanded;
  }
  if (!finite(config.position_dedup_tolerance) || config.position_dedup_tolerance < 0.0 ||
    !finite(config.yaw_dedup_tolerance) || config.yaw_dedup_tolerance < 0.0)
  {
    setError(error, "candidate deduplication tolerances must be finite and non-negative");
    return expanded;
  }

  for (const auto & seed : document.seeds) {
    if (!finiteSeed(seed) || seed.position_search_radius < 0.0 ||
      seed.yaw_search_radius < 0.0 || seed.position_step <= 0.0 || seed.yaw_step <= 0.0)
    {
      setError(error, "candidate seed is invalid");
      return {};
    }
    const auto x_offsets = makeOffsets(seed.position_search_radius, seed.position_step);
    const auto y_offsets = makeOffsets(seed.position_search_radius, seed.position_step);
    const auto yaw_offsets = makeOffsets(seed.yaw_search_radius, seed.yaw_step);
    const std::size_t remaining_limit =
      config.max_expanded_candidates >= expanded.size() ?
      config.max_expanded_candidates - expanded.size() : 0;
    if (productExceeds(
        x_offsets.size(), y_offsets.size(), yaw_offsets.size(), remaining_limit))
    {
      setError(error, "candidate expansion exceeds max_expanded_candidates");
      return {};
    }
    for (const double dx : x_offsets) {
      for (const double dy : y_offsets) {
        for (const double dyaw : yaw_offsets) {
          Candidate candidate;
          candidate.expansion_index = expanded.size();
          candidate.id = seed.id + ":" + std::to_string(candidate.expansion_index);
          candidate.source = seed.source;
          candidate.map_id = seed.map_id;
          candidate.map_hash = seed.map_hash;
          candidate.x = seed.x + dx;
          candidate.y = seed.y + dy;
          candidate.z = seed.z;
          candidate.yaw = normalizeYaw(seed.yaw + dyaw);
          candidate.distance_from_seed = std::sqrt(dx * dx + dy * dy);
          candidate.covariance_score = seed.covariance_score;
          candidate.priority = seed.priority;
          expanded.push_back(std::move(candidate));
        }
      }
    }
  }

  std::stable_sort(
    expanded.begin(), expanded.end(),
    [](const Candidate & first, const Candidate & second) {
      if (first.priority != second.priority) {
        return first.priority > second.priority;
      }
      if (first.covariance_score != second.covariance_score) {
        return first.covariance_score < second.covariance_score;
      }
      if (first.distance_from_seed != second.distance_from_seed) {
        return first.distance_from_seed < second.distance_from_seed;
      }
      if (first.expansion_index != second.expansion_index) {
        return first.expansion_index < second.expansion_index;
      }
      return first.id < second.id;
    });

  std::vector<Candidate> selected;
  selected.reserve(std::min(config.max_candidates, expanded.size()));
  for (const auto & candidate : expanded) {
    const bool duplicate = std::any_of(
      selected.begin(), selected.end(),
      [&candidate, &config](const Candidate & existing) {
        return sameCandidate(existing, candidate, config);
      });
    if (duplicate) {
      continue;
    }
    selected.push_back(candidate);
    if (selected.size() == config.max_candidates) {
      break;
    }
  }
  return selected;
}

bool saveLastPoseAtomic(
  const std::filesystem::path & path,
  const LastPoseRecord & record,
  std::string * error)
{
  if (!validatePoseRecord(record, error)) {
    return false;
  }

  const auto parent = path.parent_path().empty() ? std::filesystem::path(".") : path.parent_path();
  const auto temporary_path = std::filesystem::path(path.string() + ".tmp");
  try {
    std::filesystem::create_directories(parent);
    {
      std::ofstream output(temporary_path);
      if (!output) {
        setError(error, "failed to open temporary last pose file");
        return false;
      }
      YAML::Emitter emitter;
      emitter << YAML::BeginMap
              << YAML::Key << "schema_version" << YAML::Value << record.schema_version
              << YAML::Key << "map_id" << YAML::Value << record.map_id
              << YAML::Key << "map_hash" << YAML::Value << record.map_hash
              << YAML::Key << "timestamp_sec" << YAML::Value << record.timestamp_sec
              << YAML::Key << "frame_id" << YAML::Value << record.frame_id
              << YAML::Key << "x" << YAML::Value << record.x
              << YAML::Key << "y" << YAML::Value << record.y
              << YAML::Key << "z" << YAML::Value << record.z
              << YAML::Key << "yaw" << YAML::Value << record.yaw
              << YAML::Key << "fitness_score" << YAML::Value << record.fitness_score
              << YAML::Key << "overlap_ratio" << YAML::Value << record.overlap_ratio
              << YAML::Key << "inlier_ratio" << YAML::Value << record.inlier_ratio
              << YAML::EndMap;
      output << emitter.c_str() << '\n';
      output.flush();
      if (!output) {
        setError(error, "failed to write temporary last pose file");
        std::error_code cleanup_error;
        std::filesystem::remove(temporary_path, cleanup_error);
        return false;
      }
    }

    std::error_code rename_error;
    std::filesystem::rename(temporary_path, path, rename_error);
    if (rename_error) {
      setError(error, "failed to atomically replace last pose: " + rename_error.message());
      std::error_code cleanup_error;
      std::filesystem::remove(temporary_path, cleanup_error);
      return false;
    }
    return true;
  } catch (const std::exception & exception) {
    setError(error, std::string("failed to save last pose: ") + exception.what());
    std::error_code cleanup_error;
    std::filesystem::remove(temporary_path, cleanup_error);
    return false;
  }
}

std::optional<LastPoseRecord> loadLastPose(
  const std::filesystem::path & path,
  const std::string & expected_map_id,
  const std::string & expected_map_hash,
  std::string * error)
{
  try {
    const YAML::Node root = YAML::LoadFile(path.string());
    LastPoseRecord record;
    if (!readRequired(root, "schema_version", &record.schema_version, error) ||
      !readRequired(root, "map_id", &record.map_id, error) ||
      !readRequired(root, "map_hash", &record.map_hash, error) ||
      !readRequired(root, "frame_id", &record.frame_id, error) ||
      !readFinite(root, "timestamp_sec", &record.timestamp_sec, error) ||
      !readFinite(root, "x", &record.x, error) ||
      !readFinite(root, "y", &record.y, error) ||
      !readFinite(root, "z", &record.z, error) ||
      !readFinite(root, "yaw", &record.yaw, error) ||
      !readFinite(root, "fitness_score", &record.fitness_score, error) ||
      !readFinite(root, "overlap_ratio", &record.overlap_ratio, error) ||
      !readFinite(root, "inlier_ratio", &record.inlier_ratio, error))
    {
      return std::nullopt;
    }
    if (!validatePoseRecord(record, error)) {
      return std::nullopt;
    }
    if ((!expected_map_id.empty() && record.map_id != expected_map_id) ||
      (!expected_map_hash.empty() && record.map_hash != expected_map_hash))
    {
      setError(error, "last pose map identity does not match the active map");
      return std::nullopt;
    }
    return record;
  } catch (const YAML::Exception & exception) {
    setError(error, std::string("failed to parse last pose: ") + exception.what());
    return std::nullopt;
  } catch (const std::exception & exception) {
    setError(error, std::string("failed to load last pose: ") + exception.what());
    return std::nullopt;
  }
}

}  // namespace agt_localization
