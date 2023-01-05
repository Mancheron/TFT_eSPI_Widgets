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

#ifndef __SPLITTER_WIDGET_H__
#define __SPLITTER_WIDGET_H__

#include "widget.h"

namespace TFT_eSPI_Widgets {

  /**
   * A splitter widget.
   *
   * By conception, widgets may have at most one child widget. A
   * splitter widget is mostly a wrapper to handle several children
   * widgets.
   */
  class SplitterWidget: public Widget {

  public:

    /**
     * Each child widget of some splitter is contained into a generic
     * widget and also has a size weight.
     */
    class SplitterChildWidget: public Widget {

    protected:

      /**
       * The size weight of this widget.
       */
      uint8_t _weight;

      /**
       * Action to perform when this widget get the focus.
       *
       * On focus, transmit the focus to its child (which must exists).
       *
       * \return Returns nothing but doxygen is buggy with inline
       * virtual void signature.
       */
      inline virtual void _focus() {
        Serial.printf("Current Splitter Child Widget %lu is transmitting the focus to its child %lu\n", id, getChild().id);
        setAcceptFocus(false);
        getChild().focus();
      }

    public:

      SplitterChildWidget(SplitterWidget &parent,
                          Widget *child = NULL,
                          uint8_t weight = 1);

      /**
       * Return the widget type.
       *
       * \return This method returns the GENERIC widget type.
       */
      inline virtual Type getType() const {
        return SPLITTER_CHILD;
      }

      /**
       * Get the weight of this splitter child widget.
       *
       * \return Returns the weight of this splitter child widget.
       */
      inline uint8_t getWeight() const {
        return _weight;
      }

      /**
       * Set a new weight for this splitter child widget.
       *
       * \param weight The new weight for this splitter child widget.
       */
      inline void setWeight(uint8_t weight) {
        getParent().as<SplitterWidget>()._weights_sum += weight - _weight;
        _weight = weight;
      }

      /**
       * Set the accept focus status.
       *
       * \remark This overloaded method also set a pre-focus border
       * when this accepts the focus.
       *
       * \param status When set to true, this widget can be focused
       * whereas it can't be anymore if set to false.
       */
      virtual void setAcceptFocus(bool status);

    };

    /**
     * The splitter orientation type.
     */
    enum Orientation {
                      HORIZONTAL, /**< Horizontal split. */
                      VERTICAL,   /**< Vertical split. */
    };

    /**
     * The NOT FOUND constant.
     *
     * \see This is typically used in the indexOf() method.
     */
    static const size_t NOT_FOUND;

    /**
     * A splitter widget random access iterator on its immutable
     * children.
     */
    class const_iterator: public std::iterator<std::random_access_iterator_tag, const SplitterChildWidget> {

      friend class SplitterWidget;

    private:

      /**
       * The immutable splitter child widget address.
       */
      pointer const *_ptr;

    public:

      /**
       * Builds a read-only iterator over the given splitter child
       * widget.
       *
       * \param ptr The address of the immutable splitter child widget
       * pointed by this iterator.
       */
      const_iterator(pointer const *ptr = NULL);

      /**
       * Make this read-only iterator pointing on the next sibling
       * immutable widget if available or pointing nowhere otherwise.
       *
       * \return Returns this read-only iterator after having been
       * incremented.
       */
      const_iterator& operator++();

      /**
       * Make this read-only iterator pointing on the next sibling
       * immutable widget if available or pointing nowhere otherwise.
       *
       * \return Returns a copy of this read-only iterator before
       * having been incremented.
       */
      const_iterator operator++(int);

      /**
       * Make this read-only iterator pointing on the previous sibling
       * immutable widget if exists or pointing nowhere otherwise.
       *
       * \return Returns this read-only iterator after having been
       * decremented.
       */
      const_iterator& operator--();

      /**
       * Make this read-only iterator pointing on the previous sibling
       * immutable widget.
       *
       * \return Returns a copy of this read-only iterator before
       * having been decremented.
       */
      const_iterator operator--(int);

      /**
       * Compare if this read-only iterator is equal to the given one.
       *
       * \param it The read-only iterator to compare to this one.
       *
       * \return Returns true if both read-only iterators are pointing
       * to the same immutable splitter child widget.
       */
      inline bool operator==(const const_iterator& it) const {
        return _ptr == it._ptr;
      }

      /**
       * Compare if this read-only iterator is different from the
       * given one.
       *
       * \param it The read-only iterator to compare to this one.
       *
       * \return Returns true if both read-only iterators are pointing
       * to different immutable splitter children widgets.
       */
      inline bool operator!=(const const_iterator& it) const {
        return !operator==(it);
      }

