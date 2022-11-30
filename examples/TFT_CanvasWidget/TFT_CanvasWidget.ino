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

void onCanvasLoopCb(Widget &w) {
  Serial.println("=> callback function");
  // Method name of GraphicalProperties objects are quite explicit.

  // Getting graphical properties (depends on the focus status).
  GraphicalProperties props = w.getGraphicalProperties();
  uint8_t v = props.getBorderSize();
  bool change_focus_state = false;
  if (v == 0) {
    w.unfocus();
    change_focus_state = true;
  } else if (v == 10) {
    w.focus();
    change_focus_state = true;
  }
  v += (w.hasFocus() ? -1 : 1); // Decrease border size if widget has
                                // focus, increase otherwise.
  props.setBorderSize(v);
  if (change_focus_state) {
    // Change the background color and border color of current
    // GraphicalProperties object on the basis of the current
    // background color.
    uint16_t bg_color = props.getBackgroundColor() ;
    switch (bg_color) {
    case TFT_YELLOW:
      props.setBorderColor(TFT_YELLOW);
      props.setBackgroundColor(TFT_CYAN);
      break;
    case TFT_CYAN:
      props.setBorderColor(TFT_CYAN);
      props.setBackgroundColor(TFT_RED);
      break;
    case TFT_RED:
      props.setBorderColor(TFT_RED);
      props.setBackgroundColor(TFT_BLUE);
      break;
    case TFT_BLUE:
    default:
      props.setBorderColor(TFT_BLUE);
      props.setBackgroundColor(TFT_YELLOW);
    }
  }
  if (w.hasFocus()) {
    // Set the new GraphicalProperties when widget is focused.
    w.setFocusGraphicalProperties(props);
  } else {
    // Set the new GraphicalProperties when widget is not focused.
    w.setDefaultGraphicalProperties(props);
  }
  w.touch(); // force redrawing the widget
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Starting TFT_eSPI Widget library Canvas demo...");
  tft.init();
  GraphicalProperties default_props(TFT_BLACK /* background color */,
                                    TFT_WHITE /* border color */);
  GraphicalProperties focus_props(TFT_WHITE /* background color */,
                                  TFT_BLACK /* border color */);
  // Any widget has its dedicated graphical properties for when it has
  // focus and its default graphical properties when it hasn't the
  // focus. If the graphical properties when the widget has the focus
  // are not provided, then they are initialized as a copy of the the
  // default ones. If no default is given, then uses default values
  // (see GraphicalProperties class documentation).
  canvas.init(tft, default_props, focus_props);
  // Add a calbback on Canvas loop() method called in order to perform
  // some extra actions.
  canvas.onLoop(onCanvasLoopCb);
  Serial.println("[End of demo setup]");
}

void loop(void) {
  Serial.println("[Entering loop]");
  // Calling the loop() method will call the loop callback function
  // defined during setup.
  canvas.loop();
  // The callback has touched the canvas, thus it need to be refreshed
  // to see the changes.
  canvas.refresh();
  Serial.println("[Sleep for 700ms]\n");
  delay(700);
}

// Local Variables:
// mode: c++
// End:
