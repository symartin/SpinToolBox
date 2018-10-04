/*
Copyright (C) 2010 Sylvain Martin (Spintec - CEA/CNRS/UJF/G-INP)
All rights reserved.

This file is part of the Spintoolbox


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

#include "SData2D.h"
#include "SDataError.h"
#include <QtCore>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2D::SData2D()
///
/// \brief	Default constructor. 
///
/// \author	Sylvain Martin
/// \date	1/25/2011
////////////////////////////////////////////////////////////////////////////////////////////////////

SData2D::SData2D():
        NbMetatData_(0),
		MagToolBoxCompatibility_(false)
{
			colName_.append("x");
			colName_.append("y");

			colUnit_.append("A.U.");
			colUnit_.append("A.U.");
}




////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2D::SData2D(QFile * file)
///
/// \brief	Constructor which open a data file. 
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \exception SERROR_NO_SUPPORTED_FILE File type no supported
/// \exception SERROR_INACCESSIBLE_FILE The file is inaccessible
/// \exception SERROR_NO_VALIDE_DATA One line of the data file is not correct
/// 								 
/// \param file  pointer to the file we want read data.
/// 				
///   create an object SDataMagToolBox, then open and read data
///   from a SData2D data file, you can access data with the
///   data() function.
////////////////////////////////////////////////////////////////////////////////////////////////////

SData2D::SData2D(QFile * file) :
	NbMetatData_(0),
	MagToolBoxCompatibility_(false),
	ptFile(NULL)
{
	colName_.append("x");
	colName_.append("y");

	colUnit_.append("A.U.");
	colUnit_.append("A.U.");
	this->openFile(file);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2D::SData2D(QFile * file)
///
/// \brief	Constructor which open a data file. 
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \exception SERROR_NO_SUPPORTED_FILE File type no supported
/// \exception SERROR_INACCESSIBLE_FILE The file is inaccessible
/// \exception SERROR_NO_VALIDE_DATA One line of the data file is not correct
/// 								 
/// \param file  path of the file we want read data.
/// 				
///   create an object SDataMagToolBox, then open and read data
///   from a SData2D data file, you can access data with the
///   data() function.
////////////////////////////////////////////////////////////////////////////////////////////////////
SData2D::SData2D( QString const file ):
	NbMetatData_(0),
	MagToolBoxCompatibility_(false)
{
	ptFile = new QFile(file);

	colName_.append("x");
	colName_.append("y");

	colUnit_.append("A.U.");
	colUnit_.append("A.U.");
	this->openFile(file);

	SData2D(ptFile);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2D::SData2D(QList<double> const xList, QList<double> const yList )
///
/// \brief	Constructor which file the data with the two lists. 
///
///
/// \param	xList	List of x value. 
/// \param	yList	List of y value. 
/// 				
////////////////////////////////////////////////////////////////////////////////////////////////////

SData2D::SData2D(QList<double> const xList, QList<double> const yList ) :
        NbMetatData_(0){

	if( xList.size() != yList.size()){
		qDebug("ERROR : SData2D::SData2D(QList<double> const xList, QList<double> const yList ) : xList.size() != yList.size() ");
		return;
	}

	this->x_.append(xList);
	this->y_.append(yList);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2D::SData2D(QList<double> const xList, QList<double> const yList )
///
/// \brief	destructor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SData2D::~SData2D(){
	if(ptFile == NULL){
		delete ptFile;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::openFile(QString file)
///
/// \brief	open a data file and put it in the data object. 
///
///
///  \exception SERROR_NO_SUPPORTED_FILE File type no supported
///  \exception SERROR_INACCESSIBLE_FILE The file is inaccessible
///  \exception SERROR_NO_VALIDE_DATA One line of the data file is not correct
///
///  \param	file	The file that we want load. 
/// 				
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2D::openFile(QString file){
    ptFile = new QFile(file);
    this->openFile(ptFile);
}




////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QVariant SData2D::metaData(QString const key) const
///
/// \brief	return the MetaData with the key give in argument. 
///
/// \param	key	The key in the map table. 
///
/// \return	the MetaData with the key give in argument. 
/// \remark return nothing (an empty QVarient) if the key is not found
////////////////////////////////////////////////////////////////////////////////////////////////////

QVariant SData2D::metaData(QString const key) const{

    if(this->MetaData_.contains(key)){
        return this->MetaData_.value(key);
    }else{
      //  throw SERROR_NO_FOUND_METADATA;
		qDebug() << key << " " << SERROR_NO_FOUND_METADATA;
        return QVariant("");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SData2D::metaDataAsDouble(QString const key) const
///
/// \brief	return the MetaData with the key give in argument. 
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \exception	SERROR_NO_CANNOT_CONVERT_METADATA	Thrown when This metadata cannot be converted. 
/// \exception	SERROR_NO_FOUND_METADATA			Thrown when the key is no found. 
///
/// \param	key	The key in the map table. 
/// 			
/// \deprecated use \c metaData(QString const key) instead.
/// 			
/// \return	the MetaData with the key give in argument. 
/// 		
///   return the MetaData with the key give in argument convert into
///   double. This function is useful when the metadata value has a unit,
///   like MetaData("Freq") = 0.500 GHz, because the toDouble() function
///   cannot correctly convert it.
////////////////////////////////////////////////////////////////////////////////////////////////////

double SData2D::metaDataAsDouble(QString const key) const{
    QRegExp regexp;
    regexp.setPattern("\\s+\\D*$");

    bool okConvert;
    double value;

    if(this->MetaData_.contains(key)){


        value = this->MetaData_.value(key).toString().replace(regexp,"").toDouble(&okConvert);

        if(okConvert){
            return value;
        }else{
            throw SERROR_NO_CANNOT_CONVERT_METADATA;
        }
    }else{
        throw SERROR_NO_FOUND_METADATA;
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setMetaData(QString const key, QVariant const value)
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

void SData2D::setMetaData(QString const key, QVariant const value){
 MetaData_.insert(key,value);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::append (double const x, double const y)
///
/// \brief	add a couple of value at the SData2D. 
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \param	x	The x value. 
/// \param	y	The y value. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2D::append (double const x, double const  y){
    this->x_.append(x);
    this->y_.append(y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::append (QList<double> const xList, QList<double> const yList)
///
/// \brief	add a list of element at SData2D
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \param	xList	List of x values. 
/// \param	yList	List of y values. 
/// 				
/// \warning	it does not check if the size of rhe x list ant of
///				the y list is the same.
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2D::append (QList<double> const xList, QList<double> const yList){
    this->x_.append(xList);
    this->y_.append(yList);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::append (SData2D::DataPoint const point)
///
/// \brief	add a point at the SData2D
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \param	point	The SData2D::DataPoint const to append. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2D::append (SData2D::DataPoint const point){
    this->x_.append(point.x_);
    this->y_.append(point.y_);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::openFile(QFile * file)
///
/// \brief	Open and read data from a data file
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
///   \exception SERROR_NO_SUPPORTED_FILE File type no supported
///   \exception SERROR_INACCESSIBLE_FILE The file is inaccessible
///   \exception SERROR_NO_VALIDE_DATA One line of the data file is not correct
///
/// \param	file	file from which we want read data
/// 				
/// Open and read data from a data file,
///   you can acces data with the \c data() function.
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2D::openFile(QFile * file){

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
	//in MagToolBox the first line contains 5 and the number of line
	// so we skip it.
		line = streamH.readLine();
			if(line[0]== '5'){
				MagToolBoxCompatibility_ = true; // c'est un fichier magtoolBox
				nbHLine++;
			}
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

   //on tourne sur tout les lignes
   while( !stream.atEnd() ) {
        line = stream.readLine();
		
        //traitetement des metadata
        if(line[0]== '#'){
			if(i<nbHLine-2){
				 treatSharpLine(line);
			}else{
				colName_ = line.replace("#","").trimmed().split(QRegExp("\\s+"));
				line = stream.readLine();
				i++;
				colUnit_ = line.replace("#","").replace("(","").replace(")","").trimmed().split(QRegExp("\\s+"));
			}
        // si la ligne n'est pas vierge
        }else if(line[0]!= '\n'){

            // on extrait les colonnes de la chaine de caractaires
            SplitList = line.split(QRegExp("\\s+"));

            // on rempli la liste
            this->x_.append(SplitList[0].toDouble());
            this->y_.append(SplitList[1].toDouble());

        }

		i++; // current line (without the MagToolBoxCompatibility_)
    }

   file->close();




}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::saveFile(QString file)
///
/// \brief	save data to a MagToolBox data file. 
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \param	file	file from which we want write data. 
/// 				
/// \exception SERROR_INACCESSIBLE_FILE The file is inaccessible
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2D::saveFile(QString file){

	QDir dir(file);
	QString path = file.left(file.size() - dir.dirName().size()) ;
	dir.mkpath (path) ;

	QFile *pfile = new QFile(file);

	saveFile(pfile);
	delete(pfile);
 }



////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::saveFile(QFile * file)
///
/// \brief	save data to a MagToolBox data file
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \exception	SERROR_INACCESSIBLE_FILE	Thrown when The file is inaccessible
///
/// \param file  file that we want write data
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2D::saveFile(QFile * file){
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        throw SERROR_INACCESSIBLE_FILE;

    QTextStream stream (file);

	// Compatibility with file magtoolbox
	if(MagToolBoxCompatibility_) {
		stream << 5 << "\t" << y_.size() << "\n";
	}
	

   // the comments are not metadata (like a=b)
   for (int i=0; i < comment_.size(); i++ ){
       stream << "# " << comment_.value(i);
   }



   //les autres meta data
   stream << "\n#";
    foreach (QString key, MetaData_.keys()){
            stream <<"\n# " << key << " = " << MetaData_.value(key).toString() ;

    }

    // les entetes des collones
	stream << "\n#\n#";
    for(int i=0; i<colName_.size(); i++){
        stream << colName_.value(i)<< "\t" ;
    }
	stream << "\n#";
	for(int i=0; i<colUnit_.size(); i++){
		stream << "(" << colUnit_.value(i) << ")\t";
	}


    // les data
    for(int i=0; i< y_.size(); i++){
        stream << "\n" << x_.value(i)<< "\t" << y_.value(i)  ;
    }

   file->close();
 }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::treatSharpLine(QString line)
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

void SData2D::treatSharpLine(QString line){
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
/// \fn	void SData2D::slideAverage(int const windows, double const PeackProtectCoeff)
///
/// \brief	Slide average. 
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
///  \param windows size of the average windows, it has to be greater than 1
///  \param PeackProtectCoeff avoids to flatten the very thin peaks, removes these points from the average
/// 							
/// do a slide average of the data, with a slide windows. start at 0
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

void SData2D::slideAverage(int const windows, double const PeackProtectCoeff){

  double somme =0;
  double prev=0;
  double next=0;
  double endAverage;
  double average=0;
  int size = y_.size();

  // fait la somme des windows premiers points
  for(int i=0; i<windows; i++){
      somme += this->y_.at(i);
  }

  prev = y_.at(0);
  y_.replace(0,somme/windows);

  // pour chaque point on fait glisser la moyenne
  for(int i=0; i< size- windows; i++){
    next = y_.at(i+windows-1);
    somme = (somme +  next - prev);
    prev = y_.at(i);
    average = somme/windows;

    // le peak protect est actif
    if((PeackProtectCoeff !=0)  ){
        //A > B et A !=0 pente décendante
        if((y_.at(i) > average) && (y_.at(i)!=0)){

            //A/B < peakCoeff => on a un pics fin
            // sinon on remplace
            if( !(abs(average/y_.at(i))<PeackProtectCoeff)){
                y_.replace(i, average);
            }
        //A < B et B !=0 pente montante
        }else if((y_.at(i) < average) && (average!=0)){

            //A/B < peakCoeff => on a un pics fin
            // sinon on remplace
            if( !(abs(y_.at(i)/average) < PeackProtectCoeff)){
                y_.replace(i, average);
            }

        }
    }else{ // on ne se souci pas des pics
       y_.replace(i, average);
   }


  }
  endAverage = y_.at(size- windows-1);

  // les derneir point sont trétait a part car
  // il n'y a plus assez de point pour continuer à
  // faire glisser la fenetre
  for(int i=size-windows-1; i< size; i++){
      somme =0;
      for(int j=0; j<windows; j++){
          if(i+j<size){
              somme+=y_.at(i+j);
          }else{
             somme+=endAverage;
          }
      }
      y_.replace(i,somme/windows);
      endAverage=somme/windows;
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2D::DataPoint SData2D::max(int const start) const
///
/// \brief	   return the point of the first max find between "start" en the end
///			   of the data
///
/// \author	Sylvain Martin
/// \date	1/25/2011
///
/// \exception	SERROR_OUT_OF_BOUNDS	The specified index is out of bounds
///
/// \param	start	The start. 
///
/// \return	The maximum value. 
////////////////////////////////////////////////////////////////////////////////////////////////////

SData2D::DataPoint SData2D::max(int const start /* =0 */) const{

    if (start> y_.size()){
        throw SERROR_OUT_OF_BOUNDS;
    }else if(y_.size() ==0 ){
		 SData2D::DataPoint point;
		 point.x_=0;
		 point.y_=0;
		return point;
	}


    double max=y_.at(start);

    SData2D::DataPoint point;
    int coordMaxi;

    for( int i = start; i <y_.size() ; i++ ){
        if(y_.at(i)>max){
            max = y_.at(i);
            coordMaxi = i;
        }
    }
    point.x_ = x_.value(coordMaxi);
    point.y_ = max;

    return point;

}



