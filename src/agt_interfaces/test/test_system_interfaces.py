from agt_interfaces.action import ChangeSystemMode, ManageMappingSession, OptimizeMap
from agt_interfaces.msg import ComponentHealth, SystemHealth, TaskReadiness
from agt_interfaces.srv import EvaluateTaskReadiness, GetSystemHealth


def test_system_interfaces_have_stable_defaults_and_constants():
    component = ComponentHealth()
    system = SystemHealth()
    readiness = TaskReadiness()
    assert component.state == ComponentHealth.STATE_UNKNOWN
    assert system.overall_state == SystemHealth.STATE_UNKNOWN
    assert not readiness.ready
    assert ChangeSystemMode.Goal.MODE_NAVIGATION == 4
    assert ManageMappingSession.Goal.OP_START == 1
    assert ManageMappingSession.Goal.OP_FINALIZE_CAPTURE == 2
    assert ManageMappingSession.Result.ERROR_GRID_SAVE_FAILED == 4
    assert ManageMappingSession.Result.ERROR_INTERNAL == 255
    mapping_goal = ManageMappingSession.Goal()
    mapping_goal.operation = ManageMappingSession.Goal.OP_START
    mapping_goal.map_id = "greenhouse_01"
    assert mapping_goal.map_id == "greenhouse_01"
    assert not ManageMappingSession.Result().success
    goal = ChangeSystemMode.Goal()
    goal.argument_keys = ["map"]
    goal.argument_values = ["/tmp/map.yaml"]
    assert goal.argument_keys == ["map"]
    assert goal.argument_values == ["/tmp/map.yaml"]
    assert OptimizeMap.Goal().backend == ""
    assert EvaluateTaskReadiness.Request().validate_task is False
    assert GetSystemHealth.Request().include_optional is False
