#ifndef SDEVICEPLUGININTERFACE_H_
#define SDEVICEPLUGININTERFACE_H_

#define QGLOBALMETADATA_SHAREDMEMORY_SIZE 1024*150 // 300Ko de meta data, c'est large ...

#include <QtCore>
#include <QScriptable>
#include <QScriptEngine>
#include <QSettings>
#include <QWidget>
#include <QSharedMemory>

#include <string.h>

#define SMETADATA_OBJ_NAME_LENGTH 15
#define SMETADATA_NAME_LENGTH 15
#define SMETADATA_SHORTCUT_LENGTH 15
#define SMETADATA_VALUE_LENGTH 15


class SGlobalMetaDataMap;

class SMetaData {

	friend class SGlobalMetaDataMap;
	friend QDataStream &operator<<(QDataStream &out, const SMetaData &myObj);
	friend QDataStream &operator>>(QDataStream &in, SMetaData &myObj);

public:
	enum enumType { boolean = 'b', string = 's', integer = 'i', doublefloat = 'd', other='o'};

	SMetaData(const QString objn, const QString metaDataName, 
				const QVariant val, const QString unit ="", const QString type ="s");

	SMetaData(const QString objn, const QString metaDataName, 
				const QVariant val, const QString unit ="", const enumType type = string);

	SMetaData();
	SMetaData(const SMetaData& p);   // copy constructor
	SMetaData & operator= (const SMetaData & other); //Overloading copy assignment operator

	~SMetaData(); 

	void setObjectName(const QString objname);
	QString objectName() const;

	void setName(const QString objname);
	QString name() const;

	QVariant value() const;
	void setValue(const QVariant val);

	QString unit() const;
	void setUnit(const QString u);

	enumType type() const;
	void setType(const enumType tp);
	void setType(const char tp);
	void setType(const QString tp);



private:
	QString objname_;
	QVariant value_;
	QString name_;
	QString unit_;
	char type_;

};

QDataStream &operator<<(QDataStream &out, const SMetaData &myObj);
QDataStream &operator>>(QDataStream &in, SMetaData &myObj);


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SGlobalMetaDataMap
///
/// \brief	class for passing the metadata between all the device plugins. it is derived of QList
///
/// \author	Sylvain Martin
/// \date	02/03/2012
///
/// \ingroup SDeviceMod
///
/// See also the Qt documentation on the QList.
////////////////////////////////////////////////////////////////////////////////////////////////////
class SGlobalMetaDataMap {
public:

	SGlobalMetaDataMap();
	~SGlobalMetaDataMap();	

	void setMetaData(QString objName, QString metaDataName, QVariant metaData, QString unit = "",
						SMetaData::enumType type = SMetaData::string);

	SMetaData MetaData(QString objName, QString metaDataName );

	bool MetaDataExist(QString objName, QString metaDataName );

	QList<SMetaData> allMetaDataOf(QString objName);
	QStringList allObjects();

	int count();

	void firstInit();
	//static void initialize();

	void clear(const QString objName);

	void stopReload(bool OnOff);

private:
	int find(QString objName, QString metaDataName,  bool load = false);
	void loadSharedMemory();
	void saveSharedMemory();
	QList<SMetaData> metadata;
	//SMetaData metadata[SMETADATA_MAX];
	QSharedMemory sharedMemory;

