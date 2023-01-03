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

#include "float_entry_widget.h"

using namespace TFT_eSPI_Widgets;

FloatEntryWidget::FloatEntryWidget(Widget &parent,
                                   float initial_value,
                                   float minimal_value,
                                   float maximal_value,
                                   uint8_t precision,
                                   const Area &area):
  Widget(parent, area),
  _value(initial_value), // reset by setValue() in constructor body
  _precision(precision), // reset by setPrecision() in constructor body
  _minimal_value(minimal_value),
  _maximal_value(maximal_value)
{
  setPrecision(precision); // This is to ensure constraints on precision are respected
  setValue(initial_value); // This is to ensure constraints on value are respected
}

void FloatEntryWidget::_handleEvent(Event event) {
  switch (event) {
  case SINGLE_LEFT_CLICK:
  case LONG_LEFT_PRESS:
    decrValue();
    break;
  case SINGLE_RIGHT_CLICK:
  case LONG_RIGHT_PRESS:
    incrValue();
    break;
  }
  touch();
}

// This is a hidden function that computes the width of the printed
// float value.
//
// The computated value depends on the given precision (prec), the
// current character width (c_w) and the given font size (f_s).
//
// The computed exponent is stored in the last parameter.
static int16_t _computeValueStringLength(float v,
                                         uint8_t prec, int16_t c_w, uint8_t f_s,
                                         int8_t &exponent) {
  exponent = trunc(log10(max<float>(1, abs(v))));
  int16_t w = 0; // the final float representation width
  size_t n = (v < 0) + 2 + prec;
  if (exponent) {
    n += 3;
    size_t nb_exponent_digits = 1;
    if (exponent >= 10) ++nb_exponent_digits;
    // A floating point number exponent is bounded to 38, thus the
    // number of digits is either one or two.
    w = nb_exponent_digits * c_w;
    if (f_s > 1) {
      // The font size of the exponent will be half the widget font
      // size.
      w /= 2;
    }
  }
  w += n * c_w; // This is the full length of the text to print.
  return w;
}

void FloatEntryWidget::_shrink() {
  TFT_eSPI &tft = getTFT();
  uint8_t f_s = getGraphicalProperties().getFontSize();
  int16_t c_w = tft.textWidth("0");
  int16_t c_h = tft.fontHeight();
  int8_t exponent;
  // the final float representation width
  int16_t w = _computeValueStringLength(_value, _precision, c_w, f_s, exponent);
  if (w > _area.width) {
    _area.width = w;
  }
  if (c_h > _area.height) {
    _area.height = c_h;
  }
}

void FloatEntryWidget::_draw() {
  TFT_eSPI &tft = getTFT();

  // The string representation of _value uses at most _precision + 8
  // characters:
  // - the minus sign if _value is negative [0 or 1]
  // - the most significative digit         [1]
  // - the decimal separator                [1]
  // - the decimal part                     [_precision]
  // - the exponent string 'x10'            [3]
  //   (the exponent will be printed later)
  // - the ending null character            [1]
  //
  // The _precision is bounded to 99 and if _value can be print in the
  // usual real number representation, then it uses less characters.
  // Thus, the maximum number of characters is at most 107.
  static char buffer[107]; // Making it static for performance.

  uint8_t f_s = getGraphicalProperties().getFontSize();
  int16_t c_w = tft.textWidth("0");

  float v = _value;
  int8_t exponent;

  // the final float representation width
  int16_t w = _computeValueStringLength(_value, _precision, c_w, f_s, exponent);
  if (exponent) {
    v /= powf(10, exponent);
  }
  snprintf(buffer, 107, "%.*f", _precision, v);
  tft.setTextDatum(TL_DATUM);
  Area inner_area = getInnerArea();
  tft.setCursor((inner_area.width - w) / 2, (inner_area.height - tft.fontHeight()) / 2);
  tft.print(buffer);
  if (exponent) {
    tft.print("x10");
    tft.setTextSize(max(1, f_s / 2));
    tft.print(exponent);
  }
}

void FloatEntryWidget::incrValue() {
  float delta = getDelta();
  float step = powf(10, -_precision);
  if ((delta / step) == -_value) {
    delta /= 10;
    if (delta < step) {
      delta = step;
    }
  }
  // The following code doesn't behave as calling directly
  // setValue(_value + _delta) since the rounding is operated
  // accroding to the current widget value and when next expected
  // value is one level of exponent less, the result of
  // setValue(_value + delta) doesn't change the current wigdet
  // value since the delta is 10 times smalled than the rounding
  // threshold.
  _value = constrain(_value + delta, _minimal_value, _maximal_value);
  setValue(_value);
}

void FloatEntryWidget::decrValue() {
  float delta = getDelta();
  float step = powf(10, -_precision);
  if ((delta / step) == _value) {
    delta /= 10;
    if (delta < step) {
      delta = step;
    }
  }
  // The following code doesn't behave as calling directly
  // setValue(_value - _delta) since the rounding is operated
  // accroding to the current widget value and when next expected
  // value is one level of exponent less, the result of
  // setValue(_value - delta) doesn't change the current wigdet
  // value since the delta is 10 times smalled than the rounding
  // threshold.
  _value = constrain(_value - delta, _minimal_value, _maximal_value);
  setValue(_value);
}
