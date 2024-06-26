/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_about;
    QWidget *centralWidget;
    QComboBox *comboBox_portNum;
    QLabel *label_portNum;
    QComboBox *comboBox_baud;
    QLabel *label_baud;
    QComboBox *comboBox_dataBit;
    QLabel *label_dataBit;
    QComboBox *comboBox_stopBit;
    QLabel *label_stopBit;
    QComboBox *comboBox_checkBit;
    QLabel *label_checkBit;
    QComboBox *comboBox_flowBit;
    QLabel *label_flowBit;
    QPushButton *pushButton_openUart;
    QStackedWidget *stackedWidget;
    QWidget *page_sendAndReceive;
    QCheckBox *checkBox_cycleSend;
    QLabel *label_cycleSendTime;
    QPushButton *pushButton_send;
    QTextEdit *textEdit_Tx;
    QPushButton *pushButton_clearRx;
    QCheckBox *checkBox_showTime;
    QCheckBox *checkBox_saveDataToFile;
    QCheckBox *checkBox_ShowHex;
    QPushButton *pushButton_save;
    QTextEdit *textEdit_Rx;
    QCheckBox *checkBox_HexSend;
    QCheckBox *checkBox_addNewLine;
    QPushButton *pushButton_clearTx;
    QLineEdit *lineEdit_cycleDelay;
    QLabel *label_rxCounter;
    QLabel *label_txCounter;
    QWidget *page_sendFiles;
    QTextEdit *textEdit_filesTransmitInfo;
    QCheckBox *checkBox_filesTransmit_showData;
    QPushButton *pushButton_filesTransmit_clear;
    QLabel *label_filesTransmit_progress;
    QLCDNumber *lcdNumber_filesTransmit;
    QLabel *label_filesTransmit_timeConsuming;
    QProgressBar *progressBar_filesTransmit;
    QLabel *label_filesTransmit_frameSize;
    QLabel *label_filesTransmit_frameInterval;
    QPushButton *pushButton_filesTransmit_openFile;
    QLineEdit *lineEdit_filesTransmit_frameGap;
    QPushButton *pushButton_filesTransmit_startTransmit;
    QLineEdit *lineEdit_filesTransmit_frameLen;
    QWidget *page_firmwareUpgrade;
    QProgressBar *progressBar_firmwareUpgrade;
    QLabel *label_firmwareUpgrade_progress;
    QTextEdit *textEdit_firmwareUpgradeInfo;
    QCheckBox *checkBox_firmwareUpgrade_showData;
    QPushButton *pushButton_firmwareUpgrade_clear;
    QLabel *label_firmwareUpgrade_timeConsuming;
    QLabel *label_firmwareUpgrade_frameSize;
    QPushButton *pushButton_firmwareUpgrade_startUpgrade;
    QLCDNumber *lcdNumber_firmwareUpgrade;
    QPushButton *pushButton_firmwareUpgrade_openFiles;
    QLineEdit *lineEdit_firmwareUpgrade_frameLen;
    QPushButton *pushButton_sendAndReceive;
    QPushButton *pushButton_filesTransmit;
    QPushButton *pushButton_firmwareUpgrade;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(771, 733);
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QStringLiteral("action_about"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        comboBox_portNum = new QComboBox(centralWidget);
        comboBox_portNum->setObjectName(QStringLiteral("comboBox_portNum"));
        comboBox_portNum->setGeometry(QRect(30, 50, 71, 31));
        label_portNum = new QLabel(centralWidget);
        label_portNum->setObjectName(QStringLiteral("label_portNum"));
        label_portNum->setGeometry(QRect(120, 60, 54, 12));
        comboBox_baud = new QComboBox(centralWidget);
        comboBox_baud->setObjectName(QStringLiteral("comboBox_baud"));
        comboBox_baud->setGeometry(QRect(30, 110, 71, 31));
        label_baud = new QLabel(centralWidget);
        label_baud->setObjectName(QStringLiteral("label_baud"));
        label_baud->setGeometry(QRect(120, 120, 54, 12));
        comboBox_dataBit = new QComboBox(centralWidget);
        comboBox_dataBit->setObjectName(QStringLiteral("comboBox_dataBit"));
        comboBox_dataBit->setGeometry(QRect(30, 170, 71, 31));
        label_dataBit = new QLabel(centralWidget);
        label_dataBit->setObjectName(QStringLiteral("label_dataBit"));
        label_dataBit->setGeometry(QRect(120, 180, 54, 12));
        comboBox_stopBit = new QComboBox(centralWidget);
        comboBox_stopBit->setObjectName(QStringLiteral("comboBox_stopBit"));
        comboBox_stopBit->setGeometry(QRect(30, 230, 71, 31));
        label_stopBit = new QLabel(centralWidget);
        label_stopBit->setObjectName(QStringLiteral("label_stopBit"));
        label_stopBit->setGeometry(QRect(120, 240, 54, 12));
        comboBox_checkBit = new QComboBox(centralWidget);
        comboBox_checkBit->setObjectName(QStringLiteral("comboBox_checkBit"));
        comboBox_checkBit->setGeometry(QRect(30, 290, 71, 31));
        label_checkBit = new QLabel(centralWidget);
        label_checkBit->setObjectName(QStringLiteral("label_checkBit"));
        label_checkBit->setGeometry(QRect(120, 300, 54, 12));
        comboBox_flowBit = new QComboBox(centralWidget);
        comboBox_flowBit->setObjectName(QStringLiteral("comboBox_flowBit"));
        comboBox_flowBit->setGeometry(QRect(30, 350, 71, 31));
        label_flowBit = new QLabel(centralWidget);
        label_flowBit->setObjectName(QStringLiteral("label_flowBit"));
        label_flowBit->setGeometry(QRect(120, 360, 54, 12));
        pushButton_openUart = new QPushButton(centralWidget);
        pushButton_openUart->setObjectName(QStringLiteral("pushButton_openUart"));
        pushButton_openUart->setGeometry(QRect(30, 410, 71, 31));
        pushButton_openUart->setBaseSize(QSize(0, 0));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(160, -10, 611, 681));
        page_sendAndReceive = new QWidget();
        page_sendAndReceive->setObjectName(QStringLiteral("page_sendAndReceive"));
        checkBox_cycleSend = new QCheckBox(page_sendAndReceive);
        checkBox_cycleSend->setObjectName(QStringLiteral("checkBox_cycleSend"));
        checkBox_cycleSend->setGeometry(QRect(230, 630, 71, 21));
        label_cycleSendTime = new QLabel(page_sendAndReceive);
        label_cycleSendTime->setObjectName(QStringLiteral("label_cycleSendTime"));
        label_cycleSendTime->setGeometry(QRect(350, 630, 21, 21));
        pushButton_send = new QPushButton(page_sendAndReceive);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        pushButton_send->setGeometry(QRect(510, 540, 81, 61));
        textEdit_Tx = new QTextEdit(page_sendAndReceive);
        textEdit_Tx->setObjectName(QStringLiteral("textEdit_Tx"));
        textEdit_Tx->setGeometry(QRect(10, 510, 491, 121));
        pushButton_clearRx = new QPushButton(page_sendAndReceive);
        pushButton_clearRx->setObjectName(QStringLiteral("pushButton_clearRx"));
        pushButton_clearRx->setGeometry(QRect(10, 470, 61, 21));
        checkBox_showTime = new QCheckBox(page_sendAndReceive);
        checkBox_showTime->setObjectName(QStringLiteral("checkBox_showTime"));
        checkBox_showTime->setGeometry(QRect(150, 470, 81, 21));
        checkBox_saveDataToFile = new QCheckBox(page_sendAndReceive);
        checkBox_saveDataToFile->setObjectName(QStringLiteral("checkBox_saveDataToFile"));
        checkBox_saveDataToFile->setGeometry(QRect(310, 470, 101, 21));
        checkBox_ShowHex = new QCheckBox(page_sendAndReceive);
        checkBox_ShowHex->setObjectName(QStringLiteral("checkBox_ShowHex"));
        checkBox_ShowHex->setGeometry(QRect(80, 470, 61, 21));
        pushButton_save = new QPushButton(page_sendAndReceive);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(240, 470, 61, 21));
        textEdit_Rx = new QTextEdit(page_sendAndReceive);
        textEdit_Rx->setObjectName(QStringLiteral("textEdit_Rx"));
        textEdit_Rx->setGeometry(QRect(10, 10, 591, 461));
        textEdit_Rx->setLineWrapMode(QTextEdit::WidgetWidth);
        checkBox_HexSend = new QCheckBox(page_sendAndReceive);
        checkBox_HexSend->setObjectName(QStringLiteral("checkBox_HexSend"));
        checkBox_HexSend->setGeometry(QRect(100, 630, 61, 21));
        checkBox_addNewLine = new QCheckBox(page_sendAndReceive);
        checkBox_addNewLine->setObjectName(QStringLiteral("checkBox_addNewLine"));
        checkBox_addNewLine->setGeometry(QRect(170, 630, 61, 21));
        pushButton_clearTx = new QPushButton(page_sendAndReceive);
        pushButton_clearTx->setObjectName(QStringLiteral("pushButton_clearTx"));
        pushButton_clearTx->setGeometry(QRect(10, 630, 81, 21));
        lineEdit_cycleDelay = new QLineEdit(page_sendAndReceive);
        lineEdit_cycleDelay->setObjectName(QStringLiteral("lineEdit_cycleDelay"));
        lineEdit_cycleDelay->setGeometry(QRect(300, 630, 41, 21));
        label_rxCounter = new QLabel(page_sendAndReceive);
        label_rxCounter->setObjectName(QStringLiteral("label_rxCounter"));
        label_rxCounter->setGeometry(QRect(520, 470, 81, 21));
        label_rxCounter->setFrameShape(QFrame::NoFrame);
        label_txCounter = new QLabel(page_sendAndReceive);
        label_txCounter->setObjectName(QStringLiteral("label_txCounter"));
        label_txCounter->setGeometry(QRect(430, 630, 71, 21));
        stackedWidget->addWidget(page_sendAndReceive);
        page_sendFiles = new QWidget();
        page_sendFiles->setObjectName(QStringLiteral("page_sendFiles"));
        textEdit_filesTransmitInfo = new QTextEdit(page_sendFiles);
        textEdit_filesTransmitInfo->setObjectName(QStringLiteral("textEdit_filesTransmitInfo"));
        textEdit_filesTransmitInfo->setGeometry(QRect(10, 10, 591, 331));
        checkBox_filesTransmit_showData = new QCheckBox(page_sendFiles);
        checkBox_filesTransmit_showData->setObjectName(QStringLiteral("checkBox_filesTransmit_showData"));
        checkBox_filesTransmit_showData->setGeometry(QRect(90, 340, 101, 21));
        pushButton_filesTransmit_clear = new QPushButton(page_sendFiles);
        pushButton_filesTransmit_clear->setObjectName(QStringLiteral("pushButton_filesTransmit_clear"));
        pushButton_filesTransmit_clear->setGeometry(QRect(10, 340, 75, 23));
        label_filesTransmit_progress = new QLabel(page_sendFiles);
        label_filesTransmit_progress->setObjectName(QStringLiteral("label_filesTransmit_progress"));
        label_filesTransmit_progress->setGeometry(QRect(10, 430, 151, 21));
        lcdNumber_filesTransmit = new QLCDNumber(page_sendFiles);
        lcdNumber_filesTransmit->setObjectName(QStringLiteral("lcdNumber_filesTransmit"));
        lcdNumber_filesTransmit->setGeometry(QRect(460, 430, 111, 41));
        label_filesTransmit_timeConsuming = new QLabel(page_sendFiles);
        label_filesTransmit_timeConsuming->setObjectName(QStringLiteral("label_filesTransmit_timeConsuming"));
        label_filesTransmit_timeConsuming->setGeometry(QRect(580, 440, 21, 20));
        progressBar_filesTransmit = new QProgressBar(page_sendFiles);
        progressBar_filesTransmit->setObjectName(QStringLiteral("progressBar_filesTransmit"));
        progressBar_filesTransmit->setGeometry(QRect(10, 370, 591, 61));
        progressBar_filesTransmit->setValue(0);
        label_filesTransmit_frameSize = new QLabel(page_sendFiles);
        label_filesTransmit_frameSize->setObjectName(QStringLiteral("label_filesTransmit_frameSize"));
        label_filesTransmit_frameSize->setGeometry(QRect(150, 450, 111, 16));
        label_filesTransmit_frameInterval = new QLabel(page_sendFiles);
        label_filesTransmit_frameInterval->setObjectName(QStringLiteral("label_filesTransmit_frameInterval"));
        label_filesTransmit_frameInterval->setGeometry(QRect(150, 480, 91, 16));
        pushButton_filesTransmit_openFile = new QPushButton(page_sendFiles);
        pushButton_filesTransmit_openFile->setObjectName(QStringLiteral("pushButton_filesTransmit_openFile"));
        pushButton_filesTransmit_openFile->setGeometry(QRect(150, 530, 211, 51));
        lineEdit_filesTransmit_frameGap = new QLineEdit(page_sendFiles);
        lineEdit_filesTransmit_frameGap->setObjectName(QStringLiteral("lineEdit_filesTransmit_frameGap"));
        lineEdit_filesTransmit_frameGap->setGeometry(QRect(270, 480, 91, 16));
        pushButton_filesTransmit_startTransmit = new QPushButton(page_sendFiles);
        pushButton_filesTransmit_startTransmit->setObjectName(QStringLiteral("pushButton_filesTransmit_startTransmit"));
        pushButton_filesTransmit_startTransmit->setGeometry(QRect(150, 600, 211, 51));
        lineEdit_filesTransmit_frameLen = new QLineEdit(page_sendFiles);
        lineEdit_filesTransmit_frameLen->setObjectName(QStringLiteral("lineEdit_filesTransmit_frameLen"));
        lineEdit_filesTransmit_frameLen->setGeometry(QRect(270, 450, 91, 16));
        stackedWidget->addWidget(page_sendFiles);
        page_firmwareUpgrade = new QWidget();
        page_firmwareUpgrade->setObjectName(QStringLiteral("page_firmwareUpgrade"));
        progressBar_firmwareUpgrade = new QProgressBar(page_firmwareUpgrade);
        progressBar_firmwareUpgrade->setObjectName(QStringLiteral("progressBar_firmwareUpgrade"));
        progressBar_firmwareUpgrade->setGeometry(QRect(10, 369, 591, 61));
        progressBar_firmwareUpgrade->setValue(0);
        label_firmwareUpgrade_progress = new QLabel(page_firmwareUpgrade);
        label_firmwareUpgrade_progress->setObjectName(QStringLiteral("label_firmwareUpgrade_progress"));
        label_firmwareUpgrade_progress->setGeometry(QRect(10, 430, 151, 21));
        textEdit_firmwareUpgradeInfo = new QTextEdit(page_firmwareUpgrade);
        textEdit_firmwareUpgradeInfo->setObjectName(QStringLiteral("textEdit_firmwareUpgradeInfo"));
        textEdit_firmwareUpgradeInfo->setGeometry(QRect(10, 10, 591, 331));
        checkBox_firmwareUpgrade_showData = new QCheckBox(page_firmwareUpgrade);
        checkBox_firmwareUpgrade_showData->setObjectName(QStringLiteral("checkBox_firmwareUpgrade_showData"));
        checkBox_firmwareUpgrade_showData->setGeometry(QRect(90, 340, 101, 21));
        pushButton_firmwareUpgrade_clear = new QPushButton(page_firmwareUpgrade);
        pushButton_firmwareUpgrade_clear->setObjectName(QStringLiteral("pushButton_firmwareUpgrade_clear"));
        pushButton_firmwareUpgrade_clear->setGeometry(QRect(10, 340, 75, 23));
        label_firmwareUpgrade_timeConsuming = new QLabel(page_firmwareUpgrade);
        label_firmwareUpgrade_timeConsuming->setObjectName(QStringLiteral("label_firmwareUpgrade_timeConsuming"));
        label_firmwareUpgrade_timeConsuming->setGeometry(QRect(580, 450, 21, 20));
        label_firmwareUpgrade_frameSize = new QLabel(page_firmwareUpgrade);
        label_firmwareUpgrade_frameSize->setObjectName(QStringLiteral("label_firmwareUpgrade_frameSize"));
        label_firmwareUpgrade_frameSize->setGeometry(QRect(150, 450, 111, 21));
        pushButton_firmwareUpgrade_startUpgrade = new QPushButton(page_firmwareUpgrade);
        pushButton_firmwareUpgrade_startUpgrade->setObjectName(QStringLiteral("pushButton_firmwareUpgrade_startUpgrade"));
        pushButton_firmwareUpgrade_startUpgrade->setGeometry(QRect(150, 600, 211, 51));
        lcdNumber_firmwareUpgrade = new QLCDNumber(page_firmwareUpgrade);
        lcdNumber_firmwareUpgrade->setObjectName(QStringLiteral("lcdNumber_firmwareUpgrade"));
        lcdNumber_firmwareUpgrade->setGeometry(QRect(460, 430, 111, 41));
        pushButton_firmwareUpgrade_openFiles = new QPushButton(page_firmwareUpgrade);
        pushButton_firmwareUpgrade_openFiles->setObjectName(QStringLiteral("pushButton_firmwareUpgrade_openFiles"));
        pushButton_firmwareUpgrade_openFiles->setGeometry(QRect(150, 530, 211, 51));
        lineEdit_firmwareUpgrade_frameLen = new QLineEdit(page_firmwareUpgrade);
        lineEdit_firmwareUpgrade_frameLen->setObjectName(QStringLiteral("lineEdit_firmwareUpgrade_frameLen"));
        lineEdit_firmwareUpgrade_frameLen->setGeometry(QRect(270, 450, 91, 21));
        stackedWidget->addWidget(page_firmwareUpgrade);
        pushButton_sendAndReceive = new QPushButton(centralWidget);
        pushButton_sendAndReceive->setObjectName(QStringLiteral("pushButton_sendAndReceive"));
        pushButton_sendAndReceive->setGeometry(QRect(20, 460, 141, 61));
        pushButton_sendAndReceive->setBaseSize(QSize(0, 0));
        pushButton_filesTransmit = new QPushButton(centralWidget);
        pushButton_filesTransmit->setObjectName(QStringLiteral("pushButton_filesTransmit"));
        pushButton_filesTransmit->setGeometry(QRect(20, 520, 141, 61));
        pushButton_filesTransmit->setBaseSize(QSize(0, 0));
        pushButton_firmwareUpgrade = new QPushButton(centralWidget);
        pushButton_firmwareUpgrade->setObjectName(QStringLiteral("pushButton_firmwareUpgrade"));
        pushButton_firmwareUpgrade->setGeometry(QRect(20, 580, 141, 61));
        pushButton_firmwareUpgrade->setBaseSize(QSize(0, 0));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 771, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action_about);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_about->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", Q_NULLPTR));
        label_portNum->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267", Q_NULLPTR));
        comboBox_baud->clear();
        comboBox_baud->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "115200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2400", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4800", Q_NULLPTR)
         << QApplication::translate("MainWindow", "14400", Q_NULLPTR)
         << QApplication::translate("MainWindow", "19200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "38400", Q_NULLPTR)
         << QApplication::translate("MainWindow", "57600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "128000", Q_NULLPTR)
         << QApplication::translate("MainWindow", "256000", Q_NULLPTR)
         << QApplication::translate("MainWindow", "512000", Q_NULLPTR)
         << QApplication::translate("MainWindow", "921600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2000000", Q_NULLPTR)
        );
        label_baud->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        comboBox_dataBit->clear();
        comboBox_dataBit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
         << QApplication::translate("MainWindow", "7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5", Q_NULLPTR)
        );
        label_dataBit->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", Q_NULLPTR));
        comboBox_stopBit->clear();
        comboBox_stopBit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1.5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
        );
        label_stopBit->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", Q_NULLPTR));
        comboBox_checkBit->clear();
        comboBox_checkBit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\346\227\240\346\240\241\351\252\214", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\245\207\346\240\241\351\252\214", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\201\266\346\240\241\351\252\214", Q_NULLPTR)
        );
        label_checkBit->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", Q_NULLPTR));
        comboBox_flowBit->clear();
        comboBox_flowBit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Hardware", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Software", Q_NULLPTR)
         << QApplication::translate("MainWindow", "UnknowFlowControl", Q_NULLPTR)
        );
        label_flowBit->setText(QApplication::translate("MainWindow", "\346\216\247\345\210\266\346\265\201", Q_NULLPTR));
        pushButton_openUart->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        checkBox_cycleSend->setText(QApplication::translate("MainWindow", "\345\276\252\347\216\257\345\221\250\346\234\237", Q_NULLPTR));
        label_cycleSendTime->setText(QApplication::translate("MainWindow", "ms", Q_NULLPTR));
        pushButton_send->setText(QApplication::translate("MainWindow", "\345\217\221 \351\200\201", Q_NULLPTR));
        pushButton_clearRx->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\347\252\227\345\217\243", Q_NULLPTR));
        checkBox_showTime->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\346\227\266\351\227\264\346\210\263", Q_NULLPTR));
        checkBox_saveDataToFile->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256\345\210\260\346\226\207\344\273\266", Q_NULLPTR));
        checkBox_ShowHex->setText(QApplication::translate("MainWindow", "HEX\346\230\276\347\244\272", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\225\260\346\215\256", Q_NULLPTR));
        checkBox_HexSend->setText(QApplication::translate("MainWindow", "HEX\345\217\221\351\200\201", Q_NULLPTR));
        checkBox_addNewLine->setText(QApplication::translate("MainWindow", "\345\212\240\346\215\242\350\241\214", Q_NULLPTR));
        pushButton_clearTx->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\345\217\221\351\200\201\345\214\272", Q_NULLPTR));
        lineEdit_cycleDelay->setText(QApplication::translate("MainWindow", "1000", Q_NULLPTR));
        label_rxCounter->setText(QApplication::translate("MainWindow", "RX:0", Q_NULLPTR));
        label_txCounter->setText(QApplication::translate("MainWindow", "TX:0", Q_NULLPTR));
        checkBox_filesTransmit_showData->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\344\274\240\350\276\223\346\225\260\346\215\256", Q_NULLPTR));
        pushButton_filesTransmit_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\347\252\227\345\217\243", Q_NULLPTR));
        label_filesTransmit_progress->setText(QApplication::translate("MainWindow", "0/0 bytes", Q_NULLPTR));
        label_filesTransmit_timeConsuming->setText(QApplication::translate("MainWindow", "\347\247\222", Q_NULLPTR));
        label_filesTransmit_frameSize->setText(QApplication::translate("MainWindow", " \345\270\247 \345\244\247 \345\260\217 (bytes):", Q_NULLPTR));
        label_filesTransmit_frameInterval->setText(QApplication::translate("MainWindow", " \345\270\247 \351\227\264 \351\232\224 (ms):", Q_NULLPTR));
        pushButton_filesTransmit_openFile->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        lineEdit_filesTransmit_frameGap->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        pushButton_filesTransmit_startTransmit->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\344\274\240\350\276\223", Q_NULLPTR));
        lineEdit_filesTransmit_frameLen->setText(QApplication::translate("MainWindow", "1024", Q_NULLPTR));
        label_firmwareUpgrade_progress->setText(QApplication::translate("MainWindow", "0/0 bytes", Q_NULLPTR));
        checkBox_firmwareUpgrade_showData->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\351\200\232\344\277\241\346\225\260\346\215\256", Q_NULLPTR));
        pushButton_firmwareUpgrade_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\347\252\227\345\217\243", Q_NULLPTR));
        label_firmwareUpgrade_timeConsuming->setText(QApplication::translate("MainWindow", "\347\247\222", Q_NULLPTR));
        label_firmwareUpgrade_frameSize->setText(QApplication::translate("MainWindow", " \345\270\247 \345\244\247 \345\260\217 (bytes):", Q_NULLPTR));
        pushButton_firmwareUpgrade_startUpgrade->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\345\215\207\347\272\247", Q_NULLPTR));
        pushButton_firmwareUpgrade_openFiles->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        lineEdit_firmwareUpgrade_frameLen->setText(QApplication::translate("MainWindow", "512", Q_NULLPTR));
        pushButton_sendAndReceive->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243\346\224\266\345\217\221", Q_NULLPTR));
        pushButton_filesTransmit->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\344\274\240\350\276\223", Q_NULLPTR));
        pushButton_firmwareUpgrade->setText(QApplication::translate("MainWindow", "\345\233\272\344\273\266\345\215\207\347\272\247", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\351\200\211\351\241\271", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
