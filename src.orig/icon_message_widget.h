#ifndef __LS_ICON_MESSAGE_WIDGET_H__
#define __LS_ICON_MESSAGE_WIDGET_H__

#include <Arduino.h>
#include <ESP_lego_sequencer/lib/widgets/ls_widget.h>
#include <ESP_lego_sequencer/lib/widgets/ls_image_widget.h>
#include <ESP_lego_sequencer/lib/widgets/ls_message_widget.h>

namespace TFT_eSPI {

  namespace Widgets {

    /**
     * A simple message Widget with an icon.
     */
    class IconMessageWidget: public Widget {

    protected:
      virtual void _draw();
      virtual void _loop();

    public:
      /**
       * Creates a wrapper widget having a message widget with an icon
       * widget attached to the given Widget.
       *
       * If the dimensions are not specified, then use the dimensions
       * of its parent. The top_left attribute of the dimensions is
       * relative to the top_left corner of its parent.
       *
       * The widget graphical properties (background color, line
       * color, line width, font color, font size) are inherited from
       * the parent widget.
       *
       * The widget area is splitted either horizontally if
       * horizontal_split is true (default) or vertically otherwise.
       *
       * The absolute value of the ratio is the percentage of the
       * widget area used for the icon widget and the other part is
       * used for the message widget.
       *
       * A positive ratio means that the icon is displayed in the
       * first part (left/top) and a negative ratio means that the
       * icon is displayed in the other part (right/bottom). The ratio
       * is constrained to the range from -100% to 100% and is set to
       * 15% by default.
       *
       * If the wrap parameter is true and the wrapped text doesn't
       * fit vertically, the text will be animated from bottom to top.
       *
       * If the wrap parameter is false and the wrapped text doesn't
       * fit horizontally, the text will be animated from right to left.
       *
       * This widget is final (can't have any more children than the
       * icon widget and the message widget).
       */
      IconMessageWidget(Widget &parent,
                        const String &message,
                        const String &icon,
                        bool wrap = false,
                        bool horizontal_split = true,
                        int8_t ratio = 15,
                        const Dimensions &area = Dimensions::empty);

      /**
       * Return the ICON_MESSAGE widget type.
       */
      inline virtual Type getType() const {
        return ICON_MESSAGE;
      }

      /**
       * Get the child Image Widget .
       */
      inline ImageWidget &getIconWidget() const {
        return *static_cast<ImageWidget *>(_children.front()); // Use static_cast since g++ is given the option -fno_rtti
      }

      /**
       * Get the child Message Widget.
       */
      inline MessageWidget &getMessageWidget() const {
        return *static_cast<MessageWidget *>(_children.back()); // Use static_cast since g++ is given the option -fno_rtti
      }

    };
  }
}

#endif
// Local Variables:
// mode: c++
// End:
