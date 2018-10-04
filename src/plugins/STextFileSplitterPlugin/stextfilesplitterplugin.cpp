#include "stextfilesplitterplugin.h"
/*#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
*/
#include <QtCore>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>
#include <QScriptContext>

//using namespace std;
Q_DECLARE_METATYPE(STextFileSplitter*)

STextFileSplitterPlugin::STextFileSplitterPlugin(QObject * parent):
	QScriptExtensionPlugin(parent)
{

}

STextFileSplitterPlugin::~STextFileSplitterPlugin()
{

}

void STextFileSplitterPlugin::initialize( const QString & key, QScriptEngine * engine )
{
	static bool initialized = false;


	if(key=="STextFileSplitter"){

		if(!initialized){ // evite le multi initialitation
			initialized = true;
			STextFileSplitter splitter;

			QScriptValue qsSplitter = engine->newQObject(&splitter);
			engine->setDefaultPrototype(qMetaTypeId<STextFileSplitter*>(),qsSplitter);

			QScriptValue ctorSplitter = engine->newFunction(STextFileSplitter::qsCtor,qsSplitter);
			engine->globalObject().setProperty("STextFileSplitter", ctorSplitter);

			
		}
	} 


}

QStringList STextFileSplitterPlugin::keys() const
{
	QStringList keysList;
	keysList << "STextFileSplitter";
	return keysList;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QScriptValue STextFileSplitter::qsCtor(QScriptContext *context, QScriptEngine *engine)
///
/// \brief	this function is use by script engine to create a new STextFileSplitter.
///
/// \author	Sylvain Martin
/// \date	25/11/2011
///
/// \param [in,out]	context	If non-null, the QScript context.
/// \param [in,out]	engine	If non-null, the QScript engine.
///
/// \return	a QScript version of a STextFileSplitter.
////////////////////////////////////////////////////////////////////////////////////////////////////

QScriptValue STextFileSplitter::qsCtor(QScriptContext *context, QScriptEngine *engine) {

	 QObject *parent;

	if(context->argumentCount() >= 2){

		 if(context->argumentCount() >= 3 && context->argument(3).isObject()){
			 parent = context->argument(3).toQObject();
		 }else{
			 parent = 0;
		 }
		QObject *object = new STextFileSplitter(context->argument(0).toString(), context->argument(1).toInteger(),parent);
		return engine->newQObject(object, QScriptEngine::ScriptOwnership);
	}else{

		qDebug() << "SCRIPT: Syntax Error: STextFileSplitter(string FileName, int numberOfLinesForEachFile, QObject * parent = 0)";

	}

}


// default constructor
STextFileSplitter::STextFileSplitter(QString FilePath, int numberOfLinesForEachFile, QObject * parent):
QObject(parent)
{
	
	// sanity check
	if (numberOfLinesForEachFile < 1) 
		numberOfLinesForEachFile = DEF_NUM_MIN_LINES;
	
	// set local 'textsplit' class variables
	numLinesForEachFile = numberOfLinesForEachFile;
	numLinesForEachFileConst = numLinesForEachFile;

	
	fin.setFileName(FilePath);

	// open file (check if file exists)		
	if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug() << "STextFileSplitter: Error: Cannot open file for input.";
	}
		
	// Invoke CountLines function.
	CountLines();
}

Q_INVOKABLE STextFileSplitter::STextFileSplitter( QObject * parent /*= 0*/ )
{

}

// count number of lines in file (private) 
void STextFileSplitter::CountLines() {
		long counter = 0;
		QTextStream in(&fin);

		QString line =  in.readLine();

		while (!line.isNull()) {
			counter++;
			line = in.readLine();
			
		}
		TotalLines = counter;
}

void STextFileSplitter::CreateOutputFiles() {

	// Determine how many output files to create.
	if ((TotalLines % numLinesForEachFile) == 0) 
			numFiles = TotalLines / numLinesForEachFile;
	else 
		numFiles = TotalLines / numLinesForEachFile + 1;

	QTextStream in(&fin);
	QString line;
	QFileInfo fileinfo(fin);
	
	// initialize currentLine to 0 (i.e. the first line of input file
	long currentLine = 0;

	// create 'numFiles' amount of output files....
	for (long i = 1; i <= numFiles; i++) {

		// build output file format, x_filename
		QString outputfiles = fileinfo.fileName() +  "_" + QString::number(i) ;


		QFile fp(fileinfo.absolutePath() + outputfiles);

		if (fp.open(QIODevice::Text | QIODevice::Append)) {
			QTextStream sout(&fp);
			
		
		    // move each line to the newly created output file.
			for (int j = currentLine; j < numLinesForEachFile; j++) {
				line = in.readLine();
				if (!line.isNull()){				
					sout << line << endl;
				}

			}


		}
		// set Currentline to the max number of lines it should take
		currentLine = numLinesForEachFile;
		// increase numLinesForEachFile with original number of lines value -- 
		numLinesForEachFile = numLinesForEachFile + numLinesForEachFileConst;
		qDebug() << "Successfully created " << outputfiles << endl;
	}

}

// Return total number of lines for input file.
int STextFileSplitter::GetNumberOfLines() const {
	return TotalLines;
}
