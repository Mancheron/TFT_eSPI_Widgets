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

#include "widget.h"

using namespace TFT_eSPI_Widgets;

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
  _default_graph_props(),
  _focus_graph_props(),
  _need_update(false),
  _event_handler_cb(NULL),
  _loop_cb(NULL),
  _focus_cb(NULL),
  _unfocus_cb(NULL)
{}

Widget::Widget(Widget &parent, const Area &area):
  _root(parent._root),
  _parent(parent),
  _child(NULL),
  _area(),
  _default_graph_props(parent._default_graph_props),
  _focus_graph_props(parent._focus_graph_props),
  _need_update(false),
  _event_handler_cb(NULL),
  _loop_cb(NULL),
  _focus_cb(NULL),
  _unfocus_cb(NULL)
{
  setArea(area);
  _parent.removeChild();
  _parent._child = this;
}

Widget::~Widget() {
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

Area Widget::getArea() const {
  Area area = _area;
  if (!isRoot()) {
    area.x -= _parent._area.x;
    area.y -= _parent._area.y;
  }
  return area;
}

void Widget::setArea(const Area &area) {
  if (isRoot()) {
    if (area.isEmpty()) {
      TFT_eSPI &tft = getTFT();
      _area.width = tft.width();
      _area.height = tft.height();
      _area.x = 0;
      _area.y = 0;
    } else {
      _area = area;
    }
  } else {
    if (area.isEmpty()) {
      uint8_t b = max(_default_graph_props.getBorderSize(), _focus_graph_props.getBorderSize());
      _area = _parent._area;
      if (_area.width > 2 * b) {
        _area.width -= 2 * b;
      } else {
        _area.width = 0;
      }
      if (_area.height > 2 * b) {
        _area.height -= 2 * b;
      } else {
        _area.height = 0;
      }
      _area.x += b;
      _area.y += b;
    } else {
      _area = area;
      _area.x += _parent._area.x;
      _area.y += _parent._area.y;
    }
  }
}

void Widget::focus() {
  if (_focus_cb) {
    _focus_cb(*this);
  }
  _setFocus(*this);
  touch();
}

void Widget::unfocus() {
  if (_unfocus_cb) {
    _unfocus_cb(*this);
  }
  _unsetFocus(*this);
  touch();
}

void Widget::handleEvent(Event event) {
  if (hasFocus()) {
    bool raise_event = (!_event_handler_cb or _event_handler_cb(*this, event));
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
  uint8_t border_size = props.getBorderSize();
  if (border_size) {
    tft.frameViewport(props.getBorderColor(), props.getBorderSize());
    tft.setViewport(_area.x + border_size,
                    _area.y + border_size,
                    _area.width - 2 * border_size,
                    _area.height - 2 * border_size);
  }
  tft.setTextSize(props.getFontSize());
  tft.setTextColor(props.getFontColor());
  yield();
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
  draw();
  if (_child) {
    _child->refresh();
  }
  yield();
}

void Widget::loop(bool recurse) {
  if (_loop_cb) {
    _loop_cb(*this);
    yield();
  }
  _loop();
  yield();
  if (recurse and _child) {
    _child->loop(recurse);
  }
}
