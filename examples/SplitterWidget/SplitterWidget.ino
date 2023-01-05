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

#include <TFT_eSPI_Widgets.h>

using namespace TFT_eSPI_Widgets;

TFT_eSPI tft;
Canvas canvas;

// On a TTGO T-Display, there is two builtin buttons, one is attached
// to the GPIO 35 pin and the other is attached to the GPIO 0 pin.
// Both those pins are HIGH when buttons are released.
PhysicalButtonHandler left_btn(35, HIGH);
PhysicalButtonHandler right_btn(0, HIGH);

// Capture left and right buttons' events and pass them to the canvas
// (root of the widget tree).
void processButtonEvents() {
  ButtonHandler::Event left_event = left_btn.getEvent();
  ButtonHandler::Event right_event = right_btn.getEvent();

  switch (left_event) {
  case ButtonHandler::SINGLE_CLICK:
    Serial.println("Canvas is passed a single left click");
    canvas.handleEvent(SINGLE_LEFT_CLICK);
    break;
  case ButtonHandler::DOUBLE_CLICK:
    Serial.println("Canvas is passed a double left click");
    canvas.handleEvent(DOUBLE_LEFT_CLICK);
    break;
  case ButtonHandler::TRIPLE_CLICK:
    Serial.println("Canvas is passed a triple left click");
    canvas.handleEvent(TRIPLE_LEFT_CLICK);
    break;
  case ButtonHandler::LONG_PRESS:
    Serial.println("Canvas is passed a long left click");
    canvas.handleEvent(LONG_LEFT_PRESS);
    break;
  }
  switch (right_event) {
  case ButtonHandler::SINGLE_CLICK:
    Serial.println("Canvas is passed a single right click");
    canvas.handleEvent(SINGLE_RIGHT_CLICK);
    break;
  case ButtonHandler::DOUBLE_CLICK:
    Serial.println("Canvas is passed a double right click");
    canvas.handleEvent(DOUBLE_RIGHT_CLICK);
    break;
  case ButtonHandler::TRIPLE_CLICK:
    Serial.println("Canvas is passed a triple right click");
    canvas.handleEvent(TRIPLE_RIGHT_CLICK);
    break;
  case ButtonHandler::LONG_PRESS:
    Serial.println("Canvas is passed a long right click");
    canvas.handleEvent(LONG_RIGHT_PRESS);
    break;
  }
}

enum Icon_t {
             MIN_ICON_ID,
             AUTHENTICATION_ICON = MIN_ICON_ID,
             ERROR_ICON,
             INFO_ICON,
             QUESTION_ICON,
             WARNING_ICON,
             MAX_ICON_ID = WARNING_ICON
};

Icon_t previous_icon;
Icon_t current_icon;
String README_message;

// This demo screen is structured like this:
// +-------------------- TFT canvas -------------------+
// | +------------ main vertical splitter -----------+ |
// | | +------------------ title ------------------+ | |
// | | |      This is a demo splitter widget.      | | |
// | | +-------------------------------------------+ | |
// | | | +--------- horizontal splitter ---------+ | | |
// | | | | +-icon-+----- vertical splitter ----+ | | | |
// | | | | |      | +------ information -----+ | | | | |
// | | | | |      | |Changing the integer    | | | | | |
// | | | | | ???? | |value below should      | | | | | |
// | | | | | ???? | |change the displayed    | | | | | |
// | | | | | ???? | |icon                    | | | | | |
// | | | | | ???? | +----- integer entry ----+ | | | | |
// | | | | | ???? | |         <value>        | | | | | |
// | | | | | ???? | +------ description -----+ | | | | |
// | | | | | ???? | |[??????] + README.txt   | | | | | |
// | | | | |      | |file content.           | | | | | |
// | | | | |      | +------------------------+ | | | | |
// | | | | +------+----------------------------+ | | | |
// | | | +---------------------------------------+ | | |
// | | +-------------------------------------------+ | |
// | +-----------------------------------------------+ |
// +---------------------------------------------------+


// Change the icon path if current_icon has changed since the last
// loop
void onIconLoop(Widget &w) {
  if (current_icon != previous_icon) {
    ImageWidget &_w = w.as<ImageWidget>();
    switch (current_icon) {
    case AUTHENTICATION_ICON:
      _w.setPath("/gtk-dialog-authentication.png");
      break;
    case ERROR_ICON:
      _w.setPath("/gtk-dialog-error.png");
      break;
    case INFO_ICON:
      _w.setPath("/gtk-dialog-info.png");
      break;
    case QUESTION_ICON:
      _w.setPath("/gtk-dialog-question.png");
      break;
    case WARNING_ICON:
      _w.setPath("/gtk-dialog-warning.png");
      break;
    }
    w.touch();
  }
}

// Change the displayed description if current_icon has changed since
// the last loop
void onDescriptionLoop(Widget &w) {
  if (current_icon != previous_icon) {
    String message = "[";
    switch (current_icon) {
    case AUTHENTICATION_ICON:
      message += "Authentication";
      break;
    case ERROR_ICON:
      message += "Error";
      break;
    case INFO_ICON:
      message += "Information";
      break;
    case QUESTION_ICON:
      message += "Question";
      break;
    case WARNING_ICON:
      message += "Warning";
    }
    message += "] ";
    message += README_message;
    MessageWidget &_w = w.as<MessageWidget>();
    _w.setMessage(message);
    w.touch();
  }
}

