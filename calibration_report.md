# LiDAR-IMU-Base 外参联合标定检查报告

数据源：`runtime/rosbag/bunker_mid360_mapping_20260901_211105`  
检查方式：只读检查仓库配置、源码 TF 发布点、rosbag2 SQLite 元数据及代表性消息。

## Sensor Configuration

### 配置位置

- FAST-LIVO2 主参数：[src/agt_odometry/config/mid360_lio_only.yaml](/home/yangxuan/agt_navigation_runtime/src/agt_odometry/config/mid360_lio_only.yaml)
- FAST-LIVO2 适配器：[src/agt_odometry/config/fast_livo2_adapter.yaml](/home/yangxuan/agt_navigation_runtime/src/agt_odometry/config/fast_livo2_adapter.yaml)
- FAST-LIVO2 启动：[src/agt_odometry/launch/fast_livo2_odometry.launch.py](/home/yangxuan/agt_navigation_runtime/src/agt_odometry/launch/fast_livo2_odometry.launch.py)
- MID360 网络参数：[src/agt_sensor_adapters/config/mid360_network.json](/home/yangxuan/agt_navigation_runtime/src/agt_sensor_adapters/config/mid360_network.json)
- MID360 启动：[src/agt_sensor_adapters/launch/mid360.launch.py](/home/yangxuan/agt_navigation_runtime/src/agt_sensor_adapters/launch/mid360.launch.py)
- 机器人外参：[src/agt_description/config/bunker_mid360.yaml](/home/yangxuan/agt_navigation_runtime/src/agt_description/config/bunker_mid360.yaml)
- URDF：[src/agt_description/urdf/agt_base.urdf.xacro](/home/yangxuan/agt_navigation_runtime/src/agt_description/urdf/agt_base.urdf.xacro)

当前传感器配置为：MID360 `lidar_type=8`，FAST-LIVO2 预处理 `lidar_type=1`、`scan_rate=10`、`scan_line=4`，IMU 启用，重力/偏置估计启用，`imu_time_offset=0`。Livox 驱动保留逐点时间的 `CustomMsg`（`xfer_format=1`）。

注意：`mid360_network.json` 中 Livox SDK 的设备级 `extrinsic_parameter` 全为零；这只是驱动侧设备配置，不应当用来代替 FAST-LIVO2 的 LiDAR-IMU 外参或 URDF 的 Base-LiDAR 外参。

## TF Tree

仓库和 bag 实际验证到的静态链是：

```text
base_footprint
└── base_link
    └── lidar_link
        ├── livox_frame
        └── imu_link
```

运行时应再由定位/里程计模块提供：

```text
map ──> odom ──> base_footprint ──> base_link ──> lidar_link
                                      ├── livox_frame
                                      └── imu_link
```

这与任务中写的 `mid360_link` 不一致：仓库没有 `mid360_link`，驱动和 bag 使用 `livox_frame`。建议后续统一采用仓库现有命名，不要额外引入同义 frame。

bag 的 `/tf_static` 只有 1 条消息，包含以下 4 条边：

| parent | child | translation (m) | rotation |
|---|---|---:|---|
| base_footprint | base_link | `[0, 0, 0.2]` | identity |
| base_link | lidar_link | `[0.2615, 0, 0.4070]` | rpy 约 `[0.0064, 0.4045, 0]` |
| lidar_link | imu_link | `[0, 0, 0]` | identity |
| lidar_link | livox_frame | `[0, 0, 0]` | identity |

因此 bag 中没有重复的静态边证据。源码检查显示固定 TF 的正常唯一 owner 是 `robot_state_publisher`；FAST-LIVO2 已在 launch 中关闭原生 TF，适配器负责 `odom -> base_footprint`。但是底盘驱动默认也有 `publish_odom_tf=true`，实机启动时必须确保它与适配器不同时发布同一条 `odom -> base_footprint`。

bag 的 `/tf` 消息数为 **0**，所以不能从本次录包验证动态 `map -> odom` 或 `odom -> base_footprint` 是否连续；bag 中底盘里程计的 frame 是 `bunker_odom -> base_footprint`，也不是标准 `odom`。

## Timestamp Analysis

bag 总时长为 **390.102455 s**，起止约为 `1788268266.127666` 到 `1788268656.230120`。

| 逻辑数据 | bag 中实际 topic | count | 频率/时间戳范围 | frame_id |
|---|---|---:|---|---|
| LiDAR | `/agt/sensors/lidar/custom` | 3896 | 约 10.00 Hz；header `1788268266.540503`–`1788268656.041052` | `livox_frame` |
| LiDAR filtered | `/agt/sensors/lidar/custom_filtered` | 3895 | 约 10.00 Hz；录包消息间隔约 65.5–131.3 ms | 未逐条反序列化确认；由同一处理链产生 |
| IMU | `/agt/sensors/imu/data` | 77909 | 约 200.00 Hz；header `1788268266.687048`–`1788268656.229968` | `livox_frame` |
| 底盘 odom | `/agt/chassis/odometry` | 39019 | 约 100 Hz；header `1788268266.127541`–`1788268656.223721` | `bunker_odom`, child `base_footprint` |
| TF | `/tf` | 0 | 无数据 | — |
| TF static | `/tf_static` | 1 | 单次 latched 发布 | 4 条静态边 |

