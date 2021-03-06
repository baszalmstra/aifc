#include "battle.h"
#include "faction_state.h"
#include "ai/i_ai_plugin.h"
#include "ai/i_ai.h"
#include "ship_state.h"
#include "ship_info.h"
#include "ai_input.h"
#include "bullet.h"
#include "entity.h"
#include "ship_pool.h"
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

  //-------------------------------------------------------------------------------------------------
  Vec2f startingOffsets [][4] = {
    { Vec2f(-1.0f, -1.0f), Vec2f(1.0f, 1.0f), Vec2f(), Vec2f() },
    { Vec2f(-1.0f, -1.0f), Vec2f(1.0f, -1.0f), Vec2f(0.0f, 1.0f), Vec2f() },
    { Vec2f(-1.0f, -1.0f), Vec2f(1.0f, -1.0f), Vec2f(-1.0f, 1.0f), Vec2f(1.0f, 1.0f) },
  };
}

//-------------------------------------------------------------------------------------------------
Battle::Battle() :
  battleTime_(0.0f),
  bounds_(50.0f * 16.f/9.f, 50.0f),
  ships_(new ShipPool())
{

}

//-------------------------------------------------------------------------------------------------
Battle::~Battle()
{

}

//-------------------------------------------------------------------------------------------------
void Battle::Initialize(const std::vector<IAIPlugin*> &ais, uint32_t numAIs, uint32_t numShips)
{
  // Initialize random ais
  uint32_t randOffset = rand() % 4;
  for (uint32_t i = 0; i < numAIs; ++i)
  {
    uint32_t rndIdx = rand();
    IAIPlugin* ai = ais[rndIdx % ais.size()];

    // Sample a random unique color
    Color color = randomColors[rand() % randomColorCount + randomColorCount * ((randOffset + i) % 4)];

    // Insert the faction
    factions_.emplace_back(new FactionState(*this, i, ai->name(), Color(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f), ai->CreateAI(i)));
    FactionState &faction = *factions_.back();

    // Create ships
    for (uint32_t j = 0; j < numShips; ++j)
    {
      int gridSize = (int)std::ceil(sqrt(numShips));
      int xPos = j % gridSize;
      int yPos = (j - xPos) / gridSize;
      float spacing = 1.f;
      float width = gridSize + spacing * (gridSize - 1);
      float height = gridSize + spacing * (gridSize - 1);
            
      ShipState *ship = CreateShip(faction);
      ship->set_position(Vec2f(bounds_.x * startingOffsets[numAIs-2][i].x * 0.8f + (-width / 2 + xPos + xPos*spacing),
                               bounds_.y * startingOffsets[numAIs - 2][i].y * 0.8f + (-height / 2 + yPos + yPos*spacing)));

      // Orient it to the center
      ship->set_orientation(std::atan2(startingOffsets[numAIs - 2][i].y, startingOffsets[numAIs - 2][i].x) + 3.141592654f);
    }
  }
}

//-------------------------------------------------------------------------------------------------
void Battle::Update(float deltaTime)
{
  battleTime_ += deltaTime;

  // Update the AI's
  for (auto &faction : factions_)
    faction->Update(deltaTime);
    
  // Check collisions
  for (auto it = ships_->begin(); it != ships_->end(); ++it)
  {
    ShipState *ship = &(*it);

    // Make sure ship isn't out of bounds yet
    if (!in_bounds(ship->position()))
    {
      //std::cout << "Ship flew out of bounds!" << std::endl;
      ship->set_hp(0);
      continue;
    }

    //// Check for ship ship collision
    //for (auto other = it + 1; other != ships_->end(); ++other)
    //{
    //  if (&other->faction() != &ship->faction() && TestCollision(*ship, *other, deltaTime))
    //  {
    //    ship->set_hp(0);
    //    other->set_hp(0);
    //    //std::cout << "Ship collision" << std::endl;
    //  }
    //}

    // Check for ship ship collision
    for(auto &bullet : bullets_) 
    {
      if (TestCollision(*ship, *bullet, deltaTime)) 
      {
        ship->OnHit(*bullet);
        bullet->set_destroyed();
        //std::cout << "Ship destroyed by bullet" << std::endl;
      }
    }

    // Finally move the ship
    if (!ship->is_dead())
      ship->Update(deltaTime);
  }

  // Walk over all ships and remove dead ones
  for (auto it = ships_->begin(); it != ships_->end();)
    if (it->is_dead())
      it = ships_->erase(it);
    else
      ++it;
  
  // Update all bullets
  for (uint32_t i = 0; i < bullets_.size();)
  {
    auto &bullet = bullets_[i];
    bullet->Update(deltaTime);
    if (!in_bounds(bullet->position()) || bullet->is_destroyed())
    {
      if (i < bullets_.size() - 1)
        std::swap(bullets_[i], bullets_[bullets_.size() - 1]);
        
      bullets_.pop_back();
    }
    else
      ++i;
  }
}

//-------------------------------------------------------------------------------------------------
ShipState* Battle::CreateShip(FactionState& faction)
{
  return &ships_->Add(faction);
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
  for (auto &ship : *ships_)
    ship.Draw();
  
  for(auto &bullet : bullets_)
    bullet->Draw();
}

//-------------------------------------------------------------------------------------------------
void Battle::Fire(ShipState& ship)
{
  if (!ship.can_fire())
    return;

  float energy = ship.weapon_energy();
  ship.set_weapon_energy(0.0f);
  
  
  Bullet* bullet = new Bullet(ship.faction(), energy);

  Vec2f direction(std::cos(ship.orientation()), std::sin(ship.orientation()));

  bullet->set_position(ship.position() + bullet->height() * direction);
  bullet->set_orientation(ship.orientation());
  bullet->set_velocity(direction * 50.0f);
  
  bullets_.emplace_back(bullet);
}

//-------------------------------------------------------------------------------------------------
bool Battle::TestCollision(const Entity& e1, const Entity& e2, float dt) const 
{
    Vec2f v_diff = e1.velocity() - e2.velocity();
    Vec2f p_diff = e1.position() - e2.position();

    float r_ship = e1.collision_radius();
    float r_bullet = e2.collision_radius();
    float r_total = r_ship + r_bullet;

    float a = v_diff.dot(v_diff);
    float b = 2 * v_diff.dot(p_diff);
    float c = p_diff.dot(p_diff) - r_total * r_total;

    float d = b*b - (4 * a * c);

    if (d < 0.0f) return false;

    float sqrtd = sqrt(d);

    float t0 = (-b - sqrtd) / (2 * a);
    float t1 = (-b + sqrtd) / (2 * a);

    return (t0 >= 0 && t0 <= dt) || (t1 >= 0 && t1 <= dt);
}
