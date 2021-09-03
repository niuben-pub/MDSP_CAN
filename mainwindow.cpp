#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionTab>

#include <QFileDialog>
#include <QThread>
#include <QString>
#include <QDebug>
#include <QFile>
#include <string.h>
#include <stdio.h>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QPalette>
#include "j1939_msg.h"
#include <QMessageBox>

class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 140; // 设置每个tabBar中item的大小
            s.rheight() =50;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;

                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x89cfff);
                    painter->setBrush(QBrush(0x89cfff));
                    painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0x5d5d5d);
                }

                painter->drawText(allRect, tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};


class SubCustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 120; // 设置每个tabBar中item的大小
            s.rheight() =40;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;

                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0xF8CBAD);
                    painter->setBrush(QBrush(0xF8CBAD));
                    painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0x5d5d5d);
                }

                painter->drawText(allRect, tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};

void MainWindow::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::updataFlashTime()
{
    FlashWriteTimeSec++;
}

void MainWindow::displayMonitor(VCI_CAN_OBJ *vci, DWORD dwRel)
{
    //显示接收到ADC数据

    if(vci->ID == (PGN57600 << 8) + (this->board1->readAddr))
    {
         float f_adc_data = 0.0f;
         memcpy(&f_adc_data,vci[0].Data,sizeof(f_adc_data));
         if(vci[0].Data[7] == (unsigned char)4)
         {
             this->protocolHand->MDSP_Board_currents = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)5)
         {
             this->protocolHand->MDSP_Board_HV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)6)
         {
             this->protocolHand->MDSP_Board_LV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)7)
         {
             this->protocolHand->MDSP_Board_temperature = f_adc_data;
             ui->lcdNumberCurrentBoard1->display(this->protocolHand->MDSP_Board_currents);
             ui->lcdNumberVoltage12Board1->display(this->protocolHand->MDSP_Board_HV);
             ui->lcdNumberVoltage5Board1->display(this->protocolHand->MDSP_Board_LV);
             ui->lcdNumberTempeBoard1->display(this->protocolHand->MDSP_Board_temperature);
         }

    }
    if(vci->ID == (PGN57600 << 8) + (this->board2->readAddr))
    {
         float f_adc_data = 0.0f;
         memcpy(&f_adc_data,vci[0].Data,sizeof(f_adc_data));
         if(vci[0].Data[7] == (unsigned char)4)
         {
             this->protocolHand->MDSP_Board_currents = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)5)
         {
             this->protocolHand->MDSP_Board_HV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)6)
         {
             this->protocolHand->MDSP_Board_LV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)7)
         {
             this->protocolHand->MDSP_Board_temperature = f_adc_data;
             ui->lcdNumberCurrentBoard2->display(this->protocolHand->MDSP_Board_currents);
             ui->lcdNumberVoltage12Board2->display(this->protocolHand->MDSP_Board_HV);
             ui->lcdNumberVoltage5Board2->display(this->protocolHand->MDSP_Board_LV);
             ui->lcdNumberTempeBoard2->display(this->protocolHand->MDSP_Board_temperature);
         }

    }
    if(vci->ID == (PGN57600 << 8) + (this->board3->readAddr))
    {
         float f_adc_data = 0.0f;
         memcpy(&f_adc_data,vci[0].Data,sizeof(f_adc_data));
         if(vci[0].Data[7] == (unsigned char)4)
         {
             this->protocolHand->MDSP_Board_currents = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)5)
         {
             this->protocolHand->MDSP_Board_HV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)6)
         {
             this->protocolHand->MDSP_Board_LV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)7)
         {
             this->protocolHand->MDSP_Board_temperature = f_adc_data;
             ui->lcdNumberCurrentBoard3->display(this->protocolHand->MDSP_Board_currents);
             ui->lcdNumberVoltage12Board3->display(this->protocolHand->MDSP_Board_HV);
             ui->lcdNumberVoltage5Board3->display(this->protocolHand->MDSP_Board_LV);
             ui->lcdNumberTempeBoard3->display(this->protocolHand->MDSP_Board_temperature);
         }

    }
    if(vci->ID == (PGN57600 << 8) + (this->board4->readAddr))
    {
         float f_adc_data = 0.0f;
         memcpy(&f_adc_data,vci[0].Data,sizeof(f_adc_data));
         if(vci[0].Data[7] == (unsigned char)4)
         {
             this->protocolHand->MDSP_Board_currents = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)5)
         {
             this->protocolHand->MDSP_Board_HV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)6)
         {
             this->protocolHand->MDSP_Board_LV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)7)
         {
             this->protocolHand->MDSP_Board_temperature = f_adc_data;
             ui->lcdNumberCurrentBoard4->display(this->protocolHand->MDSP_Board_currents);
             ui->lcdNumberVoltage12Board4->display(this->protocolHand->MDSP_Board_HV);
             ui->lcdNumberVoltage5Board4->display(this->protocolHand->MDSP_Board_LV);
             ui->lcdNumberTempeBoard4->display(this->protocolHand->MDSP_Board_temperature);
         }

    }
    if(vci->ID == (PGN57600 << 8) + (this->board5->readAddr))
    {
         float f_adc_data = 0.0f;
         memcpy(&f_adc_data,vci[0].Data,sizeof(f_adc_data));
         if(vci[0].Data[7] == (unsigned char)4)
         {
             this->protocolHand->MDSP_Board_currents = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)5)
         {
             this->protocolHand->MDSP_Board_HV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)6)
         {
             this->protocolHand->MDSP_Board_LV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)7)
         {
             this->protocolHand->MDSP_Board_temperature = f_adc_data;
             ui->lcdNumberCurrentBoard5->display(this->protocolHand->MDSP_Board_currents);
             ui->lcdNumberVoltage12Board5->display(this->protocolHand->MDSP_Board_HV);
             ui->lcdNumberVoltage5Board5->display(this->protocolHand->MDSP_Board_LV);
             ui->lcdNumberTempeBoard5->display(this->protocolHand->MDSP_Board_temperature);
         }

    }
    if(vci->ID == (PGN57600 << 8) + (this->board6->readAddr))
    {
         float f_adc_data = 0.0f;
         memcpy(&f_adc_data,vci[0].Data,sizeof(f_adc_data));
         if(vci[0].Data[7] == (unsigned char)4)
         {
             this->protocolHand->MDSP_Board_currents = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)5)
         {
             this->protocolHand->MDSP_Board_HV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)6)
         {
             this->protocolHand->MDSP_Board_LV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)7)
         {
             this->protocolHand->MDSP_Board_temperature = f_adc_data;
             ui->lcdNumberCurrentBoard6->display(this->protocolHand->MDSP_Board_currents);
             ui->lcdNumberVoltage12Board6->display(this->protocolHand->MDSP_Board_HV);
             ui->lcdNumberVoltage5Board6->display(this->protocolHand->MDSP_Board_LV);
             ui->lcdNumberTempeBoard6->display(this->protocolHand->MDSP_Board_temperature);
         }

    }
    if(vci->ID == (PGN57600 << 8) + (this->board7->readAddr))
    {
         float f_adc_data = 0.0f;
         memcpy(&f_adc_data,vci[0].Data,sizeof(f_adc_data));
         if(vci[0].Data[7] == (unsigned char)4)
         {
             this->protocolHand->MDSP_Board_currents = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)5)
         {
             this->protocolHand->MDSP_Board_HV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)6)
         {
             this->protocolHand->MDSP_Board_LV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)7)
         {
             this->protocolHand->MDSP_Board_temperature = f_adc_data;
             ui->lcdNumberCurrentBoard7->display(this->protocolHand->MDSP_Board_currents);
             ui->lcdNumberVoltage12Board7->display(this->protocolHand->MDSP_Board_HV);
             ui->lcdNumberVoltage5Board7->display(this->protocolHand->MDSP_Board_LV);
             ui->lcdNumberTempeBoard7->display(this->protocolHand->MDSP_Board_temperature);
         }

    }
    if(vci->ID == (PGN57600 << 8) + (this->board8->readAddr))
    {
         float f_adc_data = 0.0f;
         memcpy(&f_adc_data,vci[0].Data,sizeof(f_adc_data));
         if(vci[0].Data[7] == (unsigned char)4)
         {
             this->protocolHand->MDSP_Board_currents = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)5)
         {
             this->protocolHand->MDSP_Board_HV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)6)
         {
             this->protocolHand->MDSP_Board_LV = f_adc_data;
         }
         else if(vci[0].Data[7] == (unsigned char)7)
         {
             this->protocolHand->MDSP_Board_temperature = f_adc_data;
             ui->lcdNumberCurrentBoard8->display(this->protocolHand->MDSP_Board_currents);
             ui->lcdNumberVoltage12Board8->display(this->protocolHand->MDSP_Board_HV);
             ui->lcdNumberVoltage5Board8->display(this->protocolHand->MDSP_Board_LV);
             ui->lcdNumberTempeBoard8->display(this->protocolHand->MDSP_Board_temperature);
         }

    }

    if(vci->ID == (PGN58624 << 8) + board1->readAddr) //读取FPGA数据
    {
        unsigned int fpga_data = (unsigned int)vci[0].Data[4] << 24;
        fpga_data += (unsigned int)vci[0].Data[5] << 16;
        fpga_data += (unsigned int)vci[0].Data[6] << 8;
        fpga_data += (unsigned int)vci[0].Data[7] ;
        ui->lineEditTestDataBoard1->setText(QString::number(fpga_data,16));

        int row = 0;
        while(ui->tableWidgetTest->item(row,0) != 0)
        {
            row++;
            if(ui->tableWidgetTest->rowCount() < row + 1)
            {
                ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
                ui->tableWidgetTest->scrollToBottom();
            }
        }

        ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
        ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("R"));
        ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(vci->ID,16)));
        ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
        for(int i = 0; i < 8; i++)
        {
            ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(vci[0].Data[i],16)));
            ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
        }
    }
    if(vci->ID == (PGN58624 << 8) + board2->readAddr) //读取FPGA数据
    {
        unsigned int fpga_data = (unsigned int)vci[0].Data[4] << 24;
        fpga_data += (unsigned int)vci[0].Data[5] << 16;
        fpga_data += (unsigned int)vci[0].Data[6] << 8;
        fpga_data += (unsigned int)vci[0].Data[7] ;
        ui->lineEditTestDataBoard2->setText(QString::number(fpga_data,16));

        int row = 0;
        while(ui->tableWidgetTest->item(row,0) != 0)
        {
            row++;
            if(ui->tableWidgetTest->rowCount() < row + 1)
            {
                ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
                ui->tableWidgetTest->scrollToBottom();
            }
        }

        ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
        ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("R"));
        ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(vci->ID,16)));
        ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
        for(int i = 0; i < 8; i++)
        {
            ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(vci[0].Data[i],16)));
            ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
        }
    }
    if(vci->ID == (PGN58624 << 8) + board3->readAddr) //读取FPGA数据
    {
        unsigned int fpga_data = (unsigned int)vci[0].Data[4] << 24;
        fpga_data += (unsigned int)vci[0].Data[5] << 16;
        fpga_data += (unsigned int)vci[0].Data[6] << 8;
        fpga_data += (unsigned int)vci[0].Data[7] ;
        ui->lineEditTestDataBoard3->setText(QString::number(fpga_data,16));

        int row = 0;
        while(ui->tableWidgetTest->item(row,0) != 0)
        {
            row++;
            if(ui->tableWidgetTest->rowCount() < row + 1)
            {
                ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
                ui->tableWidgetTest->scrollToBottom();
            }
        }

        ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
        ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("R"));
        ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(vci->ID,16)));
        ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
        for(int i = 0; i < 8; i++)
        {
            ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(vci[0].Data[i],16)));
            ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
        }
    }
    if(vci->ID == (PGN58624 << 8) + board4->readAddr) //读取FPGA数据
    {
        unsigned int fpga_data = (unsigned int)vci[0].Data[4] << 24;
        fpga_data += (unsigned int)vci[0].Data[5] << 16;
        fpga_data += (unsigned int)vci[0].Data[6] << 8;
        fpga_data += (unsigned int)vci[0].Data[7] ;
        ui->lineEditTestDataBoard4->setText(QString::number(fpga_data,16));

        int row = 0;
        while(ui->tableWidgetTest->item(row,0) != 0)
        {
            row++;
            if(ui->tableWidgetTest->rowCount() < row + 1)
            {
                ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
                ui->tableWidgetTest->scrollToBottom();
            }
        }

        ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
        ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("R"));
        ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(vci->ID,16)));
        ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
        for(int i = 0; i < 8; i++)
        {
            ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(vci[0].Data[i],16)));
            ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
        }
    }
    if(vci->ID == (PGN58624 << 8) + board5->readAddr) //读取FPGA数据
    {
        unsigned int fpga_data = (unsigned int)vci[0].Data[4] << 24;
        fpga_data += (unsigned int)vci[0].Data[5] << 16;
        fpga_data += (unsigned int)vci[0].Data[6] << 8;
        fpga_data += (unsigned int)vci[0].Data[7] ;
        ui->lineEditTestDataBoard5->setText(QString::number(fpga_data,16));

        int row = 0;
        while(ui->tableWidgetTest->item(row,0) != 0)
        {
            row++;
            if(ui->tableWidgetTest->rowCount() < row + 1)
            {
                ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
                ui->tableWidgetTest->scrollToBottom();
            }
        }

        ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
        ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("R"));
        ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(vci->ID,16)));
        ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
        for(int i = 0; i < 8; i++)
        {
            ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(vci[0].Data[i],16)));
            ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
        }
    }
    if(vci->ID == (PGN58624 << 8) + board6->readAddr) //读取FPGA数据
    {
        unsigned int fpga_data = (unsigned int)vci[0].Data[4] << 24;
        fpga_data += (unsigned int)vci[0].Data[5] << 16;
        fpga_data += (unsigned int)vci[0].Data[6] << 8;
        fpga_data += (unsigned int)vci[0].Data[7] ;
        ui->lineEditTestDataBoard6->setText(QString::number(fpga_data,16));

        int row = 0;
        while(ui->tableWidgetTest->item(row,0) != 0)
        {
            row++;
            if(ui->tableWidgetTest->rowCount() < row + 1)
            {
                ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
                ui->tableWidgetTest->scrollToBottom();
            }
        }

        ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
        ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("R"));
        ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(vci->ID,16)));
        ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
        for(int i = 0; i < 8; i++)
        {
            ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(vci[0].Data[i],16)));
            ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
        }
    }
    if(vci->ID == (PGN58624 << 8) + board7->readAddr) //读取FPGA数据
    {
        unsigned int fpga_data = (unsigned int)vci[0].Data[4] << 24;
        fpga_data += (unsigned int)vci[0].Data[5] << 16;
        fpga_data += (unsigned int)vci[0].Data[6] << 8;
        fpga_data += (unsigned int)vci[0].Data[7] ;
        ui->lineEditTestDataBoard7->setText(QString::number(fpga_data,16));

        int row = 0;
        while(ui->tableWidgetTest->item(row,0) != 0)
        {
            row++;
            if(ui->tableWidgetTest->rowCount() < row + 1)
            {
                ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
                ui->tableWidgetTest->scrollToBottom();
            }
        }

        ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
        ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("R"));
        ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(vci->ID,16)));
        ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
        for(int i = 0; i < 8; i++)
        {
            ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(vci[0].Data[i],16)));
            ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
        }
    }
    if(vci->ID == (PGN58624 << 8) + board8->readAddr) //读取FPGA数据
    {
        unsigned int fpga_data = (unsigned int)vci[0].Data[4] << 24;
        fpga_data += (unsigned int)vci[0].Data[5] << 16;
        fpga_data += (unsigned int)vci[0].Data[6] << 8;
        fpga_data += (unsigned int)vci[0].Data[7] ;
        ui->lineEditTestDataBoard8->setText(QString::number(fpga_data,16));

        int row = 0;
        while(ui->tableWidgetTest->item(row,0) != 0)
        {
            row++;
            if(ui->tableWidgetTest->rowCount() < row + 1)
            {
                ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
                ui->tableWidgetTest->scrollToBottom();
            }
        }

        ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
        ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("R"));
        ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(vci->ID,16)));
        ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
        for(int i = 0; i < 8; i++)
        {
            ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(vci[0].Data[i],16)));
            ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
        }
    }


}

