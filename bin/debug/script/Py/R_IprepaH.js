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
	const    MAX_I 		= 	10	; //mA
	const    MAX_V 		= 	1500	; //mV
	const    BASE_NAME	= 	"RI_"; //prefix of the name
	const    BASE_NAME_RH    =      "RH_";
	const    BASE_NAMEV	= 	"VI_";
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
	const    fieldInterval	= 	0.05	; // must be greater than 0.001
	const    fieldDv		=	0.5	; 
	const    V_H               =     -0.15	;//between -8 and 8
	const    currentMin      =      -0.18  ;//mA
	const    currentMax      =      0.18 ;//mA
	const    currentInterval =      0.001      ;//mA
	const    H0                   = 149.35*V_H+0.08;
	const    round_H          =Math.round(H0);
	
	const    current 	        =	0.05/MILI   ; //mA
	
	const    technician		= "PY"	
	const    serieName		= "DBMTJ"	
	const    sampleName		= "P638";
	const    junctionLineName	= "2";
	const    junctionColName	= "2";
	const    junctionTypeName    = "C3J2";
	const    mesure                   = "RI";
	const    champ			= "-22.5 Oe";
	const    mode                     = "Current";  
	const    cmt			= "";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= "2013_09_25";					
						
	const    name1			= "";
	const    name2                    ="";
						    
						
	
	const    folder			= serieName + "\\"
						+ sampleName + "\\"
						+ studyName + "\\"
						+ junctionName + "\\"
						+ mesure + "\\"
						+ champ+ "\\";
						    
	const    path			= DATA_PATH + "\\" + folder;
	

