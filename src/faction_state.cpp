#include "faction_state.h"
#include "ship_state.h"
#include "ai/i_ai.h"
#include "ai_input.h"
#include "faction_ai_command.h"
#include "battle.h"
#include "ship_pool.h"

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
void FactionState::Update(float deltaTime)
{
  std::vector<ShipInfo> shipInfos;
  std::vector<ShipInfo> friendlyShips;

  // Gather info on all ships
  for (auto &ship : battle_.ships())
  {
    shipInfos.emplace_back(
      ship.faction().id(), ship.id(),
      ship.hp(), ship.max_hp(),
      ship.position(), ship.orientation(),
      ship.mass(), ship.velocity());

    if (&ship.faction() == this)
      friendlyShips.emplace_back(
        ship.faction().id(), ship.id(),
        ship.hp(), ship.max_hp(),
        ship.position(), ship.orientation(),
        ship.mass(), ship.velocity());
  }

  // Create the input buffer
  AIInput input(deltaTime,
    battle_.bounds(),
    std::move(shipInfos),
    std::move(friendlyShips));

  FactionAICommand command;
  ai_->Update(input, command);

	const ActionBuffer& commandBuffer = command.read_buffer();
	while (!commandBuffer.read_eof())
	{
		AIAction action = commandBuffer.BeginReadEvent();
    ProcessAction(action, commandBuffer);
		commandBuffer.EndReadEvent();
	}
}

//---------------------------------------------------------------------------------------------------
void FactionState::ProcessAction(AIAction action, const ActionBuffer& commandBuffer)
{
  ShipState* ship;
  uint32_t shipId;
  switch (action)
  {
  case kForce:
    shipId = commandBuffer.ReadUInt();
    ship = battle_.ships().has(shipId) ? &battle_.ships().lookup(shipId) : nullptr;
    if (ship != nullptr && &ship->faction() == this)
    {
      Vec2f force = commandBuffer.ReadVec2f();
      float totalForceSquared = force.lengthSquared();
      if (totalForceSquared > AICommand::kMaxForce*AICommand::kMaxForce)
        force = force.normalized() * AICommand::kMaxForce;        
      ship->set_force(force);
    }
    break;
  case kFire:
    shipId = commandBuffer.ReadUInt();
    ship = battle_.ships().has(shipId) ? &battle_.ships().lookup(shipId) : nullptr;
    if (ship != nullptr && &ship->faction() == this)
      battle_.Fire(*ship);
    break;
  }
}