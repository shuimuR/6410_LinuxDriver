/****************************************************************************
** Meta object code from reading C++ file 'qdeclarativeviewinspector.h'
**
** Created: Tue Oct 11 11:35:31 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/qdeclarativeviewinspector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdeclarativeviewinspector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QmlJSDebugger__QDeclarativeViewInspector[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      55,   42,   41,   41, 0x05,
     100,   87,   41,   41, 0x05,
     126,   41,   41,   41, 0x05,
     144,   41,   41,   41, 0x05,
     173,   41,   41,   41, 0x05,
     195,   41,   41,   41, 0x05,
     215,   41,   41,   41, 0x05,
     244,  238,   41,   41, 0x05,
     280,  273,   41,   41, 0x05,
     316,  309,   41,   41, 0x05,

 // slots: signature, parameters, type, tag, flags
     351,  345,   41,   41, 0x0a,
     384,   41,  379,   41, 0x0a,
     414,  405,   41,   41, 0x0a,
     436,  273,   41,   41, 0x0a,
     461,  309,   41,   41, 0x0a,
     486,  273,   41,   41, 0x08,
     523,  309,   41,   41, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QmlJSDebugger__QDeclarativeViewInspector[] = {
    "QmlJSDebugger::QDeclarativeViewInspector\0"
    "\0inDesignMode\0designModeBehaviorChanged(bool)\0"
    "showAppOnTop\0showAppOnTopChanged(bool)\0"
    "reloadRequested()\0marqueeSelectToolActivated()\0"
    "selectToolActivated()\0zoomToolActivated()\0"
    "colorPickerActivated()\0color\0"
    "selectedColorChanged(QColor)\0factor\0"
    "animationSpeedChanged(qreal)\0paused\0"
    "animationPausedChanged(bool)\0value\0"
    "setDesignModeBehavior(bool)\0bool\0"
    "designModeBehavior()\0appOnTop\0"
    "setShowAppOnTop(bool)\0setAnimationSpeed(qreal)\0"
    "setAnimationPaused(bool)\0"
    "animationSpeedChangeRequested(qreal)\0"
    "animationPausedChangeRequested(bool)\0"
};

const QMetaObject QmlJSDebugger::QDeclarativeViewInspector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QmlJSDebugger__QDeclarativeViewInspector,
      qt_meta_data_QmlJSDebugger__QDeclarativeViewInspector, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QmlJSDebugger::QDeclarativeViewInspector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QmlJSDebugger::QDeclarativeViewInspector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QmlJSDebugger::QDeclarativeViewInspector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QmlJSDebugger__QDeclarativeViewInspector))
        return static_cast<void*>(const_cast< QDeclarativeViewInspector*>(this));
    return QObject::qt_metacast(_clname);
}

int QmlJSDebugger::QDeclarativeViewInspector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: designModeBehaviorChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: showAppOnTopChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: reloadRequested(); break;
        case 3: marqueeSelectToolActivated(); break;
        case 4: selectToolActivated(); break;
        case 5: zoomToolActivated(); break;
        case 6: colorPickerActivated(); break;
        case 7: selectedColorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 8: animationSpeedChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 9: animationPausedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: setDesignModeBehavior((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: { bool _r = designModeBehavior();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: setShowAppOnTop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: setAnimationSpeed((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 14: setAnimationPaused((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: animationSpeedChangeRequested((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 16: animationPausedChangeRequested((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void QmlJSDebugger::QDeclarativeViewInspector::designModeBehaviorChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QmlJSDebugger::QDeclarativeViewInspector::showAppOnTopChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QmlJSDebugger::QDeclarativeViewInspector::reloadRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QmlJSDebugger::QDeclarativeViewInspector::marqueeSelectToolActivated()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QmlJSDebugger::QDeclarativeViewInspector::selectToolActivated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QmlJSDebugger::QDeclarativeViewInspector::zoomToolActivated()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void QmlJSDebugger::QDeclarativeViewInspector::colorPickerActivated()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void QmlJSDebugger::QDeclarativeViewInspector::selectedColorChanged(const QColor & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QmlJSDebugger::QDeclarativeViewInspector::animationSpeedChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QmlJSDebugger::QDeclarativeViewInspector::animationPausedChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
