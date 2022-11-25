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

#ifndef __AREA_H__
#define __AREA_H__

#include <Arduino.h>
#include "coordinates.h"
#include "dimensions.h"

namespace TFT_eSPI_Widgets {

  /**
   * Area on the screen.
   *
   * Defines an anchored rectangular area on the Cartesion system.
   */
  struct Area: public Coordinates, Dimensions {

    /**
     * An empty area that acts as a reference value.
     */
    static const Area reference_value;

    /**
     * Define new area.
     *
     * \param w The width.
     *
     * \param h The height.
     *
     * \param x The leftmost position.
     *
     * \param y The upmost position.
     */
    Area(uint16_t w, uint16_t h, int32_t x, int32_t y);

    /**
     * Define new area.
     *
     * \param dim The dimensions.
     *
     * \param top_left The top left anchor.
     */
    Area(const Dimensions &dim = Dimensions::empty,
         const Coordinates &top_left = Coordinates::origin);

    /**
     * Compare given area to the current one to know if they have the
     * same dimensions and are anchored on the same position.
     *
     * \param area The area to compare to current ones (current area
     * is the left operand and given area is the right operand of
     * comparison operator).
     *
     * \return The comparison succeed if both areas define exactly the
     * same area on the Cartesian system.
     */
    inline bool operator==(const Area &area) const {
      return (this->Dimensions::operator==(area) and
              this->Coordinates::operator==(area));
    }

    /**
     * Compare given area to the current one to know if they have
     * different dimensions or are anchored on different positions.
     *
     * \param area The area to compare to current ones (current area
     * is the left operand and given area is the right operand of
     * comparison operator).
     *
     * \return The comparison succeed if both areas define different
     * areas on the Cartesian system.
     */
    inline bool operator!=(const Area &area) const {
      return !operator==(area);
    }

    /**
     * Check whether the given area and the current ones overlaps.
     *
     * \param area The area to check for overlap against current one.
     *
     * \return The method succeed if both areas intersect together on
     * the Cartesian coordinates system.
     */
    bool overlap(const Area &area) const;

    /**
     * Check whether the given area is included into the current one.
     *
     * \param area The area to check for inclusion in the current one.
     *
     * \return The method succeed if the given area is inclusion in
     * the current one.
     */
    bool contains(const Area &area) const;

    /**
     * Check whether the given coordinates is included into the
     * current area.
     *
     * \param coords The coordinates to check for inclusion in the
     * current area.
     *
     * \return The method succeed if the given coordinates is included
     * in the current area.
     */
    bool contains(const Coordinates &coords) const;

  };

}

#endif
// Local Variables:
// mode: c++
// End:
