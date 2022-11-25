#include "canvas.h"

using namespace TFT_eSPI_Widgets;

Canvas::Canvas():
  Widget(),
  _focus_widget(NULL)
{}

Canvas::Canvas(TFT_eSPI &tft,
               const GraphicalProperties &default_graphical_properties,
               const GraphicalProperties &focus_graphical_properties,
               const Area &area):
  Canvas()
{
  init(tft, default_graphical_properties, focus_graphical_properties, area);
}

void Canvas::init(TFT_eSPI &tft,
                  const GraphicalProperties &default_graphical_properties,
                  const GraphicalProperties &focus_graphical_properties,
                  const Area &area) {
  if (_tft) return;
  _tft = &tft;
  setDefaultGraphicalProperties(default_graphical_properties);
  if (&focus_graphical_properties == &GraphicalProperties::default_values) {
    setFocusGraphicalProperties(default_graphical_properties);
  } else {
    setFocusGraphicalProperties(focus_graphical_properties);
  }
  if (area.isEmpty()) {
    _area.width = tft.width();
    _area.height = tft.height();
    _area.x = 0;
    _area.y = 0;
  } else {
    _area = area;
  }
}
