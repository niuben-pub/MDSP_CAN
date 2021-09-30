#include "canthread.h"
#include "ControlCAN.h"
#include <QTime>
#include <QCoreApplication>
#include <QMetaType>
#include <QString>
#include <j1939_msg.h>
#include <QMutex>
#include <windows.h>
    VCI_BOARD_INFO vbi;
CANThread::CANThread()
{
    stopped = false;
    canThreadTimer = new QTimer(this);
    qRegisterMetaType<VCI_CAN_OBJ>("VCI_CAN_OBJ");
    qRegisterMetaType<DWORD>("DWORD");
    canThreadTimer->stop();
    canThreadTimer->setInterval(2000); //设置定时周期  单位ms
    connect(canThreadTimer,SIGNAL(timeout()),this,SLOT(sendADCrequestData()));

}

void CANThread::stop()
{
    stopped = true;
}

bool CANThread::openCAN()
{
    int nDeviceType = deviceType; /* USBCAN-2A或USBCAN-2C或CANalyst-II */
    int nDeviceInd = debicIndex; /* 第1个设备 */
    int nCANInd = debicCom; /* 第1个通道 */
    DWORD dwRel;
    dwRel = VCI_OpenDevice(nDeviceType, nDeviceInd, nCANInd);
    if(dwRel != 1)
    {
//        qDebug()<<"open fail:"<< MB_OK<<MB_ICONQUESTION;
        return false;
    }
    else
//        qDebug()<<"open success";

    dwRel = VCI_ClearBuffer(nDeviceType, nDeviceInd, nCANInd);
    dwRel = VCI_ClearBuffer(nDeviceType, nDeviceInd, nCANInd+1);
    VCI_INIT_CONFIG vic;
    vic.AccCode=0x80000008;
    vic.AccMask=0xFFFFFFFF;
    vic.Filter=1;
    vic.Mode=0;
    switch (baundRate) {
    case 10:
        vic.Timing0=0x31;
        vic.Timing1=0x1c;
        break;
    case 20:
        vic.Timing0=0x18;
        vic.Timing1=0x1c;
        break;
    case 40:
        vic.Timing0=0x87;
        vic.Timing1=0xff;
        break;
    case 50:
        vic.Timing0=0x09;
        vic.Timing1=0x1c;
        break;
    case 80:
        vic.Timing0=0x83;
        vic.Timing1=0xff;
        break;
    case 100:
        vic.Timing0=0x04;
        vic.Timing1=0x1c;
        break;
    case 125:
        vic.Timing0=0x03;
        vic.Timing1=0x1c;
        break;
    case 200:
        vic.Timing0=0x81;
        vic.Timing1=0xfa;
        break;
    case 250:
        vic.Timing0=0x01;
        vic.Timing1=0x1c;
        break;
    case 400:
        vic.Timing0=0x80;
        vic.Timing1=0xfa;
        break;
    case 500:
        vic.Timing0=0x00;
        vic.Timing1=0x1c;
        break;
    case 666:
        vic.Timing0=0x80;
        vic.Timing1=0xb6;
        break;
    case 800:
        vic.Timing0=0x00;
        vic.Timing1=0x16;
        break;
    case 1000:
        vic.Timing0=0x00;
        vic.Timing1=0x14;
        break;
    case 33:
        vic.Timing0=0x09;
        vic.Timing1=0x6f;
        break;
    case 66:
        vic.Timing0=0x04;
        vic.Timing1=0x6f;
        break;
    case 83:
        vic.Timing0=0x03;
        vic.Timing1=0x6f;
        break;
    default:
        break;
    }
    dwRel = VCI_InitCAN(nDeviceType, nDeviceInd, nCANInd, &vic);
    dwRel = VCI_InitCAN(nDeviceType, nDeviceInd, nCANInd+1, &vic);
    if(dwRel !=1)
    {
        return false;
    }



    dwRel = VCI_ReadBoardInfo(nDeviceType, nDeviceInd, &vbi);
    if(dwRel != 1)
    {
        return false;
    }
    else
    {
        qDebug()<<"CAN通道数："<<vbi.can_Num;
        qDebug()<<"硬件版本号:"<<vbi.hw_Version;
        qDebug()<<"接口库版本号："<<vbi.in_Version;
        qDebug()<<"中断号"<<vbi.irq_Num;
    }

    if(VCI_StartCAN(nDeviceType, nDeviceInd, nCANInd) !=1)
    {
        return false;
    }
    else
        qDebug()<<"start"<<nCANInd<<"success:";

    int comid = nCANInd+1;
    if(VCI_StartCAN(nDeviceType, nDeviceInd, comid) !=1)
    {
        return false;
    }
    else
        qDebug()<<"start"<<comid<<"success:";

    return true;
}

