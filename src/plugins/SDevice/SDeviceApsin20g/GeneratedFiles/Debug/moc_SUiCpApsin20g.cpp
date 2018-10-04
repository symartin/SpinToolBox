/****************************************************************************
** Meta object code from reading C++ file 'SUiCpApsin20g.h'
**
** Created: Thu 8. Nov 11:39:12 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUiCpApsin20g.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SUiCpApsin20g.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SUiCpApsin20g[] = {

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
      23,   15,   14,   14, 0x08,
      51,   14,   14,   14, 0x08,
      83,   14,   14,   14, 0x08,
     116,  114,   14,   14, 0x08,
     151,  114,   14,   14, 0x08,
     185,   14,   14,   14, 0x08,
     222,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SUiCpApsin20g[] = {
    "SUiCpApsin20g\0\0checked\0"
    "on_cmdMwOnOff_clicked(bool)\0"
    "on_dsbMwPower_editingFinished()\0"
    "on_dsbMwFreq_editingFinished()\0d\0"
    "on_dsbMwPower_valueChanged(double)\0"
    "on_dsbMwFreq_valueChanged(double)\0"
    "on_dsbMwPowerLimit_editingFinished()\0"
    "on_cmdMwGo_clicked()\0"
};

const QMetaObject SUiCpApsin20g::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SUiCpApsin20g,
      qt_meta_data_SUiCpApsin20g, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SUiCpApsin20g::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SUiCpApsin20g::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SUiCpApsin20g::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SUiCpApsin20g))
        return static_cast<void*>(const_cast< SUiCpApsin20g*>(this));
    if (!strcmp(_clname, "Ui_SUiCpApsin20g"))
        return static_cast< Ui_SUiCpApsin20g*>(const_cast< SUiCpApsin20g*>(this));
    return QWidget::qt_metacast(_clname);
}

int SUiCpApsin20g::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_cmdMwOnOff_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: on_dsbMwPower_editingFinished(); break;
        case 2: on_dsbMwFreq_editingFinished(); break;
        case 3: on_dsbMwPower_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: on_dsbMwFreq_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: on_dsbMwPowerLimit_editingFinished(); break;
        case 6: on_cmdMwGo_clicked(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
