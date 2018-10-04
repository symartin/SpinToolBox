/****************************************************************************
** Meta object code from reading C++ file 'SDeviceSR830.h'
**
** Created: Thu 4. Apr 10:24:21 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDeviceSR830.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDeviceSR830.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDeviceSR830Plugin[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_SDeviceSR830Plugin[] = {
    "SDeviceSR830Plugin\0"
};

const QMetaObject SDeviceSR830Plugin::staticMetaObject = {
    { &SDevicePluginInterface::staticMetaObject, qt_meta_stringdata_SDeviceSR830Plugin,
      qt_meta_data_SDeviceSR830Plugin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceSR830Plugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceSR830Plugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceSR830Plugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceSR830Plugin))
        return static_cast<void*>(const_cast< SDeviceSR830Plugin*>(this));
    if (!strcmp(_clname, "SpinToolBox.SDevicePluginInterface"))
        return static_cast< SDevicePluginInterface*>(const_cast< SDeviceSR830Plugin*>(this));
    return SDevicePluginInterface::qt_metacast(_clname);
}

int SDeviceSR830Plugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SDevicePluginInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SDeviceSR830[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   14,   13,   13, 0x05,
      49,   14,   13,   13, 0x05,

 // methods: signature, parameters, type, tag, flags
      80,   75,   13,   13, 0x02,
     107,  101,   13,   13, 0x02,
     134,  124,   13,   13, 0x02,
     155,   13,   13,   13, 0x02,
     162,   13,   13,   13, 0x02,
     169,   13,   13,   13, 0x02,
     176,   13,   13,   13, 0x02,
     187,   13,   13,   13, 0x02,
     206,   13,  199,   13, 0x02,
     210,   13,  199,   13, 0x02,
     214,   13,  199,   13, 0x02,
     218,   13,  199,   13, 0x02,
     226,   13,   13,   13, 0x02,
     241,   13,  233,   13, 0x02,
     260,   13,  255,   13, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SDeviceSR830[] = {
    "SDeviceSR830\0\0log,name\0logError(QString,QString)\0"
    "logEvent(QString,QString)\0freq\0"
    "setFrequency(double)\0phase\0setPhase(double)\0"
    "amplitude\0setAmplitude(double)\0setX()\0"
    "setY()\0setR()\0setTheta()\0AutoPhase()\0"
    "double\0X()\0Y()\0R()\0Theta()\0init()\0"
    "QString\0description()\0bool\0available()\0"
};

const QMetaObject SDeviceSR830::staticMetaObject = {
    { &SDeviceGpib::staticMetaObject, qt_meta_stringdata_SDeviceSR830,
      qt_meta_data_SDeviceSR830, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceSR830::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceSR830::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceSR830::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceSR830))
        return static_cast<void*>(const_cast< SDeviceSR830*>(this));
    return SDeviceGpib::qt_metacast(_clname);
}

int SDeviceSR830::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SDeviceGpib::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: logError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: logEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: setFrequency((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: setPhase((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: setAmplitude((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: setX(); break;
        case 6: setY(); break;
        case 7: setR(); break;
        case 8: setTheta(); break;
        case 9: AutoPhase(); break;
        case 10: { double _r = X();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 11: { double _r = Y();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 12: { double _r = R();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 13: { double _r = Theta();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 14: init(); break;
        case 15: { QString _r = description();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { bool _r = available();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void SDeviceSR830::logError(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDeviceSR830::logEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
