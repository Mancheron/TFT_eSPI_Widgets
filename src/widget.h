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

#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "graphical_properties.h"
#include "area.h"

namespace TFT_eSPI_Widgets {

  /**
   * The kind of widget currently displayed on the screen.
   */
  enum Type {
             CANVAS,        /**< Canvas widget. */
             GENERIC,       /**< Generic widget. */
             IMAGE,         /**< Image widget. */
             INT_ENTRY,     /**< Integer entry widget. */
             FLOAT_ENTRY,   /**< Float entry widget. */
             STRING_ENTRY,  /**< String entry widget. */
             MESSAGE,       /**< Simple message widget. */
             CUSTOM,        /**< Custom widget. */
  };

  /**
   * Button click events.
   *
   * Widgets are assumed to handle signal from two (physical or
   * logical) buttons arbitrarily called the left button and the right
   * button.
   *
   * Both buttons are supposed to be clickable once, twice or thrice
   * in a short period of time.
   *
   * Both buttons are also supposed to be clickable for a long period
   * of time.
   *
   * All this situations are represented by the emission of
   * different signal events (one for each situation).
   *
   * Whatever the widget having the focus, a triple click on the left
   * button should apply the unfocus() method on it whereas a triple
   * click on the right button should apply the focus() method on its
   * child.
   */
  enum Event {
              SINGLE_LEFT_CLICK,  /**< Single left click event */
              DOUBLE_LEFT_CLICK,  /**< Double left click event */
              TRIPLE_LEFT_CLICK,  /**< Triple left click event */
              LONG_LEFT_PRESS,    /**< Long left pressed event */
              SINGLE_RIGHT_CLICK, /**< Single right click event */
              DOUBLE_RIGHT_CLICK, /**< Double right click event */
              TRIPLE_RIGHT_CLICK, /**< Triple right click event */
              LONG_RIGHT_PRESS,   /**< Long right pressed event */
  };

  /**
   * The Widget Interface.
   *
   * A widget is a graphical element representation to be drawn on
   * some TFT screen. It can be seen as a component unit of the screen
   * and are organized as a tree, such that a widget has a parent
   * widget in the tree (except the root widget, of course) and may
   * have a child or children. This structure is referred as the
   * widget tree in this documentation.
   *
   * Any widget must derive from this interface and must at least
   * override the getType() method.
   *
   * In order to customize the widget behavior, the following
   * protected methods should be overridden:
   *  - _focus(),
   *  - _unfocus(),
   *  - _handleEvent(),
   *  - _loop(),
   *  - _draw().
   *
   * Each widget **except** the root widget must be created
   * *dynamically* (using the `new` operator). The root widget (and
   * this widget interface) is able to delete each dynamically created
   * widget associated to a parent widget in order to have no memory
   * leaks.
   */
  class Widget {

    /**
     * The counter for setting widget IDs.
     */
    static size_t _counter;

  public:

    /**
     * Retrieve the current ID counter value.
     *
     * \return This gives the number of created widgets since the
     * beginning.
     */
    inline static size_t getCounter() {
      return _counter;
    }

    /**
     * The type of callback function that can be applyed to add some
     * hooks on widget loop(), draw(), refresh(), focus() and
     * unfocus() methods.
     */
    typedef void (*widget_cb_t)(Widget &);

    /**
     * The type of callback function that can be applyed to add some
     * hooks on widget handleEvent() method.
     *
     * If the function returns true, then the event will not be
     * further processed by the default event handler of the widget.
     */
    typedef bool (*event_handler_cb_t)(Widget &, Event);

  protected:

    /**
     * The root of the widget tree.
     */
    Widget &_root;

    /**
     * The parent of the current widget in the widget tree
     */
    Widget &_parent;

    /**
     * The address of the child widget (if any).
     */
    Widget *_child;

    /**
     * The area used by the widget.
     *
     * The top left anchor of the area is the absolute position from
     * the top left corner of the TFT screen.
     */
    Area _area;

    /**
     * The graphical properties to use to draw the widget when it
     * hasn't got the focus.
     */
    GraphicalProperties _default_graph_props;

    /**
     * The graphical properties to use to draw the widget when it has
     * got the focus.
     */
    GraphicalProperties _focus_graph_props;

