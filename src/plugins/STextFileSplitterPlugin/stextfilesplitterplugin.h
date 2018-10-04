#ifndef STEXTFILESPLITTERPLUGIN_H
#define STEXTFILESPLITTERPLUGIN_H

#include "stextfilesplitterplugin_global.h"
#include <QScriptExtensionPlugin>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include <QFile>
#include <QVector>
#include <QString>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>
#include <QScriptContext>
#include <QString>




class STEXTFILESPLITTERPLUGIN_EXPORT STextFileSplitterPlugin : 
			public QScriptExtensionPlugin, protected QScriptable
{
public:
	STextFileSplitterPlugin(QObject * parent = 0);
	~STextFileSplitterPlugin();

	void initialize ( const QString & key, QScriptEngine * engine );
	QStringList keys () const;

private:

};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	STextFileSplitter
///
/// \brief	Class to split huge data files in smaller files
///
/// \author	Sylvain Martin
/// \date	23/11/2011
///
/// \ingroup SDataMod
///
/// \remark not really code in qt use STL library instead
/// find on internet, the author is Pieter Claassens (pc(a)nanoteq.com)
////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEF_NUM_MIN_LINES 50

class STextFileSplitter :public QObject, protected QScriptable{
	Q_OBJECT;
public: 
	// default constructor
	Q_INVOKABLE STextFileSplitter(QObject * parent = 0);
	Q_INVOKABLE STextFileSplitter(QString FileName, int numberOfLinesForEachFile, QObject * parent = 0);
	static QScriptValue STextFileSplitter::qsCtor(QScriptContext *context, QScriptEngine *engine);
	Q_INVOKABLE void CreateOutputFiles();
	// return number of lines in text file...
	Q_INVOKABLE int GetNumberOfLines() const;
protected: 
	void CountLines();
private:
	long numLinesForEachFile, numLinesForEachFileConst, numFiles, TotalLines;
	QFile fin;


};

#endif // STEXTFILESPLITTERPLUGIN_H
