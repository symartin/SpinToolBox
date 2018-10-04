/****************************************************************************
** Meta object code from reading C++ file 'SDeviceApsin20g.h'
**
** Created: Thu 8. Nov 11:39:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SDeviceApsin20g.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDeviceApsin20g.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDeviceApsin20gPlugin[] = {

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
      32,   23,   22,   22, 0x05,
      58,   23,   22,   22, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SDeviceApsin20gPlugin[] = {
    "SDeviceApsin20gPlugin\0\0log,name\0"
    "logError(QString,QString)\0"
    "logEvent(QString,QString)\0"
};

const QMetaObject SDeviceApsin20gPlugin::staticMetaObject = {
    { &SDevicePluginInterface::staticMetaObject, qt_meta_stringdata_SDeviceApsin20gPlugin,
      qt_meta_data_SDeviceApsin20gPlugin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceApsin20gPlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceApsin20gPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceApsin20gPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceApsin20gPlugin))
        return static_cast<void*>(const_cast< SDeviceApsin20gPlugin*>(this));
    if (!strcmp(_clname, "SpinToolBox.SDevicePluginInterface"))
        return static_cast< SDevicePluginInterface*>(const_cast< SDeviceApsin20gPlugin*>(this));
    return SDevicePluginInterface::qt_metacast(_clname);
}

int SDeviceApsin20gPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SDeviceApsin20gPlugin::logError(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDeviceApsin20gPlugin::logEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_SDeviceApsin20g[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      24,   16,   17,   16, 0x02,
      36,   16,   16,   16, 0x02,
      57,   16,   17,   16, 0x02,
      65,   16,   16,   16, 0x02,
      82,   16,   16,   16, 0x02,
     110,  104,   16,   16, 0x02,
     125,   16,   16,   16, 0x22,
     136,   16,   16,   16, 0x02,
     154,   16,  149,   16, 0x02,
     172,  168,  149,   16, 0x02,
     198,   16,  190,   16, 0x02,
     209,   16,  190,   16, 0x02,
     223,   16,  149,   16, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SDeviceApsin20g[] = {
    "SDeviceApsin20g\0\0double\0frequency()\0"
    "setFrequency(double)\0power()\0"
    "setPower(double)\0setPowerLimit(double)\0"
    "OnOff\0activate(bool)\0activate()\0"
    "deactivate()\0bool\0isActivated()\0cmd\0"
    "visaSend(QString)\0QString\0visaRead()\0"
    "description()\0available()\0"
};

const QMetaObject SDeviceApsin20g::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SDeviceApsin20g,
      qt_meta_data_SDeviceApsin20g, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDeviceApsin20g::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDeviceApsin20g::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDeviceApsin20g::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDeviceApsin20g))
        return static_cast<void*>(const_cast< SDeviceApsin20g*>(this));
    return QObject::qt_metacast(_clname);
}

int SDeviceApsin20g::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { double _r = frequency();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 1: setFrequency((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 2: { double _r = power();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 3: setPower((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 4: setPowerLimit((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 5: activate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: activate(); break;
        case 7: deactivate(); break;
        case 8: { bool _r = isActivated();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = visaSend((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { QString _r = visaRead();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = description();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { bool _r = available();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
