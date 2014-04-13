#pragma once

#include <string>
#include <memory>
#include <vector>
#include "action_buffer.h"
#include "color.h"

class ShipState;
class IAI;
class AIInput;
class ActionBuffer;

class FactionState
{
public:
  /// Default constructor
  FactionState(uint32_t id, const std::string &name, const Color& color, std::unique_ptr<IAI> ai);

  /// Default destructor
  ~FactionState();

  /// Returns the color of the faction
  const Color& color() const { return color_; }

  /// Returns the name of the faction
  const std::string& name() const { return name_; }

  /// Returns a vector with all the ships of this faction
  const std::vector<std::unique_ptr<ShipState>> &ships() const { return ships_; }

  /// Updates the AI of the faction
  void Update(const AIInput& worldState) const;

  /// Creates a ship for this faction
  ShipState *CreateShip();

private:
	void ProcessAction(AIAction action, const ActionBuffer& commandBuffer);

private:
  uint32_t id_;
  std::string name_;
  Color color_;

  std::vector<std::unique_ptr<ShipState>> ships_;
  std::unique_ptr<IAI> ai_;
};