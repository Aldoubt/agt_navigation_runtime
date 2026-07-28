from agt_interfaces.action import (
    ChangeSystemMode,
    ExecuteMission,
    ManageMappingSession,
    OptimizeMap,
)
from agt_interfaces.msg import (
    BagSessionSummary,
    ComponentHealth,
    ExperimentSummary,
    MapVersionSummary,
    MissionEvent,
    MissionStatus,
    RobotState,
    SystemHealth,
    TaskReadiness,
)
from agt_interfaces.srv import (
    EvaluateTaskReadiness,
    GetRobotState,
    GetSystemHealth,
    ListBagSessions,
    ListExperiments,
    ListMapVersions,
    ManageBagSession,
    ManageMapVersion,
    SetMissionRunState,
)


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
    assert MissionStatus.STATE_INTERRUPTED == 12
    assert MissionStatus.STEP_WAYPOINT_TASK == 1
    assert MissionStatus.STEP_WAIT_EVENT == 3
    assert MissionEvent().event_type == ""
    assert MapVersionSummary.STATE_READY == 3
    assert BagSessionSummary.STATE_RECORDING == 2
    assert RobotState.MODE_UNKNOWN == 0
    assert RobotState().system_mode == RobotState.MODE_UNKNOWN
    assert not RobotState().mission_status_known
    assert not RobotState().active_map_known
    assert ExecuteMission.Goal().mission_id == ""
    assert GetRobotState.Request().include_details is False
    assert SetMissionRunState.Request.COMMAND_PAUSE == 1
    assert ListMapVersions.Request().state == MapVersionSummary.STATE_UNKNOWN
    assert ManageMapVersion.Request.OP_PURGE == 7
    assert ManageMapVersion.Request.OP_IMPORT_CANDIDATE == 8
    assert ManageMapVersion.Request().candidate_map_yaml == ""
    assert ManageMapVersion.Response.ERROR_CONFIRMATION_REQUIRED == 5
    assert ListBagSessions.Response().sessions == []
    assert ManageBagSession.Request.OP_INTERRUPT_EXPERIMENT == 7
    assert ManageBagSession.Request.OP_ADD_EXPERIMENT_EVENT == 10
    assert ManageBagSession.Response.ERROR_PROFILE_INVALID == 4
    assert ManageBagSession.Request().experiment_title == ""
    assert ManageBagSession.Request().tags_json == ""
    assert ExperimentSummary.STATE_INTERRUPTED == 4
    assert ListExperiments.Response().experiments == []
