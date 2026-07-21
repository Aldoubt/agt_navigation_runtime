# msg

统一状态、能力描述和模块健康消息目录。

- `LocalizationStatus.msg`：定位状态、错误码、候选统计和质量字段。`pose_valid` 表示已经通过
  项目质量门禁的全局定位；`has_converged` 只表示配准后端收敛，二者不能混用。

`candidate_source` 是对比实验的稳定分组键：手动 `/initialpose` 固定为
`manual_initialpose`，Action 显式初值固定为 `action_initial_pose`，其他来源使用
`last_valid_pose`、`configured` 或 `external_coarse_pose`。
