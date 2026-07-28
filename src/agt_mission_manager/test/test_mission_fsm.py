import pytest

from agt_mission_manager.mission_fsm import MissionFsm
from agt_mission_manager.mission_model import MissionError, MissionState


def test_pause_resume_transition_is_explicit():
    fsm = MissionFsm()
    for state in (
        MissionState.VALIDATING, MissionState.RUNNING, MissionState.PAUSING,
        MissionState.PAUSED, MissionState.RESUMING, MissionState.RUNNING, MissionState.SUCCEEDED,
    ):
        fsm.transition(state)
    assert fsm.state == MissionState.SUCCEEDED


def test_invalid_transition_is_rejected():
    with pytest.raises(MissionError):
        MissionFsm().transition(MissionState.RUNNING)


@pytest.mark.parametrize(
    "state",
    [
        MissionState.VALIDATING, MissionState.RUNNING, MissionState.WAITING_DURATION,
        MissionState.WAITING_EVENT, MissionState.PAUSED, MissionState.CANCELING,
    ],
)
def test_active_state_recovers_as_interrupted(state):
    assert MissionFsm.recover(state) == MissionState.INTERRUPTED
