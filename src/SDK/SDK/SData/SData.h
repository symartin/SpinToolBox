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

#ifndef SDATA_H
#define SDATA_H

#include <QtCore>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SData
///
/// \brief	Abstract class for the manipulation of the data in n dimensions.
///
/// \author	Sylvain Martin
/// \date	26/01/2011
///
/// \ingroup SDataMod
///
/// the implantation is not finished yet
////////////////////////////////////////////////////////////////////////////////////////////////////
class SData {

public:
	SData();
	~SData();


	virtual QVariant  metaData(QString const key) const;
	virtual void setMetaData(QString const key, QVariant const value);
	virtual void clearMetaData();

	virtual void delItem(int i)=0;

	virtual void setColName(int ColNum,QString name);
	virtual QString colName(int ColNum);

	virtual void setColUnit(int ColNum, QString Unit);
	virtual QString colUnit(int ColNum);

	virtual void addComment(QString com);
	virtual void addComment( QStringList comList );
	virtual QStringList comment() const;
	virtual void setComment(QStringList comList);
	virtual void clearComment();
	virtual int sizeComment();


	virtual int count() const = 0;
	virtual int size() const = 0;

	virtual void openFile(QFile * file) =0;
	virtual void openFile(QString file) =0;

	virtual void saveFile(QFile * file)=0;
	virtual void saveFile(QString file)=0;

	virtual int numCol();

protected:
	void treatSharpLine(QString line);
	int extractHeader(const QFile * fl); // extract header 
	int numCol_;

	QVariantMap MetaData_;
	int NbMetatData_;
	QStringList comment_;
	QStringList colName_;
	QStringList colUnit_;
	bool MagToolBoxCompatibility_;


};



#endif // SDATA_H