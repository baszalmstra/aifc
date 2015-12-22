#include "babai.h"

#include "ai_input.h"
#include "ai_command.h"

#include <cmath>
#include <algorithm>

#include "steering.h"

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

  //-------------------------------------------------------------------------------------------------
  bool AccumulateForce(Vec2f &runningTotal, const Vec2f& toAdd)
  {
    float magnitudeSoFar = runningTotal.length();
    float magnitudeRemaining = AICommand::kMaxForce - magnitudeSoFar;
    if (magnitudeRemaining <= 0.0f)
      return false;

    float magnitudeToAdd = toAdd.length();
    if (magnitudeToAdd < magnitudeRemaining)
      runningTotal += toAdd;
    else
      runningTotal += toAdd.normalized() * magnitudeRemaining;
    return true;
  }
}

struct Babai::Ship 
{
  Ship(const Vec2f& bounds) :
    steering(bounds)
  {}

  Steering steering;
  uint32_t target;
};

//-------------------------------------------------------------------------------------------------
Babai::Babai(uint32_t id) : 
  id_(id), 
  randomOffset_(rand()),
  time_(0.0f)
{
}

//-------------------------------------------------------------------------------------------------
Babai::~Babai()
{
}

//-------------------------------------------------------------------------------------------------
void Babai::Update(const AIInput& input, AICommand& command)
{
  // Gather all enemy ships
  std::vector<ShipInfo const*> enemies;
  std::unordered_map<ShipId, ShipInfo const*> idToEnemy;
  for (auto& info : input.ships())
    if (info.faction_id() != id_)
    {
      enemies.emplace_back(&info);
      idToEnemy.emplace(info.id(), &info);
    }

  // Walk over all ships
  for (auto &info : input.friendly_ships())
  {
    // Do we have this in our map yet?
    auto it = steeringBehaviors_.find(info.id());
    if (it == steeringBehaviors_.end())
    {
      it = steeringBehaviors_.emplace(info.id(), std::unique_ptr<Ship>(new Ship(input.bounds()))).first;
      it->second->target = 0xffffffff;
    }

    // Get the steering behavior
    Steering &steering = it->second->steering;

    // Select a target if this ship doesn't have a target yet.
    ShipInfo const *target = nullptr;
    if (it->second->target == 0xffffffff && enemies.size() > 0 && (id_ % 2) == 1)
      it->second->target = enemies[std::rand() % enemies.size()]->id();

    // Find the target
    if (it->second->target != 0xffffffff)
    {
      auto targetIt = idToEnemy.find(it->second->target);
      if (targetIt != idToEnemy.end())
        target = targetIt->second;
    }

    // No enemy this frame
    if (!target)
      it->second->target = 0xffffffff;

    Vec2f force(0, 0);
    AccumulateForce(force, steering.avoid_bounds(info, input.delta_time())*10);
    if (target) AccumulateForce(force, steering.persuit(info, *target));
    else AccumulateForce(force, steering.wander(info, input.delta_time()));
    
    command.ApplyShipForce(info.id(), force);

    if (target && (target->position() - info.position()).lengthSquared() < 500 && 
      info.velocity().normalized().dot((target->position() - info.position()).normalized()) > 0.95f)
      command.Fire(info.id());
  }
}