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
#pragma once

#ifndef SDATAND_H
#define SDATAND_H

#include "SData.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SData2D
///
/// \brief	Class for the manipulation of the data in N dimensions (generalized the SData2D class).
///
/// \author	Sylvain Martin
/// \date	22/11/2011
///
/// \ingroup SDataMod
///
/// \remark Data are stocked in a vector of column.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

class SDataND : public SData {

	SDataND(int nbCol);	
	SDataND(QFile * file);
	SDataND(QString const file);
	SDataND(QList<double> const xlist, QList<double> const ylist);
	SDataND(SDataND *data);

	~SDataND();

	virtual int count() const;
	virtual int size() const;

	virtual void openFile(QFile * file);
	virtual void openFile(QString file);

	virtual void saveFile(QFile * file);
	virtual void saveFile(QString file);

	virtual void delItem(int i);


protected:


	// Data are stocked in a vector of column
	QVector<QVector<double> > data_;

	QFile * ptFile;


};





#endif //SDATAND_H