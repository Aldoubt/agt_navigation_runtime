from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


ACTION_MOCKS = (
    "scripts/mock_waypoint_task_server.py",
    "scripts/mock_gimbal_server.py",
    "scripts/mock_vision_server.py",
)


def _read(relative: str) -> str:
    return (PACKAGE / relative).read_text(encoding="utf-8")


def test_action_mocks_do_not_depend_on_an_asyncio_event_loop():
    """Humble rclpy ActionServer does not provide asyncio.sleep() a running loop.

    These hardware-free mocks deliberately use synchronous execute callbacks and
    a MultiThreadedExecutor/ReentrantCallbackGroup so their small simulated
    delays can coexist with cancel callbacks without requiring an asyncio loop.
    """

    for relative in ACTION_MOCKS:
        source = _read(relative)
        assert "asyncio.sleep" not in source, relative
        assert "async def _execute" not in source, relative
        assert "def _execute(self, goal_handle)" in source, relative
        assert "time.sleep(step)" in source, relative
        assert "ReentrantCallbackGroup" in source, relative
        assert "callback_group=ReentrantCallbackGroup()" in source, relative
        assert "MultiThreadedExecutor" in source, relative
        assert "MultiThreadedExecutor(num_threads=2)" in source, relative