void MainWindow::initUi()
{
    this->setWindowTitle("MDSP-CAN Tool V1.0");


    ui->tableWidgetTest->setColumnWidth(0,90);
    ui->tableWidgetTest->setColumnWidth(1,60);
    ui->tableWidgetTest->setColumnWidth(2,76);
    for(int i = 3; i <= 10; i++)
    {
        ui->tableWidgetTest->setColumnWidth(i,28);
        ui->tableWidgetTest->setHorizontalHeaderItem(i,new QTableWidgetItem(QString::number(i - 3)));
    }

    ui->tabWidget->setCurrentIndex(0);//设置选中第一个标签
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
    ui->tabWidget_2->setCurrentIndex(0);//设置选中第一个标签
    ui->tabWidget_2->tabBar()->setStyle(new SubCustomTabStyle);
    ui->tabWidget_3->setCurrentIndex(0);//设置选中第一个标签
    ui->tabWidget_3->tabBar()->setStyle(new SubCustomTabStyle);
    ui->tabWidget_4->setCurrentIndex(0);//设置选中第一个标签
    ui->tabWidget_4->tabBar()->setStyle(new SubCustomTabStyle);
    ui->tabWidget_6->setCurrentIndex(0);//设置选中第一个标签
    ui->tabWidget_6->tabBar()->setStyle(new SubCustomTabStyle);

    ui->btnStatusBoard1->setEnabled(false); //关闭监控按钮

}

