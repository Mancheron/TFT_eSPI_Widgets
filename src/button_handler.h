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

#ifndef __BUTTON_HANDLER_H__
#define __BUTTON_HANDLER_H__

#include <Arduino.h>

namespace TFT_eSPI_Widgets {

  /**
   * A simple button handler.
   *
   * This is a basic class interface to capture button events in order
   * to provide the minimal functionnalities to work with widgets.
   *
   * It is suggested to use instead a more advanced library such as
   * `Button2` which is available at
   * https://github.com/LennartHennigs/Button2 (see
   * https://www.arduino.cc/reference/en/libraries/button2/).
   */
  class ButtonHandler {

  public:

    /**
     * Button status type.
     */
    enum Status {
                 PRESSED, /**< The button is pressed. */
                 RELEASED /**< The button is released. */
    };

    /**
     * Detected event type.
     */
    enum Event {
                NONE,         /**< No event. */
                SINGLE_CLICK, /**< Single click event. */
                DOUBLE_CLICK, /**< Double click event. */
                TRIPLE_CLICK, /**< Triple click event. */
                LONG_PRESS,   /**< Long pressed event. */
    };

    /**
     * The default time (in milliseconds) under which a click is
     * considered as short. That means that above this delay, a click
     * is considered as long by default.
     */
    static const unsigned long SHORT_CLICK_MAX_DELAY = 200;

    /**
     * The default time (in milliseconds) between two clicks to
     * consider them as consecutive (for double clicks or triple
     * clicks).
     */
    static const unsigned long DEBOUNCE_DELAY = 100;

  protected:

    /**
     * The starting time (in milliseconds) of the first click (from a
     * potential serie of clicks).
     */
    unsigned long _first_pressed;

    /**
     * The starting time (in milliseconds) of the second click (from a
     * potential serie of clicks). A non zero value means that there
     * was already a first short click.
     */
    unsigned long _second_pressed;

    /**
     * The starting time (in milliseconds) of the third click (from a
     * potential serie of clicks). A non zero value means that there
     * was already a first and a second short clicks.
     */
    unsigned long _third_pressed;
    /**
     * The last time (in milliseconds) the button was released. This
     * parameter is used to check the time spent from the last click
     * in order to check if there is a serie of clicks.
     */
    unsigned long _last_released;

    /**
     * The status of the button on the last time it was observed.
     */
    Status _current_status;

    /**
     * The time (in milliseconds) under which a click is considered as
     * short. That means that above this delay, a click is considered
     * as long by default.
     */
    const unsigned long _short_click_max_delay;

    /**
     * The time (in milliseconds) between two clicks to consider them
     * as consecutive (for double clicks or triple clicks).
     */
    const unsigned long _debounce_delay;

  public:

    /**
     * Creates a new button handler.
     *
     * \param short_click_max_delay Time (in milliseconds) under which
     * a click is considered as short. That means that above this
     * delay, a click is considered as long by default.
     *
     * \param debounce_delay Time (in milliseconds) between two clicks
     * to consider them as consecutive (for double clicks or triple
     * clicks).
     */
    ButtonHandler(unsigned long short_click_max_delay,
                  unsigned long debounce_delay);

    /**
     * Reset any click information and set button status to RELEASE.
     */
    void reset();

    /**
     * Get the current button status.
     *
     * Any derived class must override this method.
     *
     * \return This method retrieve the current button status.
     */
    virtual Status getStatus() const = 0;

    /**
     * Get the current detected event.
     *
     * \return This method detects and return the button event.
     */
    Event getEvent();

  };

}

#endif
// Local Variables:
// mode: c++
// End:
