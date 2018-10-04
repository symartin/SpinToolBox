/****************************************************************************
** Meta object code from reading C++ file 'SInterfaceGpib.h'
**
** Created: Thu 8. Nov 11:40:07 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SInterface/SInterfaceGpib.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SInterfaceGpib.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SInterfaceGpib[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      24,   15,   16,   15, 0x02,
      43,   15,   38,   15, 0x02,
      50,   15,   38,   15, 0x02,
      66,   15,   62,   15, 0x02,
      85,   78,   15,   15, 0x02,
     113,  100,   15,   15, 0x02,
     163,  150,   15,   15, 0x02,
     188,  150,   15,   15, 0x02,
     225,  217,   15,   15, 0x02,
     277,  258,  249,   15, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SInterfaceGpib[] = {
    "SInterfaceGpib\0\0QString\0description()\0"
    "bool\0init()\0available()\0int\0GPIBibsta()\0"
    "active\0activate(bool)\0address,mode\0"
    "switcher(Addr4882_t,GpibElementMode)\0"
    "address,data\0send(Addr4882_t,QString)\0"
    "send(Addr4882_t,const char*)\0address\0"
    "enableLocal(Addr4882_t)\0QVariant\0"
    "address,bufferLong\0receive(Addr4882_t,long)\0"
};

const QMetaObject SInterfaceGpib::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SInterfaceGpib,
      qt_meta_data_SInterfaceGpib, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SInterfaceGpib::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SInterfaceGpib::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SInterfaceGpib::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SInterfaceGpib))
        return static_cast<void*>(const_cast< SInterfaceGpib*>(this));
    return QObject::qt_metacast(_clname);
}

int SInterfaceGpib::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QString _r = description();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { bool _r = init();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = available();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { int _r = GPIBibsta();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: activate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: switcher((*reinterpret_cast< Addr4882_t(*)>(_a[1])),(*reinterpret_cast< GpibElementMode(*)>(_a[2]))); break;
        case 6: send((*reinterpret_cast< const Addr4882_t(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: send((*reinterpret_cast< Addr4882_t(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 8: enableLocal((*reinterpret_cast< const Addr4882_t(*)>(_a[1]))); break;
        case 9: { QVariant _r = receive((*reinterpret_cast< const Addr4882_t(*)>(_a[1])),(*reinterpret_cast< const long(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
