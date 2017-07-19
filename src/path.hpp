#pragma once

#include <vector>

#include "transform.hpp"

namespace fbvg {

struct PolyLine {
  std::vector<vect> points;

  void addPoint(vect);
};

struct Path {

  PolyLine curLine;
  std::vector<PolyLine> lines;

  float strokeWidth;

  void addLine(PolyLine);

  void moveTo(vect);
  void lineTo(vect);
};

}
