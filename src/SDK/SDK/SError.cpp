#include <qstring.h>
#include <qdebug.h>

#include "SDevice\SDeviceVirtual.h"



#include "SError.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>the stream operator for qDebug </summary>
///
/// <value>	The QDebug object </value>
////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
/// <remarks>	Sylvain Martin, 1/14/2011. </remarks>
///
/// <param name="name">			The name. </param>
/// <param name="imp">			The importance (FATAL, WARNING, WEAK or NON). </param>
/// <param name="description">	The description. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

SError::SError(	QString name, importance imp,  QString description){
		this->name = name;
		this->description = description;
		this->imp = imp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	cast the importance in QString. </summary>
///
/// <remarks>	Sylvain Martin, 1/14/2011. </remarks>
///
/// <param name="imp">	The importance. </param>
///
/// <returns>	a QString with FATAL, WARNING, WEAK or NON. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

QString SError::stringImp(importance imp){

	QString simp;
	switch(this->imp){
			case SError::FATAL:
				simp = "fatal";
				break;
			case SError::HIGHT:
				simp = "hight";
				break;
			case SError::LOW:
				simp = "low";
				break;
			case SError::WARNING:
				simp = "warning";
				break;
			case SError::NON:
				simp = "non";
				break;
	}
	return simp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	QString casting operator. </summary>
///
/// <remarks>	Sylvain Martin, 1/14/2011. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

SError::operator QString(void){
	return QString("ERROR (") + stringImp(this->imp) +") :" + this->name + QString("\n") + this->description + QString();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	overload of the comparaison operator </summary>
///
/// <remarks>	Sylvain Martin, 1/17/2011. </remarks>
///
/// <param name="chaine">	The error. </param>
///
/// <returns>	true if it succeeds, false if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

bool SError::operator==(const SError &error){
	return (this->name == error.name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Traitements. </summary>
///
/// <remarks>	Sylvain Martin, 1/17/2011. </remarks>
///
/// <param name="error">	[in,out] The error. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SError::traitement(SDeviceVirtual * device, SError& error){
		//Hierachie dans les erreurs !
		switch(error.imp){
			case SError::FATAL: // Fatal on arrete tout !!
				device->setUnavailable();
				throw error;
				break;

			case SError::HIGHT : // on met l'instrument en non disponible
			case SError::LOW:
				device->setUnavailable();
				qDebug()  << error;
			case SError::WARNING: // ba, pas si grave ...
				break;
			}
}

void SError::traitement(SError& error){
	//Hierachie dans les erreurs !
	switch(error.imp){
	case SError::FATAL:
		throw error;
		break;
	case SError::HIGHT : // on met l'instrument en non disponible
	case SError::LOW:
		qDebug()  << error;
	case SError::WARNING: // ba, pas si grave ...
		break;
	}
}
