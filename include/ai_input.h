#pragma once

#include "ship_info.h"

#include <vector>
#include <cstdint>

typedef uint32_t ShipId;

class AIInput
{

public:
  AIInput(double deltaTime, std::vector<ShipInfo>&& info, std::vector<uint16_t> factionOffsets) :
    deltaTime_(deltaTime),
    shipInfo_(std::forward<std::vector<ShipInfo>>(info)),
    shipOffsets_(std::forward<std::vector<uint16_t>>(factionOffsets)) {};

  virtual ~AIInput() {};

  /// Returns a list of all enemy ships
  std::vector<ShipInfo> ships() const { return shipInfo_; }

  /// Returns the ship info of the ship with the given id
  const ShipInfo& shipInfo(ShipId id) const { return shipInfo_[id]; }

  /// Returns the delta time of the frame
  double delta_time() const { return deltaTime_; }

private:
  double deltaTime_;
  std::vector<ShipInfo> shipInfo_;
  std::vector<uint16_t> shipOffsets_;
};
