# agt_experiment_manager

The package owns versioned experiment sessions under the configured runtime
directory. It atomically writes manifest/health snapshots, fsynced JSONL event
and localization-result streams, explicit rosbag profiles, summary JSON and
Markdown reports. A `RUNNING` session discovered after restart is marked
`INTERRUPTED`; it is never silently completed.

`experiment_manager_node.py` is the sole Runtime owner of record/playback processes. It loads
explicit profiles from `config/bag_profiles.yaml`; recording never uses `ros2 bag record -a`.
The service boundary is `/agt/data/bags/manage`, with `/agt/data/bags/list` for discovery and the
reliable transient-local `/agt/data/bags/status` for current state. The same service creates,
starts, completes, interrupts, and invalidates experiments and snapshots mission, map, platform,
calibration, and Nav2 bindings.

The `calibration` profile is the P1/P2 BUNKER wheel/LIO capture contract. It explicitly requests
TF, MID360, IMU, wheel odometry, chassis status, FAST-LIVO2 odometry/registered cloud, the project
navigation command topic, diagnostics, and optional canonical GNSS. A command-inert monitor-mode
capture may legitimately contain zero `/agt/navigation/cmd_vel` messages; the offline calibration
metadata gate therefore requires sensor/odom/TF/status evidence to be non-empty while treating
command and GNSS evidence as optional unless GNSS is explicitly required.

## Field navigation commissioning recorder flow

`field_mapping.launch.py` and `field_navigation.launch.py` start Runtime components only; neither
launch file owns or starts a rosbag subprocess. `agt_experiment_manager` remains the sole Runtime owner
of rosbag recording and playback.

For Phase A mapping/calibration capture, create and start the experiment, then start the explicit
`field_mapping_baseline` profile before moving the robot. For Phase C navigation validation, create
and start a separate experiment and start the explicit `field_navigation_baseline` profile before
moving the robot. Stop the recording through `/agt/data/bags/manage` before completing, interrupting,
or invalidating the experiment. Do not add a second `ros2 bag record` path to bringup wrappers.

Unexpected recorder/player exits publish `ERROR`; restart recovery marks a persisted `RUNNING`
experiment `INTERRUPTED`. A managed mapping Action may create an experiment and start an explicit
profile through the same service, but no second recorder ownership boundary is introduced.

`record_teach_repeat_result()` attaches one demo/run result with teach manifest,
path/map hashes, repeatability metrics, localization summary, execution result,
repository snapshot, and config snapshot references. `record_failure_case()`
appends an fsynced failure-case JSONL record. Both require an existing RUNNING
experiment.

职责：合并实验配置、生成有效参数快照、记录版本和实验产物。

不承载算法逻辑。
