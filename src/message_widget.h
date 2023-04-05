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

#ifndef __MESSAGE_WIDGET_H__
#define __MESSAGE_WIDGET_H__

#include "widget.h"

namespace TFT_eSPI_Widgets {

  /**
   * A simple message Widget.
   */
  class MessageWidget: public Widget {

  protected:

    /**
     * The raw message to display.
     */
    String _orig_message;

    /**
     * The processed message that is displayed.
     */
    String _message;

    /**
     * The number of lines required to display the message.
     */
    int16_t _number_of_lines;

    /**
     * The current offset of the displayed message (relative to the
     * top left corner of the inner area).
     */
    Coordinates _offset;

    /**
     * The wrap status of the message (true if the message is tio be
     * wrapped and false otherwise).
     */
    bool _wrap;

    /**
     * The last time the message has been drawn.
     */
    uint64_t _last_update;

    /**
     * The delay between two frame animation when the message is not
     * sticked to one border.
     */
    uint64_t _animation_delay;

    /**
     * The delay before animation starts when the message is sticked
     * to one border.
     */
    uint64_t _stick_delay;

    /**
     * The offset step to animate the message.
     */
    uint16_t _step;

    /**
     * Fit the current widget area to the inner area of its parent.
     *
     * \param recurse This is the recurse value passed to the fit()
     * method. This parameter is not used for this widget.
     *
     * \param check_for_update This is the check_for_update parameter
     * passed to the fit() method. This parameter is not used for this
     * widget.
     */
    inline virtual void _fit(bool recurse, bool check_for_update) {
      updateMessage();
    }

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
     */
    virtual void _shrink(bool recurse, bool check_for_update);

    /**
     * The specific drawing code for message widgets.
     */
    virtual void _draw();

    /**
     * The specific loop code for message widgets (computation for any
     * animation).
     *
     * \param recurse This is the recurse value passed to the loop()
     * method. This parameter is not used for this widget.
     */
    virtual void _loop(bool recurse);

  public:

    /**
     * Creates a message widget attached to the given Widget.
     *
     * The widget graphical properties (background color, line color,
     * line width, font color, font size) are inherited from the
     * parent widget. This widget doesn't accept the focus by default
     * (this can be changed using the setAcceptFocus() method).
     *
     * \param parent The parent widget of the current one. Be aware
     * that if this parent already has a child widget, then this child
     * is automatically destroyed.
     *
     * \param message The message displayed in the widget. The message
     * alignment can be set with the help of some onDraw callback
     * function.
     *
     * \param wrap If the wrap parameter is true and the wrapped text
     * doesn't fit vertically, the text will be animated from bottom
     * to top. If the wrap parameter is false (default) and the
     * wrapped text doesn't fit horizontally, the text will be
     * animated from right to left.
     *
     * \param animation_delay Set the minimal delay (in milliseconds)
     * between to text animation (be aware that it also depends on the
     * time required by the loop() function).
     *
     * \param stick_delay Set the minimal delay (in milliseconds)
     * before the text being animated (like if it was sitcked on the
     * border ; be aware that it also depends on the time required by
     * the loop() function).
     *
     * \param step The shift in pixels to be applied between two
     * animated frames.
     *
     * \param area The area used by the widget. If the area dimension
     * is empty, then use the area of its parent minus its maximal
     * border size according to its focus state. The top left anchor
     * of the area is relative to the top left corner of its parent.
     *
     * \remark There is no verification about the area to fit into the
     * parent area.
     */
    MessageWidget(Widget &parent,
                  const String &message,
                  bool wrap = false,
                  uint64_t animation_delay = 100,
                  uint64_t stick_delay = 1000,
                  uint16_t step = 2,
                  const Area &area = Area::reference_value);


    /**
     * Return the widget type.
     *
     * \return This method returns the MESSAGE widget type.
     */
    inline virtual Type getType() const {
      return MESSAGE;
    }

    /**
     * Get the displayed message.
     *
     * \return This returns the widget message which is displayed.
     */
    inline String getMessage() const {
      return _message;
    }

    /**
     * Get the original message.
     *
     * \return This returns the widget original message.
     */
    inline String getOriginalMessage() const {
      return _orig_message;
    }

    /**
     * Set the message.
     *
     * \param message The message displayed in the widget.
     *
     * \see See updateMessage() if the text is to be wrapped.
     */
    inline void setMessage(const String &message) {
      _orig_message = message;
      updateMessage();
    }

