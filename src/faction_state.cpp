#include "faction_state.h"
#include "ship_state.h"

//---------------------------------------------------------------------------------------------------
FactionState::FactionState(const std::string &name, const Color& color) :
  name_(name),
  color_(color)
{

}

//---------------------------------------------------------------------------------------------------
FactionState::~FactionState()
{

}

//---------------------------------------------------------------------------------------------------
ShipState *FactionState::CreateShip()
{
  std::unique_ptr<ShipState> ship(new ShipState(*this));
  ShipState *shipPtr = ship.get();
  ships_.emplace_back(std::move(ship));
  return shipPtr;
}