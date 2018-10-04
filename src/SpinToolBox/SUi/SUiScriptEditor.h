/****************************************************************************
**
** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information help Qt licensing is available at:
** http://www.trolltech.com/products/qt/licensing.html or by
** contacting info@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include "SScript\SScriptEngine.h"

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qsciapis.h> 

class QAction;
class QMenu;
class QsciScintilla;
class QScriptEngineDebugger;
class QStackedLayout;

class SUiScriptEditor : public QMainWindow
{
    Q_OBJECT

public:
    SUiScriptEditor(SScriptEngine* qsEngine, QString file = "", QWidget * parent =0);

protected:
    void closeEvent(QCloseEvent *event);

signals:
	void run( const QString & program, const QString & fileName , int lineNumber, bool debugger );
	void abortEngine();

public slots:
	void alreadyRun(); 
	void swichToDebugMode();
	void swichToEditMode();
	void onFocus(QWidget * , QWidget * );

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void help();
    void documentWasModified();
	void execute();
	void switchLexerNormal();
	void switchLexerDebugComp();
	void throwKill();
	void endKilling();
	void tabDbgCurrentChanged(int index);
	void executeSelectedText();


private:
	
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
	void createScintilla();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
	void setupUI();


	QsciLexerJavaScript *lexerJSNormal;
	QsciLexerJavaScript *lexerJSDebugComp;
    QsciScintilla *txtSci; 

    QString curFile;

    QMenu *mnuFile;
    QMenu *mnuEdit;
    QMenu *mnuHelp;
	QMenu *mnuScript;
	QMenu *mnuHighlighting;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
	QToolBar *scriptToolBar;

    QAction *newAct; /// \TODO changer les nom pour coherance
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *helpAct;
	QAction *actCallTips;

	QAction *actExecute;
	QAction *actSelectedExecute;
	QAction *actDebugTogg;
	QAction *actDbgInterrupt;
	QAction *actDbgContinue ;
    QAction *actDbgStepOver ;
    QAction *actDbgStepInto;
	QAction* actDbgClearConsole;
	QAction* actDbgClearDebugOutput;
	QAction* actDbgClearErrorLog;

	QAction *actLexerJSNormal;
	QAction *actLexerJSDebugComp;

	QAction *actKill;
	SScriptEngine* qsEng ;

	QWidget * wdgDbgConsole;
	QWidget * wdgDbgText;
	QWidget * wdgDbgOutput;
	QWidget * wdgDbgErrorLog;
	QWidget* wdgDbgLocals;
	QWidget * wdgDbgStack;
	QWidget* wdgDbgBreakpoints;

	QStackedLayout* stkText;
	QTabWidget *	tabDbg;
	int tabDbgCurrentTab;
	QSplitter * splitter;
	
};

#endif
