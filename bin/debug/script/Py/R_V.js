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
	const    AP 		= 	-6	; //Volt command of the Kepco
	const    P 			= 	6	; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
	const    MAX_I 		= 	1	; //mA
	const    MAX_V 		= 	1.500	; //V
	const    BASE_NAME	= 	"RV_"; //prefix of the name
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
	const    V_H               =      0.8     ;//between -8 and 8
	const    voltageMin      =      -0.4  ;//V
	const    voltageMax      =      0.4  ;//V
	const    voltageInterval =      0.01      ;//V
	
	//const    current 	        =	0.1   ; //mA
	
	const    technician		= "PY"	
	const    serieName		= "DBMTJ"	
	const    sampleName		= "D751";
	const    junctionLineName	= "9";
	const    junctionColName	= "7";
	const    junctionTypeName    = "A5J1";
	const    mode                     = "Voltage";  
	const    cmt			= "";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= "2013_01_30";					
						
	const    name			= "%HOe";
	
	const    folder			= serieName + "\\"
						+ sampleName + "\\"
						+ studyName + "\\"
						+ junctionName + "\\"
						+ mode + "\\";
						    
	const    path			= DATA_PATH + "\\" + folder;
	

/********************************************************************************
*                                                Functions
**********************************************************************************/
// does one point of I, does the measurment, and add the result to the data
function oneVoltagePoint(data_, plot_, K2400, V) {
	
			K2400.setVoltage(V);
			delay(0.2); 
			var IV = K2400.readIV(); // on stock pour le metre en entete
		
	
			R = IV[1]/IV[0];
			//if(I==0){R=0;}
				
	
			data_.append(V,R);
			plot_.append(V,R);
			plot_.autoScale();
}
// Increment or decrement the current depending on
// the start point, stop point and the index of the loop
function stepVoltage(start, stop, loop){
	if(start == stop){
		return voltageMax;
	}else{
		if(start < stop){		
			return Math.round( ((start + loop*voltageInterval))*10000)/10000;
		}else{
			return Math.round( ((start - loop*voltageInterval))*10000)/10000;
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
	K2400.setCurrentRange(MAX_I*2/MILI);  //range
	K2400.setVoltageRange(MAX_V*2);
	
	K2400.setVoltageCompliance(MAX_V); // max 
	K2400.setCurrentCompliance(MAX_I/MILI);
	K2400.setCurrent(0);
	delay(0.1);
	K2400.activate();
	
	 // on lit le courant et la tension, 
	var IV0 = K2400.readIV(); // on stock pour le metre en entete
	

		
	
		
	// *****************************************************	
		//we initialize the data object, and the plot object
		var data = new SData2D();
		var plot = new SPlot2D();
		plot.setTitle("R(V):  H = "  + (149.35*V_H+0.08).toString() + " Oe");
		plot.setWindowTitle("R(V):  H = "  +(149.35*V_H+0.08).toString()  + " Oe");
		plot.show(); 

		
	// *****************************************************	
		//we initialize the field
		/*DAQ.sweep(fieldMin  , fieldDv, CHAN);
		DAQ.sweep(fieldMax  , fieldDv, CHAN);
		DAQ.sweep(V_H  , fieldDv, CHAN);*/
		DAQ.sweep(0 , fieldDv, CHAN);
		
	// *****************************************************	
		// put all varibles of the loop at zero
		var V     = voltageMin;
		var loop  = 0;
	// *****************************************************
		// we do the first half currentMin -> 0
		loop=0;
		while(V < 0-voltageInterval){
			V = stepVoltage(voltageMin, 0-voltageInterval, loop);	
			oneVoltagePoint(data, plot, K2400, V);
			loop++;
		}
		
	//// *****************************************************
		// we do the first half currentMin -> 0
		loop=0;
		while(V < voltageMax){
			V = stepVoltage(0+voltageInterval, voltageMax, loop);	
			oneVoltagePoint(data, plot, K2400, V);
			loop++;
		}
		
	// *****************************************************
		// we do the second half currentMax -> currentMin
		// put all varibles of the loop at zero
		loop =0;		
		while(V> 0+voltageInterval){
			V = stepVoltage(voltageMax,0+voltageInterval, loop);	
			oneVoltagePoint(data, plot, K2400, V) ;
			loop++;
		}
		
		loop =0;		
		while(V> voltageMin){
			V = stepVoltage(0-voltageInterval, voltageMin, loop);	
			oneVoltagePoint(data, plot, K2400, V) ;
			loop++;
		}
		
		
		
		data.setColName("V","R");
		data.setColUnit("V","Ohms");
		data.addComment("R(V) avec Mode source de tension")	;
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
		data.setMetaData("field"			, 149.35*V+0.08);		
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
		myName = name+ "." + EXT;
		
		myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
		myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
		myName = myName.replace("%V_H",	FixFloatToStr(V_H,1,2)) ;
		
		data.saveFile(path + "/" +BASE_NAME + myName)
		print(myName + " is saved.");
		plot.hide();
		/*delete plot;
		delete data;*/
	
	
	K2400.setVoltage(0);
	delay(0.1);
	K2400.deactivate();     
	delay(0.1);
	K2400.enableLocal();
	DAQ.sweep(0, fieldDv, CHAN) ;
	if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;



		