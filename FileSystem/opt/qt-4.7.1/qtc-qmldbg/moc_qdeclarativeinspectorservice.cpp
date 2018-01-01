/****************************************************************************
** Meta object code from reading C++ file 'qdeclarativeinspectorservice.h'
**
** Created: Tue Oct 11 11:35:32 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/qdeclarativeinspectorservice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdeclarativeinspectorservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QmlJSDebugger__QDeclarativeInspectorService[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: signature, parameters, type, tag, flags
      64,   45,   44,   44, 0x05,
     101,   93,   44,   44, 0x05,
     153,  140,   44,   44, 0x05,
     198,  185,   44,   44, 0x05,
     224,   44,   44,   44, 0x05,
     242,   44,   44,   44, 0x05,
     264,   44,   44,   44, 0x05,
     293,   44,   44,   44, 0x05,
     313,   44,   44,   44, 0x05,
     374,  340,   44,   44, 0x05,
     468,  440,   44,   44, 0x25,
     549,  530,   44,   44, 0x25,
     620,  603,   44,   44, 0x05,
     670,  663,   44,   44, 0x05,
     716,  704,   44,   44, 0x05,
     760,  753,   44,   44, 0x05,
     796,   44,   44,   44, 0x05,

 // slots: signature, parameters, type, tag, flags
     833,  827,   44,   44, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QmlJSDebugger__QDeclarativeInspectorService[] = {
    "QmlJSDebugger::QDeclarativeInspectorService\0"
    "\0hasDebuggingClient\0debuggingClientChanged(bool)\0"
    "objects\0currentObjectsChanged(QList<QObject*>)\0"
    "inDesignMode\0designModeBehaviorChanged(bool)\0"
    "showAppOnTop\0showAppOnTopChanged(bool)\0"
    "reloadRequested()\0selectToolRequested()\0"
    "selectMarqueeToolRequested()\0"
    "zoomToolRequested()\0colorPickerToolRequested()\0"
    "qml,parent,imports,filename,order\0"
    "objectCreationRequested(QString,QObject*,QStringList,QString,int)\0"
    "qml,parent,imports,filename\0"
    "objectCreationRequested(QString,QObject*,QStringList,QString)\0"
    "qml,parent,imports\0"
    "objectCreationRequested(QString,QObject*,QStringList)\0"
    "object,newParent\0"
    "objectReparentRequested(QObject*,QObject*)\0"
    "object\0objectDeletionRequested(QObject*)\0"
    "speedFactor\0animationSpeedChangeRequested(qreal)\0"
    "paused\0executionPauseChangeRequested(bool)\0"
    "clearComponentCacheRequested()\0color\0"
    "selectedColorChanged(QColor)\0"
};

const QMetaObject QmlJSDebugger::QDeclarativeInspectorService::staticMetaObject = {
    { &QDeclarativeDebugService::staticMetaObject, qt_meta_stringdata_QmlJSDebugger__QDeclarativeInspectorService,
      qt_meta_data_QmlJSDebugger__QDeclarativeInspectorService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QmlJSDebugger::QDeclarativeInspectorService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QmlJSDebugger::QDeclarativeInspectorService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QmlJSDebugger::QDeclarativeInspectorService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QmlJSDebugger__QDeclarativeInspectorService))
        return static_cast<void*>(const_cast< QDeclarativeInspectorService*>(this));
    return QDeclarativeDebugService::qt_metacast(_clname);
}

int QmlJSDebugger::QDeclarativeInspectorService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeDebugService::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: debuggingClientChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: currentObjectsChanged((*reinterpret_cast< const QList<QObject*>(*)>(_a[1]))); break;
        case 2: designModeBehaviorChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: showAppOnTopChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: reloadRequested(); break;
        case 5: selectToolRequested(); break;
        case 6: selectMarqueeToolRequested(); break;
        case 7: zoomToolRequested(); break;
        case 8: colorPickerToolRequested(); break;
        case 9: objectCreationRequested((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 10: objectCreationRequested((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 11: objectCreationRequested((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3]))); break;
        case 12: objectReparentRequested((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 13: objectDeletionRequested((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 14: animationSpeedChangeRequested((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 15: executionPauseChangeRequested((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: clearComponentCacheRequested(); break;
        case 17: selectedColorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void QmlJSDebugger::QDeclarativeInspectorService::debuggingClientChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QmlJSDebugger::QDeclarativeInspectorService::currentObjectsChanged(const QList<QObject*> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QmlJSDebugger::QDeclarativeInspectorService::designModeBehaviorChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QmlJSDebugger::QDeclarativeInspectorService::showAppOnTopChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QmlJSDebugger::QDeclarativeInspectorService::reloadRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QmlJSDebugger::QDeclarativeInspectorService::selectToolRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void QmlJSDebugger::QDeclarativeInspectorService::selectMarqueeToolRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void QmlJSDebugger::QDeclarativeInspectorService::zoomToolRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void QmlJSDebugger::QDeclarativeInspectorService::colorPickerToolRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void QmlJSDebugger::QDeclarativeInspectorService::objectCreationRequested(const QString & _t1, QObject * _t2, const QStringList & _t3, const QString & _t4, int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 12
void QmlJSDebugger::QDeclarativeInspectorService::objectReparentRequested(QObject * _t1, QObject * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void QmlJSDebugger::QDeclarativeInspectorService::objectDeletionRequested(QObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void QmlJSDebugger::QDeclarativeInspectorService::animationSpeedChangeRequested(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void QmlJSDebugger::QDeclarativeInspectorService::executionPauseChangeRequested(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void QmlJSDebugger::QDeclarativeInspectorService::clearComponentCacheRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 16, 0);
}
QT_END_MOC_NAMESPACE
