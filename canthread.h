#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QThread>
#include "ControlCAN.h"
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include <QTime>
class CANThread:public QThread
{
    Q_OBJECT
public:
    CANThread();

    void stop();

    bool openCAN();

    void closeCAN();

    void sendData(int ID, unsigned char *ch);
    int deviceType;
    int debicIndex;
    int baundRate;
    int debicCom;
    bool stopped;
    QTimer *canThreadTimer;  //定时器

signals:
    void getProtocolData(VCI_CAN_OBJ *vci,DWORD dwRel);
public slots:
    void sendADCrequestData(void);


private:
    void run();
    void sleep(unsigned int msec);
    void usleep(unsigned int usec);
    QMutex CanThreadMutex;

};

#endif // CANTHREAD_H