void CANThread::closeCAN()
{
    VCI_CloseDevice(deviceType, debicIndex);
}

void CANThread::sendData(int ID,unsigned char *ch)
{
    CanThreadMutex.lock();
    VCI_CAN_OBJ vco[1];
    DWORD dwRel;
    int count = 1;
    vco[0].ID =ID ;
    vco[0].RemoteFlag = 0;
    vco[0].ExternFlag = 1;
    vco[0].DataLen = 8;
    for(int i = 0; i<8 ; i++)
    {
        vco[0].Data[i] = ch[i];
    }
    dwRel = VCI_Transmit(deviceType, debicIndex, debicCom, vco,count);
    if(dwRel < 0)
    {
        qDebug()<<"发送错误："<<dwRel;
    }
    usleep(200);  //延时不能小于200us
    CanThreadMutex.unlock();
}


void CANThread::sendADCrequestData()
{
    for(int boardAddr = 1 ; boardAddr <= 8; boardAddr++)
    {

        //读FPGA内部温度
        int ID = (PGN59940 << 8) + boardAddr;;  //读FPGA内部温度命令  boardAddr是设备地址
        unsigned char send_str[8] = {0};
        this->sendData(ID,(unsigned char*)send_str);
        sleep(10);  //

        ID = (PGN57600 << 8) + boardAddr;  //请求ADC 命令  boardAddr是设备地址
        unsigned char arr[8] = {0};  //第[7]字节表示通道号
        arr[7] = 4;//ADC0  chn4
        this->sendData(ID,(unsigned char *)arr);
        sleep(10);  //给AD转换留足够时间
        arr[7] = 5;//ADC1  chn5
        this->sendData(ID,(unsigned char *)arr);
        sleep(10);
        arr[7] = 6;//ADC2  chn6
        this->sendData(ID,(unsigned char *)arr);
        sleep(10);
        arr[7] = 7;//ADC3  chn7
        this->sendData(ID,(unsigned char *)arr);
        sleep(10);



    }

}
void CANThread::run()
{
    DWORD dwRel;
    while(!stopped)
    {
        VCI_CAN_OBJ vco[2500];
        dwRel = VCI_Receive(deviceType, debicIndex, debicCom, vco,2500,0);
        if(dwRel > 0)
        {
            emit getProtocolData(vco,dwRel);
        }
        else if(dwRel == (DWORD)-1)
        {
            qDebug()<<"设备不存在或USB掉线";
        }

    }
    stopped = false;
}

void CANThread::sleep(unsigned int msec)
{
   QTime dieTime = QTime::currentTime().addMSecs(msec);
   while( QTime::currentTime() < dieTime )
       QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void CANThread::usleep(unsigned int usec)
{
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    double time = 0.0f;
    if(QueryPerformanceFrequency(&nFreq) == 0)
    {
        qDebug()<<"get frequency err";
    }
    QueryPerformanceCounter(&nBeginTime);
    while(time < (double)usec / 1000000)
    {
        QueryPerformanceCounter(&nEndTime);
        time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);  //保证其它线程不会被阻塞
    }

}
