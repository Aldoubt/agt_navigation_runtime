import json

from agt_mission_manager.mission_model import (
    MapBinding,
    Mission,
    MissionRuntimeStatus,
    MissionState,
    MissionStep,
    StepType,
)
from agt_mission_manager.mission_report import MissionReportWriter


HASH = "sha256:" + "a" * 64
INSPECTION_HASH = "sha256:" + "b" * 64
HOME_HASH = "sha256:" + "c" * 64


def _mission():
    return Mission(
        mission_id="flower_inspection",
        mission_version="v1",
        content_sha256=HASH,
        map_binding=MapBinding("mock_map", "v1", HASH),
        steps=(
            MissionStep(
                "inspect",
                StepType.INSPECTION_TASK,
                inspection_task_id="inspection_01",
                inspection_task_revision=1,
                expected_content_sha256=INSPECTION_HASH,
            ),
            MissionStep(
                "return_home",
                StepType.RETURN_HOME,
                task_group_id="home_mock",
                task_group_revision=1,
                expected_content_sha256=HOME_HASH,
            ),
        ),
    )


def test_report_links_inspection_evidence_and_labels_point_sum_estimate(tmp_path):
    evidence_root = tmp_path / "inspection_evidence"
    report_root = evidence_root / "report"
    report_root.mkdir(parents=True)
    (report_root / "report.json").write_text(
        json.dumps(
            {
                "schema_version": 1,
                "session_id": "inspection_session_01",
                "inspection_task_id": "inspection_01",
                "count_target": "litchi_flower",
                "count_mode": "POINT_DEDUP",
                "totals": {
                    "raw_instance_count": 18,
                    "unique_instance_count": 12,
                    "ambiguous_instance_count": 2,
                },
            }
        ),
        encoding="utf-8",
    )

    writer = MissionReportWriter(tmp_path / "mission_reports", run_id="run_001")
    writer.start(_mission())
    writer.record_step(
        index=0,
        step=_mission().steps[0],
        success=True,
        message="inspection completed",
        session_id="inspection_session_01",
        artifact_uri=str(evidence_root),
    )
    writer.record_step(
        index=1,
        step=_mission().steps[1],
        success=True,
        message="home reached",
    )
    status = MissionRuntimeStatus.for_mission(_mission())
    status.state = MissionState.SUCCEEDED
    status.message = "mission completed"
    report_uri = writer.finish(status)

    report = json.loads((tmp_path / "mission_reports" / "flower_inspection" / "run_001" / "report.json").read_text(encoding="utf-8"))
    assert report_uri.endswith("report.json")
    assert report["state"] == "SUCCEEDED"
    assert report["home_returned"] is True
    assert report["inspection_summary"]["raw_instance_count"] == 18
    assert report["inspection_summary"]["point_sum_estimate"] == 12
    assert report["inspection_summary"]["ambiguous_instance_count"] == 2
    assert "global_unique_count" not in report["inspection_summary"]
    assert report["inspection_summary"]["count_semantics"] == "POINT_SUM_ESTIMATE"
    assert report["steps"][0]["artifact_uri"] == str(evidence_root)
    assert (tmp_path / "mission_reports" / "flower_inspection" / "run_001" / "steps.csv").is_file()
    assert (tmp_path / "mission_reports" / "flower_inspection" / "run_001" / "inspections.csv").is_file()
