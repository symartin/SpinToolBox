/*******************************************************************************
* Title : 	RH.js
* Autor :	Sylvain Martin
* Brief : 	example script that do a R(H) curve, the first part defines some constant, 
* 		the seconde the parametres of the measurment, and the last one do the it.
* Version :	1.1.0
*********************************************************************************/

/*********************************************************************************
* Change log :
* 	v1.10 :
*	     - bug fix save path
*
*
*
**********************************************************************************/
/*********************************************************************************
*                                                 CONSTANTE
**********************************************************************************/
	const    AP 		= 	-8	; //Volt command of the Kepco
	const    P 			= 	8	; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
	const    MAX_I 		= 	0.020	; //A
	const    MAX_V 		= 	1.500	; //V
	const    BASE_NAME	= 	"RH_"; //prefix of the name
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
	const    fieldInterval	= 	0.1	; // must be bigger than 0.001
	const    fieldDv		=	0.5	; 
	
	const    voltageStart 	=	100	; //mV
	const    voltageStop	=	100	; //mV	
	const    voltageInterval=	50	; //mV

	const    technician		= "PY"	
	const    serieName		= "SBMTJ"	
	const    sampleName		= "D641";
	const    junctionLineName	= "6";
	const    junctionColName	= "5";
	const    junctionTypeName    = "D6J1";
	const    mode                     = "Voltage";
	const    preparation             = "preparation2";  	
	
	const    junctionName		=  junctionColName + 
						junctionLineName + 
						junctionTypeName;
						
	const    studyName		= "2013_03_07";					
						
	const    name			= "";
	const    folder			= serieName + "\\"
						+ sampleName + "\\"
						+ studyName + "\\"
						+ junctionName + "\\"
						+ mode + "\\" 
						+ preparation + "\\"
						+ "100mV" + "\\";
						    
	const    path			= DATA_PATH + "/" + folder;
	
	const    cmt			= " ";