    /**
     * The widget drawing status.
     *
     * This is true if the widget needs to be (re)drawn.
     */
    bool _need_update;

    /**
     * A custom callback function to call when some event is passed to
     * the current widget.
     */
    event_handler_cb_t _event_handler_cb;

    /**
     * A custom callback function to call when the draw() method is
     * called on the current widget.
     */
    widget_cb_t _draw_cb;

    /**
     * A custom callback function to call when the refresh() method is
     * called on the current widget.
     */
    widget_cb_t _refresh_cb;

    /**
     * A custom callback function to call when the loop() method is
     * called on the current widget.
     */
    widget_cb_t _loop_cb;

    /**
     * A custom callback function to call when the current widget get
     * the focus.
     */
    widget_cb_t _focus_cb;

    /**
     * A custom callback function to call when the current widget
     * loose the focus.
     */
    widget_cb_t _unfocus_cb;

    /**
     * Get the TFT screen attached to current widget by asking the
     * root of the widget tree.
     *
     * \remark This method **must** be overridden by any class that
     * define root Widgets but **shouldn't** be overridden by other
     * derived class.
     *
     * \return This method returns the TFT screen object.
     */
    inline virtual TFT_eSPI &_getTFT() const { return _root._getTFT(); }

    /**
     * Fit the current widget area to the inner area of its parent.
     *
     * \remark This method might be overridden by any derived class
     * that have some custom size fitting strategy.
     *
     * \param recurse This is the recurse value passed to the fit()
     * method.
     *
     * \param check_for_update This is the check_for_update parameter
     * passed to the fit() method.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _fit(bool recurse, bool check_for_update) {}

    /**
     * Shrink the current widget area to the smallest dimension that
     * allows to see its content.
     *
     * \remark This method might be overridden by any derived class
     * that have some minimal size content.
     *
     * \param recurse This is the recurse value passed to the shrink()
     * method. Allmost all widgets should ignore this parameter.
     *
     * \param check_for_update This is the check_for_update parameter
     * passed to the fit() method.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _shrink(bool recurse, bool check_for_update) {}

    /**
     * Get the focus status of the given widget by asking the root of
     * the widget tree.
     *
     * \remark This method **must** be overridden by any class that
     * define root Widgets but **shouldn't** be overridden by other
     * derived class.
     *
     * \param w The widget for which we want to know if it is focused.
     *
     * \return This method returns true if the given widgets has the
     * focus.
     */
    inline virtual bool _hasFocus(const Widget &w) const {
      return _root._hasFocus(w);
    }

    /**
     * Set the focus on the given widget by asking the root of the
     * widget tree to give the focus.
     *
     * \remark This method **must** be overridden by any class that
     * define root Widgets but **shouldn't** be overridden by other
     * derived class.
     *
     * \param w The widget for which we want to give the focus.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _setFocus(Widget &w) {
      _root._setFocus(w);
    }

    /**
     * Loose the focus from the given widget by asking the root of the
     * widget tree to remove the focus.
     *
     * \remark This method **must** be overridden by any class that
     * define root Widgets but **shouldn't** be overridden by other
     * derived class.
     *
     * \param w The widget for which we want to remove the focus.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _unsetFocus(Widget &w) {
      _root._unsetFocus(w);
    }

    /**
     * Action to perform when the current widget get the focus.
     *
     * Does nothing by default.
     *
     * \remark This method might be overridden by any derived class
     * that needs to perform specific actions when current widget has
     * the focus.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _focus() {}

    /**
     * Action to perform when the current widget loose the focus.
     *
     * Does nothing by default.
     *
     * \remark This method might be overridden by any derived class
     * that needs to perform specific actions when current widget
     * loose the focus.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _unfocus() {}

    /**
     * Action to perform when the current widget is passed some event.
     *
     * Does nothing by default.
     *
     * \remark This method might be overridden by any derived class
     * that needs to perform specific actions when current widget is
     * passed some event.
     *
     * \param event The event to handle.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _handleEvent(Event event) {}

    /**
     * Action to perform when the loop method is called on the current
     * widget.
     *
     * Does nothing by default.
     *
     * \remark This method might be overridden by any derived class
     * that needs to perform specific actions when loop() method is
     * called on the current widget.
     *
     * \param recurse This is the recurse value passed to the loop()
     * method. Allmost all widgets should ignore this parameter.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _loop(bool recurse) {}

    /**
     * Action to perform when the draw() method is called on the
     * current widget.
     *
     * This method is called after the viewport is set and drawn
     * according to the graphical properties and before child is
     * printed (if any).
     *
     * Does nothing by default.
     *
     * \remark This method should be overridden by any derived class
     * that needs to perform specific actions when the current widget
     * is drawn.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _draw() {}

    /**
     * Action to perform when the refresh() method is called on the
     * current widget.
     *
     * This method is called at the end of the refresh().
     *
     * Does nothing by default.
     *
     * \remark This method should be overridden by any derived class
     * that needs to perform specific actions when the current widget
     * is refreshed.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    inline virtual void _refresh() {}

  public:

    /**
     * This widget ID.
     */
    const size_t id;

