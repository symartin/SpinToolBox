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
	const    P 			= 	8    ; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
	const    MAX_I 		= 	1	; //A
	const    MAX_V 		=	1.50; //V
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
	
	const    currentStart 	=	0.05	; //mA
	const    currentStop	=	0.05 ; //mA	
	const    currentInterval=	0.01; //mA

	const    technician		= "PY"	
	const    serieName		= "DBMTJ"	
	const    sampleName		= "P638";
	const    junctionLineName	= "2";
	const    junctionColName	= "2";
	const    junctionTypeName    = "C3J1";
	const    mode                     = "Current"; 
	const    preparation             = "preparation2";
        //const    excursion                = "-2.5_2.5";	
	
	const    junctionName		=  junctionColName + 
						junctionLineName + 
						junctionTypeName;
						
	const    studyName		= "2013_09_25";					
						
	const    name			= "%I";
	const    folder			= serieName + "\\"
						+ sampleName + "\\"
						+ studyName + "\\"
						+ junctionName + "\\"
						+ mode + "\\"
						+ preparation + "\\";
						    
	const    path			= DATA_PATH + "/" + folder;
	
	const    cmt			= " ";
/********************************************************************************
*                                                Functions
**********************************************************************************/
// does one point of H, sweep the field, does the measurment, and add the result to the data
function oneFieldPoint(data_, plot_, DAQ, H) {
	
			DAQ.sweep(H  , fieldDv, CHAN);
			delay(0.2); // because without that, the field is not stable
			var VI = K2400.readVI(); // on stock pour le metre en entete
	

			R = VI[0]/VI[1];
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
	if(currentInterval == 0){
		curentNbPoint =0;
	}else{
		var curentNbPoint =  Math.abs((currentStop - currentStart)/currentInterval)+1;
	}
	if(curentNbPoint == 0){ // currentStop ==  currentStart
		curentNbPoint = 1; 
	}else if(Math.abs(curentNbPoint)*currentInterval >  Math.abs(currentStop)){
		curentNbPoint -= 1;
	}
	
	
	// currentStart safety  *********************************
	if(Math.abs(currentStart) > MAX_I*MILI){
		warningMsgBox("Protection echantillon (courant start trop fort) : " 
					+ currentStart.toString(), "R(H)");
		stop();
	}
	//  currentStop safety  *********************************
	if(Math.abs(currentStop) > MAX_I*MILI){
		warningMsgBox("Protection echantillon (courant stop trop fort) : "  +
					currentStop.toString(), "R(H)");
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
	K2400.setCurrentRange(1/MILI);  //range
	K2400.voltageRange(MAX_V*2);
	
	K2400.setVoltageCompliance(MAX_V); // max 
	K2400.setCurrentCompliance(10/MILI);
	K2400.setCurrent(0);
	K2400.activate();
	
	 // on lit le courant et la tension, 
	//var VI0 = K2400.readVI(); // on stock pour le metre en entete
	
	// *****************************************************	
		//we initialize the field
		DAQ.sweep(fieldInit  , fieldDv, CHAN); //->Hmax
		delay(0.5);
		DAQ.sweep(fieldStart, fieldDv, CHAN);//->H=0
		delay(0.5);
		DAQ.sweep(fieldMin, fieldDv, CHAN);//->Hmin
		delay(0.5);
	
	for(var j=0 ; j<curentNbPoint ; j++){    //current loop
		
		K2400.setCurrent(0);
		
	// *****************************************************		
		if(curentNbPoint == 1){
			var I = currentStart/MILI;
		}else{
			var I  = (currentStart+ j*currentInterval)/MILI;
		}

		// we set the current
		K2400.setCurrent(I);
		
	// *****************************************************	
		//we initialize the data object, and the plot object
		var data = new SData2D();
		var plot = new SPlot2D();
		plot.setTitle("R(H):  I = "  + (I*MILI).toString() + " mA");
		plot.setWindowTitle("R(H):  I = "  +(I*MILI).toString()  + " mA");
		plot.show(); 

	// *****************************************************	
		// put all varibles of the loop at zero
		var H     = fieldMin;
		var loop  = 0;
	// *****************************************************
		// we do the first quarter 	fieldMin -> fieldStart
		while(H < fieldStart){
			H = stepField(fieldMin, fieldStart, loop);	
			oneFieldPoint(data, plot, DAQ, H);
			loop++;
		}
		
	// *****************************************************
		// we do the seconde quarter fieldStart -> fieldMax
		// put all varibles of the loop at zero
		loop =0;		
		while(H < fieldMax){
			H = stepField(fieldStart,fieldMax, loop);	
			oneFieldPoint(data, plot, DAQ, H) ;
			loop++;
		}
		
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
		
		
		data.setColName("H","R");
		data.setColUnit("Vc","Ohms");
		data.addComment("R(H) avec Mode source de courant")	;
		data.addComment(cmt);		
		data.setMetaData("I", I*MILI);	
		//data.setMetaData("V0", VI0[0]*MILI);	
		data.setMetaData("fieldStart"		, fieldStart);	
		data.setMetaData("fieldInit"		, fieldInit);	
		data.setMetaData("fieldMax"		, fieldMax);	
		data.setMetaData("fieldStop"		, fieldStop);	
		data.setMetaData("fieldFinal"		, fieldFinal);	
		data.setMetaData("fieldInterval"	, fieldInterval);
		data.setMetaData("fieldDv"		, fieldDv);		
		
		data.setMetaData("currentStart"	, currentStart*MILI);	
		data.setMetaData("currentStop"		, currentStop*MILI);	
		data.setMetaData("currentInterval"	, currentInterval*MILI);
		
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
		myName = myName.replace("%I",	FixFloatToStr(I*MILI,1,4)) ;
		
		data.saveFile(path + "/" +BASE_NAME + myName)
		print(myName + " is saved.");
		//plot.hide();
		
		K2400.setCurrent(0);
		
	
		/*K2400.setCurrent(-I);
		
		// *****************************************************	
		//we initialize the data object, and the plot object
		var data = new SData2D();
		var plot = new SPlot2D();
		plot.setTitle("R(H):  I = "  + (-I*MILI).toString() + " mA");
		plot.setWindowTitle("R(H):  I = "  +(-I*MILI).toString()  + " mA");
		plot.show(); 
		
	// *****************************************************	
		// put all varibles of the loop at zero
		var H     = fieldMin;
		var loop  = 0;
	// *****************************************************
		// we do the first quarter 	fieldMin -> fieldStart
		while(H < fieldStart){
			H = stepField(fieldMin, fieldStart, loop);	
			oneFieldPoint(data, plot, DAQ, H);
			loop++;
		}
		
	// *****************************************************
		// we do the seconde quarter fieldStart -> fieldMax
		// put all varibles of the loop at zero
		loop =0;		
		while(H < fieldMax){
			H = stepField(fieldStart,fieldMax, loop);	
			oneFieldPoint(data, plot, DAQ, H) ;
			loop++;
		}
		
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
		
		
		data.setColName("H","R");
		data.setColUnit("Vc","Ohms");
		data.addComment("R(H) avec Mode source de courant")	;
		data.addComment(cmt);		
		data.setMetaData("I", -I*MILI);	
		//data.setMetaData("V0", VI0[0]*MILI);	
		data.setMetaData("fieldStart"		, fieldStart);	
		data.setMetaData("fieldInit"		, fieldInit);	
		data.setMetaData("fieldMax"		, fieldMax);	
		data.setMetaData("fieldStop"		, fieldStop);	
		data.setMetaData("fieldFinal"		, fieldFinal);	
		data.setMetaData("fieldInterval"	, fieldInterval);
		data.setMetaData("fieldDv"		, fieldDv);		
		
		data.setMetaData("currentStart"	, currentStart*MILI);	
		data.setMetaData("currentStop"		, currentStop*MILI);	
		data.setMetaData("currentInterval"	, currentInterval*MILI);
		
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
		myName = myName.replace("%I",	FixFloatToStr(-I*MILI,1,2)) ;
		
		data.saveFile(path + "/" +BASE_NAME + myName)
		print(myName + " is saved.");
		plot.hide();
		/*delete plot;
		delete data;*/  
	}// fin boucle courant 
	   
	K2400.setCurrent(0);
	K2400.deactivate();
	delay(0.1);
	DAQ.sweep(fieldFinal, fieldDv, CHAN) ;   
	delay(0.1);
	K2400.enableLocal();
	if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;
  
		