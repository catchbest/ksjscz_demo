/****************************************************************************
** Meta object code from reading C++ file 'ImageLabel.h'
**
** Created: Thu Aug 17 18:10:25 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ImageLabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CImageLabel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      26,   24,   12,   12, 0x05,
      59,   24,   12,   12, 0x05,
      94,   24,   12,   12, 0x05,
     126,   24,   12,   12, 0x05,
     171,  165,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CImageLabel[] = {
    "CImageLabel\0\0explains()\0e\0"
    "sigmousePressEvent(QMouseEvent*)\0"
    "sigmouseReleaseEvent(QMouseEvent*)\0"
    "sigmouseMoveEvent(QMouseEvent*)\0"
    "sigmouseDoubleClickEvent(QMouseEvent*)\0"
    "event\0sigwheelEvent(QWheelEvent*)\0"
};

void CImageLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CImageLabel *_t = static_cast<CImageLabel *>(_o);
        switch (_id) {
        case 0: _t->explains(); break;
        case 1: _t->sigmousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->sigmouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->sigmouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->sigmouseDoubleClickEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->sigwheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CImageLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CImageLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_CImageLabel,
      qt_meta_data_CImageLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CImageLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CImageLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CImageLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CImageLabel))
        return static_cast<void*>(const_cast< CImageLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int CImageLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CImageLabel::explains()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CImageLabel::sigmousePressEvent(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CImageLabel::sigmouseReleaseEvent(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CImageLabel::sigmouseMoveEvent(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CImageLabel::sigmouseDoubleClickEvent(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CImageLabel::sigwheelEvent(QWheelEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
