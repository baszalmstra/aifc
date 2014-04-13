#pragma once

#include "entity.h"

class FactionState;

class Bullet : public Entity
{
public:
  Bullet(const FactionState& faction, float energy);
  
public:
  /// Returns the bullet's energy
  float energy() const { return energy_; }

  /// Returns the height of the bullet
  float height() const { return height_; }

  /// Returns true if the bullet is destroyed
  bool is_destroyed() const { return destroyed_; }

  /// Mark the bullet as destroyed so it will be garbage collected
  void set_destroyed(bool destroyed = true) { destroyed_ = destroyed; }

public:
  void Update(float deltaTime);

  /// Draws the bullet
  void Draw();

private:
  const FactionState& faction_;
  const float energy_;
  
  float height_;
  bool destroyed_;
};
