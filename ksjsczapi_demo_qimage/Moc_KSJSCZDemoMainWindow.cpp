/****************************************************************************
** Meta object code from reading C++ file 'KSJSCZDemoMainWindow.h'
**
** Created: Thu Sep 7 18:12:48 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "KSJSCZDemoMainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KSJSCZDemoMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CKSJSCZDemoMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x09,
      40,   22,   22,   22, 0x09,
      62,   56,   22,   22, 0x09,
      82,   56,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CKSJSCZDemoMainWindow[] = {
    "CKSJSCZDemoMainWindow\0\0OnStartCapture()\0"
    "OnStopCapture()\0value\0OnHorScrollbar(int)\0"
    "OnVerScrollbar(int)\0"
};

void CKSJSCZDemoMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CKSJSCZDemoMainWindow *_t = static_cast<CKSJSCZDemoMainWindow *>(_o);
        switch (_id) {
        case 0: _t->OnStartCapture(); break;
        case 1: _t->OnStopCapture(); break;
        case 2: _t->OnHorScrollbar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnVerScrollbar((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CKSJSCZDemoMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CKSJSCZDemoMainWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CKSJSCZDemoMainWindow,
      qt_meta_data_CKSJSCZDemoMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CKSJSCZDemoMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CKSJSCZDemoMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CKSJSCZDemoMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CKSJSCZDemoMainWindow))
        return static_cast<void*>(const_cast< CKSJSCZDemoMainWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int CKSJSCZDemoMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
