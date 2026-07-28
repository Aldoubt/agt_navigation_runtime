from __future__ import annotations

from dataclasses import dataclass

from .mission_model import MissionError, MissionState


_TRANSITIONS = {
    MissionState.IDLE: {MissionState.VALIDATING},
    MissionState.VALIDATING: {MissionState.RUNNING, MissionState.FAILED, MissionState.CANCELING},
    MissionState.RUNNING: {
        MissionState.WAITING_DURATION, MissionState.WAITING_EVENT, MissionState.PAUSING,
        MissionState.CANCELING, MissionState.SUCCEEDED, MissionState.FAILED,
    },
    MissionState.WAITING_DURATION: {
        MissionState.PAUSED, MissionState.CANCELING, MissionState.RUNNING, MissionState.FAILED,
    },
    MissionState.WAITING_EVENT: {
        MissionState.PAUSED, MissionState.CANCELING, MissionState.RUNNING, MissionState.FAILED,
    },
    MissionState.PAUSING: {MissionState.PAUSED, MissionState.CANCELING, MissionState.FAILED},
    MissionState.PAUSED: {MissionState.RESUMING, MissionState.CANCELING},
    MissionState.RESUMING: {MissionState.RUNNING, MissionState.FAILED, MissionState.CANCELING},
    MissionState.CANCELING: {MissionState.CANCELED, MissionState.FAILED},
}


@dataclass
class MissionFsm:
    state: MissionState = MissionState.IDLE

    def transition(self, target: MissionState) -> MissionState:
        if target not in _TRANSITIONS.get(self.state, set()):
            raise MissionError(f"invalid mission transition {self.state.name} -> {target.name}")
        self.state = target
        return self.state

    @staticmethod
    def recover(state: MissionState) -> MissionState:
        if state in {
            MissionState.VALIDATING, MissionState.RUNNING, MissionState.WAITING_DURATION,
            MissionState.WAITING_EVENT, MissionState.PAUSING, MissionState.PAUSED,
            MissionState.RESUMING, MissionState.CANCELING,
        }:
            return MissionState.INTERRUPTED
        return state

