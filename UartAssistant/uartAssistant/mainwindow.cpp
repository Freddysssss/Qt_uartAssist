#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QByteArray>
#include <QTextCodec>
#include <QDateTime>
#include <QFont>
#include <QTextEdit>
#include <QMimeType>
#include <QMimeDatabase>
#include <QObject>

#define PACKAGE_TYPE_UPDATE_REQUEST     1
#define PACKAGE_TYPE_PACKAGE_SUM        2
#define PACKAGE_TYPE_FILE_DATA          3
#define PACKAGE_TYPE_FILE_SEND_END      4

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("串口助手");
    setWindowIcon(QIcon(":/image/uart.jpg"));//设置窗口图标
    serial = new QSerialPort();

    txBytesCounter = 0;
    rxBytesCounter = 0;
    ui->stackedWidget->setCurrentIndex(0);
//    ui->pushButton_sendAndReceive->setDisabled(true);
//    ui->pushButton_filesTransmit->setEnabled(true);
//    ui->pushButton_firmwareUpgrade->setEnabled(true);

    ui->pushButton_sendAndReceive->setCheckable(true);
    ui->pushButton_sendAndReceive->setChecked(true);
    ui->pushButton_filesTransmit->setCheckable(true);
    ui->pushButton_firmwareUpgrade->setCheckable(true);
    ui->pushButton_filesOperation->setCheckable(true);
    //将按键添加到组中
    pButtonGroup = new QButtonGroup(this);
    pButtonGroup->setExclusive(true);//设置为互斥
    pButtonGroup->addButton(ui->pushButton_sendAndReceive);
    pButtonGroup->addButton(ui->pushButton_filesTransmit);
    pButtonGroup->addButton(ui->pushButton_firmwareUpgrade);
    pButtonGroup->addButton(ui->pushButton_filesOperation);

    //自动更新端口定时器
    portUpdataTimer = new QTimer();
    portUpdataTimer->start(500);
    oldPortStringList.clear();
    lastList.clear();
    this->checkPort();

    //循环发送定时器
    cycleSendTimer = new QTimer();
    //文件发送定时器
    fileSendTimer = new QTimer();
    //文件传输时间定时器
    filesTransmitTimer = new QTimer();
    ui->lcdNumber_filesTransmit->setSmallDecimalPoint(true);
    //固件升级时间定时器
    firmwareUpgradeTimer = new QTimer();
    ui->lcdNumber_firmwareUpgrade->setSmallDecimalPoint(true);
    //固件升级超时定时器
    firmwareUpgradeTimeoutTimer = new QTimer();
    //请求更新字库超时定时器
    requestUpdateFontTimeoutTimer = new QTimer();
    //擦除字库超时定时器
    eraseFontTimeoutTimer = new QTimer();

    ui->progressBar_filesTransmit->setValue(0);
    ui->label_filesTransmit_progress->setText(QString("%1/%2 %3").arg("0").arg("0").arg("bytes"));
    ui->progressBar_firmwareUpgrade->setValue(0);
    ui->label_firmwareUpgrade_progress->setText(QString("%1/%2 %3").arg("0").arg("0").arg("bytes"));
    ui->lcdNumber_filesTransmit->display(0);
    ui->lcdNumber_firmwareUpgrade->display(0);
    filesTransmitCounter = 0;
    firmwareUpgradeCounter = 0;

    this->setConnections();
    ui->pushButton_send->setDisabled(true);
    ui->pushButton_filesTransmit_startTransmit->setDisabled(true);
    ui->pushButton_firmwareUpgrade_startUpgrade->setDisabled(true);
    ui->comboBox_baud->setCurrentText("115200");
//  ui->textEdit_Rx->setLineWrapMode(QTextEdit::WidgetWidth);//与窗口宽度对齐自动换行
//    ui->checkBox_showTime->setChecked(true);

    QFont font;
    font.setPointSize(20);
    ui->pushButton_send->setFont(font);
//    ui->pushButton_send->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(224, 224, 224);");

//    ui->groupBox->addAction();
    enUpdateState = UPDATE_STATE_IDLE;
    filesTransmit_framesCounter = 0;
    firmwareUpgrade_framesCounter = 0;
    firmwareUpgrade_framesCounter = 0;

    filesOperation_newFileByte.clear();
    filesOperation_index = -1;

    //滚动条保存在最底部
    ui->textEdit_filesOperationInfo->moveCursor(QTextCursor::End);
    ui->textEdit_firmwareUpgradeInfo->moveCursor(QTextCursor::End);
    ui->textEdit_filesTransmitInfo->moveCursor(QTextCursor::End);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::checkSum(uchar *buf, int len)
{
    int checksum = 0;
    for(int i = 0; i < len; i++)
    {
        checksum += static_cast<int>(buf[i]);
    }
    return checksum;
}

