# agt_experiment_manager

The package owns versioned experiment sessions under the configured runtime
directory. It atomically writes manifest/health snapshots, fsynced JSONL event
and localization-result streams, explicit rosbag profiles, summary JSON and
Markdown reports. A `RUNNING` session discovered after restart is marked
`INTERRUPTED`; it is never silently completed.

`bag_record.launch.py` remains the compatible entrypoint and selects
`minimal`, `mapping`, `localization`, `navigation`, `teach_repeat`, or `full_experiment` from
`config/bag_profiles.yaml`. The list is explicit and never uses `record -a`.

`experiment_manager_node.py` is the sole runtime owner of record/playback processes. It exposes
`/agt/data/bags/list`, `/agt/data/bags/manage`, and the reliable transient-local
`/agt/data/bags/status`. The service also creates/completes/interrupts experiments and snapshots
mission, map, platform, calibration, and Nav2 bindings. Unexpected recorder/player exits publish
`ERROR`; restart recovery marks a persisted `RUNNING` experiment `INTERRUPTED`.

The managed mapping Action automatically creates an experiment and starts the explicit `mapping`
profile through this service. The launch recorder remains only for legacy direct-launch callers.

`record_teach_repeat_result()` attaches one demo/run result with teach manifest,
path/map hashes, repeatability metrics, localization summary, execution result,
repository snapshot, and config snapshot references. `record_failure_case()`
appends an fsynced failure-case JSONL record. Both require an existing RUNNING
experiment and do not create a second experiment ownership boundary.

职责：合并实验配置、生成有效参数快照、记录版本和实验产物。

不承载算法逻辑。