void onIconSelectionChange(Widget &w, int32_t old_value, int32_t new_value) {
  IntegerEntryWidget &_w = w.as<IntegerEntryWidget>();
  previous_icon = (Icon_t) old_value;
  current_icon = (Icon_t) new_value;
}

// Function to call once during the setup to initialize the tft and
// its associated widgets.
void initScreen() {

  // Initialize the TFT screen.
  tft.init();
  tft.setRotation(1);

  // Add a canvas widget to handle the TFT screen.
  canvas.init(tft,
              GraphicalProperties(TFT_DARKGREY /* background color */,
                                  TFT_RED /* border color */,
                                  TFT_WHITE /* font color */,
                                  0 /* border size */,
                                  1 /* font size */),
              GraphicalProperties(TFT_DARKGREY /* background color */,
                                  TFT_BLUE /* border color */,
                                  TFT_WHITE /* font color */,
                                  2 /* border size */,
                                  1 /* font size */)
              );

  // Add a splash screen
  new MessageWidget(canvas,
                    "This is a demo splitter widget.\n\n           Loading...");
  canvas.getChild().shrink();
  canvas.touch();
  canvas.loop();
  canvas.refresh();
  delay(3000);

  // Add a vertical splitter.
  new SplitterWidget(canvas, SplitterWidget::VERTICAL);
  SplitterWidget &main_v_splitter = canvas.getChild<SplitterWidget>();

  // Add a "title" label as first child of the main vertical splitter.
  new MessageWidget(main_v_splitter, "This is a demo splitter widget.");

  // Add an horizontal (default) splitter as second child of the main
  // vertical splitter
  new SplitterWidget(main_v_splitter);

  // By default, all splitter children have a unit weight. Let us give
  // a weight of 9 for the horizontal splitter within the main
  // vertical splitter.
  main_v_splitter[1].setWeight(9);

  // Retrieving the horizontal splitter.
  SplitterWidget &h_splitter = main_v_splitter[1].getChild<SplitterWidget>();

  // Add an image (with a fake path) as first child of the horizontal splitter
  new ImageWidget(h_splitter, "<no path for now>");

  // Add a vertical splitter as second child of the horizontal
  // splitter, reserving room for 3 children.
  new SplitterWidget(h_splitter, SplitterWidget::VERTICAL, 3);

  // Give a weight of 4 for this vertical splitter.
  h_splitter[1].setWeight(4);

  SplitterWidget &inner_v_splitter = h_splitter[1].getChild<SplitterWidget>();

  new MessageWidget(inner_v_splitter,
                    "Changing the integer value below should change the displayed icon.",
                    true);

  current_icon = INFO_ICON;
  previous_icon = ERROR_ICON;
  new IntegerEntryWidget(inner_v_splitter, current_icon, MIN_ICON_ID, MAX_ICON_ID);

  new MessageWidget(inner_v_splitter, "<MESSAGE TO BE UDPATED>", true);

  README_message = "";
  fs::File fd = TFT_eSPI_Widgets_FS.open("/README.txt");
  if (fd) {
    while (fd.available()) {
      README_message += fd.readString();
    }
    fd.close();
  } else {
    Serial.println("Failed to open README.txt file");
  }

  // Update of the icon and associated message.
  h_splitter[0].getChild().onLoop(onIconLoop);
  inner_v_splitter[1].getChild<IntegerEntryWidget>().onValueChange(onIconSelectionChange);
  inner_v_splitter[2].getChild().onLoop(onDescriptionLoop);

  // Setting respective weights 3, 2 and 5 to the rightmost inner
  // vertical splitter components.
  inner_v_splitter[0].setWeight(6);
  inner_v_splitter[1].setWeight(3);
  inner_v_splitter[2].setWeight(11);

  // Adding a border around the canvas.
  GraphicalProperties props = canvas.getDefaultGraphicalProperties();
  props.setBorderSize(2);
  canvas.setDefaultGraphicalProperties(props);

  // Fitting the widgets to use all the available space.
  canvas.fit(true);
  canvas.loop();
  canvas.refresh();

  // Shrink the title widget in order to make it centered.
  main_v_splitter[0].getChild().shrink();

  // Shrink the icon in order to make it centered.
  h_splitter[0].getChild().shrink();

  // Force redraw on next loop.
  canvas.touch();
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("Starting TFT_eSPI Widget library Canvas demo...");

  Serial.println("[Mounting " stringify(TFT_eSPI_Widgets_FS) "]");
  if(!TFT_eSPI_Widgets_FS.begin(false)){
    Serial.println(stringify(TFT_eSPI_Widgets_FS) " mount Failed!!!");
    return;
  }

  listDirectoryContent();

  initScreen();

  left_btn.init();
  right_btn.init();

  // Print widget tree on Serial.
  Serial.println("Widget tree:");
  canvas.print();

  Serial.println("[End of demo setup]");
}

void loop(void) {

  // Catch button events.
  processButtonEvents();

  // Calling the loop() method on canvas.
  canvas.loop();

  // Then refresh the canvas.
  canvas.refresh();

  // Saving the current icon information.
  previous_icon = current_icon;

  delay(10);

}

// Local Variables:
// mode: c++
// End:
