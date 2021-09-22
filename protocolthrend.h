#ifndef PROTOCOLTHREND_H
#define PROTOCOLTHREND_H


#include <QThread>
#include "ControlCAN.h"
#include <QDebug>


class ProtocolThrend:public QThread
{
    Q_OBJECT
public:
    ProtocolThrend();
    bool flash_init_completed(void);
    bool stopped;

    bool data_update;  //数据更新标志
    bool flash_inited; //flash擦除完成标志
    unsigned char UpdateWriteAddr;
    unsigned char UpdateReadAddr;
    float MDSP_Board_currents;
    float MDSP_Board_HV;
    float MDSP_Board_LV;
    float MDSP_Board_temperature;
    float MDSP_Board_FPGAtemperature;
    VCI_CAN_OBJ *CANdata;
public slots:
    void protocolHand(VCI_CAN_OBJ *vci);
private:
    void run();
    void sleep(unsigned int msec);
};

#endif // PROTOCOLTHREND_H
