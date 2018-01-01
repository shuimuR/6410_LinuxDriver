/****************************************************************************
** Meta object code from reading C++ file 'qdeclarativeviewinspector_p.h'
**
** Created: Tue Oct 11 11:35:35 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qdeclarativeviewinspector_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdeclarativeviewinspector_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QmlJSDebugger__QDeclarativeViewInspectorPrivate[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      57,   49,   48,   48, 0x0a,
      84,   48,   48,   48, 0x0a,
     107,  100,   48,   48, 0x0a,
     160,  152,   48,   48, 0x0a,
     204,   48,   48,   48, 0x0a,
     266,  232,   48,   48, 0x0a,
     355,  327,   48,   48, 0x2a,
     431,  412,   48,   48, 0x2a,
     482,  480,   48,   48, 0x0a,
     522,   48,   48,   48, 0x0a,
     551,   48,   48,   48, 0x0a,
     581,   48,   48,   48, 0x0a,
     612,   48,   48,   48, 0x0a,
     634,   48,   48,   48, 0x0a,
     663,   48,   48,   48, 0x0a,
     688,   48,   48,   48, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QmlJSDebugger__QDeclarativeViewInspectorPrivate[] = {
    "QmlJSDebugger::QDeclarativeViewInspectorPrivate\0"
    "\0visible\0_q_setToolBoxVisible(bool)\0"
    "_q_reloadView()\0status\0"
    "_q_onStatusChanged(QDeclarativeView::Status)\0"
    "objects\0_q_onCurrentObjectsChanged(QList<QObject*>)\0"
    "_q_applyChangesFromClient()\0"
    "qml,parent,imports,filename,order\0"
    "_q_createQmlObject(QString,QObject*,QStringList,QString,int)\0"
    "qml,parent,imports,filename\0"
    "_q_createQmlObject(QString,QObject*,QStringList,QString)\0"
    "qml,parent,imports\0"
    "_q_createQmlObject(QString,QObject*,QStringList)\0"
    ",\0_q_reparentQmlObject(QObject*,QObject*)\0"
    "_q_deleteQmlObject(QObject*)\0"
    "_q_changeToSingleSelectTool()\0"
    "_q_changeToMarqueeSelectTool()\0"
    "_q_changeToZoomTool()\0"
    "_q_changeToColorPickerTool()\0"
    "_q_clearComponentCache()\0"
    "_q_removeFromSelection(QObject*)\0"
};

const QMetaObject QmlJSDebugger::QDeclarativeViewInspectorPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QmlJSDebugger__QDeclarativeViewInspectorPrivate,
      qt_meta_data_QmlJSDebugger__QDeclarativeViewInspectorPrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QmlJSDebugger::QDeclarativeViewInspectorPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QmlJSDebugger::QDeclarativeViewInspectorPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QmlJSDebugger::QDeclarativeViewInspectorPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QmlJSDebugger__QDeclarativeViewInspectorPrivate))
        return static_cast<void*>(const_cast< QDeclarativeViewInspectorPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QmlJSDebugger::QDeclarativeViewInspectorPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _q_setToolBoxVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _q_reloadView(); break;
        case 2: _q_onStatusChanged((*reinterpret_cast< QDeclarativeView::Status(*)>(_a[1]))); break;
        case 3: _q_onCurrentObjectsChanged((*reinterpret_cast< QList<QObject*>(*)>(_a[1]))); break;
        case 4: _q_applyChangesFromClient(); break;
        case 5: _q_createQmlObject((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 6: _q_createQmlObject((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 7: _q_createQmlObject((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3]))); break;
        case 8: _q_reparentQmlObject((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 9: _q_deleteQmlObject((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 10: _q_changeToSingleSelectTool(); break;
        case 11: _q_changeToMarqueeSelectTool(); break;
        case 12: _q_changeToZoomTool(); break;
        case 13: _q_changeToColorPickerTool(); break;
        case 14: _q_clearComponentCache(); break;
        case 15: _q_removeFromSelection((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
