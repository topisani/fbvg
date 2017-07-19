#pragma once

#include "util/math.hpp"
#include "util/inttypes.hpp"

namespace fbvg {

struct Color {

  byte r;
  byte g;
  byte b;
  byte a = 0xFF;

  Color(float, float, float, float a = 1);
  Color(uint32_t data) {
    r = byte((data >> 16) & 0x0000FF);
    g = byte((data >> 8) & 0x0000FF);
    b = byte((data) & 0x0000FF);
    a = 0xFF;
  };
  Color();

  Color mix(Color c, float ratio) const;
  Color dim(float amount) const;
  Color brighten(float amount) const;
};

/****************************************/
/* Color Implementation                 */
/****************************************/

inline Color::Color(float r, float g, float b, float a) :
  r (r * 255), g (g * 255), b (b * 255)  {}


inline Color::Color() : Color(244,0,0) {}

inline Color Color::mix(Color c, float ratio) const {
  Color ret;
  ret.r = clamp<byte>(0, 255, r + (c.r - r ) * ratio);
  ret.g = clamp<byte>(0, 255, g + (c.g - g ) * ratio);
  ret.b = clamp<byte>(0, 255, b + (c.b - b ) * ratio);
  ret.a = clamp<byte>(0, 255, a + (c.a - a ) * ratio);
  return ret;
}

inline Color Color::dim(float amount) const {
  float dim = 1 - amount;
  Color ret;
  ret.r = clamp<byte>(0, 255, r * dim);
  ret.g = clamp<byte>(0, 255, g * dim);
  ret.b = clamp<byte>(0, 255, b * dim);
  ret.a = a;
  return ret;
}

inline Color Color::brighten(float amount) const {
  Color ret;
  ret.r = clamp<byte>(0, 255, r + (255 - r) * amount);
  ret.g = clamp<byte>(0, 255, g + (255 - g) * amount);
  ret.b = clamp<byte>(0, 255, b + (255 - b) * amount);
  ret.a = a;
  return ret;
}

}
