#include "dimensions.h"

using namespace TFT_eSPI_Widgets;

const Dimensions Dimensions::empty(0, 0);

Dimensions::Dimensions(uint16_t w, uint16_t h): width(w), height(h) {}

static uint16_t _product(uint16_t v, float factor) {
  static uint16_t max_value = uint16_t(-1);
  static float max_value_as_float = float(max_value);
  factor = abs(factor);
  float res_as_float = float(v) * factor;
  uint16_t res = uint16_t(res_as_float);
  if (res_as_float > max_value_as_float) {
    res = max_value;
  }
  return res;
}

Dimensions &Dimensions::operator*=(float factor) {
  width = _product(width, factor);
  height = _product(height, factor);
  return *this;
}

Dimensions Dimensions::operator*(float factor) const {
  Dimensions res(*this);
  res *= factor;
  return res;
}
