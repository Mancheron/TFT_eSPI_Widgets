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

#include "widget.h"

using namespace TFT_eSPI_Widgets;

size_t Widget::_counter = 0;

#define TYPE2CSTR_CASE(t) case t: return #t

const char *Widget::getTypeString(Type t) {
  switch (t) {
    TYPE2CSTR_CASE(CANVAS);
    TYPE2CSTR_CASE(GENERIC);
    TYPE2CSTR_CASE(IMAGE);
    TYPE2CSTR_CASE(INT_ENTRY);
    TYPE2CSTR_CASE(FLOAT_ENTRY);
    TYPE2CSTR_CASE(STRING_ENTRY);
    TYPE2CSTR_CASE(MESSAGE);
    TYPE2CSTR_CASE(CUSTOM);
  }
}

Widget::Widget():
  _root(*this),
  _parent(*this),
  _child(NULL),
  _area(),
  _accept_focus(true),
  _default_graph_props(),
  _focus_graph_props(),
  _need_update(false),
  _event_handler_cb(NULL),
  _draw_cb(NULL),
  _refresh_cb(NULL),
  _loop_cb(NULL),
  _focus_cb(NULL),
  _unfocus_cb(NULL),
  id(++_counter)
{}

Widget::Widget(Widget &parent, const Area &area):
  _root(parent._root),
  _parent(parent),
  _child(NULL),
  _area(),
  _accept_focus(parent._accept_focus),
  _default_graph_props(parent._default_graph_props),
  _focus_graph_props(parent._focus_graph_props),
  _need_update(false),
  _event_handler_cb(NULL),
  _draw_cb(NULL),
  _refresh_cb(NULL),
  _loop_cb(NULL),
  _focus_cb(NULL),
  _unfocus_cb(NULL),
  id(++_counter)
{
  setArea(area);
  _parent.removeChild();
  _parent._child = this;
}

Widget::~Widget() {
  unfocus();
  removeChild();
  if (!isRoot()) {
    _parent._child = NULL;
    yield();
  }
}

void Widget::removeChild() {
  if (_child) {
    delete _child;
    _child = NULL;
    yield();
  }
}

Area Widget::getArea(bool absolute) const {
  Area area = _area;
  if (!isRoot()) {
    if (!absolute) {
      area.x -= _parent._area.x;
      area.y -= _parent._area.y;
    }
  }
  return area;
}

Area Widget::getInnerArea(bool absolute) const {
  Area area = getArea(absolute);
  uint8_t border_size = max(getFocusGraphicalProperties().getBorderSize(),
                            getDefaultGraphicalProperties().getBorderSize());
  if (area.width > 2 * border_size) {
    area.width -= 2 * border_size;
  } else {
    area.width = 0;
  }
  if (area.height > 2 * border_size) {
    area.height -= 2 * border_size;
  } else {
    area.height = 0;
  }
  area.x += border_size;
  area.y += border_size;
  return area;
}

void Widget::setArea(const Area &area, bool absolute, bool check_for_update) {
  Area orig_area = _area;
  if (area.isEmpty()) {
    fit(false, false);
  } else {
    if (isRoot()) {
      _area = area;
    } else {
      _area = area;
      if (!absolute) {
        _area.x += _parent._area.x;
        _area.y += _parent._area.y;
      }
    }
  }
  if (check_for_update) {
    touchOnAreaChanges(orig_area);
  }
}

void Widget::fit(bool recurse, bool check_for_update) {
  Area orig_area = _area;
  if (isRoot()) {
    _area = getScreenArea();
  } else {
    _area = _parent.getInnerArea(true);
  }
  _fit(recurse, check_for_update);
  if (recurse and _child) {
    _child->fit(true, check_for_update);
  }
  if (check_for_update) {
    touchOnAreaChanges(orig_area);
  }
}

void Widget::shrink(uint8_t horizontal, uint8_t vertical, bool recurse, bool check_for_update) {
  Area orig_area = _area;
  _area.width = 0;
  _area.height = 0;
  if (_child) {
    if (recurse) {
      _child->shrink(horizontal, vertical, true, check_for_update);
    }
    _area = _child->getArea(true);
  }
  TFT_eSPI &tft = getTFT();
  tft.setTextSize(getGraphicalProperties().getFontSize());
  _shrink(recurse, check_for_update);
  uint8_t border_size = max(getFocusGraphicalProperties().getBorderSize(),
                            getDefaultGraphicalProperties().getBorderSize());
  _area.width += 2 * border_size;
  _area.height += 2 * border_size;
  _area.x -= border_size;
  _area.y -= border_size;
  setPosition(horizontal, vertical, false);
  if (check_for_update) {
    touchOnAreaChanges(orig_area);
  }
}

