#include "ls_ipv4_widget.h"
#include "../ls_messages.h"
#include <list>

using namespace TFT_eSPI_Widgets;
using namespace std;

IPv4Widget::IPv4Widget(Widget &parent,
                       const IPAddress &ip,
                       const Dimensions &area):
  Widget(parent, area),
  _current_field(0)
{
  GraphicalProperties default_props = getDefaultGraphicalProperties();
  GraphicalProperties focus_props = getFocusGraphicalProperties();
  uint8_t border_size = max(default_props.getBorderSize(),
                            focus_props.getBorderSize());

  default_props.setBorderSize(0); // No border for unfocus entries and for dots

  TFT_eSPI &tft = getTFT();
  Dimensions char_dims(tft.textWidth("0"), tft.fontHeight());

  Dimensions field_area(3 * char_dims.w + 2 * border_size,
                        char_dims.h + 2 * border_size,
                        Coordinates(border_size, border_size));
  Dimensions dot_area = char_dims;
  dot_area.top_left.x = field_area.w + border_size;

  for (size_t i = 0; i < 4 ; ++i) {
    IntegerEntryWidget *widget = new IntegerEntryWidget(*this, ip[i], 0, 255, field_area);
    widget->setDefaultGraphicalProperties(default_props);
    field_area.top_left.x += field_area.w + dot_area.w;
  }

  for (size_t i = 0; i < 3 ; ++i) {
    MessageWidget *widget = new MessageWidget(*this, ".", false, dot_area);
    widget->setDefaultGraphicalProperties(default_props);
    dot_area.top_left.x += field_area.w + dot_area.w;
  }

  makeFinal();
}


IPAddress IPv4Widget::getValue() const {
  IPAddress ip;
  list<Widget *>::const_iterator it = _children.begin();
  for (size_t i = 0; i < 4 ; ++i) {
    const IntegerEntryWidget *ptr = static_cast<const IntegerEntryWidget *>(*it);
    ip[i] = ptr->getValue();
    ++it;
  }
  return ip;
}

void IPv4Widget::setValue(const IPAddress &ip) {
  list<Widget *>::iterator it = _children.begin();
  for (size_t i = 0; i < 4 ; ++i) {
    IntegerEntryWidget *ptr = static_cast<IntegerEntryWidget *>(*it);
    ptr->setValue(ip[i]);
    ++it;
  }
}

void IPv4Widget::_giveFocus() {
  list<Widget *>::iterator it = _children.begin();
  for (size_t i = 0; i < _current_field ; ++i) {
    ++it;
  }
}

void IPv4Widget::_eventHandler(Event event) {
  switch (event) {
  case SIMPLE_LEFT_CLICK:
    if (++_current_field >= 4) {
      _current_field = 0;
    }
    _giveFocus();
    break;
  case SIMPLE_RIGHT_CLICK:
    if (!_current_field--) {
      _current_field = 4;
    }
    _giveFocus();
    break;
  case DOUBLE_RIGHT_CLICK:
    unfocus();
  }
  touch();
}
