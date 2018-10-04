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
	const    AP 		= 	-8	; //Volt command of the Kepco <=8
	const    P 			= 	8	; //Volt command of the Kepco <=8
	const    ZERO 		= 	0	; //Volt command of the Kepco 
	const    MAX_I 		= 	1	; //A
	const    MAX_V 		= 	2	; //V
	const    BASE_NAME	= 	"VI_"; //prefix of the name
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

	const    fieldStart	= 	AP	; // usually P or AP
	const    fieldInit		= 	P	; // usually P or AP
	const    fieldMax		= 	P	; // usually P or AP
	const    fieldMin		= 	AP	; // usually P or AP
	const    fieldStop	= 	ZERO	; // usually Zero
	const    fieldFinal		= 	ZERO	; // usually Zero
	const    fieldInterval	= 	0.05	; // must be greater than 0.001
	const    fieldDv		=	0.5	; 
	const    currentDv	=	0.5	;
	const    currentInterval=	0.00000020 ; //pas en courant (mA)
	const    currentMax	=	0.000080	;
	const    currentMin	=	-0.000100;
	const    currentStart	=	ZERO	;//valeur initiale du courant
	const    V_H               =  7  ;
	const    H                   = 149.35*V_H+0.08;
	const    round_H          =Math.round(H);
	
	
	
	const    current 	        =	0.00001/MILI	; //mA
	
	const    technician		= "PY"	
	const    serieName		= "DBMTJ"	
	const    sampleName		= "P684";
	const    junctionLineName	= "3";
	const    junctionColName	= "4";
	const    junctionTypeName    = "C2J5";
	const    mesure                   = "VI";
	const    cmt			= "";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
						
	const    studyName		= "2013_09_13";					
						
	const    name			= "%round_H";
	
	const    folder			= serieName + "\\"
						+ sampleName + "\\"
						+ studyName + "\\"
						+ junctionName + "\\"
						+ mesure + "\\";
						
						
	const    path			= DATA_PATH + "\\" + folder;
	

/********************************************************************************
*                                                Functions
**********************************************************************************/
// does one point of H, sweep the field, does the measurment, and add the result to the data
function oneFieldPoint(dataRH_, plotRH_, DAQ, H) {
	
			DAQ.sweep(H  , fieldDv, CHAN);
			delay(0.2); // because without that, the field is not stable
			var VI = K2400.readVI(); // on stock pour le metre en entete
	

			R = VI[0]/VI[1];
			dataRH_.append(H,R);
			plotRH_.append(H,R);
			plotRH_.autoScale();
}


function oneCurrentPoint(data_, plot_, K2400, I) 
{
	
			K2400.setCurrent(I/MILI);
			delay(0.2); // because without that, the field is not stable
			var VI = K2400.readVI(); // on stock pour le metre en entete
			
			//R = VI[0]/VI[1];
			data_.append(VI[1],VI[0]);
			plot_.append(VI[1],VI[0]);
			plot_.autoScale();
	//delay(1);
}


// Increment or decrement the field depending on
// the start point, stop point and the index of the loop
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

