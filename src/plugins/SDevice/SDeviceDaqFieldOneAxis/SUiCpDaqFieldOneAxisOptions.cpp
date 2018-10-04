#include "SUiCpDaqFieldOneAxisOptions.h"
#include <QScriptable>
#include <QScriptEngine>
#include <QSettings>
#include <QtCore>
#include <QtGui>

SUiCpDaqFieldOneAxisOptions::SUiCpDaqFieldOneAxisOptions(QWidget * parent):QDialog(parent)
{
	setupUi(this);


	set_ = new QSettings ( "SpinToolBox.ini", QSettings::IniFormat, this );
	set_->beginGroup("SDeviceDaqFieldOneAxis");	
	txtCoeff->setText(set_->value("DacKepcoCoeff", "5/6").toString());
	set_->endGroup();
	
}


SUiCpDaqFieldOneAxisOptions::~SUiCpDaqFieldOneAxisOptions(void)
{
}


void SUiCpDaqFieldOneAxisOptions::on_cmdOk_clicked (){

	QScriptEngine engine;
	QScriptValue resultat = engine.evaluate(txtCoeff->text());
	if(resultat.isNumber()){
		set_->beginGroup("SDeviceDaqFieldOneAxis");	
		set_->setValue("DacKepcoCoeff", txtCoeff->text()); 
		set_->endGroup();
		this->hide();
		this->deleteLater();

	}else{
		QMessageBox msgBox;
		msgBox.setText("The value for the coefficient is not a valid number.");
		msgBox.exec();
	}
	

}