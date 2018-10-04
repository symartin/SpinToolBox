/****************************************************************************
** Meta object code from reading C++ file 'QTechSpinBox.h'
**
** Created: Fri 26. Jul 16:13:16 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUi/QTechSpinBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QTechSpinBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QTechSpinBox[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
      10,   64, // properties
       1,   94, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      35,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   57,   13,   13, 0x0a,
      84,   78,   13,   13, 0x0a,
     126,  121,   13,   13, 0x0a,
     142,   13,   13,   13, 0x09,
     161,   13,   13,   13, 0x08,
     175,   13,   13,   13, 0x08,
     195,   13,   13,   13, 0x08,
     213,   13,   13,   13, 0x08,

 // properties: name, type, flags
     237,  232, 0x03095103,
     247,  232, 0x03095103,
     265,  258, 0x06095103,
     273,  258, 0x06095103,
     281,  258, 0x06095103,
     300,  292, 0x0a095103,
     322,  309, 0x0009510b,
     335,  258, 0x06095103,
     346,  341, 0x01095103,
     360,  341, 0x01095103,

 // enums: name, flags, count, data
     309, 0x0,    4,   98,

 // enum data: key, value
     371, uint(QTechSpinBox::Cut),
     375, uint(QTechSpinBox::BankersRule),
     387, uint(QTechSpinBox::Arithmetic),
     398, uint(QTechSpinBox::Symmetric),

       0        // eod
};

static const char qt_meta_stringdata_QTechSpinBox[] = {
    "QTechSpinBox\0\0valueChanged(double)\0"
    "valueChanged(QString)\0val\0setValue(double)\0"
    "event\0contextMenuEvent(QContextMenuEvent*)\0"
    "step\0setStep(double)\0setValueFromText()\0"
    "stepCahnged()\0setModeScientific()\0"
    "setModeEngineer()\0setModeClassical()\0"
    "uint\0predigits\0postdigits\0double\0"
    "minimum\0maximum\0singleStep\0QString\0"
    "baseUnit\0Roundingrule\0roundingRule\0"
    "value\0bool\0unitModifiers\0stepInUnit\0"
    "Cut\0BankersRule\0Arithmetic\0Symmetric\0"
};

const QMetaObject QTechSpinBox::staticMetaObject = {
    { &QAbstractSpinBox::staticMetaObject, qt_meta_stringdata_QTechSpinBox,
      qt_meta_data_QTechSpinBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QTechSpinBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QTechSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QTechSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTechSpinBox))
        return static_cast<void*>(const_cast< QTechSpinBox*>(this));
    return QAbstractSpinBox::qt_metacast(_clname);
}

int QTechSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: setValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: contextMenuEvent((*reinterpret_cast< QContextMenuEvent*(*)>(_a[1]))); break;
        case 4: setStep((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: setValueFromText(); break;
        case 6: stepCahnged(); break;
        case 7: setModeScientific(); break;
        case 8: setModeEngineer(); break;
        case 9: setModeClassical(); break;
        default: ;
        }
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< uint*>(_v) = predigits(); break;
        case 1: *reinterpret_cast< uint*>(_v) = postdigits(); break;
        case 2: *reinterpret_cast< double*>(_v) = minimum(); break;
        case 3: *reinterpret_cast< double*>(_v) = maximum(); break;
        case 4: *reinterpret_cast< double*>(_v) = singleStep(); break;
        case 5: *reinterpret_cast< QString*>(_v) = baseUnit(); break;
        case 6: *reinterpret_cast< Roundingrule*>(_v) = roundingRule(); break;
        case 7: *reinterpret_cast< double*>(_v) = value(); break;
        case 8: *reinterpret_cast< bool*>(_v) = unitModifiers(); break;
        case 9: *reinterpret_cast< bool*>(_v) = stepInUnit(); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setPredigits(*reinterpret_cast< uint*>(_v)); break;
        case 1: setPostdigits(*reinterpret_cast< uint*>(_v)); break;
        case 2: setMinimum(*reinterpret_cast< double*>(_v)); break;
        case 3: setMaximum(*reinterpret_cast< double*>(_v)); break;
        case 4: setSingleStep(*reinterpret_cast< double*>(_v)); break;
        case 5: setBaseUnit(*reinterpret_cast< QString*>(_v)); break;
        case 6: setRoundingRule(*reinterpret_cast< Roundingrule*>(_v)); break;
        case 7: setValue(*reinterpret_cast< double*>(_v)); break;
        case 8: setUnitModifiers(*reinterpret_cast< bool*>(_v)); break;
        case 9: setStepInUnit(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QTechSpinBox::valueChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QTechSpinBox::valueChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
