from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def read(relative):
    return (ROOT / relative).read_text(encoding='utf-8')


def test_ros_adapter_is_read_only_and_consumes_authoritative_robot_state():
    text = read('agt_operator_gateway/ros_adapter.py')
    assert '/agt/system/robot_state' in text
    assert 'RobotState' in text
    assert 'create_subscription' in text
    for forbidden in (
        'create_publisher(',
        'create_client(',
        'create_service(',
        'ActionClient(',
        'nav2_msgs',
        'geometry_msgs',
    ):
        assert forbidden not in text


def test_package_declares_base_transport_and_delivery_task_dependencies():
    package = read('package.xml')
    for dependency in (
        'agt_interfaces',
        'agt_navigation',
        'rclpy',
        'python3-aiohttp',
        'nav2_msgs',
        'geometry_msgs',
    ):
        assert f'<exec_depend>{dependency}</exec_depend>' in package


def test_default_config_matches_hmi_freshness_and_browser_contract():
    config = read('config/operator_gateway.yaml')
    assert 'robot_state_topic: /agt/system/robot_state' in config
    assert 'runtime_freshness_ms: 1500' in config
    assert 'offline_after_ms: 5000' in config
    assert 'port: 8765' in config
    assert 'cors_allowed_origins:' in config
    assert "- '*'" in config


def test_node_script_starts_gateway_without_write_clients():
    script = read('scripts/operator_gateway_node.py')
    assert 'GatewayHttpServer' in script
    assert 'RobotStateAdapter' in script
    assert 'allowed_origins=node.cors_allowed_origins' in script
    for forbidden in ('create_client(', 'ActionClient(', 'send_goal', 'publish('):
        assert forbidden not in script


def test_ros_adapter_exposes_cors_origin_parameter_without_owning_http_policy():
    adapter = read('agt_operator_gateway/ros_adapter.py')
    assert 'declare_parameter' in adapter
    assert "'cors_allowed_origins'" in adapter
    assert "['*']" in adapter
    assert 'def cors_allowed_origins' in adapter
