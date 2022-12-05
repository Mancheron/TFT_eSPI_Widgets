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

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <stdexcept>
#include "widget.h"

namespace TFT_eSPI_Widgets {

  /**
   * The canvas is the only kind of Widget that has no parent, but
   * is explicitelly attached to some TFT screen.
   */
  class Canvas: public Widget {

  protected:

    /**
     * The address of the TFT attached to this widget.
     *
     * It must be set using the init() method (or the non default
     * Canvas() constructor).
     */
    TFT_eSPI *_tft;

    /**
     * The address of the focused widget (if any).
     */
    Widget *_focus_widget;

    /**
     * Whether or not transmit the focus on the parent of the
     * unfocused widget.
     */
    bool _transmit_focus;

    /**
     * Throws an exception if the current canvas is not initalized.
     */
    inline void _ensure_initialized() const {
      if (!_tft) {
        throw std::runtime_error("You must initialize the canvas first before calling any other method on it!");
      }
    }

    /**
     * Get the TFT screen attached to current widget.
     *
     * \return This method returns the TFT screen object.
     */
    inline virtual TFT_eSPI &_getTFT() const {
      _ensure_initialized();
      return *_tft;
    }

    /**
     * Get the focus status of the given widget.
     *
     * \param w The widget for which we want to know if it is focused.
     *
     * \return This method returns true if the given widgets has the
     * focus.
     */
    inline virtual bool _hasFocus(const Widget &w) const {
      _ensure_initialized();
      return _focus_widget == &w;
    }

    /**
     * Set the focus on the given widget.
     *
     * \param w The widget for which we want to give the focus.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _setFocus(Widget &w) {
      _ensure_initialized();
      if (_focus_widget) {
        _transmit_focus = false;
        _focus_widget->unfocus();
        _transmit_focus = true;
      }
      _focus_widget = &w;
    }

    /**
     * Loose the focus from the given widget.
     *
     * \param w The widget for which we want to remove the focus.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _unsetFocus(Widget &w) {
      _ensure_initialized();
      if (_focus_widget == &w) {
        _focus_widget = NULL;
        if (_transmit_focus and (&w != this)) {
          w.getParent().focus();
        }
      }
    }

    /**
     * Action to perform when the current widget is passed some event.
     *
     * Send the event to the focused widget (if any).
     *
     * \param event The event to handle.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _handleEvent(Event event) {
      if (_focus_widget and (_focus_widget != this)) {
        _focus_widget->handleEvent(event);
      } else {
        if (event == TRIPLE_LEFT_CLICK) {
          if (!_focus_widget) {
            focus();
          }
        }
      }
    }

  public:

    /**
     * Creates a canvas widget (which must be initialized with the
     * init() method).
     */
    Canvas();

    /**
     * Creates (and initialize) a canvas widget (rectangular area)
     * associated to the given TFT.
     *
     * \param tft The TFT screen where this canvas and its descendants
     * will be drawn.
     *
     * \param default_graphical_properties The graphical properties to
     * use to draw this canvas when it hasn't got the focus.
     *
     * \param focus_graphical_properties The graphical properties to
     * use to draw this canvas when it has got the focus. If it is set
     * to the GraphicalProperties::default_values constant), then the
     * value of the default_graphical_properties is used instead.
     *
     * \param area The area on the TFT screen to use for this
     * canvas. The area anchor is the absolute position according to
     * the main TFT screen top left corner. There is no verification
     * about the area to fit into the TFT screen. If the area is
     * empty, then uses the TFT dimensions and places the area anchor
     * at the Coordinates::origin.
     *
     * \see See init() method.
     */
    Canvas(TFT_eSPI &tft,
           const GraphicalProperties &default_graphical_properties = GraphicalProperties::default_values,
           const GraphicalProperties &focus_graphical_properties = GraphicalProperties::default_values,
           const Area &area = Area::reference_value);

    /**
     * Initialize the canvas widget (rectangular area) associated to
     * the given TFT.
     *
     * \param tft The TFT screen where this canvas and its descendants
     * will be drawn.
     *
     * \param default_graphical_properties The graphical properties to
     * use to draw this canvas when it hasn't got the focus.
     *
     * \param focus_graphical_properties The graphical properties to
     * use to draw this canvas when it has got the focus. If it is set
     * to the GraphicalProperties::default_values constant), then the
     * value of the default_graphical_properties is used instead.
     *
     * \param area The area on the TFT screen to use for this
     * canvas. The area anchor is the absolute position according to
     * the main TFT screen top left corner. There is no verification
     * about the area to fit into the TFT screen. If the area is
     * empty, then uses the TFT dimensions and places the area anchor
     * at the Coordinates::origin.
     *
     * If the widget was already initialized, then does nothing.
     */
    void init(TFT_eSPI &tft,
              const GraphicalProperties &default_graphical_properties = GraphicalProperties::default_values,
              const GraphicalProperties &focus_graphical_properties = GraphicalProperties::default_values,
              const Area &area = Area::empty);

    /**
     * Return the widget type.
     *
     * \return This method returns the CANVAS widget type.
     */
    inline virtual Type getType() const {
      return CANVAS;
    }

    /**
     * Return a pointer to the widget having the focus (if any).
     *
     * \return This method returns the address of the widget having
     * the focus or NULL if not widget has it.
     */
    inline const Widget *getFocusedWidget() const {
      _ensure_initialized();
      return _focus_widget;
    }

  };

}

#endif
// Local Variables:
// mode: c++
// End:
