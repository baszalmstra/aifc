#include "ship_state.h"
#include <SDL_opengl.h>

//-------------------------------------------------------------------------------------------------
ShipState::ShipState() :
  position_(0.0f, 0.0f),
  orientation_(0.0f),
  maxHp_(100),
  hp_(maxHp_)
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
  glRotatef(orientation_, 0.0f, 0.0f, 1.0f);

  glBegin(GL_TRIANGLES);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.2f, 0.0f);
    glVertex3f(0.0f, 0.2f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 0.0f);        
  glEnd();

  glPopMatrix();
}
