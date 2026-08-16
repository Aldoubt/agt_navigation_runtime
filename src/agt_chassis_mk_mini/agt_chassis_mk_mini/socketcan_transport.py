"""Minimal Linux SocketCAN transport for MK-mini extended CAN frames."""

from dataclasses import dataclass
import socket
import struct
from typing import Optional


CAN_EFF_FLAG = 0x80000000
CAN_RTR_FLAG = 0x40000000
CAN_ERR_FLAG = 0x20000000
CAN_EFF_MASK = 0x1FFFFFFF

# Linux classic struct can_frame: can_id, can_dlc, padding, 8 data bytes.
CAN_FRAME_STRUCT = struct.Struct("=IB3x8s")


@dataclass(frozen=True)
class CanFrame:
    can_id: int
    data: bytes


def pack_linux_can_frame(logical_id: int, data: bytes) -> bytes:
    can_id = int(logical_id)
    payload = bytes(data)
    if not 0 <= can_id <= CAN_EFF_MASK:
        raise ValueError("CAN ID must fit the 29-bit extended identifier field")
    if len(payload) != 8:
        raise ValueError("MK-mini classic CAN transport requires an 8-byte payload")
    return CAN_FRAME_STRUCT.pack(can_id | CAN_EFF_FLAG, 8, payload)


def unpack_linux_can_frame(raw: bytes) -> CanFrame:
    frame = bytes(raw)
    if len(frame) != CAN_FRAME_STRUCT.size:
        raise ValueError("expected a 16-byte Linux classic CAN frame")
    raw_can_id, dlc, payload = CAN_FRAME_STRUCT.unpack(frame)
    if raw_can_id & CAN_ERR_FLAG:
        raise ValueError("CAN error frame is not an MK-mini data frame")
    if raw_can_id & CAN_RTR_FLAG:
        raise ValueError("CAN RTR frame is not supported")
    if not raw_can_id & CAN_EFF_FLAG:
        raise ValueError("expected an extended CAN frame")
    if dlc != 8:
        raise ValueError(f"expected DLC 8, got {dlc}")
    return CanFrame(can_id=raw_can_id & CAN_EFF_MASK, data=payload[:8])


class SocketCanTransport:
    """Nonblocking PF_CAN/SOCK_RAW transport.

    Interface configuration (bitrate/up/down) is intentionally external to this
    class so the ROS launch never requires root privileges.
    """

    def __init__(self, interface: str) -> None:
        if not interface or not str(interface).strip():
            raise ValueError("SocketCAN interface must be non-empty")
        self.interface = str(interface)
        self._socket: Optional[socket.socket] = None

    @property
    def is_open(self) -> bool:
        return self._socket is not None

    def open(self) -> None:
        if self._socket is not None:
            return
        sock = socket.socket(socket.PF_CAN, socket.SOCK_RAW, socket.CAN_RAW)
        try:
            sock.setblocking(False)
            sock.bind((self.interface,))
        except Exception:
            sock.close()
            raise
        self._socket = sock

    def close(self) -> None:
        sock = self._socket
        self._socket = None
        if sock is not None:
            sock.close()

    def send(self, logical_id: int, data: bytes) -> None:
        if self._socket is None:
            raise RuntimeError("SocketCAN transport is not open")
        raw = pack_linux_can_frame(logical_id, data)
        sent = self._socket.send(raw)
        if sent != len(raw):
            raise OSError(f"short SocketCAN write: {sent}/{len(raw)} bytes")

    def recv_nonblocking(self) -> Optional[CanFrame]:
        if self._socket is None:
            raise RuntimeError("SocketCAN transport is not open")
        try:
            raw = self._socket.recv(CAN_FRAME_STRUCT.size)
        except BlockingIOError:
            return None
        return unpack_linux_can_frame(raw)

    def __enter__(self):
        self.open()
        return self

    def __exit__(self, exc_type, exc, tb) -> None:
        self.close()
