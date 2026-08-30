from __future__ import annotations

from typing import Any

from aiohttp import web

from .commissioning_http import register_commissioning_routes
from .commissioning_port import CommissioningPort
from .server import create_app
from .state_store import GatewayStateStore


def create_delivery_app(
    store: GatewayStateStore,
    *,
    commissioning: CommissioningPort | None = None,
    **gateway_options: Any,
) -> web.Application:
    """Compose delivery-specific capabilities around the stable base Gateway.

    The base server continues to own robot/mission telemetry and mission writes.
    Commissioning routes are additive and do not change those semantics.
    """

    app = create_app(store, **gateway_options)
    register_commissioning_routes(
        app,
        commissioning=commissioning,
        write_api_enabled=bool(gateway_options.get('write_api_enabled', False)),
        command_token=str(gateway_options.get('command_token', '')),
    )
    return app
