/****************************************************************************
** Meta object code from reading C++ file 'SUiCpPSAE4440A.h'
**
** Created: Mon 25. Feb 12:06:22 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUiCpPSAE4440A.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SUiCpPSAE4440A.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SUiCpPSAE4440A[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x08,
      56,   16,   15,   15, 0x08,
      95,   16,   15,   15, 0x08,
     128,   15,   15,   15, 0x08,
     155,   15,   15,   15, 0x08,
     182,  180,   15,   15, 0x08,
     216,  180,   15,   15, 0x08,
     251,   16,   15,   15, 0x08,
     291,  286,   15,   15, 0x08,
     347,  341,   15,   15, 0x08,
     387,  341,   15,   15, 0x08,
     419,   16,   15,   15, 0x08,
     455,   16,   15,   15, 0x08,
     487,   15,   15,   15, 0x08,
     509,   15,   15,   15, 0x08,
     530,   15,   15,   15, 0x08,
     561,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SUiCpPSAE4440A[] = {
    "SUiCpPSAE4440A\0\0d\0"
    "on_dsbSaStopFreq_valueChanged(double)\0"
    "on_dsbSaStartFreq_valueChanged(double)\0"
    "on_dsbSaRbw_valueChanged(double)\0"
    "on_cmdSaCheckRbw_clicked()\0"
    "on_cmdSaAskRbw_clicked()\0i\0"
    "on_dsbSaAverage_valueChanged(int)\0"
    "on_dsbSaNbPoints_valueChanged(int)\0"
    "on_dsbSaLevel_valueChanged(double)\0"
    "text\0on_cmbxSaAttenuation_currentIndexChanged(QString)\0"
    "state\0on_chkbxSaMarkerOnOff_stateChanged(int)\0"
    "on_chkbxSaLog_stateChanged(int)\0"
    "on_dsbSaMarker_valueChanged(double)\0"
    "on_sldSaMarker_sliderMoved(int)\0"
    "on_cmdSaMax_clicked()\0on_cmdSaGo_clicked()\0"
    "on_cmdSaTargetFolder_clicked()\0"
    "on_cmdSaMeasure_clicked()\0"
};

const QMetaObject SUiCpPSAE4440A::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SUiCpPSAE4440A,
      qt_meta_data_SUiCpPSAE4440A, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SUiCpPSAE4440A::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SUiCpPSAE4440A::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SUiCpPSAE4440A::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SUiCpPSAE4440A))
        return static_cast<void*>(const_cast< SUiCpPSAE4440A*>(this));
    if (!strcmp(_clname, "Ui_SUiCpPSAE4440A"))
        return static_cast< Ui_SUiCpPSAE4440A*>(const_cast< SUiCpPSAE4440A*>(this));
    return QWidget::qt_metacast(_clname);
}

int SUiCpPSAE4440A::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_dsbSaStopFreq_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: on_dsbSaStartFreq_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: on_dsbSaRbw_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: on_cmdSaCheckRbw_clicked(); break;
        case 4: on_cmdSaAskRbw_clicked(); break;
        case 5: on_dsbSaAverage_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: on_dsbSaNbPoints_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: on_dsbSaLevel_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: on_cmbxSaAttenuation_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: on_chkbxSaMarkerOnOff_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: on_chkbxSaLog_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: on_dsbSaMarker_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: on_sldSaMarker_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: on_cmdSaMax_clicked(); break;
        case 14: on_cmdSaGo_clicked(); break;
        case 15: on_cmdSaTargetFolder_clicked(); break;
        case 16: on_cmdSaMeasure_clicked(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
