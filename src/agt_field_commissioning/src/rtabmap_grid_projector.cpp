#include <algorithm>
#include <cmath>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <opencv2/core/types.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/types.h>
#include <rtabmap/core/LocalGridMaker.h>
#include <rtabmap/core/Parameters.h>
#include <rtabmap/core/Transform.h>

namespace
{

struct Options
{
  std::filesystem::path input;
  std::filesystem::path output_pgm;
  std::filesystem::path output_yaml;
  double cell_size{0.05};
  double max_ground_angle_deg{35.0};
  int normal_k{20};
  double min_ground_height{-0.4};
  double max_ground_height{0.5};
  double max_obstacle_height{2.0};
};

std::string requireValue(int argc, char ** argv, int * index)
{
  if (*index + 1 >= argc) {
    throw std::runtime_error(std::string("missing value for ") + argv[*index]);
  }
  ++(*index);
  return argv[*index];
}

Options parseOptions(int argc, char ** argv)
{
  Options options;
  for (int i = 1; i < argc; ++i) {
    const std::string key(argv[i]);
    if (key == "--input") {
      options.input = requireValue(argc, argv, &i);
    } else if (key == "--output-pgm") {
      options.output_pgm = requireValue(argc, argv, &i);
    } else if (key == "--output-yaml") {
      options.output_yaml = requireValue(argc, argv, &i);
    } else if (key == "--cell-size") {
      options.cell_size = std::stod(requireValue(argc, argv, &i));
    } else if (key == "--max-ground-angle-deg") {
      options.max_ground_angle_deg = std::stod(requireValue(argc, argv, &i));
    } else if (key == "--normal-k") {
      options.normal_k = std::stoi(requireValue(argc, argv, &i));
    } else if (key == "--min-ground-height") {
      options.min_ground_height = std::stod(requireValue(argc, argv, &i));
    } else if (key == "--max-ground-height") {
      options.max_ground_height = std::stod(requireValue(argc, argv, &i));
    } else if (key == "--max-obstacle-height") {
      options.max_obstacle_height = std::stod(requireValue(argc, argv, &i));
    } else {
      throw std::runtime_error("unknown argument: " + key);
    }
  }

  if (options.input.empty() || options.output_pgm.empty() || options.output_yaml.empty()) {
    throw std::runtime_error("--input, --output-pgm and --output-yaml are required");
  }
  if (!(options.cell_size >= 0.01 && options.cell_size <= 1.0)) {
    throw std::runtime_error("cell size must be within [0.01, 1.0] m");
  }
  if (!(options.max_ground_angle_deg > 0.0 && options.max_ground_angle_deg < 90.0)) {
    throw std::runtime_error("max ground angle must be within (0, 90) deg");
  }
  if (options.normal_k < 3) {
    throw std::runtime_error("normal-k must be >= 3");
  }
  if (!(options.min_ground_height < options.max_ground_height)) {
    throw std::runtime_error("min ground height must be smaller than max ground height");
  }
  return options;
}

rtabmap::ParametersMap makeParameters(const Options & options)
{
  rtabmap::ParametersMap parameters;
  parameters["Grid/CellSize"] = std::to_string(options.cell_size);
  parameters["Grid/NormalsSegmentation"] = "true";
  parameters["Grid/NormalK"] = std::to_string(options.normal_k);
  parameters["Grid/MaxGroundAngle"] = std::to_string(options.max_ground_angle_deg * M_PI / 180.0);
  parameters["Grid/MinGroundHeight"] = std::to_string(options.min_ground_height);
  parameters["Grid/MaxGroundHeight"] = std::to_string(options.max_ground_height);
  parameters["Grid/MaxObstacleHeight"] = std::to_string(options.max_obstacle_height);
  parameters["Grid/3D"] = "false";
  parameters["Grid/PreVoxelFiltering"] = "true";
  return parameters;
}

struct Bounds
{
  double min_x{std::numeric_limits<double>::infinity()};
  double max_x{-std::numeric_limits<double>::infinity()};
  double min_y{std::numeric_limits<double>::infinity()};
  double max_y{-std::numeric_limits<double>::infinity()};

  void include(const pcl::PointXYZ & point)
  {
    if (!std::isfinite(point.x) || !std::isfinite(point.y)) {
      return;
    }
    min_x = std::min(min_x, static_cast<double>(point.x));
    max_x = std::max(max_x, static_cast<double>(point.x));
    min_y = std::min(min_y, static_cast<double>(point.y));
    max_y = std::max(max_y, static_cast<double>(point.y));
  }

