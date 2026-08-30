from __future__ import annotations

import importlib.util
from pathlib import Path
import sys


PACKAGE_ROOT = Path(__file__).resolve().parents[1]
MODULE = PACKAGE_ROOT / "agt_hardware_bringup" / "socketcan_preflight.py"


def load_module():
    spec = importlib.util.spec_from_file_location("socketcan_preflight", MODULE)
    if spec is None or spec.loader is None:
        raise RuntimeError("unable to load socketcan_preflight module")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


HEALTHY = """2: can0: <NOARP,UP,LOWER_UP,ECHO> mtu 16 qdisc fq_codel state UP mode DEFAULT group default qlen 10
    link/can  promiscuity 0  allmulti 0 minmtu 0 maxmtu 0
    can state ERROR-ACTIVE (berr-counter tx 0 rx 0) restart-ms 100
      bitrate 500000 sample-point 0.875
      tq 12 prop-seg 69 phase-seg1 70 phase-seg2 20 sjw 1 brp 1
    RX: bytes  packets  errors  dropped  missed  mcast
        81234   1234     0       0       0       0
    TX: bytes  packets  errors  dropped  carrier collsns
        1024    20       0       0       0       0
"""


def test_parse_healthy_can_link():
    module = load_module()
    details = module.parse_ip_link_details(HEALTHY)
    assert details["interface"] == "can0"
    assert details["is_can"] is True
    assert details["oper_state"] == "UP"
    assert details["can_state"] == "ERROR-ACTIVE"
    assert details["bitrate"] == 500000
    assert details["berr_tx"] == 0
    assert details["berr_rx"] == 0
    assert details["rx_errors"] == 0
    assert details["tx_errors"] == 0
    assert details["rx_dropped"] == 0
    assert details["tx_dropped"] == 0


def test_evaluate_accepts_matching_healthy_link():
    module = load_module()
    ok, blockers = module.evaluate_can_link(module.parse_ip_link_details(HEALTHY), 500000)
    assert ok is True
    assert blockers == []


def test_evaluate_rejects_bitrate_mismatch():
    module = load_module()
    ok, blockers = module.evaluate_can_link(module.parse_ip_link_details(HEALTHY), 250000)
    assert ok is False
    assert "bitrate_mismatch:500000!=250000" in blockers


def test_evaluate_rejects_non_can_interface():
    module = load_module()
    details = module.parse_ip_link_details(
        "2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 state UP\n    link/ether aa:bb:cc:dd:ee:ff\n"
    )
    ok, blockers = module.evaluate_can_link(details)
    assert ok is False
    assert "not_can_interface" in blockers


def test_evaluate_rejects_bus_off():
    module = load_module()
    text = HEALTHY.replace("ERROR-ACTIVE", "BUS-OFF")
    ok, blockers = module.evaluate_can_link(module.parse_ip_link_details(text), 500000)
    assert ok is False
    assert "can_state:BUS-OFF" in blockers


def test_evaluate_rejects_missing_or_down_interface_evidence():
    module = load_module()
    ok, blockers = module.evaluate_can_link({})
    assert ok is False
    assert "missing_interface_evidence" in blockers

    details = module.parse_ip_link_details(HEALTHY.replace("state UP", "state DOWN"))
    ok, blockers = module.evaluate_can_link(details)
    assert ok is False
    assert "oper_state:DOWN" in blockers


def test_parser_extracts_nonzero_error_counters_as_evidence():
    module = load_module()
    text = HEALTHY.replace("berr-counter tx 0 rx 0", "berr-counter tx 3 rx 4")
    text = text.replace("1234     0       0", "1234     7       8")
    text = text.replace("20       0       0", "20       9       10")
    details = module.parse_ip_link_details(text)
    assert details["berr_tx"] == 3
    assert details["berr_rx"] == 4
    assert details["rx_errors"] == 7
    assert details["tx_errors"] == 9
    assert details["rx_dropped"] == 8
    assert details["tx_dropped"] == 10


def test_dynamic_observation_rejects_new_errors_and_reports_deltas():
    module = load_module()
    before = module.parse_ip_link_details(HEALTHY)
    after_text = HEALTHY.replace("berr-counter tx 0 rx 0", "berr-counter tx 1 rx 2")
    after_text = after_text.replace("1234     0       0", "1234     3       4")
    after = module.parse_ip_link_details(after_text)

    ok, blockers, deltas = module.evaluate_can_observation(before, after, 500000)

    assert ok is False
    assert deltas["berr_tx"] == 1
    assert deltas["berr_rx"] == 2
    assert deltas["rx_errors"] == 3
    assert deltas["rx_dropped"] == 4
    assert "counter_increase:berr_tx:+1" in blockers
    assert "counter_increase:rx_errors:+3" in blockers


def test_dynamic_observation_accepts_packet_growth_without_error_growth():
    module = load_module()
    before = module.parse_ip_link_details(HEALTHY)
    after_text = HEALTHY.replace("81234   1234", "91234   2234").replace(
        "1024    20", "2024    120"
    )
    after = module.parse_ip_link_details(after_text)

    ok, blockers, deltas = module.evaluate_can_observation(before, after, 500000)

    assert ok is True
    assert blockers == []
    assert all(value == 0 for value in deltas.values())


def test_run_preflight_can_take_two_read_only_samples():
    module = load_module()
    samples = [module.parse_ip_link_details(HEALTHY), module.parse_ip_link_details(HEALTHY)]
    calls = []

    def collector(interface):
        calls.append(interface)
        return samples.pop(0), []

    report = module.run_preflight(
        "can0",
        500000,
        observation_sec=0.01,
        collector=collector,
        sleeper=lambda _: None,
    )

    assert calls == ["can0", "can0"]
    assert report["ready"] is True
    assert report["observation_sec"] == 0.01
    assert report["evidence"]["before"]["can_state"] == "ERROR-ACTIVE"
    assert report["evidence"]["after"]["can_state"] == "ERROR-ACTIVE"
    assert report["evidence"]["delta"]["rx_errors"] == 0
