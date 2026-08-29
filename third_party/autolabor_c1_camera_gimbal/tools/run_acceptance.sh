#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MODE="${1:-offline}"
ROS_SETUP="${ROS_SETUP:-/opt/ros/humble/setup.bash}"
RESULT_ROOT="${RESULT_ROOT:-$ROOT/acceptance_results}"
RUN_ID="$(date +%Y%m%d_%H%M%S)"
RUN_DIR="$RESULT_ROOT/$MODE-$RUN_ID"
mkdir -p "$RUN_DIR"

log() { printf '[acceptance] %s\n' "$*"; }
fail() { printf '[acceptance] FAIL: %s\n' "$*" >&2; exit 1; }

if [[ ! -f "$ROS_SETUP" ]]; then
  fail "ROS2 Humble setup not found at $ROS_SETUP"
fi
# shellcheck disable=SC1090
source "$ROS_SETUP"
command -v colcon >/dev/null || fail "colcon not found"

run_source_tests() {
  cd "$ROOT"
  log "running source-level regression tests"
  python3 -m pytest -q tests 2>&1 | tee "$RUN_DIR/source_pytest.log"
  mkdir -p "$RUN_DIR/cpp"
  c++ -std=c++17 -Wall -Wextra -Werror -pedantic \
    -I "$ROOT/src/pantilt_camera_serial/include" \
    "$ROOT/tests/cpp/test_arrival_judge.cpp" -o "$RUN_DIR/cpp/test_arrival_judge"
  "$RUN_DIR/cpp/test_arrival_judge"
  c++ -std=c++17 -Wall -Wextra -Werror -pedantic \
    -I "$ROOT/src/pantilt_camera_serial/include" \
    "$ROOT/tests/cpp/test_serial_protocol.cpp" -o "$RUN_DIR/cpp/test_serial_protocol"
  "$RUN_DIR/cpp/test_serial_protocol"
  python3 -m py_compile \
    "$ROOT/src/camera_gimbal_capability/camera_gimbal_capability/capability_node.py" \
    "$ROOT/src/camera_gimbal_capability/camera_gimbal_capability/policy.py" \
    "$ROOT/src/autolabor_c1_bringup/scripts/fake_gimbal_camera.py" \
    "$ROOT/src/autolabor_c1_bringup/scripts/test_capability.py" \
    "$ROOT/src/autolabor_c1_bringup/scripts/test_expected_error.py" \
    "$ROOT/src/autolabor_c1_bringup/scripts/test_capability_cancel.py"
}

build_and_test() {
  cd "$ROOT"
  run_source_tests
  log "building workspace"
  colcon build --symlink-install --event-handlers console_direct+ 2>&1 | tee "$RUN_DIR/colcon_build.log"
  # shellcheck disable=SC1091
  source "$ROOT/install/setup.bash"
  log "running colcon tests"
  colcon test --event-handlers console_direct+ 2>&1 | tee "$RUN_DIR/colcon_test.log"
  colcon test-result --verbose 2>&1 | tee "$RUN_DIR/colcon_test_result.log"
}

wait_for_action() {
  local action_name="$1"
  local deadline=$((SECONDS + 15))
  while (( SECONDS < deadline )); do
    if ros2 action list 2>/dev/null | grep -Fxq "$action_name"; then
      return 0
    fi
    sleep 0.25
  done
  return 1
}

run_capability_acceptance() {
  local output_dir="$1"
  mkdir -p "$output_dir"
  ros2 run autolabor_c1_bringup test_capability.py --ros-args \
    -p output_dir:="$output_dir" 2>&1 | tee "$output_dir/test_capability.log"
  python3 "$ROOT/tools/validate_acceptance.py" \
    "$output_dir/capability_summary.json" \
    --report "$output_dir/machine_validation.json"
}

