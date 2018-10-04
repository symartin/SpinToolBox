/*
Copyright (C) 2010-2011 Sylvain Martin (Spintec - CEA/CNRS/UJF/G-INP)
All rights reserved.

This file is part of the SpinToolBox

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


#include "SDataND.h"
#include <QtCore>


SDataND::SDataND( QFile * file )
{

}

SDataND::SDataND( QString const file )
{

}

SDataND::SDataND( QList<double> const xlist, QList<double> const ylist )
{

}

SDataND::SDataND( SDataND *data )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDataND::SDataND(QList<double> const xList, QList<double> const yList )
///
/// \brief	destructor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SDataND::~SDataND(){
	if(ptFile == NULL){
		delete ptFile;
	}
}
int SDataND::count() const
{
	return 0;
}

int SDataND::size() const
{
	return 0;
}

void SDataND::openFile( QFile * file )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDataND::openFile(QString file)
///
/// \brief	open a data file and put it in the data object. 
///
///
///  \exception SERROR_NO_SUPPORTED_FILE File type no supported
///  \exception SERROR_INACCESSIBLE_FILE The file is inaccessible
///  \exception SERROR_NO_VALIDE_DATA One line of the data file is not correct
///
///  \param	file	The file that we want load. 
/// 				
////////////////////////////////////////////////////////////////////////////////////////////////////

void SDataND::openFile(QString file){
	ptFile = new QFile(file);
	this->openFile(ptFile);
}


void SDataND::saveFile( QFile * file )
{

}

void SDataND::saveFile( QString file )
{

}

void SDataND::delItem( int i )
{

}

