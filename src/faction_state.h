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
class Battle;

class FactionState
{
public:
  /// Default constructor
  FactionState(Battle& battle, uint32_t id, const std::string &name, const Color& color, std::unique_ptr<IAI> ai);

  /// Default destructor
  ~FactionState();

  /// Returns the color of the faction
  const Color& color() const { return color_; }

  /// Returns the name of the faction
  const std::string& name() const { return name_; }

  /// Updates the AI of the faction
  void Update(float deltaTime);

  /// Creates a ship for this faction
  ShipState *CreateShip();

  /// Returns the id of the faction
  uint32_t id() const { return id_; }

private:
	void ProcessAction(AIAction action, const ActionBuffer& commandBuffer);

private:
  Battle& battle_;
  uint32_t id_;
  std::string name_;
  Color color_;

  std::unique_ptr<IAI> ai_;
};