////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SError.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		1/20/2011
///
/// \brief	Declares the error class.
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

#ifndef SERROR_H_
#define SERROR_H_

#include <qstring.h>
#include "SDevice\SDeviceVirtual.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SError
///
/// \brief	class of object throw when an exception has been came. 
///
/// \author	Sylvain Martin
/// \date	1/20/2011
////////////////////////////////////////////////////////////////////////////////////////////////////

class  SError {
public :

	enum importance {FATAL, HIGHT, LOW, WARNING, NON};
	QString name;
	QString description;
	importance imp;

	SError(QString name, importance imp = FATAL,  QString description = "");
	operator QString();
	bool operator==(const SError &chaine);

	static void traitement(SDeviceVirtual * device, SError& error);
	static void traitement(SError& error);
protected:	
	QString stringImp(importance imp);

};

#endif //SERROR_H_