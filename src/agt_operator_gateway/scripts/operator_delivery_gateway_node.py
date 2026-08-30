#!/usr/bin/env python3

from __future__ import annotations

import os
from pathlib import Path

from ament_index_python.packages import get_package_share_directory
import rclpy

from agt_field_commissioning.service import CommissioningService
from agt_operator_gateway.commissioning_port import FilesystemCommissioningPort
from agt_operator_gateway.delivery_http_server import DeliveryGatewayHttpServer
from agt_operator_gateway.mission_ros_adapter import MissionCommandAdapter
from agt_operator_gateway.ros_adapter import RobotStateAdapter
from agt_operator_gateway.run_ros_adapter import RunRosAdapter

COMMAND_TOKEN_ENV = "AGT_OPERATOR_COMMAND_TOKEN"


def _path_parameter(node, name: str, default: str = "") -> Path | None:
    raw = str(node.declare_parameter(name, default).value).strip()
    return Path(raw).expanduser().resolve() if raw else None


def main(args=None) -> None:
    rclpy.init(args=args)
    node = RobotStateAdapter()

    command_token = os.environ.get(COMMAND_TOKEN_ENV, "").strip()
    mission_commands = None
    write_api_enabled = False
    if node.write_api_enabled:
        if command_token:
            mission_commands = MissionCommandAdapter(
                node,
                timeout_s=node.mission_command_timeout_s,
            )
            write_api_enabled = True
        else:
            node.get_logger().error(
                f"write_api_enabled requested but {COMMAND_TOKEN_ENV} is empty; "
                "delivery Gateway will remain read-only"
            )

    commissioning = None
    commissioning_enabled = bool(
        node.declare_parameter("commissioning_enabled", False).value
    )
    if commissioning_enabled:
        site_id = str(node.declare_parameter("commissioning_site_id", "").value).strip()
        run_id = str(node.declare_parameter("commissioning_run_id", "").value).strip()
        runtime_dir = _path_parameter(node, "commissioning_runtime_dir", "runtime")
        sites_root = _path_parameter(node, "commissioning_sites_root", "")
        state_root = _path_parameter(node, "commissioning_state_root", "")
        vehicle_profile = _path_parameter(node, "commissioning_vehicle_profile", "")

        contracts_share = Path(get_package_share_directory("agt_runtime_contracts"))
        vehicle_schema = _path_parameter(
            node,
            "commissioning_vehicle_schema",
            str(contracts_share / "schemas" / "vehicle_profile.schema.json"),
        )
        site_schema = _path_parameter(
            node,
            "commissioning_site_schema",
            str(contracts_share / "schemas" / "site_package.schema.json"),
        )

        if runtime_dir is None:
            raise RuntimeError("commissioning_runtime_dir cannot be empty")
        sites_root = sites_root or (runtime_dir / "sites")
        state_root = state_root or (runtime_dir / "state")
        missing = [
            name
            for name, value in (
                ("commissioning_site_id", site_id),
                ("commissioning_run_id", run_id),
                ("commissioning_vehicle_profile", vehicle_profile),
                ("commissioning_vehicle_schema", vehicle_schema),
                ("commissioning_site_schema", site_schema),
            )
            if not value
        ]
        if missing:
            node.get_logger().error(
                "commissioning Gateway disabled because required parameters are missing: "
                + ", ".join(missing)
            )
        else:
            assert vehicle_profile is not None
            assert vehicle_schema is not None
            assert site_schema is not None
            service = CommissioningService(
                runtime_dir=runtime_dir,
                sites_root=sites_root,
                state_root=state_root,
                vehicle_profile=vehicle_profile,
                vehicle_schema=vehicle_schema,
                site_schema=site_schema,
            )
            commissioning = FilesystemCommissioningPort(service, site_id, run_id)
            node.get_logger().info(
                f"commissioning Gateway bound to {site_id}/{run_id} under {runtime_dir}"
            )

    run_control = None
    run_control_enabled = bool(
        node.declare_parameter("run_control_enabled", False).value
    )
    if run_control_enabled:
        run_control = RunRosAdapter(
            node,
            robot_state_provider=node.latest_robot_state,
            timeout_s=float(node.declare_parameter("run_command_timeout_s", 5.0).value),
            relocalize_timeout_s=float(
                node.declare_parameter("run_relocalize_timeout_s", 15.0).value
            ),
            max_candidates=int(node.declare_parameter("run_relocalize_max_candidates", 64).value),
            lidar_component_id=str(
                node.declare_parameter("run_lidar_component_id", "lidar").value
            ).strip(),
            camera_gimbal_component_id=str(
                node.declare_parameter("run_camera_gimbal_component_id", "camera_gimbal").value
            ).strip(),
            localization_freshness_s=float(
                node.declare_parameter("run_localization_freshness_s", 2.0).value
            ),
            health_freshness_s=float(
                node.declare_parameter("run_health_freshness_s", 2.0).value
            ),
        )
        node.get_logger().info(
            "run Gateway enabled; physical AUTO permit remains fail-closed until a dedicated source is integrated"
        )

    server = DeliveryGatewayHttpServer(
        node.store,
        host=node.host,
        port=node.port,
        stream_poll_s=node.stream_poll_s,
        offline_after_ms=node.offline_after_ms,
        allowed_origins=node.cors_allowed_origins,
        mission_commands=mission_commands,
        commissioning=commissioning,
        task_authoring=None,
        run_control=run_control,
        write_api_enabled=write_api_enabled,
        command_token=command_token,
    )
    try:
        server.start()
        mode = "read-write" if write_api_enabled else "read-only"
        node.get_logger().info(
            f"field delivery gateway listening on http://{node.host}:{node.port} ({mode})"
        )
        rclpy.spin(node)
    finally:
        server.stop()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
