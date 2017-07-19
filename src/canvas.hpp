#pragma once

#include <stack>

#include "transform.hpp"
#include "path.hpp"
#include "color.hpp"

namespace fbvg {

class Rasterizer;

struct CanvasState {

  Transform transform;
  float lineWidth;
  Color strokeColor;
};

class Canvas {

  Rasterizer *rasterizer;
  std::stack<CanvasState> stateStack;

  Path path;

public:

  CanvasState state;

  explicit Canvas(Rasterizer *r) : rasterizer (r) {}

  /****************************************/
  /* State                                */
  /****************************************/

  Canvas& save();

  Canvas& restore();

  /****************************************/
  /* Transformations                      */
  /****************************************/

  Canvas& transform(const Transform&);

  Canvas& translate(vect);

  Canvas& scale(float);
  Canvas& scale(vect);

  Canvas& rotate(float);

  /****************************************/
  /* Path handling                        */
  /****************************************/

  Canvas& beginPath();

  Canvas& stroke();

  /****************************************/
  /* Basic Drawing                        */
  /****************************************/

  Canvas& moveTo(vect);

  Canvas& lineTo(vect);
};

}
