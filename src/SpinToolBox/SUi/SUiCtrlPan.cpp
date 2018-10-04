#include "SUiCtrlPan.h"
#include <QtCore>
#include <QtGui>
#include "SDKDevice/SDevicePluginInterface.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SUiCtrlPan::SUiCtrlPan(QList<SDevicePluginInterface *> lstPlugin,
/// 	SGlobalMetaDataMap * GlobalMetaDataMap, QWidget * parent )
///
/// \brief	Constructor.
///
/// \author	Sylvain Martin
/// \date	17/10/2012
///
/// \param [in,out]	lstPlugin		 	Have to be non-null, the list of the plugins.
/// \param [in,out]	GlobalMetaDataMap	Have to be non-null, the global meta data map.
/// \param [in,out]	parent			 	If non-null, the parent.
////////////////////////////////////////////////////////////////////////////////////////////////////
SUiCtrlPan::SUiCtrlPan(QList<SDevicePluginInterface *> lstPlugin,
		SGlobalMetaDataMap * GlobalMetaDataMap, QWidget * parent /* = NULL*/ ):
		gmdm_(GlobalMetaDataMap), QMainWindow(parent)
{
	
	this->setGeometry(QRect(0, 0, 635, 390));
	DeviceTab_ = new QTabWidget(this);
	
	
	metaDataReader = new SUiMetaDataReader(this);
	DeviceTab_->addTab(metaDataReader,"Global Meta Data");



	DeviceTab_->setObjectName(QString::fromUtf8("DeviceTab_"));
	DeviceTab_->setGeometry(QRect(0, 20, 630, 351));
	DeviceTab_->setTabShape(QTabWidget::Rounded);
	DeviceTab_->setDocumentMode(true);
	DeviceTab_->setMovable(true);

	int t = lstPlugin.count();
	for(int i =0; i < t; i++){
		if(lstPlugin.at(i)->isControlPanel())
			DeviceTab_->addTab(lstPlugin.at(i)->controlPanel(),lstPlugin.at(i)->shortName());
	}

// 	//action of execute the script
// 	actGlobalMetaDataWindow = new QAction("Global Meta Data",this);
// 	actGlobalMetaDataWindow->setShortcut(Qt::CTRL +  Qt::Key_M);
// 	actGlobalMetaDataWindow->setStatusTip(tr("Global Meta Data window"));
// 	connect(actGlobalMetaDataWindow, SIGNAL(triggered()), this, SLOT(globalMetaDataWindowShow()));

	//mnuFile = menuBar()->addMenu(tr("&File"));
	//mnuFile->addAction(actGlobalMetaDataWindow);


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SUiCtrlPan::~SUiCtrlPan(void)
///
/// \brief	Destructor.
///
/// \author	Sylvain Martin
/// \date	17/10/2012
////////////////////////////////////////////////////////////////////////////////////////////////////
SUiCtrlPan::~SUiCtrlPan(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiCtrlPan::globalMetaDataWindowShow()
///
/// \brief	(SLOT) open the visualization window of the global metadata tree.
///
/// \author	Sylvain Martin
/// \date	17/10/2012
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiCtrlPan::globalMetaDataWindowShow()
{




}