	bool stopReload_;


};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class
///
/// \brief	Virtual class for all the devices Plugin. It is virtual pure so it cannot be instanced.
///
/// \author	Sylvain Martin
/// \date	1/12/2011
///
/// \ingroup SDeviceMod
////////////////////////////////////////////////////////////////////////////////////////////////////
class SDevicePluginInterface: public QObject{
	Q_OBJECT;

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool load()
	///
	/// \brief	initialize the plugin
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	/// \param GlobalMetaDataMap pointer on the global object containing all the metadata
	///
	/// \return true if all is ok, false otherwise
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool load () = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	QString name() const
	///
	/// \brief	return the complete name of the plugin
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	/// \return return the name of the plugin
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual QString name () const = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	QString shortName() const
	///
	/// \brief	return the short name of the plugin.
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	/// \return return the short name of the plugin
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual QString shortName () const = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	QString description() const
	///
	/// \brief	return the description of the plugin
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	/// \return return the description of the plugin
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual QString description()const = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	QString plgVersion() const
	///
	/// \brief	return the version of the SDK that is needed for run the plugin
	///
	/// \author	Sylvain Martin
	/// \date	13/01/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual QString plgVersion() const =0 ;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	QString SDKVersion() const 
	///
	/// \brief	return the version of the SDK which is required for this plugin
	///
	/// \author	Sylvain Martin
	/// \date	13/01/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual QString SDKVersion()  const =0 ;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool isScriptable()
	///
	/// \brief	does the plugin add some function to the script engine
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	/// \return true, yes it does, false, no it does no
	///
	/// \sa isScriptable
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool isScriptable() = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool scriptable( QScriptEngine * engine )
	///
	/// \brief	add (or not) some functions to the script engine
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	/// \param engine the script engine
	/// \sa isScriptable
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool scriptable(QScriptEngine * engine)=0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual bool isSetting();
	///
	/// \brief	(virtual pure) does the plugin have a setting window ?
	///
	/// \author	Sylvain Martin
	/// \date	25/02/2012
	///
	/// \return true, yes it does, false, no it does no
	///
	/// \sa setting
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool isSetting() =0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual QWidget * setting(QSettings set)=0;
	///
	/// \brief	(virtual pure) give (or not) a setting window.
	///
	/// \author	Sylvain Martin
	/// \date	25/01/2012
	///
	/// \param set the QSettings object of the application
	/// \sa isSetting
	///
	/// \remark it do not manage the destruction of the object, so you ave to define a parent
	///			or destroy it your self
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual QWidget * setting(QWidget * parrent = NULL)=0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool isControlPanel()
	///
	/// \brief	does the plugin add a tab to the control panel to the script engine
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	/// \return true, yes it does, false, no it does no
	///
	/// \sa ControlPanel()
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool isControlPanel() = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	QString controlPanel() const
	///
	/// \brief	add (or not) a tab to the control panel 
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	/// \param engine the script engine
	/// \sa isControlPanel
	///
	/// \remark SDeviceK2400Plugin do not manage the destruction of the object, so you ave to define a parent
	///			or destroy it your self 
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual QWidget * controlPanel(QWidget * parrent = NULL)=0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void shutdown()
	///
	/// \brief	shutdown the plugin (by example before closing the application)
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void shutdown() = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool unload()
	///
	/// \brief	this function is call when the plugin is unload
	///
	/// \author	Sylvain Martin
	/// \date	13/01/2011
	///
	/// \return true if all is ok, false otherwise
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool unload()=0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	int SDeviceK2400::state()
	///
	/// \brief	what is the state of the plugin
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	///
	/// 0 : ready, 1 : busy, 2 unavailable
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual int state()=0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool SDeviceK2400::available()
	///
	/// \brief	is the plugin available ?
	///
	/// \author	Sylvain Martin
	/// \date	01/12/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool available()=0;


signals:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void logError(QString log, QString name);
	///
	/// \brief	(Signal) send a signal when the is an error non fatal
	///
	/// \author	Sylvain Martin
	/// \date	20/04/2012
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void logError(QString log, QString name);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool SDeviceK2400::available()
	///
	/// \brief	(Signal) send a signal when some thing important append
	///
	/// \author	Sylvain Martin
	/// \date	20/04/2012
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void logEvent(QString log, QString name);
};



Q_DECLARE_INTERFACE(SDevicePluginInterface, "SpinToolBox.SDevicePluginInterface")

#endif /* SDEVICEVIRTUAL_H_ */