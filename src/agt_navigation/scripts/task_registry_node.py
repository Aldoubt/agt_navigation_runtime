#!/usr/bin/env python3

from pathlib import Path

from agt_interfaces.srv import (
    ArchiveTaskGroup,
    GetTaskGroup,
    ListTaskGroups,
    PutTaskGroup,
)
from agt_navigation.task_registry import TaskRegistry, TaskRegistryError
import rclpy
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node


_ERROR_BY_CODE = {
    "INVALID_REQUEST": 1,
    "TASK_NOT_FOUND": 2,
    "TASK_REVISION_CONFLICT": 3,
    "TASK_CONTENT_HASH_MISMATCH": 3,
    "TASK_SCHEMA_INVALID": 4,
    "MAP_NOT_READY": 5,
    "MAP_VERSION_MISMATCH": 5,
    "TASK_MAP_BINDING_MISMATCH": 5,
    "TASK_NOT_SYNCED": 255,
}


class TaskRegistryNode(Node):
    def __init__(self) -> None:
        super().__init__("agt_task_registry")
        runtime_dir = Path(str(self.declare_parameter("runtime_dir", "runtime").value)).expanduser()
        maps_root_value = str(self.declare_parameter("maps_root", "").value).strip()
        maps_root = Path(maps_root_value).expanduser() if maps_root_value else runtime_dir / "maps"
        self._registry = TaskRegistry(
            maps_root,
            maximum_task_bytes=int(self.declare_parameter("maximum_task_bytes", 1024 * 1024).value),
            backup_count=int(self.declare_parameter("backup_count", 5).value),
            recent_request_limit=int(self.declare_parameter("recent_request_limit", 256).value),
        )
        group = MutuallyExclusiveCallbackGroup()
        self.create_service(ListTaskGroups, "/agt/navigation/tasks/list", self._list, callback_group=group)
        self.create_service(GetTaskGroup, "/agt/navigation/tasks/get", self._get, callback_group=group)
        self.create_service(PutTaskGroup, "/agt/navigation/tasks/put", self._put, callback_group=group)
        self.create_service(ArchiveTaskGroup, "/agt/navigation/tasks/archive", self._archive, callback_group=group)

    @staticmethod
    def _fill_error(response, exc: TaskRegistryError):
        problem = exc.problem
        response.success = False
        response.error_code = int(_ERROR_BY_CODE.get(problem.code, 255))
        response.blocker_code = problem.code
        response.operator_message = problem.operator_message
        response.technical_message = problem.technical_message
        return response

    def _list(self, request, response):
        try:
            tasks = self._registry.list_tasks(str(request.map_id), str(request.map_version_id))
            response.success = True
            response.error_code = ListTaskGroups.Response.ERROR_NONE
            response.map_id = str(request.map_id)
            response.map_version_id = str(request.map_version_id)
            response.task_group_ids = [task.task_group_id for task in tasks]
            response.names = [task.name for task in tasks]
            response.revisions = [int(task.revision) for task in tasks]
            response.content_sha256 = [task.content_sha256 for task in tasks]
            response.enabled_point_counts = [len(task.enabled_points) for task in tasks]
            response.updated_at = [task.updated_at for task in tasks]
            response.validation_states = ["VALID" for _task in tasks]
        except TaskRegistryError as exc:
            self._fill_error(response, exc)
        except Exception as exc:
            response.success = False
            response.error_code = ListTaskGroups.Response.ERROR_INTERNAL
            response.blocker_code = "TASK_NOT_SYNCED"
            response.operator_message = "任务仓库暂时不可用。"
            response.technical_message = str(exc)
        return response

    def _get(self, request, response):
        try:
            stored = self._registry.get_task(
                str(request.map_id),
                str(request.map_version_id),
                str(request.task_group_id),
                int(request.task_revision),
            )
            response.success = True
            response.error_code = GetTaskGroup.Response.ERROR_NONE
            response.map_id = stored.task.map_binding.map_id
            response.map_version_id = stored.task.map_binding.map_version_id
            response.task_group_id = stored.task.task_group_id
            response.revision = int(stored.task.revision)
            response.content_sha256 = stored.task.content_sha256
            response.task_json = stored.task_json
        except TaskRegistryError as exc:
            self._fill_error(response, exc)
        except Exception as exc:
            response.success = False
            response.error_code = GetTaskGroup.Response.ERROR_INTERNAL
            response.blocker_code = "TASK_NOT_SYNCED"
            response.operator_message = "任务仓库暂时不可用。"
            response.technical_message = str(exc)
        return response

    def _put(self, request, response):
        try:
            result = self._registry.put_task(
                str(request.task_json),
                map_id=str(request.map_id),
                map_version_id=str(request.map_version_id),
                task_group_id=str(request.task_group_id),
                expected_revision=int(request.expected_revision),
                client_request_id=str(request.client_request_id),
            )
            response.success = True
            response.error_code = PutTaskGroup.Response.ERROR_NONE
            response.duplicate_request = result.duplicate_request
            response.map_id = result.task.map_binding.map_id
            response.map_version_id = result.task.map_binding.map_version_id
            response.task_group_id = result.task.task_group_id
            response.revision = int(result.task.revision)
            response.content_sha256 = result.task.content_sha256
            response.task_json = result.task_json
        except TaskRegistryError as exc:
            self._fill_error(response, exc)
        except Exception as exc:
            response.success = False
            response.error_code = PutTaskGroup.Response.ERROR_INTERNAL
            response.blocker_code = "TASK_NOT_SYNCED"
            response.operator_message = "任务尚未同步到机器人。"
            response.technical_message = str(exc)
        return response

    def _archive(self, request, response):
        try:
            result = self._registry.archive_task(
                str(request.map_id),
                str(request.map_version_id),
                str(request.task_group_id),
                expected_revision=int(request.expected_revision),
                client_request_id=str(request.client_request_id),
            )
            response.success = True
            response.error_code = ArchiveTaskGroup.Response.ERROR_NONE
            response.duplicate_request = result.duplicate_request
            response.map_id = result.map_id
            response.map_version_id = result.map_version_id
            response.task_group_id = result.task_group_id
            response.archived_revision = int(result.archived_revision)
            response.archived_relative_path = result.archived_relative_path
        except TaskRegistryError as exc:
            self._fill_error(response, exc)
        except Exception as exc:
            response.success = False
            response.error_code = ArchiveTaskGroup.Response.ERROR_INTERNAL
            response.blocker_code = "TASK_NOT_SYNCED"
            response.operator_message = "任务归档失败。"
            response.technical_message = str(exc)
        return response


def main(args=None) -> None:
    rclpy.init(args=args)
    node = TaskRegistryNode()
    executor = MultiThreadedExecutor(num_threads=2)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
