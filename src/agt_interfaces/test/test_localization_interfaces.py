from agt_interfaces.action import Relocalize
from agt_interfaces.msg import LocalizationStatus


def test_localization_status_constants_and_defaults():
    status = LocalizationStatus()
    status.state = LocalizationStatus.STATE_SEARCHING
    status.error_code = LocalizationStatus.ERROR_AMBIGUOUS_RESULT
    status.status_stale = True

    assert status.state == 1
    assert status.error_code == 108
    assert LocalizationStatus.ERROR_STALE_SCAN == 113
    assert LocalizationStatus.ERROR_INVALID_SCAN_TIMESTAMP == 114
    assert status.status_stale is True
    assert status.pose_valid is False


def test_relocalize_generated_types_and_mode_constants():
    goal = Relocalize.Goal()
    goal.mode = Relocalize.Goal.MODE_SINGLE_INITIAL_POSE
    goal.use_initial_pose = True
    goal.max_candidates = 3

    feedback = Relocalize.Feedback()
    feedback.state = LocalizationStatus.STATE_TRACKING

    result = Relocalize.Result()
    result.success = False
    result.error_code = LocalizationStatus.ERROR_TIMEOUT

    assert goal.mode == 1
    assert goal.use_initial_pose is True
    assert goal.max_candidates == 3
    assert feedback.state == 3
    assert result.error_code == 106
