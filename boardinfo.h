#ifndef BOARDINFO_H
#define BOARDINFO_H


class boardinfo
{
public:
    boardinfo();
    boardinfo(unsigned char addr);
    unsigned char writerAddr = 0;
    unsigned char readAddr = 0;
    unsigned int IN1_3G_NUM = 0; // ��Ƶ����1������
    unsigned int IN2_3G_NUM = 0; // ��Ƶ����2������
};

#endif // BOARDINFO_H
