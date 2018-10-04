////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevicePSAE4440A.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		14/03/2011
///
/// \brief	Declares the SDevicePSAE4440A class
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

#ifndef SDEVICEPSAE4440A_H
#define SDEVICEPSAE4440A_H

#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>


#include "SDK/SData/SData2D.h"
#include "SDKDevice/SDevicePluginInterface.h"
#include "SDK/SpinToolBoxSDK.h"
#include "SDKDevice/SDevice/SDeviceGpib.h"

#include "SDevicePSAE4440A_global.h"


#define SDEVICEPSAE4440A_MAJOR_VERSION_COMPATIBILITY 2
#define SDEVICEPSAE4440A_MINOR_VERSION_COMPATIBILITY 0
#define SDEVICEPSAE4440A_VERSION 1.5
#define SDEVICEPSAE4440A_SHORT_NAME "PSAE4440A"

#include "SDKDevice/SpinToolBoxSDKDevice.h"


#if SDEVICEDAQFIELDONEAXIS_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MAJOR_VERSION \
	&& SDEVICEDAQFIELDONEAXIS_VERSION_COMPATIBILITY != STB_SDK_DEVICE_MINOR_VERSION
#error STB_SDK_DEVICE_ERROR_TXT
#endif







class SDevicePSAE4440A;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDevicePSAE4440APlugin
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
class SDEVICEPSAE4440A_EXPORT SDevicePSAE4440APlugin : public SDevicePluginInterface
{
	Q_INTERFACES(SDevicePluginInterface)
		Q_OBJECT

public:
	SDevicePSAE4440APlugin();
	~SDevicePSAE4440APlugin();

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

	SDevicePSAE4440A * PSAE4440A;
	int state_;
};



////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDevicePSAE4440A
///
/// \brief	Provides control of the E4440A PSA Spectrum Analyzer, 3 Hz - 26.5 GHz, Agilent. 
///		
/// \ingroup SDeviceMod
///  
/// \image html spectrum_analyzer_E4440A.jpg "spectrum analyzer E4440A"
/// 								 	   		 		 
/// The Agilent E4440A PSA high-performance spectrum analyzer measures and monitors complex RF and
/// microwave signals up to 26.5 GHz. With optional external mixing, the frequency coverage expands
/// to 110 GHz by Agilent external mixer, and to 325 GHz by other vendors' mixer.
/// 
/// \par Performance
///
///    \li +/-0.19 dB absolute amplitude accuracy
///    \li -155 dBm (-169 dBm w/preamp) displayed average noise level (DANL)
///    \li -118 dBc/Hz phase noise at 10 kHz offset
///    \li 81 dB W-CDMA ACLR dynamic range
///
/// \par  Analysis bandwidth
///
///    \li 10 MHz analysis bandwidth (option B7J for the Basic mode)
///    \li Optional 40 or 80 MHz analysis bandwidth to capture and measure complex signals. View the demo
///    \li -78 dB (nominal) third order intermodulation for 40 or 80 MHz analysis bandwidth
///    \li Up to 300 MHz analysis bandwidth for calibrated VSA measurements
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class SDevicePSAE4440A: public SDeviceGpib {
	Q_OBJECT;

public:
	SDevicePSAE4440A(QObject *parent = NULL);
	SDevicePSAE4440A(double const FreqStart, double const FreqStop, double const RBW, int const average = 0, QObject *parent = NULL);
	virtual ~SDevicePSAE4440A();

	void setScriptEngin(QScriptEngine * engine);


	Q_INVOKABLE virtual void metaDataOnOff(bool onOff);

	//@{
	Q_INVOKABLE virtual void setFreqStart(double const freq);
	Q_INVOKABLE virtual double freqStart();

	Q_INVOKABLE virtual void setFreqStop(double const freq);
	Q_INVOKABLE virtual double freqStop();

	Q_INVOKABLE virtual void setRbw(double const RBW);
	Q_INVOKABLE virtual double rbw();
	Q_INVOKABLE virtual double checkRbw(double const rbw);

	Q_INVOKABLE virtual void setAttenuation(int const Att);
	Q_INVOKABLE virtual int attenuation();

	Q_INVOKABLE virtual void setNbPoints(int const NbPts);
	Q_INVOKABLE virtual int nbPoints();

	Q_INVOKABLE virtual void setNbAverage(int const NbAvrg);
	Q_INVOKABLE virtual int nbAverage();

	Q_INVOKABLE virtual void setRefLevel(double const RefLvl);
	Q_INVOKABLE virtual double refLevel();

	Q_INVOKABLE virtual void setLogDisplay(bool const OnOff);
	Q_INVOKABLE virtual bool logDisplay();

	Q_INVOKABLE virtual double sweepTime();

	//@}
	//@name Miscellaneous 
	//@{
	struct Point2D {
		double x;
		double y;
		Point2D(){x=0;y=0;};
	};
	Q_INVOKABLE virtual void setMarker(double const frequence, int num=1);
	Q_INVOKABLE virtual void marker(bool const OnOff, int const num=1);
	Q_INVOKABLE virtual double readMarker(int const num);
	virtual SDevicePSAE4440A::Point2D MaxSearch();
	Q_INVOKABLE virtual void restart();
	//@}

	//@name Measurement
	//@{
	virtual SData2D * readSpectrum();
	Q_INVOKABLE virtual QScriptValue qsReadSpectrum();

	//@}
	//@name Inherited from SDeviceVirtual
	//@{
	//herité de SDeviceVirtual
	Q_INVOKABLE virtual void init ();
	Q_INVOKABLE virtual QString name () const;
	Q_INVOKABLE virtual QString description()const;
	Q_INVOKABLE virtual bool available();
	//@}
private:
	bool metaDataOnOff_;
	bool mark1Active_;
	bool mark2Active_;
	inline void setMetaData(const QString key, const QVariant value, const QString unit ="", const SMetaData::enumType type = SMetaData::string);
	SGlobalMetaDataMap gmdm_;
	QScriptEngine * engine_;

};




#endif // SDEVICEPSAE4440A_H
