/****************************************************************************
** Meta object code from reading C++ file 'color_wheel.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Qt-Color-Picker-master/src/color_wheel.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'color_wheel.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Color_Wheel_t {
    QByteArrayData data[17];
    char stringdata[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Color_Wheel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Color_Wheel_t qt_meta_stringdata_Color_Wheel = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 12),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 13),
QT_MOC_LITERAL(4, 40, 8),
QT_MOC_LITERAL(5, 49, 1),
QT_MOC_LITERAL(6, 51, 6),
QT_MOC_LITERAL(7, 58, 1),
QT_MOC_LITERAL(8, 60, 13),
QT_MOC_LITERAL(9, 74, 1),
QT_MOC_LITERAL(10, 76, 8),
QT_MOC_LITERAL(11, 85, 1),
QT_MOC_LITERAL(12, 87, 5),
QT_MOC_LITERAL(13, 93, 3),
QT_MOC_LITERAL(14, 97, 10),
QT_MOC_LITERAL(15, 108, 5),
QT_MOC_LITERAL(16, 114, 10)
    },
    "Color_Wheel\0colorChanged\0\0colorSelected\0"
    "setColor\0c\0setHue\0h\0setSaturation\0s\0"
    "setValue\0v\0color\0hue\0saturation\0value\0"
    "wheelWidth\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Color_Wheel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       5,   62, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x05,
       3,    1,   47,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    1,   50,    2, 0x0a,
       6,    1,   53,    2, 0x0a,
       8,    1,   56,    2, 0x0a,
      10,    1,   59,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, QMetaType::QColor,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    5,
    QMetaType::Void, QMetaType::QReal,    7,
    QMetaType::Void, QMetaType::QReal,    9,
    QMetaType::Void, QMetaType::QReal,   11,

 // properties: name, type, flags
      12, QMetaType::QColor, 0x00485103,
      13, QMetaType::QReal, 0x00094103,
      14, QMetaType::QReal, 0x00094103,
      15, QMetaType::QReal, 0x00094103,
      16, QMetaType::UInt, 0x00095103,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,

       0        // eod
};

void Color_Wheel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Color_Wheel *_t = static_cast<Color_Wheel *>(_o);
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->colorSelected((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: _t->setColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 3: _t->setHue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 4: _t->setSaturation((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 5: _t->setValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Color_Wheel::*_t)(QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Color_Wheel::colorChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (Color_Wheel::*_t)(QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Color_Wheel::colorSelected)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Color_Wheel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Color_Wheel.data,
      qt_meta_data_Color_Wheel,  qt_static_metacall, 0, 0}
};


const QMetaObject *Color_Wheel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Color_Wheel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Color_Wheel.stringdata))
        return static_cast<void*>(const_cast< Color_Wheel*>(this));
    return QWidget::qt_metacast(_clname);
}

int Color_Wheel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = color(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = hue(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = saturation(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = value(); break;
        case 4: *reinterpret_cast< uint*>(_v) = wheelWidth(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: setHue(*reinterpret_cast< qreal*>(_v)); break;
        case 2: setSaturation(*reinterpret_cast< qreal*>(_v)); break;
        case 3: setValue(*reinterpret_cast< qreal*>(_v)); break;
        case 4: setWheelWidth(*reinterpret_cast< uint*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Color_Wheel::colorChanged(QColor _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Color_Wheel::colorSelected(QColor _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
