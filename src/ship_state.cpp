#include "ship_state.h"
#include "faction_state.h"
#include <SDL_opengl.h>

//-------------------------------------------------------------------------------------------------
ShipState::ShipState(FactionState &faction, uint32_t id) :
  id_(id),
  faction_(faction),
  position_(0.0f, 0.0f), velocity_(0.0f, 0.0f),
  orientation_(0.0f), angularVelocity_(0.0f),
  maxHp_(100),
  hp_(maxHp_),
  force_(8.0f), torque_(1.0f),
  mass_(1.0f)
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
  glTranslatef(position_.x, position_.y, 0.0f);
  glRotatef(orientation_ * (180/3.141592654f), 0.0f, 0.0f, 1.0f);

  glBegin(GL_TRIANGLES);
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
  angularVelocity_ += angularAcceleration * deltaTime;
  orientation_ += angularVelocity_ * deltaTime;

  // Calculate the direction of force
  Float2 directionOfForce(-std::sin(orientation_), std::cos(orientation_));
  
  // Calculate the acceleration
  float acceleration = force_ / mass_;
  velocity_ += directionOfForce * acceleration * static_cast<float>(deltaTime);

  // Update the velocity
  position_ += velocity_ * deltaTime;
  
}