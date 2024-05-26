/****************************************************************************
** Meta object code from reading C++ file 'chartwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../chartwidget.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chartwidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSChartWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSChartWidgetENDCLASS = QtMocHelpers::stringData(
    "ChartWidget"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSChartWidgetENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSChartWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSChartWidgetENDCLASS_t qt_meta_stringdata_CLASSChartWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11)   // "ChartWidget"
    },
    "ChartWidget"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSChartWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject ChartWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSChartWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSChartWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSChartWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ChartWidget, std::true_type>
    >,
    nullptr
} };

void ChartWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *ChartWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSChartWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChartWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSBarChartWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSBarChartWidgetENDCLASS = QtMocHelpers::stringData(
    "BarChartWidget"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSBarChartWidgetENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSBarChartWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSBarChartWidgetENDCLASS_t qt_meta_stringdata_CLASSBarChartWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14)   // "BarChartWidget"
    },
    "BarChartWidget"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBarChartWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject BarChartWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<ChartWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSBarChartWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBarChartWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBarChartWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BarChartWidget, std::true_type>
    >,
    nullptr
} };

void BarChartWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *BarChartWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BarChartWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBarChartWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return ChartWidget::qt_metacast(_clname);
}

int BarChartWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChartWidget::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSPieChartWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSPieChartWidgetENDCLASS = QtMocHelpers::stringData(
    "PieChartWidget"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSPieChartWidgetENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSPieChartWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSPieChartWidgetENDCLASS_t qt_meta_stringdata_CLASSPieChartWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14)   // "PieChartWidget"
    },
    "PieChartWidget"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPieChartWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject PieChartWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<ChartWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSPieChartWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPieChartWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPieChartWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PieChartWidget, std::true_type>
    >,
    nullptr
} };

void PieChartWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *PieChartWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PieChartWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPieChartWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return ChartWidget::qt_metacast(_clname);
}

int PieChartWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChartWidget::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
