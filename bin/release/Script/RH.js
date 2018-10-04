/*******************************************************************************
* Title : 	RH.js
* Autor :	Sylvain Martin
* Brief : 	example script that do a R(H) curve, the first part defines some constant, 
* 		the seconde the parametres of the measurment, and the last one do the it.
* Version :	1.0.4
*********************************************************************************/

/*********************************************************************************
*                                                 CONSTANTE
**********************************************************************************/
	const    AP 		= 	-6	; //Volt command of the Kepco
	const    P 			= 	6	; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
	const    MAX_I 		= 	0.020	; //A
	const    MAX_V 		= 	0.500	; //V
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
	const    fieldInterval	= 	0.01	; // must be greater than 0.001
	const    fieldDv		=	0.5	; 
	
	const    currentStart 	=	-1	; //mA
	const    currentStop	=	-20	; //mA	
	const    currentInterval=	-1	; //mA

	const    technician		= "Sylvain MARTIN"	
	const    serieName		= "CCP.BTF5HJ"	
	const    sampleName		= "#4alpha";
	const    junctionLineName	= "f";
	const    junctionColName	= "II";
	const    junctionTypeName    = "2C";
	
	const    junctionName		=  junctionColName + 
						junctionLineName + 
						junctionTypeName;
						
	const    studyName		= nowTime("mmhh");					
						
	const    name			= "%DATE%_%ImA";
	const    folder			= "data/" + serieName + "/" + 
						   nowDate("yyyyMMdd")+ "/" +
						    junctionName + "/" + studyName;
						    
	const    path			= DATA_PATH + "/" + folder;
	
	const    cmt			= "avec bouclier circulaire";
/********************************************************************************
*                                                Functions
**********************************************************************************/
// does one point of H, sweep the field, does the measurment, and add the result to the data
function oneFieldPoint(data_, plot_, DAQ, H) {
	
			DAQ.sweep(H  , fieldDv, CHAN);
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
		var curentNbPoint =  Math.abs((currentStop - currentStart)/currentInterval);
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
	K2400.setMode(SDeviceK2400.CURRENT);
	K2400.setCurrentRange(MAX_I*2);  //range
	K2400.voltageRange(MAX_V*2);
	
	K2400.setVoltageCompliance(MAX_V); // max 
	K2400.setCurrentCompliance(MAX_I);
	K2400.setCurrent(0);
	K2400.activate();
	
	 // on lit le courant et la tension, 
	var VI0 = K2400.readVI(); // on stock pour le metre en entete
	
	for(var j=0 ; j<curentNbPoint ; j++){    //current loop
		
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
		//we initialize the field
		DAQ.sweep(fieldInit  , fieldDv, CHAN);
		delay(0.5);
		DAQ.sweep(fieldStart, fieldDv, CHAN);
		delay(0.5);
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
		
		data.setColName("H","R");
		data.setColUnit("Vc","Ohms");
		data.addComment("R(H) avec Mode source de courant")	;
		data.addComment(cmt);		
		data.setMetaData("I", I*MILI);	
		data.setMetaData("V0", VI0[0]*MILI);	
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
		
		data.setMetaData("date"	, nowDate("dd/mm/yyyy"));
		data.setMetaData("time"	, nowTime("hh-mm-ss"));
		
		var myName = "";
		myName = name+ "." + EXT;
		
		myName = myName.replace("%DATE%",nowDate("yyyyMMdd")) ;
		myName = myName.replace("%TIME%",nowTime("hh-mm-ss")) ;
		myName = myName.replace("%I",	FixFloatToStr(I*MILI,2,2)) ;
		
		data.saveFile(path + "/" +BASE_NAME + myName)
		print(myName + " is saved.");
		plot.hide();
		delete plot;
		delete data;
	}// fin boucle courant
	
	DAQ.sweep(fieldFinal, fieldDv, CHAN) ;
	K2400.setCurrent(0);
	K2400.deactivate();
	
	if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;



		