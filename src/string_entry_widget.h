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

#ifndef __STRING_ENTRY_WIDGET_H__
#define __STRING_ENTRY_WIDGET_H__

#include <Arduino.h>
#include "widget.h"

namespace TFT_eSPI_Widgets {

  /**
   * A string entry widget.
   */
  class StringEntryWidget: public Widget {


  public:

   /**
     * The type of callback function that can be called when the
     * string entry widget value is changed.
     *
     * \see See onValueChange() method
     */
    typedef void (*value_change_cb_t)(Widget &, const String &, const String &);


  protected:

    /**
     * The current value of the widget.
     */
    String _value;

    /**
     * The cursor position of the current widget.
     */
    uint8_t _pos;

    /**
     * The last time the string entry has been drawn.
     */
    uint64_t _last_update;

    /**
     * The current offset of the string entry widget (relative
     * to the top left corner of the inner area).
     */
    Coordinates _offset;

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
     *   - Simple left click => change the letter at the current
     *     cursor position to the previous value (in the decreasing
     *     ASCII order and cycling to the end after the first possible
     *     letter).
     *   - Long left click => fast change the letter at the current
     *     cursor position to the previous value.
     *   - Double left click => move the cursor position to the left
     *     (no effect if cursor is at the leftmost position).
     *   - Simple right click => change the letter at the current
     *     cursor position to the next value (in the increasing
     *     ASCII order and cycling to the beginning after the last
     *     possible letter).
     *   - Long right click => fast change the letter at the current
     *     cursor position to the next value.
     *   - Double right click => move the cursor position to the right
     *     (no effect if cursor is at the rightmost position).
     *
     * \param event The event to handle.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _handleEvent(Event event);

    /**
     * The specific drawing code for string entry widgets.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _draw();

    /**
     * The specific loop code for string entry widgets (computation for any
     * animation).
     *
     * \param recurse This is the recurse value passed to the loop()
     * method. This parameter is not used for this widget.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _loop(bool recurse);

  public:

    /**
     * Creates a string entry widget attached to the given Widget.
     *
     * The widget graphical properties (background color, line
     * color, line width, font color, font size) are inherited from
     * the parent widget.
     *
     * \param parent The parent widget of the current one. Be aware
     * that if this parent already has a child widget, then this child
     * is automatically destroyed.
     *
     * \param entry_length The string entry length. This define the
     * length of the string value associated to the widget as well as
     * the number of entry positions to display.
     *
     * \param initial_value The initial value to set for this entry
     * widget. If the given value is longer than the entry_length,
     * then it will be truncated. If it is smaller than the entry
     * length, then ending positions are filled with spaces. Only the
     * ASCII table symbols from space (code 32) to the tilde (code
     * 126) are available. If the string v has characters outside this
     * range, then they are replaced by question marks.
     *
     * \param initial_pos The initial position of the cursor. Any
     * initial position greater than the initial string length will
     * set the cursor after the last non empty character of the
     * initial string if any or at the last position.
     *
     * \param area The area used by the widget. If the area dimension
     * is empty, then use the area of its parent minus its maximal
     * border size according to its focus state. The top left anchor
     * of the area is relative to the top left corner of its parent.
     *
     * \remark There is no verification about the area to fit into the
     * parent area.
     */
    StringEntryWidget(Widget &parent,
                      uint8_t entry_length = 255,
                      const String &initial_value = "",
                      uint8_t initial_pos = (uint8_t) -1,
                      const Area &area = Area::reference_value);

    /**
     * Return the widget type.
     *
     * \return This method returns the STRING_ENTRY widget type.
     */
    inline virtual Type getType() const {
      return STRING_ENTRY;
    }

    /**
     * Get the current widget value.
     *
     * \return This method returns the current value of the widget.
     * The string is not trimmed and is always of size the entry
     * length specified during this widget construction.
     */
    inline String getValue() const {
      return _value;
    }

    /**
     * Set the widget value.
     *
     * \param v The value to set for this entry widget. If the given
     * value is longer than the entry_length, then it will be
     * truncated. If it is smaller than the entry length, then ending
     * positions are filled with spaces. Only the ASCII table symbols
     * from space (code 32) to the tilde (code 126) are available. If
     * the string v has characters outside this range, then they are
     * replaced by question marks.
     */
    void setValue(const String &v);

    /**
     * Get the cursor position.
     *
     * \return The returned value is the current position of the
     * cursor (the letter that can be modified by clicking on the
     * buttons) starting from 0 for the first character.
     */
    inline uint8_t getCursorPos() const {
      return _pos;
    }

    /**
     * Set the cursor position.
     *
     * \param p The position of the cursor (the letter that can be
     * modified by clicking on the buttons) starting from 0 for the
     * first character. Any position greater than the entry length
     * will set the cursor after the last non empty character of the
     * initial string if any or at the last position.
     */
    void setCursorPos(uint8_t p);

    /**
     * Set the cursor position to the next position.
     */
    inline void nextCursorPos() {
      if (++_pos >= _value.length()) {
        _pos = _value.length() - 1;
      }
    }

    /**
     * Set the cursor position to the previous position.
     */
    inline void previousCursorPos() {
      if (_pos-- == 0) {
        _pos = 0;
      }
    }

    /**
     * Set the letter at the cursor position to the next value.
     */
    void nextLetterAtCursorPos();

    /**
     * Set the letter at the cursor position to the next value.
     */
    void previousLetterAtCursorPos();

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
