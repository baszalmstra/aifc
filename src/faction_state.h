#pragma once

#include <string>
#include <memory>
#include <vector>
#include "color.h"

class ShipState;

class FactionState final
{
public:
  /// Default constructor
  FactionState(const std::string &name, const Color& color);

  /// Default destructor
  ~FactionState();

  /// Returns the color of the faction
  const Color& color() const { return color_; }

  /// Returns the name of the faction
  const std::string& name() const { return name_; }

  /// Returns a vector with all the ships of this faction
  const std::vector<std::unique_ptr<ShipState>> &ships() const { return ships_; }

  /// Creates a ship for this faction
  ShipState *CreateShip();

private:
  std::string name_;
  Color color_;

  std::vector<std::unique_ptr<ShipState>> ships_;
};