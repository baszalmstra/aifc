#pragma once

#include "math_types.h"

class Entity
{
protected:
  Entity();

public:
  virtual ~Entity();

  /// Returns the velocity of the ship
  const Vec2f& velocity() const { return velocity_; }

  /// Sets the velocity of the object
  void set_velocity(const Vec2f& velocity) { velocity_ = velocity; }

  /// Returns the angular velocity
  float angular_velocity() const { return angularVelocity_; }

  /// Sets the angular velocity
  void set_angular_velocity(float angularVelocity) { angularVelocity_ = angularVelocity; }

  /// Returns the collision radius of the ship
  float collision_radius() const { return collisionRadius_; }

  /// Sets the collision radius of the the object
  void set_collision_radius(float radius) { collisionRadius_ = radius; }

  /// Returns the position of the ship
  const Vec2f& position() const { return position_; }

  /// Sets the position of the ship
  void set_position(const Vec2f& position) { position_ = position; }

  /// Returns the orientation of the ship
  float orientation() const { return orientation_; }

  /// Sets the orientation of the ship
  void set_orientation(float orientation) { orientation_ = orientation; }

public:
  /// Called to draw the object
  virtual void Draw() = 0;

  /// Called to update the object
  virtual void Update(float deltaTime) = 0;

private:
  Vec2f position_, velocity_;
  float orientation_, angularVelocity_;
  float collisionRadius_;
};