/****************************************************************************
** Meta object code from reading C++ file 'SScriptEngine.h'
**
** Created: Fri 29. Apr 11:11:09 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SScript/SScriptEngine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SScriptEngine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SScriptEngine[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      35,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      98,   61,   48,   14, 0x0a,
     156,  128,   48,   14, 0x2a,
     198,  181,   48,   14, 0x2a,
     227,  219,   48,   14, 0x2a,
     240,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SScriptEngine[] = {
    "SScriptEngine\0\0line\0exception(int)\0"
    "alreadyRun()\0QScriptValue\0"
    "program,fileName,lineNumber,debugger\0"
    "run(QString,QString,int,bool)\0"
    "program,fileName,lineNumber\0"
    "run(QString,QString,int)\0program,fileName\0"
    "run(QString,QString)\0program\0run(QString)\0"
    "abort()\0"
};

const QMetaObject SScriptEngine::staticMetaObject = {
    { &QScriptEngine::staticMetaObject, qt_meta_stringdata_SScriptEngine,
      qt_meta_data_SScriptEngine, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SScriptEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SScriptEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SScriptEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SScriptEngine))
        return static_cast<void*>(const_cast< SScriptEngine*>(this));
    return QScriptEngine::qt_metacast(_clname);
}

int SScriptEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScriptEngine::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: exception((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: alreadyRun(); break;
        case 2: { QScriptValue _r = run((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 3: { QScriptValue _r = run((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 4: { QScriptValue _r = run((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 5: { QScriptValue _r = run((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 6: abort(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SScriptEngine::exception(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SScriptEngine::alreadyRun()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
