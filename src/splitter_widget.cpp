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

#include "splitter_widget.h"

using namespace TFT_eSPI_Widgets;

const size_t SplitterWidget::NOT_FOUND = -1;

/////////////////////////////////////////
// SplitterWidget::SplitterChildWidget //
/////////////////////////////////////////

SplitterWidget::SplitterChildWidget::SplitterChildWidget(SplitterWidget &parent,
                                                         Widget *child,
                                                         uint8_t weight):
  Widget(parent, Area::reference_value),
  _weight(0)
{
  Widget::setAcceptFocus(false);
  _child = child;
  setWeight(weight);
  _default_graph_props.setBorderSize(0);
  _focus_graph_props.setBorderSize(1);
  if (child) {
    // Hack to access the _parent protected member of the Widget base class.
    child->*(&SplitterChildWidget::_parent) = this;
  }
}

void SplitterWidget::SplitterChildWidget::setAcceptFocus(bool status) {
  if (status != getAcceptFocus()) {
    GraphicalProperties props1 = getDefaultGraphicalProperties();
    GraphicalProperties props2 = getFocusGraphicalProperties();
    setDefaultGraphicalProperties(props2);
    setFocusGraphicalProperties(props1);
    Widget::setAcceptFocus(status);
    touch();
  }
}

////////////////////////////////////
// SplitterWidget::const_iterator //
////////////////////////////////////

SplitterWidget::const_iterator::const_iterator(SplitterWidget::const_iterator::pointer const *ptr):
  _ptr(ptr)
{}

SplitterWidget::const_iterator& SplitterWidget::const_iterator::operator++() {
  if (_ptr and *_ptr) {
    const SplitterWidget &splitter = (*_ptr)->getParent().as<SplitterWidget>();
    if (++_ptr >= splitter._children + splitter.size()) {
      _ptr = NULL;
    }
  }
  return *this;
}

SplitterWidget::const_iterator SplitterWidget::const_iterator::operator++(int) {
  const_iterator tmp(*this);
  operator++();
  return tmp;
}

SplitterWidget::const_iterator& SplitterWidget::const_iterator::operator--() {
  if (_ptr and *_ptr) {
    const SplitterWidget &splitter = (*_ptr)->getParent().as<SplitterWidget>();
    if (--_ptr < splitter._children) {
      _ptr = NULL;
    }
  }
  return *this;
}

SplitterWidget::const_iterator SplitterWidget::const_iterator::operator--(int) {
  const_iterator tmp(*this);
  operator--();
  return tmp;
}

SplitterWidget::const_iterator::difference_type SplitterWidget::const_iterator::operator-(const const_iterator it) const {
  ptrdiff_t v = 0;
  const SplitterWidget &splitter = (*_ptr)->getParent().as<SplitterWidget>();
  pointer const *first = splitter._children;
  pointer const *second = first + splitter._number_of_children;
  if (_ptr) {
    first = _ptr;
  } else {
    first = second;
  }
  if (it._ptr) {
    second = it._ptr;
  }
  return first - second;
}

SplitterWidget::const_iterator::difference_type SplitterWidget::const_iterator::rank() const {
  if (!_ptr) return -1;
  const SplitterWidget &splitter = (*_ptr)->getParent().as<SplitterWidget>();
  return operator-(const_iterator(splitter._children));
}

//////////////////////////////
// SplitterWidget::iterator //
//////////////////////////////

SplitterWidget::iterator::iterator(SplitterWidget::iterator::pointer *ptr):
  _ptr(ptr)
{}

SplitterWidget::iterator& SplitterWidget::iterator::operator++() {
  if (_ptr and *_ptr) {
    const SplitterWidget &splitter = (*_ptr)->getParent().as<SplitterWidget>();
    if (++_ptr >= splitter._children + splitter.size()) {
      _ptr = NULL;
    }
  }
  return *this;
}

SplitterWidget::iterator SplitterWidget::iterator::operator++(int) {
  iterator tmp(*this);
  operator++();
  return tmp;
}

SplitterWidget::iterator& SplitterWidget::iterator::operator--() {
  if (_ptr and *_ptr) {
    const SplitterWidget &splitter = (*_ptr)->getParent().as<SplitterWidget>();
    if (--_ptr < splitter._children) {
      _ptr = NULL;
    }
  }
  return *this;
}

SplitterWidget::iterator SplitterWidget::iterator::operator--(int) {
  iterator tmp(*this);
  operator--();
  return tmp;
}

