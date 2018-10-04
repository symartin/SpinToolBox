/*******************************************************************************
* Title : 	intermodulation measurment .js
* Autor :	Sylvain Martin
* Brief : 	Sweep Low frequency RF for intermodulation measurment 
* Version :	1.2.0
*********************************************************************************/	
/*
change log :
-------------
	*/
/*********************************************************************************
*                                                 CONSTANTE
**********************************************************************************/
	const    AP 		= 	-6	; //Volt command of the Kepco
	const    P 			= 	6	; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
	const    MAX_I 		= 	0.022	; //A
	const    MAX_V 		= 	0.500	; //V
	const    BASE_NAME	= 	""; //prefix of the name
	const    EXT	 	= 	"spectre.stb"; //extention
	const    MILI		=	1000	;
	const    DEBUG		=	1	;
	const    CHAN		=	0	;
	const    FIELD_0_END 	=  	1	;
	const    DATA_PATH    =      "D:\\Data"; // path of the data	
/*********************************************************************************
*                                                 PARAMETERS
**********************************************************************************/	

	
	const    technician		= "Sylvain MARTIN"	
	const    serieName		= "CCP.BTF5HJ"	
	const    sampleName		= "#6";
	const    junctionLineName	= "a";
	const    junctionColName	= "V";
	const    junctionTypeName    = "1A";
	const    cmt			= "avec bouclier droit, ss ampli," 
		    cmt			= cmt+"avec power-spliter 3vs1(-6dB)";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= 	"20130204";
	const    runName			= 	"";
	
	var    name			= "%DATE%_" + runName
							+"_%ImA_%PdBm_%FMHz";
	

	
	var    folder			= serieName + "\\"
						+ studyName + "\\"
						+ sampleName + "\\"
						+ junctionName + "\\"
						+ runName+ "\\";
						    
	var    path			= DATA_PATH + "\\" + folder;
	
///////////////////////////////////////////////////////////////////////////////////////
//				variables exterieures au script
////////////////////////////////////////////////////////////////////////////////////////

	var 		field 			= 	-0.90;
	const    	current 	        =	-20.0	; //mA
	const 	freqNat		= 	449; // MHz
	const 	avg			= 	10;
	
	ModMw = RSSMA100A; // APSIN20G;  PSGE8257D; RSSMA100A*/
	
	
///////////////////////////////////////////////////////////////////////////////////////
//					fonctions outils
////////////////////////////////////////////////////////////////////////////////////////
function FixFloatToStr(num, presZero, postZero){
	
	var intergerPart = "";
	var sign = "";
	if (num< 0) sign = "-";
	
	
	while(Math.abs(num) < Math.pow(10,presZero-1)){
		presZero--;
		intergerPart += "0";		
	}
	
	return sign + intergerPart + Math.abs(num).toFixed(postZero);	
}

	
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
	data.setMetaData("NumberAverage"	, avg);		
	data.setMetaData("SaAttenuation"	, PSAE4440A.attenuation());	
	data.setMetaData("SaNbPoints"		, PSAE4440A.nbPoints());	
	
	
	data.setMetaData("FreqNaturel"		, (freqNat/1000).toFixed(3) );
	data.setMetaData("FreqNatUnit"		, "GHz");	
	data.setMetaData("IUnit"			, "mA");	
	data.setMetaData("runName"		, runName);	
	data.setMetaData("sampleName"		, sampleName);	
	data.setMetaData("junctionLineName"	, junctionLineName);	
	data.setMetaData("junctionColName"	, junctionColName);
	data.setMetaData("junctionTypeName"	, junctionTypeName);	
	data.setMetaData("junctionName"	, junctionName);	
	data.setMetaData("serieName"		, serieName);		
	data.setMetaData("field"			, field);	
	data.setMetaData("fieldUnit"		, "Vc");	
	data.setMetaData("technician"		, technician);	

	var VI = K2400.readVI(); // on stock pour le metre en entete
	var R = VI[0]/VI[1];

	
	// put some metadata ****************************************
	data.setMetaData("V"				, VI[0]*MILI);	
	data.setMetaData("VUnit"			, "mV");	
	data.setMetaData("I"				, VI[1]*MILI);	
	data.setMetaData("IUnit"			, "mI");	
	data.setMetaData("R"				, R);	
	data.setMetaData("RUnit"			, "Ohm");	
	
	data.setMetaData("date"	, nowDate("dd/MM/yyyy"));
	data.setMetaData("time"	, nowTime("hh:mm:ss"));
	

}

///////////////////////////////////////////////////////////////////////////////////////
//				 function Spectrum
////////////////////////////////////////////////////////////////////////////////////////
function Spectre(mwpwr, mwfreq,f0 ){

	var    folder = serieName + "\\"+ studyName + "\\"
			+ sampleName + "\\"	+ junctionName + "\\"
			+ runName+ "\\";
						    
	path	= DATA_PATH + "\\" + folder;
	
	// setup the  MW generator ***************************************
	ModMw.setPowerLimit(5);
	ModMw.setPower(mwpwr);
	ModMw.setFrequency(mwfreq/1000); // setFrequence en GHz
	ModMw.activate(true);
	
	// setup the  spectrum analyser  ***************************************
	var span =50;
	var rbw = PSAE4440A.checkRbw(2*span/(1000*PSAE4440A.nbPoints()));
	
	PSAE4440A.setFreqStart((f0-span)/1000);
	PSAE4440A.setFreqStop((f0+span)/1000);
	PSAE4440A.setNbAverage(avg);
	PSAE4440A.setRefLevel(-65);
	
	//On prend le spectre ******************************************
	delay(0.2);
	var data = new SData2D;
	data = PSAE4440A.ReadSpectrum();
	delay(0.2);
	data.addComment(cmt);
	
	metadata(data, rbw, mwpwr, mwfreq);
	
	
	var    name			= "%DATE%_" + runName
							+"_%ImA_%PdBm_%FMHz";
							
							
	// make a cool name **************************************************		
	var myName = "";
	myName = name;
	myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
	myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
	myName = myName.replace("%I",	FixFloatToStr(current,2,2)) ;
	myName = myName.replace("%F",	FixFloatToStr(mwfreq ,2,2)) ;
	myName = myName.replace("%P",	FixFloatToStr(mwpwr,2,2)) ;
		
	
	// on fait un fichier freq Max p/r freq MW ******************************************
	data.saveFile(path + "/" +BASE_NAME + myName + "." + EXT);

	//on afiche le resultat
	/*var plot2 = new SPlot2D();
	plot2.setData(data);
	plot2.show();*/
}

