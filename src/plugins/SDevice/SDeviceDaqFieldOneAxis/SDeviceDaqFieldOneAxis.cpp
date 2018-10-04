////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceDaqFieldOneAxis.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		29/02/2012
///
/// \brief	implement the plugin and the class SDeviceDaqFieldOneAxis
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

#include "SDeviceDaqFieldOneAxis.h"
#include "SUiCpDaqFieldOneAxis.h"
#include "SUiCpDaqFieldOneAxisOptions.h"
#include <QtCore>
#include <QScriptable>
#include <QScriptEngine>
#include <QSettings>
#include "SDKDevice/SDevicePluginInterface.h"

#include <QScriptable>
#include <QScriptEngine>


Q_EXPORT_PLUGIN2("SDeviceDaqFieldOneAxis", SDeviceDaqFieldOneAxisPlugin)



SDeviceDaqFieldOneAxisPlugin::SDeviceDaqFieldOneAxisPlugin():state_(2),DAQ(NULL)
{

}

SDeviceDaqFieldOneAxisPlugin::~SDeviceDaqFieldOneAxisPlugin()
{
	if(DAQ!=NULL)
		delete DAQ;

	SGlobalMetaDataMap gmdm_;
	gmdm_.clear(QString(SDEVICEDAQFIELDONEAXIS_SHORT_NAME));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceDaqFieldOneAxisPlugin::load()
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
bool SDeviceDaqFieldOneAxisPlugin::load()
{
	DAQ = SInterfaceDaq::instance();
	return DAQ->available();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceDaqFieldOneAxisPlugin::name() const
///
/// \brief	return the complete name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceDaqFieldOneAxisPlugin::name() const
{
	return QString("Magnetic field coil 1-axis commanded with NI-DAQmx");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceDaqFieldOneAxisPlugin::shortName() const
///
/// \brief	return the short name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the short name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceDaqFieldOneAxisPlugin::shortName() const
{
	return QString(SDEVICEDAQFIELDONEAXIS_SHORT_NAME);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceDaqFieldOneAxisPlugin::description() const
///
/// \brief	return the description of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the description of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceDaqFieldOneAxisPlugin::description() const
{
	 
		
	QString des	= "This plugin is design for command a one-axis magnetic field, ";
	des	+="generated with a coil; the coil is supplied by a power generator (like a Kepco) commanded ";
	des	+="by a national instrument DAQ card.\n\n";
	 
	des	+="Be careful, the DAQ card has a -10V/+10V consign, but the supply ";
	des	+="generator can have a different range (like -12V/+12V), so there";
	des	+="is a prefactor conversion in the setting/code source that convert the consign ";
	des	+="(in this case the prefactor is equal to 10/12).";

	return des;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceDaqFieldOneAxisPlugin::scriptable( QScriptEngine * engine )
///
/// \brief	add (or not) some functions to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::scriptable
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceDaqFieldOneAxisPlugin::scriptable( QScriptEngine * engine )
{
	static bool initialized = false;

	if(!initialized){ // evite le multi initialitation
		try{
			initialized = true;

			SInterfaceDaq* DAQ = SInterfaceDaq::instance();

			QScriptValue qsvDaq = engine->newQObject(DAQ,QScriptEngine::ScriptOwnership);
			engine->globalObject().setProperty("DaqFieldOneAxis", qsvDaq);

			if(!DAQ->available()){
				initialized = false;	
				engine->evaluate("var DAQ = new Object(); DAQ.available = false;","Initialization");
			}
			// pour la rétro compatibilité
			engine->evaluate("var DAQ = DaqFieldOneAxis;","Initialization");

		}catch(QString error){
			initialized = false;
			engine->evaluate("var DAQ = new Object(); DAQ.available = false;","Initialization");
			qDebug()  <<" ERROR (LOW): initialization of the DaqFieldOneAxis's script object failed" 
				<< error;
			return false;

		}
	}


	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceDaqFieldOneAxisPlugin::isScriptable()
///
/// \brief	does the plugin add some function to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceDaqFieldOneAxisPlugin::isScriptable()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceDaqFieldOneAxisPlugin::isControlPanel()
///
/// \brief	does the plugin add a tab to the control panel to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceDaqFieldOneAxisPlugin::isControlPanel()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceDaqFieldOneAxisPlugin::controlPanel() const
///
/// \brief	add (or not) a tab to the control panel 
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isControlPanel
///
/// \remark SDeviceDaqFieldOneAxisPlugin do not manage the destruction of the object, so you ave to define a parent
///			or destroy it your self 
////////////////////////////////////////////////////////////////////////////////////////////////////
QWidget * SDeviceDaqFieldOneAxisPlugin::controlPanel(QWidget * parent /*= NULL*/)
{

	QWidget * CtrlPanel = new SUiCpDaqFieldOneAxis(parent);
	return CtrlPanel;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceDaqFieldOneAxisPlugin::isSetting()
///
/// \brief	does the plugin have a setting window ?
///
/// \author	Sylvain Martin
/// \date	25/02/2012
/// \sa SDeviceDaqFieldOneAxisPlugin::controlPanel
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceDaqFieldOneAxisPlugin::isSetting()
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QWidget* SDeviceDaqFieldOneAxisPlugin::controlPanel() 
///
/// \brief	give (or not) a setting window.
///
/// \author	Sylvain Martin
/// \date	25/01/2012
///
/// \param set the QSetting object of the application (like that the plugin can put some stuffs in it)
/// \param parrent the parent of the widget
/// \sa SDeviceApsin20gPlugin::isSetting
///
/// \remark SDeviceApsin20gPlugin do not manage the destruction of the object, so you ave to define a parent
///			or destroy it your self 
////////////////////////////////////////////////////////////////////////////////////////////////////
QWidget * SDeviceDaqFieldOneAxisPlugin::setting(QWidget * parrent /*= NULL*/ )
{
	QWidget * widSetting = new SUiCpDaqFieldOneAxisOptions(parrent);
	return widSetting;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceDaqFieldOneAxisPlugin::shutdown()
///
/// \brief	shutdown the plugin (by example before closing the application)
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isControlPanel
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceDaqFieldOneAxisPlugin::shutdown()
{
	SInterfaceDaq* DAQ = SInterfaceDaq::instance();
	DAQ->sweep(0,0.5,0);
	state_=2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SDeviceDaqFieldOneAxisPlugin::state()
///
/// \brief	what is the state of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// 0 : ready, 1 : busy, 2 unavailable
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDeviceDaqFieldOneAxisPlugin::state()
{
	return state_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceDaqFieldOneAxisPlugin::available()
///
/// \brief	is the plugin available
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceDaqFieldOneAxisPlugin::available()
{
		return 	DAQ->available();;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceDaqFieldOneAxisPlugin::plgVersion() const
///
/// \brief	return the version of the SDK that is needed for run the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceDaqFieldOneAxisPlugin::plgVersion() const
{
	return QString::number(SDEVICEDAQFIELDONEAXIS_VERSION);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceDaqFieldOneAxisPlugin::plgVersion() const
///
/// \brief	return the version of the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceDaqFieldOneAxisPlugin::SDKVersion() const 
{
	return QString::number(SDEVICEDAQFIELDONEAXIS_MAJOR_VERSION_COMPATIBILITY) + 
		QString(".") + QString::number(SDEVICEDAQFIELDONEAXIS_MINOR_VERSION_COMPATIBILITY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceDaqFieldOneAxisPlugin::plgVersion() const
///
/// \brief	this function is call when the plugin is unload
///
/// \author	Sylvain Martin
/// \date	13/01/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceDaqFieldOneAxisPlugin::unload()
{
	qDebug()  <<" WARNING: unloading of the DaqFieldOneAxis's script object failed \n" ;
	qDebug()  <<" \t because the function is not implanted yet\n" ;

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//										Class   SInterfaceDaq										//
/////////////////////////////////////////////////////////////////////////////////////////////////////



#include "NIDAQmx/NIDAQmx.h"
#include <QCoreApplication>
#include <time.h>
#include <qdebug.h>
// initialize pointer
SInterfaceDaq* SInterfaceDaq::instance_ = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  SInterfaceDaq::~SInterfaceDaq(void)
///
/// \brief	Constructor
///
/// Initialize the memory and the internal variables.
////////////////////////////////////////////////////////////////////////////////////////////////////
SInterfaceDaq::SInterfaceDaq(void):
VOut(NULL),	VIn(NULL),prefactor_ (0),autoStart(0),
	timeout(10.0),BufferSizeOut(1000), BufferSizeIn(20),
	Vmax(10.0), Vmin(-10.0), VOldChan0_(0), VOldChan1_(0),
	ChanOut0("/Dev1/ao0"),ChanOut1("/Dev1/ao1"),
	ChanIn1("/Dev1/ai1"), ChanIn2("/Dev1/ai2"),
	running_(false),metaDataOnOff_(true)
{

	loadSettings();



	// on initialise les deux tableaux
	DataOut = new float64[BufferSizeOut];
	for (int i=0; i< BufferSizeOut ; i++){
		*(DataOut + i) = prefactor_*(float64) i/(BufferSizeOut-1.0);;
	}



	DataIn = new double[BufferSizeIn];
	for (int i=0; i< BufferSizeIn ; i++) DataIn[i]=0.0;

	if(DAQmxCreateTask("", &VOut) <0) available_ =false;  //pour initialiser VOut

	//setMetaData("Vfield", "N/A", "Vc",SMetaData::doublefloat); 
	//setMetaData("dVfield", "N/A","Vc/s",SMetaData::doublefloat); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  SInterfaceDaq::~SInterfaceDaq(void)
///
/// \brief	destructor
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SInterfaceDaq::~SInterfaceDaq(void){
	delete DataOut;
	delete DataIn;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  SInterfaceDaq* SInterfaceDaq::instance()
///
/// \brief	get the pointer to the singleton class
///
/// \return	null if it fails, else return a pointer to the SInterfaceDaq object. 
///
/// Implement the logic here to instantiate the class for the first time by validating the member
/// pointer. If member pointer is already pointing to some valid memory it means that the first
/// object is created and it should not allow for the next instantiation so simply return the
/// member pointer without calling its ctor. 
////////////////////////////////////////////////////////////////////////////////////////////////////

SInterfaceDaq* SInterfaceDaq::instance(){

//	gmdm_ = GlobalMetaDataMap;

	if (NULL == instance_) {
		//creating singleton.
		instance_ =  new SInterfaceDaq;


	}else{
		//singleton already created!
		// do nothing
	}

	return instance_;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SInterfaceDaq::sweep(double V,double dV, int channel)
///
/// \brief	(SCRIPTABLE) it does a sweeps between the older constant voltage and a new one  
///
/// \param	V		The goal value in volts   
/// \param	dV		The "speed" of the sweep
/// \param	channel	The channel (0 or 1). 
/// 
/// \so running()
/// \so finished()
/// \so Prefactor()
/// \so SetPrefactor
///
/// \remark for historical reason a pre-factor is applied on the V value for be compatible with different Kepcos.
///
/// it emits the finished() signal when the task is finished
/// it does nothing if a task is already running
/// it does noting if the channel is not correct
/// it does noting if the command is greater than the card limit
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceDaq::sweep(double V,double dV, int channel){

	running_ = true;

	double t;
	double incrementV;
	double tpsSweep;
	float64 rate;  ///< the rate of the output
	double Vo;

	double Vold; ///<
	QString ChanOut;

	switch (channel){
	case 0:
		ChanOut = ChanOut0;
		Vold = VOldChan0_;
		VOldChan0_ = V;
		break;
	case 1:
		ChanOut = ChanOut1;
		Vold = VOldChan1_;
		VOldChan1_ = V;
		break;
	default:
		return;
	}
	if((fabs(V) > Vmax) || (V == Vold)) {
		running_ = false;
		emit finished();
		return; //TODO metre une erreur ici
	}



	tpsSweep = fabs((V-Vold)/dV);		///< temps entre consigne et ancienne valeur
	rate = (double)BufferSizeOut/tpsSweep;		///<vittese de de lecture de la consigne par la carte DAQ	
	incrementV = (V-Vold)/(BufferSizeOut - 1);	///< diference en tension entre deux points de consigne 

	// pour pouvoir modifier la frequence de generation Rate, il faut recreer la Task
	if(DAQmxClearTask(VOut) <0) available_ = false;
	DAQmxCreateTask("", &VOut);


	//Add an analog output channel to the task
	DAQmxCreateAOVoltageChan (VOut,
		ChanOut.toAscii().data(), "", 
		Vmin, Vmax,	DAQmx_Val_Volts, "");

	//To configure the timing parameters 
	DAQmxCfgSampClkTiming(VOut,
		"OnboardClock",	rate, DAQmx_Val_Rising,
		DAQmx_Val_FiniteSamps, BufferSizeOut);

	// on fait un tableau ou l'on stoque la consigne que l'on va envoyer
	for ( int i=0 ; i<BufferSizeOut ; i++){


		Vo= prefactor_*(Vold + i*incrementV);
		t = i*tpsSweep/((double)BufferSizeOut); 
 
		if(t<tpsSweep) DataOut[i] = (float64) prefactor_*( Vold + i*incrementV );
		else DataOut[i] = (float64) prefactor_*V;


		if(fabs(DataOut[i]) > Vmax)	{ //TODO il faut gerer corectement les dépacement !!!
			//sécurité pour rester sous le seuil de 10V de la daq
			DataOut[i] = prefactor_*Vmax*0.99*sgn(DataOut[i]);
			qDebug() << "attention seuillage de tension DAQ!\n";
		}
	}


	DAQmxWriteAnalogF64(VOut,BufferSizeOut,autoStart,timeout,DAQmx_Val_GroupByChannel,DataOut ,&SamplesWritten, 0);
	DAQmxStartTask (VOut);

	delay(tpsSweep);
	DAQmxClearTask(VOut);  
	emit finished();

	setMetaData("Vfield", V, "Vc",SMetaData::doublefloat); 
	setMetaData("dVfield", dV,"Vc/s",SMetaData::doublefloat); 

	running_ = false;

	return ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	inline double SInterfaceDaq::fabs(double num)
///
/// \brief	compute the absolute value of num. 
///
/// \param	num	a number. 
///
/// \return	the absolute value of num. 
////////////////////////////////////////////////////////////////////////////////////////////////////

inline double SInterfaceDaq::fabs(double num){

	if(num<0){
		return -num;
	}else{
		return num;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	inline double SInterfaceDaq::sgn(double number)
///
/// \brief	return the sign of the number. 
///
/// \param	number	a number. 
///
/// \return	-1 if number is negative an +1 if it is positive. 
/// \remark 0 is positive		
////////////////////////////////////////////////////////////////////////////////////////////////////

inline double SInterfaceDaq::sgn(double number){	
	if(number <0) return -1;
	else return 1;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	inline double SInterfaceDaq::delay(double i)
///
/// \brief	(SCRIPTABLE) do a break during i seconds 
///
/// \param	number	a number of seconds. 
///
/// let the rest of the application process normally (e.g. the GUIs)		
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SInterfaceDaq::delay(double i)    
{
	clock_t start,end;
	start=clock();

	while(((end=clock())-start)<=i*CLOCKS_PER_SEC){
		QCoreApplication::processEvents ();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE bool SInterfaceDaq::available(void)
///
/// \brief	(SCRIPTABLE) Gets if the DAQ is available. 
///
/// \return	true if it available, false if it not.
/// \remark It does not indicate if a task is running.
/// \so SInterfaceDaq::running()
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE bool SInterfaceDaq::available(void){
	//on verifie que la carte est tjs non disponible
	if(!running_ && DAQmxClearTask(VOut) <0) available_ = true;

	setMetaData("available", available_, "", SMetaData::boolean); 
	return(available_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE bool SInterfaceDaq::running()
///
/// \brief	(SCRIPTABLE) Gets if the DAQ is running a task. 
///
/// \return	true if it is running a task, false if it not.
/// \remark It does not indicate if a task is available.
/// \so SInterfaceDaq::available(void)
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE bool SInterfaceDaq::running()
{
	return running_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE double SInterfaceDaq::vOld(int channel)
///
/// \brief	(SCRIPTABLE) Gets the final value of the last sweep command
///
/// \return	a voltage in volt
/// \remark It does not indicate if a task is available.
/// \so SInterfaceDaq::sweep(double V,double dV, int channel)
///
/// if channel is not 0 or 1 return 0
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE double SInterfaceDaq::vOld( int channel /*= 0*/ )
{

	switch (channel){
	case 0:
		return VOldChan0_;
	case 1:
		return VOldChan1_;
	default:
		return 0;
	}

	setMetaData( "vOld0", VOldChan0_,"",SMetaData::doublefloat );
	//setMetaData("vOld1", VOldChan1_,"",SMetaData::doublefloat); 


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceDaq::setMetaData( QString key, QVariant value )
///
/// \brief	Change the value of the metadata for this device in the global map SGlobalMetaDataMap 
///
/// \param the key in the sub map of metatdata for this device
/// \param value the value corresponding of the key
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SInterfaceDaq::setMetaData( const QString key, const QVariant value, const QString unit, const SMetaData::enumType type)
{

	if(metaDataOnOff_) gmdm_.setMetaData(QString(SDEVICEDAQFIELDONEAXIS_SHORT_NAME),key,value, unit , type);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceDaq::metaDataOnOff( bool onOff )
///
/// \brief	activate or deactivate the Global Metadata System
///
/// \param onOff in the sub map of metatdata for this device
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SInterfaceDaq::metaDataOnOff( bool onOff )
{
	metaDataOnOff_ = onOff;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceDaq::loadSettings()
///
/// \brief	load the settings from the ini file
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SInterfaceDaq::loadSettings()
{
	// on a besoin d'un moteur QSript car cela permet de metre des valeurs tel que 5/6
	QScriptEngine engine;


	// On récupere les préferences pour ce pluging
	QSettings set_( "SpinToolBox.ini", QSettings::IniFormat, this );

	set_.beginGroup("SDeviceDaqFieldOneAxis");	
	QVariant val = set_.value("DacKepcoCoeff", "5/6");
	set_.endGroup();



	QScriptValue resultat = engine.evaluate(val.toString());
	if(resultat.isNumber()){
		prefactor_ = resultat.toNumber();

	}else{ // Pb valeur fausse ds le ini
		QMessageBox msgBox;
		msgBox.setText("The value for the coefficient is not a valid number.");
		msgBox.exec();
		this->available_ = false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE double SInterfaceDaq::timeSweep( double V, double dV,int channel)
///
/// \brief	return the time needed to do a sweep from Vold (the actual field) and V at the speed
/// 		dV.
///
/// \author	Sylvain Martin
/// \date	18/10/2012
///
/// \param	V	   	The wanted field.
/// \param	dV	   	The speed.
/// \param	channel	The on which channel.
///
/// \return	.
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE double SInterfaceDaq::timeSweep( double V, double dV,int channel)
{
	return fabs((V-vOld())/dV);
}
