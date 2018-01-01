/****************************************************************************
** Meta object code from reading C++ file 'loggerwidget.h'
**
** Created: Tue Oct 11 11:35:48 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "loggerwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loggerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoggerWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      23,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   32,   13,   13, 0x0a,
      59,   52,   13,   13, 0x08,
      95,   13,   13,   13, 0x08,
     110,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LoggerWidget[] = {
    "LoggerWidget\0\0opened()\0closed()\0msg\0"
    "append(QString)\0action\0"
    "warningsPreferenceChanged(QAction*)\0"
    "readSettings()\0saveSettings()\0"
};

const QMetaObject LoggerWidget::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LoggerWidget,
      qt_meta_data_LoggerWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoggerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoggerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoggerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoggerWidget))
        return static_cast<void*>(const_cast< LoggerWidget*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LoggerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: opened(); break;
        case 1: closed(); break;
        case 2: append((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: warningsPreferenceChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: readSettings(); break;
        case 5: saveSettings(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void LoggerWidget::opened()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LoggerWidget::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
