# AGT vendored Vikit snapshot

- Upstream: `https://github.com/Rhymer-Lcy/rpg_vikit_ros2_fisheye.git`
- Fixed commit: `fee3d50ae2af472fb27eb62b4526dd4b32ede8ef`
- Imported packages: `vikit_common`, `vikit_ros`
- Upstream lineage and fisheye changes: see `README.md`

The unused `vikit_py` package, nested Git metadata, backup files, and the
upstream stray `ername` file are intentionally excluded. This snapshot is
built in the same workspace as FAST-LIVO so a legacy workspace overlay is not
required.

Local build integration changes:

- declare `ament_cmake` as the `vikit_common` build type;
- remove obsolete `cmake_modules` package dependencies because this source
  already carries the required CMake module;
- keep x86 builds on a generic alignment ABI (`-march=x86-64`) while allowing
  instruction scheduling through `-mtune=native`.

The upstream repository does not provide a standalone LICENSE/COPYING file at
the fixed commit. Both imported package manifests declare `GPLv3`. Preserve
their copyright notices and treat standalone license-text/provenance review as
an explicit release-blocking item; this file does not replace that review.
