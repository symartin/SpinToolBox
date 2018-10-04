<?xml version="1.0"?><doc>
<members>
<member name="T:SGlobalMetaDataMap" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="77">
\class	SGlobalMetaDataMap

\brief	class for passing the metadata between all the device plugins. it is derived of QList

\author	Sylvain Martin
\date	02/03/2012

\ingroup SDeviceMod

See also the Qt documentation on the QList.
</member>
<member name="T:SDevicePluginInterface" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="127">
\class

\brief	Virtual class for all the devices Plugin. It is virtual pure so it cannot be instanced.

\author	Sylvain Martin
\date	1/12/2011

\ingroup SDeviceMod
</member>
<member name="M:SDevicePluginInterface.load" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="142">
\fn	bool load()

\brief	initialize the plugin

\author	Sylvain Martin
\date	01/12/2011

\param GlobalMetaDataMap pointer on the global object containing all the metadata

\return true if all is ok, false otherwise
</member>
<member name="M:SDevicePluginInterface.name" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="156">
\fn	QString name() const

\brief	return the complete name of the plugin

\author	Sylvain Martin
\date	01/12/2011

\return return the name of the plugin
</member>
<member name="M:SDevicePluginInterface.shortName" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="168">
\fn	QString shortName() const

\brief	return the short name of the plugin.

\author	Sylvain Martin
\date	01/12/2011

\return return the short name of the plugin
</member>
<member name="M:SDevicePluginInterface.description" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="180">
\fn	QString description() const

\brief	return the description of the plugin

\author	Sylvain Martin
\date	01/12/2011

\return return the description of the plugin
</member>
<member name="M:SDevicePluginInterface.plgVersion" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="192">
\fn	QString plgVersion() const

\brief	return the version of the SDK that is needed for run the plugin

\author	Sylvain Martin
\date	13/01/2011
</member>
<member name="M:SDevicePluginInterface.SDKVersion" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="202">
\fn	QString SDKVersion() const 

\brief	return the version of the SDK which is required for this plugin

\author	Sylvain Martin
\date	13/01/2011
</member>
<member name="M:SDevicePluginInterface.isScriptable" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="212">
\fn	bool isScriptable()

\brief	does the plugin add some function to the script engine

\author	Sylvain Martin
\date	01/12/2011

\return true, yes it does, false, no it does no

\sa isScriptable
</member>
<member name="M:SDevicePluginInterface.scriptable(QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="226">
\fn	bool scriptable( QScriptEngine * engine )

\brief	add (or not) some functions to the script engine

\author	Sylvain Martin
\date	01/12/2011

\param engine the script engine
\sa isScriptable
</member>
<member name="M:SDevicePluginInterface.isSetting" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="239">
\fn	virtual bool isSetting();

\brief	(virtual pure) does the plugin have a setting window ?

\author	Sylvain Martin
\date	25/02/2012

\return true, yes it does, false, no it does no

\sa setting
</member>
<member name="M:SDevicePluginInterface.setting(QWidget*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="253">
\fn	virtual QWidget * setting(QSettings set)=0;

\brief	(virtual pure) give (or not) a setting window.

\author	Sylvain Martin
\date	25/01/2012

\param set the QSettings object of the application
\sa isSetting

\remark it do not manage the destruction of the object, so you ave to define a parent
		or destroy it your self
</member>
<member name="M:SDevicePluginInterface.isControlPanel" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="269">
\fn	bool isControlPanel()

\brief	does the plugin add a tab to the control panel to the script engine

\author	Sylvain Martin
\date	01/12/2011

\return true, yes it does, false, no it does no

\sa ControlPanel()
</member>
<member name="M:SDevicePluginInterface.controlPanel(QWidget*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="283">
\fn	QString controlPanel() const

\brief	add (or not) a tab to the control panel 

\author	Sylvain Martin
\date	01/12/2011

\param engine the script engine
\sa isControlPanel

\remark SDeviceK2400Plugin do not manage the destruction of the object, so you ave to define a parent
		or destroy it your self 