void Widget::setPosition(uint8_t horizontal, uint8_t vertical, bool check_for_update) {
  Area area, orig_area = _area;
  if (isRoot()) {
    area = getScreenArea();
  } else {
    area = _parent.getInnerArea(true);
  }
  if (horizontal != -1) {
    horizontal = constrain(horizontal, 0, 100);
    // We don't care about the current widget fits horizontally into
    // its parent/screen since the computation is the same in both
    // cases.
    _area.x = area.x + horizontal * (area.width - _area.width) / 100;
  }
  if (vertical != -1) {
    vertical = constrain(vertical, 0, 100);
    // We don't care about the current widget fits vertically into its
    // parent/screen since the computation is the same in both cases.
    _area.y = area.y + vertical * (area.height - _area.height) / 100;
  }
  if (check_for_update) {
    touchOnAreaChanges(orig_area);
  }
}

void Widget::touchOnAreaChanges(const Area &orig_area) {
  if (orig_area != _area) {
    // The widget area has changed, we need to redraw it.
    touch();
    if (!_area.contains(orig_area)) {
      // The new widget area doesn't includes its old area.
      // It is better to redraw the canvas.
      _parent.touch();
    }
  }
}

void Widget::focus() {
  if (_accept_focus) {
    if (_focus_cb) {
      _focus_cb(*this);
    }
    _focus(); // Specific widget subclass focus action (if any).
    _setFocus(*this); // Root of the widget tree can now focus this widget.
    touch();
  } else {
    if (hasChild()) {
      getChild().focus();
    }
  }
}

void Widget::unfocus() {
  if (_accept_focus) {
    if (_unfocus_cb) {
      _unfocus_cb(*this);
    }
    _unfocus(); // Specific widget subclass unfocus action (if any).
    _unsetFocus(*this); // Root of the widget tree can now unfocus this widget.
    touch();
  } else {
    if (!isRoot()) {
      getParent().unfocus();
    }
  }
}

void Widget::handleEvent(Event event) {
  if (hasFocus()) {
    bool raise_event = !(_event_handler_cb and _event_handler_cb(*this, event));
    switch (event) {
    case TRIPLE_RIGHT_CLICK:
      if (_child) {
        _child->focus();
      }
      break;
    case TRIPLE_LEFT_CLICK:
      unfocus();
      break;
    default:
      if (raise_event) {
        _handleEvent(event);
      }
    }
  } else {
    if (isRoot()) {
      _handleEvent(event);
    }
  }
}

void Widget::draw() {
  if (!_need_update) return;
  const GraphicalProperties &props = getGraphicalProperties();
  TFT_eSPI &tft = getTFT();
  tft.setViewport(_area.x, _area.y, _area.width, _area.height);
  tft.fillScreen(props.getBackgroundColor());
  if (props.getBorderSize()) {
    tft.frameViewport(props.getBorderColor(), props.getBorderSize());
  }
  Area inner_area = getInnerArea(true);
  tft.setViewport(inner_area.x,
                  inner_area.y,
                  inner_area.width,
                  inner_area.height);
  tft.setTextSize(props.getFontSize());
  tft.setTextColor(props.getFontColor());
  yield();
  if (_draw_cb) {
    _draw_cb(*this);
    yield();
  }
  _draw();
  yield();
  tft.resetViewport();
  if (_child) {
    _child->touch();
  }
  _need_update = false;
  yield();
}

void Widget::refresh() {
  if (_refresh_cb) {
    _refresh_cb(*this);
    yield();
  }
  draw();
  if (_child) {
    _child->refresh();
  }
  _refresh();
  yield();
}

void Widget::loop(bool recurse) {
  if (_loop_cb) {
    _loop_cb(*this);
    yield();
  }
  _loop(recurse);
  yield();
  if (recurse and _child) {
    _child->loop(recurse);
  }
}
