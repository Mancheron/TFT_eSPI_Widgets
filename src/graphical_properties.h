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

#ifndef __GRAPHICAL_PROPERTIES_H__
#define __GRAPHICAL_PROPERTIES_H__

#include <Arduino.h>
#include <TFT_eSPI.h>

namespace TFT_eSPI_Widgets {

  /**
   * Basic graphical properties definition.
   */
  class GraphicalProperties {

  private:

    uint16_t _background_color;
    uint16_t _border_color;
    uint16_t _font_color;
    uint8_t _border_size;
    uint8_t _font_size;

  public:

    /**
     * An default graphical properties that can acts as a reference
     * value.
     */
    static const GraphicalProperties default_values;

    /**
     * Create graphical properties.
     *
     * \note The color code are using a 16 bit representation, with
     * the first 5 bits to encode the red component value, the next 6
     * bits to encode the green component value and 5 last bits to
     * encode the blue component value. One can use the
     * TFT_eSPI::color565() method to convert a 24 bits encoded color
     * to a 16 bits encoded one.
     *
     * \param background_color The color to use to fill the background
     * of some widget area.
     *
     * \param border_color The color to use to draw the border of some
     * widget area (see also border_size parameter).
     *
     * \param font_color The color to use to draw strings on some
     * widget.
     *
     * \param border_size The line width of the border to draw (not
     * drawn if border_size is set to 0).
     *
     * \param font_size The font size (scale factor) to use to draw
     * strings on some widgets that have text inside.
     */
    GraphicalProperties(uint16_t background_color = TFT_BLACK,
                        uint16_t border_color = TFT_BLACK,
                        uint16_t font_color = TFT_WHITE,
                        uint8_t border_size = 0,
                        uint8_t font_size = 2);

    /**
     * Get the background color of the widget.
     *
     * \return Return the background color using a 16 bits encoding
     * (see the note in the constructor documentation).
     */
    inline uint16_t getBackgroundColor() const {
      return _background_color;
    }

    /**
     * Set the background color of the widget.
     *
     * \param color The color to use to fill the background of some
     * widget area (see the note in the constructor documentation).
     */
    inline void setBackgroundColor(uint16_t color) {
      _background_color = color;
    }

    /**
     * Get the border color of the widget.
     *
     * \return Return the border color using a 16 bits encoding
     * (see the note in the constructor documentation).
     */
    inline uint16_t getBorderColor() const {
      return _border_color;
    }

    /**
     * Set the border color of the widget.
     *
     * \param color The color to use to draw the border of some widget
     * area (see the note in the constructor documentation and the
     * setBorderSize() method).
     */
    inline void setBorderColor(uint16_t color) {
      _border_color = color;
    }

    /**
     * Get the border size of the widget.
     *
     * \return Return the line width of the border to draw (not drawn
     * if border_size is set to 0).
     */
    inline uint8_t getBorderSize() const {
      return _border_size;
    }

    /**
     * Set the border size of the widget.
     *
     * \param size The line width of the border to draw (not drawn if
     * border_size is set to 0).
     */
    inline void setBorderSize(uint8_t size) {
      _border_size = size;
    }

    /**
     * Get the font color of the widget.
     *
     * \return Return the font color using a 16 bits encoding
     * (see the note in the constructor documentation).
     */
    inline uint16_t getFontColor() const {
      return _font_color;
    }

    /**
     * Set the font color of the widget.
     *
     * \param color The color to use to draw strings on some widget
     * (see the note in the constructor documentation).
     */
    inline void setFontColor(uint16_t color) {
      _font_color = color;
    }

    /**
     * Get the font size of the widget.
     *
     * \return Return the font size used to draw strings on some
     * widgets that have text inside.
     */
    inline uint8_t getFontSize() const {
      return _font_size;
    }

    /**
     * Set the font size of the widget.
     *
     * \param size The font size (scale factor) to use to draw strings
     * on some widgets that have text inside.
     */
    inline void setFontSize(uint8_t size) {
      _font_size = size;
    }

  };

}

#endif
// Local Variables:
// mode: c++
// End:
