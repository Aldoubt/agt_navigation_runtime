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
    text = text.replace("1234     0", "1234     7").replace("20       0", "20       9")
    details = module.parse_ip_link_details(text)
    assert details["berr_tx"] == 3
    assert details["berr_rx"] == 4
    assert details["rx_errors"] == 7
    assert details["tx_errors"] == 9
