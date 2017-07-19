#include "rasterizer.hpp"

#include <algorithm>

namespace fbvg {

Rasterizer::Rasterizer(byte* buff, int w, int h, uint d) :
  buffer (buff), width (w), height (h), depth (d) {}

void Rasterizer::setPixel(int x, int y, const Color &c) {
  buffer[(x * width + y) * depth + 0] = c.r;
  buffer[(x * width + y) * depth + 1] = c.g;
  buffer[(x * width + y) * depth + 2] = c.b;
}

void Rasterizer::drawPath(const Path& path, const CanvasState& state) {

  for (auto &&line : path.lines) {
    if (line.points.size() == 0) continue;
    auto it = line.points.begin();
    vect lastP = *it;
    it++;
    for (auto end = line.points.end(); it != end; it++) {
      vect p = *it;
      drawLine(lastP, p, state.strokeColor);
      lastP = p;
    }
  }
}

void Rasterizer::drawLine(vect v1, vect v2, const Color& c) {
  int dx =  std::abs(v2.x - v1.x);
  int dy = -std::abs(v2.y - v1.y);
  int sx = v1.x < v2.x ? 1 : -1;
  int sy = v1.y < v2.y ? 1 : -1;
  int err = dx + dy, e2;
 
  int x = v1.x, y = v1.y;
  int endX = v2.x, endY = v2.y;
  for(;;) {  /* loop */
    setPixel(x, y, c);
    if (x == endX && y == endY) break;
    e2 = 2*err;
    if (e2 >= dy) { err += dy; x += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y += sy; } /* e_xy+e_y < 0 */
  }
}
}
