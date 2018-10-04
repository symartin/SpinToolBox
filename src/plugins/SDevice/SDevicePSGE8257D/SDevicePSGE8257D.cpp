////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SDeviceE8557D.cpp
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

#include "SDevicePSGE8257D.h"
#include <SDK/SError.h>
#include <SDKDevice/SDevice/SDeviceError.h>  
#include <SDKDevice/SDevice/SDeviceGpib.h> 
#include <SDKDevice/SDevicePluginInterface.h>
#include "SUiCpPSGE8257D.h"

#include <qdebug.h>
#include <QtCore>

#define GHZ 1000000000
#define MHZ 1000000
#define KHZ 1000

#include <QtCore>

Q_EXPORT_PLUGIN2("SDevicePSGE8257DPlugin", SDevicePSGE8257DPlugin)


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDevicePSGE8257DPlugin::SDevicePSGE8257DPlugin()
///
/// \brief	constructor
///
/// \author	Sylvain Martin
/// \date	01/12/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
	SDevicePSGE8257DPlugin::SDevicePSGE8257DPlugin():state_(2),PSGE8257D(NULL)
{
}

SDevicePSGE8257DPlugin::~SDevicePSGE8257DPlugin()
{
	if(PSGE8257D!=NULL)
		delete PSGE8257D;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDevicePSGE8257DPlugin::load()
///
/// \brief	initialize the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSGE8257DPlugin::load()
{
	//GlobalMetaDataMap_ = GlobalMetaDataMap;
	PSGE8257D = new SDevicePSGE8257D(this);

	if(PSGE8257D->available()) state_=0;
	return PSGE8257D->available();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257DPlugin::name() const
///
/// \brief	return the complete name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSGE8257DPlugin::name() const
{
	return QString("Agilent Technologies Analog Signal Generator E8257D");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257DPlugin::shortName() const
///
/// \brief	return the short name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the short name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSGE8257DPlugin::shortName() const
{
	return QString(SDEVICEPSGE8257D_SHORT_NAME);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257DPlugin::description() const
///
/// \brief	return the description of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the description of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSGE8257DPlugin::description() const
{
	QString des	=  "The Agilent E8257D is a fully synthesized signal generator with high output";
	des	+= "power, low phase noise, and optional ramp sweep capability";

	return des;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDevicePSGE8257DPlugin::scriptable( QScriptEngine * engine )
///
/// \brief	add (or not) some functions to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::scriptable
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSGE8257DPlugin::scriptable( QScriptEngine * engine )
{
	
	static bool initialized = false;

	if(!initialized){ // evite le multi initialitation
		try{
			initialized = true;
			SDevicePSGE8257D*	PSGE8257D = new SDevicePSGE8257D();

			QScriptValue qsvSDevicePSGE8257D = engine->newQObject(PSGE8257D,QScriptEngine::ScriptOwnership);
			engine->globalObject().setProperty("PSGE8257D", qsvSDevicePSGE8257D);
		
		}catch(SError error){
			initialized = false;
			engine->evaluate("var PSGE8257D = new Object(); PSGE8257D.available = false;","Initialization");
			qDebug()  <<" ERROR (LOW): initialization of the Agilent PSGE8257D's script object failed" 
				<< error;

			engine->evaluate("var PSGE8257D = new Object(); PSGE8257D.available = false;","Initialization");

			return false;

		}
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDevicePSGE8257DPlugin::isScriptable()
///
/// \brief	does the plugin add some function to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSGE8257DPlugin::isScriptable()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDevicePSGE8257DPlugin::isControlPanel()
///
/// \brief	does the plugin add a tab to the control panel to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSGE8257DPlugin::isControlPanel()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257DPlugin::controlPanel() const
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
QWidget * SDevicePSGE8257DPlugin::controlPanel(QWidget * parent /*= NULL*/)
{

	QWidget * CtrlPanel = new SUiCpPSGE8257D(parent);
	return CtrlPanel;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDevicePSGE8257DPlugin::isSetting()
///
/// \brief	does the plugin have a setting window ?
///
/// \author	Sylvain Martin
/// \date	25/02/2012
/// \sa SDevicePSGE8257D::controlPanel
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSGE8257DPlugin::isSetting()
{
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QWidget* SDevicePSGE8257DPlugin::controlPanel()
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
QWidget * SDevicePSGE8257DPlugin::setting(QWidget * parrent /*= NULL*/ )
{
	QWidget * widSetting = new QWidget(parrent); //!TODO ALL !!!
	return widSetting;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSGE8257DPlugin::shutdown()
///
/// \brief	shutdown the plugin (by example before closing the application)
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isControlPanel
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSGE8257DPlugin::shutdown()
{
//	PSGE8257D->deactivate();
	state_=2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SDevicePSGE8257DPlugin::state()
///
/// \brief	what is the state of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// 0 : ready, 1 : busy, 2 unavailable
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDevicePSGE8257DPlugin::state()
{
	return state_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDevicePSGE8257DPlugin::available()
///
/// \brief	is the plugin available
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSGE8257DPlugin::available()
{
	return PSGE8257D->available();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257DPlugin::plgVersion() const
///
/// \brief	return the version of the SDK that is needed for run the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSGE8257DPlugin::plgVersion() const
{
	return QString::number(SDEVICEPSGE8257D_VERSION);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257DPlugin::plgVersion() const
///
/// \brief	return the version of the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDevicePSGE8257DPlugin::SDKVersion() const 
{
	return QString::number(SDEVICEPSGE8257D_MAJOR_VERSION_COMPATIBILITY) + 
		QString(".") + QString::number(SDEVICEPSGE8257D_MINOR_VERSION_COMPATIBILITY);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDevicePSGE8257DPlugin::plgVersion() const
///
/// \brief	this function is call when the plugin is unload
///
/// \author	Sylvain Martin
/// \date	13/01/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSGE8257DPlugin::unload()
{
	qDebug()  <<" WARNING: unloading of the Agilent PSGE8257D's script object failed \n" ;
	qDebug()  <<" \t because the function is not implanted yet\n" ;

	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDevicePSGE8257D::SDevicePSGE8257D(QObject *parent)
///
/// \brief	Constructor.
///
/// \author	Sylvain Martin
/// \date	04/02/2013
///
/// \param [in,out]	parent	If non-null, the parent.
////////////////////////////////////////////////////////////////////////////////////////////////////

SDevicePSGE8257D::SDevicePSGE8257D(QObject *parent):SDeviceGpib(parent), powerLimit_(-10),
	metaDataOnOff_(true),frequency_(0),power_(-135)
{
	init();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSGE8257D::init(void)
///
/// \brief	Initializes the PSG E8257D device. 
///
/// this function is automatically call at the initialization of this object
////////////////////////////////////////////////////////////////////////////////////////////////////

void SDevicePSGE8257D::init(void){

	setMetaData( "frequency", "N/A","GHz",SMetaData::boolean );
	setMetaData( "power", "N/A","dBm",SMetaData::doublefloat );
	setMetaData( "powerLimit", "N/A","dBm",SMetaData::doublefloat );
	setMetaData( "available", false,"",SMetaData::boolean );
	setMetaData( "activate", false,"",SMetaData::boolean );

	try{
		gpib_ =  SInterfaceGpib::instance();
		elmt_= gpib_->findGpibElement(QString("Agilent Technologies, E8257D"));

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
/// \fn	void SDevicePSAE4440A::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the frequency of the microwave. 
///
/// \param	freq The frequency in GHz. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSGE8257D::setFrequency(double const freq){
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
/// \fn	void SDevicePSAE4440A::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the power of the microwave. 
///
/// \param	pwr The power in dBm. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSGE8257D::setPower(double const pwr){

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
/// \fn	void SDevicePSAE4440A::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the power limit of the microwave. 
///
/// \param	pwr The power in dBm. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSGE8257D::setPowerLimit(const double pwrLim){
	setMetaData( "powerLimit", powerLimit_,"dBm",SMetaData::doublefloat );
	powerLimit_ = pwrLim; 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) activates or deactivates the microwave. 
///
/// \param	OnOff  activate if true, deactivates otherwise. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSGE8257D::activate(bool OnOff){
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
/// \fn	 QString SDevicePSGE8257D::description(void) const
///
/// \brief	(SCRIPTABLE) Gets a brief description of the device. 
///
/// \return	a description of the device. 
////////////////////////////////////////////////////////////////////////////////////////////////////

QString SDevicePSGE8257D::description(void) const
{

	QString des	=  "The Agilent E8257D is a fully synthesized signal generator with high output";
	des	+= "power, low phase noise, and optional ramp sweep capability";


	return des;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDevicePSGE8257D::available(void)
///
/// \brief	(SCRIPTABLE) Gets the availability. 
///
/// \return	true if the device is available, false if it is not. 
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSGE8257D::available( void ){

	try{
		gpib_ =  SInterfaceGpib::instance();
		elmt_= gpib_->findGpibElement(QString("Agilent Technologies, E8257D"));

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
/// \fn	double SDevicePSGE8257D::frequence() const 
///
/// \brief	get the frequency of the microwave in GHz. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSGE8257D::frequency() const {
	return frequency_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDevicePSGE8257D::frequence() const 
///
/// \brief	get the power of the microwave in dBm.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSGE8257D::power( ) const {
	return power_;}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDevicePSGE8257D::frequence() const 
///
/// \brief	get the power limit of the microwave. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDevicePSGE8257D::powerLimit( ) const {
	return powerLimit_;}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDevicePSGE8257D::frequence() const 
///
/// \brief	get if the generator is Activated. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDevicePSGE8257D::isActivated( ){
	return activated_;}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSGE8257D::setMetaData( QString key, QVariant value )
///
/// \brief	Change the value of the metadata for this device in the global map SGlobalMetaDataMap 
///
/// \param the key in the sub map of metatdata for this device
/// \param value the value corresponding of the key
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSGE8257D::setMetaData( const QString key, const QVariant value, const QString unit, const SMetaData::enumType type)
{

	if(metaDataOnOff_) gmdm_.setMetaData(QString(SDEVICEPSGE8257D_SHORT_NAME),key,value, unit , type);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSGE8257D::metaDataOnOff( bool onOff )
///
/// \brief	activate or deactivate the Global Metadata System
///
/// \param onOff in the sub map of metatdata for this device
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDevicePSGE8257D::metaDataOnOff( bool onOff )
{
	metaDataOnOff_ = onOff;
}