/****************************************************************************
** Meta object code from reading C++ file 'SUiCpDaqFieldOneAxis.h'
**
** Created: Thu 8. Nov 11:24:38 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUiCpDaqFieldOneAxis.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SUiCpDaqFieldOneAxis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SUiCpDaqFieldOneAxis[] = {

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

 // slots: signature, parameters, type, tag, flags
      24,   22,   21,   21, 0x08,
      62,   22,   21,   21, 0x08,
      96,   21,   21,   21, 0x08,
     120,   21,   21,   21, 0x08,
     144,   21,   21,   21, 0x08,
     167,   21,   21,   21, 0x08,
     199,  193,   21,   21, 0x08,
     247,  239,   21,   21, 0x08,
     278,   21,   21,   21, 0x08,
     298,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SUiCpDaqFieldOneAxis[] = {
    "SUiCpDaqFieldOneAxis\0\0d\0"
    "on_dsbFieldValue_valueChanged(double)\0"
    "on_sldFieldValue_sliderMoved(int)\0"
    "on_cmdFieldGo_clicked()\0on_cmdFieldAP_clicked()\0"
    "on_cmdFieldP_clicked()\0on_cmdFieldZero_clicked()\0"
    "state\0on_chkbxFieldRealTime_stateChanged(int)\0"
    "checked\0on_cmdFieldOnOff_clicked(bool)\0"
    "on_cmdOpt_clicked()\0moveSlider()\0"
};

const QMetaObject SUiCpDaqFieldOneAxis::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SUiCpDaqFieldOneAxis,
      qt_meta_data_SUiCpDaqFieldOneAxis, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SUiCpDaqFieldOneAxis::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SUiCpDaqFieldOneAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SUiCpDaqFieldOneAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SUiCpDaqFieldOneAxis))
        return static_cast<void*>(const_cast< SUiCpDaqFieldOneAxis*>(this));
    if (!strcmp(_clname, "Ui_SUiCpDaqFieldOneAxis"))
        return static_cast< Ui_SUiCpDaqFieldOneAxis*>(const_cast< SUiCpDaqFieldOneAxis*>(this));
    return QWidget::qt_metacast(_clname);
}

int SUiCpDaqFieldOneAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_dsbFieldValue_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: on_sldFieldValue_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_cmdFieldGo_clicked(); break;
        case 3: on_cmdFieldAP_clicked(); break;
        case 4: on_cmdFieldP_clicked(); break;
        case 5: on_cmdFieldZero_clicked(); break;
        case 6: on_chkbxFieldRealTime_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: on_cmdFieldOnOff_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: on_cmdOpt_clicked(); break;
        case 9: moveSlider(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
