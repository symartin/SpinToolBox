#include "SUiMainWindow.h"

//ui
#include "SUi\SUiScriptEditor.h"
//#include "SUi\SUiCmdMan.h"

#include <QtCore>
#include <QtGui>

#include "SDK/SData/SData2D.h"
#include "SDK/SPlot/SPlot2D.h"

#include "SUi/SUiPluginManager.h"

#include "SDKDevice/SDevicePluginInterface.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::SUiMainWindow()
///
/// \brief	Constructor.
////////////////////////////////////////////////////////////////////////////////////////////////////
SUiMainWindow::SUiMainWindow(QWidget *parent/*=NULL*/):
	 QMainWindow(parent),
	 winCmdMan(NULL),
	 winCtrlPan(NULL),
	 qsEgn(NULL)
{
	setupUi(this);

	setAcceptDrops(true);

	QSettings settings( "SpinToolBox.ini", QSettings::IniFormat );
	settings.beginGroup("plugin");

	QDir plugDir = QDir(qApp->applicationDirPath()); // Comme avant, on crée un QDir.
	plugDir.cd("./plugins/SDevice"); // On se déplace encore.

	// this function has to be executed one (and only once) 
	// before any using of the meta data system
	SGlobalMetaDataMap gmdm;
	gmdm.firstInit();


	foreach(QString file, plugDir.entryList(QDir::Files)) {
		// we load the plugin
		QPluginLoader loader(plugDir.absoluteFilePath(file));

		// if we can instanced it
		if(QObject *plugin = loader.instance()){
			//we cast in SDevicePluginInterface to use it
			SDevicePluginInterface* myPlugin = qobject_cast<SDevicePluginInterface *>(plugin);

			//we take the info on the plugin.
			SPlgInfo tmp = PlgInfoCtor(myPlugin);

			//if this plugin is in the list of the wished plugin and is has a script module, let's go!
			if(settings.value(myPlugin->shortName(), false).toBool()){ //Plugin found and load
				myPlugin->load();
				lstPugin.push_back(myPlugin);
				//qDebug() << myPlugin->shortName();

				tmp.isLoad=true;

			}else{ // Plugin found but not load
				loader.unload();
				tmp.isLoad=false; 
				
			}

			//we put the plugin in the list
			lstPuginInfo.push_back(tmp); 
		}
	}
	//we load the script engine
	qsEgn = new SScriptEngine(lstPugin, &gmdm, this);
}


