////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUi\SUiCpK2400.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/12/2012
///
/// \brief	Declares the class that correspond to the K2400 control panel
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


#include "GeneratedFiles\ui_SUiCpK2400.h"
#include "SDeviceK2400.h"
#include <QtCore>
#include <QtGui>

#define MiliAmp 1000



////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDevicePSAE4440APlugin
///
/// \brief	it is the class that manage the control panel of the Keithley k2400
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	01/03/2012
/// 			
/// \sa SDeviceK2400	
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class SUiCpK2400 :
	public QWidget,
	public Ui_SUiCpK2400
{
	Q_OBJECT;
public:
	SUiCpK2400(QWidget * parent = NULL);
	~SUiCpK2400(void);

private slots:
	void on_cmdDcOnOff_clicked (bool checked);
	void on_dsbDcValue_valueChanged(double d);

	void on_radbttDcCurrent_clicked ( bool checked);
	void on_radbttDcVoltage_clicked ( bool checked);

	void on_dsbDcValue_editingFinished();
	void on_dsbDcCurrentMax_editingFinished();
	void on_dsbDcVoltageMax_editingFinished();

private:
	QString hearderMsgFormat( QString msg, QColor color );
	void delay(double i) ;
	SDeviceK2400* K2400;
};