///////////////////////////////////////////////////////////////////////////////////////
//				Sweep en fréquence a puissance variable
////////////////////////////////////////////////////////////////////////////////////////	
function sweepFreq(start, stop, pwr, pas){
	

	
	
	for( var mwfreq = start;  mwfreq <= stop;  mwfreq=mwfreq+pas){
		// on prend un spectre
		Spectre(pwr, mwfreq, freqNat );
		
		// on écrit l'avencement
		print("Pmw = "  + pwr + " dBm \tFmw = " 
				+ parseFloat(mwfreq).toFixed(2) +" MHz\t" 
				+ parseFloat((mwfreq)/(span)*100).toFixed(2) + "%");
		 

	}
	
	print("Fini !!");

}

///////////////////////////////////////////////////////////////////////////////////////
//				Sweep en fréquence a puissance variable
////////////////////////////////////////////////////////////////////////////////////////	
function sweepPwr(mwfreq,  PwrTab){
	
	for( var i = 0;  i < PwrTab.length ;  i++){
		// on prend un spectre
		Spectre(PwrTab[i], mwfreq, freqNat );
		
		// on écrit l'avencement
		print("Pmw = "  + PwrTab[i] + " dBm \tFmw = " 
				+ parseFloat(mwfreq).toFixed(2) +" MHz\t" 
				+ parseFloat(i/PwrTab.length*100).toFixed(2) + "%");
		 

	}
	
	print("Fini !!");

}

///////////////////////////////////////////////////////////////////////////////////////
//						 Main
////////////////////////////////////////////////////////////////////////////////////////

	



/*

var Pwr = new Array(-30,-27.0,-25.0,-23.0,-20.0,-18.2,-17.0,-16.0,-15.2,-14.6,
				-14.0,-13.5,-13.0,-12.6,-12.2,-11.9,-11.5,-11.2,-11.0,
				-10.7,-10.5,-10.2,-10.0,-9.8,-9.6,-9.4,-9.2,-9.0,-8.9,
				-8.7,-8.5,-8.4,-8.2,-8.1,-8.0,-7.8,-7.7,-7.6,-7.4,-7.3,
				-7.2,-7.1,-7.0);
*/
ModMw.setPowerLimit(2);

/*var Pwr = new Array(-20.00,-16.02,-13.01,-11.25,-10.00,-9.03,-8.24,-7.57,-6.99,-6.48,
			-6.02,-5.61,-5.23,-4.88,-4.56,-4.26,-3.98,-3.72,-3.47,-3.23,-3.01,
			-2.80,-2.60,-2.40,-2.22,-2.04,-1.87,-1.71,-1.55,-1.40,-1.25,-1.11,-0.97,
			-0.84,-0.71,-0.58,-0.46,-0.34,-0.22,-0.11,0.00);
			*/
			
			
var Pwr = new Array(-40.00,-38.00,-36.00,-34.00,-32.00,-30.00,-28.00,-26.00,
				-24.00,-22.00,-20.00,-16.02,-13.01,-11.25,-10.00);
/////////////////////////////////////////////////////////////////////////
	runName		= 	"1832-TestMaxSynchro";							
	sweepPwr(freqNat*2,Pwr);

/////////////////////////////////////////////////////////////////////////
  /*  runName		= 	"PwrVarFreq15Mz";
	

	
sweepPwr(15,Pwr);

/////////////////////////////////////////////////////////////////////////
    runName		= 	"PwrVarFreq25Mz";
	

	
sweepPwr(25,Pwr);

/////////////////////////////////////////////////////////////////////////
    runName		= 	"PwrVarFreq40Mz";

	
sweepPwr(40,Pwr);
*/
/////////////////////////////////////////////////////////////////////////
	runName			= 	nowTime("hhmm") + "_SyncVarFreqPwr-12dBm";
	sweepFreq(2, 15, -15, 0.25);
	sweepFreq(15.5, 40, -15, 0.5);
/////////////////////////////////////////////////////////////////////////
/*	runName		= 	"ModFreqVarPwr-15dBm";
	sweepFreq(2, 15, -15, 0.25);
	sweepFreq(15.5, 40, -15, 0.5);
*/
/////////////////////////////////////////////////////////////////////////	
	/*runName		= 	"ModFreqVarPwr-08dBm";
	sweepFreq(2, 15, -8, 0.25);
	sweepFreq(15.5, 40, -8, 0.5);*/
	
/////////////////////////////////////////////////////////////////////////
	/*runName		= 	"ModFreqVarPwr-10dBm";
	sweepFreq(2, 15, -10, 0.25);
	sweepFreq(15.5, 40, -10, 0.5);*/

/////////////////////////////////////////////////////////////////////////


PSGE8257D.activate(false);
//Spectre(mwpwr, 0.5, freqNat );