/****************************************************************************
** Meta object code from reading C++ file 'QScienceSpinBox.h'
**
** Created: Fri 26. Jul 16:13:17 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUi/QScienceSpinBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QScienceSpinBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QScienceSpinBox[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       3,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      28,   16,   16,   16, 0x0a,
      39,   37,   16,   16, 0x0a,
      58,   37,   16,   16, 0x0a,
      83,   77,   16,   16, 0x0a,
     125,  120,   16,   16, 0x0a,
     141,   16,   16,   16, 0x08,
     155,   16,   16,   16, 0x08,
     175,   16,   16,   16, 0x08,
     193,   16,   16,   16, 0x08,

 // properties: name, type, flags
     216,  210, 0x07095103,
     120,  226, 0x02095103,
     235,  230, 0x01095103,

       0        // eod
};

static const char qt_meta_stringdata_QScienceSpinBox[] = {
    "QScienceSpinBox\0\0stepDown()\0stepUp()\0"
    "d\0setMaximum(double)\0setMinimum(double)\0"
    "event\0contextMenuEvent(QContextMenuEvent*)\0"
    "step\0setStep(double)\0stepChanged()\0"
    "setModeScientific()\0setModeEngineer()\0"
    "setModeClassic()\0QChar\0delimiter\0int\0"
    "bool\0byDecimals\0"
};

const QMetaObject QScienceSpinBox::staticMetaObject = {
    { &QDoubleSpinBox::staticMetaObject, qt_meta_stringdata_QScienceSpinBox,
      qt_meta_data_QScienceSpinBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QScienceSpinBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QScienceSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QScienceSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QScienceSpinBox))
        return static_cast<void*>(const_cast< QScienceSpinBox*>(this));
    return QDoubleSpinBox::qt_metacast(_clname);
}

int QScienceSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDoubleSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stepDown(); break;
        case 1: stepUp(); break;
        case 2: setMaximum((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: setMinimum((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: contextMenuEvent((*reinterpret_cast< QContextMenuEvent*(*)>(_a[1]))); break;
        case 5: setStep((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: stepChanged(); break;
        case 7: setModeScientific(); break;
        case 8: setModeEngineer(); break;
        case 9: setModeClassic(); break;
        default: ;
        }
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QChar*>(_v) = delimiter(); break;
        case 1: *reinterpret_cast< int*>(_v) = step(); break;
        case 2: *reinterpret_cast< bool*>(_v) = byDecimals(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDelimiter(*reinterpret_cast< QChar*>(_v)); break;
        case 1: setStep(*reinterpret_cast< int*>(_v)); break;
        case 2: setByDecimals(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
