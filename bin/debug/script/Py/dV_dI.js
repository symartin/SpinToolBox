/*******************************************************************************
* Title : 	dV/dI.js
* Autor :	Sylvain Martin
* Brief : 	dV/dI data+curve using Lock-in SR830
		devices : DAQ(field)/K2400(current or voltage source)/SR830 (Lock-in)
* Version :	1.0.0
*********************************************************************************/

/*********************************************************************************
*                                                 CONSTANTE
**********************************************************************************/
	const    AP 		= 	-8	; //Volt command of the Kepco
	const    P 			= 	8	; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
	const    MAX_I 		= 	1	; //mA
	const    MAX_V 		= 	2	; //V
	const    BASE_NAMEIX		= 	"IX_ "; //prefix of the name
	const    BASE_NAMEIY		= 	"IY_ ";
	const    BASE_NAMEIR		= 	"IR_ ";
	const    BASE_NAMEITheta	=	"ITheta_ ";
	const    BASE_NAME_RH	=	"RHprepa_";
	const    BASE_NAMEIdVdI	=	"IdVdI_";
	const    BASE_NAMEVdVdI	=	"VdVdI_";
	const    EXT	 	= 	"dat"; //extention
	const    MILI		=	1000	;
	const    DEBUG		=	1	;
	const    CHAN		=	0	;
	const    FIELD_0_END 	=  	1	;
	const    DATA_PATH    =      "D:\\Data"; // path of the data
	const    R_0		=	35470000 ; //Ohms, résistance de protection du lock-in
	const    mini		=	0.004 ; //V valeur minimale du lock-in
/*********************************************************************************
*                                                 PARAMETERS
**********************************************************************************/
/*********** DAQ Parameters ************/

	const    fieldStart	= 	ZERO	; // usually P or AP
	const    fieldInit		= 	P	; // usually P or AP
	const    fieldMax		= 	P	; // usually P or AP
	const    fieldMin		= 	AP	; // usually P or AP
	const    fieldStop	= 	ZERO	; // usually Zero
	const    fieldFinal		= 	ZERO	; // usually Zero 
	const    fieldInterval	= 	0.1	; // must be greater than 0.001
	const    fieldDv		=	0.5	; 
	const    V_H               =     -5	;//between -8 and 8
	const    H0                   = 149.35*V_H+0.08;
	const    round_H          =Math.round(H0);

/*********** K2400 Parameters ************/
	const    currentMin      =      -0.006  ;//mA
	const    currentMax      =      0.006	;//mA
	const    currentInterval =      0.00001     ;//mA
	const    current 	        =	0.0005/MILI   ; //mA

/*********** Lock-in Parameters ************/
	const    frequency  = 8.9; //Hz
	const    amplitude  = 0.100; //2*currentInterval/(2*MILI)*R_0; //V 

/*********** Storage Parameters ************/
	const    technician		= "PY"	
	const    serieName		= "DBMTJ"	
	const    sampleName		= "P684";
	const    junctionLineName	= "3";
	const    junctionColName	= "4";
	const    junctionTypeName    = "C4J1";
	const    mesure                   = "-750 Oe";
	const    mode                     = "dVdI";  
	const    cmt			= "";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= "2013_09_12";					
						
	const    name			= "";
	
	const    folder			= serieName + "\\"
						+ sampleName + "\\"
						+ studyName + "\\"
						+ junctionName + "\\"
						+ mesure + "\\";
						    
	const    path			= DATA_PATH + "\\" + folder;
	

/********************************************************************************
*                                                Functions
**********************************************************************************/
function oneFieldPoint(dataRH_, plotRH_, DAQ, H) {
			
			DAQ.sweep(H  , fieldDv, CHAN);
			delay(0.2); // because without that, the field is not stable
			var VI = K2400.readVI(); // on stock pour le metre en entete
	
			Resistance = VI[0]/VI[1];
			dataRH_.append(H,Resistance);
			plotRH_.append(H,Resistance);
			plotRH_.autoScale();
}

function stepField(start, stop, loopH){
	if(start == stop){
		return fieldMax;
	}else{
		if(start < stop){		
			return Math.round( (start + loopH*fieldInterval)*100000000)/100000000;
		}else{
			return Math.round( (start - loopH*fieldInterval)*100000000)/100000000;
		}
	}	
}

