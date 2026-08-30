from __future__ import annotations

from typing import Any

from aiohttp import web

from .commissioning_http import register_commissioning_routes
from .commissioning_port import CommissioningPort
from .delivery_ports import InspectionAuthoringPort, RunControlPort, TaskAuthoringPort
from .server import create_app
from .state_store import GatewayStateStore
from .task_run_http import register_task_run_routes


def create_delivery_app(
    store: GatewayStateStore,
    *,
    commissioning: CommissioningPort | None = None,
    task_authoring: TaskAuthoringPort | None = None,
    inspection_authoring: InspectionAuthoringPort | None = None,
    run_control: RunControlPort | None = None,
    **gateway_options: Any,
) -> web.Application:
    """Compose delivery-specific capabilities around the stable base Gateway.

    The base server continues to own robot/mission telemetry and mission writes.
    Commissioning, task/inspection authoring and run-control routes are additive
    and do not change those semantics.
    """

    app = create_app(store, **gateway_options)
    write_api_enabled = bool(gateway_options.get("write_api_enabled", False))
    command_token = str(gateway_options.get("command_token", ""))

    async def add_delivery_cors_methods(
        _request: web.Request,
        response: web.StreamResponse,
    ) -> None:
        if 'Access-Control-Allow-Methods' in response.headers:
            response.headers['Access-Control-Allow-Methods'] = 'GET, POST, PUT, OPTIONS'

    async def delivery_options(_request: web.Request) -> web.Response:
        """Accept browser CORS preflight for additive delivery API routes.

        Origin validation and CORS response headers remain owned by the base
        Gateway middleware/response hook.  This handler only ensures that
        browser preflight does not stop at aiohttp's default 405 response for
        commissioning/task/run write routes added after create_app().
        """
        return web.Response(status=204)

    app.on_response_prepare.append(add_delivery_cors_methods)

    register_commissioning_routes(
        app,
        commissioning=commissioning,
        write_api_enabled=write_api_enabled,
        command_token=command_token,
    )
    register_task_run_routes(
        app,
        task_authoring=task_authoring,
        inspection_authoring=inspection_authoring,
        run_control=run_control,
        write_api_enabled=write_api_enabled,
        command_token=command_token,
    )

    # Base mission commands already have explicit OPTIONS routes.  Delivery
    # capabilities are registered later, so provide a narrow API-wide fallback
    # for their browser preflight requests instead of duplicating an OPTIONS
    # registration for every POST/PUT endpoint.
    app.router.add_route('OPTIONS', '/api/v1/{tail:.*}', delivery_options)
    return app
