/*******************************************************************************
* Title : 	Caracterisation rf.js
* Autor :	Sylvain Martin
* Brief : 	fait un sweep de la source RF et mesure le signale resulatant avec 
*		l'analyseur de spectre. Permet de fair la caracterisation des composants
* Version :	1.0
*********************************************************************************/	

/*********************************************************************************
*                                                 CONSTANTE
**********************************************************************************/
	const    AP 		= 	-6	; //Volt command of the Kepco
	const    P 			= 	6	; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
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
	const    cmt			= "test du power spliter 1 vs 2 : entré 2 sortie 3" ;   					


	var nbAverage = 0;
	ModMw = PSGE8257D; // APSIN20G;  PSGE8257D;*/
	
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
function metadata(data){
	
	data.setMetaData("RBW"			, PSAE4440A.rbw() );	
	data.setMetaData("RBWUnit"		, "GHz");	
	data.setMetaData("SaNumberAverage"	, nbAverage);		
	data.setMetaData("SaAttenuation"	, PSAE4440A.attenuation());	
	data.setMetaData("SaNbPoints"		, PSAE4440A.nbPoints());	

	data.setMetaData("studyName"		, studyName);	
	data.setMetaData("serieName"		, serieName);		
	data.setMetaData("technician"		, technician);	


	data.setMetaData("date"	, nowDate("dd/MM/yyyy"));
	data.setMetaData("time"	, nowTime("hh:mm:ss"));
	
}

///////////////////////////////////////////////////////////////////////////////////////
//				 function Spectrum
////////////////////////////////////////////////////////////////////////////////////////
function Spectre(Fmw, Pmw, FmaxVsFmw, FmaxVsPmw,PmaxVsFmw,PmaxVsPmw){
	
	// setup the  spectrum analyser  ***************************************
	var span = 100;
	PSAE4440A.setNbPoints(4000);
	var rbw = PSAE4440A.checkRbw(span/(1000*PSAE4440A.nbPoints()));
	PSAE4440A.setLogDisplay (true);
	
	if(Fmw-span<0.1){
		PSAE4440A.setFreqStart((0.1)/1000);
		PSAE4440A.setFreqStop((Fmw+span-(Fmw-span)+0.1)/1000);
	}else{
		PSAE4440A.setFreqStart((Fmw-span)/1000);
		PSAE4440A.setFreqStop((Fmw+span)/1000);
	}
	PSAE4440A.setNbAverage(nbAverage);
	PSAE4440A.setRefLevel(-10);
	
	
	// setup the  MW generator ***************************************
	ModMw.setPowerLimit(5);
	ModMw.setPower(Pmw);
	ModMw.setFrequency(Fmw/1000); // setFrequence en GHz
	ModMw.activate(true);
	
	
	//On prend le spectre ******************************************
	delay(0.2);
	var data = new SData2D;
	data = PSAE4440A.ReadSpectrum();
	delay(0.2);
	
	// on rempli les metadata *******************************************
	data.addComment(cmt);
	metadata(data);
	

	// make a cool name **************************************************		
	var myName = "";
	myName = name;
	myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
	myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
	myName = myName.replace("%P",	FixFloatToStr(Pmw,2,2)) ;
	myName = myName.replace("%F",	FixFloatToStr(Fmw,2,2)) ;
	
	// on fait un fichier freq Max p/r freq MW ******************************************
	data.saveFile(path + "/" + "spectres" + "/" + myName + "." + EXT);
	
	// Recheche du max ********************************************
	var ptMax = data.max();
	
	// on fait un fichier freq Max p/r freq MW ******************************************
	FmaxVsFmw.append(Fmw,ptMax[0]*1000);
	FmaxVsPmw.append(Pmw,ptMax[0]*1000);
	PmaxVsFmw.append(Fmw,ptMax[1]);
	PmaxVsPmw.append(Pmw,ptMax[1]);
	
	delete data;

}




