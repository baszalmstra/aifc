#include "faction_ai_command.h"
#include <algorithm>

//-------------------------------------------------------------------------------------------------
FactionAICommand::FactionAICommand() 
{
}

//-------------------------------------------------------------------------------------------------
FactionAICommand::~FactionAICommand() 
{
}

//-------------------------------------------------------------------------------------------------
void FactionAICommand::ApplyShipForce(uint32_t ship, const Vec2f& force)
{
  buffer_.BeginWrite(kForce);
  buffer_.WriteUInt(ship);
  buffer_.WriteVec2(force);
  buffer_.EndWrite();
}

//-------------------------------------------------------------------------------------------------
void FactionAICommand::Fire(uint32_t ship)
{
  buffer_.BeginWrite(kFire);
  buffer_.WriteUInt(ship);
  buffer_.EndWrite();
}