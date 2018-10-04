/*******************************************************************************
* Title : 	mono_RH.js
* Autor :	Sylvain Martin
* Brief : 	example script that do a R(H) curve, the first part defines some constant, 
* 		the seconde the parametres of the measurment, and the last one do the 
*		measurement.
* Version :	1.0.0
*********************************************************************************/

/*********************************************************************************
*                                                 CONSTANTE
**********************************************************************************/
	const    AP 		= 	-8	; //Volt command of the Kepco
	const    P 			= 	8	; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
	const    MAX_I 		= 	20	; //mA
	const    MAX_V 		= 	1500	; //mV
	const    BASE_NAME	= 	"RV_"; //prefix of the name
	const    BASE_NAME_RH    =      "RHprepa_";
	const    EXT	 	= 	"dat"; //extention
	const    MILI		=	1000	;
	const    DEBUG		=	1	;
	const    CHAN		=	0	;
	const    FIELD_0_END 	=  	1	;
	const    DATA_PATH    =      "D:\\Data"; // path of the data
/*********************************************************************************
*                                                 PARAMETERS
**********************************************************************************/
// preparation (without measurement) zero -> fieldInit -> fieldStart
// fieldStart -> fieldMax -> fieldStart -> fieldMin -> fieldStart
// preparation (without measurement) fieldStart -> fieldFinal

	const    fieldStart	= 	ZERO	; // usually P or AP
	const    fieldInit		= 	P	; // usually P or AP
	const    fieldMax		= 	P	; // usually P or AP
	const    fieldMin		= 	AP	; // usually P or AP
	const    fieldStop	= 	ZERO	; // usually Zero
	const    fieldFinal		= 	ZERO	; // usually Zero 
	const    fieldInterval	= 	0.1	; // must be greater than 0.001
	const    fieldDv		=	0.5	; 
	const    V_H               =     4	;//between -8 and 8
	const    voltageMin      =      -0.5  ;//mA
	const    voltageMax      =      0.5 ;//mA
	const    voltageInterval =      0.01      ;//mA
	const    H0                   = 149.35*V_H+0.08;
	const    round_H          =Math.round(H0);
	
	const    Voltage	        =	100/MILI   ; //V
	
	const    technician		= "PY"	
	const    serieName		= "SBMTJ"	
	const    sampleName		= "D641";
	const    junctionLineName	= "6";
	const    junctionColName	= "5";
	const    junctionTypeName    = "D6J1";
	const    mesure                   = "600Oe";
	const    mode                     = "Voltage";  
	const    cmt			= "";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= "2013_03_07";					
						
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
			var IV = K2400.readIV(); // on stock pour le metre en entete
	

			R = IV[1]/IV[0];
			dataRH_.append(H,R);
			plotRH_.append(H,R);
			plotRH_.autoScale();
}

function stepField(start, stop, loopH){
	if(start == stop){
		return fieldMax;
	}else{
		if(start < stop){		
			return Math.round( (start + loopH*fieldInterval)*10000)/10000;
		}else{
			return Math.round( (start - loopH*fieldInterval)*10000)/10000;
		}
	}	
}
/*********************************************************************************
*					SAFETY
**********************************************************************************/

	// current safety  *********************************
	if(Math.abs(Voltage) > MAX_V){
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
/************************************************************************************/
	
	
	K2400.setMode(mode);
	K2400.setCurrentRange(MAX_I*2/MILI);  //range
	K2400.setVoltageRange(MAX_V*2/MILI);
	
	K2400.setVoltageCompliance(MAX_V/MILI); // max 
	K2400.setCurrentCompliance(MAX_I/MILI);
	K2400.setVoltage(0);
	delay(0.1);
	K2400.activate();
	
	
	//we initialize the data object, and the plot object
		var dataRH = new SData2D();
		var plotRH = new SPlot2D();
		plotRH.setTitle("R(H):  V = "  + (MILI*Voltage).toString() + " mV");
		plotRH.setWindowTitle("R(H):  V = "  +(MILI*Voltage).toString()  + " mV");
		plotRH.show();
	
	// ****************************************************
		
		//we initialize the field
		DAQ.sweep(fieldMax  , fieldDv, CHAN);
		DAQ.sweep(fieldMin  , fieldDv, CHAN);
		
		K2400.setVoltage(Voltage);
		delay(0.5);
		
		var H=fieldMin;
		var loopH=0;
		/*
		while(H < fieldMax){
			H = stepField(fieldMin, fieldMax, loopH);	
			oneFieldPoint(dataRH, plotRH, DAQ, H);
			loopH++;
		}*/
		
		loopH=0;
		while(H < V_H){
			H = stepField(fieldMin, V_H, loopH);	
			oneFieldPoint(dataRH, plotRH, DAQ, H);
			loopH++;
		}
		
		dataRH.setColName("H","R");
		dataRH.setColUnit("Oe","Ohms");
		dataRH.addComment("R(H) avec Mode source de courant")	;
		dataRH.addComment(cmt);		

		//data.setMetaData("V0", VI0[0]/MILI);	
		//data.setMetaData("V0Unit", "V");	
		//data.setMetaData("I", current);	
	/*	data.setMetaData("fieldStart"		, fieldStart);	
		data.setMetaData("fieldInit"		, fieldInit);	
		data.setMetaData("fieldMax"		, fieldMax);	
		data.setMetaData("fieldStop"		, fieldStop);	
		data.setMetaData("fieldFinal"		, fieldFinal);	
		data.setMetaData("fieldInterval"	, fieldInterval);*/
		//dataRH.setMetaData("current"			, current);		
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
		
		//myName_RH = myName_RH.replace("%DATE%",nowDate("yyyyMMdd")) ;
		//myName_RH = myName_RH.replace("%TIME%",nowTime("hh-mm-ss")) ;
		//myName_RH = myName_RH.replace("%round_H", FixFloatToStr(round_H,1,0)) ;
		
		dataRH.saveFile(path + "/" +BASE_NAME_RH+ myName_RH)
		print(myName_RH + " is saved.");
	
		var IV = K2400.readVI(); 
		K2400.setVoltage(Voltage);	
		delay(0.2); 
		R = IV[1]/IV[0];
		//print(R);
		delay(0.2);
		
		//plotRH.hide();
		
	K2400.setVoltage(0);
	delay(0.1);
	K2400.deactivate();     
	delay(0.1);
	K2400.enableLocal();
	/*DAQ.sweep(0, fieldDv, CHAN) ;
	if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;*/		
	
			