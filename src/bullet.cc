#include "bullet.h"
#include "faction_state.h"
#include <SDL_opengl.h>
#include <cmath>

//---------------------------------------------------------------------------------------------------
Bullet::Bullet(const FactionState & faction, float energy) :
  faction_(faction),
  energy_(energy),
  destroyed_(false)
{
  height_ = energy_/60 + 1.8f;
  set_collision_radius(0.1f);
}

//---------------------------------------------------------------------------------------------------
void Bullet::Update(float deltaTime)
{
  set_position(position() + velocity() * deltaTime);  
}

//---------------------------------------------------------------------------------------------------
void Bullet::Draw()
{
  Vec2f pos(position());

  // Draw all bullets
  float dirX = std::cos(orientation());
  float dirY = std::sin(orientation());  
  const float width = energy_/400.0f+0.2f;

  Color bulletColor(faction_.color());
  bulletColor.r *= 2.0f;
  bulletColor.g *= 2.0f;
  bulletColor.b *= 2.0f;

  Color darkBulletColor(faction_.color());
  darkBulletColor.r *= 0.1f;
  darkBulletColor.g *= 0.1f;
  darkBulletColor.b *= 0.1f;

  const float halfWidth = width*0.5f;
  glColor4fv(bulletColor);
  glVertex3f(height_*0.2f*dirX + pos.x, height_*0.2f*dirY + pos.y, 0.0f);
  glVertex3f(-halfWidth*dirY + pos.x, dirX*halfWidth + pos.y, 0.0f);
  glVertex3f(halfWidth*dirY + pos.x, dirX*-halfWidth + pos.y, 0.0f);
  glVertex3f(halfWidth*dirY + pos.x, dirX*-halfWidth + pos.y, 0.0f);
  glVertex3f(-halfWidth*dirY + pos.x, dirX*halfWidth + pos.y, 0.0f);
  glColor4fv(darkBulletColor);
  glVertex3f(-height_*0.8f*dirX + pos.x, -height_*0.8f*dirY + pos.y, 0.0f);
}