    /**
     * Creates an orphan widget with an empty area.
     */
    Widget();

    /**
     * Creates a widget (rectangular area) attached to the given
     * Widget.
     *
     * The widget graphical properties (background color, line color,
     * line width, font color, font size) are inherited from the
     * parent widget.
     *
     * \param parent The parent widget of the current one. Be aware
     * that if this parent already has a child widget, then this child
     * is automatically destroyed.
     *
     * \param area The area used by the widget. If the area dimension
     * is empty, then use the area of its parent minus its maximal
     * border size according to its focus state. The top left anchor
     * of the area is relative to the top left corner of its parent.
     *
     * \remark There is no verification about the area to fit into the
     * parent area.
     */
    Widget(Widget &parent, const Area &area);

    /**
     * Prevent copy construction of some widget.
     */
    Widget(const Widget &w) = delete;

    /**
     * Prevent overwriting a widget by another one.
     */
    Widget &operator=(const Widget &w) = delete;

    /**
     * Destroy the widget and its descendants (if any).
     *
     * If this is not an orphan widget, then it removes itself from
     * its parent _child attribute.
     */
    virtual ~Widget();

    /**
     * Interrogate about the current widget being the root of the
     * widget tree.
     *
     * \return This method returns true if and only if the current
     * widget is the root of the widget tree.
     */
    inline bool isRoot() const {
      return this == &_root;
    }

    /**
     * Return the root widget.
     *
     * Actually, any widget is in a widget tree.
     *
     * \return This method returns the widget tree root.
     */
    inline Widget &getRoot() const {
      return _root;
    }

    /**
     * Return the parent widget.
     *
     * \return This method returns the current widget parent in the
     * widget tree (see getRoot() documentation).
     */
    inline Widget &getParent() const {
      return _parent;
    }

    /**
     * Interrogate about some child existence for current widget.
     *
     * \return This method returns true if and only if the current
     * widget has a child.
     */
    inline bool hasChild() const {
      return _child != NULL;
    }

    /**
     * Cast the current widget to its real derived class.
     *
     * \see It is safer to ensure the correct widget type is used (may
     * be using getType()).
     *
     * \return Return a reference on the current widget child (be
     * aware that this child must exist).
     */
    template <typename T>
    T &as() {
      return *static_cast<T *>(this);
    }

    /**
     * Cast the current widget to its real derived class.
     *
     * \see It is safer to ensure the correct widget type is used (may
     * be using getType()).
     *
     * \return Return a reference on the current widget child (be
     * aware that this child must exist).
     */
    template <typename T>
    const T &as() const {
      return *static_cast<const T *>(this);
    }

    /**
     * Retrieve the child of the current widget.
     *
     * By default, the return type is Widget reference, but one can
     * specify the real type of the widget (no verification is done)
     * in order to use the specific subtype methods.
     *
     * \see It is safer to use the hasChild() method to ensure for the
     * child existence before using this. It is also a good idea to
     * ensure the correct widget type is used (may be using
     * getType()).
     *
     * \see The type conversion is operated by the as() method.
     *
     * \return Return a reference on the current widget child (be
     * aware that this child must exist).
     */
    template <typename T = Widget>
    T &getChild() const {
      return _child->as<T>();
    }

