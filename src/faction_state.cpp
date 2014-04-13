#include "faction_state.h"
#include "ship_state.h"
#include "ai/i_ai.h"
#include "ai_input.h"
#include "faction_ai_command.h"

//---------------------------------------------------------------------------------------------------
FactionState::FactionState(uint32_t id, const std::string &name, const Color& color, std::unique_ptr<IAI> ai) :
  id_(id),
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
  std::unique_ptr<ShipState> ship(new ShipState(*this, id_ | (uint32_t) (ships_.size()) << 3));
  ShipState *shipPtr = ship.get();
  ships_.emplace_back(std::move(ship));
  return shipPtr;
}

//---------------------------------------------------------------------------------------------------
void FactionState::Update(const AIInput& worldState) const
{
  FactionAICommand command;
  ai_->Update(worldState, command);

	const ActionBuffer& commandBuffer = command.read_buffer();
	while (!commandBuffer.read_eof())
	{
		uint16_t eventId = commandBuffer.BeginReadEvent();

		commandBuffer.EndReadEvent();
	}

  for (auto &ship : ships_)
    ship->Update(worldState.delta_time());
}