LiDAR `CustomMsg` 含约 19,968–20,064 点/包，逐点 `offset_time` 例如每点约 4.947 µs，`timebase` 与第一点时间一致；满足 FAST-LIO/FAST-LIVO2 进行扫描内去畸变所需的逐点时间信息。

bag 写入时间相对消息 header 的延迟并非恒定零值。代表性统计为：

- IMU：平均约 **0.303 ms**，中位数 **0.205 ms**，最大约 **44.7 ms**；
- 底盘 odom：平均约 **0.421 ms**，中位数 **0.214 ms**，最大约 **147 ms**，且存在少量 header 时间非单调/异常间隔；
- LiDAR 首包约 **191 ms**、末包约 **106 ms** 的 bag-write/header 差值，显示启动/接收队列延迟；不能据此直接当作传感器时钟偏移。

结论：IMU/LiDAR 的频率和逐点时间满足 FAST-LIO 基本输入条件；但 `imu_time_offset=0` 尚未由硬件同步或运动相关分析证明，且录包显示接收延迟有启动瞬态。建议实际运行时使用传感器 header/timebase，并在稳定运动段估计固定时偏，而不是使用 bag 写入时间。

## Extrinsic Parameters

### `T_lidar_imu`

FAST-LIVO2 参数为：

```yaml
extrinsic_T: [0.011, 0.02329, -0.04412]
extrinsic_R: identity
```

从源码 `setImuToLidarExtrinsic()` 及点变换可知，这组参数实际被用于把 LiDAR 点变换到 IMU/body 坐标：`p_imu = R * p_lidar + T`。因此它不是“Base 到 LiDAR”的替代项。数值量级约 5.1 cm，作为 MID360 内部 LiDAR-IMU 杆臂是合理的；但它与 URDF 中 `lidar_link -> imu_link = identity` 不一致，存在重复/冲突表达：当前系统同时假定 IMU 与 LiDAR 原点重合，又在 FAST-LIVO2 内部使用非零杆臂。

IMU 消息 frame 是 `livox_frame`，而 FAST-LIVO2 参数没有自动从 TF 推导这组内部外参。必须明确选择一个权威来源，并保证另一处是等价表达；当前状态不应标记为已完成联合标定。

### `T_lidar_base`

当前 BUNKER 初值为 `base_link -> lidar_link`：

```text
t = [0.2615, 0.0000, 0.4070] m
rpy = [0.0064, 0.4045, 0.0000] rad
     = [0.37, 23.18, 0] deg
```

平移与仓库注释中的“LiDAR 中心离地约 0.607 m、base_link 高度暂定 0.200 m”一致，但 `calibration_verified=false`，x/y、base datum 和 yaw 尚未机械实测。

姿态存在风险：首尾各 1000 个 IMU 样本的平均加速度约 `[-0.254, -0.005, 0.960]` 和 `[-0.253, -0.009, 0.961]`（单位为消息量纲），由重力方向得到的简单倾角约 14.8°，与配置的 +23.2° 不一致。由于该段不具备独立“完全静止且已知坐标系”证明，不能仅凭此样本决定正负号；但它足以说明当前 +23.2° 不能直接视为已验证值。

ROS REP-103 下，正 pitch 会使传感器 +X 朝向 +Z 的相反方向（按右手绕 +Y 旋转）；因此必须结合 MID360 实物安装面和 RViz 轴检查，重点排除 pitch 符号反转、LiDAR 倒装 180°、以及把 `base_link -> lidar_link` 误填成逆变换。

## Recommended Parameters

当前建议结论：**输入频率通过，外参配置暂不通过最终验收**。`calibration_verified` 应保持 `false`。