void MainWindow::initSignalslots()
{
    //接收到canthread线程接收到的数据 并显示
    connect(canthread,&CANThread::getProtocolData,this,&MainWindow::displayMonitor);
    //接收到canthread线程接收到的数据 传递到数据处理线程
    connect(canthread,&CANThread::getProtocolData,protocolHand,&ProtocolThrend::protocolHand);
    //Flash写入计时
    connect(FlashWriteTimer,SIGNAL(timeout()),this,SLOT(updataFlashTime()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canthread = new CANThread();
    protocolHand = new ProtocolThrend();
    board1 = new boardinfo();
    board2 = new boardinfo();
    board3 = new boardinfo();
    board4 = new boardinfo();
    board5 = new boardinfo();
    board6 = new boardinfo();
    board7 = new boardinfo();
    board8 = new boardinfo();
    FlashWriteTimer = new QTimer(this);
    FlashWriteTimer->stop();
    FlashWriteTimer->setInterval(1000); //设置定时周期  单位ms
    initUi();
    initSignalslots();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnDefParam_clicked()
{
    ui->CANType->setCurrentIndex(4);
    ui->index->setCurrentIndex(0);
    ui->baundRate->setCurrentIndex(13);
    ui->CANCom->setCurrentIndex(0);
}

void MainWindow::on_btnFinish_clicked()
{
    if(ui->btnFinish->text() == tr("Open"))
    {
        canthread->deviceType = ui->CANType->currentIndex();
        canthread->debicIndex = ui->index->currentIndex();
        canthread->baundRate = (int)ui->baundRate->currentText().remove("Kbps").toFloat();
        canthread->debicCom = ui->CANCom->currentIndex();

        bool dev = canthread->openCAN();
        this->sleep(3500); //等待设备启动完成
        if(dev == true)
        {
            canthread->start();
            protocolHand->start();
        }
        else
        {
            qDebug()<<"设备启动失败";
        //    QMessageBox::critical(this, tr("设备启动失败"),  tr("请检查插接口是否松动，是否重复打开设备"), QMessageBox::Ok );
            return;
        }
        ui->btnFinish->setText(tr("Close"));


    }
    else if(ui->btnFinish->text() == tr("Close"))
    {
        ui->btnFinish->setText(tr("Open"));
        canthread->stop();
        canthread->closeCAN();
    }
}

void MainWindow::on_pushButton3GINBoard1_clicked()
{
    bool ok;
    this->board1->writerAddr = ui->lineEditDevAddrBoard1->text().toULongLong(&ok,10);
    this->board1->readAddr = this->board1->writerAddr << 4;
    this->board1->IN1_3G_NUM = ui->lineEdit3GIN1Board1->text().toULongLong(&ok,10);
    this->board1->IN2_3G_NUM = ui->lineEdit3GIN2Board1->text().toULongLong(&ok,10);

}

void MainWindow::on_pushButton3GINClearBoard1_clicked()
{
    ui->lineEditDevAddrBoard1->clear();
    ui->lineEdit3GIN1Board1->clear();
    ui->lineEdit3GIN2Board1->clear();
}

void MainWindow::on_pushButton3GINBoard2_clicked()
{
    bool ok;
    this->board2->writerAddr = ui->lineEditDevAddrBoard2->text().toULongLong(&ok,10);
    this->board2->readAddr = this->board2->writerAddr << 4;
    this->board2->IN1_3G_NUM = ui->lineEdit3GIN1Board2->text().toULongLong(&ok,10);
    this->board2->IN2_3G_NUM = ui->lineEdit3GIN2Board2->text().toULongLong(&ok,10);
}

void MainWindow::on_pushButton3GINClearBoard2_clicked()
{
    ui->lineEditDevAddrBoard2->clear();
    ui->lineEdit3GIN1Board2->clear();
    ui->lineEdit3GIN2Board2->clear();
}

void MainWindow::on_pushButton3GINBoard3_clicked()
{
    bool ok;
    this->board3->writerAddr = ui->lineEditDevAddrBoard3->text().toULongLong(&ok,10);
    this->board3->readAddr = this->board3->writerAddr << 4;
    this->board3->IN1_3G_NUM = ui->lineEdit3GIN1Board3->text().toULongLong(&ok,10);
    this->board3->IN2_3G_NUM = ui->lineEdit3GIN2Board3->text().toULongLong(&ok,10);
}

void MainWindow::on_pushButton3GINClearBoard3_clicked()
{
    ui->lineEditDevAddrBoard3->clear();
    ui->lineEdit3GIN1Board3->clear();
    ui->lineEdit3GIN2Board3->clear();
}


void MainWindow::on_pushButton3GINBoard4_clicked()
{
    bool ok;
    this->board4->writerAddr = ui->lineEditDevAddrBoard4->text().toULongLong(&ok,10);
    this->board4->readAddr = this->board4->writerAddr << 4;
    this->board4->IN1_3G_NUM = ui->lineEdit3GIN1Board4->text().toULongLong(&ok,10);
    this->board4->IN2_3G_NUM = ui->lineEdit3GIN2Board4->text().toULongLong(&ok,10);
}

void MainWindow::on_pushButton3GINClearBoard4_clicked()
{
    ui->lineEditDevAddrBoard4->clear();
    ui->lineEdit3GIN1Board4->clear();
    ui->lineEdit3GIN2Board4->clear();
}

void MainWindow::on_pushButton3GINBoard5_clicked()
{
    bool ok;
    this->board5->writerAddr = ui->lineEditDevAddrBoard5->text().toULongLong(&ok,10);
    this->board5->readAddr = this->board5->writerAddr << 4;
    this->board5->IN1_3G_NUM = ui->lineEdit3GIN1Board5->text().toULongLong(&ok,10);
    this->board5->IN2_3G_NUM = ui->lineEdit3GIN2Board5->text().toULongLong(&ok,10);
}

void MainWindow::on_pushButton3GINClearBoard5_clicked()
{
    ui->lineEditDevAddrBoard5->clear();
    ui->lineEdit3GIN1Board5->clear();
    ui->lineEdit3GIN2Board5->clear();
}

void MainWindow::on_pushButton3GINBoard6_clicked()
{
    bool ok;
    this->board6->writerAddr = ui->lineEditDevAddrBoard6->text().toULongLong(&ok,10);
    this->board6->readAddr = this->board6->writerAddr << 4;
    this->board6->IN1_3G_NUM = ui->lineEdit3GIN1Board6->text().toULongLong(&ok,10);
    this->board6->IN2_3G_NUM = ui->lineEdit3GIN2Board6->text().toULongLong(&ok,10);
}

void MainWindow::on_pushButton3GINClearBoard6_clicked()
{
    ui->lineEditDevAddrBoard6->clear();
    ui->lineEdit3GIN1Board6->clear();
    ui->lineEdit3GIN2Board6->clear();
}

void MainWindow::on_pushButton3GINBoard7_clicked()
{
    bool ok;
    this->board7->writerAddr = ui->lineEditDevAddrBoard7->text().toULongLong(&ok,10);
    this->board7->readAddr = this->board7->writerAddr << 4;
    this->board7->IN1_3G_NUM = ui->lineEdit3GIN1Board7->text().toULongLong(&ok,10);
    this->board7->IN2_3G_NUM = ui->lineEdit3GIN2Board7->text().toULongLong(&ok,10);
}

void MainWindow::on_pushButton3GINClearBoard7_clicked()
{
    ui->lineEditDevAddrBoard7->clear();
    ui->lineEdit3GIN1Board7->clear();
    ui->lineEdit3GIN2Board7->clear();
}


void MainWindow::on_pushButton3GINBoard8_clicked()
{
    bool ok;
    this->board8->writerAddr = ui->lineEditDevAddrBoard8->text().toULongLong(&ok,10);
    this->board8->readAddr = this->board8->writerAddr << 4;
    this->board8->IN1_3G_NUM = ui->lineEdit3GIN1Board8->text().toULongLong(&ok,10);
    this->board8->IN2_3G_NUM = ui->lineEdit3GIN2Board8->text().toULongLong(&ok,10);
//    qDebug()<<"board1 "<<board1->readAddr<<" "<<board1->writerAddr<<" "<<board1->IN1_3G_NUM<<" "<<board1->IN2_3G_NUM;
//    qDebug()<<"board2 "<<board2->readAddr<<" "<<board2->writerAddr<<" "<<board2->IN1_3G_NUM<<" "<<board2->IN2_3G_NUM;
//    qDebug()<<"board3 "<<board3->readAddr<<" "<<board3->writerAddr<<" "<<board3->IN1_3G_NUM<<" "<<board3->IN2_3G_NUM;
//    qDebug()<<"board4 "<<board4->readAddr<<" "<<board4->writerAddr<<" "<<board4->IN1_3G_NUM<<" "<<board4->IN2_3G_NUM;
//    qDebug()<<"board5 "<<board5->readAddr<<" "<<board5->writerAddr<<" "<<board5->IN1_3G_NUM<<" "<<board5->IN2_3G_NUM;
//    qDebug()<<"board6 "<<board6->readAddr<<" "<<board6->writerAddr<<" "<<board6->IN1_3G_NUM<<" "<<board6->IN2_3G_NUM;
//    qDebug()<<"board7 "<<board7->readAddr<<" "<<board7->writerAddr<<" "<<board7->IN1_3G_NUM<<" "<<board7->IN2_3G_NUM;
//    qDebug()<<"board8 "<<board8->readAddr<<" "<<board8->writerAddr<<" "<<board8->IN1_3G_NUM<<" "<<board8->IN2_3G_NUM;
}

void MainWindow::on_pushButton3GINClearBoard8_clicked()
{
    ui->lineEditDevAddrBoard8->clear();
    ui->lineEdit3GIN1Board8->clear();
    ui->lineEdit3GIN2Board8->clear();
}

void MainWindow::on_btnStatusBoard1_clicked()
{
    if(ui->btnStatusBoard1->text() == tr("Open"))
    {
        ui->btnStatusBoard1->setText(tr("Close"));
        //this->canthread->Adc_flag = true;
        this->canthread->canThreadTimer->start();


    }
    else if(ui->btnStatusBoard1->text() == tr("Close"))
    {
        ui->btnStatusBoard1->setText(tr("Open"));
        //this->canthread->Adc_flag = false;
        this->canthread->canThreadTimer->stop();
    }
}



void MainWindow::on_btnUpdate_2_clicked()
{

    unsigned char boardNum = ui->comboBoxBoardNum_2->currentIndex() + 1;
    if(boardNum == 1)
    {
        this->protocolHand->UpdateReadAddr = board1->readAddr;
        this->protocolHand->UpdateWriteAddr = board1->writerAddr;
    }
    else if(boardNum == 2)
    {
        this->protocolHand->UpdateReadAddr = board2->readAddr;
        this->protocolHand->UpdateWriteAddr = board2->writerAddr;
    }
    else if(boardNum == 3)
    {
        this->protocolHand->UpdateReadAddr = board3->readAddr;
        this->protocolHand->UpdateWriteAddr = board3->writerAddr;
    }
    else if(boardNum == 4)
    {
        this->protocolHand->UpdateReadAddr = board4->readAddr;
        this->protocolHand->UpdateWriteAddr = board4->writerAddr;
    }
    else if(boardNum == 5)
    {
        this->protocolHand->UpdateReadAddr = board5->readAddr;
        this->protocolHand->UpdateWriteAddr = board5->writerAddr;
    }
    else if(boardNum == 6)
    {
        this->protocolHand->UpdateReadAddr = board6->readAddr;
        this->protocolHand->UpdateWriteAddr = board6->writerAddr;
    }
    else if(boardNum == 7)
    {
        this->protocolHand->UpdateReadAddr = board7->readAddr;
        this->protocolHand->UpdateWriteAddr = board7->writerAddr;
    }
    else if(boardNum == 8)
    {
        this->protocolHand->UpdateReadAddr = board8->readAddr;
        this->protocolHand->UpdateWriteAddr = board8->writerAddr;
    }


    ui->progressBar->setValue(0);
    ui->labelUpdateMsg->clear();
    ui->FlashTimelabel->clear();
    QString file_name = QFileDialog::getOpenFileName(this,tr("./"),"",tr("bbt(*.bbt)"));

    if(file_name.isEmpty())
    {
        return;
    }
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open file false";
        return;
    }
    int ID = (PGN57344 << 8) + this->protocolHand->UpdateWriteAddr;  //擦除flash 命令
    this->protocolHand->flash_inited = false; //更新Flash init状态 防止多次擦除导致的错误
    unsigned int file_size = 0; //总文件长度
    unsigned int sent_size = 0; //总文件长度
    char str[128] = "";
    unsigned char send_str[8] = {0};
    int data_len = 0;
    file_size = file.size();
    qDebug()<<"file_size "<<file_size;
    memcpy(send_str, &file_size, sizeof (file_size));

    canthread->sendData(ID,(unsigned char*)send_str);

    this->ui->labelUpdateMsg_2->setText("Erasing flash...");
    this->protocolHand->flash_init_completed();  //等待MCU完成Flash擦除
    this->ui->labelUpdateMsg_2->setText("Flash erasure is complete");
    ID = (PGN60160 << 8) + this->protocolHand->UpdateWriteAddr;  //写code 命令
    this->ui->labelUpdateMsg_2->setText("Firmware programming...");
    FlashWriteTimer->start();
    FlashWriteTimeSec = 0;
    while (!file.atEnd())
    {
        memset(str, 0, sizeof (str));
        data_len = file.read(str,128);
        for(int i = 0; i < data_len ; i += 8)
        {
            for(int j = 0; j < 8 ;j++)
            {
               send_str[j] = str[j + i];
            }
            if( data_len - i < 8 )  // 不足8字节的部分  数据填充为 0
            {
                for(int k = data_len - i  ; k < 8 ; k++)
                {
                    send_str[k] = 0;
                }
            }
            canthread->sendData(ID,(unsigned char*)send_str);

            sent_size += 8;
            ui->progressBar_2->setValue((float)sent_size / file_size * 100);
            ui->FlashTimelabel_2->setText(QString::number(FlashWriteTimeSec / 60) + ":" + QString::number(FlashWriteTimeSec % 60));
        }
    }
    this->ui->labelUpdateMsg_2->setText("update completed");
    file.close();
}

void MainWindow::on_btnUpdateMode_2_clicked()
{

    if(ui->btnStatusBoard1->text() == tr("Close"))  //关闭监控
    {
        ui->btnStatusBoard1->setText(tr("Open"));
        //this->canthread->Adc_flag = false;
        this->canthread->canThreadTimer->stop();
    }

    ui->btnStatusBoard1->setEnabled(false); //关闭该按钮

    qDebug()<<"设置工作模式";
    int ID = 0;
    unsigned char send_str[8] = {0};
    qDebug()<<"升级模式";
    send_str[7] = UPGRADEMODE;

    ID = (PGN56468 << 8) + this->board1->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board2->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board3->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board4->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board5->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board6->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board7->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board8->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);

}

void MainWindow::on_btnStatusBoard1_2_clicked()
{
    qDebug()<<"设置工作模式";
    int ID = 0;
    unsigned char send_str[8] = {0};
    qDebug()<<"监控模式";
    send_str[7] = STATUSMODE;

    ID = (PGN56468 << 8) + this->board1->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board2->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board3->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board4->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board5->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board6->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board7->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board8->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ui->btnStatusBoard1->setEnabled(true);
}

void MainWindow::on_btnUpdateMode_3_clicked()
{
    if(ui->btnStatusBoard1->text() == tr("Close"))  //关闭监控
    {
        ui->btnStatusBoard1->setText(tr("Open"));
        //this->canthread->Adc_flag = false;
        this->canthread->canThreadTimer->stop();
    }

    ui->btnStatusBoard1->setEnabled(false); //关闭该按钮

    qDebug()<<"设置工作模式";
    int ID = 0;
    unsigned char send_str[8] = {0};
    qDebug()<<"升级模式";
    send_str[7] = UPGRADEMODE;

    ID = (PGN56468 << 8) + this->board1->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board2->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board3->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board4->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board5->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board6->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board7->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
    ID = (PGN56468 << 8) + this->board8->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(50);
}

void MainWindow::on_btnUpdate_3_clicked()
{
    unsigned char boardNum = ui->comboBoxBoardNum_3->currentIndex() + 1;
    if(boardNum == 1)
    {
        this->protocolHand->UpdateReadAddr = board1->readAddr;
        this->protocolHand->UpdateWriteAddr = board1->writerAddr;
    }
    else if(boardNum == 2)
    {
        this->protocolHand->UpdateReadAddr = board2->readAddr;
        this->protocolHand->UpdateWriteAddr = board2->writerAddr;
    }
    else if(boardNum == 3)
    {
        this->protocolHand->UpdateReadAddr = board3->readAddr;
        this->protocolHand->UpdateWriteAddr = board3->writerAddr;
    }
    else if(boardNum == 4)
    {
        this->protocolHand->UpdateReadAddr = board4->readAddr;
        this->protocolHand->UpdateWriteAddr = board4->writerAddr;
    }
    else if(boardNum == 5)
    {
        this->protocolHand->UpdateReadAddr = board5->readAddr;
        this->protocolHand->UpdateWriteAddr = board5->writerAddr;
    }
    else if(boardNum == 6)
    {
        this->protocolHand->UpdateReadAddr = board6->readAddr;
        this->protocolHand->UpdateWriteAddr = board6->writerAddr;
    }
    else if(boardNum == 7)
    {
        this->protocolHand->UpdateReadAddr = board7->readAddr;
        this->protocolHand->UpdateWriteAddr = board7->writerAddr;
    }
    else if(boardNum == 8)
    {
        this->protocolHand->UpdateReadAddr = board8->readAddr;
        this->protocolHand->UpdateWriteAddr = board8->writerAddr;
    }


    ui->progressBar->setValue(0);
    ui->labelUpdateMsg->clear();
    ui->FlashTimelabel->clear();
    QString file_name = QFileDialog::getOpenFileName(this,tr("./"),"",tr("bbt(*.bbt)"));

    if(file_name.isEmpty())
    {
        return;
    }
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open file false";
        return;
    }
    int ID = (PGN57344 << 8) + this->protocolHand->UpdateWriteAddr;  //擦除flash 命令
    this->protocolHand->flash_inited = false; //更新Flash init状态 防止多次擦除导致的错误
    unsigned int file_size = 0; //总文件长度
    unsigned int sent_size = 0; //总文件长度
    char str[128] = "";
    unsigned char send_str[8] = {0};
    int data_len = 0;
    file_size = file.size();
    qDebug()<<"file_size "<<file_size;
    memcpy(send_str, &file_size, sizeof (file_size));

    canthread->sendData(ID,(unsigned char*)send_str);

    this->ui->labelUpdateMsg->setText("Erasing flash...");
    this->protocolHand->flash_init_completed();  //等待MCU完成Flash擦除
    this->ui->labelUpdateMsg->setText("Flash erasure is complete");
    ID = (PGN60160 << 8) + this->protocolHand->UpdateWriteAddr;  //写code 命令
    this->ui->labelUpdateMsg->setText("Firmware programming...");
    FlashWriteTimer->start();
    FlashWriteTimeSec = 0;
    while (!file.atEnd())
    {
        memset(str, 0, sizeof (str));
        data_len = file.read(str,128);
        for(int i = 0; i < data_len ; i += 8)
        {
            for(int j = 0; j < 8 ;j++)
            {
               send_str[j] = str[j + i];
            }
            if( data_len - i < 8 )  // 不足8字节的部分  数据填充为 0
            {
                for(int k = data_len - i  ; k < 8 ; k++)
                {
                    send_str[k] = 0;
                }
            }
            canthread->sendData(ID,(unsigned char*)send_str);

            sent_size += 8;
            ui->progressBar->setValue((float)sent_size / file_size * 100);
            ui->FlashTimelabel->setText(QString::number(FlashWriteTimeSec / 60) + ":" + QString::number(FlashWriteTimeSec % 60));
        }
    }
    this->ui->labelUpdateMsg->setText("update completed");
    file.close();
}

