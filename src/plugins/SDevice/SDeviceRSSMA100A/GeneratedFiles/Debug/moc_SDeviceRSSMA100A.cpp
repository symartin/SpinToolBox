/****************************************************************************
** Meta object code from reading C++ file 'SDeviceRSSMA100A.h'
**
** Created: Mon 4. Feb 16:23:25 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDeviceRSSMA100A.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDeviceRSSMA100A.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDeviceRSSMA100APlugin[] = {

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

static const char qt_meta_stringdata_SDeviceRSSMA100APlugin[] = {
    "SDeviceRSSMA100APlugin\0\0log,name\0"
    "logError(QString,QString)\0"
    "logEvent(QString,QString)\0"
};

const QMetaObject SDeviceRSSMA100APlugin::staticMetaObject = {
    { &SDevicePluginInterface::staticMetaObject, qt_meta_stringdata_SDeviceRSSMA100APlugin,
      qt_meta_data_SDeviceRSSMA100APlugin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceRSSMA100APlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceRSSMA100APlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceRSSMA100APlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceRSSMA100APlugin))
        return static_cast<void*>(const_cast< SDeviceRSSMA100APlugin*>(this));
    if (!strcmp(_clname, "SpinToolBox.SDevicePluginInterface"))
        return static_cast< SDevicePluginInterface*>(const_cast< SDeviceRSSMA100APlugin*>(this));
    return SDevicePluginInterface::qt_metacast(_clname);
}

int SDeviceRSSMA100APlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SDevicePluginInterface::qt_metacall(_c, _id, _a);
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
void SDeviceRSSMA100APlugin::logError(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDeviceRSSMA100APlugin::logEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_SDeviceRSSMA100A[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x02,
      44,   17,   17,   17, 0x02,
      65,   17,   17,   17, 0x02,
      82,   17,   17,   17, 0x02,
     104,   17,   17,   17, 0x02,
     127,   17,  119,   17, 0x02,
     146,   17,  141,   17, 0x02,
     165,   17,  158,   17, 0x02,
     177,   17,  158,   17, 0x02,
     185,   17,  158,   17, 0x02,
     198,   17,  141,   17, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SDeviceRSSMA100A[] = {
    "SDeviceRSSMA100A\0\0onOff\0metaDataOnOff(bool)\0"
    "setFrequency(double)\0setPower(double)\0"
    "setPowerLimit(double)\0activate(bool)\0"
    "QString\0description()\0bool\0available()\0"
    "double\0frequency()\0power()\0powerLimit()\0"
    "isActivated()\0"
};

const QMetaObject SDeviceRSSMA100A::staticMetaObject = {
    { &SDeviceGpib::staticMetaObject, qt_meta_stringdata_SDeviceRSSMA100A,
      qt_meta_data_SDeviceRSSMA100A, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceRSSMA100A::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceRSSMA100A::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceRSSMA100A::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceRSSMA100A))
        return static_cast<void*>(const_cast< SDeviceRSSMA100A*>(this));
    return SDeviceGpib::qt_metacast(_clname);
}

int SDeviceRSSMA100A::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SDeviceGpib::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: metaDataOnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setFrequency((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 2: setPower((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 3: setPowerLimit((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 4: activate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: { QString _r = description();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { bool _r = available();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { double _r = frequency();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 8: { double _r = power();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 9: { double _r = powerLimit();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 10: { bool _r = isActivated();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE