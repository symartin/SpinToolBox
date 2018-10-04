/****************************************************************************
** Meta object code from reading C++ file 'SUiPluginManager.h'
**
** Created: Thu 22. Nov 18:47:25 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUi/SUiPluginManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SUiPluginManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SUiPluginManager[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      54,   37,   17,   17, 0x0a,
     132,  124,   17,   17, 0x0a,
     163,  124,   17,   17, 0x0a,
     192,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SUiPluginManager[] = {
    "SUiPluginManager\0\0on_cmdOK_clicked()\0"
    "current,previous\0"
    "on_lstchkPlugin_currentItemChanged(QListWidgetItem*,QListWidgetItem*)\0"
    "checked\0on_chkScriptable_clicked(bool)\0"
    "on_chkCtlPanel_clicked(bool)\0"
    "on_cmdOpt_clicked()\0"
};

const QMetaObject SUiPluginManager::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SUiPluginManager,
      qt_meta_data_SUiPluginManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SUiPluginManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SUiPluginManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SUiPluginManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SUiPluginManager))
        return static_cast<void*>(const_cast< SUiPluginManager*>(this));
    if (!strcmp(_clname, "Ui::SUiPluginManager"))
        return static_cast< Ui::SUiPluginManager*>(const_cast< SUiPluginManager*>(this));
    return QDialog::qt_metacast(_clname);
}

int SUiPluginManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_cmdOK_clicked(); break;
        case 1: on_lstchkPlugin_currentItemChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 2: on_chkScriptable_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_chkCtlPanel_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: on_cmdOpt_clicked(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
