/****************************************************************************
** Meta object code from reading C++ file 'color_preview.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Qt-Color-Picker-master/src/color_preview.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'color_preview.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Color_Preview_t {
    QByteArrayData data[13];
    char stringdata[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Color_Preview_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Color_Preview_t qt_meta_stringdata_Color_Preview = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 7),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 12),
QT_MOC_LITERAL(4, 36, 8),
QT_MOC_LITERAL(5, 45, 1),
QT_MOC_LITERAL(6, 47, 5),
QT_MOC_LITERAL(7, 53, 10),
QT_MOC_LITERAL(8, 64, 10),
QT_MOC_LITERAL(9, 75, 10),
QT_MOC_LITERAL(10, 86, 7),
QT_MOC_LITERAL(11, 94, 10),
QT_MOC_LITERAL(12, 105, 8)
    },
    "Color_Preview\0clicked\0\0colorChanged\0"
    "setColor\0c\0color\0alpha_mode\0Alpha_Mode\0"
    "background\0NoAlpha\0SplitAlpha\0AllAlpha\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Color_Preview[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   36, // properties
       1,   48, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x05,
       3,    1,   30,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    1,   33,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    5,

 // properties: name, type, flags
       6, QMetaType::QColor, 0x00495103,
       7, 0x80000000 | 8, 0x0009500b,
       9, QMetaType::QBrush, 0x00095103,

 // properties: notify_signal_id
       1,
       0,
       0,

 // enums: name, flags, count, data
       8, 0x0,    3,   52,

 // enum data: key, value
      10, uint(Color_Preview::NoAlpha),
      11, uint(Color_Preview::SplitAlpha),
      12, uint(Color_Preview::AllAlpha),

       0        // eod
};

void Color_Preview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Color_Preview *_t = static_cast<Color_Preview *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->colorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: _t->setColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Color_Preview::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Color_Preview::clicked)) {
                *result = 0;
            }
        }
        {
            typedef void (Color_Preview::*_t)(QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Color_Preview::colorChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Color_Preview::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Color_Preview.data,
      qt_meta_data_Color_Preview,  qt_static_metacall, 0, 0}
};


const QMetaObject *Color_Preview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Color_Preview::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Color_Preview.stringdata))
        return static_cast<void*>(const_cast< Color_Preview*>(this));
    return QWidget::qt_metacast(_clname);
}

int Color_Preview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = color(); break;
        case 1: *reinterpret_cast< Alpha_Mode*>(_v) = alphaMode(); break;
        case 2: *reinterpret_cast< QBrush*>(_v) = getBackground(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: setAlphaMode(*reinterpret_cast< Alpha_Mode*>(_v)); break;
        case 2: setBackground(*reinterpret_cast< QBrush*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Color_Preview::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Color_Preview::colorChanged(QColor _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
