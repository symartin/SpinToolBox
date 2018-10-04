////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUiCpRSSMA100A.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		04/03/20132
///
/// \brief	implement the GUI SUiCpRSSMA100A for the RSSMA100A microwave generator
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
#include "SUiCpRSSMA100A.h"
#include "SDeviceRSSMA100A.h"

#define GHZ 1000000000
#define MHZ 1000000
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn SUiCpRSSMA100A::SUiCpRSSMA100A(QWidget * parent = NULL )
///
/// \brief	constructor
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
SUiCpRSSMA100A::SUiCpRSSMA100A(QWidget * parent ):QWidget(parent)
{
	RSSMA100 = new SDeviceRSSMA100A(this);
	

	// setup ui of the microwave generator tab
	setupUi(this);
	dsbMwFreq->setBaseUnit("Hz");
	dsbMwFreq->setPredigits(3);
	dsbMwFreq->setPostdigits(2);
	dsbMwFreq->setMinimum(9*MHZ);
	dsbMwFreq->setMaximum(20*GHZ);
	dsbMwFreq->setUnitModifiers(true);
	dsbMwFreq->setStepInUnit(true);
	dsbMwFreq->setStep(0.1);
	dsbMwFreq->setValue(100*MHZ);

	dsbMwPower->setBaseUnit("dBm");
	dsbMwPower->setPredigits(3);
	dsbMwPower->setPostdigits(1);
	dsbMwPower->setMinimum(-145);
	dsbMwPower->setMaximum(0);
	dsbMwPower->setUnitModifiers(true);
	dsbMwPower->setStepInUnit(true);
	dsbMwPower->setStep(0.1);

	dsbMwPowerLimit->setBaseUnit("dBm");
	dsbMwPowerLimit->setPredigits(3);
	dsbMwPowerLimit->setPostdigits(1);
	dsbMwPowerLimit->setMinimum(-145);
	dsbMwPowerLimit->setMaximum(0);
	dsbMwPowerLimit->setUnitModifiers(true);
	dsbMwPowerLimit->setStepInUnit(true);
	dsbMwPowerLimit->setStep(0.1);
	dsbMwPowerLimit->setValue(-10);


	// The microwave generator TODO
	if (!RSSMA100->available()){
		ledMw->setRed();
		lblMwState->setText(hearderMsgFormat("The microwave generator is unavailable",Qt::red));
	}else{
		ledMw->setGrey();
		dsbMwPower->setValue(RSSMA100->power());
		dsbMwFreq->setValue(RSSMA100->frequency()*GHZ);

	}

}


SUiCpRSSMA100A::~SUiCpRSSMA100A(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpRSSMA100A::on_cmdMwOnOff_clicked()
/// \brief	(SLOT) When the [Go] button of the microwave generator tab is clicked.
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpRSSMA100A::on_cmdMwGo_clicked(){
	if(!ledMw->isRed() && RSSMA100->available()
		&& cmdMwOnOff->isChecked()){

			if(dsbMwPower->value() < dsbMwPowerLimit->value()){
				RSSMA100->setPower(dsbMwPower->value());
				RSSMA100->setFrequency(dsbMwFreq->value()/GHZ);
			}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpRSSMA100A::on_cmdMwOnOff_clicked()
/// \brief	(SLOT) When the [ON]/[OFF] button of the microwave generator tab is clicked.
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpRSSMA100A::on_cmdMwOnOff_clicked(bool checked ){
	if(ledMw->isRed()){ // on check si le device est tjs indispos
		cmdMwOnOff->setChecked(false);
		cmdMwOnOff->setText("OFF");
		if (RSSMA100->available()){
			lblMwState->setText(hearderMsgFormat("Microwave generator OFF",Qt::gray));
			ledMw->setGrey();
		}
		return;
	}else if(!RSSMA100->available()){ // on check si le device est tjs dispos
		ledMw->setRed();
		cmdMwOnOff->setText("OFF");
		lblMwState->setText(hearderMsgFormat("The Microwave generators is unavailable",Qt::red));
		return;
	}

	if(checked){
		ledMw->setGreen();
		lblMwState->setText(hearderMsgFormat("Microwave generators ON",Qt::darkGreen));
		cmdMwOnOff->setText("ON");

		RSSMA100->setFrequency(dsbMwFreq->value()/GHZ);

		RSSMA100->setPowerLimit( dsbMwPowerLimit->value() );

		if(dsbMwPower->value() < dsbMwPowerLimit->value()){
			RSSMA100->setPower(dsbMwPower->value());
		}

		RSSMA100->activate(true);

	}else{
		RSSMA100->activate(false);
		RSSMA100->enableLocal();
		cmdMwOnOff->setText("OFF");
		lblMwState->setText(hearderMsgFormat("Microwave generators OFF",Qt::gray));
		ledMw->setGrey();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpRSSMA100A::on_dsbMwPower_editingFinished()
/// \brief	(SLOT) when the value of the microwave generator power double spin box changes
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpRSSMA100A::on_dsbMwPower_editingFinished(){
	if(chkbxMwRealTime->isChecked()){
		if(dsbMwPower->value() < dsbMwPowerLimit->value()
			&&  cmdMwOnOff->isChecked()){
			RSSMA100->setPower(dsbMwPower->value());
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void on_dsbMwPower_valueChanged(double d)
/// \brief	(SLOT) when the value of the microwave generator power double spin box changes
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpRSSMA100A::on_dsbMwPower_valueChanged(double d){
	if(chkbxMwRealTime->isChecked()) on_dsbMwPower_editingFinished();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpRSSMA100A::on_dsbMwFreq_editingFinished()
/// \brief	(SLOT) when the value of the microwave generator frequency double spin box changes 
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpRSSMA100A::on_dsbMwFreq_editingFinished(){
	if(chkbxMwRealTime->isChecked()){
		if(!ledMw->isRed() && RSSMA100->available()
			&& cmdMwOnOff->isChecked()){
			RSSMA100->setFrequency(dsbMwFreq->value()/GHZ);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void on_dsbMwFreq_valueChanged(double d)
/// \brief	(SLOT) when the value of the microwave generator frequency double spin box changes 
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpRSSMA100A::on_dsbMwFreq_valueChanged(double d)
{
	if(chkbxMwRealTime->isChecked()) on_dsbMwFreq_editingFinished();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpRSSMA100A::on_dsbMwPowerLimit_editingFinished()
/// \brief	(SLOT) when the value of the microwave generator power limit double spin box changes 
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpRSSMA100A::on_dsbMwPowerLimit_editingFinished(){
	if(!ledMw->isRed() && RSSMA100->available()){
		RSSMA100->setPowerLimit(dsbMwPowerLimit->value());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SUiCpRSSMA100A::hearderMsgFormat( QString msg, QColor color )
///
/// \brief Format a text (font and color) to the header of the form.
///
/// \param msg The text that will be format
/// \param color The color desired.
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SUiCpRSSMA100A::hearderMsgFormat( QString msg, QColor color ){

	QString res =  QString("<p align=\"center\"><span style=\" font-size:16pt; font-weight:600; color:")
		+ color.name() + QString("\">") + msg + QString("</span></p>");

	return res;

}