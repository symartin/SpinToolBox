#ifndef SUIPLUGINMANAGER_H
#define SUIPLUGINMANAGER_H

#include "GeneratedFiles/ui_SUiPluginManager.h"
#include "SDKDevice/SDevicePluginInterface.h"
#include <QMainWindow>
#include <QtCore>
#include <qdebug>

#define SUIPLUGINMANAGER_UIPMDEBUG
#ifdef SUIPLUGINMANAGER_UIPMDEBUG
#  define pmDebug qDebug
#else
#  define pmDebug if (false) qDebug
#endif


typedef struct  {
	QString name;
	QString shortName;
	QString description;
	bool scriptable;
	bool cmdpan;
	bool activate;
	QString plgVersion;
	QString sdkVersion;
	bool isSetting;
	bool isLoad;
}SPlgInfo;

class SUiPluginManager : public QDialog, public Ui::SUiPluginManager
{
	Q_OBJECT

public slots:
	void on_cmdOK_clicked();
	void on_lstchkPlugin_currentItemChanged( QListWidgetItem * current, QListWidgetItem * previous );
	void on_chkScriptable_clicked (bool checked); 
	void on_chkCtlPanel_clicked (bool checked); 
	void on_cmdOpt_clicked();
	
	

public:
	SUiPluginManager(QList<SPlgInfo> LsPluginInfo, QList<SDevicePluginInterface *> lstPugin, QWidget *parent = 0);
	~SUiPluginManager();
	QList<SDevicePluginInterface *> lstPugin_;
	QList<SPlgInfo> LsPluginInfo_;


private:
	//QList<SPlgInfo> LsPluginInfo_;
	QSettings * settings;
	//SPlgInfo PlgInfoCtor(SDevicePluginInterface * plugin);


};






#endif
