# agt_sensor_adapters

将传感器原生输出转换到统一 AGT 接口。当前已迁入旧仓库验证过的
`livox_ros_driver2`，并提供 MID360 启动入口：

```bash
ros2 launch agt_sensor_adapters mid360.launch.py
```

统一输出：

- `/agt/sensors/lidar/custom`：`livox_ros_driver2/msg/CustomMsg`，保留每点
  `offset_time/line/tag`，供 FAST-LIVO2 使用。
- `/agt/sensors/imu/data`：MID360 内置 IMU，frame 为 `livox_frame`。

这里有意使用 `xfer_format=1` 的 Livox 原生消息。选定的
`Aldoubt/FASTLIVO2_ROS2@a713004` 只有 Livox `CustomMsg` 路径会使用每点时间、线号和
回波标签；它没有 MID360 PointCloud2 handler。PointCloud2 仍作为 V2 注册点云等通用
输出格式，不作为该后端的原始输入。

网络配置填写在 `config/mid360_network.json`。当前实车基线为：主机网卡
`192.168.1.5/24`，MID360 `192.168.1.157`。主机应使用独立有线网卡配置该静态地址，
无线网卡继续负责 Web/局域网访问，不要为传感器网卡设置默认网关：

```bash
nmcli connection show
sudo nmcli connection modify "<MID360有线连接名>" \
  ipv4.method manual ipv4.addresses 192.168.1.5/24 \
  ipv4.gateway "" ipv4.dns "" ipv4.never-default yes ipv6.method disabled
sudo nmcli connection down "<MID360有线连接名>"
sudo nmcli connection up "<MID360有线连接名>"
ip route get 192.168.1.157
ping -I <MID360网卡名> -c 4 192.168.1.157
```

`ip route get` 必须显示 `src 192.168.1.5` 和 MID360 有线网卡。更换网卡或雷达后，
同时修改该 JSON 的 `host_net_info` 地址和 `lidar_configs[0].ip`，不要修改第三方
驱动目录。设备配置中的 extrinsic 保持全零；机器人安装外参只填写在
`agt_description/config/bunker_mid360.yaml` 或 `mk_mini_mid360.yaml`，避免两处重复补偿。

启动入口支持显式选择配置文件：

```bash
ros2 launch agt_sensor_adapters mid360.launch.py \
  user_config_path:="$(realpath src/agt_sensor_adapters/config/mid360_network.json)" \
  publish_freq:=10.0 frame_id:=livox_frame use_sim_time:=false
```

启动前会检查 JSON 文件存在；实车启动后必须确认 `/agt/sensors/lidar/custom` 和
`/agt/sensors/imu/data` 正在发布。

离线只能验证构建、launch 和配置格式。实机后需检查 topic、QoS、点云/IMU 频率、
时间戳、丢包和 frame，再将结果记录到根 README 的模块验收清单。
