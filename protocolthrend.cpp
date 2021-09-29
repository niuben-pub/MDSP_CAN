#include "protocolthrend.h"
#include <QThread>
#include "ControlCAN.h"
#include <QTime>
#include <QCoreApplication>
#include <QMetaType>
#include <QString>
#include <string.h>
#include "j1939_msg.h"
using namespace std;

ProtocolThrend::ProtocolThrend()
{
    stopped = false;
    data_update = false;
    flash_inited = false;
    qRegisterMetaType<VCI_CAN_OBJ>("VCI_CAN_OBJ");
    qRegisterMetaType<DWORD>("DWORD");
    this->CANdata = new VCI_CAN_OBJ();
}

void ProtocolThrend::protocolHand(VCI_CAN_OBJ *vci)
{
   // qDebug()<<"from thread slot:" <<QThread::currentThreadId();
 //   qDebug()<<"protocol :"<<vci[0].ID;
    memcpy(this->CANdata,vci,sizeof (VCI_CAN_OBJ));
    data_update = true;  //数据更新
}

void ProtocolThrend::run()
{
    int num = 0;
    while(!stopped)
    {
        if(data_update)
        {
            //qDebug()<<"from thread slot:" <<QThread::currentThreadId() << num++;
//            qDebug("data :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x",\
//                    this->CANdata->ID,\
//                    this->CANdata->Data[0],\
//                    this->CANdata->Data[1],\
//                    this->CANdata->Data[2],\
//                    this->CANdata->Data[3],\
//                    this->CANdata->Data[4],\
//                    this->CANdata->Data[5],\
//                    this->CANdata->Data[6],\
//                    this->CANdata->Data[7]\
//                    );


            if(this->CANdata->ID == (PGN57344 << 8) + UpdateReadAddr)  //修改MCU flash 初始化标志
            {
                this->flash_inited = true;
            }

            data_update = false;
        }

    }
}

bool ProtocolThrend::flash_init_completed(void)
{
    while(!flash_inited)// 等待flash 擦除完成
    {
        sleep(300);// 不能省略 防止 flash_inited 被同时读写
    }
    return true;
}

void ProtocolThrend::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

