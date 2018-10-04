#pragma once
#include <QtCore>
#include <QtGui>
#include "GeneratedFiles/Ui_SUiCpApsin20g.h"
#include "SDeviceApsin20g.h"

class SUiCpApsin20g :
	public QWidget,
	public Ui_SUiCpApsin20g
{
	Q_OBJECT;

public:
	SUiCpApsin20g(QWidget * parent = NULL );
	~SUiCpApsin20g(void);

private slots:
	void on_cmdMwOnOff_clicked(bool checked );
	void on_dsbMwPower_editingFinished();
	void on_dsbMwFreq_editingFinished();

	void on_dsbMwPower_valueChanged(double d);
	void on_dsbMwFreq_valueChanged(double d);
	void on_dsbMwPowerLimit_editingFinished();

	void on_cmdMwGo_clicked();

private:
	SDeviceApsin20g * Apsin20g;
	QString SUiCpApsin20g::hearderMsgFormat( QString msg, QColor color );
};

