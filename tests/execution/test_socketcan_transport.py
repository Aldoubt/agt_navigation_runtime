import importlib.util
from pathlib import Path
import struct
import sys

import pytest


ROOT = Path(__file__).resolve().parents[2]
MODULE_PATH = (
    ROOT
    / "src"
    / "agt_chassis_mk_mini"
    / "agt_chassis_mk_mini"
    / "socketcan_transport.py"
)


def load_transport():
    spec = importlib.util.spec_from_file_location("socketcan_transport", MODULE_PATH)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def test_linux_frame_pack_adds_extended_flag_but_preserves_logical_id():
    t = load_transport()
    payload = bytes.fromhex("84 3E 00 00 00 00 00 BA")
    raw = t.pack_linux_can_frame(0x18C4D2D0, payload)
    assert len(raw) == 16
    raw_can_id, dlc = struct.unpack_from("=IB", raw)
    assert raw_can_id == (0x18C4D2D0 | t.CAN_EFF_FLAG)
    assert dlc == 8
    frame = t.unpack_linux_can_frame(raw)
    assert frame.can_id == 0x18C4D2D0
    assert frame.data == payload


def test_pack_rejects_non_29_bit_id_and_non_eight_byte_payload():
    t = load_transport()
    with pytest.raises(ValueError, match="29-bit"):
        t.pack_linux_can_frame(0x20000000, bytes(8))
    with pytest.raises(ValueError, match="8-byte"):
        t.pack_linux_can_frame(0x18C4D2D0, bytes(7))


def test_unpack_rejects_standard_rtr_and_error_frames():
    t = load_transport()
    payload = bytes(8)
    standard = t.CAN_FRAME_STRUCT.pack(0x123, 8, payload)
    with pytest.raises(ValueError, match="extended"):
        t.unpack_linux_can_frame(standard)

    rtr = t.CAN_FRAME_STRUCT.pack(0x18C4D2D0 | t.CAN_EFF_FLAG | t.CAN_RTR_FLAG, 8, payload)
    with pytest.raises(ValueError, match="RTR"):
        t.unpack_linux_can_frame(rtr)

    error = t.CAN_FRAME_STRUCT.pack(0x18C4D2D0 | t.CAN_EFF_FLAG | t.CAN_ERR_FLAG, 8, payload)
    with pytest.raises(ValueError, match="error"):
        t.unpack_linux_can_frame(error)


def test_unpack_rejects_wrong_dlc_or_frame_size():
    t = load_transport()
    raw = t.CAN_FRAME_STRUCT.pack(0x18C4D2D0 | t.CAN_EFF_FLAG, 7, bytes(8))
    with pytest.raises(ValueError, match="DLC"):
        t.unpack_linux_can_frame(raw)
    with pytest.raises(ValueError, match="16-byte"):
        t.unpack_linux_can_frame(bytes(15))


def test_transport_source_does_not_shell_out_to_configure_can_interface():
    source = MODULE_PATH.read_text(encoding="utf-8").lower()
    assert "subprocess" not in source
    assert "os.system" not in source
    assert "ip link" not in source
    assert "sudo" not in source
