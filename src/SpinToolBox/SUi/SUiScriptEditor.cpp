
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

#include <QtGui>
#include <QApplication>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qsciapis.h> 

#include <QtScriptTools/qscriptenginedebugger.h>
#include "SScript\SScriptEngine.h"
#include "SUiScriptEditor.h"

#include <time.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	SUiScriptEditor::SUiScriptEditor(SScriptEngine* qsEngine , QString file, QWidget * parent)
///
/// \brief	Constructor.
///
/// \author	Sylvain Martin
/// \date	16/11/2012
///
/// \param [in,out]	qsEngine	The QScript engine.
/// \param	file				The file that the main window "want" to load or an empty string.
/// \param [in,out]	parent  	If non-null, the parent.
////////////////////////////////////////////////////////////////////////////////////////////////////
SUiScriptEditor::SUiScriptEditor(SScriptEngine* qsEngine  , QString file,  QWidget * parent):
QMainWindow(parent), qsEng(qsEngine),
	tabDbgCurrentTab(0),
	lexerJSDebugComp(NULL)
{

	//Scintilla text edit
	txtSci = new QsciScintilla(this);
	txtSci->SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR,0);

	setupUI();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	createScintilla();
	readSettings();

	//we connect the window with the script engine
	this->connect(this, SIGNAL(run(const QString &, const QString &, int, bool)), 
		qsEngine, SLOT(run(const QString &, const QString &, int, bool)));

	this->connect(qsEngine, SIGNAL(alreadyRun()), this, SLOT(alreadyRun()));
	this->connect(qsEngine->debugger(), SIGNAL(evaluationSuspended()),this , SLOT(swichToDebugMode()));
	this->connect(qsEngine->debugger(), SIGNAL(evaluationResumed()),this , SLOT(swichToEditMode()));

	connect(qApp, SIGNAL(focusChanged ( QWidget * , QWidget *  ) ),this,SLOT(onFocus(QWidget * , QWidget * )));
	connect(this, SIGNAL(abortEngine()), qsEngine, SLOT(abort()));

	if(!file.isEmpty()){
		loadFile(file);
	}else{
		setCurrentFile("");
	}

	this->setWindowIcon(QIcon(":icon/scriptedit.png"));

}


