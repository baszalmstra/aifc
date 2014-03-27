#include "faction_state.h"
#include "ship_state.h"
#include "ai/i_ai.h"
#include "ai_input.h"
#include "ai_command.h"

//---------------------------------------------------------------------------------------------------
FactionState::FactionState(const std::string &name, const Color& color, std::unique_ptr<IAI> ai) :
  name_(name),
  color_(color),
  ai_(std::move(ai))
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

//---------------------------------------------------------------------------------------------------
void FactionState::Update()
{
  AIInput input;
  AICommand command;
  ai_->Update(input, command);
}