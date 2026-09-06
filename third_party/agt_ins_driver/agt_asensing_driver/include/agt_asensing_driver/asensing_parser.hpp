#pragma once

#include <cstdint>
#include <vector>
#include "agt_asensing_driver/ins_data.hpp"

namespace agt_asensing_driver
{
class ASENSINGParser
{
public:
  std::vector<INSData> feed(const uint8_t * data, std::size_t size);
  std::vector<INSData> feed(const std::vector<uint8_t> & data)
  { return feed(data.data(), data.size()); }

private:
  std::vector<uint8_t> buffer_;
};
}  // namespace agt_asensing_driver