      /**
       * Dereference this read-only iterator.
       *
       * \return This return the immutable splitter child widget (not
       * the immutable widget attached to this).
       */
      inline reference operator*() const {
        return **_ptr;
      }

      /**
       * Arrow operator to dereference this iterator.
       *
       * \return This return the immutable splitter child widget
       * address (not the immutable widget attached to this).
       */
      inline pointer operator->() const {
        return *_ptr;
      }

      /**
       * Compute the difference between two read-only iterators.
       *
       * \param it The right part of the operand (the read-only
       * iterator to subtract from this read-only iterator).
       *
       * \return This return the rank difference between the current
       * read-only iterator (left operand) and the given read-only
       * iterator (right operand).
       */
      difference_type operator-(const const_iterator it) const;

      /**
       * Compute the rank position of the current read-only iterator.
       *
       * \return This return the rank of the iterator from the
       * beginning or -1 if iterator isn't referencing anything.
       */
      difference_type rank() const;

    };

    /**
     * A splitter widget random access iterator on its children.
     */
    class iterator: public std::iterator<std::random_access_iterator_tag, SplitterChildWidget> {

      friend class SplitterWidget;

    private:

      /**
       * The splitter child widget to point to.
       */
      pointer *_ptr;

    public:

      /**
       * Builds an iterator over the given splitter child widget.
       *
       * \param ptr The address of the splitter child widget pointed
       * by this iterator.
       */
      iterator(pointer *ptr = NULL);

      /**
       * Make this iterator pointing on the next sibling widget if
       * available or pointing nowhere otherwise.
       *
       * \return Returns this iterator after having been incremented.
       */
      iterator& operator++();

      /**
       * Make this iterator pointing on the next sibling widget if
       * available or pointing nowhere otherwise.
       *
       * \return Returns a copy of this iterator before having been
       * incremented.
       */
      iterator operator++(int);

      /**
       * Make this iterator pointing on the previous sibling widget if
       * exists or pointing nowhere otherwise.
       *
       * \return Returns this iterator after having been decremented.
       */
      iterator& operator--();

      /**
       * Make this iterator pointing on the previous sibling widget.
       *
       * \return Returns a copy of this iterator before having been
       * decremented.
       */
      iterator operator--(int);

      /**
       * Compare if this iterator is equal to the given one.
       *
       * \param it The iterator to compare to this one.
       *
       * \return Returns true if both iterators are pointing to the
       * same splitter child widget.
       */
      inline bool operator==(const iterator& it) const {
        return _ptr == it._ptr;
      }

      /**
       * Compare if this iterator is different from the given one.
       *
       * \param it The iterator to compare to this one.
       *
       * \return Returns true if both iterators are pointing to
       * different splitter children widgets.
       */
      inline bool operator!=(const iterator& it) const {
        return !operator==(it);
      }

      /**
       * Dereference this iterator.
       *
       * \return This return the splitter child widget (not the widget
       * attached to this).
       */
      inline reference operator*() {
        return **_ptr;
      }

      /**
       * Arrow operator to dereference this iterator.
       *
       * \return This return the splitter child widget address (not
       * the widget attached to this).
       */
      inline pointer operator->() {
        return *_ptr;
      }

      /**
       * Compute the difference between two iterators.
       *
       * \param it The right part of the operand (the to subtract from
       * this iterator).
       *
       * \return This return the rank difference between the current
       * iterator (left operand) and the given iterator (right
       * operand).
       */
      difference_type operator-(const iterator it) const;

      /**
       * Compute the rank position of the current iterator.
       *
       * \return This return the rank of the iterator from the
       * beginning or -1 if iterator isn't referencing anything.
       */
      difference_type rank() const;

      /**
       * Build a read-only iterator from this iterator.
       *
       * \return Returns a read-only iterator pointing on the same
       * splitter child widget.
       */
      inline operator const_iterator() const {
        return const_iterator(_ptr);
      }

    };

  protected:

    /**
     * The splitter widget children.
     */
    SplitterChildWidget **_children;

    /**
     * The splitter widget number of children.
     */
    size_t _number_of_children;

    /**
     * The splitter widget reserved space for children.
     */
    size_t _children_reserved_size;

    /**
     * The splitter orientation.
     */
    Orientation _orientation;

    /**
     * The sum of the children weight.
     */
    uint16_t _weights_sum;

    /**
     * The last child known to have the focus.
     */
    iterator _current_child;

    /**
     * An internal state needed to add a new sibling child.
     */
    bool _state;

