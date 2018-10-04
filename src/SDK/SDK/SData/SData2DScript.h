#pragma once
#ifndef SDATA2DSCRIPT_H_
#define SDATA2DSCRIPT_H_

#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>
#include "SData2D.h"

Q_DECLARE_METATYPE(SData2D*)
Q_DECLARE_METATYPE(SData2D)
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SData2DScript
///
/// \brief	this class provides a Qt Script warper for the \SData2D class 
///
/// \author	Sylvain Martin
/// \date	1/28/2011
/// 		
/// \ingroup SDataMod	
/// 		 
/// this class takes up the useful functions of the class SData2D in order to use it in the Qt script.
/// 
/// \sa SData2D	 
////////////////////////////////////////////////////////////////////////////////////////////////////

class SData2DScript :public QObject, protected QScriptable {
	Q_OBJECT;

public:
	SData2DScript(QObject * parent = 0);
	SData2DScript(SData2D * data, QObject * parent);
	SData2DScript(SData2D  data, QObject * parent);

	~SData2DScript(void);

	static QScriptValue qsCtor(QScriptContext *context, QScriptEngine *engine);
	QScriptValue toScriptValue(QScriptContext *context, QScriptEngine *engine);
	

	static QScriptValue toScriptValue(QScriptEngine *engine, const SData2D &s);
	static void fromScriptValue(const QScriptValue &obj, SData2D &s);

	Q_INVOKABLE void setData(SData2D  data);

    Q_INVOKABLE void openFile(QString const file);
    Q_INVOKABLE void saveFile(QString const file);

    Q_INVOKABLE void append(QVariantList x, QVariantList y);
	Q_INVOKABLE void append(double x, double y);

	Q_INVOKABLE void delItem( int i );

	Q_INVOKABLE void slideAverage(int const windows = 20, double const PeackProtectCoeff=0);

	Q_INVOKABLE double x(int i);
	Q_INVOKABLE double y(int i);

	Q_INVOKABLE void setx( int i, double val );
	Q_INVOKABLE void sety( int i, double val );

	Q_INVOKABLE int count();
	Q_INVOKABLE int size();

	Q_INVOKABLE QVariant metaData(QString const key) const;
    Q_INVOKABLE void setMetaData(QString const key, QVariant const value);

	Q_INVOKABLE void setColName(QString Xname, QString Yname);

	Q_INVOKABLE void setColXName(QString Xname);
	Q_INVOKABLE QString colXName();

	Q_INVOKABLE void setColYName(QString Yname);
	Q_INVOKABLE QString colYName();


	Q_INVOKABLE void setColUnit(QString XUnit, QString YUnit);

	Q_INVOKABLE void setColXUnit(QString XUnit);
	Q_INVOKABLE QString colXUnit();

	Q_INVOKABLE void setColYUnit(QString YUnit);
	Q_INVOKABLE QString colYUnit();

	Q_INVOKABLE QScriptValue max(int const start = 0) const;

	Q_INVOKABLE void addComment(QString com);
	Q_INVOKABLE QScriptValue comment() const;
	Q_INVOKABLE void clearComment();

	SData2D * data2DObject();
	SData2D data2DObjectCopy();

protected:
	SData2D * data2D_;
};

#endif