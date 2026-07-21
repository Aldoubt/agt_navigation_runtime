#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <fstream>

#include "agt_localization/map_readiness.hpp"

namespace
{

class MapReadinessTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    root_ = std::filesystem::temp_directory_path() /
      ("agt_localization_map_readiness_" +
      std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(root_);
    pcd_ = root_ / "localization_map.pcd";
    record_ = root_ / "localization_map.processing.yaml";
    std::ofstream(pcd_) << "placeholder\n";
  }

  void TearDown() override
  {
    std::filesystem::remove_all(root_);
  }

  void writeRecord(const std::string & state, const std::string & map_file)
  {
    std::ofstream output(record_);
    output << "schema_version: 1\n"
           << "state: " << state << "\n"
           << "map_file: " << map_file << "\n";
  }

  void writeHashedRecord(const std::string & hash)
  {
    std::ofstream output(record_);
    output << "schema_version: 1\n"
           << "state: ready\n"
           << "map_file: " << pcd_.filename().string() << "\n"
           << "pcd_sha256: " << hash << "\n";
  }

  std::filesystem::path root_;
  std::filesystem::path pcd_;
  std::filesystem::path record_;
};

}  // namespace

TEST_F(MapReadinessTest, AcceptsReadyRecordForMatchingPcd)
{
  writeRecord("ready", pcd_.filename().string());
  const auto result = agt_localization::validateMapProcessingRecord(record_, pcd_);
  EXPECT_TRUE(result.ready) << result.message;
  EXPECT_FALSE(result.record_hash_verified);
  EXPECT_EQ(
    result.map_hash,
    "sha256:2f73349cfc4630255319c6c8dfc1b46a8996ace9d14d8e07563b165915918ec2");
}

TEST_F(MapReadinessTest, VerifiesRecordedPcdHashAndExpectedIdentity)
{
  writeHashedRecord(
    "sha256:2F73349CFC4630255319C6C8DFC1B46A8996ACE9D14D8E07563B165915918EC2");
  const std::string hash =
    "sha256:2f73349cfc4630255319c6c8dfc1b46a8996ace9d14d8e07563b165915918ec2";
  auto result = agt_localization::validateMapProcessingRecord(record_, pcd_, "", hash);
  EXPECT_TRUE(result.ready) << result.message;
  EXPECT_TRUE(result.record_hash_verified);

  result = agt_localization::validateMapProcessingRecord(
    record_, pcd_, "", "sha256:deadbeef");
  EXPECT_FALSE(result.ready);
  EXPECT_NE(result.message.find("does not match"), std::string::npos);
}

TEST_F(MapReadinessTest, AcceptsLegacyRecordWithoutMapId)
{
  writeRecord("ready", pcd_.filename().string());
  const auto result = agt_localization::validateMapProcessingRecord(
    record_, pcd_, "greenhouse_01");
  EXPECT_TRUE(result.ready) << result.message;
}

TEST_F(MapReadinessTest, RejectsMismatchedRecordedPcdHash)
{
  writeHashedRecord(
    "sha256:7f8b1dfc466b6249f06cbe55c9174df2578e7754da793fded244ef5cba2a38f1");
  const auto result = agt_localization::validateMapProcessingRecord(record_, pcd_);
  EXPECT_FALSE(result.ready);
  EXPECT_NE(result.message.find("PCD hash"), std::string::npos);
}

TEST_F(MapReadinessTest, RejectsNonReadyAndMismatchedRecords)
{
  writeRecord("processing", pcd_.filename().string());
  auto result = agt_localization::validateMapProcessingRecord(record_, pcd_);
  EXPECT_FALSE(result.ready);
  EXPECT_NE(result.message.find("not ready"), std::string::npos);

  writeRecord("ready", "other_map.pcd");
  result = agt_localization::validateMapProcessingRecord(record_, pcd_);
  EXPECT_FALSE(result.ready);
  EXPECT_NE(result.message.find("does not match"), std::string::npos);
}
