/****************************************************************************
** Meta object code from reading C++ file 'SUiMetaDataReader.h'
**
** Created: Thu 22. Nov 18:47:24 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUi/SUiMetaDataReader.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SUiMetaDataReader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SUiMetaDataReader[] = {

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
      21,   19,   18,   18, 0x0a,
      46,   18,   18,   18, 0x0a,
      70,   18,   18,   18, 0x0a,
     122,   93,   18,   18, 0x0a,
     191,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SUiMetaDataReader[] = {
    "SUiMetaDataReader\0\0e\0closeEvent(QCloseEvent*)\0"
    "on_cmdRefresh_clicked()\0UpdateGlobalMetaData()\0"
    "gmdm,allMetaDataOfObj,parent\0"
    "updateOneObject(SGlobalMetaDataMap&,QList<SMetaData>,QStandardItem*)\0"
    "loadGlobalMetaData()\0"
};

const QMetaObject SUiMetaDataReader::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SUiMetaDataReader,
      qt_meta_data_SUiMetaDataReader, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SUiMetaDataReader::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SUiMetaDataReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SUiMetaDataReader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SUiMetaDataReader))
        return static_cast<void*>(const_cast< SUiMetaDataReader*>(this));
    if (!strcmp(_clname, "Ui_SUiMetaDataReader"))
        return static_cast< Ui_SUiMetaDataReader*>(const_cast< SUiMetaDataReader*>(this));
    return QWidget::qt_metacast(_clname);
}

int SUiMetaDataReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: on_cmdRefresh_clicked(); break;
        case 2: UpdateGlobalMetaData(); break;
        case 3: updateOneObject((*reinterpret_cast< SGlobalMetaDataMap(*)>(_a[1])),(*reinterpret_cast< QList<SMetaData>(*)>(_a[2])),(*reinterpret_cast< QStandardItem*(*)>(_a[3]))); break;
        case 4: loadGlobalMetaData(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
