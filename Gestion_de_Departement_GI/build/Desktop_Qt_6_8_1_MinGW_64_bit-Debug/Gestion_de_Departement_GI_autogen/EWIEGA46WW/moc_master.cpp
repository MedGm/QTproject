/****************************************************************************
** Meta object code from reading C++ file 'master.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../master.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'master.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN6MasterE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN6MasterE = QtMocHelpers::stringData(
    "Master",
    "addStudent",
    "",
    "delStudent",
    "AjouterStage",
    "updateStudent",
    "deleteStudent",
    "showSchedule",
    "showStudents",
    "showStage",
    "onComboBoxChanged"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN6MasterE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    0,   73,    2, 0x08,    6 /* Private */,
       8,    0,   74,    2, 0x08,    7 /* Private */,
       9,    0,   75,    2, 0x08,    8 /* Private */,
      10,    0,   76,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Master::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN6MasterE.offsetsAndSizes,
    qt_meta_data_ZN6MasterE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN6MasterE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Master, std::true_type>,
        // method 'addStudent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'delStudent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'AjouterStage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateStudent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteStudent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showSchedule'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showStudents'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showStage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onComboBoxChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Master::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Master *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addStudent(); break;
        case 1: _t->delStudent(); break;
        case 2: _t->AjouterStage(); break;
        case 3: _t->updateStudent(); break;
        case 4: _t->deleteStudent(); break;
        case 5: _t->showSchedule(); break;
        case 6: _t->showStudents(); break;
        case 7: _t->showStage(); break;
        case 8: _t->onComboBoxChanged(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Master::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Master::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN6MasterE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Master::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
