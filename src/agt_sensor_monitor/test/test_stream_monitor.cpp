#include <gtest/gtest.h>
#include "agt_sensor_monitor/stream_monitor.hpp"
using agt_sensor_monitor::StreamConfig;
using agt_sensor_monitor::StreamMonitor;

TEST(StreamMonitor, RateAndFreshness) {
  StreamConfig c; c.name = "imu"; c.min_rate_hz = 2.0; c.max_stale_sec = 1.0; c.max_message_age_sec = 1.0;
  StreamMonitor m(c, 4); m.observe(10.0, 0.0); m.observe(10.5, 0.5); m.observe(11.0, 1.0);
  auto s = m.status(11.1, 1.1, 1.1, 0.0); EXPECT_NEAR(s.estimated_rate_hz, 2.0, 1e-9); EXPECT_TRUE(s.healthy);
  s = m.status(11.1, 2.2, 2.2, 0.0); EXPECT_TRUE(s.stale); EXPECT_FALSE(s.healthy);
}
TEST(StreamMonitor, RollbackAndDuplicate) {
  StreamConfig c; c.max_stale_sec = 10.0; c.max_message_age_sec = 10.0;
  StreamMonitor m(c); m.observe(1.0, 0.0); m.observe(1.0, 1.0); m.observe(0.0, 2.0);
  auto s = m.status(2.0, 2.0, 2.0, 0.0); EXPECT_EQ(s.duplicate_stamp_count, 1U); EXPECT_EQ(s.rollback_count, 1U); EXPECT_FALSE(s.timestamp_monotonic); EXPECT_FALSE(s.healthy);
}
TEST(StreamMonitor, StartupGrace) {
  StreamConfig c; c.min_rate_hz = 100.0; c.max_stale_sec = 1.0; c.max_message_age_sec = 1.0;
  StreamMonitor m(c); m.observe(1.0, 0.0); auto s = m.status(1.0, 0.1, 0.1, 3.0); EXPECT_TRUE(s.rate_ok); EXPECT_TRUE(s.healthy);
}