function oneDataPoint(dataIX_,dataIY_,dataIR_,dataITheta_, dataIdVdI_, plotIdVdI_, dataVdVdI_, plotVdVdI_, K2400, I) {
	
			K2400.setCurrent(I/MILI);
			delay(0.1);
			var VI = K2400.readVI();
			Resistance = VI[0]/VI[1];
			Vdc=VI[0];
			//K2400.setAutoVoltageRange(false);
			//K2400.setVoltMeasRange(2);
			X  = SR830.X();
			Y  = SR830.Y();
			R  = 1.4142*SR830.R();
			Theta  = SR830.Theta();
			dVdI = R/((1.4142*amplitude-(Abs(R)))/R_0);
	
	dataIX_.append(I,X);
	dataIY_.append(I,Y);
	dataIR_.append(I,R);
	dataITheta_.append(I,Theta);
	dataIdVdI_.append(I,dVdI);
	dataVdVdI_.append(Vdc,dVdI);
	
	plotIdVdI_.append(I,dVdI);
	plotIdVdI_.autoScale();
	
	plotVdVdI_.append(Vdc,dVdI);
	plotVdVdI_.autoScale();
	delay(5);
			
}

function stepCurrent(start, stop, loop){
	if(start == stop){
		return currentMax;
	}else{
		if(start < stop){		
			return Math.round( ((start + loop*currentInterval))*100000000)/100000000;
		}else{
			return Math.round( ((start - loop*currentInterval))*100000000)/100000000;
		}
	}	
}

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

function Abs(x){
if (x>=0) { return x;}
else{
	if (x<0){ return -x;}
	}
}
/*********************************************************************************
*					SAFETY
**********************************************************************************/

	// current safety  *********************************
	if(Math.abs(currentMax) > 3*MAX_I){
		warningMsgBox("Protection echantillon (courant start trop fort) : " 
					+ current.toString(), "R(H)");
		stop();
	}
	
	// Keithley 2400 ok? ************************************
	if(!K2400.available){
		warningMsgBox("The Keithley 2400 is not available.", "R(H)");
		stop();
	}
	// DAQ ok? ************************************
	if(!DAQ.available){
		warningMsgBox("The DAQ card is not available.", "R(H)");
		stop();
	}

/*********************************************************************************
					DO IT
**********************************************************************************/	
	
	
	//clear the log output
	clear();
	print("work folder : " + path);
	
	// first set up of the  Keithley 2400 
	K2400.setMode(mode);
	
	K2400.setCurrentRange(0.01/MILI);  //range
	K2400.setVoltageRange(2);
	
	K2400.setVoltageCompliance(MAX_V); // max 
	K2400.setCurrentCompliance(1/MILI);
	
	
	
	K2400.setCurrent(0);
	delay(0.1);
	K2400.activate();
	K2400.setAutoVoltageRange(false);
	
	// *****************************************************	
		//Initialisation de dataH et plotH pour la préparation du champ au courant "current"
		
		var dataRH = new SData2D();
		var plotRH = new SPlot2D();
		plotRH.setTitle("R(H):  I = "  + (MILI*current).toString() + " mA");
		plotRH.setWindowTitle("R(H):  I = "  +(MILI*current).toString()  + " mA");
		plotRH.show(); 
		
		SR830.setAmplitude(mini); // pour la mesure de R(H), pas de lock-in, 0.004V est la plus petite valeur possible
		
		// Initialisation du champ à V_H
		
			// Balayage initial
			DAQ.sweep(fieldMax  , fieldDv, CHAN);
			DAQ.sweep(fieldMin  , fieldDv, CHAN);
		
		K2400.setCurrent(current);
		delay(0.5);
		
		var H=fieldMin;
		var loopH=0;
		
		while(H < V_H){
			H = stepField(fieldMin, V_H, loopH);	
			oneFieldPoint(dataRH, plotRH, DAQ, H);
			loopH++;
		}
		/*
		loopH=0;
		while(H > V_H){
			H = stepField(fieldMax, V_H, loopH);	
			oneFieldPoint(dataRH, plotRH, DAQ, H);
			loopH++;
		}*/
		
		// Enregistrement des dataH + metadataH
		
		dataRH.setColName("H","R");
		dataRH.setColUnit("Oe","Ohms");
		dataRH.addComment("R(H) avec Mode source de courant")	;
		dataRH.addComment(cmt);		

		dataRH.setMetaData("current"			, current);		
		dataRH.setMetaData("fieldUnit"		, "Vc");	
		dataRH.setMetaData("studyName"		, studyName);	
		dataRH.setMetaData("sampleName"		, sampleName);	
		dataRH.setMetaData("junctionLineName"	, junctionLineName);	
		dataRH.setMetaData("junctionColName"	, junctionColName);
		dataRH.setMetaData("junctionTypeName"	, junctionTypeName);	
		dataRH.setMetaData("junctionName"	, junctionName);	
		dataRH.setMetaData("serieName"		, serieName);		
		dataRH.setMetaData("technician"		, technician);	
		dataRH.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		dataRH.setMetaData("time"	, nowTime("hh:mm:ss"));
		
		var myName_RH = "";
		myName_RH = name+ "." + EXT;
		
		myName_RH = myName_RH.replace("%round_H", FixFloatToStr(round_H,1,0)) ;
		
		dataRH.saveFile(path + "/" +BASE_NAME_RH+ myName_RH)
		print(myName_RH + " is saved.");
		
		K2400.setCurrent(0);
		
		delay(30); // Attendre 20s pour brancher le lock-in

