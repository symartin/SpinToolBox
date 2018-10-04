/****************************************************************************
** Meta object code from reading C++ file 'SDeviceDaqFieldOneAxis.h'
**
** Created: Thu 8. Nov 11:24:40 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDeviceDaqFieldOneAxis.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDeviceDaqFieldOneAxis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDeviceDaqFieldOneAxisPlugin[] = {

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
      39,   30,   29,   29, 0x05,
      65,   30,   29,   29, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SDeviceDaqFieldOneAxisPlugin[] = {
    "SDeviceDaqFieldOneAxisPlugin\0\0log,name\0"
    "logError(QString,QString)\0"
    "logEvent(QString,QString)\0"
};

const QMetaObject SDeviceDaqFieldOneAxisPlugin::staticMetaObject = {
    { &SDevicePluginInterface::staticMetaObject, qt_meta_stringdata_SDeviceDaqFieldOneAxisPlugin,
      qt_meta_data_SDeviceDaqFieldOneAxisPlugin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceDaqFieldOneAxisPlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceDaqFieldOneAxisPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceDaqFieldOneAxisPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceDaqFieldOneAxisPlugin))
        return static_cast<void*>(const_cast< SDeviceDaqFieldOneAxisPlugin*>(this));
    if (!strcmp(_clname, "SpinToolBox.SDevicePluginInterface"))
        return static_cast< SDevicePluginInterface*>(const_cast< SDeviceDaqFieldOneAxisPlugin*>(this));
    return SDevicePluginInterface::qt_metacast(_clname);
}

int SDeviceDaqFieldOneAxisPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SDeviceDaqFieldOneAxisPlugin::logError(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDeviceDaqFieldOneAxisPlugin::logEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_SInterfaceDaq[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      26,   14,   14,   14, 0x05,
      40,   14,   14,   14, 0x05,

 // methods: signature, parameters, type, tag, flags
      54,   48,   14,   14, 0x02,
      81,   14,   74,   14, 0x02,
     103,   93,   14,   14, 0x02,
     139,  124,   14,   14, 0x02,
     169,   14,  164,   14, 0x02,
     181,   14,  164,   14, 0x02,
     199,  191,   74,   14, 0x02,
     209,   14,   74,   14, 0x22,
     229,  216,   74,   14, 0x02,
     263,  258,   74,   14, 0x22,

       0        // eod
};

static const char qt_meta_stringdata_SInterfaceDaq[] = {
    "SInterfaceDaq\0\0finished()\0unavailable()\0"
    "ready()\0onOff\0metaDataOnOff(bool)\0"
    "double\0prefactor()\0prefactor\0"
    "setPrefactor(double)\0Vz,dVz,channel\0"
    "sweep(double,double,int)\0bool\0available()\0"
    "running()\0channel\0vOld(int)\0vOld()\0"
    "V,dV,channel\0timeSweep(double,double,int)\0"
    "V,dV\0timeSweep(double,double)\0"
};

const QMetaObject SInterfaceDaq::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SInterfaceDaq,
      qt_meta_data_SInterfaceDaq, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SInterfaceDaq::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SInterfaceDaq::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SInterfaceDaq::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SInterfaceDaq))
        return static_cast<void*>(const_cast< SInterfaceDaq*>(this));
    return QObject::qt_metacast(_clname);
}

int SInterfaceDaq::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finished(); break;
        case 1: unavailable(); break;
        case 2: ready(); break;
        case 3: metaDataOnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: { double _r = prefactor();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 5: setPrefactor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: sweep((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: { bool _r = available();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { double _r = vOld((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 10: { double _r = vOld();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 11: { double _r = timeSweep((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 12: { double _r = timeSweep((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SInterfaceDaq::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SInterfaceDaq::unavailable()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SInterfaceDaq::ready()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
