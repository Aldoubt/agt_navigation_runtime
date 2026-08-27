from pathlib import Path
import xml.etree.ElementTree as ET

import pytest
import yaml


XACRO_NS = "http://www.ros.org/wiki/xacro"
EXPECTED_PARENTS = {
    "base_link": "base_footprint",
    "lidar_link": "base_link",
    "livox_frame": "lidar_link",
    "imu_link": "lidar_link",
    "gps_link": "base_link",
}


def _model_root():
    model = Path(__file__).parents[1] / "urdf" / "agt_base.urdf.xacro"
    return ET.parse(model).getroot()


def test_required_frames_have_one_parent():
    root = _model_root()
    parents_by_child = {}
    for joint in root.findall("joint"):
        child = joint.find("child")
        parent = joint.find("parent")
        if child is not None and parent is not None:
            parents_by_child.setdefault(child.attrib["link"], []).append(
                parent.attrib["link"]
            )

    assert parents_by_child == {
        child: [parent] for child, parent in EXPECTED_PARENTS.items()
    }


def test_base_footprint_is_a_root_frame():
    root = _model_root()
    child_frames = {
        child.attrib["link"]
        for child in root.findall("joint/child")
    }
    assert "base_footprint" not in child_frames


def test_extrinsics_are_launch_overridable():
    root = _model_root()
    argument_names = {
        argument.attrib["name"]
        for argument in root.findall(f"{{{XACRO_NS}}}arg")
    }
    assert {
        "lidar_x",
        "lidar_y",
        "lidar_z",
        "lidar_roll",
        "lidar_pitch",
        "lidar_yaw",
        "gps_x",
        "gps_y",
        "gps_z",
        "gps_roll",
        "gps_pitch",
        "gps_yaw",
    }.issubset(argument_names)


def test_description_launch_propagates_all_gnss_extrinsics_to_xacro():
    launch_source = (
        Path(__file__).parents[1] / "launch" / "description.launch.py"
    ).read_text(encoding="utf-8")
    for name in ("gps_x", "gps_y", "gps_z", "gps_roll", "gps_pitch", "gps_yaw"):
        assert f'("{name}",' in launch_source


def test_gps_link_is_unique_and_fixed_to_base_link():
    root = _model_root()
    links = [link.attrib["name"] for link in root.findall("link")]
    assert links.count("gps_link") == 1
    joints = [
        joint
        for joint in root.findall("joint")
        if joint.attrib.get("name") == "base_link_to_gps_link"
    ]
    assert len(joints) == 1
    joint = joints[0]
    assert joint.attrib["type"] == "fixed"
    assert joint.find("parent").attrib["link"] == "base_link"
    assert joint.find("child").attrib["link"] == "gps_link"


def test_bunker_bag_derived_mid360_candidate_matches_static_ground_estimate():
    config = Path(__file__).parents[1] / "config" / "bunker_mid360.yaml"
    parameters = yaml.safe_load(config.read_text(encoding="utf-8"))["/**"][
        "ros__parameters"
    ]

    assert parameters["calibration_verified"] is False
    assert parameters["lidar_x"] == pytest.approx(
        parameters["base_length"] / 2.0 - 0.250
    )
    assert parameters["lidar_y"] == pytest.approx(0.0)
    assert parameters["base_link_z"] + parameters["lidar_z"] == pytest.approx(
        0.607, abs=0.005
    )
    assert parameters["lidar_roll"] == pytest.approx(0.0064, abs=0.002)
    assert parameters["lidar_pitch"] == pytest.approx(0.4045, abs=0.01)
    assert parameters["lidar_yaw"] == pytest.approx(0.0)


def test_gnss_extrinsic_is_explicitly_provisional():
    config = Path(__file__).parents[1] / "config" / "bunker_mid360.yaml"
    parameters = yaml.safe_load(config.read_text(encoding="utf-8"))["/**"][
        "ros__parameters"
    ]

    assert parameters["calibration_verified"] is False
    for name in ("gps_x", "gps_y", "gps_z", "gps_roll", "gps_pitch", "gps_yaw"):
        assert parameters[name] == pytest.approx(0.0)
