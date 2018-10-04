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
	const    MAX_I 		= 	0.020 ; //A
	const    MIN_I		=	-0.020; 
	const    MAX_V 		= 	1.500	; //V
	const    BASE_NAME	= 	"IV_200"; //prefix of the name
	const    BASE_NAME_RH = "RHprepa_200";
	const    EXT	 	= 	"dat"; //extention
	const    MILI		=	1000	;
	const    DEBUG		=	1	;
	const    CHAN		=	0	;
	const    FIELD_0_END 	=  	1	;
	const    DATA_PATH    =      "D:\\Data"; // path of the data
	
	//const    maxV	=	0.6; //borne supérieure de la tension(V)
	//const    minV	=	-0.6;
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
	const    fieldInterval	= 	0.1	; // must be greater than 0.001
	const    fieldDv		=	0.5	; 
	const    voltageDv	=	0.5	;
	const    voltageInterval=	0.01 ; //pas en tension (V)
	const    voltageMax	=	0.9	;
	const    voltageMin	=	-0.9	;
	const    voltageStart	=	ZERO	;//valeur initiale du courant
	const    V_H               =   -7.5;
	const    H                   = 149.35*V_H+0.08;
	const    round_H          = Math.round(H);
	
	
	
	const    current 	        =	1	; //mA
	const    V_pol             =      0.2    ;//V
	
	const    technician		= "PY"	
	const    serieName		= "DBMTJ"	
	const    sampleName		= "D751";
	const    junctionLineName	= "9";
	const    junctionColName	= "7";
	const    junctionTypeName    = "A2J4";
	const    mesure                   = "IV";
	const    cmt			= "";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= "2013_02_26";					
						
	const    name			= "";
	const    champ_mesure         = "-1120Oe"; 
	
	const    folder			= serieName + "\\"
						+ sampleName + "\\"
						+ studyName + "\\"
						+ junctionName + "\\"
						+ mesure + "\\"
						+ champ_mesure + "\\";
						    
	const    path			= DATA_PATH + "\\" + folder;
	

/********************************************************************************
*                                                Functions
**********************************************************************************/
// does one point of H, sweep the field, does the measurment, and add the result to the data
function oneFieldPoint(dataRH_, plotRH_, DAQ, H) 
{
	
			DAQ.sweep(H  , fieldDv, CHAN);
			delay(0.2); // because without that, the field is not stable
			var IV = K2400.readIV(); // on stock pour le metre en entete*/
		

			R = IV[1]/IV[0];
			dataRH_.append(H,R);
			plotRH_.append(H,R);
			plotRH_.autoScale();
}


function oneVoltagePoint(data_, plot_, K2400, V) 
{
	
			K2400.setVoltage(V);
			delay(0.2); // because without that, the field is not stable
			var IV = K2400.readIV(); // on stock pour le metre en entete
			
			//R = VI[0]/VI[1];
			data_.append(IV[1],IV[0]);
			plot_.append(IV[1],IV[0]);
			plot_.autoScale();
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
function stepVoltage(start, stop, loopV){
	if(start == stop){
		return voltageMax;
	}else{
		if(start < stop){		
			return Math.round( (start + loopV*voltageInterval)*1000000)/1000000;
		}else{
			return Math.round( (start - loopV*voltageInterval)*1000000)/1000000;
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
	if(Math.abs(current) > MAX_I*MILI){
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
	K2400.setMode("VOLTAGE");
	K2400.setCurrentRange(MAX_I*2);  //range
	K2400.setVoltageRange(MAX_V*2);
	
	K2400.setVoltageCompliance(MAX_V); // max 
	K2400.setCurrentCompliance(MAX_I);
	K2400.setVoltage(0);
	delay(0.1);
	K2400.activate();
	
	 // on lit le courant et la tension, 
	var IV0 = K2400.readIV(); // on stock pour le metre en entete
	

		
	
		
	// *****************************************************	
		//we initialize the data object, and the plot object
		//we initialize the data object, and the plot object
		var dataRH = new SData2D();
		var plotRH = new SPlot2D();
		plotRH.setTitle("R(H):  V = "  + (V_pol).toString() + "V");
		plotRH.setWindowTitle("R(H):  V = "  + (V_pol).toString() + "V");
		plotRH.show(); 
		
		var data = new SData2D();
		var plot = new SPlot2D();
		plot.setTitle(" I(V) : H=" + (round_H).toString() +  "Oe");
		plot.setWindowTitle("I(V) : H=" + (round_H).toString() +  "Oe" );
		plot.show(); 

		
	// *****************************************************	
		//we initialize the field
		DAQ.sweep(fieldMax, fieldDv, CHAN); //0 field
		DAQ.sweep(fieldMin, fieldDv, CHAN); //état P (maxH)
	// *****************************************************		
		K2400.setVoltage(V_pol);
		
		var H=fieldMin;
		var loopH=0;
		
		/*while(H < fieldMax){
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
		
		
		K2400.setVoltage(0);	
		
	// *****************************************************	
		// put all variables of the loop at zero
		var V	=voltageStart
		//var H	=0.0;
		//var loopH   =0;
		var loopI    =0;
	// *****************************************************
	
		
		//cadran voltageStart -> voltageMax
		loopV =0;
		while(V >= voltageMin) 
		{
		V = stepVoltage(voltageStart,voltageMin, loopV);	
		oneVoltagePoint(data, plot, K2400, V) ;
		loopV++;	
		}
		
		//cadran voltageMax -> voltageStart
		loopV =0;
		while(V < voltageMax) 
		{
		V = stepVoltage(voltageMin,voltageMax, loopV);	
		oneVoltagePoint(data, plot, K2400, V) ;
		loopV++;	
		}
		
		//cadran voltageStart -> voltageMin
		loopV =0;
		while(V >= voltageMin) 
		{
		V = stepVoltage(voltageMax,voltageMin, loopV);	
		oneVoltagePoint(data, plot, K2400, V) ;
		loopV++;	
		}
		
		
		
		data.setColName("V","I");
		data.setColUnit("V","A");
		//data.addComment("R(H) avec Mode source de courant")	;
		//data.addComment(cmt);		

		//data.setMetaData("V0", VI0[0]/MILI);	
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
		myName = name + "." + EXT;
		
		myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
		myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
		myName = myName.replace("%round_H",	FixFloatToStr(round_H,1,0)) ;
		
		data.saveFile(path + "/" +BASE_NAME + myName)
		print(myName + " is saved.");
		plot.hide();
		//delete plot;
		//delete data;
	
	K2400.setVoltage(0);
	K2400.deactivate(); 
	delay(0.1);
	DAQ.sweep(fieldFinal, fieldDv, CHAN) ;
	delay(0.1);
	K2400.enableLocal();
	if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;
	print("Done : " + path);



		