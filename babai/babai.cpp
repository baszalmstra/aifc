#include "babai.h"

#include "ai_input.h"
#include "ai_command.h"

#include <cmath>
#include <algorithm>

//-------------------------------------------------------------------------------------------------
namespace {
  const float pi = 3.141592654f;
  const float twoPi = pi * 2.0f;

  float shortestAngle(float a, float b)
  {
    float result = a - b;
    if (result > pi)
      result -= twoPi;
    if (result < -pi)
      result += twoPi;
    return result;
  }
}

//-------------------------------------------------------------------------------------------------
Babai::Babai(uint32_t id) : 
  id_(id), 
  randomOffset_(rand())
{
}

//-------------------------------------------------------------------------------------------------
Babai::~Babai()
{
}

//-------------------------------------------------------------------------------------------------
void Babai::Update(const AIInput& input, AICommand& command)
{
  std::vector<ShipInfo const*> enemyShips;
  Vec2f otherShip = Vec2f(0.0f, 0.0f);
  for (const ShipInfo &enemy : input.ships())
    if (enemy.faction_id() != id_)
      enemyShips.push_back(&enemy);

  for (uint32_t i = 0; i < input.friendly_ships().size(); ++i)
  {  
    const ShipInfo &ship = input.friendly_ships()[i];
    ShipInfo const*enemy = enemyShips.empty() ? nullptr : enemyShips[(randomOffset_+i)%enemyShips.size()];

    // Go to the center of the galaxy
    Vec2f currentHeading(std::sin(ship.orientation()), std::cos(ship.orientation()));
    
    // Rotate to that position
    const Vec2f direction = (enemy ? enemy->position() : Vec2f(0.0f)) - ship.position();
    const Vec2f heading = direction.normalized();
    const float headingDotDir = ship.velocity().normalized().dot(heading);
    const float speed = heading.dot(ship.velocity());
    if (speed < 10.0f)
      command.SetShipForce(ship.id(), (10-speed)/input.delta_time());
    else
      command.SetShipForce(ship.id(), 0.0f);

    if (headingDotDir > 0 && direction.dot(direction) < 300.0f && enemy != nullptr)
      command.Fire(ship.id());

    const float angle = std::fmod(std::atan2(direction.y, direction.x), twoPi);

    const float maxTorque = AICommand::kMaxTorque/5;
    const float shortestStopTime = ship.angular_velocity() / maxTorque;
    const float shortestStopDistance = ship.angular_velocity()*ship.angular_velocity() / (2 * maxTorque);
    float wantAngle = shortestAngle(ship.orientation(), angle);
        
    float x = 0.5f - (ship.angular_velocity()*ship.angular_velocity()) / (4 * maxTorque*wantAngle);
    float absx = std::abs(x);
    if (std::abs(ship.angular_velocity() * input.delta_time()) >= std::abs(wantAngle))
    {
      command.SetShipTorque(ship.id(), -ship.angular_velocity() / input.delta_time());
      continue;
    }

    float angleSign = wantAngle < 0 ? -1.f : 1.0f;
    if (x < 0.0f)
    {
      command.SetShipTorque(ship.id(), maxTorque*angleSign);
      continue;
    }
    else
    {
      command.SetShipTorque(ship.id(), -maxTorque*angleSign);
      continue;
    }
  }
}
