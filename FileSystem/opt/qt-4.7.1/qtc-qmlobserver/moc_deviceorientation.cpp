/****************************************************************************
** Meta object code from reading C++ file 'deviceorientation.h'
**
** Created: Tue Oct 11 11:35:48 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "deviceorientation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deviceorientation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DeviceOrientation[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       1,   19, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // enums: name, flags, count, data
      40, 0x0,    5,   23,

 // enum data: key, value
      52, uint(DeviceOrientation::UnknownOrientation),
      71, uint(DeviceOrientation::Portrait),
      80, uint(DeviceOrientation::Landscape),
      90, uint(DeviceOrientation::PortraitInverted),
     107, uint(DeviceOrientation::LandscapeInverted),

       0        // eod
};

static const char qt_meta_stringdata_DeviceOrientation[] = {
    "DeviceOrientation\0\0orientationChanged()\0"
    "Orientation\0UnknownOrientation\0Portrait\0"
    "Landscape\0PortraitInverted\0LandscapeInverted\0"
};

const QMetaObject DeviceOrientation::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DeviceOrientation,
      qt_meta_data_DeviceOrientation, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DeviceOrientation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DeviceOrientation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DeviceOrientation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceOrientation))
        return static_cast<void*>(const_cast< DeviceOrientation*>(this));
    return QObject::qt_metacast(_clname);
}

int DeviceOrientation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: orientationChanged(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void DeviceOrientation::orientationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
