/****************************************************************************
** Meta object code from reading C++ file 'SUiScriptEditor.h'
**
** Created: Fri 29. Apr 11:11:09 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUi/SUiScriptEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SUiScriptEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SUiScriptEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      54,   17,   16,   16, 0x05,
      84,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      98,   16,   16,   16, 0x0a,
     111,   16,   16,   16, 0x0a,
     130,   16,   16,   16, 0x0a,
     150,  148,   16,   16, 0x0a,
     177,   16,   16,   16, 0x08,
     187,   16,   16,   16, 0x08,
     199,   16,  194,   16, 0x08,
     206,   16,  194,   16, 0x08,
     215,   16,   16,   16, 0x08,
     223,   16,   16,   16, 0x08,
     245,   16,   16,   16, 0x08,
     255,   16,   16,   16, 0x08,
     275,   16,   16,   16, 0x08,
     298,   16,   16,   16, 0x08,
     311,  305,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SUiScriptEditor[] = {
    "SUiScriptEditor\0\0program,fileName,lineNumber,debugger\0"
    "run(QString,QString,int,bool)\0"
    "abortEngine()\0alreadyRun()\0"
    "swichToDebugMode()\0swichToEditMode()\0"
    ",\0onFocus(QWidget*,QWidget*)\0newFile()\0"
    "open()\0bool\0save()\0saveAs()\0about()\0"
    "documentWasModified()\0execute()\0"
    "switchLexerNormal()\0switchLexerDebugComp()\0"
    "Kill()\0index\0tabDbgCurrentChanged(int)\0"
};

const QMetaObject SUiScriptEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SUiScriptEditor,
      qt_meta_data_SUiScriptEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SUiScriptEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SUiScriptEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SUiScriptEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SUiScriptEditor))
        return static_cast<void*>(const_cast< SUiScriptEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SUiScriptEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: run((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 1: abortEngine(); break;
        case 2: alreadyRun(); break;
        case 3: swichToDebugMode(); break;
        case 4: swichToEditMode(); break;
        case 5: onFocus((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 6: newFile(); break;
        case 7: open(); break;
        case 8: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: about(); break;
        case 11: documentWasModified(); break;
        case 12: execute(); break;
        case 13: switchLexerNormal(); break;
        case 14: switchLexerDebugComp(); break;
        case 15: Kill(); break;
        case 16: tabDbgCurrentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void SUiScriptEditor::run(const QString & _t1, const QString & _t2, int _t3, bool _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SUiScriptEditor::abortEngine()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
