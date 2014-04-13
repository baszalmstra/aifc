#include "battle.h"
#include "faction_state.h"
#include "ai/i_ai_plugin.h"
#include "ai/i_ai.h"
#include "ship_state.h"
#include "ship_info.h"
#include "ai_input.h"
#include "bullet.h"
#include "entity.h"
#include <cstdlib>
#include <iostream>
#include <SDL_opengl.h>
#include <cmath>

//-------------------------------------------------------------------------------------------------
namespace {

  Color randomColors [] = {
    Color(0, 192, 129),
    Color(42, 129, 101),
    Color(0, 104, 70),
    Color(64, 227, 174),
    Color(115, 227, 191),
    Color(83, 8, 195),
    Color(81, 47, 131),
    Color(43, 2, 105),
    Color(135, 71, 229),
    Color(164, 120, 229),
    Color(255, 229, 0),
    Color(171, 160, 56),
    Color(138, 124, 0),
    Color(255, 236, 72),
    Color(255, 242, 129),
    Color(255, 86, 0),
    Color(171, 95, 56),
    Color(138, 46, 0),
    Color(255, 133, 72),
    Color(255, 171, 129),
  };

  uint32_t randomColorCount = sizeof(randomColors) / sizeof(Color) / 4;
}

//-------------------------------------------------------------------------------------------------
Battle::Battle() :
  battleTime_(0.0f)
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
  uint32_t randOffset = rand() % 4;
  for (uint32_t i = 0; i < numAIs; ++i)
  {
    uint32_t rndIdx = rand();
    IAIPlugin* ai = ais[rndIdx % ais.size()];

    // Sample a random unique color
    Color color = randomColors[rand() % randomColorCount + randomColorCount * ((randOffset + i) % 4)];

    // Insert the faction
    factions_.emplace_back(new FactionState(i, ai->name(), Color(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f), ai->CreateAI(i)));
  }

  // Create a few ships per faction
  for (auto &faction : factions_)
  { 
    for (uint32_t i = 0; i < numShips; ++i)
    {
      ShipState *ship = faction->CreateShip();
      ship->set_position(Vec2f((float)rand() / (float)RAND_MAX * 40.0f- 20.0f,
                                (float)rand() / (float)RAND_MAX * 40.0f - 20.0f));
    }
  }
}

//-------------------------------------------------------------------------------------------------
void Battle::Update(float deltaTime)
{
  battleTime_ += deltaTime;

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
      ship->position(), ship->orientation(),
      ship->mass(), ship->velocity(), ship->angular_velocity());
  }

  // Create the input buffer
  AIInput input(deltaTime, 
    std::move(shipInfos), 
    std::move(factionOffsets));

  // Let the faction update based on the state of the world
  for (auto &faction : factions_)
    faction->Update(input);
  
  // Update all bullets
  for(auto &bullet : bullets_)
    bullet->Update(deltaTime);
}

//-------------------------------------------------------------------------------------------------
void Battle::Draw()
{
  // Draw all bullets
  glBegin(GL_TRIANGLES);
  for (auto &bullet : bullets_)
    bullet->Draw();
  glEnd();

  // Draw all ships
  for (auto &faction : factions_)
    for (auto &ship : faction->ships())
      ship->Draw();
  
  for(auto &bullet : bullets_)
    bullet->Draw();
}

//-------------------------------------------------------------------------------------------------
void Battle::Fire(ShipState& ship)
{
  // Create bullet and set parameters, velocity still needs to be set!
  Bullet* bullet = new Bullet(ship.faction());
  bullet->set_position(ship.position());
  bullet->set_orientation(ship.orientation());
  // TODO: set velocity
  
  bullets_.emplace_back(bullet);
}

//-------------------------------------------------------------------------------------------------
bool Battle::TestCollision(const Entity& e1, const Entity& e2, float dt) const {
    Vec2f v_diff = e1.velocity() - e2.velocity();
    Vec2f p_diff = e1.position() - e2.position();

    float r_ship = e1.collision_radius();
    float r_bullet = e2.collision_radius();
    float r_diff = r_ship - r_bullet;

    float a = v_diff.dot(v_diff);
    float b = 2 * v_diff.dot(p_diff);
    float c = p_diff.dot(p_diff) - r_diff;

    float d = b*b - (4 * a * c);

    if (d < 0.0f) return false;

    float t0 = (-b - sqrt(d)) / (2 * a);
    float t1 = (-b + sqrt(d)) / (2 * a);

    return (t0 > 0 && t0 < dt) || (t1 > 0 && t1 < dt);
}

