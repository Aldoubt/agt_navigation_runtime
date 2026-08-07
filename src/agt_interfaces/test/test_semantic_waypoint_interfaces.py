from agt_interfaces.msg import SemanticWaypoint, SemanticWaypointArray
from rclpy.serialization import deserialize_message, serialize_message


def test_semantic_waypoint_array_round_trip():
    waypoint = SemanticWaypoint()
    waypoint.id = "home"
    waypoint.name = "Home"
    waypoint.role = "home"
    waypoint.pose.position.x = 1.25
    waypoint.pose.position.y = -0.5
    waypoint.pose.orientation.w = 1.0
    waypoint.position_tolerance = 0.25
    waypoint.yaw_tolerance = 0.3
    waypoint.preferred_speed = 0.2
    waypoint.tags = ["safe", "charging"]
    waypoint.enabled = True

    message = SemanticWaypointArray()
    message.header.frame_id = "map"
    message.schema_version = "1.1"
    message.map_id = "greenhouse_01"
    message.base_map_sha256 = "a" * 64
    message.waypoints = [waypoint]

    restored = deserialize_message(
        serialize_message(message), SemanticWaypointArray
    )
    assert restored.header.frame_id == "map"
    assert restored.schema_version == "1.1"
    assert restored.map_id == "greenhouse_01"
    assert restored.base_map_sha256 == "a" * 64
    assert len(restored.waypoints) == 1
    assert restored.waypoints[0].id == "home"
    assert restored.waypoints[0].role == "home"
    assert restored.waypoints[0].tags == ["safe", "charging"]
    assert restored.waypoints[0].enabled is True
