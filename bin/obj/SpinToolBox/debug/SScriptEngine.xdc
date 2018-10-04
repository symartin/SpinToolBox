<?xml version="1.0"?><doc>
<members>
<member name="D:size_t" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\serror.h" line="2">
\file		SError.h
		
\author		Sylvain Martin
\version	1.0
\date		1/20/2011

\brief	Declares the error class.
		
\section LICENSE

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details at
http://www.gnu.org/copyleft/gpl.html
</member>
<member name="D:QtCoreModule" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\sdevice\sdevicevirtual.h" line="2">
\file		SDevice\SDeviceVirtual.h
		
\author		Sylvain Martin
\version	1.0
\date		20/01/2011

\brief	declare a virtual class for all the devices
		
\section LICENSE

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details at
http://www.gnu.org/copyleft/gpl.html
</member>
<member name="T:SDeviceVirtual" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\sdevice\sdevicevirtual.h" line="33">
\class	SDeviceVirtual

\brief	Virtual class for all the devices. It is virtual pur so it cannot be instancied.

\author	Sylvain Martin
\date	1/20/2011
		
\ingroup SDeviceMod
</member>
<member name="T:SError" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\serror.h" line="31">
\class	SError

\brief	class of object throw when an exception has been came. 

\author	Sylvain Martin
\date	1/20/2011
</member>
<member name="T:SData2D" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\sdata\sdata2d.h" line="31">
\class	SData2D

\brief	Class for the manipulation of the data in 2 dimensions (y and y).

\author	Sylvain Martin
\date	1/26/2011

\ingroup SDataMod
</member>
<member name="T:SData2DScript" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\sdata\sdata2dscript.h" line="14">
\class	SData2DScript

\brief	this class provides a Qt Script warper for the \SData2D class 

\author	Sylvain Martin
\date	1/28/2011
		
\ingroup SDataMod	
		 
this class takes up the useful functions of the class SData2D in order to use it in the Qt script.

\sa SData2D	 
</member>
<!-- Le commentaire de document XML incorrect pour le membre 'F:lsNone' est ignoré. -->
<member name="T:QCPAxis.AxisType" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\qcustomplot.h" line="770">
\cond INCLUDE_QPROPERTIES
\endcond
</member>
<member name="T:QCustomPlot.AntialiasedElement" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\qcustomplot.h" line="1054">
\cond INCLUDE_QPROPERTIES
\endcond
</member>
<member name="T:SPlot2D" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="37">
\class	SPlot2D

\brief	define a Main windows that contained a 2D Plot with all the basic tool (zoom, ...).

\author	Sylvain Martin
\date	2/4/2011

\remark order to use Qwt as a dll and inherit a QWT object we must define the macro in the
		preprocessor QWT_DLL. in , the project need a preprocessor define
		[configuration properties]-&gt;[c/c++]-&gt;[preprocessor]-&gt;[preprocessor definitions]-&gt; QWT_DLL
		(and leave the rest as it is)

\sa SPlot2DWidget

contained a sub-class of QwtPlot that has some new functions, like a \c zoom, an \c autoscale
and a way to chose a scale (\c doSelectScaleWin).
</member>
<member name="M:SPlot2D.antialiasing" decl="true" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="74">
@name propertiesFunction
general properties 

</member>
<member name="M:SPlot2D.SaveImagePng(QString!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Double,System.Int32,System.Int32)" decl="true" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="84">
@name variousFunction
Various functions 

</member>
<member name="M:SPlot2D.setData(SData2D*,System.Int32!System.Runtime.CompilerServices.IsConst)" decl="true" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="95">
@name DataFunctions
Functions concerning the data

</member>
<member name="M:SPlot2D.setName(QString!System.Runtime.CompilerServices.IsConst,System.Int32!System.Runtime.CompilerServices.IsConst)" decl="true" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="121">
@name GraphsFunctions
Functions concerning the graphs

</member>
<member name="T:SPlotSetScale" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="214">
\class	SPlotSetScale

\brief	(PRIVATE) small QDialog to let the user set a scale.

\author	Sylvain Martin
\date	2/4/2011

it is a private class, do not use it directly !
</member>
<member name="M:SPlotSetScale.#ctor(QWidget*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="231">
\fn	void SPlotSetScale::SPlotSetScale(void)

\brief	put the initials value for the maximum of the minimum of the 2 scales (x and y)

\param [in,out]	parent	If non-null, the Qt parent.
</member>
<member name="M:SPlotSetScale.initialValue(System.Double,System.Double,System.Double,System.Double)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="245">
\fn	void SPlotSetScale::initialValue

\brief	puts the initials value for the maximum of the minimum of the 2 scales (x and y)

\param Xmin the maximum of the x scale
\param Xmax the minimum of the x scale
\param Ymin the maximum of the y scale
\param Ymax the minimum of the y scale
</member>
<member name="M:SPlotSetScale.scaleChange(System.Double,System.Double,System.Double,System.Double)" decl="true" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="263">
\fn	void SPlotSetScale::scaleChange

\brief	(SIGNAL) sends the scales selected by the user.

\param Xmin the maximum of the x scale
\param Xmax the minimum of the x scale
\param Ymin the maximum of the y scale
\param Ymax the minimum of the y scale

this signal is send when the OK button is clicked
</member>
<member name="M:SPlotSetScale.ScaleToAll" decl="true" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="277">
\fn	void ScaleToAll()

