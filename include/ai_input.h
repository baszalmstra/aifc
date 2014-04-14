#pragma once

#include "ship_info.h"

#include <vector>
#include <cstdint>

typedef uint32_t ShipId;

class AIInput
{

public:
  AIInput(float deltaTime, std::vector<ShipInfo>&& info, std::vector<ShipInfo>&& friendlyShips) :
    deltaTime_(deltaTime),
    shipInfo_(std::forward<std::vector<ShipInfo>>(info)),
    friendlyShips_(std::forward<std::vector<ShipInfo>>(friendlyShips)) {};

  virtual ~AIInput() {};

  /// Returns a list of all enemy ships
  std::vector<ShipInfo> ships() const { return shipInfo_; }

  /// Returns the ship info of the ship with the given id
  const ShipInfo& shipInfo(ShipId id) const { return shipInfo_[id]; }

  /// Returns a list of all ships that belong the current processing ai
  std::vector<ShipInfo> friendly_ships() const { return friendlyShips_; }

  /// Returns the delta time of the frame
  float delta_time() const { return deltaTime_; }

private:
  float deltaTime_;
  std::vector<ShipInfo> shipInfo_;
  std::vector<ShipInfo> friendlyShips_;
};