void MainWindow::checkPort()
{
#if 1
    //方法1：
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();//获取当前可用端口号，并存入列表
    QSerialPortInfo info;

    if (lastList.size() != list.size())
    {
        ui->comboBox_portNum->clear();
        for (int i = 0; i < list.size(); i++)
        {
            info = list.at(i);//获取端口信息
            ui->comboBox_portNum->addItem(info.portName());//将端口的端口号名称添加到下拉框中
        }
        lastList = list;
    }
#else
    QStringList newPortStringList;
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    #if 1
    //方法2：
    for (int i = 0; i < list.size(); i++)
    {
        newPortStringList.insert(i, list.at(i).portName());//端口名逐个加入到列表中
    }
    #else
    //方法3：
    for (const QSerialPortInfo &info : list)
    {
        newPortStringList += info.portName();
    }
    #endif
    if (list.size() != lastList.size())
    {
        ui->comboBox_portNum->clear();
        ui->comboBox_portNum->addItems(newPortStringList);
        lastList = list;
    }
#endif
}
void MainWindow::setConnections()
{
    connect(ui->pushButton_sendAndReceive, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(ui->pushButton_filesTransmit, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(ui->pushButton_firmwareUpgrade, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(ui->pushButton_filesOperation, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_abstractButtonClicked(QAbstractButton*)));
    connect(ui->pushButton_openUart, &QPushButton::clicked, this, &MainWindow::setUartParam);
    connect(ui->pushButton_send, &QPushButton::clicked, this, &MainWindow::sendUartData);
    connect(ui->pushButton_clearRx, &QPushButton::clicked, this, &MainWindow::clearRxBuff);
    connect(ui->pushButton_clearTx, &QPushButton::clicked, this, &MainWindow::clearTxBuff);
    connect(ui->pushButton_save, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(ui->pushButton_filesTransmit_openFile, &QPushButton::clicked, this, &MainWindow::filesTransmit_openFile);
    connect(ui->pushButton_firmwareUpgrade_openFiles, &QPushButton::clicked, this, &MainWindow::firmwareUpgrade_openFile);
    connect(ui->pushButton_filesOperation_openFiles, &QPushButton::clicked, this, &MainWindow::filesOperation_openFiles);
    connect(ui->pushButton_filesTransmit_startTransmit, &QPushButton::clicked, this, &MainWindow::filesTransmit_sendFile);
    connect(ui->pushButton_firmwareUpgrade_startUpgrade, &QPushButton::clicked, this, &MainWindow::firmwareUpgrade_sendFile);
    connect(ui->pushButton_filesOperation_mergeFiles, &QPushButton::clicked, this, &MainWindow::on_handle_filesOperation_mergeFiles);
    connect(ui->pushButton_filesTransmit_clear, &QPushButton::clicked, ui->textEdit_filesTransmitInfo, &QTextEdit::clear);
    connect(ui->pushButton_filesOperation_clearFiles, &QPushButton::clicked, this, &MainWindow::on_handleFilesOperation_clearFiles);
    connect(ui->pushButton_filesOperation_sendFileInfo, &QPushButton::clicked, this, &MainWindow::on_handleFilesOperation_sendFileInfo);
    connect(ui->pushButton_firmwareUpgrade_clear, &QPushButton::clicked, [=](){
        ui->textEdit_firmwareUpgradeInfo->clear();
    });
    connect(ui->pushButton_filesOperation_clear, &QPushButton::clicked, ui->textEdit_filesOperationInfo, ui->textEdit_filesOperationInfo->clear);

    connect(ui->checkBox_saveDataToFile, &QCheckBox::clicked, this, &MainWindow::saveRxData);
    connect(ui->checkBox_cycleSend, &QCheckBox::clicked, this, &MainWindow::uartCycleSend);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readCOM);
    connect(serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(portUpdataTimer, &QTimer::timeout, this, &MainWindow::checkPort);
    connect(fileSendTimer, &QTimer::timeout, this, &MainWindow::fileTimerSend);
    connect(cycleSendTimer, &QTimer::timeout, this, &MainWindow::on_handleCycleSend);
    connect(filesTransmitTimer, &QTimer::timeout, this, &MainWindow::on_handleFiresTransmitCounter);
    connect(firmwareUpgradeTimer, &QTimer::timeout, this, &MainWindow::on_handleFirmwareUpgradeCounter);
    connect(firmwareUpgradeTimeoutTimer, &QTimer::timeout, this, &MainWindow::on_handleFirmwareUpgradeTimeout);
    connect(requestUpdateFontTimeoutTimer, &QTimer::timeout, this, &MainWindow::on_handleRequestUpdateFontTimeout);
    connect(eraseFontTimeoutTimer, &QTimer::timeout, this, &MainWindow::on_handleEraseFontTimeout);
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::on_showAbout);
}

void MainWindow::setPortNum()
{
    serial->setPortName(ui->comboBox_portNum->currentText());
}

void MainWindow::setBaudRate()
{
    serial->setBaudRate(ui->comboBox_baud->currentText().toInt());
}

void MainWindow::setDataBit()
{
    switch (ui->comboBox_dataBit->currentIndex())
    {
        case 0: serial->setDataBits(QSerialPort::Data8); break;
        case 1: serial->setDataBits(QSerialPort::Data7); break;
        case 2: serial->setDataBits(QSerialPort::Data6); break;
        case 3: serial->setDataBits(QSerialPort::Data5); break;
        default:break;
    }
}

void MainWindow::setStopBit()
{
    switch (ui->comboBox_stopBit->currentIndex())
    {
        case 0: serial->setStopBits(QSerialPort::OneStop); break;
        case 1: serial->setStopBits(QSerialPort::OneAndHalfStop); break;
        case 2: serial->setStopBits(QSerialPort::TwoStop); break;
        default:break;
    }
}

void MainWindow::setCheckBit()
{
    switch (ui->comboBox_checkBit->currentIndex())
    {
        case 0: serial->setParity(QSerialPort::NoParity); break;
        case 1: serial->setParity(QSerialPort::OddParity); break;
        case 2: serial->setParity(QSerialPort::EvenParity); break;
        default:break;
    }
}

void MainWindow::setFlowBit()
{
    switch (ui->comboBox_flowBit->currentIndex())
    {
        case 0: serial->setFlowControl(QSerialPort::NoFlowControl); break;
        case 1: serial->setFlowControl(QSerialPort::HardwareControl); break;
        case 2: serial->setFlowControl(QSerialPort::SoftwareControl); break;
        case 3: serial->setFlowControl(QSerialPort::UnknownFlowControl); break;
        default:break;
    }
}

void MainWindow::openUart()
{
    qDebug()<<ui->pushButton_openUart->text();

    portUpdataTimer->stop();
    this->setPortNum();
    this->setBaudRate();
    this->setDataBit();
    this->setStopBit();
    this->setCheckBit();
    this->setFlowBit();

    if (serial->open(QIODevice::ReadWrite))
    {
        if (ui->pushButton_filesTransmit->isChecked())
            ui->textEdit_filesTransmitInfo->append("串口打开成功！");
        else if (ui->pushButton_firmwareUpgrade->isChecked())
            ui->textEdit_firmwareUpgradeInfo->append("串口打开成功！");
        ui->pushButton_openUart->setText("关闭串口");
        ui->pushButton_openUart->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(255, 0, 0);");
        ui->comboBox_portNum->setDisabled(true);
        ui->comboBox_baud->setDisabled(true);
        ui->comboBox_dataBit->setDisabled(true);
        ui->comboBox_stopBit->setDisabled(true);
        ui->comboBox_checkBit->setDisabled(true);
        ui->comboBox_flowBit->setDisabled(true);

        ui->pushButton_send->setEnabled(true);
        ui->pushButton_filesTransmit_startTransmit->setEnabled(true);
        ui->pushButton_firmwareUpgrade_startUpgrade->setEnabled(true);
//      ui->pushButton_send->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(0, 128, 255);");

        return;
    }
    else
    {
        if (ui->pushButton_filesTransmit->isChecked())
            ui->textEdit_filesTransmitInfo->append("串口打开失败！");
        else if (ui->pushButton_firmwareUpgrade->isChecked())
            ui->textEdit_firmwareUpgradeInfo->append("串口打开失败！");
        QMessageBox::about(NULL, "提示", "串口打开失败\r\n不存在或已被占用");     //当串口打开失败时出现临时窗口提示
        return;
    }
}

void MainWindow::closeUart()
{
    qDebug()<<ui->pushButton_openUart->text();
    if (ui->pushButton_filesTransmit->isChecked())
        ui->textEdit_filesTransmitInfo->append("关闭串口");
    else if (ui->pushButton_firmwareUpgrade->isChecked())
        ui->textEdit_firmwareUpgradeInfo->append("关闭串口");

    portUpdataTimer->start(500);
    ui->pushButton_openUart->setText("打开串口");
    ui->pushButton_openUart->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(224, 224, 224);");
    ui->comboBox_portNum->setEnabled(true);
    ui->comboBox_baud->setEnabled(true);
    ui->comboBox_dataBit->setEnabled(true);
    ui->comboBox_stopBit->setEnabled(true);
    ui->comboBox_checkBit->setEnabled(true);
    ui->comboBox_flowBit->setEnabled(true);

    ui->pushButton_send->setDisabled(true);
    ui->pushButton_filesTransmit_startTransmit->setDisabled(true);
    ui->pushButton_firmwareUpgrade_startUpgrade->setDisabled(true);
//        ui->pushButton_send->setStyleSheet("color: rgb(100, 100, 100); background-color: rgb(200, 200, 200);");

    fileSendTimer->stop();
    ui->progressBar_filesTransmit->setValue(0);
    ui->progressBar_firmwareUpgrade->setValue(0);
    ui->label_filesTransmit_progress->setText(QString("%1/%2 %3").arg("0").arg(0).arg("bytes"));
    ui->label_firmwareUpgrade_progress->setText(QString("%1/%2 %3").arg("0").arg(0).arg("bytes"));
    filesTransmitTimer->stop();
    firmwareUpgradeTimer->stop();
    filesTransmitCounter = 0;
    firmwareUpgradeCounter = 0;
    ui->lcdNumber_filesTransmit->display(0);
    ui->lcdNumber_firmwareUpgrade->display(0);

    serial->close();
}

void MainWindow::switchPage()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());//得到按下的按钮的指针
    if (btn == ui->pushButton_sendAndReceive)
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (btn == ui->pushButton_filesTransmit)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (btn == ui->pushButton_firmwareUpgrade)
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if (btn == ui->pushButton_filesOperation)
    {
        ui->stackedWidget->setCurrentIndex(3);
    }
}

void MainWindow::on_abstractButtonClicked(QAbstractButton *button)
{
    qDebug() << "Clicked Button : " << button->text();
}

void MainWindow::setUartParam()
{
    if (ui->pushButton_openUart->text() == "打开串口")
    {
        this->openUart();
    }
    else if (ui->pushButton_openUart->text() == "关闭串口")
    {
        this->closeUart();
    }
}

void MainWindow::sendUartData()
{
    QString data = ui->textEdit_Tx->toPlainText();
    txBytesCounter += data.size();
    ui->label_txCounter->setText(QString("%1%2").arg("TX:").arg(txBytesCounter));
    qDebug()<<"send:"<<data.size();

    if (ui->checkBox_HexSend->isChecked())
    {
        QByteArray arr;
#if 0
        //方法1：
        for (int i=0; i<data.size(); i++)
        {
            if (data[i] == " ") continue;
            int num = data.mid(i, 2).toUInt(nullptr, 16);
            i++;
            arr.append(num);
        }
#else
        //方法2：
        if (data.contains(" "))
        {
            data.replace(QString(" "), QString(""));//删除空格
        }
        arr = QByteArray::fromHex(data.toLatin1());
#endif
        if (ui->checkBox_addNewLine->isChecked())
        {
            arr.append("\r\n");
        }
        serial->write(arr);
    }
    else
    {
//        serial->write(ui->textEdit_Tx->toPlainText().toUtf8());
//        serial->write(ui->textEdit_Tx->toPlainText().toLocal8Bit());//既可发送字符、数字，也可发送中文
        if (ui->checkBox_addNewLine->isChecked())
        {
            data.append("\r\n");
        }
        serial->write(data.toLocal8Bit());
    }
}

void MainWindow::uartCycleSend()
{
    if (ui->checkBox_cycleSend->isChecked())
    {
        cycleSendTimer->start(ui->lineEdit_cycleDelay->text().toInt());
    }
    else
    {
        cycleSendTimer->stop();
    }
}

void MainWindow::on_handleFilesOperation_clearFiles()
{
    qDebug() <<"清空文件";
    ui->textEdit_filesOperationInfo->append("清空文件\r\n");

    filesOperation_index = -1;
    filesOperation_newFileByte.clear();
    ui->lineEdit_filesOperation_filesNum->setText(QString::number(0));
    memset(filesOperation_fileLen, 0, FILES_OPERATION_FILES_NUM_MAX);
}

