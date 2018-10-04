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

#ifndef SDATA2D_H
#define SDATA2D_H

#undef max

#include <QtCore>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SData2D
///
/// \brief	Class for the manipulation of the data in 2 dimensions (y and y).
///
/// \author	Sylvain Martin
/// \date	1/26/2011
///
/// \ingroup SDataMod
////////////////////////////////////////////////////////////////////////////////////////////////////

class SData2D {
public:
    SData2D();
    SData2D(QFile * file);
	SData2D(QString const file);
    SData2D(QList<double> const xlist, QList<double> const ylist);
	SData2D(SData2D *data);

	~SData2D();

    typedef struct{
            double x_;
            double y_;
    } DataPoint;

	void SData2D::setData(SData2D data);

    QVariant metaData(QString const key) const;
    double metaDataAsDouble(QString const key) const;
    void setMetaData(QString const key, QVariant const value);

	void clearMetaData();
	void delItem(int i);

	void setColName(QString Xname, QString Yname);

	void setColXName(QString Xname);
	QString colXName();

	void setColYName(QString Yname);
	QString colYName();


	void setColUnit(QString XUnit, QString YUnit);

	void setColXUnit(QString XUnit);
	QString colXUnit();

	void setColYUnit(QString YUnit);
	QString colYUnit();

	void addComment(QString com);
	void addComment( QStringList comList );
	QStringList comment() const;
	void setComment(QStringList comList);
	void clearComment();
	int sizeComment();

    void append (double const x, double const  y);
    void append (QList<double> const xList, QList<double> const yList);
    void append (SData2D::DataPoint const point);

	void overwrite(SData2D & data);
	void overwrite(SData2D * data);
	int count() const;
	int size() const;

    void openFile(QFile * file);
    void openFile(QString file);

    void saveFile(QFile * file);
    void saveFile(QString file);

    void slideAverage(int const windows = 20, double const PeackProtectCoeff=0);
    SData2D::DataPoint max(int const start = 0) const;

	QList<double> * x() ;
	QList<double> * y() ;

	double *xData();
	double *yData();

 protected:
    QVariantMap MetaData_;
    void treatSharpLine(QString line);
    int NbMetatData_;
	QStringList comment_;
	QStringList colName_;
	QStringList colUnit_;
	bool MagToolBoxCompatibility_;
	QList<double> x_;
	QList<double> y_;
	QVector<double> vectX;
	QVector<double> vectY;


	QFile * ptFile;
	
};

#endif // SDATA2D_H