////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SData2D::count(void)
///
/// \brief	Gets the count of element. 
///
/// \sa SData2D::size()
////////////////////////////////////////////////////////////////////////////////////////////////////

int SData2D::count(void) const{
		return x_.count();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SData2D::SData2D(SData2D &data)
///
/// \brief	Copy constructor. 
///
/// \author	Sylvain Martin
/// \date	2/2/2011
///
/// \param [in,out]	data	The data. 
////////////////////////////////////////////////////////////////////////////////////////////////////

SData2D::SData2D(SData2D * data){
	this->x_ = data->x_;
	this->y_ = data->y_;
	this->MetaData_ = data->MetaData_;
	this->NbMetatData_ = data->NbMetatData_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setData(SData2D * data)
///
/// \brief	Copy an other SData2D in this one. 
///
/// \author	Sylvain Martin
/// \date	12/09/2011
///
/// \param [in]	data	The data. 
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::setData(SData2D  data){
	this->x_ = data.x_;
	this->y_ = data.y_;
	this->MetaData_ = data.MetaData_;
	this->NbMetatData_ = data.NbMetatData_;

	this->setColXName(data.colXName());
	this->setColYName(data.colYName());
	this->setColXUnit(data.colXUnit());
	this->setColYUnit(data.colYUnit());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::overwrite(SData2D &data)
///
/// \brief	Overwrites all the data an replace by argument data. 
///
/// \author	Sylvain Martin
/// \date	2/2/2011
///
/// \param [in,out]	data	The data. 
/// 				
/// this function is useful for the script part of the application, for the function
///  \c SData2DScript::fromScriptValue
///     
///  \sa SData2D::overwrite(SData2D &data)
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2D::overwrite(SData2D &data){

	this->x_ = data.x_;
	this->y_ = data.y_;
	this->MetaData_ = data.MetaData_;
	this->NbMetatData_ = data.NbMetatData_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::overwrite(SData2D &data)
///
/// \brief	Overwrites all the data an replace by argument data. 
///
/// \author	Sylvain Martin
/// \date	2/2/2011
///
/// \param [in,out]	data	The data. 
/// 				
/// this function is useful for the script part of the application, for the function
///  \c SData2DScript::fromScriptValue
///     
///  \sa SData2D::overwrite(SData2D *data)
////////////////////////////////////////////////////////////////////////////////////////////////////

void SData2D::overwrite(SData2D *data){

	this->x_ = data->x_;
	this->y_ = data->y_;
	this->MetaData_ = data->MetaData_;
	this->NbMetatData_ = data->NbMetatData_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::addComment( QString com )
///
/// \brief	add a comment that will be put in the header
///
/// \param com	The new line of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::addComment( QString com ){
	comment_.append(com);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::addComment( QString com )
///
/// \brief	add a comment that will be put in the header
///
/// \param com	The \c QList<QString> of new lines of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::addComment(QStringList comList ){
	comment_.append(comList);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<QString> SData2D::comment() const
///
/// \brief	return the list of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList SData2D::comment() const
{
	return comment_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<QString> SData2D::comment() const
///
/// \brief	return the list of comment
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::setComment( QStringList comList )
{
	comment_ = comList;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::clearComment()
///
/// \brief	clear the all comments
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::clearComment()
{
	comment_.clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::clearMetaData()
///
/// \brief	clear the all the metadata
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::clearMetaData()
{
	MetaData_.clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColName( QString Xname, QString Yname )
///
/// \brief	set the name of the columns
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::setColName( QString Xname, QString Yname )
{
	colName_.clear();
	colName_.append(Xname);
	colName_.append(Yname);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColXName( QString Xname)
///
/// \brief	set the name of the X column
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::setColXName( QString Xname )
{
	colName_.replace(0,Xname);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColYName( QString Yname)
///
/// \brief	set the name of the X column
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::setColYName( QString Yname )
{
	colName_.replace(1,Yname);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColUnit( QString XUnit, QString YUnit )
///
/// \brief	set the units of the columns
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::setColUnit( QString XUnit, QString YUnit )
{
	colUnit_.clear();
	colUnit_.append(XUnit);
	colUnit_.append(YUnit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColXUnit( QString XUnit )
///
/// \brief	set the unit of the X column
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::setColXUnit( QString XUnit )
{
	colUnit_.replace(0,XUnit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColXUnit( QString XUnit )
///
/// \brief	set the unit of the X column
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::setColYUnit( QString YUnit )
{
	colUnit_.replace(0,YUnit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColXUnit( QString XUnit )
///
/// \brief	return the name of the X column
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SData2D::colXName()
{
	return colName_.value(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColXUnit( QString XUnit )
///
/// \brief	return the name of the y column
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SData2D::colYName()
{

	
	return colName_.value(1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColXUnit( QString XUnit )
///
/// \brief	return the unit of the X column
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SData2D::colXUnit()
{
	return colUnit_.value(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::setColXUnit( QString XUnit )
///
/// \brief	return the unit of the y column
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SData2D::colYUnit()
{
	return colUnit_.value(1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::sizeComment()
///
/// \brief	return the number of comments
////////////////////////////////////////////////////////////////////////////////////////////////////
int SData2D::sizeComment()
{
	return comment_.size();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SData2D::size(void)
///
/// \brief	Gets the count of element. 
///
/// \sa SData2D::count()
////////////////////////////////////////////////////////////////////////////////////////////////////
int SData2D::size() const
{
	return count();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<double> * SData2D::x()
///
/// \brief	Gets a pointer to the x data QList
///
/// \sa SData2D::y()
////////////////////////////////////////////////////////////////////////////////////////////////////
QList<double> * SData2D::x() 
{
	return &x_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QList<double> * SData2D::y()
///
/// \brief	Gets a pointer to the y data QList
///
/// \sa SData2D::x()
////////////////////////////////////////////////////////////////////////////////////////////////////
QList<double> * SData2D::y() 
{
	return &y_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double * SData2D::xData()
///
/// \brief	Gets a pointer to the x data like a plain C++ array
///
/// \sa SData2D::yData()
////////////////////////////////////////////////////////////////////////////////////////////////////
double * SData2D::xData() 
{
	 vectX = x_.toVector();
	return vectX.data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double * SData2D::yData()
///
/// \brief	Gets a pointer to the y data like a plain C++ array
///
/// \sa SData2D::xData()
////////////////////////////////////////////////////////////////////////////////////////////////////
double * SData2D::yData() 
{
	vectY = y_.toVector();
	return vectY.data();

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SData2D::delItem( int i )
///
/// \brief	delete an item of the data
///
/// \param i the index of the item
///
/// if i is out of range, do nothing
////////////////////////////////////////////////////////////////////////////////////////////////////
void SData2D::delItem( int i )
{
	 if(i< this->size()){
		 x_.removeAt(i);
		 y_.removeAt(i);
	 }
}
