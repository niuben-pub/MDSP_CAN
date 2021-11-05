#ifndef J1939_MSG_H
#define J1939_MSG_H

#define J1939_MSG_LENGTH	9  //��Ϣ����
#define J1939_DATA_LENGTH	8  //���ݳ���



#define CAN_FLASH_ERASE (0x01);

#define PGN53760 (0xD200)  // ��Flash����
#define PGN53504 (0xD100)  // д����оƬ�Ĵ���
#define PGN53248 (0xD000)  // ������оƬ�Ĵ���


#define PGN61184 (0xEF00)  // ���԰�

#define PGN60928 (0xEE00)  // IDOG
#define PGN60672 (0xED00)  // ��д CAN�շ���ַ
#define PGN60416 (0xEC00)  // ��������ʼ������
#define PGN60160 (0xEB00)  // ���������ݲ�����
#define PGN59940 (0xEA00)  // ��FPGA�ڲ��¶�
#define PGN56468 (0xE900)  // ����ģʽ�л�
#define PGN59392 (0xE800)  // IDOG����
#define PGN59136 (0xE700)  // ��MCU
#define PGN58880 (0xE600)  // ��MDSP
#define PGN58624 (0xE500)  // ��FPGA
#define PGN58368 (0xE400)  // ����MCU
#define PGN58112 (0xE300)  // ����MDSP
#define PGN57856 (0xE200)  // ����FPGA
#define PGN57600 (0xE100)  // ����ADC����
#define PGN57344 (0xE000)  // ����flash����


#define MDSP_SOURCE_ADDR (0x01) // ���豸��ַ
#define PC_SOURCE_ADDR (0x02) // ���豸��ַ


#define RUNMODE (0x00)
#define UPGRADEMODE (0x01)
#define STATUSMODE (0X02)
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
