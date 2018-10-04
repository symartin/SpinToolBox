////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceGpib.cpp
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


#include <QtCore>
#include <QScriptable>
#include <QScriptEngine>
#include <QSettings>

#include "SDKDevice/SDevicePluginInterface.h"
#include "SDKDevice/SInterface/SInterfaceGpib.h"
//#include "SDK/gpib-32/ni488.h"
#include "SDeviceGpib.h"


Q_EXPORT_PLUGIN2("SDeviceGpibPlugin", SDeviceGpibPlugin)




SDeviceGpibPlugin::SDeviceGpibPlugin():state_(2),GPIB(NULL)
{
	GPIB = SInterfaceGpib::instance();
}

SDeviceGpibPlugin::~SDeviceGpibPlugin()
{
	SGlobalMetaDataMap gmdm_;
	gmdm_.clear(QString(SDEVICEGPIB_SHORT_NAME));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceGpibPlugin::load()
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
bool SDeviceGpibPlugin::load()
{
	
	return GPIB->available();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceGpibPlugin::name() const
///
/// \brief	return the complete name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceGpibPlugin::name() const
{
	return QString("GPIB direct control");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceGpibPlugin::shortName() const
///
/// \brief	return the short name of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the short name of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceGpibPlugin::shortName() const
{
	return QString(SDEVICEGPIB_SHORT_NAME);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceGpibPlugin::description() const
///
/// \brief	return the description of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return return the description of the plugin
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceGpibPlugin::description() const
{


	QString des	= "GPIB";

	return des;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceGpibPlugin::scriptable( QScriptEngine * engine )
///
/// \brief	add (or not) some functions to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::scriptable
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceGpibPlugin::scriptable( QScriptEngine * engine )
{
	static bool initialized = false;
/*
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
	*/

	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceGpibPlugin::isScriptable()
///
/// \brief	does the plugin add some function to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceGpibPlugin::isScriptable()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceGpibPlugin::isControlPanel()
///
/// \brief	does the plugin add a tab to the control panel to the script engine
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceGpibPlugin::isControlPanel()
{
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceGpibPlugin::controlPanel() const
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
QWidget * SDeviceGpibPlugin::controlPanel(QWidget * parent /*= NULL*/)
{

	QWidget * CtrlPanel = new QWidget(parent);
	return CtrlPanel;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceGpibPlugin::isSetting()
///
/// \brief	does the plugin have a setting window ?
///
/// \author	Sylvain Martin
/// \date	25/02/2012
/// \sa SDeviceDaqFieldOneAxisPlugin::controlPanel
///
/// \return true, yes it does, false, no it does no
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceGpibPlugin::isSetting()
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QWidget* SDeviceGpibPlugin::controlPanel() 
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
QWidget * SDeviceGpibPlugin::setting(QWidget * parrent /*= NULL*/ )
{
	QWidget * widSetting = new QWidget(parrent); //!TODO ALL !!!
	return widSetting;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceGpibPlugin::shutdown()
///
/// \brief	shutdown the plugin (by example before closing the application)
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// \param engine the script engine
/// \sa SDeviceK2400::isControlPanel
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceGpibPlugin::shutdown()
{

	state_=2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SDeviceGpibPlugin::state()
///
/// \brief	what is the state of the plugin
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
/// 0 : ready, 1 : busy, 2 unavailable
////////////////////////////////////////////////////////////////////////////////////////////////////
int SDeviceGpibPlugin::state()
{
	return state_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SDeviceGpibPlugin::available()
///
/// \brief	is the plugin available
///
/// \author	Sylvain Martin
/// \date	01/12/2011
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceGpibPlugin::available()
{
	return 	GPIB->available();;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceGpibPlugin::plgVersion() const
///
/// \brief	return the version of the SDK that is needed for run the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceGpibPlugin::plgVersion() const
{
	return QString::number(SDEVICEGPIB_VERSION);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceGpibPlugin::plgVersion() const
///
/// \brief	return the version of the plugin
///
/// \author	Sylvain Martin
/// \date	13/01/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceGpibPlugin::SDKVersion() const 
{
	return QString::number(SDEVICEGPIB_MAJOR_VERSION_COMPATIBILITY) + 
		QString(".") + QString::number(SDEVICEGPIB_MINOR_VERSION_COMPATIBILITY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceGpibPlugin::plgVersion() const
///
/// \brief	this function is call when the plugin is unload
///
/// \author	Sylvain Martin
/// \date	13/01/2011
///
/// \return true if all is ok, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceGpibPlugin::unload()
{
	qDebug()  <<" WARNING: unloading of the DaqFieldOneAxis's script object failed \n" ;
	qDebug()  <<" \t because the function is not implanted yet\n" ;

	return true;
}