    /**
     * Remove current widget child and all its descendants in the
     * widget tree (if any).
     */
    virtual void removeChild();

    /**
     * Return the widget type (must be overridden by specialized
     * class)
     *
     * \return The concrete widget type is returned.
     */
    virtual Type getType() const = 0;

    /**
     * Return the given widget type as a string.
     *
     * \param t The widget type.
     *
     * \return Return a C string human readable name for the given
     * type.
     */
    static const char *getTypeString(Type t);

    /**
     * Return the widget type as a string.
     *
     * \note Custom widget should override this method in order to
     * have both level of description.  As an example, let us suppose
     * that we have a custom widget object of some MyCustomWidget
     * class:
     * ```C++
     * MyCustomWidget w(...); // Don't give details on constructor
     *                        // parameters
     * Widget &w_ref = w; // Here, w_ref is mostly considered as a
     *                    // widget (except for the virtual methods
     *                    // overridden by the MyCustomWidget class
     *                    // definition, of course!).
     * Serial.println(w_ref.getTypeString()); // This should print
     *                                        // "CUSTOM" on Serial
     *                                        // monitor.
     * Serial.println(w.getTypeString());     // This should print the
     *                                        // custom string defined in
     *                                        // the overridden method
     *                                        // during MyCustomWidget
     *                                        // class definition.
     * ```
     *
     * \return Return the C string human readable name for the current
     * widget concrete type.
     */
    inline const char *getTypeString() const {
      return getTypeString(getType());
    }

    /**
     * Get the widget area.
     *
     * \param absolute If true, then define the anchor position of the
     * area absolute from the top left corner of the screen. If false
     * (default), then define the anchor position of the area relative
     * to the top left corner of its parent if current widget is not
     * the root of the widget tree.
     *
     * \return Return the widget area.
     */
    Area getArea(bool absolute = false) const;

    /**
     * Get the widget inner area.
     *
     * \param absolute If false (default), then define the anchor
     * position of the area absolute from the top left corner of the
     * screen. If true, then define the anchor position of the area
     * relative to the top left corner of the widget area.
     *
     * \return Return the widget inner area. It is the widget area
     * reduced by the maximal border width.
     */
    Area getInnerArea(bool absolute = false) const;

    /**
     * Get the screen area.
     *
     * \return Return the TFT screen area.
     */
    inline Area getScreenArea() const {
      TFT_eSPI &tft = getTFT();
      return Area(tft.width(), tft.height(), 0, 0);
    }

    /**
     * Set the widget area.
     *
     * \param area The area used by the widget. Except for root
     * widget, if the area dimension is empty, then fit to the parent
     * inner area. For the root widget, if the area dimension is
     * empty, then uses the TFT screen dimensions.
     *
     * \param absolute If false (default), then the anchor position of
     * the given area is absolute from the top left corner of the
     * screen. If true, then the anchor position of the given area is
     * relative to the top left corner of its parent if current widget
     * is not the root of the widget tree.
     *
     * \param check_for_update When this parameter is true, then
     * automatically call the touchOnAreaChanges() method after
     * setting the area, else does nothing more.
     *
     * \remark There is no verification about the area to fit into the
     * TFT screen or even the parent area.
     */
    void setArea(const Area &area, bool absolute = false, bool check_for_update = true);

    /**
     * Fit the current widget area to the inner area of its parent.
     *
     * \param recurse If the widget has a child and if recurse is
     * true, then the fit() method is applied on the child and all its
     * descendants (false by default).
     *
     * \param check_for_update When this parameter is true (default),
     * then automatically call the touchOnAreaChanges() method after
     * setting the area, else does nothing more.
     */
    void fit(bool recurse = false, bool check_for_update = true);

