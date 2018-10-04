////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceE8257D.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/03/2012
///
/// \brief	Declares the SDeviceE8257D class
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
#ifndef SDEVICEE8257D_H_
#define SDEVICEE8257D_H_
#include "sdevicepsge8257d_global.h"
#include "SDKDevice/SDevicePluginInterface.h"
#include <SDK/SpinToolBoxSDK.h>
#include <SDKDevice/SDevice/SDeviceGpib.h>
#include <QtCore>
#include <QtGui>

#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>

#define SDEVICEPSGE8257D_MAJOR_VERSION_COMPATIBILITY 2
#define SDEVICEPSGE8257D_MINOR_VERSION_COMPATIBILITY 0
#define SDEVICEPSGE8257D_VERSION 1.1
#define SDEVICEPSGE8257D_SHORT_NAME "PSGE8257D"

#include "SDKDevice/SpinToolBoxSDKDevice.h"


#if SDEVICEPSGE8257D_MAJOR_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MAJOR_VERSION \
	|| SDEVICEPSGE8257D_MINOR_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MINOR_VERSION
#error "This file was written for a SDK Device version 2.0 It cannot be used with another version."
#endif



class SDevicePSGE8257D;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDevicePSGE8257DPlugin
///
/// \brief	it is the plugin class for include all the functions of the device in the script module. 
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	01/03/2012
/// 			
/// \sa SDevicePSGE8257D	
///
/// this class is base on the standard class to plug-in all the function of the device in the
/// QtScript module (thank to the QObject proprieties) and provide a GUI control panel  
////////////////////////////////////////////////////////////////////////////////////////////////////
class SDEVICEPSGE8257D_EXPORT SDevicePSGE8257DPlugin : public SDevicePluginInterface
{
	Q_INTERFACES(SDevicePluginInterface)
		Q_OBJECT

public:
	SDevicePSGE8257DPlugin();
	~SDevicePSGE8257DPlugin();

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
	SDevicePSGE8257D * PSGE8257D;
	SGlobalMetaDataMap * GlobalMetaDataMap_;
	int state_;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceE8257D 
///
/// \brief	Provides control of the E8557D microwave generator, 3 Hz - 26.5 GHz, Agilent. 
///		
/// \ingroup SDeviceMod 
/// 		 
/// \image html microwave_generator_AgilentE8257D.png "microwave generator Agilent E8257D"
/// 
/// 								 	   		 		 
/// The Agilent E8257D is a fully synthesized signal generator with high output
/// power, low phase noise, and optional ramp sweep capability
/// 
/// 
/// \par Industry's Best Performance up to 40 GHz
/// 
/// The E8257D PSG analog signal generator delivers industry-leading output power, 
/// level accuracy, and phase noise performance up to 40 GHz.
/// The PSG analog signal generator's high output power and superior level accuracy often
/// eliminates the need of an external amplifier for testing high power devices and 
/// minimizes test uncertainty to identify errors early in the design process. 
/// The world-class phase noise performance (typically -126 dBc/Hz @ 10 GHz carrier 
/// and 10 kHz offset) is ideal for local oscillator, low jitter clock substitution 
/// and adjacent channel selectivity tests. When testing advanced RF & microwave radar,
/// communications, and control systems, the PSG analog signal generator delivers the 
/// performance you demand.
/// 
/// \par Modular Microwave Signal Generator Platform
/// 
///	Generate continuous wave (CW) signals for LO substitution or swept stimulus response
/// analysis. Optionally add AM, FM, ØM and/or pulse modulation to accurately characterize
/// RF and microwave components and devices. Many performance enhancement options are also
/// available to configure the signal generator to meet your specific test requirements. 
/// Tailor the PSG for today's RF and microwave test applications and easily upgrade in 
/// the future as your needs change.
///
///
/// \par Signal Characteristics
///
/// \li 250 kHz to 40, (.001 Hz resolution)
/// \li +23 dBm @ 20 GHz, +17dBm @ 40 GHz, +14 dBm @ 67 GHz output power (typ); > +30 dBm (typ) with Option 521.
/// \li Industry’s best SSB phase noise Option UNY.
///
/// \parModulation
///
/// \li AM, FM, (phase)M, pulse, and scan
/// \li 8 ns rise/fall times and 20 ns pulse width (typ)
/// \li Dual internal function generators: sine, square, triangular, ramp, and noise
///
/// \parSweep
///
/// \li Step, list, and ramp sweep (frequency and power)
/// \li Source control using PSA Series Option 215
/// \li Agilent 8757D scalar network analyzer code compatible
///
/// \parAutomation and Communication Interface
///
/// \li 10BaseT LAN and GPIB
/// \li SCPI and IVI-COM drivers
/// \li Backwards compatible with all PSG signal generators
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class SDevicePSGE8257D: public SDeviceGpib {
	Q_OBJECT;

public:
	SDevicePSGE8257D(QObject *parent=0);
	void init(void);

	Q_INVOKABLE virtual void metaDataOnOff( bool onOff );

	Q_INVOKABLE virtual void setFrequency(double const);
	Q_INVOKABLE virtual void setPower(double const );
	Q_INVOKABLE virtual void setPowerLimit( double const );
	Q_INVOKABLE virtual void activate(bool);

	// heritage de SDeviceVirtual
	Q_INVOKABLE virtual QString description() const;
	Q_INVOKABLE virtual bool available(void);

	Q_INVOKABLE virtual double frequency() const ;
	Q_INVOKABLE virtual double power( ) const ;
	Q_INVOKABLE virtual double powerLimit( ) const;	
	Q_INVOKABLE virtual bool isActivated( );


private:
	inline void setMetaData(const QString key, const QVariant value, const QString unit ="", const SMetaData::enumType type = SMetaData::string);
	bool metaDataOnOff_;
	SGlobalMetaDataMap  gmdm_;


	double frequency_;
	double power_;
	bool activated_;
	double powerLimit_;
};

#endif //SDEVICEE8257D_H_





