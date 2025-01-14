#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QAbstractButton>
#include <QButtonGroup>
#include <QFileDialog>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//    QSerialPort *serial = new QSerialPort();
    QSerialPort *serial;
    QTimer *portUpdataTimer;
    QTimer *fileSendTimer;
    QTimer *cycleSendTimer;
    QTimer *filesTransmitTimer;
    QTimer *firmwareUpgradeTimer;
    QTimer *firmwareUpgradeTimeoutTimer;
    QTimer *requestUpdateFontTimeoutTimer;
    QTimer *eraseFontTimeoutTimer;

    QStringList oldPortStringList;
    QList<QSerialPortInfo> lastList;
    QString FileText;//读取到的文本文件数据
    QByteArray filesTransmit_fileByte;//读取到的文件数据
    QByteArray firmwareUpgrade_fileByte;//读取到的文件数据
#define FILES_OPERATION_FILES_NUM_MAX   10
    QByteArray filesOperation_filesByte[FILES_OPERATION_FILES_NUM_MAX];//读取到的文件数据
    QByteArray filesOperation_newFileByte;//合并生成的新文件数据
    QString pathForTextDataFile;
    QByteArray dataToWrite;

    int txBytesCounter;//发送字节计数
    int rxBytesCounter;//接收字节计数
    int filesTransmit_fileLen;//文件字节大小
    int firmwareUpgrade_fileLen;//文件字节大小
    int filesOperation_fileLen[FILES_OPERATION_FILES_NUM_MAX];//文件字节大小
    int filesOperation_index;//打开的文件的序号
    int filesTransmit_framesCounter;//帧计数
    int firmwareUpgrade_framesCounter;//帧计数
    int filesTransmit_eachFrameLen;//一帧字节长度
    int firmwareUpgrade_eachFrameLen;//一帧字节长度
    int filesTransmit_framesSum;//帧总数量
    int firmwareUpgrade_framesSum;//帧总数量
    int filesTransmit_sendFrameLen;//发送的帧长度
    int firmwareUpgrade_sendFrameLen;//发送的帧长度
    int filesTransmit_progressCount;//进度条计数
    int firmwareUpgrade_progressCount;//进度条计数
    int flag_update_firmware_disable;//禁止固件更新标志
    int eraseFontTimerCounter;//擦除字库定时器计时
    bool ifSendWithText;//是否以文本形式发送
    float filesTransmitCounter;
    float firmwareUpgradeCounter;
    uchar *senBinBuff;
    QButtonGroup *pButtonGroup;

    enum {
        UPDATE_STATE_IDLE = 0,
        UPDATE_STATE_SEND_UPDATE_REQUEST,
        UPDATE_STATE_SEND_PACK_LEN,
        UPDATE_STATE_SEND_PACK,
        UPDATE_STATE_SEND_END,
    }enUpdateState;

    int checkSum(uchar *buf, int len);
    void checkPort();
    void setConnections();
    void setPortNum();
    void setBaudRate();
    void setDataBit();
    void setStopBit();
    void setCheckBit();
    void setFlowBit();
    void openUart();
    void closeUart();

private slots:
    void switchPage();
    void on_abstractButtonClicked(QAbstractButton *button);
    void setUartParam();
    void sendUartData();
    void uartCycleSend();
    void on_handleFilesOperation_clearFiles();
    void on_handleFilesOperation_sendFileInfo();
    void on_handleCycleSend();
    void readCOM();
    void clearRxBuff();
    void clearTxBuff();
    void filesTransmit_openFile();
    void firmwareUpgrade_openFile();
    int filesOperation_openOneFile(QByteArray *filesOperation_fileByte, int index);
    void filesOperation_openFiles();
    void filesTransmit_sendFile();
    void firmwareUpgrade_sendFile();
    void on_handle_filesOperation_mergeFiles();
    void on_handleFirmwareUpgradeError();
    void sendOnePack(int packType);
    void filesTransmit_updateProgressBar();
    void firmwareUpgrade_updateProgressBar();
    void fileTimerSend();
    void on_handleFiresTransmitCounter();
    void on_handleFirmwareUpgradeCounter();
    void on_handleFirmwareUpgradeTimeout();
    void on_handleRequestUpdateFontTimeout();
    void on_handleEraseFontTimeout();
    void saveFile();
    void saveRxData();
    void handleError(QSerialPort::SerialPortError error);
    void on_textEdit_Rx_textChanged();
    void on_showAbout();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
