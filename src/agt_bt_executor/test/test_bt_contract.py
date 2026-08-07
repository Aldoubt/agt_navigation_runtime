from pathlib import Path

ROOT = Path(__file__).parents[1]

def test_bt_contract_has_no_direct_motion_ownership():
    source = "\n".join(p.read_text() for p in (ROOT / "src").glob("*.cpp"))
    assert "nav2_msgs/action" not in source
    assert "geometry_msgs::msg::Twist" not in source
    assert "create_publisher<" not in source
    assert "create_publisher<tf2" not in source

def test_smoke_tree_is_non_motion_and_bt4():
    xml = (ROOT / "behavior_trees/v25_05_smoke.xml").read_text()
    assert 'BTCPP_format="4"' in xml
    assert "AlwaysSuccess" in xml
    assert "ExecuteWaypointTask" not in xml
