#ifndef SUIMAINWINDOWS_H
#define SUIMAINWINDOWS_H




#include <QtCore>
#include <QtGui>

#include "GeneratedFiles\ui_SUiMainWindow.h"
#include "SUiCtrlPan.h"
#include "SUiPluginManager.h"

//script engine
#include <QtScript/QScriptengine>
#include <QtScriptTools/qscriptenginedebugger.h>
#include <SScript/SScriptEngine.h>

class SUiScriptEditor;
class SUiCmdMan;

class SUiMainWindow : public QMainWindow, public Ui::SUiMainWindow
{
	Q_OBJECT
public slots:
	void on_cmdOpen_clicked();
	void on_cmdNewScript_clicked();
	void on_cmdCmdMan_clicked();
	void on_cmdQuit_clicked();
	void on_cmdPlgMng_clicked();
	void dropEvent ( QDropEvent * event );
	void dragEnterEvent(QDragEnterEvent *event);


public:
	SUiMainWindow(QWidget *parent = 0);
	~SUiMainWindow();

private:
	void newScriptWindow(QString file = "");
	void closeEvent(QCloseEvent *e);
	void askQuit();
	void openFile(QStringList paths);


	// pour le moteur de script 
	void startScriptEngine();
	void killScriptEngine();


	//pour récuperer les differents element du moteur de script
	QWidget * wdgDbgConsole;
	QWidget * wdgDbgText;
	QWidget * wdgDbgOutput;
	QWidget * wdgDbgErrorLog;
	QWidget* wdgDbgLocals;
	QWidget * wdgDbgStack;
	QWidget* wdgDbgBreakpoints;


	SPlgInfo PlgInfoCtor( SDevicePluginInterface * myPlugin );

	QList<SPlgInfo> lstPuginInfo;
	QList<SDevicePluginInterface *> lstPugin;

	SUiCmdMan * winCmdMan;
	SUiCtrlPan * winCtrlPan;
	SUiScriptEditor * winScriptEditor;
	SScriptEngine * qsEgn; ///<Script engine

	SGlobalMetaDataMap gmdm;
};

#endif // SUIMAINWINDOWS_H