SplitterWidget::iterator::difference_type SplitterWidget::iterator::operator-(const iterator it) const {
  ptrdiff_t v = 0;
  const SplitterWidget &splitter = (*_ptr)->getParent().as<SplitterWidget>();
  pointer *first = splitter._children;
  pointer *second = first + splitter._number_of_children;
  if (_ptr) {
    first = _ptr;
  } else {
    first = second;
  }
  if (it._ptr) {
    second = it._ptr;
  }
  return first - second;
}

SplitterWidget::iterator::difference_type SplitterWidget::iterator::rank() const {
  if (!_ptr) return -1;
  const SplitterWidget &splitter = (*_ptr)->getParent().as<SplitterWidget>();
  return operator-(iterator(splitter._children));
}

////////////////////
// splitterWidget //
////////////////////

SplitterWidget::SplitterWidget(Widget &parent,
                               Orientation orientation,
                               size_t reserve,
                               const Area &area):
  Widget(parent, area),
  _children(NULL),
  _number_of_children(0),
  _children_reserved_size(0),
  _orientation(orientation),
  _weights_sum(0),
  _current_child(end()),
  _layout(FIT),
  _need_layout(false),
  _state(true)
{
  this->reserve(reserve);
}

SplitterWidget::~SplitterWidget() {
  clear();
  shrink_to_fit();
}

void SplitterWidget::_applyLayout() {
  if (!_need_layout) return;

  if (_layout == FIT) {
    fit(true, true);
  } else if (_layout == SHRINK) {
    shrink(true, true);
  }
  _updateCurrentChild();
  _need_layout = false;
  touch();
}

void SplitterWidget::_updateCurrentChild(SplitterWidget::iterator from,
                                         SplitterWidget::iterator not_found,
                                         bool ascending_order) {
  if (from == end()) {
    from = _current_child != end() ? _current_child : begin();
  }

  if ((from != end()) and !from->getChild().getAcceptFocus()) {
    if (ascending_order) {
      while ((++from != end()) and !from->getChild().getAcceptFocus());
    } else {
      while ((--from != end()) and !from->getChild().getAcceptFocus());
    }
  }
  if (from == end()) {
    from = not_found;
  }

  if (from != _current_child) {
    if (_current_child != end()) {
      _current_child->setAcceptFocus(false);
    }
    _current_child = from;
    if (_current_child != end()) {
      if (hasFocus()) {
        _child = &(_current_child->getChild());
        _current_child->setAcceptFocus(true);
      } else {
        _child = NULL;
      }
    } else {
      _child = NULL;
    }
    touch();
  }
}

void SplitterWidget::_fit(bool recurse, bool check_for_update) {
  uint16_t current_weight = 0;
  float hscale = 1, vscale = 1;
  int32_t xshift = 0, yshift = 0;
  Area area = getInnerArea(true);
  for (iterator it = begin(); it != end(); ++it) {
    if (it->getWeight()) {
      if (_orientation == HORIZONTAL) {
        hscale = float(it->getWeight()) / _weights_sum;
      } else {
        vscale = float(it->getWeight()) / _weights_sum;
      }
      Area new_area = Area(area.width * hscale,
                           area.height * vscale,
                           area.x + xshift,
                           area.y + yshift);
      it->setArea(new_area,
                  true /* absolute area */,
                  true /* touch on area change */);
      if (recurse) {
        it->getChild().fit(true, check_for_update);
      }
      current_weight += it->getWeight();
      if (_orientation == HORIZONTAL) {
        xshift += new_area.width;
      } else {
        yshift += new_area.height;
      }
    }
  }
}

void SplitterWidget::_shrink(bool recurse, bool check_for_update) {
  _area = Area(0, 0, _area.x, _area.y);
  for (iterator it = begin(); it != end(); ++it) {
    if (it->getWeight()) {
      it->shrink(0, 0, recurse, false);
      Area child_area = it->getArea();
      if (_orientation == HORIZONTAL) {
        _area.width += child_area.width;
        if (_area.height < child_area.height) {
          _area.height = child_area.height;
        }
      } else {
        if (_area.width < child_area.width) {
          _area.width = child_area.width;
        }
        _area.height += child_area.height;
      }
    }
  }
  // Centering shrunken children
  for (iterator it = begin(); it != end(); ++it) {
    if (it->getWeight()) {
      Area child_area = it->getArea();
      if (_orientation == HORIZONTAL) {
        child_area.height = _area.height;
      } else {
        child_area.width = _area.width;
      }
      it->setArea(child_area);
      it->getChild().setPosition(50, 50, check_for_update);
    }
  }
}

