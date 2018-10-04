#include "SUiCpPSAE4440A.h"
#include <time.h>
#include <math.h>
#include <QtCore>
#include <QtGui>

#include "SDK/SData/SData2D.h"
#include "SDevicePSAE4440A.h"
#include "SDK/SError.h"
#include <SDK/SPlot/SPlot2D.h>
#include <SDK/SUi/QTechSpinBox.h>

#define GHZ 1000000000

#define SDEVICEK2400_SHORT_NAME "Keithley2400"
#define SDEVICEDAQFIELDONEAXIS_SHORT_NAME "DaqFieldOneAxis"
#define SDEVICEPSGE8257D_SHORT_NAME "PSGE8257D"


SUiCpPSAE4440A::SUiCpPSAE4440A(QWidget * parrent):QWidget(parrent)
{
	setupUi(this);
	PSA = new SDevicePSAE4440A(this);

	// setup ui of the spectrum analyzer tab
	dsbSaStopFreq->setBaseUnit("Hz");
	dsbSaStopFreq->setPredigits(3);
	dsbSaStopFreq->setPostdigits(2);
	dsbSaStopFreq->setMinimum(3);
	dsbSaStopFreq->setMaximum(26.5*GHZ);
	dsbSaStopFreq->setUnitModifiers(true);
	dsbSaStopFreq->setSingleStep(0.5);
	dsbSaStopFreq->setStepInUnit(true);

	dsbSaStartFreq->setBaseUnit("Hz");
	dsbSaStartFreq->setPredigits(3);
	dsbSaStartFreq->setPostdigits(2);
	dsbSaStartFreq->setMinimum(3);
	dsbSaStartFreq->setMaximum(26.5*GHZ);
	dsbSaStartFreq->setUnitModifiers(true);
	dsbSaStartFreq->setStepInUnit(true);

	dsbSaMarker->setBaseUnit("Hz");
	dsbSaMarker->setPredigits(3);
	dsbSaMarker->setPostdigits(2);
	dsbSaMarker->setMinimum(1);
	dsbSaMarker->setMaximum(26.5*GHZ);
	dsbSaMarker->setUnitModifiers(true);
	dsbSaMarker->setStepInUnit(true);


	dsbSaRbw->setBaseUnit("Hz");
	dsbSaRbw->setPredigits(3);
	dsbSaRbw->setPostdigits(2);
	dsbSaRbw->setMinimum(1);
	dsbSaRbw->setMaximum(26.5*GHZ);
	dsbSaRbw->setUnitModifiers(true);
	dsbSaRbw->setStepInUnit(true);

/*	dsbSaStopFreq->setDecimals(2);
	dsbSaStopFreq->setMaximum(26.5*GHZ);
	dsbSaStopFreq->setMinimum(3);
	dsbSaStopFreq->setByDecimals(false);
	dsbSaStopFreq->setStep(0.1);

	dsbSaStartFreq->setDecimals(2);
	dsbSaStartFreq->setMaximum(26.5*GHZ);
	dsbSaStartFreq->setMinimum(3);
	dsbSaStartFreq->setByDecimals(false);
	dsbSaStartFreq->setStep(0.1);

	dsbSaRbw->setDecimals(2);
	dsbSaRbw->setMaximum(26.5*GHZ);
	dsbSaRbw->setMinimum(1);
	dsbSaRbw->setByDecimals(false);
	dsbSaRbw->setStep(0.1);*/

	for (int i=0; i<=70; i+=2){
		cmbxSaAttenuation->addItem(QString::number(i) + QString(" db"));
	}

	QString tips = "Name of the file (without the extension), with the auto tag :\n";
	tips += "    %I the current (en mA)\n";
	tips += "    %H the field (en Vc)\n";
	tips += "    %V the voltage (en V)\n";
	tips += "    %R the resistance (en Ohm)\n";
	tips += "    %F the microwave generator frequency (en GHz)\n";
	tips += "    %P the microwave generator power (en dBm)";

	txtSaFileName->setToolTip(tips);

	// Spectrum analyzer PSA E4440A 
	if (!PSA->available()){
		lblSaState->setText(hearderMsgFormat("The spectrum analyzer is unavailable",Qt::red));
		ledSa->setRed();
	}else{
		ledSa->setYellow();

		dsbSaStopFreq->setValue(PSA->freqStop()*GHZ);
		dsbSaStartFreq->setValue(PSA->freqStart()*GHZ);
		dsbSaRbw->setValue(PSA->rbw()*GHZ);
		dsbSaNbPoints->setValue(PSA->nbPoints());

		cmbxSaAttenuation->setCurrentIndex(PSA->attenuation()/2);
		dsbSaLevel->setValue(PSA->refLevel());
		dsbSaAverage->setValue(PSA->nbAverage());

		dsbSaMarker->setMaximum(dsbSaStopFreq->value());
		dsbSaMarker->setMinimum(dsbSaStartFreq->value());

		chkbxSaLog->setChecked(false);
		//chkbxSaLog

		ledSa->setGreen();
	}		

	connect(dsbSaStartFreq,SIGNAL(valueChanged(double)),dsbSaMarker,SLOT(setMinimum(double)));
	connect(dsbSaStopFreq,SIGNAL(valueChanged(double)),dsbSaMarker,SLOT(setMaximum(double)));
}


