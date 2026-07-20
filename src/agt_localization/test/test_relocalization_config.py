from pathlib import Path

import yaml


def test_ndt_thread_count_uses_validated_bunker_baseline():
    config_path = Path(__file__).parents[1] / "config" / "relocalization.yaml"
    config = yaml.safe_load(config_path.read_text(encoding="utf-8"))

    num_threads = config["/**"]["ros__parameters"]["ndt_num_threads"]
    assert isinstance(num_threads, int)
    assert num_threads == 4
    assert num_threads >= 1
