////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevicePSAE4440A.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		14/03/2011
///
/// \brief	Implants the class and the plugin corresponding to SDevicePSAE4440A
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

#include "SDK/SError.h"
#include "SDKDevice/SDevice/SDeviceError.h"
#include "SDKDevice/SDevice/SDeviceGpib.h"

#include "SDevicePSAE4440A.h"
#include "SUiCpPSAE4440A.h"

#include "SDK/SData/SData2D.h"
#include "SDK/SData/SData2DScript.h"

#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>
#include <QStringList>
#include <QList>


#define GHZ 1000000000
#define MHZ 1000000
#define KHZ 1000

/*****************************************************************************************************/
/*										SDevicePSAE4440APlugin                                       */
/*****************************************************************************************************/

#include <QtCore>

Q_EXPORT_PLUGIN2("SDevicePSAE4440APlugin", SDevicePSAE4440APlugin)


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDevicePSGE8257D::SDevicePSGE8257D()
///
/// \brief	constructor
///
/// \author	Sylvain Martin
/// \date	01/12/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
SDevicePSAE4440APlugin::SDevicePSAE4440APlugin():state_(2),PSAE4440A(NULL)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDevicePSGE8257D::~SDevicePSGE8257D()
///
/// \brief	destructor
///
/// \author	Sylvain Martin
/// \date	01/12/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
SDevicePSAE4440APlugin::~SDevicePSAE4440APlugin()
{
	if(PSAE4440A!=NULL)
		delete PSAE4440A;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::load()
///
/// \brief	initialize the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSAE4440APlugin::load()
{
	//GlobalMetaDataMap_ = GlobalMetaDataMap;
	PSAE4440A = new SDevicePSAE4440A(this);

	if(PSAE4440A->available()) state_=0;
	return PSAE4440A->available();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400::name() const
///
/// \brief	return the complete name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSAE4440APlugin::name() const
{
	return QString("Agilent Technologies, PSA Series Spectrum Analyzer E4440A");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400::shortName() const
///
/// \brief	return the short name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the short name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSAE4440APlugin::shortName() const
{
	return QString(SDEVICEPSAE4440A_SHORT_NAME);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400::description() const
///
/// \brief	return the description of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the description of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSAE4440APlugin::description() const
{
	QString des	=  "The Agilent E4440A PSA high-performance spectrum analyzer measures and monitors complex RF and";
	des	+= "microwave signals up to 26.5 GHz. With optional external mixing, the frequency coverage expands";
	des	+= "to 110 GHz by Agilent external mixer, and to 325 GHz by other vendors' mixer.";

	return des;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::scriptable( QScriptEngine * engine )
///
/// \brief	add (or not) some functions to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::scriptable
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSAE4440APlugin::scriptable( QScriptEngine * engine )
{
	static bool initialized = false;

	if(!initialized){ // evite le multi initialitation
		try{
			initialized = true;
			SDevicePSAE4440A*	PSAE4440A = new SDevicePSAE4440A();

			QScriptValue qsvSDevicePSAE4440A = engine->newQObject(PSAE4440A,QScriptEngine::ScriptOwnership);
			engine->globalObject().setProperty("PSAE4440A", qsvSDevicePSAE4440A);
			engine->evaluate("PSAE4440A.ReadSpectrum = PSAE4440A.qsReadSpectrum;\n","Initialization");

		}catch(SError error){

			initialized = false;
			engine->evaluate("var PSAE4440A = new Object(); PSAE4440A.available = false;","Initialization");
			qDebug()  <<" ERROR (LOW): initialization of the Agilent PSAE4440A's script object failed" 
				<< error;
			return false;

		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::isScriptable()
///
/// \brief	does the plugin add some function to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSAE4440APlugin::isScriptable()
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::isControlPanel()
///
/// \brief	does the plugin add a tab to the control panel to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSAE4440APlugin::isControlPanel()
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400::controlPanel() const
///
/// \brief	add (or not) a tab to the control panel 
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isControlPanel
///
/// \remark SDevicePSGE8257D do not manage the destruction of the object, so you ave to define a parent
///			or destroy it your self 
////////////////////////////////////////////////////////////////////////////////////////////////////
QWidget * SDevicePSAE4440APlugin::controlPanel(QWidget * parent /*= NULL*/)
{

	QWidget * CtrlPanel = new SUiCpPSAE4440A(parent);
	return CtrlPanel;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDevicePSGE8257D::isSetting()
///
/// \brief	does the plugin have a setting window ?
///
/// \author	Sylvain Martin
/// \date	25/02/2012
/// \sa SDevicePSGE8257D::controlPanel
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSAE4440APlugin::isSetting()
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QWidget* SDeviceApsin20gPlugin::controlPanel() 
///
/// \brief	give (or not) a setting window.
///
/// \author	Sylvain Martin
/// \date	25/01/2012
///
/// \param engine the script engine
/// \sa SDeviceApsin20gPlugin::isSetting
///
/// \remark SDeviceApsin20gPlugin do not manage the destruction of the object, so you ave to define a parent
///			or destroy it your self 
////////////////////////////////////////////////////////////////////////////////////////////////////
QWidget * SDevicePSAE4440APlugin::setting(QWidget * parrent /*= NULL*/ )
{
	QWidget * widSetting = new QWidget(parrent); //!TODO ALL !!!
	return widSetting;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::shutdown()
///
/// \brief	shutdown the plugin (by example before closing the application)
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isControlPanel
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440APlugin::shutdown()
{
	//PSAE4440A->deactivate();
	state_=2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SDeviceK2400::state()
///
/// \brief	what is the state of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// 0 : ready, 1 : busy, 2 unavailable
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDevicePSAE4440APlugin::state()
{
	return state_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::available()
///
/// \brief	is the plugin available
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSAE4440APlugin::available()
{
	return PSAE4440A->available();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257D::plgVersion() const
///
/// \brief	return the version of the SDK that is needed for run the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSAE4440APlugin::plgVersion() const
{
	return QString::number(SDEVICEPSAE4440A_VERSION);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257D::plgVersion() const
///
/// \brief	return the version of the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSAE4440APlugin::SDKVersion() const 
{
	return QString::number(SDEVICEPSAE4440A_MAJOR_VERSION_COMPATIBILITY) + 
		QString(".") + QString::number(SDEVICEPSAE4440A_MINOR_VERSION_COMPATIBILITY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257D::plgVersion() const
///
/// \brief	this function is call when the plugin is unload
///
/// \author	Sylvain Martin
/// \date	13/01/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSAE4440APlugin::unload()
{
	qDebug()  <<" WARNING: unloading of the Agilent PSAE4440A's script object failed \n" ;
	qDebug()  <<" \t because the function is not implanted yet\n" ;

	return true;
}



/*****************************************************************************************************/
/*										SDevicePSAE4440A                                             */
/*****************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDevicePSAE4440A::SDevicePSAE4440A()
///
/// \brief	Default constructor. 
///
/// \author	Sylvain Martin
/// \date	1/26/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
SDevicePSAE4440A::SDevicePSAE4440A(QObject *parent)  : 
 metaDataOnOff_(true) {

	init();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDevicePSAE4440A::SDevicePSAE4440A(double FreqStart, double FreqStop, double RBW,
/// int average, QObject *parent)
///
/// \brief	Constructor. 
///
/// \author	Sylvain Martin
/// \date	1/27/2011
///
/// \param	FreqStart		The start frequency . 
/// \param	FreqStop		The stop frequency . 
/// \param	RBW				The resolution of bandwidth. 
/// \param	average			The average( optional, by default 0). 
/// \param [in,out]	parent	If non-null, the Qt parent. 
////////////////////////////////////////////////////////////////////////////////////////////////////
SDevicePSAE4440A::SDevicePSAE4440A(double const FreqStart, double const FreqStop, double const RBW, int const average, QObject *parent): 
 metaDataOnOff_(true){

	init();
	setFreqStart(FreqStart);
	setFreqStop(FreqStop);
	setRbw(RBW);
	setNbAverage(average);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::init(void)
///
/// \brief	Initializes the PSA E4440A device. 
///
/// this function is automatically call at the initialization of this object
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::init(void){
	try{
		gpib_ =  SInterfaceGpib::instance();
		elmt_= gpib_->findGpibElement(QString("Agilent Technologies, E4440A"));

		if (!(elmt_.PAD ==-1)) available_ = true;


	}catch(SError error){
		if (!(error == SDEVICEERROR_GPIB_FINDLSTN)){
			SError::traitement(this,error);	
		}else{

			this->setUnavailable();
			//	qDebug() << "\nAgilent PSAE4440A not found.\n";
		}

	}

	setMetaData( "freqStart", "N/A","GHz" ,SMetaData::doublefloat );
	setMetaData( "freqStop", "N/A","GHz" ,SMetaData::doublefloat );
	setMetaData( "rbw", "N/A","GHz" ,SMetaData::doublefloat );
	setMetaData( "attenuation","N/A","dB" ,SMetaData::doublefloat );
	setMetaData( "nbPoints", "N/A","" ,SMetaData::doublefloat );
	setMetaData( "nbAverage", "N/A" ,"",SMetaData::doublefloat );
	setMetaData( "refLevel", "N/A" ,"dBm",SMetaData::doublefloat );
	setMetaData( "nbAverage", "N/A","",SMetaData::doublefloat );
	setMetaData( "available", "N/A","",SMetaData::boolean );
	setMetaData("LogDisplay", "N/A" ,"",SMetaData::boolean );

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDevicePSAE4440A::~SDevicePSAE4440A()
///
/// \brief	Destructor. 
////////////////////////////////////////////////////////////////////////////////////////////////////
SDevicePSAE4440A::~SDevicePSAE4440A() {
	// TODO Auto-generated destructor stub
	gmdm_.clear(SDEVICEPSAE4440A_SHORT_NAME);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the start frequency. 
///
/// \param	freq The frequency in GHz. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::setFreqStart(double const freq) {
	QString cmd;

	try{
		cmd = QString("FREQ:STAR ") + QString::number(freq) + QString(" GHZ");
		setMetaData( "freqStart", freq,"GHz" ,SMetaData::doublefloat );
		gpibSend(cmd);
	}catch(SError error){
		SError::traitement(this,error);
	}


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDevicePSAE4440A::freqStart()
///
/// \brief	(SCRIPTABLE) Gets the start frequency. 
/// 
/// \exception SDEVICEERROR_CANNOT_CONVERT_DATA Thrown when the recived data cannot be convert.
/// 
/// \return	the start frequency in GHz, if error 0. 
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSAE4440A::freqStart() {

	try{
		gpibSend("FREQ:STAR?");
		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			double f = read.toDouble()/1.0E9;;
			setMetaData( "freqStart", f,"GHz" ,SMetaData::doublefloat );
			return f; // sinon on ne peut pas convertir les nombre de la forme 0.0E0 == 0 !!
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}
	}catch(SError error){
		SError::traitement(this,error);
		return 0.0;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::setFreqStop(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the stop frequency. 
///
///
/// \param	freq The frequency in GHz. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::setFreqStop(double const freq) {

	QString cmd;

	try{
		cmd = QString("FREQ:STOP ") + QString::number(freq) + QString(" GHZ");
		setMetaData( "freqStop", freq,"GHz" ,SMetaData::doublefloat );
		gpibSend(cmd);
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDevicePSAE4440A::freqStop()
///
/// \brief	(SCRIPTABLE) Gets the stop frequency. 
///
/// \return	the stop frequency in GHz, if error 0. 
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSAE4440A::freqStop(){

	try{
		gpibSend("FREQ:STOP?");
		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			double f = read.toDouble()/1.0E9;;
			setMetaData( "freqStop", f ,"GHz",SMetaData::doublefloat );
			return f; // sinon on ne peut pas convertir les nombre de la forme 0.0E0 == 0 !!
 		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}
	}catch(SError error){
		SError::traitement(this,error);
		return 0.0;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::setRbw(double const RBW)
///
/// \brief	(SCRIPTABLE) Sets the resolution de Bandwith. 
///
/// \param	RBW	The resolution de Bandwith in GHz. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::setRbw(double const RBW) {

	QString cmd;

	try{

		if (RBW< 1/KHZ){
			cmd = QString("BAND ") + QString::number(RBW, 'f') + QString(" GHZ");
		}else{ // for the small RBW, avoid the cmd == 0.000000 GHZ
			cmd = QString("BAND ") + QString::number(RBW*GHZ, 'f') + QString(" HZ");
		}
		setMetaData( "rbw", RBW,"GHz" ,SMetaData::doublefloat );
		gpibSend(cmd);
	}catch(SError error){
		SError::traitement(this,error);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDevicePSAE4440A::rbw()
///
/// \brief	(SCRIPTABLE) Gets the resolution de Bandwith.
/// 
/// \exception SDEVICEERROR_CANNOT_CONVERT_DATA Thrown when the recived data cannot be convert.
/// 
/// \return	the resolution de Bandwith in GHz, if error 0.0. 
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSAE4440A::rbw(){

	try{
		gpibSend("BAND?");
		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			double rbw_ = read.toDouble()/1.0E9;

			setMetaData( "rbw", rbw_, "GHz", SMetaData::doublefloat );
			return rbw_; // sinon on ne peut pas convertir les nombre de la forme 0.0E0 == 0 !!

			return read.toDouble()/1.0E9;
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}
	}catch(SError error){
		SError::traitement(this,error);
		return 0.0;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::setAttenuation(double const Att)
///
/// \brief	(SCRIPTABLE) Sets the attenuation. 
/// 
/// \exception SDEVICEERROR_CANNOT_CONVERT_DATA Thrown when the recived data cannot be convert.
/// 
/// \param	Att	The Attenuation in dB. 
/// \remark all the atenuation is not possible.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::setAttenuation(int const Att) {
	QString cmd;

	try{
		cmd = QString("POW:ATT ") + QString::number(Att) + QString(" dB");
		gpibSend(cmd);
		setMetaData( "attenuation", Att,"dB" ,SMetaData::doublefloat );
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE virtual double SDevicePSAE4440A::attenuation(void)
///
/// \brief	Gets the attenuation. 
/// 
/// \exception SDEVICEERROR_CANNOT_CONVERT_DATA Thrown when the recived data cannot be convert.
/// 
/// \return	the attenuation in dBm. 
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDevicePSAE4440A::attenuation(void){

	try{
		gpibSend("POW:ATT?");
		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			int att = (int)read.toDouble();
			setMetaData( "attenuation", att ,"dB",SMetaData::doublefloat );
			return att; // sinon on ne peut pas convertir les nombre de la forme 0.0E0 == 0 !!
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}
	}catch(SError error){
		SError::traitement(this,error);
		return 0;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::setNbPoints(int const NbPts)
///
/// \brief	(SCRIPTABLE) Sets the number of points for each spectrum sweep. 
///
/// \param	NbPts	The number of points. 
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::setNbPoints(int const NbPts) {

	QString cmd;

	try{
		cmd = QString("SWE:POIN ") + QString::number(NbPts);
		gpibSend(cmd);
		setMetaData( "nbPoints", NbPts,"" ,SMetaData::doublefloat );
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SDevicePSAE4440A::nbPoints()
///
/// \brief	(SCRIPTABLE) Gets the number of points for each spectrum sweep. 
///
/// \exception SDEVICEERROR_CANNOT_CONVERT_DATA Thrown when the recived data cannot be convert.
/// 
/// \return	the number of points, if error 0. 
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDevicePSAE4440A::nbPoints() {

	try{
		gpibSend("SWE:POIN?");
		QVariant read = gpibRead(100);

		if( read.canConvert<int>() && read.convert(QVariant::Int) ){
			int nb = read.toInt();
			setMetaData( "nbPoints", nb ,"",SMetaData::doublefloat );
			return nb;
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

		

	}catch(SError error){
		SError::traitement(this,error);
		return 0;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::setNbAverage(int const NbAvrg)
///
/// \brief	(SCRIPTABLE) Sets the number of average, 0 desactivate the average. 
///
/// \param	NbAvrg	The number of  average between 0 and 1000. 
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::setNbAverage(int const NbAvrg) {

	QString cmd;
	try{

		if (NbAvrg == 0){
			gpibSend(":AVER OFF");

		}else if ((NbAvrg>0)&&(NbAvrg<=1000))	{
			cmd = QString(":AVER:COUN ") + QString::number(NbAvrg);
			gpibSend(cmd);
			gpibSend("AVER ON");

		}

		setMetaData( "nbAverage", NbAvrg ,"",SMetaData::doublefloat );

	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::setMarker(double const frequence, int num)
///
/// \brief	(SCRIPTABLE) Sets the position (in frequency) of the marker number num. 
///
/// \param	frequence	The frequence in GHz. 
/// \param	num			Number of the marker, by default equal at 1. 
/// \remark if num is different of 1 or 2, this function do nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::setMarker(double const frequence, int const  num) {

	QString cmd;

	switch (num){
	case 1:
		if(mark1Active_){
			cmd = QString("CALC:MARK1:X ") + QString::number(frequence, 'f') + QString(" GHz");
		}else{ return;}
		break;
	case 2:
		if(mark2Active_){
			cmd = QString("CALC:MARK2:X ") + QString::number(frequence, 'f') + QString(" GHz");
		}else{ return;}
		break;
	default:
		return;
	};

	try{
		gpibSend(cmd);

	}catch(SError error){
		SError::traitement(this,error);
	}



	bool mark1Active_;
	bool mark2Active_; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::marker(int num, bool OnOff)
///
/// \brief	(SCRIPTABLE) Enable or disable the marker number num. by default num=1;
///
/// \param	num		Number of the marker 1 or 2. 
/// \param	OnOff	false to disable,  true to enable the marker. 
/// 				
/// \remark if num is different of 1 or 2, this function do nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::marker(bool const OnOff, int const num) {

	QString on;
	QString off;

	switch (num){
	case 1:
		on = "CALC:MARK1:MODE POS";
		off = "CALC:MARK1:MODE OFF";
		break;
	case 2:
		on = "CALC:MARK2:MODE POS";
		off = "CALC:MARK2:MODE OFF";
		break;
	default:
		return;
	};

	try{
		if (OnOff){
			gpibSend(on);
		}else{
			gpibSend(off);
		}

	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::readMarker(int num)
///
/// \brief	(SCRIPTABLE) returns the Y position of the marker. 
///
/// \param	num	Number of the marker 1 or 2. 
/// 
/// \exception SDEVICEERROR_CANNOT_CONVERT_DATA Thrown when the recived data cannot be convert.
///  			
/// \warning the marker should it be on otherwise error
/// 		 
/// \remark if num is different of 1 or 2, this function do nothing and return 0
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSAE4440A::readMarker(int const num) {

	try{

		switch (num){
		case 1:
			gpibSend(":CALC:MARK1:Y?");
			break;
		case 2:
			gpibSend(":CALC:MARK2:Y?");
			break;
		default:
			return 0.0;
		};

		QVariant read = gpibRead(50);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			return read.toDouble();
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}
	}catch(SError error){
		SError::traitement(this,error);
		return 0.0;
	}



}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::setRefLevel(double RefLvl)
///
/// \brief	(SCRIPTABLE) Sets the reference level. 
///
/// \param	RefLvl	The reference level in dBm. 
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::setRefLevel(double const RefLvl) {

	try{
		QString cmd = QString("DISP:WIND:TRAC:Y:RLEV ") + QString::number(RefLvl, 'f') + QString("dBm");
		gpibSend(cmd);
		setMetaData( "refLevel", RefLvl ,"dBm",SMetaData::doublefloat );
	}catch(SError error){
		SError::traitement(this,error);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDevicePSAE4440A::refLevel()
///
/// \brief	(SCRIPTABLE) Gets the reference level. 
///
/// \exception SDEVICEERROR_CANNOT_CONVERT_DATA Thrown when the recived data cannot be convert.
/// 											
/// \param	RefLvl	The reference level in dBm. 
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSAE4440A::refLevel() {

	try{
		gpibSend(":DISP:WIND:TRAC:Y:RLEV?");

		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			double lvl = read.toDouble();
			setMetaData( "refLevel", lvl , "dBm",SMetaData::doublefloat );
			return lvl;
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
		return 0;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDevicePSAE4440A::sweepTime()
///
/// \brief	(SCRIPTABLE) Gets the sweep time. 
/// 
/// \exception SDEVICEERROR_CANNOT_CONVERT_DATA Thrown when the recived data cannot be convert.
/// 
/// \return	the sweep time. 
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSAE4440A::sweepTime() {

	try{
		gpibSend(":SWE:TIME?");

		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			return read.toDouble();
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
		return 0;
	}


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::readSpectrum()
///
/// \brief	Reads a spectrum in the analyzer. 
///
/// \exception	SDEVICEERROR_CANNOT_CONVERT_DATA	Thrown when the recived data cannot be convert.. 
/// 												
/// \remark Much of the functioning of this part remains unclear. 
/// 		I tried to adapt it  from MagToolBox without really understanding it.
/// 		So maybe i made mistakes.
/// 		
/// \remark this function is scriptable throuth \c qsReadSpectrum
/// 		
/// \return a pointer to a \c SData2D object, the user have to destroy the object at the end
////////////////////////////////////////////////////////////////////////////////////////////////////
SData2D * SDevicePSAE4440A::readSpectrum() {


	int asStatue =0 ;  // statue de l'analyseur de spectre
	QVariant read ;// variable de stockage des reponnse GPIB


	double vrai_delai=0.5 ; //  // varible obscure venant de MagToolBox

	double freqStop = this->freqStop();
	double freqStart = this->freqStart();
	int nbPoints = this->nbPoints();

	QList<double> spectreX;
	QList<double> spectreY;


	/*---------------------------------*/
	gpibSend("INIT:IMM");
	delay(0.5);

	//on demande l'etat du systeme
	gpibSend("STAT:OPER?");

	read = gpibRead(100);

	if(!( read.canConvert<int>() 
		&& read.convert(QVariant::Int)) ) throw SDEVICEERROR_CANNOT_CONVERT_DATA;
	asStatue = read.toInt();

	/*---------------------------------*/
	// si c'est 40 ou 41 on est sur la mesure d'avant (avec ou non une calib en cours)
	if ((asStatue == 41)||(asStatue == 40)){ //

		delay(2); // donc on attent un peu qu'il démare cette mesure
		gpibSend("STAT:OPER?"); //on re demande l'etat du systeme
		read = gpibRead(100);
		if(!( read.canConvert<int>() 
			&& read.convert(QVariant::Int) )) throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		asStatue = read.toInt();
	}

	/*---------------------------------*/

	// on attent que cela ce fasse
	while ((asStatue == 1)||(asStatue == 33)||
		(asStatue == 0)||(asStatue == 32)){  // 1 et 33 pour recalibration

			delay(0.5);
			gpibSend("STAT:OPER?"); //on re demande l'etat du systeme

			read = gpibRead(100);
			if( !(read.canConvert<int>() 
				&& read.convert(QVariant::Int)) ) throw SDEVICEERROR_CANNOT_CONVERT_DATA;
			asStatue = read.toInt();

	}


	/*---------------------------------*/

	//on demande les data
	gpibSend("TRAC:DATA? TRACE1\r\n");

	//on attend que le registre soit plein
	while (( GpibInterface()->GPIBibsta() & END) == 0){
		delay(vrai_delai);
		read = gpibRead(119999L);

	}

	// on récupere une chaine de caracteres de valeur séparées par des virgules
	if( !(read.canConvert<QString>() &&
		read.convert(QVariant::String) )) throw SDEVICEERROR_CANNOT_CONVERT_DATA;

	QStringList sread= read.toString().split(',');


	for(int i =0; i < sread.count();i++){
		spectreY.append(sread.at(i).toDouble());
		spectreX.append( freqStart + i*(freqStop - freqStart)/(nbPoints-1.0));
	}
	SData2D * data = new SData2D(spectreX,spectreY); 


	data->setColName("Freq","Amp");
	data->setColUnit("GHz","V");
	return data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::nbAverage(int const NbAvrg)
///
/// \brief	(SCRIPTABLE) read the number of average. 
/// 
/// \exception SDEVICEERROR_CANNOT_CONVERT_DATA Thrown when the recived data cannot be convert.
/// 						
/// \return the number of average. 	
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDevicePSAE4440A::nbAverage(){

	try{
		gpibSend("ACP:AVER:COUN?");

		QVariant read = gpibRead(100);

		if( read.canConvert<int>() && read.convert(QVariant::Int) ){
			int nb = read.toInt();
			setMetaData( "nbAverage", nb ,"",SMetaData::doublefloat );
			return nb; 
			
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
		return 0;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QScriptValue SDevicePSAE4440A::qsReadSpectrum(void)
///
/// \brief	(SCRIPTABLE) Gets the spectrum. 
///
/// \return	a SData2DScript object with the data. 
///
/// This function is for the QtScript module 
////////////////////////////////////////////////////////////////////////////////////////////////////
QScriptValue SDevicePSAE4440A::qsReadSpectrum(void){


	int asStatue =0 ;  // statue de l'analyseur de spectre
	QVariant read ;// variable de stockage des reponnse GPIB


	double vrai_delai=0.5 ; //  // varible obscure venant de MagToolBox

	double freqStop = this->freqStop();
	double freqStart = this->freqStart();
	int nbPoints = this->nbPoints();

	QList<double> spectreY;

	/*---------------------------------*/
	gpibSend("INIT:IMM");
	delay(0.1);

	//on demande l'etat du systeme
	gpibSend("STAT:OPER?");

	read = gpibRead(100);

	if(!( read.canConvert<int>() 
		&& read.convert(QVariant::Int)) ) throw SDEVICEERROR_CANNOT_CONVERT_DATA;
	asStatue = read.toInt();

	/*---------------------------------*/
	// si c'est 40 ou 41 on est sur la mesure d'avant (avec ou non une calib en cours)
	if ((asStatue == 41)||(asStatue == 40)){ //
		while((asStatue == 41)||(asStatue == 40)){
		delay(0.1); // donc on attent un peu qu'il démare cette mesure
		gpibSend("STAT:OPER?"); //on re demande l'etat du systeme
		read = gpibRead(100);
		if(!( read.canConvert<int>() 
			&& read.convert(QVariant::Int) )) throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		asStatue = read.toInt();
		}
	}

	/*---------------------------------*/

	// on attent que cela ce fasse
	while ((asStatue == 1)||(asStatue == 33)||
		(asStatue == 0)||(asStatue == 32)){  // 1 et 33 pour recalibration

			delay(0.2);
			gpibSend("STAT:OPER?"); //on re demande l'etat du systeme

			read = gpibRead(100);
			if( !(read.canConvert<int>() 
				&& read.convert(QVariant::Int)) ) throw SDEVICEERROR_CANNOT_CONVERT_DATA;
			asStatue = read.toInt();

	}


	/*---------------------------------*/

	//on demande les data
	gpibSend("TRAC:DATA? TRACE1\r\n");

	//on attend que le registre soit plein
	while (( GpibInterface()->GPIBibsta() & END) == 0){
		delay(vrai_delai);
		read = gpibRead(119999L);

	}

	// on récupere une chaine de caracteres de valeur séparées par des virgules
	if( !(read.canConvert<QString>() &&
		read.convert(QVariant::String) )) throw SDEVICEERROR_CANNOT_CONVERT_DATA;

	QStringList sread= read.toString().split(',');

	QString qsCmd;
	QTextStream qtsCmd(&qsCmd);

	
	qtsCmd << "var vbn = new SData2D();";

	
	qsCmd.reserve(nbPoints*35);


	for(int i =0; i < nbPoints ;i++){
		// on calcule les abscisse
		// on récupere les ordonées
		if(i<sread.count()){
			qtsCmd << "vbn.append(" << freqStart + i*(freqStop - freqStart)/(nbPoints-1.0) << "," << sread.at(i) << ");\n";
		}else{
			qtsCmd << "vbn.append(" << freqStart + i*(freqStop - freqStart)/(nbPoints-1.0) << "," << 0 << ");\n";
		}

	}

	qtsCmd << "vbn.setColName(\"Freq\",\"Amp\");";
	qtsCmd << "vbn.setColUnit(\"GHz\",\"V\");";
	qtsCmd << "vbn;";

	return  this->engine()->evaluate(qsCmd);;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::restart(void)
///
/// \brief	(SCRIPTABLE) reset the average spectrum analyzer. 
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::restart(void){
	try{
		gpibSend(":ABOR");
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE QString SDevicePSAE4440A::name(void) const
///
/// \brief	Gets the name. 
///
/// \return	the name of the device. 
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSAE4440A::name(void) const{

	return elmt_.name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE virtual QString SDevicePSAE4440A::description(void) const
///
/// \brief	Gets a brief description of the device. 
///
/// \return	a description of the device. 
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSAE4440A::description(void) const
{
	QString des	=  "The Agilent E4440A PSA high-performance spectrum analyzer measures and monitors complex RF and";
	des	+= "microwave signals up to 26.5 GHz. With optional external mixing, the frequency coverage expands";
	des	+= "to 110 GHz by Agilent external mixer, and to 325 GHz by other vendors' mixer.";

	return des;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDevicePSAE4440A::available(void)
///
/// \brief	(SCRIPTABLE) Gets the availability. 
///
/// \return	true if the device is available, false if it is not. 
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSAE4440A::available(void){	

	try{
		gpib_ =  SInterfaceGpib::instance();
		elmt_= gpib_->findGpibElement(QString("Agilent Technologies, E4440A"));

		available_ = (elmt_.PAD !=-1);

	}catch(SError error){
		if (!(error == SDEVICEERROR_GPIB_FINDLSTN)){
			SError::traitement(this,error);	
		}else{

			this->setUnavailable();
			//	qDebug() << "\nAgilent PSAE4440A not found.\n";
		}

	}

	setMetaData( "available", available_ ,"",SMetaData::boolean );
	return available_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 double SDevicePSAE4440A::checkRbw(double const rbw)
///
/// \brief	(SCRIPTABLE) Set and return the acceptable resolution of bandwidth the closest to rbw. 
///
/// \return	the closest resolution of bandwidth of the given rbw.
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSAE4440A::checkRbw(double const rbw){
	this->setRbw(rbw);
	delay(0.3);

	double rbw_ = this->rbw();
	setMetaData( "rbw", rbw_,"",SMetaData::doublefloat );
	return rbw_;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setMetaData( QString key, QVariant value )
///
/// \brief	Change the value of the metadata for this device in the global map SGlobalMetaDataMap 
///
/// \param key the key in the sub map of metatdata for this device
/// \param value the value corresponding of the key
/// \param unit the unit of the value
/// \param type the type  of the value
///
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void SDevicePSAE4440A::setMetaData(const QString key, const QVariant value, const QString unit, 
								const SMetaData::enumType type )
{
	if (metaDataOnOff_) gmdm_.setMetaData(QString(SDEVICEPSAE4440A_SHORT_NAME), key, value,unit, type);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::metaDataOnOff( bool onOff )
///
/// \brief	activate or deactivate the Global Metadata System
///
/// \param onOff in the sub map of metatdata for this device
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSAE4440A::metaDataOnOff( bool onOff )
{
	metaDataOnOff_ = onOff;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 void SDevicePSAE4440A::setLogDisplay(bool const OnOff)
///
/// \brief	(SCRIPTABLE) Put the display in logarithmic view 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  void SDevicePSAE4440A::setLogDisplay(bool const OnOff){
	QString mode;
	if(OnOff){
		mode = "LOG";
	}else{
		mode = "LIN";
	}


	try{
		QString cmd = QString("DISP:WIND:TRAC:Y:SPAC ") + mode;
		gpibSend(cmd);
		setMetaData( "LogDisplay", OnOff ,"" ,SMetaData::boolean );
	}catch(SError error){
		SError::traitement(this,error);
	}


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 bool SDevicePSAE4440A::logDisplay()
///
/// \brief	(SCRIPTABLE) check if the display is in logarithmic view 
///
/// \return	true if the display is in logarithmic view, otherwise returns false.
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  bool SDevicePSAE4440A::logDisplay(){
try{
	gpibSend("DISP:WIND:TRAC:Y:SPAC?");

	QVariant read = gpibRead(100);

	if( read.canConvert<bool>() && read.convert(QVariant::Bool) ){
		bool log = read.toBool();
		setMetaData("LogDisplay", log ,"",SMetaData::boolean );
		return log; 

	}else{
		throw SDEVICEERROR_CANNOT_CONVERT_DATA;
	}

}catch(SError error){
	SError::traitement(this,error);
	return 0;
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE SDevicePSAE4440A::Point2D SDevicePSAE4440A::PeakSearch()
///
/// \brief	Get the max on the spectrum (x in HZ, y in SA unit).
///
/// \author	Sylvain Martin
/// \date	25/02/2013
///
/// \return	.
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE  SDevicePSAE4440A::Point2D SDevicePSAE4440A::MaxSearch()
{

	Point2D point;
	try{
		gpibSend("CALC:MARK:MAX");
		gpibSend("CALC:MARK:X?");
		QVariant xread = gpibRead(100);

		gpibSend("CALC:MARK:Y?");
		QVariant yread = gpibRead(100);


		if( xread.canConvert<double>() && xread.convert(QVariant::Double) 
			&& yread.canConvert<double>() && yread.convert(QVariant::Double)){
			point.x= xread.toDouble();
			point.y= yread.toDouble();
			return point; 

		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
		return point;
	}
}
