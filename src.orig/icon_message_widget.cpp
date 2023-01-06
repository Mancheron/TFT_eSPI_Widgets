#include "ls_icon_message_widget.h"
#include "../ls_messages.h"

using namespace TFT_eSPI_Widgets;

IconMessageWidget::IconMessageWidget(Widget &parent,
                                     const String &message,
                                     const String &icon,
                                     bool wrap,
                                     bool horizontal_split,
                                     int8_t ratio,
                                     const Dimensions &area):
  Widget(parent, area)
{
  Dimensions
    icon_area = Dimensions::empty,
    message_area = Dimensions::empty;
  int8_t abs_ratio = abs(constrain(ratio, -100, 100));
  if (horizontal_split) {
    icon_area.w = _area.w * abs_ratio / 100;
    icon_area.h = _area.h;
    message_area.w = _area.w - icon_area.w;
    message_area.h = _area.h;
    if (ratio > 0) {
      icon_area.top_left.x = 0;
      message_area.top_left.x = icon_area.w;
    } else {
      icon_area.top_left.x = message_area.w;
      message_area.top_left.x = 0;
    }
    icon_area.top_left.y = 0;
    message_area.top_left.y = 0;
  } else {
    icon_area.w = _area.w;
    icon_area.h = _area.h * abs_ratio / 100;
    message_area.w = _area.w;
    message_area.h = _area.h - icon_area.h;
    icon_area.top_left.x = 0;
    message_area.top_left.x = 0;
    if (ratio > 0) {
      icon_area.top_left.y = 0;
      message_area.top_left.y = icon_area.h;
    } else {
      icon_area.top_left.y = message_area.h;
      message_area.top_left.y = 0;
    }
  }
  new ImageWidget(*this, icon, icon_area);
  new MessageWidget(*this, message, wrap, message_area);
  makeFinal();
}

void IconMessageWidget::_loop() {
  getMessageWidget().loop();
}
