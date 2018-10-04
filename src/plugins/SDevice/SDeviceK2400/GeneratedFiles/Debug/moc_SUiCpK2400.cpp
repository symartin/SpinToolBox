/****************************************************************************
** Meta object code from reading C++ file 'SUiCpK2400.h'
**
** Created: Thu 8. Nov 11:24:54 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUiCpK2400.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SUiCpK2400.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SUiCpK2400[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x08,
      50,   48,   11,   11, 0x08,
      85,   12,   11,   11, 0x08,
     118,   12,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,
     220,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SUiCpK2400[] = {
    "SUiCpK2400\0\0checked\0on_cmdDcOnOff_clicked(bool)\0"
    "d\0on_dsbDcValue_valueChanged(double)\0"
    "on_radbttDcCurrent_clicked(bool)\0"
    "on_radbttDcVoltage_clicked(bool)\0"
    "on_dsbDcValue_editingFinished()\0"
    "on_dsbDcCurrentMax_editingFinished()\0"
    "on_dsbDcVoltageMax_editingFinished()\0"
};

const QMetaObject SUiCpK2400::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SUiCpK2400,
      qt_meta_data_SUiCpK2400, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SUiCpK2400::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SUiCpK2400::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SUiCpK2400::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SUiCpK2400))
        return static_cast<void*>(const_cast< SUiCpK2400*>(this));
    if (!strcmp(_clname, "Ui_SUiCpK2400"))
        return static_cast< Ui_SUiCpK2400*>(const_cast< SUiCpK2400*>(this));
    return QWidget::qt_metacast(_clname);
}

int SUiCpK2400::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_cmdDcOnOff_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: on_dsbDcValue_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: on_radbttDcCurrent_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_radbttDcVoltage_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: on_dsbDcValue_editingFinished(); break;
        case 5: on_dsbDcCurrentMax_editingFinished(); break;
        case 6: on_dsbDcVoltageMax_editingFinished(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
