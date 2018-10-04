////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUiCpDaqFieldOneAxis.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/03/2012
///
/// \brief	Implement the class that correspond to the command panel of DaqFieldOneAxis
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

#include "SUiCpDaqFieldOneAxis.h"
#include "SDeviceDaqFieldOneAxis.h"
#include "SUiCpDaqFieldOneAxisOptions.h"
#include <SDK\SError.h>
#include <SDK\SUi\SUiLblLed.h>
#include <QtCore>
#include <QtGui>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SUiCpK2400::SUiCpK2400(QWidget * parrent /* = NULL*/ )
///
/// \brief constructor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SUiCpDaqFieldOneAxis::SUiCpDaqFieldOneAxis(QWidget * parent /* = NULL*/ ):QWidget( parent ),Vold(0),Vc(0),TimerMovingSlider(NULL)
{

	setupUi(this);

		try{

			DAQ =  SInterfaceDaq::instance();

			// Card DAQ mx
			if (!DAQ->available()){
				hearderMsgFormat("The field command is unavailable",Qt::red);
				this->ledField->setRed();
			}else{
				this->ledField->setGrey();
			}

		}catch (SError error){
			//qDebug()<< error;
		}

		if (TimerMovingSlider == NULL) 	//timer pour le slide
			TimerMovingSlider = new QTimer(this);

		connect(TimerMovingSlider, SIGNAL(timeout()), this, SLOT(moveSlider()));
}
SUiCpDaqFieldOneAxis::~SUiCpDaqFieldOneAxis()
{
	changeField(0);

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::on_dsbField_valueChanged( double d )
///
/// \brief (SLOT) when the value of the double spin box of the field tab changes
///
/// \param d the new value
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpDaqFieldOneAxis::on_dsbFieldValue_valueChanged( double d ){

	if (chkbxFieldRealTime->isChecked()){
		changeField(dsbFieldValue->value(),dsbFieldSpeed->value());
	}else{
		sldFieldValue->setValue(d*100.0);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::on_sldField_valueChanged( double d )
///
/// \brief (SLOT) when the value of the slide bar of the field tab changes
///
/// \param d the new value
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpDaqFieldOneAxis::on_sldFieldValue_sliderMoved( int d ){

	static int Old =0;

	if (DAQ->running() || ledField->isYellow()){

		sldFieldValue->setValue(Old);

	}else{
		dsbFieldValue->setValue(d/100.0);
		if (chkbxFieldRealTime->isChecked()){	
			changeField(dsbFieldValue->value(),dsbFieldSpeed->value());
		}
		Old = d;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::on_cmdFieldGo_clicked( double d )
///
/// \brief (SLOT) when the [GO] button of the field tab is clicked
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpDaqFieldOneAxis::on_cmdFieldGo_clicked(){

	changeField(dsbFieldValue->value(),dsbFieldSpeed->value());

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::on_cmdFieldGo_clicked( double d )
///
/// \brief (SLOT) when the [AP] (AP for anti-parallel)button of the field tab is clicked
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpDaqFieldOneAxis::on_cmdFieldAP_clicked(){
	changeField(FIELD_AP_VALUE);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::on_cmdFieldGo_clicked( double d )
///
/// \brief (SLOT) when the [P] (P for parallel) button of the field tab is clicked
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpDaqFieldOneAxis::on_cmdFieldP_clicked(){
	changeField(FIELD_P_VALUE);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::on_cmdFieldGo_clicked( double d )
///
/// \brief (SLOT) when the [-0-] (for zero) button of the field tab is clicked
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpDaqFieldOneAxis::on_cmdFieldZero_clicked(){
	changeField(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::on_cmdFieldGo_clicked( double d )
///
/// \brief (SLOT) when the [Real Time] button of the field tab is clicked (and the state change)
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpDaqFieldOneAxis::on_chkbxFieldRealTime_stateChanged( int state ){
	//on_cmdFieldGo_clicked();

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::on_cmdFieldGo_clicked( double d )
///
/// \brief (SLOT) when the [ON]/[OFF] button of the field tab is clicked
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpDaqFieldOneAxis::on_cmdFieldOnOff_clicked( bool checked ){

	// si on est en train de faire qqc on n'accepte pas le changement de statue
	if (DAQ->running() || ledField->isYellow()){
		cmdFieldOnOff->setChecked(!checked);
		return;
	}

	if(ledField->isRed()){ // on check si le device est tjs indispos
		cmdFieldOnOff->setChecked(false);
		if (DAQ->available()){
			lblFieldState->setText(hearderMsgFormat("DC source OFF",Qt::gray));
			ledField->setGrey();
			cmdFieldOnOff->setText("OFF");
		}
		return;
	}else if(!DAQ->available()){ // on check si le device est tjs dispos
		ledField->setRed();
		cmdFieldOnOff->setText("OFF");
		lblFieldState->setText(hearderMsgFormat("The field bias is unavailable",Qt::red));
		return;
	}

	if(checked){
		ledField->setGreen();
		cmdFieldOnOff->setText("ON");
		lblFieldState->setText(hearderMsgFormat("Field ON",Qt::darkGreen));
		on_cmdFieldGo_clicked();

	}else{
		lblFieldState->setText(hearderMsgFormat("Field OFF",Qt::gray));
		cmdFieldOnOff->setText("OFF");
		ledField->setYellow();
		DAQ->sweep(0,0.7,dsbFieldChannel->value());
		ledField->setGrey();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::changeField( double V, double dV )
///
/// \brief 
/// \param	V		The goal value in volts   
/// \param	dV		The "speed" of the sweep
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpDaqFieldOneAxis::changeField( double V, double dV /* = 0.8*/ ){

	bool timerNeeded = false; // par defaut le timer est off

	if(V == DAQ->vOld()) return;

	// On active le timer que si le deplacement et suffisament grand
	if (qAbs(Vold-V)>0.05){
		timerNeeded = true;
		sldFieldValue->setValue(Vold*100);
	}

	
	Vc = V;
	double VOLDtest = DAQ->vOld();
	if (cmdFieldOnOff->isChecked() && ledField->isGreen()){		
			

		double tpsSweep = fabs((V-DAQ->vOld())/dV)+0.01;		///< temps entre consigne et ancienne valeur
		
		
		TimerMovingSlider->setInterval(10);
		timerStep_ = 10*(V-DAQ->vOld())/(tpsSweep*1000);
		if(timerNeeded) TimerMovingSlider->start();
		
		ledField->setYellow();
		DAQ->sweep(V,dV,dsbFieldChannel->value());
		sldFieldValue->setValue(V*100);
		dsbFieldValue->setValue(V);
		ledField->setGreen();

		Vold = V;
		TimerMovingSlider->stop();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::moveSlider()
///
/// \brief	function activated by the timer for moving the slider
///
/// \author	Sylvain Martin
/// \date	29/10/2012
////////////////////////////////////////////////////////////////////////////////////////////////////

void SUiCpDaqFieldOneAxis::moveSlider(){

	double Vnext= Vold*100 +timerStep_*100;

	if(	(Vc<Vold && Vnext>Vc*100) ||
		(Vc>Vold && Vnext<Vc*100) 
		){
		sldFieldValue->setValue(Vnext);
		Vold = Vnext/100.0;
	}else{
		sldFieldValue->setValue(Vc*100);
		Vold =Vc;

		TimerMovingSlider->stop();
	}

	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::hearderMsgFormat( QString msg, QColor color )
///
/// \brief Format a text (font and color) to the header of the form.
///
/// \param msg The text that will be format
/// \param color The color desired.
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SUiCpDaqFieldOneAxis::hearderMsgFormat( QString msg, QColor color ){

	QString res =  QString("<p align=\"center\"><span style=\" font-size:16pt; font-weight:600; color:")
		+ color.name() + QString("\">") + msg + QString("</span></p>");

	return res;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpDaqFieldOneAxis::delay(double i) 
/// \brief	Pause the application for i seconds 
///
/// \param i the number of seconds
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpDaqFieldOneAxis::delay(double i) 
{
	clock_t start,end;
	start=clock();

	while(((end=clock())-start)<=i*CLOCKS_PER_SEC){
		QCoreApplication::processEvents ();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpDaqFieldOneAxis::on_cmdOpt_clicked()
///
/// \brief	Handles command option clicked signals.
///
/// \author	Sylvain Martin
/// \date	18/10/2012
////////////////////////////////////////////////////////////////////////////////////////////////////

void SUiCpDaqFieldOneAxis::on_cmdOpt_clicked()
{
	QWidget * widSetting = new SUiCpDaqFieldOneAxisOptions(this);
	widSetting->show();
}

