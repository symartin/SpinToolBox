////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SInterface\SInterfaceDaq.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		02/24/2011
///
/// \brief	Declares the SInterfaceDaq class
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

#include "SInterfaceDaq.h"
#include "NIDAQmx/NIDAQmx.h"
#include <QCoreApplication>
#include <time.h>
#include <qdebug.h>
// initialize pointer
SInterfaceDaq* SInterfaceDaq::instance_ = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  SInterfaceDaq::~SInterfaceDaq(void)
///
/// \brief	Constructor
///
/// Initialize the memory and the internal variables.
////////////////////////////////////////////////////////////////////////////////////////////////////
SInterfaceDaq::SInterfaceDaq(void):
			VOut(NULL),	VIn(NULL),prefactor_ (5.0/6.0),autoStart(0),
			timeout(10.0),BufferSizeOut(1000), BufferSizeIn(20),
			Vmax(10.0), Vmin(-10.0), VOldChan0_(0), VOldChan1_(0),
			ChanOut0("/Dev1/ao0"),ChanOut1("/Dev1/ao1"),
			ChanIn1("/Dev1/ai1"), ChanIn2("/Dev1/ai2"),
			running_(false)
{

	// on initialise les deux tableaux
	DataOut = new float64[BufferSizeOut];
	for (int i=0; i< BufferSizeOut ; i++){
		*(DataOut + i) = prefactor_*(float64) i/(BufferSizeOut-1.0);;
	}
		


	DataIn = new double[BufferSizeIn];
	for (int i=0; i< BufferSizeIn ; i++) DataIn[i]=0.0;

	if(DAQmxCreateTask("", &VOut) <0) available_ =false;  //pour initialiser VOut
}

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn  SInterfaceDaq::~SInterfaceDaq(void)
 ///
 /// \brief	destructor
 ///
 ///
 ////////////////////////////////////////////////////////////////////////////////////////////////////
SInterfaceDaq::~SInterfaceDaq(void){
	delete DataOut;
	delete DataIn;
}

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn  SInterfaceDaq* SInterfaceDaq::instance()
 ///
 /// \brief	get the pointer to the singleton class
 ///
 /// \return	null if it fails, else return a pointer to the SInterfaceDaq object. 
 ///
 /// Implement the logic here to instantiate the class for the first time by validating the member
 /// pointer. If member pointer is already pointing to some valid memory it means that the first
 /// object is created and it should not allow for the next instantiation so simply return the
 /// member pointer without calling its ctor. 
 ////////////////////////////////////////////////////////////////////////////////////////////////////