// Increment or decrement the current depending on
// the start point, stop point and the index of the loop
function stepCurrent(start, stop, loopI){
	if(start == stop){
		return currentMax;
	}else{
		if(start < stop){		
			return Math.round( (start + loopI*currentInterval)*10000000000)/10000000000;
		}else{
			return Math.round( (start - loopI*currentInterval)*10000000000)/10000000000;
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
*					DO IT
**********************************************************************************/	
	
	//clear the log output
	clear();
	print("work folder : " + path);
	
	// first set up of the  Keithley 2400 
	K2400.setMode("CURRENT");
	K2400.setCurrentRange(0.001/MILI);  //range
	K2400.voltageRange(2);
	
	K2400.setVoltageCompliance(MAX_V); // max 
	K2400.setCurrentCompliance(1/MILI);
	K2400.setCurrent(0);
	delay(0.1);
	K2400.activate();
	
	 // on lit le courant et la tension, 
	var VI0 = K2400.readVI(); // on stock pour le metre en entete
	

		
	
		
	// *****************************************************	
		//we initialize the data object, and the plot object
		var dataRH = new SData2D();
		var plotRH = new SPlot2D();
		plotRH.setTitle("R(H):  I = "  + (MILI*current).toString() + " mA");
		plotRH.setWindowTitle("R(H):  I = "  +(MILI*current).toString()  + " mA");
		plotRH.show(); 
		
		
		var data = new SData2D();
		var plot = new SPlot2D();
		plot.setTitle(" V(I): H = " + round_H.toString() + "Oe"  );
		plot.setWindowTitle(" V(I): H = " + round_H.toString() + "Oe"  );
		plot.show(); 

		
	// *****************************************************	
		//we initialize the field
		DAQ.sweep(fieldInit  , fieldDv, CHAN); //->Hmax
		delay(0.5);
		DAQ.sweep(fieldStart, fieldDv, CHAN);//->H=0
		delay(0.5);
		DAQ.sweep(fieldMin, fieldDv, CHAN);//->Hmin
		delay(0.5);
		
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
		myName_RH = name+ "." + EXT;
		
		myName_RH = myName_RH.replace("%DATE%",nowDate("yyyyMMdd")) ;
		myName_RH = myName_RH.replace("%TIME%",nowTime("hh-mm-ss")) ;
		myName_RH = myName_RH.replace("%round_H", FixFloatToStr(round_H,1,0)) ;
		
		dataRH.saveFile(path + "/" +BASE_NAME_RH+ myName_RH)
		print(myName_RH + " is saved.");
		
		
		K2400.setCurrent(0);	
	// *****************************************************	
		// put all variables of the loop at zero
		var I		=currentStart
		//var H     = fieldStart;
		//var loopH  = 0;
		var loopI  = 0;
	// *****************************************************
	
		//cadran currentStart -> currentMax
		loopI =0;
		while(I <= currentMax) 
		{
		I = stepCurrent(currentStart,currentMax, loopI);	
		oneCurrentPoint(data, plot, K2400, I) ;
		loopI++;	
		}
		
		//cadran currentMax -> currentMin
		loopI =0;
		while(I >= currentMin) 
		{
		I = stepCurrent(currentMax,currentMin, loopI);	
		oneCurrentPoint(data, plot, K2400, I) ;
		loopI++;	
		}
		
		//cadran currentMin -> currentMax
		loopI =0;
		while(I <= currentMax){
		I = stepCurrent(currentMin,currentMax, loopI);
		oneCurrentPoint(data, plot, K2400, I) ;
		loopI++;
		}
		
		/*
		//cadran currentStart -> currentMin
		loopI =0;
		while(I >= currentMin){
		I = stepCurrent(currentStart,currentMin, loopI);
		oneCurrentPoint(data, plot, K2400, I) ;
		loopI++;
		}
		
		//cadran currentMin -> currentStart
		loopI =0;
		while(I <= currentStart){
		I = stepCurrent(currentMin,currentStart, loopI);
		oneCurrentPoint(data, plot, K2400, I) ;
		loopI++;
		}
		
		//cadran currentStart -> currentMax
		loopI =0;
		while(I <= currentMax){
		I = stepCurrent(currentStart,currentMax, loopI);
		oneCurrentPoint(data, plot, K2400, I) ;
		loopI++;
		}
		*/
		
		
		data.setColName("I","V");
		data.setColUnit("mA","V");
		//data.addComment("R(H) avec Mode source de courant")	;
		//data.addComment(cmt);		

		data.setMetaData("V0", VI0[0]/MILI);	
		data.setMetaData("V0Unit", "V");	
		data.setMetaData("I", current);	
		data.setMetaData("fieldStart"		, fieldStart);	
		data.setMetaData("fieldInit"		, fieldInit);	
		data.setMetaData("fieldMax"		, fieldMax);	
		data.setMetaData("fieldStop"		, fieldStop);	
		data.setMetaData("fieldFinal"		, fieldFinal);	
		data.setMetaData("fieldInterval"	, fieldInterval);
		data.setMetaData("fieldDv"		, fieldDv);		
		data.setMetaData("fieldUnit"		, "Vc");	
		data.setMetaData("current"		, current);	
		data.setMetaData("currentUnit"		, "mA");	
		data.setMetaData("studyName"		, current);	
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
		myName = name+ "." + EXT;
		
		myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
		myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
		myName = myName.replace("%round_H",	FixFloatToStr(round_H,1,0)) ;
		
		data.saveFile(path + "/" +BASE_NAME + myName)
		print(myName + " is saved.");
		//plot.hide();
		//plotRH.hide();
		//delete plot;
		//delete data;
	
	K2400.setCurrent(0);
	K2400.deactivate();
	delay(0.1);
	DAQ.sweep(fieldFinal, fieldDv, CHAN) ;
	delay(0.1);
	K2400.enableLocal();
	if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;
	print("Done : " + path);



		