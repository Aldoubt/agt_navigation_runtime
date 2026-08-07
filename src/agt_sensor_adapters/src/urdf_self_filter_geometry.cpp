#include "agt_sensor_adapters/urdf_self_filter_geometry.hpp"

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

#include <urdf/model.h>

namespace agt_sensor_adapters
{
namespace
{

void require_finite(double value, const std::string & path)
{
  if (!std::isfinite(value)) {
    throw std::runtime_error(path + " must be finite");
  }
}

void require_positive(double value, const std::string & path)
{
  require_finite(value, path);
  if (value <= 0.0) {
    throw std::runtime_error(path + " must be > 0");
  }
}

UrdfCollisionPrimitive parse_collision(
  const urdf::LinkSharedPtr & link, const urdf::CollisionSharedPtr & collision,
  std::size_t collision_index)
{
  if (!link || !collision || !collision->geometry) {
    throw std::runtime_error("URDF contains an empty collision entry");
  }

  UrdfCollisionPrimitive primitive;
  primitive.name = link->name + "/collision_" + std::to_string(collision_index);
  primitive.link_name = link->name;

  const auto & origin = collision->origin;
  primitive.origin_xyz = {
    origin.position.x,
    origin.position.y,
    origin.position.z,
  };
  primitive.origin_xyzw = {
    origin.rotation.x,
    origin.rotation.y,
    origin.rotation.z,
    origin.rotation.w,
  };
  for (std::size_t index = 0; index < primitive.origin_xyz.size(); ++index) {
    require_finite(
      primitive.origin_xyz[index], primitive.name + ".origin_xyz[" + std::to_string(index) + "]");
  }
  for (std::size_t index = 0; index < primitive.origin_xyzw.size(); ++index) {
    require_finite(
      primitive.origin_xyzw[index],
      primitive.name + ".origin_xyzw[" + std::to_string(index) + "]");
  }
  const double quaternion_norm = std::sqrt(
    primitive.origin_xyzw[0] * primitive.origin_xyzw[0] +
    primitive.origin_xyzw[1] * primitive.origin_xyzw[1] +
    primitive.origin_xyzw[2] * primitive.origin_xyzw[2] +
    primitive.origin_xyzw[3] * primitive.origin_xyzw[3]);
  if (!(quaternion_norm > 0.0) || !std::isfinite(quaternion_norm)) {
    throw std::runtime_error(primitive.name + ".origin quaternion must be non-zero and finite");
  }
  for (auto & value : primitive.origin_xyzw) {
    value /= quaternion_norm;
  }

  switch (collision->geometry->type) {
    case urdf::Geometry::BOX: {
      const auto & box = static_cast<const urdf::Box &>(*collision->geometry);
      require_positive(box.dim.x, primitive.name + ".box.x");
      require_positive(box.dim.y, primitive.name + ".box.y");
      require_positive(box.dim.z, primitive.name + ".box.z");
      primitive.type = UrdfPrimitiveType::BOX;
      primitive.dimensions = {box.dim.x, box.dim.y, box.dim.z};
      break;
    }
    case urdf::Geometry::SPHERE: {
      const auto & sphere = static_cast<const urdf::Sphere &>(*collision->geometry);
      require_positive(sphere.radius, primitive.name + ".sphere.radius");
      primitive.type = UrdfPrimitiveType::SPHERE;
      primitive.dimensions = {sphere.radius, 0.0, 0.0};
      break;
    }
    case urdf::Geometry::CYLINDER: {
      const auto & cylinder = static_cast<const urdf::Cylinder &>(*collision->geometry);
      require_positive(cylinder.radius, primitive.name + ".cylinder.radius");
      require_positive(cylinder.length, primitive.name + ".cylinder.length");
      primitive.type = UrdfPrimitiveType::CYLINDER;
      primitive.dimensions = {cylinder.radius, cylinder.length, 0.0};
      break;
    }
    case urdf::Geometry::MESH:
      throw std::runtime_error(
        primitive.name +
        " uses mesh collision geometry; add a primitive collision proxy for the realtime self-filter");
    default:
      throw std::runtime_error(primitive.name + " uses an unsupported URDF collision geometry type");
  }

  return primitive;
}

}  // namespace

bool UrdfCollisionPrimitive::contains_local(
  const std::array<double, 3> & point, double padding) const
{
  if (!std::isfinite(padding) || padding < 0.0) {
    return false;
  }
  if (!std::isfinite(point[0]) || !std::isfinite(point[1]) || !std::isfinite(point[2])) {
    return false;
  }

  switch (type) {
    case UrdfPrimitiveType::BOX:
      return std::abs(point[0]) <= dimensions[0] / 2.0 + padding &&
             std::abs(point[1]) <= dimensions[1] / 2.0 + padding &&
             std::abs(point[2]) <= dimensions[2] / 2.0 + padding;
    case UrdfPrimitiveType::SPHERE: {
      const double radius = dimensions[0] + padding;
      return point[0] * point[0] + point[1] * point[1] + point[2] * point[2] <=
             radius * radius;
    }
    case UrdfPrimitiveType::CYLINDER: {
      const double radius = dimensions[0] + padding;
      const double half_length = dimensions[1] / 2.0 + padding;
      return point[0] * point[0] + point[1] * point[1] <= radius * radius &&
             std::abs(point[2]) <= half_length;
    }
  }
  return false;
}

UrdfSelfFilterGeometry parse_urdf_self_filter_geometry(const std::string & robot_description)
{
  if (robot_description.empty()) {
    throw std::runtime_error("robot_description is empty");
  }

  urdf::Model model;
  if (!model.initString(robot_description)) {
    throw std::runtime_error("failed to parse robot_description as URDF");
  }

  std::vector<urdf::LinkSharedPtr> links;
  model.getLinks(links);

  UrdfSelfFilterGeometry result;
  for (const auto & link : links) {
    if (!link) {
      continue;
    }
    std::vector<urdf::CollisionSharedPtr> collisions = link->collision_array;
    if (collisions.empty() && link->collision) {
      collisions.push_back(link->collision);
    }
    for (std::size_t index = 0; index < collisions.size(); ++index) {
      result.primitives.push_back(parse_collision(link, collisions[index], index));
    }
  }

  if (result.primitives.empty()) {
    throw std::runtime_error("robot_description contains no supported collision geometry");
  }
  return result;
}

}  // namespace agt_sensor_adapters
