# Third-party notices

`agt_navigation_v2` is a multi-license aggregate. The root Apache-2.0
[`LICENSE`](LICENSE) applies only to project-owned material unless a file or directory
states otherwise. It does not replace or narrow any third-party copyright notice or
license.

This inventory records the principal components known to the current source tree. It
is not a complete binary SBOM: every release must regenerate an inventory from the
actual source commits, system packages, FetchContent downloads, container layers,
firmware, datasets and model weights being delivered.

## Vendored source

| Component | Local source | Recorded license | Upstream |
| --- | --- | --- | --- |
| FAST-LIVO2 ROS 2 | `third_party/fast_livo2_ros2` | GPL-2.0; local package metadata normalizes this conservatively as `GPL-2.0-only` | [HKU-MARS original](https://github.com/hku-mars/FAST-LIVO2), [ROS 2 fork](https://github.com/SuperLDG/FAST-LIVO2) |
| rpg_vikit ROS 2 fisheye | `third_party/rpg_vikit_ros2_fisheye` | Package manifests declare GPLv3; fixed upstream snapshot has no standalone LICENSE/COPYING file | [Rhymer-Lcy fork](https://github.com/Rhymer-Lcy/rpg_vikit_ros2_fisheye), [UZH-RPG lineage](https://github.com/uzh-rpg/rpg_vikit) |
| Livox ROS Driver 2 | `third_party/livox_ros_driver2` | MIT for the files identified by its license manifest; bundled and external SDK material must be checked separately | [Livox-SDK](https://github.com/Livox-SDK/livox_ros_driver2) |
| BUNKER ROS 2 | `third_party/bunker_ros2` | Top-level Apache-2.0 text; package manifests state BSD and require provenance reconciliation before product release | [AgileX Robotics](https://github.com/agilexrobotics/bunker_ros2) |
| ugv_sdk | `third_party/ugv_sdk` | Top-level Apache-2.0 text; package metadata states BSD and requires provenance reconciliation before product release | [Weston Robot](https://github.com/westonrobot/ugv_sdk) |
| ndt_omp ROS 2 | `third_party/ndt_omp_ros2` | BSD-2-Clause plus preserved PCL contributor notices | [koide3/ndt_omp](https://github.com/koide3/ndt_omp) |
| ROS Qt5 GUI App maintained fork | `third_party/ros_qt5_gui_app` | GPL-2.0; bundled/fetched libraries retain their own licenses | [chengyangkj](https://github.com/chengyangkj/Ros_Qt5_Gui_App) |
| relocalization_core imported module | `third_party/relocalization_core` | Apache-2.0 | Local license file |

Do not remove the license files, copyright headers or modification history within
these directories. A modified GPL binary delivered to another party must be matched
with the complete corresponding source and other materials required by its applicable
GPL version.

## Commit-pinned external coverage workspace

[`nav_dependencies.repos`](nav_dependencies.repos) records the authoritative source
commits used by the separate coverage workspace:

| Component | Recorded license |
| --- | --- |
| Open Navigation Coverage | Apache-2.0 |
| Fields2Cover | BSD-3-Clause |
| steering_functions | Apache-2.0, with separate third-party notices |
| Matplot++ | MIT |
| nlohmann/json | MIT, with its repository's additional per-file notices |

ROS 2, Navigation2, Qt, OctoMap, PCL, Eigen, OpenCV, Shapely and other system or
transitive dependencies are not vendored completely here. Their exact installed
versions and license payloads must be included in a product release audit.

## Known release blockers

- FAST-LIVO2's GPLv2 declaration and the currently selected Vikit packages' GPLv3
  declaration require upstream clarification, compatible relicensing, or dependency
  replacement before distributing their linked build product.
- The Vikit snapshot lacks a standalone license text at the fixed upstream commit.
- BUNKER ROS 2 and ugv_sdk have inconsistent top-level license texts and package
  metadata.
- The modified GPL-2.0 Qt GUI cannot be delivered as a proprietary-only binary without
  a separate permission or replacement. Qt's own LGPL/GPL/commercial terms remain an
  additional, independent obligation.

This file is an engineering provenance record, not legal advice or a substitute for
review of the controlling license texts.