/********************************************************************************
*                                                Functions
**********************************************************************************/
function oneFieldPoint(dataRH_, plotRH_, DAQ, H) {
	
			DAQ.sweep(H  , fieldDv, CHAN);
			delay(0.2); // because without that, the field is not stable
			var VI = K2400.readVI(); // on stock pour le metre en entete
	

			R = VI[0]/VI[1];
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


// does one point of I, does the measurment, and add the result to the data
function oneCurrentPoint(dataV_, data_, plot_, K2400, I) {
	
			K2400.setCurrent(I/MILI);
			delay(0.1); 
			var VI = K2400.readVI(); // on stock pour le metre en entete
		
	
			R = VI[0]/VI[1];
			//if(I==0){R=0;}
				
			dataV_.append(I,VI[0]);
			data_.append(I,R);
			plot_.append(I,R);
			plot_.autoScale();
	
}


// Increment or decrement the current depending on
// the start point, stop point and the index of the loop
function stepCurrent(start, stop, loop){
	if(start == stop){
		return CurrentMax;
	}else{
		if(start < stop){		
			return Math.round( ((start + loop*currentInterval))*10000)/10000;
		}else{
			return Math.round( ((start - loop*currentInterval))*10000)/10000;
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
/*********************************************************************************
*					SAFETY
**********************************************************************************/

	// current safety  *********************************
	if(Math.abs(currentMax) > MAX_I){
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
*					DO IT
**********************************************************************************/	
	
	//clear the log output
	clear();
	print("work folder : " + path);
	
	// first set up of the  Keithley 2400 
	K2400.setMode(mode);
	K2400.setCurrentRange(10/MILI);  //range
	K2400.setVoltageRange(MAX_V*2/MILI);
	
	K2400.setVoltageCompliance(MAX_V/MILI); // max 
	K2400.setCurrentCompliance(MAX_I/MILI);
	K2400.setCurrent(0);
	delay(0.1);
	K2400.activate();
	
	
	 // on lit le courant et la tension, 
	var VI0 = K2400.readVI(); // on stock pour le metre en entete
	
	Offset_0=VI0[0];
	
		
	// *****************************************************	
		//we initialize the data object, and the plot object
		var dataRH = new SData2D();
		var plotRH = new SPlot2D();
		plotRH.setTitle("R(H):  I = "  + (MILI*current).toString() + " mA");
		plotRH.setWindowTitle("R(H):  I = "  +(MILI*current).toString()  + " mA");
		plotRH.show(); 
		
		var dataV= new SData2D();
		var data = new SData2D();
		var plot = new SPlot2D();
		plot.setTitle("R(I):  H = "  + Math.round(149.35*V_H+0.08).toString() + " Oe");
		plot.setWindowTitle("R(I):  H = "  +Math.round(149.35*V_H+0.08).toString()  + " Oe");
		plot.show(); 
	// ****************************************************
		
		//we initialize the field
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
		}
		*/
		
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
		myName_RH = name1+ "." + EXT;
		
		//myName_RH = myName_RH.replace("%DATE%",nowDate("yyyyMMdd")) ;
		//myName_RH = myName_RH.replace("%TIME%",nowTime("hh-mm-ss")) ;
		//myName_RH = myName_RH.replace("%round_H", FixFloatToStr(round_H,1,0)) ;
		
		dataRH.saveFile(path + "/" +BASE_NAME_RH+ myName_RH)
		print(myName_RH + " is saved.");
		
		
		K2400.setCurrent(0);	
		
		
	// *****************************************************	
		// put all varibles of the loop at zero
		const near0_step=3;
		var I     = 0+near0_step*currentInterval;
		var loop  = 0;
	
	// *****************************************************
		// 0 -> currentMax
		loop=0;
		while(I < currentMax){
			I = stepCurrent(0+near0_step*currentInterval, currentMax, loop);	
			oneCurrentPoint(dataV ,data, plot, K2400, I);
			loop++;
		}
		
		
	// *****************************************************
		// currentMax -> 0
		loop =0;		
		while(I> 0+near0_step*currentInterval){
			I = stepCurrent(currentMax,0+near0_step*currentInterval, loop);	
			oneCurrentPoint(dataV ,data, plot, K2400, I) ;
			loop++;
		}
		
	// *****************************************************
		// 0 -> currentMin
		loop =0;		
		while(I> currentMin){
			I = stepCurrent(0-near0_step*currentInterval, currentMin, loop);	
			oneCurrentPoint(dataV ,data, plot, K2400, I) ;
			loop++;
		}
		
	// *****************************************************
		// currentMin -> 0
		loop=0;
		while(I < 0-near0_step*currentInterval){
			I = stepCurrent(currentMin,0-near0_step*currentInterval, loop);	
			oneCurrentPoint(dataV ,data, plot, K2400, I);
			loop++;
		}
		
	// *****************************************************
		// 0 -> currentMax
		loop=0;
		while(I < currentMax){
			I = stepCurrent(0+near0_step*currentInterval, currentMax, loop);	
			oneCurrentPoint(dataV ,data, plot, K2400, I);
			loop++;
		}
		
	// *****************************************************
		
		/* sauvegarde  de R(I) */
		
		data.setColName("I","R");
		data.setColUnit("mA","Ohms");
		data.addComment("R(I) avec Mode source de courant")	;
		data.addComment(cmt);		

		//data.setMetaData("V0", VI0[0]/MILI);	
		//data.setMetaData("V0Unit", "V");	
		//data.setMetaData("I", current);	
	/*	data.setMetaData("fieldStart"		, fieldStart);	
		data.setMetaData("fieldInit"		, fieldInit);	
		data.setMetaData("fieldMax"		, fieldMax);	
		data.setMetaData("fieldStop"		, fieldStop);	
		data.setMetaData("fieldFinal"		, fieldFinal);	
		data.setMetaData("fieldInterval"	, fieldInterval);*/
		data.setMetaData("field"			, 149.35*V_H+0.08);		
		data.setMetaData("fieldUnit"		, "Vc");	


		data.setMetaData("studyName"		, studyName);	
		data.setMetaData("sampleName"		, sampleName);	
		data.setMetaData("junctionLineName"	, junctionLineName);	
		data.setMetaData("junctionColName"	, junctionColName);
		data.setMetaData("junctionTypeName"	, junctionTypeName);	
		data.setMetaData("junctionName"	, junctionName);	
		data.setMetaData("serieName"		, serieName);		

		data.setMetaData("technician"		, technician);	
		
		data.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		data.setMetaData("time"	, nowTime("hh:mm:ss"));
		
		var myName = "";
		myName = name2+ "." + EXT;
		
		//myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
		//myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
		myName = myName.replace("%round_H",	FixFloatToStr(round_H,1,0)) ;
		
		data.saveFile(path + "/" +BASE_NAME + myName)
		print(myName + " is saved.");
	
		/*  sauvegarde  de V(I) */
		
		dataV.setColName("I","V");
		dataV.setColUnit("mA","V");
		dataV.addComment("R(I) avec Mode source de courant")	;
		dataV.addComment(cmt);		

		//data.setMetaData("V0", VI0[0]/MILI);	
		//data.setMetaData("V0Unit", "V");	
		//data.setMetaData("I", current);	
	/*	data.setMetaData("fieldStart"		, fieldStart);	
		data.setMetaData("fieldInit"		, fieldInit);	
		data.setMetaData("fieldMax"		, fieldMax);	
		data.setMetaData("fieldStop"		, fieldStop);	
		data.setMetaData("fieldFinal"		, fieldFinal);	
		data.setMetaData("fieldInterval"	, fieldInterval);*/
		dataV.setMetaData("field"			, 149.35*V_H+0.08);		
		dataV.setMetaData("fieldUnit"		, "Vc");
		dataV.setMetaData("Offset à courant nul (V)"		, Offset_0);


		dataV.setMetaData("studyName"		, studyName);	
		dataV.setMetaData("sampleName"		, sampleName);	
		dataV.setMetaData("junctionLineName"	, junctionLineName);	
		dataV.setMetaData("junctionColName"	, junctionColName);
		dataV.setMetaData("junctionTypeName"	, junctionTypeName);	
		dataV.setMetaData("junctionName"	, junctionName);	
		dataV.setMetaData("serieName"		, serieName);		

		dataV.setMetaData("technician"		, technician);	
		
		dataV.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		dataV.setMetaData("time"	, nowTime("hh:mm:ss"));
		
		var myNameV = "";
		myNameV = name2+ "." + EXT;
		
		//myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
		//myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
		myNameV = myName.replace("%round_H",	FixFloatToStr(round_H,1,0)) ;
		
		dataV.saveFile(path + "/" +BASE_NAMEV + myNameV)
		print(myNameV + " is saved.");
		//plot.hide();
		//plotRH.hide();
		
		
		/*delete plot;
		delete data;*/
	
	K2400.setCurrent(0);
	delay(0.1);
	K2400.deactivate();     
	delay(0.1);
	K2400.enableLocal();
	DAQ.sweep(0, fieldDv, CHAN) ;
	if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;