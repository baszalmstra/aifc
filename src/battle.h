#pragma once

#include <array>
#include <memory>
#include <vector>
#include "math_types.h"

class IAIPlugin;
class FactionState;
class Entity;
class Bullet;
class ShipState;
class ShipPool;

class Battle final
{
public:
  // Default constructor
  Battle();

  // Destructor
  ~Battle();

  // Initializes a random battle from ai's
  void Initialize(const std::vector<IAIPlugin*> &ais);

  // Updates the battle
  void Update(float deltaTime);

  // Draws the battle
  void Draw();
  
  /// Fires a bullet from a ship
  void Fire(ShipState& ship);

  // Returns the number of factions
  size_t num_factions() const { return factions_.size(); }

  /// Returns true if a certain position is in bounds
  bool in_bounds(const Vec2f &pos) const { return pos.x >= -bounds_.x && pos.x <= bounds_.x && pos.y >= -bounds_.y && pos.y <= bounds_.y; }

  /// Creates a ship for a specific faction
  ShipState* CreateShip(FactionState& faction);

  /// Returns the ship pool
  const ShipPool& ships() const { return *ships_; }
  ShipPool& ships() { return *ships_; }

private:
  bool TestCollision(const Entity& e1, const Entity& e2, float dt) const;

private:
  std::vector<std::unique_ptr<FactionState> > factions_;
  std::vector<std::unique_ptr<Bullet>> bullets_;  
  std::unique_ptr<ShipPool> ships_;

  double battleTime_;
  Vec2f bounds_;
};
