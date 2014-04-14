#pragma once

#include "entity.h"
#include <cstdint>

class FactionState;

class Bullet;
class ShipState final : public Entity
{
public:
  /// Default constructor
  ShipState();
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
  
  /// Returns the faction to which this ship belongs
  const FactionState& faction() const { return *faction_; }

  /// Returns the amount of weapon energy has been built up
  float weapon_energy() const { return weaponEnergy_; }

  /// Sets the amount of weapon energy
  void set_weapon_energy(float energy) { weaponEnergy_ = energy; }

  /// Returns true if the ship can fire
  bool can_fire() const;

  /// Called when the ship is hit by a bullet. Returns true if the ship died
  bool OnHit(const Bullet &bullet);

  /// Returns true if the ship died
  bool is_dead() const { return hp_ == 0; }

public:
  /// Draws the ship
  void Draw() override;

  /// Updates the ship based on its torque and linear force
  void Update(float deltaTime) override;

private:
  uint32_t id_;
  FactionState *faction_;
  uint16_t maxHp_, hp_;
  float force_, torque_;
  float mass_;
  float weaponEnergy_, weaponRechargeRate_;

  float hitTime_;
};