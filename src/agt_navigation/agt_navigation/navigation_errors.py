from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class Blocker:
    code: str
    operator_message: str
    technical_message: str
    error_code: int = 0


_OPERATOR_MESSAGES = {
    "NO_ACTIVE_MAP": "尚未激活可执行地图，请先激活 READY 地图版本。",
    "MAP_NOT_READY": "当前地图尚未准备完成，请先登记并激活 READY 地图版本。",
    "MAP_VERSION_MISMATCH": "任务属于其他地图版本，请切换地图或重新绑定任务。",
    "MAP_GEOMETRY_MISMATCH": "任务地图几何与当前地图不一致，请复制到当前地图后重新校验。",
    "MAP_YAML_HASH_MISMATCH": "地图 YAML 内容与任务绑定不一致，请重新登记或重新绑定任务。",
    "MAP_IMAGE_HASH_MISMATCH": "地图栅格内容与任务绑定不一致，请重新登记或重新绑定任务。",
    "LOCALIZATION_PCD_HASH_MISSING": "定位地图尚未准备完成，请重新生成或登记地图版本。",
    "LOCALIZATION_PCD_HASH_MISMATCH": "定位地图与当前任务绑定不一致，请重新激活正确地图版本。",
    "TASK_NOT_FOUND": "机器人端没有找到该任务，请先同步任务。",
    "TASK_REVISION_CONFLICT": "任务版本已变化，请刷新任务后再执行。",
    "TASK_CONTENT_HASH_MISMATCH": "任务内容校验失败，请重新保存并同步任务。",
    "TASK_SCHEMA_INVALID": "任务文件格式无效，请修正任务后重新保存。",
    "TASK_MAP_BINDING_MISMATCH": "任务地图绑定与当前地图不一致，请重新绑定任务。",
    "TASK_NOT_SYNCED": "任务尚未同步到机器人。",
    "LOCALIZATION_NOT_READY": "定位尚未就绪，请完成重定位并确认跟踪状态。",
    "LOCALIZATION_STATUS_STALE": "定位状态已过期，请确认定位节点仍在运行。",
    "TASK_READINESS_NOT_READY": "系统任务门禁未就绪，请查看系统状态阻塞原因。",
    "SAFETY_NOT_READY": "安全链路尚未允许导航，请确认安全控制器和运动使能。",
    "ESTOP_LATCHED": "急停已触发或锁存，请解除急停后再执行。",
    "NAV2_UNAVAILABLE": "Nav2 多点导航服务不可用，请检查导航链启动状态。",
    "TASK_ALREADY_ACTIVE": "已有任务正在执行，请等待完成或取消后再提交。",
    "DUPLICATE_REQUEST": "重复请求已收到，机器人不会启动第二个任务。",
    "INVALID_REQUEST": "任务请求无效，请刷新界面后重试。",
    "LEGACY_TASK_FILE_DISABLED": "本地任务文件执行入口已弃用，请使用任务同步后执行。",
    "NAV2_REJECTED": "Nav2 拒绝了任务，请检查导航链状态。",
    "NAV2_FAILED": "任务执行失败，请查看诊断详情。",
    "CANCELED": "任务已取消。",
}


def blocker(code: str, technical_message: str = "", *, error_code: int = 0) -> Blocker:
    normalized = code.strip().upper() or "INVALID_REQUEST"
    return Blocker(
        code=normalized,
        operator_message=_OPERATOR_MESSAGES.get(normalized, _OPERATOR_MESSAGES["INVALID_REQUEST"]),
        technical_message=technical_message or normalized,
        error_code=error_code,
    )

