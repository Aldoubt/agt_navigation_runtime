from agt_system_manager.readiness import ComponentEvidence, overall_health_state


STATE_UNKNOWN = 0
STATE_OK = 1
STATE_WARN = 2
STATE_ERROR = 3


def test_empty_required_health_is_unknown():
    assert overall_health_state(()) == STATE_UNKNOWN


def test_required_components_all_ok_is_ok():
    components = (
        ComponentEvidence("sensors", required=True, known=True, state=STATE_OK),
        ComponentEvidence("localization", required=True, known=True, state=STATE_OK),
    )
    assert overall_health_state(components) == STATE_OK


def test_optional_error_does_not_block_required_health():
    components = (
        ComponentEvidence("sensors", required=True, known=True, state=STATE_OK),
        ComponentEvidence("camera", required=False, known=True, state=STATE_ERROR),
    )
    assert overall_health_state(components) == STATE_WARN


def test_unknown_required_component_is_error_fail_closed():
    components = (
        ComponentEvidence("sensors", required=True, known=False, state=STATE_UNKNOWN),
    )
    assert overall_health_state(components) == STATE_ERROR


def test_required_error_dominates_warn():
    components = (
        ComponentEvidence("sensors", required=True, known=True, state=STATE_WARN),
        ComponentEvidence("chassis", required=True, known=True, state=STATE_ERROR),
    )
    assert overall_health_state(components) == STATE_ERROR
