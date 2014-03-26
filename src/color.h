#pragma once

class Color
{
public:
  Color() {};
  Color(float r_, float g_, float b_, float a_ = 1.0f) : r(r_), g(g_), b(b_), a(a_) {};

  operator float*() { return elems; }
  operator float const*() const { return elems; }

public:
  union
  {
    struct { float r, g, b, a; };
    float elems[4];
  };
};