////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDeviceDaqFieldOneAxis.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		29/02/2012
///
/// \brief	Declare the plugin and the class SDeviceDaqFieldOneAxis
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
#ifndef SDEVICEDAQFIELDONEAXIS_H
#define SDEVICEDAQFIELDONEAXIS_H


#include "SDeviceDaqFieldOneAxis_global.h"
#include "SDKDevice/SDevicePluginInterface.h"

#include <QtCore>
#include <QtGui>
#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>


#define SDEVICEDAQFIELDONEAXIS_MAJOR_VERSION_COMPATIBILITY 2
#define SDEVICEDAQFIELDONEAXIS_MINOR_VERSION_COMPATIBILITY 0
#define SDEVICEDAQFIELDONEAXIS_VERSION 1.0
#define SDEVICEDAQFIELDONEAXIS_SHORT_NAME "DaqFieldOneAxis"

#include "SDKDevice/SpinToolBoxSDKDevice.h"

#if !defined(STB_SDK_DEVICE)
#error "The header file doesn't include SpinToolBoxSDK.h"
#elif SDEVICEDAQFIELDONEAXIS_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MAJOR_VERSION \
	&& SDEVICEDAQFIELDONEAXIS_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MINOR_VERSION
#error "This file was written for a SDK Device version 2.0 It cannot be used with another version."
#endif


class SInterfaceDaq ;


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
class SDEVICEDAQFIELDONEAXIS_EXPORT SDeviceDaqFieldOneAxisPlugin : public SDevicePluginInterface
{
	Q_INTERFACES(SDevicePluginInterface)
		Q_OBJECT

public:
	SDeviceDaqFieldOneAxisPlugin();
	~SDeviceDaqFieldOneAxisPlugin();

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
	SInterfaceDaq* DAQ;
};



#include <QString>
#include <QObject>
#include "NIDAQmx/NIDAQmx.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SInterfaceDaq
///
/// \brief	singleton class for the Ni-DAQmx interface. 
///
/// \author	Sylvain Martin
/// \date	1/20/2011
/// 		
/// \ingroup SInterfaceMod
///
/// \image html NI-DAQmx.gif "NI-DAQmx card"
///
/// NI-DAQmx is National Instruments' newest, next-generation data acquisition driver. 
/// NI-DAQmx incorporates an entirely new driver architecture and API, complete with new
/// functions and development tools for controlling National Instruments DAQ devices.  
/// NI-DAQmx is entirely separate from the Traditional NI-DAQ driver. The architectural 
/// changes and new features allow NI-DAQmx to deliver increased ease-of-use and improved 
/// performance over the Traditional NI-DAQ driver.
/// NI-DAQmx defines and enforces a state model, which eliminates unnecessary reconfigurations
/// of input limits, timing, triggering, and accessories. This improvement significantly increases
/// overall performance, but is most noticeable in single-point software-timed analog input. 
/// The link below contains examples that illustrate the significant single-point software-timed 
/// speed improvement in NI-DAQmx over Traditional NI-DAQ. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////

class SInterfaceDaq : public QObject {
	Q_OBJECT;

public:

	// equivalent du constructeur et du destructeur pour un singleton
	static SInterfaceDaq* instance();
	~SInterfaceDaq(void);

	Q_INVOKABLE void metaDataOnOff(bool onOff);

	// Access the Prefactor
	Q_INVOKABLE double prefactor(void)				{ return(prefactor_);		};
	Q_INVOKABLE void setPrefactor(double prefactor)	{ prefactor_ = prefactor;	};

	//do a voltage sweep
	Q_INVOKABLE void sweep(double Vz,double dVz, int channel);

	//available accessors
	Q_INVOKABLE bool available();

	//running accessors
	Q_INVOKABLE bool running();
	//vOld accessors
	Q_INVOKABLE double vOld(int channel = 0);

	Q_INVOKABLE double timeSweep(double V,double dV,int channel = 0);
signals:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	inline double SInterfaceDaq::finished()
	///
	/// \brief	(SIGNAL) emitted when the task is finished, the board can do another 
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void finished();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	inline double SInterfaceDaq::unavailable()
	///
	/// \brief	(SIGNAL) emitted when the board becomes unavailable
	/// \todo not yet used
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void unavailable();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	inline double SInterfaceDaq::ready()
	///
	/// \brief	(SIGNAL) emitted when the board is anew available 
	/// \todo not yet used
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void ready();

private:
	bool metaDataOnOff_;
	//gestion des metadata
	inline void setMetaData(const QString key, const QVariant value, const QString unit ="", const SMetaData::enumType type = SMetaData::string);
	SGlobalMetaDataMap  gmdm_;

	// we want a singleton class
	// Private constructor
	SInterfaceDaq();
	// Prevent assignment
	SInterfaceDaq(const SInterfaceDaq& sSInterfacedaq){} 

	void loadSettings();

	// Prevent copy-construction  
	SInterfaceDaq& operator=(const SInterfaceDaq & sGpibInterface){} 

	//utility functions
	inline double fabs(double num);
	inline double sgn(double number);
	void delay(double i)   ;

	bool running_;
	bool available_;
	static SInterfaceDaq* instance_; ///< stock the pointer to the singleton class

	// ce prefacteur est utile pour corriger de la base 12 du kepco utile pour les fonctions
	// init_champ_perp et do_champ_perp. 
	double prefactor_; 

	//pour garder en memoire la derniere valeur
	double VOldChan0_; ///< pour garder en memoire la derniere valeur pour channel out 0
	double VOldChan1_; ///< pour garder en memoire la derniere valeur pour channel out 1


	double Vmax;		///< the maximum value for the daq in volts
	double Vmin;		///< the minimum value for the daq in volts	 
	QString ChanOut0;   ///< path to the channel out 0
	QString ChanOut1;	///< path to the channel out 1
	QString ChanIn1;	///< path to the channel in 0
	QString ChanIn2;	///< path to the channel in 1

	TaskHandle  VOut;  ///< handle(unsigned long) of the out task
	TaskHandle  VIn;   ///< handle(unsigned long of the in task

	int BufferSizeOut;
	int BufferSizeIn;

	double     *DataOut;	///< \c double[BufferSizeOut] stocking the consigne for out task
	double     *DataIn;		///< \c double[BufferSizeIn] stocking the consigne for in task

	signed long SamplesWritten;  //TODO je n'ai pas la moindre idée de sont utilisation ...
	signed long SamplesRead;     //TODO je n'ai pas la moindre idée de sont utilisation ...
	int			autoStart;       //TODO je n'ai pas la moindre idée de sont utilisation ...

	double timeout;




};

#endif // SDEVICEDAQFIELDONEAXIS_H
