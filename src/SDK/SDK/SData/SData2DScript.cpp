////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SDevice\SData2DScript.cpp
///
/// \author		Sylvain Martin
/// \version	1.0
/// \date		1/20/2011
///
/// \brief	implante the SData2DScript class
///
/// This file is part of the SpinToolBox project
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
#include "SData2DScript.h"
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>
#include <SData\SData2D.h>
#include <QVariant.h>
#include <QList.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2DScript::SData2DScript(QObject * parent)
///
/// \brief	defalut constructor.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param [in,out]	parent	If non-null, the Qt parent.
////////////////////////////////////////////////////////////////////////////////////////////////////

SData2DScript::SData2DScript(QObject * parent):
				QObject(parent){
	data2D_ = new SData2D();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2DScript::SData2DScript(SData2D * data, QObject * parent)
///
/// \brief	psedo constructor by copy.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param 	data	the data.
/// \param 	parent	If non-null, the Qt parent.
////////////////////////////////////////////////////////////////////////////////////////////////////

SData2DScript::SData2DScript(SData2D * data, QObject * parent):
	QObject(parent){
	data2D_ = data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2DScript::SData2DScript(SData2D * data, QObject * parent)
///
/// \brief	psedo constructor by copy.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param 	data	the data.
/// \param 	parent	If non-null, the Qt parent.
////////////////////////////////////////////////////////////////////////////////////////////////////
SData2DScript::SData2DScript(SData2D  data, QObject * parent) :QObject(parent){

	data2D_ = new SData2D(data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2DScript::~SData2DScript(void)
///
/// \brief	Destructor.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
////////////////////////////////////////////////////////////////////////////////////////////////////

SData2DScript::~SData2DScript(void){
	if(data2D_ != NULL){
		delete(data2D_);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QScriptValue SData2DScript::qsCtor(QScriptContext *context, QScriptEngine *engine)
///
/// \brief	this function is use by script engine to create a new SData2D.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param [in,out]	context	If non-null, the QScript context.
/// \param [in,out]	engine	If non-null, the QScript engine.
///
/// \return	a QScript version of a SData2D.
////////////////////////////////////////////////////////////////////////////////////////////////////

QScriptValue SData2DScript::qsCtor(QScriptContext *context, QScriptEngine *engine) {

	 if(context->argument(0).isObject()){
			QObject *parent = context->argument(0).toQObject();
	 }

     QObject *object = new SData2DScript();
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QScriptValue SData2DScript::toQScriptValue(QScriptContext *context, QScriptEngine *engine)
///
/// \brief	Converts this object to a q script value.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param [in,out]	context	If non-null, the context.
/// \param [in,out]	engine	If non-null, the engine.
///
/// \return	This object as a QScriptValue.
////////////////////////////////////////////////////////////////////////////////////////////////////

QScriptValue SData2DScript::toScriptValue(QScriptContext *context, QScriptEngine *engine){
	return engine->newQObject(this, QScriptEngine::ScriptOwnership);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE void SData2DScript::openFile(QString const file)
///
/// \brief	Opens a file.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param	file	The file.
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE void SData2DScript::openFile(QString const file){
	try{
		data2D_->openFile(file);
	}catch(QString error){
		qDebug() << "SCRIPT ERROR : (in the function openFile)" << error;
		qDebug() << "Do not forget to escape the \\ charactere" << error;
		qDebug() << "file = " << file;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE void SData2DScript::slideAverage(int const windows, double const PeackProtectCoeff)
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
///  \param windows size of the average windows, it has to be greater than 1
///  \param PeackProtectCoeff avoids to flatten the very thin peaks, removes these points from the average
///
/// 							   do a slide averadge of the data, with a slide windows. start at 0
///   - value(0) <= average(value(0) to value(windows-1))
///   - value(1) <= average(value(1) to value(1+windows-1))
///   - ...
///   - value(size-windows) <= average(value(end-windows) to value(size-1))
///   - value(size-windows+1)<= average(value(end-windows+1) to value(size-1) and value(size-windows))
///   - ...
///
///   for the "windows" last points the missing points are replaced by the
///   last average value computed with the last points.
///
///   the complexity is O(n)
///
///   PeackProtectCoeff is useful when the signal is a sum of a signal with a low
///   amplitude and a Dirac peak. for "protect" the Dirac peak, if the ratio
///   between the point with and without the average is small enough, the
///   average is canceled for this point. the ratio is always compute with
///   the smallest over the biggest. If PeackProtectCoeff==0, all signal are average.
///
///   For well working take PeackProtectCoeff  >~ 1/window
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE void SData2DScript::slideAverage(int const windows, double const PeackProtectCoeff){
	data2D_->slideAverage(windows, PeackProtectCoeff);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE void SData2DScript::append(QScriptContext *context, QScriptEngine *engine)
///
/// \brief	(SCRIPTABLE) Appends a couple of arrays.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param [in,out]	context	If non-null, the QtScript context.
/// \param [in,out]	engine	If non-null, the QtScript .
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2DScript::append(QVariantList x, QVariantList y){

	QVariant xtmp;
	QVariant ytmp;
	if( y.count() == x.count()){
		for(int i =0; i< y.count();i++){
			xtmp = x.at(i);
			ytmp = y.at(i);

			if( xtmp.canConvert<double>() && xtmp.convert(QVariant::Double)
				&& ytmp.canConvert<double>() && ytmp.convert(QVariant::Double)){
					data2D_->append(xtmp.toDouble(),ytmp.toDouble());
			}
		}
	}


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE void SData2DScript::append(QScriptContext *context, QScriptEngine *engine)
///
/// \brief	(SCRIPTABLE) Appends a couple of value.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param [in,out]	context	If non-null, the QtScript context.
/// \param [in,out]	engine	If non-null, the QtScript .
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2DScript::append(double x, double y){
	data2D_->append(x,y);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SData2DScript::x(int i)
///
/// \brief	(SCRIPTABLE) get the value at index position i in the ordinate of the data.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param	i	index of the wanted value.
///
/// If the index i is out of bounds, the function returns 0.
////////////////////////////////////////////////////////////////////////////////////////////////////

double SData2DScript::x(int i){
	return data2D_->x()->value(i);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SData2DScript::y(int i)
///
/// \brief	(SCRIPTABLE) get the value at index position i in the abscissa of the data.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param	i	index of the wanted value.
///
/// If the index i is out of bounds, the function returns 0.
////////////////////////////////////////////////////////////////////////////////////////////////////

double SData2DScript::y(int i){
	return data2D_->y()->value(i);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SData2DScript::count(void)
///
/// \brief	(SCRIPTABLE) Gets the count of element. 
///
/// \sa SData2DScript::size()
/////////////////////////////////////////////////////////////////////////////////////////////////////

int SData2DScript::count(void){
	return data2D_->x()->count();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE void SData2DScript::saveFile(QString const file)
///
/// \brief	(SCRIPTABLE) Saves the data in a file.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param	file	file from which we want write data.
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2DScript::saveFile(QString const file){
	try{
		data2D_->saveFile(file);
	}catch(QString error){
		qDebug() << "SCRIPT ERROR : (in the function saveFile)" << error;
		qDebug() << "Do not forget to escape the \\ charactere" << error;
		qDebug() << "file = " << file;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 QVariant SData2DScript::metaData(QString const key) const
///
/// \brief	(SCRIPTABLE) return the MetaData with the key give in arguement.
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \param	key	The key in the map table.
///
/// \return	the MetaData with the key give in arguement.
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE QVariant SData2DScript::metaData(QString const key) const{
	try{
		return data2D_->metaData(key);
	}catch(QString error){
		qDebug() << "SCRIPT ERROR : (in the function metaData)" << error;
		qDebug() << "key = " << key;
		return QVariant("");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 void SData2DScript::setMetaData(QString const key, QVariant const value)
///
/// \brief	(SCRIPTABLE) add or reset a key of the metadata.
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \param	key		The key.
/// \param	value	The value.
///
///  \warning if the key already exist, this function just overwrite it.
//////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE void SData2DScript::setMetaData(QString const key, QVariant const value){
	data2D_->setMetaData(key,value);
}

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn	QScriptValue SData2DScript::toScriptValue(QScriptEngine *engine, const SData2D &s)
 ///
 /// \brief	Converts this object to a QScriptValue.
 ///
 /// \author	Sylvain Martin
 /// \date	2/2/2011
 ///
 /// \param [in,out]	engine	If non-null, the engine.
 /// \param	s					The.
 ///
 /// \return	This object as a QScriptValue.
 ////////////////////////////////////////////////////////////////////////////////////////////////////

 QScriptValue SData2DScript::toScriptValue(QScriptEngine *engine, const SData2D &s)
 {
	 QObject *object = new SData2DScript(SData2D(s),NULL);
     return engine->newQObject(object, QScriptEngine::ScriptOwnership);
 }



 void SData2DScript::fromScriptValue(const QScriptValue &obj, SData2D &s)
 {
	 SData2DScript *qsData = qobject_cast<SData2DScript*>(obj.toQObject());
	// s.setData(qsData->data2DObjectCopy());
	 s.overwrite(qsData->data2DObject());
 }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2D * SData2DScript::data2DObject(void)
///
/// \brief	Gets the SData2D object en capsuled by this warper.
///
/// \author	Sylvain Martin
/// \date	2/2/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////

SData2D * SData2DScript::data2DObject(void)
{
	return data2D_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2D * SData2DScript::data2DObject(void)
///
/// \brief	Gets a copy of SData2D object en capsuled by this warper.
///
/// \author	Sylvain Martin
/// \date	2/2/2011
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SData2D SData2DScript::data2DObjectCopy(){
	return *data2D_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::setColName( QString Xname, QString Yname )
///
/// \brief	set the name of the columns
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::setColName( QString Xname, QString Yname )
{
	data2D_->setColName(Xname,Yname);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::setColXName( QString Xname )
///
/// \brief	set the name of the X column
////////////////////////////////////////////////////////////////////////////////////////////////////

Q_INVOKABLE void SData2DScript::setColXName( QString Xname )
{
	data2D_->setColXName(Xname);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::colXName(  )
///
/// \brief	return the name of the X column
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE QString SData2DScript::colXName()
{
	return data2D_->colXName();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::setColYName( QString Yname )
///
/// \brief	set the name of the Y column
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::setColYName( QString Yname )
{
		data2D_->setColYName(Yname);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::colYName(  )
///
/// \brief	return the name of the Y column
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE QString SData2DScript::colYName()
{
	return data2D_->colYName();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::setColUnit( QString XUnit, QString YUnit )
///
/// \brief	set the units of the columns
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::setColUnit( QString XUnit, QString YUnit )
{
	data2D_->setColUnit(XUnit,YUnit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::setColXUnit( QString XUnit )
///
/// \brief	set the units of the columns
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::setColXUnit( QString XUnit )
{
	data2D_->setColXUnit(XUnit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::colXUnit()
///
/// \brief	return the unit of the X column
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE QString SData2DScript::colXUnit()
{
	return data2D_->colXUnit();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::setColYUnit( QString YUnit )
///
/// \brief	set the unit of the Y column
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::setColYUnit( QString YUnit )
{
	data2D_->setColYUnit(YUnit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::colYUnit()
///
/// \brief	return the unit of the Y column
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE QString SData2DScript::colYUnit()
{
	return data2D_->colYUnit();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::addComent( QString com )
///
/// \brief	add a comment that will be put in the header
///
/// \param com	The new line of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::addComment( QString com )
{
	data2D_->addComment(com);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2DScript::addComment( QString com )
///
/// \brief	add a comment that will be put in the header
///
/// \param return an QsScript array with all the comments
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE QScriptValue SData2DScript::comment() const
{
	QString qsCmd;
	QTextStream qtsCmd(&qsCmd);
	QStringList comments = data2D_->comment();


	qtsCmd << "new Array(" ;

	for (int i=0; i<comments.size()-1; i++){
		qtsCmd << "\"" << comments.at(i) << "\",";
	}

	qtsCmd << comments.at(comments.size()-1) << ")" ;

	qsCmd = qtsCmd.readAll();

	QScriptValue res = this->engine()->evaluate(qsCmd);

	return res;
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SData2DScript::clearComment(void)
///
/// \brief	(SCRIPTABLE) Empty the data 
///
/// \sa SData2DScript::clearComment()
/////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::clearComment()
{
	data2D_->clearComment();

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SData2DScript::size(void)
///
/// \brief	(SCRIPTABLE) Gets the count of element. 
///
/// \sa SData2DScript::count()
/////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE int SData2DScript::size()
{
	return data2D_->size();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SData2DScript::size(void)
///
/// \brief	(SCRIPTABLE) Gets the count of element. 
///
/// \sa SData2DScript::count()
/// \return an array : (x,y)	
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE QScriptValue SData2DScript::max( int const start /*= 0*/ ) const
{
	 SData2D::DataPoint pt = data2D_->max(start) ;

	 QString qsCmd;
	 QTextStream qtsCmd(&qsCmd);

	 QScriptValue res;

	 try{
		
			 qtsCmd << "new Array(" << pt.x_ <<" , " << pt.y_ << ")" ;
			 res = this->engine()->evaluate(qsCmd);

	 }catch(QString error){
		 qtsCmd << "new Array(0 , 0)" ;
		 qDebug() << error;
		 res = this->engine()->evaluate(qsCmd);
	 }

	 return res;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SData2DScript::setx( int i, double val )
///
/// \brief	(SCRIPTABLE) set the value val at index position i in the abscissa of the data.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param	i	index of the wanted value.
/// \param	val	the wanted value.
///
/// If the index i is out of bounds, the function do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::setx( int i, double val )
{
	if(i < data2D_->x()->size()){
		data2D_->x()->replace(i,val) ;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SData2DScript::setx( int i, double val )
///
/// \brief	(SCRIPTABLE) set the value val at index position i in the ordinate of the data.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param	i	index of the wanted value.
/// \param	val	the wanted value.
///
/// If the index i is out of bounds, the function do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::sety( int i, double val )
{
	if(i < data2D_->y()->size()){
		data2D_->y()->replace(i,val) ;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 void SData2DScript::setData( SData2D * data )
///
/// \brief	(SCRIPTABLE) Copy an other SData2D in this one. 
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param	data the data to copy.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::setData( SData2D  data )
{

	data2D_->setData(data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::delItem( int i )
///
/// \brief	(SCRIPTABLE) Delete an item of the data.
///
/// \param i the index of the item
///
/// if i is out of range, do nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SData2DScript::delItem( int i ){
	data2D_->delItem(  i );
}
