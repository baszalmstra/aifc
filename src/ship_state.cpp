#include "ship_state.h"
#include "faction_state.h"
#include <SDL_opengl.h>
#include <cmath>

//-------------------------------------------------------------------------------------------------
ShipState::ShipState(FactionState &faction, uint32_t id) :
  id_(id),
  faction_(faction),
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
  glTranslatef(position().x, position().y, 0.0f);
  glRotatef(orientation() * (180/3.141592654f), 0.0f, 0.0f, 1.0f);

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
  set_angular_velocity(angular_velocity() + angularAcceleration * deltaTime);
  set_orientation(orientation() + angular_velocity() * deltaTime);

  // Calculate the direction of force
  Vec2f directionOfForce(-std::sin(orientation()), std::cos(orientation()));
  
  // Calculate the acceleration
  float acceleration = force_ / mass_;
  set_velocity(velocity() + directionOfForce * acceleration * static_cast<float>(deltaTime));

  // Update the position
  set_position(position() + velocity() * deltaTime);
  
}
