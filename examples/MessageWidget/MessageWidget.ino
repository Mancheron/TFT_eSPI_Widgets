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

#include <TFT_eSPI_Widgets.h>

using namespace TFT_eSPI_Widgets;

TFT_eSPI tft;
Canvas canvas;

const char *simple_message = "A simple message";
const char *long_message = "A long message that should be animated to be readable.";
const char *wrapped_message = "A long message that should fit on several lines without the need of some animation.";
const char *huge_message = "A so long message that even beeing wrapped, the entire screen is not enough to display it at once.\n\n"
  "This is why there is a vertical animation to read it until the end.";

unsigned long start_cycle;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Starting TFT_eSPI Widget library Message demo...");
  tft.init();
  tft.setRotation(1);
  canvas.init(tft,
              GraphicalProperties(TFT_DARKGREY /* background color */,
                                  TFT_RED /* border color */,
                                  TFT_WHITE /* font color */,
                                  2 /* border size */)
              );

  // Add a generic widget to the canvas such that this widget area
  // fits 90% of the full screen and is centered on it.
  Area area = canvas.getArea();
  area.x += 0.05 * area.width;
  area.y += 0.05 * area.height;
  area *= 0.9;

  // It is REQUIRED to create any child widget using the "new"
  // keyword.
  new GenericWidget(canvas, area);

  // Change the generic widget graphical properties.
  canvas.getChild().setDefaultGraphicalProperties(GraphicalProperties(TFT_WHITE /* background color */,
                                                                      TFT_BLUE /* border color */,
                                                                      TFT_BLACK /* font color */,
                                                                      4 /* border size */,
                                                                      2 /* font size */));

  // Add a message widget to the generic widget.
  //
  // It is REQUIRED to create any child widget using the "new"
  // keyword.
  new MessageWidget(canvas.getChild(), simple_message);

  // By default, the message graphical properties are inherited from
  // the generic widget properties.

  // A tip to add a margin is to define the border color of the
  // message widget being the same as the background color.
  GraphicalProperties p = canvas.getChild().getChild().getDefaultGraphicalProperties();
  p.setBorderColor(p.getBackgroundColor());
  canvas.getChild().getChild().setDefaultGraphicalProperties(p);

  // Here we play with the focus state by defining new colors when
  // message widget will have focus.
  p.setBackgroundColor(TFT_BLACK);
  p.setBorderColor(TFT_BLACK);
  p.setFontColor(TFT_WHITE);
  canvas.getChild().getChild().setFocusGraphicalProperties(p);

  // Force redraw on next loop.
  canvas.touch();

  Serial.print("- root widget type is: ");
  Serial.println(canvas.getTypeString());
  Serial.print("- child widget type is: ");
  Serial.println(canvas.getChild().getTypeString());
  Serial.print("- grandchild widget type is: ");
  Serial.println(canvas.getChild().getChild().getTypeString());

  Serial.println("[End of demo setup]");
  Serial.println("The first message will be prompted for only 5 seconds.");
  Serial.println("==========");
  start_cycle = millis();

}

void loop(void) {

  // Calling the loop() method will call the loop of any descendant
  // widget from the current canvas in the widget tree.
  canvas.loop();
  canvas.refresh();

  unsigned long now = millis() - start_cycle;

  // By default, getChild() will return a Widget (the base class of
  // any widget), but it is possible to specify the subclass of widget
  // in order to use specific methods (be aware that no control is
  // done, so any mistake on the subclass will be fatal).
  MessageWidget &w = canvas.getChild().getChild<MessageWidget>();

  // Since w is known to be a message widget, we can access to its
  // original message.
  String m = w.getOriginalMessage();
  if ((m == simple_message) and (now > 5000)) {
    // After 5 seconds, we replace the message of the message widget
    // by a new message.
    Serial.println("Replacement of the widget message:");
    Serial.print("old: ");
    Serial.println(m);
    // Here we change the message for a longer one.
    w.setMessage(long_message);
    Serial.print("new: ");
    Serial.println(w.getOriginalMessage());
    // The message widget must be redrawn on next loop.
    w.touch();
    Serial.println("This message will be prompted for 35 seconds.");
    Serial.println("==========");
  }

  // We follow the same mechanism as before to set a new message, but
  // this message will be wrapped (play attention to the inner second
  // comment)
  if ((m == long_message) and (now > 40000)) {
    // After 35 more seconds, we replace the message of the message
    // widget by a new message.
    Serial.println("Replacement of the widget message:");
    Serial.print("old: ");
    Serial.println(m);
    w.setMessage(wrapped_message);
    // Here we change the message widget behavior. Now, the too large
    // messages will be wrapped.
    w.setWrap(true);
    Serial.print("new: ");
    Serial.println(w.getOriginalMessage());
    w.touch();
    Serial.println("This message will be prompted for 5 seconds.");
    Serial.println("==========");
  }

  // Here we simply set a so huge text that we should observe vertical
  // scrolling
  if ((m == wrapped_message) and (now > 45000)) {
    // After 5 more seconds, we replace the message of the message
    // widget by a new message.
    Serial.println("Replacement of the widget message:");
    Serial.print("old: ");
    Serial.println(m);
    w.setMessage(huge_message);
    Serial.print("new: ");
    Serial.println(w.getOriginalMessage());
    w.touch();
    Serial.println("This message will be prompted for 35 seconds.");
    Serial.println("==========");
  }

  // We just restart from the simple message, but change the focus
  // state of the message widget.
  if (now > 80000) {
    // After about 80 seconds, we replace the message of the message
    // widget by the simple message.
    Serial.println("Replacement of the widget message:");
    Serial.print("old: ");
    Serial.println(m);
    w.setMessage(simple_message);
    // We modify the message widget to not wrap the text.
    w.setWrap(false);
    Serial.print("new: ");
    Serial.println(w.getOriginalMessage());
    // And just for fun, we change the focus
    if (w.hasFocus()) {
      Serial.println("=> Unfocus the message widget.");
      w.unfocus();
    } else {
      Serial.println("=> Set focus on the message widget.");
      w.focus();
    }
    w.touch();
    Serial.println("This message will be prompted for 5 seconds.");
    Serial.println("==========");
    start_cycle = millis();
  }

}

// Local Variables:
// mode: c++
// End:
