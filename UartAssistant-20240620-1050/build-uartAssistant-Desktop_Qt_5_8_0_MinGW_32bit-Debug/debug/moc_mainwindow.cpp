/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../uartAssistant/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[33];
    char stringdata0[591];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "switchPage"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 24), // "on_abstractButtonClicked"
QT_MOC_LITERAL(4, 48, 16), // "QAbstractButton*"
QT_MOC_LITERAL(5, 65, 6), // "button"
QT_MOC_LITERAL(6, 72, 12), // "setUartParam"
QT_MOC_LITERAL(7, 85, 12), // "sendUartData"
QT_MOC_LITERAL(8, 98, 13), // "uartCycleSend"
QT_MOC_LITERAL(9, 112, 18), // "on_handleCycleSend"
QT_MOC_LITERAL(10, 131, 7), // "readCOM"
QT_MOC_LITERAL(11, 139, 11), // "clearRxBuff"
QT_MOC_LITERAL(12, 151, 11), // "clearTxBuff"
QT_MOC_LITERAL(13, 163, 22), // "filesTransmit_openFile"
QT_MOC_LITERAL(14, 186, 24), // "firmwareUpgrade_openFile"
QT_MOC_LITERAL(15, 211, 22), // "filesTransmit_sendFile"
QT_MOC_LITERAL(16, 234, 24), // "firmwareUpgrade_sendFile"
QT_MOC_LITERAL(17, 259, 29), // "on_handleFirmwareUpgradeError"
QT_MOC_LITERAL(18, 289, 11), // "sendOnePack"
QT_MOC_LITERAL(19, 301, 8), // "packType"
QT_MOC_LITERAL(20, 310, 31), // "filesTransmit_updateProgressBar"
QT_MOC_LITERAL(21, 342, 33), // "firmwareUpgrade_updateProgres..."
QT_MOC_LITERAL(22, 376, 13), // "fileTimerSend"
QT_MOC_LITERAL(23, 390, 29), // "on_handleFiresTransmitCounter"
QT_MOC_LITERAL(24, 420, 31), // "on_handleFirmwareUpgradeCounter"
QT_MOC_LITERAL(25, 452, 31), // "on_handleFirmwareUpgradeTimeout"
QT_MOC_LITERAL(26, 484, 8), // "saveFile"
QT_MOC_LITERAL(27, 493, 10), // "saveRxData"
QT_MOC_LITERAL(28, 504, 11), // "handleError"
QT_MOC_LITERAL(29, 516, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(30, 545, 5), // "error"
QT_MOC_LITERAL(31, 551, 26), // "on_textEdit_Rx_textChanged"
QT_MOC_LITERAL(32, 578, 12) // "on_showAbout"

    },
    "MainWindow\0switchPage\0\0on_abstractButtonClicked\0"
    "QAbstractButton*\0button\0setUartParam\0"
    "sendUartData\0uartCycleSend\0"
    "on_handleCycleSend\0readCOM\0clearRxBuff\0"
    "clearTxBuff\0filesTransmit_openFile\0"
    "firmwareUpgrade_openFile\0"
    "filesTransmit_sendFile\0firmwareUpgrade_sendFile\0"
    "on_handleFirmwareUpgradeError\0sendOnePack\0"
    "packType\0filesTransmit_updateProgressBar\0"
    "firmwareUpgrade_updateProgressBar\0"
    "fileTimerSend\0on_handleFiresTransmitCounter\0"
    "on_handleFirmwareUpgradeCounter\0"
    "on_handleFirmwareUpgradeTimeout\0"
    "saveFile\0saveRxData\0handleError\0"
    "QSerialPort::SerialPortError\0error\0"
    "on_textEdit_Rx_textChanged\0on_showAbout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  144,    2, 0x08 /* Private */,
       3,    1,  145,    2, 0x08 /* Private */,
       6,    0,  148,    2, 0x08 /* Private */,
       7,    0,  149,    2, 0x08 /* Private */,
       8,    0,  150,    2, 0x08 /* Private */,
       9,    0,  151,    2, 0x08 /* Private */,
      10,    0,  152,    2, 0x08 /* Private */,
      11,    0,  153,    2, 0x08 /* Private */,
      12,    0,  154,    2, 0x08 /* Private */,
      13,    0,  155,    2, 0x08 /* Private */,
      14,    0,  156,    2, 0x08 /* Private */,
      15,    0,  157,    2, 0x08 /* Private */,
      16,    0,  158,    2, 0x08 /* Private */,
      17,    0,  159,    2, 0x08 /* Private */,
      18,    1,  160,    2, 0x08 /* Private */,
      20,    0,  163,    2, 0x08 /* Private */,
      21,    0,  164,    2, 0x08 /* Private */,
      22,    0,  165,    2, 0x08 /* Private */,
      23,    0,  166,    2, 0x08 /* Private */,
      24,    0,  167,    2, 0x08 /* Private */,
      25,    0,  168,    2, 0x08 /* Private */,
      26,    0,  169,    2, 0x08 /* Private */,
      27,    0,  170,    2, 0x08 /* Private */,
      28,    1,  171,    2, 0x08 /* Private */,
      31,    0,  174,    2, 0x08 /* Private */,
      32,    0,  175,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->switchPage(); break;
        case 1: _t->on_abstractButtonClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: _t->setUartParam(); break;
        case 3: _t->sendUartData(); break;
        case 4: _t->uartCycleSend(); break;
        case 5: _t->on_handleCycleSend(); break;
        case 6: _t->readCOM(); break;
        case 7: _t->clearRxBuff(); break;
        case 8: _t->clearTxBuff(); break;
        case 9: _t->filesTransmit_openFile(); break;
        case 10: _t->firmwareUpgrade_openFile(); break;
        case 11: _t->filesTransmit_sendFile(); break;
        case 12: _t->firmwareUpgrade_sendFile(); break;
        case 13: _t->on_handleFirmwareUpgradeError(); break;
        case 14: _t->sendOnePack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->filesTransmit_updateProgressBar(); break;
        case 16: _t->firmwareUpgrade_updateProgressBar(); break;
        case 17: _t->fileTimerSend(); break;
        case 18: _t->on_handleFiresTransmitCounter(); break;
        case 19: _t->on_handleFirmwareUpgradeCounter(); break;
        case 20: _t->on_handleFirmwareUpgradeTimeout(); break;
        case 21: _t->saveFile(); break;
        case 22: _t->saveRxData(); break;
        case 23: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 24: _t->on_textEdit_Rx_textChanged(); break;
        case 25: _t->on_showAbout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