    /**
     * The splitter layout.
     */
    enum {
          FITTED,   /**< The splitter children fit this splitter
                       according to their weight. */
          SHRINKED, /**< This splitter is shrinked to its children
                       size. */
    } _layout;

    /**
     * The splitter layout needs.
     */
    bool _need_layout;

    /**
     * Update the current child to the first that accepts being focused.
     *
     * \param from An iterator positionned at the starting sibling
     * child. If it doesn't reference any child (default), then use
     * the _current_child iterator (or the first child if there is no
     * current child).
     *
     * \param not_found The value to set for the current child
     * iterator if not found (default to end()).
     *
     * \param ascending_order Defines the searching direction. If
     * true, then the new current child is searched in ascending order
     * from the actual current child (left to right / top to bottom),
     * otherwise it searched in opposite order (right to left / bottom
     * to top).
     */
    void _updateCurrentChild(iterator from = iterator(),
                             iterator not_found = iterator(),
                             bool ascending_order = true);

    /**
     * Apply this splitter layout if needed.
     */
    void _applyLayout();

    /**
     * Fit the current widget area to the inner area of its parent.
     *
     * \remark This method might be overridden by any derived class
     * that have some custom size fitting strategy.
     *
     * \param recurse This is the recurse value passed to the fit()
     * method. If the widget has children and if recurse is true, then
     * the fit() method is applied on the children and all their
     * descendants. The children fitting is done according to their
     * weight and the splitter orientation. A zero weighted child
     * widget is ignored on fitting.
     *
     * \param check_for_update This is the check_for_update parameter
     * passed to the fit() method. When this parameter is true, then
     * automatically call the touchOnAreaChanges() method after
     * setting the area, else does nothing more.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _fit(bool recurse, bool check_for_update);

    /**
     * Shrink the current widget area to the smallest dimension that
     * allows to see its content.
     *
     * \param recurse This is the recurse value passed to the shrink()
     * method. If the widget has children and if recurse is true, then
     * the shrink() method is applied on the children and their
     * descendants (starting from the deeper descendants widgets)
     * before shrinking current widget. The weight of shrinked
     * children is simply ignored for shrinking current splitter,
     * except for children having a zero weight which are considered
     * as empty areas.
     *
     * \param check_for_update This is the check_for_update parameter
     * passed to the shrink() method. When this parameter is true,
     * then automatically call the touchOnAreaChanges() method after
     * setting the area, else does nothing more.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _shrink(bool recurse, bool check_for_update);

    /**
     * Action to perform when this widget is passed some event.
     *
     * Specific events this widget can handle are:
     *   - Simple left click => move the selection to the previous
     *     sibling widget (no effect if cursor is at the leftmost
     *     position).
     *   - Simple right click => move the selection to the next
     *     sibling widget (no effect if cursor is at the rightmost
     *     position).
     *   - Double right click => give the focus to the selected child.
     *
     * \param event The event to handle.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _handleEvent(Event event);

    /**
     * Action to perform when this widget get the focus.
     *
     * On focus, the default graphical properties of the child at the
     * _current_child position (set to the first if not already set)
     * is set to this widget focus graphical properties with a one
     * point line width border.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _focus();

    /**
     * Action to perform when this widget loose the focus.
     *
     * On unfocus, the default graphical properties of the child at
     * the _current_child position (set to the first if not already
     * set) is set to this widget default graphical properties with a
     * zero point line width border.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _unfocus();

    /**
     * Action to perform when the loop method is called on the current
     * widget.
     *
     * Call the loop() method on each child of the current splitter.
     *
     * \param recurse This is the recurse value passed to the loop()
     * method, which is forwarded to children loop() calls.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _loop(bool recurse);

    /**
     * Action to perform when the draw() method is called on the
     * current widget.
     *
     * This method is called after the viewport is set and drawn
     * according to the graphical properties. This draw the current
     * widget children.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _draw();

    /**
     * Action to perform when the refresh() method is called on the
     * current widget.
     *
     * This method is called at the end of the refresh(). This refresh
     * all the current widget children.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _refresh();

  public:

    /**
     * Creates a splitter widget attached to the given Widget.
     *
     * The widget graphical properties (background color, line color,
     * line width, font color, font size) are inherited from the
     * parent widget. This widget accepts the focus if and only of its
     * parent does too.
     *
     * \param parent The parent widget of the current one. Be aware
     * that if this parent already has a child widget, then this child
     * is automatically destroyed.
     *
     * \param orientation The splitter orientation (either HORIZONTAL
     * or VERTICAL) is used to define the children positions.
     *
     * \param reserve The splitter allocates room dynamically to store
     * its children miming the standard C++ vector behavior. If the
     * number of total children to be added is known (or pretty well
     * estimated), it is possible to reserve the specified room in
     * order to avoid reallocations.
     *
     * \param area The area used by the widget. If the area dimension
     * is empty, then use the area of its parent minus its maximal
     * border size according to its focus state. The top left anchor
     * of the area is relative to the top left corner of its parent.
     *
     * \remark There is no verification about the area to fit into the
     * parent area.
     */
    SplitterWidget(Widget &parent,
                   Orientation orientation = HORIZONTAL,
                   size_t reserve = 0,
                   const Area &area = Area::reference_value);