1. 机械测量并冻结唯一的 `base_link -> lidar_link`：确认 base datum、x/y/z、roll/pitch/yaw；用 RViz 的 TF axes 和地面平面验证方向。持久化位置是 `src/agt_description/config/bunker_mid360.yaml`；URDF 由 `src/agt_description/launch/bunker_description.launch.py` 传入这些值，运行时只做临时覆盖。
2. 明确 `T_lidar_imu` 的坐标约定。若采用 FAST-LIVO2 的非零内部标定，则应让 `lidar_link -> imu_link` 的 TF 与同一物理结果一致，或在系统设计上明确 TF 仅表示 frame 命名重合且不再被算法重复使用；不要把 `[0.011,0.02329,-0.04412]` 同时当作 `base_link -> lidar_link`。
3. FAST-LIVO2 参数只在 `src/agt_odometry/config/mid360_lio_only.yaml` 的 `extrin_calib` 和 `time_offset.imu_time_offset` 修改；不要改第三方算法。建议先保留 `publish_tf=false`，由 `src/agt_odometry/launch/fast_livo2_odometry.launch.py` 的 adapter 唯一发布动态 odom TF。
4. 在 `src/agt_sensor_adapters/launch/mid360.launch.py` 保持驱动 `frame_id=livox_frame`，或未来统一改名时同步修改驱动、URDF、FAST-LIVO2 输出和所有测试；当前不建议引入 `mid360_link` 别名。
5. 底盘启动位于 `src/agt_chassis_bunker/launch/bunker.launch.py`。FAST-LIVO2 adapter 已发布 `odom -> base_footprint` 时，应将底盘 `publish_odom_tf` 关闭，或停用 adapter 的对应发布；同时统一底盘 odom message 的 `header.frame_id` 为 `odom`，否则 Nav2/定位链会看到 `bunker_odom` 与 `odom` 两套根 frame。
6. 录制下一段标定 bag 时，应包含实际使用的 `/agt/sensors/lidar/custom`、`/agt/sensors/imu/data`、`/tf_static` 以及 FAST-LIO 输出；保持 `use_sim_time=false`，并在启动后等待静态 TF 发布完成。对稳定运动段做 LiDAR-IMU 时偏估计，目标是固定 offset，而不是用 bag 写入延迟替代 `imu_time_offset`。

本次检查没有修改任何现有代码或配置；本报告是唯一新增文件。

## Tracked Chassis Description Re-check

补充检查对象：`tracked_chassis_description_fixed/`。该描述比仓库原有简化 Xacro 更接近实际上车模型：它保留了 SolidWorks CAD 座标系、MID360 CAD 安装座，并将实际 LiDAR 标定作为独立 residual 层。

其默认文件为 `config/cad_alignment.initial_guess.yaml`，当前仍是候选值：`calibration_verified=false`、`candidate_only=true`。实际链为：

```text
base_footprint
└── base_link
    └── chassis_cad_link
        └── lidar_mount_link
            └── lidar_link
                ├── livox_frame
                └── imu_link
```

当 `lidar_mount_to_lidar` 为 identity 时，按当前 YAML 合成得到：

```text
base_link -> lidar_link
translation ~= [0.406075, 0.000000, 0.727468] m
rpy         ~= [0, 0.226893, 0] rad = [0, 13.0, 0] deg
```

其中包含：

- `base_link -> chassis_cad_link`: `[0.247951, 0, 0.623786] m`；
- `chassis_cad_link -> lidar_mount_link`: `[0.158124, 0, 0.103682] m`，pitch `13.0°`；
- `lidar_mount_link -> lidar_link`: 当前 identity residual。

这意味着不能把旧描述中的 `[0.2615, 0, 0.4070] m / 23.2°` 直接写入新模型；两者的参考原点不同，且新模型已经把 CAD 安装关系分层表达。

### Bag effect check

对指定 bag 的 LiDAR 首帧和 IMU 首尾各 1000 个样本做了支持性检查：

- LiDAR `CustomMsg` 的 `header.frame_id` 为 `livox_frame`，`timebase` 与首点时间一致，约 10 Hz；
- IMU `header.frame_id` 为 `livox_frame`，约 200 Hz；
- IMU 首 1000 点平均加速度约 `[-0.2549, -0.0046, 0.9600]`，由重力方向得到的简化倾角约 `14.87°`；末 1000 点约 `[-0.2534, -0.0092, 0.9606]`，倾角约 `14.78°`；
- 新 description 的 CAD nominal pitch `13.0°` 与该重力倾角相差约 `1.8°`，方向和量级上明显比旧的 `23.2°` 更一致。

这不是完整的 six-DoF 联合优化结果：该 bag 没有已知地面/标靶坐标、没有动态 `/tf`，且机器人在采集期间有运动。因此目前只能判定“新 CAD 外参初值得到 bag 重力方向的较好支持”，不能从此 bag 单独可靠估计 yaw、x/y 杆臂或 LiDAR-IMU 细小平移。

第一帧 LiDAR 做无先验平面 RANSAC 时得到过约 22° 倾斜的高支持平面，但它可能是场景中的墙面/斜面，不能直接当作地面标定结果；这也是本次不把该值写回 YAML 的原因。

### Updated recommendation

后续应以 `tracked_chassis_description_fixed/config/cad_alignment.initial_guess.yaml` 为外参分层的主候选源：优先保留 CAD nominal，实车 LiDAR 校正写入 `lidar_mount_to_lidar`。FAST-LIVO2 的 `extrin_calib` 仍需单独与其内部 LiDAR-IMU 坐标约定对齐，不能因为 `lidar_link -> imu_link` 在 URDF 中为 identity 就自动认为内部 IMU 外参已经完成。