void SUiScriptEditor::closeEvent(QCloseEvent *event)
{
	if (maybeSave()) {
		writeSettings();
		event->accept();
	} else {
		event->ignore();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::newFile()
///
/// \brief	Creates a new file.
///
/// \author	Sylvain Martin
/// \date	16/11/2012
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::newFile()
{
	if (maybeSave()) {
		txtSci->clear();
		setCurrentFile("");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::open()
///
/// \brief	Opens a file.
///
/// \author	Sylvain Martin
/// \date	16/11/2012
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::open()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this, "Choose a script file",
			QApplication::applicationDirPath (), 
			"Script Files (*.js *.stb.js);;Other text file (*.txt *.*)");

		if (!fileName.isEmpty())
			loadFile(fileName);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SUiScriptEditor::save()
///
/// \brief	Saves the current file.
///
/// \author	Sylvain Martin
/// \date	16/11/2012
///
/// \return	true if it succeeds, false if it fails.
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SUiScriptEditor::save()
{
	if (curFile.isEmpty()) {
		return saveAs();
	} else {
		return saveFile(curFile);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SUiScriptEditor::saveAs()
///
/// \brief	Saves the file with a new name/location.
///
/// \author	Sylvain Martin
/// \date	16/11/2012
///
/// \return	true if it succeeds, false if it fails.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool SUiScriptEditor::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Choose a script file", QApplication::applicationDirPath (), 
		"Script Files (*.js *.stb.js);;Other text file (*.txt *.*)");
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

void SUiScriptEditor::help()
{
	QMessageBox::warning ( this, "Help", "To consult the documentation, generate the Doxygene documentation....", QMessageBox::Ok);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::documentWasModified()
///
/// \brief	put a stat (*) next to the name of the document if this on was modified since the last save.
///
/// \author	Sylvain Martin
/// \date	16/11/2012
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::documentWasModified()
{
	setWindowModified(txtSci->isModified());
}
//////////////////////////////////////////////////////////////////////////
/// \fn void SUiScriptEditor::createActions()
///
/// \brief Create the action.
///
/////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::createActions(){

	//action of execute the script
	actExecute = new QAction(QIcon(":icon/execute.png"), "Execute",this);
	actExecute->setShortcut(Qt::CTRL +  Qt::Key_E);
	actExecute->setStatusTip(tr("Execute the script"));
	connect(actExecute, SIGNAL(triggered()), this, SLOT(execute()));

	//action execute the selected text
	actSelectedExecute = new QAction(QIcon(":icon/execute.png"), "Execute the selected text",this);
	actSelectedExecute->setShortcut(Qt::CTRL + Qt::SHIFT +  Qt::Key_E);
	actSelectedExecute->setStatusTip(tr("Execute the selected text"));
	connect(actSelectedExecute, SIGNAL(triggered()), this, SLOT(executeSelectedText()));

	// action of toggle the debugger
	actDebugTogg = new QAction(QIcon(":icon/debug.png"), tr("&Debugger"), this);
	actDebugTogg->setStatusTip(tr("Activate/deactivate the debugger"));
	actDebugTogg->setShortcut(Qt::CTRL  + Qt::Key_D);
	actDebugTogg->setCheckable (true);
	actDebugTogg->setChecked (false);

	// kill the script	
	///\TODO find a way to kill the script
	actKill = new QAction(QIcon(":icon/kill.png"), "throwKill",this);
	actKill->setShortcut(Qt::CTRL   + Qt::Key_K);
	actKill->setStatusTip(tr("throwKill the script!"));
	connect(actKill, SIGNAL(triggered()), this, SLOT(throwKill()));

	// debugger actions
	actDbgInterrupt = qsEng->debugger()->action( QScriptEngineDebugger::InterruptAction);
	actDbgContinue = qsEng->debugger()->action(QScriptEngineDebugger::ContinueAction);
	actDbgStepOver = qsEng->debugger()->action(QScriptEngineDebugger::StepOverAction);
	actDbgStepInto = qsEng->debugger()->action(QScriptEngineDebugger::StepIntoAction);
	actDbgClearConsole = qsEng->debugger()->action(QScriptEngineDebugger::ClearConsoleAction);
	actDbgClearDebugOutput = qsEng->debugger()->action(QScriptEngineDebugger::ClearDebugOutputAction);
	actDbgClearErrorLog = qsEng->debugger()->action(QScriptEngineDebugger::ClearErrorLogAction);


	actDbgClearDebugOutput->setShortcut(Qt::Key_F2);
	actDbgClearConsole->setShortcut(Qt::Key_F3);
	actDbgClearErrorLog->setShortcut(Qt::Key_F4);

	//action of show the completion list
	actCallTips = new QAction("Call Tips",this);
	actCallTips->setShortcut(Qt::CTRL + Qt::Key_Space);
	actCallTips->setStatusTip(tr("Show the call tips"));
	connect(actCallTips, SIGNAL(triggered()), txtSci, SLOT(autoCompleteFromAll()));

	//switch the lexer between the two mode
	actLexerJSNormal = new QAction("Normal mode",this);
	connect(actLexerJSNormal, SIGNAL(triggered()), this, SLOT(switchLexerNormal()));

	actLexerJSDebugComp = new QAction("Debug compatibility mode",this);
	connect(actLexerJSDebugComp, SIGNAL(triggered()), this, SLOT(switchLexerDebugComp()));

	//action of put a new script
	newAct = new QAction(QIcon(":icon/new.png"), tr("&New"), this);
	newAct->setShortcut(tr("Ctrl+N"));
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

	//action of open a script
	openAct = new QAction(QIcon(":icon/open.png"), tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	//action of save a script
	saveAct = new QAction(QIcon(":icon/save.png"), tr("&Save"), this);
	saveAct->setShortcut(tr("Ctrl+S"));
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	//action of save as a script
	saveAsAct = new QAction(tr("Save &As..."), this);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	//action of close the window
	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	// action of cut
	cutAct = new QAction(QIcon(":icon/cut.png"), tr("Cu&t"), this);
	cutAct->setShortcut(tr("Ctrl+X"));
	cutAct->setStatusTip(tr("Cut the current selection's contents to the "
		"clipboard"));
	connect(cutAct, SIGNAL(triggered()), txtSci, SLOT(cut()));

	//action of copy
	copyAct = new QAction(QIcon(":icon/copy.png"), tr("&Copy"), this);
	copyAct->setShortcut(tr("Ctrl+C"));
	copyAct->setStatusTip(tr("Copy the current selection's contents to the "
		"clipboard"));
	connect(copyAct, SIGNAL(triggered()), txtSci, SLOT(copy()));

	//action of past
	pasteAct = new QAction(QIcon(":icon/paste.png"), tr("&Paste"), this);
	pasteAct->setShortcut(tr("Ctrl+V"));
	pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
		"selection"));
	connect(pasteAct, SIGNAL(triggered()), txtSci, SLOT(paste()));

	// show the help box
	helpAct = new QAction(tr("&Help"), this);
	helpAct->setStatusTip(tr("Show the application's documentation"));
	connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));



	cutAct->setEnabled(false);
	copyAct->setEnabled(false);

	connect(txtSci, SIGNAL(copyAvailable(bool)),
		cutAct, SLOT(setEnabled(bool)));
	connect(txtSci, SIGNAL(copyAvailable(bool)),
		copyAct, SLOT(setEnabled(bool)));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::createMenus()
///
/// \brief	setup the menu bar
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::createMenus()
{
	mnuFile = menuBar()->addMenu(tr("&File"));
	mnuFile->addAction(newAct);
	mnuFile->addAction(openAct);
	mnuFile->addAction(saveAct);
	mnuFile->addAction(saveAsAct);
	mnuFile->addSeparator();
	mnuFile->addAction(exitAct);



	mnuEdit = menuBar()->addMenu(tr("&Edit"));
	mnuEdit->addAction(cutAct);
	mnuEdit->addAction(copyAct);
	mnuEdit->addAction(pasteAct);
	mnuEdit->addSeparator();
	mnuEdit->addAction(actCallTips);
	mnuHighlighting = mnuEdit->addMenu("Syntax highlighting");
	mnuHighlighting->addAction(actLexerJSNormal);
	mnuHighlighting->addAction(actLexerJSDebugComp);


	mnuScript = menuBar()->addMenu(tr("&Script"));
	mnuScript->addAction(actExecute);
	mnuScript->addAction(actSelectedExecute);	
	mnuScript->addAction(actDebugTogg);

	mnuScript->addSeparator();
	mnuScript->addAction(actKill);
	mnuScript->addAction(actDbgInterrupt);
	mnuScript->addAction(actDbgContinue);
	mnuScript->addAction(actDbgStepOver) ;
	mnuScript->addAction(actDbgStepInto);

	mnuScript->addSeparator();
	mnuScript->addAction(actDbgClearConsole);
	mnuScript->addAction(actDbgClearDebugOutput);
	mnuScript->addAction(actDbgClearErrorLog);

	menuBar()->addSeparator();

	mnuHelp = menuBar()->addMenu(tr("&Help"));
	mnuHelp->addAction(helpAct);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::createToolBars()
///
/// \brief	setup the tools bar
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::createToolBars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(newAct);
	fileToolBar->addAction(openAct);
	fileToolBar->addAction(saveAct);

	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(cutAct);
	editToolBar->addAction(copyAct);
	editToolBar->addAction(pasteAct);

	scriptToolBar = addToolBar(tr("Script"));
	scriptToolBar->addAction(actExecute);
	scriptToolBar->addAction(actDebugTogg);
	scriptToolBar->addSeparator(); //----
	scriptToolBar->addAction(actKill);
	scriptToolBar->addAction(actDbgInterrupt);
	scriptToolBar->addAction(actDbgContinue);
	scriptToolBar->addAction(actDbgStepOver);
	scriptToolBar->addAction(actDbgStepInto);



}

void SUiScriptEditor::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::readSettings()
///
/// \brief	Reads the settings.
///
/// \author	Sylvain Martin
/// \date	16/11/2012
////////////////////////////////////////////////////////////////////////////////////////////////////

void SUiScriptEditor::readSettings(){

	QSettings settings ( "SpinToolBox.ini", QSettings::IniFormat, this );	
	settings.beginGroup("ScriptEditor");	
	

	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(700, 600)).toSize();
	resize(size);
	move(pos);
	splitter->restoreState(settings.value("splitterSizes").toByteArray());

	// on ferme la section (pour future utilisation du fichier ini)
	settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::writeSettings()
///
/// \brief	Writes the settings.
///
/// \author	Sylvain Martin
/// \date	16/11/2012
////////////////////////////////////////////////////////////////////////////////////////////////////

void SUiScriptEditor::writeSettings()
{
	
	QSettings settings( "SpinToolBox.ini", QSettings::IniFormat, this );	
	settings.beginGroup("ScriptEditor");	
	
	
	settings.setValue("pos", pos());
	settings.setValue("size", size());
	settings.setValue("ScriptEditorSplitterSizes", splitter->saveState());

	// on ferme la section (pour future utilisation du fichier ini)
	settings.endGroup();

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::maybeSave()
///
/// \brief	ask if the user want save the current file
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SUiScriptEditor::maybeSave()
{
	if (txtSci->isModified()) {
		int ret = QMessageBox::warning(this, tr("SpinToolBox"),
			tr("The script has been modified.\n"
			"Do you want to save your changes?"),
			QMessageBox::Yes | QMessageBox::Default,
			QMessageBox::No,
			QMessageBox::Cancel | QMessageBox::Escape);
		if (ret == QMessageBox::Yes)
			return save();
		else if (ret == QMessageBox::Cancel)
			return false;
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::loadFile(const QString &fileName)
///
/// \brief	open the file
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly)) {
		QMessageBox::warning(this, tr("SpinToolBox"),
			tr("Cannot read file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	txtSci->setText(in.readAll());
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool SUiScriptEditor::saveFile(const QString &fileName)
///
/// \brief	save the file
///
////////////////////////////////////////////////////////////////////////////////////////////////////
bool SUiScriptEditor::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly)) {
		QMessageBox::warning(this, tr("SpinToolBox"),
			tr("Cannot write file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << txtSci->text();
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::createScintilla()
///
/// \brief	set up of the highlight and other stuffs on the text editor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	txtSci->setModified(false);
	setWindowModified(false);

	QString shownName;
	if (curFile.isEmpty())
		shownName = "untitled.js";
	else
		shownName = strippedName(curFile);

	setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("SpinToolBox")));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	QString SUiScriptEditor::strippedName(const QString &fullFileName)
///
/// \brief return the name of the file from the complate path
///
////////////////////////////////////////////////////////////////////////////////////////////////////
QString SUiScriptEditor::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::execute()
///
/// \brief	slot that emits a signal for run the script
///
/// normally the run signal is connected to run slot of the script engine
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::execute(){

	emit run(txtSci->text(),curFile,1 , actDebugTogg->isChecked ());

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::alreadyRun()
///
/// \brief	(SLOT) slot that puts a message in the statue bar because only on script can be execute  at once
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::alreadyRun(){
	statusBar()->showMessage("Only on script can be execute at once",1000);

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::swichToDebugMod()
///
/// \brief	(SLOT) switch the text editor with the text display of the debugger
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::swichToDebugMode(){
	stkText->setCurrentIndex(1);

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::swichToEditMode()
///
/// \brief	(SLOT) switch text display of the debugger with the Scintilla text editor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::swichToEditMode(){
	stkText->setCurrentIndex(0);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::createScintilla()
///
/// \brief	set up of the highlight and other stuffs on the text editor
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::createScintilla(){

	txtSci->setUtf8(true); // encodage en UTF8

	txtSci->setMarginLineNumbers(1, true); // numérotation des lignes
	txtSci->setMarginWidth(1, 35); // agrandissement de la marge
	txtSci->setAutoIndent(true);

	//we have tow lexer, in function of wich on the user prefers
	lexerJSNormal = new QsciLexerJavaScript; // création du lexer
	lexerJSDebugComp = new QsciLexerJavaScript; // création du lexer

	txtSci->setLexer(lexerJSNormal); // application du lexer au QsciScintilla

	QsciAPIs *api = new QsciAPIs(lexerJSNormal); // déclaration de l'api

	api->load(QApplication::applicationDirPath() + "/AutoCompletion.api"); // chargement du fichier texte
	api->prepare(); // préparation  de l'auto-completion
	lexerJSNormal->setAPIs(api); // application de l'api au lexer

	txtSci->setAutoCompletionSource(QsciScintilla::AcsAPIs); // application de l'auto-completion à la zone de texte
	txtSci->setAutoCompletionThreshold(2); // la liste sera affichée au bout de 1 caractère

	QStringList sep;
	sep << " " << "\t" << "\n"<< ";" << ",";
	txtSci->setAutoCompletionWordSeparators(sep);


	txtSci->setAutoCompletionFillupsEnabled(true);
	txtSci->setCallTipsStyle(QsciScintilla::CallTipsContext);
	txtSci->setFolding(QsciScintilla::BoxedFoldStyle, 2);


	txtSci->setUnmatchedBraceBackgroundColor(QColor("red"));

//	txtSci->setMatchedBraceIndicator(QsciScintilla::RoundBoxIndicator);

	txtSci->setBraceMatching(QsciScintilla::SloppyBraceMatch) ;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::switchLexerNormal()
///
/// \brief	switch the Lexer of Scintilla to the Normal mode
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::switchLexerNormal()
{
	txtSci->setLexer(lexerJSNormal);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::switchLexerDebugComp()
///
/// \brief	switch the Lexer of Scintilla to the Debug compatibility mode
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::switchLexerDebugComp()
{
	if(lexerJSDebugComp == NULL){

		QsciAPIs *api = new QsciAPIs(lexerJSDebugComp); // déclaration de l'api

		api->load(QApplication::applicationDirPath() + "/AutoCompletion.api"); // chargement du fichier texte
		api->prepare(); // préparation  de l'auto-completion

		lexerJSDebugComp->setAPIs(api);

		// set the fonts and colors
		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleNormal), QsciLexerJavaScript::Default );
		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleNormal), QsciLexerJavaScript::Operator );

		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleNormal), QsciLexerJavaScript::Identifier );

		lexerJSDebugComp->setColor(Qt::darkGreen, QsciLexerCPP::DoubleQuotedString );
		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleNormal), QsciLexerCPP::DoubleQuotedString );

		lexerJSDebugComp->setColor(Qt::darkGreen, QsciLexerCPP::SingleQuotedString  );
		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleNormal), QsciLexerCPP::SingleQuotedString );

		lexerJSDebugComp->setColor(Qt::darkBlue, QsciLexerCPP::Number );
		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleNormal), QsciLexerCPP::Number );

		lexerJSDebugComp->setColor(Qt::darkYellow, QsciLexerCPP::Keyword  );
		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleNormal), QsciLexerCPP::Keyword );

		lexerJSDebugComp->setColor(Qt::darkBlue, QsciLexerCPP::PreProcessor  );
		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleNormal), QsciLexerCPP::PreProcessor );

		lexerJSDebugComp->setColor(Qt::darkGreen, QsciLexerCPP::Comment );
		lexerJSDebugComp->setColor(Qt::darkGreen, QsciLexerCPP::CommentLine ); 
		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleItalic), QsciLexerCPP::Comment );
		lexerJSDebugComp->setFont(QFont("Times", 10, QFont::StyleItalic), QsciLexerCPP::CommentLine ); 


	}

	txtSci->setLexer(lexerJSDebugComp);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::setupUI()
