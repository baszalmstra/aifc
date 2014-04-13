#pragma once

#include "float2.h"

#include <cstdint>

typedef uint32_t ShipId;

class ShipInfo {

public:
    /// Default constructor
    ShipInfo();

    /// Default destructor
    virtual ~ShipInfo();

    /// Returns the id of the ship
    ShipId id() const { return id_; }

    /// Returns the hp of the ship
    uint32_t hp() const { return hp_; }

    /// Returns the maximum hp of the ship
    uint32_t max_hp() const { return maxHp_; }

    /// Returns the current position of the ship in world space
    const Float2& position() const { return pos_; }

    /// Returns the orientation of the ship in radians
    float orientation() const { return orientation_; }

private:
    ShipId id_;
    uint32_t hp_, maxHp_;
    Float2 pos_;
    float orientation_;
};
