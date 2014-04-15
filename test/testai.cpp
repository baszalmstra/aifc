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
    for (auto &ship : input.friendly_ships())
    {
        command.SetShipForce(ship.id(), 1.0);
    }

    if (!input.friendly_ships().empty()) {
        command.Fire(input.friendly_ships().front().id());
    }

}
