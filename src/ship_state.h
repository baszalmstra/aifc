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

public:
  /// Draws the ship
  void Draw();

private:
  uint32_t id_;
  FactionState &faction_;
  Float2 position_;
  float orientation_;
  uint16_t maxHp_, hp_;
};