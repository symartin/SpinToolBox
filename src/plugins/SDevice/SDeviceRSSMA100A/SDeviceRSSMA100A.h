////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceRSSMA100A.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/03/2012
///
/// \brief	Declares the SDeviceRSSMA100DPlugin and the SDeviceRSSMA100A class
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
#ifndef SDEVICERSSMA100A_H
#define SDEVICERSSMA100A_H

#include "sdevicerssma100a_global.h"

#include "SDKDevice/SDevicePluginInterface.h"
#include <SDK/SpinToolBoxSDK.h>
#include <SDKDevice/SDevice/SDeviceGpib.h>
#include <QtCore>
#include <QtGui>

#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>

#define SDEVICERSSMA100A_MAJOR_VERSION_COMPATIBILITY 2
#define SDEVICERSSMA100A_MINOR_VERSION_COMPATIBILITY 0
#define SDEVICERSSMA100A_VERSION 1.1
#define SDEVICERSSMA100A_SHORT_NAME "RSSMA100A"

#include "SDKDevice/SpinToolBoxSDKDevice.h"


#if SDEVICERSSMA100A_MAJOR_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MAJOR_VERSION \
	|| SDEVICERSSMA100A_MINOR_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MINOR_VERSION
#error "This file was written for a SDK Device version 2.0 It cannot be used with another version."
#endif


class SDeviceRSSMA100A;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceRSSMA100DPlugin
///
/// \brief	it is the plugin class for include all the functions of the device in the script module. 
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	01/03/2012
/// 			
/// \sa SDeviceRSSMA100
///
/// this class is base on the standard class to plug-in all the function of the device in the
/// QtScript module (thank to the QObject proprieties) and provide a GUI control panel  
////////////////////////////////////////////////////////////////////////////////////////////////////

class SDEVICERSSMA100A_EXPORT SDeviceRSSMA100APlugin : public SDevicePluginInterface
{
	Q_INTERFACES(SDevicePluginInterface)
		Q_OBJECT

public:
	SDeviceRSSMA100APlugin();
	~SDeviceRSSMA100APlugin();

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
	SDeviceRSSMA100A * RSSMA100A;
	SGlobalMetaDataMap * GlobalMetaDataMap_;
	int state_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceRSSMA100A
///
/// \brief	Provides control of the SMA 100A microwave generator, 3 Hz - 26.5 GHz, Rohde & Schward.
///		
/// \ingroup SDeviceMod
///  
/// \image html microwave_generator_RSSMA100A.jpg "microwave generator Rohde & Schward SMA100A"
/// 								 	   		 		 
/// The R&S SMA 100A combines superior signal quality with very high setting speed, which 
/// makes it ideal for any task. Whether in development, production, service or maintenance,
/// the R&S SMA 100A does an excellent job.
///
/// In the frequency range from 9 kHz to 6 GHz, it can generate CW signals as well as all 
/// common types of analog modulation (AM, FM, ?M, pulse modulation). Excellent specifications 
/// and a wide range of modulation signals – these are the characteristic features of the R&S SMA 100A. 
/// In addition, a low-jitter clock synthesizer option supplies differential clock signals
/// of up to 1.5 GHz independently of the RF frequency.
///
/// 
/// \par SMA100A Specifications and Features
/// 
/// \li Very low SSB phase noise of typ. –135 dBc
/// \li Wideband noise of typ. –160 dBc
/// \li Nonharmonics of typ. –100 dBc
/// \li Very short frequency and level setting times of <3 ms across the entire frequency and level range
/// \li Fast hopping mode with flexibly addressable frequency and level pairs, as fast as normal list mode
/// \li Frequency setting time of typ. <10 µs within a bandwidth of 40 MHz due to direct access to the DDS-based synthesizer (with the R&S SMA-B20 or -B22 option)
/// \li Very high level accuracy and repeatability
/// \li Electronic attenuator with built-in overvoltage protection over entire frequency range
/// \li Pulse modulator with excellent characteristics (on/off ratio >80 dB, rise/fall time typ. 10 ns)
/// \li Pulse generator integrated as standard
/// \li Built-in LF generator up to 1 MHz, optional multifunction generator (R&S SMA-K24) up to 10 MHz
/// \li Optional low-jitter clock synthesizer up to 1.5 GHz (R&S SMA-B29)
/// \li Intuitive user interface with graphical display of signal flow (block diagram)
/// \li Remote control via GPIB or LAN
/// \li USB connectors (e.g. for keyboard, mouse, memory stick)
/// \li Selectable SCPI- or 8662A/63A-compatible IEC/IEEE bus command set
/// \li Control via remote operation tool (e.g. VNC)
/// \li performance you demand.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
class SDEVICERSSMA100A_EXPORT SDeviceRSSMA100A: public SDeviceGpib {
	Q_OBJECT;

public:
	SDeviceRSSMA100A(QObject *parent=0);
	void init(void);

	Q_INVOKABLE virtual void metaDataOnOff( bool onOff );

	Q_INVOKABLE virtual void setFrequency(double const);
	Q_INVOKABLE virtual void setPower(double const );
	Q_INVOKABLE virtual void setPowerLimit( double const );
	Q_INVOKABLE virtual void activate(bool);

	// heritage de SDeviceVirtual
	Q_INVOKABLE virtual QString description() const;
	Q_INVOKABLE virtual bool available(void);

	Q_INVOKABLE virtual double frequency() ;
	Q_INVOKABLE virtual double power( ) ;
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

#endif // SDEVICERSSMA100A_H




