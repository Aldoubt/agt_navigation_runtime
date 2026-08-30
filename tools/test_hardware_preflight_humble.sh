#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ROS_SETUP="/opt/ros/humble/setup.bash"

if [[ ! -f "$ROS_SETUP" ]]; then
  echo "ERROR: ROS 2 Humble setup not found at $ROS_SETUP" >&2
  exit 2
fi

# ROS/ament environment scripts may probe variables that are intentionally
# unset. Temporarily disable nounset only while sourcing setup files, then
# restore the strict shell contract for the actual smoke test.
set +u
source "$ROS_SETUP"
set -u

for command in python3 colcon ros2; do
  if ! command -v "$command" >/dev/null 2>&1; then
    echo "ERROR: required command not found: $command" >&2
    exit 2
  fi
done

# Build in an isolated workspace so this smoke tests the preflight packages
# themselves. agt_hardware_bringup intentionally has product composition
# packages as exec_depend; discovering the entire Runtime workspace would make
# colcon require that full product dependency closure before this package-only
# build can start.
SMOKE_WS="$(mktemp -d -t agt-preflight-humble-XXXXXX)"
cleanup() {
  rm -rf "$SMOKE_WS"
}
trap cleanup EXIT

mkdir -p "$SMOKE_WS/src"
cp -a "$ROOT/src/agt_description" "$SMOKE_WS/src/agt_description"
cp -a "$ROOT/src/agt_hardware_bringup" "$SMOKE_WS/src/agt_hardware_bringup"

cd "$SMOKE_WS"

mapfile -t discovered_packages < <(colcon list --names-only | sort)
expected_packages=(agt_description agt_hardware_bringup)
if [[ "${discovered_packages[*]}" != "${expected_packages[*]}" ]]; then
  echo "ERROR: isolated smoke workspace discovered unexpected packages" >&2
  printf '  discovered: %s\n' "${discovered_packages[*]}" >&2
  exit 3
fi

echo "[1/3] Building isolated Humble preflight packages"
colcon build \
  --event-handlers console_direct+ \
  --packages-select \
    agt_description \
    agt_hardware_bringup

echo "[2/3] Running package tests"
set +u
source "$SMOKE_WS/install/setup.bash"
set -u
colcon test \
  --event-handlers console_direct+ \
  --packages-select \
    agt_description \
    agt_hardware_bringup
colcon test-result --verbose

echo "[3/3] Checking installed CLI/assets"
ros2 run agt_hardware_bringup socketcan_preflight.py --help >/dev/null
ros2 run agt_hardware_bringup vehicle_preflight.py --help >/dev/null
python3 - <<'PY'
from pathlib import Path
from ament_index_python.packages import get_package_share_directory

hardware = Path(get_package_share_directory('agt_hardware_bringup'))
description = Path(get_package_share_directory('agt_description'))

required = (
    hardware / 'launch' / 'bunker_mid360.launch.py',
    hardware / 'config' / 'sensor_profiles.yaml',
    description / 'launch' / 'bunker_description.launch.py',
    description / 'config' / 'bunker_mid360.yaml',
)
missing = [str(path) for path in required if not path.is_file()]
if missing:
    raise SystemExit('missing installed preflight assets: ' + ', '.join(missing))
PY

echo "PASS: ROS 2 Humble preflight package build/test/install smoke"