case "$MODE" in
  offline)
    build_and_test
    log "PASS: offline build/test gate completed"
    ;;
  simulated)
    build_and_test
    # shellcheck disable=SC1091
    source "$ROOT/install/setup.bash"

    start_fake() {
      local label="$1"
      shift
      log "starting fake hardware case: $label"
      ros2 launch autolabor_c1_bringup autolabor_c1_fake.launch.py \
        capture_output_root:="$RUN_DIR/captured_images" "$@" \
        >"$RUN_DIR/${label}.log" 2>&1 &
      LAUNCH_PID=$!
      wait_for_action /camera_gimbal/acquire_view || {
        kill "$LAUNCH_PID" 2>/dev/null || true
        wait "$LAUNCH_PID" 2>/dev/null || true
        fail "AcquireView action did not appear for $label"
      }
    }
    stop_fake() {
      kill "$LAUNCH_PID" 2>/dev/null || true
      wait "$LAUNCH_PID" 2>/dev/null || true
      LAUNCH_PID=""
      sleep 0.5
    }
    trap '[[ -n "${LAUNCH_PID:-}" ]] && kill "$LAUNCH_PID" 2>/dev/null || true' EXIT

    start_fake simulated_success
    run_capability_acceptance "$RUN_DIR/capability"
    stop_fake

    start_fake simulated_camera_stale publish_images:=false
    ros2 run autolabor_c1_bringup test_expected_error.py --ros-args \
      -p expected_error:=300 2>&1 | tee "$RUN_DIR/camera_stale_probe.log"
    stop_fake

    start_fake simulated_gimbal_unavailable serial_connected:=false
    ros2 run autolabor_c1_bringup test_expected_error.py --ros-args \
      -p expected_error:=200 2>&1 | tee "$RUN_DIR/gimbal_unavailable_probe.log"
    stop_fake

    start_fake simulated_post_motion_image_timeout drop_images_on_motion:=true
    ros2 run autolabor_c1_bringup test_expected_error.py --ros-args \
      -p expected_error:=301 2>&1 | tee "$RUN_DIR/post_motion_image_timeout_probe.log"
    stop_fake

    start_fake simulated_motion_failure fail_motion:=true
    ros2 run autolabor_c1_bringup test_expected_error.py --ros-args \
      -p expected_error:=202 2>&1 | tee "$RUN_DIR/motion_failure_probe.log"
    stop_fake

    start_fake simulated_cancel move_delay:=2.0
    ros2 run autolabor_c1_bringup test_capability_cancel.py \
      2>&1 | tee "$RUN_DIR/cancel_probe.log"
    stop_fake

    log "PASS: simulated success + negative fault + cancel gates completed"
    ;;
  hardware)
    build_and_test
    # shellcheck disable=SC1091
    source "$ROOT/install/setup.bash"
    CAMERA_DEVICE="${CAMERA_DEVICE:-/dev/video4}"
    GIMBAL_PORT="${GIMBAL_PORT:-/dev/ttyUSB0}"
    MANAGE_LAUNCH="${MANAGE_LAUNCH:-1}"
    if [[ "$MANAGE_LAUNCH" == "1" ]]; then
      [[ -e "$CAMERA_DEVICE" ]] || fail "camera device not found: $CAMERA_DEVICE"
      [[ -e "$GIMBAL_PORT" ]] || fail "gimbal serial port not found: $GIMBAL_PORT"
      log "starting real bringup camera=$CAMERA_DEVICE gimbal=$GIMBAL_PORT"
      ros2 launch autolabor_c1_bringup autolabor_c1.launch.py \
        gui:=false device_path:="$CAMERA_DEVICE" port_name:="$GIMBAL_PORT" \
        capture_output_root:="$RUN_DIR/captured_images" \
        >"$RUN_DIR/hardware_launch.log" 2>&1 &
      LAUNCH_PID=$!
      trap 'kill "$LAUNCH_PID" 2>/dev/null || true; wait "$LAUNCH_PID" 2>/dev/null || true' EXIT
    fi
    wait_for_action /camera_gimbal/acquire_view || fail "AcquireView action did not appear"
    ros2 run autolabor_c1_bringup check_status.py 2>&1 | tee "$RUN_DIR/check_status.log"
    run_capability_acceptance "$RUN_DIR/capability"
    log "MACHINE PASS: proceed to HUMAN_ACCEPTANCE_CHECKLIST.md before final sign-off"
    ;;
  *)
    echo "usage: $0 {offline|simulated|hardware}" >&2
    exit 2
    ;;
esac

printf '%s\n' "$RUN_DIR" > "$RESULT_ROOT/latest_${MODE}.txt"
log "artifacts: $RUN_DIR"
