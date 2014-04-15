#pragma once

#include "ship_info.h"

#include <vector>
#include <cstdint>

typedef uint32_t ShipId;

class AIInput
{

public:
  AIInput(float deltaTime, 
    Vec2f bounds,
    std::vector<ShipInfo>&& info, 
    std::vector<ShipInfo>&& friendlyShips) :
    deltaTime_(deltaTime),
    shipInfo_(std::forward<std::vector<ShipInfo>>(info)),
    friendlyShips_(std::forward<std::vector<ShipInfo>>(friendlyShips)),
    bounds_(bounds) {};

  virtual ~AIInput() {};

  /// Returns the world bounds (-x, x)
  const Vec2f bounds() const { return bounds_; };

  /// Returns a list of all enemy ships
  const std::vector<ShipInfo>& ships() const { return shipInfo_; }

  /// Returns a list of all ships that belong the current processing ai
  const std::vector<ShipInfo>& friendly_ships() const { return friendlyShips_; }

  /// Returns the delta time of the frame
  float delta_time() const { return deltaTime_; }

private:
  float deltaTime_;
  std::vector<ShipInfo> shipInfo_;
  std::vector<ShipInfo> friendlyShips_;
  Vec2f bounds_;
};
