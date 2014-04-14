#include "faction_state.h"
#include "ship_state.h"
#include "ai/i_ai.h"
#include "ai_input.h"
#include "faction_ai_command.h"
#include "battle.h"

//---------------------------------------------------------------------------------------------------
FactionState::FactionState(Battle& battle, uint32_t id, const std::string &name, const Color& color, std::unique_ptr<IAI> ai) :
  battle_(battle),
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
  return battle_.CreateShip(*this);
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
}