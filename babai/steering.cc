#include "steering.h"

#include <cstdlib>
#include <ship_info.h>
#include <ai_command.h>

namespace {

  Vec2f largest_magnitude(const Vec2f& a, const Vec2f& b)
  {
    return a.lengthSquared() > b.lengthSquared() ? a : b;
  }

}

//-------------------------------------------------------------------------------------------------
Steering::Steering(const Vec2f& bounds) : 
  bounds_(bounds)
{
  wanderTarget_ =
    Vec2f((static_cast<float>(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 2.0f - 1.0f),
    (static_cast<float>(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 2.0f - 1.0f)).normalized() * wanderRadius;
}

//-------------------------------------------------------------------------------------------------
Vec2f Steering::wander(const ShipInfo& ship, float deltaTime)
{
  // First add a small random vector to the target's position
  wanderTarget_ += Vec2f((static_cast<float>(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 2.0f - 1.0f) * wanderJitter * deltaTime,
                         (static_cast<float>(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 2.0f - 1.0f) * wanderJitter * deltaTime);

  // Reproject it onto the circle
  wanderTarget_ = wanderTarget_.normalized() * wanderRadius;

  // Move the target into a position in front of our vehicle
  Vec2f targetLocal = wanderTarget_ + Vec2f(wanderDistance, 0);

  // Convert it to world space 
  float s = std::sin(ship.orientation()), c = std::cos(ship.orientation());
  Vec2f targetWorld = Vec2f(c*targetLocal.x - s * targetLocal.y, s*targetLocal.x + c*targetLocal.y);

  // Return as our force
  return targetWorld;
}

//-------------------------------------------------------------------------------------------------
Vec2f Steering::avoid_bounds(const class ShipInfo& ship, float deltaTime)
{
  CreateFeelers(ship);

  Vec2f maxForce(0, 0);
  for (int i = 0; i < 3; ++i)
  {
    Vec2f feeler = feelers_[i];
    if (feeler.x < -bounds_.x)
      maxForce = largest_magnitude(Vec2f(-bounds_.x - feeler.x, 0), maxForce);
    if (feeler.x > bounds_.x)
      maxForce = largest_magnitude(Vec2f(bounds_.x - feeler.x, 0), maxForce);
    if (feeler.y < -bounds_.y)
      maxForce = largest_magnitude(Vec2f(0, -bounds_.y - feeler.y), maxForce);
    if (feeler.y > bounds_.y)
      maxForce = largest_magnitude(Vec2f(0, bounds_.y - feeler.y), maxForce);
  }
  
  return maxForce;
}

//-------------------------------------------------------------------------------------------------
Vec2f Steering::seek(const class ShipInfo& self, const Vec2f& target)
{
  Vec2f desiredVelocity = (target - self.position()).normalized() * AICommand::kMaxSpeed;
  return desiredVelocity - self.velocity();
}

//-------------------------------------------------------------------------------------------------
Vec2f Steering::persuit(const class ShipInfo& self, const class ShipInfo& other)
{
  Vec2f toEvader = other.position() - self.position();
  Vec2f heading = self.velocity().normalized();
  Vec2f otherHeading = other.velocity().normalized();

  float relativeHeading = heading.dot(otherHeading);

  if ((toEvader.dot(heading) > 0) && relativeHeading < -0.95f)
    return seek(self, other.position());

  float lookAheadTime = toEvader.length() / (AICommand::kMaxSpeed + other.velocity().length());

  return seek(self, other.position() + other.velocity() * (lookAheadTime - 1.0f));
}

//-------------------------------------------------------------------------------------------------
void Steering::CreateFeelers(const class ShipInfo& ship)
{
  Vec2f heading = Vec2f(std::cos(ship.orientation()), std::sin(ship.orientation()));
  feelers_[0] = ship.position() + 40 * heading;

  float headingLeftOrient = ship.orientation() + 3.141592654f * 3.5 * 0.5f;
  Vec2f headingLeft = Vec2f(std::cos(headingLeftOrient), std::sin(headingLeftOrient));
  feelers_[1] = ship.position() + 40 * 0.5f * headingLeft;

  float headingRightOrient = ship.orientation() + 3.141592654f * 0.5 * 0.5f;
  Vec2f headingRight = Vec2f(std::cos(headingRightOrient), std::sin(headingRightOrient));
  feelers_[2] = ship.position() + 40 * 0.5f * headingRight;
}