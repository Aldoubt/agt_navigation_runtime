import importlib.util
from pathlib import Path

from agt_interfaces.srv import ListBagSessions, ManageBagSession
import rclpy


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "experiment_manager_node.py"
SPEC = importlib.util.spec_from_file_location("experiment_manager_node", SCRIPT)
MODULE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MODULE)


def test_generated_bag_services_return_typed_idle_state(tmp_path):
    rclpy.init(args=["--ros-args", "-p", f"runtime_dir:={tmp_path}"])
    node = MODULE.ExperimentManagerNode()
    try:
        listed = node._list_sessions(
            ListBagSessions.Request(), ListBagSessions.Response()
        )
        assert listed.success
        assert listed.sessions == []
        request = ManageBagSession.Request()
        request.operation = ManageBagSession.Request.OP_STATUS
        status = node._manage_session(request, ManageBagSession.Response())
        assert status.success
        assert status.session.state == status.session.STATE_IDLE
        assert not status.session.simulation
    finally:
        node.destroy_node()
        rclpy.shutdown()


def test_unknown_bag_profile_fails_closed(tmp_path):
    rclpy.init(args=["--ros-args", "-p", f"runtime_dir:={tmp_path}"])
    node = MODULE.ExperimentManagerNode()
    try:
        create = ManageBagSession.Request()
        create.operation = ManageBagSession.Request.OP_CREATE_EXPERIMENT
        create.experiment_title = "Bag Test"
        created = node._manage_session(create, ManageBagSession.Response())
        assert created.success
        request = ManageBagSession.Request()
        request.operation = ManageBagSession.Request.OP_START_RECORDING
        request.experiment_id = created.session.experiment_id
        request.profile_id = "not_configured"
        response = node._manage_session(request, ManageBagSession.Response())
        assert not response.success
        assert response.error_code == ManageBagSession.Response.ERROR_PROFILE_INVALID
    finally:
        node.destroy_node()
        rclpy.shutdown()

