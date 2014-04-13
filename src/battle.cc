#include "battle.h"
#include "faction_state.h"
#include "ai/i_ai_plugin.h"
#include "ai/i_ai.h"
#include "ship_state.h"
#include "ship_info.h"
#include "ai_input.h"
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
    factions_.emplace_back(new FactionState(i, ai->name(), randomColors[rndIdx % randomColorCount], ai->CreateAI(i)));
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
void Battle::Update(double deltaTime)
{
  std::vector<ShipInfo> shipInfos;
  std::vector<uint16_t> factionOffsets;

  // Gather info on all ships
  const size_t numAis = factions_.size();
  for (uint32_t i = 0; i < numAis; ++i)
  {
    factionOffsets.push_back(static_cast<uint16_t>(shipInfos.size()));
    auto& faction = factions_[i];
    for (auto &ship : faction->ships())
      shipInfos.emplace_back(
      i, ship->id(),
      ship->hp(), ship->max_hp(),
      ship->position(), ship->orientation());
  }

  // Create the input buffer
  AIInput input(deltaTime, 
    std::move(shipInfos), 
    std::move(factionOffsets));

  // Let the faction update based on the state of the world
  for (auto &faction : factions_)
    faction->Update(input);
}

//-------------------------------------------------------------------------------------------------
void Battle::Draw()
{
  for (auto &faction : factions_)
    for (auto &ship : faction->ships())
      ship->Draw();
}