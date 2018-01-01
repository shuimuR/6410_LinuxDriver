/****************************************************************************
** Meta object code from reading C++ file 'qmlruntime.h'
**
** Created: Tue Oct 11 11:35:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qmlruntime.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmlruntime.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDeclarativeViewer[] = {

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

 // slots: signature, parameters, type, tag, flags
      26,   20,   19,   19, 0x0a,
      59,   54,   19,   19, 0x0a,
      84,   19,   79,   19, 0x0a,
      98,   19,   19,   19, 0x0a,
     109,   19,   19,   19, 0x0a,
     119,   19,   19,   19, 0x0a,
     128,   19,   19,   19, 0x0a,
     143,   19,   19,   19, 0x0a,
     161,   19,   19,   19, 0x0a,
     197,  192,   19,   19, 0x0a,
     217,   19,   19,   19, 0x0a,
     237,   19,   19,   19, 0x0a,
     260,   19,   19,   19, 0x0a,
     280,   19,   19,   19, 0x0a,
     296,   19,   19,   19, 0x0a,
     314,   19,   19,   19, 0x0a,
     331,   19,   19,   19, 0x0a,
     350,   19,   19,   19, 0x0a,
     373,   19,   19,   19, 0x0a,
     389,   19,   19,   19, 0x08,
     406,   19,   19,   19, 0x08,
     427,   19,   19,   19, 0x08,
     447,   19,   19,   19, 0x08,
     461,   19,   19,   19, 0x08,
     486,   19,   19,   19, 0x08,
     506,   19,   19,   19, 0x08,
     525,   19,   19,   19, 0x08,
     553,   19,   19,   19, 0x08,
     581,  574,   19,   19, 0x08,
     615,  610,   19,   19, 0x08,
     634,   19,   19,   19, 0x08,
     657,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDeclarativeViewer[] = {
    "QDeclarativeViewer\0\0value\0"
    "setDesignModeBehavior(bool)\0size\0"
    "sceneResized(QSize)\0bool\0open(QString)\0"
    "openFile()\0openUrl()\0reload()\0"
    "takeSnapShot()\0toggleRecording()\0"
    "toggleRecordingWithSelection()\0code\0"
    "ffmpegFinished(int)\0showProxySettings()\0"
    "proxySettingsChanged()\0rotateOrientation()\0"
    "statusChanged()\0pauseAnimations()\0"
    "stepAnimations()\0setAnimationStep()\0"
    "changeAnimationSpeed()\0launch(QString)\0"
    "appAboutToQuit()\0autoStartRecording()\0"
    "autoStopRecording()\0recordFrame()\0"
    "chooseRecordingOptions()\0pickRecordingFile()\0"
    "toggleFullScreen()\0changeOrientation(QAction*)\0"
    "orientationChanged()\0factor\0"
    "animationSpeedChanged(qreal)\0show\0"
    "showWarnings(bool)\0warningsWidgetOpened()\0"
    "warningsWidgetClosed()\0"
};

const QMetaObject QDeclarativeViewer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QDeclarativeViewer,
      qt_meta_data_QDeclarativeViewer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDeclarativeViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDeclarativeViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDeclarativeViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDeclarativeViewer))
        return static_cast<void*>(const_cast< QDeclarativeViewer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QDeclarativeViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setDesignModeBehavior((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: sceneResized((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 2: { bool _r = open((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: openFile(); break;
        case 4: openUrl(); break;
        case 5: reload(); break;
        case 6: takeSnapShot(); break;
        case 7: toggleRecording(); break;
        case 8: toggleRecordingWithSelection(); break;
        case 9: ffmpegFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: showProxySettings(); break;
        case 11: proxySettingsChanged(); break;
        case 12: rotateOrientation(); break;
        case 13: statusChanged(); break;
        case 14: pauseAnimations(); break;
        case 15: stepAnimations(); break;
        case 16: setAnimationStep(); break;
        case 17: changeAnimationSpeed(); break;
        case 18: launch((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: appAboutToQuit(); break;
        case 20: autoStartRecording(); break;
        case 21: autoStopRecording(); break;
        case 22: recordFrame(); break;
        case 23: chooseRecordingOptions(); break;
        case 24: pickRecordingFile(); break;
        case 25: toggleFullScreen(); break;
        case 26: changeOrientation((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 27: orientationChanged(); break;
        case 28: animationSpeedChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 29: showWarnings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: warningsWidgetOpened(); break;
        case 31: warningsWidgetClosed(); break;
        default: ;
        }
        _id -= 32;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
