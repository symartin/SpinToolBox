////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUi\SUiCpK2400.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		02/24/2011
///
/// \brief	implement the class that correspond to the K2400 control panel
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

#include <time.h>
#include <math.h>
#include <QtCore>
#include <QtGui>

#include "SUiCpK2400.h"
#include "SDeviceK2400.h"
#include "SDK/SError.h"
#include "GeneratedFiles\ui_SUiCpK2400.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SUiCpK2400::SUiCpK2400(QWidget * parrent /* = NULL*/ )
///
/// \brief constructor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SUiCpK2400::SUiCpK2400(QWidget * parent /* = NULL*/ ):QWidget(parent)
{

	setupUi(this);

	try{

		K2400 = new SDeviceK2400(this);

			// DC source Keithley K2400
			if (!K2400->available()){
				lblDcState->setText(hearderMsgFormat("The DC bias is unavailable",Qt::red));
				ledDc->setRed();
			}else{
				ledDc->setGrey();
				K2400->setMode(SDeviceK2400::CURRENT);
				dsbDcCurrentMax->setValue(20);
				dsbDcVoltageMax->setValue(500);
			}

	}catch (SError error){
		qDebug()<< error;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SUiCpK2400::~SUiCpK2400(void)
///
/// \brief Destructor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SUiCpK2400::~SUiCpK2400(void)
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpK2400::on_dsbDcCurrentMax_valueChanged( double d )
///
/// \brief (SLOT) when the value of current limit double spin box changes (in the DC bias tab)
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpK2400::on_dsbDcCurrentMax_editingFinished(){
		double d = dsbDcCurrentMax->value();
	if(!ledDc->isRed()){
		K2400->setCurrentCompliance(d/MiliAmp);
		K2400->setCurrentRange(d/MiliAmp);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpK2400::on_dsbDcVoltageMax_valueChanged( double d )
///
/// \brief (SLOT) when the value of voltage limit double spin box changes (in the DC bias tab)
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpK2400::on_dsbDcVoltageMax_editingFinished(){
	double d = dsbDcVoltageMax->value();

	if(!ledDc->isRed()){
		K2400->setVoltageCompliance(d/MiliAmp);
		K2400->setVoltageRange(d/MiliAmp);
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpK2400::on_radbttDcCurrent_clicked( bool checked )
///
/// \brief (SLOT) When the [Current] radio button of the DC bias tab is clicked.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpK2400::on_radbttDcCurrent_clicked( bool checked ){
	if(checked && !ledDc->isRed()){
		K2400->setMode(SDeviceK2400::CURRENT);
		on_dsbDcValue_valueChanged(dsbDcCurrentMax->value());	
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpK2400::on_radbttDcVoltage_clicked( bool checked )
///
/// \brief (SLOT) When the [Voltage] radio button of the DC bias tab is clicked.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpK2400::on_radbttDcVoltage_clicked( bool checked ){
	if(checked && !ledDc->isRed()){
		K2400->setMode(SDeviceK2400::VOLTAGE);
		on_dsbDcValue_valueChanged(dsbDcCurrentMax->value());	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpK2400::hearderMsgFormat( QString msg, QColor color )
///
/// \brief Format a text (font and color) to the header of the form.
///
/// \param msg The text that will be format
/// \param color The color desired.
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SUiCpK2400::hearderMsgFormat( QString msg, QColor color ){

	QString res =  QString("<p align=\"center\"><span style=\" font-size:16pt; font-weight:600; color:")
		+ color.name() + QString("\">") + msg + QString("</span></p>");

	return res;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpK2400::on_cmdDcOnOff_clicked( bool checked )
///
/// \brief (SLOT) When the [ON]/[OFF] button of the DC bias tab is clicked.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpK2400::on_cmdDcOnOff_clicked( bool checked ){
	if(ledDc->isRed()){ // on check si le device est tjs indispos
		cmdDcOnOff->setChecked(false);
		if (K2400->available()){
			lblDcState->setText(hearderMsgFormat("DC source OFF",Qt::gray));
			cmdDcOnOff->setText("OFF");
			ledDc->setGrey();
		}
		return;
	}else if(!K2400->available()){ // on check si le device est tjs dispos
		ledDc->setRed();
		lblDcState->setText(hearderMsgFormat("The DC bias is unavailable",Qt::red));
		cmdDcOnOff->setText("OFF");
		return;
	}

	if(checked){
		ledDc->setGreen();
		lblDcState->setText(hearderMsgFormat("DC source ON",Qt::darkGreen));
		cmdDcOnOff->setText("ON");

		if(radbttDcVoltage->isChecked() && !ledDc->isRed()){
			K2400->setMode(SDeviceK2400::VOLTAGE);
		}

		if(radbttDcCurrent->isChecked() && !ledDc->isRed()){
			K2400->setMode(SDeviceK2400::CURRENT);
		}

		K2400->setCurrentCompliance(dsbDcCurrentMax->value()/MiliAmp);
		K2400->setVoltageCompliance(dsbDcVoltageMax->value()/MiliAmp);		
		K2400->setVoltageRange(100.0/MiliAmp);
		K2400->setCurrentRange(100.0/MiliAmp);

		on_dsbDcValue_editingFinished();		
		K2400->activate();

	}else{
		K2400->enableLocal();
		K2400->deactivate();
		lblDcState->setText(hearderMsgFormat("DC source OFF",Qt::gray));
		cmdDcOnOff->setText("OFF");
		ledDc->setGrey();
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpK2400::delay(double i) 
/// \brief	Pause the application for i seconds 
///
/// \param i the number of seconds
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpK2400::delay(double i) 
{
	clock_t start,end;
	start=clock();

	while(((end=clock())-start)<=i*CLOCKS_PER_SEC){
		QCoreApplication::processEvents ();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpK2400::on_dsbDcValue_valueChanged( double d )
///
/// \brief (SLOT) When the [Value] double spin box of the DC bias tab is changed  
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpK2400::on_dsbDcValue_valueChanged( double d ){
	if(chkbxDcRealTime->isChecked()) on_dsbDcValue_editingFinished();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpK2400::on_dsbDcValue_editingFinished(double d)
///
/// \brief (SLOT) When the [Value] double spin box of the DC bias tab is changed  
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpK2400::on_dsbDcValue_editingFinished()
{
	double d = dsbDcValue->value();

	if(ledDc->isGreen()){
		if(radbttDcCurrent->isChecked() && qAbs(dsbDcValue->value()) <= qAbs(dsbDcCurrentMax->value())){
			double var = dsbDcValue->value();
			K2400->setCurrent(dsbDcValue->value()/1000);
			QList<double> VI =  K2400->readVI();

			lblDcCurrent->setText("I = " + QString::number(VI.value(1)*MiliAmp,'f',6) + QString(" mA"));
			lblDcVoltage->setText("V = " + QString::number(VI.value(0)*MiliAmp,'f',6) +  QString(" mV"));

			if(VI.value(1)!= 0){
				lblDcResistance->setText("R = " + QString::number(VI.value(0)/VI.value(1),'f',6) 
					+ QString(" ") + QString(QChar(937)));
			}else{
				lblDcResistance->setText("R = ?.??????? " + QString(QChar(937)));
			}

		}
		if(radbttDcVoltage->isChecked() && dsbDcValue->value() <= dsbDcVoltageMax->value()){
			K2400->setVoltage(dsbDcValue->value()/MiliAmp);
			QList<double> IV =  K2400->readIV();

			lblDcCurrent->setText("I = " + QString::number(IV.value(0)*MiliAmp,'f',6) + QString(" mA"));
			lblDcVoltage->setText("V = " + QString::number(IV.value(1)*MiliAmp,'f',6) + QString(" mA"));

			if(IV.value(0)!= 0){
				lblDcResistance->setText("R = " + QString::number(IV.value(1)/IV.value(0),'f',6) + 
					QString(" ") + QString(QChar(937)));
			}else{
				lblDcResistance->setText("R = ?.??????? " + QString(QChar(937)));
			}

		}

		delay(0.1);
	}
}

