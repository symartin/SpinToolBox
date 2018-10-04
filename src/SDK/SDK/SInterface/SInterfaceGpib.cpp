////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SGpibInterface.h
///
/// \author		Sylvain Martin
/// \version	1.0
/// \date		1/20/2011
///
/// \brief	Implants the SGpibInterface class.
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
////////////////////////////////////////////////////////////////////////////////////////////////////

//Qt include
#include "QtCore\qglobal.h"
#include "QtCore\qbitarray.h"
#include "QtCore\qdebug.h"
#include "QtCore\qstring.h"
#include "QtCore\qlist.h"
#include "QtCore\qvariant.h"

//Gpib include
#include <Windows.h>
#include "gpib-32/ni488.h"
#include <string.h>

#include "SInterfaceGpib.h"
#include "SDevice/SDeviceError.h"

// initialize pointer
SInterfaceGpib* SInterfaceGpib::instance_ = 0;

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn	SInterfaceGpib* SInterfaceGpib::instance()
 ///
 /// \brief	get the pointer to the singleton class
 ///
 /// \author	Sylvain Martin
 /// \date	1/7/2011
 ///
 /// \return	null if it fails, else.
 ///
 /// Implement the logic here to instantiate the class for the first time by validating the member
 /// pointer. If member pointer is already pointing to some valid memory it means that the first
 /// object is created and it should not allow for the next instantiation so simply return the
 /// member pointer without calling its ctor.
 ////////////////////////////////////////////////////////////////////////////////////////////////////

 SInterfaceGpib* SInterfaceGpib::instance(){
	if (NULL == instance_) {
        instance_ =  new SInterfaceGpib;
      }

	 return instance_;
}

 ////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SInterfaceGpib::~SInterfaceGpib(void)
///
/// \brief	Destructor.
///
/// \author	Sylvain Martin
/// \date	1/20/2011
////////////////////////////////////////////////////////////////////////////////////////////////////

