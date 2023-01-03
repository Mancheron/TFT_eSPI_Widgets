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

#ifndef __IMAGE_WIDGET_H__
#define __IMAGE_WIDGET_H__

#include "widget.h"

namespace TFT_eSPI_Widgets {

  /**
   * A widget to display images.
   *
   * Images can be either defined as bmp, jpeg or png files or by raw
   * pixel data.
   */
  class ImageWidget: public Widget {

  public:

    /**
     * The detected file format.
     */
    enum FileFormat {
                     NOT_SET,  /**< File format not yet determined. */
                     RAW_DATA, /**< Raw pixel data format. */
                     BMP,      /**< Bitmap file format. */
                     JPG,      /**< JPEG file format. */
                     PNG,      /**< Portable Network Graphic format. */
                     UNKNOWN,  /**< File format not known. */
    };

  protected:

    /**
     * The image path (require to have a storage access).
     */
    String _path;

    /**
     * The image format.
     */
    FileFormat _format;

    /**
     * The image pixel data (must reside in flash storage
     * e.g. PROGMEM). The number of pixels should be equal to the
     * product of dimensions (see _dimensions attribute).
     */
    const uint16_t *_data;

    /**
     * The image dimensions.
     *
     * The dimension area should be equal to the number of pixels of
     * the _data parameter if using raw pixel data.
     *
     * If the image is defined by a file (see _path attribute), then
     * the _dimensions attribute is updated during image drawing.
     */
    Dimensions _dimensions;

    /**
     * The top left corner of the image is set at the given offset
     * relative to the top left corner of the inner area.
     */
    Coordinates _offset;

    /**
     * Shrink the current widget area to the smallest dimension that
     * allows to see its content.
     *
     * \param recurse This is the recurse value passed to the shrink()
     * method. This parameter is not used for this widget.
     *
     * \param check_for_update This is the check_for_update parameter
     * passed to the fit() method. This parameter is not used for this
     * widget.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _shrink(bool recurse, bool check_for_update);

    /**
     * Update the image dimensions information.
     *
     * If image is defined from file, then if the format is not set,
     * try to detect the file format then on success, update the image
     * dimensions. If image is defined from raw data, this does
     * nothing.
     *
     * \return If image is defined from file, this return true if the
     * dimensions are correctly set and the file format detected. If
     * image is defined from raw data, this is always true.
     */
    bool _updateDimensions();

    /**
     * The specific drawing code for image widgets.
     *
     * \return Returns nothing but doxygen is buggy with inline
     * virtual void signature.
     */
    virtual void _draw();

    /**
     * Try drawing a BMP image.
     *
     * \param real_drawing When true (default), try to draw the image
     * from file. When false, only try to set the file format and on
     * success updates the image dimensions.
     *
     * \return This method returns true if the file format is
     * recognized and correctly drawn.
     */
    bool _drawBmpImage(bool real_drawing = true);

    /**
     * Try drawing a JPEG image.
     *
     * \param real_drawing When true (default), try to draw the image
     * from file. When false, only try to set the file format and on
     * success updates the image dimensions.
     *
     * \return This method returns true if the file format is
     * recognized and correctly drawn.
     */
    bool _drawJpgImage(bool real_drawing = true);

    /**
     * Try drawing a PNG image.
     *
     * \param real_drawing When true (default), try to draw the image
     * from file. When false, only try to set the file format and on
     * success updates the image dimensions.
     *
     * \return This method returns true if the file format is
     * recognized and correctly drawn.
     */
    bool _drawPngImage(bool real_drawing = true);

  public:

