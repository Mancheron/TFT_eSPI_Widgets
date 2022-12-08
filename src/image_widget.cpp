/******************************************************************************
 *                                                                             *
 *  Copyright © 2022      -- LIRMM/CNRS/UM                                     *
 *                           (Laboratoire d'Informatique, de Robotique et de   *
 *                           Microélectronique de Montpellier /                *
 *                           Centre National de la Recherche Scientifique /    *
 *                           Université de Montpellier)                        *
 *                                                                             *
 *  Auteurs/Authors: Alban MANCHERON  <alban.mancheron@lirmm.fr>               *
 *                                                                             *
 *  Programmeurs/Programmers:                                                  *
 *                   Alban MANCHERON  <alban.mancheron@lirmm.fr>               *
 *                                                                             *
 *  -------------------------------------------------------------------------  *
 *                                                                             *
 *  Ce fichier fait partie de la librairie TFT_eSPI_Widgets.                   *
 *                                                                             *
 *  La librairie TFT_eSPI_Widgets a pour objet de simplifier le développement  *
 *  d'interfaces graphiques  pour l'uitlisateur  (GUI)  en se basant  sur une  *
 *  approche par *widgets* (composants graphiques).                            *
 *                                                                             *
 *  Ce logiciel est régi par la licence CeCILL-C soumise au droit français et  *
 *  respectant les principes  de diffusion des logiciels libres.  Vous pouvez  *
 *  utiliser, modifier et/ou redistribuer ce programme sous les conditions de  *
 *  la licence CeCILL-C telle que diffusée par le CEA, le CNRS et l'INRIA sur  *
 *  le site "http://www.cecill.info".                                          *
 *                                                                             *
 *  En contrepartie de l'accessibilité au code source et des droits de copie,  *
 *  de modification et de redistribution accordés par cette licence, il n'est  *
 *  offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,  *
 *  seule une responsabilité  restreinte pèse  sur l'auteur du programme,  le  *
 *  titulaire des droits patrimoniaux et les concédants successifs.            *
 *                                                                             *
 *  À  cet égard  l'attention de  l'utilisateur est  attirée sur  les risques  *
 *  associés  au chargement,  à  l'utilisation,  à  la modification  et/ou au  *
 *  développement  et à la reproduction du  logiciel par  l'utilisateur étant  *
 *  donné  sa spécificité  de logiciel libre,  qui peut le rendre  complexe à  *
 *  manipuler et qui le réserve donc à des développeurs et des professionnels  *
 *  avertis  possédant  des  connaissances  informatiques  approfondies.  Les  *
 *  utilisateurs  sont donc  invités  à  charger  et  tester  l'adéquation du  *
 *  logiciel  à leurs besoins  dans des conditions  permettant  d'assurer  la  *
 *  sécurité de leurs systêmes et ou de leurs données et,  plus généralement,  *
 *  à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.         *
 *                                                                             *
 *  Le fait  que vous puissiez accéder  à cet en-tête signifie  que vous avez  *
 *  pris connaissance de la licence CeCILL-C, et que vous en avez accepté les  *
 *  termes.                                                                    *
 *                                                                             *
 *  -------------------------------------------------------------------------  *
 *                                                                             *
 *  This File is part of the TFT_eSPI_Widgets library.                         *
 *                                                                             *
 *  The TFT_eSPI_Widgets library aims to make easy the GUI development using   *
 *  a Widget approach.                                                         *
 *                                                                             *
 *  This software is governed by the CeCILL-C license under French law and     *
 *  abiding by the rules of distribution of free software. You can use,        *
 *  modify and/ or redistribute the software under the terms of the CeCILL-C   *
 *  license as circulated by CEA, CNRS and INRIA at the following URL          *
 *  "http://www.cecill.info".                                                  *
 *                                                                             *
 *  As a counterpart to the access to the source code and rights to copy,      *
 *  modify and redistribute granted by the license, users are provided only    *
 *  with a limited warranty and the software's author, the holder of the       *
 *  economic rights, and the successive licensors have only limited            *
 *  liability.                                                                 *
 *                                                                             *
 *  In this respect, the user's attention is drawn to the risks associated     *
 *  with loading, using, modifying and/or developing or reproducing the        *
 *  software by the user in light of its specific status of free software,     *
 *  that may mean that it is complicated to manipulate, and that also          *
 *  therefore means that it is reserved for developers and experienced         *
 *  professionals having in-depth computer knowledge. Users are therefore      *
 *  encouraged to load and test the software's suitability as regards their    *
 *  requirements in conditions enabling the security of their systems and/or   *
 *  data to be ensured and, more generally, to use and operate it in the same  *
 *  conditions as regards security.                                            *
 *                                                                             *
 *  The fact that you are presently reading this means that you have had       *
 *  knowledge of the CeCILL-C license and that you accept its terms.           *
 *                                                                             *
 ******************************************************************************/

