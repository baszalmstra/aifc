#pragma once

#include <vector>
#include <cstdint>

typedef uint32_t ShipId;

class AICommand {
public:
  enum {
    kMaxTorque = 1000,
    kMaxForce = 100,
    kMaxEnergy = 100,
    kFireThreshold = 5,
  };

public:
  /// Default destructor
  virtual ~AICommand() {};

  /// Set the velocity of the ship with the given id
  virtual void SetShipForce(uint32_t shipId, float force) = 0;

  /// Set the angular force of the ship with the given id
  virtual void SetShipTorque(uint32_t shipId, float force) = 0;

  /// Tells the specified ship to fire
  virtual void Fire(uint32_t shipId) = 0;
};
