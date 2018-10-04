////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceK2400.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/12/2011
///
/// \brief	Implements the SDevicek2400 class
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

#include "SDeviceApsin20g.h"
#include "SUiCpApsin20g.h"
#include <QtCore>
#include <QScriptEngine>
#include <QScriptValue>

#include <qdebug.h>

#include "SDKDevice/SDevicePluginInterface.h"
#include "SDKDevice\visa32\visa.h"
#include <string.h>

Q_EXPORT_PLUGIN2("SDeviceApsin20g", SDeviceApsin20gPlugin)



SDeviceApsin20gPlugin::SDeviceApsin20gPlugin():state_(2),Apsin20g(NULL)
{

}

SDeviceApsin20gPlugin::~SDeviceApsin20gPlugin()
{
	if(Apsin20g!=NULL)
		delete Apsin20g;

	SGlobalMetaDataMap gmdm_;
	gmdm_.clear(QString(ASPIN20G_SHORT_NAME));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceApsin20gPlugin::load()
///
/// \brief	initialize the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceApsin20gPlugin::load()
{
	
	Apsin20g = new SDeviceApsin20g();

	if(Apsin20g->available()) state_=0;
	return Apsin20g->available();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceApsin20gPlugin::name() const
///
/// \brief	return the complete name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceApsin20gPlugin::name() const
{
	return QString("APSIN20G 10MHZ - 20GHZ");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceApsin20gPlugin::shortName() const
///
/// \brief	return the short name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the short name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceApsin20gPlugin::shortName() const
{
		return QString(ASPIN20G_SHORT_NAME);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceApsin20gPlugin::description() const
///
/// \brief	return the description of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the description of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceApsin20gPlugin::description() const
{
	QString des	= "The APSIN20G is a low noise microwave signal generator, ";
	des	+="offering very good phase noise, ";
	des	+="high dynamic range, fast switching times, ";
	des	+="and exceptional modulation capabilities.";
	
	return des;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceApsin20gPlugin::scriptable( QScriptEngine * engine )
///
/// \brief	add (or not) some functions to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::scriptable
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceApsin20gPlugin::scriptable( QScriptEngine * engine )
{
	static bool initialized = false;

	if(!initialized){ // evite le multi initialitation
		
			initialized = true;

			SDeviceApsin20g* Apsin20g = new SDeviceApsin20g();
			
			QScriptValue qsvSDeviceApsin20g = engine->newQObject(Apsin20g,QScriptEngine::ScriptOwnership);
			QScriptValue qsvMetaSDeviceApsin20g = engine->newQMetaObject(Apsin20g->metaObject());

			engine->globalObject().setProperty("APSIN20G", qsvSDeviceApsin20g);
			engine->globalObject().setProperty("SDeviceApsin20g", qsvMetaSDeviceApsin20g); // Pour les Enums


			qDebug()  << "\nSCRIPT : APSIN20G add to the script environment";

			if(!Apsin20g->available()){
				initialized = false;
				qDebug()  << "\nWARNING :SCRIPT : Failed to add APSIN20G object to the script environment";
				engine->evaluate("var APSIN20G = new Object(); APSIN20G.available = false;","Initialization");
				return false;
			}
		}

	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceApsin20gPlugin::isScriptable()
///
/// \brief	does the plugin add some function to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceApsin20gPlugin::isScriptable()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceApsin20gPlugin::isControlPanel()
///
/// \brief	does the plugin add a tab to the control panel to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceApsin20gPlugin::isControlPanel()
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QWidget* SDeviceApsin20gPlugin::controlPanel() 
///
/// \brief	add (or not) a tab to the control panel 
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceApsin20gPlugin::isControlPanel
///
/// \remark SDeviceApsin20gPlugin do not manage the destruction of the object, so you ave to define a parent
///			or destroy it your self 
////////////////////////////////////////////////////////////////////////////////////////////////////
QWidget * SDeviceApsin20gPlugin::controlPanel(QWidget * parrent /*= NULL*/)
{
	
	QWidget * CtrlPanel = new SUiCpApsin20g(parrent); //!TODO ALL !!!
	return CtrlPanel;
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
QWidget * SDeviceApsin20gPlugin::setting(QWidget * parrent /*= NULL*/ )
{
	QWidget * widSetting = new QWidget(parrent); //!TODO ALL !!!
	return widSetting;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceApsin20gPlugin::shutdown()
///
/// \brief	shutdown the plugin (by example before closing the application)
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isControlPanel
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceApsin20gPlugin::shutdown()
{
	Apsin20g->deactivate();
	state_=2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SDeviceApsin20gPlugin::state()
///
/// \brief	what is the state of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// 0 : ready, 1 : busy, 2 unavailable
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDeviceApsin20gPlugin::state()
{
	return state_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceApsin20gPlugin::available()
///
/// \brief	is the plugin available
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceApsin20gPlugin::available()
{
	return Apsin20g->available();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400Plugin::plgVersion() const
///
/// \brief	return the version of the SDK that is needed for run the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceApsin20gPlugin::plgVersion() const
{

	QString res = "1.1";
	
	return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400Plugin::plgVersion() const
///
/// \brief	return the version of the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceApsin20gPlugin::SDKVersion() const
{
	return QString::number(ASPIN20G_MAJOR_VERSION_COMPATIBILITY) + 
		QString(".") + QString::number(ASPIN20G_MINOR_VERSION_COMPATIBILITY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceK2400Plugin::plgVersion() const
///
/// \brief	this function is call when the plugin is unload
///
/// \author	Sylvain Martin
/// \date	13/01/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceApsin20gPlugin::unload()
{
	qDebug()  <<" WARNING: unloading of the Apsin20g's script object failed" ;
	qDebug()  <<" \t because the function is not implanted yet" ;

	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceApsin20gPlugin::isControlPanel()
///
/// \brief	does the plugin have a setting window ?
///
/// \author	Sylvain Martin
/// \date	25/02/2012
/// \sa SDeviceApsin20gPlugin::controlPanel
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceApsin20gPlugin::isSetting()
{
 return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///									IMPLETATION OF SDeviceK2400
////////////////////////////////////////////////////////////////////////////////////////////////////

#define GHZ 1000000000
#define MHZ 1000000
#define KHZ 1000


SDeviceApsin20g::SDeviceApsin20g( QObject *parent/*=0*/ ):powerLimit_(0)
{
	init();
}

SDeviceApsin20g::~SDeviceApsin20g()
{
	
	status = viClose (instr);
	status = viClose (defaultRM);

	instr = NULL;
	defaultRM = NULL;
}




////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceApsin20g::init(void)
///
/// \brief	Initializes the PSG E8257D device. 
///
/// this function is automatically call at the initialization of this object
////////////////////////////////////////////////////////////////////////////////////////////////////

void SDeviceApsin20g::init(void){

	char stringinput[512];

 /*
	* First we must call viOpenDefaultRM to get the manager
	* handle.  We will store this handle in defaultRM.
	*/
   status=viOpenDefaultRM (&defaultRM);
   if (status < VI_SUCCESS)  
   {
	  qDebug() << "WARNING : SDeviceApsin20g : VISA : Could not open a session to the VISA Resource Manager!\n";
	  return;
   }
														  
   /*
	* Now we will open a VISA session to the serial port (COM1).
	* We must use the handle from viOpenDefaultRM and we must   
	* also use a string that indicates which instrument to open.  This
	* is called the instrument descriptor.  The format for this string
	* can be found in the function panel by right clicking on the 
	* descriptor parameter. After opening a session to the
	* device, we will get a handle to the instrument which we 
	* will use in later VISA functions.  The AccessMode and Timeout
	* parameters in this function are reserved for future
	* functionality.  These two parameters are given the value VI_NULL.
	*/
   status = viOpen (defaultRM, ASPIN20G_USB_NAME, 4, VI_NULL, &instr);
   if (status < VI_SUCCESS) 
   {
	   qDebug() << "WARNING : SDeviceApsin20g : VISA : Cannot open a session to the device.\n";
	   qDebug() << "device address : " << ASPIN20G_USB_NAME;
	   available_ = false;
	   return;
	
   }


     /*
     * Set timeout value to 5000 milliseconds (5 seconds).
     */ 
  // status = viSetAttribute (instr, VI_ATTR_TMO_VALUE, 5000);
  
    /*
     * At this point we now have a session open to the instrument.
	 * We can use this session handle to write 
     * an ASCII command to the instrument.  We will use the viWrite function
     * to send the string "*IDN?", asking for the device's identification.  
     */
   strcpy(stringinput,"*IDN?\n");
   status = viWrite (instr, (ViBuf)stringinput, strlen(stringinput), &writeCount);
   if (status < VI_SUCCESS)  
   {
	   qDebug() << "WARNING : SDeviceApsin20g : VISA : Error writing to the device\n" ;
	   qDebug() << "          error number : " << status;
	   return;
   }

       /*
     * Now we will attempt to read back a response from the device to
     * the identification query that was sent.  We will use the viRead
     * function to acquire the data.  We will try to read back 100 bytes.
     * After the data has been read the response is displayed.
     */
   status = viRead (instr, buffer, 255, &retCount);
   if (status < VI_SUCCESS) 
   {
       qDebug() << "Apsin20g : Error reading a response from the device\n" ;
   }


}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceApsin20g::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the frequency of the microwave. 
///
/// \param	freq The frequency in GHz. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceApsin20g::setFrequency(double const freq){
	frequency_ = freq;

	    QString cmd;
	    cmd = QString("FREQ ") + QString::number(freq*GHZ, 'f',10) + QString("\n");
		visaSend(cmd);

		setMetaData("frequency",freq);
	
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceApsin20g::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the power of the microwave. 
///
/// \param	pwr The power in dBm. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceApsin20g::setPower(double const pwr){

	if (pwr >= -100 && pwr <= powerLimit_){

		QString cmd;

			cmd = QString("POW ") + QString::number(pwr) + QString("\n");
			visaSend(cmd);

			setMetaData("power",pwr);
			power_ = pwr;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceApsin20g::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) Sets the power limit of the microwave. 
///
/// \param	pwr The power in dBm. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceApsin20g::setPowerLimit(const double pwrLim){
	setMetaData("powerLimit",pwrLim);
	powerLimit_ = pwrLim; 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceApsin20g::setFreqStart(double const freq)
///
/// \brief	(SCRIPTABLE) activates or deactivates the microwave. 
///
/// \param	OnOff  activate if true, deactivates otherwise. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceApsin20g::activate(bool OnOff){
	activated_ = OnOff;

	QString cmd;


		if(OnOff){
			cmd = QString(":OUTP ON\n");
			setMetaData("activate",true);
		}else{
			setMetaData("activate",false);
			cmd = QString(":OUTP OFF\n");
		}

		visaSend(cmd);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 QString SDeviceApsin20g::description(void) const
///
/// \brief	(SCRIPTABLE) Gets a brief description of the device. 
///
/// \return	a description of the device. 
////////////////////////////////////////////////////////////////////////////////////////////////////

QString SDeviceApsin20g::description(void) const
{

	QString des	=  "The Agilent E8257D is a fully synthesized signal generator with high output";
	des	+= "power, low phase noise, and optional ramp sweep capability";


	return des;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceApsin20g::available(void)
///
/// \brief	(SCRIPTABLE) Gets the availability. 
///
/// \return	true if the device is available, false if it is not. 
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceApsin20g::available( void ){

	return available_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceApsin20g::deactivate()
///
/// \brief	(SCRIPTABLE) deactivates the microwave. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  void SDeviceApsin20g::deactivate()
{
	activate(false);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceApsin20g::frequency()
///
/// \brief	(SCRIPTABLE) give the actual frequency of the microwave (in GHz). 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  double SDeviceApsin20g::frequency() {
	
	// ask the frequency 
	visaSend(":FREQ?\n");
	QString sfreq = visaRead();


	// convert to a double
	bool convert = true;
	double freq = sfreq.toDouble(&convert);

	// if no error return the result
	if(convert){
		setMetaData("frequency",freq/GHZ);
		return freq/GHZ;
	}else{
		qDebug() << "\nWARNING :\n\t SDeviceApsin20g : Error to convert the answer of the device to a double\n" ;
		qDebug() << "\answer  : " << sfreq;
		return 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SDeviceApsin20g::power()
///
/// \brief	(SCRIPTABLE) give the actual frequency of the microwave (in dBm). 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  double SDeviceApsin20g::power()
{
	// ask the frequency 
	visaSend(":POW?\n");
	QString spow = visaRead();


	// convert to a double
	bool convert = true;
	double pow = spow.toDouble(&convert);

	// if no error return the result
	if(convert){
		setMetaData("power",pow);
		return pow;
	}else{
		qDebug() << "\nWARNING :\n\t SDeviceApsin20g : Error to convert the answer of the device to a double\n" ;
		qDebug() << "\answer  : " << spow;
		return 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceApsin20g::isActivated()
///
/// \brief	(SCRIPTABLE) return is the microwave is activated (On) or not. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  bool SDeviceApsin20g::isActivated()
{
	return activated_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn bool SDeviceApsin20g::visaSend(QString cmd)
///
/// \brief	(SCRIPTABLE) Send this command to the device (in ASCII).
///
/// \author	Sylvain Martin
/// \date	06/01/2012
///
/// \param	data	The data to send (in text form).
/// \return true if all is ok, false if there is an error
///
/// \remarks	the data will be cast in char * (with QByteArray)
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  bool SDeviceApsin20g::visaSend(QString cmd)
{
	
	// pour transformer le Qstring en char *
	QByteArray ba = cmd.toAscii();
	char* charCmd = ba.data();

	//nombre de caractere
	long count = cmd.toLatin1().size();


	status = viWrite (instr, (ViBuf)charCmd, count, &writeCount);
	if (status < VI_SUCCESS)  
	{
		qDebug() << "\nWARNING :\n\t SDeviceApsin20g : VISA : Error writing to the device\n" ;
		qDebug() << "\tcommande send : " << charCmd;
		qDebug() << "\terror number : " << status;
		return false;
	}
	
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  QString SDeviceApsin20g::visaRead()
///
/// \brief	(SCRIPTABLE) Read the response of the device (in ASCII).
///
/// \author	Sylvain Martin
/// \date	06/01/2012
///
/// \param	data	The data to send (in text form).
/// \return true if all is ok, false if there is an error
///
/// \remarks	the data will be cast in char * (with QByteArray)
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  QString SDeviceApsin20g::visaRead(){
	status = viRead (instr, buffer, 255, &retCount);
	if (status < VI_SUCCESS) 
	{
		qDebug() << "\nWARNING :\n\t SDeviceApsin20g : VISA : Error reading from the device\n" ;
		qDebug() << "\terror number : " << status;

		return QString("");
	}else{
		return  QString::fromAscii((const char*)buffer, retCount) ;
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
void SDeviceApsin20g::setMetaData( QString key, QVariant value )
{
	gmdm_.setMetaData(QString(ASPIN20G_SHORT_NAME),key,value);

}