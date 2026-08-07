from pathlib import Path

ROOT = Path(__file__).parents[1]
SOURCE = (ROOT / "src/relocalize_action.cpp").read_text()
HEADER = (ROOT / "include/agt_bt_executor/relocalize_action.hpp").read_text()
ACTION = (ROOT.parent / "agt_interfaces/action/Relocalize.action").read_text()


def test_uses_project_relocalize_action_and_required_ports():
    assert "agt_interfaces/action/relocalize.hpp" in HEADER
    assert '"/agt/localization/relocalize"' in SOURCE
    for port in ("mode", "timeout_s", "max_candidates", "use_last_valid_pose",
                 "use_configured_candidates", "publish_debug"):
        assert f'"{port}"' in SOURCE


def test_goal_and_result_contract_are_fail_closed():
    assert "use_last_valid_pose" in ACTION
    assert "use_configured_candidates" in ACTION
    assert "result.success" in SOURCE
    assert "cancelActive" in (ROOT / "include/agt_bt_executor/ros_action_node.hpp").read_text()
