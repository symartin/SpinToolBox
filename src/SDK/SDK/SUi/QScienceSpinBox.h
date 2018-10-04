////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUi\QScienceSpinBox.h
/// 		
/// \author		Matthias Pospiech (http://www.matthiaspospiech.de/blog/)
/// \version	1.0
/// \date		2010
///
/// \brief	Declares the SInterfaceDaq class
/// 		
/// \section LICENSE
///
/// This program is free software; you can redistribute it and/or
/// modify it under the terms of the GNU General Public License as
/// published by the Free Software Foundation; either version 2 of
/// the License, or (at your option) any later version.
/// 
/// This program is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
/// General Public License for more details at
/// http://www.gnu.org/copyleft/gpl.html
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef __QScienceSpinBox_H__
#define __QScienceSpinBox_H__

#include <QtGui>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <QtCore/QString>

static bool isIntermediateValueHelper(qint64 num, qint64 minimum, qint64 maximum, qint64 *match = 0);
//////////////////////////////////////////////////////////////////////////////////////////////
/// \clase QScienceSpinBox
///
/// \ingroup SUiMod
/// \brief  this class provides a Qt widget that can handle numbers in a scientific notation.
///
/// Since I started using Qt over a year ago I have been asking and looking for a Qt widget
/// that can handle numbers in a scientific notation. Unfortunately Qt Software does not offer
/// such a solution nor is it trivial to implement. With the hints I got in some public web
/// forums I implement the solution provided here.
///
/// widget is derived from QDoubleSpinBox. It uses a decimal value of 1000
/// (that is more decimal points than a double can handle) and implements a new decimal
/// value for the presentation in scientific notation. The Validator is realised by setting
/// the LineEdit to a QDoubleValidator::ScientificNotation. However the most important part
/// is the reimplementation of textFromValue and valueFromText. This unfortunately requires
/// to copy the whole validation code of QDoubleSpinBox, which can not be borrowed and
/// represents the major part of the code.
///
/// If someone can show a shrinked but still functional equivalent version that would be great.
/// In the end I think that it would be better if such a solution would be included into a Qt
/// release, especially because in its current form I use so much of their code.
//////////////////////////////////////////////////////////////////////////////////////////////////////

class QScienceSpinBox : public QDoubleSpinBox
{
	Q_OBJECT;


	Q_PROPERTY(QChar delimiter READ delimiter WRITE setDelimiter);
	Q_PROPERTY(int step READ step WRITE setStep);
	Q_PROPERTY(bool byDecimals READ byDecimals WRITE setByDecimals);
public:
    QScienceSpinBox(QWidget * parent = 0);

	int decimals() const;
	void setDecimals(int value);

    QString textFromValue ( double value ) const;
    double valueFromText ( const QString & text ) const;

	void setDelimiter(QChar del);
	QChar delimiter();
	double step();

	bool byDecimals();
	void setByDecimals(bool bd);

private:
	bool byDecimals_;
	int dispDecimals;
	double step_;
    QChar delimiter_, thousand;
	QDoubleValidator * v;

	QMenu * mnuContext;
	QWidget * widStep;
	QVBoxLayout * vlStep;
	QLabel * lblStep;
	QLineEdit * txtStep;
	QWidgetAction  * actwidPrecision;

	QMenu * mnuMode;
	QAction * actModeScientific;
	QAction * actModeEngineer;
	QAction * actModeClassic;
	QActionGroup* actModeGroup;

private:
	void initLocalValues(QWidget *parent);
    bool isIntermediateValue(const QString &str) const;
    QVariant validateAndInterpret(QString &input, int &pos, QValidator::State &state) const;
	QValidator::State validate(QString &text, int &pos) const;
	void fixup(QString &input) const;
	QString stripped(const QString &t, int *pos) const;
	double round(double value) const;
	void stepBy(int steps);
	void setupMenu();

public slots:
	void stepDown();
	void stepUp();
	void setMaximum(double d);
	void setMinimum(double d);
	void contextMenuEvent(QContextMenuEvent *event);
	void setStep(double step);


private slots:
	void stepChanged();
	void setModeScientific();
	void setModeEngineer();
	void setModeClassic();
};

#endif