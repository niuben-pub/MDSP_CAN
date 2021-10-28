#include "imgoverlaylabel.h"
#include <QDebug>
imgoverlayLabel::imgoverlayLabel(QWidget *parent) : QLabel(parent)
{

}

void imgoverlayLabel::paintEvent(QPaintEvent *event)
{
   // qDebug()<<"SUMpaintEvent"<<endl;
    QPainter *painter = new QPainter(this);

    painter->drawPixmap(0,0,DrawWindowWidth,DrawWindowHeight,this->pixBlank);


    for(int index = 0; index < 8; index++)
    {
        for(int i = 0 ; i <= 2; i+=2)
        {
            for(int j = 0; j <= 2; j+=2)
            {
                if(this->regTableBoard[index][i][j] == OVERLY_IN1_3G_1920x1080)
                {
                    painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth*2,DrawWindowQuarHeight*2,this->pix3GIN1Board[index]);
                }
                if(this->regTableBoard[index][i][j] == OVERLY_IN2_3G_1920x1080)
                {
                    painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth*2,DrawWindowQuarHeight*2,this->pix3GIN2Board[index]);
                }
            }
        }

        for(int i = 0 ; i <= 3; i++)
        {
            for(int j = 0; j <= 3; j++)
            {
                if(this->regTableBoard[index][i][j] == OVERLY_IN1_3G_960x540)
                {
                    painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pix3GIN1Board[index]);
                }
                if(this->regTableBoard[index][i][j] == OVERLY_IN2_3G_960x540)
                {
                    painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pix3GIN2Board[index]);
                }
                if(this->regTableBoard[index][i][j] == OVERLY_COLOR_960x540)
                {
                    painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pixColorBoard[index]);
                }
                if(this->regTableBoard[index][i][j] == OVERLY_DETECTION_960x540)
                {
                    if(this->displayDetectionModeRegBoard[index] == OVERLY_DETECTION_IN1)
                    {
                        painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pixIN1DetectionBoard[index]);
                    }
                    else if(this->displayDetectionModeRegBoard[index] == OVERLY_DETECTION_IN2)
                    {
                        painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pixIN2DetectionBoard[index]);
                    }
                }
                if(this->regTableBoard[index][i][j] == OVERLY_LVDS_IN_960x540)
                {
                    if(this->displayLvdsINRegBoard[index] == OVERLY_LVDS_IN1)
                    {
                        painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pixIN1LVDSinBoard[index]);
                    }
                    else if(this->displayLvdsINRegBoard[index] == OVERLY_LVDS_IN2)
                    {
                        painter->drawPixmap(j*DrawWindowQuarWidth,i*DrawWindowQuarHeight,DrawWindowQuarWidth,DrawWindowQuarHeight,this->pixIN2LVDSinBoard[index]);
                    }


                }
            }
        }


        if(this->displayModeRegBoard[index] == OVERLY_SDI_4K_FROM_IN1)
        {
            painter->drawPixmap(0,0,DrawWindowQuarWidth * 4, DrawWindowQuarHeight * 4,this->pix3GIN1Board[index]);
        }

        if(this->displayModeRegBoard[index] == OVERLY_SDI_4K_FROM_IN2)
        {
            painter->drawPixmap(0,0,DrawWindowQuarWidth * 4, DrawWindowQuarHeight * 4,this->pix3GIN2Board[index]);
        }






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
}

void imgoverlayLabel::updataImg()
{
    //qDebug()<<"SUMupdate();"<<endl;
    this->update();  //更新会调用绘图事件
}
