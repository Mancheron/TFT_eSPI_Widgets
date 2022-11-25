#include "area.h"

using namespace TFT_eSPI_Widgets;

const Area Area::reference_value;

Area::Area(uint16_t w, uint16_t h, int32_t x, int32_t y):
  Dimensions(w, h),
  Coordinates(x, y)
{}

Area::Area(const Dimensions &dim, const Coordinates &top_left):
  Dimensions(dim),
  Coordinates(top_left)
{}

bool Area::overlap(const Area &area) const {
  return ((((x <= area.x) and (area.x <= x + width)) or
           ((area.x <= x) and (x <= area.x + area.width))) and
          (((y <= area.y) and (area.y <= y + height)) or
           ((area.y <= y) and (y <= area.y + area.height))));
}

bool Area::contains(const Area &area) const {
  return (((x <= area.x) and (area.x + area.width <= x + width)) and
          ((y <= area.y) and (area.y + area.height <= y + height)));
}

bool Area::contains(const Coordinates &coords) const {
  return (((x <= coords.x) and (coords.x <= x + width)) and
          ((y <= coords.y) and (coords.y <= y + height)));
}
