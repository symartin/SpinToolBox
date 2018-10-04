/*
Copyright (C) 2010-2012 Sylvain Martin (Spintec - CEA/CNRS/UJF/G-INP)
All rights reserved.

This file is part of the SpinToolBox project

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
#include "Splot2D.h"
#include <QtCore>
#include <QtGui>

// initiation des membres static
QList<SPlot2D*> SPlot2D::lstPlot2D;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn SPlot2D::SPlot2D(QWidget *parent)
///
/// \brief	constructor.
///
/// \param parent if not null, the Qt parent
////////////////////////////////////////////////////////////////////////////////////////////////////
SPlot2D::SPlot2D(QWidget *parent /* = NULL */)
	:totCurve_(-1),QMainWindow(parent),autoReplot_(true),antialiasing_(false),winScale(NULL),pointSelection_(false)
{
	
	setupUI();
	lstPlot2D.append(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn SPlot2D::SPlot2D( SData2D *data, QWidget *parent)
///
/// \brief	constructor.
///
/// \param data a pointer to the data that we want in first curve
/// \param parent if not null, the Qt parent
///
/// \warning do not destroy the data before the complete load of the windows
////////////////////////////////////////////////////////////////////////////////////////////////////
SPlot2D::SPlot2D(SData2D *data ,QWidget *parent /*= 0*/)
	:totCurve_(0),QMainWindow(parent),autoReplot_(true),antialiasing_(false),winScale(NULL),pointSelection_(false)
{
	
	lstPlot2D.append(this);
	setupUI();

	// create graph and assign data to it:
	customPlot_->addGraph();
	customPlot_->graph(0)->setData(data->x(), data->y());
	customPlot_->graph(0)->setPen(QPen(Qt::blue));
	customPlot_->graph(0)->setBrush(QBrush(QColor(0, 0, 0, 0)));


	// give the axes some labels:
	customPlot_->xAxis->setLabel(data->colXName() + " (" + data->colXUnit() +")");
	customPlot_->xAxis->setGrid(true);

	customPlot_->yAxis->setLabel(data->colYName() + " (" + data->colYUnit() +")");
	customPlot_->yAxis->setGrid(true);

	// set axes ranges, so we see all data:
	doAutoScale();


}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn SPlot2D::~SPlot2D()
///
/// \brief	destructor.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SPlot2D::~SPlot2D(){
	lstPlot2D.removeAll(this);
	if(winScale!= NULL)  delete winScale;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn QCustomPlot * SPlot2D::CustomPlotWidget()
///
/// \brief	return the QCustomPlot object (it's a C++ object, not scriptable).
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QCustomPlot * SPlot2D::CustomPlotWidget(){
	return customPlot_;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setupUI(void)
///
/// \brief	Sets up the user interface.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::setupUI(void){
	this->setMinimumSize(200,200);
	this->setGeometry(200,200,300,300);
	this->setObjectName("Plot 2D");
	this->setWindowIcon(QIcon(":/compass32.png"));

	// on desactive le menu contextuel, care je veux metre le mien
	// permet d'enlver le menu contextuel des toolbars...
	this->setContextMenuPolicy(Qt::NoContextMenu);

	customPlot_ = new QCustomPlot(this);
	this->setCentralWidget(customPlot_);

	// configure right and top axis to show ticks but no labels (could've also just called customPlot->setupFullAxesBox):
	customPlot_->xAxis2->setVisible(true);
	customPlot_->xAxis2->setTickLabels(false);
	customPlot_->yAxis2->setVisible(true);
	customPlot_->yAxis2->setTickLabels(false);
	// make left and bottom axes always transfer their ranges to right and top axes:
	customPlot_->connect(customPlot_->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot_->xAxis2, SLOT(setRange(QCPRange)));
	customPlot_->connect(customPlot_->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot_->yAxis2, SLOT(setRange(QCPRange)));
	// make range movable by mouse interaction (click and drag):
	customPlot_->setRangeDrag(Qt::Horizontal | Qt::Vertical);
	customPlot_->setRangeZoom(Qt::Horizontal | Qt::Vertical);


	connect(customPlot_,SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(mouseMouved(QMouseEvent*)));

	//we initialize the statue bar
	this->statusBar()->showMessage("",0);
	// set the global properties
	setAntialiasing(antialiasing_);

	// let's do a tool bar
	toolBar = new QToolBar("Main toolbar", this);
	toolBar->setIconSize(QSize (40,40));

	//le bouton autoscale
	actAutoScale = new QAction("&Auto Scale",this);
	actAutoScale->setIcon(QIcon(":/icon/autoscale.png"));
	actAutoScale->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
	actAutoScale->setToolTip("Auto Scale (Ctrl + A)");
	toolBar->addAction(actAutoScale);
	connect(actAutoScale, SIGNAL(triggered()),this, SLOT(doAutoScale()));

	//le bouton Set Scale
	actSetScale = new QAction("&Set Scale",this);
	actSetScale->setIcon(QIcon(":/icon/setsacle.png"));
	actSetScale->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	actSetScale->setToolTip("set Scale (Ctrl + S)");
	toolBar->addAction(actSetScale);
	connect(actSetScale, SIGNAL(triggered()),this, SLOT(doSelectScaleWin()));

	//le bouton autoscale
	actSetAutoScale = new QAction("&Set AutoScale",this);
	actSetAutoScale->setIcon(QIcon(":/icon/runningscale.png"));
	actSetAutoScale->setCheckable ( true );
	actSetAutoScale->setChecked(true);
	actSetAutoScale->setToolTip("AutoScale when the data are update");
	toolBar->addAction(actSetAutoScale);
	connect(actSetAutoScale, SIGNAL(toggled(bool)),this, SLOT(setAutoScale(bool)));

	//le bouton antialiasing
	actSetAntialiasing = new QAction("&Set antialiasing",this);
	actSetAntialiasing->setIcon(QIcon(":/icon/antialiasing.png"));
	actSetAntialiasing->setCheckable ( true );
	actSetAntialiasing->setChecked(false);
	actSetAntialiasing->setToolTip("Disable antialiasing speed up the rendering");
	toolBar->addAction(actSetAntialiasing);
	connect(actSetAntialiasing, SIGNAL(toggled(bool)),this, SLOT(setAntialiasing(bool)));

	//le bouton Point selection
// 	actPointSelection = new QAction("&Point selection",this);
// 	actPointSelection->setIcon(QIcon(":icon/pointselection.png"));
// 	actPointSelection->setCheckable (true);
// 	actPointSelection->setChecked(false);
// 	actPointSelection->setToolTip("Activate/deactivate point selection");
// 	toolBar->addAction(actPointSelection);
// 	connect(actSetAntialiasing, SIGNAL(toggled(bool)),this, SLOT(setPointSelection(bool)));

	// on met la bar d'outil en place
	toolBar->setObjectName("Main toolbar");
	toolBar->setFloatable (false);
	toolBar->setMovable (false);

	addToolBar(toolBar);
	
	// Menu contextual
	mnuContextual = new QMenu(this);
	//le bouton Copy coordinates
	actCopyCoor = new QAction("Copy coordinates\tCtrl + C",this);
	actCopyCoor->setToolTip("Put the coordinates of this point in the clipboard");
	mnuContextual->addAction(actCopyCoor);
	connect(actCopyCoor, SIGNAL(triggered()),this, SLOT(doCopyCoor()));

	//le bouton Save the picture
	actSaveImage = new QAction("Save the picture",this);
	actSaveImage->setToolTip("Save the graph in a file");
	mnuContextual->addAction(actSaveImage);
	connect(actSaveImage, SIGNAL(triggered()),this, SLOT(doSaveImage()));

	//le bouton Copy coordinates
	actOpt = new QAction("Option",this);
	actOpt->setToolTip("Option for the graph");
	mnuContextual->addAction(actOpt);
	connect(actOpt, SIGNAL(triggered()),this, SLOT(doOpt()));

	//we put an icon
//	QIcon icon;
//	icon.addFile(QString::fromUtf8(":/compass.ico"), QSize(), QIcon::Normal, QIcon::Off);
//	this->setWindowIcon(icon);

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QColor SPlot2D::stringToColor(QString name)
///
/// \brief	(Private) 
///
/// \param name the name of the color
///
///
/// Return a color from its name.
////////////////////////////////////////////////////////////////////////////////////////////////////
// QColor SPlot2D::stringToColor(QString colorName){
// 	QColor color;
// 
// 	if(colorName.contains("white", Qt::CaseInsensitive)){
// 		color.setNamedColor("white") ;
// 
// 	}else if(colorName.contains("black", Qt::CaseInsensitive)){
// 		color.setNamedColor("black") ;
// 
// 	}else if(colorName.contains("red", Qt::CaseInsensitive)){
// 		color.setNamedColor("red") ;
// 
// 	}else if(colorName.contains("darkRed", Qt::CaseInsensitive)){
// 		color.setNamedColor("darkRed") ;
// 
// 	}else if(colorName.contains("green", Qt::CaseInsensitive)){
// 		color.setNamedColor("green") ;
// 
// 	}else if(colorName.contains("darkGreen", Qt::CaseInsensitive)){
// 		color.setNamedColor("darkGreen") ;
// 
// 	}else if(colorName.contains("blue", Qt::CaseInsensitive)){
// 		color.setNamedColor("blue") ;
// 
// 	}else if(colorName.contains("darkBlue", Qt::CaseInsensitive)){
// 		color.setNamedColor("darkBlue") ;
// 
// 	}else if(colorName.contains("cyan", Qt::CaseInsensitive)){
// 		color.setNamedColor("cyan") ;
// 
// 	}else if(colorName.contains("darkCyan", Qt::CaseInsensitive)){
// 		color.setNamedColor("darkCyan") ;
// 
// 	}else if(colorName.contains("magenta", Qt::CaseInsensitive)){
// 		color.setNamedColor("cyan") ;
// 
// 	}else if(colorName.contains("darkMagenta", Qt::CaseInsensitive)){
// 		color.setNamedColor("darkCyan") ;
// 
// 	}else if(colorName.contains("yellow", Qt::CaseInsensitive)){
// 		color.setNamedColor("yellow") ;
// 
// 	}else if(colorName.contains("darkYellow", Qt::CaseInsensitive)){
// 		color.setNamedColor("darkYellow") ;
// 
// 	}else if(colorName.contains("gray", Qt::CaseInsensitive)){
// 		color.setNamedColor("gray") ;
// 
// 	}else if(colorName.contains("darkGray", Qt::CaseInsensitive)){
// 		color.setNamedColor("darkGray") ;
// 
// 	}else if(colorName.contains("lightGray", Qt::CaseInsensitive)){
// 		color.setNamedColor("lightGray") ;
// 	}else{
// 		color.setNamedColor("blue") ;
// 	}
// 	return color;
// }
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QPen SPlot2D::stringToPenStyle( const QString &sytleName )
///
/// \brief	(Private) 
///
/// \param name the name of the style
///
///
/// Return a pen with a style \c name.
////////////////////////////////////////////////////////////////////////////////////////////////////
QPen SPlot2D::stringToPenStyle( const QString &sytleName ) 
{
	QPen pen;

	if(sytleName.contains("SolidLine", Qt::CaseInsensitive)){
		pen.setStyle (Qt::SolidLine) ;

	}else if(sytleName.contains("DashLine", Qt::CaseInsensitive)){
		pen.setStyle (Qt::DashLine) ;

	}else if(sytleName.contains("DotLine", Qt::CaseInsensitive)){
		pen.setStyle (Qt::DotLine) ;

	}else if(sytleName.contains("DashDotLine", Qt::CaseInsensitive)){
		pen.setStyle (Qt::DashDotLine) ;

	}else if(sytleName.contains("DashDotDotLine", Qt::CaseInsensitive)){
		pen.setStyle (Qt::DashDotDotLine) ;
	}else{
		pen.setStyle (Qt::SolidLine) ;
	}
	return pen;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void int SPlot2D::setData(SData2D  *data, int const graphNb)
///
/// \brief	(SCRIPTABLE) 
///
/// \param nbCurve the number of the curve that we want to set data point, by default 0.
///
/// \sa addData
/// \sa clearData
///
/// clear all the data, and add the new data of the curve \a nbCurve, if \a nbCurve is greater that
/// the total of curve, make a new curve an return the number of this on, otherwise return nbCurve.
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE int SPlot2D::setData(SData2D  *data, int const nbCurve)
{

	if (nbCurve > totCurve_){
		customPlot_->addGraph();
		totCurve_++;
		customPlot_->graph(totCurve_)->setData(data->x(),data->y());
		if(autoReplot_) doReplot();
		return totCurve_;

	}else{
		customPlot_->graph(nbCurve)->addData(data->x(),data->y());
		if(autoReplot_) doReplot();
		return nbCurve;
	}

	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void int SPlot2D::setData(SData2D  *data, int const graphNb)
///
/// \brief	(SCRIPTABLE) 
///
/// \param nbCurve the number of the curve that we want to set data point, by default 0.
///
/// \sa addData
/// \sa clearData
///
/// clear all the data, and add the new data of the curve \a nbCurve, if \a nbCurve is greater that
/// the total of curve, make a new curve an return the number of this on, otherwise return nbCurve.
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE int SPlot2D::setData(SData2D  data, int const graphNb)
{


	if (graphNb > totCurve_){
		customPlot_->addGraph();
		totCurve_++;
		customPlot_->graph(totCurve_)->setData(data.x(),data.y());
		if(autoReplot_) doReplot();
		return totCurve_;

	}else{
		customPlot_->addGraph();
		customPlot_->graph(graphNb)->setData(data.x(),data.y());
		if(autoReplot_) doReplot();
		return graphNb;
	}

	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SPlot2D::addData(SData2D  *data, int const graphNb)
///
/// \brief	(SCRIPTABLE) add new points at the end of the actual data, create the curve if necessary .
///
/// \param nbCurve the number of the curve that we want add points, by default 0.
///
/// \sa int addData(SData2D  data, int const nbCurve=0);
/// \sa int addData(double const x, double const y, int const nbCurve=0);
/// \sa int addData(QVector<double> const x, QVector<double> const  y, int const nbCurve=0);
///
/// If nbCurve is grater than the number of curve make a new one and returns its number 
/// else returns nbCurve. 
////////////////////////////////////////////////////////////////////////////////////////////////////
int SPlot2D::addData(SData2D  *data, int const nbCurve){

	if (nbCurve > totCurve_){
		totCurve_++;
		customPlot_->addGraph();
		customPlot_->graph(totCurve_)->addData(data->x(),data->y());
		if(autoReplot_) doReplot();
		return totCurve_;

	}else{
		customPlot_->graph(nbCurve)->addData(data->x(),data->y());
		if(autoReplot_) doReplot();
		return nbCurve;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SPlot2D::addData(SData2D  data, int const graphNb)
///
/// \brief	(SCRIPTABLE) add new points at the end of the actual data, create the curve if necessary .
///
/// \param nbCurve the number of the curve that we want add points, by default 0.
///
/// \sa int addData(SData2D  *data, int const nbCurve=0);
/// \sa int addData(double const x, double const y, int const nbCurve=0);
/// \sa int addData(QVector<double> const x, QVector<double> const  y, int const nbCurve=0);
///
/// If nbCurve is grater than the number of curve make a new one and returns its number 
/// else returns nbCurve. 
////////////////////////////////////////////////////////////////////////////////////////////////////
int SPlot2D::addData(SData2D  data, int const graphNb){

	if (graphNb > totCurve_){
		customPlot_->addGraph();
		totCurve_++;
		customPlot_->graph(totCurve_)->addData(*data.x(),*data.y());
		if(autoReplot_) doReplot();
		return totCurve_;

	}else{
		customPlot_->addGraph();
		customPlot_->graph(graphNb)->addData(*data.x(), *data.y());
		if(autoReplot_) doReplot();
		return graphNb;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SPlot2D::addData(double const x, double const  y, int const nbCurve)
///
/// \brief	(SCRIPTABLE) add new points at the end of the actual data, create the curve if necessary .
///
/// \param nbCurve the number of the curve that we want add points, by default 0.
///
/// \sa int addData(SData2D  *data, int const nbCurve=0);
/// \sa int addData(SData2D  data, int const nbCurve=0);
/// \sa int addData(QVector<double> const x, QVector<double> const  y, int const nbCurve=0);
///
/// If nbCurve is grater than the number of curve make a new one and returns its number 
/// else returns nbCurve. 
////////////////////////////////////////////////////////////////////////////////////////////////////
	int SPlot2D::addData(double const x, double const  y, int const nbCurve){

	if (nbCurve > totCurve_){	
		totCurve_++;
		customPlot_->graph(totCurve_)->addData(x,y);
		if(autoReplot_) doReplot();
		return totCurve_;

	}else{
		customPlot_->graph(nbCurve)->addData(x,y);
		if(autoReplot_) doReplot();
		return nbCurve;
	}


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::append(double  const x, double const  y, int const graphNb)
///
/// \brief	(SCRIPTABLE) add new points at the end of the actual data, create the curve if necessary .
///
/// \param nbCurve the number of the curve that we want add points, by default 0.
///
/// \sa int addData(SData2D  *data, int const nbCurve=0);
/// \sa int addData(SData2D  data, int const nbCurve=0);
/// \sa int addData(QVector<double> const x, QVector<double> const  y, int const nbCurve=0);
///
/// Overload or \ref addData(double const x, double const  y, int const nbCurve), just of compatibility
/// with old script, do not use it...
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::append(double  const x, double const  y, int const nbCurve)
{
	addData(x, y, nbCurve);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int SPlot2D::addData(QVector<double> const x, QVector<double> const  y, int const nbCurve)
///
/// \brief	(SCRIPTABLE) add new points at the end of the actual data, create the curve if necessary .
///
/// \param nbCurve the number of the curve that we want add points, by default 0.
///
/// \sa int addData(SData2D  *data, int const nbCurve=0);
/// \sa int addData(SData2D  data, int const nbCurve=0);
/// \sa int addData(double const x, double const y, int const nbCurve=0);
///
/// If nbCurve is grater than the number of curve make a new one and returns its number 
/// else returns nbCurve. 
////////////////////////////////////////////////////////////////////////////////////////////////////
int SPlot2D::addData(QVector<double> const x, QVector<double> const  y, int const nbCurve){

	if (nbCurve > totCurve_){
		customPlot_->addGraph();
		totCurve_++;
		customPlot_->graph(totCurve_)->addData(x,y);
		if(autoReplot_) doReplot();
		return totCurve_;

	}else{
		customPlot_->graph(nbCurve)->addData(x,y);
		if(autoReplot_) doReplot();
		return nbCurve;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::removeDataBefore(double X,int const nbCurve=0)
///
/// \brief	(SCRIPTABLE) Removes all data points with abscissa smaller than \a X.
///
/// \param nbCurve the number of the curve that we want to remove point, by default 0.
///
/// \sa addData
/// \sa clearData
/// \sa removeDataAfter
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::removeDataBefore(double X,int const nbCurve){
	if (nbCurve <= totCurve_){
		customPlot_->graph(nbCurve)->removeDataBefore(X);
		if(autoReplot_) doReplot();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::removeDataAfter(double X,int const nbCurve=0)
///
/// \brief	(SCRIPTABLE) Removes all data points with abscissa greater than \a X.
///
/// \param nbCurve the number of the curve that we want to remove point, by default 0.
///
/// \sa addData
/// \sa clearData
/// \sa removeDataBefore
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::removeDataAfter(double X,int const nbCurve){
	if (nbCurve <= totCurve_){
		customPlot_->graph(nbCurve)->removeDataAfter(X);
		if(autoReplot_) doReplot();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::removeData(double fromX, double toX,int const nbCurve=0)
///
/// \brief	(SCRIPTABLE) Removes all data points with abscissa between \a fromX and \a toX.
///
/// \param nbCurve the number of the curve that we want to remove point, by default 0.
///
/// \sa addData
/// \sa clearData
/// \sa removeDataBefore
///
/// Removes all data points with key between \a fromKey and \a toKey. if \a fromKey is
///	greater or equal to \a toKey, the function does nothing. To remove a single data point with known
///	key, use \ref removeData(double key).
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::removeData(double fromX, double toX,int const nbCurve){
	if (nbCurve <= totCurve_){
		customPlot_->graph(nbCurve)->removeData(fromX,  toX);
		if(autoReplot_) doReplot();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::removeData(double X,int const nbCurve=0)
///
/// \brief	(SCRIPTABLE) Removes all data points with abscissa at X.
///
/// \param nbCurve the number of the curve that we want to remove point, by default 0.
///
/// \sa addData
/// \sa clearData
/// \sa removeDataBefore
///
/// Removes a single data point at \a key. If the position is not known with absolute precision,
/// consider using \ref removeData(double fromKey, double toKey) with a small fuzziness interval
/// around the suspected position, depeding on the precision with which the key is known.
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::removeData(double X,int const nbCurve){
	if (nbCurve <= totCurve_){
		customPlot_->graph(nbCurve)->removeData(X);
		if(autoReplot_) doReplot();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::removeData(double X,int const nbCurve=0)
///
/// \brief	(SCRIPTABLE) Removes all data points.
///
/// \param nbCurve the number of the curve that we want to remove point, by default 0.
///
/// \sa removeData
/// \sa removeDataAfter
/// \sa removeDataBefore
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::clearData(int const nbCurve){
	if (nbCurve <= totCurve_){
		customPlot_->graph(nbCurve)->clearData();
		if(autoReplot_) doReplot();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void setVisible(bool visible,int nbCurve=0)
///
/// \brief	(SCRIPTABLE) Removes all graphs from the plot.
///
/// Removes all graphs from the plot (and the legend, if necessary).
/// Returns the number of graphs removed.
////////////////////////////////////////////////////////////////////////////////////////////////////
int SPlot2D::clearAllData()
 {
	return customPlot_->clearGraphs();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void setVisible(bool visible,int nbCurve=0)
///
/// \brief	(SCRIPTABLE) Put a curve visible or not.
///
/// \param nbCurve the number of the curve that we want to put visible or not, by default 0.
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SPlot2D::setVisible(bool visible,int nbCurve)
{
	if (nbCurve <= totCurve_){	
		customPlot_->graph(nbCurve)->setVisible(visible);
		if(autoReplot_) customPlot_->replot();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void setPen(const QPen &pen,int nbCurve=0)
///
/// \brief	(SCRIPTABLE) 
///
/// \param nbCurve the number of the curve that we want to change the pen by default 0.
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::setPen(const QPen &pen,int nbCurve)
{
	if (nbCurve <= totCurve_){	
		customPlot_->graph(nbCurve)->setPen(pen);
		if(autoReplot_) customPlot_->replot();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setPen(const QString penStyle, const QString penColor, int nbCurve)
///
/// \brief	(SCRIPTABLE) set a style of line and a color to a curve
///
/// \param nbCurve the number of the curve that we want to set a color and style by default 0.
///
/// If nbCurve is greater than the number of curve do nothing.
/// By default solid blue line.
///
/// Sets the RGB value of this a curve to \a penColor, which may be in one
///	of these formats:
///
///\list
///	\i #RGB (each of R, G, and B is a single hex digit)
///	\i #RRGGBB
///	\i #RRRGGGBBB
///	\i #RRRRGGGGBBBB
///	\i A name from the list of colors defined in the list of \l{SVG color keyword names}
/// (http://www.w3.org/TR/SVG/types.html#ColorKeywords)provided by the World Wide Web 
/// Consortium; for example, "steelblue" or "gainsboro".
///	\endlist
///
///
/// List of style:
/// \li SolidLine
/// \li DashLine
/// \li DotLine
/// \li DashDotLine
/// \li DashDotLine
///
/// \remark If the penStyle string is not valid, a solid line will be take.
/// \remark If the penColor string is not valid, blue will be take.
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SPlot2D::setPen(const QString penStyle, const QString penColor, int nbCurve)
{

	if (nbCurve > totCurve_) return;	

	QColor color;

	if (QColor::isValidColor(penColor)){
		 color.setNamedColor(penColor);
	}else{
		color.setNamedColor("blue");
	}

	QPen pen = stringToPenStyle(penStyle);


	pen.setColor(color);

	customPlot_->graph(nbCurve)->setPen(pen);
	if(autoReplot_) customPlot_->replot();
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 void SPlot2D::setName(QString name, int nbCurve)
///
/// \brief	(SCRIPTABLE) set a name at a curve
///
/// \param nbCurve the number of the curve that we want to change the style of line, by default 0.
///
/// If nbCurve is greater than the number of curve do nothing. The name is the textual
///  representation of this plottable as it is displayed in the QCPLegend of
/// the parent QCustomPlot. It may contain any utf-8 characters, including newlines.
////////////////////////////////////////////////////////////////////////////////////////////////////
 void SPlot2D::setName(QString name, int nbCurve){
	 if (nbCurve > totCurve_) return;	
	 customPlot_->graph(nbCurve)->setName(name);
	 if(autoReplot_) customPlot_->replot();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	  QString SPlot2D::Name(int nbCurve)
///
/// \brief	(SCRIPTABLE) get the name of a curve
///
/// \param nbCurve the number of the curve that we want to change the style of line, by default 0.
///
/// If nbCurve is greater than the number of curve do nothing. The name is the textual
/// representation of this plottable as it is displayed in the QCPLegend of
/// the parent QCustomPlot. It may contain any utf-8 characters, including newlines.
////////////////////////////////////////////////////////////////////////////////////////////////////
 QString SPlot2D::name(const int nbCurve) const{
	if (nbCurve > totCurve_) return QString("");	
	return customPlot_->graph(nbCurve)->name();

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	   void SPlot2D::setColor( QString colorName, int nbCurve)
///
/// \brief	(SCRIPTABLE) Set the color of a curve, by default blue.
///
/// \param nbCurve the number of the curve that we want to change the style of line, by default 0.
///
/// \sa setPen
///
/// If nbCurve is greater than the number of curve do nothing. 
/// see \a setPen for the naming convention.
////////////////////////////////////////////////////////////////////////////////////////////////////
 void SPlot2D::setColor( const QString colorName, const int nbCurve)
{
	 if (nbCurve > totCurve_) return;	
	  QPen pen = customPlot_->graph(nbCurve)->pen();
	  QColor color;

	  if (QColor::isValidColor(colorName)){
		  color.setNamedColor(colorName);
	  }else{
		  color.setNamedColor("blue");
	  }

	  pen.setColor(color);

	  customPlot_->graph(nbCurve)->setPen(pen);
	 if(autoReplot_) customPlot_->replot();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setScatterStyle(QString ScatterStyle, int nbCurve=0)
///
/// \brief	(SCRIPTABLE) 
///
/// \param nbCurve the number of the curve that we want to change the style of line, by default 0.
 ///
 /// \sa setPen
 ///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::setPenStyle(const QString LineStyle, const int nbCurve)
{
	if (nbCurve > totCurve_) return;	
	QPen pen = customPlot_->graph(nbCurve)->pen();
	pen.setStyle(stringToPenStyle(LineStyle).style());
	customPlot_->graph(nbCurve)->setPen(pen);
	if(autoReplot_) customPlot_->replot();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setScatterStyle(QString ScatterStyle, int nbCurve=0)
///
/// \brief	(SCRIPTABLE) change the style of the Scatter, by default none.
///
/// \param nbCurve the number of the curve that we want to change the style of scatter, by default 0.
///
/// If nbCurve is greater than the number of curve do nothing.
///
/// List of available scatter : 
/// \li None  no scatter symbols are drawn (e.g. data only represented with lines, see \ref setLineStyle)
/// \li Dot      a single pixel, \ref setScatterSize has no influence on its size.
/// \li Cross    a cross (x)
/// \li Plus     a plus (+)
/// \li Circle    a circle which is not filled
/// \li Disc      a circle which is filled with the color of the graph's pen (not the brush!)
/// \li Square    a square which is not filled
/// \li Star      a star with eight arms, i.e. a combination of cross and plus
/// \li Triangle  an equilateral triangle which is not filled, standing on baseline
/// \li TriangleInverted an equilateral triangle which is not filled, standing on corner
/// \li CrossSquare       a square which is not filled, with a cross inside
/// \li PlusSquare        a square which is not filled, with a plus inside
/// \li CrossCircle       a circle which is not filled, with a cross inside
/// \li PlusCircle        a circle which is not filled, with a plus inside
/// \li Peace      a circle which is not filled, with one vertical and two downward diagonal lines
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::setScatterStyle(const QString ScatterStyle, const int nbCurve)
{
	
	if (nbCurve > totCurve_) return;	
	
	if(ScatterStyle.contains("none", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssNone);
	}else if(ScatterStyle.contains("dot", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssDot);
	}else if(ScatterStyle.contains("cross", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssCross);
	}else if(ScatterStyle.contains("plus", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssPlus);
	}else if(ScatterStyle.contains("circle", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssCircle);
	}else if(ScatterStyle.contains("disk", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssDisc);
	}else if(ScatterStyle.contains("Square", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssSquare);
	}else if(ScatterStyle.contains("Star", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssStar);
	}else if(ScatterStyle.contains("Triangle", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssTriangle);
	}else if(ScatterStyle.contains("TriangleInverted", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssTriangleInverted);
	}else if(ScatterStyle.contains("CrossSquare", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssCrossSquare);
	}else if(ScatterStyle.contains("CrossCircle", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssCrossCircle);
	}else if(ScatterStyle.contains("PlusCircle", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssPlusCircle);
	}else if(ScatterStyle.contains("Peace", Qt::CaseInsensitive)){
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssPeace);
	}else{
		customPlot_->graph(nbCurve)->setScatterStyle(QCPGraph::ssNone);
	}
	if(autoReplot_) customPlot_->replot();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setScatterSize(double size, int nbCurve=0)
///
/// \brief	(SCRIPTABLE) set the size of the Scatter
///
/// \param nbCurve the number of the curve that we want to change the size of the scatter, by default 0.
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::setScatterSize(const double size, const int nbCurve)
{
	if (nbCurve > totCurve_) return;	
	customPlot_->graph(nbCurve)->setScatterSize(size);
	if(autoReplot_) customPlot_->replot();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setScatterSize(double size, int nbCurve=0)
///
/// \brief	(SCRIPTABLE) set the style of link between the point
///
/// 3 styles of link between points:
/// \li None data points are not connected with any lines 
/// 		(e.g. data only represented with symbols according to the scatter style)
/// \li Line data points are connected by a straight line
/// \li Impulse data points are represented by a straight line parallel to the value axis,
///         which ranges down/up to the key axis
///
/// Note : you have to put a style of scatter (not \c none) for
/// see it.
//////////////////////////////////////////////////////////////////////////////////////////////////////

void SPlot2D::setPointLink( const QString PointLinkStyle, const int nbCurve/*=0*/ )
{
	if (PointLinkStyle.toLower().trimmed() == "none"){
		customPlot_->graph(nbCurve)->setLineStyle(QCPGraph::lsNone);
	}else if(PointLinkStyle.toLower().trimmed() == "impulse"){
		customPlot_->graph(nbCurve)->setLineStyle(QCPGraph::lsImpulse);
	}else{
		customPlot_->graph(nbCurve)->setLineStyle(QCPGraph::lsLine);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setScatterSize(double size, int nbCurve=0)
///
/// \brief	(SCRIPTABLE) set the style of link between the point
///
/// 3 styles of link between points:
/// \li none data points are not connected with any lines 
/// 		(e.g. data only represented with symbols according to the scatter style)
/// \li line data points are connected by a straight line
/// \li impulse data points are represented by a straight line parallel to the value axis,
///         which ranges down/up to the key axis
///
/// Note : you have to put a style of scatter (not \c none) for
/// see it.
//////////////////////////////////////////////////////////////////////////////////////////////////////
 QString SPlot2D::pointLink(const int nbCurve)const{

	 if ( customPlot_->graph(nbCurve)->lineStyle() == QCPGraph::lsNone){
		 return "none";
	 }else if(customPlot_->graph(nbCurve)->lineStyle() == QCPGraph::lsImpulse){
		 return "impulse";
	 }else if(customPlot_->graph(nbCurve)->lineStyle() == QCPGraph::lsStepCenter){
		 return "stepCenter";
	 }else if(customPlot_->graph(nbCurve)->lineStyle() == QCPGraph::lsStepLeft){
		 return "stepLeft";
	 }else if(customPlot_->graph(nbCurve)->lineStyle() == QCPGraph::lsStepRight){
		 return "stepRight";
	 }else if(customPlot_->graph(nbCurve)->lineStyle() == QCPGraph::lsLine){
		 return "nine";
	 }else{
		return "bug";
	 }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SPlot2D::lineStyle(int nbCurve=0) const
///
/// \brief	(SCRIPTABLE) 
///
/// \param nbCurve the number of the curve that we want to have the style of line, by default 0.
///
/// \sa setPen
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SPlot2D::penStyle(const int nbCurve) const
{
	if (nbCurve > totCurve_) return QString("");	
	QPen pen = customPlot_->graph(nbCurve)->pen();

	if(pen.style() == Qt::SolidLine){
		return "SolidLine";
	}else if(pen.style() == Qt::DashLine){
		return "DashLine";
	}else if(pen.style() == Qt::DotLine){
		return "DotLine";
	}else if(pen.style() == Qt::DashDotLine){
		return "DashDotLine";
	}else if(pen.style() == Qt::DashDotDotLine){
		return "DashDotDotLine";
	}else{
		return "Bug";
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SPlot2D::scatterStyle(int nbCurve=0) const
///
/// \brief	(SCRIPTABLE) 
///
/// \param nbCurve the number of the curve that we want to have the style of the scatter, by default 0.
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SPlot2D::scatterStyle(const int nbCurve) const
{
	if (nbCurve > totCurve_) return "";	

	if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssNone){
		return "None";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssDot){
		return "Dot";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssCross){
		return "Cross";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssPlus){
		return "Plus";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssCircle){
		return "Circle";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssDisc){
		return "Disc";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssSquare){
		return "Square";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssStar){
		return "Star";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssTriangle){
		return "Triangle";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssTriangleInverted){
		return "TriangleInverted";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssCrossSquare){
		return "CrossSquare";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssCrossCircle){
		return "CrossCircle";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssPlusCircle){
		return "PlusCircle";
	}else if(customPlot_->graph(nbCurve)->scatterStyle() == QCPGraph::ssPeace){
		return "Peace";
	}else{
		return "Bug";
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	double SPlot2D::scatterSize(int nbCurve=0) const
///
/// \brief	(SCRIPTABLE) get the size of the scatter
///
/// \param nbCurve the number of the curve that we want to have the size of the scatter, by default 0.
///
/// If nbCurve is greater than the number of curve do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////////
double SPlot2D::scatterSize(const int nbCurve) const
{
	if (nbCurve > totCurve_) return 0;		
	return customPlot_->graph(nbCurve)->scatterSize();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString color(const int nbCurve =0) const
///
/// \brief	(SCRIPTABLE) Get the color of a curve.
///
/// \param nbCurve the number of the curve that we want to have the size of the scatter, by default 0.
///
/// \sa setPen
///
/// If nbCurve is greater than the number of curve do nothing.
///
/// Returns the name of the color of the curve nbCurve in the format "#RRGGBB"; i.e. a "#"
/// character followed by three two-digit hexadecimal numbers.
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SPlot2D::color(const int nbCurve) const
{
	if (nbCurve > totCurve_) return "";	
	QPen pen;
	pen =  customPlot_->graph(nbCurve)->pen();
	return pen.color().name();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::doAutoScale()
///
/// \brief (SCRIPTABLE) Rescales the graph to contain all data.
/// 
/// If nbCurve is greater than the number of curve do
/// nothing.
///
/// Rescales the key and value axes associated with this graph to contain all data points, 
//  so the whole graph is visible
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::doAutoScale(){
	customPlot_->rescaleAxes();
	customPlot_->replot();

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SPlot2D::autoScale()
///
/// \brief	(SCRIPTABLE) get if the auto scale is on
///
/// If true, rescale automatically the graph after each append
/// of data. If autoReplot is off, the scaling will occur when
/// the user send a replot.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::doReplot()
{
		
	if(autoScale_){
		doAutoScale();
	}else{
		customPlot_->replot();	
	} 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SPlot2D::autoScale()
///
/// \brief	(SCRIPTABLE) get if the auto scale is on
///
/// If true, rescale automatically the graph after each append
/// of data. If autoReplot is off, the scaling will occur when
/// the user send a replot.
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE bool SPlot2D::autoScale()
{
	return autoScale_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setAutoScale( const bool onOff )
///
/// \brief	(SCRIPTABLE) set if the graph have to be rescales 
///
/// If true, rescale automatically the graph after each append
/// of data. If autoReplot is off, the scaling will occur when
/// the user send a replot.
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SPlot2D::setAutoScale( const bool onOff )
{
	autoScale_=onOff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setScale(double Xmin,double
/// Xmax, double Ymin, double Ymax)
///
/// \brief (SCRIPTABLE) sets the scales selected by the user.
///
/// \param Xmin the maximum of the x scale
/// \param Xmax the minimum of the x scale
/// \param Ymin the maximum of the y scale
/// \param Ymax the minimum of the y scale
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::setScale(double Xmin, double Xmax, double Ymin, double Ymax){
	customPlot_->xAxis->setRange(Xmin,Xmax);
	customPlot_->yAxis->setRange(Ymin,Ymax);
	customPlot_->replot();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2DWidget::doSelectScaleWin()
///
/// \brief	(SLOT) Open a dialog box asking the scale.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::doSelectScaleWin(){
	if(winScale==NULL){
		winScale = new SPlotSetScale(this);
	}

	winScale->initialValue(	
		customPlot_->xAxis2->range().lower,
		customPlot_->xAxis2->range().upper,
		customPlot_->yAxis2->range().lower,
		customPlot_->yAxis2->range().upper
		);

	connect(winScale, SIGNAL(scaleChange(double,double,double,double)),
		this, SLOT(setScale(double,double,double,double)));

	connect(winScale, SIGNAL(ScaleToAll()),
		this, SLOT(doScaleToAll()));

	winScale->show();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void doScaleToAll()
///
/// \brief	(SCRIPTABLE) Apply the scale at all the 2D plot open.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::doScaleToAll(){
	
	double xmin = customPlot_->xAxis2->range().lower;
	double xmax = customPlot_->xAxis2->range().upper;
	double ymin = customPlot_->yAxis2->range().lower;
	double ymax = customPlot_->yAxis2->range().upper;

	for (int i =0;i<lstPlot2D.count(); i++){
		lstPlot2D.at(i)->setScale(xmin,xmax, ymin,ymax);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setAntialiasing( const bool onOf/*=true*/ )
///
/// \brief	(SCRIPTABLE) enable or not the antialiasing
///
/// the antialiasing decreases the performance.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::setAntialiasing( const bool onOff/*=true*/ )
{
	if(onOff==antialiasing_) return;

	antialiasing_=onOff;
	// Performance Tweaks :avoid any kind of antialiasing, especially in graph lines (QCustomPlot::setAntialiasedElements) 
	//customPlot_->setAntialiasedElement(QCustomPlot::aeGrid ,onOff);
	customPlot_->setAntialiasedElement(QCustomPlot::aeGraphs ,onOff);
	//customPlot_->setAntialiasedElement(QCustomPlot::aeAxes ,onOff);
	customPlot_->setAntialiasedElement(QCustomPlot::aeSubGrid ,onOff);
	customPlot_->setAntialiasedElement(QCustomPlot::aeScatters ,onOff);
	customPlot_->setAntialiasedElement(QCustomPlot::aeFills ,onOff);
	customPlot_->setAntialiasedElement(QCustomPlot::aeErrorBars ,onOff);
	customPlot_->replot();
	//doReplot();
}

void SPlot2D::setPointSelection( const bool onOff )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SPlot2D::antialiasing() const
///
/// \brief (SCRIPTABLE) get if the antialiasing is active.
///
/// the antialiasing decreases the performance.
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SPlot2D::antialiasing() const
{
	return antialiasing_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SPlot2D::antialiasing() const
///
/// \brief	get if the antialiasing is active.
///
/// the antialiasing decreases the performance.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::mouseMouved( QMouseEvent * event )
{
	double x,y;



	char styleX = 'g',styleY = 'g';

	customPlot_->plottable()->pixelsToCoords(event->posF(),x,y);

	// Hack for avoid the 0.000000000001
	if (qAbs(x)<=0.001 || qAbs(x)>=1000 ){
		styleX = 'e';
	}

	if (qAbs(y)<=0.001 || qAbs(y)>=1000 ){
		styleY = 'e';
	}

	if(	x< customPlot_->xAxis->range().lower || 
		x> customPlot_->xAxis->range().upper ||
		y< customPlot_->yAxis->range().lower || 
		y> customPlot_->yAxis->range().upper){
		this->statusBar()->clearMessage();
		MousePostion_ = "";
	} else{
		MousePostion_ = "(" + QString::number(x,styleX,6) + "," + QString::number(y,styleX,6)+")";
		this->statusBar()->showMessage(MousePostion_,0);
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SPlot2D::keyPressEvent(QKeyEvent *event)
///
/// \brief	get if the antialiasing is active.
///
/// the antialiasing decreases the performance.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::keyPressEvent(QKeyEvent *event)
{
	if(event->key() ==  Qt::Key_C && QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		QClipboard *clipboard = QApplication::clipboard();
		clipboard->setText(MousePostion_);
		event->accept();
	}
	else
	{
		event->ignore();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SPlot2D::antialiasing() const
///
/// \brief	get if the antialiasing is active.
///
/// the antialiasing decreases the performance.setuse
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::mouseReleaseEvent ( QMouseEvent * ev ) {
	if(ev->button() == Qt::RightButton){
		ev->accept();
		mnuContextual->exec(ev->globalPos());
		
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SPlot2D::antialiasing() const
///
/// \brief	get if the antialiasing is active.
///
/// the antialiasing decreases the performance.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::doCopyCoor(){
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(MousePostion_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::doSaveImage()
///
/// \brief save an image of the graph.
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::doSaveImage(){

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Graph like Image/PDF"),
		"",	tr("Images PNG (*.png);; PDF file(*.pdf)"));

	if(fileName.isEmpty()) return;

	SPlotImageSize PlotImageSize (this);
	PlotImageSize.setImgHeight(customPlot_->height()+52);
	PlotImageSize.setImgWidth(customPlot_->width());
	PlotImageSize.exec();

	if( PlotImageSize.result()== PlotImageSize.Rejected) return ;

	if(fileName.endsWith (".png", Qt::CaseInsensitive)){
		customPlot_->deselectAll();
		customPlot_->savePngScaled(fileName, PlotImageSize.imgScale(), PlotImageSize.imgHeight(), PlotImageSize.imgWidth());

	}else if (fileName.endsWith (".pdf", Qt::CaseInsensitive)){
		customPlot_->savePdf(fileName, !PlotImageSize.imgCosmeticPen(), PlotImageSize.imgHeight(), PlotImageSize.imgWidth());
	}


}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::SaveImagePng(const QString &fileName, double scale, int width, int height)
///
/// \brief save the graph in a picture file.
///
///	Saves a PNG image file to \a fileName on disc. The output plot will have a base \a width and \a
/// height which is then scaled by factor \a scale. If you for example set both \a width and \a height to
/// 100 and \a scale to 2, you will end up with a PNG file of size 200*200 in which all graphical
/// elements are scaled up by factor 2 (line widths, texts, etc.). This scaling is done not by
/// stretching a 100*100 image but by actually scaling the painter, so the result will have full
/// 200*200 pixel resolution.
/// 
/// The objects of the plot will appear in the current selection state. So when you don't want e.g.
/// selected axes to be painted in their selected look, deselect everything with \ref deselectAll
/// before calling this function.
/// 
/// \warning
/// \li If calling this function inside the constructor of the parent of the QCustomPlot widget
/// (i.e. the MainWindow constructor, if QCustomPlot is inside the MainWindow), always provide
/// explicit non-zero widths and heights. If you leave \a width or \a height as 0 (default), this
/// function uses the current width and height of the QCustomPlot widget. However, in Qt, these
/// aren't defined yet inside the constructor, so you would get an image that has strange
/// widths/heights.
/// \li When using the raster graphicssystem: There currently is a bug in the Qt painting system that
/// prevents proper scaling of pen widths when using the raster graphicssystem. So if you use this
/// function and need properly scaled pens widths, consider using a different graphicssystem than
/// raster (or apply a non-zero pen width to all pens, since the bug only occurs for cosmetic pens).////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::SaveImagePng(const QString &fileName, double scale, int width, int height){
	customPlot_->savePngScaled(fileName,scale,width,height);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn void SPlot2D::SaveImagePdf(const QString &fileName, bool noCosmeticPen, int width, int height)
///
/// \brief save the graph in a PDF file.
///
///  Saves a PDF with the vectorized plot to the file \a fileName. The axis ratio as well as the scale
///  of texts and lines will be derived from the specified \a width and \a height. This means, the
///  output will look like the normal on-screen output of a QCustomPlot widget with the corresponding
///  pixel width and height. If either \a width or \a height is zero, the exported image will have
///  the same dimensions as the QCustomPlot widget currently has.
/// 
///  \a noCosmeticPen disables the use of cosmetic pens when drawing to the PDF file. Cosmetic pens
///  are pens with numerical width 0, which are always drawn as a one pixel wide line, no matter what
///  zoom factor is set in the PDF-Viewer. For more information about cosmetic pens, see QPainter and
///  QPen documentation.
///   
///  The objects of the plot will appear in the current selection state. So when you don't want e.g.
///  selected axes to be painted in their selected look, deselect everything with \ref deselectAll
///  before calling this function.
/// 
///  \warning
///  \li If you plan on editing the exported PDF file with a vector graphics editor like
///  Inkscape, it is advised to set \a noCosmeticPen to true to avoid losing those cosmetic lines
///  (which might be quite many, because cosmetic pens are the default for e.g. axes and tick marks).
///  \li If calling this function inside the constructor of the parent of the QCustomPlot widget
///  (i.e. the MainWindow constructor, if QCustomPlot is inside the MainWindow), always provide
///  explicit non-zero widths and heights. If you leave \a width or \a height as 0 (default), this
///  function uses the current width and height of the QCustomPlot widget. However, in Qt, these
///  aren't defined yet inside the constructor, so you would get an image that has strange
///  widths/heights.
///   
///  \see SaveImagePng
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::SaveImagePdf(const QString &fileName, bool noCosmeticPen, int width, int height){
	customPlot_->savePngScaled(fileName,noCosmeticPen,width,height);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::doOpt()
///
/// \brief	(TODO) some options ...
////////////////////////////////////////////////////////////////////////////////////////////////////
void SPlot2D::doOpt(){
	QMessageBox msgBox;
	msgBox.setText("Not yet ...");
	msgBox.exec();
	;}



////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE void SPlot2D::setTitle( const QString title ) const
///
/// \brief set the title of the window
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SPlot2D::setTitle( const QString title )
{
	customPlot_->setTitle(title);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	Q_INVOKABLE void SPlot2D::title() const
///
/// \brief get the title of the window
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE QString SPlot2D::title() const
{
	return customPlot_->title();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QScriptValue SData2DScript::qsCtor(QScriptContext *context, QScriptEngine *engine)
///
/// \brief	this function is use by script engine to create a new SPlot2D object.
///
/// \author	Sylvain Martin
/// \date	1/28/2011
///
/// \param [in,out]	context	If non-null, the QScript context.
/// \param [in,out]	engine	If non-null, the QScript engine.
///
/// \return	a QScript version of a SData2D.
////////////////////////////////////////////////////////////////////////////////////////////////////

QScriptValue SPlot2D::qsCtor(QScriptContext *context, QScriptEngine *engine) {
	QWidget *parent;
	QString name;

	if(context->argument(0).isObject()){
		parent = qobject_cast<QWidget *>(context->argument(0).toQObject());
	}else{
		parent = NULL;
	}

	// on ajoute un graph, pck par defaut les scripts ne le font pas et ça bug ...
	SPlot2D *plot  = new SPlot2D(parent);

	plot->customPlot_->addGraph();
	plot->customPlot_->graph(0)->setPen(QPen(Qt::blue));
	plot->customPlot_->graph(0)->setBrush(QBrush(QColor(0, 0, 0, 0)));
	plot->customPlot_->xAxis->setLabel("x");
	plot->customPlot_->xAxis->setGrid(true);
	plot->customPlot_->yAxis->setLabel("y");
	plot->customPlot_->yAxis->setGrid(true);
	

	QObject *object = plot;



	return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setXLabel( const QString label )
///
/// \brief	(SCRIPTABLE) set the label of the X axis
///
/// \author	Sylvain Martin
/// \date	04/10/2012
///
/// \param label the label wanted
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SPlot2D::setXLabel( const QString label )
{
	if(totCurve_<=-1) return;
	customPlot_->xAxis->setLabel(label);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setYLabel( const QString label )
///
/// \brief	(SCRIPTABLE) set the label of the Y axis
///
/// \author	Sylvain Martin
/// \date	04/10/2012
///
/// \param label the label wanted
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SPlot2D::setYLabel( const QString label )
{
	if(totCurve_<=-1) return;
	customPlot_->yAxis->setLabel(label);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SPlot2D::setLabels( const QString label )
///
/// \brief	(SCRIPTABLE) set the label of the x and Y axis
///
/// \author	Sylvain Martin
/// \date	04/10/2012
///
/// \param Xlabel the label wanted for the x axis
/// \param Ylabel the label wanted for the y axis
////////////////////////////////////////////////////////////////////////////////////////////////////
Q_INVOKABLE void SPlot2D::setLabels( const QString Xlabel,const QString Ylabel )
{
	if(totCurve_<=-1) return;
	customPlot_->yAxis->setLabel(Ylabel);
	customPlot_->xAxis->setLabel(Xlabel);
}
