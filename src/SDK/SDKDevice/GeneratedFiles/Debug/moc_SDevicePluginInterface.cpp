/****************************************************************************
** Meta object code from reading C++ file 'SDevicePluginInterface.h'
**
** Created: Thu 8. Nov 11:40:07 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDevicePluginInterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDevicePluginInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDevicePluginInterface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   24,   23,   23, 0x05,
      59,   24,   23,   23, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SDevicePluginInterface[] = {
    "SDevicePluginInterface\0\0log,name\0"
    "logError(QString,QString)\0"
    "logEvent(QString,QString)\0"
};

const QMetaObject SDevicePluginInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SDevicePluginInterface,
      qt_meta_data_SDevicePluginInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDevicePluginInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDevicePluginInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDevicePluginInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDevicePluginInterface))
        return static_cast<void*>(const_cast< SDevicePluginInterface*>(this));
    return QObject::qt_metacast(_clname);
}

int SDevicePluginInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: logError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: logEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SDevicePluginInterface::logError(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDevicePluginInterface::logEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