  bool valid() const
  {
    return std::isfinite(min_x) && std::isfinite(max_x) &&
           std::isfinite(min_y) && std::isfinite(max_y) &&
           max_x >= min_x && max_y >= min_y;
  }
};

void writePgm(
  const std::filesystem::path & path,
  std::size_t width,
  std::size_t height,
  const std::vector<unsigned char> & pixels)
{
  std::filesystem::create_directories(path.parent_path());
  const auto temporary = std::filesystem::path(path.string() + ".tmp");
  std::ofstream output(temporary, std::ios::binary | std::ios::trunc);
  if (!output) {
    throw std::runtime_error("failed to open PGM output");
  }
  output << "P5\n" << width << " " << height << "\n255\n";
  output.write(reinterpret_cast<const char *>(pixels.data()), static_cast<std::streamsize>(pixels.size()));
  output.close();
  if (!output) {
    throw std::runtime_error("failed to write PGM output");
  }
  std::filesystem::rename(temporary, path);
}

void writeYaml(
  const std::filesystem::path & path,
  const std::filesystem::path & pgm,
  double cell_size,
  double origin_x,
  double origin_y)
{
  std::filesystem::create_directories(path.parent_path());
  const auto temporary = std::filesystem::path(path.string() + ".tmp");
  std::ofstream output(temporary, std::ios::trunc);
  if (!output) {
    throw std::runtime_error("failed to open YAML output");
  }
  output << "image: " << pgm.filename().string() << "\n"
         << "resolution: " << cell_size << "\n"
         << "origin: [" << origin_x << ", " << origin_y << ", 0.0]\n"
         << "negate: 0\n"
         << "occupied_thresh: 0.65\n"
         << "free_thresh: 0.196\n"
         << "mode: trinary\n";
  output.close();
  if (!output) {
    throw std::runtime_error("failed to write YAML output");
  }
  std::filesystem::rename(temporary, path);
}

}  // namespace

int main(int argc, char ** argv)
{
  try {
    const auto options = parseOptions(argc, argv);

    auto cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(options.input.string(), *cloud) != 0 || cloud->empty()) {
      throw std::runtime_error("failed to load a non-empty XYZ PCD: " + options.input.string());
    }

    pcl::IndicesPtr indices(new pcl::Indices());
    indices->reserve(cloud->size());
    for (std::size_t i = 0; i < cloud->size(); ++i) {
      indices->push_back(static_cast<pcl::index_t>(i));
    }

    rtabmap::LocalGridMaker grid_maker(makeParameters(options));
    pcl::IndicesPtr ground_indices(new pcl::Indices());
    pcl::IndicesPtr obstacle_indices(new pcl::Indices());
    auto segmented = grid_maker.segmentCloud<pcl::PointXYZ>(
      cloud,
      indices,
      rtabmap::Transform::getIdentity(),
      cv::Point3f(0.0f, 0.0f, 0.0f),
      ground_indices,
      obstacle_indices);

    if (!segmented || segmented->empty()) {
      throw std::runtime_error("RTAB-Map segmentation returned an empty cloud");
    }
    if (ground_indices->empty() && obstacle_indices->empty()) {
      throw std::runtime_error("RTAB-Map segmentation produced no ground or obstacle cells");
    }

    Bounds bounds;
    for (const auto & point : segmented->points) {
      bounds.include(point);
    }
    if (!bounds.valid()) {
      throw std::runtime_error("segmented cloud has no finite XY bounds");
    }

    const double margin = options.cell_size;
    const double origin_x = std::floor((bounds.min_x - margin) / options.cell_size) * options.cell_size;
    const double origin_y = std::floor((bounds.min_y - margin) / options.cell_size) * options.cell_size;
    const double max_x = std::ceil((bounds.max_x + margin) / options.cell_size) * options.cell_size;
    const double max_y = std::ceil((bounds.max_y + margin) / options.cell_size) * options.cell_size;
    const auto width = static_cast<std::size_t>(std::max(1.0, std::ceil((max_x - origin_x) / options.cell_size)));
    const auto height = static_cast<std::size_t>(std::max(1.0, std::ceil((max_y - origin_y) / options.cell_size)));
    std::vector<unsigned char> pixels(width * height, static_cast<unsigned char>(205));

    const auto paint = [&](const pcl::Indices & selected, unsigned char value) {
      for (const auto index : selected) {
        if (index < 0 || static_cast<std::size_t>(index) >= segmented->size()) {
          continue;
        }
        const auto & point = segmented->points[static_cast<std::size_t>(index)];
        if (!std::isfinite(point.x) || !std::isfinite(point.y)) {
          continue;
        }
        const auto mx = static_cast<long>(std::floor((point.x - origin_x) / options.cell_size));
        const auto my = static_cast<long>(std::floor((point.y - origin_y) / options.cell_size));
        if (mx < 0 || my < 0 || mx >= static_cast<long>(width) || my >= static_cast<long>(height)) {
          continue;
        }
        const std::size_t row = height - 1U - static_cast<std::size_t>(my);
        const std::size_t offset = row * width + static_cast<std::size_t>(mx);
        if (value == 0 || pixels[offset] != 0) {
          pixels[offset] = value;
        }
      }
    };

    // Ground first, obstacles second. Obstacles therefore always override free cells.
    paint(*ground_indices, static_cast<unsigned char>(254));
    paint(*obstacle_indices, static_cast<unsigned char>(0));

    writePgm(options.output_pgm, width, height, pixels);
    writeYaml(options.output_yaml, options.output_pgm, options.cell_size, origin_x, origin_y);

    std::cout << "rtabmap_grid_projector: width=" << width
              << " height=" << height
              << " ground=" << ground_indices->size()
              << " obstacles=" << obstacle_indices->size() << std::endl;
    return 0;
  } catch (const std::exception & exception) {
    std::cerr << "rtabmap_grid_projector: " << exception.what() << std::endl;
    return 2;
  }
}