\brief (SIGNAL) Apply the scale at all the 2D plot open.

</member>
<member name="T:SPlotImageSize" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="303">
\class	SPlotImageSize

\brief	(PRIVATE) small QDialog to let select the size of the saved image

\author	Sylvain Martin
\date	2/4/2011

it is a private class, do not use it directly !
</member>
<member name="M:SPlotImageSize.#ctor(QWidget*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\sdk\sdk\splot\splot2d.h" line="320">
\fn	void SPlotSetScale::SPlotSetScale(void)

\brief	put the initials value for the maximum of the minimum of the 2 scales (x and y)

\param [in,out]	parent	If non-null, the Qt parent.
</member>
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
<member name="M:SScriptEngine.#ctor(QList&lt;SDevicePluginInterface**&gt;,SGlobalMetaDataMap*,QWidget*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="25">
\fn	void SInterfaceGpib::SScriptEngine()

\brief	constructor

</member>
<member name="M:SScriptEngine.initSData2D" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="84">
\fn	void SScriptEngine::initData2D()

\brief	add to the engine the possibility to instantiate a new \c SData2D

\so SData2D
</member>
<member name="M:SScriptEngine.initSPlot2D" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="107">
\fn	void SScriptEngine::initSPlot2D()

\brief	add to the engine the possibility to instantiate a new \c SPlot2D

\so SPlot2D
</member>
<member name="M:SScriptEngine.debugger" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="129">
\fn	void SScriptEngine::setDebugger(QScriptEngineDebugger * debugger)

\brief	get the debugger object, the SScriptEngine object instantiates one in the constructor

</member>
<member name="M:SScriptEngine.abort" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="141">
\fn	void SScriptEngine::abort()

\brief	(SLOT) Aborts any script evaluation currently taking place in this engine.

If the engine isn't evaluating a script (i.e. isEvaluating() returns false), 
this function does nothing.

\remark This function are the same that QScriptEngine::abortEvaluation() but it is a slot.
</member>
<!-- Le commentaire de document XML incorrect pour le membre 'M:SScriptEngine.run(QString!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,QString!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32,System.Boolean)' est ignoré. -->
<member name="M:SScriptEngine.intToolFunction" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="211">
\fn  void SScriptEngine::intToolFunction()

\brief	load the tool functions like delay(), debug(), ... in the script engin


</member>
<member name="M:qsDelay(QScriptContext*,QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="271">
\fn	QScriptValue qsDelay(QScriptContext * context, QScriptEngine * qsEng)

\brief	(SCRIPTABLE) (with delay())

</member>
<member name="M:qsDebug(QScriptContext*,QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="289">
\fn	 QScriptValue qsDebug(QScriptContext *context, QScriptEngine *engine)

\brief	(SCRIPTABLE) (with debug()) Write something to the debug console.

</member>
<member name="M:qsStop(QScriptContext*,QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="308">
\fn QScriptValue qsStop( QScriptContext *context, QScriptEngine *engine )

\brief	(SCRIPTABLE) (with stop()) stop the script.

\example stop();

\ingroup SScriptMod	
</member>
<member name="M:qsWarningMsgBox(QScriptContext*,QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="323">
\fn  QScriptValue qsWarningMsgBox( QScriptContext *context, QScriptEngine *engine )

\brief	(SCRIPTABLE) (with warningMsgBox()) show a warning message box with. 

\example warningMsgBox("be careful!", "My title");

\deprecated Use the Qt binding.

The first argument is text and the second the title.

\ingroup SScriptMod	
</member>
<member name="M:qsNowDate(QScriptContext*,QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="352">
\fn	    QScriptValue qsNowDate( QScriptContext *context, QScriptEngine *engine )

\brief	(SCRIPTABLE) (with nowDate()) return the date of today, see the documentation of qt for the argument

\example nowDate("yyyymmdd"); return 20110309

\deprecated Use the Qt binding.

\ingroup SScriptMod	
</member>
<member name="M:qsNowTime(QScriptContext*,QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="374">
\fn	    QScriptValue qsNowTime( QScriptContext *context, QScriptEngine *engine )

\brief	(SCRIPTABLE) (with nowTime()) return the time, see the documentation of qt for the argument

\example nowTime(""hh-mm-ss""); return 16-03-22

\deprecated Use the Qt binding.

\ingroup SScriptMod	
</member>
<member name="M:qsClear(QScriptContext*,QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="397">
\fn	   QScriptValue qsClear( QScriptContext *context, QScriptEngine *engine )

\brief	(SCRIPTABLE) (with clear()) clear the Debug Output text, the Console and the Error Log

\example clear(); 
\ingroup SScriptMod	

</member>
<member name="M:qsBip(QScriptContext*,QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="436">
\fn	   QScriptValue qsClear( QScriptContext *context, QScriptEngine *engine )

\brief	(SCRIPTABLE) (with bip()) does a bip-sound 

\example bip(); 

\TODO the default sound is played instead of the wav file, I do not know why...
\ingroup SScriptMod	
</member>
<member name="M:qsInclude(QScriptContext*,QScriptEngine*)" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sscript\sscriptengine.cpp" line="452">
\fn	   QScriptValue qsClear( QScriptContext *context, QScriptEngine *engine )

\brief	(SCRIPTABLE) (with include()) include a file to the current context

\example include("c:\\mylib.js"); 

\ingroup SScriptMod	
</member>
</members>
</doc>