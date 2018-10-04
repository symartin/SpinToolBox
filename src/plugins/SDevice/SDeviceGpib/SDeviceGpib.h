////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceGpib.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		29/02/2012
///
/// \brief	Declare the plugin and the class SDeviceGpib
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
#ifndef SDEVICEGPIB_H
#define SDEVICEGPIB_H

#include "SDeviceGpib_global.h"
#include "SDKDevice/SDevicePluginInterface.h"

#include <QtCore>
#include <QtGui>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>

#include "SDKDevice/SInterface/SInterfaceGpib.h"
#include "SDKDevice/SDevice/SDeviceGpib.h"
#include "SDKDevice/SDevice/SDeviceVirtual.h"
#include "SDKDevice/gpib-32/ni488.h"


#include "SDK/SpinToolBoxSDK.h"
#define SDEVICEGPIB_MAJOR_VERSION_COMPATIBILITY 2
#define SDEVICEGPIB_MINOR_VERSION_COMPATIBILITY 0
#define SDEVICEGPIB_VERSION 0.1
#define SDEVICEGPIB_SHORT_NAME "Gpib"

#include "SDKDevice/SpinToolBoxSDKDevice.h"
#if !defined(STB_SDK_DEVICE)
#error "The header file doesn't include SpinToolBoxSDK.h"
#elif STB_SDK_DEVICE_MAJOR_VERSION != SDEVICEGPIB_MAJOR_VERSION_COMPATIBILITY \
	&& STB_SDK_DEVICE_MINOR_VERSION != SDEVICEGPIB_MINOR_VERSION_COMPATIBILITY
#error "This file was written for a SDK Device version 2.0 It cannot be used with another version."
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceDaqFieldOneAxisPlugin
///
/// \brief	it is the plugin class for include all the functions of the device in the script module. 
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	29/02/2012
/// 			
/// \sa 	
///
/// this class is base on the standard class to plug-in all the function of the device in the
/// QtScript module (thank to the QObject proprieties) and provide a GUI control panel  
////////////////////////////////////////////////////////////////////////////////////////////////////
class SDEVICEGPIB_EXPORT SDeviceGpibPlugin : public SDevicePluginInterface
{
	Q_INTERFACES(SDevicePluginInterface)
	Q_OBJECT

public:
	SDeviceGpibPlugin();
	~SDeviceGpibPlugin();

	bool load ();
	QString name () const;
	QString shortName () const;
	QString description()const;

	QString plgVersion() const ;
	QString SDKVersion() const ;

	bool isScriptable();
	bool scriptable(QScriptEngine * engine);

	bool isControlPanel();
	QWidget * controlPanel(QWidget * parrent = NULL);

	bool isSetting();
	QWidget * setting(QWidget * parrent = NULL );

	void shutdown();
	bool unload();

	int state();
	virtual bool available();

signals:
	void logError(QString log, QString name);
	void logEvent(QString log, QString name);

private:
	int state_;
	SInterfaceGpib* GPIB;
};



#endif