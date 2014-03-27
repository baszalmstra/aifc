#pragma once

#include <cstdint>

// --------------------------------------------------------------------------------

template<typename T>
class Vec2 final
{

public:
  Vec2() {}
  Vec2(T x_, T y_) : x(x_), y(y_) {}
  Vec2(T value) : x(value), y(value) {}

  ~Vec2() {}

  /// returns dot product
  T dot(const Vec2& v) const { return x * v.x + y * v.y; }

  /// returns addition of this and v
  Vec2 operator+(const Vec2& v) const {  return Vec2(x + v.x, y + v.y); }

  /// returns this minus v
  Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }

  /// multiplies vector with a scalar
  Vec2 operator*(T s) const { return Vec2(x * s, y * s); }

  /// multiplies vector with a scalar
  friend Vec2 operator*(T s, const Vec2& v) { return Vec2(v.x * s, v.y * s); }

  union {
      struct { T x, y; };
      T m[2];
  };
};

// --------------------------------------------------------------------------------

template<typename T>
class Vec3 final
{

public:
  Vec3() {}
  Vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
  Vec3(T value) : x(value), y(value), z(value) {}

  ~Vec3() {}

  /// returns dot product
  T dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

  /// returns cross product
  T cross(const Vec3& v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x ); }

  /// returns addition with v
  Vec3 operator+(const Vec3& v) const {  return Vec3(x + v.x, y + v.y, z + v.z); }

  /// returns this minus v
  Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }

  /// multiplies vector with a scalar
  Vec3 operator*(T s) const { return Vec3(x * s, y * s, z * s); }

  /// multiplies vector with a scalar
  friend Vec3 operator*(T s, const Vec3& v) { return Vec3(v.x * s, v.y * s, v.z * s); }

  union {
      struct { T x, y, z; };
      T m[3];
  };
};

typedef Vec2<float> Vec2f;
typedef Vec2<uint16_t> Vec2i16;
typedef Vec2<uint32_t> Vec2i32;

typedef Vec3<float> Vec3f;
typedef Vec3<uint16_t> Vec3i16;
typedef Vec3<uint32_t> Vec3i32;
