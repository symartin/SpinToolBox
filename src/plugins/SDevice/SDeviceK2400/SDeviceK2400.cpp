////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceK2400.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/12/2011
///
/// \brief	Implements the class that correspond to the K2400 control panel
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

#include "SDeviceK2400.h"
#include "SUiCpK2400.h"
#include "SDKDevice/SDevice/SDeviceError.h"
#include <QtCore>
#include <SDKDevice/SDevicePluginInterface.h>



Q_EXPORT_PLUGIN2("SDeviceK2400", SDeviceK2400Plugin)


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDeviceK2400Plugin::SDeviceK2400Plugin()
///
/// \brief	constructor
///
/// \author	Sylvain Martin
/// \date	01/12/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
SDeviceK2400Plugin::SDeviceK2400Plugin():state_(2),K2400(NULL)
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDeviceK2400Plugin::~SDeviceK2400Plugin()
///
/// \brief	destructor
///
/// \author	Sylvain Martin
/// \date	23/03/2012
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SDeviceK2400Plugin::~SDeviceK2400Plugin()
{
	if(K2400!=NULL)
		delete K2400;

	SGlobalMetaDataMap gmdm_;
	gmdm_.clear(QString(SDEVICEK2400_SHORT_NAME));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::load()
///
/// \brief	initialize the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param GlobalMetaDataMap pointer on the global object containing all the metadata
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400Plugin::load()
{
	//	gmdm_ = GlobalMetaDataMap;
	K2400 = new SDeviceK2400(this);

	this->connect(K2400,SIGNAL(logError(QString, QString)),SIGNAL(logError(QString, QString)));
	this->connect(K2400,SIGNAL(logEvent(QString, QString)),SIGNAL(logEvent(QString, QString)));

	if(K2400->available()) state_=0;
	return K2400->available();
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
QString SDeviceK2400Plugin::name() const
{
	return QString("KEITHLEY INSTRUMENTS INC., MODEL 2400");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400::shortName() const
///
/// \brief	return the short name of the plugin.
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the short name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceK2400Plugin::shortName() const
{
		return QString(SDEVICEK2400_SHORT_NAME);
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
QString SDeviceK2400Plugin::description() const
{
	QString des	= "Keithley 2400 is designed";
	des	+=" specifically for test applications that demand tightly ";
	des	+="coupled sourcing and measurement.\nAll SourceMeter models ";
	des	+="provide precision voltage and current sourcing as well ";
	des	+="as measurement capabilities. Each SourceMeter instrument ";
	des	+="is both a highly stable DC power source and a true ";
	des	+="instrument-grade 5-1/2 digit multimeter. The power ";
	des	+="source characteristics include low noise, precision, ";
	des	+="and readback. The multimeter capabilities include high ";
	des	+="repeatability and low noise. The result is a compact, ";
	des	+="single-channel, DC parametric tester. In operation, ";
	des	+="these instruments can act as a voltage source, a ";
	des	+="current source, a voltage meter, a current meter, ";
	des	+="and an ohmmeter.";

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
/// \sa SDeviceK2400::isScriptable
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400Plugin::scriptable( QScriptEngine * engine )
{
	static bool initialized = false;

	if(!initialized){ // evite le multi initialitation
		try{
			initialized = true;

			SDeviceK2400* K2400Script = new SDeviceK2400();
			this->connect(K2400Script,SIGNAL(logError(QString,QString)),SIGNAL(logError(QString,QString)));
			this->connect(K2400Script,SIGNAL(logEvent(QString,QString)),SIGNAL(logEvent(QString,QString)));


			K2400->setMode(SDeviceK2400::CURRENT);
			QScriptValue qsvSDeviceK2400 = engine->newQObject(K2400Script,QScriptEngine::ScriptOwnership);
			QScriptValue qsvMetaSDeviceK2400 = engine->newQMetaObject(K2400Script->metaObject());

			engine->globalObject().setProperty("K2400", qsvSDeviceK2400);
			engine->globalObject().setProperty("SDeviceK2400", qsvMetaSDeviceK2400); // Pour les Enums
			engine->evaluate("K2400.readIV = K2400.qsReadIV; K2400.readVI = K2400.qsReadVI;\n","Initialization");
			engine->evaluate("K2400.CURRENT = \"CURRENT\"; K2400.VOLTAGE = \"VOLTAGE\";\n","Initialization");
			engine->evaluate("K2400.mode = K2400.qsMode;\n","Initialization");
		

			qDebug()  << "Keithley 2400 SourceMeter found";

			if(!K2400->available()){
				initialized = false;
				qDebug()  << "Keithley 2400 SourceMeter cannot be found";
				engine->evaluate("var K2400 = new Object(); K2400.available = false;","Initialization");
			}
		}catch(SError error){
			initialized = false;
			engine->evaluate("var K2400 = new Object(); K2400.available = false;","Initialization");
			qDebug()  <<" ERROR (LOW): initialization of the Keithley 2400 SourceMeter's script object failed" 
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
///
/// \sa SDeviceK2400::scriptable
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400Plugin::isScriptable()
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
///
/// \sa SDeviceK2400::ControlPanel()
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400Plugin::isControlPanel()
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
/// \remark SDeviceK2400Plugin do not manage the destruction of the object, so you ave to define a parent
///			or destroy it your self 
////////////////////////////////////////////////////////////////////////////////////////////////////
QWidget * SDeviceK2400Plugin::controlPanel(QWidget * parent /*= NULL*/)
{
	
	QWidget * CtrlPanel = new SUiCpK2400(parent);
	return CtrlPanel;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400Plugin::isSetting()
///
/// \brief	does the plugin have a setting window ?
///
/// \author	Sylvain Martin
/// \date	25/02/2012
/// \sa SDeviceK2400Plugin::controlPanel
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400Plugin::isSetting()
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
QWidget * SDeviceK2400Plugin::setting(QWidget * parrent /*= NULL*/ )
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
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400Plugin::shutdown()
{
	K2400->deactivate();
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
int SDeviceK2400Plugin::state()
{
	return state_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::available()
///
/// \brief	is the plugin available ?
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400Plugin::available()
{
	return K2400->available();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400Plugin::plgVersion() const
///
/// \brief	return the version of the SDK that is needed for run the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceK2400Plugin::plgVersion() const
{
	return QString::number(SDEVICEK2400_VERSION);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400Plugin::SDKVersion() const 
///
/// \brief	return the version of the SDK which is required for this plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceK2400Plugin::SDKVersion() const 
{
	return QString::number(SDEVICEK2400_MAJOR_VERSION_COMPATIBILITY) + 
		QString(".") + QString::number(SDEVICEK2400_MINOR_VERSION_COMPATIBILITY);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400Plugin::unload()
///
/// \brief	this function is call when the plugin is unload
///
/// \author	Sylvain Martin
/// \date	13/01/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400Plugin::unload()
{
	qDebug()  <<" WARNING: unloading of the Keithley 2400 SourceMeter's script object failed \n" ;
	qDebug()  <<" \t because the function is not implanted yet\n" ;

	return true;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
///									IMPLETATION OF SDeviceK2400
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SDeviceK2400.h"
#include "SDKDevice/SInterface/SInterfaceGpib.h"
#include "SDKDevice/SDevice/SDeviceGpib.h"
#include "SDKDevice/SDevice/SDeviceVirtual.h"
#include "SDKDevice/SDevicePluginInterface.h"
#include "SDK/SError.h"
#include "SDKDevice/SDevice/SDeviceError.h"

#include <QtCore>
#include <qdebug>

#include <QObject>

#include <QScriptable>
#include <QScriptEngine>
#include <QScriptValue>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDeviceK2400::SDeviceK2400(QObject *parent)
///
/// \brief	Default constructor. 
///
/// \author	Sylvain Martin
/// \date	1/20/2011
///
/// \param	parent	If non-null, the Qt parent. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SDeviceK2400::SDeviceK2400(QObject *parent) : 
SDeviceGpib(parent){

	//gmdm_ = GlobalMetaDataMap;

	Imax=(1);
	Vmax=(20);
	available_ = false;
	init();

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDeviceK2400::SDeviceK2400(MODE mode, QObject *parent)
///
/// \brief	Constructor. 
///
/// \author	Sylvain Martin
/// \date	1/20/2011
///
/// \param	mode			The mode (CURRENT or VOLTAGE). 
/// \param [in,out]	parent	If non-null, the Qt parent. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SDeviceK2400::SDeviceK2400(MODE mode, QObject *parent): 
SDeviceGpib(parent){

//	gmdm_ = GlobalMetaDataMap;

	Imax=(1);
	Vmax=(20);
	available_ = false;
	init();

	if (available_) setMode(mode);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::available(void)
///
/// \brief	(SCRIPTABLE) Gets the availability. 
///
/// \author	Sylvain Martin
/// \date	1/20/2011
///
/// \return	true if the device is available, false if it is not. 
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400::available(void){
	try{
		elmt_= gpib_->findGpibElement(QString("KEITHLEY INSTRUMENTS INC.,MODEL 2400"));
		available_ = true;
	}catch(SError error){
		available_ = false;
		setMetaData("available",false,"",SMetaData::string);
		return false;
	}
	setMetaData("available",available_);
	return available_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceK2400::current(void)
///
/// \brief	(SCRIPTABLE) Reads the current. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \return	The current in amperes. 
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDeviceK2400::current(void){

	QList<double> res =  readIV();
	setMetaData("current",res.value(0)*MILI,"mA",SMetaData::doublefloat);
	return res.value(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setCurrent(const double current)
///
/// \brief	(SCRIPTABLE) Sets a current. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011. 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE Thrown when Thrown when The device has a problem or is busy.
///
/// \param	current	The current  in amperes. 
/// 				
/// if the \c current is greater than \c Imax fixed with \c setCurrentCompliance, \c current is put
/// at \c Vmax	
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setCurrent(double current){
	if (!available_) sendLogError("setCurrent : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
	if(current>Imax) current = Imax;

	try{
		QString cmd = QString(":SOUR:CURR:LEV ") + QString::number(current);
		gpibSend(cmd);
		setMetaData("current",current*MILI,"mA",SMetaData::doublefloat);
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceK2400::voltage(void)
///
/// \brief	(SCRIPTABLE) Reads the voltage. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \return	The voltage in volts. 
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDeviceK2400::voltage(void){

	QList<double> res =  readVI();
	setMetaData("voltage",res.value(0)*MILI,"mV",SMetaData::doublefloat);
	return res.value(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setVoltage(const double voltage)
///
/// \brief	(SCRIPTABLE) Sets a voltage. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when Thrown when The device has a problem or is busy.or is busy.
///
/// \param	voltage	The voltage in volts. 
/// 				
/// if the \c voltage is greater than \c Vmax fixed with \c setVoltageCompliance, \c voltage is put
/// at \c Vmax		
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setVoltage(double voltage){
	if (!available_) sendLogError("setVoltage : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
	if(voltage>Vmax) voltage = Vmax;


	try{	
		QString cmd = QString(":SOUR:VOLT:LEV ") + QString::number(voltage,'f');
		gpibSend(cmd);
		setMetaData("voltage",voltage*MILI,"mV",SMetaData::doublefloat);
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setMode(const MODE mode)
///
/// \brief	(SCRIPTABLE) change the mode of the DC generator, current or voltage. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when Thrown when The device has a problem or is busy.or is busy. or is busy.
///
/// \param	mode	The mode : CURRENT or VOLTAGE. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setMode(const MODE mode){
	if (!available_) sendLogError("setMode : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

	try{

		switch(mode){
		case CURRENT:
			gpibSend(":SOUR:FUNC CURR");
			gpibSend(":SOUR:CURR:MODE FIX");
			gpibSend(":SENS:FUNC \"VOLT\"");
			setMetaData("mode","current","",SMetaData::string);
			break;

		case VOLTAGE:
			gpibSend(":SOUR:FUNC VOLT");
			gpibSend(":SOUR:VOLT:MODE FIX");
			gpibSend(":SENS:FUNC \"CURR\"");
			setMetaData("mode","voltage","",SMetaData::string);
			break;
		}

		mode_ = mode;
	}catch(SError error){
		SError::traitement(this,error);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setMode( const QString mode )
///
/// \brief	(SCRIPTABLE) change the mode of the DC generator, current or voltage. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when Thrown when The device has a problem or is busy.or is busy. or is busy.
///
/// \param	mode	The mode : CURRENT or VOLTAGE. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  void SDeviceK2400::setMode( const QString mode )
{
	if (mode.trimmed().toUpper() == "CURRENT"){
		setMode(CURRENT);
	}else if(mode.trimmed().toUpper() == "VOLTAGE"){
		setMode(VOLTAGE);
	}else{
		sendLogError("setMode : mode must be \"CURRENT\" or \"VOLTAGE\"");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<double> SDeviceK2400::readVI(void)
///
/// \brief	(INDIRECTLY SCRIPTABLE)Reads the voltage and the current. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when Thrown when The device has a problem or is busy.or is busy..
/// \exception	SDEVICEERROR_CANNOT_CONVERT_DATA		Thrown when the recived data cannot be
/// 													convert. 
///
/// \return	a QList<double> with at(0) the current and at(1) the voltage.  
/// \remark this function is scriptable throuth \c qsReadVI
////////////////////////////////////////////////////////////////////////////////////////////////////
QList<double> SDeviceK2400::readVI(void){
	if (!available_) sendLogError("readVI : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
	QList<double> res;

	try{
		setAutoVoltageRange(false);
		setVoltMeasRange(2);
		gpibSend(":MEAS:VOLT?");
		delay(0.1);
		QVariant read = gpibRead(100);

		if( read.canConvert<QString>() && read.convert(QVariant::String) ){

			QStringList sread= read.toString().split(',',QString::SkipEmptyParts);
			res.append(sread.value(0).toDouble());
			res.append(sread.value(1).toDouble());

			setMetaData("I",sread.value(1,0).toDouble()*MILI,"mA",SMetaData::doublefloat);
			setMetaData("V",sread.value(0,0).toDouble()*MILI,"mV",SMetaData::doublefloat);

			return res;
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;

		}
	}catch(SError error){
		SError::traitement(this,error);
		return res;

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QScriptValue SDeviceK2400::qsReadVI(void)
///
/// \brief	(SCRIPTABLE) Reads the voltage and the current. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \return	a QtScript compatible value containing an array with at(0) the voltage and at(1) the current 
///
/// \remark this function is especially implanted to be used in script module, do not use it in a c++
///			module, you can call it \c readVI because of an overload in the script engine.
////////////////////////////////////////////////////////////////////////////////////////////////////
QScriptValue SDeviceK2400::qsReadVI(void){


	QString qsCmd;
	QTextStream qtsCmd(&qsCmd);
	QScriptValue res;

	try{

		QList<double> IV = readVI();

		if(IV.count() ==2){
			qtsCmd << "new Array(" << IV.at(0) <<" , " << IV.at(1) << ")" ;
		}else{
			qtsCmd << "new Array(0,0)";
			qDebug() << ("ERROR (SCRIPT) : readVI fail ");
		}

		qsCmd = qtsCmd.readAll();

		res = this->engine()->evaluate(qsCmd);
	}catch(SError error){
		qtsCmd << "new Array(0 , 0)" ;
		qDebug() << error;
		res = this->engine()->evaluate(qsCmd);
	}
	return res;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<double> SDeviceK2400::readIV(void)
///
/// \brief	(INDIRECTLY SCRIPTABLE)Reads the current and the voltage. 
///
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when Thrown when The device has a problem or is busy.or is busy.
/// \exception	SDEVICEERROR_CANNOT_CONVERT_DATA		Thrown when the function cannot convert
/// 													the read data into double. 
///
/// \return	a QList<double> with at(0) the current and at(1) the voltage. 
/// \remark this function is scriptable throuth \c qsReadIV
////////////////////////////////////////////////////////////////////////////////////////////////////
QList<double> SDeviceK2400::readIV(void){
	if (!available_) sendLogError("readIV : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
	QList<double> res;


	try{
		gpibSend(":MEAS:CURR?");
		delay(0.1);		
		QVariant read = gpibRead(100);

		if( read.canConvert<QString>() && read.convert(QVariant::String) ){

			QStringList sread= read.toString().split(',',QString::SkipEmptyParts);

			res.append(sread.at(1).toDouble());
			res.append(sread.at(0).toDouble());

			setMetaData("I",sread.at(1).toDouble()*MILI,"mA",SMetaData::doublefloat);
			setMetaData("V",sread.at(0).toDouble()*MILI,"mV",SMetaData::doublefloat);

			return res;
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}
	}catch(SError error){
		SError::traitement(this,error);
		return res;

	}	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QScriptValue SDeviceK2400::qsReadIV(void)
///
/// \brief	(SCRIPTABLE) Reads the current and the voltage. 
///
/// \return	a QtScript compatible value containing an array with at(0) the current and at(1) the voltage 
///
/// \remark this function is especially implanted to be used in script module, do not use it in a c++
///			module, you can call it \c readIV because of an overload in the script engine.
////////////////////////////////////////////////////////////////////////////////////////////////////
QScriptValue SDeviceK2400::qsReadIV(void){

	QString qsCmd;
	QTextStream qtsCmd(&qsCmd);

	QScriptValue res;

	try{
		QList<double> IV = readIV();

		if(IV.count() ==2){
			qtsCmd << "new Array(" << IV.at(0) <<" , " << IV.at(1) << ")" ;
		}else{
			qtsCmd << "new Array(0,0)";
			qDebug() << ("ERROR (SCRIPT) : readIV fail ");
		}
		qsCmd = qtsCmd.readAll();

		res = this->engine()->evaluate(qsCmd);
	}catch(SError error){
		qtsCmd << "new Array(0 , 0)" ;
		SError::traitement(this,error);
		res = this->engine()->evaluate(qsCmd);
	}

	return res;


}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setCurrentRange(double Imax)
///
/// \brief	(SCRIPTABLE) Sets the current limit. 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when Thrown when The device has a problem or is busy.or is busy.
///
/// \param	Imax	The maximum current.  
///
/// \remark Is not the same thing that the compliance. the current range  gives a range (µA, mA, ...)  
/// 		 the compliance sets a security limit
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setCurrentRange(double Imax){

	try{	
		if (!available_) sendLogError("setCurrentRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd = QString(":SOUR:CURR:RANG ") + QString::number(Imax,'f');
		gpibSend(cmd);
		setMetaData("currentRange",Imax*MILI,"mA",SMetaData::doublefloat);
	}catch(SError error){
		SError::traitement(this,error);
	}

	this->Imax = Imax;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setVoltageRange(double Vmax)
///
/// \brief	(SCRIPTABLE) Sets a voltage limit (compliance). 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when Thrown when The device has a problem or is busy.or is busy.
///
/// \param	Vmax	The  maximum Voltage. 
/// 				
/// \remark Is not the same thing that the compliance. the current range gives a range(µV,mV,..), 
/// 		 the compliance sets a security limit
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setVoltageRange(double Vmax){

	try{	
		if (!available_) sendLogError("setVoltageRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString(":SOUR:VOLT:RANG ") + QString::number(Vmax,'f');
		gpibSend(cmd);
		setMetaData("voltageRange",Vmax,"V",SMetaData::doublefloat);
	}catch(SError error){
		SError::traitement(this,error);
	}

	this->Vmax = Vmax;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setVoltMeasRange(double Vm)
///
/// \brief	(SCRIPTABLE) Sets the Voltage range when current source. 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when Thrown when The device has a problem or is busy.or is busy.
///
/// \param	Vm	voltage range.  
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setVoltMeasRange(double Vm){

	try{	
		if (!available_) sendLogError("setVoltMeasRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd = QString(":SENS:VOLT:RANG ") + QString::number(Vm,'f');
		gpibSend(cmd);
		setMetaData("voltageMeasRange",Vm,"V",SMetaData::doublefloat);
	}catch(SError error){
		SError::traitement(this,error);
	}

	//this->Vm = Vm;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceK2400::currentRange(void)
///
/// \brief	(SCRIPTABLE) Gets the current limit. 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when Thrown when The device has a problem or is busy.or is busy.
/// \exception	SDEVICEERROR_CANNOT_CONVERT_DATA		Thrown when the function cannot convert
/// 													the read data into double. 
/// 													
/// \remark Is not the same thing that the compliance. the range limit gives a range (µA, mA, ...) 
/// 		 the compliance sets a security limit
/// 		
/// \return	the current limit. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDeviceK2400::currentRange(void){

	try{	
		if (!available_) sendLogError("currentRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString(":SOUR:CURR:RANG?");
		gpibSend(cmd);

		QVariant read = gpibRead();
		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			this->Imax = read.toDouble();
			setMetaData("currentRange",read.toDouble()*MILI,"mA",SMetaData::doublefloat);
			return read.toDouble();
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;

		}
	}catch(SError error){
		SError::traitement(this,error);
	}
	return (0.0); // pour faire plaisir au compilo
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceK2400::voltageLimit(void)
///
/// \brief	(SCRIPTABLE) Gets the voltage limit. 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when The device has a problem or is busy.
/// \exception	SDEVICEERROR_CANNOT_CONVERT_DATA		Thrown when the function cannot convert
/// 													the read data into double. 
/// 													
/// \remark Is not the same thing that the compliance. the voltage range  gives a range (µA, mA, ...) 
/// 		 the compliance sets a security limit
/// 		
/// \return	the voltage limit. 
///
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDeviceK2400::voltageRange(void){

	try{	
		if (!available_) sendLogError("voltageRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd = QString(":SOUR:VOLT:RANG?");
		gpibSend(cmd);

		QVariant read = gpibRead();
		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			this->Vmax = read.toDouble();
			setMetaData("voltageRange",read.toDouble()*MILI,"mV",SMetaData::doublefloat);
			return read.toDouble();
			
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;

		}
	}catch(SError error){
		SError::traitement(this,error);
	}

	return (0.0); // pour faire plaisir au compilo
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::init(void)
///
/// \brief	Initializes the K2400 device. 
///
/// this function is automatically call at the initialization of this object
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::init(void){
	
	setMetaData("activate", "N/A","",SMetaData::boolean);
	setMetaData("available", "N/A","",SMetaData::boolean);
	setMetaData("V", "N/A","mV",SMetaData::doublefloat);
	setMetaData("I", "N/A","mA",SMetaData::doublefloat);
	setMetaData("voltageRange", "N/A","mV",SMetaData::doublefloat);
	setMetaData("currentRange", "N/A","mA",SMetaData::doublefloat);
	setMetaData("voltageCompliance","N/A","mV",SMetaData::doublefloat);
	setMetaData("currentCompliance", "N/A","mA",SMetaData::doublefloat);
	setMetaData("Imax", "N/A","mA",SMetaData::doublefloat);
	setMetaData("Vmax", "N/A","mV",SMetaData::doublefloat);
	setMetaData("autoVoltageRange","N/A","",SMetaData::boolean);
	setMetaData("autoCurrentRange","N/A","",SMetaData::boolean);


	try{
		gpib_ =  SInterfaceGpib::instance();
		elmt_= gpib_->findGpibElement(QString("KEITHLEY INSTRUMENTS INC.,MODEL 2400"));

		if (!(elmt_.PAD ==-1)) available_ = true;


	}catch(SError error){
		if (!(error == SDEVICEERROR_GPIB_FINDLSTN) && !(error ==SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE)){
			SError::traitement(this,error);	
		}else{

			this->setUnavailable();
			qDebug() << "the Keithley 2400 cannot be found";
		}

	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400::description(void) const
///
/// \brief	(SCRIPTABLE) Gets the description of the device. 
///
/// \return	the brief description of the device. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceK2400::description(void) const{

	QString des	= "Keithley 2400 is designed";
	des	+=" specifically for test applications that demand tightly";
	des	+="coupled sourcing and measurement.\n All SourceMeter models";
	des	+="provide precision voltage and current sourcing as well ";
	des	+="as measurement capabilities. Each SourceMeter instrument ";
	des	+="is both a highly stable DC power source and a true ";
	des	+="instrument-grade 5-1/2 digit multimeter. The power ";
	des	+="source characteristics include low noise, precision, ";
	des	+="and readback. The multimeter capabilities include high ";
	des	+="repeatability and low noise. The result is a compact, ";
	des	+="single-channel, DC parametric tester. In operation, ";
	des	+="these instruments can act as a voltage source, a ";
	des	+="current source, a voltage meter, a current meter, ";
	des	+="and an ohmmeter.";

	return des;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::activate()
///
/// \brief	(SCRIPTABLE) Activates the DC generator. 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when The device has a problem or is busy. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::activate(){


	try{
		if (!available_) sendLogError("setAutoCurrentRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd = QString("OUTP ON");
		gpibSend(cmd);
		setMetaData("activate",true,"",SMetaData::boolean);
	}catch(SError error){
		SError::traitement(this,error);
		setMetaData("activate",false);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::deactivate(void)
///
/// \brief	(SCRIPTABLE) Deactivates the DC generator. 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when The device has a problem or is busy.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::deactivate(void){


	try{
		if (!available_) sendLogError("setAutoCurrentRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd = QString("OUTP OFF");
		gpibSend(cmd);
		setMetaData("activate",false,"",SMetaData::boolean);
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setCurrentCompliance(double Icomp)
///
/// \brief	(SCRIPTABLE) Sets a current compliance (limit of protection). 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when The device has a problem or is busy.
/// 													
/// \remark Is not the same thing that the current limit. the current range give a range(µA,mA,..), 
/// 		the compliance is for security reasons.
/// 		
/// \param	Icomp	the current compliance. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setCurrentCompliance(const double Icomp){


	try{
		if (!available_) sendLogError("setCurrentCompliance : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd = QString(":SENSe:CURR:PROT ") + QString::number(Icomp,'f');;
		gpibSend(cmd);
		Imax = Icomp;
		setMetaData("currentCompliance",Icomp*MILI,"mA",SMetaData::doublefloat);
		setMetaData("Imax", Icomp*MILI,"mA",SMetaData::doublefloat);
	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceK2400::currentCompliance(void)
///
/// \brief	(SCRIPTABLE) Reads the current compliance (limit of protection). 
///
/// 													
/// \remark Is not the same thing that the current limit. the current range give a range(µV,mV,..), 
/// 		the compliance is for security reasons.
/// 		
/// \return	The current compliance. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDeviceK2400::currentCompliance(void){


	try{	
		if (!available_) sendLogError("currentCompliance : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd = QString(":SENSe:CURR:PROT?");
		gpibSend(cmd);

		QVariant read = gpibRead();
		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			this->Vmax = read.toDouble();
			setMetaData("currentCompliance",read.toDouble()*MILI,"mA",SMetaData::doublefloat);
			setMetaData("Imax", read.toDouble()*MILI,"mA",SMetaData::doublefloat);
			return this->Vmax;
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;

		}
	}catch(SError error){
		SError::traitement(this,error);
	}
	return (0.0); // pour faire plaisir au compilo
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setVoltageCompliance(double Vcomp)
///
/// \brief	(SCRIPTABLE) Sets a voltage compliance (limit of protection). 
///
///
/// \remark Is not the same thing that the voltage limit. the voltage range give a range(µV,mV,..), 
/// 		the compliance is for security reasons.
/// 		
/// \param	Vcomp	The voltage. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setVoltageCompliance(const double Vcomp){


	try{ 
		if (!available_) sendLogError("setVoltageCompliance : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd = QString(":SENSe:VOLT:PROT ") + QString::number(Vcomp,'f');;
		gpibSend(cmd);
		Vmax=Vcomp;
		setMetaData("voltageCompliance",Vcomp*MILI,"mV",SMetaData::doublefloat);
		setMetaData("Vmax", Vcomp*MILI,"mV",SMetaData::doublefloat);
	}catch(SError error){
		SError::traitement(this,error);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceK2400::voltageCompliance(void)
///
/// \brief	(SCRIPTABLE) Reads the voltage compliance (limit of protection). 
///
/// \remark Is not the same thing that the voltage limit. the voltage limit give a range, 
/// 		the compliance is for security raesons.
/// 		
/// \return	The voltage compliance. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
double SDeviceK2400::voltageCompliance(void){


	try{
		if (!available_) sendLogError("voltageCompliance : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd = QString(":SENSe:VOLT:PROT?");
		gpibSend(cmd);

		QVariant read = gpibRead();
		if( read.canConvert<double>() && read.convert(QVariant::Double) ){
			this->Vmax = read.toDouble();
			setMetaData("voltageCompliance",read.toDouble()*MILI,"mV",SMetaData::doublefloat);
			setMetaData("Vmax", read.toDouble()*MILI,"mV",SMetaData::doublefloat);
			return this->Vmax;
			
		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;

		}
	}catch(SError error){
		SError::traitement(this,error);
	}
	return (0.0); // pour faire plaisir au compilo
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::putLocalMode(void)
///
/// \brief	(SCRIPTABLE) Puts in local mode (the user can use the front keys). 
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when The device has a problem or is busy.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::putLocalMode(void){
	try{
		if (!available_) sendLogError("putLocalMode : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		gpib_->enableLocal(elmt_);
	}catch(SError error){
		SError::traitement(this,error);
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setMetaData( QString key, QVariant value )
///
/// \brief	Change the value of the metadata for this device in the global map SGlobalMetaDataMap 
///
/// \param the key in the sub map of metatdata for this device
/// \param value the value corresponding of the key
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setMetaData( const QString key, const QVariant value, const QString unit, const SMetaData::enumType type)
{
	
   if(metaDataOnOff_) gmdm_.setMetaData(QString(SDEVICEK2400_SHORT_NAME),key,value, unit , type);
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDevicePSAE4440A::metaDataOnOff( bool onOff )
///
/// \brief	activate or deactivate the Global Metadata System
///
/// \param onOff in the sub map of metatdata for this device
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::metaDataOnOff( bool onOff )
{
	metaDataOnOff_ = onOff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceK2400::setAutoCurrentRange( bool onOff )
///
/// \brief	activate or deactivate the auto current range function.
///
/// \param onOff true activate, false deactivate.
///
/// \sa void SDeviceK2400::autoVoltageRange()
/// \sa void SDeviceK2400::setAutoVoltageRange( bool onOff )
/// \sa bool SDeviceK2400::autoCurrentRange()
///
/// Auto range limits are included to support the auto range change mode. F or voltage and
/// current, the upper limit is controlled by the compliance range and cannot be programmed.
/// For the auto ohms mode, however, the lower limit is adjustable. The lower limit for all
/// three functions is programmable and must be less than or equal to the upper limit. If the
/// lower limit is equal to the upper limit, auto ranging is effectively disabled. When auto
/// ranging is disabled, you can manually change to any range below the lower limit (V, I or
/// Ohms) or any range above the upper limit (Ohms only).
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceK2400::setAutoCurrentRange( bool onOff )
{
	
	try{ 
		if (!available_) sendLogError("setAutoCurrentRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd;

		if (onOff){
			cmd = QString(":SENSe:CURRent:RANGe:AUTO ON");
		}else{
		   cmd = QString(":SENSe:CURRent:RANGe:AUTO OFF");
		}


		gpibSend(cmd);

		setMetaData("autoCurrentRange",onOff,"",SMetaData::boolean);


	}catch(SError error){
		SError::traitement(this,error);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 void SDeviceK2400::setAutoVoltageRange( bool onOff )
///
/// \brief	activate or deactivate the auto voltage range function
///
/// \param onOff true activate, false deactivate
///
/// \sa void SDeviceK2400::autoVoltageRange()
/// \sa void SDeviceK2400::setAutoCurrentRange( bool onOff )
/// \sa bool SDeviceK2400::autoCurrentRange()
///
/// Auto range limits are included to support the auto range change mode. F or voltage and
/// current, the upper limit is controlled by the compliance range and cannot be programmed.
/// For the auto ohms mode, however, the lower limit is adjustable. The lower limit for all
/// three functions is programmable and must be less than or equal to the upper limit. If the
/// lower limit is equal to the upper limit, auto ranging is effectively disabled. When auto
/// ranging is disabled, you can manually change to any range below the lower limit (V, I or
/// Ohms) or any range above the upper limit (Ohms only).
////////////////////////////////////////////////////////////////////////////////////////////////////
 void SDeviceK2400::setAutoVoltageRange( bool onOff )
{
	try{ 
		if (!available_) sendLogError("setAutoVoltageRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
		QString cmd;

		if (onOff){
			cmd = QString(":SENSe:VOLTage:RANGe:AUTO ON");
		}else{
			cmd = QString(":SENSe:VOLTage:RANGe:AUTO OFF");
		}

		gpibSend(cmd);
		setMetaData("autoVoltageRange",onOff,"",SMetaData::boolean);


	}catch(SError error){
		SError::traitement(this,error);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::autoCurrentRange()
///
/// \brief	read if the auto current range function is activated or deactivated 
///
/// \return true activate, false deactivate
///
/// \sa void SDeviceK2400::autoVoltageRange()
/// \sa void SDeviceK2400::setAutoVoltageRange( bool onOff )
/// \sa void SDeviceK2400::setAutoCurrentRange( bool onOff )
///
/// Auto range limits are included to support the auto range change mode. F or voltage and
/// current, the upper limit is controlled by the compliance range and cannot be programmed.
/// For the auto ohms mode, however, the lower limit is adjustable. The lower limit for all
/// three functions is programmable and must be less than or equal to the upper limit. If the
/// lower limit is equal to the upper limit, auto ranging is effectively disabled. When auto
/// ranging is disabled, you can manually change to any range below the lower limit (V, I or
/// Ohms) or any range above the upper limit (Ohms only).
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400::autoCurrentRange()
{

	try{
		if (!available_) sendLogError("autoCurrentRange : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString(":SENSe:CURRent:RANGe:AUTO?");
		gpibSend(cmd);

		QVariant read = gpibRead();
		if( read.canConvert<bool>() && read.convert(QVariant::Bool) ){
			bool autoCurrentRange_ = read.toBool();

			setMetaData("autoCurrentRange",autoCurrentRange_,"",SMetaData::boolean);
			return autoCurrentRange_;

		}else{
			sendLogError("autoCurrentRange : " + STRING_ERROR_CANNOT_CONVERT_DATA);
			return false;
		}
	}catch(SError error){
		SError::traitement(this,error);
	}
	return (false); // pour faire plaisir au compilo
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::autoCurrentRange()
///
/// \brief	read if the auto voltage range function is activated or deactivated 
///
/// \return true activate, false deactivate
///
/// \sa void SDeviceK2400::setAutoVoltageRange( bool onOff )
/// \sa void SDeviceK2400::setAutoCurrentRange( bool onOff )
/// \sa bool SDeviceK2400::autoCurrentRange()
///
/// Auto range limits are included to support the auto range change mode. F or voltage and
/// current, the upper limit is controlled by the compliance range and cannot be programmed.
/// For the auto ohms mode, however, the lower limit is adjustable. The lower limit for all
/// three functions is programmable and must be less than or equal to the upper limit. If the
/// lower limit is equal to the upper limit, auto ranging is effectively disabled. When auto
/// ranging is disabled, you can manually change to any range below the lower limit (V, I or
/// Ohms) or any range above the upper limit (Ohms only).
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  bool SDeviceK2400::autoVoltageRange()
{
	try{
		if (!available_) throw SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE;
		QString cmd = QString(":SENSe:VOLTage:RANGe:AUTO?");
		gpibSend(cmd);

		QVariant read = gpibRead();
		if( read.canConvert<bool>() && read.convert(QVariant::Bool) ){
			bool autoVoltageRange_ = read.toBool();

			setMetaData("autoVoltageRange",autoVoltageRange_,"",SMetaData::boolean);
			return autoVoltageRange_;

		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;

		}
	}catch(SError error){
		SError::traitement(this,error);
	}
	return (false); // pour faire plaisir au compilo
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceK2400::isActivated( )
///
/// \brief	read if the auto voltage range function is activated or deactivated 
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
/// \return true if it is activate, false if it is deactivate
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceK2400::isActivated( ){

	return isActivated_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDeviceK2400::MODE SDeviceK2400::mode( )
///
/// \brief	Gets the mode of the generator (Scriptable through qsMode)
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
/// \return return the mode of the DC source Current or Voltage.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SDeviceK2400::MODE SDeviceK2400::mode( ) {

	return mode_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 QString SDeviceK2400::qsMode()
///
/// \brief	(SCRIPTABLE) Gets the mode of the generator
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
/// \return return the mode of the DC source CURRENT or VOLTAGE.
///
///
/// In the script you can call "mode()" for this function
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  QString SDeviceK2400::qsMode()
{
 if(mode_ == CURRENT) {
	 return "CURRENT";
 }else{
	 return "VOLTAGE";
 }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SDeviceVisa::sendLogError( QString log )
///
/// \brief	Emit a signal because of an error
/// 
/// \param the description of the error
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SDeviceK2400::sendLogError( QString log )
{
	emit logError(QString("WARNING : VISA :An error occurred opening a session to"), SDEVICEK2400_SHORT_NAME);
}
