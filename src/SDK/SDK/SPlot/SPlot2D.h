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
#include <QMainWindow>
#include <QList>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>
#include "SDK/SPlot/qcustomplot.h"


#include "../GeneratedFiles/ui_SPlotSetScale.h"
#include "../GeneratedFiles/ui_SPlotImageSize.h"
#include "SDK/SData/SData2D.h"

class SPlotSetScale;
class SPlot2D;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SPlot2D
///
/// \brief	define a Main windows that contained a 2D Plot with all the basic tool (zoom, ...).
///
/// \author	Sylvain Martin
/// \date	2/4/2011
///
/// \remark order to use Qwt as a dll and inherit a QWT object we must define the macro in the
/// 		preprocessor QWT_DLL. in , the project need a preprocessor define
/// 		[configuration properties]->[c/c++]->[preprocessor]->[preprocessor definitions]-> QWT_DLL
/// 		(and leave the rest as it is)
///
/// \sa SPlot2DWidget
///
/// contained a sub-class of QwtPlot that has some new functions, like a \c zoom, an \c autoscale
/// and a way to chose a scale (\c doSelectScaleWin).
////////////////////////////////////////////////////////////////////////////////////////////////////
class SPlot2D : public QMainWindow  , protected QScriptable
{
	Q_OBJECT

public:


	static QList<SPlot2D*> lstPlot2D;


	SPlot2D(QWidget *parent = 0);
	SPlot2D(SData2D *data ,QWidget *parent = 0);
	static QScriptValue qsCtor(QScriptContext *context, QScriptEngine *engine);

	~SPlot2D();

	QCustomPlot * CustomPlotWidget();
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void SPlot2D::mouseReleaseEvent ( QMouseEvent * ev );
		// 
	/** 
	*	@name propertiesFunction
	*	general properties 
	*/
	//@{
	
	Q_INVOKABLE bool antialiasing() const;
	Q_INVOKABLE bool autoScale();

	//@}
		/** 
	*	@name variousFunction
	*	Various functions 
	*/
	//@{
	Q_INVOKABLE void SaveImagePng(const QString &fileName, double scale, int width=0, int height=0);
	Q_INVOKABLE void SaveImagePdf(const QString &fileName, bool noCosmeticPen=false, int width=0, int height=0);
	Q_INVOKABLE void setTitle(const QString title);
	Q_INVOKABLE QString title() const;
	//@}
	// 
	/** 
	*	@name DataFunctions
	*	Functions concerning the data
	*/
	//@{
	Q_INVOKABLE int setData(SData2D  *data, int const nbCurve=0);
	Q_INVOKABLE int setData(SData2D  data, int const nbCurve=0);

	Q_INVOKABLE int addData(SData2D  *data, int const nbCurve=0);
	Q_INVOKABLE int addData(SData2D  data, int const nbCurve=0);
	Q_INVOKABLE int addData(double const x, double const y, int const nbCurve=0);
	Q_INVOKABLE int addData(QVector<double> const x, QVector<double> const  y, int const nbCurve=0);

	Q_INVOKABLE void append(double  const x, double const  y, int const nbCurve=0); 

	Q_INVOKABLE void removeDataBefore(double X,int const nbCurve=0);
	Q_INVOKABLE void removeDataAfter(double X,int const nbCurve=0);
	Q_INVOKABLE void removeData(double fromX, double toX,int const nbCurve=0);
	Q_INVOKABLE void removeData(double X,int const nbCurve=0);


	Q_INVOKABLE void clearData(const int curveNb =0);
	Q_INVOKABLE int clearAllData();
	//@}

	// 
	/** 
	*	@name GraphsFunctions
	*	Functions concerning the graphs
	*/
	//@{
	Q_INVOKABLE void setName(const QString title, const int nbCurve=0);
	Q_INVOKABLE QString name(const int nbCurve =0) const;

	Q_INVOKABLE void setXLabel(const QString label);
	Q_INVOKABLE void setYLabel(const QString label);
	Q_INVOKABLE void setLabels(const QString Xlabel,const QString Ylabel);
	

	Q_INVOKABLE void setVisible(const bool visible,const int nbCurve=0);
	void setPen(const QPen &pen,int nbCurve=0);
	Q_INVOKABLE void setPen(const QString penStyle, const QString penColor, int nbCurve);


	Q_INVOKABLE void setPointLink(const QString PointLinkStyle, const int nbCurve=0);
	Q_INVOKABLE void setPenStyle(const QString LineStyle, const int nbCurve=0);
	Q_INVOKABLE void setScatterStyle(const QString ScatterStyle, const int nbCurve=0);
	Q_INVOKABLE void setScatterSize(const double size, const int nbCurve=0);
	Q_INVOKABLE void setColor( const QString colorName, const int nbCurve =0);

	Q_INVOKABLE QString pointLink(const int nbCurve=0)const;
	Q_INVOKABLE QString penStyle(const int nbCurve=0) const;
	Q_INVOKABLE QString scatterStyle(const int nbCurve=0) const;
	Q_INVOKABLE	double scatterSize(const int nbCurve=0) const;
	Q_INVOKABLE QString color(const int nbCurve =0) const;
	
	//@}
	