void MainWindow::on_pushButtonTestWBoard1_clicked()
{
    qDebug()<<"写FPGA寄存器";
    unsigned char send_str[8] = {0};
    bool ok;
    int ID = (PGN57856 << 8) + this->board1->writerAddr;  //写FPGA命令
    quint64 regaddr = ui->lineEditTestAddrBoard1->text().toULongLong(&ok,16);
    quint64 regdata = ui->lineEditTestDataBoard1->text().toULongLong(&ok,16);
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }


}

void MainWindow::on_pushButtonTestRBoard1_clicked()
{
    qDebug()<<"读FPGA寄存器";
    int ID = (PGN58624 << 8) + this->board1->writerAddr;  //读FPGA命令
    unsigned char send_str[8] = {0};
    bool ok;
    quint64 data = ui->lineEditTestAddrBoard1->text().toULongLong(&ok,16);
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestWBoard2_clicked()
{
    qDebug()<<"写FPGA寄存器";
    unsigned char send_str[8] = {0};
    bool ok;
    int ID = (PGN57856 << 8) + this->board2->writerAddr;  //写FPGA命令
    quint64 regaddr = ui->lineEditTestAddrBoard2->text().toULongLong(&ok,16);
    quint64 regdata = ui->lineEditTestDataBoard2->text().toULongLong(&ok,16);
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestRBoard2_clicked()
{
    qDebug()<<"读FPGA寄存器";
    int ID = (PGN58624 << 8) + this->board2->writerAddr;  //读FPGA命令
    unsigned char send_str[8] = {0};
    bool ok;
    quint64 data = ui->lineEditTestAddrBoard2->text().toULongLong(&ok,16);
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestWBoard3_clicked()
{
    qDebug()<<"写FPGA寄存器";
    unsigned char send_str[8] = {0};
    bool ok;
    int ID = (PGN57856 << 8) + this->board3->writerAddr;  //写FPGA命令
    quint64 regaddr = ui->lineEditTestAddrBoard3->text().toULongLong(&ok,16);
    quint64 regdata = ui->lineEditTestDataBoard3->text().toULongLong(&ok,16);
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestRBoard3_clicked()
{
    qDebug()<<"读FPGA寄存器";
    int ID = (PGN58624 << 8) + this->board3->writerAddr;  //读FPGA命令
    unsigned char send_str[8] = {0};
    bool ok;
    quint64 data = ui->lineEditTestAddrBoard3->text().toULongLong(&ok,16);
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestWBoard4_clicked()
{
    qDebug()<<"写FPGA寄存器";
    unsigned char send_str[8] = {0};
    bool ok;
    int ID = (PGN57856 << 8) + this->board4->writerAddr;  //写FPGA命令
    quint64 regaddr = ui->lineEditTestAddrBoard4->text().toULongLong(&ok,16);
    quint64 regdata = ui->lineEditTestDataBoard4->text().toULongLong(&ok,16);
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestRBoard4_clicked()
{
    qDebug()<<"读FPGA寄存器";
    int ID = (PGN58624 << 8) + this->board4->writerAddr;  //读FPGA命令
    unsigned char send_str[8] = {0};
    bool ok;
    quint64 data = ui->lineEditTestAddrBoard4->text().toULongLong(&ok,16);
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestWBoard5_clicked()
{
    qDebug()<<"写FPGA寄存器";
    unsigned char send_str[8] = {0};
    bool ok;
    int ID = (PGN57856 << 8) + this->board5->writerAddr;  //写FPGA命令
    quint64 regaddr = ui->lineEditTestAddrBoard5->text().toULongLong(&ok,16);
    quint64 regdata = ui->lineEditTestDataBoard5->text().toULongLong(&ok,16);
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestRBoard5_clicked()
{
    qDebug()<<"读FPGA寄存器";
    int ID = (PGN58624 << 8) + this->board5->writerAddr;  //读FPGA命令
    unsigned char send_str[8] = {0};
    bool ok;
    quint64 data = ui->lineEditTestAddrBoard5->text().toULongLong(&ok,16);
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestWBoard6_clicked()
{
    qDebug()<<"写FPGA寄存器";
    unsigned char send_str[8] = {0};
    bool ok;
    int ID = (PGN57856 << 8) + this->board6->writerAddr;  //写FPGA命令
    quint64 regaddr = ui->lineEditTestAddrBoard6->text().toULongLong(&ok,16);
    quint64 regdata = ui->lineEditTestDataBoard6->text().toULongLong(&ok,16);
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestRBoard6_clicked()
{
    qDebug()<<"读FPGA寄存器";
    int ID = (PGN58624 << 8) + this->board6->writerAddr;  //读FPGA命令
    unsigned char send_str[8] = {0};
    bool ok;
    quint64 data = ui->lineEditTestAddrBoard6->text().toULongLong(&ok,16);
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestWBoard7_clicked()
{
    qDebug()<<"写FPGA寄存器";
    unsigned char send_str[8] = {0};
    bool ok;
    int ID = (PGN57856 << 8) + this->board7->writerAddr;  //写FPGA命令
    quint64 regaddr = ui->lineEditTestAddrBoard7->text().toULongLong(&ok,16);
    quint64 regdata = ui->lineEditTestDataBoard7->text().toULongLong(&ok,16);
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestRBoard7_clicked()
{
    qDebug()<<"读FPGA寄存器";
    int ID = (PGN58624 << 8) + this->board7->writerAddr;  //读FPGA命令
    unsigned char send_str[8] = {0};
    bool ok;
    quint64 data = ui->lineEditTestAddrBoard7->text().toULongLong(&ok,16);
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestWBoard8_clicked()
{
    qDebug()<<"写FPGA寄存器";
    unsigned char send_str[8] = {0};
    bool ok;
    int ID = (PGN57856 << 8) + this->board8->writerAddr;  //写FPGA命令
    quint64 regaddr = ui->lineEditTestAddrBoard8->text().toULongLong(&ok,16);
    quint64 regdata = ui->lineEditTestDataBoard8->text().toULongLong(&ok,16);
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButtonTestRBoard8_clicked()
{
    qDebug()<<"读FPGA寄存器";
    int ID = (PGN58624 << 8) + this->board8->writerAddr;  //读FPGA命令
    unsigned char send_str[8] = {0};
    bool ok;
    quint64 data = ui->lineEditTestAddrBoard8->text().toULongLong(&ok,16);
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
        qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);

    int row = 0;
    while(ui->tableWidgetTest->item(row,0) != 0)
    {
        row++;
        if(ui->tableWidgetTest->rowCount() < row + 1)
        {
            ui->tableWidgetTest->setRowCount(ui->tableWidgetTest->rowCount() + 1);
            ui->tableWidgetTest->scrollToBottom();
        }
    }

    ui->tableWidgetTest->setItem(row,0,new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss zzz")));  //系统时间
    ui->tableWidgetTest->setItem(row,1,new QTableWidgetItem("W"));
    ui->tableWidgetTest->setItem(row,2,new QTableWidgetItem(QString::number(ID,16)));
    ui->tableWidgetTest->item(row,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetTest->item(row,2)->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 8; i++)
    {
        ui->tableWidgetTest->setItem(row,3 + i,new QTableWidgetItem(QString::number(send_str[i],16)));
        ui->tableWidgetTest->item(row, 3 + i)->setTextAlignment(Qt::AlignCenter);
    }
}
