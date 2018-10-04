
#include "SDeviceVisa.h"
#include <time.h>
#include <QtCore>



////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn bool SDeviceVisa::init(QString adresse)
///
/// \brief	(SCRIPTABLE) init the communication with the device at the adress \c add.
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
/// \param	data	The data to send (in text form).
/// \return true if all is ok, false if there is an error
///
/// \remarks	the data will be cast in char * (with QByteArray)
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDeviceVisa::init(QString add){


//	 First we must call viOpenDefaultRM to get the manager
//	 handle.  We will store this handle in defaultRM.

   status=viOpenDefaultRM (&defaultRM);
   if (status < VI_SUCCESS)  
   {
	  sendLogError("WARNING : VISA : Could not open a session to the VISA Resource Manager!");
	  return false;
   }
														  

//	 Now we will open a VISA session to the serial port (COM1).
//	 We must use the handle from viOpenDefaultRM and we must   
//	 also use a string that indicates which instrument to open.  This
//	 is called the instrument descriptor.  The format for this string
//	 can be found in the function panel by right clicking on the 
//	 descriptor parameter. After opening a session to the
//	 device, we will get a handle to the instrument which we 
//	 will use in later VISA functions.  The AccessMode and Timeout
//	 parameters in this function are reserved for future
//	 functionality.  These two parameters are given the value VI_NULL.

   // pour transformer le Qstring en char *
   QByteArray ba = add.toAscii();
   char* charAdd = ba.data();

   status = viOpen (defaultRM, charAdd, 4, VI_NULL, &instr);
   if (status < VI_SUCCESS) 
   {
	   sendLogError("WARNING : VISA : Cannot open a session to the device.\n");
	   sendLogError("device address : " + add);

		available_ = false;
		return false;
   }

	// Set timeout value to 5000 milliseconds (1 seconds).
   status = viSetAttribute (instr, VI_ATTR_TMO_VALUE, 1000);
  
   if (status < VI_SUCCESS)  
   {
	   sendLogError("WARNING : VISA : Error writing to the device\n" );
	   sendLogError("          error number : " + status);
	   return false;
   }



   return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn bool SDeviceVisa::visaSend(QString cmd)
///
/// \brief	(SCRIPTABLE) Send this command to the device (in ASCII).
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
/// \param	data	The data to send (in text form).
/// \return true if all is ok, false if there is an error
///
/// \remarks	the data will be cast in char * (with QByteArray)
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  bool SDeviceVisa::visaSend(QString cmd)
{
	if (!available_) return false;

	// pour transformer le Qstring en char *
	QByteArray ba = cmd.toAscii();
	char* charCmd = ba.data();

	//nombre de caractere
	long count = cmd.toLatin1().size();

	//strcpy(stringinput,"*IDN?\n");
	status = viWrite (instr, (ViBuf)charCmd, count, &writeCount);
	if (status < VI_SUCCESS)  
	{
		sendLogError("WARNING : VISA : Error writing to the device\n") ;
		sendLogError("\tcommande send : " + cmd);
		sendLogError("\terror number : " + QString::number(status));
		sendLogError("\terror address : " + address_);
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  QString SDeviceApsin20g::visaRead()
///
/// \brief	(SCRIPTABLE) Read the response of the device (in ASCII).
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
/// \param	data	The data to send (in text form).
/// \return true if all is ok, false if there is an error
///
/// \remarks	the data will be cast in char * (with QByteArray)
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE  QString SDeviceVisa::visaRead(const long bufferSize){

	if (!available_) return QString();
	unsigned char *buff = new unsigned char[bufferSize];

	status = viRead (instr, buff, bufferSize, &retCount);
	if (status < VI_SUCCESS) 
	{
		sendLogError("WARNING : VISA : Error reading from the device") ;
		sendLogError("\terror number : " + QString::number(status));
		sendLogError("\terror address : " + address_);

		return QString("");
	}else{
		return  QString::fromAscii((const char*)buff, retCount) ;
	}

	delete buff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  QStringList SDeviceVisa::findAdress(QString expression)
///
/// \brief	(SCRIPTABLE) find all the device that correspond to expression
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
/// \param	expression	This is a regular expression followed by an optional logical expression.
/// \return a list of the found devices
///
/// \remarks see the documentation of viFindRsrc() in the visa documentation.	
///
/// Special Characters for expression:
///  \li \c ? Matches any one character.
///  \li \c \\ Makes the character that follows it an ordinary character.
///  \li \c [list] Matches any one character from the enclosed list.
///  \li \c [^list] Matches any character not in the enclosed list.
///  \li \c * Matches 0 or more occurrences of the preceding character or expression.
///  \li \c exp|exp Matches either the preceding or following expression.
///  \li \c (exp) Grouping characters or expressions.
///  \li \c + Matches 1 or more occurrences of the preceding character or expression.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList SDeviceVisa::findAdress(QString expression){

	 char instrDescriptor[VI_FIND_BUFLEN];
	 ViUInt32 numInstrs=0;
	 ViFindList findList;
	 ViSession defaultRM=0, instr=0;
	 ViStatus status;
	 unsigned char buffer[512];
	 QStringList res;

	 
	// pour transformer le Qstring en char *
	QByteArray ba = expression.toAscii();
	char* charCmd = ba.data();

	//nombre de caractere
	long count = expression.toLatin1().size();


	/* First we will need to open the default resource manager. */
	status = viOpenDefaultRM (&defaultRM);
	if (status < VI_SUCCESS)
	{
		sendLogError("WARNING : VISA : Could not open a session to the VISA Resource Manager!") ;
		sendLogError("\terror number : " + QString::number(status));
		return res;
	}  

	  /*
     * Find all the VISA resources in our system and store the number of resources
     * in the system in numInstrs.  Notice the different query descriptions a
     * that are available.

        Interface         Expression
    --------------------------------------
        GPIB              "GPIB[0-9]*::?*INSTR"
        VXI               "VXI?*INSTR"
        GPIB-VXI          "GPIB-VXI?*INSTR"
        Any VXI           "?*VXI[0-9]*::?*INSTR"
        Serial            "ASRL[0-9]*::?*INSTR"
        PXI               "PXI?*INSTR"
        All instruments   "?*INSTR"
        All resources     "?*"
    */
	status = viFindRsrc (defaultRM, charCmd, &findList, &numInstrs, instrDescriptor);


	if (status < VI_SUCCESS){
			sendLogError("WARNING : VISA : An error occurred finding the next resource.") ;
			sendLogError("\terror number : " + QString::number(status));
			sendLogError(QString("\terror address : %s").arg(instrDescriptor));
			viClose (defaultRM);
			return QStringList();
	}

	res.append(QString::fromAscii((const char*)instrDescriptor, retCount) );

		while (--numInstrs){

			/* stay in this loop until we find all instruments */
			status = viFindNext (findList, instrDescriptor);  /* find next desriptor */

			if (status < VI_SUCCESS){   /* did we find the next resource? */
				sendLogError("WARNING : VISA : An error occurred finding the next resource.") ;
				sendLogError("\terror number : " + QString::number(status));
				viClose (defaultRM);
				return res; 
			} 

		} /* end while */

		status = viClose(findList);
		status = viClose (defaultRM);

		return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  QStringList SDeviceVisa::findAdress(QString name)
///
/// \brief	(SCRIPTABLE) find all the device that have name in their name
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
/// \return a list of the found devices
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList SDeviceVisa::findElement(QString name){

	 char instrDescriptor[VI_FIND_BUFLEN];
	 ViUInt32 numInstrs=0;
	 ViFindList findList;
	 ViSession defaultRM=0, instr=0;
	 ViStatus status;
	 unsigned char buffer[512];
	 QStringList res;
	 QString findName;
	 static char stringinput[256];


	/* First we will need to open the default resource manager. */
	status = viOpenDefaultRM (&defaultRM);
	if (status < VI_SUCCESS)
	{
		sendLogError("WARNING : VISA : Could not open a session to the VISA Resource Manager!") ;
		sendLogError("\terror number : " + QString::number(status));
		return res;
	}  


     // Find all the VISA resources in our system and store the number of resources
     // in the system in numInstrs.  Notice the different query descriptions a
     // that are available.
	status = viFindRsrc (defaultRM, "?*INSTR", &findList, &numInstrs, instrDescriptor);

	if (status < VI_SUCCESS){
			sendLogError("WARNING : VISA : An error occurred finding the next resource.") ;
			sendLogError("\terror number : " + QString::number(status));
			sendLogError(QString("\terror address : %s").arg(instrDescriptor));
			viClose (defaultRM);
			return QStringList();
	}

	/* Now we will open a session to the instrument we just found. */
	status = viOpen (defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
	if (status < VI_SUCCESS)
	{
		sendLogError(QString("WARNING : VISA :An error occurred opening a session to"));
		sendLogError("\terror number : " + QString::number(status));
		sendLogError(QString("\terror address : %s").arg(instrDescriptor));

	}else{

		strcpy(stringinput,"*IDN?\n");
		ViUInt32 BytesToWrite = (ViUInt32)strlen(stringinput);

		//we ask the name
		status = viWrite (instr, (ViBuf)stringinput, BytesToWrite, &writeCount);
		status = viRead (instr, buffer, 512, &retCount);

		QString namefind = QString::fromAscii((const char*)buffer, retCount);

		if (namefind.contains (name, Qt::CaseInsensitive)){
			res.append(QString::fromAscii((const char*)instrDescriptor) );
		}

		// Now close the session.                     
		viClose (instr);
	}



		while (--numInstrs)
		{
			/* stay in this loop until we find all instruments */
			status = viFindNext (findList, instrDescriptor);  /* find next desriptor */
			if (status < VI_SUCCESS) 
			{   /* did we find the next resource? */
				sendLogError("WARNING : VISA : An error occurred finding the next resource.") ;
				sendLogError("\terror number : " + QString::number(status));
				viClose (defaultRM);
				return res; 
			} 

			status = viOpen (defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
			if (status < VI_SUCCESS)
			{
				sendLogError(QString("WARNING : VISA :An error occurred opening a session to"));
				sendLogError("\terror number : " + QString::number(status));
				sendLogError(QString("\terror address : %s").arg(instrDescriptor));
			}else{

				/* Now we will open a session to the instrument we just found. */
				status = viOpen (defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
				if (status < VI_SUCCESS)
				{
					sendLogError(QString("WARNING : VISA :An error occurred opening a session to"));
					sendLogError("\terror number : " + QString::number(status));
					sendLogError(QString("\terror address : %s").arg(instrDescriptor));

				}else{

					
					strcpy(stringinput,"*IDN?\n");
					ViUInt32 BytesToWrite = (ViUInt32)strlen(stringinput);

					//we ask the name
					status = viWrite (instr, (ViBuf)stringinput, BytesToWrite, &writeCount);
					status = viRead (instr, buffer, 512, &retCount);

					QString namefind = QString::fromAscii((const char*)buffer, retCount);

						if (namefind.contains (name, Qt::CaseInsensitive)){
							res.append(QString::fromAscii((const char*)instrDescriptor) );
						}

						// Now close the session.                     
						viClose (instr);
				}
			}

		}    /* end while */

		status = viClose(findList);
		status = viClose (defaultRM);

		return res;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  QString address(QString cmd) const
///
/// \brief	(SCRIPTABLE) return the address of visa the device
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceVisa::address(QString cmd) const{
	return address_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  QString SDeviceVisa::name(void) const
///
/// \brief	(SCRIPTABLE) return the address of visa the device
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SDeviceVisa::name(void){
	 if (!available_) return QString();
	 visaSend("*IDN?\n");
	 delay(0.001);
	 return visaRead();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  QString address(QString cmd)
///
/// \brief	(SCRIPTABLE) return the address of visa the device
///
/// \author	Sylvain Martin
/// \date	19/04/2012
///
////////////////////////////////////////////////////////////////////////////////////////////////////
 void SDeviceVisa::setAvailable(bool OnOff){
	 available_ = OnOff;
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn  QString address(QString cmd) const
 ///
 /// \brief	(SCRIPTABLE) return the address of visa the device
 ///
 /// \author	Sylvain Martin
 /// \date	19/04/2012
 ///
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 bool SDeviceVisa::available(void) const{
	 return available_;
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn void SDeviceVisa::delay(double i) const 
 ///
 /// \brief	Pause the application for i seconds
 /// 
 /// \param i the number of second. 
 //////////////////////////////////////////////////////////////////////////////////////////////////// 
 void SDeviceVisa::delay(double i) const
 {
	 clock_t start,end;
	 start=clock();

	 while(((end=clock())-start)<=i*CLOCKS_PER_SEC){
		 QCoreApplication::processEvents ();
	 }

 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn  void SDeviceVisa::setTimeOut(double time) 
 ///
 /// \brief	Set the timeout to i second.
 /// 
 /// \param i the number of second. 
 //////////////////////////////////////////////////////////////////////////////////////////////////// 
 void SDeviceVisa::setTimeOut(double time) {
	 if (!available_) return;
	status = viSetAttribute (instr, VI_ATTR_TMO_VALUE, time*1000);
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn void SDeviceVisa::sendLogError( QString log )
 ///
 /// \brief	Emit a signal because of an error
 /// 
 /// \param the description of the error
 //////////////////////////////////////////////////////////////////////////////////////////////////// 
 void SDeviceVisa::sendLogError( QString log )
 {
	 emit logError(QString("WARNING : VISA :An error occurred opening a session to"),SDEVICEVISA_NAME);
 }