void SUiMainWindow::startScriptEngine(){
	////Widget from the debugger
	//wdgDbgText = (qsEng->debugger()->widget(QScriptEngineDebugger::CodeWidget));
	//wdgDbgOutput = (qsEng->debugger()->widget(QScriptEngineDebugger::DebugOutputWidget));
	//wdgDbgOutput->setMaximumHeight (500);
	//wdgDbgConsole = (qsEng->debugger()->widget(QScriptEngineDebugger::ConsoleWidget));
	//wdgDbgConsole->setMaximumHeight (500);
	//wdgDbgErrorLog = (qsEng->debugger()->widget(QScriptEngineDebugger::ErrorLogWidget)); 
	//wdgDbgErrorLog->setMaximumHeight (500);
	//wdgDbgLocals = (qsEng->debugger()->widget(QScriptEngineDebugger::LocalsWidget)); 
	//wdgDbgLocals->setMaximumHeight (500);
	//wdgDbgStack = (qsEng->debugger()->widget(QScriptEngineDebugger::StackWidget)); 
	//wdgDbgStack->setMaximumHeight (500);
	//wdgDbgBreakpoints = (qsEng->debugger()->widget(QScriptEngineDebugger::BreakpointsWidget)); 
	//wdgDbgBreakpoints->setMaximumHeight (500);
}
void SUiMainWindow::killScriptEngine(){


}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::~SUiMainWindow()
///
/// \brief	Destructor.
////////////////////////////////////////////////////////////////////////////////////////////////////
SUiMainWindow::~SUiMainWindow()
{
	if(qsEgn != NULL) delete qsEgn;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::on_cmdOpen_clicked()
///
/// \brief	(SLOT) When the user click on the [Open] button
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::on_cmdOpen_clicked(){
	//select one on more file
	QStringList paths = QFileDialog::getOpenFileNames ( this,"Choose a script file", QApplication::applicationDirPath (),
		"Image Files (*.js *.stb.js *.qs);;Data text file (*.txt *.dat);;Other file (*.*)");

	// for each open it
	openFile(paths);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::openFile(QStringList paths)
///
/// \brief	open a list of files
///
/// \param paths a list of path
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::openFile(QStringList paths){
	QStringList extScript;
	extScript << "js" << "qs";

	QStringList extData;
	extData << "txt" << "dat" << "stb";

	for(int i=0; i< paths.size();i++){
		QFileInfo file(paths.at(i));

		if(file.exists()){
			if(extScript.contains(file.suffix(), Qt::CaseInsensitive)){ // script
				newScriptWindow(paths.at(i));
			}else if (extData.contains(file.suffix(), Qt::CaseInsensitive)){ // 2D data
				SData2D data(paths.at(i));
				SPlot2D * plot = new SPlot2D(&data,false);

				plot->setWindowTitle("SpinToolBox - " + file.fileName());
				plot->setTitle(data.colXName() + " vs. " + data.colYName());
				plot->show();
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::on_cmdNewScript_clicked()
///
/// \brief	(SLOT) When the user click on the [New Script] button
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::on_cmdNewScript_clicked(){
	newScriptWindow();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  SUiMainWindow::newScriptWindow(QString file)
///
/// \brief
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::newScriptWindow(QString path/*=""*/){
	//we create a new instance of the script windows
	winScriptEditor = new SUiScriptEditor(qsEgn, path);
	winScriptEditor->setWindowFlags(Qt::Window);

	// let's go!
	winScriptEditor->show();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::on_cmdNewScript_clicked()
///
/// \brief	(SLOT) When the user click on the [Control panel] button
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::on_cmdCmdMan_clicked()
{
	
	
	if (winCtrlPan == NULL){
			winCtrlPan = new SUiCtrlPan(lstPugin);
	}
	winCtrlPan->setWindowFlags(Qt::Window);
	winCtrlPan->setWindowIcon(QIcon(":icon/controlpanel.png"));
	winCtrlPan->setWindowTitle("Control panel - SpinToolBox");
	winCtrlPan->show();
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::on_cmdNewScript_clicked()
///
/// \brief	(SLOT) When the user click on the [Quit] button
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::on_cmdQuit_clicked(){
	askQuit();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::closeEvent(QCloseEvent *e)
///
/// \brief	(SLOT) When the user click on the [X] (close) button
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::closeEvent(QCloseEvent *e){
	e->ignore();
	askQuit();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::askQuit()
///
/// \brief	make sure if the user really want quit, and emit a signal to do it
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::askQuit()
{
	QString txt = 	QString("If you quit, all will stay in this state (field, current, ...). ") +
		QString("Make sure that it does not damage the devices. The script engine, ")+
		QString("if it is running, will be stop brutally. Are you sure to want quit ?") ;

	int ret = QMessageBox::question(this, "Warning",txt,	QMessageBox::Yes,QMessageBox::No);

	if(ret == QMessageBox::Yes){
		qsEgn->abort();
		qApp->quit();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::dropEvent ( QDropEvent * event )
///
/// \brief	When the user drop some elements
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::dropEvent ( QDropEvent * event ){
	QStringList paths;
	QString tmp;
	QString MimeTypeToStrip = "file:///";

	if(event->mimeData()->hasUrls()){
		QList<QUrl> url = event->mimeData()->urls();

		//we want a QStringList, not a QList<QUrl>
		for (int i=0; i<url.size(); i++){
			tmp = url.at(i).toString();
			paths << tmp.right(tmp.size() - MimeTypeToStrip.size());
		}

		openFile(paths);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::dragEnterEvent(QDragEnterEvent *event)
///
/// \brief	Check if the element is "dropable".
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::dragEnterEvent(QDragEnterEvent *event){
	QStringList validExtension;
	validExtension.append("js");
	validExtension.append("qs");
	validExtension.append("txt");
	validExtension.append("dat");
	validExtension.append("stb");

	QString MimeTypeToStrip = "file:///";

	if(event->mimeData()->hasUrls())
	{
		if(event->mimeData()->urls()[0].toString().startsWith(MimeTypeToStrip))
		{
			// Check extension
			QString path = event->mimeData()->urls()[0].toString();
			QString ext = path.mid(path.lastIndexOf(".") + 1);
			if(validExtension.contains(ext, Qt::CaseInsensitive))
				event->acceptProposedAction();
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn  void SUiMainWindow::on_cmdPlgMng_clicked()
///
/// \brief	when the user click on Plugin Manager
////////////////////////////////////////////////////////////////////////////////////////////////////
void SUiMainWindow::on_cmdPlgMng_clicked()
{
	SUiPluginManager* plgMng = new SUiPluginManager(lstPuginInfo,   lstPugin, this);
	plgMng->show();
	connect(plgMng, SIGNAL(accepted()), plgMng, SLOT(close()));
}

SPlgInfo SUiMainWindow::PlgInfoCtor( SDevicePluginInterface * myPlugin )
{
	SPlgInfo plginfo;
	plginfo.name = myPlugin->name();
	plginfo.description = myPlugin->description();
	plginfo.cmdpan = myPlugin->isControlPanel();
	plginfo.scriptable = myPlugin->isScriptable();
	plginfo.shortName = myPlugin->shortName();
	plginfo.sdkVersion = myPlugin->SDKVersion();
	plginfo.plgVersion = myPlugin->plgVersion();
	plginfo.isSetting = myPlugin->isSetting();
	plginfo.isLoad=false;
	return plginfo;
}