////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SGpibInterface.h
///
/// \author		Sylvain Martin
/// \version	1.0
/// \date		1/20/2011
///
/// \brief	Declares the SGpibInterface class
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

#ifndef SGPIBINTERFACE_H_
#define SGPIBINTERFACE_H_

#include <QObject>
#include <QString>
#include <QList>
#include <qvariant.h>
#include <Windows.h>

#include "../gpib-32/ni488.h"
#include "../SError.h"

#define GPIB0 0  ///< the identifier of the GPIB board
#define EOTMODE DABend ///< mode of sending data to the devices

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SGpibInterface
///
/// \brief	Gpib interface.
///
/// \author	Sylvain Martin
/// \date	1/20/2011
/// \ingroup SInterfaceMod
////////////////////////////////////////////////////////////////////////////////////////////////////
/* GPIB status bit vector :                                */
/*       global variable ibsta and wait mask               */

#define ERR     (1<<15) /* Error detected                  */
#define TIMO    (1<<14) /* Timeout                         */
#define END     (1<<13) /* EOI or EOS detected             */
#define SRQI    (1<<12) /* SRQ detected by CIC             */
#define RQS     (1<<11) /* Device needs service            */
#define SPOLL   (1<<10) /* Board has been serially polled  */
#define EVENT   (1<<9)  /* An event has occured            */
#define CMPL    (1<<8)  /* I/O completed                   */
#define LOK     (1<<7)  /* Local lockout state             */
#define REM     (1<<6)  /* Remote state                    */
#define CIC     (1<<5)  /* Controller-in-Charge            */
#define ATN     (1<<4)  /* Attention asserted              */
#define TACS    (1<<3)  /* Talker active                   */
#define LACS    (1<<2)  /* Listener active                 */
#define DTAS    (1<<1)  /* Device trigger state            */
#define DCAS    (1<<0)  /* Device clear state              */

class SInterfaceGpib : public QObject {
	Q_OBJECT;

public:
	// equivalent du constructeur et du destructeur pour un singleton
	static SInterfaceGpib* instance();
	static void close();

	//getter
	Q_INVOKABLE QString description() const;
	Q_INVOKABLE bool init() const;
	Q_INVOKABLE bool available() const;
	Q_INVOKABLE int GPIBibsta();
	//enume de mode de device
	enum GpibElementMode {LISTENER, TALKER};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \struct	GpibElement
	///
	/// \brief	this structure defines one device (adress, name ...)
	///
	/// \author	Sylvain Martin
	/// \date	1/20/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	struct GpibElement{
		QString name;			///<name
		Addr4882_t PAD;         ///< Primary address
		Addr4882_t SAD;         ///< Secondary address
		GpibElementMode mode;
	};

	//active ou desactive la carte
	Q_INVOKABLE void activate(bool active);

	// change le mode d'un device
	//? recuperation de MagToolBox pas tres claire encore...
	Q_INVOKABLE void switcher(Addr4882_t address,GpibElementMode mode);
	void switcher(GpibElement& instrument ,GpibElementMode mode);

	 QList<GpibElement> deviceList(int maxDevice=30);
	 GpibElement findGpibElement(QString name);

	 Q_INVOKABLE void send(const Addr4882_t address,			const QString data);
	 void send(const GpibElement& instrument,		const QString data);
	 Q_INVOKABLE void send(Addr4882_t address,	const char *data);
	 void send(GpibElement& instrument,	const char *data);

	 Q_INVOKABLE void enableLocal(const Addr4882_t address);
	 void enableLocal(const GpibElement& instrument);

	 Q_INVOKABLE QVariant receive( const Addr4882_t  address,		const long bufferLong);
	 QVariant receive( const GpibElement&  instrument,	const long bufferLong);

	 ~SInterfaceGpib(void);

protected:
	// we want a singleton class
	 // Private constructor
	SInterfaceGpib();
	// Prevent assignment
	SInterfaceGpib(const SInterfaceGpib& sGpibInterface){}
	// Prevent copy-construction
	SInterfaceGpib& operator=(const SInterfaceGpib & sGpibInterface){}

	 SError gpibError(SError error);

	 static SInterfaceGpib* instance_; ///< stock the pointer to the singleton class
	 QString description_; ///< stock the description of the device
	 bool isActivated_; ///< stock if the interface is activated
	 bool isInit_; ///< stock if the interface has been initialised
	 int NumInstruments_;  ///< number of instrument detected on the GPIB board
};

#endif /* SGPIBINTERFACE_H_ */