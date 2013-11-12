/****************************************************************************
** Meta object code from reading C++ file 'gradient_slider.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Qt-Color-Picker-master/src/gradient_slider.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gradient_slider.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Gradient_Slider_t {
    QByteArrayData data[8];
    char stringdata[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Gradient_Slider_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Gradient_Slider_t qt_meta_stringdata_Gradient_Slider = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 10),
QT_MOC_LITERAL(2, 27, 6),
QT_MOC_LITERAL(3, 34, 15),
QT_MOC_LITERAL(4, 50, 8),
QT_MOC_LITERAL(5, 59, 15),
QT_MOC_LITERAL(6, 75, 10),
QT_MOC_LITERAL(7, 86, 9)
    },
    "Gradient_Slider\0background\0colors\0"
    "QVector<QColor>\0gradient\0QLinearGradient\0"
    "firstColor\0lastColor\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gradient_Slider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QBrush, 0x00095103,
       2, 0x80000000 | 3, 0x0009510b,
       4, 0x80000000 | 5, 0x0008510b,
       6, QMetaType::QColor, 0x00085103,
       7, QMetaType::QColor, 0x00085103,

       0        // eod
};

void Gradient_Slider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QColor> >(); break;
        }
    }

    Q_UNUSED(_o);
}

const QMetaObject Gradient_Slider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_Gradient_Slider.data,
      qt_meta_data_Gradient_Slider,  qt_static_metacall, 0, 0}
};


const QMetaObject *Gradient_Slider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gradient_Slider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gradient_Slider.stringdata))
        return static_cast<void*>(const_cast< Gradient_Slider*>(this));
    return QSlider::qt_metacast(_clname);
}

int Gradient_Slider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QBrush*>(_v) = background(); break;
        case 1: *reinterpret_cast< QVector<QColor>*>(_v) = colors(); break;
        case 2: *reinterpret_cast< QLinearGradient*>(_v) = gradient(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = firstColor(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = lastColor(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setBackground(*reinterpret_cast< QBrush*>(_v)); break;
        case 1: setColors(*reinterpret_cast< QVector<QColor>*>(_v)); break;
        case 2: setGradient(*reinterpret_cast< QLinearGradient*>(_v)); break;
        case 3: setFirstColor(*reinterpret_cast< QColor*>(_v)); break;
        case 4: setLastColor(*reinterpret_cast< QColor*>(_v)); break;
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
