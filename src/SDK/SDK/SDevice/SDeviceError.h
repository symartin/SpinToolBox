////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SDeviceError.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		1/20/2011
///
/// \brief	declare the exception for the device module
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
#ifndef SDEVICEERROR_H_
#define SDEVICEERROR_H_

#include <QString>

#include "..\SError.h"




 
												
const SError SDEVICEERROR_CANNOT_CONVERT_DATA		= SError("GPIB QVariant is not convertible"				, SError::LOW);		///< Thrown when the recived data cannot be convert.

const SError SDEVICEERROR_GPIB_NOT_INITIALISED		= SError("GPIB device is not Initialised"				, SError::HIGHT);		///< The GPIB board cannot be initialised

const SError SDEVICEERROR_GPIB_NOT_ACTIVATED		= SError("GPIB device is not activated"					, SError::HIGHT);		///< The GPIB board is not activated

const SError SDEVICEERROR_GPIB_UNABLE_OPEN_BOARD	= SError("GPIB Unable to open the board"				, SError::HIGHT);	///< The soft cannot open the GPIB board

const SError SDEVICEERROR_GPIB_FINDLSTN				= SError("GPIB Unable to issue FindLstn call"			, SError::WARNING, "We must turn on, at least, one device to use the GPIB");	///< The soft cannot find any device

const SError SDEVICEERROR_GPIB_SWITCHER_SENDER		= SError("GPIB Unable to switch the device to sender"	, SError::HIGHT);   ///< The soft cannot switch the device to sender

const SError SDEVICEERROR_GPIB_SWITCHER_TALKER		= SError("GPIB Unable to witch the device to talker"	, SError::HIGHT);	///< The soft cannot switch the device to talker

const SError SDEVICEERROR_GPIB_SEND					= SError("GPIB Unable to send data"						, SError::HIGHT);	///< The soft cannot send data

const SError SDEVICEERROR_GPIB_RECEIVE				= SError("GPIB Unable to receive data"					, SError::HIGHT);	///< The soft receive data

const SError SDEVICEERROR_GPIB_ENABLE_LOCAL			= SError("GPIB Unable to put the local mode"			, SError::HIGHT);	///< The soft cannot put the divice in local mode

const SError SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	= SError("GPIB the device is unavailable"				, SError::WARNING,      "is plugged in? is it on?");	///< The device has a problem or is busy





const QString STRING_ERROR_CANNOT_CONVERT_DATA		= "GPIB QVariant is not convertible";		///< Thrown when the recived data cannot be convert.

const QString STRING_ERROR_GPIB_NOT_INITIALISED		= "GPIB device is not initialised";		///< The GPIB board cannot be initialised

const QString STRING_ERROR_GPIB_NOT_ACTIVATED		= "GPIB device is not activated";		///< The GPIB board is not activated

const QString STRING_ERROR_GPIB_UNABLE_OPEN_BOARD	= "GPIB Unable to open the board";	///< The soft cannot open the GPIB board

const QString STRING_ERROR_GPIB_FINDLSTN			= "GPIB Unable to issue FindLstn call";	///< The soft cannot find any device

const QString STRING_ERROR_GPIB_SWITCHER_SENDER		= "GPIB Unable to switch the device to sender";   ///< The soft cannot switch the device to sender

const QString STRING_ERROR_GPIB_SWITCHER_TALKER		= "GPIB Unable to witch the device to talker";	///< The soft cannot switch the device to talker

const QString STRING_ERROR_GPIB_SEND				= "GPIB Unable to send data";	///< The soft cannot send data

const QString STRING_ERROR_GPIB_RECEIVE				= "GPIB Unable to receive data";	///< The soft receive data

const QString STRING_ERROR_GPIB_ENABLE_LOCAL		= "GPIB Unable to put the local mode";	///< The soft cannot put the divice in local mode

const QString STRING_ERROR_GPIB_DEVICE_UNAVAILABLE	= "GPIB the device is unavailable";	///< The device has a problem or is busy



#endif /* SDEVICEERROR_H_ */