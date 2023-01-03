TFT_eSPI_Widgets Library
========================

This library is a simple widget API to enhance the TFT_eSPI library.

It aims to make easy the GUI development using a Widget approach. Notice
that this is a simplified version with some simple widgets definitions, but
it allows to be extended quite easily using inheritance.

Documentation
-------------

It is recommanded to run the `doxygen` utility in the top source directory
of this library to generate the complete documentation in HTML format.

Once generated, the documentation should reside in the `docs/html`
subdirectory.

In this directory, there should have an `index.html` file which is the main
page of the documentation.

Installation
------------

### Requirements

The TFT_eSPI_Widgets library requires the `TFT_eSPI` library which can be found
at https://github.com/Bodmer/TFT_eSPI/

### Manual installation

Install the `TFT_eSPI` using either the manual installation procedure or by
using the Arduino IDE `Manage Libraries` item of the `Tools` menu.

There is two possibility to download the `TFT_eSPI_Widgets` source code. You
can either download tarballs or clone the `git` repository.

In both cases, you need to visit the web site:
https://gite.lirmm.fr/doccy/TFT_eSPI_Widgets/

If you choose to download the `TFT_eSPI_Widgets` archive, then you simply
need to uncompress it into your arduino `libraries` local directory.

If you choose the `git` clone, then clone the library repository directly
under your `libraries` local directory.


### Arduino IDE installation

Download the `TFT_eSPI_Widgets` zip archive and i the Arduino IDE, open the
`Sketch` menu, select the `Include Library` submenu, then select the `Add
.ZIP library` item. In the dialog select the zip archive of this library and
that's all.

Getting Started
---------------

There is some examples to introduce the `TFT_eSPI_Widgets` library usage.
The first example to start learning the API is in the subdirectory `Canvas`.
It shows how to initialize a canvas and describe the basic graphical
properties of any widgets. It also introduce how to add a callback to the
loop() widget method.

Bug Reporting
-------------

While we use an extensive set of unit tests and test coverage tools
you might still find bugs in the library. We encourage you to report
any problems with the library via the
[gitlab issue tracking system](https://gite.lirmm.fr/doccy/TFT_eSPI_Widgets/-/issues)
of the project.

Licensing
---------

Copyright © 2022-2023 -- LIRMM / CNRS / UM
(Laboratoire d'Informatique, de Robotique et de Microélectronique de Montpellier /
Centre National de la Recherche Scientifique /
Université de Montpellier)

-------------------------------------------------------------------------

La librairie TFT_eSPI_Widgets a pour objet de simplifier le développement
d'interfaces graphiques  pour l'uitlisateur  (GUI)  en se basant  sur une
approche par *widgets* (composants graphiques).

Ce logiciel est régi par la licence CeCILL-C soumise au droit français et
respectant les principes  de diffusion des logiciels libres.  Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions de
la licence CeCILL-C telle que diffusée par le CEA, le CNRS et l'INRIA sur
le site "http://www.cecill.info".

En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité  restreinte pèse  sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les concédants successifs.

À  cet égard  l'attention de  l'utilisateur est  attirée sur  les risques
associés  au chargement,  à  l'utilisation,  à  la modification  et/ou au
développement  et à la reproduction du  logiciel par  l'utilisateur étant
donné  sa spécificité  de logiciel libre,  qui peut le rendre  complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis  possédant  des  connaissances  informatiques  approfondies.  Les
utilisateurs  sont donc  invités  à  charger  et  tester  l'adéquation du
logiciel  à leurs besoins  dans des conditions  permettant  d'assurer  la
sécurité de leurs systêmes et ou de leurs données et,  plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.

Le fait  que vous puissiez accéder  à cet en-tête signifie  que vous avez
pris connaissance de la licence CeCILL-C, et que vous en avez accepté les
termes.

-------------------------------------------------------------------------

The TFT_eSPI_Widgets library aims to make easy the GUI development using
a Widget approach.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software. You can use,
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty and the software's author, the holder of the
economic rights, and the successive licensors have only limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading, using, modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean that it is complicated to manipulate, and that also
therefore means that it is reserved for developers and experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and, more generally, to use and operate it in the same
conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.

-------------------------------------------------------------------------

[Click here to access the full licence](LICENSE.md)

Auteurs/Authors:
----------------

* Alban MANCHERON  <alban.mancheron@lirmm.fr>

Contact:
--------

* Alban MANCHERON  <alban.mancheron@lirmm.fr>

URL:
----

https://gite.lirmm.fr/doccy/TFT_eSPI_Widgets

