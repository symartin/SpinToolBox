////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUiCpDaqFieldOneAxis.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/03/2012
///
/// \brief	Declares the class that correspond to the command panel of DaqFieldOneAxis
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


#include "GeneratedFiles\ui_SUiCpDaqFieldOneAxis.h"
#include "SDeviceDaqFieldOneAxis.h"
#include <QtCore>
#include <QtGui>

#define FIELD_AP_VALUE -6
#define FIELD_P_VALUE 6

class SUiCpDaqFieldOneAxis :
	public QWidget,
	public Ui_SUiCpDaqFieldOneAxis
{
	Q_OBJECT;
public:
	SUiCpDaqFieldOneAxis(QWidget * parent = NULL);
	~SUiCpDaqFieldOneAxis(void);

	private slots:
		void on_dsbFieldValue_valueChanged (double d);
		void on_sldFieldValue_sliderMoved (int d);
		void on_cmdFieldGo_clicked ();
		void on_cmdFieldAP_clicked ();
		void on_cmdFieldP_clicked ();
		void on_cmdFieldZero_clicked ();
		void on_chkbxFieldRealTime_stateChanged(int state );
		void on_cmdFieldOnOff_clicked (bool checked);
		void on_cmdOpt_clicked();
		void moveSlider();


private:
	QString hearderMsgFormat( QString msg, QColor color );
	void delay(double i) ;
	void changeField(double V, double dV = 0.8);
	double timerStep_;
	double Vc; ///< Vconsigne
	double Vold ;
	SInterfaceDaq * DAQ;
	QTimer * TimerMovingSlider;

};