#pragma once
#include <nlohmann/json.hpp>
#include "topology_map.h"

struct CaptureView {
  std::string id;
  double pan_deg{0.0};
  double tilt_deg{-10.0};
  double timeout_s{5.0};
  double settle_duration_s{0.5};
};

struct CaptureGroup {
  bool enabled{false};
  std::string task_id{"inspection_route_01"};
  std::string camera_id{"inspection_camera"};
  bool save_image{true};
  std::vector<CaptureView> views;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    CaptureView, id, pan_deg, tilt_deg, timeout_s, settle_duration_s)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    CaptureGroup, enabled, task_id, camera_id, save_image, views)

struct TaskChain {
  std::vector<TopologyMap::PointInfo> points;
  CaptureGroup capture_group;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(TaskChain, points, capture_group);
