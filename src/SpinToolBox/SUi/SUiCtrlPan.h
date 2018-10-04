////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUi\SUiCtrlPan.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		20/01/2012
///
/// \brief	Declares the SUiCmdMan and the SUiLblLed classes
/// 		
/// \section LICENSE
///
/// This program is free software; you can redistribute it and/or
/// modify it under the terms of the GNU General Public License as
/// published by the Free Software Foundation; either version 2 of
/// the License, or (at your option) any later version.
/// 
/// This program is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
/// General Public License for more details at
/// http://www.gnu.org/copyleft/gpl.html
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QtCore>
#include <QtGui>
#include "SDKDevice/SDevicePluginInterface.h"
#include "SUiMetaDataReader.h"

class SDataTreeModel;

class SUiCtrlPan : public QMainWindow
{
	Q_OBJECT;
public:
	SUiCtrlPan(QList<SDevicePluginInterface *> lstPugin,
				SGlobalMetaDataMap * GlobalMetaDataMap = NULL,
				QWidget * parent = NULL );

	~SUiCtrlPan(void);

private slots:
		void globalMetaDataWindowShow();

private:
		QTabWidget * DeviceTab_;
		QAction * actGlobalMetaDataWindow;
		QMenu * mnuFile;
		SGlobalMetaDataMap * gmdm_;
		SDataTreeModel * model;
		QTreeView * view;
		SUiMetaDataReader * metaDataReader;
};

