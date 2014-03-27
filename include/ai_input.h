#pragma once

#include "ship_info.h"

#include <vector>
#include <cstdint>

typedef uint32_t ShipId;

class AIInput
{

public:
  AIInput() {};

  virtual ~AIInput(){};

    std::vector<ShipInfo> getMyShipInfo() const { return std::vector<ShipInfo>(); }

    std::vector<ShipInfo> getEnemyShipInfo() const { return std::vector<ShipInfo>(); }

    const ShipInfo& getShipInfo(ShipId id) const { return ship_info_[id]; }

private:

    std::vector<ShipInfo> my_ship_info_;

    std::vector<ShipInfo> enemy_ship_info_;

    std::vector<ShipInfo> ship_info_;

};
