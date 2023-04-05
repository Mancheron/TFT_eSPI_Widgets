Splitter Widget demo {#SplitterWidgetDemo}
====================

[See [SplitterWidget.ino](./SplitterWidget_8ino-example.html)]: @example{lineno} SplitterWidget.ino

[Widget]: @ref TFT_eSPI_Widgets::Widget "Widget"

[ButtonHandler]: @ref TFT_eSPI_Widgets::ButtonHandler "Button Handler"

[MessageWidget]: @ref TFT_eSPI_Widgets::MessageWidget "Message Widget"

[SplitterWidget]: @ref TFT_eSPI_Widgets::SplitterWidget "Splitter Widget"

[SplitterChildWidget]: @ref TFT_eSPI_Widgets::SplitterWidget::SplitterChildWidget "Splitter Child Widget"

[IntegerEntryWidget]: @ref TFT_eSPI_Widgets::IntegerEntryWidget "Integer Entry Widget"

[IntegerEntryWidgetDemo]: \ref IntegerEntryWidget.ino "Integer Entry Widget demo"

[Button2]: https://github.com/LennartHennigs/Button2

[Button2Ref]: https://www.arduino.cc/reference/en/libraries/button2/

This demo supposed to have some knowledges about the component
[widgets][Widget] in use (you should at least see the
[IntegerEntryWidgetDemo] prior to this one).

This demo screen is structured like this:
~~~
+-------------------- TFT canvas -------------------+
| +------------ main vertical splitter -----------+ |
| | +------------------ title ------------------+ | |
| | |      This is a demo splitter widget.      | | |
| | +-------------------------------------------+ | |
| | | +--------- horizontal splitter ---------+ | | |
| | | | +-icon-+----- vertical splitter ----+ | | | |
| | | | |      | +------ information -----+ | | | | |
| | | | |      | |Changing the integer    | | | | | |
| | | | | ???? | |value below should      | | | | | |
| | | | | ???? | |change the displayed    | | | | | |
| | | | | ???? | |icon                    | | | | | |
| | | | | ???? | +----- integer entry ----+ | | | | |
| | | | | ???? | |         <value>        | | | | | |
| | | | | ???? | +------ description -----+ | | | | |
| | | | | ???? | |[??????] + README.txt   | | | | | |
| | | | |      | |file content.           | | | | | |
| | | | |      | +------------------------+ | | | | |
| | | | +------+----------------------------+ | | | |
| | | +---------------------------------------+ | | |
| | +-------------------------------------------+ | |
| +-----------------------------------------------+ |
+---------------------------------------------------+
~~~

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

Once a [SplitterWidget] is focused, if at least one of its
[children][SplitterChildWidget] can accept the focus, it is
highlighted. By single clicking on the left button (respectively the
right button), it is possible to select the previous (respectively
next) sibling [child][SplitterChildWidget]. To transmit the focus to
the selected [child][SplitterChildWidget], right click trice like for
other [widgets][Widget]. The focus will then be automatically
transferred to the *real* [child widget][Widget].

By navigating to the [IntegerEntryWidget], it is possible to change
the value using the left/right buttons (see
[IntegerEntryWidgetDemo]). Changing the value will change the
displayed icon as well as the information [MessageWidget] just above
the [IntegerEntryWidget].

<!--
Local Variables:
eval: (flyspell-mode)
ispell-local-dictionary: "american"
End:
-->
