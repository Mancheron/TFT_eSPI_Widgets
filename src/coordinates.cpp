#include "coordinates.h"

using namespace TFT_eSPI_Widgets;

const Coordinates Coordinates::origin(0, 0);

Coordinates::Coordinates(): x(0), y(0) {}

Coordinates::Coordinates(int32_t x, int32_t y): x(x), y(y) {}

Coordinates &Coordinates::operator+=(const Coordinates &coords) {
  x += coords.x;
  y += coords.y;
  return *this;
}

Coordinates Coordinates::operator+(const Coordinates &coords) const {
  Coordinates res(*this);
  res += coords;
  return res;
}

Coordinates &Coordinates::operator-=(const Coordinates &coords) {
  x -= coords.x;
  y -= coords.y;
  return *this;
}

Coordinates Coordinates::operator-(const Coordinates &coords) const {
  Coordinates res(*this);
  res -= coords;
  return res;
}
