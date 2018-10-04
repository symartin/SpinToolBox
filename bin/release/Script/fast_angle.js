/*******************************************************************************
* Title : 	fast_angle.js
* Autor :	Sylvain Martin
* Brief : 	
* Version :	1.0.2
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
	
/*********************************************************************************
*                                                 PARAMETERS
**********************************************************************************/
// preparation (without measurement) zero -> fieldInit -> fieldStart
// fieldStart -> fieldMax -> fieldStart -> fieldMin -> fieldStart
// preparation (without measurement) fieldStart -> fieldFinal

	const    fieldInit		= 	P	; // usually P or AP	
	const    fieldMax		= 	P	; // usually P or AP
	const    fieldMin		= 	AP	; // usually P or AP	
	const    fieldStop	= 	ZERO	; // usually Zero
	const    fieldDv		=	0.5	; 
	
	const    current	 	=	-1	; //mA

	const    technician		= "Sylvain MARTIN"	
	const    serieName		= "CCP.BTF5HJ"	
	const    sampleName		= "#4alpha";
	const    junctionLineName	= "f";
	const    junctionColName	= "II";
	const    junctionTypeName    = "2D";
	
	const    angle			= "015.0";
	const    angleManip		= "335.0"
	
	const    junctionName		=  junctionColName + 
						junctionLineName + 
						junctionTypeName;
						
	const    studyName		= "angle 002" 					
						
	const    name			= "%DATE%_" + angle.toString()+ "Deg_%ImA";
	const    folder			= "data/" + serieName + "/" + 
						   nowDate("yyyyMMdd")+ "/" +
						    junctionName + "/" + studyName;
						    
	const    path			= appPath + "/" + folder;
	
	const    cmt			= "avec bouclier circulaire";
	
	const    tabH 			= new Array(3,6,-3,-6);
	const    tabR			= new Array();
/********************************************************************************
*                                                Functions
**********************************************************************************/
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
	if(Math.abs(H) > MAX_I*MILI){
		warningMsgBox("Protection echantillon (courant start trop fort) : " 
					+ currentStart.toString(), "R(H)");
		stop();
	}
	
	for(var H in tabH){
		if(Math.abs(current) > fieldMax){
			warningMsgBox("Protection bobine (une champ trop fort est demandé) : " 
					+ currentStart.toString(), "fast_angle");
			stop();
		}
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
	
	// we set the current
	K2400.setCurrent(current/MILI);	
	
	// *****************************************************	
	//we initialize the field
	DAQ.sweep(fieldInit  , fieldDv, CHAN);
	delay(1);
	DAQ.sweep(0, fieldDv, CHAN);
	delay(1);
	for(var H in tabH){
		
		DAQ.sweep(H  , fieldDv, CHAN);
		delay(1);
		var VI = K2400.readVI(); // on stock pour le metre en entete
		R = VI[0]/VI[1];
		tabR.push(R);
	}
	
	var stringR = "";
	for(var R in tabR){
		stringR +=  R.toString() + "\t";

	}
	
	print(angleManip,"\t",angle,"\t",stringR);
	