///
/// \brief	set up the UI (Scintilla, debug console, ...)
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::setupUI(){


	//a layout for organize the space

	splitter = new QSplitter();
	splitter->setOrientation(Qt::Vertical);

	//Widget from the debugger
	wdgDbgText = (qsEng->debugger()->widget(QScriptEngineDebugger::CodeWidget));
	wdgDbgOutput = (qsEng->debugger()->widget(QScriptEngineDebugger::DebugOutputWidget));
	wdgDbgOutput->setMaximumHeight (500);
	wdgDbgConsole = (qsEng->debugger()->widget(QScriptEngineDebugger::ConsoleWidget));
	wdgDbgConsole->setMaximumHeight (500);
	wdgDbgErrorLog = (qsEng->debugger()->widget(QScriptEngineDebugger::ErrorLogWidget)); 
	wdgDbgErrorLog->setMaximumHeight (500);
	wdgDbgLocals = (qsEng->debugger()->widget(QScriptEngineDebugger::LocalsWidget)); 
	wdgDbgLocals->setMaximumHeight (500);
	wdgDbgStack = (qsEng->debugger()->widget(QScriptEngineDebugger::StackWidget)); 
	wdgDbgStack->setMaximumHeight (500);
	wdgDbgBreakpoints = (qsEng->debugger()->widget(QScriptEngineDebugger::BreakpointsWidget)); 
	wdgDbgBreakpoints->setMaximumHeight (500);

	//we can switch between Scintilla and CodeWidget, so we put a QStackedLayout
	stkText = new QStackedLayout(splitter);
	stkText->addWidget(txtSci);
	stkText->addWidget(wdgDbgText);
	QWidget* textWidget = new QWidget(this);
	textWidget->setLayout(stkText);
	splitter->addWidget(textWidget);
	splitter->setCollapsible(splitter->indexOf(textWidget) ,false);


	//we can switch between the ConsoleWidget and the DebugOutputWidget, hear we put a tabwidget	
	tabDbg = new QTabWidget(splitter);
	tabDbg->setMovable(true);
	tabDbg->setTabShape(QTabWidget::Rounded);
	tabDbg->setDocumentMode(true);
	tabDbg->addTab(wdgDbgConsole, QString("Console"));
	tabDbg->addTab(wdgDbgOutput, QString("Output"));
	tabDbg->addTab(wdgDbgErrorLog, QString("Error Log"));
	tabDbg->addTab(wdgDbgLocals, QString("Locals"));
	tabDbg->addTab(wdgDbgStack, QString("Stack"));
	tabDbg->addTab(wdgDbgBreakpoints, QString("Breakpoints"));
	tabDbg->setMaximumHeight (500);
	splitter->addWidget(tabDbg);

	QList<int> list;
	list.append(500);
	list.append(200);
	splitter->setSizes ( list  );


	//we put all in the main windows
	this->setCentralWidget(splitter);

	connect(txtSci, SIGNAL(textChanged()),
		this, SLOT(documentWasModified()));

	connect(tabDbg, SIGNAL(currentChanged(int)),
		this, SLOT(tabDbgCurrentChanged(int)));

	//we put an icon
	QIcon icon;
	icon.addFile(QString::fromUtf8(":/compass.ico"), QSize(), QIcon::Normal, QIcon::Off);
	this->setWindowIcon(icon);
	

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::setupUI()
///
/// \brief	set up the UI (Scintilla, debug console, ...)
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::onFocus(QWidget * old, QWidget * now){

	if(now == txtSci){
		auto  state = splitter->saveState();

		tabDbg->clear ();
		tabDbg->addTab(wdgDbgConsole, QString("Console"));
		tabDbg->addTab(wdgDbgOutput, QString("Output"));
		tabDbg->addTab(wdgDbgErrorLog, QString("Error Log"));
		tabDbg->addTab(wdgDbgLocals, QString("Locals"));
		tabDbg->addTab(wdgDbgStack, QString("Stack"));
		tabDbg->addTab(wdgDbgBreakpoints, QString("Breakpoints"));
		tabDbg->setCurrentIndex(tabDbgCurrentTab);
		tabDbg->setMaximumHeight (500);

		stkText->removeWidget(wdgDbgText);
		stkText->addWidget(wdgDbgText);
		splitter->restoreState(state);

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::throwKill()
///
/// \brief	(SLOT) when the user clicks on the kill action, ask if he really want it, and if yes, do it
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::throwKill()
{
	if (!qsEng->isEvaluating()){
		return;
	}

	int ret = QMessageBox::question(this, "SpintToolBox",
		"This action will stop the script, do you really want do this?", 
		QMessageBox::Yes,QMessageBox::No);

	if(ret == QMessageBox::No){
		//no so goodbye!
		return;
	}else{

		//on interonpt le script
		actDbgInterrupt->trigger();
		statusBar()->showMessage("Waiting until the end of the current operation (device or C++ function)", 20000);

		// qd script interompu, on l'arrete
		connect(qsEng->debugger(), SIGNAL(evaluationSuspended()), this, SLOT(endKilling()));




	
	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::endKilling()
///
/// \brief	the throwKill function ask to the engine to interrupt, this function stop the engine
/// 		 after the interruption
///
/// \author	Sylvain Martin
/// \date	16/11/2012
////////////////////////////////////////////////////////////////////////////////////////////////////

void SUiScriptEditor::endKilling(){

	swichToEditMode();
	qsEng->abortEvaluation();

	clock_t start,end;
	start=clock();
	
	while(((end=clock())-start)<=0.01*CLOCKS_PER_SEC){
		QCoreApplication::processEvents ();
	}

	actDbgContinue->trigger();
	actDbgClearConsole->trigger();
	
	statusBar()->showMessage(" The script was stopped", 8000);
	//swichToEditMode();

	disconnect(qsEng->debugger(), SIGNAL(evaluationSuspended()), this, SLOT(endKilling()));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::tabDbgCurrentChanged( int index )
///
/// \brief	(SLOT) when the user change of tab, it is useful went we reconstruct the tab when the focus changes
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::tabDbgCurrentChanged( int index )
{
	if(index != -1 && tabDbg->count()==6 ){
		tabDbgCurrentTab = index;
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void SUiScriptEditor::executeSelectedText()
///
/// \brief	(SLOT) Execute the selected text.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiScriptEditor::executeSelectedText(){
	if(txtSci->hasSelectedText()){
		emit run(txtSci->selectedText(),curFile,1 , actDebugTogg->isChecked ());
	}
}