#pragma once
#include <QtCore>
#include <QtGui>
#include "GeneratedFiles/Ui_SUiCpPSGE8257D.h"
#include "SDevicePSGE8257D.h"

class SUiCpPSGE8257D :
	public QWidget,
	public Ui_SUiCpPSGE8257D
{
	Q_OBJECT;

public:
	SUiCpPSGE8257D(QWidget * parent = NULL );
	~SUiCpPSGE8257D(void);

private slots:
	void on_cmdMwOnOff_clicked(bool checked );
	void on_dsbMwPower_editingFinished();
	void on_dsbMwFreq_editingFinished();

	void on_dsbMwPower_valueChanged(double d);
	void on_dsbMwFreq_valueChanged(double d);
	void on_dsbMwPowerLimit_editingFinished();

	void on_cmdMwGo_clicked();

private:
	SDevicePSGE8257D * PSGE;
	QString SUiCpPSGE8257D::hearderMsgFormat( QString msg, QColor color );
};

