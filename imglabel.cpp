#include "imglabel.h"
#include <QDebug>

ImgLabel::ImgLabel(QWidget *parent) : QLabel(parent)
{
    InitConnect();
}

void ImgLabel::resetRegData()
{
    //目标识别开关
    detectionStateReg = DETECTION_OFF;
    //硬件版本号
    hardwareVersionReg = 0;
    //设备状态寄存器
    deviceStateReg = 0;
    //fpga内部温度寄存器
    fpgaTempReg = 0;
    //3g in1 图像尺寸寄存器  1 - 1080p  0 - 540p
    img3GIn1SizeReg = IN_3G_SIZE_1920X1080;
    //3g in2 图像尺寸寄存器  1 - 1080p  0 - 540p
    img3GIn2SizeReg = IN_3G_SIZE_1920X1080;
    //12g 输入开关
    in12GSwitchReg = IN_12G_SWITCH_ON;
    //显示模式寄存器
    displayModeReg = SDI_4K_16;
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            regTable[i][j] = 0x00;
        }
    }
}

void ImgLabel::resetRegData1()
{
    //目标识别开关
    detectionStateReg = DETECTION_OFF;
    //硬件版本号
    hardwareVersionReg = 0;
    //设备状态寄存器
    deviceStateReg = 0;
    //fpga内部温度寄存器
    fpgaTempReg = 0;
    //3g in1 图像尺寸寄存器  1 - 1080p  0 - 540p
    img3GIn1SizeReg = IN_3G_SIZE_1920X1080;
    //3g in2 图像尺寸寄存器  1 - 1080p  0 - 540p
    img3GIn2SizeReg = IN_3G_SIZE_1920X1080;
    //12g 输入开关
    in12GSwitchReg = IN_12G_SWITCH_ON;
    //显示模式寄存器
    displayModeReg = SDI_4K_16;
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            regTable[i][j] = COLOR_960x540;
        }
    }
}

void ImgLabel::PrintRegTable()
{
    for (int i = 0; i < 4; i++)
    {
        qDebug()<<"["<<regTable[i][0]<<"]"<<"["<<regTable[i][1]<<"]"<<"["<<regTable[i][2]<<"]"<<"["<<regTable[i][3]<<"]"<<endl;
    }
    qDebug()<<"Img3GIn1Size "<<Img3GIn1Size<<endl;
    qDebug()<<"Img3GIn2Size "<<Img3GIn2Size<<endl;
    qDebug()<<"ImgType "<<ImgType<<endl;
}

