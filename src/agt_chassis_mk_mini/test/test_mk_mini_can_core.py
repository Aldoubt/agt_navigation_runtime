import ast
from pathlib import Path

from agt_chassis_mk_mini.mk_mini_command_state import CommandStateMachine, Gear
from agt_chassis_mk_mini.mk_mini_protocol import (
    Gear as ProtocolGear,
    encode_ctrl_command,
)
from agt_chassis_mk_mini.socketcan_transport import (
    CAN_EFF_FLAG,
    pack_linux_can_frame,
    unpack_linux_can_frame,
)


def test_protocol_manual_golden_vectors():
    assert encode_ctrl_command(
        gear=ProtocolGear.D,
        speed_mps=0.0,
        steering_deg=0.0,
        alive_counter=1,
    ) == bytes.fromhex("04 00 00 00 00 00 10 14")
    assert encode_ctrl_command(
        gear=ProtocolGear.D,
        speed_mps=1.0,
        steering_deg=0.0,
        alive_counter=0,
    ) == bytes.fromhex("84 3E 00 00 00 00 00 BA")
    assert encode_ctrl_command(
        gear=ProtocolGear.DISABLE,
        speed_mps=0.0,
        steering_deg=-25.0,
        alive_counter=0,
    ) == bytes.fromhex("00 00 C0 63 0F 00 00 AC")


def test_startup_motion_requires_stationary_feedback_hold():
    machine = CommandStateMachine(
        command_timeout=0.20,
        feedback_timeout=0.20,
        speed_deadband=0.01,
        shift_speed_threshold=0.05,
        gear_shift_hold_sec=0.05,
        park_hold_sec=0.20,
    )
    machine.update_command(speed_mps=0.5, steering_deg=2.0, stamp=0.0)
    assert machine.step(0.0).gear == Gear.PARK
    machine.update_feedback(speed_mps=0.0, stamp=0.0)
    assert machine.step(0.0).gear == Gear.PARK
    machine.update_feedback(speed_mps=0.0, stamp=0.06)
    shifted = machine.step(0.06)
    assert shifted.gear == Gear.DRIVE
    assert shifted.speed_mps == 0.0
    assert machine.step(0.07).speed_mps == 0.5


def test_socketcan_extended_flag_is_transport_only():
    payload = bytes.fromhex("84 3E 00 00 00 00 00 BA")
    raw = pack_linux_can_frame(0x18C4D2D0, payload)
    frame = unpack_linux_can_frame(raw)
    assert frame.can_id == 0x18C4D2D0
    assert frame.data == payload
    assert int.from_bytes(raw[:4], "little") & CAN_EFF_FLAG


def test_backend_and_launch_python_parse_without_importing_ros_runtime():
    package_root = Path(__file__).resolve().parents[1]
    for relative in ["scripts/mk_mini_can_backend.py", "launch/mk_mini.launch.py"]:
        source = (package_root / relative).read_text(encoding="utf-8")
        ast.parse(source, filename=relative)
