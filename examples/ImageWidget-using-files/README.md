Image Widgets using files stored on the file system demo {#ImageWidgetDemo2}
========================================================

[Doxygen tag -- don't remove]: \example{lineno} ImageWidget-using-files.ino

[Widget]: @ref TFT_eSPI_Widgets::Widget "Widget"

[Canvas]: @ref TFT_eSPI_Widgets::Canvas "Canvas"

[ImageWidget]: @ref TFT_eSPI_Widgets::ImageWidget "Image Widget"

[Gnu-Tux-160x80.bmp]: ./examples/ImageWidget-using-files/data/Gnu-Tux-160x80.bmp "Gnu-Tux-160x80.bmp"

[Gnu-Tux-160x80.jpg]: ./examples/ImageWidget-using-files/data/Gnu-Tux-160x80.jpg "Gnu-Tux-160x80.jpg"

[Gnu-Tux-160x80.png]: ./examples/ImageWidget-using-files/data/Gnu-Tux-160x80.png "Gnu-Tux-160x80.png"

[Gnu-Tux-320x160.bmp]: ./examples/ImageWidget-using-files/data/Gnu-Tux-320x160.bmp "Gnu-Tux-320x160.bmp"

[Gnu-Tux-320x160.jpg]: ./examples/ImageWidget-using-files/data/Gnu-Tux-320x160.jpg "Gnu-Tux-320x160.jpg"

[Gnu-Tux-320x160.png]: ./examples/ImageWidget-using-files/data/Gnu-Tux-320x160.png "Gnu-Tux-320x160.png"

This demo shows how to use the [ImageWidget] with files on the file
system.

The file system to use is automatically set according to the
hardware (see file fs_wrapper.h) but can be forced by defining the
`USE_<FS_TYPE>` prior to include the TFT_eSPI_Widgets.h header:
~~~{.cpp}
#define USE_SPIFFS      // for using SPIFFS
// #define USE_LittleFS // for using LittleFS
// #define USE_SDFS     // for using SDFS
// #define USE_SD       // for using the Legacy SD
#include <TFT_eSPI_Widgets.h>
~~~

The original image is a 160x80 pixel bitmap image stored on the file
system representing young comics stylized GNU and TuX characters. The
[ImageWidget] is shrunk to the minimal size (thus 160x80) and centered
on the [Canvas].

After a while, the image is replaced by the same bitmap image (still
stored on the file system) with a resolution of 320x160 pixel to
illustrates the image cropping (only the upper left quarter is
displayed).

Then the image is moved to the top (thus only the lower left quarter
is displayed). The image is thus moved to the left (only the lower
right quarter image is displayed) and finally the image is moved to
the bottom (only the upper right quarter is displayed). At the end,
the same animation is repeated using JPG images and then with PNG
images (with the same resolutions). The demo loops over and over with
BMP, JPG, PNG, BMP, JPG, ...

  size  |           BMP          |           JPG          |           PNG
------- | ---------------------- | ---------------------- | ----------------------
 160x80 | ![Gnu-Tux-160x80.bmp]  | ![Gnu-Tux-160x80.jpg]  | ![Gnu-Tux-160x80.png]
320x160 | ![Gnu-Tux-320x160.bmp] | ![Gnu-Tux-320x160.jpg] | ![Gnu-Tux-320x160.png]

<!--
Local Variables:
eval: (flyspell-mode)
ispell-local-dictionary: "american"
End:
-->
