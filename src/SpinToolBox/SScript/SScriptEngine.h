/*
Copyright (C) 2010 Sylvain Martin (Spintec - CEA/CNRS/UJF/G-INP)
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

#ifndef SSCRIPTENGIN_H
#define SSCRIPTENGIN_H

#include <QtScript/QScriptengine>
#include <QtScriptTools/qscriptenginedebugger.h>
#include "SDKDevice/SDevicePluginInterface.h" 

class QMainWindow;
class QScriptValue;

QScriptValue qsDelay(QScriptContext * context, QScriptEngine * qsEng) ;
QScriptValue qsDebug(QScriptContext *context, QScriptEngine *engine);
QScriptValue qsStop(QScriptContext *context, QScriptEngine *engine);
QScriptValue qsWarningMsgBox( QScriptContext *context, QScriptEngine *engine );
QScriptValue qsNowTime( QScriptContext *context, QScriptEngine *engine );
QScriptValue qsNowDate( QScriptContext *context, QScriptEngine *engine );
QScriptValue qsClear( QScriptContext *context, QScriptEngine *engine );
QScriptValue qsBip( QScriptContext *context, QScriptEngine *engine );
QScriptValue qsInclude(QScriptContext *context, QScriptEngine *engine );

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SScriptEngine
///
/// \brief	this is a derivate class from QScriptEngine which initialize the the script engine for SpinToolBox
///
/// \author	Sylvain Martin
/// \date	1/28/2011
/// 		
/// \ingroup SScriptMod	
/// 		 
////////////////////////////////////////////////////////////////////////////////////////////////////
class SScriptEngine : public QScriptEngine {
Q_OBJECT;


public slots:
	QScriptValue run ( const QString & program, 
			const QString & fileName = QString(), int lineNumber = 1, bool debugger=false );
	void abort();


signals:
	void exception(int line); ///< emit when an execption occure
	void alreadyRun(); ///< emit when the slot run is call and a script is already running

public:
	const QScriptEngineDebugger * debugger() const;

	SScriptEngine(QList<SDevicePluginInterface *> lstPugin, 
				SGlobalMetaDataMap * GlobalMetaDataMap = NULL, QWidget *parent = 0);
	

	void initSData2D();
	void initSPlot2D();
private:
	void intToolFunction();

protected:
	QMainWindow * qsDebugStdWindow;
	QScriptEngineDebugger * qsDebugger;

};

#endif //SSCRIPTENGIN_H