///////////////////////////////////////////////////////////////////////////////////////
//		   			fonction de sweep	 
////////////////////////////////////////////////////////////////////////////////////////
function SweepFmw(FStart, FStop, FStep, Pmw){
	
	// creation du fichier Fmax(Fmw)
	var FmaxVsFmw = new SData2D;
	FmaxVsFmw.addComment("Frequence du maximum en fonction de la fréquence de la MW");	
	FmaxVsFmw.setColName("Fmw", "Fmax");
	FmaxVsFmw.setColUnit("MHz","MHz");
	metadata(FmaxVsFmw);
	
	// creation du fichier Fmax(Fmw)
	var FmaxVsPmw = new SData2D;
	FmaxVsPmw.addComment("Frequence du maximum en fonction de la puissance de la MW");	
	FmaxVsPmw.setColName("Pmw", "Fmax");
	FmaxVsPmw.setColUnit("dBm","MHz");
	metadata(FmaxVsPmw);
	
	// creation du fichier Fmax(Fmw)
	var PmaxVsFmw = new SData2D;
	PmaxVsFmw.addComment("Puissace du maximum en fonction de la fréquence de la MW");	
	PmaxVsFmw.setColName("Fmw", "Pmax");
	PmaxVsFmw.setColUnit("MHz","dBm");
	metadata(PmaxVsFmw);

	// creation du fichier Fmax(Fmw)
	var PmaxVsPmw = new SData2D;
	PmaxVsPmw.addComment("Puissance du maximum en fonction de la puissance de la MW");	
	PmaxVsPmw.setColName("Pmw", "Pmax");
	PmaxVsPmw.setColUnit("dBm","dBm");
	metadata(PmaxVsPmw);



	// Boucle de mesure
	for(var F=FStart;
		(FStart <  FStop  && F<=FStop) || (FStart >=  FStop  && F >= FStop) ; 
			F= F + FStep){
				Spectre(F, Pmw, FmaxVsFmw, FmaxVsPmw, PmaxVsFmw, PmaxVsPmw);
	}
	
	
	// sauvgarde
	FmaxVsFmw.saveFile(path + "/" + studyName +"_" + runName + "_FmaxVsFmw"	+ ".dat");
	FmaxVsPmw.saveFile(path + "/" + studyName + "_" + runName + "_FmaxVsPmw" + ".dat");
	PmaxVsFmw.saveFile(path + "/" + studyName + "_" + runName + "_PmaxVsFmw" + ".dat");	
	PmaxVsPmw.saveFile(path + "/" + studyName + "_" + runName + "_PmaxVsPmw" + ".dat");	

	var plotFmaxVsFmw = new SPlot2D();
	plotFmaxVsFmw.setData(FmaxVsFmw);
	plotFmaxVsFmw.setTitle("Frequence max = fct(Frequence MW)" );
	plotFmaxVsFmw.setLabels( "Frequence (MHz)", "Frequence (MHz)") 	
	plotFmaxVsFmw.show();

	var plotFmaxVsPmw = new SPlot2D();
	plotFmaxVsPmw.setData(FmaxVsPmw);
	plotFmaxVsPmw.setTitle("Frequence max = fct(Puissance MW)" );
	plotFmaxVsPmw.setLabels ( "Puissance (dBm)", "Frequence (MHz)") 	
	plotFmaxVsPmw.show();

	var plotPmaxVsFmw = new SPlot2D();
	plotPmaxVsFmw.setData(PmaxVsFmw);
	plotPmaxVsFmw.setTitle("Puissance max = fct(Frequence MW)" );
	plotPmaxVsFmw.setLabels( "Puissance (MHz)", "Frequence (MHz)") 
	plotPmaxVsFmw.show();
	
	var plotPmaxVsPmw = new SPlot2D();
	plotPmaxVsPmw.setData(PmaxVsPmw);
	plotPmaxVsPmw.setTitle("Puissance max= fct(Puissance MW)");
	plotPmaxVsPmw.setLabels 	( "Puissance (dBm)",	"Puissance (dBm)") 	
	plotPmaxVsPmw.show();
	
	
	delete FmaxVsFmw;
	delete FmaxVsPmw;
	delete PmaxVsFmw;
	delete PmaxVsPmw;
}



