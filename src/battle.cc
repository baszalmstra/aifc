#include "battle.h"
#include "faction_state.h"
#include "ai/i_ai_plugin.h"
#include "ai/i_ai.h"
#include "ship_state.h"
#include <cstdlib>

//-------------------------------------------------------------------------------------------------
namespace {

  Color randomColors [] = {
    Color(255, 0, 0),
    Color(0, 255, 0),
    Color(0, 0, 255),
    Color(255, 255, 0),
    Color(255, 0, 255),
    Color(0, 255, 255),
  };

  uint32_t randomColorCount = sizeof(randomColors) / sizeof(Color);
}

//-------------------------------------------------------------------------------------------------
Battle::Battle()
{

}

//-------------------------------------------------------------------------------------------------
Battle::~Battle()
{

}

//-------------------------------------------------------------------------------------------------
void Battle::Initialize(const std::vector<IAIPlugin*> &ais)
{
  const uint32_t numAIs = 2;
  const uint32_t numShips = 3;

  // Initialize random ais
  for (uint32_t i = 0; i < numAIs; ++i)
  {
    uint32_t rndIdx = rand();
    IAIPlugin* ai = ais[rndIdx % ais.size()];
    factions_.emplace_back(new FactionState(ai->name(), randomColors[rndIdx % randomColorCount], ai->CreateAI()));
  }

  // Create a few ships per faction
  for (auto &faction : factions_)
  {
    for (uint32_t i = 0; i < numShips; ++i)
    {
      ShipState *ship = faction->CreateShip();
      ship->set_position(Float2((float)rand() / (float)RAND_MAX * 40.0f- 20.0f,
                                (float)rand() / (float)RAND_MAX * 40.0f - 20.0f));
    }
  }
}

//-------------------------------------------------------------------------------------------------
void Battle::Update()
{
  for (auto &faction : factions_)
    faction->Update();
}

//-------------------------------------------------------------------------------------------------
void Battle::Draw()
{
  for (auto &faction : factions_)
    for (auto &ship : faction->ships())
      ship->Draw();
}