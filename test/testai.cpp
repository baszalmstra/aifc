#include "testai.h"

#include "ai_input.h"
#include "ai_command.h"

//-------------------------------------------------------------------------------------------------
TestAI::TestAI()
{
}

//-------------------------------------------------------------------------------------------------
TestAI::~TestAI()
{
}

//-------------------------------------------------------------------------------------------------
void TestAI::Update(const AIInput& input, AICommand& command)
{
  for (auto it : input.friendly_ships())
  {
    command.Fire(it.id());
    //command.SetShipTorque(it.id(), 10.0f);
  }
}
