/****************************************************************************
** Meta object code from reading C++ file 'color_selector.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Qt-Color-Picker-master/src/color_selector.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'color_selector.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Color_Selector_t {
    QByteArrayData data[13];
    char stringdata[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Color_Selector_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Color_Selector_t qt_meta_stringdata_Color_Selector = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 10),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 13),
QT_MOC_LITERAL(4, 41, 13),
QT_MOC_LITERAL(5, 55, 16),
QT_MOC_LITERAL(6, 72, 1),
QT_MOC_LITERAL(7, 74, 10),
QT_MOC_LITERAL(8, 85, 11),
QT_MOC_LITERAL(9, 97, 14),
QT_MOC_LITERAL(10, 112, 18),
QT_MOC_LITERAL(11, 131, 7),
QT_MOC_LITERAL(12, 139, 10)
    },
    "Color_Selector\0showDialog\0\0accept_dialog\0"
    "reject_dialog\0update_old_color\0c\0"
    "updateMode\0Update_Mode\0dialogModality\0"
    "Qt::WindowModality\0Confirm\0Continuous\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Color_Selector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   40, // properties
       1,   46, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a,
       3,    0,   35,    2, 0x08,
       4,    0,   36,    2, 0x08,
       5,    1,   37,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    6,

 // properties: name, type, flags
       7, 0x80000000 | 8, 0x0009510b,
       9, 0x80000000 | 10, 0x0009510b,

 // enums: name, flags, count, data
       8, 0x0,    2,   50,

 // enum data: key, value
      11, uint(Color_Selector::Confirm),
      12, uint(Color_Selector::Continuous),

       0        // eod
};

void Color_Selector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Color_Selector *_t = static_cast<Color_Selector *>(_o);
        switch (_id) {
        case 0: _t->showDialog(); break;
        case 1: _t->accept_dialog(); break;
        case 2: _t->reject_dialog(); break;
        case 3: _t->update_old_color((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Color_Selector::staticMetaObject = {
    { &Color_Preview::staticMetaObject, qt_meta_stringdata_Color_Selector.data,
      qt_meta_data_Color_Selector,  qt_static_metacall, 0, 0}
};


const QMetaObject *Color_Selector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Color_Selector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Color_Selector.stringdata))
        return static_cast<void*>(const_cast< Color_Selector*>(this));
    return Color_Preview::qt_metacast(_clname);
}

int Color_Selector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Color_Preview::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Update_Mode*>(_v) = updateMode(); break;
        case 1: *reinterpret_cast< Qt::WindowModality*>(_v) = dialogModality(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setUpdateMode(*reinterpret_cast< Update_Mode*>(_v)); break;
        case 1: setDialogModality(*reinterpret_cast< Qt::WindowModality*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