    /**
     * Creates an image widget attached to the given Widget.
     *
     * The widget graphical properties (background color, line
     * color, line width, font color, font size) are inherited from
     * the parent widget.
     *
     * The image is displayed with its natural dimensions and is not
     * resized to fit or expand to this inner area.
     *
     * \param parent The parent widget of the current one. Be aware
     * that if this parent already has a child widget, then this child
     * is automatically destroyed.
     *
     * \param path The image path (require to have a storage access).
     * If the image path is not found on the storage (or if there is
     * no storage access, then does nothing).
     *
     * \param offset The top left corner of the image is set at the
     * given offset relative to the top left corner of the inner area.
     *
     * \param area The area used by the widget. If the area dimension
     * is empty, then use the area of its parent minus its maximal
     * border size according to its focus state. The top left anchor
     * of the area is relative to the top left corner of its parent.
     *
     * \remark There is no verification about the area to fit into the
     * parent area.
     */
    ImageWidget(Widget &parent,
                const String &path,
                const Coordinates &offset = Coordinates::origin,
                const Area &area = Area::reference_value);

    /**
     * Creates an image widget attached to the given Widget.
     *
     * The widget graphical properties (background color, line
     * color, line width, font color, font size) are inherited from
     * the parent widget.
     *
     * The image is displayed with its natural dimensions and is not
     * resized to fit or expand to this inner area.
     *
     * \param parent The parent widget of the current one. Be aware
     * that if this parent already has a child widget, then this child
     * is automatically destroyed.
     *
     * \param data The image pixel data (must reside in flash storage
     * e.g. PROGMEM). The number of pixels should be equal to the
     * product of dimensions (see dimensions parameter).
     *
     * \param dimensions The image dimensions. The dimension area
     * should be equal to the number of pixels of the data parameter.
     *
     * \param offset The top left corner of the image is set at the
     * given offset relative to the top left corner of the inner area.
     *
     * \param area The area used by the widget. If the area dimension
     * is empty, then use the area of its parent minus its maximal
     * border size according to its focus state. The top left anchor
     * of the area is relative to the top left corner of its parent.
     *
     * \remark There is no verification about the area to fit into the
     * parent area.
     */
    ImageWidget(Widget &parent,
                const uint16_t *data,
                const Dimensions &dimensions,
                const Coordinates &offset = Coordinates::origin,
                const Area &area = Area::reference_value);

    /**
     * Return the widget type.
     *
     * \return This method returns the IMAGE widget type.
     */
    inline virtual Type getType() const {
      return IMAGE;
    }

    /**
     * Get the image path.
     *
     * \return Returns the image path.
     */
    inline String getPath() const {
      return _path;
    }

    /**
     * Set the image path.
     *
     * \param path The image path (require to have a storage access).
     * If the image path is not found on the storage (or if there is
     * no storage access, then this remove any image information
     * data).
     */
    void setPath(const String &path) {
      _data = NULL;
      _dimensions = Dimensions::empty;
      _path = path;
      _format = NOT_SET;
      _updateDimensions();
    }

    /**
     * Get the image file format.
     *
     * \return Returns the image file format.
     */
    inline FileFormat getFileFormat() const {
      return _format;
    }

    /**
     * Get the image data.
     *
     * \return Returns the image raw data (each pixel is coded using
     * RGB565 with endianess).
     */
    inline const uint16_t *getData() const {
      return _data;
    }

    /**
     * Get the image dimensions.
     *
     * \return Returns the image dimensions.
     */
    inline const Dimensions &getDimensions() const {
      return _dimensions;
    }

    /**
     * Set the image data.
     *
     * \param data The image pixel data (must reside in flash storage
     * e.g. PROGMEM). The number of pixels should be equal to the
     * product of dimensions (see dimensions parameter).
     *
     * \param dimensions The image dimensions. The dimension area
     * should be equal to the number of pixels of the data parameter.
     */
    inline void setData(const uint16_t *data, const Dimensions &dimensions) {
      _path = "";
      _data = data;
      _dimensions = dimensions;
      _format = RAW_DATA;
    }

    /**
     * Get the image offset.
     *
     * \return Returns the image top left corner offset relative to
     * the top left corner of the inner area.
     */
    inline Coordinates getOffset() const {
      return _offset;
    }

    /**
     * Set the image offset.
     *
     * \param offset The top left corner of the image is set at the
     * given offset relative to the top left corner of the inner area.
     */
    inline void setOffset(const Coordinates &offset) {
      _offset = offset;
    }

  };

}

#endif
// Local Variables:
// mode: c++
// End:
