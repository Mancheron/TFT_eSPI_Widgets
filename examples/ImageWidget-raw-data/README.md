Image Widgets using raw data demo {#ImageWidgetDemo1}
=================================

[See [ImageWidget-raw-data.ino](./ImageWidget-raw-data_8ino-example.html)]: @example{lineno} ImageWidget-raw-data.ino

[Widget]: @ref TFT_eSPI_Widgets::Widget "Widget"

[Canvas]: @ref TFT_eSPI_Widgets::Canvas "Canvas"

[ImageWidget]: @ref TFT_eSPI_Widgets::ImageWidget "Image Widget"

[Gnu-Tux-160x80.png]: ./examples/ImageWidget-using-files/data/Gnu-Tux-160x80.png "Gnu-Tux-160x80.png"

[Gnu-Tux-320x160.png]: ./examples/ImageWidget-using-files/data/Gnu-Tux-320x160.png "Gnu-Tux-320x160.png"

[Gnu-Tux-160x80.h]: @ref Gnu-Tux-160x80.h "Gnu-Tux-160x80.h"

[Gnu-Tux-320x160.h]: @ref Gnu-Tux-320x160.h "Gnu-Tux-320x160.h"

[ImageConverterURL]: http://rinkydinkelectronics.com/t_imageconverter565.php "ImageConverter 565 Online tool"

This demo shows how to use the [ImageWidget].

The original image is a 160x80 pixel image representing young comics
stylized GNU and TuX characters. The [ImageWidget] is shrunk to the
minimal size (thus 160x80) and centered on the [Canvas].

After a while, the image is replaced by the same image with a
resolution of 320x160 pixel to illustrates the image cropping (only
the upper left quarter is displayed). Then the image is moved to the
top (thus only the lower left quarter is displayed). The image is thus
moved to the left (only the lower right quarter image is displayed)
and finally the image is moved to the bottom (only the upper right
quarter is displayed). At the end, the original image is restored and
the animation stars again.

The image are stored as a matrix of pixels using 565 color encoding
(16 bits unsigned integer) and were generated from the following PNG
files using the [ImageConverterURL] and were manually edited for
convenience (see files [Gnu-Tux-160x80.h] and [Gnu-Tux-320x160.h]).

![Gnu-Tux-160x80.png]
![Gnu-Tux-320x160.png]

<!--
Local Variables:
eval: (flyspell-mode)
ispell-local-dictionary: "american"
End:
-->