</member>
<member name="M:SDevicePluginInterface.shutdown" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="299">
\fn	void shutdown()

\brief	shutdown the plugin (by example before closing the application)

\author	Sylvain Martin
\date	01/12/2011

</member>
<member name="M:SDevicePluginInterface.unload" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="310">
\fn	bool unload()

\brief	this function is call when the plugin is unload

\author	Sylvain Martin
\date	13/01/2011

\return true if all is ok, false otherwise
</member>
<member name="M:SDevicePluginInterface.state" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="322">
\fn	int SDeviceK2400::state()

\brief	what is the state of the plugin

\author	Sylvain Martin
\date	01/12/2011

0 : ready, 1 : busy, 2 unavailable
</member>
<member name="M:SDevicePluginInterface.available" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="334">
\fn	bool SDeviceK2400::available()

\brief	is the plugin available ?

\author	Sylvain Martin
\date	01/12/2011
</member>
<member name="M:SDevicePluginInterface.logError(QString,QString)" decl="true" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="346">
\fn	void logError(QString log, QString name);

\brief	(Signal) send a signal when the is an error non fatal

\author	Sylvain Martin
\date	20/04/2012
</member>
<member name="M:SDevicePluginInterface.logEvent(QString,QString)" decl="true" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdkdevice\sdeviceplugininterface.h" line="356">
\fn	bool SDeviceK2400::available()

\brief	(Signal) send a signal when some thing important append

\author	Sylvain Martin
\date	20/04/2012
</member>
<member name="T:SScriptEngine" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.h" line="43">
\class	SScriptEngine

\brief	this is a derivate class from QScriptEngine which initialize the the script engine for SpinToolBox

\author	Sylvain Martin
\date	1/28/2011
		
\ingroup SScriptMod	
		 
</member>
<member name="M:SUiScriptEditor.#ctor(SScriptEngine*,QString,QWidget*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="37">
\fn	SUiScriptEditor::SUiScriptEditor(SScriptEngine* qsEngine , QString file, QWidget * parent)

\brief	Constructor.

\author	Sylvain Martin
\date	16/11/2012

\param [in,out]	qsEngine	The QScript engine.
\param	file				The file that the main window "want" to load or an empty string.
\param [in,out]	parent  	If non-null, the parent.
</member>
<member name="M:SUiScriptEditor.newFile" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="99">
\fn	void SUiScriptEditor::newFile()

\brief	Creates a new file.

\author	Sylvain Martin
\date	16/11/2012
</member>
<member name="M:SUiScriptEditor.open" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="115">
\fn	void SUiScriptEditor::open()

\brief	Opens a file.

\author	Sylvain Martin
\date	16/11/2012
</member>
<member name="M:SUiScriptEditor.save" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="135">
\fn	bool SUiScriptEditor::save()

\brief	Saves the current file.

\author	Sylvain Martin
\date	16/11/2012

\return	true if it succeeds, false if it fails.
</member>
<member name="M:SUiScriptEditor.saveAs" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="154">
\fn	bool SUiScriptEditor::saveAs()

\brief	Saves the file with a new name/location.

\author	Sylvain Martin
\date	16/11/2012

\return	true if it succeeds, false if it fails.
</member>
<member name="M:SUiScriptEditor.documentWasModified" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="180">
\fn	void SUiScriptEditor::documentWasModified()

\brief	put a stat (*) next to the name of the document if this on was modified since the last save.

\author	Sylvain Martin
\date	16/11/2012
</member>
<member name="M:SUiScriptEditor.createActions" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="192">
\fn void SUiScriptEditor::createActions()

\brief Create the action.

</member>
<member name="M:SUiScriptEditor.createMenus" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="219">
\TODO find a way to kill the script
\fn	void SUiScriptEditor::createMenus()

\brief	setup the menu bar

</member>
<member name="M:SUiScriptEditor.createToolBars" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="369">
\fn	void SUiScriptEditor::createToolBars()

\brief	setup the tools bar

</member>
<member name="M:SUiScriptEditor.readSettings" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="406">
\fn	void SUiScriptEditor::readSettings()