function SweepPmw(PStart, PStop, PStep, Fmw){
	
	// creation du fichier Fmax(Fmw)
	var FmaxVsFmw = new SData2D;
	FmaxVsFmw.addComment("Frequence du maximum en fonction de la fréquence de la MW");	
	FmaxVsFmw.setColName("Fmw", "Fmax");
	FmaxVsFmw.setColUnit("MHz","MHz");
	metadata(FmaxVsFmw);
	
	// creation du fichier Fmax(Fmw)
	var FmaxVsPmw = new SData2D;
	FmaxVsPmw.addComment("Frequence du maximum en fonction de la puissance de la MW");	
	FmaxVsPmw.setColName("Pmw", "Fmax");
	FmaxVsPmw.setColUnit("dBm","MHz");
	metadata(FmaxVsPmw);
	
	// creation du fichier Fmax(Fmw)
	var PmaxVsFmw = new SData2D;
	PmaxVsFmw.addComment("Puissace du maximum en fonction de la fréquence de la MW");	
	PmaxVsFmw.setColName("Fmw", "Pmax");
	PmaxVsFmw.setColUnit("MHz","dBm");
	metadata(PmaxVsFmw);

	// creation du fichier Fmax(Fmw)
	var PmaxVsPmw = new SData2D;
	PmaxVsPmw.addComment("Puissance du maximum en fonction de la puissance de la MW");	
	PmaxVsPmw.setColName("Pmw", "Pmax");
	PmaxVsPmw.setColUnit("dBm","dBm");
	metadata(PmaxVsPmw);



	// Boucle de mesure
	for(var P=PStart;
		(PStart <  PStop  && P<=FStop) || (PStart >=  PStop  && P >= PStop) ; 
			P= P + PStep){
				Spectre(Fmw, P, FmaxVsFmw, FmaxVsPmw, PmaxVsFmw, PmaxVsPmw);
	}
	
	
	// sauvgarde
	FmaxVsFmw.saveFile(path + "/" + studyName +"_" + runName + "_FmaxVsFmw"	+ ".dat");
	FmaxVsPmw.saveFile(path + "/" + studyName + "_" + runName + "_FmaxVsPmw" + ".dat");
	PmaxVsFmw.saveFile(path + "/" + studyName + "_" + runName + "_PmaxVsFmw" + ".dat");	
	PmaxVsPmw.saveFile(path + "/" + studyName + "_" + runName + "_PmaxVsPmw" + ".dat");	

	var plotFmaxVsFmw = new SPlot2D();
	plotFmaxVsFmw.setData(FmaxVsFmw);
	plotFmaxVsFmw.setTitle("Frequence max = fct(Frequence MW)" );
	plotFmaxVsFmw.setLabels( "Frequence (MHz)", "Frequence (MHz)") 	
	plotFmaxVsFmw.show();

	var plotFmaxVsPmw = new SPlot2D();
	plotFmaxVsPmw.setData(FmaxVsPmw);
	plotFmaxVsPmw.setTitle("Frequence max = fct(Puissance MW)" );
	plotFmaxVsPmw.setLabels ( "Puissance (dBm)", "Frequence (MHz)") 	
	plotFmaxVsPmw.show();

	var plotPmaxVsFmw = new SPlot2D();
	plotPmaxVsFmw.setData(PmaxVsFmw);
	plotPmaxVsFmw.setTitle("Puissance max = fct(Frequence MW)" );
	plotPmaxVsFmw.setLabels( "Puissance (MHz)", "Frequence (MHz)") 
	plotPmaxVsFmw.show();
	
	var plotPmaxVsPmw = new SPlot2D();
	plotPmaxVsPmw.setData(PmaxVsPmw);
	plotPmaxVsPmw.setTitle("Puissance max= fct(Puissance MW)");
	plotPmaxVsPmw.setLabels 	( "Puissance (dBm)",	"Puissance (dBm)") 	
	plotPmaxVsPmw.show();
	
	
	delete FmaxVsFmw;
	delete FmaxVsPmw;
	delete PmaxVsFmw;
	delete PmaxVsPmw;
}

///////////////////////////////////////////////////////////////////////////////////////
//		   			Main
////////////////////////////////////////////////////////////////////////////////////////



var    studyName		= "20121116";		
var    runName		= nowTime("hhmm")  + "_Caracterisation PwrSpliter 2vs3";		
var    name		= studyName+"_" + runName +"_%PdBm_%FMHz";
var    folder		= serieName + "\\" + studyName + "\\" + runName+ "\\";
var    path			= DATA_PATH + "\\" + folder;


SweepFmw(1, 100, 0.5, -10);

ModMw.activate(false);

//fini !!

	//warningMsgBox("Fini !!" , "Amp(I)/fct(I)");