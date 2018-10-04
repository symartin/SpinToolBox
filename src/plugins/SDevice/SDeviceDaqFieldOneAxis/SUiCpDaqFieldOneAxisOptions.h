#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUiCpDaqFieldOneAxisOption.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		15/10/2012
///
/// \brief	Declares the class that correspond to the option dialog of DaqFieldOneAxis
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
#include "GeneratedFiles\ui_SUiCpDaqFieldOneAxisOptions.h"
#include <QScriptable>
#include <QScriptEngine>
#include <QSettings>
#include <QtCore>
#include <QtGui>



class SUiCpDaqFieldOneAxisOptions :
	public QDialog,
	public Ui_SUiCpDaqFieldOneAxisOptions
{
	Q_OBJECT;

public:
	SUiCpDaqFieldOneAxisOptions(QWidget * parent = NULL);
	~SUiCpDaqFieldOneAxisOptions(void);

	private slots:
		void on_cmdOk_clicked ();



private:
	QSettings *set_;

};