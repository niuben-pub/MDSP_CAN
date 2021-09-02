#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ControlCAN.h"
#include <QDebug>
#include "protocolthrend.h"
#include "canthread.h"
#include "boardinfo.h"
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


    void on_btnDefParam_clicked();

    void on_btnFinish_clicked();  //设备启动按钮

    void updataFlashTime(void);

    void displayMonitor(VCI_CAN_OBJ *vci,DWORD dwRel);

    void on_pushButton3GINBoard1_clicked();

    void on_pushButton3GINClearBoard1_clicked();

    void on_pushButton3GINBoard2_clicked();

    void on_pushButton3GINClearBoard2_clicked();

    void on_pushButton3GINBoard3_clicked();

    void on_pushButton3GINClearBoard3_clicked();

    void on_pushButton3GINBoard4_clicked();

    void on_pushButton3GINClearBoard4_clicked();

    void on_pushButton3GINBoard5_clicked();

    void on_pushButton3GINClearBoard5_clicked();

    void on_pushButton3GINBoard6_clicked();

    void on_pushButton3GINClearBoard6_clicked();

    void on_pushButton3GINBoard7_clicked();

    void on_pushButton3GINClearBoard7_clicked();

    void on_pushButton3GINBoard8_clicked();

    void on_pushButton3GINClearBoard8_clicked();

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
