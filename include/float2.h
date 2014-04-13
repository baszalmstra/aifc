#pragma once

class Float2 final {

public:
  Float2() {};
  Float2(float x_, float y_) : x(x_), y(y_) {}
  Float2(float value) : x(value), y(value) {}

  ~Float2() {};

  /// Binary operators
  Float2 operator+(const Float2& other) { return Float2(x + other.x, y + other.y); }
  Float2 operator-(const Float2& other) { return Float2(x - other.x, y - other.y); }
  Float2 operator*(const Float2& other) { return Float2(x * other.x, y * other.y); }
  Float2 operator/(const Float2& other) { return Float2(x / other.x, y / other.y); }

  Float2 operator*(float scalar) { return Float2(x * scalar, y * scalar); }
  Float2 operator/(float scalar) { return Float2(x / scalar, y / scalar); }

  Float2 &operator+=(const Float2& other) { x += other.x; y += other.y; return *this; }
  Float2 &operator-=(const Float2& other) { x -= other.x; y -= other.y; return *this; }
  Float2 &operator*=(const Float2& other) { x *= other.x; y *= other.y; return *this; }
  Float2 &operator/=(const Float2& other) { x /= other.x; y /= other.y; return *this; }

  Float2 &operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
  Float2 &operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }
  
  

  union {
      struct { float x, y; };
      float m[2];
  };
};
