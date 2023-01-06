/******************************************************************************
 *                                                                             *
 *  Copyright © 2022-2023 -- LIRMM/CNRS/UM                                     *
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

#include <TFT_eSPI_Widgets.h>

using namespace TFT_eSPI_Widgets;

// The TFT screen used for this demo
TFT_eSPI tft;

// The Canvas widget on which widgets are printed
Canvas canvas;

// On a TTGO T-Display, there is two builtin buttons, one is attached
// to the GPIO 35 pin and the other is attached to the GPIO 0 pin.
// Both those pins are HIGH when buttons are released.
PhysicalButtonHandler left_btn(35, HIGH);
PhysicalButtonHandler right_btn(0, HIGH);

// This callback function will be called when a double click (from
// either the right or the left button) occurs on an
// IntegerEntryWidget.
//
// When the double click comes from the left button, the integer entry
// value is decremented by 10 whereas when the double click comes from
// the right button, the integer entry value is incremented by 10.
bool onDoubleClickCb(Widget &w, Event e) {
  IntegerEntryWidget &_w = w.as<IntegerEntryWidget>();
  bool handled = false;
  if ((e == DOUBLE_LEFT_CLICK) || (e == DOUBLE_RIGHT_CLICK)) {
    if (e == DOUBLE_LEFT_CLICK) {
      _w.setValue(_w.getValue() - 10);
    } else {
      _w.setValue(_w.getValue() + 10);
    }
    _w.touch();
    handled = true;
  }
  return handled;
}

// Capture left and right buttons' events and pass them to the canvas
// (root of the widget tree).
void processButtonEvents() {
  ButtonHandler::Event left_event = left_btn.getEvent();
  ButtonHandler::Event right_event = right_btn.getEvent();

  switch (left_event) {
  case ButtonHandler::SINGLE_CLICK:
    canvas.handleEvent(SINGLE_LEFT_CLICK);
    break;
  case ButtonHandler::DOUBLE_CLICK:
    canvas.handleEvent(DOUBLE_LEFT_CLICK);
    break;
  case ButtonHandler::TRIPLE_CLICK:
    canvas.handleEvent(TRIPLE_LEFT_CLICK);
    break;
  case ButtonHandler::LONG_PRESS:
    canvas.handleEvent(LONG_LEFT_PRESS);
    break;
  }
  switch (right_event) {
  case ButtonHandler::SINGLE_CLICK:
    canvas.handleEvent(SINGLE_RIGHT_CLICK);
    break;
  case ButtonHandler::DOUBLE_CLICK:
    canvas.handleEvent(DOUBLE_RIGHT_CLICK);
    break;
  case ButtonHandler::TRIPLE_CLICK:
    canvas.handleEvent(TRIPLE_RIGHT_CLICK);
    break;
  case ButtonHandler::LONG_PRESS:
    canvas.handleEvent(LONG_RIGHT_PRESS);
    break;
  }
}


// Compute the color corresponding to the float value in the gradient
// color starting to color from to color to using the given middle
// color
uint32_t getGradientColor(float x, uint32_t from = 0x0000ff, uint32_t middle = 0xffff00, uint32_t to = 0xff0000) {
  uint32_t color;
  uint8_t lower_red, lower_green, lower_blue, upper_red, upper_green, upper_blue, red, green, blue;
  if (x < 0.5) {
    lower_red = (from >> 16) & 0xff;
    lower_green = (from >> 8) & 0xff;
    lower_blue = from & 0xff;
    upper_red = (middle >> 16) & 0xff;
    upper_green = (middle >> 8) & 0xff;
    upper_blue = middle & 0xff;
    x *= 2;
  } else {
    lower_red = (middle >> 16) & 0xff;
    lower_green = (middle >> 8) & 0xff;
    lower_blue = middle & 0xff;
    upper_red = (to >> 16) & 0xff;
    upper_green = (to >> 8) & 0xff;
    upper_blue = to & 0xff;
    x = 2 * (x - 0.5);
  }
  red = x * (upper_red - lower_red) + lower_red;
  green = x * (upper_green - lower_green) + lower_green;
  blue = x * (upper_blue - lower_blue) + lower_blue;
  color = (red << 16) | (green << 8) | blue;
  return color;
}

// Compute the position ratio of the current value in the given range.
float getProportion(int32_t v, int32_t lower, int32_t upper) {
  return ((upper > lower)
          ? float(v - lower) / (upper - lower)
          : ((upper == lower)
             ? 0.5
             : getProportion(v, upper, lower)));
}

// The arduino initialisation function
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Starting TFT_eSPI Widget library Integer Entry demo...");
  tft.init();
  tft.setRotation(2);
  left_btn.init();
  right_btn.init();

  canvas.init(tft,
              GraphicalProperties(TFT_DARKGREY /* background color */,
                                  TFT_RED /* border color */,
                                  TFT_WHITE /* font color */,
                                  2 /* border size */),
              GraphicalProperties(TFT_DARKGREY /* background color */,
                                  TFT_BLUE /* border color */,
                                  TFT_WHITE /* font color */,
                                  4 /* border size */)
              );

  // Add a generic widget to the canvas such that this widget area
  // fits 50% of the full screen.
  Area area = canvas.getArea();
  area *= 0.5;

  // It is REQUIRED to create any child widget using the "new"
  // keyword.
  new IntegerEntryWidget(canvas, 42, -30, 120, area);

  // Centering horizontally and vertically the integer entry widget
  canvas.getChild().setPosition(50, 50);

  // Associated the onDoubleClickCb function to the integer entry
  // widget.
  canvas.getChild().onEvent(onDoubleClickCb);
  float x = getProportion(42, -30, 120);
  uint32_t color24 = getGradientColor(x);
  uint16_t color16 = tft.color24to16(color24);
  GraphicalProperties props = canvas.getFocusGraphicalProperties();
  props.setBackgroundColor(color16);
  canvas.getChild().setFocusGraphicalProperties(props);

  // Give focus on the integer entry widget
  canvas.getChild().focus();
  // Force redraw on next loop.
  canvas.touch();

  // Print widget tree on Serial.
  Serial.println("Widget tree:");
  canvas.print();

  Serial.println("[End of demo setup]");
  Serial.println("The value is set to 42 and is constrained into the range [-30, 120].");
  Serial.println("It is required to have two 'buttons' that can send events.");
  Serial.println("==========");
  Serial.println("To give the focus to the canvas, use a triple right click. Do it again to give the focus to the integer entry.");
  Serial.println("To unfocus the integer entry, use a triple left click. Do it again to unfocus the canvas.");
}

// The arduino infinite loop function
void loop() {

  // Calling the loop() method will call the loop of any descendant
  // widget from the current canvas in the widget tree.
  canvas.loop();
  canvas.refresh();

  // Retrieving the current value of the widget
  IntegerEntryWidget &w = canvas.getChild<IntegerEntryWidget>();
  int v = w.getValue();

  // Catch button events.
  processButtonEvents();

  // If the integer entry value has changed after processing the
  // button events, we change the integer entry widget background
  // according to the current value (from blue to red).
  if (v != w.getValue()) {
    GraphicalProperties props = w.getFocusGraphicalProperties();
    if (w.getMaximalValue() != w.getMinimalValue()) {
      float x = getProportion(w.getValue(), w.getMinimalValue(), w.getMaximalValue());
      uint32_t color24 = getGradientColor(x);
      uint16_t color16 = tft.color24to16(color24);
      props.setBackgroundColor(color16);
      w.setFocusGraphicalProperties(props);
    }
  }

}

// Local Variables:
// mode: c++
// End:
