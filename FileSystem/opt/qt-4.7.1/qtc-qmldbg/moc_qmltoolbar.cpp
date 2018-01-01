/****************************************************************************
** Meta object code from reading C++ file 'qmltoolbar.h'
**
** Created: Tue Oct 11 11:35:34 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "editor/qmltoolbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmltoolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QmlJSDebugger__QmlToolBar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   27,   26,   26, 0x05,
      70,   63,   26,   26, 0x05,
     112,   99,   26,   26, 0x05,
     144,   26,   26,   26, 0x05,
     166,   26,   26,   26, 0x05,
     187,   26,   26,   26, 0x05,
     215,   26,   26,   26, 0x05,
     234,   26,   26,   26, 0x05,
     266,   26,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
     300,   99,   26,   26, 0x0a,
     334,  328,   26,   26, 0x0a,
     359,   26,   26,   26, 0x0a,
     381,   26,   26,   26, 0x0a,
     402,   26,   26,   26, 0x0a,
     430,   26,   26,   26, 0x0a,
     460,  445,   26,   26, 0x0a,
     485,   63,   26,   26, 0x0a,
     510,   99,   26,   26, 0x08,
     545,   26,   26,   26, 0x08,
     567,   26,   26,   26, 0x08,
     596,   26,   26,   26, 0x08,
     624,   26,   26,   26, 0x08,
     659,   26,   26,   26, 0x08,
     681,   26,   26,   26, 0x08,
     699,   26,   26,   26, 0x08,
     715,   26,   26,   26, 0x08,
     738,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QmlJSDebugger__QmlToolBar[] = {
    "QmlJSDebugger::QmlToolBar\0\0factor\0"
    "animationSpeedChanged(qreal)\0paused\0"
    "animationPausedChanged(bool)\0inDesignMode\0"
    "designModeBehaviorChanged(bool)\0"
    "colorPickerSelected()\0selectToolSelected()\0"
    "marqueeSelectToolSelected()\0"
    "zoomToolSelected()\0applyChangesToQmlFileSelected()\0"
    "applyChangesFromQmlFileSelected()\0"
    "setDesignModeBehavior(bool)\0color\0"
    "setColorBoxColor(QColor)\0activateColorPicker()\0"
    "activateSelectTool()\0activateMarqueeSelectTool()\0"
    "activateZoom()\0slowDownFactor\0"
    "setAnimationSpeed(qreal)\0"
    "setAnimationPaused(bool)\0"
    "setDesignModeBehaviorOnClick(bool)\0"
    "activatePlayOnClick()\0"
    "activateColorPickerOnClick()\0"
    "activateSelectToolOnClick()\0"
    "activateMarqueeSelectToolOnClick()\0"
    "activateZoomOnClick()\0activateFromQml()\0"
    "activateToQml()\0changeAnimationSpeed()\0"
    "updatePlayAction()\0"
};

const QMetaObject QmlJSDebugger::QmlToolBar::staticMetaObject = {
    { &QToolBar::staticMetaObject, qt_meta_stringdata_QmlJSDebugger__QmlToolBar,
      qt_meta_data_QmlJSDebugger__QmlToolBar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QmlJSDebugger::QmlToolBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QmlJSDebugger::QmlToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QmlJSDebugger::QmlToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QmlJSDebugger__QmlToolBar))
        return static_cast<void*>(const_cast< QmlToolBar*>(this));
    return QToolBar::qt_metacast(_clname);
}

int QmlJSDebugger::QmlToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: animationSpeedChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: animationPausedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: designModeBehaviorChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: colorPickerSelected(); break;
        case 4: selectToolSelected(); break;
        case 5: marqueeSelectToolSelected(); break;
        case 6: zoomToolSelected(); break;
        case 7: applyChangesToQmlFileSelected(); break;
        case 8: applyChangesFromQmlFileSelected(); break;
        case 9: setDesignModeBehavior((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: setColorBoxColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 11: activateColorPicker(); break;
        case 12: activateSelectTool(); break;
        case 13: activateMarqueeSelectTool(); break;
        case 14: activateZoom(); break;
        case 15: setAnimationSpeed((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 16: setAnimationPaused((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: setDesignModeBehaviorOnClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: activatePlayOnClick(); break;
        case 19: activateColorPickerOnClick(); break;
        case 20: activateSelectToolOnClick(); break;
        case 21: activateMarqueeSelectToolOnClick(); break;
        case 22: activateZoomOnClick(); break;
        case 23: activateFromQml(); break;
        case 24: activateToQml(); break;
        case 25: changeAnimationSpeed(); break;
        case 26: updatePlayAction(); break;
        default: ;
        }
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void QmlJSDebugger::QmlToolBar::animationSpeedChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QmlJSDebugger::QmlToolBar::animationPausedChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QmlJSDebugger::QmlToolBar::designModeBehaviorChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QmlJSDebugger::QmlToolBar::colorPickerSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QmlJSDebugger::QmlToolBar::selectToolSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QmlJSDebugger::QmlToolBar::marqueeSelectToolSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void QmlJSDebugger::QmlToolBar::zoomToolSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void QmlJSDebugger::QmlToolBar::applyChangesToQmlFileSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void QmlJSDebugger::QmlToolBar::applyChangesFromQmlFileSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