#include "image_widget.h"
#include <PNGdec.h>
#include <TJpg_Decoder.h>

#if defined(ESP32)
#  include <FS.h>
#  include <SPIFFS.h>
#  define TFT_eSPI_Widgets_FS SPIFFS
#elif defined(ESP8266)
#  include <LittleFS.h>
#  define TFT_eSPI_Widgets_FS LittleFS
#else
#  include <SD.h>
#  define TFT_eSPI_Widgets_FS SDLib::SD
#endif

using namespace TFT_eSPI_Widgets;

static SemaphoreHandle_t _mutex = NULL;
static StaticSemaphore_t _mutex_buffer;

// Some usefull functions to open and read from a file.
static File _read_only_open(const char *path) {
  File fd = TFT_eSPI_Widgets_FS.open(path, FILE_READ);
  if (!fd) {
    Serial.printf("File '%s' not found\n", path);
  }
  yield();
  return fd;
};

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.
static uint16_t _read16(File &fd) {
  uint16_t result;
  ((uint8_t *)&result)[0] = fd.read(); // LSB
  ((uint8_t *)&result)[1] = fd.read(); // MSB
  return result;
}

static uint32_t _read32(File &fd) {
  uint32_t result;
  ((uint8_t *)&result)[0] = fd.read(); // LSB
  ((uint8_t *)&result)[1] = fd.read();
  ((uint8_t *)&result)[2] = fd.read();
  ((uint8_t *)&result)[3] = fd.read(); // MSB
  return result;
}

// Callback functions for PNGdec library.
static PNG _png_handler;

static void *_png_open_cb(const char *filename, int32_t *size) {
  File *fd_ptr = new File;
  *fd_ptr = _read_only_open(filename);
  if (*fd_ptr) {
    *size = fd_ptr->size();
  } else {
    delete fd_ptr;
    fd_ptr = NULL;
  }
  return fd_ptr;
}

static void _png_close_cb(void *fh) {
  if (!fh) return;
  File *fd_ptr = static_cast<File *>(fh);
  fd_ptr->close();
  yield();
  delete fd_ptr;
}

static int32_t _png_read_cb(PNGFILE *png_file, uint8_t *buffer, int32_t length) {
  if (!png_file) return 0;
  File fd = *static_cast<File *>(png_file->fHandle);
  return fd.read(buffer, length);
}

static int32_t _png_seek_cb(PNGFILE *png_file, int32_t position) {
  if (!png_file) return 0;
  File fd = *static_cast<File *>(png_file->fHandle);
  return fd.seek(position);
}

struct _png_user_data {
  TFT_eSPI &tft;
  Coordinates pos;
  uint16_t *buffer;
  size_t buffer_size;
};

