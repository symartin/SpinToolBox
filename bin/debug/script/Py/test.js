/*********************************************************************************/

/*********************************************************************************
*                                                 CONSTANTE
**********************************************************************************/
	const    AP 		= 	-6	; //Volt command of the Kepco
	const    P 			= 	6	; //Volt command of the Kepco
	const    ZERO 		= 	0	; //Volt command of the Kepco
	const    MAX_I 		= 	0.001	; //mA
	const    MAX_V 		= 	1.2	; //V
	const    BASE_NAMEIX		= 	"test_ "; //prefix of the name
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
	const    V_H               =     0.7	;//between -8 and 8
	const    H0                   = 149.35*V_H+0.08;
	const    round_H          =Math.round(H0);

/*********** K2400 Parameters ************/
	const    currentMin      =      -0.00110  ;//mA
	const    currentMax      =      0.00110 ;//mA
	const    currentInterval =      0.00001      ;//mA
	const    current 	        =	0.001/MILI   ; //mA

/*********** Lock-in Parameters ************/
	const    frequency  = 1000; //Hz
	const    amplitude  = 5*currentInterval/(2*MILI)*R_0; //V 

/*********** Storage Parameters ************/
	const    technician		= "PY"	
	const    serieName		= "DBMTJ"	
	const    sampleName		= "P901";
	const    junctionLineName	= "4";
	const    junctionColName	= "3";
	const    junctionTypeName    = "C4J5";
	const    mesure                   = "105 Oe";
	const    mode                     = "dVdI";  
	const    cmt			= "";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= "2013_08_21";					
						
	const    name			= "";
	
	const    folder			= serieName + "\\"
						+ sampleName + "\\"
						+ studyName + "\\"
						+ junctionName + "\\"
						+ mesure + "\\";
						    
	const    path			= DATA_PATH + "\\" + folder;

function oneDataPoint(dataIX_,dataIY_,dataIR_,dataITheta_, dataIdVdI_, plotIdVdI_, K2400, I) {
	
			K2400.setCurrent(I/MILI);
			delay(0.01); 
			var VI = K2400.readVI(); 
			
			
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

// first set up of the  Keithley 2400 
	K2400.setMode(mode);
	K2400.setCurrentRange(0.001/MILI);  //range
	K2400.setVoltageRange(2*MAX_V);
	
	K2400.setVoltageCompliance(MAX_V); // max 
	K2400.setCurrentCompliance(2*MAX_I/MILI);
	K2400.setCurrent(0);
	delay(0.1);
	K2400.activate();

// Initialisation des variables
		const near0_step=1;
		var I     = 0+near0_step*currentInterval;
		var loop  = 0;
	// *****************************************************
		// 0 -> CurrentMax
			loop=0;
			while(I < currentMax){
				I = stepCurrent(0+near0_step*currentInterval, currentMax, loop);	
				oneDataPoint(dataIX, dataIY, dataIR, dataITheta, dataIdVdI, plotIdVdI, K2400, I);
				loop++;
			}
			
			K2400.setCurrent(0);
delay(0.1);
K2400.deactivate();     
delay(0.1);
K2400.enableLocal(); // Local K2400
SR830.setAmplitude(mini);
//RAZ du champ			
DAQ.sweep(0, fieldDv, CHAN) ;
if(FIELD_0_END) DAQ.sweep(0, fieldDv, CHAN) ;