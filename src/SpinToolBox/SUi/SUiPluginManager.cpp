

#include "SUiPluginManager.h"
#include "SDKDevice\SDevicePluginInterface.h"

#include <qdebug>
#include <QtCore>
#include <QtGui>

SUiPluginManager::SUiPluginManager( QList<SPlgInfo> LsPluginInfo, QList<SDevicePluginInterface *> lstPugin, QWidget *parent /*= 0*/ ):
	lstPugin_(lstPugin),QDialog(parent)
{
	// load the Qt designer ui 
	setupUi(this);
	
	//on ouvre le fichier ini a la bonne section
	settings = new QSettings ( "SpinToolBox.ini", QSettings::IniFormat, this );	
	settings->beginGroup("plugin");	

	chkQtCore->setChecked(settings->value("QtCore", false).toBool());  
	chkQtGui->setChecked(settings->value("QtGui", false).toBool());  

	for( int i = 0; i != LsPluginInfo.count(); ++i) {

		
		LsPluginInfo[i].activate = settings->value(LsPluginInfo.value(i).shortName, false).toBool();   
		QListWidgetItem * it = new QListWidgetItem(LsPluginInfo.value(i).name, lstchkPlugin);

		if(LsPluginInfo[i].activate)
			it->setCheckState(Qt::Checked);
		else
			it->setCheckState(Qt::Unchecked);
	}

	// on ferme la section (pour future utilisation du fichier ini)
	settings->endGroup();

	LsPluginInfo_ = LsPluginInfo;

}

SUiPluginManager::~SUiPluginManager()
{
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiPluginManager::on_cmdOK_clicked()
///
/// \brief	when the user click sur OK
///
/// \author	Sylvain Martin
/// \date	20/01/2012
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiPluginManager::on_cmdOK_clicked()
{

	settings->beginGroup("plugin");
	QString shortName;
	for(int i=0 ; i < lstchkPlugin->count() ; i++){

		for( int j = 0; j < LsPluginInfo_.count(); ++j) {

			if(lstchkPlugin->item(i)->text() == LsPluginInfo_.value(i).name){
				shortName = LsPluginInfo_.value(i).shortName;
			}
		}

		if(lstchkPlugin->item(i)->checkState() == Qt::Checked){
			settings->setValue(shortName, true); 
		}else{
			settings->setValue(shortName, false); 
		}
		
	}
	
	settings->setValue("QtCore", chkQtCore->isChecked()); 
	settings->setValue("QtGui", chkQtGui->isChecked()); 


	settings->endGroup();
	QMessageBox::information(this,"SpinToolBox - Plugin manager","You have to restart the software for applying the modifications");
	emit accepted ();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiPluginManager::on_lstPlugin_currentItemChanged( QListWidgetItem * current, QListWidgetItem * previous )
///
/// \brief	put all the information on the right side of the windows
///
/// \author	Sylvain Martin
/// \date	20/01/2012
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiPluginManager::on_lstchkPlugin_currentItemChanged( QListWidgetItem * current, QListWidgetItem * previous )
{
	
	for( int i = 0; i != LsPluginInfo_.count(); ++i) {

		if(current->text() == LsPluginInfo_.value(i).name){
			lblTitle->setText(LsPluginInfo_.value(i).name);
			lblDescription->setText(LsPluginInfo_.value(i).description);
			chkScriptable->setChecked(LsPluginInfo_.value(i).scriptable);
			chkCtlPanel->setChecked(LsPluginInfo_.value(i).cmdpan);
			lblPluginVersion->setText(LsPluginInfo_.value(i).plgVersion);
			lblSdkVersion->setText(LsPluginInfo_.value(i).sdkVersion);
			cmdOpt->setEnabled(LsPluginInfo_.value(i).isSetting && LsPluginInfo_.value(i).isLoad);
			break;
		}

	}
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiPluginManager::on_chkScriptable_toggled( bool checked )
///
/// \brief	when the chkScriptable widget is checked or unchecked
///
/// \author	Sylvain Martin
/// \date	20/01/2012
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiPluginManager::on_chkScriptable_clicked ( bool checked )
{
	// we cannot change it !!
	chkScriptable->setChecked(!checked);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiPluginManager::on_chkCtlPanel_clicked( bool checked )
///
/// \brief	when the chkCtlPanel widget is checked or unchecked
///
/// \author	Sylvain Martin
/// \date	20/01/2012
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiPluginManager::on_chkCtlPanel_clicked( bool checked )
{
	// we cannot change it !!
	chkCtlPanel->setChecked(!checked);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiPluginManager::on_chkCtlPanel_clicked( bool checked )
///
/// \brief	when the chkCtlPanel widget is checked or unchecked
///
/// \author	Sylvain Martin
/// \date	20/01/2012
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiPluginManager::on_cmdOpt_clicked(){

	for( int i = 0; i != lstPugin_.count(); ++i) {

		if(lstchkPlugin->selectedItems().first()->text() == lstPugin_.value(i)->name()){
			if(lstPugin_.value(i)->isSetting()) lstPugin_.value(i)->setting( this)->show();
		}

	}
	
		
}