static void _png_draw_cb(PNGDRAW *png_draw) {
  if (!png_draw) return;
  _png_user_data &data = *static_cast<_png_user_data *>(png_draw->pUser);
  _png_handler.getLineAsRGB565(png_draw, data.buffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  data.tft.pushImage(data.pos.x, data.pos.y + png_draw->y, png_draw->iWidth, 1, data.buffer);
}

// End of callback functions.

ImageWidget::ImageWidget(Widget &parent,
                         const String &path,
                         const Coordinates &offset,
                         const Area &area):
  Widget(parent, area),
  _path(path),
  _format(NOT_SET),
  _data(NULL),
  _dimensions(Dimensions::empty),
  _offset(offset)
{
  if (!_mutex) {
    _mutex = xSemaphoreCreateBinaryStatic(&_mutex_buffer);
    xSemaphoreGive(_mutex);
  }
  _updateDimensions();
}

ImageWidget::ImageWidget(Widget &parent,
                         const uint16_t *data,
                         const Dimensions &dimensions,
                         const Coordinates &offset,
                         const Area &area):
  Widget(parent, area),
  _path(),
  _format(RAW_DATA),
  _data(data),
  _dimensions(dimensions),
  _offset(offset)
{}

void ImageWidget::_shrink() {
  _area.width = _dimensions.width;
  _area.height = _dimensions.height;
}

bool ImageWidget::_updateDimensions() {
  if (_data) return true;

  if (_format == NOT_SET) {
    if (TFT_eSPI_Widgets_FS.exists(_path.c_str())) {
      // First try to open using file extension.
      String _str = _path;
      _str.toLowerCase();
      if (_str.endsWith(".bmp")) {
        Serial.printf("Trying to open file '%s' from its BMP extension...\t", _path.c_str());
        if (_drawBmpImage(false)) {
          _format = BMP;
          Serial.println("[Success]");
        } else {
          Serial.println("[Failure]");
        }
      } else if (_str.endsWith(".jpg") or _str.endsWith(".jpeg")) {
        Serial.printf("Trying to open file '%s' from its JPG extension...\t", _path.c_str());
        if (_drawJpgImage(false)) {
          _format = JPG;
          Serial.println("[Success]");
        } else {
          Serial.println("[Failure]");
        }
      } else if (_str.endsWith(".png")) {
        Serial.printf("Trying to open file '%s' from its PNG extension...\t", _path.c_str());
        if (_drawPngImage(false)) {
          _format = PNG;
          Serial.println("[Success]");
        } else {
          Serial.println("[Failure]");
        }
      } else {
        // At the end, try to open the file with all the methods
        Serial.printf("Trying to open file '%s' as a BMP...\t", _path.c_str());
        if (!_str.endsWith(".bmp") and _drawBmpImage(false)) {
          _format = BMP;
          Serial.println("[Success]");
        } else {
          Serial.println("[Failure]");
          Serial.printf("Trying to open file '%s' as a JPG...\t", _path.c_str());
          if (!_str.endsWith(".jpg") and !_str.endsWith(".jpeg") and _drawJpgImage(false)) {
            _format = JPG;
            Serial.println("[Success]");
          } else {
            Serial.println("[Failure]");
            Serial.printf("Trying to open file '%s' as a PNG...\t", _path.c_str());
            if (!_str.endsWith(".png") and _drawPngImage(false)) {
              _format = PNG;
              Serial.println("[Success]");
            } else {
              Serial.println("[Failure]");
              Serial.printf("Unable to detect the file format for the path '%s'\n", _path.c_str());
              _format = UNKNOWN;
            }
          }
        }
      }
    } else {
      _format = UNKNOWN;
      Serial.printf("File '%s' not found.\n", _path.c_str());
    }
  }
  yield();
  if (_format != UNKNOWN) {
    Serial.printf("Image size is %ux%u\n", _dimensions.width, _dimensions.height);
  }
  return _format != UNKNOWN;
}

void ImageWidget::_draw() {
  const GraphicalProperties &props = getGraphicalProperties();
  if (_data) {
    TFT_eSPI &tft = getTFT();
    bool oldSwapBytes = tft.getSwapBytes();
    tft.setSwapBytes(true);
    tft.pushImage(_offset.x, _offset.y, _dimensions.width, _dimensions.height, _data);
    tft.setSwapBytes(oldSwapBytes);
  } else {
    switch (_format) {
    case BMP:
      _drawBmpImage();
      break;
    case JPG:
      _drawJpgImage();
      break;
    case PNG:
      _drawPngImage();
      break;
    case NOT_SET:
      _updateDimensions();
      _draw(); // Recursive call [after calling _updateDimensions(),
               // the _format is anything but NOT_SET].
      break;
    default:
      Serial.println("File format not supported.");
    }
  }
  yield();
}

bool ImageWidget::_drawBmpImage(bool real_drawing) {
  File fd = _read_only_open(_path.c_str());
  if (!fd) return false;
  uint32_t seekOffset;
  uint16_t row, col;
  int16_t x = _offset.x;
  int16_t y = _offset.y;

  uint16_t v = _read16(fd);
  if (v != 0x4D42) { // The file doesn't start with the BMP Magic Bytes
    fd.close();
    yield();
    return false;
  }

  _read32(fd);
  _read32(fd);
  seekOffset = _read32(fd);
  _read32(fd);
  _dimensions.width = _read32(fd);
  _dimensions.height = _read32(fd);
  if (real_drawing) {
    if ((_read16(fd) == 1) && (_read16(fd) == 24) && (_read32(fd) == 0)) {
      y += _dimensions.height - 1;

      TFT_eSPI &tft = getTFT();
      bool oldSwapBytes = tft.getSwapBytes();
      tft.setSwapBytes(true);
      fd.seek(seekOffset);

      uint16_t padding = (4 - ((_dimensions.width * 3) & 3)) & 3;
      uint8_t lineBuffer[_dimensions.width * 3 + padding];

      for (row = 0; row < _dimensions.height; row++) {
        fd.read(lineBuffer, sizeof(lineBuffer));
        uint8_t*  bptr = lineBuffer;
        uint16_t* tptr = (uint16_t*)lineBuffer;
        // Convert 24 to 16 bit colours
        for (uint16_t col = 0; col < _dimensions.width; col++) {
          uint8_t b = *bptr++;
          uint8_t g = *bptr++;
          uint8_t r = *bptr++;
          *tptr++ = tft.color565(r, g, b);
        }

        // Push the pixel row to screen, pushImage will crop the line if needed
        // y is decremented as the BMP image is drawn bottom up
        tft.pushImage(x, y--, _dimensions.width, 1, (uint16_t*)lineBuffer);
      }
      tft.setSwapBytes(oldSwapBytes);
    }
  }
  fd.close();
  yield();
  return true;
}

static ImageWidget *_current_image_widget = NULL;

bool _jpg_draw_cb(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  if (!_current_image_widget) return false;
  if (x >= _current_image_widget->getInnerArea().width) return true;
  if (y >= _current_image_widget->getInnerArea().height) return true;
  _current_image_widget->getTFT().pushImage(x, y, w, h, bitmap);
  yield();
  return true;
}

bool ImageWidget::_drawJpgImage(bool real_drawing) {
  TFT_eSPI &tft = getTFT();
  TJpgDec.setJpgScale(1);
  TJpgDec.setCallback(_jpg_draw_cb);
  JRESULT v = TJpgDec.getFsJpgSize(&_dimensions.width,
                                   &_dimensions.height,
                                   _path.c_str(),
                                   TFT_eSPI_Widgets_FS);
  if (v == JDR_OK) {
    if (real_drawing) {
      xSemaphoreTake(_mutex, portMAX_DELAY);
      if (_current_image_widget) {
        Serial.printf("%s:%s:%:This is a bug. "
                      "Please contact the authors of this library.\n",
                      __FILE__, __FUNCTION__, __LINE__);
        // _current_image_widget internal variable must be NULL
        exit(1);
      }
      _current_image_widget = this;
      bool oldSwapBytes = tft.getSwapBytes();
      tft.setSwapBytes(true);
      v = TJpgDec.drawFsJpg(_offset.x,
                            _offset.y,
                            _path.c_str(),
                            TFT_eSPI_Widgets_FS);
      tft.setSwapBytes(oldSwapBytes);
      _current_image_widget = NULL;
      xSemaphoreGive(_mutex);
    }
  } else {
    _dimensions = Dimensions::empty;
  }
  yield();
  return v == JDR_OK;
}

bool ImageWidget::_drawPngImage(bool real_drawing) {
  xSemaphoreTake(_mutex, portMAX_DELAY);
  int16_t v = _png_handler.open(_path.c_str(),
                                _png_open_cb,
                                _png_close_cb,
                                _png_read_cb,
                                _png_seek_cb,
                                _png_draw_cb);
  if (v == PNG_SUCCESS) {
    TFT_eSPI &tft = getTFT();
    _dimensions = Dimensions(_png_handler.getWidth(), _png_handler.getHeight());
    if (real_drawing) {
      tft.startWrite();
      uint16_t *buffer = new uint16_t[_png_handler.getWidth()];
      _png_user_data extra_data = {
                                   tft,
                                   _offset,
                                   buffer,
                                   _png_handler.getWidth()
      };
      v = _png_handler.decode(&extra_data, 0);
      delete [] buffer;
      _png_handler.close();
      tft.endWrite();
    }
  }
  xSemaphoreGive(_mutex);
  return v == PNG_SUCCESS;
}