/**
头        长度	    命令 数量  序号总 大小	               命令 数量  序号1 大小	               序号2 大小		            序号3 大小		         序号4 大小		          校验
0xA9 0x54 0x00 0x14 0xE0 0x04 0x00 0x12 0x34 0x56 0x78 0xE0 0x04 0x01 0x12 0x00 0x00 0x00 0x02 0x00 0x34 0x00 0x00 0x03 0x00 0x00 0x56 0x00 0x04 0x00 0x00 0x00 0x78 0xXX 0xXX
*/
void MainWindow::on_handleFilesOperation_sendFileInfo()
{
    QByteArray sendBuf;
    int checksum = 0;
    int filesNum = ui->lineEdit_filesOperation_filesNum->text().toInt();
    int dataLen = 4 + filesNum * 5;
    int fileSize[filesNum];
    int filesSize = filesOperation_newFileByte.size();//合并后新文件大小

    if (filesNum > FILES_OPERATION_FILES_NUM_MAX) return;

    if (ui->pushButton_openUart->text() == "打开串口")
    {
        QMessageBox::warning(this, "警告", "请先打开串口");
        return;
    }

    if (ui->lineEdit_filesOperation_filesNum->text().toInt() < 1)
    {
        QMessageBox::warning(this, "警告", "文件不存在，请先打开文件合并保存！");
        return;
    }

    sendBuf.clear();
    sendBuf.append("\xA9\x54");//head

    //data length
    sendBuf.append(static_cast<char>((dataLen>>8)&0xFF));
    sendBuf.append(static_cast<char>((dataLen>>0)&0xFF));
    //cmd
    sendBuf.append("\xE0");
    //files number
    sendBuf.append(static_cast<char>(filesNum));

    //合并后的文件大小
    //file serial number
    sendBuf.append(static_cast<char>(0));
    //file size
    sendBuf.append(static_cast<char>((filesSize>>24)&0xFF));
    sendBuf.append(static_cast<char>((filesSize>>16)&0xFF));
    sendBuf.append(static_cast<char>((filesSize>> 8)&0xFF));
    sendBuf.append(static_cast<char>((filesSize>> 0)&0xFF));

    //合并前各个文件大小
    for (int i = 0; i < filesNum; i++)
    {
        fileSize[i] = filesOperation_fileLen[i];

        //file serial number
        sendBuf.append(static_cast<char>(i + 1));
        //file size
        sendBuf.append(static_cast<char>((fileSize[i]>>24)&0xFF));
        sendBuf.append(static_cast<char>((fileSize[i]>>16)&0xFF));
        sendBuf.append(static_cast<char>((fileSize[i]>> 8)&0xFF));
        sendBuf.append(static_cast<char>((fileSize[i]>> 0)&0xFF));
    }

    for(int i = 0; i < sendBuf.size(); i++){
        checksum += sendBuf.at(i) & 0xff;
    }

    //checksum
    sendBuf.append(static_cast<char>((checksum>>8)&0xFF));
    sendBuf.append(static_cast<char>(checksum&0xFF));
    serial->write(sendBuf);

    QString tmpBuff = sendBuf.toHex().toUpper();
    QString hexBuff;
    int hexNum = 0;
    for (int i=0; i<tmpBuff.size(); i++)
    {
        hexBuff[hexNum++] = tmpBuff[i];
        if (i%2 == 1 && i != tmpBuff.size())
        {
            hexBuff[hexNum++] = ' ';
        }
    }
    qDebug()<<hexBuff;
//    ui->textEdit_filesOperationInfo->append(hexBuff);
    ui->textEdit_firmwareUpgradeInfo->append("发送文件信息：");
    ui->textEdit_firmwareUpgradeInfo->append(hexBuff);
    ui->textEdit_firmwareUpgradeInfo->append("请求擦除旧字库！");
    requestUpdateFontTimeoutTimer->start(3000);//3s
    ui->stackedWidget->setCurrentIndex(2);//切换到固件升级窗口
    ui->pushButton_firmwareUpgrade->setChecked(true);
}

void MainWindow::on_handleCycleSend()
{
    if (ui->pushButton_openUart->text() == "关闭串口" && \
        ui->textEdit_Tx->toPlainText().isEmpty() == false)
    {
        this->sendUartData();
    }
}


void MainWindow::readCOM()//-----问题：接收很多中文时有时会出现乱码
{
    QByteArray serialBuff = serial->readAll();//存储串口接收缓冲区
    QString textBuff = ui->textEdit_Rx->toPlainText();//获取接收区原本的数据
    rxBytesCounter += serialBuff.size();
    ui->label_rxCounter->setText(QString("%1%2").arg("RX:").arg(rxBytesCounter));
//    qDebug()<<"接收字节大小："<<serialBuff.size();
//    qDebug()<<QString::fromLocal8Bit(serialBuff);

    if (ui->pushButton_sendAndReceive->isChecked())
    {
        if (ui->checkBox_ShowHex->isChecked())
        {
            QString tmpBuff = serialBuff.toHex();
            QString hexBuff;
            int hexNum = 0;
            for (int i=0; i<tmpBuff.size(); i++)
            {
                hexBuff[hexNum++] = tmpBuff[i];
                if (i%2 == 1 && i != tmpBuff.size())
                {
                    hexBuff[hexNum++] = ' ';
                }
            }

            if (ui->checkBox_showTime->isChecked())
            {
    //            qDebug()<<"显示HEX+时间";
                QString sysTime = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] ");
                ui->textEdit_Rx->append(sysTime + hexBuff.toUpper());//可显示中文
            }
            else
            {
    //            qDebug()<<"显示HEX";
    //            ui->textEdit_Rx->append(hexBuff);//会换行
                ui->textEdit_Rx->setText(textBuff+hexBuff.toUpper());//不换行
            }
        }
        else
        {
            //ui->textEdit_Rx->append(serialBuff);//显示接收区
            QString Data = QString::fromLocal8Bit(serialBuff);
            if (ui->checkBox_showTime->isChecked())
            {
    //            qDebug()<<"显示文本+时间";
                QString sysTime = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] ");
                ui->textEdit_Rx->append(sysTime + Data);//可显示中文
    //            ui->textEdit_Rx->setText(textBuff + sysTime + Data);
            }
            else
            {
    //            qDebug()<<"显示文本";
    //            ui->textEdit_Rx->append(Data);//可显示中文，会换行
    //            ui->textEdit_Rx->append(serialBuff);//可显示中文，会换行
    //            ui->textEdit_Rx->setText(textBuff+Data);//不换行---接收到的数据越多越慢，必须经常清空
    //            ui->textEdit_Rx->insertPlainText(Data);//不会换行，但同样收到数据越多会越慢
    //            ui->textEdit_Rx->insertPlainText(serialBuff);//有时会多出回车换行，不支持中文
    //            ui->textEdit_Rx->setText(textBuff+serialBuff);//接收全字符正常，不支持收中文
                ui->textEdit_Rx->setText(textBuff+Data);//接收全字符多出换行，支持收中文
            }
        }

        if (ui->checkBox_saveDataToFile->isChecked())
        {
            QFile file(pathForTextDataFile);
            if (file.open(QIODevice::WriteOnly))
            {
                file.write(ui->textEdit_Rx->toPlainText().toLocal8Bit());
                file.close();
            }
        }
    }
    else if (ui->pushButton_firmwareUpgrade->isChecked())
    {
//        if (enUpdateState == UPDATE_STATE_IDLE)
//        {
//            return;
//        }

        QString tmpBuff = serialBuff.toHex();
        QString hexBuff;
        int error_code = 0;
        int hexNum = 0;
        for (int i=0; i<tmpBuff.size(); i++)
        {
            hexBuff[hexNum++] = tmpBuff[i];
            if (i%2 == 1 && i != tmpBuff.size())
            {
                hexBuff[hexNum++] = ' ';
            }
        }

        //解析收到的反馈数据
        uchar *buf = reinterpret_cast<unsigned char*>(serialBuff.data());
        int bufLen = serialBuff.size();
//        qDebug()<<"bufLen="<<bufLen;
//        for (int i=0;i<bufLen;i++)
//        {
//            qDebug()<<"buf["<<i<<"] = "<<buf[i];
//        }

        //check head
        if (buf[0] != 0xAA || buf[1] != 0x55)
        {
            error_code = 0x01;
        }

        //check length
        if ((buf[2] + 6) != bufLen)
        {
            error_code = 0x02;
        }

        //check checksum
        int checksum = static_cast<int>(buf[bufLen - 2]) << 8 | static_cast<int>(buf[bufLen - 1]);
        if (checksum != this->checkSum(buf, bufLen - 2))
        {
            error_code = 0x03;
        }

        //check feedback
        if (buf[3] == 0x00)
        {
            error_code = 0x04;
        }

        if (error_code)
        {
            qDebug()<<"error_code = "<<error_code;
            QString strNum = QString::number(error_code);
            ui->textEdit_firmwareUpgradeInfo->append("错误码："+strNum);
            this->on_handleFirmwareUpgradeError();
            return;
        }

        if (buf[3] == 0x04)//正在擦除旧字库
        {
            requestUpdateFontTimeoutTimer->stop();
            eraseFontTimeoutTimer->start(1000);//1s
            flag_update_firmware_disable = 1;//禁止更新固件(此时下位机正在擦除旧字库，等其擦除完成方可继续更新)
            ui->textEdit_firmwareUpgradeInfo->append("旧字库擦除中，请等待......");
        }
        if (buf[3] == 0x05)//旧字库擦除完成
        {
            if (flag_update_firmware_disable)
            {
                flag_update_firmware_disable = 0;//允许更新固件
                eraseFontTimerCounter = 0;
                eraseFontTimeoutTimer->stop();
                ui->textEdit_firmwareUpgradeInfo->append("擦除完成，请升级字库！");
            }
        }

        if (enUpdateState == UPDATE_STATE_IDLE)
        {
            qDebug()<<"warning: enUpdateState is not UPDATE_STATE_IDLE";
            return;
        }

        static int packCnt = 0;
        firmwareUpgradeTimeoutTimer->stop();
        if (buf[3] == 0x01)//请求文件数据包长度
        {
            qDebug()<<"<<--：请求文件数据包长度";
            qDebug()<<"respond:"<<hexBuff;
            if (enUpdateState != UPDATE_STATE_SEND_UPDATE_REQUEST)
            {
                qDebug()<<"Update state is not idle"<<enUpdateState;
                QString strNum = QString::number(7);//状态错误
                ui->textEdit_firmwareUpgradeInfo->append("错误码："+strNum);
                this->on_handleFirmwareUpgradeError();
                return;
            }
            enUpdateState = UPDATE_STATE_SEND_PACK_LEN;

            if (ui->checkBox_firmwareUpgrade_showData->isChecked())
            {
                ui->textEdit_firmwareUpgradeInfo->append("接收第0帧: "+hexBuff.toUpper());
                ui->textEdit_firmwareUpgradeInfo->append("");
            }

            this->sendOnePack(PACKAGE_TYPE_PACKAGE_SUM);//发送文件分包数量
        }
        else if (buf[3] == 0x02)//请求第n帧数据
        {
            int pack_number = ((int)buf[4]<<8 | (int)buf[5]);
//            qDebug()<<"<<--：请求第"<<pack_number<<"帧数据";
//            qDebug()<<"respond:"<<hexBuff;
            if (ui->checkBox_firmwareUpgrade_showData->isChecked())
            {
                packCnt = pack_number;
                QString str = QString::number(packCnt);
                ui->textEdit_firmwareUpgradeInfo->append("接收第"+str+"帧: "+hexBuff.toUpper());
                ui->textEdit_firmwareUpgradeInfo->append("");
            }

            if (pack_number <= firmwareUpgrade_framesSum)//请求的序列号不超过最大序列号，表明还有数据没发完
            {
                if (enUpdateState == UPDATE_STATE_SEND_PACK_LEN
                    && pack_number == 1)
                {
                    enUpdateState = UPDATE_STATE_SEND_PACK;
                }
                if (enUpdateState != UPDATE_STATE_SEND_PACK)
                {
                    qDebug()<<"Update state is not send pack len"<<enUpdateState;
                    QString strNum = QString::number(7);//状态错误
                    ui->textEdit_firmwareUpgradeInfo->append("错误码："+strNum);
                    this->on_handleFirmwareUpgradeError();
                    return;
                }
                this->sendOnePack(PACKAGE_TYPE_FILE_DATA);//发送第n帧数据
            }
            else //请求的序列号超过了最大序列号，表明bin文件已经发送完成
            {
                if (enUpdateState != UPDATE_STATE_SEND_PACK)
                {
                    qDebug()<<"Update state is not send pack"<<enUpdateState;
                    QString strNum = QString::number(7);//状态错误
                    ui->textEdit_firmwareUpgradeInfo->append("错误码："+strNum);
                    this->on_handleFirmwareUpgradeError();
                    return;
                }
                enUpdateState = UPDATE_STATE_SEND_END;
                this->sendOnePack(PACKAGE_TYPE_FILE_SEND_END);//发送指令，表明更新包已经全部发送完成
            }
        }
        else if (buf[3] == 0x03)//升级完成
        {
            if (enUpdateState != UPDATE_STATE_SEND_END)
            {
                qDebug()<<"Update state is not send pack"<<enUpdateState;
                QString strNum = QString::number(7);//状态错误
                ui->textEdit_firmwareUpgradeInfo->append("错误码："+strNum);
                this->on_handleFirmwareUpgradeError();
                return;
            }
            qDebug()<<"<<--：升级完成";
            qDebug()<<"respond:"<<hexBuff;
            if (ui->checkBox_firmwareUpgrade_showData->isChecked())
            {
                QString str = QString::number(packCnt+1);
                ui->textEdit_firmwareUpgradeInfo->append("接收第"+str+"帧: "+hexBuff.toUpper());
                ui->textEdit_firmwareUpgradeInfo->append("");
            }
            ui->textEdit_firmwareUpgradeInfo->append("更新成功！");
            enUpdateState = UPDATE_STATE_IDLE;
            firmwareUpgradeTimer->stop();
            QMessageBox::information(this, "提示", "更新成功！");//结束发送
            ui->pushButton_firmwareUpgrade_startUpgrade->setText("开始升级");
        }
    }
}

