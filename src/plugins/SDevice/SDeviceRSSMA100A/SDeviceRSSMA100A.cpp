////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SDeviceRSSMA100A.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/03/2012
///
/// \brief	Implants the class and the plugin corresponding to SDeviceE8257D 
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
#include "SDeviceRSSMA100A.h"
#include <SDK/SError.h>
#include <SDKDevice/SDevice/SDeviceError.h>  
#include <SDKDevice/SDevice/SDeviceGpib.h> 
#include <SDKDevice/SDevicePluginInterface.h>
#include "SUiCpRSSMA100A.h"

#include <qdebug.h>
#include <QtCore>

#define GHZ 1000000000
#define MHZ 1000000
#define KHZ 1000

#include <QtCore>

Q_EXPORT_PLUGIN2("SDeviceRSSMA100APlugin", SDeviceRSSMA100APlugin)





////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDevicePSGE8257D::SDevicePSGE8257D()
///
/// \brief	constructor
///
/// \author	Sylvain Martin
/// \date	01/12/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
SDeviceRSSMA100APlugin::SDeviceRSSMA100APlugin():state_(2),RSSMA100A(NULL)
{
}

SDeviceRSSMA100APlugin::~SDeviceRSSMA100APlugin()
{
	if(RSSMA100A!=NULL)
		delete RSSMA100A;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceRSSMA100APlugin::load()
///
/// \brief	initialize the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceRSSMA100APlugin::load()
{
	//GlobalMetaDataMap_ = GlobalMetaDataMap;
	RSSMA100A = new SDeviceRSSMA100A(this);

	if(RSSMA100A->available()) state_=0;
	return RSSMA100A->available();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceRSSMA100APlugin::name() const
///
/// \brief	return the complete name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceRSSMA100APlugin::name() const
{
	return QString("Rohde & Schwarz SMA 100 Signal Generator");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceRSSMA100APlugin::shortName() const
///
/// \brief	return the short name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the short name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceRSSMA100APlugin::shortName() const
{
	return QString(SDEVICERSSMA100A_SHORT_NAME);
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
QString SDeviceRSSMA100APlugin::description() const
{
	QString des	=  "The R&S SMA 100A combines superior signal quality with very high setting speed, ";
		des	+= 	"which makes it ideal for any task. Whether in development, production, service or maintenance, ";
		des	+= 	" the R&S SMA 100A does an excellent job. \n\n";
		des	+= 	"In the frequency range from 9 kHz to 6 GHz, it can generate CW signals as well as all common types ";
		des	+= 	"of analog modulation (AM, FM, PM, pulse modulation). Excellent specifications and a wide range ";
		des	+= 	"of modulation signals - these are the characteristic features of the R&S SMA 100A. In addition, ";
		des	+= 	"a low-jitter clock synthesizer option supplies differential clock signals of up to 1.5 GHz ";
		des	+= 	"independently of the RF frequency.";

	return des;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceRSSMA100APlugin::scriptable( QScriptEngine * engine )
///
/// \brief	add (or not) some functions to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::scriptable
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceRSSMA100APlugin::scriptable( QScriptEngine * engine )
{

	static bool initialized = false;

	if(!initialized){ // evite le multi initialitation
		try{
			initialized = true;
			SDeviceRSSMA100A*	scRSSMA100A = new SDeviceRSSMA100A();

			QScriptValue qsvDeviceRSSMA100A = engine->newQObject(scRSSMA100A,QScriptEngine::ScriptOwnership);
			engine->globalObject().setProperty("RSSMA100A", qsvDeviceRSSMA100A);

		}catch(SError error){
			initialized = false;
			engine->evaluate("var RSSMA100A = new Object(); RSSMA100A.available = false;","Initialization");
			qDebug()  <<" ERROR (LOW): initialization of the Rohde & Schwarz RSSMA100A's script object failed" 
				<< error;

			engine->evaluate("var RSSMA100A = new Object(); RSSMA100A.available = false;","Initialization");

			return false;

		}
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceRSSMA100APlugin::isScriptable()
///
/// \brief	does the plugin add some function to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceRSSMA100APlugin::isScriptable()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceRSSMA100APlugin::isControlPanel()
///
/// \brief	does the plugin add a tab to the control panel to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceRSSMA100APlugin::isControlPanel()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceRSSMA100APlugin::controlPanel() const
///
/// \brief	add (or not) a tab to the control panel 
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isControlPanel
///
/// \remark SDeviceRSSMA100APlugin do not manage the destruction of the object, so you ave to define a parent
///			or destroy it your self 
////////////////////////////////////////////////////////////////////////////////////////////////////
QWidget * SDeviceRSSMA100APlugin::controlPanel(QWidget * parent /*= NULL*/)
{
	
	QWidget * CtrlPanel = new SUiCpRSSMA100A(parent);
	return CtrlPanel;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceRSSMA100APlugin::isSetting()
///
/// \brief	does the plugin have a setting window ?
///
/// \author	Sylvain Martin
/// \date	25/02/2012
/// \sa SDevicePSGE8257D::controlPanel
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceRSSMA100APlugin::isSetting()
{
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QWidget* SDeviceRSSMA100APlugin::controlPanel()
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
QWidget * SDeviceRSSMA100APlugin::setting(QWidget * parrent /*= NULL*/ )
{
	QWidget * widSetting = new QWidget(parrent); //!TODO ALL !!!
	return widSetting;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceRSSMA100APlugin::shutdown()
///
/// \brief	shutdown the plugin (by example before closing the application)
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isControlPanel
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceRSSMA100APlugin::shutdown()
{
	//	PSGE8257D->deactivate();
	state_=2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SDeviceRSSMA100APlugin::state()
///
/// \brief	what is the state of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// 0 : ready, 1 : busy, 2 unavailable
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDeviceRSSMA100APlugin::state()
{
	return state_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceRSSMA100APlugin::available()
///
/// \brief	is the plugin available
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceRSSMA100APlugin::available()
{
	return RSSMA100A->available();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceRSSMA100APlugin::plgVersion() const
///
/// \brief	return the version of the SDK that is needed for run the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceRSSMA100APlugin::plgVersion() const
{
	return QString::number(SDEVICERSSMA100A_VERSION);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceRSSMA100APlugin::plgVersion() const
///
/// \brief	return the version of the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceRSSMA100APlugin::SDKVersion() const 
{
	return QString::number(SDEVICERSSMA100A_MAJOR_VERSION_COMPATIBILITY) + 
		QString(".") + QString::number(SDEVICERSSMA100A_MINOR_VERSION_COMPATIBILITY);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceRSSMA100APlugin::plgVersion() const
///
/// \brief	this function is call when the plugin is unload
///
/// \author	Sylvain Martin
/// \date	13/01/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceRSSMA100APlugin::unload()
{
	qDebug()  <<" WARNING: unloading of the R&S SMA100A's script object failed \n" ;
	qDebug()  <<" \t because the function is not implanted yet\n" ;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDeviceRSSMA100A::SDeviceRSSMA100A(QObject *parent)
///
/// \brief	Constructor.
///
/// \author	Sylvain Martin
/// \date	04/02/2013
///
/// \param [in,out]	parent	If non-null, the parent.
////////////////////////////////////////////////////////////////////////////////////////////////////

SDeviceRSSMA100A::SDeviceRSSMA100A(QObject *parent):SDeviceGpib(parent), powerLimit_(-10),metaDataOnOff_(true)
{
	init();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceRSSMA100A::init(void)
///
/// \brief	Initializes the PSG E8257D device. 
///
/// this function is automatically call at the initialization of this object
////////////////////////////////////////////////////////////////////////////////////////////////////

void SDeviceRSSMA100A::init(void){

	setMetaData( "frequency", "N/A","GHz",SMetaData::boolean );
	setMetaData( "power", "N/A","dBm",SMetaData::doublefloat );
	setMetaData( "powerLimit", "N/A","dBm",SMetaData::doublefloat );
	setMetaData( "available", false,"",SMetaData::boolean );
	setMetaData( "activate", false,"",SMetaData::boolean );

	try{
		gpib_ =  SInterfaceGpib::instance();
		elmt_= gpib_->findGpibElement(QString("Rohde&Schwarz,SMA100A"));

		if (!(elmt_.PAD ==-1)) available_ = true;


	}catch(SError error){
		if (!(error == SDEVICEERROR_GPIB_FINDLSTN)){
			SError::traitement(this,error);	
		}else{

			this->setUnavailable();
			//qDebug() << "\nAgilent PSGE8257D not found.\n";
		}

	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceRSSMA100A::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the frequency of the microwave. 
///
/// \param	freq The frequency in GHz. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceRSSMA100A::setFrequency(double const freq){
	frequency_ = freq;

	QString cmd;

	try{

		if (freq< 1/KHZ){
			cmd = QString(":FREQ ") + QString::number(freq, 'f') + QString(" GHZ");
		}else{ // for the small RBW, avoid the cmd == 0.000000 GHZ
			cmd = QString(":FREQ ") + QString::number(freq*GHZ, 'f') + QString(" HZ");
		}
		setMetaData( "frequency", freq,"GHz",SMetaData::boolean );
		gpibSend(cmd);
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceRSSMA100A::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the power of the microwave. 
///
/// \param	pwr The power in dBm. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceRSSMA100A::setPower(double const pwr){

	if (pwr >= -135 && pwr <= powerLimit_){

		QString cmd;

		try{
			cmd = QString(":POW ") + QString::number(pwr) + QString(" DBM");
			power_ = pwr;
			gpibSend(cmd);
			setMetaData( "power", power_,"dBm",SMetaData::doublefloat );
		}catch(SError error){
			SError::traitement(this,error);
		}


		power_ = pwr;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceRSSMA100A::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the power limit of the microwave. 
///
/// \param	pwr The power in dBm. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceRSSMA100A::setPowerLimit(const double pwrLim){
	setMetaData( "powerLimit", powerLimit_,"dBm",SMetaData::doublefloat );
	powerLimit_ = pwrLim; 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceRSSMA100A::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) activates or deactivates the microwave. 
///
/// \param	OnOff  activate if true, deactivates otherwise. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceRSSMA100A::activate(bool OnOff){
	activated_ = OnOff;

	QString cmd;

	try{
		if(OnOff){
			cmd = QString(":OUTP ON");
			setMetaData( "activate", true,"",SMetaData::boolean );
		}else{
			cmd = QString(":OUTP OFF");
			setMetaData( "activate", false,"",SMetaData::boolean );
		}

		gpibSend(cmd);
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 QString SDeviceRSSMA100A::description(void) const
///
/// \brief	(SCRIPTABLE) Gets a brief description of the device. 
///
/// \return	a description of the device. 
////////////////////////////////////////////////////////////////////////////////////////////////////

QString SDeviceRSSMA100A::description(void) const
{

	QString des	=  "The Agilent E8257D is a fully synthesized signal generator with high output";
	des	+= "power, low phase noise, and optional ramp sweep capability";


	return des;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceRSSMA100A::available(void)
///
/// \brief	(SCRIPTABLE) Gets the availability. 
///
/// \return	true if the device is available, false if it is not. 
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceRSSMA100A::available( void ){

	try{
		gpib_ =  SInterfaceGpib::instance();
		elmt_= gpib_->findGpibElement(QString("Rohde&Schwarz,SMA100A"));

		available_ = (elmt_.PAD !=-1);
	}catch(SError error){
		available_ = false;
		if (!(error == SDEVICEERROR_GPIB_FINDLSTN)){
			SError::traitement(this,error);			
		}else{
			this->setUnavailable();
		}

	}

	setMetaData( "available", available_,"",SMetaData::boolean );
	return available_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceRSSMA100A::frequence() const
///
/// \brief	get the frequency of the microwave in GHz. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDeviceRSSMA100A::frequency() {

	try{
		this->gpibSend(":FREQ?");

		QVariant read = this->gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			double freq = read.toDouble()/GHZ;
			setMetaData( "frequency", freq,"GHz",SMetaData::boolean );
			frequency_=freq;
			return freq; 

		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
		return 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceRSSMA100A::frequence() const
///
/// \brief	get the power of the microwave in dBm.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDeviceRSSMA100A::power( ) {
	try{
		this->gpibSend(":POW?");

		QVariant read = this->gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			double pow = read.toDouble();
			setMetaData( "power", pow,"dBm",SMetaData::doublefloat );
			power_=pow;
			return pow; 

		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
		return 0;
	};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceRSSMA100A::frequence() const
///
/// \brief	get the power limit of the microwave. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDeviceRSSMA100A::powerLimit( ) const {
	return powerLimit_;}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceRSSMA100A::frequence() const
///
/// \brief	get if the generator is Activated. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceRSSMA100A::isActivated( ){
	return activated_;}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceRSSMA100A::setMetaData( QString key, QVariant value )
///
/// \brief	Change the value of the metadata for this device in the global map SGlobalMetaDataMap 
///
/// \param the key in the sub map of metatdata for this device
/// \param value the value corresponding of the key
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceRSSMA100A::setMetaData( const QString key, const QVariant value, const QString unit, const SMetaData::enumType type)
{

	if(metaDataOnOff_) gmdm_.setMetaData(QString(SDEVICERSSMA100A_SHORT_NAME),key,value, unit , type);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceRSSMA100A::metaDataOnOff( bool onOff )
///
/// \brief	activate or deactivate the Global Metadata System
///
/// \param onOff in the sub map of metatdata for this device
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceRSSMA100A::metaDataOnOff( bool onOff )
{
	metaDataOnOff_ = onOff;
}