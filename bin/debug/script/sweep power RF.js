/*******************************************************************************
* Title : 	sweep RF.js
* Autor :	Sylvain Martin
* Brief : 	fait un sweep du signal RF de la MW et regarde ce qui ce passe avec le
*		l'annalyseur de spectre a f0
* Version :	1.0.5
*********************************************************************************/	
/*
change log :
-------------
	1.0.5 : add a system for delete the RF signal on the spectre
*/

include(app.path+"/Script/const.js");
include(app.path+"/Script/tools.js");


/*********************************************************************************
*                                                 PARAMETERS
**********************************************************************************/	

	
	const    technician		= "Sylvain MARTIN"	
	const    serieName		= "CCP.BTF5HJ"	

						

						    
	const    path			= DATA_PATH + "\\" + folder;
	
///////////////////////////////////////////////////////////////////////////////////////
//				variables exterieures au script
////////////////////////////////////////////////////////////////////////////////////////

	var 		field 			= 	0.95;
	const    	current 	        =	-20.0	; //mA
	const 	FreqNat		= 	436; // MHz
	var 		mwpwr 		= 	-7.6; // puissance de la MW en dBm
	var		deltaf0		=	32.0; //MHz
	var		pasf			= 	0.8; //MHz



///////////////////////////////////////////////////////////////////////////////////////
//		   on fait 2 fichiers avec les coordonees du maximum		 
////////////////////////////////////////////////////////////////////////////////////////
	var dataMaxFreq = new SData2D;
	
	var cmt2;
	cmt2   =  "Frequence du maximum de signal par rapport à la fréquence";
	cmt2 += "de la source micro onde.";
	cmt2 += "Realisé avec le PSAE4440A";
	
	dataMaxFreq.addComment(cmt2);	
	dataMaxFreq.setColName("MwFreq", "SigFreq");
	dataMaxFreq.setColUnit("GHz","GHz");

	var dataSigAmpVsMwAmp = new SData2D;
	
	var cmt2;
	cmt2   =  "amplitude du maximum de signal par rapport à l'amplitude";
	cmt2 += "de la source micro onde.";
	cmt2 += "Realisé avec le PSAE4440A";
	
	dataSigAmpVsMwAmp.addComment(cmt2);	
	dataSigAmpVsMwAmp.setColName("MwAmp", "SigAmp");
	dataSigAmpVsMwAmp.setColUnit("dBm","V");
	
	var dataMaxAmp = new SData2D;
	
	var cmt2;
	cmt2   =  "amplitude du maximum de signal par rapport à la fréquence";
	cmt2 += "de la source micro onde.";
	cmt2 += "Realisé avec le PSAE4440A";
	
	dataMaxAmp.addComment(cmt2);	
	dataMaxAmp.setColName("MwFreq", "SigAmp");
	dataMaxAmp.setColUnit("GHz","V");
	
///////////////////////////////////////////////////////////////////////////////////////
//		    ad some metadata to the SData2D object		 
////////////////////////////////////////////////////////////////////////////////////////
function metadata(data, rbw, mwpwr, mwfreq){
	

	data.setMetaData("RBW"			, rbw );	
	data.setMetaData("RBWUnit"		, "GHz");	
	data.setMetaData("MwPower"		, mwpwr);	
	data.setMetaData("MwPowerUnit"		, "dBm");	
	data.setMetaData("MwFreq"			, mwfreq);	
	data.setMetaData("MwFreqUnit"		, "MHz");	
	
	data.setMetaData("FreqNaturel"		, (FreqNat/1000).toFixed(3) );
	data.setMetaData("FreqNatUnit"		, "GHz");	
	data.setMetaData("I"				, current.toFixed(3) );	
	data.setMetaData("IUnit"			, "mA");	
	data.setMetaData("studyName"		, studyName);	
	data.setMetaData("sampleName"		, sampleName);	
	data.setMetaData("junctionLineName"	, junctionLineName);	
	data.setMetaData("junctionColName"	, junctionColName);
	data.setMetaData("junctionTypeName"	, junctionTypeName);	
	data.setMetaData("junctionName"	, junctionName);	
	data.setMetaData("serieName"		, serieName);		
	data.setMetaData("field"			, field);	
	data.setMetaData("fieldUnit"		, "Vc");	
	data.setMetaData("technician"		, technician);	

	
	data.setMetaData("date"	, nowDate("dd/MM/yyyy"));
	data.setMetaData("time"	, nowTime("hh:mm:ss"));
	
}