void MainWindow::clearRxBuff()
{
    rxBytesCounter = 0;
    ui->label_rxCounter->setText(QString("%1%2").arg("RX:").arg(rxBytesCounter));
    ui->textEdit_Rx->clear();
}

void MainWindow::clearTxBuff()
{
    txBytesCounter = 0;
    ui->label_txCounter->setText(QString("%1%2").arg("TX:").arg(txBytesCounter));
    ui->textEdit_Tx->clear();
}

void MainWindow::filesTransmit_openFile()
{
//    QString path = QDir::currentPath();  //系统当前目录
    QString path = QCoreApplication::applicationDirPath();//APP绝对路径
    QString dlgTitle = "打开文件";  //对话框标题
    QString filter = "所有文件(*.*);;\
                      文本文件(*.txt);;\
                      二进制文件(*.bin);;\
                      十六进制文件(*.hex);;\
                      图片(*.png *.jpg *.jpeg *.bmp *.ico *.gif);;\
                      音频、视频文件(*.audio *.video)"; //文件过滤器

    QString filePath = QFileDialog::getOpenFileName(this,dlgTitle,path,filter);
    QFileInfo fileInfo(filePath);

    ui->textEdit_filesTransmitInfo->append("打开文件");
    qDebug()<<"filePath="<<filePath;
    if (filePath.isEmpty())
    {
        ui->textEdit_filesTransmitInfo->append("取消打开文件！");
//        QMessageBox::warning(this, "警告", "文件路径为空");
        return;
    }

    //文件路径显示到信息框
    ui->textEdit_filesTransmitInfo->append(filePath);

    QFile file(filePath);
    if (file.exists() == false)
    {
        ui->textEdit_filesTransmitInfo->append("警告：文件不存在！");
        QMessageBox::warning(this, "警告", "文本不存在");
        return;
    }

    if (file.open(QIODevice::ReadOnly) == false)
    {
        ui->textEdit_filesTransmitInfo->append("警告：文件打开失败！");
        QMessageBox::warning(this, "警告", "打开失败");
        return;
    }

    //判断文件类型
    int type = 0;
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(filePath);
    QString stringFile(filePath);
    qDebug()<<"mime.name = "<<mime.name();
    if (mime.name().startsWith("text/") &&
        stringFile.contains(".hex") == false)//------注意：HEX文件打开时是"text/plain"，保存时是"application/x-zerosize"
    {
        type = 1;//文本文件--eg. text/plain,text/html/,text/css,text/javascript
        qDebug()<<"Type of open file：text file.";
    }
    else if (mime.name().startsWith("application/") ||
             stringFile.contains(".hex") == true)
    {
        type = 2;//二进制文件--eg. application/xml,application/pdf
        qDebug()<<"Type of open file：hex file.";
    }
    else if (mime.name().startsWith("image/"))
    {
        type = 3;//图像文件--eg. image/gif,image/png,image/jpeg,image/bmp
        qDebug()<<"Type of open file：image file.";
    }
    else if (mime.name().startsWith("audio/"))
    {
        type = 4;//音频文件--eg. audio/wav,audio/midi,audio/mpeg,audio/webm
        qDebug()<<"Type of open file：audio file.";
    }
    else if (mime.name().startsWith("video/"))
    {
        type = 5;//视频文件--eg. video/mp4,video/x-flv,video/webm
        qDebug()<<"Type of open file：video file.";
    }
    ifSendWithText = false;
    //读取文件
    filesTransmit_fileByte = file.readAll();//读取文件所有数据
    file.close();
    switch (type)
    {
        case 1:
        {
            ifSendWithText = true;

            /* 判断编码 */
            QTextCodec::ConverterState state;
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");//由于应用程序默认的编码是utf-8，所以需要让解码器设置为utf-8
            FileText = codec->toUnicode(filesTransmit_fileByte.constData(),filesTransmit_fileByte.size(),&state);//将数据格式转换成解码器的格式，转换的状态保存在state中
            //若有无效字符则是GBK编码
            if (state.invalidChars > 0)
            {
                qDebug()<<"需要转码";
                //转码后返回
                FileText = QTextCodec::codecForName("GBK")->toUnicode(filesTransmit_fileByte);//将GBK编码格式转换为编码器格式(此处编码器格式为utf-8)
                filesTransmit_fileByte = FileText.toLatin1();
            }
            else
            {
                qDebug()<<"无需转码";
                FileText =  filesTransmit_fileByte;
            }
        }break;
        case 2:
        case 3:
        case 4:
        case 5:
            break;
    }

    if (FileText.isEmpty() && filesTransmit_fileByte.isEmpty())
    {
        ui->textEdit_filesTransmitInfo->append("警告：文件内容为空！");
        QMessageBox::information(this, "提示", "文件内容空");
        return;
    }

    if (ifSendWithText) filesTransmit_fileLen = FileText.size();
    else filesTransmit_fileLen = filesTransmit_fileByte.size();
    qDebug()<<"filesTransmit_fileLen="<<filesTransmit_fileLen;
    ui->progressBar_filesTransmit->setValue(0);
    ui->label_filesTransmit_progress->setText(QString("%1/%2 %3").arg("0").arg(filesTransmit_fileLen).arg("bytes"));
    filesTransmitCounter = 0;
    ui->lcdNumber_filesTransmit->display(0);
//    int init_frame_len;
//    if (filesTransmit_fileLen < 1024) init_frame_len = 128;
//    else
//    {
//        init_frame_len = filesTransmit_fileLen / 100;
//        if (filesTransmit_fileLen % 100) init_frame_len = filesTransmit_fileLen / 100 + 1;
//        else init_frame_len = filesTransmit_fileLen / 100;
//    }
//    ui->lineEdit_filesTransmit_frameLen->setText(QString("%1").arg(init_frame_len));

//    qDebug()<<"file data:"<<FileText;
}

