from math import cos, sin
from types import SimpleNamespace as NS

from agt_operator_gateway.contract import (
    GATEWAY_API_VERSION,
    GATEWAY_STREAM_SCHEMA,
    build_capabilities,
    build_mission_view,
    build_navigation_view,
    build_robot_snapshot,
)


def ns(**kwargs):
    return NS(**kwargs)


def quat_from_yaw(yaw):
    return ns(x=0.0, y=0.0, z=sin(yaw / 2.0), w=cos(yaw / 2.0))


def make_state(*, ready=True, warnings=False, localization_state=3, pose_valid=True,
               mission_state=2, mission_id='inspection-01', map_known=True):
    task_readiness = ns(
        ready=ready,
        blocker_codes=[] if ready else ['LOCALIZATION_LOST'],
        blocker_messages=[] if ready else ['localization is lost'],
        warning_codes=['LOW_RATE'] if warnings else [],
        warning_messages=['lidar rate degraded'] if warnings else [],
    )
    localization = ns(
        state=localization_state,
        pose_valid=pose_valid,
        backend='relocalization',
        global_pose=ns(
            pose=ns(
                pose=ns(
                    position=ns(x=4.2, y=-1.5, z=0.0),
                    orientation=quat_from_yaw(1.2),
                )
            )
        ),
    )
    active_map = ns(map_id='greenhouse', map_version_id='v3', active=True)
    mission = ns(
        state=mission_state,
        mission_id=mission_id,
        mission_version='v1',
        current_step_index=1,
        total_steps=4,
        current_step_id='P02',
    )
    return ns(
        revision=7,
        system_mode=5,
        active_profile='bunker_field',
        task_readiness_known=True,
        task_readiness_freshness_s=0.1,
        task_readiness=task_readiness,
        active_map_known=map_known,
        active_map=active_map,
        localization_status_known=True,
        localization_freshness_s=0.2,
        localization=localization,
        mission_status_known=bool(mission_id),
        mission_freshness_s=0.2,
        mission=mission,
    )


def test_contract_versions_are_frozen():
    assert GATEWAY_API_VERSION == 'agt.operator.gateway/v1'
    assert GATEWAY_STREAM_SCHEMA == 'agt.operator.stream/v1'


def test_ready_projection_preserves_authoritative_readiness_and_pose():
    state = make_state()
    snapshot = build_robot_snapshot(state, robot_id='agt-01', robot_name='BUNKER')
    assert snapshot['identity'] == {'id': 'agt-01', 'name': 'BUNKER'}
    assert snapshot['mode'] == 'AUTO'
    assert snapshot['readiness'] == 'READY'
    assert snapshot['blockers'] == []
    assert snapshot['warnings'] == []
    assert snapshot['pose']['x'] == 4.2
    assert snapshot['pose']['y'] == -1.5
    assert abs(snapshot['pose']['yawRad'] - 1.2) < 1e-9
    assert snapshot['localization']['state'] == 'TRACKING'
    assert snapshot['localization']['quality'] is None
    assert snapshot['localization']['ageMs'] == 200
    assert snapshot['activeMap'] == {'id': 'greenhouse', 'version': 'v3'}
    assert snapshot['activeMission']['id'] == 'inspection-01'


def test_warning_downgrades_ready_to_degraded_without_inventing_blocker():
    snapshot = build_robot_snapshot(make_state(warnings=True), robot_id='r', robot_name='R')
    assert snapshot['readiness'] == 'DEGRADED'
    assert snapshot['blockers'] == []
    assert snapshot['warnings'] == [{'code': 'LOW_RATE', 'message': 'lidar rate degraded'}]


def test_blocked_projection_uses_task_readiness_blocker():
    snapshot = build_robot_snapshot(make_state(ready=False), robot_id='r', robot_name='R')
    assert snapshot['readiness'] == 'BLOCKED'
    assert snapshot['blockers'] == [
        {'code': 'LOCALIZATION_LOST', 'message': 'localization is lost'}
    ]


def test_invalid_pose_does_not_report_tracking_pose_as_valid_navigation_data():
    state = make_state(localization_state=6, pose_valid=False)
    snapshot = build_robot_snapshot(state, robot_id='r', robot_name='R')
    navigation = build_navigation_view(state)
    assert snapshot['localization']['state'] == 'LOST'
    assert snapshot['pose'] == {'x': 0.0, 'y': 0.0, 'yawRad': 0.0}
    assert navigation['robotPose'] == {'x': 0.0, 'y': 0.0, 'yawRad': 0.0}
    assert navigation['map'] is None


def test_mission_projection_maps_runtime_state_and_progress():
    mission = build_mission_view(make_state(mission_state=6))
    assert mission['id'] == 'inspection-01'
    assert mission['state'] == 'PAUSED'
    assert mission['currentStep'] == 2
    assert mission['totalSteps'] == 4
    assert mission['progress'] == 0.25
    assert mission['route'] == []


def test_no_active_mission_uses_explicit_compatibility_sentinel():
    mission = build_mission_view(make_state(mission_id=''))
    assert mission == {
        'id': '__none__',
        'name': 'No active mission',
        'state': 'READY',
        'currentStep': 0,
        'totalSteps': 0,
        'progress': 0.0,
        'route': [],
        'loop': {'enabled': False, 'count': 1},
    }


def test_capabilities_are_conservative_for_p0():
    assert build_capabilities() == {
        'mapping': False,
        'localization': True,
        'navigation': True,
        'pointCloud': False,
        'globalMap': False,
        'localObstacles': False,
        'missionEdit': False,
        'inspection': False,
        'manipulator': False,
    }
