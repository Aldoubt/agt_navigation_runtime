import re
from pathlib import Path

SRC_ROOT = Path(__file__).resolve().parents[2]
NAVIGATION_LAUNCH = SRC_ROOT / "agt_navigation" / "launch" / "navigation.launch.py"


def _declares_argument(source: str, name: str, default: str) -> bool:
    pattern = (
        rf'DeclareLaunchArgument\(\s*"{re.escape(name)}"\s*,\s*'
        rf'default_value="{re.escape(default)}"'
    )
    return re.search(pattern, source) is not None


def test_rviz_goal_bridge_is_explicit_opt_in():
    source = NAVIGATION_LAUNCH.read_text(encoding="utf-8")

    assert _declares_argument(source, "enable_rviz_goal_bridge", "false")

    bridge_match = re.search(
        r'Node\(\s*'
        r'package="agt_navigation"\s*,\s*'
        r'executable="goal_pose_bridge\.py".*?'
        r'condition=IfCondition\(LaunchConfiguration\("enable_rviz_goal_bridge"\)\)',
        source,
        flags=re.DOTALL,
    )
    assert bridge_match is not None, (
        "goal_pose_bridge.py must only start when enable_rviz_goal_bridge is true"
    )


def test_normal_navigation_keeps_direct_task_pose_goals_disabled():
    source = NAVIGATION_LAUNCH.read_text(encoding="utf-8")

    assert '"allow_direct_pose_goals": False' in source
