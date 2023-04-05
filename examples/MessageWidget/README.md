Message Widget demo {#MessageWidgetDemo}
===================

[See [MessageWidget.ino](./MessageWidget_8ino-example.html)]: @example{lineno} MessageWidget.ino

[Widget]: @ref TFT_eSPI_Widgets::Widget "Widget"

[Canvas]: @ref TFT_eSPI_Widgets::Canvas "Canvas"

[GenericWidget]: @ref TFT_eSPI_Widgets::GenericWidget "Generic Widget"

[MessageWidget]: @ref TFT_eSPI_Widgets::MessageWidget "Message Widget"

This is a simple demo for the [MessageWidget].

This demo screen is structured like this:
~~~
+---------------- TFT canvas ----------------+
| +------------ Generic Widget ------------+ |
| | +---------- Message Widget ----------+ | |
| | |                                    | | |
| | | Some messages                      | | |
| | |                                    | | |
| | +------------------------------------+ | |
| +----------------------------------------+ |
+--------------------------------------------+
~~~

First, a short message (that should fit into the screen) is displayed
for 5 seconds.

Second, a longer one line message (that shouldn't fit into the screen)
is displayed for 35 seconds to illustrate the horizontal animation.

Third, a long message is displayed for 5 seconds using wrap mode and
should fit into the entire screen.

Fourth, a very long message is displayed for 35 seconds using wrap
mode but shouldn't fit into the entire screen to illustrate the
vertical animation.

After these four steps, the [MessageWidget] is (focused and) shrunk to
the size of the first message and the four steps are done using this
very small widget area.

The demo loops over and over...

This demo also shows how to use [GenericWidget] to add some extra
space between the [Canvas] and the [MessageWidget]. This trick can be
used to add a kind of margin around the message.

<!--
Local Variables:
eval: (flyspell-mode)
ispell-local-dictionary: "american"
End:
-->