    /**
     * Shrink the current widget area to the smallest dimension that
     * allows to see its content.
     *
     * \see This method will internally call setPosition() and
     * _shrink().
     *
     * \param horizontal The horizontal anchor placement of this
     * widget expressed as a percentage. Setting 0% means align on the
     * left of the parent inner area, whereas 100% means align on the
     * right of the parent inner area. The special '-1' value means
     * (which is equalt to 255 as unsigned 8 bits integer) won't
     * change the horizontal position. Default is centering.
     *
     * \param vertical The vertical anchor placement of this widget
     * after being shrinked expressed as a percentage. Setting 0%
     * means align on the top of the parent inner area, whereas 100%
     * means align on the bottom of the parent inner area. The special
     * '-1' value means (which is equalt to 255 as unsigned 8 bits
     * integer) won't change the vertical position. Default is
     * centering.
     *
     * \param recurse If the widget has a child and if recurse is
     * true, then the shrink() method is applied on the child and its
     * descendants (starting from the deeper descendants widgets)
     * before shrinking current widget (false by default).
     *
     * \param check_for_update When this parameter is true (default),
     * then automatically call the touchOnAreaChanges() method after
     * setting the area, else does nothing more.
     */
    void shrink(uint8_t horizontal = 50,
                uint8_t vertical = 50,
                bool recurse = false,
                bool check_for_update = true);

    /**
     * Position the current widget relative to its parents for non
     * root widgets or to the screen otherwise.
     *
     * \param horizontal The horizontal anchor placement of this
     * widget expressed as a percentage. Setting 0% means align on the
     * left of the parent inner area, whereas 100% means align on the
     * right of the parent inner area. The special '-1' value means
     * (which is equalt to 255 as unsigned 8 bits integer) won't
     * change the horizontal position (this is the default).
     *
     * \param vertical The vertical anchor placement of this widget
     * expressed as a percentage. Setting 0% means align on the top of
     * the parent inner area, whereas 100% means align on the bottom
     * of the parent inner area. The special '-1' value means (which
     * is equalt to 255 as unsigned 8 bits integer) won't change the
     * vertical position (this is the default).
     *
     * \param check_for_update When this parameter is true (default),
     * then automatically call the touchOnAreaChanges() method after
     * setting the area, else does nothing more.
     */
    void setPosition(uint8_t horizontal = -1,
                     uint8_t vertical = -1,
                     bool check_for_update = true);

    /**
     * Touch the current widget if the area differs from the given
     * one. Additionally, touch the parent widget (if any) if the
     * current area doesn't completely includes the given one.
     *
     * This is typically needed to call this method after calling
     * setArea(), setPosition(), fit() or shrink() on the current
     * widget.
     *
     * \param orig_area The area to compare with the current widget
     * area (typically a backup of the area before some modification).
     */
    void touchOnAreaChanges(const Area &orig_area);

    /**
     * Get the current graphical properties (according to the focus
     * status).
     *
     * \return This method returns either the default graphical
     * properties of current widget (if it is not focused) or its
     * focus graphical properties.
     */
    inline const GraphicalProperties &getGraphicalProperties() const {
      return hasFocus() ? _focus_graph_props : _default_graph_props;
    }

    /**
     * Get the default graphical properties (the properties used to
     * draw the widget when it hasn't got the focus).
     *
     * \return This method returns the default graphical properties of
     * current widget.
     */
    inline const GraphicalProperties &getDefaultGraphicalProperties() const {
      return _default_graph_props;
    }

    /**
     * Set the default graphical properties.
     *
     * \param graphical_properties The graphical properties to use to
     * draw the widget when it hasn't got the focus.
     */
    inline void setDefaultGraphicalProperties(const GraphicalProperties &graphical_properties) {
      _default_graph_props = graphical_properties;
    }

    /**
     * Get the focus graphical properties (the properties used to draw
     * the widget when it has got the focus).
     *
     * \return This method returns the focus graphical properties of
     * current widget.
     */
    inline const GraphicalProperties &getFocusGraphicalProperties() const {
      return _focus_graph_props;
    }

    /**
     * Set the focus graphical properties.
     *
     * \param graphical_properties The graphical properties to use to
     * draw the widget when it has got the focus.
     */
    inline void setFocusGraphicalProperties(const GraphicalProperties &graphical_properties) {
      _focus_graph_props = graphical_properties;
    }

    /**
     * Any extra action that must operate during event handling.
     *
     * \param cb The callback function to call when the handleEvent()
     * method is called on the widget.
     */
    inline void onEvent(const event_handler_cb_t &cb) {
      _event_handler_cb = cb;
    }

