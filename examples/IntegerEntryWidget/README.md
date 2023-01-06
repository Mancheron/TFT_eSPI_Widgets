Integer Entry Widget demo {#IntegerEntryWidgetDemo}
=========================

[Doxygen tag -- don't remove]: \example{lineno} IntegerEntryWidget.ino

[Widget]: @ref TFT_eSPI_Widgets::Widget "Widget"

[ButtonHandler]: @ref TFT_eSPI_Widgets::ButtonHandler "Button Handler"

[IntegerEntryWidget]: @ref TFT_eSPI_Widgets::IntegerEntryWidget "Integer Entry Widget"

[Button2]: https://github.com/LennartHennigs/Button2

[Button2Ref]: https://www.arduino.cc/reference/en/libraries/button2/

This demo shows how to use an [IntegerEntryWidget].

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

The [IntegerEntryWidget] has the focus on start.

On start, the value of the [IntegerEntryWidget] is set to 42. The
value is also constrained into the range [-30, 120].

Still by design, when the [IntegerEntryWidget] has the focus, a single
click on the left button decrease the value whereas a single right
click increase the value.

In this demo, there is an additional callback function associated to
the [IntegerEntryWidget] event handling in order to handle double left
click and double right click. When the double click comes from the
left button, the integer entry value is decremented by 10 whereas when
the double click comes from the right button, the integer entry value
is incremented by 10.

The background of the [IntegerEntryWidget] is updated according to the
current value (from blue when value is -30 to red when value is 120
going through yellow).

<!--
Local Variables:
eval: (flyspell-mode)
ispell-local-dictionary: "american"
End:
-->
