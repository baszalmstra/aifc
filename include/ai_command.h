#pragma once

#include <vector>
#include <cstdint>

#include "math_types.h"

typedef uint32_t ShipId;

class AICommand {
public:
  enum {
    kMaxSpeed = 40,
    kMaxForce = 500,
    kFireThreshold = 5,
  };

public:
  /// Default destructor
  virtual ~AICommand() {};

  /// Apply a force to the ship
  virtual void ApplyShipForce(uint32_t shipId, const Vec2f& force) = 0;
  
  /// Tells the specified ship to fire
  virtual void Fire(uint32_t shipId) = 0;
};