    /**
     * Any extra action that must operate during the drawing.
     *
     * \param cb The callback function to call when the draw() method
     * is called on the widget.
     */
    inline void onDraw(const widget_cb_t &cb) {
      _draw_cb = cb;
    }

    /**
     * Any extra action that must operate during the refresh.
     *
     * \param cb The callback function to call when the refresh()
     * method is called on the widget.
     */
    inline void onRefresh(const widget_cb_t &cb) {
      _refresh_cb = cb;
    }

    /**
     * Any extra action that must operate during the loop.
     *
     * \param cb The callback function to call when the loop() method
     * is called on the widget.
     */
    inline void onLoop(const widget_cb_t &cb) {
      _loop_cb = cb;
    }

    /**
     * Any extra action that must operate when current widget get the
     * focus.
     *
     * \param cb The callback function to call when the focus() method
     * is called on the widget.
     */
    inline void onFocus(const widget_cb_t &cb) {
      _focus_cb = cb;
    }

    /**
     * Any extra action that must operate when current widget loose
     * the focus.
     *
     * \param cb The callback function to call when the unfocus()
     * method is called on the widget.
     */
    inline void onUnfocus(const widget_cb_t &cb) {
      _unfocus_cb = cb;
    }

    /**
     * Return the attached TFT screen.
     *
     * \return This method returns the TFT object screen on which it
     * is drawn.
     */
    inline TFT_eSPI &getTFT() const {
      return _getTFT();
    }

    /**
     * Return true if and only if current Widget has focus.
     *
     * \return This method succeed if current Widget has focus and
     * fails otherwise.
     */
    inline bool hasFocus() const {
      return _hasFocus(*this);
    }

    /**
     * Focus on the current widget.
     *
     * \see A callback function can be set using onFocus() method.
     */
    void focus();

    /**
     * Focus off the current widget.
     *
     * \see A callback function can be set using onUnfocus() method.
     */
    void unfocus();

    /**
     * Any action that must operate on event.
     *
     * For any widget, when a triple left click event is passed and
     * the current widget has the focus, then it is unfocused and the
     * focus is given to its parent (if any).
     *
     * For any widget, when a triple right click event is passed and
     * the current widget has the focus, then the focus is given to
     * its child (if any). If no widget has the focus, then the root
     * widget get it.
     *
     * If current widget hasn't got the focus, then does nothing.
     *
     * \see A callback function can be set using onEvent() method.
     *
     * \param event The event to handle.
     */
    void handleEvent(Event event);

    /**
     * Draw or redraw the widget if necessary (if current widget has
     * been touched since its last drawing).
     *
     * \note If the widget is effectively drawn, then its child widget
     * (if any) is touched.
     *
     * \see See touch() and refresh() methods.
     */
    void draw();

    /**
     * Draw the widget if necessary (if widget has been touched since
     * its last drawing) and refresh also its descendants in the
     * widget tree.
     *
     * \details This completes the draw() method since on (re)drawing
     * the current widget, its child (if any) is only touched but not
     * (re)drawn. After (re)drawing current widget, the refresh()
     * method is called on its child, propagating the drawing of its
     * descendant widgets in the widget tree.
     *
     * Calling the refresh() method on the root widget will perform a
     * depth-first traversal of the tree and will redraw all touched
     * widgets and there descendants. Thus, touching the root widget
     * and refreshing it will redraw the entire screen (see the
     * examples provided with this library).
     *
     * \see See touch() and draw() methods.
     */
    void refresh();

    /**
     * Force (re-)drawing on next draw() call.
     *
     * If draw() method is called on some of its ascendants widget in
     * the widget tree has not been touched, then current widget is
     * not drawn(). On the contrary, if refresh() method is called on
     * some of its parent, whatever the parent has been touched or
     * not, this will be (re)drawn.
     *
     * \see See draw() and refresh() methods.
     */
    inline void touch() {
      _need_update = true;
    }

    /**
     * Actions to perform on arduino `loop()` function.
     *
     * \see A callback function can be set using onLoop() method.
     *
     * \param recurse If the widget has a child and if recurse is
     * true, then the loop() method is applied on the child (true by
     * default).
     */
    void loop(bool recurse = true);

  };

}

#endif
// Local Variables:
// mode: c++
// End:
