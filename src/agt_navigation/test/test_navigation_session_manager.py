from agt_interfaces.msg import NavigationSessionStatus
from agt_navigation.session_manager import NavigationSessionManager, SessionSpec
import pytest
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, ReliabilityPolicy


@pytest.fixture
def manager():
    if not rclpy.ok():
        rclpy.init()
    node = Node("navigation_session_manager_test")
    value = NavigationSessionManager(node)
    try:
        yield value
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


def _spec():
    return SessionSpec(
        client_request_id="request_1",
        map_id="site",
        map_version_id="v1",
        task_group_id="route",
        task_revision=2,
        task_content_sha256="sha256:" + "1" * 64,
    )


def test_session_status_topic_is_reliable_transient_local(manager):
    publisher = manager.publisher
    qos = publisher.qos_profile
    assert qos.reliability == ReliabilityPolicy.RELIABLE
    assert qos.durability == DurabilityPolicy.TRANSIENT_LOCAL
    assert qos.depth == 1


def test_state_machine_records_terminal_result(manager):
    status = manager.start(_spec())
    assert status.state == NavigationSessionStatus.STATE_VALIDATING
    manager.transition(NavigationSessionStatus.STATE_ACCEPTED, total_waypoints=3)
    manager.transition(
        NavigationSessionStatus.STATE_RUNNING,
        current_waypoint=1,
        total_waypoints=3,
    )
    status = manager.transition(
        NavigationSessionStatus.STATE_SUCCEEDED,
        current_waypoint=3,
        total_waypoints=3,
    )
    assert status.terminal
    assert status.success
    assert status.current_waypoint == 3
    assert status.task_group_id == "route"


def test_illegal_transition_is_rejected(manager):
    manager.start(_spec())
    with pytest.raises(ValueError):
        manager.transition(NavigationSessionStatus.STATE_SUCCEEDED)


def test_get_session_filters_latest_status(manager):
    manager.start(_spec())
    request = type("Request", (), {"session_id": "", "client_request_id": "request_1"})()
    response = type("Response", (), {})()
    response.status = NavigationSessionStatus()
    response = manager.fill_get_response(request, response)
    assert response.success
    assert response.status.client_request_id == "request_1"

    request.client_request_id = "other"
    response = type("Response", (), {})()
    response.status = NavigationSessionStatus()
    response = manager.fill_get_response(request, response)
    assert not response.success
