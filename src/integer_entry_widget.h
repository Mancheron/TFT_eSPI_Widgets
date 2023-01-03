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

#ifndef __INTEGER_ENTRY_WIDGET_H__
#define __INTEGER_ENTRY_WIDGET_H__

#include <Arduino.h>
#include <limits>
#include "widget.h"

namespace TFT_eSPI_Widgets {

  /**
   * An integer entry widget.
   */
  class IntegerEntryWidget: public Widget {

  public:

    /**
     * The type of callback function that can be called when the
     * integer entry widget value is changed.
     *
     * \see See onValueChange() method
     */
    typedef void (*value_change_cb_t)(Widget &, int32_t, int32_t);

  protected:

    /**
     * The current value of the widget.
     */
    int32_t _value;

    /**
     * The minimal allowed value for the widget.
     */
    int32_t _minimal_value;

    /**
     * The maximal allowed value for the widget.
     */
    int32_t _maximal_value;

    /**
     * A custom callback function to call when this widget value
     * changes.
     */
    value_change_cb_t _value_change_cb;

    /**
     * Shrink the current widget area to the smallest dimension that
     * allows to see its content.
     *
     * \param recurse This is the recurse value passed to the shrink()
     * method. This parameter is not used for this widget.
     *
     * \param check_for_update This is the check_for_update parameter
     * passed to the fit() method. This parameter is not used for this
     * widget.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _shrink(bool recurse, bool check_for_update);

    /**
     * Action to perform when the current widget is passed some event.
     *
     * Specific events this widget can handle are:
     *   - Simple right click => increase the value
     *   - Long right click => fast increase the value
     *   - Simple left click => decrease the value
     *   - Long left click => fast decrease the value
     *
     * \param event The event to handle.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _handleEvent(Event event);

    /**
     * The specific drawing code for integer entry widgets.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _draw();

  public:

    /**
     * Creates an integer entry widget attached to the given Widget.
     *
     * The widget graphical properties (background color, line
     * color, line width, font color, font size) are inherited from
     * the parent widget.
     *
     * The widget initial value is 0 by default, but must belong to
     * the interval defined by the minimal_value and maximal_value
     * parameters. So if the initial value is lower than the minimal
     * value, then it is set to the minimal value and if the initial
     * value is greater than the maximal value, then it is set to the
     * maximal value.
     *
     * \param parent The parent widget of the current one. Be aware
     * that if this parent already has a child widget, then this child
     * is automatically destroyed.
     *
     * \param initial_value The initial value of the widget.
     *
     * \param minimal_value The minimal value of the widget. If the
     * initial value is lower than this minimal value, then the
     * initial value is set to this minimal value.
     *
     * \param maximal_value The maximal value of the widget. If the
     * initial value is greater than this maximal value, then the
     * initial value is set to this maximal value.
     *
     * \param area The area used by the widget. If the area dimension
     * is empty, then use the area of its parent minus its maximal
     * border size according to its focus state. The top left anchor
     * of the area is relative to the top left corner of its parent.
     *
     * \remark There is no verification about the area to fit into the
     * parent area.
     */
    IntegerEntryWidget(Widget &parent,
                       int32_t initial_value = 0,
                       int32_t minimal_value = INT_MIN,
                       int32_t maximal_value = INT_MAX,
                       const Area &area = Area::reference_value);

    /**
     * Return the widget type.
     *
     * \return This method returns the INT_ENTRY widget type.
     */
    inline virtual Type getType() const {
      return INT_ENTRY;
    }

    /**
     * Get the current widget value.
     *
     * \return This method returns the current value of the widget.
     */
    inline int32_t getValue() const {
      return _value;
    }

    /**
     * Set the widget value.
     *
     * \param v The value to set to the current widget.
     *
     * If the given value is lower than the minimal widget value, then
     * the current value is set to the minimal value. If the given
     * value is greater than the maximal widget value, then the
     * current value is set to the maximal value.
     */
    inline void setValue(int32_t v) {
      int32_t orig_value = _value;
      _value = constrain(v, _minimal_value, _maximal_value);
      if (_value_change_cb and (orig_value != _value)) {
        _value_change_cb(*this, orig_value, _value);
      }
    }

    /**
     * Get the minimal widget value.
     *
     * \return This method returns the minimal value of the widget.
     */
    inline int32_t getMinimalValue() const {
      return _minimal_value;
    }

    /**
     * Set the widget minimal value.
     *
     * \param v The minimal value of the widget. If the initial value
     * is lower than this minimal value, then the initial value is set
     * to this minimal value.
     */
    inline void setMinimalValue(int32_t v) {
      _minimal_value = v;
      setValue(_value);
    }

    /**
     * Get the maximal widget value.
     *
     * \return This method returns the maximal value of the widget.
     */
    inline int32_t getMaximalValue() const {
      return _maximal_value;
    }

    /**
     * Set the widget maximal value.
     *
     * \param v The maximal value of the widget. If the initial value
     * is greater than this maximal value, then the initial value is
     * set to this maximal value.
     */
    inline void setMaximalValue(int32_t v) {
      _maximal_value = v;
      setValue(_value);
    }

    /**
     * Increment the current value (up to the upper bound).
     */
    inline void incrValue() {
      setValue(++_value);
    }

    /**
     * Decrement the current value (down to the lower bound).
     */
    inline void decrValue() {
      setValue(--_value);
    }

    /**
     * Any extra action that must operate when the value changes.
     *
     * \param cb The callback function to call when the setValue()
     * method is called on this widget.
     */
    inline void onValueChange(const value_change_cb_t cb) {
      _value_change_cb = cb;
    }

  };

}

#endif
// Local Variables:
// mode: c++
// End:
