#include <gtest/gtest.h>

#include "agt_interfaces/action/change_system_mode.hpp"
#include "agt_interfaces/action/optimize_map.hpp"
#include "agt_interfaces/msg/system_health.hpp"
#include "agt_interfaces/msg/task_readiness.hpp"
#include "agt_interfaces/srv/set_localization_mode.hpp"

TEST(SystemInterfaces, DefaultsAndConstantsAreGenerated)
{
  agt_interfaces::action::ChangeSystemMode::Goal goal;
  goal.argument_keys = {"map"};
  goal.argument_values = {"map.yaml"};
  EXPECT_EQ(goal.argument_keys.size(), 1U);
  EXPECT_EQ(agt_interfaces::action::ChangeSystemMode::Goal::MODE_NAVIGATION, 4U);
  EXPECT_EQ(agt_interfaces::msg::SystemHealth::STATE_UNKNOWN, 0U);
  EXPECT_FALSE(agt_interfaces::msg::TaskReadiness().ready);
  EXPECT_EQ(agt_interfaces::srv::SetLocalizationMode::Request::MODE_MANUAL_ONLY, 0U);
  EXPECT_TRUE(agt_interfaces::action::OptimizeMap::Goal().backend.empty());
}
