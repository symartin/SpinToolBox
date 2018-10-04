/****************************************************************************
** Meta object code from reading C++ file 'SDeviceGpib.h'
**
** Created: Thu 8. Nov 11:40:07 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDevice/SDeviceGpib.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDeviceGpib.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDeviceGpib[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   13,   12,   12, 0x05,
      35,   13,   12,   12, 0x05,

 // methods: signature, parameters, type, tag, flags
      64,   12,   53,   12, 0x02,
      74,   70,   12,   12, 0x02,
     102,   93,   12,   12, 0x02,
     136,  129,  120,   12, 0x02,
     151,   12,  120,   12, 0x22,
     162,   12,   12,   12, 0x02,
     184,   12,  176,   12, 0x02,
     191,   12,   12,   12, 0x02,
     210,  208,   12,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SDeviceGpib[] = {
    "SDeviceGpib\0\0log\0logError(QString)\0"
    "logEvent(QString)\0Addr4882_t\0PAD()\0"
    "pad\0setPAD(Addr4882_t)\0commande\0"
    "gpibSend(QString)\0QVariant\0buffer\0"
    "gpibRead(long)\0gpibRead()\0enableLocal()\0"
    "QString\0name()\0setUnavailable()\0i\0"
    "delay(double)\0"
};

const QMetaObject SDeviceGpib::staticMetaObject = {
    { &SDeviceVirtual::staticMetaObject, qt_meta_stringdata_SDeviceGpib,
      qt_meta_data_SDeviceGpib, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceGpib::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceGpib::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceGpib::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceGpib))
        return static_cast<void*>(const_cast< SDeviceGpib*>(this));
    return SDeviceVirtual::qt_metacast(_clname);
}

int SDeviceGpib::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SDeviceVirtual::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: logError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: logEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { Addr4882_t _r = PAD();
            if (_a[0]) *reinterpret_cast< Addr4882_t*>(_a[0]) = _r; }  break;
        case 3: setPAD((*reinterpret_cast< const Addr4882_t(*)>(_a[1]))); break;
        case 4: gpibSend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { QVariant _r = gpibRead((*reinterpret_cast< const long(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: { QVariant _r = gpibRead();
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 7: enableLocal(); break;
        case 8: { QString _r = name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: setUnavailable(); break;
        case 10: delay((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SDeviceGpib::logError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDeviceGpib::logEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
