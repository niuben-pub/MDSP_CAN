#include "imglabel.h"
#include <QDebug>

ImgLabel::ImgLabel(QWidget *parent) : QLabel(parent)
{
    InitConnect();
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
    if(ImgType == IMG_IN1_3G)
    {
        if(Img3GIn1Size == INPUT_SIZE_1920X1080)
        {
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                this->regTable[0][0] = 0;
                this->regTable[0][1] = 1;
                this->regTable[1][0] = 4;
                this->regTable[1][1] = 5;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[0][0] = IN1_3G_1920x1080;
                this->regTable[0][1] = IN1_3G_1920x1080;
                this->regTable[1][0] = IN1_3G_1920x1080;
                this->regTable[1][1] = IN1_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                this->regTable[0][2] = 2;
                this->regTable[0][3] = 3;
                this->regTable[1][2] = 6;
                this->regTable[1][3] = 7;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[0][2] = IN1_3G_1920x1080;
                this->regTable[0][3] = IN1_3G_1920x1080;
                this->regTable[1][2] = IN1_3G_1920x1080;
                this->regTable[1][3] = IN1_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();

            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                this->regTable[2][0] = 8;
                this->regTable[2][1] = 9;
                this->regTable[3][0] = 12;
                this->regTable[3][1] = 13;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[2][0] = IN1_3G_1920x1080;
                this->regTable[2][1] = IN1_3G_1920x1080;
                this->regTable[3][0] = IN1_3G_1920x1080;
                this->regTable[3][1] = IN1_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();

            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                this->regTable[2][2] = 10;
                this->regTable[2][3] = 11;
                this->regTable[3][2] = 14;
                this->regTable[3][3] = 15;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[2][2] = IN1_3G_1920x1080;
                this->regTable[2][3] = IN1_3G_1920x1080;
                this->regTable[3][2] = IN1_3G_1920x1080;
                this->regTable[3][3] = IN1_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
        }
        else if(Img3GIn1Size == INPUT_SIZE_960X540)
        {
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                if(regTable[0][0] == IN1_3G_1920x1080 || regTable[0][0] == IN2_3G_1920x1080)
                {
                    this->regTable[0][0] = 0;
                    this->regTable[0][1] = 1;
                    this->regTable[1][0] = 4;
                    this->regTable[1][1] = 5;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                if(regTable[0][2] == IN1_3G_1920x1080 || regTable[0][2] == IN2_3G_1920x1080)
                {
                    this->regTable[0][2] = 2;
                    this->regTable[0][3] = 3;
                    this->regTable[1][2] = 6;
                    this->regTable[1][3] = 7;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                if(regTable[2][0] == IN1_3G_1920x1080 || regTable[2][0] == IN2_3G_1920x1080)
                {
                    this->regTable[2][0] = 8;
                    this->regTable[2][1] = 9;
                    this->regTable[3][0] = 12;
                    this->regTable[3][1] = 13;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }

            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                if(regTable[2][2] == IN1_3G_1920x1080 || regTable[2][2] == IN2_3G_1920x1080)
                {
                    this->regTable[2][2] = 10;
                    this->regTable[2][3] = 11;
                    this->regTable[3][2] = 14;
                    this->regTable[3][3] = 15;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN1_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
            }
        }
    }
    else if(ImgType == IMG_IN2_3G)
    {
        if(Img3GIn2Size == INPUT_SIZE_1920X1080)
        {
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                this->regTable[0][0] = 0;
                this->regTable[0][1] = 1;
                this->regTable[1][0] = 4;
                this->regTable[1][1] = 5;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[0][0] = IN2_3G_1920x1080;
                this->regTable[0][1] = IN2_3G_1920x1080;
                this->regTable[1][0] = IN2_3G_1920x1080;
                this->regTable[1][1] = IN2_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                this->regTable[0][2] = 2;
                this->regTable[0][3] = 3;
                this->regTable[1][2] = 6;
                this->regTable[1][3] = 7;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[0][2] = IN2_3G_1920x1080;
                this->regTable[0][3] = IN2_3G_1920x1080;
                this->regTable[1][2] = IN2_3G_1920x1080;
                this->regTable[1][3] = IN2_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();

            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                this->regTable[2][0] = 8;
                this->regTable[2][1] = 9;
                this->regTable[3][0] = 12;
                this->regTable[3][1] = 13;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[2][0] = IN2_3G_1920x1080;
                this->regTable[2][1] = IN2_3G_1920x1080;
                this->regTable[3][0] = IN2_3G_1920x1080;
                this->regTable[3][1] = IN2_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();

            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                this->regTable[2][2] = 10;
                this->regTable[2][3] = 11;
                this->regTable[3][2] = 14;
                this->regTable[3][3] = 15;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[2][2] = IN2_3G_1920x1080;
                this->regTable[2][3] = IN2_3G_1920x1080;
                this->regTable[3][2] = IN2_3G_1920x1080;
                this->regTable[3][3] = IN2_3G_1920x1080;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
        }
        else if(Img3GIn2Size == INPUT_SIZE_960X540)
        {
            if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
            {
                if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
                {
                    this->regTable[0][0] = 0;
                    this->regTable[0][1] = 1;
                    this->regTable[1][0] = 4;
                    this->regTable[1][1] = 5;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
            }
            else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
            {
                if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
                {
                    this->regTable[0][2] = 2;
                    this->regTable[0][3] = 3;
                    this->regTable[1][2] = 6;
                    this->regTable[1][3] = 7;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
            }
            else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
            {
                if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
                {
                    this->regTable[2][0] = 8;
                    this->regTable[2][1] = 9;
                    this->regTable[3][0] = 12;
                    this->regTable[3][1] = 13;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }

            }
            else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
            {
                if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
                {
                    this->regTable[2][2] = 10;
                    this->regTable[2][3] = 11;
                    this->regTable[3][2] = 14;
                    this->regTable[3][3] = 15;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
                else
                {
                    this->regTable[zone_y][zone_x] = regindex;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                    this->regTable[zone_y][zone_x] = IN2_3G_960x540;
                    emit this->regChange((unsigned int *)regTable);
                    PrintRegTable();
                }
            }
        }

    }
    else if(ImgType == IMG_COLOR)
    {
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {
                this->regTable[0][0] = 0;
                this->regTable[0][1] = 1;
                this->regTable[1][0] = 4;
                this->regTable[1][1] = 5;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                this->regTable[0][2] = 2;
                this->regTable[0][3] = 3;
                this->regTable[1][2] = 6;
                this->regTable[1][3] = 7;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {
                this->regTable[2][0] = 8;
                this->regTable[2][1] = 9;
                this->regTable[3][0] = 12;
                this->regTable[3][1] = 13;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {
                this->regTable[2][2] = 10;
                this->regTable[2][3] = 11;
                this->regTable[3][2] = 14;
                this->regTable[3][3] = 15;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = COLOR_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
        }

    }
    else if(ImgType == IMG_AI)
    {
        if(regindex == 0 || regindex == 1 ||regindex == 4 || regindex == 5)
        {
            if(regTable[0][0] == IN2_3G_1920x1080 || regTable[0][0] == IN1_3G_1920x1080)
            {
                this->regTable[0][0] = 0;
                this->regTable[0][1] = 1;
                this->regTable[1][0] = 4;
                this->regTable[1][1] = 5;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
        }
        else if(regindex == 2 || regindex == 3 ||regindex == 6 || regindex == 7)
        {
            if(regTable[0][2] == IN2_3G_1920x1080 || regTable[0][2] == IN1_3G_1920x1080)
            {
                this->regTable[0][2] = 2;
                this->regTable[0][3] = 3;
                this->regTable[1][2] = 6;
                this->regTable[1][3] = 7;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
        }
        else if(regindex == 8 || regindex == 9 ||regindex == 12 || regindex == 13)
        {
            if(regTable[2][0] == IN2_3G_1920x1080 || regTable[2][0] == IN1_3G_1920x1080)
            {
                this->regTable[2][0] = 8;
                this->regTable[2][1] = 9;
                this->regTable[3][0] = 12;
                this->regTable[3][1] = 13;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }

        }
        else if(regindex == 10 || regindex == 11 ||regindex == 14 || regindex == 15)
        {
            if(regTable[2][2] == IN2_3G_1920x1080 || regTable[2][2] == IN1_3G_1920x1080)
            {
                this->regTable[2][2] = 10;
                this->regTable[2][3] = 11;
                this->regTable[3][2] = 14;
                this->regTable[3][3] = 15;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
            }
            else
            {
                this->regTable[zone_y][zone_x] = regindex;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
                this->regTable[zone_y][zone_x] = DETECTION_960x540;
                emit this->regChange((unsigned int *)regTable);
                PrintRegTable();
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
    qDebug()<<"enter"<<endl;
}

void ImgLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        unsigned int Pos_X = 0; //Êó±êµã»÷×ø±ê
        unsigned int Pos_Y = 0;
        unsigned int Zone_X = 0;
        unsigned int Zone_Y = 0;
        Pos_X = event->x();
        Pos_Y = event->y();

        if(Pos_Y >= 0 && Pos_Y < 68)
        {
            Zone_Y = 0;
        }
        else if (Pos_Y >= 68 && Pos_Y < 136)
        {
            Zone_Y = 1;
        }
        else if (Pos_Y >= 136 && Pos_Y < 204)
        {
            Zone_Y = 2;
        }
        else if (Pos_Y >= 204 && Pos_Y < 270)
        {
            Zone_Y = 3;
        }
        else
        {
            Zone_Y = 0;
        }

        if(Pos_X >= 0 && Pos_X < 120)
        {
            Zone_X = 0;
        }
        else if (Pos_X >= 120 && Pos_X < 240)
        {
            Zone_X = 1;
        }
        else if (Pos_X >= 240 && Pos_X < 360)
        {
            Zone_X = 2;
        }
        else if (Pos_X >= 360 && Pos_X < 480)
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
        qDebug()<<"RightButton press"<<endl;
        PrintRegTable();
    }

}

void ImgLabel::paintEvent(QPaintEvent *event)
{
    qDebug()<<"paintEvent"<<endl;
    QPainter *painter = new QPainter(this);
    QPixmap pix;


    for(int i = 0 ; i <= 2; i+=2)
    {
        for(int j = 0; j <= 2; j+=2)
        {
            if(this->regTable[i][j] == IN1_3G_1920x1080)
            {
                pix.load(":/images/1.png");
                painter->drawPixmap(j*120,i*68,120*2,68*2,pix);
            }
            if(this->regTable[i][j] == IN2_3G_1920x1080)
            {
                pix.load(":/images/22.png");
                painter->drawPixmap(j*120,i*68,120*2,68*2,pix);
            }
        }
    }


    for(int i = 0 ; i <= 3; i++)
    {
        for(int j = 0; j <= 3; j++)
        {
            if(this->regTable[i][j] <= 15)
            {
                pix.load(":/images/0.png");
                painter->drawPixmap(j*120,i*68,120,68,pix);
            }
            if(this->regTable[i][j] == IN1_3G_960x540)
            {
                pix.load(":/images/1.png");
                painter->drawPixmap(j*120,i*68,120,68,pix);
            }
            if(this->regTable[i][j] == IN2_3G_960x540)
            {
                pix.load(":/images/22.png");
                painter->drawPixmap(j*120,i*68,120,68,pix);
            }
            if(this->regTable[i][j] == COLOR_960x540)
            {
                pix.load(":/images/col.png");
                painter->drawPixmap(j*120,i*68,120,68,pix);
            }
            if(this->regTable[i][j] == DETECTION_960x540)
            {
                pix.load(":/images/ai.png");
                painter->drawPixmap(j*120,i*68,120,68,pix);
            }

        }
    }

    painter->setPen(0x010101);
    painter->drawRect(0,0,480,270);

    painter->drawLine(120,0,120,270);
    painter->drawLine(240,0,240,270);
    painter->drawLine(360,0,360,270);

    painter->drawLine(0,68,480,68);
    painter->drawLine(0,136,480,136);
    painter->drawLine(0,204,480,204);

    delete painter;
}

void ImgLabel::updataImg()
{
    qDebug()<<"this->update();"<<endl;
    this->update();
}
