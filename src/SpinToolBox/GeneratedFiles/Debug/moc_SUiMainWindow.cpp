/****************************************************************************
** Meta object code from reading C++ file 'SUiMainWindow.h'
**
** Created: Thu 22. Nov 18:47:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SUi/SUiMainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SUiMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SUiMainWindow[] = {

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
      15,   14,   14,   14, 0x0a,
      36,   14,   14,   14, 0x0a,
      62,   14,   14,   14, 0x0a,
      85,   14,   14,   14, 0x0a,
     106,   14,   14,   14, 0x0a,
     135,  129,   14,   14, 0x0a,
     158,  129,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SUiMainWindow[] = {
    "SUiMainWindow\0\0on_cmdOpen_clicked()\0"
    "on_cmdNewScript_clicked()\0"
    "on_cmdCmdMan_clicked()\0on_cmdQuit_clicked()\0"
    "on_cmdPlgMng_clicked()\0event\0"
    "dropEvent(QDropEvent*)\0"
    "dragEnterEvent(QDragEnterEvent*)\0"
};

const QMetaObject SUiMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SUiMainWindow,
      qt_meta_data_SUiMainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SUiMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SUiMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SUiMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SUiMainWindow))
        return static_cast<void*>(const_cast< SUiMainWindow*>(this));
    if (!strcmp(_clname, "Ui::SUiMainWindow"))
        return static_cast< Ui::SUiMainWindow*>(const_cast< SUiMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SUiMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_cmdOpen_clicked(); break;
        case 1: on_cmdNewScript_clicked(); break;
        case 2: on_cmdCmdMan_clicked(); break;
        case 3: on_cmdQuit_clicked(); break;
        case 4: on_cmdPlgMng_clicked(); break;
        case 5: dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 6: dragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
