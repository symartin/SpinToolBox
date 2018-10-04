////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUiMetaDataReader.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		07/03/2012
///
/// \brief	Declare the class of the Meta Data Reader Window
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

#include "GeneratedFiles/ui_SUiMetaDataReader.h"
#include <QtCore>
#include <QtGui>
#include "SDKDevice/SDevicePluginInterface.h"

class SUiMetaDataReader :
	public QWidget,
	public Ui_SUiMetaDataReader
{
	Q_OBJECT;

public:
	SUiMetaDataReader(QWidget *parent = 0);
	~SUiMetaDataReader(void);

public slots:
	void closeEvent(QCloseEvent *e);
	void on_cmdRefresh_clicked();
	void UpdateGlobalMetaData();

	void updateOneObject( SGlobalMetaDataMap &gmdm, QList<SMetaData> allMetaDataOfObj, QStandardItem * parent );

	private slots:
	void loadGlobalMetaData();

private:
	QTimer * timer;
	QStandardItemModel * model_;
};

/*class NoEditDelegate: public QStyledItemDelegate {
public:
	NoEditDelegate(QObject* parent=0): QStyledItemDelegate(parent) {}
	virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
		return 0;
	}
};*/