SInterfaceGpib::~SInterfaceGpib(void){
	close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SInterfaceGpib::SInterfaceGpib()
///
/// \brief	Default constructor.
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \exception	SDEVICEERROR_GPIB_UNABLE_OPEN_BOARD	Thrown Thrown when gpib driver unable to open
/// 													board.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

SInterfaceGpib::SInterfaceGpib(){
	/*
	 *	SendIFC() resets the GPIB bus by asserting the 'interface clear' (IFC)
	 *	bus line for a duration of at least 100 microseconds. The board specified
	 *	by board_desc must be the system controller in order to assert IFC. The
	 *	interface clear causes all devices to untalk and unlisten, puts them into
	 *	serial poll disabled state (don't worry, you will still be able to conduct
	 *	serial polls), and the board becomes controller-in-charge.
	 */
    SendIFC(GPIB0);

	description_ = "TODO : put something here...";

    if (ibsta & ERR) {
		throw gpibError(SDEVICEERROR_GPIB_UNABLE_OPEN_BOARD);
    }else{
		isInit_ = true;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::close()
///
/// \brief	close the  the GPIB board.
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \exception	SDEVICEERROR_GPIB_NOT_INITIALISED	Thrown when gpib is not
/// 												initialised.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceGpib::close(){
	if(!instance_->isInit_){
		throw SDEVICEERROR_GPIB_NOT_INITIALISED;
	}else{
		ibonl (GPIB0, 0);
		instance_->isInit_ = false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SInterfaceGpib::description() const
///
/// \brief	retun a bref description of the GPIB device.
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \return	retun a bref description of the GPIB device.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

QString SInterfaceGpib::description() const {
	return description_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SInterfaceGpib::isInit() const
///
/// \brief	check if the device has been initialised or not.
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \return	true if it was Initialised otherwise false.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

bool SInterfaceGpib::init() const {
	return isInit_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SInterfaceGpib::isActivated() const
///
/// \brief	check if the device is activated or not.
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \return	true if it was activated otherwise false.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

bool SInterfaceGpib::available() const {
	return isActivated_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::activate(bool active)
///
/// \brief	activate or desactivate the GPIB device.
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \param	active	true to active.
///
/// \warning always deactivate the GPIB device before the end of the software.
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceGpib::activate(bool active) {
	qDebug() << " SInterfaceGpib::activate not yet available !!! ";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<SInterfaceGpib::GpibElement> SInterfaceGpib::deviceList(int maxDevice)
///
/// \brief	check the <c>maxDevice</c> first communication port and do the list of the connected devices.
///
/// \author	Sylvain Martin
/// \date	1/17/2011
///
/// \exception	SDEVICEERROR_GPIB_NOT_INITIALISED	if the device is not initialised.
/// \exception	SDEVICEERROR_GPIB_NOT_ACTIVATED		if the device is not activated.
/// \exception	SDEVICEERROR_GPIB_FINDLSTN			if the device is not activated.
/// \exception	SDEVICEERROR_GPIB_RECEIVE			if unable to issue FindLstn call.
///
/// \param	maxDevice	The maximum device (beween 1 and 30).
///
/// \return	a <c>QList&lt;GpibElement&gt;</c> with the name, the PAD  (Primary ADdress) and the
///			SAD (Secondary ADdress) of the connected devices.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

QList<SInterfaceGpib::GpibElement> SInterfaceGpib::deviceList(int maxDevice) {
	SendIFC(GPIB0);

	// la ou on va stoquer le rerour
	QList<GpibElement> tmpList;

	// on consider que la carte GPIB est déjà Controller-In-Charge cf init()
	if(!isInit_) throw SDEVICEERROR_GPIB_NOT_INITIALISED;
	if(!isActivated_) throw SDEVICEERROR_GPIB_NOT_ACTIVATED;

	/*
	*  Create an array containing all valid GPIB primary addresses,
	*  except for primary address 0.  Your GPIB interface board is at
	*  address 0 by default.  This array (Instruments) will be given to
	*  the function FindLstn to find all instruments.  The constant
	*  NOADDR, defined in NI488.H, signifies the end of the array.
	*/
	Addr4882_t *Instruments = new Addr4882_t[maxDevice+1];     // Array of primary addresses
	Addr4882_t *Result= new Addr4882_t[maxDevice+1];          // Array of listen addresses
	Q_ASSERT_X(Instruments && Result,"deviceList", "memory allocation probleme");

	for (int loop = 0; loop < maxDevice; loop++) {
		Instruments[loop] = (Addr4882_t)(loop + 1);
	}
	Instruments[maxDevice] = NOADDR; //NOADDR == le dernier element

	/*
	*  Print message to tell user that the program is searching for all
	*  active listeners.  Find all of the instruments on the bus.  Store
	*  the instrument addresses in the array Result. Note, the
	*  instruments must be powered on and connected with a GPIB cable in
	*  order for FindLstn to detect them. If the error bit ERR is set in
	*  ibsta, call GPIBCleanup with an error message.
	*/

	FindLstn(GPIB0, Instruments, Result, 31);
	if (ibsta & ERR){
		throw gpibError(SDEVICEERROR_GPIB_FINDLSTN);
	}

	/*
	 *  ibcntl contains the actual number of addresses stored in the
	 *  Result array. Assign the value of ibcntl to the variable
	 *  Num_Instruments. Print the number of instruments found.
	 */

    NumInstruments_ = ibcntl;

	/*
	*  The Result array contains the addresses of all the instruments
	*  found by FindLstn. Use the constant NOADDR, as defined in
	*  NI488.H, to signify the end of the array.
	*/
	Q_ASSERT(NumInstruments_ <=maxDevice); //pas de depasement de tableau
	Result[NumInstruments_] = NOADDR;

	/*
	*  Print out each instrument's PAD and SAD, one at a time.
	*
	*  Establish a FOR loop to print out the information. The variable
	*  LOOP will serve as a counter for the FOR loop and as the index
	*  to the array Result.
	*/

	for (int loop = 0; loop < NumInstruments_; loop++)
	{
		/*
		* on cree un element GPIB
		*/
		GpibElement GEtmp;
		char buffer[4096]; //buffer ou on va stocker la réponce lors de la demande du nom
		Addr4882_t device_addr[2];

		// tous les element trouver ici sont des listener
		GEtmp.mode = LISTENER;

		/*
		*  The low byte of the instrument address is the primary
		*  address. Assign the variable PAD the primary address of the
		*  instrument. The macro GetPAD, defined in NI488.H, returns
		*  the low byte of the instrument address.
		*/

		GEtmp.PAD = GetPAD(Result[loop]);

		/*
		*  The high byte of the instrument address is the secondary
		*  address. Assign the variable SAD the primary address of the
		*  instrument. The macro GetSAD, defined in NI488.H, returns
		*  the high byte of the instrument address.
		*/

		GEtmp.SAD = GetSAD(Result[loop]);

		//on prepar un tableau pour la fonction EnableRemote
		device_addr[0] = GEtmp.PAD;
		device_addr[1] = NOADDR;

		//on choisie avec quel device on travaille
		EnableRemote(GPIB0,device_addr);

		//on demande son nom
		SendDataBytes(GPIB0,const_cast<char*>("*IDN?\r\n"),7L,DABend);

		//on récupere son nom
		Receive(GPIB0, Result[loop], buffer, 4094L, STOPend);

		// erreur ??
		if (ibsta & ERR){
			throw gpibError(SDEVICEERROR_GPIB_RECEIVE);
		}

		// la fin de la chaine de caracter doit etre \0 (heritage du c)
		buffer[4095] = '\0';
		GEtmp.name = buffer;
		tmpList.append(GEtmp);
	}       /* End of FOR loop */

	// on nettoie deriere nous
	delete[] Instruments;
	delete[] Result;

	return tmpList;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::switcher(GpibElement& instrument, GpibElementMode mode)
///
/// \brief	switch the mode of the device GpibElement&amp; elmt.
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \param [in,out]	instrument	The instrument.
/// \param	mode				The mode.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceGpib::switcher(GpibElement& instrument, GpibElementMode mode){
	if(instrument.mode != mode){
		instrument.mode = mode;
		switcher(instrument.PAD,mode);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::switcher(Addr4882_t address,GpibElementMode mode)
///
/// \brief	switch the mode of the device Addr4882_t instrument.
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \exception	SDEVICEERROR_GPIB_SWITCHER_SENDER	Thrown when GPIB Unable to switch the
/// 												 device to sender.
///
/// \param	address	The instrument.
/// \param	mode	The mode.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceGpib::switcher(Addr4882_t address,GpibElementMode mode){
	// on fait une liste, mais il n'y aura q'un element utile le [0], le deusieme
	// est l'indicateur de fin de liste NOADDR.
	Addr4882_t str_dev[2];

	switch (mode){
		case LISTENER :
			str_dev[0] = address;
			str_dev[1] = NOADDR;
			SendSetup(GPIB0,str_dev);

			if (ibsta & ERR){
				throw gpibError(SDEVICEERROR_GPIB_SWITCHER_SENDER);
			}
			break;

		case TALKER :
			ReceiveSetup(GPIB0, address);
			if (ibsta & ERR){
				throw gpibError(SDEVICEERROR_GPIB_SWITCHER_TALKER);
			 }
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::send(Addr4882_t address, QString data)
///
/// \brief	Send this data to one device (in ASCII).
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \exception	SDEVICEERROR_GPIB_SEND	Thrown when GPIB Unable to send data.
///
/// \param	address	The address of the device (between 1 and 30).
/// \param	data	The data to send (in text form).
///
/// \remarks	the data will be cast in char * (with QByteArray)
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceGpib::send(Addr4882_t address, QString data){
	Q_ASSERT((address > 0 && address <=30));

	// pour transformer le Qstring en char *
	QByteArray ba = data.toAscii();
	char* charData = ba.data();

	//nombre de caractere
	long count = data.toLatin1().size();

	//on envoie
	Send(GPIB0, address, (PVOID)charData, count, EOTMODE);

	if (ibsta & ERR){
		throw gpibError(SDEVICEERROR_GPIB_SEND);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::send(const GpibElement& instrument, const QString data)
///
/// \brief	Send this data to one device (in ASCII).
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \param	instrument	The instrument thas the data will be sent (the function sent to the
/// 					instrument.PAD adress).
/// \param	data		The data to send (in text form).
///
/// \remarks	the data will be cast in char * (with QByteArray)
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceGpib::send(const GpibElement&  instrument, const QString data){
	send(instrument.PAD, data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::send(Addr4882_t address, const char *data)
///
/// \brief	Send this data to one device (in ASCII).
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \exception	SDEVICEERROR_GPIB_SEND	GPIB Unable to send data.
///
/// \param	address	The address of the device (between 1 and 30).
/// \param	data	The data, it must fini by '\0'.
///
/// \remarks	Use preferently the function with data in QString because of the pointeur and the
/// 			'\0' problems.
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceGpib::send(Addr4882_t address, const char *data){
	Q_ASSERT((address > 0 && address <=30));

	//on envoie
	Send(GPIB0, address, (PVOID)data, strlen(data), EOTMODE);

	if (ibsta & ERR){
		throw gpibError(SDEVICEERROR_GPIB_SEND);
	}
}

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn	void SInterfaceGpib::send(GpibElement& instrument, const char *data)
 ///
 /// \brief	Send this data to one device (in ASCII).
 ///
 /// \author	Sylvain Martin
 /// \date	1/7/2011
 ///
 /// \param [in,out]	instrument	The instrument thas the data will be sent (the function sent
 /// 								to the instrument.PAD adress).
 /// \param	data					The data, it must fini by '\0'.
 ///
 /// \remarks		Use preferently the function with data in QString because of the pointeur and
 /// 				the '\0' problems.
 ////////////////////////////////////////////////////////////////////////////////////////////////////

 void SInterfaceGpib::send(GpibElement& instrument,	const char *data){
	 send(instrument.PAD,data);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QVariant SInterfaceGpib::receive( Addr4882_t address, long bufferLong)
///
/// \brief	receive this message (in ASCII).
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \exception	SDEVICEERROR_GPIB_RECEIVE	Thrown when GPIB Unable to receive data.
///
/// \param	address		The address of the device (between 1 and 30).
/// \param	bufferLong	The length of the buffer (e.g. if it is 100L it will take the
/// 					  all the characters until the 100th).
///
/// \return	a \c QVariant with the data in it.
///
/// \remarks	the data will be cast in QVariant (with QByteArray)
/// \remarks	HACK : j'ai enlevé le throw car ça planter systématiquement, qd erreur, je ne sais pas pk ...
////////////////////////////////////////////////////////////////////////////////////////////////////

QVariant SInterfaceGpib::receive( Addr4882_t address, long bufferLong){
	char * buffer = new char[bufferLong];

	for (int i = 0; i <bufferLong-1; i++ ){
		buffer[i]=0;
	}
	buffer[bufferLong-1] = '\0';

	Receive(GPIB0 , address, buffer, bufferLong, STOPend);
	buffer[ibcnt]='\0'; // on met un fin de chaine sur le dernier caractere

	if (ibsta & ERR){
		// HACK : j'ai enlevé le throw car ça planter systématiquement, qd erreur, je ne sais pas pk ...
		qDebug() <<  gpibError(SDEVICEERROR_GPIB_RECEIVE);
		QVariant Retour("");
		return Retour;
	}else{
		QVariant Retour(buffer);	
		return Retour;
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QVariant SInterfaceGpib::receive(const GpibElement& instrument, long bufferLong)
///
/// \brief	receive this message (in ASCII).
///
/// \author	Sylvain Martin
/// \date	1/7/2011
///
/// \param	instrument	The instrument thas the data will be received (the
/// 					   function sent to the instrument.PAD adress).
/// \param	bufferLong	The lenght of the buffer (e.g. if it is 100L it will take the
/// 					  all the caracters until the 100th).
///
/// \return	the data.
///
/// \remarks	the data will be cast in QVariant (with QByteArray)
////////////////////////////////////////////////////////////////////////////////////////////////////

QVariant SInterfaceGpib::receive(const GpibElement&  instrument, long bufferLong){
	return receive(instrument.PAD, bufferLong);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SInterfaceGpib::GpibElement SInterfaceGpib::findGpibElement(QString name)
///
/// \brief	Searches for the first Gpib element that has a efective name containing name.
///
/// \author	Sylvain Martin
/// \date	1/17/2011
///
/// \exception	SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE	Thrown when The device has a problem.
///
/// \param	name	part of the efective name of the device.
///
/// \return	The found GpibElement, or an element with PAD=-1 if it is not found.
///
/// \remarks	the case is insensitive.
////////////////////////////////////////////////////////////////////////////////////////////////////

SInterfaceGpib::GpibElement SInterfaceGpib::findGpibElement(QString name){
	QList<GpibElement> list = deviceList();

	  foreach (SInterfaceGpib::GpibElement elmt, list){ //macro QT4 (c'est pas du vrai c++)
			if (elmt.name.contains (name, Qt::CaseInsensitive)){
				return elmt;
			}
	  }
	  throw SDEVICEERROR_GPIB_DEVICE_UNAVAILABLE;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SError SInterfaceGpib::gpibError(SError error)
///
/// \brief	add a description for the GPIB error.
///
/// \author	Sylvain Martin
/// \date	1/17/2011
///
/// \param	error	The error object.
///
/// \return	.
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////

SError SInterfaceGpib::gpibError(SError error){
	QString codeErrorIbsta;
	QString codeErrorIberr;

	 if (ibsta & ERR )  codeErrorIbsta = " ERR";
	 if (ibsta & TIMO)  codeErrorIbsta = " TIMO";
	 if (ibsta & END )  codeErrorIbsta = " END";
	 if (ibsta & SRQI)  codeErrorIbsta = " SRQI";
	 if (ibsta & RQS )  codeErrorIbsta = " RQS";
	 if (ibsta & CMPL)  codeErrorIbsta = " CMPL";
	 if (ibsta & LOK )  codeErrorIbsta = " LOK";
	 if (ibsta & REM )  codeErrorIbsta = " REM";
	 if (ibsta & CIC )  codeErrorIbsta = " CIC";
	 if (ibsta & ATN )  codeErrorIbsta = " ATN";
	 if (ibsta & TACS)  codeErrorIbsta = " TACS";
	 if (ibsta & LACS)  codeErrorIbsta = " LACS";
	 if (ibsta & DTAS)  codeErrorIbsta = " DTAS";
	 if (ibsta & DCAS)  codeErrorIbsta = " DCAS";

	 if (iberr == EDVR) codeErrorIberr = " EDVR <System Error>";
	 if (iberr == ECIC) codeErrorIberr = " ECIC <Not Controller In Charge>";
	 if (iberr == ENOL) codeErrorIberr = " ENOL <No Listener>";
	 if (iberr == EADR) codeErrorIberr = " EADR <Address error>";
	 if (iberr == EARG) codeErrorIberr = " EARG <Invalid argument>";
	 if (iberr == ESAC) codeErrorIberr = " ESAC <Not Sys Ctrlr>";
	 if (iberr == EABO) codeErrorIberr = " EABO <Op. aborted>";
	 if (iberr == ENEB) codeErrorIberr = " ENEB <No GPIB board>";
	 if (iberr == EOIP) codeErrorIberr = " EOIP <Async I/O in prg>";
	 if (iberr == ECAP) codeErrorIberr = " ECAP <No capability>";
	 if (iberr == EFSO) codeErrorIberr = " EFSO <File sys. error>";
	 if (iberr == EBUS) codeErrorIberr = " EBUS <Command error>";
	 if (iberr == ESTB) codeErrorIberr = " ESTB <Status byte lost>";
	 if (iberr == ESRQ) codeErrorIberr = " ESRQ <SRQ stuck on>";
	 if (iberr == ETAB) codeErrorIberr = " ETAB <Table Overflow>";

	QString description;
	QTextStream ts(&description);
	ts	<< "\n\tibsta : " << ibsta << " (" << codeErrorIbsta << ")"
		<< "\n\tiberr : " << iberr << " (" << codeErrorIberr << ")"
		<< "\n\tibcnt : " << ibcntl;

	error.description +=  description;

	return error;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::enableLocal(const Addr4882_t address)
///
/// \brief	Place specified device in local mod (i.e. it can be "programmed" from the front panel
/// controls).
///
/// \author	Sylvain Martin
/// \date	1/17/2011
///
/// \exception	gpibError	Thrown when gpib error.
///
/// \param	address	The address.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceGpib::enableLocal(const Addr4882_t address){
	// on fait une liste, mais il n'y aura q'un element utile le [0], le deusieme
	// est l'indicateur de fin de liste NOADDR.
	Addr4882_t str_dev[2];

	// on fait un tableau de 1 element
	str_dev[0] = address;
	str_dev[1] = NOADDR;

	EnableLocal(GPIB0,str_dev);

	if (ibsta & ERR){
			throw gpibError(SDEVICEERROR_GPIB_ENABLE_LOCAL);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::enableLocal(const GpibElement& instrument)
///
/// \brief	Place specified device in local mod (i.e. it can be "programmed" from the front panel
/// controls).
///
/// \author	Sylvain Martin
/// \date	1/17/2011
///
/// \param	instrument	The Gpib Element.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceGpib::enableLocal(const GpibElement& instrument){
	enableLocal(instrument.PAD);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE int SInterfaceGpib::ibsta(void)
///
/// \brief	Gets the state of the GPIB board.
///
/// \author	Sylvain Martin
/// \date	1/24/2011
///
/// \return	.
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE int SInterfaceGpib::GPIBibsta(void){
	return ibsta;
}