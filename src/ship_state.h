#pragma once

#include <cstdint>
#include "float2.h"

class FactionState;

class ShipState
{
public:
  /// Default constructor
  ShipState(FactionState &faction, uint32_t id);

  /// Default destructor
  ~ShipState();

  /// Returns the position of the ship
  const Float2& position() const { return position_; }

  /// Sets the position of the ship
  void set_position(const Float2& position) { position_ = position; }

  /// Returns the orientation of the ship
  float orientation() const { return orientation_; }

  /// Sets the orientation of the ship
  void set_orientation(float orientation) { orientation_ = orientation; }

  /// Returns the hp of the ship
  uint16_t hp() const { return hp_; }

  /// Sets the hp of the ship
  void set_hp(uint16_t hp) { hp_ = hp; }

  /// Returns the maximum hp of the ship
  uint16_t max_hp() const { return maxHp_; }

  /// Sets the maximum hp of the ship
  void set_max_hp(uint16_t maxHp) { maxHp_ = maxHp; }

  /// Returns the id of the ship
  uint32_t id() const { return id_; }

  /// Sets the force on the ship
  void set_force(float force) { force_ = force; }

  /// Returns the current force on the ship
  float force() const { return force_; }

  /// Sets the torque on the ship
  void set_torque(float torque) { torque_ = torque; }

  //// Returns the torque on the ship
  float torque() const { return torque_; }
  
  /// Returns the mass of the ship
  float mass() const { return mass_; }

  /// Returns the velocity of the ship
  const Float2& velocity() const { return velocity_; }

  /// Returns the angular velocity
  float angular_velocity() const { return angularVelocity_; }

  /// Returns the collision radius of the ship
  float collision_radius() const { return 0.5f; }

public:
  /// Draws the ship
  void Draw();

  /// Updates the ship based on its torque and linear force
  void Update(float deltaTime);

private:
  uint32_t id_;
  FactionState &faction_;
  Float2 position_, velocity_;
  float orientation_, angularVelocity_;
  uint16_t maxHp_, hp_;
  float force_, torque_;
  float mass_;
};