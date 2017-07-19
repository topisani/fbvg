#pragma once

#include <cmath>

namespace fbvg {

struct Transform;

struct vect {
  float x, y;

  vect(float x, float y) : x (x), y (y) {}

  void apply(const Transform &t);

  void rotate(float angle) {
    float s = std::sin(angle);
    float c = std::cos(angle);

    float nx = x * c - y * s;
    float ny = x * s + y * c;

    x = nx; y = ny;
  }

  bool operator==(const vect& r) {return x == r.x && y == r.y;}
  bool operator!=(const vect& r) {return x != r.x && y != r.y;}
  vect operator-(const vect& r) {return {x - r.x, y - r.y};}
  vect operator+(const vect& r) {return {x + r.x, y + r.y};}
};

struct Transform {

  float a = 1, b = 0; // î
  float c = 0, d = 1; // ĵ
  float tx = 0, ty = 0; // transform

  Transform() {}

  Transform(float a, float b, float c, float d, float tx, float ty) :
    a (a), b (b), c (c), d (d), tx (tx), ty (ty) {}

  Transform(vect i, vect j, vect t) :
    a (i.x), b (i.y), c (j.x), d (j.y), tx (t.x), ty (t.y) {}

  void translate(vect t) {
    tx += t.x * a + t.y * b;
    ty += t.x * c + t.y * d;
  }

  void rotate(float angle) {
    float fsin = std::sin(angle);
    float fcos = std::cos(angle);

    float na = a * fcos + c * fsin;
    float nb = b * fcos + d * fsin;
    float nc = c * fcos - a * fsin;
    float nd = d * fcos - b * fsin;

    a = na; b = nb; c = nc; d = nd;
  }

  void scale(float s) {
    a *= s;
    b *= s;
    c *= s;
    d *= s;
  }

  void scale(vect s) {
    a *= s.x;
    b *= s.x;
    c *= s.y;
    d *= s.y;
  }

  void concat(const Transform &t) {
    float na = a * t.a + b * t.c;
    float nb = a * t.b + b * t.d;
    float nc = c * t.a + d * t.c;
    float nd = c * t.b + d * t.d;
    float nx = tx * t.a + ty * t.b + t.tx;
    float ny = tx * t.c + ty * t.d + t.ty;

    a = na; b = nb; c = nc; d = nd; tx = nx; ty = ny;
  }

  void invert() {
    float det = 1.0f / (a * d - b * c);

    float na = det * d;
    float nb = -det * b;
    float nc = -det * c;
    float nd = det * a;
    float nx = det * (c * ty - d * tx);
    float ny = det * (b * tx - a * ty);

    a = na; b = nb; c = nc; d = nd; tx = nx; ty = ny;
  }

  bool isIdentity() {
    return a == 1 && b == 0 && c == 0 && d == 1 && tx == 0 && ty == 0;
  }

  vect apply(vect v) {
    return {
      tx + v.x * a + v.y * b,
      ty + v.x * c + v.y * d
    };
  }

  const static Transform identity;
};


// Out of line vect implementations
inline void vect::apply(const Transform& t) {
  float nx = t.tx + x * t.a + y * t.b;
  float ny = t.ty + x * t.c + y * t.d;

  x = nx; y = ny;
}

}
