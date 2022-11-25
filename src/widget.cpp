#include "widget.h"

using namespace TFT_eSPI_Widgets;

#define TYPE2CSTR_CASE(t) case t: return #t

const char *Widget::getTypeString(Type t) {
  switch (t) {
    TYPE2CSTR_CASE(CANVAS);
    TYPE2CSTR_CASE(GENERIC);
    TYPE2CSTR_CASE(CUSTOM);
  }
}

Widget::Widget():
  _root(*this),
  _parent(*this),
  _child(NULL),
  _area(),
  _default_graph_props(),
  _focus_graph_props(),
  _need_update(false),
  _event_handler_cb(NULL),
  _loop_cb(NULL),
  _focus_cb(NULL),
  _unfocus_cb(NULL)
{}

Widget::Widget(Widget &parent, const Area &area):
  _root(parent._root),
  _parent(parent),
  _child(NULL),
  _area(area),
  _default_graph_props(parent._default_graph_props),
  _focus_graph_props(parent._focus_graph_props),
  _need_update(false),
  _event_handler_cb(NULL),
  _loop_cb(NULL),
  _focus_cb(NULL),
  _unfocus_cb(NULL)
{
  if (_area.isEmpty()) {
    uint8_t b = max(_default_graph_props.getBorderSize(), _focus_graph_props.getBorderSize());
    _area = parent._area;
    _area.width -= 2 * b;
    _area.height -= 2 * b;
    _area.x += b;
    _area.y += b;
  } else {
    _area.x += parent._area.x;
    _area.y += parent._area.y;
  }
  _parent.removeChild();
  _parent._child = this;
}

Widget::~Widget() {
  removeChild();
  if (&_root != this) {
    _parent._child = NULL;
    yield();
  }
}

void Widget::removeChild() {
  if (_child) {
    delete _child;
    _child = NULL;
    yield();
  }
}

void Widget::focus() {
  if (_focus_cb) {
    _focus_cb(*this);
  }
  _setFocus(*this);
  touch();
}

void Widget::unfocus() {
  if (_unfocus_cb) {
    _unfocus_cb(*this);
  }
  _unsetFocus(*this);
  touch();
}

void Widget::eventHandler(Event event) {
  if (hasFocus()) {
    bool raise_event = (!_event_handler_cb or _event_handler_cb(*this, event));
    if (event == LONG_RIGHT_CLICK) {
      unfocus();
    } else {
      if (raise_event) {
        _eventHandler(event);
      }
    }
  }
}

void Widget::draw() {
  if (!_need_update) return;
  const GraphicalProperties &props = getGraphicalProperties();
  TFT_eSPI &tft = getTFT();
  tft.setViewport(_area.x, _area.y, _area.width, _area.height);
  tft.fillScreen(props.getBackgroundColor());
  if (props.getBorderSize()) {
    tft.frameViewport(props.getBorderColor(), props.getBorderSize());
  }
  tft.setTextSize(props.getFontSize());
  tft.setTextColor(props.getFontColor());
  yield();
  _draw();
  yield();
  tft.resetViewport();
  if (_child) {
    _child->touch();
  }
  _need_update = false;
  yield();
}

void Widget::refresh() {
  draw();
  if (_child) {
    _child->refresh();
  }
  yield();
}

void Widget::loop(bool recurse) {
  if (_loop_cb) {
    _loop_cb(*this);
    yield();
  }
  _loop();
  yield();
  if (recurse and _child) {
    _child->loop(recurse);
  }
}
