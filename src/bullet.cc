#include "bullet.h"
#include "faction_state.h"
#include <SDL_opengl.h>
#include <cmath>

//---------------------------------------------------------------------------------------------------
Bullet::Bullet(const FactionState & faction) :
  faction_(faction),
  energy_(0.0f)
{
  
  
}

//---------------------------------------------------------------------------------------------------
void Bullet::Update(float deltaTime)
{
  
  
}

//---------------------------------------------------------------------------------------------------
void Bullet::Draw()
{
  Vec2f pos(0.0f, std::fmod((float) 0.0f * 100, 50.0f));

  // Draw all bullets
  float orientation_ = 0;
  float dirY = std::cos(orientation_);
  float dirX = std::sin(orientation_);
  const float width = 0.2f * energy_;
  const float height = 1.8f * energy_;

  const float halfWidth = width*0.5f;
  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  glVertex3f(height*0.2f * -dirX + pos.x, height*0.2f * dirY + pos.y, 0.0f);
  glVertex3f(-halfWidth*dirY + pos.x, -halfWidth*dirX + pos.y, 0.0f);
  glVertex3f(halfWidth*dirY + pos.x, halfWidth*dirX + pos.y, 0.0f);
  glVertex3f(halfWidth*dirY + pos.x, halfWidth*dirX + pos.y, 0.0f);
  glVertex3f(-halfWidth*dirY + pos.x, -halfWidth*dirX + pos.y, 0.0f);
  glColor4f(0.0f, 0.1f, 0.0f, 0.3f);
  glVertex3f(-height*0.8f*-dirX + pos.x, -height*0.8f*dirY + pos.y, 0.0f);  
}
