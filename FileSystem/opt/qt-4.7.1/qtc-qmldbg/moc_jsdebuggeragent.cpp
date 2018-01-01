/****************************************************************************
** Meta object code from reading C++ file 'jsdebuggeragent.h'
**
** Created: Tue Oct 11 11:35:30 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/jsdebuggeragent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jsdebuggeragent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QmlJSDebugger__JSDebuggerAgent[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QmlJSDebugger__JSDebuggerAgent[] = {
    "QmlJSDebugger::JSDebuggerAgent\0"
};

const QMetaObject QmlJSDebugger::JSDebuggerAgent::staticMetaObject = {
    { &QDeclarativeDebugService::staticMetaObject, qt_meta_stringdata_QmlJSDebugger__JSDebuggerAgent,
      qt_meta_data_QmlJSDebugger__JSDebuggerAgent, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QmlJSDebugger::JSDebuggerAgent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QmlJSDebugger::JSDebuggerAgent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QmlJSDebugger::JSDebuggerAgent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QmlJSDebugger__JSDebuggerAgent))
        return static_cast<void*>(const_cast< JSDebuggerAgent*>(this));
    if (!strcmp(_clname, "QScriptEngineAgent"))
        return static_cast< QScriptEngineAgent*>(const_cast< JSDebuggerAgent*>(this));
    return QDeclarativeDebugService::qt_metacast(_clname);
}

int QmlJSDebugger::JSDebuggerAgent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeDebugService::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