    /**
     * Creates a splitter widget attached to the given splitter widget.
     *
     * \remark Building a copy of any widget is prohibited by the
     * TFT_eSPI_Widgets library architecture. This is why the Widget
     * base class copy constructor is deleted. Thus, the problem is
     * that if we want to attach an *horizontal by default* splitter
     * to some existing splitter using the "normal" constructor, it is
     * needed to cast the parent splitter widget as a base
     * widget. Otherwise, the compiler interpret the construction as a
     * copy constructor. This is why we need to force using the
     * "normal" splitter constructor to avoid this issue.
     */
    inline SplitterWidget(SplitterWidget &parent):
      SplitterWidget(parent.as<Widget>()) {}

    /**
     * Destroy this widget and its descendants (if any).
     */
    virtual ~SplitterWidget();

    /**
     * Return this widget type (must be overridden by specialized
     * class)
     *
     * \return The concrete widget type is returned.
     */
    inline virtual Type getType() const {
      return SPLITTER;
    }

    /**
     * Set the given widget as the last child of the current widget.
     *
     * The given widget is added with unit weight.
     *
     * \remark Due to its internal representation, the removeChild()
     * method does nothing on this splitter widget.
     *
     * \param w The widget to append to the children.
     */
    virtual inline void setChild(Widget &w) {
      setChild(w, 1);
    }

    /**
     * Set the given widget as the last child of the current widget
     * using the given weight.
     *
     * This is an extended version of setChild() method to set some
     * given weight. A zero weight means to not take the child widget
     * into account for splitting current area, but also to not update
     * the child area on shrink/fit operations.
     *
     * \see A non zero weight has an incidence on fit() and shrink()
     * methods (see _fit() and _shrink()).
     *
     * \param w The widget to append to the children.
     *
     * \param weight The widget area weight in the split.
     */
    void setChild(Widget &w, uint8_t weight);

    /**
     * Returns the position of the widget in the layout.
     *
     * \param w The widget to locate in the layout.
     *
     * \return Returns the position of the given widget in the
     * splitter layout. The position starts from 0. If splitter is
     * horizontally orientated, it corresponds to the leftmost widget
     * and positions increase from left to right. If splitter is
     * vertically orientated, it corresponds to the upper widget and
     * positions increase from top to bottom. The special value
     * NOT_FOUND is returned if the given widget is not found in the
     * splitter layout.
     */
    size_t indexOf(const Widget &w) const;

    /**
     * Locate the given widget in the layout.
     *
     * \param w The widget to locate.
     *
     * \return This returns an iterator pointing on the given
     * SplitterChildWidget item of the children collection or the
     * end() iterator if widget is not found.
     */
    inline iterator find(const Widget &w) const {
      size_t p = indexOf(w);
      return (p == NOT_FOUND) ? iterator() : iterator(&(_children[p]));
    }

    /**
     * Locate the given widget in the layout.
     *
     * \param w The widget to locate.
     *
     * \return This returns a const_iterator pointing on the given
     * SplitterChildWidget item of the children collection or the
     * cend() const_iterator if widget is not found.
     */
    inline const_iterator cfind(const Widget &w) const {
      return (const_iterator) find(w);
    }

    /**
     * Return a reference on the child widget wrapper at the given
     * position.
     *
     * \param i The position of the wanted widget in the splitter
     * layout. The position starts from 0. If splitter is horizontally
     * orientated, it corresponds to the leftmost widget and positions
     * increase from left to right. If splitter is vertically
     * orientated, it corresponds to the upper widget and positions
     * increase from top to bottom. The special value NOT_FOUND is
     * returned if the given widget is not found in the splitter
     * layout.
     *
     * \remark No verification of the validity of the given position
     * is done. Thus it may lead to some error.
     */
    inline SplitterChildWidget &operator[](size_t i) {
      return *_children[i];
    }

