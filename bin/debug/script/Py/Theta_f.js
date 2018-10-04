/*******************************************************************************
* Title : 	dV/dI.js
* Autor :	Sylvain Martin
* Brief : 	dV/dI data+curve using Lock-in SR830
		devices : DAQ(field)/K2400(current or voltage source)/SR830 (Lock-in)
* Version :	1.0.0
*********************************************************************************/

/*********************************************************************************
*                                                 CONSTANTE
**********************************************************************************/
	const    BASE_NAMEfX		= 	"fX_ "; //prefix of the name
	const    BASE_NAMEfY		= 	"fY_ ";
	const    BASE_NAMEfR		= 	"fR_ ";
	const    BASE_NAMEfTheta	=	"fTheta_ ";
	const    EXT	 	= 	"dat"; //extention
	const    MILI		=	1000	;
	const    DEBUG		=	1	;
	const    DATA_PATH    =      "D:\\Data"; // path of the data
	const    R_0		=	35470000 ; //Ohms, résistance de protection du lock-in
	const    mini		=	0.004 ; //V valeur minimale du lock-in
/*********************************************************************************
*                                                 PARAMETERS
**********************************************************************************/

/*********** K2400 Parameters ************/
	
	const    Current 	        =	0.001/MILI   ; //mA

/*********** Lock-in Parameters ************/

	const    amplitude  = 0.100; //2*currentInterval/(2*MILI)*R_0; //V 

/*********** Storage Parameters ************/
	const    technician		= "PY"	
	const    serieName		= "DBMTJ"	
	const    sampleName		= "test_R";
	const    junctionLineName	= "";
	const    junctionColName	= "";
	const    junctionTypeName    = "balayage_f";
	const    mesure                   = "";
	const    mode                     = "balayage_f";  
	const    cmt			= "";
	
	const    junctionName		=  junctionColName 
						+ junctionLineName 
						+ junctionTypeName;
						
	const    studyName		= "2013_09_10";					
						
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


function oneDataPoint(datafX_,datafY_,datafR_,datafTheta_, plotfTheta_, SR830, f) {
	
			SR830.setFrequency(f);
			//K2400.setAutoVoltageRange(false);
			//K2400.setVoltMeasRange(2);
			X  = SR830.X();
			Y  = SR830.Y();
			R  = 1.4142*SR830.R();
			Theta  = SR830.Theta();
			
	
	datafX_.append(f,X);
	datafY_.append(f,Y);
	datafR_.append(f,R);
	datafTheta_.append(f,Theta);
	plotfTheta_.autoScale();
	
	//delay();
			
}

function stepFrequency1(start, stop, loop){
	if(start == stop){
		return 10;
	}else{
		if(start < stop){		
			return Math.round( (start + loop*1)*100000000)/100000000;
		}else{
			return Math.round( (start - loop*1)*100000000)/100000000;
		}
	}	
}

function stepFrequency10(start, stop, loop){
	if(start == stop){
		return 10;
	}else{
		if(start < stop){		
			return Math.round( (start + loop*10)*100000000)/100000000;
		}else{
			return Math.round( (start - loop*10)*100000000)/100000000;
		}
	}	
}

