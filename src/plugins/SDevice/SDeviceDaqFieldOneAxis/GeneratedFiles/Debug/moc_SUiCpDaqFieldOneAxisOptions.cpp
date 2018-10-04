/****************************************************************************
** Meta object code from reading C++ file 'SUiCpDaqFieldOneAxisOptions.h'
**
** Created: Thu 8. Nov 11:24:37 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUiCpDaqFieldOneAxisOptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SUiCpDaqFieldOneAxisOptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SUiCpDaqFieldOneAxisOptions[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SUiCpDaqFieldOneAxisOptions[] = {
    "SUiCpDaqFieldOneAxisOptions\0\0"
    "on_cmdOk_clicked()\0"
};

const QMetaObject SUiCpDaqFieldOneAxisOptions::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SUiCpDaqFieldOneAxisOptions,
      qt_meta_data_SUiCpDaqFieldOneAxisOptions, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SUiCpDaqFieldOneAxisOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SUiCpDaqFieldOneAxisOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SUiCpDaqFieldOneAxisOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SUiCpDaqFieldOneAxisOptions))
        return static_cast<void*>(const_cast< SUiCpDaqFieldOneAxisOptions*>(this));
    if (!strcmp(_clname, "Ui_SUiCpDaqFieldOneAxisOptions"))
        return static_cast< Ui_SUiCpDaqFieldOneAxisOptions*>(const_cast< SUiCpDaqFieldOneAxisOptions*>(this));
    return QDialog::qt_metacast(_clname);
}

int SUiCpDaqFieldOneAxisOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_cmdOk_clicked(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
