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

#include "string_entry_widget.h"

using namespace TFT_eSPI_Widgets;

StringEntryWidget::StringEntryWidget(Widget &parent,
                                     uint8_t entry_length,
                                     const String &initial_value,
                                     uint8_t initial_pos,
                                     const Area &area):
  Widget(parent, area),
  _value(), // Reset by setValue() in the constructor body
  _pos(0), // Reset by the setCursorPos() in the constructor body
  _last_update(millis()),
  _offset()
{
  _value.reserve(entry_length);
  for (size_t i = 0; i < entry_length; ++i) {
    _value += ' ';
  }
  setValue(initial_value);
  setCursorPos(initial_pos);
}

void StringEntryWidget::setValue(const String &v) {
  String orig_value = _value;
  size_t n = v.length();
  size_t l = _value.length();
  for (size_t i = 0; i < l; ++i) {
    char c = ' ';
    if (i < n) {
      c = v[i];
      if ((c < 32) || (c > 126)) {
        c = '?';
      }
    }
    _value[i] = c;
  }
  if (_value_change_cb and (orig_value != _value)) {
    _value_change_cb(*this, orig_value, _value);
  }
}

void StringEntryWidget::setCursorPos(uint8_t p) {
  if (p < _value.length()) {
    _pos = p;
  } else {
    uint8_t last_space = _value.length();
    while (last_space-- and (_value[last_space] == ' '));
    if (_value[++last_space] == ' ') {
      _pos = last_space;
    } else {
      _pos = _value.length() - 1;
    }
  }
}

void StringEntryWidget::_shrink(bool recurse, bool check_for_update) {
  TFT_eSPI &tft = getTFT();
  int16_t c_w = tft.textWidth(" ");
  int16_t c_h = tft.fontHeight();
  _area.width = c_w * _value.length();
  _area.height = c_h + 4 /* for the underline */;
}

void StringEntryWidget::_handleEvent(Event event) {
  switch (event) {
  case SINGLE_LEFT_CLICK:
  case LONG_LEFT_PRESS:
    previousLetterAtCursorPos();
    break;
  case DOUBLE_LEFT_CLICK:
    previousCursorPos();
    break;
  case SINGLE_RIGHT_CLICK:
  case LONG_RIGHT_PRESS:
    nextLetterAtCursorPos();
    break;
  case DOUBLE_RIGHT_CLICK:
    nextCursorPos();
    break;
  }
  touch();
}

void StringEntryWidget::_draw() {
  TFT_eSPI &tft = getTFT();
  GraphicalProperties props =  getGraphicalProperties();
  Area inner_area = getInnerArea();
  inner_area.x = 0; // Since in viewport
  inner_area.y = 0; // Since in viewport
  int16_t c_w = tft.textWidth(" ");
  int16_t c_h = tft.fontHeight();
  int16_t lg = c_w * _value.length();
  int16_t m = inner_area.width - lg;
  _offset.y = (inner_area.height - c_h) / 2;
  if (m < 0) {
    Area cursor(c_w, c_h, _offset.x + c_w * _pos, _offset.y);
    if (!inner_area.contains(cursor)) {
      if (cursor.x + cursor.width > inner_area.width) {
        // Cursor position is out of bound on the right side of the widget area
        _offset.x -= (cursor.x + cursor.width) - inner_area.width;
      } else if (cursor.x < 0) {
        // Cursor position is out of bound on the left side of the widget area
        _offset.x -= cursor.x - 1;
      } else {
        Serial.printf("%s:%s:%:This is a bug. "
                      "Please contact the authors of this library.\n",
                      __FILE__, __FUNCTION__, __LINE__);
        // The cursor is supposed to be outside the inner area, but is
        // not outside the left border neither the right border.
      }
    }
  } else {
    _offset.x = m / 2;
  }
  tft.setCursor(_offset.x, _offset.y);
  tft.setTextDatum(TL_DATUM);
  tft.drawString(_value, _offset.x, _offset.y);
  tft.drawFastHLine(_offset.x, _offset.y + c_h + 1, lg, props.getFontColor());
  bool inversion = _last_update & 1lu; // Using the _last_update millisecond as color inversion status
  _last_update = millis();
  if (inversion) {
    // draw current position with inverted colors
    tft.fillRect(_offset.x + _pos * c_w - 1, _offset.y - 1, c_w, c_h, props.getFontColor());
    tft.setTextColor(props.getBackgroundColor());
    tft.drawString(String(_value[_pos]), _offset.x + _pos * c_w, _offset.y);
    // remove inversion status for next drawing
    _last_update &= ~1;
  } else {
    // set inversion status for next drawing
    _last_update |= 1;
  }
  // Since if the next _loop() call is done in less than 1
  // millisecond, it will cause an overflow.
  _last_update -= 2;
}

void StringEntryWidget::_loop(bool recurse) {
  // Nothing for the moment.
  unsigned long now = millis();
  if (now - _last_update > 500) {
    touch();
  }
}

void StringEntryWidget::nextLetterAtCursorPos() {
  String orig_value = _value;
  if (++_value[_pos] > 126) _value[_pos] = 32;
  if (_value_change_cb) {
    _value_change_cb(*this, orig_value, _value);
  }
}

void StringEntryWidget::previousLetterAtCursorPos() {
  String orig_value = _value;
  if (--_value[_pos] < 32) _value[_pos] = 126;
  if (_value_change_cb) {
    _value_change_cb(*this, orig_value, _value);
  }
}