/********************************************************************************
*                                                Functions
**********************************************************************************/
// does one point of H, sweep the field, does the measurment, and add the result to the data
function oneFieldPoint(data_, plot_, DAQ, H) {
	
			DAQ.sweep(H  , fieldDv, CHAN);
			delay(0.2); // because without that, the field is not stable
			var IV = K2400.readIV(); // on stock pour le metre en entete
		

			R = IV[1]/IV[0];
			data_.append(H,R);
			plot_.append(H,R);
			plot_.autoScale();
}
// Increment or decrement the field depending on
// the start point, stop point and the index of the loop
function stepField(start, stop, loop){
	if(start == stop){
		return fieldMax;
	}else{
		if(start < stop){		
			return Math.round( (start + loop*fieldInterval)*10000)/10000;
		}else{
			return Math.round( (start - loop*fieldInterval)*10000)/10000;
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

	// the number of points ***********************************
	if(voltageInterval == 0){
		voltageNbPoint =0;
	}else{
		var voltageNbPoint =  Math.abs((voltageStop - voltageStart)/voltageInterval)+1;
	}
	if(voltageNbPoint == 0){ // currentStop ==  currentStart
		voltageNbPoint = 1; 
	}else if(Math.abs(voltageNbPoint)*voltageInterval >  Math.abs(voltageStop)){
		voltageNbPoint -= 1;
	}
	

	
	// currentStart safety  *********************************
	if(Math.abs(voltageStart/MILI) > MAX_V){
		warningMsgBox("Protection echantillon (voltage start trop fort) : " 
					+ voltageStart.toString(), "R(H)");
		stop();
	}
	//  currentStop safety  *********************************
	if(Math.abs(voltageStop/MILI) > MAX_V){
		warningMsgBox("Protection echantillon (voltage stop trop fort) : "  +
					voltageStop.toString(), "R(H)");
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
	K2400.activate();
	
	 // on lit le courant et la tension, 
	//var VI0 = K2400.readVI(); // on stock pour le metre en entete

	//we initialize the field
	DAQ.sweep(fieldInit  , fieldDv, CHAN); //->Hmax
	delay(0.5);
	DAQ.sweep(fieldStart, fieldDv, CHAN);//->H=0
	delay(0.5);
	DAQ.sweep(fieldMin, fieldDv, CHAN);//->Hmin
	delay(0.5);


	for(var j=0 ; j<voltageNbPoint ; j++){    //current loop
		
	// *****************************************************		
		K2400.setVoltage(0);

	// *****************************************************		
		
		if(voltageNbPoint == 1){
			var V = voltageStart/MILI;
		}else{
			var V  = (voltageStart+ j*voltageInterval)/MILI;
		}

		// we set the current
		K2400.setVoltage(V);
		
	// *****************************************************	
		//we initialize the data object, and the plot object
		var data = new SData2D();
		var plot = new SPlot2D();
		plot.setTitle("R(H):  V = "  + (V*MILI).toString() + " mV");
		plot.setWindowTitle("R(H):  V = "  +(V*MILI).toString()  + " mV");
		plot.show(); 

		
	
	// *****************************************************	
		// put all varibles of the loop at init
		var H     = fieldMin;
		var loop  = 0;
	// *****************************************************
		// we do the first quarter 	fieldMin -> fieldStart
		while(H < fieldMax){
			H = stepField(fieldMin, fieldMax, loop);	
			oneFieldPoint(data, plot, DAQ, H);
			loop++;
		}
		
	// *****************************************************
		// we do the seconde quarter fieldStart -> fieldMax
		// put all varibles of the loop at zero
		loop =0;		
		while(H > fieldMin){
			H = stepField(fieldMax,fieldMin, loop);	
			oneFieldPoint(data, plot, DAQ, H) ;
			loop++;
		}
	/*	
	// *****************************************************
		// we do the seconde quarter  fieldMax ->  fieldStart
		// put all varibles of the loop at zero
		loop =0;		
		while(H > fieldStart){
			H = stepField(fieldMax,fieldStart, loop);	
			oneFieldPoint(data, plot, DAQ, H) ;
			loop++;
		}
		
		// *****************************************************
		// we do the seconde quarter  fieldStart ->  fieldMin
		// put all varibles of the loop at zero
		loop =0;		
		while(H > fieldMin){
			H = stepField(fieldStart, fieldMin, loop);	
			oneFieldPoint(data, plot, DAQ, H) ;
			loop++;
		}
		*/
		
		data.setColName("H","R");
		data.setColUnit("Vc","Ohms");
		data.addComment("R(H) avec Mode source de courant")	;
		data.addComment(cmt);		
		data.setMetaData("V", V*MILI);	
		//data.setMetaData("V0", IV0[0]*MILI);	
		data.setMetaData("fieldStart"		, fieldStart);	
		data.setMetaData("fieldInit"		, fieldInit);	
		data.setMetaData("fieldMax"		, fieldMax);	
		data.setMetaData("fieldStop"		, fieldStop);	
		data.setMetaData("fieldFinal"		, fieldFinal);	
		data.setMetaData("fieldInterval"	, fieldInterval);
		data.setMetaData("fieldDv"		, fieldDv);		
		
		data.setMetaData("voltageStart"	, voltageStart);	
		data.setMetaData("voltageStop"		, voltageStop);	
		data.setMetaData("voltageInterval"	, voltageInterval);
		
		data.setMetaData("sampleName"		, sampleName);	
		data.setMetaData("junctionLineName"	, junctionLineName);	
		data.setMetaData("junctionColName"	, junctionColName);
		data.setMetaData("junctionTypeName"	, junctionTypeName);	
		data.setMetaData("junctionName"	, junctionName);	
		data.setMetaData("serieName"		, serieName);		

		data.setMetaData("technician"		, technician);	
		
		data.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		data.setMetaData("time"	, nowTime("hh-mm-ss"));
		
		var myName = "";
		myName = name+ "." + EXT;
		
		myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
		myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
		myName = myName.replace("%V",	FixFloatToStr(V*MILI,2,0)) ;
		
		data.saveFile(path + "/" +BASE_NAME + myName)
		print(myName + " is saved.");
		plot.hide();
		
		K2400.setVoltage(0);
		
/*	// *****************************************************	
		//we initialize the field
		DAQ.sweep(fieldInit  , fieldDv, CHAN);
		delay(0.5);
		DAQ.sweep(fieldStart, fieldDv, CHAN);
		delay(0.5);    
		
		// we set the current
		K2400.setVoltage(-V);
		
	// *****************************************************	
		//we initialize the data object, and the plot object
		var data = new SData2D();
		var plot = new SPlot2D();
		plot.setTitle("R(H):  V = "  + (-V*MILI).toString() + " mV");
		plot.setWindowTitle("R(H):  V = "  +(-V*MILI).toString()  + " mV");
		plot.show(); 

		
	
	// *****************************************************	
		// put all varibles of the loop at zero
		var H     = 0.0;
		var loop  = 0;
	// *****************************************************
		// we do the first quarter 	fieldStart -> fieldMax
		while(H < fieldMax){
			H = stepField(fieldStart, fieldMax, loop);	
			oneFieldPoint(data, plot, DAQ, H);
			loop++;
		}
		
	// *****************************************************
		// we do the seconde quarter fieldMax -> fieldStart
		// put all varibles of the loop at zero
		loop =0;		
		while(H > fieldStart){
			H = stepField(fieldMax,fieldStart, loop);	
			oneFieldPoint(data, plot, DAQ, H) ;
			loop++;
		}
		
	// *****************************************************
		// we do the seconde quarter  fieldStart ->  fieldMin
		// put all varibles of the loop at zero
		loop =0;		
		while(H > fieldMin){
			H = stepField(fieldStart,fieldMin, loop);	
			oneFieldPoint(data, plot, DAQ, H) ;
			loop++;
		}
		
		// *****************************************************
		// we do the seconde quarter  fieldStart ->  fieldMin
		// put all varibles of the loop at zero
		loop =0;		
		while(H < fieldStart){
			H = stepField(fieldMin, fieldStart, loop);	
			oneFieldPoint(data, plot, DAQ, H) ;
			loop++;
		}
		
		// *****************************************************
		// we do the seconde quarter  fieldStart ->  fieldMax
		// put all varibles of the loop at zero
		loop =0;		
		while(H < fieldMax){
			H = stepField(fieldStart, fieldMax, loop);	
			oneFieldPoint(data, plot, DAQ, H) ;
			loop++;
		}
		
		
		data.setColName("H","R");
		data.setColUnit("Vc","Ohms");
		data.addComment("R(H) avec Mode source de courant")	;
		data.addComment(cmt);		
		data.setMetaData("V", -V*MILI);	
		//data.setMetaData("V0", IV0[0]*MILI);	
		data.setMetaData("fieldStart"		, fieldStart);	
		data.setMetaData("fieldInit"		, fieldInit);	
		data.setMetaData("fieldMax"		, fieldMax);	
		data.setMetaData("fieldStop"		, fieldStop);	
		data.setMetaData("fieldFinal"		, fieldFinal);	
		data.setMetaData("fieldInterval"	, fieldInterval);
		data.setMetaData("fieldDv"		, fieldDv);		
		
		data.setMetaData("voltageStart"	, voltageStart);	
		data.setMetaData("voltageStop"		, voltageStop);	
		data.setMetaData("voltageInterval"	, voltageInterval);
		
		data.setMetaData("sampleName"		, sampleName);	
		data.setMetaData("junctionLineName"	, junctionLineName);	
		data.setMetaData("junctionColName"	, junctionColName);
		data.setMetaData("junctionTypeName"	, junctionTypeName);	
		data.setMetaData("junctionName"	, junctionName);	
		data.setMetaData("serieName"		, serieName);		

		data.setMetaData("technician"		, technician);	
		
		data.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		data.setMetaData("time"	, nowTime("hh-mm-ss"));
		
		var myName = "";
		myName = name+ "." + EXT;
		
		myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
		myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
		myName = myName.replace("%V",	FixFloatToStr(-V*MILI,2,0)) ;
		
		data.saveFile(path + "/" +BASE_NAME + myName)
		print(myName + " is saved.");
		plot.hide();
		
		/*delete plot;
		delete data;*/     
	}// fin boucle courant
	
	K2400.setVoltage(0);
	DAQ.sweep(fieldFinal, fieldDv, CHAN) ;
	delay(0.1);
	K2400.deactivate();     
	delay(0.1);
	K2400.enableLocal();
	if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;



		