void ImgLabel::handleImgControl(unsigned int zone_x, unsigned int zone_y)
{
    unsigned int regindex = zone_y * 4 + zone_x;
    displayModeReg = SDI_4K_16;
    qDebug()<<ImgType;
    if(ImgType == IMG_IN1_3G)
    {
        if(Img3GIn1Size == INPUT_SIZE_1920X1080)
        {
            img3GIn1SizeReg = IN_3G_SIZE_1920X1080;
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                this->regTable[0][0] = 0;
                this->regTable[0][1] = 0;
                this->regTable[1][0] = 0;
                this->regTable[1][1] = 0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[0][0] = IN1_3G_1920x1080;
                this->regTable[0][1] = IN1_3G_1920x1080;
                this->regTable[1][0] = IN1_3G_1920x1080;
                this->regTable[1][1] = IN1_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);

            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                this->regTable[0][2] = 0;
                this->regTable[0][3] = 0;
                this->regTable[1][2] = 0;
                this->regTable[1][3] = 0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[0][2] = IN1_3G_1920x1080;
                this->regTable[0][3] = IN1_3G_1920x1080;
                this->regTable[1][2] = IN1_3G_1920x1080;
                this->regTable[1][3] = IN1_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);


            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                this->regTable[2][0] = 0;
                this->regTable[2][1] = 0;
                this->regTable[3][0] = 0;
                this->regTable[3][1] = 0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[2][0] = IN1_3G_1920x1080;
                this->regTable[2][1] = IN1_3G_1920x1080;
                this->regTable[3][0] = IN1_3G_1920x1080;
                this->regTable[3][1] = IN1_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);


            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                this->regTable[2][2] = 0;
                this->regTable[2][3] = 0;
                this->regTable[3][2] = 0;
                this->regTable[3][3] = 0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[2][2] = IN1_3G_1920x1080;
                this->regTable[2][3] = IN1_3G_1920x1080;
                this->regTable[3][2] = IN1_3G_1920x1080;
                this->regTable[3][3] = IN1_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(Img3GIn1Size == INPUT_SIZE_960X540)
        {
            img3GIn1SizeReg = IN_3G_SIZE_960x540;
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                if(regTable[0][0] == IN1_3G_1920x1080 || regTable[0][0] == IN2_3G_1920x1080)
                {
                    this->regTable[0][0] = 0;
                    this->regTable[0][1] = 0;
                    this->regTable[1][0] = 0;
                    this->regTable[1][1] = 0;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                if(regTable[0][2] == IN1_3G_1920x1080 || regTable[0][2] == IN2_3G_1920x1080)
                {
                    this->regTable[0][2] = 0;
                    this->regTable[0][3] = 0;
                    this->regTable[1][2] = 0;
                    this->regTable[1][3] = 0;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                if(regTable[2][0] == IN1_3G_1920x1080 || regTable[2][0] == IN2_3G_1920x1080)
                {
                    this->regTable[2][0] = 0;
                    this->regTable[2][1] = 0;
                    this->regTable[3][0] = 0;
                    this->regTable[3][1] = 0;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }

            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                if(regTable[2][2] == IN1_3G_1920x1080 || regTable[2][2] == IN2_3G_1920x1080)
                {
                    this->regTable[2][2] = 0;
                    this->regTable[2][3] = 0;
                    this->regTable[3][2] = 0;
                    this->regTable[3][3] = 0;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
            }
        }
        else if(Img3GIn1Size == INPUT_SIZE_FULL)
        {
            img3GIn1SizeReg = IN_3G_SIZE_1920X1080;   //全屏显示需要先将视频管道切到 1080P
            if(regindex >= 0 && regindex <= 15)
            {
                displayModeReg = SDI_4K_FROM_IN1;
            }
            emit this->regChange((unsigned int *)regTable);

        }
    }
    else if(ImgType == IMG_IN2_3G)
    {
        if(Img3GIn2Size == INPUT_SIZE_1920X1080)
        {
            img3GIn2SizeReg = IN_3G_SIZE_1920X1080;
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                this->regTable[0][0] = 0;
                this->regTable[0][1] = 0;
                this->regTable[1][0] = 0;
                this->regTable[1][1] = 0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[0][0] = IN2_3G_1920x1080;
                this->regTable[0][1] = IN2_3G_1920x1080;
                this->regTable[1][0] = IN2_3G_1920x1080;
                this->regTable[1][1] = IN2_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);

            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                this->regTable[0][2] = 0;
                this->regTable[0][3] = 0;
                this->regTable[1][2] = 0;
                this->regTable[1][3] = 0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[0][2] = IN2_3G_1920x1080;
                this->regTable[0][3] = IN2_3G_1920x1080;
                this->regTable[1][2] = IN2_3G_1920x1080;
                this->regTable[1][3] = IN2_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);


            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                this->regTable[2][0] = 0;
                this->regTable[2][1] = 0;
                this->regTable[3][0] = 0;
                this->regTable[3][1] = 0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[2][0] = IN2_3G_1920x1080;
                this->regTable[2][1] = IN2_3G_1920x1080;
                this->regTable[3][0] = IN2_3G_1920x1080;
                this->regTable[3][1] = IN2_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);


            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                this->regTable[2][2] = 0;
                this->regTable[2][3] = 0;
                this->regTable[3][2] = 0;
                this->regTable[3][3] = 0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[2][2] = IN2_3G_1920x1080;
                this->regTable[2][3] = IN2_3G_1920x1080;
                this->regTable[3][2] = IN2_3G_1920x1080;
                this->regTable[3][3] = IN2_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(Img3GIn2Size == INPUT_SIZE_960X540)
        {
            img3GIn2SizeReg = IN_3G_SIZE_960x540;
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
                {
                    this->regTable[0][0] = 0;
                    this->regTable[0][1] = 0;
                    this->regTable[1][0] = 0;
                    this->regTable[1][1] = 0;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
                {
                    this->regTable[0][2] = 0;
                    this->regTable[0][3] = 0;
                    this->regTable[1][2] = 0;
                    this->regTable[1][3] = 0;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
                {
                    this->regTable[2][0] = 0;
                    this->regTable[2][1] = 0;
                    this->regTable[3][0] = 0;
                    this->regTable[3][1] = 0;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }

            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
                {
                    this->regTable[2][2] = 0;
                    this->regTable[2][3] = 0;
                    this->regTable[3][2] = 0;
                    this->regTable[3][3] = 0;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);

                }
            }
        }
        else if(Img3GIn2Size == INPUT_SIZE_FULL)
        {
            img3GIn2SizeReg = IN_3G_SIZE_1920X1080;   //全屏显示需要先将视频管道切到 1080P
            if(regindex >= 0 && regindex <= 15)
            {
                displayModeReg = SDI_4K_FROM_IN2;
            }
            emit this->regChange((unsigned int *)regTable);
        }

    }
    else if(ImgType == IMG_COLOR)
    {
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {
                this->regTable[0][0] =  0;
                this->regTable[0][1] =  0;
                this->regTable[1][0] =  0;
                this->regTable[1][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                this->regTable[0][2] =  0;
                this->regTable[0][3] =  0;
                this->regTable[1][2] =  0;
                this->regTable[1][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {
                this->regTable[2][0] =  0;
                this->regTable[2][1] =  0;
                this->regTable[3][0] =  0;
                this->regTable[3][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);

            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {
                this->regTable[2][2] =  0;
                this->regTable[2][3] =  0;
                this->regTable[3][2] =  0;
                this->regTable[3][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }

    }
    else if(ImgType == IMG_AI_IN1)
    {

        this->detectionStateReg = DETECTION_IN1;
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {
                this->regTable[0][0] =  0;
                this->regTable[0][1] =  0;
                this->regTable[1][0] =  0;
                this->regTable[1][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                this->regTable[0][2] =  0;
                this->regTable[0][3] =  0;
                this->regTable[1][2] =  0;
                this->regTable[1][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {
                this->regTable[2][0] =  0;
                this->regTable[2][1] =  0;
                this->regTable[3][0] =  0;
                this->regTable[3][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {
                this->regTable[2][2] =  0;
                this->regTable[2][3] =  0;
                this->regTable[3][2] =  0;
                this->regTable[3][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }

    }
    else if(ImgType == IMG_AI_IN2)
    {

        this->detectionStateReg = DETECTION_IN2;
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {
                this->regTable[0][0] =  0;
                this->regTable[0][1] =  0;
                this->regTable[1][0] =  0;
                this->regTable[1][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                this->regTable[0][2] =  0;
                this->regTable[0][3] =  0;
                this->regTable[1][2] =  0;
                this->regTable[1][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {
                this->regTable[2][0] =  0;
                this->regTable[2][1] =  0;
                this->regTable[3][0] =  0;
                this->regTable[3][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {
                this->regTable[2][2] =  0;
                this->regTable[2][3] =  0;
                this->regTable[3][2] =  0;
                this->regTable[3][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }

    }
    else if(ImgType == IMG_LVDS_IN1)
    {
        this->lvdsInSwitchReg = LVDS_IN1;
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {
                this->regTable[0][0] =  0;
                this->regTable[0][1] =  0;
                this->regTable[1][0] =  0;
                this->regTable[1][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                this->regTable[0][2] =  0;
                this->regTable[0][3] =  0;
                this->regTable[1][2] =  0;
                this->regTable[1][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {
                this->regTable[2][0] =  0;
                this->regTable[2][1] =  0;
                this->regTable[3][0] =  0;
                this->regTable[3][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {
                this->regTable[2][2] =  0;
                this->regTable[2][3] =  0;
                this->regTable[3][2] =  0;
                this->regTable[3][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
    }

    else if(ImgType == IMG_LVDS_IN2)
    {
        this->lvdsInSwitchReg = LVDS_IN2;
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {
                this->regTable[0][0] =  0;
                this->regTable[0][1] =  0;
                this->regTable[1][0] =  0;
                this->regTable[1][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                this->regTable[0][2] =  0;
                this->regTable[0][3] =  0;
                this->regTable[1][2] =  0;
                this->regTable[1][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {
                this->regTable[2][0] =  0;
                this->regTable[2][1] =  0;
                this->regTable[3][0] =  0;
                this->regTable[3][1] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {
                this->regTable[2][2] =  0;
                this->regTable[2][3] =  0;
                this->regTable[3][2] =  0;
                this->regTable[3][3] =  0;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                this->regTable[zone_y][zone_x] = LVDS_IN_960x540;
                emit this->regChange((unsigned int *)regTable);

            }
        }
    }
}

void ImgLabel::clearImg(unsigned int zone_x, unsigned int zone_y)
{

    unsigned int regindex = zone_y * 4 + zone_x;
    displayModeReg = SDI_4K_16;
    qDebug()<<ImgType;
    if(ImgType == IMG_IN1_3G)
    {
        if(Img3GIn1Size == INPUT_SIZE_1920X1080)
        {
            img3GIn1SizeReg = IN_3G_SIZE_1920X1080;
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                if(this->isBoard1)
                {
                    this->regTable[0][0] = COLOR_960x540;
                    this->regTable[0][1] = COLOR_960x540;
                    this->regTable[1][0] = COLOR_960x540;
                    this->regTable[1][1] = COLOR_960x540;
                }
                else
                {
                    this->regTable[0][0] = 0;
                    this->regTable[0][1] = 0;
                    this->regTable[1][0] = 0;
                    this->regTable[1][1] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                if(this->isBoard1)
                {
                    this->regTable[0][2] = COLOR_960x540;
                    this->regTable[0][3] = COLOR_960x540;
                    this->regTable[1][2] = COLOR_960x540;
                    this->regTable[1][3] = COLOR_960x540;
                }
                else
                {
                    this->regTable[0][2] = 0;
                    this->regTable[0][3] = 0;
                    this->regTable[1][2] = 0;
                    this->regTable[1][3] = 0;
                }

                emit this->regChange((unsigned int *)regTable);


            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                if(this->isBoard1)
                {
                    this->regTable[2][0] = COLOR_960x540;
                    this->regTable[2][1] = COLOR_960x540;
                    this->regTable[3][0] = COLOR_960x540;
                    this->regTable[3][1] = COLOR_960x540;
                }
                else
                {
                    this->regTable[2][0] = 0;
                    this->regTable[2][1] = 0;
                    this->regTable[3][0] = 0;
                    this->regTable[3][1] = 0;
                }
                emit this->regChange((unsigned int *)regTable);



            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                if(this->isBoard1)
                {
                    this->regTable[2][2] = COLOR_960x540;
                    this->regTable[2][3] = COLOR_960x540;
                    this->regTable[3][2] = COLOR_960x540;
                    this->regTable[3][3] = COLOR_960x540;
                }
                else
                {
                    this->regTable[2][2] = 0;
                    this->regTable[2][3] = 0;
                    this->regTable[3][2] = 0;
                    this->regTable[3][3] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(Img3GIn1Size == INPUT_SIZE_960X540)
        {
            img3GIn1SizeReg = IN_3G_SIZE_960x540;
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                if(regTable[0][0] == IN1_3G_1920x1080 || regTable[0][0] == IN2_3G_1920x1080)
                {

                    if(this->isBoard1)
                    {
                        this->regTable[0][0] = COLOR_960x540;
                        this->regTable[0][1] = COLOR_960x540;
                        this->regTable[1][0] = COLOR_960x540;
                        this->regTable[1][1] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[0][0] = 0;
                        this->regTable[0][1] = 0;
                        this->regTable[1][0] = 0;
                        this->regTable[1][1] = 0;
                    }

                    emit this->regChange((unsigned int *)regTable);
                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }

                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                if(regTable[0][2] == IN1_3G_1920x1080 || regTable[0][2] == IN2_3G_1920x1080)
                {
                    if(this->isBoard1)
                    {
                        this->regTable[0][2] = COLOR_960x540;
                        this->regTable[0][3] = COLOR_960x540;
                        this->regTable[1][2] = COLOR_960x540;
                        this->regTable[1][3] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[0][2] = 0;
                        this->regTable[0][3] = 0;
                        this->regTable[1][2] = 0;
                        this->regTable[1][3] = 0;
                    }

                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                if(regTable[2][0] == IN1_3G_1920x1080 || regTable[2][0] == IN2_3G_1920x1080)
                {
                    if(this->isBoard1)
                    {
                        this->regTable[2][0] = COLOR_960x540;
                        this->regTable[2][1] = COLOR_960x540;
                        this->regTable[3][0] = COLOR_960x540;
                        this->regTable[3][1] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[2][0] = 0;
                        this->regTable[2][1] = 0;
                        this->regTable[3][0] = 0;
                        this->regTable[3][1] = 0;
                    }

                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }

            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                if(regTable[2][2] == IN1_3G_1920x1080 || regTable[2][2] == IN2_3G_1920x1080)
                {

                    if(this->isBoard1)
                    {
                        this->regTable[2][2] = COLOR_960x540;
                        this->regTable[2][3] = COLOR_960x540;
                        this->regTable[3][2] = COLOR_960x540;
                        this->regTable[3][3] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[2][2] = 0;
                        this->regTable[2][3] = 0;
                        this->regTable[3][2] = 0;
                        this->regTable[3][3] = 0;
                    }

                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
            }
        }
        else if(Img3GIn1Size == INPUT_SIZE_FULL)
        {
            this->resetRegData();
            emit this->regChange((unsigned int *)regTable);
        }
    }
    else if(ImgType == IMG_IN2_3G)
    {
        if(Img3GIn2Size == INPUT_SIZE_1920X1080)
        {
            img3GIn2SizeReg = IN_3G_SIZE_1920X1080;
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                if(this->isBoard1)
                {
                    this->regTable[0][0] = COLOR_960x540;
                    this->regTable[0][1] = COLOR_960x540;
                    this->regTable[1][0] = COLOR_960x540;
                    this->regTable[1][1] = COLOR_960x540;
                }
                else
                {
                    this->regTable[0][0] = 0;
                    this->regTable[0][1] = 0;
                    this->regTable[1][0] = 0;
                    this->regTable[1][1] = 0;
                }
                emit this->regChange((unsigned int *)regTable);


            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {

                if(this->isBoard1)
                {
                    this->regTable[0][2] = COLOR_960x540;
                    this->regTable[0][3] = COLOR_960x540;
                    this->regTable[1][2] = COLOR_960x540;
                    this->regTable[1][3] = COLOR_960x540;
                }
                else
                {
                   this->regTable[0][2] = 0;
                   this->regTable[0][3] = 0;
                   this->regTable[1][2] = 0;
                   this->regTable[1][3] = 0;
                }
                emit this->regChange((unsigned int *)regTable);



            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                if(this->isBoard1)
                {
                    this->regTable[2][0] = COLOR_960x540;
                    this->regTable[2][1] = COLOR_960x540;
                    this->regTable[3][0] = COLOR_960x540;
                    this->regTable[3][1] = COLOR_960x540;
                }
                else
                {
                   this->regTable[2][0] = 0;
                   this->regTable[2][1] = 0;
                   this->regTable[3][0] = 0;
                   this->regTable[3][1] = 0;
                }

                emit this->regChange((unsigned int *)regTable);


            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {

                if(this->isBoard1)
                {
                    this->regTable[2][2] = COLOR_960x540;
                    this->regTable[2][3] = COLOR_960x540;
                    this->regTable[3][2] = COLOR_960x540;
                    this->regTable[3][3] = COLOR_960x540;
                }
                else
                {
                   this->regTable[2][2] = 0;
                   this->regTable[2][3] = 0;
                   this->regTable[3][2] = 0;
                   this->regTable[3][3] = 0;
                }

                emit this->regChange((unsigned int *)regTable);
            }
        }
        else if(Img3GIn2Size == INPUT_SIZE_960X540)
        {
            img3GIn2SizeReg = IN_3G_SIZE_960x540;
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
                {
                    if(this->isBoard1)
                    {
                        this->regTable[0][0] = COLOR_960x540;
                        this->regTable[0][1] = COLOR_960x540;
                        this->regTable[1][0] = COLOR_960x540;
                        this->regTable[1][1] = COLOR_960x540;
                    }
                    else
                    {
                       this->regTable[0][0] = 0;
                       this->regTable[0][1] = 0;
                       this->regTable[1][0] = 0;
                       this->regTable[1][1] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
                {
                    if(this->isBoard1)
                    {
                         this->regTable[0][2] = COLOR_960x540;
                         this->regTable[0][3] = COLOR_960x540;
                         this->regTable[1][2] = COLOR_960x540;
                         this->regTable[1][3] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[0][2] = 0;
                        this->regTable[0][3] = 0;
                        this->regTable[1][2] = 0;
                        this->regTable[1][3] = 0;
                    }

                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
                {
                    if(this->isBoard1)
                    {
                         this->regTable[2][0] = COLOR_960x540;
                         this->regTable[2][1] = COLOR_960x540;
                         this->regTable[3][0] = COLOR_960x540;
                         this->regTable[3][1] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[2][0] = 0;
                        this->regTable[2][1] = 0;
                        this->regTable[3][0] = 0;
                        this->regTable[3][1] = 0;
                    }

                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }

            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
                {
                    if(this->isBoard1)
                    {
                         this->regTable[2][2] = COLOR_960x540;
                         this->regTable[2][3] = COLOR_960x540;
                         this->regTable[3][2] = COLOR_960x540;
                         this->regTable[3][3] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[2][2] = 0;
                        this->regTable[2][3] = 0;
                        this->regTable[3][2] = 0;
                        this->regTable[3][3] = 0;
                    }

                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);

                    if(this->isBoard1)
                    {
                        this->regTable[zone_y][zone_x] = COLOR_960x540;
                    }
                    else
                    {
                        this->regTable[zone_y][zone_x] = 0;
                    }
                    emit this->regChange((unsigned int *)regTable);

                }
            }
        }
        else if(Img3GIn2Size == INPUT_SIZE_FULL)
        {
            this->resetRegData();
            emit this->regChange((unsigned int *)regTable);
        }

    }
    else if(ImgType == IMG_COLOR)
    {
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {
                if(this->isBoard1)
                {
                     this->regTable[0][0] = COLOR_960x540;
                     this->regTable[0][1] = COLOR_960x540;
                     this->regTable[1][0] = COLOR_960x540;
                     this->regTable[1][1] = COLOR_960x540;
                }
                else
                {
                    this->regTable[0][0] = 0;
                    this->regTable[0][1] = 0;
                    this->regTable[1][0] = 0;
                    this->regTable[1][1] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                if(this->isBoard1)
                {
                     this->regTable[0][2] = COLOR_960x540;
                     this->regTable[0][3] = COLOR_960x540;
                     this->regTable[1][2] = COLOR_960x540;
                     this->regTable[1][3] = COLOR_960x540;
                }
                else
                {
                    this->regTable[0][2] = 0;
                    this->regTable[0][3] = 0;
                    this->regTable[1][2] = 0;
                    this->regTable[1][3] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {
                if(this->isBoard1)
                {
                     this->regTable[2][0] = COLOR_960x540;
                     this->regTable[2][1] = COLOR_960x540;
                     this->regTable[3][0] = COLOR_960x540;
                     this->regTable[3][1] = COLOR_960x540;
                }
                else
                {
                    this->regTable[2][0] = 0;
                    this->regTable[2][1] = 0;
                    this->regTable[3][0] = 0;
                    this->regTable[3][1] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {
                if(this->isBoard1)
                {
                     this->regTable[2][2] = COLOR_960x540;
                     this->regTable[2][3] = COLOR_960x540;
                     this->regTable[3][2] = COLOR_960x540;
                     this->regTable[3][3] = COLOR_960x540;
                }
                else
                {
                    this->regTable[2][2] = 0;
                    this->regTable[2][3] = 0;
                    this->regTable[3][2] = 0;
                    this->regTable[3][3] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
        }

    }
    else if(ImgType == IMG_AI_IN1 || ImgType == IMG_AI_IN2)
    {
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {
                if(this->isBoard1)
                {
                     this->regTable[0][0] = COLOR_960x540;
                     this->regTable[0][1] = COLOR_960x540;
                     this->regTable[1][0] = COLOR_960x540;
                     this->regTable[1][1] = COLOR_960x540;
                }
                else
                {
                    this->regTable[0][0] = 0;
                    this->regTable[0][1] = 0;
                    this->regTable[1][0] = 0;
                    this->regTable[1][1] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                if(this->isBoard1)
                {
                    this->regTable[0][2] = COLOR_960x540;
                    this->regTable[0][3] = COLOR_960x540;
                    this->regTable[1][2] = COLOR_960x540;
                    this->regTable[1][3] = COLOR_960x540;
                }
                else
                {
                   this->regTable[0][2] = 0;
                   this->regTable[0][3] = 0;
                   this->regTable[1][2] = 0;
                   this->regTable[1][3] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {

                if(this->isBoard1)
                {
                    this->regTable[2][0] = COLOR_960x540;
                    this->regTable[2][1] = COLOR_960x540;
                    this->regTable[3][0] = COLOR_960x540;
                    this->regTable[3][1] = COLOR_960x540;
                }
                else
                {
                   this->regTable[2][0] = 0;
                   this->regTable[2][1] = 0;
                   this->regTable[3][0] = 0;
                   this->regTable[3][1] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {

                if(this->isBoard1)
                {
                    this->regTable[2][2] = COLOR_960x540;
                    this->regTable[2][3] = COLOR_960x540;
                    this->regTable[3][2] = COLOR_960x540;
                    this->regTable[3][3] = COLOR_960x540;
                }
                else
                {
                   this->regTable[2][2] = 0;
                   this->regTable[2][3] = 0;
                   this->regTable[3][2] = 0;
                   this->regTable[3][3] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
        }

    }
    else if(ImgType == IMG_LVDS_IN1)
    {
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {

                if(this->isBoard1)
                {
                    this->regTable[0][0] = COLOR_960x540;
                    this->regTable[0][1] = COLOR_960x540;
                    this->regTable[1][0] = COLOR_960x540;
                    this->regTable[1][1] = COLOR_960x540;
                }
                else
                {
                   this->regTable[0][0] = 0;
                   this->regTable[0][1] = 0;
                   this->regTable[1][0] = 0;
                   this->regTable[1][1] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                if(this->isBoard1)
                {
                    this->regTable[0][2] = COLOR_960x540;
                    this->regTable[0][3] = COLOR_960x540;
                    this->regTable[1][2] = COLOR_960x540;
                    this->regTable[1][3] = COLOR_960x540;
                }
                else
                {
                   this->regTable[0][2] = 0;
                   this->regTable[0][3] = 0;
                   this->regTable[1][2] = 0;
                   this->regTable[1][3] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {
                if(this->isBoard1)
                {
                    this->regTable[2][0] = COLOR_960x540;
                    this->regTable[2][1] = COLOR_960x540;
                    this->regTable[3][0] = COLOR_960x540;
                    this->regTable[3][1] = COLOR_960x540;
                }
                else
                {
                   this->regTable[2][0] = 0;
                   this->regTable[2][1] = 0;
                   this->regTable[3][0] = 0;
                   this->regTable[3][1] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {
                if(this->isBoard1)
                {
                    this->regTable[2][2] = COLOR_960x540;
                    this->regTable[2][3] = COLOR_960x540;
                    this->regTable[3][2] = COLOR_960x540;
                    this->regTable[3][3] = COLOR_960x540;
                }
                else
                {
                   this->regTable[2][2] = 0;
                   this->regTable[2][3] = 0;
                   this->regTable[3][2] = 0;
                   this->regTable[3][3] = 0;
                }

                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);

                if(this->isBoard1)
                {
                    this->regTable[zone_y][zone_x] = COLOR_960x540;
                }
                else
                {
                    this->regTable[zone_y][zone_x] = 0;
                }
                emit this->regChange((unsigned int *)regTable);

            }
        }
    }

}



void ImgLabel::InitConnect()
{
    connect(this,SIGNAL(mousePaint()),this,SLOT(updataImg()));
}

void ImgLabel::enterEvent(QEvent *event)
{
   // qDebug()<<"enter"<<endl;
}

void ImgLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug()<<"LeftButton press"<<endl;
        unsigned int Pos_X = 0; //鼠标点击坐标
        unsigned int Pos_Y = 0;
        unsigned int Zone_X = 0;
        unsigned int Zone_Y = 0;
        Pos_X = event->x();
        Pos_Y = event->y();

        if(Pos_Y >= 0 && Pos_Y < DrawWindowQuarHeight)
        {
            Zone_Y = 0;
        }
        else if (Pos_Y >= DrawWindowQuarHeight && Pos_Y < (DrawWindowQuarHeight * 2))
        {
            Zone_Y = 1;
        }
        else if (Pos_Y >= (DrawWindowQuarHeight * 2) && Pos_Y < (DrawWindowQuarHeight * 3))
        {
            Zone_Y = 2;
        }
        else if (Pos_Y >= (DrawWindowQuarHeight * 3) && Pos_Y < DrawWindowHeight)
        {
            Zone_Y = 3;
        }
        else
        {
            Zone_Y = 0;
        }

        if(Pos_X >= 0 && Pos_X < DrawWindowQuarWidth)
        {
            Zone_X = 0;
        }
        else if (Pos_X >= DrawWindowQuarWidth && Pos_X < (DrawWindowQuarWidth * 2))
        {
            Zone_X = 1;
        }
        else if (Pos_X >= (DrawWindowQuarWidth * 2) && Pos_X < (DrawWindowQuarWidth * 3))
        {
            Zone_X = 2;
        }
        else if (Pos_X >= (DrawWindowQuarWidth * 3) && Pos_X < DrawWindowWidth)
        {
            Zone_X = 3;
        }
        else
        {
            Zone_X = 3;
        }
        handleImgControl(Zone_X, Zone_Y);
        emit this->mousePaint();

    }

    if(event->button() == Qt::RightButton)
    {
        //PrintRegTable();
        qDebug()<<"LeftButton press"<<endl;
        unsigned int Pos_X = 0; //鼠标点击坐标
        unsigned int Pos_Y = 0;
        unsigned int Zone_X = 0;
        unsigned int Zone_Y = 0;
        Pos_X = event->x();
        Pos_Y = event->y();

        if(Pos_Y >= 0 && Pos_Y < DrawWindowQuarHeight)
        {
            Zone_Y = 0;
        }
        else if (Pos_Y >= DrawWindowQuarHeight && Pos_Y < (DrawWindowQuarHeight * 2))
        {
            Zone_Y = 1;
        }
        else if (Pos_Y >= (DrawWindowQuarHeight * 2) && Pos_Y < (DrawWindowQuarHeight * 3))
        {
            Zone_Y = 2;
        }
        else if (Pos_Y >= (DrawWindowQuarHeight * 3) && Pos_Y < DrawWindowHeight)
        {
            Zone_Y = 3;
        }
        else
        {
            Zone_Y = 0;
        }

        if(Pos_X >= 0 && Pos_X < DrawWindowQuarWidth)
        {
            Zone_X = 0;
        }
        else if (Pos_X >= DrawWindowQuarWidth && Pos_X < (DrawWindowQuarWidth * 2))
        {
            Zone_X = 1;
        }
        else if (Pos_X >= (DrawWindowQuarWidth * 2) && Pos_X < (DrawWindowQuarWidth * 3))
        {
            Zone_X = 2;
        }
        else if (Pos_X >= (DrawWindowQuarWidth * 3) && Pos_X < DrawWindowWidth)
        {
            Zone_X = 3;
        }
        else
        {
            Zone_X = 3;
        }
        clearImg(Zone_X, Zone_Y);
        emit this->mousePaint();
    }

}

void ImgLabel::paintEvent(QPaintEvent *event)
{
    //qDebug()<<"SUBpaintEvent"<<endl;
    QPainter *painter = new QPainter(this);

    painter->drawPixmap(0,0,DrawWindowWidth,DrawWindowHeight,this->pixBlank);

    for(int i = 0 ; i <= 2; i+=2)
    {
        for(int j = 0; j <= 2; j+=2)
        {
            if(this->regTable[i][j] == IN1_3G_1920x1080)
            {
                painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth*2,DrawWindowQuarHeight*2,this->pix3GIN1);
            }
            if(this->regTable[i][j] == IN2_3G_1920x1080)
            {
                painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth*2,DrawWindowQuarHeight*2,this->pix3GIN2);
            }
        }
    }

    for(int i = 0 ; i <= 3; i++)
    {
        for(int j = 0; j <= 3; j++)
        {
            if(this->regTable[i][j] == IN1_3G_960x540)
            {
                painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pix3GIN1);
            }
            if(this->regTable[i][j] == IN2_3G_960x540)
            {
                painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pix3GIN2);
            }
            if(this->regTable[i][j] == COLOR_960x540)
            {
                painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pixColor);
            }
            if(this->regTable[i][j] == DETECTION_960x540)
            {
                if(this->detectionStateReg == DETECTION_IN1)
                {
                    painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pixDetectionIN1);
                }
                else if(this->detectionStateReg == DETECTION_IN2)
                {
                    painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pixDetectionIN2);
                }

            }
            if(this->regTable[i][j] == LVDS_IN_960x540)
            {
                if(this->lvdsInSwitchReg == LVDS_IN1)
                {
                    painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->lvdsIN1);
                }
                else if(this->lvdsInSwitchReg == LVDS_IN2)
                {
                    painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->lvdsIN2);
                }
            }

        }
    }

    if(this->displayModeReg == SDI_4K_FROM_IN1)
    {
        painter->drawPixmap(0,0,DrawWindowQuarWidth * 4, DrawWindowQuarHeight * 4,this->pix3GIN1);
    }

    if(this->displayModeReg == SDI_4K_FROM_IN2)
    {
        painter->drawPixmap(0,0,DrawWindowQuarWidth * 4, DrawWindowQuarHeight * 4,this->pix3GIN2);
    }

    painter->setPen(0x010101);
    painter->drawRect(0,0,DrawWindowWidth,DrawWindowHeight);

    painter->drawLine(DrawWindowQuarWidth,0,DrawWindowQuarWidth,DrawWindowHeight);
    painter->drawLine(DrawWindowQuarWidth * 2,0,DrawWindowQuarWidth * 2,DrawWindowHeight);
    painter->drawLine(DrawWindowQuarWidth * 3,0,DrawWindowQuarWidth * 3,DrawWindowHeight);

    painter->drawLine(0, DrawWindowQuarHeight, DrawWindowWidth, DrawWindowQuarHeight);
    painter->drawLine(0, DrawWindowQuarHeight * 2,DrawWindowWidth, DrawWindowQuarHeight * 2);
    painter->drawLine(0, DrawWindowQuarHeight * 3,DrawWindowWidth, DrawWindowQuarHeight * 3);

    delete painter;

    emit this->imgoverlayupdataImg();
}

void ImgLabel::updataImg()
{
    qDebug()<<"SUBupdate();"<<endl;
    this->update();  //更新会调用绘图事件
}
