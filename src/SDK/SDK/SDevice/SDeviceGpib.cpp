////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SDeviceGpib.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		1/20/2011
///
/// \brief	implante a virtual class or the GPIB devices
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
#include "SDeviceGpib.h"
#include "SDeviceError.h"
#include <qdebug>
#include <QtCore>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceGpib::gpibSend(QString commande)
///
/// \brief	send a direct commande to this device by gbib. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \param	commande	The commande sent to the device. 
///
/// \remark this function is normally used only by the other functions of the class, 
/// 		not by the user. It do not check anything So use this function carefully. 
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceGpib::gpibSend(QString commande){
	if (!available_)  logError(STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);
	
	try{	
		gpib_->send(elmt_, commande);
	}catch(SError error){
		SError::traitement(this,error);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QVariant SDeviceGpib::gpibRead(const long longBuffer)const
///
/// \brief	Read data in the GPIB board. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \param	longBuffer	length of the buffer, by default 131072 bits (128 Ko).
///
/// \return	. 
///
/// \remark this function is normally used only by the other functions of the class, 
/// 		not by the user. It do not check anything So use this function carefully.
////////////////////////////////////////////////////////////////////////////////////////////////////
QVariant SDeviceGpib::gpibRead(const long buffer) { 
	if (!available_)  logError(STRING_ERROR_GPIB_DEVICE_UNAVAILABLE);

	try{	
		return gpib_->receive(elmt_,buffer);
	}catch(SError error){
		SError::traitement(this,error);

	}

	return QVariant("");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceGpib::setGpibElement(const SInterfaceGpib::GpibElement elmt)
///
/// \brief	Sets a GPIB element which contains the contains the name, the primary and secondary address. . 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \param	elmt GPIB element. 
/// 			 
/// \remarks	Normaly the primary adress is auto set at the construction of the object. So use
/// 			this function carefully. 
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceGpib::setGpibElement(const SInterfaceGpib::GpibElement elmt){

	Q_ASSERT(elmt.PAD <=30 && elmt.PAD >0);
	elmt_ = elmt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Addr4882_t SDeviceGpib::PAD(void) const
///
/// \brief	Gets the PAD (Primary address) of the device. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \return	the PAD (Primary address). 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
Addr4882_t SDeviceGpib::PAD(void) const{

	return elmt_.PAD;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SInterfaceGpib::GpibElement SDeviceGpib::GpibElement(void) const
///
/// \brief	Gets the GPIB element which contains the contains the name, the primary and secondary address. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \return	the GPIB element. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SInterfaceGpib::GpibElement SDeviceGpib::GpibElement(void) const
{
	return elmt_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceGpib::setPAD(const Addr4882_t pad)
///
/// \brief	Sets a PAD (Primary address) of the device. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \param	pad	The pad. 
///
/// \remarks	Normaly the primary adress is auto set at the construction of the object. So use
/// 			this function carefully. 
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceGpib::setPAD(const Addr4882_t pad){
	Q_ASSERT(pad <=30 && pad >0);
	elmt_.PAD = pad;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SInterfaceGpib* SDeviceGpib::GpibInterface(void) const
///
/// \brief	Gets the gpib interface. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \return	a pointer to the GpibInterface.
/// 		
/// \remark this function is normally used only by the other functions of the class, 
/// 		not by the user. It do not check anything So use this function carefully.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SInterfaceGpib* SDeviceGpib::GpibInterface(void) const
{
	return gpib_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SDeviceGpib::name(void) const
///
/// \brief	Gets the name. 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
/// \return	The efective name of the device. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceGpib::name(void) const{
	return elmt_.name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SDeviceGpib::enableLocal(void)
///
/// \brief	actives the front panel commands (activates the "local mode"). 
///
/// \author	Sylvain Martin
/// \date	1/13/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SDeviceGpib::enableLocal(void){
	gpib_->enableLocal(elmt_.PAD);
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SDeviceGpib::delay(double i) 
///
/// \brief	Pause the application for i seconds
/// 
/// \param i the number of second. 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
void SDeviceGpib::delay(double i) 
{
	clock_t start,end;
	start=clock();

	while(((end=clock())-start)<=i*CLOCKS_PER_SEC){
		QCoreApplication::processEvents ();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SDeviceGpib::setUnavailable(void)
///
/// \brief Sets the device unavailable. 
///
////////////////////////////////////////////////////////////////////////////////////////////////////

void SDeviceGpib::setUnavailable(void){
	available_ = false;
}


