/****************************************************************************
** Meta object code from reading C++ file 'STCalendarWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../STCalendarWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'STCalendarWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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
struct qt_meta_stringdata_CLASSSTCalendarWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSTCalendarWidgetENDCLASS = QtMocHelpers::stringData(
    "STCalendarWidget",
    "DateSelectSignal",
    "",
    "date",
    "HaveDateSelect",
    "JumpLastYear",
    "JumpLastMonth",
    "JumpNextMonth",
    "JumpNextYear",
    "SetDate"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSTCalendarWidgetENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[17];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[15];
    char stringdata5[13];
    char stringdata6[14];
    char stringdata7[14];
    char stringdata8[13];
    char stringdata9[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSTCalendarWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSTCalendarWidgetENDCLASS_t qt_meta_stringdata_CLASSSTCalendarWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 16),  // "STCalendarWidget"
        QT_MOC_LITERAL(17, 16),  // "DateSelectSignal"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 4),  // "date"
        QT_MOC_LITERAL(40, 14),  // "HaveDateSelect"
        QT_MOC_LITERAL(55, 12),  // "JumpLastYear"
        QT_MOC_LITERAL(68, 13),  // "JumpLastMonth"
        QT_MOC_LITERAL(82, 13),  // "JumpNextMonth"
        QT_MOC_LITERAL(96, 12),  // "JumpNextYear"
        QT_MOC_LITERAL(109, 7)   // "SetDate"
    },
    "STCalendarWidget",
    "DateSelectSignal",
    "",
    "date",
    "HaveDateSelect",
    "JumpLastYear",
    "JumpLastMonth",
    "JumpNextMonth",
    "JumpNextYear",
    "SetDate"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSTCalendarWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   59,    2, 0x0a,    3 /* Public */,
       5,    0,   62,    2, 0x0a,    5 /* Public */,
       6,    0,   63,    2, 0x0a,    6 /* Public */,
       7,    0,   64,    2, 0x0a,    7 /* Public */,
       8,    0,   65,    2, 0x0a,    8 /* Public */,
       9,    0,   66,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QDate,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QDate,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject STCalendarWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSSTCalendarWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSTCalendarWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSTCalendarWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<STCalendarWidget, std::true_type>,
        // method 'DateSelectSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QDate, std::false_type>,
        // method 'HaveDateSelect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QDate, std::false_type>,
        // method 'JumpLastYear'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'JumpLastMonth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'JumpNextMonth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'JumpNextYear'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SetDate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void STCalendarWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<STCalendarWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->DateSelectSignal((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 1: _t->HaveDateSelect((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 2: _t->JumpLastYear(); break;
        case 3: _t->JumpLastMonth(); break;
        case 4: _t->JumpNextMonth(); break;
        case 5: _t->JumpNextYear(); break;
        case 6: _t->SetDate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (STCalendarWidget::*)(QDate );
            if (_t _q_method = &STCalendarWidget::DateSelectSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *STCalendarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *STCalendarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSTCalendarWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int STCalendarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void STCalendarWidget::DateSelectSignal(QDate _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
