#pragma once

#include <array>
#include <string>
#include <vector>

namespace agt_sensor_adapters
{

enum class UrdfPrimitiveType
{
  BOX,
  SPHERE,
  CYLINDER,
};

struct UrdfCollisionPrimitive
{
  std::string name;
  std::string link_name;
  UrdfPrimitiveType type{UrdfPrimitiveType::BOX};

  // BOX: {x, y, z}; SPHERE: {radius, 0, 0}; CYLINDER: {radius, length, 0}.
  std::array<double, 3> dimensions{};

  // URDF collision origin: transform from geometry-local frame into link frame.
  std::array<double, 3> origin_xyz{};
  std::array<double, 4> origin_xyzw{0.0, 0.0, 0.0, 1.0};

  bool contains_local(const std::array<double, 3> & point, double padding) const;
};

struct UrdfSelfFilterGeometry
{
  std::vector<UrdfCollisionPrimitive> primitives;
};

// Parse primitive URDF collision geometry from robot_description. Mesh collision
// geometry is intentionally rejected: the realtime self-filter requires an
// explicit box/sphere/cylinder proxy rather than silently under-filtering a mesh.
UrdfSelfFilterGeometry parse_urdf_self_filter_geometry(const std::string & robot_description);

}  // namespace agt_sensor_adapters
