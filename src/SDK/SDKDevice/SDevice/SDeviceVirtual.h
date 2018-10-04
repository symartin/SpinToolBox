////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SDeviceVirtual.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		20/01/2011
///
/// \brief	declare a virtual class for all the devices
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

#ifndef SDEVICEVIRTUAL_H_
#define SDEVICEVIRTUAL_H_


#include <QString>
#include <QObject>
#include <QScriptable>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SDeviceVirtual
///
/// \brief	Virtual class for all the devices. It is virtual pur so it cannot be instancied.
///
/// \author	Sylvain Martin
/// \date	1/20/2011
/// 		
/// \ingroup SDeviceMod
////////////////////////////////////////////////////////////////////////////////////////////////////

class SDeviceVirtual:public QObject, protected QScriptable {
	Q_OBJECT;

public:

	SDeviceVirtual(QObject *parent=0): QObject(parent){} ;

	 Q_INVOKABLE virtual void init () = 0;
	 Q_INVOKABLE virtual QString name () const = 0;
	 Q_INVOKABLE virtual QString description()const = 0;
	 Q_INVOKABLE virtual bool available()=0;
	 Q_INVOKABLE virtual void setUnavailable()=0;

};



#endif /* SDEVICEVIRTUAL_H_ */
