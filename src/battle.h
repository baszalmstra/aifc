#pragma once

#include <array>
#include <memory>
#include <vector>

class IAIPlugin;
class FactionState;
class ShipState;
class Bullet;

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

  // Returns the number of factions
  size_t num_factions() const { return factions_.size(); }

private:
  std::vector<std::unique_ptr<FactionState> > factions_;
  std::vector<std::unique_ptr<Bullet> > bullets_;

  bool TestCollision(const ShipState& ship, const ShipState& bullet) const;
};
