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
	const    sampleName		= "#4Selma";
	const    junctionLineName	= "d";
	const    junctionColName	= "IV";
	const    junctionTypeName    = "2D";
	const    cmt			= "avec bouclier droit, recherche des langues d'Arnold";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= "20120301";		
	const    studyNumber		= "m07p6dBm";
						
	const    name			= "%DATE%_" + studyNumber
							+"_%ImA_%PdBm_%FMHz";
	
	const    folder			= serieName + "\\"
						+ studyName + "\\"
						+ sampleName + "\\"
						+ junctionName + "\\"
						+ studyNumber+ "\\";
						    
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

	var dataMaxAmp = new SData2D;
	
	var cmt2;
	cmt2   =  "amplitude du maximum de signal par rapport à la fréquence";
	cmt2 += "de la source micro onde.";
	cmt2 += "Realisé avec le PSAE4440A";
	
	dataMaxAmp.addComment(cmt2);	
	dataMaxAmp.setColName("MwFreq", "SigAmp");
	dataMaxAmp.setColUnit("GHz","nV²/Hz");
	
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
	PSGE8257D.setFrequence(mwfreq/1000); // setFrequence en GHz
	PSGE8257D.activate(true);
	
	// setup the  spectrum analyser  ***************************************
	var span = 50;
	var rbw = PSAE4440A.checkRbw(span/(1000*8001));
	
	PSAE4440A.setFreqStart((f0-span)/1000);
	PSAE4440A.setFreqStop((f0+span)/1000);
	PSAE4440A.setNbAverage(0);
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
	dataMaxAmp.append(mwfreq/1000,2*ptMax[1]*ptMax[1]/(rbw*1e9)*1e18);
	data.saveFile(path + "/" +BASE_NAME + myName + "." + EXT);
	datatmp.saveFile(path + "/" + "Revised_" + BASE_NAME + myName  + "." + EXT);
}

	
	var f0 = FreqNat; //MHz

for (var mwfreq=2*f0-deltaf0; mwfreq<= 2*f0+deltaf0; mwfreq= mwfreq+pasf){


	 Spectre(mwpwr, mwfreq,f0 );
	 print("Pmw = "  + mwpwr + " dBm \tFmw = " 
			+ parseFloat(mwfreq).toFixed(2) +" MHz\t" 
			+ parseFloat((mwfreq-2*f0-deltaf0)/(2*deltaf0)*100+100).toFixed(2) + "%");
	
}
	dataMaxFreq.saveFile(path + "/" + studyName +"_" + studyNumber + "_FreqMax" 
					+"_Pmw" + parseFloat(mwpwr).toFixed(3) + ".dat");

	dataMaxAmp.saveFile(path + "/" + studyName + "_" + studyNumber + "_AmpMax" 
					+"_Pmw" + parseFloat(mwpwr).toFixed(3) + ".dat")

	PSGE8257D.activate(false);
	var plot = new SPlot2D();
	plot.setData(dataMaxFreq);
	plot.show();

	var plot2 = new SPlot2D();
	plot2.setData(dataMaxAmp);
	plot2.show();

	print("Fini !!");