///////////////////////////////////////////////////////////////////////////////////////
//				 function Spectrum
////////////////////////////////////////////////////////////////////////////////////////
function Spectre(mwpwr, mwfreq,f0 ){
	
	// setup the  MW generator ***************************************
	PSGE8257D.setPowerLimit(0);
	PSGE8257D.setPower(mwpwr);
	PSGE8257D.setFrequency(mwfreq/1000); // setFrequence en GHz
	PSGE8257D.activate(true);
	
	// setup the  spectrum analyser  ***************************************
	var span = 100;
	var rbw = PSAE4440A.checkRbw(span/(1000*8001));
	
	PSAE4440A.setFreqStart((f0-span)/1000);
	PSAE4440A.setFreqStop((f0+span)/1000);
	PSAE4440A.setNbAverage(avg);
	PSAE4440A.setRefLevel(-70);

	
	//On prend le spectre ******************************************
	delay(5);
	var data = new SData2D;
	data = PSAE4440A.ReadSpectrum();
	delay(1);
	data.addComment(cmt);
	
	// Recheche du max ********************************************
        var datatmp = new SData2D();
	datatmp.setData(data);
	// on eleve le signale de la MW, sinon c'est tjs elle le max
	if ( mwfreq<=f0+span && mwfreq >=f0-span ){
		for (var i=0; i< datatmp.count(); i++){

			if( datatmp.x(i)> (mwfreq - 0.15)/1000 && 
				datatmp.x(i)< (mwfreq + 0.15)/1000){
				datatmp.sety(i,0);
			}
			
		}
	}
	datatmp.slideAverage();
	var ptMax = datatmp.max();

	// put some metadata ****************************************
	data.setMetaData("MaxAmp"			, ptMax[1]);
	data.setMetaData("MaxAmpUnit"		, "V");	
	data.setMetaData("MaxFreq"		, ptMax[0]);	
	data.setMetaData("MaxFreqUnit"		, "GHz");
	
	metadata(data, rbw, mwpwr, mwfreq);

	datatmp.setMetaData("MaxAmp"			, ptMax[1]);
	datatmp.setMetaData("MaxAmpUnit"		, "V");	
	datatmp.setMetaData("MaxFreq"			, ptMax[0]);	
	datatmp.setMetaData("MaxFreqUnit"		, "GHz");
	
	metadata(datatmp, rbw, mwpwr, mwfreq);
	
	// make a cool name **************************************************		
	var myName = "";
	myName = name;
	myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
	myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
	myName = myName.replace("%I",	FixFloatToStr(current,2,2)) ;
	myName = myName.replace("%F",	FixFloatToStr(mwfreq ,2,2)) ;
	myName = myName.replace("%P",	FixFloatToStr(mwpwr,2,2)) ;
		
	
	// on fait un fichier freq Max p/r freq MW ******************************************
	dataMaxFreq.append(mwfreq/1000,ptMax[0]);
	dataMaxAmp.append(mwfreq/1000,ptMax[1]);
	
	dataSigAmpVsMwAmp.append(mwpwr,ptMax[1]);
	
	data.saveFile(path + "/" +BASE_NAME + myName + "." + EXT);
	datatmp.saveFile(path + "/" + "Revised_" + BASE_NAME + myName  + "." + EXT);
}

	
////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////
function SweepPwr( MwPwrTab, MwFreq, f0){

	for( var i = 0;  i < MwPwrTab.length ;  i++){
			
		// on prend un spectre
		Spectre(MwPwrTab[i], MwFreq,f0 )
			
		// on écrit l'avencement
		print("Pmw = "  + MwPwrTab[i] + " dBm\t" 
					+ parseFloat(i/MwPwrTab.length*100).toFixed(2) + "%");
			 
	}
		
	print("Fini !!");
}

function SweepFreq( MwPwr, MwFreq, DeltaF, PasF, f0){
	
	for (var Freq=2*f0-DeltaF; MwFreq<= 2*f0+DeltaF; Freq= Freq+PasF){

		 Spectre(MwPwr, Freq,f0 );
		 print("Pmw = "  + mwpwr + " dBm \tFmw = " 
				+ parseFloat(mwfreq).toFixed(2) +" MHz\t" 
				+ parseFloat((mwfreq-2*f0-deltaf0)/(2*deltaf0)*100+100).toFixed(2) + "%");
		
	}


}



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                     Main
///////////////////////////////////////////////////////////////////////////////////////////////////
const    sampleName		= "#4alpha";
const    junctionLineName	= "b";
const    junctionColName	= "II";
const    junctionTypeName    = "2D";
const    cmt			= "avec bouclier droit, ss ampli, " 
	    cmt			= cmt+"avec power-spliter 3vs1 (-5.6dB)";
		    
const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;

const    studyName		= "20120502";		
const    studyNumber		= "SeuilLock2";
						
const    name			= "%DATE%_" + studyNumber
							+"_%ImA_%PBm_%FHz";
	
const    folder	= serieName + "\\" + studyName + "\\"
			+ sampleName + "\\" + junctionName + "\\"
			+ studyNumber+ "\\";
			
			
const field 			= 	-1.00;
const current 	        =	-19.0	; //mA
const freqNat		= 	424; // MHz
const avg			= 	0; // number of average 

var ModMwPwr = -12; // le 5.6 a cause du
var MwFreq = 2*freqNat; //MHz
var MwPwrTab = new Array(-22.6,-22.2,-21.9,-21.5,-21.2,-21.0,-20.7,-20.5,-20.2,
					-20.0,-19.8,-19.6,-19.4,-19.2,-19.0,-18.9,-18.7,-18.5,
					-18.4,-18.2,-18.1,-18.0,-17.8,-17.7,-17.6,-17.4,-17.3,
					-17.2,-17.1,-17.0,-16.9,-16.8,-16.7,-16.6,-16.5,-16.4,
					-16.3,-16.2,-16.1,-16.0);
					
SweepPwr( MwPwrTab, MwFreq, freqNat)

////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////
	dataMaxFreq.saveFile(path + "/" + studyName +"_" + studyNumber + "_FreqMax" 
					+"_Pmw" + parseFloat(mwpwr).toFixed(3) + ".dat");

	dataMaxAmp.saveFile(path + "/" + studyName + "_" + studyNumber + "_AmpMax" 
					+"_Pmw" + parseFloat(mwpwr).toFixed(3) + ".dat")


	dataSigAmpVsMwAmp.saveFile(path + "/" + studyName + "_" + studyNumber + "_SigAmpVsMwAmp" 
					+"_Pmw" + parseFloat(mwpwr).toFixed(3) + ".dat")



	PSGE8257D.activate(false);
	var plot = new SPlot2D();
	plot.setData(dataMaxFreq);
	plot.show();

	var plot = new SPlot2D();
	plot.setData(dataSigAmpVsMwAmp);
	plot.show();
	
	var plot2 = new SPlot2D();
	plot2.setData(dataMaxAmp);
	plot2.show();

	print("Fini !!");