function stepFrequency100(start, stop, loop){
	if(start == stop){
		return 10;
	}else{
		if(start < stop){		
			return Math.round( (start + loop*100)*100000000)/100000000;
		}else{
			return Math.round( (start - loop*100)*100000000)/100000000;
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

function Abs(x){
if (x>=0) { return x;}
else{
	if (x<0){ return -x;}
	}
}
/*********************************************************************************
*					SAFETY
**********************************************************************************/

	
	// Keithley 2400 ok? ************************************
	if(!K2400.available){
		warningMsgBox("The Keithley 2400 is not available.", "R(H)");
		stop();
	}
	/*// DAQ ok? ************************************
	if(!DAQ.available){
		warningMsgBox("The DAQ card is not available.", "R(H)");
		stop();
	}
*/
/*********************************************************************************
					DO IT
**********************************************************************************/	
	
	
	//clear the log output
	clear();
	print("work folder : " + path);
	
	// first set up of the  Keithley 2400 
	K2400.setMode(mode);
	
	K2400.setCurrentRange(0.01/MILI);  //range
	K2400.setVoltageRange(2);
	
	K2400.setVoltageCompliance(2); // max 
	K2400.setCurrentCompliance(1/MILI);
	
	
	
	K2400.setCurrent(0);
	delay(0.1);
	K2400.activate();
	K2400.setCurrent(Current);


// *****************************************************
/****** Paramètrage du lock-in *******/
	SR830.setAmplitude(amplitude);
		// Balayage en frequance
		
		//Initialisation des tableaux de datas
		var datafX = new SData2D();
		var datafY = new SData2D();
		var datafR = new SData2D();
		var datafTheta = new SData2D();
		var plotfTheta = new SPlot2D();
		
		plotfTheta.setTitle("Déphasage(f) : I = "  + (Current).toString() );
		plotfTheta.setWindowTitle("Déphasage(f) : I = "  +(Current).toString()  );
		plotfTheta.show(); 
		
		// Initialisation des variables
		var f     = 1
		var loop  = 0;
	// *****************************************************
		// 1 -> 100
		
			loop=0;
			while(f < 100){
				f = stepFrequency1(1, 100, loop);	
				oneDataPoint(datafX,datafY,datafR,datafTheta, plotfTheta, SR830, f);
				delay(5);
				loop++;
			}
			
			
		
	// *****************************************************
		// 100 -> 1000
		
		loop =0;		
		while(f < 1000){
			f = stepFrequency10(100,1000, loop);	
			oneDataPoint(datafX,datafY,datafR,datafTheta, plotfTheta, SR830, f);
			delay(1);
			loop++;
		}
		
		
		
		
		
	// *****************************************************
		// 1000 -> 10000
		loop =0;		
		while(f < 10000){
			f = stepFrequency100(1000, 10000, loop);	
			oneDataPoint(datafX,datafY,datafR,datafTheta, plotfTheta, SR830, f);
			delay(1);
			loop++;
		}
		

		
	/*************************Enregistrement data*****************************/
		
		/***** Theta *****/
			 
		datafTheta.setColName("f","Theta");
		datafTheta.setColUnit("Hz","degrés");
		datafTheta.addComment("Theta = arctan(Y/X)")	;
		datafTheta.addComment(cmt);	
		datafTheta.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		datafTheta.setMetaData("studyName"		, studyName);	
		datafTheta.setMetaData("sampleName"		, sampleName);	
		datafTheta.setMetaData("junctionLineName"	, junctionLineName);	
		datafTheta.setMetaData("junctionColName"	, junctionColName);
		datafTheta.setMetaData("junctionTypeName"	, junctionTypeName);	
		datafTheta.setMetaData("junctionName"	, junctionName);	
		datafTheta.setMetaData("serieName"		, serieName);		
		datafTheta.setMetaData("technician"		, technician);	
		datafTheta.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		datafTheta.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNamefTheta = "";
		myNamefTheta = name+ "." + EXT;
		
		myNamefTheta = myNamefTheta.replace("%Current", FixFloatToStr(Current,1,0)) ;
		
		datafTheta.saveFile(path + "/" +BASE_NAMEfTheta+ myNamefTheta)
		print(myNamefTheta + " is saved.");
			
			/***** X *****/
			
		datafX.setColName("f","X");
		datafX.setColUnit("Hz","V");
		datafX.addComment("X = V_signal cos(dephasage)")	;
		datafX.addComment(cmt);
		datafX.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		datafX.setMetaData("studyName"		, studyName);	
		datafX.setMetaData("sampleName"		, sampleName);	
		datafX.setMetaData("junctionLineName"	, junctionLineName);	
		datafX.setMetaData("junctionColName"	, junctionColName);
		datafX.setMetaData("junctionTypeName"	, junctionTypeName);	
		datafX.setMetaData("junctionName"	, junctionName);	
		datafX.setMetaData("serieName"		, serieName);		
		datafX.setMetaData("technician"		, technician);	
		datafX.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		datafX.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNamefX = "";
		myNamefX = name+ "." + EXT;
		
		myNamefX = myNamefX.replace("%Current", FixFloatToStr(Current,1,0)) ;
		
		datafX.saveFile(path + "/" +BASE_NAMEfX+ myNamefX)
		print(myNamefX + " is saved.");
		
			/***** Y *****/
			
		datafY.setColName("f","Y");
		datafY.setColUnit("Hz","V");
		datafY.addComment("Y = V_signal sin(dephasage)")	;
		datafY.addComment(cmt);
		datafY.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		datafY.setMetaData("studyName"		, studyName);	
		datafY.setMetaData("sampleName"		, sampleName);	
		datafY.setMetaData("junctionLineName"	, junctionLineName);	
		datafY.setMetaData("junctionColName"	, junctionColName);
		datafY.setMetaData("junctionTypeName"	, junctionTypeName);	
		datafY.setMetaData("junctionName"	, junctionName);	
		datafY.setMetaData("serieName"		, serieName);		
		datafY.setMetaData("technician"		, technician);	
		datafY.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		datafY.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNamefY = "";
		myNamefY = name+ "." + EXT;
		
		myNamefY = myNamefY.replace("%Current", FixFloatToStr(Current,1,0)) ;
		
		datafY.saveFile(path + "/" +BASE_NAMEfY+ myNamefY)
		print(myNamefY + " is saved.");
		
			/***** R *****/
			
		datafR.setColName("f","R");
		datafR.setColUnit("Hz","V");
		datafR.addComment("R = sqrt(X²+Y²)")	;
		datafR.addComment(cmt);	
		datafR.setMetaData("Lock-in Amplitude (V)"		, amplitude);	
		datafR.setMetaData("studyName"		, studyName);	
		datafR.setMetaData("sampleName"		, sampleName);	
		datafR.setMetaData("junctionLineName"	, junctionLineName);	
		datafR.setMetaData("junctionColName"	, junctionColName);
		datafR.setMetaData("junctionTypeName"	, junctionTypeName);	
		datafR.setMetaData("junctionName"	, junctionName);	
		datafR.setMetaData("serieName"		, serieName);		
		datafR.setMetaData("technician"		, technician);	
		datafR.setMetaData("date"	, nowDate("dd/MM/yyyy"));
		datafR.setMetaData("time"	, nowTime("hh:mm:ss"));
			
		var myNamefR = "";
		myNamefR = name+ "." + EXT;
		
		myNamefR = myNamefR.replace("%Current", FixFloatToStr(Current,1,0)) ;
		
		datafR.saveFile(path + "/" +BASE_NAMEfR+ myNamefR)
		print(myNamefR + " is saved.");
		
			
		
		
		
	/*************************************************************************/
	
K2400.setCurrent(0);
delay(0.1);
K2400.deactivate();     
delay(0.1);
K2400.enableLocal(); // Local K2400
SR830.setAmplitude(mini);
SR830.setFrequency(1);
		

	
	