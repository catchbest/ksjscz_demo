/****************************************************************************
** Meta object code from reading C++ file 'KSJSCZDemoMainWindow.h'
**
** Created: Fri Sep 8 10:11:51 2017
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
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x09,
      49,   22,   22,   22, 0x09,
      75,   22,   22,   22, 0x09,
      98,   22,   22,   22, 0x09,
     117,   22,   22,   22, 0x09,
     129,   22,   22,   22, 0x09,
     142,   22,   22,   22, 0x09,
     155,   22,   22,   22, 0x09,
     166,   22,   22,   22, 0x09,
     193,   22,   22,   22, 0x09,
     231,   22,   22,   22, 0x09,
     261,   22,   22,   22, 0x09,
     293,   22,   22,   22, 0x09,
     323,   22,   22,   22, 0x09,
     340,   22,   22,   22, 0x09,
     371,   22,   22,   22, 0x09,
     401,   22,   22,   22, 0x09,
     431,   22,   22,   22, 0x09,
     461,   22,   22,   22, 0x09,
     493,   22,   22,   22, 0x09,
     525,   22,   22,   22, 0x09,
     554,   22,   22,   22, 0x09,
     586,   22,   22,   22, 0x09,
     619,   22,   22,   22, 0x09,
     651,   22,   22,   22, 0x09,
     683,   22,   22,   22, 0x09,
     712,   22,   22,   22, 0x09,
     739,   22,   22,   22, 0x09,
     766,   22,   22,   22, 0x09,
     792,   22,   22,   22, 0x09,
     818,   22,   22,   22, 0x09,
     844,   22,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CKSJSCZDemoMainWindow[] = {
    "CKSJSCZDemoMainWindow\0\0OnTriggerModeChanged(int)\0"
    "OnExpTimerChanged(double)\0"
    "OnExpLinesChanged(int)\0OnGainChanged(int)\0"
    "OnReadReg()\0OnWriteReg()\0OnReadGpio()\0"
    "OnSetFov()\0OnTriggerDelayChanged(int)\0"
    "OnParseBarcodeChkBoxStateChanged(int)\0"
    "OnSaveChkBoxStateChanged(int)\0"
    "OnMirrorChkBoxStateChanged(int)\0"
    "OnFlipChkBoxStateChanged(int)\0"
    "OnStartCapture()\0OnEan13ChkBoxStateChanged(int)\0"
    "OnEan8ChkBoxStateChanged(int)\0"
    "OnUPCAChkBoxStateChanged(int)\0"
    "OnUPCEChkBoxStateChanged(int)\0"
    "OnISBN10ChkBoxStateChanged(int)\0"
    "OnISBN13ChkBoxStateChanged(int)\0"
    "OnI25ChkBoxStateChanged(int)\0"
    "OnCODE39ChkBoxStateChanged(int)\0"
    "OnCODE128ChkBoxStateChanged(int)\0"
    "OnPDF417ChkBoxStateChanged(int)\0"
    "OnQRCODEChkBoxStateChanged(int)\0"
    "OnDensitySpinBoxChanged(int)\0"
    "OnALedCheckBoxChanged(int)\0"
    "OnBLedCheckBoxChanged(int)\0"
    "OnIO1CheckBoxChanged(int)\0"
    "OnIO2CheckBoxChanged(int)\0"
    "OnIO3CheckBoxChanged(int)\0OnTimerFrameRate()\0"
};

void CKSJSCZDemoMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CKSJSCZDemoMainWindow *_t = static_cast<CKSJSCZDemoMainWindow *>(_o);
        switch (_id) {
        case 0: _t->OnTriggerModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OnExpTimerChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->OnExpLinesChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnGainChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->OnReadReg(); break;
        case 5: _t->OnWriteReg(); break;
        case 6: _t->OnReadGpio(); break;
        case 7: _t->OnSetFov(); break;
        case 8: _t->OnTriggerDelayChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->OnParseBarcodeChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->OnSaveChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->OnMirrorChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->OnFlipChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->OnStartCapture(); break;
        case 14: _t->OnEan13ChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->OnEan8ChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->OnUPCAChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->OnUPCEChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->OnISBN10ChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->OnISBN13ChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->OnI25ChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->OnCODE39ChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->OnCODE128ChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->OnPDF417ChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->OnQRCODEChkBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->OnDensitySpinBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->OnALedCheckBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->OnBLedCheckBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->OnIO1CheckBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->OnIO2CheckBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->OnIO3CheckBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->OnTimerFrameRate(); break;
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
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