SUiCpPSAE4440A::~SUiCpPSAE4440A(void)
{
	delete PSA;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCmdMan::on_cmdSaMeasure_clicked()
/// \brief	(SLOT) take a measurement with the spectrum analyzer
///
/// \remark it is here that the shortcut for the name of the file (%H %I ...) is defined with the 
///		global metadata system
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpPSAE4440A::on_cmdSaMeasure_clicked(){

	QString I;
	QString V;
	QString R;
	QString H;
	QString P;
	QString F;
	
	// if no valid path, goodbye !
	QFileInfo dir(txtSaTargetFolder->text());
	if (!(dir.isDir())){
		QMessageBox::warning(this, "SpinTollBox - Error", "The directory is not valid.", QMessageBox::Ok, NULL);
		return;
	}else if (!dir.isWritable()){
		QMessageBox::warning(this, "SpinTollBox - Error", "You must have write permission to the output directory.", QMessageBox::Ok, NULL);
		return;	
	}

	if (ledSa->isGreen()){
		//on measure at once !
		ledSa->setYellow();

		// on force le chargement une fois, et on le block
		gmdm.MetaDataExist(SDEVICEK2400_SHORT_NAME,"available");
		gmdm.stopReload(true);

		// Pour le K2400 **********************************************************
		if (gmdm.MetaDataExist(SDEVICEK2400_SHORT_NAME,"available")
			&& gmdm.MetaData(SDEVICEK2400_SHORT_NAME,"available").value().toBool()
			&& gmdm.MetaData(SDEVICEK2400_SHORT_NAME,"activate").value().toBool()){

				double dI = gmdm.MetaData(SDEVICEK2400_SHORT_NAME,"I").value().toDouble();
				double dV = gmdm.MetaData(SDEVICEK2400_SHORT_NAME,"V").value().toDouble();
				I=QString::number(dI,'f',4);
				V=QString::number(dV,'f',4);

				if(dI!= 0)
					R=QString::number(dV/dI,'f',2);
				else
					R="Nan";	
		}else{
			R="Nan";	
			V="00.00";	
			I="00.00";	
		}

		// Pour le champ **********************************************************
		if (gmdm.MetaDataExist(SDEVICEDAQFIELDONEAXIS_SHORT_NAME,"available")
			&& gmdm.MetaData(SDEVICEDAQFIELDONEAXIS_SHORT_NAME,"available").value().toBool()){
				H = QString::number(gmdm.MetaData(SDEVICEDAQFIELDONEAXIS_SHORT_NAME,"Vfield").value().toDouble(),'f',2);
		}else{
			H="00.00";
		}

		// Pour le MW **********************************************************	
		if (gmdm.MetaDataExist(SDEVICEPSGE8257D_SHORT_NAME,"available")
			&& gmdm.MetaData(SDEVICEPSGE8257D_SHORT_NAME,"available").value().toBool()
			&& gmdm.MetaData(SDEVICEPSGE8257D_SHORT_NAME,"activate").value().toBool()){

			P = QString::number(gmdm.MetaData(SDEVICEPSGE8257D_SHORT_NAME,"power").value().toDouble(),'f',2);
			F = QString::number(gmdm.MetaData(SDEVICEPSGE8257D_SHORT_NAME,"frequency").value().toDouble(),'f',6);
		}else{
			P="-00.00";
			F="00.000000";
		}

		// on redemare le chargement automatique
		gmdm.stopReload(false);

		// setup the spectrum analyzer
		on_cmdSaGo_clicked();

		// lets go !
		SData2D * data = PSA->readSpectrum(); 


		// we format the metadata
		if(R != "Nan") data->setMetaData("R",R);
		data->setMetaData("I",I);
		data->setMetaData("V",V);
		if(H != "Nan") data->setMetaData("H",H);

		data->setMetaData("Attenuation",cmbxSaAttenuation->currentText());
		data->setMetaData("RBW",dsbSaRbw->value());
		data->setMetaData("Attenuation",cmbxSaAttenuation->currentText());
		data->setMetaData("NbAverage",dsbSaAverage->value());
		data->setMetaData("sweepTime",PSA->sweepTime()*1000);

		//get current date
		QDate date = QDate::currentDate();
		data->setMetaData("Date" , date.toString("dd MMMM yyyy"));

		//get current time
		QTime time = QTime::currentTime();
		data->setMetaData("Time" , time.toString());

		data->addComment("Measurement done by the control pannel of SpinTollBox");
		data->addComment(txtSaComments->text());
		data->setColName("Frequency","Voltage");
		data->setColUnit("GHz","V");

		/*
		we format the name
		Name of the file, with the auto tag :
		%I the current (en mA)
		%H the field (en Vc)
		%V the voltage (en V)
		%R the resistance (en Ohm)
		%F the microwave generator frequency (en GHz)
		%P the microwave generator power (en dBm)
		*/
		
		QString name = txtSaFileName->text();
		name.replace("%I",I,Qt::CaseInsensitive);
		name.replace("%H",H,Qt::CaseInsensitive);
		name.replace("%V",V,Qt::CaseInsensitive);
		name.replace("%R",R,Qt::CaseInsensitive);
		name.replace("%F",F,Qt::CaseInsensitive);
		name.replace("%P",P,Qt::CaseInsensitive);
		name.replace("%%","%",Qt::CaseInsensitive);
		name.replace("%DATE%",date.toString("yyyyMMdd"),Qt::CaseInsensitive);
		name.replace("%TIME%",time.toString("hh-mm-ss"),Qt::CaseInsensitive);

		QString shortName = name;
		name = name + ".spectre.stb";
		name = txtSaTargetFolder->text() + "\\" + name;

		// we write the file
		QFileInfo file(name);

		if (file.exists()){
			// the file exist, we ask if we overwrite it
			int ret = QMessageBox::question(this, "Error",
				"The file already exist, do you want overwrite it?", 
				QMessageBox::Yes,QMessageBox::No);

			if(ret == QMessageBox::No){
				//no so goodbye!
				ledSa->setGreen();
				return;
			}
		}

		//we write the file
		data->saveFile(name);

		SPlot2D * plot = new SPlot2D(this);
		plot->setWindowTitle(shortName + "- SpinToolBox");
		plot->setData(data);
		plot->show();
		//it's finished
		ledSa->setGreen();


	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCmdMan::on_dsbMwFreq_valueChanged()
/// \brief	(SLOT) when the value of the microwave generator power limit double spin box changes 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_cmdSaAskRbw_clicked()
{
	double rbw = (dsbSaStopFreq->value() - dsbSaStartFreq->value())/(double)dsbSaNbPoints->value();
	dsbSaRbw->setValue(rbw);
	on_cmdSaCheckRbw_clicked();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_dsbSaStopFreq_valueChanged( double d )
///
/// \brief (SLOT) when the value of the [Stop Frequency] double spin box is changed 
//					(in the Spectrum Analyzer).
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_dsbSaStopFreq_valueChanged( double d ){

	sldSaMarker->setMaximum(d/50.0);

	if (ledSa->isGreen() && chkbxSaRealTime->isChecked()){
		PSA->setFreqStop(dsbSaStopFreq->value()/GHZ);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_dsbSaStopFreq_valueChanged( double d )
///
/// \brief (SLOT) when the value of the [Start Frequency] double spin box is changed 
//					(in the Spectrum Analyzer).
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_dsbSaStartFreq_valueChanged( double d ){
	sldSaMarker->setMinimum(d/50.0);

	if (ledSa->isGreen() && chkbxSaRealTime->isChecked()){
		PSA->setFreqStop(dsbSaStartFreq->value()/GHZ);
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_dsbSaRbw_valueChanged( double d )
///
/// \brief (SLOT) when the value of the [RBW] double spin box is changed 
//					(in the Spectrum Analyzer).
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_dsbSaRbw_valueChanged( double d ){

	if (ledSa->isGreen() && chkbxSaRealTime->isChecked()){

		ledSa->setYellow();
		PSA->setRbw(dsbSaRbw->value()/GHZ);

		delay(0.3);
		// on met la valeur efective du rbw choisit par l'analyseur car toute les valeur ne sont pas compatible
		double rbw1= PSA->rbw();
		double rbw2= dsbSaRbw->value();
		if(fabs(PSA->rbw() - dsbSaRbw->value()*GHZ) >0.00000001){
			cmdSaCheckRbw->setIcon(QIcon(":icon/cross.png"));
		}else{
			cmdSaCheckRbw->setIcon(QIcon(":icon/check.png"));
		}

		ledSa->setGreen();
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_cmdSaCheckRbw_clicked()
///
/// \brief (SLOT) when the value of the [check] (close to the rbw double spin box) is clicked
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_cmdSaCheckRbw_clicked(){
	if (ledSa->isGreen()){

		ledSa->setYellow();
		double rbw2 =dsbSaRbw->value()/GHZ;
		PSA->setRbw(dsbSaRbw->value()/GHZ);

		delay(0.3);
		double rbw1	=PSA->rbw();
		dsbSaRbw->setValue(PSA->rbw()*GHZ);
		cmdSaCheckRbw->setIcon(QIcon(":icon/check.png"));
		ledSa->setGreen();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_dsbSaAverage_valueChanged( int i )
///
/// \brief (SLOT) when the value of the [Average] changed
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_dsbSaAverage_valueChanged( int i ){
	if (ledSa->isGreen() && chkbxSaRealTime->isChecked()){
		PSA->setNbAverage(dsbSaAverage->value());
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_dsbSaNbPoints_valueChanged( int i )
///
/// \brief (SLOT) when the value of the [Number of Points] changed
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_dsbSaNbPoints_valueChanged( int i ){
	if (ledSa->isGreen() && chkbxSaRealTime->isChecked()){
		PSA->setNbPoints(dsbSaNbPoints->value());
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_dsbSaLevel_valueChanged( double d )
///
/// \brief (SLOT) when the value of the [ref level] changed
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_dsbSaLevel_valueChanged( double d ){
	if (ledSa->isGreen() && chkbxSaRealTime->isChecked()){
		PSA->setRefLevel(dsbSaLevel->value());
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_cmbxSaAttenuation_currentIndexChanged( const QString & text )
///
/// \brief (SLOT) when the value of the [Attenuation] changed
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_cmbxSaAttenuation_currentIndexChanged( const QString & text ){
	if (ledSa->isGreen() && chkbxSaRealTime->isChecked()){
		PSA->setAttenuation(text.left(text.length()-3).toInt());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_chkbxSaMarkerOnOff_stateChanged( int state )
///
/// \brief (SLOT) when the value check box of the marker is clicked (activate or deactivate the marker)
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_chkbxSaMarkerOnOff_stateChanged( int state ){

	if (ledSa->isGreen()){

		if(state){
			PSA->marker(true,1);
		}else{
			PSA->marker(false,1);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_dsbSaMarker_valueChanged( double d )
///
/// \brief (SLOT) when the value of the double spin box of the marker is changed
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_dsbSaMarker_valueChanged( double d ){

	sldSaMarker->setValue(d/50.0); // le QSlider ne suporte pas les valeurs < 9.0e+9
	if (ledSa->isGreen() && chkbxSaMarkerOnOff->isChecked()){
		PSA->setMarker(d/GHZ, 1);
		delay(0.01);
		lblSaMarker->setText("M = " + QString::number(PSA->readMarker(1)*1000) + " mV");
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_sldSaMarker_sliderMoved( int d )
///
/// \brief (SLOT) when the value Slider of the marker is moved
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_sldSaMarker_sliderMoved( int d ){
	dsbSaMarker->setValue(d*50.0);

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_cmdSaGo_clicked()
///
/// \brief (SLOT) when the [GO] button is clicked, update all the settings of the spectrum analyzer
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_cmdSaGo_clicked(){

	if (ledSa->isRed() && PSA->available()){

		ledSa->setGreen();
		lblSaState->setText(hearderMsgFormat("The spectrum analyzer ON",Qt::darkGreen));
		return;

	}else if (!PSA->available()){
		ledSa->setRed();
		lblSaState->setText(hearderMsgFormat("The spectrum analyzer is unavailable",Qt::red));
		return;
	}

	if (ledSa->isGreen()){

		ledSa->setYellow();
		PSA->setAttenuation(cmbxSaAttenuation->currentText().left(cmbxSaAttenuation->currentText().length()-3).toInt());
		delay(0.2);
		PSA->setRefLevel(dsbSaLevel->value());
		delay(0.2);
		PSA->setNbPoints(dsbSaNbPoints->value());
		delay(0.2);
		PSA->setRbw(dsbSaRbw->value()/GHZ);
		delay(0.2);
		PSA->setFreqStart(dsbSaStartFreq->value()/GHZ);
		delay(0.2);
		PSA->setFreqStop(dsbSaStopFreq->value()/GHZ);
		delay(0.2);
		PSA->setNbAverage(dsbSaAverage->value());
		delay(0.2);
		dsbSaRbw->setValue(PSA->rbw()*GHZ);

		ledSa->setGreen();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpPSAE4440A::on_cmdSaGo_clicked()
///
/// \brief	Handles command Max clicked signals.
///
/// \author	Sylvain Martin
/// \date	25/02/2013
////////////////////////////////////////////////////////////////////////////////////////////////////

void SUiCpPSAE4440A::on_cmdSaMax_clicked()
{
	chkbxSaMarkerOnOff->setChecked(true);
	SDevicePSAE4440A::Point2D res = PSA->MaxSearch();
	dsbSaMarker->setValue(res.x);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpPSAE4440A::on_chkbxSaLog_stateChanged( int state )
///
/// \brief when the state of the check box log/lin change
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_chkbxSaLog_stateChanged( int state )
{
	PSA->setLogDisplay(state);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCmdMan::on_cmdSaGo_clicked()
///
/// \brief (SLOT) when the [...] (target folder) button is clicked, update all the settings of the spectrum analyzer
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCpPSAE4440A::on_cmdSaTargetFolder_clicked()
{
	QString	path = QFileDialog::getExistingDirectory ( this,"Choose a script file", QApplication::applicationDirPath ()); 
	txtSaTargetFolder->setText(path);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SUiCpPSAE4440A::delay(double i) 
/// \brief	Pause the application for i seconds 
///
/// \param i the number of seconds
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SUiCpPSAE4440A::delay(double i) 
{
	clock_t start,end;
	start=clock();

	while(((end=clock())-start)<=i*CLOCKS_PER_SEC){
		QCoreApplication::processEvents ();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCpPSAE4440A::hearderMsgFormat( QString msg, QColor color )
///
/// \brief Format a text (font and color) to the header of the form.
///
/// \param msg The text that will be format
/// \param color The color desired.
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SUiCpPSAE4440A::hearderMsgFormat( QString msg, QColor color ){

	QString res =  QString("<p align=\"center\"><span style=\" font-size:16pt; font-weight:600; color:")
		+ color.name() + QString("\">") + msg + QString("</span></p>");

	return res;

}