    /**
     * Return a constant reference on the child widget wrapper at the
     * given position.
     *
     * \param i The position of the wanted widget in the splitter
     * layout. The position starts from 0. If splitter is horizontally
     * orientated, it corresponds to the leftmost widget and positions
     * increase from left to right. If splitter is vertically
     * orientated, it corresponds to the upper widget and positions
     * increase from top to bottom. The special value NOT_FOUND is
     * returned if the given widget is not found in the splitter
     * layout.
     *
     * \remark No verification of the validity of the given position
     * is done. Thus it may lead to some error.
     */
    inline const SplitterChildWidget &operator[](size_t i) const {
      return *_children[i];
    }

    /**
     * Return an iterator pointing to the first WidgetChild of the
     * current splitter widget children.
     *
     * \return Return the first iterator associated to the first
     * WidgetChild of the current splitter widget children.
     */
    inline iterator begin() {
      return iterator(_children);
    }

    /**
     * Return a const_iterator pointing to the first WidgetChild of
     * the current splitter widget children.
     *
     * \return Return the first const_iterator associated to the first
     * WidgetChild of the current splitter widget children.
     */
    inline const_iterator cbegin() const {
      return const_iterator(_children);
    }

    /**
     * Return an iterator pointing to the after the last WidgetChild
     * of the current splitter widget children.
     *
     * \return Return the iterator associated to the after the last
     * WidgetChild of the current splitter widget children.
     */
    inline iterator end() {
      return iterator();
    }

    /**
     * Return a const_iterator pointing to the after the last
     * WidgetChild of the current splitter widget children.
     *
     * \return Return the const_iterator associated to the after the
     * last WidgetChild of the current splitter widget children.
     */
    inline const_iterator cend() const {
      return const_iterator();
    }

    /**
     * Erase the widget located at the given position.
     *
     * \param i The position of the widget to remove.
     */
    void erase(size_t i);

    /**
     * Erase the widget located at the given position.
     *
     * \param it The position of the widget to remove.
     *
     * \return This returns the iterator following the removed
     * element. If it refers to the last element, then the end()
     * iterator is returned.
     */
    inline iterator erase(iterator it) {
      size_t i = it.rank();
      erase(i);
      return ((i == _number_of_children) ? iterator() : iterator(&(_children[i])));
    }

    /**
     * Swap the position of the widget children in the current
     * splitter.
     *
     * \param i The position of the first widget to swap.
     *
     * \param j The position of the second widget to swap.
     */
    void swap(size_t i, size_t j);

    /**
     * Swap the position of the widget children in the current
     * splitter.
     *
     * \param it1 The position of the first widget to swap.
     *
     * \param it2 The position of the second widget to swap.
     */
    void swap(iterator &it1, iterator &it2);

    /**
     * Reserve some space for future children widgets.
     *
     * \param n The size to reserve. If this size is smaller than the
     * actual number of children widgets, then it behaves as if
     * shrink_to_fit() was called (actually it is the way
     * shrink_to_fit() works). That means that in such case, the
     * reserved size is the minimal room to fit all the children. If
     * there is no child, then it clears the memory.
     */
    void reserve(size_t n);

    /**
     * This shrink the memory size to store children widgets to the
     * minimal size.
     *
     * \remark This method has nothing to do with the shrink() and
     * fit() methods. Its name comes from the standard c++ vector
     * definition (like any other methods of splitter widgets related
     * to the array handling).
     */
    inline void shrink_to_fit() {
      reserve(0);
    }

    /**
     * Get the layout orientation of current splitter.
     *
     * \return This returns either HORIZONTAL or VERTICAL.
     */
    inline Orientation getOrientation() const {
      return _orientation;
    }

    /*
     * Set the layout of splitter.
     *
     * \param orientation The layout orientation.
     */
    inline void setOrientation(Orientation orientation) {
      _orientation = orientation;
    }

    /**
     * Check whether the current slitter has any children.
     *
     * \return This is true if the current splitter widgets has no
     * child.
     */
    inline bool empty() const {
      return !_number_of_children;
    }

    /**
     * Get the number of children of the current slitter widget.
     *
     * \return This returns the number of children of the current
     * slitter widget.
     */
    inline size_t size() const {
      return _number_of_children;
    }

    /**
     * Get the current capacity of the current slitter widget.
     *
     * \return This returns the pre-reserved space for storing all
     * children of the current slitter widget.
     */
    inline size_t capacity() const {
      return _children_reserved_size;
    }

    /**
     * Removes all children from current widget.
     *
     * You may call shrink_to_fit() after clearing the splitter from
     * its children in order to clear the reserved memory.
     */
    void clear();

    void _print(const String &prefix, Print &printer) const;

  };

}

#endif
// Local Variables:
// mode: c++
// End:
