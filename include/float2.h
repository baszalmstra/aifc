#pragma once

class Float2 final {

public:
  Float2() {};
  Float2(float x_, float y_) : x(x_), y(y_) {}
  Float2(float value) : x(value), y(value) {}

  ~Float2() {};

  union {
      struct { float x, y; };
      float m[2];
  };
};
