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
    QByteArrayData data[43];
    char stringdata0[853];
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
QT_MOC_LITERAL(9, 112, 34), // "on_handleFilesOperation_clear..."
QT_MOC_LITERAL(10, 147, 36), // "on_handleFilesOperation_sendF..."
QT_MOC_LITERAL(11, 184, 18), // "on_handleCycleSend"
QT_MOC_LITERAL(12, 203, 7), // "readCOM"
QT_MOC_LITERAL(13, 211, 11), // "clearRxBuff"
QT_MOC_LITERAL(14, 223, 11), // "clearTxBuff"
QT_MOC_LITERAL(15, 235, 22), // "filesTransmit_openFile"
QT_MOC_LITERAL(16, 258, 24), // "firmwareUpgrade_openFile"
QT_MOC_LITERAL(17, 283, 26), // "filesOperation_openOneFile"
QT_MOC_LITERAL(18, 310, 11), // "QByteArray*"
QT_MOC_LITERAL(19, 322, 23), // "filesOperation_fileByte"
QT_MOC_LITERAL(20, 346, 5), // "index"
QT_MOC_LITERAL(21, 352, 24), // "filesOperation_openFiles"
QT_MOC_LITERAL(22, 377, 22), // "filesTransmit_sendFile"
QT_MOC_LITERAL(23, 400, 24), // "firmwareUpgrade_sendFile"
QT_MOC_LITERAL(24, 425, 35), // "on_handle_filesOperation_merg..."
QT_MOC_LITERAL(25, 461, 29), // "on_handleFirmwareUpgradeError"
QT_MOC_LITERAL(26, 491, 11), // "sendOnePack"
QT_MOC_LITERAL(27, 503, 8), // "packType"
QT_MOC_LITERAL(28, 512, 31), // "filesTransmit_updateProgressBar"
QT_MOC_LITERAL(29, 544, 33), // "firmwareUpgrade_updateProgres..."
QT_MOC_LITERAL(30, 578, 13), // "fileTimerSend"
QT_MOC_LITERAL(31, 592, 29), // "on_handleFiresTransmitCounter"
QT_MOC_LITERAL(32, 622, 31), // "on_handleFirmwareUpgradeCounter"
QT_MOC_LITERAL(33, 654, 31), // "on_handleFirmwareUpgradeTimeout"
QT_MOC_LITERAL(34, 686, 33), // "on_handleRequestUpdateFontTim..."
QT_MOC_LITERAL(35, 720, 25), // "on_handleEraseFontTimeout"
QT_MOC_LITERAL(36, 746, 8), // "saveFile"
QT_MOC_LITERAL(37, 755, 10), // "saveRxData"
QT_MOC_LITERAL(38, 766, 11), // "handleError"
QT_MOC_LITERAL(39, 778, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(40, 807, 5), // "error"
QT_MOC_LITERAL(41, 813, 26), // "on_textEdit_Rx_textChanged"
QT_MOC_LITERAL(42, 840, 12) // "on_showAbout"

    },
    "MainWindow\0switchPage\0\0on_abstractButtonClicked\0"
    "QAbstractButton*\0button\0setUartParam\0"
    "sendUartData\0uartCycleSend\0"
    "on_handleFilesOperation_clearFiles\0"
    "on_handleFilesOperation_sendFileInfo\0"
    "on_handleCycleSend\0readCOM\0clearRxBuff\0"
    "clearTxBuff\0filesTransmit_openFile\0"
    "firmwareUpgrade_openFile\0"
    "filesOperation_openOneFile\0QByteArray*\0"
    "filesOperation_fileByte\0index\0"
    "filesOperation_openFiles\0"
    "filesTransmit_sendFile\0firmwareUpgrade_sendFile\0"
    "on_handle_filesOperation_mergeFiles\0"
    "on_handleFirmwareUpgradeError\0sendOnePack\0"
    "packType\0filesTransmit_updateProgressBar\0"
    "firmwareUpgrade_updateProgressBar\0"
    "fileTimerSend\0on_handleFiresTransmitCounter\0"
    "on_handleFirmwareUpgradeCounter\0"
    "on_handleFirmwareUpgradeTimeout\0"
    "on_handleRequestUpdateFontTimeout\0"
    "on_handleEraseFontTimeout\0saveFile\0"
    "saveRxData\0handleError\0"
    "QSerialPort::SerialPortError\0error\0"
    "on_textEdit_Rx_textChanged\0on_showAbout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  179,    2, 0x08 /* Private */,
       3,    1,  180,    2, 0x08 /* Private */,
       6,    0,  183,    2, 0x08 /* Private */,
       7,    0,  184,    2, 0x08 /* Private */,
       8,    0,  185,    2, 0x08 /* Private */,
       9,    0,  186,    2, 0x08 /* Private */,
      10,    0,  187,    2, 0x08 /* Private */,
      11,    0,  188,    2, 0x08 /* Private */,
      12,    0,  189,    2, 0x08 /* Private */,
      13,    0,  190,    2, 0x08 /* Private */,
      14,    0,  191,    2, 0x08 /* Private */,
      15,    0,  192,    2, 0x08 /* Private */,
      16,    0,  193,    2, 0x08 /* Private */,
      17,    2,  194,    2, 0x08 /* Private */,
      21,    0,  199,    2, 0x08 /* Private */,
      22,    0,  200,    2, 0x08 /* Private */,
      23,    0,  201,    2, 0x08 /* Private */,
      24,    0,  202,    2, 0x08 /* Private */,
      25,    0,  203,    2, 0x08 /* Private */,
      26,    1,  204,    2, 0x08 /* Private */,
      28,    0,  207,    2, 0x08 /* Private */,
      29,    0,  208,    2, 0x08 /* Private */,
      30,    0,  209,    2, 0x08 /* Private */,
      31,    0,  210,    2, 0x08 /* Private */,
      32,    0,  211,    2, 0x08 /* Private */,
      33,    0,  212,    2, 0x08 /* Private */,
      34,    0,  213,    2, 0x08 /* Private */,
      35,    0,  214,    2, 0x08 /* Private */,
      36,    0,  215,    2, 0x08 /* Private */,
      37,    0,  216,    2, 0x08 /* Private */,
      38,    1,  217,    2, 0x08 /* Private */,
      41,    0,  220,    2, 0x08 /* Private */,
      42,    0,  221,    2, 0x08 /* Private */,

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
    QMetaType::Int, 0x80000000 | 18, QMetaType::Int,   19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
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
    QMetaType::Void, 0x80000000 | 39,   40,
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
        case 5: _t->on_handleFilesOperation_clearFiles(); break;
        case 6: _t->on_handleFilesOperation_sendFileInfo(); break;
        case 7: _t->on_handleCycleSend(); break;
        case 8: _t->readCOM(); break;
        case 9: _t->clearRxBuff(); break;
        case 10: _t->clearTxBuff(); break;
        case 11: _t->filesTransmit_openFile(); break;
        case 12: _t->firmwareUpgrade_openFile(); break;
        case 13: { int _r = _t->filesOperation_openOneFile((*reinterpret_cast< QByteArray*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: _t->filesOperation_openFiles(); break;
        case 15: _t->filesTransmit_sendFile(); break;
        case 16: _t->firmwareUpgrade_sendFile(); break;
        case 17: _t->on_handle_filesOperation_mergeFiles(); break;
        case 18: _t->on_handleFirmwareUpgradeError(); break;
        case 19: _t->sendOnePack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->filesTransmit_updateProgressBar(); break;
        case 21: _t->firmwareUpgrade_updateProgressBar(); break;
        case 22: _t->fileTimerSend(); break;
        case 23: _t->on_handleFiresTransmitCounter(); break;
        case 24: _t->on_handleFirmwareUpgradeCounter(); break;
        case 25: _t->on_handleFirmwareUpgradeTimeout(); break;
        case 26: _t->on_handleRequestUpdateFontTimeout(); break;
        case 27: _t->on_handleEraseFontTimeout(); break;
        case 28: _t->saveFile(); break;
        case 29: _t->saveRxData(); break;
        case 30: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 31: _t->on_textEdit_Rx_textChanged(); break;
        case 32: _t->on_showAbout(); break;
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
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
