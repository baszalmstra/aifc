#include "testai.h"

#include "ai_input.h"
#include "ai_command.h"

TestAI::TestAI()
{
}

TestAI::~TestAI()
{
}

//-------------------------------------------------------------------------------------------------
void TestAI::Update(const AIInput& input, AICommand& command)
{
    std::vector<ShipInfo> my_ships = input.getMyShipInfo();

    // Check if I have any ships left...
    if (!my_ships.empty())
    {
        // I do! Get a random one (first one in the list)
        const ShipInfo& ship_info = my_ships.front();
    }
}
