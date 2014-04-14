#include "faction_ai_command.h"

//-------------------------------------------------------------------------------------------------
FactionAICommand::FactionAICommand() 
{
}

//-------------------------------------------------------------------------------------------------
FactionAICommand::~FactionAICommand() 
{
}

//-------------------------------------------------------------------------------------------------
void FactionAICommand::SetShipForce(uint32_t ship, float force)
{
  buffer_.BeginWrite(kForce);
  buffer_.WriteUInt(ship);
  buffer_.WriteFloat(force);
  buffer_.EndWrite();
}

//-------------------------------------------------------------------------------------------------
void FactionAICommand::SetShipTorque(uint32_t ship, float force)
{
  buffer_.BeginWrite(kTorque);
  buffer_.WriteUInt(ship);
  buffer_.WriteFloat(force);
  buffer_.EndWrite();
}

//-------------------------------------------------------------------------------------------------
void FactionAICommand::Fire(uint32_t ship)
{
  buffer_.BeginWrite(kFire);
  buffer_.WriteUInt(ship);
  buffer_.EndWrite();
}