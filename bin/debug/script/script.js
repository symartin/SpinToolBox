if(K2400.available){
		K2400.setCurrentLimit(0.01);
		delay(0.1);
		K2400.setVoltageLimit(1.0);
		K2400.setVoltageCompliance(1.0);
		delay(0.1);

		delay(0.1);
		K2400.activate();

		var res = new Array(2)
		K2400.setMode(SDeviceK2400.VOLTAGE);
		K2400.setVoltage(0.001);
		res = K2400.readIV();
		debug("V : " ,res[1]*1000, " mV");
		debug("I : " ,res[0]*1000, " mA");
		debug("R : " , res[1]/res[0]);

		var res2 = new Array(2)
		K2400.setMode(SDeviceK2400.CURRENT);
		K2400.setCurrent(0.001);
		res2 = K2400.readVI();
		debug("V : " ,res2[0]*1000, " mV");
		debug("I : " ,res2[1]*1000, " mA");
		debug("R : " , res2[0]/res2[1]);

		delay(0.1);
		K2400.deactivate();
		delay(0.1);
		K2400.enableLocal(); 
}
	    
    
if(PSAE4440A.available){
	PSAE4440A.setRefLevel(-70.0);
	PSAE4440A.setAttenuation(2);
	PSAE4440A.setNbAverage(0);
	PSAE4440A.setFreqStart(1.0);
	PSAE4440A.setFreqStop(5);
	PSAE4440A.setRbw(0.5);

	PSAE4440A.restart();

	var data = new SData2D;
	data = PSAE4440A.qsReadSpectrum();
	data.saveFile("D:\\Sylvain\\Instru\\SpinToolBox\\test.spectre.stb");
}

//test !!!
for (i=1; i<=100; i++){
	delay(1);  
	debug(i);
   }
    
var data2 = new SData2D;
data2.openFile("D:\\Sylvain\\Instru\\SpinToolBox\\test.spectre.stb");
var plot = new SPlot2D();
plot.setData(data2);
plot.show();