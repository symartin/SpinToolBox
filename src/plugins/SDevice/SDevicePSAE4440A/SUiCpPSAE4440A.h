#pragma once



#include "GeneratedFiles\ui_SUiCpPSAE4440A.h"
#include "SDevicePSAE4440A.h"
#include <QtCore>
#include <QtGui>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SUiCpPSAE4440A
///
/// \brief	it is the class that manage the control panel of the Agilent PSA E4440A.
///
/// \ingroup SDeviceMod
/// 
/// \author	Sylvain Martin
/// \date	01/03/2012
/// 			
/// \sa SDevicePSAE4440A	
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
class SUiCpPSAE4440A :
	public QWidget,
	public Ui_SUiCpPSAE4440A
{
	Q_OBJECT;
public:
	SUiCpPSAE4440A(QWidget * parrent = NULL);
	~SUiCpPSAE4440A(void);

	private slots:
		void on_dsbSaStopFreq_valueChanged(double d);
		void on_dsbSaStartFreq_valueChanged(double d);
		void on_dsbSaRbw_valueChanged(double d);
		void on_cmdSaCheckRbw_clicked();
		void on_cmdSaAskRbw_clicked();


		void on_dsbSaAverage_valueChanged(int i); //!
		void on_dsbSaNbPoints_valueChanged(int i); //!

		void on_dsbSaLevel_valueChanged(double d);
		void on_cmbxSaAttenuation_currentIndexChanged( const QString & text );
		void on_chkbxSaMarkerOnOff_stateChanged(int state );

		void on_chkbxSaLog_stateChanged(int state );
		void on_dsbSaMarker_valueChanged(double d);
		void on_sldSaMarker_sliderMoved (int d);
		void on_cmdSaMax_clicked();

		void on_cmdSaGo_clicked();

		void on_cmdSaTargetFolder_clicked();
		void on_cmdSaMeasure_clicked();

private:
	QString hearderMsgFormat( QString msg, QColor color );
	void delay(double i) ;
	SDevicePSAE4440A * PSA;
	SGlobalMetaDataMap gmdm;
};