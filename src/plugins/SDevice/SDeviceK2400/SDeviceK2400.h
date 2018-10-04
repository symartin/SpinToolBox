////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceK2400.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		01/12/2011
///
/// \brief	declare the plugin and the class SDevicek2400
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
#ifndef SDEVICEK2400_H
#define SDEVICEK2400_H


#include "SDeviceK2400_global.h"
#include "SDKDevice/SDevicePluginInterface.h"

#include <QtCore>
#include <QtGui>

#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>

#include "SDK/SpinToolBoxSDK.h"
#include "SDKDevice/SDevice/SDeviceGpib.h"

#define SDEVICEK2400_MAJOR_VERSION_COMPATIBILITY 2
#define SDEVICEK2400_MINOR_VERSION_COMPATIBILITY 0
#define SDEVICEK2400_VERSION 1.1
#define SDEVICEK2400_SHORT_NAME "Keithley2400"


#if STB_SDK_DEVICE_MAJOR_VERSION != SDEVICEGPIB_MAJOR_VERSION_COMPATIBILITY \
	&& STB_SDK_DEVICE_MINOR_VERSION != SDEVICEGPIB_MINOR_VERSION_COMPATIBILITY
#error "This file was written for a SDK Device version 2.0 It cannot be used with another version."
#endif

#define MILI 1000

class SDeviceK2400;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceK2400Plugin
///
/// \brief	it is the plugin class for include all the functions of the device in the script module. 
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	01/02/2012
/// 			
/// \sa SDeviceK2400	
///
/// this class is base on the standard class to plug-in all the function of the device in the
/// QtScript module (thank to the QObject proprieties) and provide a GUI control panel  
////////////////////////////////////////////////////////////////////////////////////////////////////
class SDEVICEK2400_EXPORT SDeviceK2400Plugin : public SDevicePluginInterface
{
	Q_INTERFACES(SDevicePluginInterface)
	Q_OBJECT

public:
	SDeviceK2400Plugin();
	~SDeviceK2400Plugin();

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
	SDeviceK2400 * K2400;
//	SGlobalMetaDataMap gmdm_;
	int state_;
};






////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceK2400
///
/// \brief	Provides control of the Keithley K2400 SourceMeter. 
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	20/01/2011
/// 		
/// \image html Keithley2400.jpg "Keithley 2400 SourceMeter"
/// 
/// Keithley 2400 is designed";
/// specifically for test applications that demand tightly
/// coupled sourcing and measurement.\n All SourceMeter models
/// provide precision voltage and current sourcing as well 
/// as measurement capabilities. Each SourceMeter instrument 
/// is both a highly stable DC power source and a true 
/// instrument-grade 5-1/2 digit multimeter. The power 
/// source characteristics include low noise, precision, 
/// and readback. The multimeter capabilities include high 
/// repeatability and low noise. The result is a compact, 
/// single-channel, DC parametric tester. In operation, 
/// these instruments can act as a voltage source, a 
/// current source, a voltage meter, a current meter, 
/// and an ohmmeter.	
/// 		
////////////////////////////////////////////////////////////////////////////////////////////////////

class  SDeviceK2400 : public SDeviceGpib{
	Q_OBJECT;
	Q_ENUMS(MODE); //< on le declare pour les metaobjects


public :

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \enum	MODE
	///
	/// \brief	Values that represent the mode of the DC generator. 
	////////////////////////////////////////////////////////////////////////////////////////////////////
	enum MODE{
		CURRENT,
		VOLTAGE
	};

	// specific at K2400
	SDeviceK2400(QObject *parent=0);
	SDeviceK2400(MODE mode, QObject *parent=0);	

	Q_INVOKABLE void metaDataOnOff( bool onOff );

	Q_INVOKABLE virtual QScriptValue qsReadVI(void);
	Q_INVOKABLE virtual QScriptValue qsReadIV(void);

	virtual QList<double> readVI(void);
	virtual QList<double> readIV(void);

	Q_INVOKABLE virtual void putLocalMode();

	Q_INVOKABLE virtual double current( );
	Q_INVOKABLE virtual void setCurrent(double current );

	Q_INVOKABLE virtual double voltage( );
	Q_INVOKABLE virtual void setVoltage(double voltage);

	virtual void setMode(const MODE mode);
	Q_INVOKABLE virtual void setMode(const QString mode);

	virtual SDeviceK2400::MODE mode();
	Q_INVOKABLE virtual QString qsMode();

	Q_INVOKABLE virtual void activate();
	Q_INVOKABLE virtual void deactivate();
	Q_INVOKABLE bool isActivated();

	Q_INVOKABLE virtual void setVoltageRange(double Vmax);
	Q_INVOKABLE virtual void setCurrentRange(double Imax);
	Q_INVOKABLE virtual void setVoltMeasRange(double Vm);

	Q_INVOKABLE virtual double currentRange(void);
	Q_INVOKABLE virtual double voltageRange(void); 

	Q_INVOKABLE virtual bool autoCurrentRange();
	Q_INVOKABLE virtual void setAutoCurrentRange(bool onOff);
	Q_INVOKABLE virtual bool autoVoltageRange();
	Q_INVOKABLE virtual void setAutoVoltageRange(bool onOff);


	Q_INVOKABLE virtual void setCurrentCompliance(double Icomp);
	Q_INVOKABLE virtual void setVoltageCompliance(double Vcomp);

	Q_INVOKABLE virtual double currentCompliance();
	Q_INVOKABLE virtual double voltageCompliance();

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
	/// \fn	bool SDeviceK2400::available()
	///
	/// \brief	(Signal) send a signal when some thing important append
	///
	/// \author	Sylvain Martin
	/// \date	20/04/2012
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void logEvent(QString log, QString name);


protected:
	SGlobalMetaDataMap gmdm_;
	inline void setMetaData(const QString key, const QVariant value, const QString unit ="", const SMetaData::enumType type = SMetaData::string);
	bool metaDataOnOff_;
	double Vmax;		///< Voltage maximum
	double Imax;		///< Current maximum
	bool isActivated_;	///< device activated or not
	MODE mode_;			///< mesurement mode
	void SDeviceK2400::sendLogError( QString log );
};

#endif // SDEVICEK2400_H
