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

#ifndef __DIMENSIONS_H__
#define __DIMENSIONS_H__

#include <Arduino.h>

namespace TFT_eSPI_Widgets {

  /**
   * Dimensions on the screen.
   *
   * Defines a rectangular area of the given width and height.
   */
  struct Dimensions {

    /**
     * The dimension width.
     */
    uint16_t width;

    /**
     * The dimension height.
     */
    uint16_t height;

    /**
     * The empty dimension
     */
    static const Dimensions empty;

    /**
     * Define new dimensions.
     *
     * \param w The width.
     *
     * \param h The height.
     */
    Dimensions(uint16_t w, uint16_t h);

    /**
     * Compare given dimensions to the current ones to know if they
     * have the same width and the same height.
     *
     * \param dim The dimensions to compare to current ones (current
     * dimensions are the left operand and given dimensions are the
     * right operand of comparison operator).
     *
     * \return The comparison succeed if both dimensions define
     * exactly the same area.
     */
    inline bool operator==(const Dimensions &dim) const {
      return ((width == dim.width) and (height == dim.height));
    }

    /**
     * Compare given dimensions to the current ones to know if they
     * have different width or different height.
     *
     * \param dim The dimensions to compare to current ones (current
     * dimensions are the left operand and given dimensions are the
     * right operand of comparison operator).
     *
     * \return The comparison succeed if both dimensions define
     * different area.
     */
    inline bool operator!=(const Dimensions &dim) const {
      return !operator==(dim);
    }

    /**
     * Apply a scale factor on the current dimensions.
     *
     * \param factor The multiplicative factor to apply to both width
     * and height of the current dimensions.
     *
     * \return The current operator returns the current updated
     * dimensions.
     */
    Dimensions &operator*=(float factor);

    /**
     * Create new dimensions which is the current one scaled by the
     * given factor.
     *
     * \param factor The multiplicative factor to apply to both width
     * and height of the current dimensions.
     *
     * \return The current operator returns the current updated
     * dimensions.
     */
    Dimensions operator*(float factor) const;

    /**
     * Return true if and only if the dimension is empty.
     *
     * \return The method returns true if the area has a 0 width or 0
     * height.
     */
    inline bool isEmpty() const {
      return !width or !height;
    }

    /**
     * Get a string representation of current dimension.
     *
     * \return This method returns a string representation of the
     * current dimension.
     */
    inline String toString() const {
      return String(width) + "x" + height;
    }

  };

}

#endif
// Local Variables:
// mode: c++
// End:
