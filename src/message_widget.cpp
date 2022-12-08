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

#include "message_widget.h"

using namespace TFT_eSPI_Widgets;

MessageWidget::MessageWidget(Widget &parent,
                             const String &message,
                             bool wrap,
                             uint64_t animation_delay,
                             uint64_t stick_delay,
                             uint16_t step,
                             const Area &area):
  Widget(parent, area),
  _orig_message(message),
  _message(),
  _number_of_lines(0),
  _offset(Coordinates::origin),
  _wrap(wrap),
  _last_update(0),
  _animation_delay(animation_delay),
  _stick_delay(stick_delay),
  _step(step)
{
  updateMessage();
}

void MessageWidget::_shrink() {
  size_t n = _orig_message.length();
  size_t nb_l = (n > 0), nb_c = 0, max_c = 0;
  for (size_t i = 0; i < n; ++i) {
    if (_orig_message[i] == '\n') {
      if (nb_c > max_c) {
        max_c = nb_c;
      }
      nb_c = 0;
      ++nb_l;
    } else {
      ++nb_c;
    }
  }
  if (nb_c > max_c) {
    max_c = nb_c;
  }
  TFT_eSPI &tft = getTFT();
  int16_t c_w = tft.textWidth("0");
  int16_t c_h = tft.fontHeight();
  _area.width = nb_c * c_w;
  _area.height = nb_l * c_h;
}

void MessageWidget::_draw() {
  TFT_eSPI &tft = getTFT();
  // Wrap on x axis
  tft.setTextWrap(_wrap, false);
  tft.setTextDatum(TL_DATUM);
  tft.setCursor(_offset.x, _offset.y);
  tft.print(_message);
  _last_update = millis();
}

void MessageWidget::updateMessage() {
  _offset = Coordinates::origin;
  _message = _orig_message;
  _number_of_lines = _message.length() > 0;
  _last_update = millis();

  if (!_wrap) return;

  TFT_eSPI &tft = getTFT();
  Area inner_area = getInnerArea();
  int16_t max_chars_per_line = max(inner_area.width / tft.textWidth("A"), 1);

  size_t last_space = 0, cur_line_width = 0;
  for (size_t i = 0; i < _message.length(); ++i) {
    switch (_message[i]) {
    case '\n':
      last_space = 0;
      cur_line_width = 0;
      ++_number_of_lines;
      break;
    case ' ':
      last_space = i;
    default:
      ++cur_line_width;
    }
    if (cur_line_width >= max_chars_per_line) {
      if (last_space) {
        // Force wrapping on the last space
        _message[last_space] = '\n';
        cur_line_width = i - last_space;
        last_space = 0;
      } else {
        // No space in the current line to properly wrap the message.
        // Wrapping will occur now!
        cur_line_width = 0;
      }
      ++_number_of_lines;
    }
  }
  _last_update = millis();
}

void MessageWidget::_loop() {
  unsigned long ellapsed_time = millis() - _last_update;
  TFT_eSPI &tft = getTFT();
  // Compute the width of each character (mono font).
  int16_t c_w = tft.textWidth("A");
  Area inner_area = getInnerArea();
  if (_wrap) {
    // The text is wrapped
    // then by computing the minimal number of lines required to display all characters.
    int16_t h = tft.fontHeight() * _number_of_lines;
    if (h > inner_area.height) {
      // The text height is greater than the widget inner height.
      if (h + _offset.y > inner_area.height) {
        // The end of the text is outside the widget inner area.
        if (((_offset.y < 0) and (ellapsed_time > _animation_delay)) or
            ((_offset.y == 0) and (ellapsed_time > _stick_delay))) {
          // The text is animated and the animation delay is passed or
          // the text isn't yet animated but the stock delay is
          // passed.
          _offset.y -= _step;
          touch();
        }
      } else {
        // The end of the text is visible.
        if (ellapsed_time > _stick_delay) {
          // Reset y offset after the stick delay is passed.
          _offset.y = 0;
          touch();
        }
      }
    }
  } else {
    // The text is not wrapped
    // Compute the width of the unwrapped message.
    int16_t w = c_w * _message.length();
    if (w > inner_area.width) {
      // The text width is greater than the widget width.
      if (w + _offset.x > inner_area.width) {
        // The end of the text is outside the widget area.
        if (((_offset.x < 0) and (ellapsed_time > _animation_delay)) or
            ((_offset.x == 0) and (ellapsed_time > _stick_delay))) {
          // The text is animated and the animation delay is passed or
          // the text isn't yet animated but the stock delay is
          // passed.
          _offset.x -= _step;
          touch();
        }
      } else {
        // The end of the text is visible.
        if (ellapsed_time > _stick_delay) {
          // Reset y offset after the stick delay is passed.
          _offset.x = 0;
          touch();
        }
      }
    }
  }
}