void MainWindow::firmwareUpgrade_openFile()
{
//    QString path = QDir::currentPath();  //系统当前目录
    QString path = QCoreApplication::applicationDirPath();//APP绝对路径
    QString dlgTitle = "打开文件";  //对话框标题
    QString filter = "二进制文件(*.bin)"; //文件过滤器
    QString filePath = QFileDialog::getOpenFileName(this,dlgTitle,path,filter);
    QFileInfo fileInfo(filePath);

    ui->textEdit_firmwareUpgradeInfo->append("打开文件");
    qDebug()<<"filePath="<<filePath;
    if (filePath.isEmpty())
    {
        ui->textEdit_firmwareUpgradeInfo->append("取消打开文件！");
//        QMessageBox::warning(this, "警告", "文件为空");
        return;
    }

    //文件路径显示到发送框
    ui->textEdit_firmwareUpgradeInfo->append(filePath);

    QFile file(filePath);
    if (file.exists() == false)
    {
        ui->textEdit_firmwareUpgradeInfo->append("警告：文件不存在！");
        QMessageBox::warning(this, "警告", "文本不存在");
        return;
    }

    if (file.open(QIODevice::ReadOnly) == false)
    {
        QMessageBox::warning(this, "警告", "打开失败");
        return;
    }

    //读取文件
    firmwareUpgrade_fileByte = file.readAll();//读取文件所有数据
    file.close();

    if (firmwareUpgrade_fileByte.isEmpty())
    {
        ui->textEdit_firmwareUpgradeInfo->append("文件内容为空！请选择有效文件！");
        QMessageBox::information(this, "提示", "文件内容空");
        return;
    }

    firmwareUpgrade_fileLen = firmwareUpgrade_fileByte.size();
    qDebug()<<"firmwareUpgrade_fileLen="<<firmwareUpgrade_fileLen;

    ui->progressBar_firmwareUpgrade->setValue(0);
    ui->label_firmwareUpgrade_progress->setText(QString("%1/%2 %3").arg("0").arg(firmwareUpgrade_fileLen).arg("bytes"));
    firmwareUpgradeCounter = 0;
    ui->lcdNumber_firmwareUpgrade->display(0);
//    qDebug()<<"file data:"<<FileText;
    //    this->sendFile();
}

int MainWindow::filesOperation_openOneFile(QByteArray *filesOperation_fileByte, int index)
{
//    QByteArray filesOperation_fileByte;//读取到的文件数据
    int filesOperation_fileLen;//文件字节大小
    QString path = QCoreApplication::applicationDirPath();//APP绝对路径
    QString dlgTitle = "打开文件";  //对话框标题

#if 1
    QString filter = "二进制文件(*.bin)"; //文件过滤器
#else
    QString filter = "二进制文件(*.bin);;\
                      十六进制文件(*.hex);;\
                      字库文件(*.FON);;\
                      文本文件(*.txt);;\
                      图片(*.png *.jpg *.jpeg *.bmp *.ico *.gif);;\
                      音频、视频文件(*.audio *.video);;\
                      所有文件(*.*)"; //文件过滤器
#endif

    QString filePath = QFileDialog::getOpenFileName(this,dlgTitle,path,filter);
    QFileInfo fileInfo(filePath);

//    ui->textEdit_filesOperationInfo->append("打开文件...");
    qDebug()<<"filePath="<<filePath;
    if (filePath.isEmpty())
    {
        ui->textEdit_filesOperationInfo->append("取消打开文件！");
        return 0;
    }

    //文件路径显示到发送框
    ui->textEdit_filesOperationInfo->append(filePath);

    QFile file(filePath);
    if (file.exists() == false)
    {
        ui->textEdit_filesOperationInfo->append("警告：文件不存在！");
        QMessageBox::warning(this, "警告", "文本不存在");
        return 0;
    }

    if (file.open(QIODevice::ReadOnly) == false)
    {
        QMessageBox::warning(this, "警告", "打开失败");
        return 0;
    }

    //读取文件
    filesOperation_fileByte[index] = file.readAll();//读取文件所有数据
    file.close();

    if (filesOperation_fileByte[index].isEmpty())
    {
        ui->textEdit_filesOperationInfo->append("文件内容为空！请选择有效文件！");
        QMessageBox::information(this, "提示", "文件内容空");
        return 0;
    }

    filesOperation_fileLen = filesOperation_fileByte[index].size();
    qDebug()<<"filesOperation_fileLen="<<filesOperation_fileLen;

//    ui->progressBar_firmwareUpgrade->setValue(0);
//    ui->label_firmwareUpgrade_progress->setText(QString("%1/%2 %3").arg("0").arg(filesOperation_fileLen).arg("bytes"));
//    firmwareUpgradeCounter = 0;
//    ui->lcdNumber_firmwareUpgrade->display(0);
//    qDebug()<<"file data:"<<FileText;
    //    this->sendFile();

    ui->textEdit_filesOperationInfo->append("文件大小：" + QString::number(filesOperation_fileLen) + " 字节");

    return filesOperation_fileLen;
}
void MainWindow::filesOperation_openFiles()
{
    int fileLenth = 0;

    filesOperation_index++;
    if (filesOperation_index >= 10)
    {
        qDebug() <<"清除文件";
        ui->textEdit_filesOperationInfo->append("\r\n清除文件");
        filesOperation_index = 0;
        filesOperation_newFileByte.clear();
        ui->lineEdit_filesOperation_filesNum->setText(QString::number(0));
    }
    qDebug() <<"打开第"<< filesOperation_index + 1 << "个文件...";
    ui->textEdit_filesOperationInfo->append("\r\n打开第"+QByteArray::number(filesOperation_index + 1)+"个文件");
    filesOperation_filesByte[filesOperation_index].clear();
    fileLenth = this->filesOperation_openOneFile(filesOperation_filesByte, filesOperation_index);
    ui->lineEdit_filesOperation_filesNum->setText(QString::number(filesOperation_index + 1));
    if (fileLenth)
    {
        filesOperation_newFileByte.append(filesOperation_filesByte[filesOperation_index]);
        filesOperation_fileLen[filesOperation_index] = fileLenth;
    }
    else
    {
        filesOperation_index--;
    }
}

void MainWindow::filesTransmit_sendFile()
{
    if (ui->pushButton_filesTransmit_startTransmit->text() == "开始传输")
    {
        if (FileText.isEmpty() && filesTransmit_fileByte.isEmpty())
        {
            qDebug()<<"文件内容为空！";
            ui->textEdit_filesTransmitInfo->append("文件内容为空！请先打开文件！");
            QMessageBox::warning(this, "错误", "文件为空！请先打开文件！");
            return;
        }

        ui->pushButton_filesTransmit_startTransmit->setText("取消传输");
        ui->textEdit_filesTransmitInfo->append("开始传输文件......");
        int frameGap = ui->lineEdit_filesTransmit_frameGap->text().toInt();
        filesTransmit_eachFrameLen = ui->lineEdit_filesTransmit_frameLen->text().toInt();
        filesTransmit_framesSum = filesTransmit_fileLen / filesTransmit_eachFrameLen;//帧总数量
        if (filesTransmit_fileLen % filesTransmit_eachFrameLen)
        {
            filesTransmit_framesSum += 1;
        }

        qDebug()<<"filesTransmit_framesSum="<<filesTransmit_framesSum;
        qDebug()<<"filesTransmit_eachFrameLen="<<filesTransmit_eachFrameLen;
        qDebug()<<"frameGap="<<frameGap;

        filesTransmit_framesCounter = 0;//帧计数
        filesTransmit_progressCount = 0;//进度条计数
        ui->progressBar_filesTransmit->setValue(0);
        ui->label_filesTransmit_progress->setText(QString("%1/%2 %3").arg("0").arg(filesTransmit_fileLen).arg("bytes"));
        filesTransmitCounter = 0;
        ui->lcdNumber_filesTransmit->display(0);
        filesTransmitTimer->start(100);

        //一次性发送全部
        if (filesTransmit_eachFrameLen <= 0 || filesTransmit_eachFrameLen >= filesTransmit_fileLen)//帧大小不在文件大小范围内
        {
            qDebug()<<"不分包发送";
            if (ifSendWithText) serial->write(FileText.toLocal8Bit());
            else serial->write(filesTransmit_fileByte);

            //将要发送的数据显示到发送窗口
    #if 1
            if (ui->checkBox_filesTransmit_showData->isChecked())
            {
                if (ifSendWithText) ui->textEdit_filesTransmitInfo->append(FileText.toLocal8Bit());
                else
                {
                    QByteArray byte;
                    int j = 0;
                    for (int i = 0; i < filesTransmit_fileByte.toHex().size(); i += 2)
                    {
                        byte[j++] = filesTransmit_fileByte.toHex().at(i);
                        byte[j++] = filesTransmit_fileByte.toHex().at(i+1);
                        byte[j++] = ' ';
                    }
                    ui->textEdit_filesTransmitInfo->append(byte.toUpper());
                }
            }
    #endif
            ui->textEdit_filesTransmitInfo->append("文件发送完成！");
            ui->progressBar_filesTransmit->setValue(100);
            ui->label_filesTransmit_progress->setText(QString("%1/%2 %3").arg(filesTransmit_fileLen).arg(filesTransmit_fileLen).arg("bytes"));
            filesTransmitCounter = 0;
            filesTransmitTimer->stop();
            QMessageBox::information(this, "提示", "文件传输完成！");
            return;
        }

        if (frameGap <= 0)
        {
            frameGap = 1;
        }

        fileSendTimer->start(frameGap);
    }
    else if (ui->pushButton_filesTransmit_startTransmit->text() == "取消传输")
    {
        ui->pushButton_filesTransmit_startTransmit->setText("开始传输");
        ui->textEdit_filesTransmitInfo->append("取消传输！");

        filesTransmit_framesCounter = 0;//帧计数
        filesTransmit_progressCount = 0;//进度条计数
        ui->progressBar_filesTransmit->setValue(0);
        ui->label_filesTransmit_progress->setText(QString("%1/%2 %3").arg("0").arg(filesTransmit_fileLen).arg("bytes"));
        filesTransmitCounter = 0;
        filesTransmitTimer->stop();
        fileSendTimer->stop();
    }
}

