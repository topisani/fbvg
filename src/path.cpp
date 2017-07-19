#include "path.hpp"

namespace fbvg {

void PolyLine::addPoint(vect v) {
  points.emplace_back(v);
}

void Path::addLine(PolyLine l) {
  lines.emplace_back(l);
}

void Path::moveTo(vect v) {
  addLine(curLine);
  curLine = PolyLine();
  curLine.addPoint(v);
}

void Path::lineTo(vect v) {
  curLine.points.emplace_back(v);
}
}
