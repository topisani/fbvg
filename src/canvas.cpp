#include "canvas.hpp"

#include "rasterizer.hpp"

namespace fbvg {

/****************************************/
/* Canvas Implementation                */
/****************************************/

Canvas& Canvas::save() {
  stateStack.push(state);
  return *this;
}

Canvas& Canvas::restore() {
  state = stateStack.top();
  stateStack.pop();
  return *this;
}

Canvas& Canvas::transform(const Transform& t) {
  state.transform.concat(t);
  return *this;
}

Canvas& Canvas::translate(vect v) {
  state.transform.translate(v);
  return *this;
}

Canvas& Canvas::scale(float s) {
  state.transform.scale(s);
  return *this;
}

Canvas& Canvas::scale(vect v) {
  state.transform.scale(v);
  return *this;
}

Canvas& Canvas::rotate(float angle) {
  state.transform.rotate(angle);
  return *this;
}

Canvas& Canvas::beginPath() {
  path = Path();
  return *this;
}

Canvas& Canvas::stroke() {
  rasterizer->drawPath(path, state);
  return *this;
}

Canvas& Canvas::moveTo(vect p) {
  path.moveTo(p);
  return *this;
}

Canvas& Canvas::lineTo(vect p) {
  path.lineTo(p);
  return *this;
}

}
