#pragma once

#include "entity.h"

class FactionState;

class Bullet : public Entity
{
public:
  Bullet(FactionState &faction);
  
public:
  /// Returns the bullet's energy
  const float energy() { return energy_; }

public:
  void Update(float deltaTime);

  /// Draws the bullet
  void Draw();

  float collision_radius() const;

private:
  FactionState &faction_;
  const float energy_;
};