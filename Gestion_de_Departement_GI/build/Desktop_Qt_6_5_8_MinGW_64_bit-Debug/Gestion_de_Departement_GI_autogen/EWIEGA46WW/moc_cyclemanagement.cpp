/****************************************************************************
** Meta object code from reading C++ file 'cyclemanagement.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../cyclemanagement.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cyclemanagement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.8. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASScyclemanagementENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASScyclemanagementENDCLASS = QtMocHelpers::stringData(
    "cyclemanagement",
    "onLevelChanged",
    "",
    "index",
    "onLogoutClicked",
    "onAddStudentClicked",
    "onDeleteStudentClicked",
    "onScheduleButtonClicked",
    "showSchedule",
    "niveau",
    "onStudentsButtonClicked",
    "onInternshipsButtonClicked",
    "onAddInternshipClicked",
    "onDeleteInternshipClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASScyclemanagementENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[16];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[16];
    char stringdata5[20];
    char stringdata6[23];
    char stringdata7[24];
    char stringdata8[13];
    char stringdata9[7];
    char stringdata10[24];
    char stringdata11[27];
    char stringdata12[23];
    char stringdata13[26];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASScyclemanagementENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASScyclemanagementENDCLASS_t qt_meta_stringdata_CLASScyclemanagementENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "cyclemanagement"
        QT_MOC_LITERAL(16, 14),  // "onLevelChanged"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 5),  // "index"
        QT_MOC_LITERAL(38, 15),  // "onLogoutClicked"
        QT_MOC_LITERAL(54, 19),  // "onAddStudentClicked"
        QT_MOC_LITERAL(74, 22),  // "onDeleteStudentClicked"
        QT_MOC_LITERAL(97, 23),  // "onScheduleButtonClicked"
        QT_MOC_LITERAL(121, 12),  // "showSchedule"
        QT_MOC_LITERAL(134, 6),  // "niveau"
        QT_MOC_LITERAL(141, 23),  // "onStudentsButtonClicked"
        QT_MOC_LITERAL(165, 26),  // "onInternshipsButtonClicked"
        QT_MOC_LITERAL(192, 22),  // "onAddInternshipClicked"
        QT_MOC_LITERAL(215, 25)   // "onDeleteInternshipClicked"
    },
    "cyclemanagement",
    "onLevelChanged",
    "",
    "index",
    "onLogoutClicked",
    "onAddStudentClicked",
    "onDeleteStudentClicked",
    "onScheduleButtonClicked",
    "showSchedule",
    "niveau",
    "onStudentsButtonClicked",
    "onInternshipsButtonClicked",
    "onAddInternshipClicked",
    "onDeleteInternshipClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASScyclemanagementENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x08,    1 /* Private */,
       4,    0,   77,    2, 0x08,    3 /* Private */,
       5,    0,   78,    2, 0x08,    4 /* Private */,
       6,    0,   79,    2, 0x08,    5 /* Private */,
       7,    0,   80,    2, 0x08,    6 /* Private */,
       8,    1,   81,    2, 0x08,    7 /* Private */,
      10,    0,   84,    2, 0x08,    9 /* Private */,
      11,    0,   85,    2, 0x08,   10 /* Private */,
      12,    0,   86,    2, 0x08,   11 /* Private */,
      13,    0,   87,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject cyclemanagement::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASScyclemanagementENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASScyclemanagementENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASScyclemanagementENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<cyclemanagement, std::true_type>,
        // method 'onLevelChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onLogoutClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddStudentClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteStudentClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onScheduleButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showSchedule'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onStudentsButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onInternshipsButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddInternshipClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteInternshipClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void cyclemanagement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<cyclemanagement *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onLevelChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->onLogoutClicked(); break;
        case 2: _t->onAddStudentClicked(); break;
        case 3: _t->onDeleteStudentClicked(); break;
        case 4: _t->onScheduleButtonClicked(); break;
        case 5: _t->showSchedule((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->onStudentsButtonClicked(); break;
        case 7: _t->onInternshipsButtonClicked(); break;
        case 8: _t->onAddInternshipClicked(); break;
        case 9: _t->onDeleteInternshipClicked(); break;
        default: ;
        }
    }
}

const QMetaObject *cyclemanagement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cyclemanagement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASScyclemanagementENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int cyclemanagement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
