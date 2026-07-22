# agt_experiment_manager

The package owns versioned experiment sessions under the configured runtime
directory. It atomically writes manifest/health snapshots, fsynced JSONL event
and localization-result streams, explicit rosbag profiles, summary JSON and
Markdown reports. A `RUNNING` session discovered after restart is marked
`INTERRUPTED`; it is never silently completed.

`bag_record.launch.py` remains the compatible entrypoint and selects
`minimal`, `mapping`, `localization`, `navigation`, or `full_experiment` from
`config/bag_profiles.yaml`. The list is explicit and never uses `record -a`.

职责：合并实验配置、生成有效参数快照、记录版本和实验产物。

不承载算法逻辑。
