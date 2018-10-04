/****************************************************************************
** Meta object code from reading C++ file 'SDevicePSAE4440A.h'
**
** Created: Mon 25. Feb 12:06:22 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDevicePSAE4440A.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDevicePSAE4440A.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDevicePSAE4440APlugin[] = {

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

static const char qt_meta_stringdata_SDevicePSAE4440APlugin[] = {
    "SDevicePSAE4440APlugin\0\0log,name\0"
    "logError(QString,QString)\0"
    "logEvent(QString,QString)\0"
};

const QMetaObject SDevicePSAE4440APlugin::staticMetaObject = {
    { &SDevicePluginInterface::staticMetaObject, qt_meta_stringdata_SDevicePSAE4440APlugin,
      qt_meta_data_SDevicePSAE4440APlugin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDevicePSAE4440APlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDevicePSAE4440APlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDevicePSAE4440APlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDevicePSAE4440APlugin))
        return static_cast<void*>(const_cast< SDevicePSAE4440APlugin*>(this));
    if (!strcmp(_clname, "SpinToolBox.SDevicePluginInterface"))
        return static_cast< SDevicePluginInterface*>(const_cast< SDevicePSAE4440APlugin*>(this));
    return SDevicePluginInterface::qt_metacast(_clname);
}

int SDevicePSAE4440APlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SDevicePSAE4440APlugin::logError(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDevicePSAE4440APlugin::logEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_SDevicePSAE4440A[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x02,
      49,   44,   17,   17, 0x02,
      77,   17,   70,   17, 0x02,
      89,   44,   17,   17, 0x02,
     109,   17,   70,   17, 0x02,
     124,  120,   17,   17, 0x02,
     139,   17,   70,   17, 0x02,
     149,  145,   70,   17, 0x02,
     170,  166,   17,   17, 0x02,
     194,   17,  190,   17, 0x02,
     214,  208,   17,   17, 0x02,
     231,   17,  190,   17, 0x02,
     249,  242,   17,   17, 0x02,
     267,   17,  190,   17, 0x02,
     286,  279,   17,   17, 0x02,
     306,   17,   70,   17, 0x02,
     323,  317,   17,   17, 0x02,
     348,   17,  343,   17, 0x02,
     361,   17,   70,   17, 0x02,
     387,  373,   17,   17, 0x02,
     419,  409,   17,   17, 0x22,
     447,  437,   17,   17, 0x02,
     464,  317,   17,   17, 0x22,
     481,  477,   70,   17, 0x02,
     497,   17,   17,   17, 0x02,
     520,   17,  507,   17, 0x02,
     537,   17,   17,   17, 0x02,
     552,   17,  544,   17, 0x02,
     559,   17,  544,   17, 0x02,
     573,   17,  343,   17, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SDevicePSAE4440A[] = {
    "SDevicePSAE4440A\0\0onOff\0metaDataOnOff(bool)\0"
    "freq\0setFreqStart(double)\0double\0"
    "freqStart()\0setFreqStop(double)\0"
    "freqStop()\0RBW\0setRbw(double)\0rbw()\0"
    "rbw\0checkRbw(double)\0Att\0setAttenuation(int)\0"
    "int\0attenuation()\0NbPts\0setNbPoints(int)\0"
    "nbPoints()\0NbAvrg\0setNbAverage(int)\0"
    "nbAverage()\0RefLvl\0setRefLevel(double)\0"
    "refLevel()\0OnOff\0setLogDisplay(bool)\0"
    "bool\0logDisplay()\0sweepTime()\0"
    "frequence,num\0setMarker(double,int)\0"
    "frequence\0setMarker(double)\0OnOff,num\0"
    "marker(bool,int)\0marker(bool)\0num\0"
    "readMarker(int)\0restart()\0QScriptValue\0"
    "qsReadSpectrum()\0init()\0QString\0name()\0"
    "description()\0available()\0"
};

const QMetaObject SDevicePSAE4440A::staticMetaObject = {
    { &SDeviceGpib::staticMetaObject, qt_meta_stringdata_SDevicePSAE4440A,
      qt_meta_data_SDevicePSAE4440A, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDevicePSAE4440A::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDevicePSAE4440A::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDevicePSAE4440A::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDevicePSAE4440A))
        return static_cast<void*>(const_cast< SDevicePSAE4440A*>(this));
    return SDeviceGpib::qt_metacast(_clname);
}

int SDevicePSAE4440A::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SDeviceGpib::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: metaDataOnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setFreqStart((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 2: { double _r = freqStart();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 3: setFreqStop((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 4: { double _r = freqStop();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 5: setRbw((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 6: { double _r = rbw();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 7: { double _r = checkRbw((*reinterpret_cast< const double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 8: setAttenuation((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 9: { int _r = attenuation();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: setNbPoints((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 11: { int _r = nbPoints();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: setNbAverage((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 13: { int _r = nbAverage();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: setRefLevel((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 15: { double _r = refLevel();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 16: setLogDisplay((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 17: { bool _r = logDisplay();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: { double _r = sweepTime();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 19: setMarker((*reinterpret_cast< const double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 20: setMarker((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 21: marker((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 22: marker((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 23: { double _r = readMarker((*reinterpret_cast< const int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 24: restart(); break;
        case 25: { QScriptValue _r = qsReadSpectrum();
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 26: init(); break;
        case 27: { QString _r = name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 28: { QString _r = description();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 29: { bool _r = available();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 30;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
