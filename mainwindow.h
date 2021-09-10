#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ControlCAN.h"
#include <QDebug>
#include "protocolthrend.h"
#include "canthread.h"
#include "boardinfo.h"
#include "imglabel.h"
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    void initUi();
    void initSignalslots();


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void writeFpgaImgconfigReg(unsigned int *regTable);

    void on_btnDefParam_clicked();

    void on_btnFinish_clicked();  //设备启动按钮

    void updataFlashTime(void);

    void displayMonitor(VCI_CAN_OBJ *vci,DWORD dwRel);

    void on_btnStatusBoard1_clicked();

    void on_btnUpdate_2_clicked();

    void on_btnUpdateMode_2_clicked();

    void on_btnStatusBoard1_2_clicked();


    void on_btnUpdateMode_3_clicked();

    void on_btnUpdate_3_clicked();

    void on_pushButtonTestWBoard1_clicked();

    void on_pushButtonTestRBoard1_clicked();

    void on_pushButtonTestWBoard2_clicked();

    void on_pushButtonTestRBoard2_clicked();

    void on_pushButtonTestWBoard3_clicked();

    void on_pushButtonTestRBoard3_clicked();

    void on_pushButtonTestWBoard4_clicked();

    void on_pushButtonTestRBoard4_clicked();

    void on_pushButtonTestWBoard5_clicked();

    void on_pushButtonTestRBoard5_clicked();

    void on_pushButtonTestWBoard6_clicked();

    void on_pushButtonTestRBoard6_clicked();

    void on_pushButtonTestWBoard7_clicked();

    void on_pushButtonTestRBoard7_clicked();

    void on_pushButtonTestWBoard8_clicked();

    void on_pushButtonTestRBoard8_clicked();

    void on_pushButtonAddrClear_clicked();

    void on_pushButtonAddrOk_clicked();

    void on_comboBox3Gin1Size_currentIndexChanged(int index);

    void on_comboBox3Gin2Size_currentIndexChanged(int index);

    void on_comboBoxImg_currentIndexChanged(int index);

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    CANThread *canthread;
    ProtocolThrend *protocolHand;
    QTimer *FlashWriteTimer;  //定时器
    unsigned int FlashWriteTimeSec = 0;

    boardinfo *board1;
    boardinfo *board2;
    boardinfo *board3;
    boardinfo *board4;
    boardinfo *board5;
    boardinfo *board6;
    boardinfo *board7;
    boardinfo *board8;


public:
    void sleep(unsigned int msec);
};

#endif // MAINWINDOW_H
