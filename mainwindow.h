#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ControlCAN.h"
#include <QDebug>
#include "protocolthrend.h"
#include "canthread.h"
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

    void on_btnFinish_clicked();

    void on_btnUpdate_clicked();

    void on_btnUpdateMode_clicked();
    void updataFlashTime(void);

    void displayMonitor(VCI_CAN_OBJ *vci,DWORD dwRel);

    void on_btnMonitor_clicked();

private:
    Ui::MainWindow *ui;
    CANThread *canthread;
    ProtocolThrend *protocolHand;
    QTimer *FlashWriteTimer;  //定时器
    unsigned int FlashWriteTimeSec = 0;

public:
    void sleep(unsigned int msec);
};

#endif // MAINWINDOW_H
