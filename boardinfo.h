#ifndef BOARDINFO_H
#define BOARDINFO_H


class boardinfo
{
public:
    boardinfo();
    boardinfo(unsigned char addr);
    unsigned char writerAddr = 0;
    unsigned char readAddr = 0;
    unsigned int IN1_3G_NUM = 0; //  ”∆µ ‰»Î1ª≠√Ê±‡∫≈
    unsigned int IN2_3G_NUM = 0; //  ”∆µ ‰»Î2ª≠√Ê±‡∫≈
};

#endif // BOARDINFO_H
