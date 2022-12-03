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

#include "Gnu-Tux-160x80.h"
#include "Gnu-Tux-320x160.h"

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

  // It is REQUIRED to create any child widget using the "new"
  // keyword.
  new ImageWidget(canvas,
                  Gnu_Tux_160x80_data,
                  Dimensions(Gnu_Tux_160x80_width, Gnu_Tux_160x80_height),
                  Coordinates::origin,
                  Area(160, 80, // Set the image area to 160x80
                       // centered on the canvas (which is expected to be
                       // larger than 160x80)
                       (canvas.getArea().width - 160) / 2,
                       (canvas.getArea().height - 80) / 2));

  // Force redraw on next loop.
  canvas.touch();

  Serial.print("- root widget type is: ");
  Serial.println(canvas.getTypeString());
  Serial.print("- child widget type is: ");
  Serial.println(canvas.getChild().getTypeString());

  Serial.println("[End of demo setup]");
  Serial.println("Images will be displayed for 2 seconds.");
  Serial.println("==========");
  start_cycle = millis();
}

void loop(void) {
  // Calling the loop() method will call the loop of any descendant
  // widget from the current canvas in the widget tree.
  canvas.loop();
  canvas.refresh();

  unsigned long ellapsed_time = millis() - start_cycle;

  // By default, getChild() will return a Widget (the base class of
  // any widget), but it is possible to specify the subclass of widget
  // in order to use specific methods (be aware that no control is
  // done, so any mistake on the subclass will be fatal).
  ImageWidget &w = canvas.getChild<ImageWidget>();

  if (ellapsed_time > 2000) {
    if (w.getData() == Gnu_Tux_160x80_data) {
      w.setData(Gnu_Tux_320x160_data,
                Dimensions(Gnu_Tux_320x160_width, Gnu_Tux_320x160_height));
      Serial.printf("Setting a %usx%us image [should be cropped]\n",
                    Gnu_Tux_320x160_width, Gnu_Tux_320x160_height);
    } else {
      Coordinates offset = w.getOffset();
      if (offset.x == 0) {
        if (offset.y == 0) {
          offset.y = -w.getDimensions().height / 2;
          Serial.println("Moving the image to the bottom.");
        } else {
          offset.x = -w.getDimensions().width / 2;
          Serial.println("Moving the image to the right.");
        }
      } else {
        if (offset.y == 0) {
          offset.x = 0;
          Serial.println("Reset image offset.");
        } else {
          offset.y = 0;
          Serial.println("Moving the image to the top.");
        }
      }
      w.setOffset(offset);
      if (w.getOffset() == Coordinates::origin) {
        w.setData(Gnu_Tux_160x80_data,
                  Dimensions(Gnu_Tux_160x80_width, Gnu_Tux_160x80_height));
        Serial.printf("Setting a %usx%us image\n",
                      Gnu_Tux_160x80_width, Gnu_Tux_160x80_height);
      }
    }
    w.touch();
    start_cycle = millis();
  }

}

// Local Variables:
// mode: c++
// End: