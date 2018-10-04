////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceSR830.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/12/2011
///
/// \brief	declare the plugin and the class SDeviceSR830
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
/// 

#ifndef SDEVICESR830_H
#define SDEVICESR830_H


#include "SDeviceSR830_global.h"
#include "SDKDevice/SDevicePluginInterface.h"

#include <QtCore>
#include <QtGui>

#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>

#include "SDK/SpinToolBoxSDK.h"
#include "SDKDevice/SDevice/SDeviceGpib.h"

#define SDEVICESR830_MAJOR_VERSION_COMPATIBILITY 2
#define SDEVICESR830_MINOR_VERSION_COMPATIBILITY 0
#define SDEVICESR830_VERSION 1.1
#define SDEVICESR830_SHORT_NAME "SR830"


#if STB_SDK_DEVICE_MAJOR_VERSION != SDEVICEGPIB_MAJOR_VERSION_COMPATIBILITY \
	&& STB_SDK_DEVICE_MINOR_VERSION != SDEVICEGPIB_MINOR_VERSION_COMPATIBILITY
#error "This file was written for a SDK Device version 2.0 It cannot be used with another version."
#endif

#define MILI 1000

class SDeviceSR830;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceSR830Plugin
///
/// \brief	it is the plugin class for include all the functions of the device in the script module. 
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	01/02/2012
/// 			
/// \sa SDeviceSR830	
///
/// this class is base on the standard class to plug-in all the function of the device in the
/// QtScript module (thank to the QObject proprieties) and provide a GUI control panel  
////////////////////////////////////////////////////////////////////////////////////////////////////
class SDEVICESR830_EXPORT SDeviceSR830Plugin : public SDevicePluginInterface
{
	Q_INTERFACES(SDevicePluginInterface)
		Q_OBJECT

public:
	SDeviceSR830Plugin();
	~SDeviceSR830Plugin();

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
	//void logError(QString log, QString name);
	//void logEvent(QString log, QString name);

private:
	SDeviceSR830 * SR830;
	//	SGlobalMetaDataMap gmdm_;
	int state_;
};






////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceSR830
///
/// \brief	Provides control of the  SR830 Lock-in. 
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	20/01/2011
/// 		
/// \image html Keithley2400.jpg "Keithley 2400 SourceMeter"
/// 
///
/// 		
////////////////////////////////////////////////////////////////////////////////////////////////////

class  SDEVICESR830_EXPORT SDeviceSR830 : public SDeviceGpib{
	Q_OBJECT;

public :

	// specific at SR830
	SDeviceSR830(QObject *parent=0);
	SDeviceSR830::~SDeviceSR830();

	/*Q_INVOKABLE void metaDataOnOff( bool onOff );

	Q_INVOKABLE virtual double voltage( );
	Q_INVOKABLE virtual void setVoltage(double voltage);

	Q_INVOKABLE virtual void activate();
	Q_INVOKABLE virtual void deactivate();
	Q_INVOKABLE bool isActivated();*/

	Q_INVOKABLE void setFrequency(double freq);
	Q_INVOKABLE void setPhase( double phase );
	Q_INVOKABLE void setAmplitude( double amplitude );
    Q_INVOKABLE void setX();
	Q_INVOKABLE void setY();
	Q_INVOKABLE void setR();
	Q_INVOKABLE void setTheta();
	Q_INVOKABLE void AutoPhase();
	Q_INVOKABLE double X();
	Q_INVOKABLE double Y();
	Q_INVOKABLE double R();
	Q_INVOKABLE double Theta();


	// heritage of class SDeviceVirtual 
	Q_INVOKABLE virtual void init();	 
	Q_INVOKABLE virtual QString description()const;
	Q_INVOKABLE virtual bool available();


signals:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void logError(QString log, QString name);
	///
	/// \brief	(Signal) send a signal when the is an error non fatal
	///
	/// \author	Sylvain Martin
	/// \date	20/04/2012
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void logError(QString log, QString name);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool SDeviceSR830::available()
	///
	/// \brief	(Signal) send a signal when some thing important append
	///
	/// \author	Sylvain Martin
	/// \date	20/04/2012
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void logEvent(QString log, QString name);


protected:
	bool available_;
	SGlobalMetaDataMap gmdm_;
	inline void setMetaData(const QString key, const QVariant value, const QString unit ="", const SMetaData::enumType type = SMetaData::string);
	bool metaDataOnOff_;
	bool isActivated_;	///< device activated or not
	void SDeviceSR830::sendLogError( QString log );
};




#endif // SDEVICESR830_H
