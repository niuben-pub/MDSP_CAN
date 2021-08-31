#ifndef J1939_MSG_H
#define J1939_MSG_H

#define J1939_MSG_LENGTH	9  //消息长度
#define J1939_DATA_LENGTH	8  //数据长度



#define CAN_FLASH_ERASE (0x01);

#define PGN60416 (0xEC00)  // 长数据起始参数组
#define PGN60160 (0xEB00)  // 长数据数据参数组

#define PGN59940 (0xEA00)  // 保留
#define PGN56468 (0xE900)  // 工作模式切换
#define PGN59392 (0xE800)  // IDOG信令
#define PGN59136 (0xE700)  // 读MCU
#define PGN58880 (0xE600)  // 读MDSP
#define PGN58624 (0xE500)  // 读FPGA
#define PGN58368 (0xE400)  // 设置MCU
#define PGN58112 (0xE300)  // 设置MDSP
#define PGN57856 (0xE200)  // 设置FPGA
#define PGN57600 (0xE100)  // 请求ADC数据
#define PGN57344 (0xE000)  // 擦除flash命令

#define MDSP_SOURCE_ADDR (0x01) // 从设备地址
#define PC_SOURCE_ADDR (0x02) // 主设备地址


#define RUNMODE (0x00)
#define UPGRADEMODE (0x01)
#define MODE2 (0X02)
#define MODE3 (0X03)
#define MODE4 (0X04)
#define MODE5 (0X05)
#define MODE6 (0X06)
#define MODE7 (0X07)


union J1939_MESSAGE_UNION;

class J1939_MSG
{
public:
    J1939_MSG();
    J1939_MESSAGE_UNION *msg;
};






#endif // J1939_MSG_H
