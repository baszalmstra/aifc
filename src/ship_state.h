#pragma once

#include "entity.h"
#include <cstdint>

class FactionState;

class ShipState : public Entity
{
public:
  /// Default constructor
  ShipState(FactionState &faction, uint32_t id);

  /// Default destructor
  ~ShipState();

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
  
  const FactionState& faction() { return faction_; }

public:
  /// Draws the ship
  void Draw() override;

  /// Updates the ship based on its torque and linear force
  void Update(float deltaTime) override;

private:
  uint32_t id_;
  FactionState &faction_;
  uint16_t maxHp_, hp_;
  float force_, torque_;
  float mass_;
};