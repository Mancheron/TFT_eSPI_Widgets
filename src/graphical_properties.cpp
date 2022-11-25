#include "graphical_properties.h"

using namespace TFT_eSPI_Widgets;

const GraphicalProperties GraphicalProperties::default_values;

GraphicalProperties::GraphicalProperties(uint16_t background_color,
                                         uint16_t border_color,
                                         uint16_t font_color,
                                         uint8_t border_size,
                                         uint8_t font_size):
  _background_color(background_color),
  _border_color(border_color),
  _font_color(font_color),
  _border_size(border_size),
  _font_size(font_size)
{}
