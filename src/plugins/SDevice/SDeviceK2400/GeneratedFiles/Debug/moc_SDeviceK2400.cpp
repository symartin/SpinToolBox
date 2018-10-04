/****************************************************************************
** Meta object code from reading C++ file 'SDeviceK2400.h'
**
** Created: Tue 27. Aug 10:40:01 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDeviceK2400.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDeviceK2400.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDeviceK2400Plugin[] = {

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

static const char qt_meta_stringdata_SDeviceK2400Plugin[] = {
    "SDeviceK2400Plugin\0"
};

const QMetaObject SDeviceK2400Plugin::staticMetaObject = {
    { &SDevicePluginInterface::staticMetaObject, qt_meta_stringdata_SDeviceK2400Plugin,
      qt_meta_data_SDeviceK2400Plugin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceK2400Plugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceK2400Plugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceK2400Plugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceK2400Plugin))
        return static_cast<void*>(const_cast< SDeviceK2400Plugin*>(this));
    if (!strcmp(_clname, "SpinToolBox.SDevicePluginInterface"))
        return static_cast< SDevicePluginInterface*>(const_cast< SDeviceK2400Plugin*>(this));
    return SDevicePluginInterface::qt_metacast(_clname);
}

int SDeviceK2400Plugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SDevicePluginInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SDeviceK2400[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       1,  169, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   14,   13,   13, 0x05,
      49,   14,   13,   13, 0x05,

 // methods: signature, parameters, type, tag, flags
      81,   75,   13,   13, 0x02,
     114,   13,  101,   13, 0x02,
     125,   13,  101,   13, 0x02,
     136,   13,   13,   13, 0x02,
     158,   13,  151,   13, 0x02,
     176,  168,   13,   13, 0x02,
     195,   13,  151,   13, 0x02,
     213,  205,   13,   13, 0x02,
     237,  232,   13,   13, 0x02,
     262,   13,  254,   13, 0x02,
     271,   13,   13,   13, 0x02,
     282,   13,   13,   13, 0x02,
     300,   13,  295,   13, 0x02,
     319,  314,   13,   13, 0x02,
     348,  343,   13,   13, 0x02,
     375,  372,   13,   13, 0x02,
     400,   13,  151,   13, 0x02,
     415,   13,  151,   13, 0x02,
     430,   13,  295,   13, 0x02,
     449,   75,   13,   13, 0x02,
     475,   13,  295,   13, 0x02,
     494,   75,   13,   13, 0x02,
     526,  520,   13,   13, 0x02,
     561,  555,   13,   13, 0x02,
     590,   13,  151,   13, 0x02,
     610,   13,  151,   13, 0x02,
     630,   13,   13,   13, 0x02,
     637,   13,  254,   13, 0x02,
     651,   13,  295,   13, 0x02,

 // enums: name, flags, count, data
     663, 0x0,    2,  173,

 // enum data: key, value
     668, uint(SDeviceK2400::CURRENT),
     676, uint(SDeviceK2400::VOLTAGE),

       0        // eod
};

static const char qt_meta_stringdata_SDeviceK2400[] = {
    "SDeviceK2400\0\0log,name\0logError(QString,QString)\0"
    "logEvent(QString,QString)\0onOff\0"
    "metaDataOnOff(bool)\0QScriptValue\0"
    "qsReadVI()\0qsReadIV()\0putLocalMode()\0"
    "double\0current()\0current\0setCurrent(double)\0"
    "voltage()\0voltage\0setVoltage(double)\0"
    "mode\0setMode(QString)\0QString\0qsMode()\0"
    "activate()\0deactivate()\0bool\0isActivated()\0"
    "Vmax\0setVoltageRange(double)\0Imax\0"
    "setCurrentRange(double)\0Vm\0"
    "setVoltMeasRange(double)\0currentRange()\0"
    "voltageRange()\0autoCurrentRange()\0"
    "setAutoCurrentRange(bool)\0autoVoltageRange()\0"
    "setAutoVoltageRange(bool)\0Icomp\0"
    "setCurrentCompliance(double)\0Vcomp\0"
    "setVoltageCompliance(double)\0"
    "currentCompliance()\0voltageCompliance()\0"
    "init()\0description()\0available()\0MODE\0"
    "CURRENT\0VOLTAGE\0"
};

const QMetaObject SDeviceK2400::staticMetaObject = {
    { &SDeviceGpib::staticMetaObject, qt_meta_stringdata_SDeviceK2400,
      qt_meta_data_SDeviceK2400, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceK2400::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceK2400::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceK2400::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceK2400))
        return static_cast<void*>(const_cast< SDeviceK2400*>(this));
    return SDeviceGpib::qt_metacast(_clname);
}

int SDeviceK2400::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SDeviceGpib::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: logError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: logEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: metaDataOnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: { QScriptValue _r = qsReadVI();
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 4: { QScriptValue _r = qsReadIV();
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 5: putLocalMode(); break;
        case 6: { double _r = current();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 7: setCurrent((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: { double _r = voltage();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 9: setVoltage((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: setMode((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: { QString _r = qsMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: activate(); break;
        case 13: deactivate(); break;
        case 14: { bool _r = isActivated();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: setVoltageRange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: setCurrentRange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: setVoltMeasRange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: { double _r = currentRange();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 19: { double _r = voltageRange();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 20: { bool _r = autoCurrentRange();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 21: setAutoCurrentRange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: { bool _r = autoVoltageRange();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 23: setAutoVoltageRange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: setCurrentCompliance((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 25: setVoltageCompliance((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: { double _r = currentCompliance();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 27: { double _r = voltageCompliance();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 28: init(); break;
        case 29: { QString _r = description();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 30: { bool _r = available();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void SDeviceK2400::logError(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDeviceK2400::logEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
