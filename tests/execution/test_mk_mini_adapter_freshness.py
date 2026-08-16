import importlib.util
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
MODULE = ROOT / "src" / "agt_chassis_mk_mini" / "agt_chassis_mk_mini" / "ackermann_math.py"
SPEC = importlib.util.spec_from_file_location("ackermann_math_freshness", MODULE)
ACK = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(ACK)


def test_command_freshness_has_closed_interval_and_rejects_missing_stamp():
    assert ACK.command_is_fresh(1.00, 1.00, 0.20)
    assert ACK.command_is_fresh(1.20, 1.00, 0.20)
    assert not ACK.command_is_fresh(1.2001, 1.00, 0.20)
    assert not ACK.command_is_fresh(1.00, float("-inf"), 0.20)
    assert not ACK.command_is_fresh(0.90, 1.00, 0.20)


def test_adapter_stops_publishing_after_upstream_twist_timeout():
    adapter = (
        ROOT / "src" / "agt_chassis_mk_mini" / "scripts" / "mk_mini_adapter.py"
    ).read_text(encoding="utf-8")
    assert "command_is_fresh" in adapter
    assert "if not command_is_fresh(" in adapter
    assert "return" in adapter.split("if not command_is_fresh(", 1)[1].split("\n", 4)[0:4]
