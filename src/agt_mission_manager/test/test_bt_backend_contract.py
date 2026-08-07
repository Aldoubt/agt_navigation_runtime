from pathlib import Path


ROOT = Path(__file__).parents[1]


def test_backend_dispatch_uses_each_executor_contract():
    source = (ROOT / "scripts/mission_manager_node.py").read_text(encoding="utf-8")
    assert 'if self._execution_backend == "behavior_tree":' in source
    assert "executor.execute(mission, resolved_paths[mission.steps[0].id])" in source
    assert "executor.execute(mission, lambda step: resolved_paths[step.id])" in source


def test_bt_runner_has_bounded_waits_and_explicit_error_mapping():
    source = (ROOT / "agt_mission_manager/bt_mission_executor.py").read_text(encoding="utf-8")
    for name in ("goal_response_timeout_s", "result_timeout_s", "cancel_timeout_s"):
        assert name in source
    assert "ERROR_TREE_FAILED: MissionErrorCode.CHILD_FAILED" in source
    assert "f\"bt_{uuid.uuid4().hex}\"" in source
    assert "task.content_sha256 != task.canonical_hash()" in source


def test_public_mission_action_remains_single_owner_and_bt_has_no_motion_ownership():
    manager = (ROOT / "scripts/mission_manager_node.py").read_text(encoding="utf-8")
    bt_source = "\n".join(path.read_text(encoding="utf-8") for path in (ROOT.parent / "agt_bt_executor/src").glob("*.cpp"))
    assert '"/agt/missions/execute"' in manager
    for forbidden in ("/agt/missions/status", "/cmd_vel", "/tf", "/tf_static", "FollowWaypoints", "NavigateToPose", "NavigateThroughPoses"):
        assert forbidden not in bt_source


def test_relocalize_clears_previous_readiness_blocker():
    source = (ROOT.parent / "agt_bt_executor/src/relocalize_action.cpp").read_text(encoding="utf-8")
    tree = (ROOT.parent / "agt_bt_executor/behavior_trees/v25_06_waypoint_mission.xml").read_text(encoding="utf-8")
    assert 'setOutput("last_blocker_code", std::string{});' in source
    assert 'setOutput("last_blocker_message", std::string{});' in source
    assert 'last_blocker_code="{last_blocker_code}"' in tree
    assert 'last_blocker_message="{last_blocker_message}"' in tree
