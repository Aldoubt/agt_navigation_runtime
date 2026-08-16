from pathlib import Path

import yaml


REPO_ROOT = Path(__file__).resolve().parents[2]


def load_yaml(path: Path):
    with path.open("r", encoding="utf-8") as stream:
        return yaml.safe_load(stream)


def test_real_mk_mini_profile_declares_v1_schema():
    profile = load_yaml(REPO_ROOT / "profiles/platforms/mk_mini.yaml")
    assert profile["schema_version"] == "1.0"
