/****************************************************************************
** Meta object code from reading C++ file 'mazegui.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Maze_GUI/mazegui.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mazegui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MazeGUI_t {
    const uint offsetsAndSize[14];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MazeGUI_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MazeGUI_t qt_meta_stringdata_MazeGUI = {
    {
QT_MOC_LITERAL(0, 7), // "MazeGUI"
QT_MOC_LITERAL(8, 18), // "generatebtnPressed"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 15), // "clearbtnPressed"
QT_MOC_LITERAL(44, 13), // "DFSbtnPressed"
QT_MOC_LITERAL(58, 13), // "BFSbtnPressed"
QT_MOC_LITERAL(72, 14) // "nextbtnPressed"

    },
    "MazeGUI\0generatebtnPressed\0\0clearbtnPressed\0"
    "DFSbtnPressed\0BFSbtnPressed\0nextbtnPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MazeGUI[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    0 /* Private */,
       3,    0,   45,    2, 0x08,    1 /* Private */,
       4,    0,   46,    2, 0x08,    2 /* Private */,
       5,    0,   47,    2, 0x08,    3 /* Private */,
       6,    0,   48,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MazeGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MazeGUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->generatebtnPressed(); break;
        case 1: _t->clearbtnPressed(); break;
        case 2: _t->DFSbtnPressed(); break;
        case 3: _t->BFSbtnPressed(); break;
        case 4: _t->nextbtnPressed(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject MazeGUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MazeGUI.offsetsAndSize,
    qt_meta_data_MazeGUI,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MazeGUI_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MazeGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MazeGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MazeGUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MazeGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
