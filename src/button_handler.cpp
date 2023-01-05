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

#include "button_handler.h"

using namespace TFT_eSPI_Widgets;

ButtonHandler::ButtonHandler(unsigned long short_click_max_delay,
                             unsigned long debounce_delay):
  _first_pressed(0),
  _second_pressed(0),
  _third_pressed(0),
  _last_released(0),
  _current_status(RELEASED),
  _short_click_max_delay(short_click_max_delay),
  _debounce_delay(debounce_delay)
{}

void ButtonHandler::reset() {
  _first_pressed = 0;
  _second_pressed = 0;
  _third_pressed = 0;
  _last_released = 0;
  _current_status = RELEASED;
}

ButtonHandler::Event ButtonHandler::getEvent() {
  Event event = NONE;
  unsigned long now = millis();
  Status status = getStatus();
  if (status == _current_status) {
    // Same status
    if (status == RELEASED) {
      // Button is still released.
      if (_last_released and (now - _last_released > _debounce_delay)) {
        // Time to process pending clicks
        if (_second_pressed) {
          event = DOUBLE_CLICK;
        } else if (_first_pressed) {
          event = SINGLE_CLICK;
        } else {
          if (Serial) {
            Serial.printf("%s:%d:%s:This is a bug. "
                          "Please contact the authors of this library.\n",
                          __FILE__, __LINE__, __FUNCTION__);
          }
        }
        reset();
      }
    } else {
      // Button is still pressed.
      if (_third_pressed) {
        // There already was a double click.
        if (now - _third_pressed > _short_click_max_delay) {
          // This is a long press that follows a double click.
          event = DOUBLE_CLICK;
          reset();
          _first_pressed = now;
        }
      } else if (_second_pressed) {
        // There already was a single click.
        if (now - _second_pressed > _short_click_max_delay) {
          // This is a long press that follows a single click.
          event = SINGLE_CLICK;
          reset();
          _first_pressed = now;
        }
      } else {
        if (now - _first_pressed > _short_click_max_delay) {
          event = LONG_PRESS;
        }
      }
    }
  } else {
    // Changing state
    if (status == RELEASED) {
      // Button is just released.
      if (_third_pressed) {
        // This is the end of the third click.
        event = TRIPLE_CLICK;
        reset();
      } else {
        // This is the end of the first or second click.
        _last_released = now;
        if (!_second_pressed) {
          // This is the first click, which may be a long one...
          if (now - _first_pressed > _short_click_max_delay) {
            reset();
          }
        }
      }
    } else {
      // Button is just pressed.
      if (!_first_pressed) {
        // Starting first click, then do nothing for now.
        _first_pressed = now;
      } else if (!_second_pressed) {
        // Starting second click, then do nothing for now.
        _second_pressed = now;
      } else if (!_third_pressed) {
        // Starting third click, then do nothing for now.
        _third_pressed = now;
      } else {
        if (Serial) {
          Serial.printf("%s:%d:%s:This is a bug. "
                        "Please contact the authors of this library.\n",
                        __FILE__, __LINE__, __FUNCTION__);
        }
      }
    }
  }
  _current_status = status;
  return event;
}
