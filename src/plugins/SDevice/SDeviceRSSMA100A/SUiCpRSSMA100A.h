#pragma once
#include <QtCore>
#include <QtGui>
#include "GeneratedFiles/Ui_SUiCpRSSMA100A.h"
#include "SDeviceRSSMA100A.h"

class SUiCpRSSMA100A :
	public QWidget,
	public Ui_SUiCpRSSMA100A
{
	Q_OBJECT;

public:
	SUiCpRSSMA100A(QWidget * parent = NULL );
	~SUiCpRSSMA100A(void);

private slots:
	void on_cmdMwOnOff_clicked(bool checked );
	void on_dsbMwPower_editingFinished();
	void on_dsbMwFreq_editingFinished();

	void on_dsbMwPower_valueChanged(double d);
	void on_dsbMwFreq_valueChanged(double d);
	void on_dsbMwPowerLimit_editingFinished();

	void on_cmdMwGo_clicked();

private:
	SDeviceRSSMA100A * RSSMA100;
	QString SUiCpRSSMA100A::hearderMsgFormat( QString msg, QColor color );
};

