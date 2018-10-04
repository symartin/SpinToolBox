/*******************************************************************************
* Title : 	Amp_freq_fct_I.js
* Autor :	Sylvain Martin
* Brief : 	mesure l'amplitute et la frequence en fonction de I
* Version :	1.5
*********************************************************************************/	

/*********************************************************************************
*                                                 CONSTANTE
**********************************************************************************/
	const    AP 		= 	-6	; //Volt command of the Kepco
	const    P 			= 	6	; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
	const    MAX_I 		= 	0.027	; //A
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
	const    sampleName		= "#12"
	const    junctionLineName	= "f";
	const    junctionColName	= "II";
	const    junctionTypeName    = "1A";
	const    cmt			= "avec bouclier droit, ac ss apli , power spliter, et un att 3dB " 
		    cmt			= cmt+" pour modulation sens :" + sens;
		    
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= "20121108";		
	const    runName			= nowTime("hhmm") ;		
	
	const    name			= studyName+"_" + runName +"_" + sens
							+"_%ImA";
	
	const    folder			= serieName + "\\"
						+ studyName + "\\"
						+ sampleName + "\\"
						+ junctionName + "\\"
						+ runName+ "\\";
						    
	const    path			= DATA_PATH + "\\" + folder;
	
///////////////////////////////////////////////////////////////////////////////////////
//				variables exterieures au script
////////////////////////////////////////////////////////////////////////////////////////

	var 		field 			= 	-0.70;
	const 	FreqNat		= 	387; // MHz
	
	// vers le "haut" ou vers le "bas" fonctione pour des courant negatif
	const    sens			= "abs_up";
	//const    sens			= "abs_down";	
	
	const 	courantStart	=	-13; //mA
	const 	courantStop	=	-23; //mA
	const 	courantStep	=	-0.2; //mA
	const 	nbAverage		=	0;

///////////////////////////////////////////////////////////////////////////////////////
//		   on fait 2 fichiers avec les coordonees du maximum		 
////////////////////////////////////////////////////////////////////////////////////////

	var dataMaxFreq = new SData2D;
	
	var cmt2;
	cmt2   =  "Frequence du maximum de signal par rapport au courant";
	
	dataMaxFreq.addComment(cmt2);	
	dataMaxFreq.setColName("I", "SigFreq");
	dataMaxFreq.setColUnit("mA","GHz");

	var dataMaxAmp = new SData2D;
	
	var cmt2;
	cmt2   =  "amplitude du maximum de signal par rapport au courant";
	
	dataMaxAmp.addComment(cmt2);	
	dataMaxAmp.setColName("I", "SigAmp");
	dataMaxAmp.setColUnit("mA","V");
	
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
function metadata(data, rbw){
	
	data.setMetaData("RBW"			, rbw );	
	data.setMetaData("RBWUnit"		, "GHz");	
	data.setMetaData("SaNumberAverage"	, nbAverage);		
	data.setMetaData("SaAttenuation"	, PSAE4440A.attenuation());	
	data.setMetaData("SaNbPoints"		, PSAE4440A.nbPoints());	

	
	data.setMetaData("FreqNaturel"		, (FreqNat/1000).toFixed(3) );
	data.setMetaData("FreqNatUnit"		, "GHz");	
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

	var VI = K2400.readVI(); // on stock pour le metre en entete
	var R = VI[0]/VI[1];

	// put some metadata ****************************************
	data.setMetaData("I"				, VI[0]/MILI);	
	data.setMetaData("IUnit"			, "mA");	
	data.setMetaData("V"				, VI[1]/MILI);	
	data.setMetaData("VUnit"			, "mV");	
	data.setMetaData("R"				, R);	
	data.setMetaData("RUnit"			, "Ohm");	
	
	data.setMetaData("date"	, nowDate("dd/MM/yyyy"));
	data.setMetaData("time"	, nowTime("hh:mm:ss"));
	
}

///////////////////////////////////////////////////////////////////////////////////////
//				 function Spectrum
////////////////////////////////////////////////////////////////////////////////////////
function Spectre(I, f0 ){
	
	// current safety  *********************************
	if(Math.abs(I) > MAX_I*MILI*1.01){
		warningMsgBox("Protection echantillon (courant start trop fort) : " 
					+ current.toString(), "R(H)");
		stop();
	}
	

	K2400.setCurrent(I/1000);
	// on lit le courant et la tension, 
	var VI = K2400.readVI(); // on stock pour le metre en entete
	
	// setup the  spectrum analyser  ***************************************
	var span = 350;
	var rbw = PSAE4440A.checkRbw(span/(1000*PSAE4440A.nbPoints()));
	
	PSAE4440A.setFreqStart((f0-span)/1000);
	PSAE4440A.setFreqStop((f0+span)/1000);
	PSAE4440A.setNbAverage(nbAverage);
	PSAE4440A.setRefLevel(-65);
	
	//On prend le spectre ******************************************
	delay(0.5);
	var data = new SData2D;
	data = PSAE4440A.ReadSpectrum();
	delay(0.5);
	data.addComment(cmt);
	

	metadata(data, rbw);
	

	
	// make a cool name **************************************************		
	var myName = "";
	myName = name;
	myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
	myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
	myName = myName.replace("%I",	FixFloatToStr(I,2,2)) ;

	
	
	// on fait un fichier freq Max p/r freq MW ******************************************
	data.saveFile(path + "/" + myName + "." + EXT);
	
	
	// Recheche du max ********************************************
	data.slideAverage(20);
	var ptMax = data.max();
	
	// on fait un fichier freq Max p/r freq MW ******************************************
	dataMaxFreq.append(I,ptMax[0]);
	dataMaxAmp.append(I,ptMax[1]);
	

	
	delete data;

}

	if(sens== "abs_up" && courantStep < 0){
		
		for(var i=courantStart; Math.abs(i)<=Math.abs(courantStop); i= i + courantStep){
			Spectre(i, FreqNat);
		}
		
	}else if(sens== "abs_down" && courantStep > 0){
			for(var i=courantStart; Math.abs(i)>=Math.abs(courantStop); i= i + courantStep){
			Spectre(i, FreqNat);
	}
	
	}else{
	warningMsgBox("Probleme de conf !!" , "Amp(I)/fct(I)");
	}

	
	metadata(dataMaxFreq, PSAE4440A.rbw());
	metadata(dataMaxAmp, PSAE4440A.rbw());
	
	dataMaxFreq.saveFile(path + "/" + studyName +"_" + runName + "_FreqMax_" +sens
					+ ".dat");

	dataMaxAmp.saveFile(path + "/" + studyName + "_" + runName + "_AmpMax_" +sens
					+ ".dat")

	//PSGE8257D.activate(false);
	var plot = new SPlot2D();
	plot.setData(dataMaxFreq);
	plot.show();

	var plot2 = new SPlot2D();
	plot2.setData(dataMaxAmp);
	plot2.show();


	delete dataMaxAmp;
	delete dataMaxFreq;
	K2400.setCurrent(0/1000);
	warningMsgBox("Fini !!" , "Amp(I)/fct(I)");