void MainWindow::firmwareUpgrade_sendFile()
{
    if (ui->pushButton_firmwareUpgrade_startUpgrade->text() == "开始升级")
    {
        if (flag_update_firmware_disable)
        {
            ui->textEdit_firmwareUpgradeInfo->append("旧字库擦除中，请稍后再试！");
            QMessageBox::warning(this, "错误", "旧字库擦除中，请稍后再试！");
            return;
        }

        if (firmwareUpgrade_fileByte.isEmpty())
        {
            qDebug()<<"文件内容为空！";
            ui->textEdit_firmwareUpgradeInfo->append("文件内容为空！请重新打开文件！");
            QMessageBox::warning(this, "错误", "文件为空！请重新打开文件！");
            return;
        }
        ui->pushButton_firmwareUpgrade_startUpgrade->setText("取消升级");

        ui->textEdit_firmwareUpgradeInfo->append("开始更新固件......");
        firmwareUpgrade_eachFrameLen = ui->lineEdit_firmwareUpgrade_frameLen->text().toInt();
        firmwareUpgrade_framesSum = firmwareUpgrade_fileLen / firmwareUpgrade_eachFrameLen;//帧总数量
        if (firmwareUpgrade_fileLen % firmwareUpgrade_eachFrameLen)
        {
            firmwareUpgrade_framesSum += 1;
        }

        firmwareUpgrade_framesCounter = 0;//帧计数
        firmwareUpgrade_progressCount = 0;//进度条计数
        ui->progressBar_firmwareUpgrade->setValue(0);
        ui->label_firmwareUpgrade_progress->setText(QString("%1/%2 %3").arg("0").arg(firmwareUpgrade_fileLen).arg("bytes"));
        firmwareUpgradeCounter = 0;
        ui->lcdNumber_firmwareUpgrade->display(0);
        firmwareUpgradeTimer->start(100);
        //先发送第一帧数据
        this->sendOnePack(PACKAGE_TYPE_UPDATE_REQUEST);//发送更新请求
    }
    else if (ui->pushButton_firmwareUpgrade_startUpgrade->text() == "取消升级")
    {
        ui->textEdit_firmwareUpgradeInfo->append("取消更新固件！");

        QString strNum = QString::number(6);//中断
        ui->textEdit_firmwareUpgradeInfo->append("错误码："+strNum);
        this->on_handleFirmwareUpgradeError();
        firmwareUpgradeTimeoutTimer->stop();
    }
}

void MainWindow::on_handle_filesOperation_mergeFiles()
{
//    for (int i = 0; i < filesOperation_index + 1; i++)
//    {
//        filesOperation_newFileByte.append(filesOperation_filesByte[i]);
//    }

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
    QString path = QCoreApplication::applicationDirPath();//APP绝对路径
    path.append("/merge/");

    bool exist;
    QDir *folder = new QDir;
    exist = folder->exists(path);//查看目录是否存在
    if(!exist)//不存在就创建
    {
        bool ok = folder->mkdir(path);
        if(!ok)
        {
            QMessageBox::warning(this,tr("创建目录"),tr("创建失败"));
            return;
        }
    }

    path.append(str);//文件名追加时间(以时间命名文件)
    qDebug()<<"path:"<<path;

    //获取带路径的文件名，并且弹出保存窗口
#if 1
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存为"), path, \
                                                    "bin files(*.bin)");
#else
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存为"), path, \
                                                    "bin files(*.bin);;\
                                                     hex files(*.hex);;\
                                                     txt files(*.txt);;\
                                                     jpeg files(*.jpeg);;\
                                                     jpg files(*.jpg);;\
                                                     png files(*.png);;\
                                                     bmp files(*.bmp);;\
                                                     gif files(*.gif);;\
                                                     ico files(*.ico);;\
                                                     all files(*.*)");
#endif

    qDebug()<<"fileName:"<<fileName;

    if (fileName.isNull())
    {
        return;
    }
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly))
    {
        qDebug()<<"error";
        QMessageBox::warning(this, tr("Error"), tr("Failed to open file!"));
        return;
    }

    ui->textEdit_filesOperationInfo->append("\r\n文件保存成功，大小：" + QString::number(filesOperation_newFileByte.size()) + " 字节");
    ui->textEdit_filesOperationInfo->append("保存路径：" + fileName);
    f.write(filesOperation_newFileByte);//转换为QByteArray形式，将接收区的数据写到f文件中
}

void MainWindow::on_handleFirmwareUpgradeError()
{
    enUpdateState = UPDATE_STATE_IDLE;
    ui->textEdit_firmwareUpgradeInfo->append("提示：\r\n 错误码  错误原因\r\n   1     帧头错误\r\n   2     帧长度错误\r\n   3     校验码错误\r\n   4     下位机反馈的错误\r\n   5     接收超时\r\n   6     用户取消更新\r\n   7     状态错误");
    ui->textEdit_firmwareUpgradeInfo->append("更新失败！");

    firmwareUpgradeTimeoutTimer->stop();
    firmwareUpgrade_framesCounter = 0;//帧计数
    firmwareUpgrade_progressCount = 0;//进度条计数
    firmwareUpgradeCounter = 0;
    ui->progressBar_firmwareUpgrade->setValue(0);
    ui->label_firmwareUpgrade_progress->setText(QString("%1/%2 %3").arg("0").arg(firmwareUpgrade_fileLen).arg("bytes"));

    firmwareUpgradeTimer->stop();
    QMessageBox::warning(this, "错误", "升级失败！");
    ui->pushButton_firmwareUpgrade_startUpgrade->setText("开始升级");
}

void MainWindow::sendOnePack(int packType)
{
    QByteArray sendBuf;
    QByteArray dataBuf;
    int checksum = 0;

    sendBuf.clear();
    dataBuf.clear();
    sendBuf.append("\xA9\x54");//head

    switch (packType)
    {
        case PACKAGE_TYPE_UPDATE_REQUEST:
        {
            enUpdateState = UPDATE_STATE_SEND_UPDATE_REQUEST;
            qDebug()<<"-->>：请求下发更新包";
            //data length
            sendBuf.append(static_cast<char>(0x00));
            sendBuf.append(static_cast<char>(0x00));
            //cmd
            sendBuf.append("\xE1");
            //package serial number
            sendBuf.append(static_cast<char>(0x00));
            sendBuf.append(static_cast<char>(0x00));
        }break;
        case PACKAGE_TYPE_PACKAGE_SUM:
        {
            qDebug()<<"-->>：更新包数量";
            //data length
            sendBuf.append(static_cast<char>(0x00));
            sendBuf.append(static_cast<char>(0x02));
            //cmd
            sendBuf.append("\xE2");
            //package serial number
            sendBuf.append(static_cast<char>(0x00));
            sendBuf.append(static_cast<char>(0x00));
//            //data (file length)
//            sendBuf.append(static_cast<char>((firmwareUpgrade_fileLen>>8)&0xFF));
//            sendBuf.append(static_cast<char>(firmwareUpgrade_fileLen&0xFF));
            //data (pack sum)
            sendBuf.append(static_cast<char>((firmwareUpgrade_framesSum>>8)&0xFF));
            sendBuf.append(static_cast<char>(firmwareUpgrade_framesSum&0xFF));
        }break;
        case PACKAGE_TYPE_FILE_DATA:
        {
//            qDebug()<<"-->>：更新包数据";
            this->firmwareUpgrade_updateProgressBar();

            //data length
//            qDebug()<<"firmwareUpgrade_sendFrameLen ="<<firmwareUpgrade_sendFrameLen;
            sendBuf.append(static_cast<char>((firmwareUpgrade_sendFrameLen>>8)&0xFF));
            sendBuf.append(static_cast<char>(firmwareUpgrade_sendFrameLen&0xFF));
            //cmd
            sendBuf.append("\xE3");
            //package serial number
//            qDebug()<<"firmwareUpgrade_eachFrameLen ="<<firmwareUpgrade_eachFrameLen;
//            qDebug()<<"firmwareUpgrade_framesCounter ="<<firmwareUpgrade_framesCounter;
            dataBuf = firmwareUpgrade_fileByte.mid(firmwareUpgrade_eachFrameLen * (firmwareUpgrade_framesCounter-1), firmwareUpgrade_sendFrameLen);
//            qDebug()<<"dataBuf ="<<dataBuf;
            sendBuf.append(static_cast<char>((firmwareUpgrade_framesCounter>>8)&0xFF));
            sendBuf.append(static_cast<char>(firmwareUpgrade_framesCounter&0xFF));
            //data
            sendBuf.append(dataBuf);
        }break;
        case PACKAGE_TYPE_FILE_SEND_END:
        {
            qDebug()<<"-->>：更新包发送完成";
            //data length
            sendBuf.append(static_cast<char>(0x00));
            sendBuf.append(static_cast<char>(0x00));
            //cmd
            sendBuf.append("\xE4");
            //package serial number
            sendBuf.append(static_cast<char>(0x00));
            sendBuf.append(static_cast<char>(0x00));
        }break;
    }
    for(int i = 0; i < sendBuf.size(); i++){
        checksum += sendBuf.at(i) & 0xff;
    }

    //checksum
    sendBuf.append(static_cast<char>((checksum>>8)&0xFF));
    sendBuf.append(static_cast<char>(checksum&0xFF));
    serial->write(sendBuf);

    QByteArray byte;
    int j = 0;
    for (int i = 0; i < sendBuf.toHex().size(); i += 2)
    {
        byte[j++] = sendBuf.toHex().at(i);
        byte[j++] = sendBuf.toHex().at(i+1);
        byte[j++] = ' ';
    }
//    qDebug()<<"send:"<<byte;
    if (ui->checkBox_firmwareUpgrade_showData->isChecked())
    {
        if (packType == PACKAGE_TYPE_UPDATE_REQUEST)
        {
            ui->textEdit_firmwareUpgradeInfo->append("发送第0帧: "+byte.toUpper());
        }
        else if (packType == PACKAGE_TYPE_PACKAGE_SUM)
        {
            ui->textEdit_firmwareUpgradeInfo->append("发送第1帧: "+byte.toUpper());
        }
        else if (packType == PACKAGE_TYPE_FILE_DATA)
        {
            QString str = QString::number(firmwareUpgrade_framesCounter+1);
            ui->textEdit_firmwareUpgradeInfo->append("发送第"+str+"帧: "+byte.toUpper());
        }
        else if (packType == PACKAGE_TYPE_FILE_SEND_END)
        {
            QString str = QString::number(firmwareUpgrade_framesCounter+2);
            ui->textEdit_firmwareUpgradeInfo->append("发送第"+str+"帧: "+byte.toUpper());
        }
    }
    firmwareUpgradeTimeoutTimer->start(10000);
}

