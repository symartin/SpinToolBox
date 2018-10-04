
#include "SDK/SError.h"

#include <QtScript/qscriptengine.h>
#include <QtScriptTools/qscriptenginedebugger.h>


#include <QtCore>
#include <QtGui>
#include <QSound>
#include "SDK/SDevice/SDeviceError.h"

#include "SDK/SData/SData2D.h"
#include "SDK/SData/SData2DScript.h"

#include "SDK/SPlot/SPlot2D.h"

#include <time.h>

#include "SScriptEngine.h"
 
#include "SDKDevice/SDevicePluginInterface.h"  

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SInterfaceGpib::SScriptEngine()
///
/// \brief	constructor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
SScriptEngine::SScriptEngine(QList<SDevicePluginInterface *> lstPugin, 
			SGlobalMetaDataMap * GlobalMetaDataMap, QWidget *parent/* = 0*/){


	qsDebugger = new QScriptEngineDebugger(this);

	qsDebugStdWindow = qsDebugger->standardWindow();
    qsDebugger->attachTo(this);

	// add the plugin for QtBinding in java script

	QSettings settings( "SpinToolBox.ini", QSettings::IniFormat );	
	settings.beginGroup("plugin");	

	if(settings.value("QtCore", false).toBool()){
		this->importExtension("qt.core");
	} 
	if(settings.value("QtGui", false).toBool()){
		this->importExtension("qt.gui");
	}

	qDebug() << "Plugins Qt javascript load:" << "\n\t" << importedExtensions ();

	// loading of the plugin ****************************************
	for(int i=0; i<lstPugin.count(); i++){

		if(lstPugin[i]->isScriptable()){
			lstPugin[i]->scriptable(this);
			qDebug() << "Plugin add in the script module: " << lstPugin[i]->name();
		}else{
			qDebug() << "Plugin failed to be add in the script module: " << lstPugin[i]->name();
		}


	}

	// add some tool function
	intToolFunction();

	//To allow event processing during interpreter execution one can specify the processing interval 
	//to be a positive value, indicating the number of milliseconds between each time 
	//QCoreApplication::processEvents() is called.
	this->setProcessEventsInterval (15);
	this->initSData2D();
	this->initSPlot2D();




}



