#pragma once

#include "util/inttypes.hpp"
#include "canvas.hpp"

namespace fbvg {

struct Rasterizer {

  int height, width;
  uint depth; // bytes pr pixel
  byte* buffer;

  Rasterizer(byte* buffer, int h, int w, uint depth);

  void setPixel(int x, int y, const Color&);

  void drawPath(const Path&, const CanvasState&);

  void drawLine(vect v1, vect v2, const Color&);
};
}
