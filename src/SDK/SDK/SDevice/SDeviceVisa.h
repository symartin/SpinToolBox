////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SDeviceVisa.h
///
/// \author		Sylvain Martin
/// \version	1.0
/// \date		19/04/2012
///
/// \brief	Declares the SDeviceVisa class
///
/// This file is part of the SpinToolBox project
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

#ifndef SDEVICEVISA_H_
#define SDEVICEVISA_H_
 
#define SDEVICEVISA_NAME "Visa"

#include "SDK\visa32\visa.h"
#include <QtCore>
#include <QObject>
#include <QScriptable>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceGpib
///
/// \brief	class for all the GPIB devices. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
/// 		
/// \ingroup SDeviceMod
////////////////////////////////////////////////////////////////////////////////////////////////////

class SDeviceVisa: public QObject {
	Q_OBJECT;
public:

	SDeviceVisa(QObject *parent=0) : QObject(parent),  available_(false){}; //< constructeur Qt de QObject

public :
	SDeviceVisa* VisaInterface () const;

	Q_INVOKABLE virtual bool init(QString add);
	Q_INVOKABLE QStringList findAdress(QString name);
	Q_INVOKABLE QStringList findElement(QString name);

	Q_INVOKABLE  virtual QString address(QString cmd) const;
	Q_INVOKABLE  virtual bool visaSend(QString cmd);
	Q_INVOKABLE  virtual QString visaRead(const long buffer = 131072);

	Q_INVOKABLE virtual QString name(void);
	Q_INVOKABLE void setAvailable(bool OnOff = true);
	Q_INVOKABLE bool available(void) const;

	Q_INVOKABLE void delay(double i) const ;
	Q_INVOKABLE void setTimeOut(double time);

signals:
	void logError(QString log, QString name);
	void logEvent(QString log, QString name);

protected:
	bool available_;
	QString address_;
	void sendLogError(QString log);
	
//	 In every source code or header file that you use it is necessary to prototype
//	 your VISA variables at the beginning of the file. You need to declare the VISA
//	 session, VISA integers, VISA strings, VISA pointers, and VISA floating variables. 
//	 Remember that if you are prototyping variables that are to be used as part of the
//	 VISA session that need this prototyping. As an example, above retCount has been
//	 prototyped as a static variable to this particular module.   It is an integer of
//	 bit length 32. If you are uncertain how to declare your VISA prototypes refer
//	 to the VISA help under the Section titled Type Assignments Table. The VISA
//	 help is located in your NI-VISA directory or folder.
	
	 ViSession defaultRM;     
	 ViSession instr;     
	 ViUInt32 retCount;
	 ViUInt32 writeCount;
	 ViStatus status;

};

#endif