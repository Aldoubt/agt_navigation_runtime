#include "agt_localization/map_readiness.hpp"

#include <array>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

#include <openssl/evp.h>
#include <yaml-cpp/yaml.h>

namespace agt_localization
{
namespace
{

MapReadinessResult failure(const std::string & message)
{
  MapReadinessResult result;
  result.message = message;
  return result;
}

void setError(std::string * error, const std::string & message)
{
  if (error != nullptr) {
    *error = message;
  }
}

bool normalizeSha256(const std::string & value, std::string * normalized)
{
  constexpr char prefix[] = "sha256:";
  const std::string hex = value.rfind(prefix, 0U) == 0U ? value.substr(7U) : value;
  if (hex.size() != 64U) {
    return false;
  }
  for (const unsigned char character : hex) {
    if (!std::isxdigit(character)) {
      return false;
    }
  }
  if (normalized != nullptr) {
    std::ostringstream output;
    output << prefix;
    for (const unsigned char character : hex) {
      output << static_cast<char>(std::tolower(character));
    }
    *normalized = output.str();
  }
  return true;
}

bool hasMatchingPath(
  const std::filesystem::path & record_path,
  const std::filesystem::path & pcd_path,
  const std::string & recorded_map_file)
{
  const auto recorded_path = std::filesystem::path(recorded_map_file);
  const auto resolved_recorded_path = recorded_path.is_absolute() ?
    recorded_path : record_path.parent_path() / recorded_path;
  std::error_code error;
  const auto absolute_recorded = std::filesystem::absolute(
    resolved_recorded_path, error).lexically_normal();
  if (error) {
    return false;
  }
  const auto absolute_pcd = std::filesystem::absolute(pcd_path, error).lexically_normal();
  return !error && absolute_recorded == absolute_pcd;
}

}  // namespace

bool computeFileSha256(
  const std::filesystem::path & path,
  std::string * digest,
  std::string * error)
{
  if (digest == nullptr) {
    setError(error, "digest output is null");
    return false;
  }
  std::ifstream input(path, std::ios::binary);
  if (!input.is_open()) {
    setError(error, "failed to open file for SHA-256: " + path.string());
    return false;
  }

  using Context = std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)>;
  Context context(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
  if (!context || EVP_DigestInit_ex(context.get(), EVP_sha256(), nullptr) != 1) {
    setError(error, "failed to initialize SHA-256");
    return false;
  }

  std::array<char, 1024U * 1024U> buffer{};
  while (input.good()) {
    input.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
    const auto count = input.gcount();
    if (count > 0 && EVP_DigestUpdate(
        context.get(), buffer.data(), static_cast<std::size_t>(count)) != 1)
    {
      setError(error, "failed to update SHA-256");
      return false;
    }
  }
  if (!input.eof()) {
    setError(error, "failed to read file for SHA-256: " + path.string());
    return false;
  }

  std::array<unsigned char, EVP_MAX_MD_SIZE> hash{};
  unsigned int hash_size = 0U;
  if (EVP_DigestFinal_ex(context.get(), hash.data(), &hash_size) != 1) {
    setError(error, "failed to finalize SHA-256");
    return false;
  }

  std::ostringstream output;
  output << "sha256:" << std::hex << std::setfill('0');
  for (unsigned int index = 0U; index < hash_size; ++index) {
    output << std::setw(2) << static_cast<unsigned int>(hash[index]);
  }
  *digest = output.str();
  return true;
}

MapReadinessResult validateMapProcessingRecord(
  const std::filesystem::path & record_path,
  const std::filesystem::path & pcd_path,
  const std::string & expected_map_id,
  const std::string & expected_map_hash)
{
  if (record_path.empty() || pcd_path.empty()) {
    return failure("map processing record and PCD path are required");
  }
  if (!std::filesystem::is_regular_file(record_path)) {
    return failure("map processing record does not exist");
  }
  if (!std::filesystem::is_regular_file(pcd_path)) {
    return failure("localization PCD does not exist");
  }

  std::string actual_map_hash;
  std::string hash_error;
  if (!computeFileSha256(pcd_path, &actual_map_hash, &hash_error)) {
    return failure(hash_error);
  }

  try {
    const auto root = YAML::LoadFile(record_path.string());
    if (!root["schema_version"] || root["schema_version"].as<int>() != 1) {
      return failure("unsupported map processing record schema_version");
    }
    if (!root["state"] || root["state"].as<std::string>() != "ready") {
      return failure("map processing record state is not ready");
    }
    if (!root["map_file"] || !root["map_file"].IsScalar()) {
      return failure("map processing record map_file is required");
    }
    const auto recorded_map_file = root["map_file"].as<std::string>();
    if (recorded_map_file.empty() || !hasMatchingPath(record_path, pcd_path, recorded_map_file)) {
      return failure("map processing record map_file does not match localization PCD");
    }
    if (!expected_map_id.empty() && root["map_id"] &&
      root["map_id"].as<std::string>() != expected_map_id)
    {
      return failure("map processing record map_id does not match active map");
    }
    std::string normalized_expected_hash;
    if (!expected_map_hash.empty() &&
      (!normalizeSha256(expected_map_hash, &normalized_expected_hash) ||
      normalized_expected_hash != actual_map_hash))
    {
      return failure("active map_hash does not match localization PCD content");
    }

    MapReadinessResult result;
    result.ready = true;
    result.map_hash = actual_map_hash;
    const YAML::Node recorded_hash =
      root["pcd_sha256"] ? root["pcd_sha256"] : root["map_hash"];
    if (recorded_hash) {
      if (!recorded_hash.IsScalar()) {
        return failure("map processing record PCD hash must be a scalar");
      }
      std::string normalized_recorded_hash;
      if (!normalizeSha256(recorded_hash.as<std::string>(), &normalized_recorded_hash)) {
        return failure("map processing record PCD hash is not a valid SHA-256 identity");
      }
      if (normalized_recorded_hash != actual_map_hash) {
        return failure("map processing record PCD hash does not match localization PCD content");
      }
      result.record_hash_verified = true;
    }
    result.message = result.record_hash_verified ?
      "map processing record is ready and PCD hash is verified" :
      "map processing record is ready; PCD hash was computed but is not recorded";
    return result;
  } catch (const YAML::Exception & exception) {
    return failure(std::string("failed to parse map processing record: ") + exception.what());
  } catch (const std::exception & exception) {
    return failure(std::string("failed to validate map processing record: ") + exception.what());
  }

}

}  // namespace agt_localization