// *****************************************************
/****** Paramètrage du lock-in *******/
	SR830.setFrequency(frequency);
	SR830.setAmplitude(amplitude);
		// Balayage en courant 
		
		//Initialisation des tableaux de datas
		var dataIX = new SData2D();
		var dataIY = new SData2D();
		var dataIR = new SData2D();
		var dataITheta = new SData2D();
		var dataIdVdI = new SData2D();
		var plotIdVdI = new SPlot2D();
		var dataVdVdI = new SData2D();
		var plotVdVdI = new SPlot2D();
		
		plotIdVdI.setTitle("dV/dI(I) : H = "  + (mesure).toString() );
		plotIdVdI.setWindowTitle("dV/dI(I) : H = "  +(mesure).toString()  );
		plotIdVdI.show();
		
		plotVdVdI.setTitle("dV/dI(Vdc) : H = "  + (mesure).toString() );
		plotVdVdI.setWindowTitle("dV/dI(Vdc) : H = "  +(mesure).toString()  );
		plotVdVdI.show(); 
		
		// Initialisation des variables
		const near0_step=1;
		var I     = 0+near0_step*currentInterval;
		var loop  = 0;
	// *****************************************************
		// 0 -> CurrentMax
		
			loop=0;
			while(I < currentMax){
				I = stepCurrent(0+near0_step*currentInterval, currentMax, loop);	
				//oneDataPoint(dataIX, dataIY, dataIR, dataITheta, dataIdVdI, plotIdVdI, dataVdVdI, plotVdVdI, K2400, I);
				loop++;
			}
			
			
		
	// *****************************************************
		// currentMax -> 0
		
		loop =0;		
		while(I> 0+near0_step*currentInterval){
			I = stepCurrent(currentMax,0+near0_step*currentInterval, loop);	
			oneDataPoint(dataIX, dataIY, dataIR, dataITheta, dataIdVdI, plotIdVdI, dataVdVdI, plotVdVdI, K2400, I);
			loop++;
		}
		
		
		
		
		
	// *****************************************************
		// 0 -> currentMin
		loop =0;		
		while(I> currentMin){
			I = stepCurrent(0-near0_step*currentInterval, currentMin, loop);	
			oneDataPoint(dataIX, dataIY, dataIR, dataITheta, dataIdVdI, plotIdVdI, dataVdVdI, plotVdVdI, K2400, I);
			loop++;
		}
		
	// *****************************************************
		// currentMin -> 0
		loop=0;
		while(I < 0-near0_step*currentInterval){
			I = stepCurrent(currentMin,0-near0_step*currentInterval, loop);	
			oneDataPoint(dataIX, dataIY ,dataIR ,dataITheta, dataIdVdI, plotIdVdI, dataVdVdI , plotVdVdI, K2400, I);
			loop++;
		}
		
	// *****************************************************
		// 0 -> currentMax
		loop=0;
		while(I < currentMax){
			I = stepCurrent(0+near0_step*currentInterval, currentMax, loop);	
			oneDataPoint(dataIX, dataIY, dataIR, dataITheta, dataIdVdI, plotIdVdI, dataVdVdI, plotVdVdI, K2400, I);
			loop++;
		}
		
	// *****************************************************
		
	/*************************Enregistrement data*****************************/
			
			/***** X *****/
			
		dataIX.setColName("Idc","X");
		dataIX.setColUnit("mA","V");
		dataIX.addComment("X = V_signal cos(dephasage)")	;
		dataIX.addComment(cmt);
		
		dataIX.setMetaData("Lock-in Frequency (Hz)"		, frequency);	
		dataIX.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		dataIX.setMetaData("studyName"		, studyName);	
		dataIX.setMetaData("sampleName"		, sampleName);	
		dataIX.setMetaData("junctionLineName"	, junctionLineName);	
		dataIX.setMetaData("junctionColName"	, junctionColName);
		dataIX.setMetaData("junctionTypeName"	, junctionTypeName);	
		dataIX.setMetaData("junctionName"	, junctionName);	
		dataIX.setMetaData("serieName"		, serieName);		
		dataIX.setMetaData("technician"		, technician);	
		dataIX.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		dataIX.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNameIX = "";
		myNameIX = name+ "." + EXT;
		
		myNameIX = myNameIX.replace("%frequency", FixFloatToStr(round_H,1,0)) ;
		
		dataIX.saveFile(path + "/" +BASE_NAMEIX+ myNameIX)
		print(myNameIX + " is saved.");
		
			/***** Y *****/
			
		dataIY.setColName("Idc","Y");
		dataIY.setColUnit("mA","V");
		dataIY.addComment("Y = V_signal sin(dephasage)")	;
		dataIY.addComment(cmt);
		
		dataIY.setMetaData("Lock-in Frequency (Hz)"		, frequency);	
		dataIY.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		dataIY.setMetaData("studyName"		, studyName);	
		dataIY.setMetaData("sampleName"		, sampleName);	
		dataIY.setMetaData("junctionLineName"	, junctionLineName);	
		dataIY.setMetaData("junctionColName"	, junctionColName);
		dataIY.setMetaData("junctionTypeName"	, junctionTypeName);	
		dataIY.setMetaData("junctionName"	, junctionName);	
		dataIY.setMetaData("serieName"		, serieName);		
		dataIY.setMetaData("technician"		, technician);	
		dataIY.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		dataIY.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNameIY = "";
		myNameIY = name+ "." + EXT;
		
		myNameIY = myNameIY.replace("%frequency", FixFloatToStr(round_H,1,0)) ;
		
		dataIY.saveFile(path + "/" +BASE_NAMEIY+ myNameIY)
		print(myNameIY + " is saved.");
		
			/***** R *****/
			
		dataIR.setColName("Idc","R");
		dataIR.setColUnit("mA","V");
		dataIR.addComment("R = sqrt(X²+Y²)")	;
		dataIR.addComment(cmt);
		
		dataIR.setMetaData("Lock-in Frequency (Hz)"		, frequency);	
		dataIR.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		dataIR.setMetaData("studyName"		, studyName);	
		dataIR.setMetaData("sampleName"		, sampleName);	
		dataIR.setMetaData("junctionLineName"	, junctionLineName);	
		dataIR.setMetaData("junctionColName"	, junctionColName);
		dataIR.setMetaData("junctionTypeName"	, junctionTypeName);	
		dataIR.setMetaData("junctionName"	, junctionName);	
		dataIR.setMetaData("serieName"		, serieName);		
		dataIR.setMetaData("technician"		, technician);	
		dataIR.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		dataIR.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNameIR = "";
		myNameIR = name+ "." + EXT;
		
		myNameIR = myNameIR.replace("%frequency", FixFloatToStr(round_H,1,0)) ;
		
		dataIR.saveFile(path + "/" +BASE_NAMEIR+ myNameIR)
		print(myNameIR + " is saved.");
		
			/***** Theta *****/
			 
		dataITheta.setColName("Idc","Theta");
		dataITheta.setColUnit("mA","degrés");
		dataITheta.addComment("Theta = arctan(Y/X)")	;
		dataITheta.addComment(cmt);
		
		dataITheta.setMetaData("Lock-in Frequency (Hz)"		, frequency);	
		dataITheta.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		dataITheta.setMetaData("studyName"		, studyName);	
		dataITheta.setMetaData("sampleName"		, sampleName);	
		dataITheta.setMetaData("junctionLineName"	, junctionLineName);	
		dataITheta.setMetaData("junctionColName"	, junctionColName);
		dataITheta.setMetaData("junctionTypeName"	, junctionTypeName);	
		dataITheta.setMetaData("junctionName"	, junctionName);	
		dataITheta.setMetaData("serieName"		, serieName);		
		dataITheta.setMetaData("technician"		, technician);	
		dataITheta.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		dataITheta.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNameITheta = "";
		myNameITheta = name+ "." + EXT;
		
		myNameITheta = myNameITheta.replace("%frequency", FixFloatToStr(round_H,1,0)) ;
		
		dataITheta.saveFile(path + "/" +BASE_NAMEITheta+ myNameITheta)
		print(myNameITheta + " is saved.");
		
		/***** IdVdI *****/
			 
		dataIdVdI.setColName("Idc","dV/dI");
		dataIdVdI.setColUnit("mA","Ohms");
		dataIdVdI.addComment("")	;
		dataIdVdI.addComment(cmt);
		
		dataIdVdI.setMetaData("Lock-in Frequency (Hz)"		, frequency);	
		dataIdVdI.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		dataIdVdI.setMetaData("studyName"		, studyName);	
		dataIdVdI.setMetaData("sampleName"		, sampleName);	
		dataIdVdI.setMetaData("junctionLineName"	, junctionLineName);	
		dataIdVdI.setMetaData("junctionColName"	, junctionColName);
		dataIdVdI.setMetaData("junctionTypeName"	, junctionTypeName);	
		dataIdVdI.setMetaData("junctionName"	, junctionName);	
		dataIdVdI.setMetaData("serieName"		, serieName);		
		dataIdVdI.setMetaData("technician"		, technician);	
		dataIdVdI.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		dataIdVdI.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNameIdVdI = "";
		myNameIdVdI = name+ "." + EXT;
		
		myNameIdVdI = myNameIdVdI.replace("%frequency", FixFloatToStr(round_H,1,0)) ;
		
		dataIdVdI.saveFile(path + "/" +BASE_NAMEIdVdI+ myNameIdVdI)
		print(myNameIdVdI + " is saved.");
		
		/***** VdVdI *****/
			 
		dataVdVdI.setColName("Vdc","dV/dI");
		dataVdVdI.setColUnit("V","Ohms");
		dataVdVdI.addComment("")	;
		dataVdVdI.addComment(cmt);
		
		dataVdVdI.setMetaData("Lock-in Frequency (Hz)"		, frequency);	
		dataVdVdI.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		dataVdVdI.setMetaData("studyName"		, studyName);	
		dataVdVdI.setMetaData("sampleName"		, sampleName);	
		dataVdVdI.setMetaData("junctionLineName"	, junctionLineName);	
		dataVdVdI.setMetaData("junctionColName"	, junctionColName);
		dataVdVdI.setMetaData("junctionTypeName"	, junctionTypeName);	
		dataVdVdI.setMetaData("junctionName"	, junctionName);	
		dataVdVdI.setMetaData("serieName"		, serieName);		
		dataVdVdI.setMetaData("technician"		, technician);	
		dataVdVdI.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		dataVdVdI.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNameVdVdI = "";
		myNameVdVdI = name+ "." + EXT;
		
		myNameVdVdI = myNameVdVdI.replace("%frequency", FixFloatToStr(round_H,1,0)) ;
		
		dataVdVdI.saveFile(path + "/" +BASE_NAMEVdVdI+ myNameVdVdI)
		print(myNameVdVdI + " is saved.");
			
		
	/*************************************************************************/
	
K2400.setCurrent(0);
delay(0.1);
K2400.deactivate();     
delay(0.1);
K2400.enableLocal(); // Local K2400
SR830.setAmplitude(mini);
//RAZ du champ			
DAQ.sweep(0, fieldDv, CHAN) ;
if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;	

	
	