void MainWindow::filesTransmit_updateProgressBar()
{
    int hadSendBytes;
    filesTransmit_framesCounter++;
    if (filesTransmit_framesCounter < filesTransmit_framesSum)
    {
        filesTransmit_sendFrameLen = filesTransmit_eachFrameLen;
        //更新进度条
        filesTransmit_progressCount = (filesTransmit_framesCounter *100)/filesTransmit_framesSum;
        hadSendBytes = filesTransmit_eachFrameLen * (filesTransmit_framesCounter-1);
    }
    else //最后一帧
    {
        if (filesTransmit_fileLen % filesTransmit_eachFrameLen)
        {
            filesTransmit_sendFrameLen = filesTransmit_fileLen % filesTransmit_eachFrameLen;
        }
        else
        {
            filesTransmit_sendFrameLen = filesTransmit_eachFrameLen;
        }
        filesTransmit_progressCount = 100;
        hadSendBytes = filesTransmit_eachFrameLen * (filesTransmit_framesCounter-1) + filesTransmit_sendFrameLen;
        fileSendTimer->stop();
    }
//    qDebug()<<"filesTransmit_fileLen="<<filesTransmit_fileLen;
//    qDebug()<<"filesTransmit_eachFrameLen="<<filesTransmit_eachFrameLen;
//    qDebug()<<"filesTransmit_framesSum="<<filesTransmit_framesSum;
//    qDebug()<<"filesTransmit_sendFrameLen="<<filesTransmit_sendFrameLen;
//    qDebug()<<"filesTransmit_framesCounter="<<filesTransmit_framesCounter;
//    qDebug()<<"filesTransmit_progressCount="<<filesTransmit_progressCount<<endl;

    ui->progressBar_filesTransmit->setValue(filesTransmit_progressCount);
    ui->label_filesTransmit_progress->setText(QString("%1/%2 %3").arg(hadSendBytes).arg(filesTransmit_fileLen).arg("bytes"));
}

void MainWindow::firmwareUpgrade_updateProgressBar()
{
    int hadSendBytes;
    firmwareUpgrade_framesCounter++;
    if (firmwareUpgrade_framesCounter < firmwareUpgrade_framesSum)
    {
        firmwareUpgrade_sendFrameLen = firmwareUpgrade_eachFrameLen;
        //更新进度条
        firmwareUpgrade_progressCount = (firmwareUpgrade_framesCounter *100)/firmwareUpgrade_framesSum;
        hadSendBytes = firmwareUpgrade_eachFrameLen * (firmwareUpgrade_framesCounter-1);
    }
    else //最后一帧
    {
        if (firmwareUpgrade_fileLen % firmwareUpgrade_eachFrameLen)
        {
            firmwareUpgrade_sendFrameLen = firmwareUpgrade_fileLen % firmwareUpgrade_eachFrameLen;
        }
        else
        {
            firmwareUpgrade_sendFrameLen = firmwareUpgrade_eachFrameLen;
        }
        firmwareUpgrade_progressCount = 100;
        hadSendBytes = firmwareUpgrade_eachFrameLen * (firmwareUpgrade_framesCounter-1) + firmwareUpgrade_sendFrameLen;
    }
//    qDebug()<<"firmwareUpgrade_framesSum="<<firmwareUpgrade_framesSum;
//    qDebug()<<"firmwareUpgrade_sendFrameLen="<<firmwareUpgrade_sendFrameLen;
//    qDebug()<<"firmwareUpgrade_framesCounter="<<firmwareUpgrade_framesCounter;
//    qDebug()<<"firmwareUpgrade_progressCount="<<firmwareUpgrade_progressCount<<endl;

    ui->progressBar_firmwareUpgrade->setValue(firmwareUpgrade_progressCount);
    ui->label_firmwareUpgrade_progress->setText(QString("%1/%2 %3").arg(hadSendBytes).arg(firmwareUpgrade_fileLen).arg("bytes"));
}

void MainWindow::fileTimerSend()
{
    QByteArray dataToSend;
    this->filesTransmit_updateProgressBar();
    if (ifSendWithText)
    {
        dataToSend = FileText.mid(filesTransmit_eachFrameLen * (filesTransmit_framesCounter-1), filesTransmit_sendFrameLen).toLocal8Bit();
//        qDebug()<<"text data："<<dataToSend;
        if (ui->checkBox_filesTransmit_showData->isChecked())
        {
            ui->textEdit_filesTransmitInfo->append(dataToSend);
        }
    }
    else
    {
        dataToSend =filesTransmit_fileByte.mid(filesTransmit_eachFrameLen * (filesTransmit_framesCounter-1), filesTransmit_sendFrameLen);

        QByteArray byte;
        int j = 0;
        for (int i = 0; i < dataToSend.toHex().size(); i += 2)
        {
            byte[j++] = dataToSend.toHex().at(i);
            byte[j++] = dataToSend.toHex().at(i+1);
            byte[j++] = ' ';
        }
//        qDebug()<<"hex data："<<byte.toUpper();
        if (ui->checkBox_filesTransmit_showData->isChecked())
        {
            ui->textEdit_filesTransmitInfo->append(byte.toUpper());
        }
    }

    serial->write(dataToSend);
    if (filesTransmit_framesCounter >= filesTransmit_framesSum)
    {
        ui->textEdit_filesTransmitInfo->append("文件发送完成！");
        filesTransmitTimer->stop();
        QMessageBox::information(this, "提示", "文件传输完成！");
        ui->pushButton_filesTransmit_startTransmit->setText("开始传输");
    }
}

void MainWindow::on_handleFiresTransmitCounter()
{
    filesTransmitCounter++;
    float filesTransmitSeconds = filesTransmitCounter / 10;
    ui->lcdNumber_filesTransmit->display(filesTransmitSeconds);
}

void MainWindow::on_handleFirmwareUpgradeCounter()
{
    firmwareUpgradeCounter++;
    float firmwareUpgradeSeconds = firmwareUpgradeCounter / 10;
    ui->lcdNumber_firmwareUpgrade->display(firmwareUpgradeSeconds);
}

void MainWindow::on_handleFirmwareUpgradeTimeout()
{
    QString strNum = QString::number(5);//超时
    ui->textEdit_firmwareUpgradeInfo->append("错误码："+strNum);
    this->on_handleFirmwareUpgradeError();
}

void MainWindow::on_handleRequestUpdateFontTimeout()
{
    requestUpdateFontTimeoutTimer->stop();
    ui->textEdit_firmwareUpgradeInfo->append("请求失败：下位机响应超时！");
    QMessageBox::warning(this,tr("错误"),tr("请求失败：下位机响应超时！"));
}

void MainWindow::on_handleEraseFontTimeout()
{
    QString textBuff = ui->textEdit_firmwareUpgradeInfo->toPlainText();//获取接收区原本的数据
    ui->textEdit_firmwareUpgradeInfo->setText(textBuff + ".");
    eraseFontTimerCounter++;
    if (eraseFontTimerCounter >= 300)//5min
    {
        eraseFontTimerCounter = 0;
        eraseFontTimeoutTimer->stop();
        ui->textEdit_firmwareUpgradeInfo->append("擦除失败：下位机响应超时！");
        QMessageBox::warning(this,tr("错误"),tr("擦除失败：下位机响应超时！"));
    }
}

void MainWindow::saveFile()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
//    QString path = "./log/";
    QString path = QCoreApplication::applicationDirPath();//APP绝对路径
    path.append("/log/");

    bool exist;
    QDir *folder = new QDir;
    exist = folder->exists(path);//查看目录是否存在
    if(!exist)//不存在就创建
    {
        bool ok = folder->mkdir(path);
        if(!ok)
        {
            QMessageBox::warning(this,tr("创建目录"),tr("创建失败"));
            return;
        }
    }

    path.append(str);//文件名追加时间(以时间命名文件)
//    path.append(".txt");//文件名追加后缀
    qDebug()<<"path:"<<path;

    //获取带路径的文件名，并且弹出保存窗口
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存为"), path, \
                                                    "txt files(*.txt);;\
                                                     bin files(*.bin);;\
                                                     hex files(*.hex);;\
                                                     jpeg files(*.jpeg);;\
                                                     jpg files(*.jpg);;\
                                                     png files(*.png);;\
                                                     bmp files(*.bmp);;\
                                                     gif files(*.gif);;\
                                                     ico files(*.ico);;\
                                                     all files(*.*)");
//    path.append(".txt");//文件名追加后缀
    qDebug()<<"fileName:"<<fileName;

    if (fileName.isNull())
    {
        return;
    }
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly))
    {
        qDebug()<<"error";
        QMessageBox::warning(this, tr("Error"), tr("Failed to open file!"));
        return;
    }

    //判断文件类型
    QString textData = ui->textEdit_Rx->toPlainText();//获取接收区原本的数据
#if 1
    //方式1：
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(fileName);
    qDebug()<<"mime.name = "<<mime.name();
    if (mime.name().startsWith("text/"))
    {
        qDebug()<<"保存文件类型: 文本文件";
        f.write(textData.toLocal8Bit());//转换为QByteArray形式，将接收区的数据写到f文件中
    }
    //------注意：HEX文件打开时是"text/plain"，保存时是"application/x-zerosize"
    else if (mime.name().startsWith("application/") ||
             mime.name().startsWith("image/"))
