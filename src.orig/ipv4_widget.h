#ifndef __LS_IPV4_WIDGET_H__
#define __LS_IPV4_WIDGET_H__

#include <Arduino.h>
#include <ESP_lego_sequencer/lib/widgets/ls_widget.h>
#include <ESP_lego_sequencer/lib/widgets/ls_message_widget.h>
#include <ESP_lego_sequencer/lib/widgets/ls_integer_entry_widget.h>

namespace TFT_eSPI {

  namespace Widgets {

    /**
     * A simple message Widget with an icon.
     */
    class IPv4Widget: public Widget {

    protected:
      uint8_t _current_field;

      /**
       * Give focus to the current field widget.
       */
      void _giveFocus();

      /**
       * Handling some events when Widget has focus.
       *
       * Events Handled:
       *   - Simple left click => set focus on the next field (cycling to the first)
       *   - Simple right click => set focus on the previous field (cycling to the last)
       *   - Double right click => unfocus
       */
      virtual void _eventHandler(Event event);

    public:
      /**
       * Creates a wrapper widget having four integer entry widgets
       * separated by dots (message widgets) attached to the given
       * Widget.
       *
       * If the dimensions are not specified, then use the dimensions
       * of its parent. The top_left attribute of the dimensions is
       * relative to the top_left corner of its parent.
       *
       * The widget graphical properties (background color, line
       * color, line width, font color, font size) are inherited from
       * the parent widget.
       *
       * The initial values of each integer entries are set according
       * to the IP address initial value.
       *
       * This widget is final (can't have any more children than the
       * integer entry widgets and the message [dots] widgets).
       */
      IPv4Widget(Widget &parent,
                 const IPAddress &ip = IPAddress(0, 0, 0, 0),
                 const Dimensions &area = Dimensions::empty);

      /**
       * Return the IPV4_ENTRY widget type.
       */
      inline virtual Type getType() const {
        return IPV4_ENTRY;
      }

      /**
       * Get the current IP address value.
       */
      IPAddress getValue() const;

      /**
       * Set the current IP address value to the widget.
       */
      void setValue(const IPAddress &ip);

    };
  }
}

#endif
// Local Variables:
// mode: c++
// End:
