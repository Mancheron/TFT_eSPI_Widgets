Float Entry Widget demo {#FloatEntryWidgetDemo}
=======================

[See [FloatEntryWidget.ino](./FloatEntryWidget_8ino-example.html)]: @example{lineno} FloatEntryWidget.ino

[Widget]: @ref TFT_eSPI_Widgets::Widget "Widget"

[ButtonHandler]: @ref TFT_eSPI_Widgets::ButtonHandler "Button Handler"

[FloatEntryWidget]: @ref TFT_eSPI_Widgets::FloatEntryWidget "Float Entry Widget"

[Button2]: https://github.com/LennartHennigs/Button2

[Button2Ref]: https://www.arduino.cc/reference/en/libraries/button2/

This demo shows how to use an [FloatEntryWidget].

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

The [FloatEntryWidget] has the focus on start.

On start, the value of the [FloatEntryWidget] is set to 0 with an
adaptive precision of two digits (according to the main exponent of
the power of ten).

Still by design, when the [FloatEntryWidget] has the focus, a single
click on the left button decrease the value whereas a single right
click increase the value.

In this demo, there is an additional callback function associated to
the [FloatEntryWidget] event handling in order to handle double left
click and double right click. When the double click comes from the
left button, the float entry value is decremented 10 times whereas
when the double click comes from the right button, the float entry
value is incremented 10 times.

<!--
Local Variables:
eval: (flyspell-mode)
ispell-local-dictionary: "american"
End:
-->
