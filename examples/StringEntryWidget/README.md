String Entry Widget Demo {#StringEntryWidgetDemo}
========================

[Doxygen tag -- don't remove]: @example{lineno} StringEntryWidget.ino

[Widget]: @ref TFT_eSPI_Widgets::Widget "Widget"

[ButtonHandler]: @ref TFT_eSPI_Widgets::ButtonHandler "Button Handler"

[StringEntryWidget]: @ref TFT_eSPI_Widgets::StringEntryWidget "String Entry Widget"

[Button2]: https://github.com/LennartHennigs/Button2

[Button2Ref]: https://www.arduino.cc/reference/en/libraries/button2/

This demo illustrates how to use a string entry widget.

The demo uses two buttons (say the left and the right button),
respectively connected to the GPIO 35 and GPIO 0 (which are the pins
used on a TTGO T-Display). The buttons are handled using the
[ButtonHandler] class provided with this library, but it is
recommended to use a more sophisticated library like [Button2][] (see
also [Button2 on Arduino reference][Button2Ref]).

By design, we can unfocus any [Widget] by clicking trice on the left
button and give the focus to the child of the focus [Widget] or to the
canvas if no [Widget] has the focus by clicking trice on the right
button.

The [StringEntryWidget] is initialized with the `"Hello World"`
value. When this [widget][StringEntryWidget] has the focus, the cursor
is blinking. On start, it is positioned after the last character.

A single left (respectively right) button click will change the ASCII
symbol at the current cursor position to the previous (respectively
next) one in the ASCII order. If there is no previous/next available
symbol, then cycle to the end/beginning. A long press on the
left/right button will change quickly the current character. A double
left (respectively right) click moves the cursor one position to the
left (respectively right) if possible.

<!--
Local Variables:
eval: (flyspell-mode)
ispell-local-dictionary: "american"
End:
-->
