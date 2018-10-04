////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceApsin20g.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/12/2011
///
/// \brief	Declare the plugin and the class SDeviceApsin20g
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
#ifndef SDEVICEAPSIN20G_H
#define SDEVICEAPSIN20G_H


#define ASPIN20G_USB_NAME "USB0::0x03EB::0xAFFF::121-212210100-0023::INSTR"

#include "SDK/SpinToolBoxSDK.h"
#define ASPIN20G_MAJOR_VERSION_COMPATIBILITY 2
#define ASPIN20G_MINOR_VERSION_COMPATIBILITY 0
#define ASPIN20G_VERSION 2
#define ASPIN20G_SHORT_NAME "APSIN20G"

#include "SDKDevice/SpinToolBoxSDKDevice.h"

#if !defined(STB_SDK_DEVICE)
#error "The header file doesn't include SpinToolBoxSDK.h"
#elif SDEVICEDAQFIELDONEAXIS_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MAJOR_VERSION \
	&& SDEVICEDAQFIELDONEAXIS_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MINOR_VERSION
#error "This file was written for a SDK Device version 2.0 It cannot be used with another version."
#endif

#include "SDeviceApsin20g_global.h"
#include "SDKDevice\SDevicePluginInterface.h"


#include <QtCore>
#include <QtGui>
class SDeviceApsin20g;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceApsin20gPlugin
///
/// \brief	it is the plugin class for include all the functions of the device in the script module. 
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	5/01/2012
/// 			
/// \sa SDeviceApsin20	
///
/// this class is base on the standard class to plug-in all the function of the device in the
/// QtScript module (thank to the QObject proprieties) and provide a GUI control panel  
////////////////////////////////////////////////////////////////////////////////////////////////////
class SDEVICEAPSIN20G_EXPORT SDeviceApsin20gPlugin : public SDevicePluginInterface
{
	Q_INTERFACES(SDevicePluginInterface)
	Q_OBJECT

public:
	SDeviceApsin20gPlugin();
	~SDeviceApsin20gPlugin();

	bool load ();
	QString name () const;
	QString shortName () const;
	QString description()const;

	QString plgVersion() const;
	QString SDKVersion() const;

	bool isScriptable();
	bool scriptable(QScriptEngine * engine);

	bool isSetting();
	QWidget * setting(QWidget * parrent = NULL);

	bool isControlPanel();
	QWidget * controlPanel(QWidget * parrent = NULL);

	void shutdown();

	int state();
	virtual bool available();
	bool unload();

signals:
	void logError(QString log, QString name);
	void logEvent(QString log, QString name);

private:
	SDeviceApsin20g * Apsin20g;
	int state_;
};




#include "SDKDevice\visa32\visa.h"
#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceApsin20g
///
/// \brief	Provides control of the APSIN20G Microwave Signal Generator. 
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	05/01/2012
/// 		
/// \image html APSIN20G.jpg "APSIN20G Microwave Signal Generator"
/// 
/// \par 9 kHz to 20 GHz+ Microwave Signal Generator
///
///	The APSIN20G is a low noise microwave signal generator, offering very good phase noise,
/// high dynamic range, fast switching times, and exceptional modulation capabilities.
///
///	\par Key Specifications:
///
/// \li 10 MHz to 20 GHz+, settable down to 9 kHz
///	\li 0.001 Hz frequency resolution
///	\li -90 to +13 dBm in 0.01 dB (option PE)
///	\li -108 dBc/Hz at 10 GHz carrier (20 kHz offset)
///	\li < 200 microsecs switching time
///	\li ultra-wideband DCFM
///	\li AM/PM/fast pulse modulation
///	\li programmable pulse trains, chirps
///	\li LAN VXI-11, USB-TMC, GPIB (opt)
///	\li DC power peak 18 Watts
///	\li Weight: 2.5 kgs total
/// 		
////////////////////////////////////////////////////////////////////////////////////////////////////

class  SDeviceApsin20g :  public QObject{
	Q_OBJECT;


	//: 
public :
	// specific at K2400
	SDeviceApsin20g(QObject *parent=0);
	~SDeviceApsin20g();

	void init(void);

	Q_INVOKABLE virtual double frequency();
	Q_INVOKABLE virtual void setFrequency(double const);

	Q_INVOKABLE virtual double power( );
	Q_INVOKABLE virtual void setPower(double const );
	Q_INVOKABLE virtual void setPowerLimit( double const );
	Q_INVOKABLE virtual void activate(bool OnOff = true);
	Q_INVOKABLE virtual void deactivate();
	Q_INVOKABLE virtual bool isActivated( );
	
	Q_INVOKABLE  bool visaSend(QString cmd);
	Q_INVOKABLE  QString visaRead();

	Q_INVOKABLE virtual QString description() const;
	Q_INVOKABLE virtual bool available(void);
	
	

protected :
	double frequency_;
	double power_;
	bool activated_;
	double powerLimit_;
	bool available_;

	//gestion des metadata
	void setMetaData( QString key, QVariant value );
	SGlobalMetaDataMap  gmdm_;

	/*
	* In every source code or header file that you use it is necessary to prototype
	* your VISA variables at the beginning of the file. You need to declare the VISA
	* session, VISA integers, VISA strings, VISA pointers, and VISA floating variables. 
	* Remember that if you are prototyping variables that are to be used as part of the
	* VISA session that need this prototyping. As an example, above retCount has been
	* prototyped as a static variable to this particular module.   It is an integer of
	* bit length 32. If you are uncertain how to declare your VISA prototypes refer
	* to the VISA help under the Section titled Type Assignments Table. The VISA
	* help is located in your NI-VISA directory or folder.
	*/
	 ViSession defaultRM;     
	 ViSession instr;     
	 ViUInt32 retCount;
	 ViUInt32 writeCount;
	 ViStatus status;
	 unsigned char buffer[255];
	 


};

#endif // SDEVICEK2400_H
