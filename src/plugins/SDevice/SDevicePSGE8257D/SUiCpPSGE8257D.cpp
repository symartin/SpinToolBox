#include "SUiCpPSGE8257D.h"
#include "SDevicePSGE8257D.h"

#define GHZ 1000000000
#define MHZ 1000000
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn SUiCpPSGE8257D::SUiCpPSGE8257D(QWidget * parent = NULL )
///
/// \brief	constructor
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
SUiCpPSGE8257D::SUiCpPSGE8257D(QWidget * parent ):QWidget(parent)
{
	PSGE = new SDevicePSGE8257D(this);
	

	// setup ui of the microwave generator tab
	setupUi(this);
	dsbMwFreq->setBaseUnit("Hz");
	dsbMwFreq->setPredigits(3);
	dsbMwFreq->setPostdigits(2);
	dsbMwFreq->setMinimum(10*MHZ);
	dsbMwFreq->setMaximum(20*GHZ);
	dsbMwFreq->setUnitModifiers(true);
	dsbMwFreq->setStepInUnit(true);
	dsbMwFreq->setStep(0.1);
	dsbMwFreq->setValue(100*MHZ);

	dsbMwPower->setBaseUnit("dBm");
	dsbMwPower->setPredigits(3);
	dsbMwPower->setPostdigits(1);
	dsbMwPower->setMinimum(-135);
	dsbMwPower->setMaximum(0);
	dsbMwPower->setUnitModifiers(true);
	dsbMwPower->setStepInUnit(true);
	dsbMwPower->setStep(0.1);

	dsbMwPowerLimit->setBaseUnit("dBm");
	dsbMwPowerLimit->setPredigits(3);
	dsbMwPowerLimit->setPostdigits(1);
	dsbMwPowerLimit->setMinimum(-135);
	dsbMwPowerLimit->setMaximum(0);
	dsbMwPowerLimit->setUnitModifiers(true);
	dsbMwPowerLimit->setStepInUnit(true);
	dsbMwPowerLimit->setStep(0.1);
	dsbMwPowerLimit->setValue(-10);


	// The microwave generator PSG E8257D
	if (!PSGE->available()){
		ledMw->setRed();
		lblMwState->setText(hearderMsgFormat("The microwave generator is unavailable",Qt::red));
	}else{
		ledMw->setGrey();
		dsbMwPower->setValue(PSGE->power());
		dsbMwFreq->setValue(PSGE->frequency()*GHZ);

	}

}


SUiCpPSGE8257D::~SUiCpPSGE8257D(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpPSGE8257D::on_cmdMwOnOff_clicked()
/// \brief	(SLOT) When the [Go] button of the microwave generator tab is clicked.
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpPSGE8257D::on_cmdMwGo_clicked(){
	if(!ledMw->isRed() && PSGE->available()
		&& cmdMwOnOff->isChecked()){

			if(dsbMwPower->value() < dsbMwPowerLimit->value()){
				PSGE->setPower(dsbMwPower->value());
				PSGE->setFrequency(dsbMwFreq->value()/GHZ);
			}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpPSGE8257D::on_cmdMwOnOff_clicked()
/// \brief	(SLOT) When the [ON]/[OFF] button of the microwave generator tab is clicked.
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpPSGE8257D::on_cmdMwOnOff_clicked(bool checked ){
	if(ledMw->isRed()){ // on check si le device est tjs indispos
		cmdMwOnOff->setChecked(false);
		cmdMwOnOff->setText("OFF");
		if (PSGE->available()){
			lblMwState->setText(hearderMsgFormat("Microwave generator OFF",Qt::gray));
			ledMw->setGrey();
		}
		return;
	}else if(!PSGE->available()){ // on check si le device est tjs dispos
		ledMw->setRed();
		cmdMwOnOff->setText("OFF");
		lblMwState->setText(hearderMsgFormat("The Microwave generators is unavailable",Qt::red));
		return;
	}

	if(checked){
		ledMw->setGreen();
		lblMwState->setText(hearderMsgFormat("Microwave generators ON",Qt::darkGreen));
		cmdMwOnOff->setText("ON");

		PSGE->setFrequency(dsbMwFreq->value()/GHZ);

		PSGE->setPowerLimit( dsbMwPowerLimit->value() );

		if(dsbMwPower->value() < dsbMwPowerLimit->value()){
			PSGE->setPower(dsbMwPower->value());
		}

		PSGE->activate(true);

	}else{
		PSGE->activate(false);
		PSGE->enableLocal();
		cmdMwOnOff->setText("OFF");
		lblMwState->setText(hearderMsgFormat("Microwave generators OFF",Qt::gray));
		ledMw->setGrey();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpPSGE8257D::on_dsbMwPower_editingFinished()
/// \brief	(SLOT) when the value of the microwave generator power double spin box changes
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpPSGE8257D::on_dsbMwPower_editingFinished(){
	if(chkbxMwRealTime->isChecked()){
		if(dsbMwPower->value() < dsbMwPowerLimit->value()
			&&  cmdMwOnOff->isChecked()){
			PSGE->setPower(dsbMwPower->value());
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void on_dsbMwPower_valueChanged(double d)
/// \brief	(SLOT) when the value of the microwave generator power double spin box changes
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpPSGE8257D::on_dsbMwPower_valueChanged(double d){
	if(chkbxMwRealTime->isChecked()) on_dsbMwPower_editingFinished();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpPSGE8257D::on_dsbMwFreq_editingFinished()
/// \brief	(SLOT) when the value of the microwave generator frequency double spin box changes 
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpPSGE8257D::on_dsbMwFreq_editingFinished(){
	if(chkbxMwRealTime->isChecked()){
		if(!ledMw->isRed() && PSGE->available()
			&& cmdMwOnOff->isChecked()){
			PSGE->setFrequency(dsbMwFreq->value()/GHZ);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void on_dsbMwFreq_valueChanged(double d)
/// \brief	(SLOT) when the value of the microwave generator frequency double spin box changes 
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpPSGE8257D::on_dsbMwFreq_valueChanged(double d)
{
	if(chkbxMwRealTime->isChecked()) on_dsbMwFreq_editingFinished();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpPSGE8257D::on_dsbMwPowerLimit_editingFinished()
/// \brief	(SLOT) when the value of the microwave generator power limit double spin box changes 
///
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpPSGE8257D::on_dsbMwPowerLimit_editingFinished(){
	if(!ledMw->isRed() && PSGE->available()){
		PSGE->setPowerLimit(dsbMwPowerLimit->value());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SUiCpPSGE8257D::hearderMsgFormat( QString msg, QColor color )
///
/// \brief Format a text (font and color) to the header of the form.
///
/// \param msg The text that will be format
/// \param color The color desired.
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SUiCpPSGE8257D::hearderMsgFormat( QString msg, QColor color ){

	QString res =  QString("<p align=\"center\"><span style=\" font-size:16pt; font-weight:600; color:")
		+ color.name() + QString("\">") + msg + QString("</span></p>");

	return res;

}