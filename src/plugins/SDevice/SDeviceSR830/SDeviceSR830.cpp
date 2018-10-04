
#include "SDeviceSR830.h"
#include "SDKDevice/SDevice/SDeviceError.h"
#include <QtCore>
#include <SDKDevice/SDevicePluginInterface.h>



Q_EXPORT_PLUGIN2("SDeviceSR830", SDeviceSR830Plugin)

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	SDeviceK2400Plugin::SDeviceK2400Plugin()
	///
	/// \brief	constructor
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
SDeviceSR830Plugin::SDeviceSR830Plugin():state_(2),SR830(NULL)
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
SDeviceSR830Plugin::~SDeviceSR830Plugin()
{
	if(SR830!=NULL)
		delete SR830;

	SGlobalMetaDataMap gmdm_;
	gmdm_.clear(QString(SDEVICESR830_SHORT_NAME));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceSR830Plugin::load()
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
bool SDeviceSR830Plugin::load()
{
	//gmdm_ = GlobalMetaDataMap;
	SR830 = new SDeviceSR830(this);

	this->connect(SR830,SIGNAL(logError(QString, QString)),SIGNAL(logError(QString, QString)));
	this->connect(SR830,SIGNAL(logEvent(QString, QString)),SIGNAL(logEvent(QString, QString)));

	if(SR830->available()) state_=0;
	return SR830->available();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceSR830Plugin::name() const
///
/// \brief	return the complete name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceSR830Plugin::name() const
{
	return QString("Stanford Research Systems , SR830");
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
QString SDeviceSR830Plugin::shortName() const
{
	return QString(SDEVICESR830_SHORT_NAME);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceSR830Plugin::description() const
///
/// \brief	return the description of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the description of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceSR830Plugin::description() const
{
	QString des	= "Lock-in SR830";

	return des;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceSR830Plugin::scriptable( QScriptEngine * engine )
///
/// \brief	add (or not) some functions to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isScriptable
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceSR830Plugin::scriptable( QScriptEngine * engine )
{
	static bool initialized = false;

	if(!initialized){ // evite le multi initialitation
		try{
			initialized = true;

			SDeviceSR830* SR830Script = new SDeviceSR830();
			this->connect(SR830Script,SIGNAL(logError(QString,QString)),SIGNAL(logError(QString,QString)));
			this->connect(SR830Script,SIGNAL(logEvent(QString,QString)),SIGNAL(logEvent(QString,QString)));


			
			QScriptValue qsvSDeviceSR830 = engine->newQObject(SR830Script,QScriptEngine::ScriptOwnership);
			QScriptValue qsvMetaSDeviceSR830 = engine->newQMetaObject(SR830Script->metaObject());

			engine->globalObject().setProperty("SR830", qsvSDeviceSR830);
			engine->globalObject().setProperty("SDeviceSR830", qsvMetaSDeviceSR830); // Pour les Enums

		//	engine->evaluate("K2400.readIV = K2400.qsReadIV; K2400.readVI = K2400.qsReadVI;\n","Initialization");
		//	engine->evaluate("K2400.CURRENT = \"CURRENT\"; K2400.VOLTAGE = \"VOLTAGE\";\n","Initialization");
		//	engine->evaluate("K2400.mode = K2400.qsMode;\n","Initialization");


			qDebug()  << "SR 830 Lock-in found";

			if(!SR830->available()){
				initialized = false;
				qDebug()  << "SR830 Lock-in cannot be found";
				engine->evaluate("var SR830 = new Object(); SR830.available = false;","Initialization");
			}
		}catch(SError error){
			initialized = false;
			engine->evaluate("var SR830 = new Object(); SR830.available = false;","Initialization");
			qDebug()  <<" ERROR (LOW): initialization of the SR830 Lock-in's script object failed" 
				<< error;
			return false;

		}
	}


	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceSR830Plugin::isScriptable()
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
bool SDeviceSR830Plugin::isScriptable()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceSR830Plugin::isControlPanel()
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
bool SDeviceSR830Plugin::isControlPanel()
{
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceSR830Plugin::controlPanel() const
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
QWidget * SDeviceSR830Plugin::controlPanel(QWidget * parent /*= NULL*/)
{

	QWidget * CtrlPanel = new QWidget();
	return CtrlPanel;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceSR830Plugin::isSetting()
///
/// \brief	does the plugin have a setting window ?
///
/// \author	Sylvain Martin
/// \date	25/02/2012
/// \sa SDeviceK2400Plugin::controlPanel
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceSR830Plugin::isSetting()
{
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QWidget* SDeviceSR830Plugin::controlPanel()
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
QWidget * SDeviceSR830Plugin::setting(QWidget * parrent /*= NULL*/ )
{
	QWidget * widSetting = new QWidget(parrent); //!TODO ALL !!!
	return widSetting;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceSR830Plugin::shutdown()
///
/// \brief	shutdown the plugin (by example before closing the application)
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceSR830Plugin::shutdown()
{
//	K2400->deactivate();
	state_=2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SDeviceSR830Plugin::state()
///
/// \brief	what is the state of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// 0 : ready, 1 : busy, 2 unavailable
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDeviceSR830Plugin::state()
{
	return state_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceSR830Plugin::available()
///
/// \brief	is the plugin available ?
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceSR830Plugin::available()
{
	return SR830->available();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceSR830Plugin::plgVersion() const
///
/// \brief	return the version of the SDK that is needed for run the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceSR830Plugin::plgVersion() const
{
	return QString::number(SDEVICESR830_VERSION);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceSR830Plugin::SDKVersion() const 
///
/// \brief	return the version of the SDK which is required for this plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceSR830Plugin::SDKVersion() const 
{
	return QString::number(SDEVICESR830_MAJOR_VERSION_COMPATIBILITY) + 
		QString(".") + QString::number(SDEVICESR830_MINOR_VERSION_COMPATIBILITY);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceSR830Plugin::unload()
///
/// \brief	this function is call when the plugin is unload
///
/// \author	Sylvain Martin
/// \date	13/01/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceSR830Plugin::unload()
{
	qDebug()  <<" WARNING: unloading of the SR830 lock-in's script object failed \n" ;
	qDebug()  <<" \t because the function is not implanted yet\n" ;

	return true;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDeviceSR830::SDeviceSR830()
///
/// \brief	Default constructor.
///
/// \author	Sylvain Martin
/// \date	28/03/2013
////////////////////////////////////////////////////////////////////////////////////////////////////

SDeviceSR830::SDeviceSR830(QObject *parent):SDeviceGpib(parent)
{
	available_ = false;
	init();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SDeviceSR830::~SDeviceSR830()
///
/// \brief	Destructor.
///
/// \author	Sylvain Martin
/// \date	28/03/2013
////////////////////////////////////////////////////////////////////////////////////////////////////

SDeviceSR830::~SDeviceSR830()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE void SDeviceSR830::setFrequency( double freq )
///
/// \brief	(SCRIPTABLE) Sets the frequency in Hz.
///
/// \author	Sylvain Martin
/// \date	28/03/2013
///
/// \param	freq	The frequency.
////////////////////////////////////////////////////////////////////////////////////////////////////

void SDeviceSR830::setFrequency( double freq )
{
	try{	
		if (!available_) sendLogError("setFrequency : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("FREQ") + QString::number(freq,'f');

		gpibSend(cmd);

		setMetaData("Frequency",freq,"Hz",SMetaData::doublefloat);


	}catch(SError error){

		SError::traitement(this,error);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceSR830::setPhase( double phase )
///
/// \brief	Sets a phase.
///
/// \author	Sylvain Martin
/// \date	03/04/2013
///
/// \param	phase	The phase.
////////////////////////////////////////////////////////////////////////////////////////////////////

void SDeviceSR830::setPhase( double phase )
{
	try{	
		if (!available_) sendLogError("setPhase : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("PHAS") + QString::number(phase);

		gpibSend(cmd);

		setMetaData("Phase",phase,"degres",SMetaData::doublefloat);


	}catch(SError error){

		SError::traitement(this,error);
	}

}

void SDeviceSR830::setAmplitude( double amplitude )
{
	try{	
		if (!available_) sendLogError("setAmplitude : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("SLVL") + QString::number(amplitude);

		gpibSend(cmd);

		setMetaData("Amplitude",amplitude,"V",SMetaData::doublefloat);


	}catch(SError error){

		SError::traitement(this,error);
	}

}

void SDeviceSR830::setX()
{
	try{	
		if (!available_) sendLogError("setX : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("DDEF") + QString::number(1) + QString(",") + QString::number(0) + QString(",") + QString::number(0);
	

		gpibSend(cmd);

		//setMetaData("X ",true,"",SMetaData::boolean);

	}catch(SError error){
		SError::traitement(this,error);
		//setMetaData("X",false);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceSR830::X()
///
/// \brief	(SCRIPTABLE)get the X value cf. lockin doc...
///
/// \author	Sylvain Martin
/// \date	03/04/2013
////////////////////////////////////////////////////////////////////////////////////////////////////

double SDeviceSR830::X()
{
	double res;
	try{	
		if (!available_) sendLogError("X : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("OUTP? 1") ;
		gpibSend(cmd);
		delay(0.1);
		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){

			res = read.toDouble();
			setMetaData("X",read.toDouble(),"V",SMetaData::doublefloat);
			return res;

		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
	}

}

void SDeviceSR830::setY()
{
	try{	
		if (!available_) sendLogError("setY : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("DDEF") + QString::number(2) + QString(",") + QString::number(0) + QString(",") + QString::number(0);


		gpibSend(cmd);

		//setMetaData("Y",true,"",SMetaData::boolean);

	}catch(SError error){
		SError::traitement(this,error);
		//setMetaData("Y",false);
	}

}

double SDeviceSR830::Y()
{
	double res;
	try{	
		if (!available_) sendLogError("Y : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("OUTP? 2") ;
		gpibSend(cmd);
		delay(0.1);
		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){

			res = read.toDouble();
			setMetaData("Y",read.toDouble(),"V",SMetaData::doublefloat);
			return res;

		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
	}

}

void SDeviceSR830::setR()
{
	try{	
		if (!available_) sendLogError("setR : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("DDEF") + QString::number(1) + QString(",") + QString::number(1) + QString(",") + QString::number(0);


		gpibSend(cmd);

		//setMetaData("R",true,"",SMetaData::boolean);

	}catch(SError error){
		SError::traitement(this,error);
		//setMetaData("R",false);
	}

}

double SDeviceSR830::R()
{
	double res;
	try{	
		if (!available_) sendLogError("R : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("OUTP? 3") ;
		gpibSend(cmd);
		delay(0.1);
		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){

			res = read.toDouble();
			setMetaData("R",read.toDouble(),"V",SMetaData::doublefloat);
			return res;

		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
	}

}

void SDeviceSR830::setTheta()
{
	try{	
		if (!available_) sendLogError("setTheta : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("DDEF") + QString::number(2) + QString(",") + QString::number(1) + QString(",") + QString::number(0);


		gpibSend(cmd);

		//setMetaData("Theta",true,"",SMetaData::boolean);

	}catch(SError error){
		SError::traitement(this,error);
		//setMetaData("Theta",false);
	}

}

double SDeviceSR830::Theta()
{
	double res;
	try{	
		if (!available_) sendLogError("Theta : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("OUTP? 4") ;
		gpibSend(cmd);
		delay(0.1);
		QVariant read = gpibRead(100);

		if( read.canConvert<double>() && read.convert(QVariant::Double) ){

			res = read.toDouble();
			setMetaData("Theta",read.toDouble(),"degres",SMetaData::doublefloat);
			return res;

		}else{
			throw SDEVICEERROR_CANNOT_CONVERT_DATA;
		}

	}catch(SError error){
		SError::traitement(this,error);
	}

}

void SDeviceSR830::AutoPhase()
{
	try{	
		if (!available_) sendLogError("AutoPhase : " + STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

		QString cmd = QString("APHS");


		gpibSend(cmd);

		//setMetaData("AutoPhase",true,"",SMetaData::boolean);

	}catch(SError error){
		SError::traitement(this,error);
		//setMetaData("AutoPhase",false);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceSR830::init(void)
///
/// \brief	Initializes the SR830 device. 
///
/// this function is automatically call at the initialization of this object
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceSR830::init(void){

	setMetaData("activate", "N/A","",SMetaData::boolean);
	setMetaData("available", "N/A","",SMetaData::boolean);
	setMetaData("Frequency", "N/A","Hz",SMetaData::doublefloat);



	try{
		gpib_ =  SInterfaceGpib::instance();
		elmt_= gpib_->findGpibElement(QString("Stanford_Research_Systems,SR830"));

		if (!(elmt_.PAD ==-1)) available_ = true;


	}catch(SError error){
		if (!(error == SDEVICEERROR_GPIB_FINDLSTN) && !(error ==SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE)){
			SError::traitement(this,error);	
		}else{

			this->setUnavailable();
			qDebug() << "the Stanford Research 830 cannot be found";
		}

	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceSR830::description(void) const
///
/// \brief	(SCRIPTABLE) Gets the description of the device. 
///
/// \return	the brief description of the device. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceSR830::description(void) const{

		QString des	= "Stanford Research 830 Lock-in";

		return des;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceSR830::available(void)
///
/// \brief	(SCRIPTABLE) Gets the availability. 
///
/// \author	Sylvain Martin
/// \date	1/20/2011
///
/// \return	true if the device is available, false if it is not. 
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceSR830::available(void){

	try{

		elmt_= gpib_->findGpibElement(QString("Stanford_Research_Systems,SR830"));
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
/// \fn	void SDeviceSR830::sendLogError( QString log )
///
/// \brief	Sends error to the log.
///
/// \author	Sylvain Martin
/// \date	28/03/2013
///
/// \param	log	The log.
////////////////////////////////////////////////////////////////////////////////////////////////////

void SDeviceSR830::sendLogError( QString log ){

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceSR830::setMetaData( QString key, QVariant value )
///
/// \brief	Change the value of the metadata for this device in the global map SGlobalMetaDataMap 
///
/// \param the key in the sub map of metatdata for this device
/// \param value the value corresponding of the key
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceSR830::setMetaData( const QString key, const QVariant value, const QString unit, const SMetaData::enumType type)
{

	if(metaDataOnOff_) gmdm_.setMetaData(QString(SDEVICESR830_SHORT_NAME),key,value, unit , type);

}