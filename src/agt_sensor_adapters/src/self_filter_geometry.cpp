#include "agt_sensor_adapters/self_filter_geometry.hpp"

#include <cmath>
#include <filesystem>
#include <stdexcept>

#include <yaml-cpp/yaml.h>

namespace agt_sensor_adapters
{
namespace
{

const YAML::Node require_node(const YAML::Node & parent, const char * key, const std::string & path)
{
  const auto node = parent[key];
  if (!node) {
    throw std::runtime_error(path + " is required");
  }
  return node;
}

double finite_number(const YAML::Node & node, const std::string & path)
{
  if (!node || !node.IsScalar()) {
    throw std::runtime_error(path + " must be a finite number");
  }
  double value = 0.0;
  try {
    value = node.as<double>();
  } catch (const YAML::Exception & error) {
    throw std::runtime_error(path + " must be a finite number: " + std::string(error.what()));
  }
  if (!std::isfinite(value)) {
    throw std::runtime_error(path + " must be finite");
  }
  return value;
}

bool boolean_value(const YAML::Node & node, const std::string & path)
{
  if (!node || !node.IsScalar()) {
    throw std::runtime_error(path + " must be boolean");
  }
  try {
    return node.as<bool>();
  } catch (const YAML::Exception & error) {
    throw std::runtime_error(path + " must be boolean: " + std::string(error.what()));
  }
}

std::array<double, 3> vector3(const YAML::Node & node, const std::string & path)
{
  if (!node || !node.IsSequence() || node.size() != 3) {
    throw std::runtime_error(path + " must contain exactly three values");
  }
  std::array<double, 3> result{};
  for (std::size_t index = 0; index < result.size(); ++index) {
    result[index] = finite_number(node[index], path + "[" + std::to_string(index) + "]");
  }
  return result;
}

AxisAlignedBox parse_box(const YAML::Node & node, const std::string & path)
{
  if (!node || !node.IsMap()) {
    throw std::runtime_error(path + " must be a mapping");
  }
  const auto name_node = require_node(node, "name", path + ".name");
  if (!name_node.IsScalar() || name_node.as<std::string>().empty()) {
    throw std::runtime_error(path + ".name must be a non-empty string");
  }
  AxisAlignedBox box;
  box.name = name_node.as<std::string>();
  box.min = vector3(require_node(node, "min", path + ".min"), path + ".min");
  box.max = vector3(require_node(node, "max", path + ".max"), path + ".max");
  for (std::size_t index = 0; index < box.min.size(); ++index) {
    if (!(box.min[index] < box.max[index])) {
      throw std::runtime_error(
        path + " requires min[" + std::to_string(index) + "] < max[" + std::to_string(index) + "]");
    }
  }
  box.verified = boolean_value(require_node(node, "verified", path + ".verified"), path + ".verified");
  const auto note = node["note"];
  if (note) {
    if (!note.IsScalar()) {
      throw std::runtime_error(path + ".note must be a string");
    }
    box.note = note.as<std::string>();
  }
  return box;
}

}  // namespace

bool AxisAlignedBox::contains(const std::array<double, 3> & point) const
{
  return point[0] >= min[0] && point[0] <= max[0] &&
         point[1] >= min[1] && point[1] <= max[1] &&
         point[2] >= min[2] && point[2] <= max[2];
}

AxisAlignedBox AxisAlignedBox::expanded(double padding) const
{
  AxisAlignedBox result = *this;
  for (std::size_t index = 0; index < result.min.size(); ++index) {
    result.min[index] -= padding;
    result.max[index] += padding;
  }
  return result;
}

bool SelfFilterGeometry::contains(const std::array<double, 3> & point) const
{
  for (const auto & box : boxes) {
    if (box.contains(point)) {
      return true;
    }
  }
  return false;
}

std::vector<AxisAlignedBox> SelfFilterGeometry::expanded_boxes() const
{
  std::vector<AxisAlignedBox> result;
  result.reserve(boxes.size());
  for (const auto & box : boxes) {
    result.push_back(box.expanded(padding));
  }
  return result;
}

std::vector<AxisAlignedBox> SelfFilterGeometry::expanded_supplemental_boxes() const
{
  std::vector<AxisAlignedBox> result;
  for (const auto & box : boxes) {
    if (!box.generated_from_platform_body) {
      result.push_back(box.expanded(padding));
    }
  }
  return result;
}

bool SelfFilterGeometry::has_unverified_box() const
{
  for (const auto & box : boxes) {
    if (!box.verified) {
      return true;
    }
  }
  return false;
}

SelfFilterGeometry load_self_filter_geometry(const std::string & profile_path)
{
  if (profile_path.empty()) {
    throw std::runtime_error("platform_profile must be a non-empty file path");
  }
  const std::filesystem::path path(profile_path);
  if (!std::filesystem::is_regular_file(path)) {
    throw std::runtime_error("platform_profile does not exist: " + path.string());
  }

  YAML::Node root;
  try {
    root = YAML::LoadFile(path.string());
  } catch (const YAML::Exception & error) {
    throw std::runtime_error("failed to parse platform_profile " + path.string() + ": " + error.what());
  }
  const auto platform = require_node(root, "platform", "platform");
  const auto geometry = require_node(platform, "geometry", "platform.geometry");
  const auto self_filter = require_node(geometry, "self_filter", "platform.geometry.self_filter");

  SelfFilterGeometry result;
  result.enabled = boolean_value(
    require_node(self_filter, "enabled", "platform.geometry.self_filter.enabled"),
    "platform.geometry.self_filter.enabled");
  const auto frame = require_node(self_filter, "frame", "platform.geometry.self_filter.frame");
  if (!frame.IsScalar() || frame.as<std::string>().empty()) {
    throw std::runtime_error("platform.geometry.self_filter.frame must be a non-empty string");
  }
  result.frame = frame.as<std::string>();
  if (result.frame != "base_footprint") {
    throw std::runtime_error(
      "platform.geometry.self_filter.frame must be base_footprint for the BUNKER filter");
  }
  result.padding = finite_number(
    require_node(self_filter, "padding", "platform.geometry.self_filter.padding"),
    "platform.geometry.self_filter.padding");
  if (result.padding < 0.0) {
    throw std::runtime_error("platform.geometry.self_filter.padding must be >= 0");
  }
  result.include_chassis_body = boolean_value(
    require_node(self_filter, "include_chassis_body", "platform.geometry.self_filter.include_chassis_body"),
    "platform.geometry.self_filter.include_chassis_body");

  const auto boxes = require_node(self_filter, "boxes", "platform.geometry.self_filter.boxes");
  if (!boxes.IsSequence()) {
    throw std::runtime_error("platform.geometry.self_filter.boxes must be a sequence");
  }
  result.boxes.reserve(boxes.size() + (result.include_chassis_body ? 1U : 0U));

  if (result.include_chassis_body) {
    const double length = finite_number(
      require_node(geometry, "length", "platform.geometry.length"), "platform.geometry.length");
    const double width = finite_number(
      require_node(geometry, "width", "platform.geometry.width"), "platform.geometry.width");
    const double height = finite_number(
      require_node(geometry, "height", "platform.geometry.height"), "platform.geometry.height");
    if (length <= 0.0) {
      throw std::runtime_error("platform.geometry.length must be > 0");
    }
    if (width <= 0.0) {
      throw std::runtime_error("platform.geometry.width must be > 0");
    }
    if (height <= 0.0) {
      throw std::runtime_error("platform.geometry.height must be > 0");
    }
    result.boxes.push_back({
      "chassis_body",
      {-length / 2.0, -width / 2.0, 0.0},
      {length / 2.0, width / 2.0, height},
      true,
      "Generated from platform.geometry length, width and height.",
      true,
    });
  }

  for (std::size_t index = 0; index < boxes.size(); ++index) {
    result.boxes.push_back(parse_box(
      boxes[index], "platform.geometry.self_filter.boxes[" + std::to_string(index) + "]"));
  }
  return result;
}

}  // namespace agt_sensor_adapters
