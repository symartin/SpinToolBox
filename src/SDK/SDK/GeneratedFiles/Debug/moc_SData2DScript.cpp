/****************************************************************************
** Meta object code from reading C++ file 'SData2DScript.h'
**
** Created: Fri 26. Jul 16:13:12 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SData/SData2DScript.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SData2DScript.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SData2DScript[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x02,
      42,   37,   14,   14, 0x02,
      60,   37,   14,   14, 0x02,
      82,   78,   14,   14, 0x02,
     116,   78,   14,   14, 0x02,
     140,  138,   14,   14, 0x02,
     179,  153,   14,   14, 0x02,
     212,  204,   14,   14, 0x22,
     230,   14,   14,   14, 0x22,
     252,  138,  245,   14, 0x02,
     259,  138,  245,   14, 0x02,
     272,  266,   14,   14, 0x02,
     289,  266,   14,   14, 0x02,
     310,   14,  306,   14, 0x02,
     318,   14,  306,   14, 0x02,
     338,  334,  325,   14, 0x02,
     366,  356,   14,   14, 0x02,
     408,  396,   14,   14, 0x02,
     442,  436,   14,   14, 0x02,
     471,   14,  463,   14, 0x02,
     488,  482,   14,   14, 0x02,
     509,   14,  463,   14, 0x02,
     532,  520,   14,   14, 0x02,
     566,  560,   14,   14, 0x02,
     587,   14,  463,   14, 0x02,
     604,  598,   14,   14, 0x02,
     625,   14,  463,   14, 0x02,
     655,  649,  636,   14, 0x02,
     664,   14,  636,   14, 0x22,
     674,  670,   14,   14, 0x02,
     694,   14,  636,   14, 0x02,
     704,   14,   14,   14, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SData2DScript[] = {
    "SData2DScript\0\0data\0setData(SData2D)\0"
    "file\0openFile(QString)\0saveFile(QString)\0"
    "x,y\0append(QVariantList,QVariantList)\0"
    "append(double,double)\0i\0delItem(int)\0"
    "windows,PeackProtectCoeff\0"
    "slideAverage(int,double)\0windows\0"
    "slideAverage(int)\0slideAverage()\0"
    "double\0x(int)\0y(int)\0i,val\0setx(int,double)\0"
    "sety(int,double)\0int\0count()\0size()\0"
    "QVariant\0key\0metaData(QString)\0key,value\0"
    "setMetaData(QString,QVariant)\0Xname,Yname\0"
    "setColName(QString,QString)\0Xname\0"
    "setColXName(QString)\0QString\0colXName()\0"
    "Yname\0setColYName(QString)\0colYName()\0"
    "XUnit,YUnit\0setColUnit(QString,QString)\0"
    "XUnit\0setColXUnit(QString)\0colXUnit()\0"
    "YUnit\0setColYUnit(QString)\0colYUnit()\0"
    "QScriptValue\0start\0max(int)\0max()\0com\0"
    "addComment(QString)\0comment()\0"
    "clearComment()\0"
};

const QMetaObject SData2DScript::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SData2DScript,
      qt_meta_data_SData2DScript, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SData2DScript::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SData2DScript::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SData2DScript::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SData2DScript))
        return static_cast<void*>(const_cast< SData2DScript*>(this));
    if (!strcmp(_clname, "QScriptable"))
        return static_cast< QScriptable*>(const_cast< SData2DScript*>(this));
    return QObject::qt_metacast(_clname);
}

int SData2DScript::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setData((*reinterpret_cast< SData2D(*)>(_a[1]))); break;
        case 1: openFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: saveFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: append((*reinterpret_cast< QVariantList(*)>(_a[1])),(*reinterpret_cast< QVariantList(*)>(_a[2]))); break;
        case 4: append((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: delItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: slideAverage((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const double(*)>(_a[2]))); break;
        case 7: slideAverage((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 8: slideAverage(); break;
        case 9: { double _r = x((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 10: { double _r = y((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 11: setx((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 12: sety((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 13: { int _r = count();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = size();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { QVariant _r = metaData((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 16: setMetaData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 17: setColName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: setColXName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: { QString _r = colXName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 20: setColYName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: { QString _r = colYName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 22: setColUnit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 23: setColXUnit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: { QString _r = colXUnit();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 25: setColYUnit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 26: { QString _r = colYUnit();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 27: { QScriptValue _r = max((*reinterpret_cast< const int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 28: { QScriptValue _r = max();
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 29: addComment((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: { QScriptValue _r = comment();
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 31: clearComment(); break;
        default: ;
        }
        _id -= 32;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
