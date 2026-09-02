# agt_inspection_exporter

冻结机器人采集端到 `agt_vision_runtime` 的离线数据协议。

## inspection_run

```text
inspection_runs/<mission_id>/
├── task.yaml
├── images/image_<unix_timestamp>.jpg
├── metadata/P01.json
└── report.json
```

每个 metadata 文件必须保留 image、robot_pose、gimbal 三个 Unix 秒级浮点时间戳。时间由 ROS Clock 产生；文件创建时间不参与协议。

## CLI

```bash
ros2 run agt_inspection_exporter export_inspection_run.py <inspection_run> <inspection_dataset>
ros2 run agt_inspection_exporter validate_inspection_dataset.py <inspection_dataset>
```

输出 dataset 只有视觉运行时需要的 `images/`、`pose.csv`、`gimbal.csv`，不依赖 ROS 或视觉模型。