	//@}
public slots:
	void doReplot();
	void doAutoScale();
	void setAutoScale(const bool onOff);
	void setAntialiasing(const bool onOff);
	void setScale(double Xmin, double Xmax, double Ymin, double Ymax);

		
private slots:
	void mouseMouved(QMouseEvent * event);
	void doSelectScaleWin();
	void doSaveImage();
	void doOpt();
	void setPointSelection(const bool onOff);
	void doCopyCoor();
	void doScaleToAll();


private:


	void setupUI();

	QCustomPlot * customPlot_;

	int totCurve_; ///> nombre de courbe sur le plot moins 1 pck ça commence a 0.

	QAction * actZoom;
	QAction * actAutoScale;
	QAction * actSetScale;
	QAction * actMarker;
	QAction * actSelectData;
	QAction * actSetAutoScale;
	QAction * actSetAntialiasing;
	QAction * actPointSelection;
	QAction * actCopyCoor;
	QAction * actSaveImage;
	QAction * actOpt;
	QMenu	* mnuContextual;


	QString MousePostion_; ///< Stock the position of the mousse for the copy function

	QToolBar *toolBar;
	bool antialiasing_;
	bool autoReplot_;
	bool autoScale_;
	bool pointSelection_;
	SPlotSetScale * winScale;
	QColor stringToColor(const QString name);
	QPen stringToPenStyle( const QString &penString ) ;


};

Q_DECLARE_METATYPE(SPlot2D*);


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SPlotSetScale
///
/// \brief	(PRIVATE) small QDialog to let the user set a scale.
///
/// \author	Sylvain Martin
/// \date	2/4/2011
///
/// it is a private class, do not use it directly !
////////////////////////////////////////////////////////////////////////////////////////////////////
class SPlotSetScale :
	public QDialog,
	public Ui_SPlotSetScale
{
	Q_OBJECT;
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void SPlotSetScale::SPlotSetScale(void)
	///
	/// \brief	put the initials value for the maximum of the minimum of the 2 scales (x and y)
	///
	/// \param [in,out]	parent	If non-null, the Qt parent.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	SPlotSetScale(QWidget *parent = NULL) : QDialog(parent){
		setupUi(this);
		connect(this, SIGNAL(accepted ()),this, SLOT(priv_scale()));
		connect(this, SIGNAL(accepted ()),this, SLOT(close()));
		connect(this, SIGNAL(rejected ()),this, SLOT(close()));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void SPlotSetScale::initialValue
	///
	/// \brief	puts the initials value for the maximum of the minimum of the 2 scales (x and y)
	///
	/// \param Xmin the maximum of the x scale
	/// \param Xmax the minimum of the x scale
	/// \param Ymin the maximum of the y scale
	/// \param Ymax the minimum of the y scale
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void initialValue(double Xmin, double Xmax, double Ymin, double Ymax){
		dsbXStart->setValue(Xmin);
		dsbXStop->setValue(Xmax);
		dsbYStart->setValue(Ymin);
		dsbYStop->setValue(Ymax);
	}

signals:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void SPlotSetScale::scaleChange
	///
	/// \brief	(SIGNAL) sends the scales selected by the user.
	///
	/// \param Xmin the maximum of the x scale
	/// \param Xmax the minimum of the x scale
	/// \param Ymin the maximum of the y scale
	/// \param Ymax the minimum of the y scale
	///
	/// this signal is send when the OK button is clicked
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void scaleChange(double Xmin, double Xmax, double Ymin, double Ymax);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void ScaleToAll()
	///
	/// \brief (SIGNAL) Apply the scale at all the 2D plot open.
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void ScaleToAll();

private slots:
	void priv_scale(){
			double Xmin = dsbXStart->value();
			double Xmax = dsbXStop->value();
			double Ymin = dsbYStart->value();
			double Ymax = dsbYStop->value();

			emit scaleChange( Xmin,  Xmax,  Ymin,  Ymax);
			this->close();
	}

	void on_cmdScaleAll_clicked(){
		priv_scale();

	}

};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SPlotImageSize
///
/// \brief	(PRIVATE) small QDialog to let select the size of the saved image
///
/// \author	Sylvain Martin
/// \date	2/4/2011
///
/// it is a private class, do not use it directly !
////////////////////////////////////////////////////////////////////////////////////////////////////
class SPlotImageSize :
	public QDialog,
	public Ui_SPlotImageSize
{
	Q_OBJECT;
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void SPlotSetScale::SPlotSetScale(void)
	///
	/// \brief	put the initials value for the maximum of the minimum of the 2 scales (x and y)
	///
	/// \param [in,out]	parent	If non-null, the Qt parent.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	SPlotImageSize(QWidget *parent = NULL) : QDialog(parent){
		setupUi(this);
		connect(this, SIGNAL(accepted ()),this, SLOT(close()));
		connect(this, SIGNAL(rejected ()),this, SLOT(close()));
	}

	int imgHeight(){ return spbHeight->value();}
	int imgWidth(){  return spbWidth->value(); }
	double imgScale(){return spbScale->value();}
	bool imgCosmeticPen(){return ckbCosmeticPen->checkState();}
	

	void setImgHeight(int value){  spbHeight->setValue(value);}
	void setImgWidth(int value){   spbWidth->setValue(value); }
	void setImgScale(double value){ spbScale->setValue(value);}
	void setImgCosmeticPen(bool value){ ckbCosmeticPen->setChecked(value);}
};