void SplitterWidget::_handleEvent(Event event) {
  if (_current_child != end()) {
    iterator from = _current_child;
    switch (event) {
    case SINGLE_LEFT_CLICK:
      _updateCurrentChild(--from, _current_child, false);
      break;
    case SINGLE_RIGHT_CLICK:
      _updateCurrentChild(++from, _current_child, true);
      break;
    }
  }
}

void SplitterWidget::_focus() {
  if (_current_child != end()) {
    _child = &(_current_child->getChild());
    _current_child->setAcceptFocus(true);
  }
}

void SplitterWidget::_unfocus() {
  if (_current_child != end()) {
    _child = NULL;
    _current_child->setAcceptFocus(false);
  }
}

void SplitterWidget::_loop(bool recurse) {
  _applyLayout();
  if (recurse) {
    for (iterator it = begin(); it != end(); ++it) {
      it->loop(true);
    }
  }
}

void SplitterWidget::_draw() {
  _applyLayout();
  for (iterator it = begin(); it != end(); ++it) {
    it->touch();
  }
}

void SplitterWidget::_refresh() {
  _applyLayout();
  for (iterator it = begin(); it != end(); ++it) {
    it->refresh();
  }
}

void SplitterWidget::_print(const String &prefix, Print &printer) const {
  printer.printf("(%s SPLITTER)", getOrientation() == HORIZONTAL ? "HORIZONTAL" : "VERTICAL");
  if (!empty()) {
    printer.println(":");
  } else {
    printer.println("");
  }
  for (const_iterator it = cbegin(); it != cend(); ++it) {
    String str = "  " + prefix;
    String str2 = str;
    str2.replace("-", " ");
    printer.printf("%s# Widget %lu is wrapped by SplitterChildWidget %lu\n", str2.c_str(), it->getChild().id, it->id);
    if (it == _current_child) {
      printer.printf("%s# ==> this is the current child of this splitter <==\n", str2.c_str());
    }
    it->getChild().print(str, printer);
  }
}

void SplitterWidget::setChild(Widget &w, uint8_t weight) {
  if (_state) {
    // Check if there is enough room to append the given widget to the
    // children
    if (_number_of_children >= _children_reserved_size) {
      // Oups. It is needed to extend the current array of children.
      reserve(2 * max<size_t>(1, _number_of_children));
    }
    _state = false;
    _children[_number_of_children++] = new SplitterChildWidget(*this, &w, weight);
    _state = true;
  }
  _need_layout = true;
}

size_t SplitterWidget::indexOf(const Widget &w) const {
  size_t i = 0;
  size_t p = NOT_FOUND;
  while ((p == NOT_FOUND) and (i < _number_of_children)) {
    if (&(_children[i]->getChild()) == &w) {
      p = i;
    }
    ++i;
  }
  return p;
}

void SplitterWidget::erase(size_t i) {
  delete _children[i];
  while (++i < _number_of_children) {
    _children[i - 1] = _children[i];
  }
  _children[--_number_of_children] = NULL;
  _need_layout = true;
}

void SplitterWidget::swap(size_t i, size_t j) {
  iterator it1(&(_children[i]));
  iterator it2(&(_children[j]));
  swap(it1, it2);
}

void SplitterWidget::swap(SplitterWidget::iterator &it1, SplitterWidget::iterator &it2) {
  if (_current_child == it1) {
    _current_child = it2;
  } else if (_current_child == it2) {
    _current_child = it1;
  }
  SplitterChildWidget *w1 = &(*it1);
  SplitterChildWidget *w2 = &(*it1);
  _children[it1.rank()] = w2;
  _children[it2.rank()] = w1;
  _need_layout = true;
}

void SplitterWidget::reserve(size_t n) {
  bool need_reallocation = false;
  if (n > _number_of_children) {
    if (n != _children_reserved_size) {
      need_reallocation = true;
    }
  } else {
    if (_number_of_children < _children_reserved_size) {
      need_reallocation = true;
      n = _number_of_children;
    }
  }
  if (need_reallocation) {
    SplitterChildWidget **new_children = NULL;
    if (n) {
      new_children = new SplitterChildWidget*[n];
      for (size_t i = 0; i < _number_of_children; ++i) {
        new_children[i] = _children[i];
      }
    }
    if (_children) {
      delete [] _children;
    }
    _children = new_children;
    _children_reserved_size = n;
  }
}

void SplitterWidget::clear() {
  iterator it = begin();
  _current_child = end();
  _child = NULL;
  while (it != end()) {
    it = erase(it);
  }
}