    /**
     * Get the behavior of the widget when the text is too large to
     * fit into the widget area.
     *
     * \return This returns true if the text is wrapped when too large
     * to fit into the widget area. Indeed, if the wrapped text
     * doesn't fit indo the widget area, then it is animated from
     * bottom to top. If the text is not wrapped but doesn't fit into
     * the widget area, then the text is animated from right to left.
     */
    inline bool getWrap() const {
      return _wrap;
    }

    /**
     * Set the behavior of the widget when the text is too large to
     * fit into the widget area.
     *
     * \param wrap If the wrap parameter is true and the wrapped text
     * doesn't fit vertically, the text will be animated from bottom
     * to top. If the wrap parameter is false (default) and the
     * wrapped text doesn't fit horizontally, the text will be
     * animated from right to left.
     *
     * \see See also the updateMessage() method.
     */
    inline void setWrap(bool wrap) {
      _wrap = wrap;
      updateMessage();
    }

    /**
     * Get the minimal delay (in milliseconds) between to text
     * animation.
     *
     * \see See also setAnimationDelay(), getStickDelay(),
     * setStickDelay(), getWrap() and setWrap() method.
     *
     * \return Return the delay between two animated frames.
     */
    inline uint64_t getAnimationDelay() const {
      return _animation_delay;
    }

    /**
     * Set the minimal delay (in milliseconds) between to text
     * animation.
     *
     * If the text doesn't fit into the widget area and the time since
     * the last effective redrawing of this widget is greater than the
     * given animation delay (and if the message is not sticked to the
     * border), then the text is scrolled (from right to left if text
     * is not wrapped and from bottom to top if text is wrapped).
     *
     * \see See also getAnimationDelay(), getStickDelay(),
     * setStickDelay(), getWrap() and setWrap() method.
     *
     * \param animation_delay The minimal delay (in milliseconds)
     * between to text animation.
     */
    inline void setAnimationDelay(uint64_t animation_delay) {
      _animation_delay = animation_delay;
    }

    /**
     * Get the minimal delay (in milliseconds) before the text is
     * unsticked from the border.
     *
     * \see See also setAnimationDelay(), getAnimationDelay(),
     * setStickDelay(), getWrap() and setWrap() method.
     *
     * \return Return the delay between two animated frames when text
     * is sticked to one border.
     */
    inline uint64_t getStickDelay() const {
      return _stick_delay;
    }

    /**
     * Set the minimal delay (in milliseconds) before the text is
     * unsticked from the border.
     *
     * If the text doesn't fit into the widget area and the time since
     * the last effective redrawing of this widget is greater than the
     * given animation delay (and if the message is sticked to the
     * border), then the text is unsticked and scrolled (from right to
     * left if text is not wrapped and from bottom to top if text is
     * wrapped).
     *
     * \see See also getAnimationDelay(), setAnimationDelay(),
     * getStickDelay(), getWrap() and setWrap() method.
     *
     * \param stick_delay Set the minimal delay (in milliseconds)
     * before the text being animated (like if it was sitcked on the
     * border).
     */
    inline void setStickDelay(uint64_t stick_delay) {
      _stick_delay = stick_delay;
    }

    /**
     * Get the pixel step between two animated frames (when the
     * message overfit the inner area).
     *
     * \return Return the shift in pixels to be applied between two
     * animated frames.
     */
    inline uint16_t getStep() const {
      return _step;
    }

    /**
     * Set the pixel step between two animated frames (when the
     * message overfit the inner area).
     *
     * \param step The shift in pixels to be applied between two
     * animated frames.
     */
    inline void setStep(uint16_t step) {
      _step = step;
    }

    /**
     * Force recompute the message to be displayed.
     *
     * If the text is to be wrapped, then try to wrap on spaces
     * instead of wrapping at the last displayed character (which is
     * the behavior of the TFT_eSPI::print() method). This also
     * updates the number of lines required to print the whole text
     * (according to the wrap status of the widget).
     *
     * \remark This method is automatically called during widget creation and
     * on each call to method setMessage() or to method setWrap(),
     * thus *a priori* there is no need to explicitly call this
     * method.
     */
    void updateMessage();

  };

}

#endif
// Local Variables:
// mode: c++
// End:
