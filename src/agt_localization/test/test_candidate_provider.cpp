#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "agt_localization/candidate_provider.hpp"

namespace
{

std::filesystem::path testPath(const std::string & name)
{
  return std::filesystem::temp_directory_path() /
    ("agt_localization_" + name + "_" +
    std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".yaml");
}

void writeText(const std::filesystem::path & path, const std::string & text)
{
  std::ofstream output(path);
  ASSERT_TRUE(output.good());
  output << text;
}

agt_localization::ConfiguredCandidateDocument documentWithSeed(
  double position_radius,
  double position_step,
  double yaw_radius,
  double yaw_step)
{
  agt_localization::ConfiguredCandidateDocument document;
  document.map_id = "map_a";
  document.map_hash = "hash_a";
  agt_localization::CandidateSeed seed;
  seed.id = "seed";
  seed.map_id = document.map_id;
  seed.map_hash = document.map_hash;
  seed.position_search_radius = position_radius;
  seed.position_step = position_step;
  seed.yaw_search_radius = yaw_radius;
  seed.yaw_step = yaw_step;
  document.seeds.push_back(seed);
  return document;
}

}  // namespace

TEST(CandidateProviderTest, LoadsConfiguredCandidates)
{
  const auto path = testPath("configured");
  writeText(
    path,
    "schema_version: 1\n"
    "map_id: map_a\n"
    "map_hash: hash_a\n"
    "candidates:\n"
    "  - id: initial\n"
    "    x: 1.0\n"
    "    y: 2.0\n"
    "    z: 0.0\n"
    "    yaw: 0.5\n"
    "    priority: 7\n");

  agt_localization::ConfiguredCandidateDocument document;
  std::string error;
  ASSERT_TRUE(agt_localization::loadConfiguredCandidates(path, &document, &error)) << error;
  ASSERT_EQ(document.map_id, "map_a");
  ASSERT_EQ(document.map_hash, "hash_a");
  ASSERT_EQ(document.seeds.size(), 1u);
  EXPECT_EQ(document.seeds.front().id, "initial");
  EXPECT_EQ(document.seeds.front().priority, 7);
  std::filesystem::remove(path);
}

TEST(CandidateProviderTest, ExpandsInStableOrderAndDeduplicates)
{
  auto document = documentWithSeed(0.5, 0.5, 0.0, 0.1);
  document.seeds.front().priority = 3;
  agt_localization::CandidateExpansionConfig config;
  config.max_candidates = 4;

  std::string error;
  const auto candidates = agt_localization::expandCandidates(document, config, &error);
  ASSERT_TRUE(error.empty()) << error;
  ASSERT_EQ(candidates.size(), 4u);
  EXPECT_EQ(candidates[0].id, "seed:0");
  EXPECT_EQ(candidates[1].id, "seed:1");
  EXPECT_EQ(candidates[2].id, "seed:2");
  EXPECT_EQ(candidates[3].id, "seed:3");
  EXPECT_NEAR(candidates[0].distance_from_seed, 0.0, 1.0e-9);
  EXPECT_NEAR(candidates[1].distance_from_seed, 0.5, 1.0e-9);

  auto duplicate_document = documentWithSeed(0.0, 0.5, 0.0, 0.1);
  auto duplicate = duplicate_document.seeds.front();
  duplicate.id = "duplicate";
  duplicate_document.seeds.push_back(duplicate);
  config.max_candidates = 8;
  error.clear();
  const auto deduplicated =
    agt_localization::expandCandidates(duplicate_document, config, &error);
  ASSERT_TRUE(error.empty()) << error;
  ASSERT_EQ(deduplicated.size(), 1u);
  EXPECT_EQ(deduplicated.front().id, "seed:0");
}

TEST(CandidateProviderTest, RejectsUnboundedExpansion)
{
  const auto document = documentWithSeed(1.0, 1.0, 1.0, 1.0);
  agt_localization::CandidateExpansionConfig config;
  config.max_expanded_candidates = 8;
  std::string error;
  const auto candidates = agt_localization::expandCandidates(document, config, &error);
  EXPECT_TRUE(candidates.empty());
  EXPECT_NE(error.find("max_expanded_candidates"), std::string::npos);
}

TEST(CandidateProviderTest, SavesAndLoadsLastPoseOnlyForMatchingMap)
{
  const auto path = testPath("last_pose");
  agt_localization::LastPoseRecord record;
  record.map_id = "map_a";
  record.map_hash = "hash_a";
  record.timestamp_sec = 42.0;
  record.x = 1.0;
  record.yaw = -0.25;
  record.fitness_score = 0.4;
  record.overlap_ratio = 0.8;
  record.inlier_ratio = 0.9;

  std::string error;
  ASSERT_TRUE(agt_localization::saveLastPoseAtomic(path, record, &error)) << error;
  const auto loaded = agt_localization::loadLastPose(path, "map_a", "hash_a", &error);
  ASSERT_TRUE(loaded.has_value()) << error;
  EXPECT_DOUBLE_EQ(loaded->x, 1.0);
  EXPECT_DOUBLE_EQ(loaded->yaw, -0.25);

  error.clear();
  const auto rejected = agt_localization::loadLastPose(path, "map_a", "different_hash", &error);
  EXPECT_FALSE(rejected.has_value());
  EXPECT_NE(error.find("does not match"), std::string::npos);
  EXPECT_FALSE(std::filesystem::exists(std::filesystem::path(path.string() + ".tmp")));
  std::filesystem::remove(path);
}
