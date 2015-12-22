#pragma once

#include "math_types.h"

class Steering
{
public:
  Steering(const Vec2f& bounds);

  Vec2f wander(const class ShipInfo& ship, float deltaTime);
  Vec2f avoid_bounds(const class ShipInfo& ship, float deltaTime);
  Vec2f seek(const class ShipInfo& self, const Vec2f& target);
  Vec2f persuit(const class ShipInfo& self, const class ShipInfo& other);

private:
  void CreateFeelers(const class ShipInfo& ship);

public:
  float wanderRadius = 1.0f;
  float wanderDistance = 0.5f;
  float wanderJitter = 40.0f;

private:
  Vec2f bounds_;
  Vec2f wanderTarget_;

  Vec2f feelers_[3];
};