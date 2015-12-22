#include "ship_state.h"
#include "faction_state.h"
#include "bullet.h"
#include <SDL_opengl.h>
#include <cmath>
#include <algorithm>
#include "ai_command.h"

//-------------------------------------------------------------------------------------------------
namespace {
  const float MaxWeaponEnergy = 100.0f;
  const float MinWeaponFireThreshold = 10.0f;
}

//-------------------------------------------------------------------------------------------------
ShipState::ShipState() : id_(0)
{

}

//-------------------------------------------------------------------------------------------------
ShipState::ShipState(FactionState &faction, uint32_t id) :
  id_(id),
  faction_(&faction),
  maxHp_(100),
  hp_(maxHp_),
  force_(0.0f),
  mass_(1.0f), 
  weaponEnergy_(0.0f),
  weaponRechargeRate_(50.0f),
  hitTime_(0.0f)
{

}

//-------------------------------------------------------------------------------------------------
ShipState::~ShipState()
{

}

//-------------------------------------------------------------------------------------------------
void ShipState::Draw()
{
  glPushMatrix();
  glTranslatef(position().x, position().y, 0.0f);
  glRotatef(orientation() * (180/3.141592654f), 0.0f, 0.0f, 1.0f);

  glBegin(GL_TRIANGLES);
    if (hitTime_ > 0)
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else
      glColor4fv(faction_->color());
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.2f, 0.0f, 0.0f);
    glVertex3f(0.2f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.5f, 0.0f);        
  glEnd();

  glPopMatrix();
}

//-------------------------------------------------------------------------------------------------
void ShipState::Update(float deltaTime)
{
  // Determine acceleration
  Vec2f accel = force_ / mass_;
  force_ = Vec2f(0, 0);

  // Update velocity
  Vec2f newVelocity = velocity() + accel*deltaTime;
  float velocityLengthSquared = newVelocity.lengthSquared();
  if (velocityLengthSquared > AICommand::kMaxSpeed*AICommand::kMaxSpeed)
    newVelocity = newVelocity / std::sqrt(velocityLengthSquared) * AICommand::kMaxSpeed;

  // Set the velocity
  set_velocity(newVelocity);

  // Update the orientation
  if (newVelocity.lengthSquared() > 0)
  {
    set_orientation(std::atan2(newVelocity.y, newVelocity.x));
  }

  // Update the position
  set_position(position() + velocity() * deltaTime);

  // Add weapon energy
  weaponEnergy_ = std::min(MaxWeaponEnergy, weaponEnergy_ + weaponRechargeRate_ * deltaTime);  

  hitTime_ -= deltaTime;
}

//-------------------------------------------------------------------------------------------------
bool ShipState::can_fire() const
{
  return weaponEnergy_ >= MinWeaponFireThreshold;
}

//-------------------------------------------------------------------------------------------------
bool ShipState::OnHit(const Bullet& bullet)
{
  hitTime_ = 0.2f;

  if (bullet.energy() > hp())
  {
    hp_ = 0;
    return true;
  }

  hp_ -= (uint16_t)bullet.energy();
  return false;
}