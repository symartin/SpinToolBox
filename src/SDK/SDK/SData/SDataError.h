/*
Copyright (C) 2010 Sylvain Martin (Spintec - CEA/CNRS/UJF/G-INP)
All rights reserved.

This file is part of the MultiMaxSpectre


This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef SERROR_H
#define SERROR_H

#include <QtCore>

const QString SERROR_NO_SUPPORTED_FILE = "File type no supported ";
const QString SERROR_INACCESSIBLE_FILE = "The file is inaccessible";
const QString SERROR_NO_VALIDE_DATA = "One line of the data file is not correct";
const QString SERROR_NO_LOADED_DATA = "No load data";
const QString SERROR_NO_FOUND_METADATA = "Key no found in the metadata map table";
const QString SERROR_NO_CANNOT_CONVERT_METADATA = "This metadata cannot be converted";
const QString SERROR_OUT_OF_BOUNDS = "The specified index is out of bounds";


#endif // SERROR_H
