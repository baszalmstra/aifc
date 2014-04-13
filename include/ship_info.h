#pragma once

#include "float2.h"

#include <cstdint>

typedef uint32_t ShipId;

class ShipInfo 
{
public:
  /// Default constructor
  ShipInfo(uint32_t factionId, ShipId id, uint32_t hp, uint32_t maxHp, const Float2 &pos, float orientation,
    float mass, const Float2& velocity, float angularVelocity) :
    factionId_(factionId),
    id_(id),
    hp_(hp),
    maxHp_(maxHp),
    pos_(pos), velocity_(velocity),
    orientation_(orientation), angularVelocity_(angularVelocity),
    mass_(mass) {}

  /// Default destructor
  virtual ~ShipInfo() {};

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

  /// Returns the id of the faction to which this ship belongs
  uint32_t faction_id() const { return factionId_; } 

  /// Returns the mass of the ship
  float mass() const { return mass_; }

  /// Returns the velocity of the ship
  const Float2& velocity() const { return velocity_; }

  /// Returns the angular velocity off the ship
  float angular_velocity() const { return angularVelocity_; }

private:
  uint32_t factionId_;
  ShipId id_;
  uint32_t hp_, maxHp_;
  Float2 pos_, velocity_;
  float orientation_, angularVelocity_;
  float mass_;
};
