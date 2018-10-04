<?xml version="1.0"?><doc>
<members>
<member name="D:size_t" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suictrlpan.h" line="2">
\file		SUi\SUiCtrlPan.h
		
\author		Sylvain Martin
\version	1.0
\date		20/01/2012

\brief	Declares the SUiCmdMan and the SUiLblLed classes
		
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
<member name="T:Ui_SUiMetaDataReader" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suimetadatareader.h" line="2">
\file		SUiMetaDataReader.h
		
\author		Sylvain Martin
\version	1.0
\date		07/03/2012

\brief	Declare the class of the Meta Data Reader Window
		
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
<!-- Le commentaire de document XML incorrect pour le membre 'M:SUiCtrlPan.#ctor(QList<SDevicePluginInterface**>,SGlobalMetaDataMap*,QWidget*)' est ignoré. -->
<member name="M:SUiCtrlPan.Dispose" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suictrlpan.cpp" line="58">
\fn	SUiCtrlPan::~SUiCtrlPan(void)

\brief	Destructor.

\author	Sylvain Martin
\date	17/10/2012
</member>
<member name="M:SUiCtrlPan.globalMetaDataWindowShow" decl="false" source="d:\sylvain\instru\spintoolbox v2.6\src\spintoolbox\sui\suictrlpan.cpp" line="70">
\fn	void SUiCtrlPan::globalMetaDataWindowShow()

\brief	(SLOT) open the visualization window of the global metadata tree.

\author	Sylvain Martin
\date	17/10/2012
</member>
</members>
</doc>