\brief	Reads the settings.

\author	Sylvain Martin
\date	16/11/2012
</member>
<member name="M:SUiScriptEditor.writeSettings" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="431">
\fn	void SUiScriptEditor::writeSettings()

\brief	Writes the settings.

\author	Sylvain Martin
\date	16/11/2012
</member>
<member name="M:SUiScriptEditor.maybeSave" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="455">
\fn	void SUiScriptEditor::maybeSave()

\brief	ask if the user want save the current file

</member>
<!-- Le commentaire de document XML incorrect pour le membre 'M:SUiScriptEditor.loadFile(QString!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)' est ignoré. -->
<!-- Le commentaire de document XML incorrect pour le membre 'M:SUiScriptEditor.saveFile(QString!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)' est ignoré. -->
<member name="M:SUiScriptEditor.setCurrentFile(QString!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="529">
\fn	void SUiScriptEditor::createScintilla()

\brief	set up of the highlight and other stuffs on the text editor

</member>
<!-- Le commentaire de document XML incorrect pour le membre 'M:SUiScriptEditor.strippedName(QString!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)' est ignoré. -->
<member name="M:SUiScriptEditor.execute" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="559">
\fn	void SUiScriptEditor::execute()

\brief	slot that emits a signal for run the script

normally the run signal is connected to run slot of the script engine
</member>
<member name="M:SUiScriptEditor.alreadyRun" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="572">
\fn	void SUiScriptEditor::alreadyRun()

\brief	(SLOT) slot that puts a message in the statue bar because only on script can be execute  at once

</member>
<member name="M:SUiScriptEditor.swichToDebugMode" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="582">
\fn	void SUiScriptEditor::swichToDebugMod()

\brief	(SLOT) switch the text editor with the text display of the debugger

</member>
<member name="M:SUiScriptEditor.swichToEditMode" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="592">
\fn	void SUiScriptEditor::swichToEditMode()

\brief	(SLOT) switch text display of the debugger with the Scintilla text editor

</member>
<member name="M:SUiScriptEditor.createScintilla" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="603">
\fn	void SUiScriptEditor::createScintilla()

\brief	set up of the highlight and other stuffs on the text editor

</member>
<member name="M:SUiScriptEditor.switchLexerNormal" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="648">
\fn	void SUiScriptEditor::switchLexerNormal()

\brief	switch the Lexer of Scintilla to the Normal mode

</member>
<member name="M:SUiScriptEditor.switchLexerDebugComp" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="658">
\fn	void SUiScriptEditor::switchLexerDebugComp()

\brief	switch the Lexer of Scintilla to the Debug compatibility mode

</member>
<member name="M:SUiScriptEditor.setupUI" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="706">
\fn	void SUiScriptEditor::setupUI()

\brief	set up the UI (Scintilla, debug console, ...)

</member>
<member name="M:SUiScriptEditor.onFocus(QWidget*,QWidget*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="781">
\fn	void SUiScriptEditor::setupUI()

\brief	set up the UI (Scintilla, debug console, ...)

</member>
<member name="M:SUiScriptEditor.throwKill" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="808">
\fn	void SUiScriptEditor::throwKill()

\brief	(SLOT) when the user clicks on the kill action, ask if he really want it, and if yes, do it

</member>
<member name="M:SUiScriptEditor.endKilling" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="844">
\fn	void SUiScriptEditor::endKilling()

\brief	the throwKill function ask to the engine to interrupt, this function stop the engine
		 after the interruption

\author	Sylvain Martin
\date	16/11/2012
</member>
<member name="M:SUiScriptEditor.tabDbgCurrentChanged(System.Int32)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="874">
\fn	void SUiScriptEditor::tabDbgCurrentChanged( int index )

\brief	(SLOT) when the user change of tab, it is useful went we reconstruct the tab when the focus changes

</member>
<member name="M:SUiScriptEditor.executeSelectedText" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suiscripteditor.cpp" line="889">
\fn	void SUiScriptEditor::executeSelectedText()

\brief	(SLOT) Execute the selected text.

</member>
</members>
</doc>