#else
    //方式2：
    QString file(fileName);
    if (file.contains(".text"))

    {
        qDebug()<<"File type: 文本文件";
        f.write(textData.toLocal8Bit());//转换为QByteArray形式，将接收区的数据写到f文件中
    }
    else if (file.contains(".bin") ||
             file.contains(".hex") ||
             file.contains(".jpeg") ||
             file.contains(".jpg") ||
             file.contains(".pgn") ||
             file.contains(".bmp") ||
             file.contains(".gif") ||
             file.contains(".ico"))
#endif
#if 0
    {
        qDebug()<<"File type: 二进制文件";
        QByteArray hexData = textData.toLocal8Bit();
        QByteArray hexDataAddEmpty;
        for (int i = 0, j = 0 ; i < hexData.size(); i += 2)
        {
            hexDataAddEmpty[j++] = hexData[i];
            hexDataAddEmpty[j++] = hexData[i+1];
            hexDataAddEmpty[j++] = ' ';
        }
        QByteArray hex_to_str =QByteArray::fromHex(hexDataAddEmpty);

        f.write(hex_to_str);//转换为QByteArray形式，将接收区的数据写到f文件中
    }
#endif
    {
        /* 接收二进制文件时要以HEX显示，再把hex数据转换成字符数组 */
        qDebug()<<"保存文件类型: 二进制文件";
        QByteArray hexData = textData.toLocal8Bit();
        QByteArray newData = QByteArray::fromHex(hexData);
//        QByteArray hexDataAddEmpty;
//        for (int i = 0, j = 0 ; i < hexData.size(); i += 2)
//        {
//            hexDataAddEmpty[j++] = hexData[i];
//            hexDataAddEmpty[j++] = hexData[i+1];
//            hexDataAddEmpty[j++] = ' ';
//        }
//        QByteArray hex_to_str =QByteArray::fromHex(hexDataAddEmpty);

        f.write(newData);//转换为QByteArray形式，将接收区的数据写到f文件中
    }
}
#include <QStandardPaths>
void MainWindow::saveRxData()
{
#if 0
    //获取程序所在路径
        QString applicationDirPath = QCoreApplication::applicationDirPath();
        qDebug() << "applicationDirPath=" << applicationDirPath;

        //程序的完整路径
        QString applicationFilePath = qApp->applicationFilePath();
        qDebug() << "applicationFilePath=" << applicationFilePath;

        //当前工作目录
        QString currentPath = QDir::currentPath();
        qDebug() << "currentPath=" << currentPath;

        //用户目录路径
        QString HomeLocation = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        qDebug() << "HomeLocation=" << HomeLocation;

        QStringList HomeLocation2 = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
        qDebug() << "HomeLocation2=" << HomeLocation2[0];

        //我的文档路径
        QString DocumentsLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        qDebug() << "DocumentsLocation=" << DocumentsLocation;

        QStringList DocumentsLocation2 = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
        qDebug() << "DocumentsLocation2=" << DocumentsLocation2[0];

        //桌面路径
        QString DesktopLocation = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        qDebug() << "DesktopLocation=" << DesktopLocation;

        QStringList DesktopLocation2 = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
        qDebug() << "DesktopLocation2=" << DesktopLocation2[0];

        //程序数据存放路径
        QString AppDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        qDebug() << "AppDataLocation=" << AppDataLocation;

        QStringList AppDataLocation2 = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
        qDebug() << "AppDataLocation2=" << AppDataLocation2[0];

        /*Qt5.5 中引入了另一种方法*/
        QString AppConfigLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
        qDebug() << "AppConfigLocation=" << AppConfigLocation;

        QStringList AppConfigLocation2 = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);
        qDebug() << "AppConfigLocation2=" << AppConfigLocation2[0];

        //临时文件路径
        QString TempLocation = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
        qDebug() << "TempLocation=" << TempLocation;

        QStringList TempLocation2 = QStandardPaths::standardLocations(QStandardPaths::TempLocation);
        qDebug() << "TempLocation2=" << TempLocation2[0];

        //更传统的方法是利用QDir的一个静态函数tempPath()
        QString tempPath  = QDir::tempPath();
        qDebug() << "tempPath=" << tempPath;
#endif
#if 1
    if (ui->checkBox_saveDataToFile->isChecked() == false)
    {
        dataToWrite.clear();
        return;
    }

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyyMMdd_hhmmss"); //设置显示格式

    /* 方式1：文件另存为 */
    //获取程序所在路径
    pathForTextDataFile = QCoreApplication::applicationDirPath();
    pathForTextDataFile.append("/log/");

    bool exist;
    QDir *folder = new QDir;
    exist = folder->exists(pathForTextDataFile);//查看目录是否存在

    if(!exist)//不存在就创建
    {
        bool ok = folder->mkdir(pathForTextDataFile);
        if(ok)
        {
//            QMessageBox::warning(this,tr("创建目录"),tr("创建成功!"));//添加提示方便查看是否成功创建
        }
        else
        {
            QMessageBox::warning(this,tr("创建目录"),tr("创建失败"));
        }
    }

    pathForTextDataFile.append(str);//文件名追加时间(以时间命名文件)
    pathForTextDataFile.append(".txt");//文件名追加后缀
    qDebug()<<"pathForTextDataFile:"<<pathForTextDataFile;

    if (pathForTextDataFile.isNull())
    {
        return;
    }
    QFile f(pathForTextDataFile);
    if(!f.open(QIODevice::WriteOnly))
    {
        qDebug()<<"error";
        QMessageBox::warning(this, tr("Error"), tr("Failed to open file!"));
        return;
    }
    QMessageBox::information(this,"另存为",tr(pathForTextDataFile.toLatin1().data()));

    f.close();
#endif
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        QMessageBox::warning(this, tr("错误"), tr("断开连接"));
        this->closeUart();
    }
}

void MainWindow::on_textEdit_Rx_textChanged()
{
    ui->textEdit_Rx->moveCursor(QTextCursor::End);
}

void MainWindow::on_showAbout()
{
    QString aboutText = "版本号：V1.0.0\r\n\r\n\
固件升级流程：\r\n\
上位机                    下位机\r\n\
发送更新请求       --> 回复请求bin文件分包数量\r\n\
发送bin文件分包数--> 回复请求下一帧（第一帧）\r\n\
发送更新包          --> 回复请求下一帧\r\n\
发送更新包已发完  --> 回复更新成功\r\n\r\n\
主机发送：\r\n\
协议格式：9字节固定格式+数据\r\n\
首：0xA9,0x54\r\n\
数据长度：2字节n（除固定格式外的数据长度）\r\n\
命令：1字节\r\n\
包序号：2字节\r\n\
数据：n字节\r\n\
校验和：2字节\r\n\
{0xA9,0x54,0x00,0x00,0xE1,0x00,0x00,0x01,0xDE}//更新请求\r\n\
{0xA9,0x54,0x00,0x02,0xE2,0x00,0x00,0x00,0x10,0x01,0xF1}//bin文件分包数\r\n\
{0xA9,0x54,0x00,0x80,0xE3,0xNN,0xNN,0xXX,......,0xXX,0xCH,0xCH}//更新包\r\n\
{0xA9,0x54,0x00,0x00,0xE4,0x00,0x00,0xCH,0xCH}//更新包已发完\r\n\r\n\
从机回复：\r\n\
协议格式：6字节固定格式+数据\r\n\
首：0xAA,0x55\r\n\
数据长度：1字节n（除固定格式外的数据长度）\r\n\
命令：1字节\r\n\
数据：2字节\r\n\
校验和：2字节\r\n\
{0xAA,0x55,0x02,0x00,0x00,0x00,0x01,0x01},//升级文件错误\r\n\
{0xAA,0x55,0x02,0x01,0x00,0x00,0x01,0x02},//请求文件信息，数据包数量\r\n\
{0xAA,0x55,0x02,0x02,0x00,0x01,0x01,0x04},//请求下一帧数据\r\n\
{0xAA,0x55,0x02,0x03,0x00,0x00,0x01,0x04},//升级完成\r\n\r\n\
升级举例:(bin文件内容：F3 22 20 34 63 84 02 00 6F 00 20 06 F3 27 A0 7C)\r\n\
1.上位机发送更新请求信号：a9 54 00 00 e1 00 00 01 de\r\n\
下位机发送信号请求bin文件分包数量：aa 55 02 01 00 00 01 02\r\n\
2.上位机发送文件分包数为16字节：a9 54 00 02 e2 00 00 00 10 01 f1\r\n\
下位机发送信号请求第1帧数据：aa 55 02 02 00 01 01 04\r\n\
3.上位机发送更新包第1帧:a9 54 00 06 e3 00 01 f3 22 20 34 63 84 04 37\r\n\
下位机发送信号请求第2帧数据：aa 55 02 02 00 02 01 05\r\n\
4.上位机发送更新包第2帧:a9 54 00 06 e3 00 02 02 00 6f 00 20 06 02 7f\r\n\
下位机发送信号请求第3帧数据：aa 55 02 02 00 03 01 06\r\n\
5.上位机发送更新包第3帧:a9 54 00 04 e3 00 03 f3 27 a0 7c 04 1d\r\n\
下位机发送信号请求第4帧数据：aa 55 02 02 00 04 01 07\r\n\
6.上位机发送更新包已发完信号：a9 54 00 00 e4 00 00 01 e1\r\n\
下位机发送升级完成信号：aa 55 02 03 00 00 01 04";
              QMessageBox::information(this,"关于",aboutText);
}

