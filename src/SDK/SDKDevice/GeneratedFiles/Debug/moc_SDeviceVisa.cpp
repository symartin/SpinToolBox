/****************************************************************************
** Meta object code from reading C++ file 'SDeviceVisa.h'
**
** Created: Thu 8. Nov 11:40:07 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDevice/SDeviceVisa.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDeviceVisa.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDeviceVisa[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   13,   12,   12, 0x05,
      48,   13,   12,   12, 0x05,

 // methods: signature, parameters, type, tag, flags
      83,   79,   74,   12, 0x02,
     114,  109,   97,   12, 0x02,
     134,  109,   97,   12, 0x02,
     167,  163,  155,   12, 0x02,
     184,  163,   74,   12, 0x02,
     209,  202,  155,   12, 0x02,
     224,   12,  155,   12, 0x22,
     235,   12,  155,   12, 0x02,
     248,  242,   12,   12, 0x02,
     267,   12,   12,   12, 0x22,
     282,   12,   74,   12, 0x02,
     296,  294,   12,   12, 0x02,
     315,  310,   12,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SDeviceVisa[] = {
    "SDeviceVisa\0\0log,name\0logError(QString,QString)\0"
    "logEvent(QString,QString)\0bool\0add\0"
    "init(QString)\0QStringList\0name\0"
    "findAdress(QString)\0findElement(QString)\0"
    "QString\0cmd\0address(QString)\0"
    "visaSend(QString)\0buffer\0visaRead(long)\0"
    "visaRead()\0name()\0OnOff\0setAvailable(bool)\0"
    "setAvailable()\0available()\0i\0delay(double)\0"
    "time\0setTimeOut(double)\0"
};

const QMetaObject SDeviceVisa::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SDeviceVisa,
      qt_meta_data_SDeviceVisa, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceVisa::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceVisa::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceVisa::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceVisa))
        return static_cast<void*>(const_cast< SDeviceVisa*>(this));
    return QObject::qt_metacast(_clname);
}

int SDeviceVisa::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: logError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: logEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: { bool _r = init((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { QStringList _r = findAdress((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 4: { QStringList _r = findElement((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 5: { QString _r = address((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { bool _r = visaSend((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { QString _r = visaRead((*reinterpret_cast< const long(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { QString _r = visaRead();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { QString _r = name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: setAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: setAvailable(); break;
        case 12: { bool _r = available();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: delay((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: setTimeOut((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void SDeviceVisa::logError(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDeviceVisa::logEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
