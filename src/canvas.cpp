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

#include "canvas.h"

using namespace TFT_eSPI_Widgets;

Canvas::Canvas():
  Widget(),
  _tft(NULL),
  _focus_widget(NULL),
  _transmit_focus(true)
{}

Canvas::Canvas(TFT_eSPI &tft,
               const GraphicalProperties &default_graphical_properties,
               const GraphicalProperties &focus_graphical_properties,
               const Area &area):
  Canvas()
{
  init(tft, default_graphical_properties, focus_graphical_properties, area);
}

void Canvas::init(TFT_eSPI &tft,
                  const GraphicalProperties &default_graphical_properties,
                  const GraphicalProperties &focus_graphical_properties,
                  const Area &area) {
  if (_tft) return;
  _tft = &tft;
  setDefaultGraphicalProperties(default_graphical_properties);
  if (&focus_graphical_properties == &GraphicalProperties::default_values) {
    setFocusGraphicalProperties(default_graphical_properties);
  } else {
    setFocusGraphicalProperties(focus_graphical_properties);
  }
  setArea(area);
}

void Canvas::_setFocus(Widget &w) {
  _ensure_initialized();
  if (w.getAcceptFocus()) {
    if (_focus_widget and (_focus_widget != &w)) {
      _transmit_focus = false;
      _focus_widget->unfocus();
      _transmit_focus = true;
    }
    _focus_widget = &w;
  }
}

void Canvas::_unsetFocus(Widget &w) {
  _ensure_initialized();
  if (_focus_widget == &w) {
    _focus_widget = NULL;
    if (_transmit_focus) {
      if (&w != this) {
        Widget *ptr = &w.getParent();
        while ((ptr != this) and !ptr->getAcceptFocus()) {
          ptr = &(ptr->getParent());
        }
        ptr->focus();
      }
    }
  }
}

void Canvas::_handleEvent(Event event) {
  if (_focus_widget and (_focus_widget != this)) {
    _focus_widget->handleEvent(event);
  } else {
    if (event == TRIPLE_RIGHT_CLICK) {
      if (!_focus_widget) {
        focus();
      }
    }
  }
}
