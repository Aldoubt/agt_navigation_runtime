#include <gtest/gtest.h>
#include <agt_interfaces/action/execute_behavior_tree.hpp>
#include <fstream>

TEST(BtExecutorNode, GoalContractDefinesFailClosedErrors) {
  using Goal = agt_interfaces::action::ExecuteBehaviorTree::Goal;
  EXPECT_EQ(Goal::ERROR_INVALID_REQUEST, 1U);
  EXPECT_EQ(Goal::ERROR_TREE_NOT_ALLOWED, 2U);
  EXPECT_EQ(Goal::ERROR_TREE_FAILED, 3U);
  EXPECT_EQ(Goal::ERROR_CANCELED, 4U);
  EXPECT_EQ(Goal::ERROR_INTERNAL, 255U);
}