SInterfaceDaq* SInterfaceDaq::instance(){

	if (NULL == instance_) {
		//creating singleton.
		instance_ =  new SInterfaceDaq;

	}else{
		//singleton already created!
		// do nothing
	}

	return instance_;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SInterfaceDaq::sweep(double V,double dV, int channel)
///
/// \brief	(SCRIPTABLE) it does a sweeps between the older constant voltage and a new one  
///
/// \param	V		The goal value in volts   
/// \param	dV		The "speed" of the sweep
/// \param	channel	The channel (0 or 1). 
/// 
/// \so running()
/// \so finished()
/// \so Prefactor()
/// \so SetPrefactor
///
/// \remark for historical reason a pre-factor is applied on the V value for be compatible with different Kepcos.
///
/// it emits the finished() signal when the task is finished
/// it does nothing if a task is already running
/// it does noting if the channel is not correct
/// it does noting if the command is greater than the card limit
////////////////////////////////////////////////////////////////////////////////////////////////////

void SInterfaceDaq::sweep(double V,double dV, int channel){

	running_ = true;
	
	double t;
	double incrementV;
	double tpsSweep;
	float64 rate;  ///< the rate of the output
	double Vo;

	double Vold; ///<
	QString ChanOut;

	switch (channel){
		case 0:
			ChanOut = ChanOut0;
			Vold = VOldChan0_;
			VOldChan0_ = V;
			break;
		case 1:
			ChanOut = ChanOut1;
			Vold = VOldChan1_;
			VOldChan1_ = V;
			break;
		default:
			return;
	}
	if((fabs(V) > Vmax) || (V == Vold)) {
		running_ = false;
		emit finished();
		return; //TODO metre une erreur ici
	}



	tpsSweep = fabs((V-Vold)/dV);		///< temps entre consigne et ancienne valeur
	rate = (double)BufferSizeOut/tpsSweep;		///<vittese de de lecture de la consigne par la carte DAQ	
	incrementV = (V-Vold)/(BufferSizeOut - 1);	///< diference en tension entre deux points de consigne 

	// pour pouvoir modifier la frequence de generation Rate, il faut recreer la Task
	if(DAQmxClearTask(VOut) <0) available_ = false;
	DAQmxCreateTask("", &VOut);


	//Add an analog output channel to the task
	DAQmxCreateAOVoltageChan (VOut,
		ChanOut.toAscii().data(), "", 
		Vmin, Vmax,	DAQmx_Val_Volts, "");

	//To configure the timing parameters 
	DAQmxCfgSampClkTiming(VOut,
		"OnboardClock",	rate, DAQmx_Val_Rising,
		DAQmx_Val_FiniteSamps, BufferSizeOut);

	// on fait un tableau ou l'on stoque la consigne que l'on va envoyer
	for ( int i=0 ; i<BufferSizeOut ; i++){
		

		Vo= prefactor_*(Vold + i*incrementV);
		t = i*tpsSweep/((double)BufferSizeOut); 

		if(t<tpsSweep) DataOut[i] = (float64) prefactor_*( Vold + i*incrementV );
		else DataOut[i] = (float64) prefactor_*V;


		if(fabs(DataOut[i]) > Vmax)	{ //TODO il faut gerer corectement les dépacement !!!
			//sécurité pour rester sous le seuil de 10V de la daq
			DataOut[i] = prefactor_*Vmax*0.99*sgn(DataOut[i]);
			qDebug() << "attention seuillage de tension DAQ!\n";
		}
	}

	
	DAQmxWriteAnalogF64(VOut,BufferSizeOut,autoStart,timeout,DAQmx_Val_GroupByChannel,DataOut ,&SamplesWritten, 0);
	DAQmxStartTask (VOut);
	
	delay(tpsSweep);// milliseconds in seconds
	DAQmxClearTask(VOut);  
	emit finished();

	running_ = false;

	return ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	inline double SInterfaceDaq::fabs(double num)
///
/// \brief	compute the absolute value of num. 
///
/// \param	num	a number. 
///
/// \return	the absolute value of num. 
////////////////////////////////////////////////////////////////////////////////////////////////////

inline double SInterfaceDaq::fabs(double num){
	
	if(num<0){
		return -num;
	}else{
		return num;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	inline double SInterfaceDaq::sgn(double number)
///
/// \brief	return the sign of the number. 
///
/// \param	number	a number. 
///
/// \return	-1 if number is negative an +1 if it is positive. 
/// \remark 0 is positive		
////////////////////////////////////////////////////////////////////////////////////////////////////

inline double SInterfaceDaq::sgn(double number){	
	if(number <0) return -1;
	else return 1;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	inline double SInterfaceDaq::delay(double i)
///
/// \brief	(SCRIPTABLE) do a break during i seconds 
///
/// \param	number	a number of seconds. 
///
/// let the rest of the application process normally (e.g. the GUIs)		
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SInterfaceDaq::delay(double i)    
{
    clock_t start,end;
    start=clock();

    while(((end=clock())-start)<=i*CLOCKS_PER_SEC){
		QCoreApplication::processEvents ();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE bool SInterfaceDaq::available(void)
///
/// \brief	(SCRIPTABLE) Gets if the DAQ is available. 
///
/// \return	true if it available, false if it not.
/// \remark It does not indicate if a task is running.
/// \so SInterfaceDaq::running()
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE bool SInterfaceDaq::available(void){
	//on verifie que la carte est tjs non disponible
	if(!running_ && DAQmxClearTask(VOut) <0) available_ = true;
	return(available_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE bool SInterfaceDaq::running()
///
/// \brief	(SCRIPTABLE) Gets if the DAQ is running a task. 
///
/// \return	true if it is running a task, false if it not.
/// \remark It does not indicate if a task is available.
/// \so SInterfaceDaq::available(void)
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE bool SInterfaceDaq::running()
{
	return running_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE double SInterfaceDaq::vOld(int channel)
///
/// \brief	(SCRIPTABLE) Gets the final value of the last sweep command
///
/// \return	a voltage in volt
/// \remark It does not indicate if a task is available.
/// \so SInterfaceDaq::sweep(double V,double dV, int channel)
///
/// if channel is not 0 or 1 return 0
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE double SInterfaceDaq::vOld( int channel /*= 0*/ )
{

	switch (channel){
	case 0:
		return VOldChan0_;
	case 1:
		return VOldChan1_;
	default:
		return 0;
	}



}