////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SScriptEngine::initData2D()
///
/// \brief	add to the engine the possibility to instantiate a new \c SData2D
///
/// \so SData2D
////////////////////////////////////////////////////////////////////////////////////////////////////
void SScriptEngine::initSData2D(){
	static bool initialized = false;

	if(!initialized){ // evite le multi initialitation
		initialized = true;
		SData2DScript data2D;
		QScriptValue qsData2D = this->newQObject(&data2D);
		this->setDefaultPrototype(qMetaTypeId<SData2D*>(),qsData2D);

		QScriptValue ctorData2D = this->newFunction(SData2DScript::qsCtor,qsData2D);
		this->globalObject().setProperty("SData2D", ctorData2D);

		qScriptRegisterMetaType<SData2D>(this, SData2DScript::toScriptValue, SData2DScript::fromScriptValue);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SScriptEngine::initSPlot2D()
///
/// \brief	add to the engine the possibility to instantiate a new \c SPlot2D
///
/// \so SPlot2D
////////////////////////////////////////////////////////////////////////////////////////////////////
void SScriptEngine::initSPlot2D(){
	static bool initialized = false;

	if(!initialized){ // evite le multi initialitation
		initialized = true;
		SPlot2D plot2D;
		QScriptValue qsPlot2D = this->newQObject(&plot2D);
		this->setDefaultPrototype(qMetaTypeId<SPlot2D*>(),qsPlot2D);

		QScriptValue ctorPlot2D = this->newFunction(SPlot2D::qsCtor,qsPlot2D);
		this->globalObject().setProperty("SPlot2D", ctorPlot2D);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SScriptEngine::setDebugger(QScriptEngineDebugger * debugger)
///
/// \brief	get the debugger object, the SScriptEngine object instantiates one in the constructor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
 const QScriptEngineDebugger* SScriptEngine::debugger() const{
	 
	return qsDebugger;

 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SScriptEngine::abort()
///
/// \brief	(SLOT) Aborts any script evaluation currently taking place in this engine.
///
/// If the engine isn't evaluating a script (i.e. isEvaluating() returns false), 
/// this function does nothing.
///
/// \remark This function are the same that QScriptEngine::abortEvaluation() but it is a slot.
////////////////////////////////////////////////////////////////////////////////////////////////////
  void SScriptEngine::abort() {
	this->abortEvaluation ();
	this->collectGarbage();
 }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QScriptValue SScriptEngine::run( const QString & program, const QString & fileName, 
///												int lineNumber, bool debugger)
///
/// \brief	(SLOT) Evaluates program, using lineNumber as the base line number, and returns the result of the evaluation.
///
/// \param program		The script code will be evaluated in the current context.
///
/// \param fileName		is used for error reporting. For example in error objects 
///						the file name is accessible through the "fileName" property 
///						if it's provided with this function.
///
/// \param lineNumber	is used to specify a starting line number for program; 
///						line number information reported by the engine that pertain to this
///						evaluation (e.g. \c uncaughtExceptionLineNumber()) will be based on this 
///						argument. For example, if program consists of two lines of code, and 
///						the statement on the second line causes a script exception, 
///						\c uncaughtExceptionLineNumber() would return the given lineNumber plus one.
///						When no starting line number is specified, line numbers will be 1-based.
///
/// \param debugger		show or not the debugger 
///
/// The script code will be evaluated in the current context.
///
/// \remark use the function evaluate of the QScriptEngine parent-object
////////////////////////////////////////////////////////////////////////////////////////////////////
QScriptValue SScriptEngine::run( const QString & program, const QString & fileName, int lineNumber,  bool debugger){

	if(!this->isEvaluating()){
		qsDebugger->setAutoShowStandardWindow(false);
		if(debugger){			
			qsDebugger->action(QScriptEngineDebugger::InterruptAction)->trigger();
		}

		 QScriptValue res = this->evaluate( program,  fileName, lineNumber);
	

		if(this->hasUncaughtException()){
		  qDebug()	<< "Uncaught exception at line"
					<< this->uncaughtExceptionLineNumber() << ": "
					<< qPrintable(this->uncaughtException().toString())
					<< "\n\n"
					<< "Backtrace: "
					<< qPrintable(this->uncaughtExceptionBacktrace().join(", "))
					<< "\n";
		  this->clearExceptions ();

	  }
		return res;
	}else{
		emit alreadyRun();
		return QScriptValue(false);
	}
 }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SScriptEngine::intToolFunction()
///
/// \brief	load the tool functions like delay(), debug(), ... in the script engin
///
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
void SScriptEngine::intToolFunction()
{
	// add function delay to the script
	// wait a certain time before go ahead.
	QScriptValue qsvDelay = this->newFunction(qsDelay);
	this->globalObject().setProperty("delay", qsvDelay);

	// add function debug to the script
	// write something to the debug console
	QScriptValue qsvDebug = this->newFunction(qsDebug);
	this->globalObject().setProperty("debug", qsvDebug);

	// add function stop to the script
	// stop the script.
	QScriptValue qsvStop = this->newFunction(qsStop);
	this->globalObject().setProperty("stop", qsvStop);

	// the path of the application
	this->evaluate("var app = new Object(); app.path = \""+ QApplication::applicationDirPath() +"\" ;","Initialization");

	// add function warningMsgBox to the script
	// call a Message Box with a warning icon.
	QScriptValue qsvWarningMsgBox = this->newFunction(qsWarningMsgBox);
	this->globalObject().setProperty("warningMsgBox", qsvWarningMsgBox);

	// add function nowTime to the script
	// return the time.
	QScriptValue qsvNowTime = this->newFunction(qsNowTime);
	this->globalObject().setProperty("nowTime", qsvNowTime);

	// add function nowDate to the script
	// return the date.
	QScriptValue qsvNowDate = this->newFunction(qsNowDate);
	this->globalObject().setProperty("nowDate", qsvNowDate);

	// add function warningMsgBox to the script
	// clear the output log box.
	QScriptValue qsvClear = this->newFunction(qsClear);
	this->globalObject().setProperty("clear", qsvClear);

	// add function bip to the script
	// do a 'bip' sound.
	QScriptValue qsvBip = this->newFunction(qsBip);
	this->globalObject().setProperty("bip", qsvBip);

	//include a file to the current context
	QScriptValue qsvInclude = this->newFunction(qsInclude);
	this->globalObject().setProperty("include", qsvInclude);


}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QScriptValue qsDelay(QScriptContext * context, QScriptEngine * qsEng)
///
/// \brief	(SCRIPTABLE) (with delay())
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QScriptValue qsDelay(QScriptContext * context, QScriptEngine * qsEng)    /*Pause l'application pour i seconds*/
{
    clock_t start,end;
    start=clock();

	double i = context->argument(0).toNumber();
    while(((end=clock())-start)<=i*CLOCKS_PER_SEC){
		QCoreApplication::processEvents ();
	}

	return QScriptValue(qsEng,true);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	 QScriptValue qsDebug(QScriptContext *context, QScriptEngine *engine)
///
/// \brief	(SCRIPTABLE) (with debug()) Write something to the debug console.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
 QScriptValue qsDebug(QScriptContext *context, QScriptEngine *engine)
 {
     QString result;
     for (int i = 0; i < context->argumentCount(); ++i) {
         if (i > 0)
             result.append(" ");
         result.append(context->argument(i).toString());
     }

		qDebug() << "SCRIPT : "<< result;

     return engine->undefinedValue();
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn QScriptValue qsStop( QScriptContext *context, QScriptEngine *engine )
 ///
 /// \brief	(SCRIPTABLE) (with stop()) stop the script.
 ///
 /// \example stop();
 ///
 /// \ingroup SScriptMod	
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 QScriptValue qsStop( QScriptContext *context, QScriptEngine *engine )
 {
	engine->abortEvaluation();

	 return QScriptValue(); // pour coller aux spécifications du moteur de script
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \fn  QScriptValue qsWarningMsgBox( QScriptContext *context, QScriptEngine *engine )
 ///
 /// \brief	(SCRIPTABLE) (with warningMsgBox()) show a warning message box with. 
 ///
 /// \example warningMsgBox("be careful!", "My title");
 /// 
 /// \deprecated Use the Qt binding.
 ///
 /// The first argument is text and the second the title.
 ///
 /// \ingroup SScriptMod	
 ////////////////////////////////////////////////////////////////////////////////////////////////////
  QScriptValue qsWarningMsgBox( QScriptContext *context, QScriptEngine *engine ){

	  QString title = "SpinToolBox Script";

	  if (context->argumentCount()>=1 && context->argument(0).isString()){

		if (context->argumentCount()>=2 && context->argument(1).isString()){
			title += ": " + context->argument(1).toString();
		}

		QMessageBox::warning(NULL, title, context->argument(0).toString(), QMessageBox::Ok, NULL);
	  }

	  return QScriptValue(); // pour coller aux spécifications du moteur de script
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	    QScriptValue qsNowDate( QScriptContext *context, QScriptEngine *engine )
  ///
  /// \brief	(SCRIPTABLE) (with nowDate()) return the date of today, see the documentation of qt for the argument
  ///
  /// \example nowDate("yyyymmdd"); return 20110309
  /// 
  /// \deprecated Use the Qt binding.
  ///
  /// \ingroup SScriptMod	
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  QScriptValue qsNowDate( QScriptContext *context, QScriptEngine *engine ){
	  //get current date
	  QDate date = QDate::currentDate();

	  if (context->argumentCount()>=1 && context->argument(0).isString()){
		  return QScriptValue(date.toString(context->argument(0).toString()));
	  }

	  return QScriptValue(); 
  }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	    QScriptValue qsNowTime( QScriptContext *context, QScriptEngine *engine )
///
/// \brief	(SCRIPTABLE) (with nowTime()) return the time, see the documentation of qt for the argument
///
/// \example nowTime(""hh-mm-ss""); return 16-03-22
/// 
/// \deprecated Use the Qt binding.
///
/// \ingroup SScriptMod	
////////////////////////////////////////////////////////////////////////////////////////////////////
  QScriptValue qsNowTime( QScriptContext *context, QScriptEngine *engine ){
	  //get current time
	  QTime time = QTime::currentTime();

	  if (context->argumentCount()>=1 && context->argument(0).isString()){
		  return QScriptValue(time.toString(context->argument(0).toString()));
	  }

	  return QScriptValue(); 
  }


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	   QScriptValue qsClear( QScriptContext *context, QScriptEngine *engine )
///
/// \brief	(SCRIPTABLE) (with clear()) clear the Debug Output text, the Console and the Error Log
///
/// \example clear(); 
/// \ingroup SScriptMod	
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QScriptValue qsClear( QScriptContext *context, QScriptEngine *engine ) {

		SScriptEngine * qsEng = qobject_cast<SScriptEngine *>(engine);

	if (context->argumentCount()==1 && context->argument(0).isString()){

		QString cmd = context->argument(0).toString();

		if(cmd.contains("DebugOutput",Qt::CaseInsensitive)){
			qsEng->debugger()->action(QScriptEngineDebugger::ClearDebugOutputAction)->trigger();
		}
		
		if(cmd.contains("Console",Qt::CaseInsensitive)){
			qsEng->debugger()->action(QScriptEngineDebugger::ClearConsoleAction)->trigger();
		}

		if(cmd.contains("ErrorLog",Qt::CaseInsensitive)){
			qsEng->debugger()->action(QScriptEngineDebugger::ClearErrorLogAction)->trigger();

		}
		return QScriptValue();
	}

	qsEng->debugger()->action(QScriptEngineDebugger::ClearDebugOutputAction)->trigger();
	qsEng->debugger()->action(QScriptEngineDebugger::ClearConsoleAction)->trigger();
	qsEng->debugger()->action(QScriptEngineDebugger::ClearErrorLogAction)->trigger();

	return QScriptValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	   QScriptValue qsClear( QScriptContext *context, QScriptEngine *engine )
///
/// \brief	(SCRIPTABLE) (with bip()) does a bip-sound 
///
/// \example bip(); 
///
/// \TODO the default sound is played instead of the wav file, I do not know why...
/// \ingroup SScriptMod	
////////////////////////////////////////////////////////////////////////////////////////////////////
QScriptValue qsBip( QScriptContext *context, QScriptEngine *engine ) {

 QSound::play(":/sounds/bip.wav");
 	return QScriptValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	   QScriptValue qsClear( QScriptContext *context, QScriptEngine *engine )
///
/// \brief	(SCRIPTABLE) (with include()) include a file to the current context
///
/// \example include("c:\\mylib.js"); 
///
/// \ingroup SScriptMod	
////////////////////////////////////////////////////////////////////////////////////////////////////
QScriptValue qsInclude(QScriptContext *context, QScriptEngine *engine )
{
	
	if (context->argumentCount()==1 && context->argument(0).isString()){


	QFile scriptFile(context->argument(0).toString());

	//check file is exited or not
	if(!scriptFile.open(QIODevice::ReadOnly))
	{	
		// create location object for the stack
		/*QScriptValue location = engine->newObject();
		location.setProperty("fileName", QScriptValue(__FILE__));
		location.setProperty("lineNumber", QScriptValue(__LINE__));
		location.setProperty("functionName", QScriptValue(__FUNCTION__));*/

		// create stack array with one location
		/*QScriptValue stack = engine->newArray();
		stack.setProperty(0, location);*/

		// create Error object and set properties
		QScriptValue err = context->throwError("The file :" + context->argument(0).toString() + "Cannot be read."); // Arghh...
		/*err.setProperty("fileName", engine->toScriptValue(__FILE__));
		err.setProperty("lineNumber", engine->toScriptValue(__LINE__));
		err.setProperty("stack", stack);*/

		// throw modifier Error object
		context->throwValue(err);
		


		return QScriptValue();
	}

	//load file
	QTextStream stream(&scriptFile);
	QString s=stream.readAll();
	scriptFile.close();

	//set ScriptContext
	QScriptContext *context = engine->currentContext();
	QScriptContext *parent=context->parentContext();
	if(parent!=0)
	{
		context->setActivationObject(context->parentContext()->activationObject());
		context->setThisObject(context->parentContext()->thisObject());
	}

	//execute the script
	QScriptValue result = engine->evaluate(s);
	return result;
	}
	return QScriptValue();
}