from __future__ import annotations

import asyncio
from threading import Event, Thread
from typing import Iterable

from aiohttp import web

from .commissioning_port import CommissioningPort
from .command_guard import CommandReplayStore
from .delivery_ports import RunControlPort, TaskAuthoringPort
from .delivery_server import create_delivery_app
from .mission_commands import MissionCommandPort
from .state_store import GatewayStateStore


class DeliveryGatewayHttpServer:
    """Threaded HTTP server for the field-delivery Gateway composition.

    The stable base Gateway remains untouched. This server only selects the
    additive delivery application factory used by field commissioning and the
    later task/run adapters.
    """

    def __init__(
        self,
        store: GatewayStateStore,
        *,
        host: str = "0.0.0.0",
        port: int = 8765,
        stream_poll_s: float = 0.05,
        offline_after_ms: int = 5000,
        allowed_origins: Iterable[str] = ("*",),
        mission_commands: MissionCommandPort | None = None,
        commissioning: CommissioningPort | None = None,
        task_authoring: TaskAuthoringPort | None = None,
        run_control: RunControlPort | None = None,
        write_api_enabled: bool = False,
        command_token: str = "",
        command_replay_store: CommandReplayStore | None = None,
    ) -> None:
        if not host:
            raise ValueError("host must not be empty")
        if port <= 0 or port > 65535:
            raise ValueError("port must be in 1..65535")
        self._store = store
        self._host = host
        self._port = int(port)
        self._stream_poll_s = float(stream_poll_s)
        self._offline_after_ms = int(offline_after_ms)
        self._allowed_origins = tuple(str(item).strip() for item in allowed_origins if str(item).strip())
        self._mission_commands = mission_commands
        self._commissioning = commissioning
        self._task_authoring = task_authoring
        self._run_control = run_control
        self._write_api_enabled = bool(write_api_enabled)
        self._command_token = str(command_token)
        self._command_replay_store = command_replay_store
        self._stop_event = Event()
        self._started_event = Event()
        self._thread = Thread(target=self._thread_main, name="agt-delivery-gateway-http", daemon=True)
        self._startup_error: BaseException | None = None

    def build_app(self) -> web.Application:
        return create_delivery_app(
            self._store,
            stream_poll_s=self._stream_poll_s,
            offline_after_ms=self._offline_after_ms,
            allowed_origins=self._allowed_origins,
            mission_commands=self._mission_commands,
            commissioning=self._commissioning,
            task_authoring=self._task_authoring,
            run_control=self._run_control,
            write_api_enabled=self._write_api_enabled,
            command_token=self._command_token,
            command_replay_store=self._command_replay_store,
        )

    def start(self, timeout_s: float = 5.0) -> None:
        if self._thread.is_alive():
            return
        self._thread.start()
        if not self._started_event.wait(timeout_s):
            raise RuntimeError("delivery gateway HTTP server startup timed out")
        if self._startup_error is not None:
            raise RuntimeError(f"delivery gateway HTTP server failed: {self._startup_error}") from self._startup_error

    def stop(self, timeout_s: float = 3.0) -> None:
        self._stop_event.set()
        if self._thread.is_alive():
            self._thread.join(timeout_s)

    def _thread_main(self) -> None:
        try:
            asyncio.run(self._serve())
        except BaseException as exc:
            self._startup_error = exc
            self._started_event.set()

    async def _serve(self) -> None:
        runner = web.AppRunner(self.build_app())
        await runner.setup()
        try:
            site = web.TCPSite(runner, self._host, self._port)
            await site.start()
            self._started_event.set()
            while not self._stop_event.is_set():
                await asyncio.sleep(0.1)
        finally:
            await runner.cleanup()
