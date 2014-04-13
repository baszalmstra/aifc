#include "ship_state.h"
#include "faction_state.h"
#include "bullet.h"
#include <SDL_opengl.h>
#include <cmath>
#include <algorithm>

//-------------------------------------------------------------------------------------------------
namespace {
  const float MaxWeaponEnergy = 100.0f;
  const float MinWeaponFireThreshold = 10.0f;
}

//-------------------------------------------------------------------------------------------------
ShipState::ShipState(FactionState &faction, uint32_t id) :
  id_(id),
  faction_(faction),
  maxHp_(100),
  hp_(maxHp_),
  force_(0.0f), torque_(0.0f),
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
      glColor4fv(faction_.color());
    glVertex3f(0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.2f, 0.0f);
    glVertex3f(0.0f, 0.2f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 0.0f);        
  glEnd();

  glPopMatrix();
}

//-------------------------------------------------------------------------------------------------
void ShipState::Update(float deltaTime)
{
  // Calculate the angular acceleration
  float angularAcceleration = torque_ / mass_;
  set_angular_velocity(angular_velocity() + angularAcceleration * deltaTime);
  set_orientation(orientation() + angular_velocity() * deltaTime);

  // Calculate the direction of force
  Vec2f directionOfForce(-std::sin(orientation()), std::cos(orientation()));
  
  // Calculate the acceleration
  float acceleration = force_ / mass_;
  set_velocity(velocity() + directionOfForce * acceleration * static_cast<float>(deltaTime));

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