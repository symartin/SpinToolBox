////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SDeviceGpib.cpp
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		23/03/2012
///
/// \brief	implants a virtual class for the device plugin, an the system of shared metadata
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
#include "SDevicePluginInterface.h"
#include <QtCore>
#include <string.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SMetaData::SMetaData(QString objn, QString metaDataName, QVariant val, QString type, QString shc)
///
/// \brief	ctor, set a value of a metadata of an object.
///
/// \author	Sylvain Martin
/// \date	13/03/2011
///
/// \param objName The name of the object.
/// \param metaDataName The name of the metadata.
/// \param val The value of the metadata.
/// \param type The type of the metadata, by default string.
///
/// type : boolean b, string s, integer i, double d 
////////////////////////////////////////////////////////////////////////////////////////////////////
SMetaData::SMetaData(const QString objn, const QString metaDataName, 
	const QVariant val, const QString unit, const QString type){

	setObjectName(objn);
	setName(metaDataName);
	setValue(val);
	setUnit(unit);

	switch  (type.toAscii().data()[0]) {
	case 'b':  setType(boolean); break;
	case 's': setType(string); break;
	case 'i': setType(integer); break;
	case 'd': setType(doublefloat); break;
	default : setType(other); break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SMetaData::SMetaData(QString objn, QString metaDataName, QVariant val, enumType type = string, QString shc = "")
///
/// \brief	ctor, set a value of a metadata of an object.
///
/// \author	Sylvain Martin
/// \date	13/03/2011
///
/// \param objn The name of the object.
/// \param metaDataName The name of the metadata.
/// \param val The value of the metadata.
/// \param unit The of the value
/// \param type The type of the metadata, by default string.
///
/// type : boolean b, string s, integer i, double d 
////////////////////////////////////////////////////////////////////////////////////////////////////
SMetaData::	SMetaData(const QString objn, const QString metaDataName, 
	const QVariant val, const QString unit, const enumType type){
	this->setObjectName(objn);
	this->setName(metaDataName);
	this->setValue(val);
	this->setType(type);
	this->setUnit(unit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SMetaData::SMetaData(QString objn, QString metaDataName, QVariant val, QString type, QString shc)
///
/// \brief	default ctor, set a value of a metadata of an object.
///
/// \author	Sylvain Martin
/// \date	13/03/2011

////////////////////////////////////////////////////////////////////////////////////////////////////
SMetaData::SMetaData(){
	this->setObjectName("");
	this->setName("");
	this->setValue(QVariant(""));
	this->setType('s');
	this->setUnit("");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SMetaData::SMetaData(const SMetaData& other) 
///
/// \brief	copy ctor, set a value of a metadata of an object.
///
/// \author	Sylvain Martin
/// \date	13/03/2011

////////////////////////////////////////////////////////////////////////////////////////////////////
SMetaData::SMetaData(const SMetaData& other)   // copy constructor
{
	 objname_ = other.objname_; 
	 value_= other.value_; 
	 name_= other.name_; 
	 type_= other.type_; 
	 unit_=other.unit_;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SMetaData & SMetaData::operator= (const SMetaData & other) 
///
/// \brief	Assignment operator ctor, set a value of a metadata of an object.
///
/// \author	Sylvain Martin
/// \date	13/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SMetaData & SMetaData::operator= (const SMetaData & other){

	objname_ = other.objname_; 
	value_= other.value_; 
	name_= other.name_; 
	type_= other.type_; 
	unit_=other.unit_;

	return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SMetaData & SMetaData::operator= (const SMetaData & other) 
///
/// \brief	dtor
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SMetaData::~SMetaData(){

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SMetaData::setObjectName(QString objname)
///
/// \brief	set the object name of the metadata.
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SMetaData::setObjectName(const QString objname){

	objname_ = objname; 

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SMetaData::objectName()
///
/// \brief	return the object name of the metadata.
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SMetaData::objectName() const{
	return objname_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SMetaData::setName(QString objname)
///
/// \brief	set the name of the metadata.
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SMetaData::setName(const QString metaDataName){

	name_= metaDataName; 

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SMetaData::name()
///
/// \brief	return the object name of the metadata.
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SMetaData::name() const{
	return (name_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SMetaData::setObjectName(QString objname)
///
/// \brief	set the object name of the metadata
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QVariant SMetaData::value() const{
	return value_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SMetaData::setValue(QVariant val)
///
/// \brief	set the value name of the metadata
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SMetaData::setValue(const QVariant val){
	value_= val; 

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SMetaData::enumType SMetaData::type()
///
/// \brief	return the type name of the metadata
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SMetaData::enumType SMetaData::type() const{
	switch  (type_) {
	case 'b': return boolean;
	case 's': return string;
	case 'i': return integer;
	case 'd': return doublefloat;
	default : return other;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SMetaData::setType(enumType tp)
///
/// \brief	set the object name of the metadata
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SMetaData::setType(const enumType tp){
	type_ = tp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SMetaData::setType(const char tp)
///
/// \brief	set the type of the metadata
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SMetaData::setType(const char tp){
	switch  (tp) {
	case 'b': setType (boolean);
	case 's': setType (string);
	case 'i': setType (integer);
	case 'd': setType (doublefloat);
	default : setType (other);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SMetaData::setType(const QString tp)
///
/// \brief	set the type of the metadata
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SMetaData::setType(const QString tp){
	switch  (tp.toAscii().data()[0]) {
	case 'b': setType (boolean);
	case 's': setType (string);
	case 'i': setType (integer);
	case 'd': setType (doublefloat);
	default : setType (other);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SMetaData::unit( )
///
/// \brief	get the unit of the metadata
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SMetaData::unit() const{
	return unit_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SMetaData::setUnit(const QString u)
///
/// \brief	set the unit of the metadata
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SMetaData::setUnit(const QString u){
	unit_=u;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QDataStream &operator<<(QDataStream &out, const SMetaData &myObj)
///
/// \brief	out stream operator for SMetaData
///
/// \author	Sylvain Martin
/// \date	21/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QDataStream &operator<<(QDataStream &out, const SMetaData &myObj){

	quint8 c='o';
	out << myObj.objname_ << myObj.name_ << myObj.value_ << myObj.unit_ << (quint8)myObj.type_;
	return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QDataStream &operator>>(QDataStream &in, SMetaData &myObj)
///
/// \brief	in stream operator for SMetaData
///
/// \author	Sylvain Martin
/// \date	21/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QDataStream &operator>>(QDataStream &in, SMetaData &myObj){

	quint8 c=myObj.type_;
	in >> myObj.objname_ >> myObj.name_ >> myObj.value_ >> myObj.unit_  >> c;
	myObj.setType(c);
	return in;
}


/****************************************************************************************************/
/*                                       SGlobalMetaDataMap                                         */
/****************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SGlobalMetaDataMap::setMetaData(QString objName, QString metaDataName, QVariant metaData)
///
/// \brief	set a value_ of a metadata of an object
///
/// \author	Sylvain Martin
/// \date	07/03/2011
///
/// \param objName The name of the object.
/// \param metaDataName The name of the metadata.
/// \param metaData The value_ of the metadata.
///
/// If the object or the metadata doesn't exist yet, it is created. If it exist, the value is replaced 
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SGlobalMetaDataMap::setMetaData(QString objName, QString metaDataName, QVariant metaData, QString unit, 
						SMetaData::enumType type){

	loadSharedMemory();

	int index=-1;

	if((index=find(objName, metaDataName))!=-1){ // If it exists already
			metadata[index].setValue(metaData);
			metadata[index].setType(type);

	}else{ // if not, we try to find a empty place
		SMetaData mdm(objName, metaDataName, metaData, unit, type );
		metadata.append(mdm);
	}

	saveSharedMemory();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SGlobalMetaDataMap::MetaDataExist(QString objName, QString metaDataName )
///
/// \brief	return if a metaData is registered for an object
///
/// \author	Sylvain Martin
/// \date	07/03/2011
///
/// \param objName the name of the object
/// \param objName the name of the metaData
///
/// \return the value if it exist, or an empty if not.
////////////////////////////////////////////////////////////////////////////////////////////////////
SMetaData SGlobalMetaDataMap::MetaData(QString objName, QString metaDataName ){
	loadSharedMemory( );
	int index=-1;

	if((index=find(objName, metaDataName))!=-1){ // If it exists 
		return metadata[index];
	}else{
		qDebug() << "ERROR : MetaData :"<< objName << "/" << metaDataName 
			 << " does not exist !";
	}
	return SMetaData();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SGlobalMetaDataMap::MetaDataExist(QString objName, QString metaDataName )
///
/// \brief	return if a metaData is registered for an object
///
/// \author	Sylvain Martin
/// \date	07/03/2011
///
/// \param objName the name of the object
/// \param objName the name of the metaData
///
/// \return true if the metadata is registered, false otherwise
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SGlobalMetaDataMap::MetaDataExist(QString objName, QString metaDataName ){
	loadSharedMemory( );
	return (find(objName, metaDataName))!=-1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<SMetaData> SGlobalMetaDataMap::allMetaDataOf(QString objName)
///
/// \brief	return if a metaData is registered for an object
///
/// \author	Sylvain Martin
/// \date	07/03/2011
///
/// \param objName the name of the object
///
/// \return the list of all metadata corresponding of an object
////////////////////////////////////////////////////////////////////////////////////////////////////
QList<SMetaData> SGlobalMetaDataMap::allMetaDataOf(QString objName){
	loadSharedMemory( );
	QList<SMetaData> list;
	for(int i=0; i< metadata.count(); i++){
		if(metadata[i].objectName() == objName){
			list.append(metadata[i]);
		}
	}

	return list;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QStringList SGlobalMetaDataMap::allObjects()
///
/// \brief	return a list with all the different objects in the metadata array
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList SGlobalMetaDataMap::allObjects(){
	loadSharedMemory( );
	
	QStringList list;

	for(int i=0; i< metadata.count(); i++){
		if(metadata[i].objectName() != "" && list.indexOf(metadata[i].objectName()) == -1 ){
			 list.append(metadata[i].objectName());
		}
	}

	return list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SGlobalMetaDataMap::loadSharedMemory( )
///
/// \brief	load the metadata array from the shared memory
///
/// \author	Sylvain Martin
/// \date	14/03/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
void SGlobalMetaDataMap::loadSharedMemory( ){
	
	if (stopReload_) return;

	if (!sharedMemory.attach()) {
		QSharedMemory::SharedMemoryError er= sharedMemory.error();
		if(er != QSharedMemory::AlreadyExists && er != QSharedMemory::NoError){
			qDebug() << ("Unable to attach to shared memory segment.\n");
			qDebug() << sharedMemory.errorString();
		}
	}

	QBuffer buffer;
	QDataStream in(&buffer);
	// QImage image;

	sharedMemory.lock();
	buffer.setData((char*)sharedMemory.constData(), sharedMemory.size());
	buffer.open(QBuffer::ReadOnly);
	in >> metadata;
	sharedMemory.unlock();

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SGlobalMetaDataMap::loadSharedMemory( )
///
/// \brief	save the metadata array to the shared memory
///
/// \author	Sylvain Martin
/// \date	14/03/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
void SGlobalMetaDataMap::saveSharedMemory( ){
		
	// load into shared memory
	QBuffer buffer;
	buffer.open(QBuffer::ReadWrite);
	QDataStream out(&buffer);
	out << metadata;
	int size = buffer.size();

	if (!sharedMemory.create(size)) {
		QSharedMemory::SharedMemoryError er= sharedMemory.error();
		if(er = QSharedMemory::AlreadyExists){
			if (!sharedMemory.attach()) {
				QSharedMemory::SharedMemoryError er2= sharedMemory.error();
				if(er2 != QSharedMemory::AlreadyExists && er2 != QSharedMemory::NoError){
					qDebug() << ("Unable to attach to shared memory segment.\n");
					qDebug() << sharedMemory.errorString();
				}
			}
		}else if(er != QSharedMemory::AlreadyExists && er != QSharedMemory::NoError){
			qDebug() << ("Unable to create shared memory segment.");
			qDebug() << sharedMemory.errorString();
			return;
		}
	}
	sharedMemory.lock();
	char *to = (char*)sharedMemory.data();
	const char *from = buffer.data().data();
	memcpy(to, from, qMin(sharedMemory.size(), size));
	sharedMemory.unlock();

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SGlobalMetaDataMap::count() const
///
/// \brief	cont the number of metadata
///
/// \author	Sylvain Martin
/// \date	12/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
int SGlobalMetaDataMap::count(){

	loadSharedMemory();
	return metadata.count();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SGlobalMetaDataMap::SGlobalMetaDataMap()
///
/// \brief	ctor
///
/// \author	Sylvain Martin
/// \date	12/03/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
SGlobalMetaDataMap::SGlobalMetaDataMap() : sharedMemory("SpinToolBox_GlobalMetaData"), stopReload_(false) 
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SGlobalMetaDataMap::~SGlobalMetaDataMap()
///
/// \brief	dtor
///
/// \author	Sylvain Martin
/// \date	12/03/2011
////////////////////////////////////////////////////////////////////////////////////////////////////
SGlobalMetaDataMap::~SGlobalMetaDataMap()
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SGlobalMetaDataMap::find(QString objName, QString metaDataName)
///
/// \brief	find a meta data int the metadata array.
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
/// \return the index of the metadata, or -1 if it is not exist.
////////////////////////////////////////////////////////////////////////////////////////////////////
int SGlobalMetaDataMap::find(QString objName, QString metaDataName, bool load){
	if(load) loadSharedMemory( );

	for(int i=0; i< metadata.count(); i++){
		if(metadata[i].objectName() == objName && metadata[i].name() == metaDataName){
			return i;
		}
	}
	return -1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void clear(const QString objname)
///
/// \brief	clear all metadata corresponding to objname
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SGlobalMetaDataMap::clear(const QString objName){
	loadSharedMemory( );
	SMetaData empty;

	for(int i=0; i< metadata.count(); i++){
		if(metadata[i].objectName() == objName){
			metadata.removeAt(i);
			//metadata[i]=empty;
		}
	}
	saveSharedMemory();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SGlobalMetaDataMap::firstInit()
///
/// \brief	initialize the shared memory system
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
/// this function has to be executed one (and only once) before any using of the meta data system
////////////////////////////////////////////////////////////////////////////////////////////////////
void SGlobalMetaDataMap::firstInit()
{
	saveSharedMemory();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SGlobalMetaDataMap::stopReload( bool OnOff )
///
/// \brief	this function stop/start the load behavior 
///
/// \author	Sylvain Martin
/// \date	14/03/2011
///
/// \param OnOff true stop the reload.
///
/// this function is useful if there are lot of meta data to get in a short time, it avoid to re-load
/// everything each time, but, the metadata are not updated.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SGlobalMetaDataMap::stopReload( bool OnOff )
{
	stopReload_ = OnOff;
}
