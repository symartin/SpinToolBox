/****************************************************************************
** Meta object code from reading C++ file 'SDeviceVirtual.h'
**
** Created: Thu 8. Nov 11:40:07 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDevice/SDeviceVirtual.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDeviceVirtual.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDeviceVirtual[] = {

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

 // methods: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x02,
      31,   15,   23,   15, 0x02,
      38,   15,   23,   15, 0x02,
      57,   15,   52,   15, 0x02,
      69,   15,   15,   15, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SDeviceVirtual[] = {
    "SDeviceVirtual\0\0init()\0QString\0name()\0"
    "description()\0bool\0available()\0"
    "setUnavailable()\0"
};

const QMetaObject SDeviceVirtual::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SDeviceVirtual,
      qt_meta_data_SDeviceVirtual, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceVirtual::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceVirtual::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceVirtual::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceVirtual))
        return static_cast<void*>(const_cast< SDeviceVirtual*>(this));
    if (!strcmp(_clname, "QScriptable"))
        return static_cast< QScriptable*>(const_cast< SDeviceVirtual*>(this));
    return QObject::qt_metacast(_clname);
}

int SDeviceVirtual::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: init(); break;
        case 1: { QString _r = name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = description();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { bool _r = available();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: setUnavailable(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
