/*
Copyright (C) 2010-2011 Sylvain Martin (Spintec - CEA/CNRS/UJF/G-INP)
All rights reserved.

This file is part of the SpinToolBox

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/


#include "SData.h"
#include <QtCore>
#include "SDataError.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QVariant SData::metaData(QString const key) const
///
/// \brief	return the MetaData with the key give in argument. 
///
/// \param	key	The key in the map table. 
///
/// \return	the MetaData with the key give in argument. 
/// \remark return nothing (an empty QVarient) if the key is not found
////////////////////////////////////////////////////////////////////////////////////////////////////
QVariant SData::metaData(QString const key) const{

	if(this->MetaData_.contains(key)){
		return this->MetaData_.value(key);
	}else{
		//  throw SERROR_NO_FOUND_METADATA;
		qDebug() << key << " " <<  SERROR_NO_FOUND_METADATA;
		return QVariant("");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::setMetaData(QString const key, QVariant const value)
///
/// \brief	add or reset a key of the metadata. 
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \param	key		The key. 
/// \param	value	The value. 
/// 				
///  \warning if the key already exist, this function just overwrite it.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData::setMetaData(QString const key, QVariant const value){
	MetaData_.insert(key,value);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::treatSharpLine(QString line)
///
/// \brief	Extract the metadata from a comment line. 
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
///   \param line QString starting with a sharp character
///
///   add element to the MetaData_ map table. extract the metadata
///   from line in the form of "# variable = value". if equal character
///   is not found the line is add to the com key of the map table.
/// 				
/// \warning
///       - If a line contains several couple, i.e. "a=b;c=d;e=f",
///      this function split its : MetaData_["a"]==b and MetaData_["c"]==d
///       and MetaData_["e"]==f.
///       - If a line contains a odd equal symbol split, i.e. "a=b;c=" ,
///       this function let empty the value of the odd key : MetaData_["a"]==b
///       and MetaData_["c"]== ""
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData::treatSharpLine(QString line){
	QStringList SplitListEqual;
	QStringList SplitListSemiColon;
	static bool FirstComment = false;

	line = line.right(line.length()-1);

	// on découpe selon les points-virgules
	SplitListSemiColon = line.split(";");

	//on fait le tour des element séparés par des points-virgules
	for(int k=0; k<SplitListSemiColon.size();k++){
		// if is it a couple a=b, but not a escape equal character '\='
		if(line.indexOf("=")!=-1 && line.indexOf("!=") == -1 ){  // si c'est un couple a=b

			SplitListEqual = SplitListSemiColon[k].split("=");
			this->NbMetatData_++;

			// on découpe pour chaque ligne (il peu y avoir plusieur couple a=b
			for(int i=0; i<SplitListEqual.size();i=i+2){
				if ((i+1)<SplitListEqual.size()){ // couple entier a=b

					this->MetaData_.insert(SplitListEqual[i].trimmed(),QVariant(SplitListEqual[i+1].trimmed()));

				}else{ // demi couple a=
					MetaData_[SplitListEqual[i].trimmed()]=QVariant("");
				}
			}

			// on evite les lignes séparatrices avec que des #
		}else if (!(line.replace("#","").trimmed() == "")){
			comment_.append(line.replace("#","").trimmed().replace("\\=","="));

		}

	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::setColName( int ColNum,QString name )
///
/// \brief	add a comment that will be put in the header
///
/// \param com	The new line of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData::setColName( int ColNum,QString name ){
	if(ColNum < colName_.size()){
		colName_.replace(ColNum,name);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::addComment( QString com )
///
/// \brief	add a comment that will be put in the header
///
/// \param com	The new line of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData::addComment( QString com ){
	comment_.append(com);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::addComment( QString com )
///
/// \brief	add a comment that will be put in the header
///
/// \param com	The \c QList<QString> of new lines of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData::addComment(QStringList comList ){
	comment_.append(comList);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<QString> SData::comment() const
///
/// \brief	return the list of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList SData::comment() const{
	return comment_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<QString> SData::comment() const
///
/// \brief	return the list of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData::setComment( QStringList comList ){
	comment_ = comList;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::clearComment()
///
/// \brief	clear the all comments
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData::clearComment(){
	comment_.clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::sizeComment()
///
/// \brief	return the number of comments
////////////////////////////////////////////////////////////////////////////////////////////////////
int SData::sizeComment()
{
	return comment_.size();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::clearMetaData()
///
/// \brief	clear the all the metadata
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData::clearMetaData(){
	MetaData_.clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData::colName( int ColNum )
///
/// \brief	
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SData::colName( int ColNum ){
	if(ColNum < colName_.size()){
		return colName_.at(ColNum);
	}

	return "";

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::setColUnit( int ColNum, QString Unit )
///
/// \brief	
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData::setColUnit( int ColNum, QString Unit ){
	if(ColNum < colUnit_.size()){
		colUnit_.replace(ColNum,Unit);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SData::colUnit( int ColNum )
///
/// \brief	
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SData::colUnit( int ColNum ){
	if(ColNum < colUnit_.size()){
		return colUnit_.at(ColNum);
	}

	return "";
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData::extractHeader()
///
/// \brief	This function extract the informations from the header (lines beginning by #).
///
/// \return the number of lines of header.
///
/// \remark The number returned does not count the line for the compatibility with MagToolBox
////////////////////////////////////////////////////////////////////////////////////////////////////
int SData::extractHeader(const QFile * fl){

	
	QFile * file = new QFile(fl->fileName());
	QStringList SplitList;
	int nbHLine=0;
	QString line;
	int i=0;

	this->setMetaData("name",file->fileName());

	if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
		throw SERROR_INACCESSIBLE_FILE;


	QTextStream streamString (file);
	QString allfile = streamString.readAll();

	QTextStream streamH(&allfile);
	//in MagToolBox the first line contains the number of line
	// so we skip it.
	if(MagToolBoxCompatibility_) streamH.readLine();

	//we count the number of header lines
	while( !streamH.atEnd() ) {
		line = streamH.readLine();
		if(line[0]== '#')
			nbHLine++;
		else{
			break;
		}
	}
	//rest the stream
	QTextStream stream (&allfile);

	//in MagToolBox the first line contains the number of line
	// so we skip it.
	if(MagToolBoxCompatibility_) stream.readLine();

	// we make a loop for treat all the header lines
	for(int i=0; i <nbHLine; i++){
		line = stream.readLine();

		//for the meta data
			if(i<nbHLine-2){
				treatSharpLine(line);
			}else{ // for the column names and the column units
				colName_ = line.replace("#","").trimmed().split(QRegExp("\\s+"));
				line = stream.readLine();

				colUnit_ = line.replace("#","").replace("(","").replace(")","").trimmed().split(QRegExp("\\s+"));
			}
		}
	return nbHLine;
	}

	

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData::SData()
///
/// \brief	default constructor
////////////////////////////////////////////////////////////////////////////////////////////////////
SData::SData():
	MagToolBoxCompatibility_(true)
{

}

SData::~SData()
{

}

int SData::numCol()
{
	return numCol_;
}
