#include "SUiMetaDataReader.h"
#include <QtCore>
#include <QtGui>
#include "SDKDevice/SDevicePluginInterface.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SUiMetaDataReader::SUiMetaDataReader(QWidget *parent)
///
/// \brief	Constructor.
///
/// \author	Sylvain Martin
/// \date	17/10/2012
///
/// \param [in,out]	parent	If non-null, the parent.
////////////////////////////////////////////////////////////////////////////////////////////////////

SUiMetaDataReader::SUiMetaDataReader(QWidget *parent):
	QWidget(parent)
{
	setupUi(this);
	model_ = new QStandardItemModel(this);
	loadGlobalMetaData();

	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(UpdateGlobalMetaData()));
	timer->setInterval (333);
	timer->start();

	//this->connect(model_,"dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight )","updated( const QModelIndex & topLeft, const QModelIndex & bottomRight )");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SUiMetaDataReader::~SUiMetaDataReader(void)
///
/// \brief	Destructor.
///
/// \author	Sylvain Martin
/// \date	17/10/2012
////////////////////////////////////////////////////////////////////////////////////////////////////
SUiMetaDataReader::~SUiMetaDataReader(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::closeEvent(QCloseEvent *e)
///
/// \brief	(SLOT) When the user click on the [X] (close) button
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMetaDataReader::closeEvent( QCloseEvent *e )
{
	this->deleteLater();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMetaDataReader::loadGlobalMetaData()
///
/// \brief	Load the GlobalMetaData an fill the panel
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMetaDataReader::loadGlobalMetaData()
{
	SGlobalMetaDataMap gmdm;
	QStringList allObjects = gmdm.allObjects();
	int nbobj = allObjects.count();

	model_->clear();
	model_->setColumnCount(3);
	model_->setRowCount(nbobj);

	for( int r=0; r<nbobj; r++ ){ // tous les obj du gmdm
		QStandardItem *item = new QStandardItem( allObjects.value(r) );
		QList<SMetaData> allMetaDataOf = gmdm.allMetaDataOf(allObjects.value(r));

		for( int i=0; i< allMetaDataOf.count(); i++ ){
			QStandardItem *childC1 = new QStandardItem( allMetaDataOf.at(i).name() );
			QStandardItem *childC2 = new QStandardItem( allMetaDataOf.at(i).value().toString() );
			QStandardItem *childC3 = new QStandardItem( allMetaDataOf.at(i).unit());

			childC1->setEditable( false );
			childC2->setEditable( false );
			childC3->setEditable( false );

			item->setChild(i,0,childC1);
			item->setChild(i,1,childC2);
			item->setChild(i,2,childC3);
		}

		model_->setItem(r, 0, item);
	}

	model_->setHorizontalHeaderItem( 0, new QStandardItem( "Name" ) );
	model_->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );
	model_->setHorizontalHeaderItem( 2, new QStandardItem( "Unit" ) );

	tvMetaData->setModel( model_ );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiMetaDataReader::UpdateGlobalMetaData()
///
/// \brief	Updates the global meta data.
///
/// \author	Sylvain Martin
/// \date	17/10/2012
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMetaDataReader::UpdateGlobalMetaData(){
	
	
	SGlobalMetaDataMap gmdm;
	QStringList allObjects = gmdm.allObjects();
	int nbobj = allObjects.count();

	QMutableListIterator<QString> r(allObjects);

	while (r.hasNext()) {

		QString objcurrent = r.next();
		QList<QStandardItem *> lsttmp = model_->findItems(objcurrent);


		if(lsttmp.count() >=1){ // on met a jour les element existant
			QStandardItem *parent = lsttmp.value(0);
			QList<SMetaData> allMetaDataOf = gmdm.allMetaDataOf(objcurrent);
			updateOneObject(gmdm, allMetaDataOf, parent);

		}else{ // on crée les nouveaux elements
			loadGlobalMetaData();
		/*	int nb = (model_->rowCount()) +1;

			QStandardItem *item = new QStandardItem( allObjects.value(nb) );
			QList<SMetaData> allMetaDataOf = gmdm.allMetaDataOf(allObjects.value(nb));

			for( int i=0; i< allMetaDataOf.count(); i++ ){
				QStandardItem *childC1 = new QStandardItem( allMetaDataOf.at(i).name() );
				QStandardItem *childC2 = new QStandardItem( allMetaDataOf.at(i).value().toString() );
				QStandardItem *childC3 = new QStandardItem( allMetaDataOf.at(i).unit());

				childC1->setEditable( false );
				childC2->setEditable( false );
				childC3->setEditable( false );

				item->setChild(i,0,childC1);
				item->setChild(i,1,childC2);
				item->setChild(i,2,childC3);
			}

			model_->insertRow (0,item);/// */
		}
	}
	tvMetaData->update();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiMetaDataReader::on_cmdRefresh_clicked()
///
/// \brief	Handles command refresh clicked signals.
///
/// \author	Sylvain Martin
/// \date	17/10/2012
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMetaDataReader::on_cmdRefresh_clicked()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiMetaDataReader::updateOneObject( SGlobalMetaDataMap &gmdm,
/// 	QList<SMetaData> allMetaDataOfObj, QStandardItem * parent )
///
/// \brief	Updates the one object.
///
/// \author	Sylvain Martin
/// \date	17/10/2012
///
/// \param [in,out]	gmdm		The Global Meta Data Map.
/// \param	allMetaDataOfObj	all meta data of object.
/// \param [in,out]	parent  	The parent coresponding to the obj in the model.
////////////////////////////////////////////////////////////////////////////////////////////////////

void SUiMetaDataReader::updateOneObject( SGlobalMetaDataMap &gmdm, QList<SMetaData> allMetaDataOfObj, QStandardItem * parent )
{
	

	// on met a jour les element qui existent déjà
	QMutableListIterator<SMetaData> i(allMetaDataOfObj);
	while (i.hasNext()) {
		SMetaData metadatacurrent = i.next() ;

		for(int j=0; j< parent->rowCount();j++){
			QStandardItem * child = parent->child(j,0);
			if(child->text()== metadatacurrent.name()){
				// on met a jour
				parent->child(j,1)->setText(metadatacurrent.value().toString());
				parent->child(j,2)->setText(metadatacurrent.unit());

				// on enlève l'élément de la liste
				i.remove();
			}
		}
	}
	// on crée les elements qui n'existaient pas
	if(allMetaDataOfObj.count()!=0){
		loadGlobalMetaData();
		/*for( int i=0; i< allMetaDataOfObj.count(); i++ ){

			QStandardItem *childC1 = new QStandardItem( allMetaDataOfObj.at(i).name() );
			QStandardItem *childC2 = new QStandardItem( allMetaDataOfObj.at(i).value().toString() );
			QStandardItem *childC3 = new QStandardItem( allMetaDataOfObj.at(i).unit());

			childC1->setEditable( false );
			childC2->setEditable( false );
			childC3->setEditable( false );

			QList<QStandardItem *> rowlst;
			rowlst.append(childC1);
			rowlst.append(childC2);
			rowlst.append(childC3);
			parent->appendRow ( rowlst );

		}*/
	}
}
