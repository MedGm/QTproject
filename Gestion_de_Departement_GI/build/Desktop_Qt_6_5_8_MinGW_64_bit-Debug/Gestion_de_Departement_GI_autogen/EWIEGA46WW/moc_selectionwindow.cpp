/****************************************************************************
** Meta object code from reading C++ file 'selectionwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../selectionwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectionwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSelectionWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSSelectionWindowENDCLASS = QtMocHelpers::stringData(
    "SelectionWindow",
    "onEngineerButtonClicked",
    "",
    "onLicenceButtonClicked",
    "onMasterButtonClicked",
    "onProfessorsButtonClicked",
    "onDemandsButtonClicked",
    "onReservationsButtonClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSelectionWindowENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[16];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[23];
    char stringdata4[22];
    char stringdata5[26];
    char stringdata6[23];
    char stringdata7[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSelectionWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSelectionWindowENDCLASS_t qt_meta_stringdata_CLASSSelectionWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "SelectionWindow"
        QT_MOC_LITERAL(16, 23),  // "onEngineerButtonClicked"
        QT_MOC_LITERAL(40, 0),  // ""
        QT_MOC_LITERAL(41, 22),  // "onLicenceButtonClicked"
        QT_MOC_LITERAL(64, 21),  // "onMasterButtonClicked"
        QT_MOC_LITERAL(86, 25),  // "onProfessorsButtonClicked"
        QT_MOC_LITERAL(112, 22),  // "onDemandsButtonClicked"
        QT_MOC_LITERAL(135, 27)   // "onReservationsButtonClicked"
    },
    "SelectionWindow",
    "onEngineerButtonClicked",
    "",
    "onLicenceButtonClicked",
    "onMasterButtonClicked",
    "onProfessorsButtonClicked",
    "onDemandsButtonClicked",
    "onReservationsButtonClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSelectionWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SelectionWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSSelectionWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSelectionWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSelectionWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SelectionWindow, std::true_type>,
        // method 'onEngineerButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLicenceButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMasterButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onProfessorsButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDemandsButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReservationsButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SelectionWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectionWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onEngineerButtonClicked(); break;
        case 1: _t->onLicenceButtonClicked(); break;
        case 2: _t->onMasterButtonClicked(); break;
        case 3: _t->onProfessorsButtonClicked(); break;
        case 4: _t->onDemandsButtonClicked(); break;
        case 5: _t->onReservationsButtonClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *SelectionWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectionWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSelectionWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SelectionWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
