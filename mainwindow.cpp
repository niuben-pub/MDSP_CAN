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
    this->statusBar()->showMessage("CAN host is not started");
    QIntValidator* aIntValidator = new QIntValidator;
    aIntValidator->setRange(1, 8);
    ui->lineEditDevAddrBoard1->setValidator(aIntValidator);  //设置设备地址只能输入 0 - 8
    ui->lineEditDevAddrBoard2->setValidator(aIntValidator);  //设置设备地址只能输入 0 - 8
    ui->lineEditDevAddrBoard3->setValidator(aIntValidator);  //设置设备地址只能输入 0 - 8
    ui->lineEditDevAddrBoard4->setValidator(aIntValidator);  //设置设备地址只能输入 0 - 8
    ui->lineEditDevAddrBoard5->setValidator(aIntValidator);  //设置设备地址只能输入 0 - 8
    ui->lineEditDevAddrBoard6->setValidator(aIntValidator);  //设置设备地址只能输入 0 - 8
    ui->lineEditDevAddrBoard7->setValidator(aIntValidator);  //设置设备地址只能输入 0 - 8
    ui->lineEditDevAddrBoard8->setValidator(aIntValidator);  //设置设备地址只能输入 0 - 8


    ui->labelImgBoard1->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard2->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard3->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard4->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard5->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard6->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard7->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard8->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件

    ui->pushButtonTestRBoard1->setEnabled(false);  //关闭寄存器读按钮
    ui->pushButtonTestRBoard2->setEnabled(false);  //关闭寄存器读按钮
    ui->pushButtonTestRBoard3->setEnabled(false);  //关闭寄存器读按钮
    ui->pushButtonTestRBoard4->setEnabled(false);  //关闭寄存器读按钮
    ui->pushButtonTestRBoard5->setEnabled(false);  //关闭寄存器读按钮
    ui->pushButtonTestRBoard6->setEnabled(false);  //关闭寄存器读按钮
    ui->pushButtonTestRBoard7->setEnabled(false);  //关闭寄存器读按钮
    ui->pushButtonTestRBoard8->setEnabled(false);  //关闭寄存器读按钮

    ui->pushButtonTestWBoard1->setEnabled(false);   //关闭寄存器写按钮
    ui->pushButtonTestWBoard2->setEnabled(false);   //关闭寄存器写按钮
    ui->pushButtonTestWBoard3->setEnabled(false);   //关闭寄存器写按钮
    ui->pushButtonTestWBoard4->setEnabled(false);   //关闭寄存器写按钮
    ui->pushButtonTestWBoard5->setEnabled(false);   //关闭寄存器写按钮
    ui->pushButtonTestWBoard6->setEnabled(false);   //关闭寄存器写按钮
    ui->pushButtonTestWBoard7->setEnabled(false);   //关闭寄存器写按钮
    ui->pushButtonTestWBoard8->setEnabled(false);   //关闭寄存器写按钮

    ui->btnWorkControlLoad->setEnabled(false);//关闭加载按钮
    ui->btnWorkControlSave->setEnabled(false);//关闭保存按钮

    ui->btnUpdate_2->setEnabled(false);  //关闭升级按钮
    ui->btnUpdate_3->setEnabled(false);  //关闭升级按钮

    setLED(ui->labMCULEDBoard1, 2, 16);
    setLED(ui->labMCULEDBoard2, 2, 16);
    setLED(ui->labMCULEDBoard3, 2, 16);
    setLED(ui->labMCULEDBoard4, 2, 16);
    setLED(ui->labMCULEDBoard5, 2, 16);
    setLED(ui->labMCULEDBoard6, 2, 16);
    setLED(ui->labMCULEDBoard7, 2, 16);
    setLED(ui->labMCULEDBoard8, 2, 16);

    setLED(ui->labFPGALEDBoard1, 2, 16);
    setLED(ui->labFPGALEDBoard2, 2, 16);
    setLED(ui->labFPGALEDBoard3, 2, 16);
    setLED(ui->labFPGALEDBoard4, 2, 16);
    setLED(ui->labFPGALEDBoard5, 2, 16);
    setLED(ui->labFPGALEDBoard6, 2, 16);
    setLED(ui->labFPGALEDBoard7, 2, 16);
    setLED(ui->labFPGALEDBoard8, 2, 16);


    setLED(ui->labDSPLEDBoard1, 2, 16);
    setLED(ui->labDSPLEDBoard2, 2, 16);
    setLED(ui->labDSPLEDBoard3, 2, 16);
    setLED(ui->labDSPLEDBoard4, 2, 16);
    setLED(ui->labDSPLEDBoard5, 2, 16);
    setLED(ui->labDSPLEDBoard6, 2, 16);
    setLED(ui->labDSPLEDBoard7, 2, 16);
    setLED(ui->labDSPLEDBoard8, 2, 16);


//    ui->tabWidget->setTabEnabled(1,false);
//    ui->tabWidget->setTabEnabled(2,false);
//    ui->tabWidget->setTabEnabled(3,false);
//    ui->tabWidget->setTabEnabled(4,false);


    ui->tableWidgetTest->setColumnWidth(0,90);
    ui->tableWidgetTest->setColumnWidth(1,60);
    ui->tableWidgetTest->setColumnWidth(2,76);
    ui->tableWidgetTest->setHorizontalHeaderItem(0,new QTableWidgetItem("SYS time"));
    ui->tableWidgetTest->setHorizontalHeaderItem(1,new QTableWidgetItem("DIR"));
    ui->tableWidgetTest->setHorizontalHeaderItem(2,new QTableWidgetItem("ID(hex)"));

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

void MainWindow::initImaLabel()
{
    ui->labelImgBoard1->pixBlank.load(":/images/0.png");
    ui->labelImgBoard1->pix3GIN1.load(":/images/1.png");
    ui->labelImgBoard1->pix3GIN2.load(":/images/2.png");
    ui->labelImgBoard1->pixDetection.load(":/images/a1.png");
    ui->labelImgBoard1->pixColor.load(":/images/col1.png");
    ui->labelImgBoard2->pixBlank.load(":/images/0.png");
    ui->labelImgBoard2->pix3GIN1.load(":/images/3.png");
    ui->labelImgBoard2->pix3GIN2.load(":/images/4.png");
    ui->labelImgBoard2->pixDetection.load(":/images/a2.png");
    ui->labelImgBoard2->pixColor.load(":/images/col2.png");
    ui->labelImgBoard3->pixBlank.load(":/images/0.png");
    ui->labelImgBoard3->pix3GIN1.load(":/images/5.png");
    ui->labelImgBoard3->pix3GIN2.load(":/images/6.png");
    ui->labelImgBoard3->pixDetection.load(":/images/a3.png");
    ui->labelImgBoard3->pixColor.load(":/images/col3.png");
    ui->labelImgBoard4->pixBlank.load(":/images/0.png");
    ui->labelImgBoard4->pix3GIN1.load(":/images/7.png");
    ui->labelImgBoard4->pix3GIN2.load(":/images/8.png");
    ui->labelImgBoard4->pixDetection.load(":/images/a4.png");
    ui->labelImgBoard4->pixColor.load(":/images/col4.png");
    ui->labelImgBoard5->pixBlank.load(":/images/0.png");
    ui->labelImgBoard5->pix3GIN1.load(":/images/9.png");
    ui->labelImgBoard5->pix3GIN2.load(":/images/10.png");
    ui->labelImgBoard5->pixDetection.load(":/images/a5.png");
    ui->labelImgBoard5->pixColor.load(":/images/col5.png");
    ui->labelImgBoard6->pixBlank.load(":/images/0.png");
    ui->labelImgBoard6->pix3GIN1.load(":/images/11.png");
    ui->labelImgBoard6->pix3GIN2.load(":/images/12.png");
    ui->labelImgBoard6->pixDetection.load(":/images/a6.png");
    ui->labelImgBoard6->pixColor.load(":/images/col6.png");
    ui->labelImgBoard7->pixBlank.load(":/images/0.png");
    ui->labelImgBoard7->pix3GIN1.load(":/images/13.png");
    ui->labelImgBoard7->pix3GIN2.load(":/images/14.png");
    ui->labelImgBoard7->pixDetection.load(":/images/a7.png");
    ui->labelImgBoard7->pixColor.load(":/images/col7.png");
    ui->labelImgBoard8->pixBlank.load(":/images/0.png");
    ui->labelImgBoard8->pix3GIN1.load(":/images/15.png");
    ui->labelImgBoard8->pix3GIN2.load(":/images/16.png");
    ui->labelImgBoard8->pixDetection.load(":/images/a8.png");
    ui->labelImgBoard8->pixColor.load(":/images/col8.png");

    ui->labelOverly->pixBlank.load(":/images/0.png");

    ui->labelOverly->pix3GIN1Board[0].load(":/images/1.png");
    ui->labelOverly->pix3GIN2Board[0].load(":/images/2.png");
    ui->labelOverly->pixDetectionBoard[0].load(":/images/a1.png");
    ui->labelOverly->pixColorBoard[0].load(":/images/col1.png");

    ui->labelOverly->pix3GIN1Board[1].load(":/images/3.png");
    ui->labelOverly->pix3GIN2Board[1].load(":/images/4.png");
    ui->labelOverly->pixDetectionBoard[1].load(":/images/a2.png");
    ui->labelOverly->pixColorBoard[1].load(":/images/col2.png");

    ui->labelOverly->pix3GIN1Board[2].load(":/images/5.png");
    ui->labelOverly->pix3GIN2Board[2].load(":/images/6.png");
    ui->labelOverly->pixDetectionBoard[2].load(":/images/a3.png");
    ui->labelOverly->pixColorBoard[2].load(":/images/col3.png");
;
    ui->labelOverly->pix3GIN1Board[3].load(":/images/7.png");
    ui->labelOverly->pix3GIN2Board[3].load(":/images/8.png");
    ui->labelOverly->pixDetectionBoard[3].load(":/images/a4.png");
    ui->labelOverly->pixColorBoard[3].load(":/images/col4.png");

    ui->labelOverly->pix3GIN1Board[4].load(":/images/9.png");
    ui->labelOverly->pix3GIN2Board[4].load(":/images/10.png");
    ui->labelOverly->pixDetectionBoard[4].load(":/images/a5.png");
    ui->labelOverly->pixColorBoard4.load(":/images/col5.png");

    ui->labelOverly->pix3GIN1Board[5].load(":/images/11.png");
    ui->labelOverly->pix3GIN2Board[5].load(":/images/12.png");
    ui->labelOverly->pixDetectionBoard[5].load(":/images/a6.png");
    ui->labelOverly->pixColorBoard[5].load(":/images/col6.png");

    ui->labelOverly->pix3GIN1Board[6].load(":/images/13.png");
    ui->labelOverly->pix3GIN2Board[6].load(":/images/14.png");
    ui->labelOverly->pixDetectionBoard[6].load(":/images/a7.png");
    ui->labelOverly->pixColorBoard[6].load(":/images/col7.png");

    ui->labelOverly->pix3GIN1Board[7].load(":/images/15.png");
    ui->labelOverly->pix3GIN2Board[7].load(":/images/16.png");
    ui->labelOverly->pixDetectionBoard[7].load(":/images/a8.png");
    ui->labelOverly->pixColorBoard[7].load(":/images/col8.png");

}

void MainWindow::initSignalslots()
{
    //接收到canthread线程接收到的数据 并显示
    connect(canthread,&CANThread::getProtocolData,this,&MainWindow::displayMonitor);
    //接收到canthread线程接收到的数据 传递到数据处理线程
    connect(canthread,&CANThread::getProtocolData,protocolHand,&ProtocolThrend::protocolHand);
    //Flash写入计时
    connect(FlashWriteTimer,SIGNAL(timeout()),this,SLOT(updataFlashTime()));

    connect(ui->labelImgBoard1,SIGNAL(regChange(unsigned int *)),this,SLOT(writeBoard1FpgaImgconfigReg(unsigned int *)));
    connect(ui->labelImgBoard2,SIGNAL(regChange(unsigned int *)),this,SLOT(writeBoard2FpgaImgconfigReg(unsigned int *)));
    connect(ui->labelImgBoard3,SIGNAL(regChange(unsigned int *)),this,SLOT(writeBoard3FpgaImgconfigReg(unsigned int *)));
    connect(ui->labelImgBoard4,SIGNAL(regChange(unsigned int *)),this,SLOT(writeBoard4FpgaImgconfigReg(unsigned int *)));
    connect(ui->labelImgBoard5,SIGNAL(regChange(unsigned int *)),this,SLOT(writeBoard5FpgaImgconfigReg(unsigned int *)));
    connect(ui->labelImgBoard6,SIGNAL(regChange(unsigned int *)),this,SLOT(writeBoard6FpgaImgconfigReg(unsigned int *)));
    connect(ui->labelImgBoard7,SIGNAL(regChange(unsigned int *)),this,SLOT(writeBoard7FpgaImgconfigReg(unsigned int *)));
    connect(ui->labelImgBoard8,SIGNAL(regChange(unsigned int *)),this,SLOT(writeBoard8FpgaImgconfigReg(unsigned int *)));

    connect(ui->labelImgBoard1,SIGNAL(imgoverlayupdataImg()),this,SLOT(updateOverlyImgRegArray()));
    connect(ui->labelImgBoard2,SIGNAL(imgoverlayupdataImg()),this,SLOT(updateOverlyImgRegArray()));
    connect(ui->labelImgBoard3,SIGNAL(imgoverlayupdataImg()),this,SLOT(updateOverlyImgRegArray()));
    connect(ui->labelImgBoard4,SIGNAL(imgoverlayupdataImg()),this,SLOT(updateOverlyImgRegArray()));
    connect(ui->labelImgBoard5,SIGNAL(imgoverlayupdataImg()),this,SLOT(updateOverlyImgRegArray()));
    connect(ui->labelImgBoard6,SIGNAL(imgoverlayupdataImg()),this,SLOT(updateOverlyImgRegArray()));
    connect(ui->labelImgBoard7,SIGNAL(imgoverlayupdataImg()),this,SLOT(updateOverlyImgRegArray()));
    connect(ui->labelImgBoard8,SIGNAL(imgoverlayupdataImg()),this,SLOT(updateOverlyImgRegArray()));
}

void MainWindow::setLED(QLabel *label, int color, int size)
{
    // 将label中的文字清空
    label->setText("");
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    case 3:
        // 黄色
        background += "rgb(255,255,0)";
        break;
    default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initImaLabel();
   // ui->labelOverly->regTableBoard1 = (const unsigned int **)ui->labelImgBoard1->regTable;
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
    this->board1->writerAddr = 1;
    this->board1->readAddr = this->board1->writerAddr << 4;
    this->board2->writerAddr = 2;
    this->board2->readAddr = this->board2->writerAddr << 4;
    this->board3->writerAddr = 3;
    this->board3->readAddr = this->board3->writerAddr << 4;
    this->board4->writerAddr = 4;
    this->board4->readAddr = this->board4->writerAddr << 4;
    this->board5->writerAddr = 5;
    this->board5->readAddr = this->board5->writerAddr << 4;
    this->board6->writerAddr = 6;
    this->board6->readAddr = this->board6->writerAddr << 4;
    this->board7->writerAddr = 7;
    this->board7->readAddr = this->board7->writerAddr << 4;
    this->board8->writerAddr = 8;
    this->board8->readAddr = this->board8->writerAddr << 4;

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

void MainWindow::updateOverlyImgRegArray()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ui->labelOverly->regTableBoard[0][i][j] = ui->labelImgBoard1->regTable[i][j];
            ui->labelOverly->regTableBoard[1][i][j] = ui->labelImgBoard2->regTable[i][j];
            ui->labelOverly->regTableBoard[2][i][j] = ui->labelImgBoard3->regTable[i][j];
            ui->labelOverly->regTableBoard[3][i][j] = ui->labelImgBoard4->regTable[i][j];
            ui->labelOverly->regTableBoard[4][i][j] = ui->labelImgBoard5->regTable[i][j];
            ui->labelOverly->regTableBoard[5][i][j] = ui->labelImgBoard6->regTable[i][j];
            ui->labelOverly->regTableBoard[6][i][j] = ui->labelImgBoard7->regTable[i][j];
            ui->labelOverly->regTableBoard[7][i][j] = ui->labelImgBoard8->regTable[i][j];
        }
    }

    ui->labelOverly->displayModeRegBoard[0] = ui->labelImgBoard1->displayModeReg;
    ui->labelOverly->displayModeRegBoard[1] = ui->labelImgBoard2->displayModeReg;
    ui->labelOverly->displayModeRegBoard[2] = ui->labelImgBoard3->displayModeReg;
    ui->labelOverly->displayModeRegBoard[3] = ui->labelImgBoard4->displayModeReg;
    ui->labelOverly->displayModeRegBoard[4] = ui->labelImgBoard5->displayModeReg;
    ui->labelOverly->displayModeRegBoard[5] = ui->labelImgBoard6->displayModeReg;
    ui->labelOverly->displayModeRegBoard[6] = ui->labelImgBoard7->displayModeReg;
    ui->labelOverly->displayModeRegBoard[7] = ui->labelImgBoard8->displayModeReg;


    ui->labelOverly->update();

}

void MainWindow::writeBoard1FpgaImgconfigReg(unsigned int *regTable)
{
    int ID = (PGN57856 << 8) + this->board1->writerAddr;  //写FPGA命令


    //先发送显示格式  显示16画  或者IN1 4K 或者IN2 4K
    unsigned char send_str[8] = {0};
    quint64 regaddr = ui->labelImgBoard1->displayModeRegAddr;
    quint64 regdata = ui->labelImgBoard1->displayModeReg;
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int k = 0; k < 8; k++)
    {
        send_str[k] = p[7 - k];
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);



    //再发送输入分辨率
    regaddr = ui->labelImgBoard1->img3GIn1SizeRegAddr;
    regdata = ui->labelImgBoard1->img3GIn1SizeReg;
    data = (regaddr<<16) + regdata;
    p = (char *)(&data);
    for(int k = 0; k < 8; k++)
    {
        send_str[k] = p[7 - k];
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);


    //再发送输入分辨率
    regaddr = ui->labelImgBoard1->img3GIn2SizeRegAddr;
    regdata = ui->labelImgBoard1->img3GIn2SizeReg;
    data = (regaddr<<16) + regdata;
    p = (char *)(&data);
    for(int k = 0; k < 8; k++)
    {
        send_str[k] = p[7 - k];
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);



    //再发送输入显示分辨率
    for (int i = 0; i < 16; i++)
    {
        //qDebug()<<"["<<regTable[i]<<"]"<<endl;
        regaddr = 0x10 + i;
        regdata = regTable[i];
        data = (regaddr<<16) + regdata;
        p = (char *)(&data);
        for(int j = 0; j < 8; j++)
        {
            send_str[j] = p[7 - j];
            //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
        }
        canthread->sendData(ID,(unsigned char*)send_str);
        sleep(10);
    }
}

void MainWindow::writeBoard2FpgaImgconfigReg(unsigned int *regTable)
{

    for (int i = 0; i < 16; i++)
    {
        //qDebug()<<"["<<regTable[i]<<"]"<<endl;
        unsigned char send_str[8] = {0};
        int ID = (PGN57856 << 8) + this->board2->writerAddr;  //写FPGA命令
        quint64 regaddr = 0x10 + i;
        quint64 regdata = regTable[i];
        quint64 data = (regaddr<<16) + regdata;
        char *p = (char *)(&data);
        for(int i = 0; i < 8; i++)
        {
            send_str[i] = p[7 - i];
            //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
        }
        canthread->sendData(ID,(unsigned char*)send_str);
        sleep(10);
    }
}

void MainWindow::writeBoard3FpgaImgconfigReg(unsigned int *regTable)
{

    for (int i = 0; i < 16; i++)
    {
        //qDebug()<<"["<<regTable[i]<<"]"<<endl;
        unsigned char send_str[8] = {0};
        int ID = (PGN57856 << 8) + this->board3->writerAddr;  //写FPGA命令
        quint64 regaddr = 0x10 + i;
        quint64 regdata = regTable[i];
        quint64 data = (regaddr<<16) + regdata;
        char *p = (char *)(&data);
        for(int i = 0; i < 8; i++)
        {
            send_str[i] = p[7 - i];
            //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
        }
        canthread->sendData(ID,(unsigned char*)send_str);
        sleep(10);
    }
}


void MainWindow::writeBoard4FpgaImgconfigReg(unsigned int *regTable)
{

    for (int i = 0; i < 16; i++)
    {
        //qDebug()<<"["<<regTable[i]<<"]"<<endl;
        unsigned char send_str[8] = {0};
        int ID = (PGN57856 << 8) + this->board4->writerAddr;  //写FPGA命令
        quint64 regaddr = 0x10 + i;
        quint64 regdata = regTable[i];
        quint64 data = (regaddr<<16) + regdata;
        char *p = (char *)(&data);
        for(int i = 0; i < 8; i++)
        {
            send_str[i] = p[7 - i];
            //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
        }
        canthread->sendData(ID,(unsigned char*)send_str);
        sleep(10);
    }
}


void MainWindow::writeBoard5FpgaImgconfigReg(unsigned int *regTable)
{

    for (int i = 0; i < 16; i++)
    {
        //qDebug()<<"["<<regTable[i]<<"]"<<endl;
        unsigned char send_str[8] = {0};
        int ID = (PGN57856 << 8) + this->board5->writerAddr;  //写FPGA命令
        quint64 regaddr = 0x10 + i;
        quint64 regdata = regTable[i];
        quint64 data = (regaddr<<16) + regdata;
        char *p = (char *)(&data);
        for(int i = 0; i < 8; i++)
        {
            send_str[i] = p[7 - i];
            //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
        }
        canthread->sendData(ID,(unsigned char*)send_str);
        sleep(10);
    }
}

void MainWindow::writeBoard6FpgaImgconfigReg(unsigned int *regTable)
{

    for (int i = 0; i < 16; i++)
    {
        //qDebug()<<"["<<regTable[i]<<"]"<<endl;
        unsigned char send_str[8] = {0};
        int ID = (PGN57856 << 8) + this->board6->writerAddr;  //写FPGA命令
        quint64 regaddr = 0x10 + i;
        quint64 regdata = regTable[i];
        quint64 data = (regaddr<<16) + regdata;
        char *p = (char *)(&data);
        for(int i = 0; i < 8; i++)
        {
            send_str[i] = p[7 - i];
            //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
        }
        canthread->sendData(ID,(unsigned char*)send_str);
        sleep(10);
    }
}

void MainWindow::writeBoard7FpgaImgconfigReg(unsigned int *regTable)
{

    for (int i = 0; i < 16; i++)
    {
        //qDebug()<<"["<<regTable[i]<<"]"<<endl;
        unsigned char send_str[8] = {0};
        int ID = (PGN57856 << 8) + this->board7->writerAddr;  //写FPGA命令
        quint64 regaddr = 0x10 + i;
        quint64 regdata = regTable[i];
        quint64 data = (regaddr<<16) + regdata;
        char *p = (char *)(&data);
        for(int i = 0; i < 8; i++)
        {
            send_str[i] = p[7 - i];
            //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
        }
        canthread->sendData(ID,(unsigned char*)send_str);
        sleep(10);
    }
}

void MainWindow::writeBoard8FpgaImgconfigReg(unsigned int *regTable)
{

    for (int i = 0; i < 16; i++)
    {
        //qDebug()<<"["<<regTable[i]<<"]"<<endl;
        unsigned char send_str[8] = {0};
        int ID = (PGN57856 << 8) + this->board8->writerAddr;  //写FPGA命令
        quint64 regaddr = 0x10 + i;
        quint64 regdata = regTable[i];
        quint64 data = (regaddr<<16) + regdata;
        char *p = (char *)(&data);
        for(int i = 0; i < 8; i++)
        {
            send_str[i] = p[7 - i];
            //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
        }
        canthread->sendData(ID,(unsigned char*)send_str);
        sleep(10);
    }
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
       // this->sleep(3500); //等待设备启动完成
        if(dev == true)
        {
            canthread->start();
            protocolHand->start();
            this->statusBar()->showMessage("CAN host startup succeeded");

//            ui->tabWidget->setTabEnabled(1,true);
//            ui->tabWidget->setTabEnabled(2,true);
//            ui->tabWidget->setTabEnabled(3,true);
//            ui->tabWidget->setTabEnabled(4,true);
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
//        ui->tabWidget->setTabEnabled(1,false);
//        ui->tabWidget->setTabEnabled(2,false);
//        ui->tabWidget->setTabEnabled(3,false);
//        ui->tabWidget->setTabEnabled(4,false);
        ui->btnFinish->setText(tr("Open"));
        canthread->stop();
        canthread->closeCAN();
    }
}



void MainWindow::on_btnStatusBoard1_clicked()
{
    if(ui->btnStatusBoard1->text() == tr("Open"))
    {
        ui->btnStatusBoard1->setText(tr("Close"));

        //this->canthread->Adc_flag = true;
        this->canthread->canThreadTimer->start();
        this->statusBar()->showMessage("Mode: Status - Realtime | Monitor: Open");

    }
    else if(ui->btnStatusBoard1->text() == tr("Close"))
    {
        ui->btnStatusBoard1->setText(tr("Open"));
        qDebug()<<"canThreadTimer Close";
        //this->canthread->Adc_flag = false;
        this->canthread->canThreadTimer->stop();
        this->statusBar()->showMessage("Mode: Status - Realtime | Monitor: Colse");
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



void MainWindow::on_btnWorkTestMode_clicked()
{

    if(ui->btnStatusBoard1->text() == tr("Close"))  //关闭监控
    {
        ui->btnStatusBoard1->setText(tr("Open"));
        //this->canthread->Adc_flag = false;
        this->canthread->canThreadTimer->stop();
    }

    ui->btnStatusBoard1->setEnabled(false); //关闭该按钮


    ui->pushButtonTestRBoard1->setEnabled(true);
    ui->pushButtonTestRBoard2->setEnabled(true);
    ui->pushButtonTestRBoard3->setEnabled(true);
    ui->pushButtonTestRBoard4->setEnabled(true);
    ui->pushButtonTestRBoard5->setEnabled(true);
    ui->pushButtonTestRBoard6->setEnabled(true);
    ui->pushButtonTestRBoard7->setEnabled(true);
    ui->pushButtonTestRBoard8->setEnabled(true);

    ui->pushButtonTestWBoard1->setEnabled(true);
    ui->pushButtonTestWBoard2->setEnabled(true);
    ui->pushButtonTestWBoard3->setEnabled(true);
    ui->pushButtonTestWBoard4->setEnabled(true);
    ui->pushButtonTestWBoard5->setEnabled(true);
    ui->pushButtonTestWBoard6->setEnabled(true);
    ui->pushButtonTestWBoard7->setEnabled(true);
    ui->pushButtonTestWBoard8->setEnabled(true);

    ui->labelImgBoard1->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard2->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard3->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard4->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard5->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard6->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard7->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard8->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件

    ui->btnUpdate_2->setEnabled(false);  //关闭升级按钮
    ui->btnUpdate_3->setEnabled(false);  //关闭升级按钮

    ui->btnWorkControlLoad->setEnabled(false);//关闭加载按钮
    ui->btnWorkControlSave->setEnabled(false);//关闭保存按钮

    this->statusBar()->showMessage("Mode : Work - Test");

}


void MainWindow::on_btnWorkControlMode_clicked()
{

    if(ui->btnStatusBoard1->text() == tr("Close"))  //关闭监控
    {
        ui->btnStatusBoard1->setText(tr("Open"));
        //this->canthread->Adc_flag = false;
        this->canthread->canThreadTimer->stop();
    }

    ui->btnStatusBoard1->setEnabled(false); //关闭开启监控该按钮

    ui->pushButtonTestRBoard1->setEnabled(false);
    ui->pushButtonTestRBoard2->setEnabled(false);
    ui->pushButtonTestRBoard3->setEnabled(false);
    ui->pushButtonTestRBoard4->setEnabled(false);
    ui->pushButtonTestRBoard5->setEnabled(false);
    ui->pushButtonTestRBoard6->setEnabled(false);
    ui->pushButtonTestRBoard7->setEnabled(false);
    ui->pushButtonTestRBoard8->setEnabled(false);

    ui->pushButtonTestWBoard1->setEnabled(false);
    ui->pushButtonTestWBoard2->setEnabled(false);
    ui->pushButtonTestWBoard3->setEnabled(false);
    ui->pushButtonTestWBoard4->setEnabled(false);
    ui->pushButtonTestWBoard5->setEnabled(false);
    ui->pushButtonTestWBoard6->setEnabled(false);
    ui->pushButtonTestWBoard7->setEnabled(false);
    ui->pushButtonTestWBoard8->setEnabled(false);

    ui->btnUpdate_2->setEnabled(false);  //关闭升级按钮
    ui->btnUpdate_3->setEnabled(false);  //关闭升级按钮

    ui->labelImgBoard1->setAttribute(Qt::WA_TransparentForMouseEvents, false); //取消屏蔽鼠标点击事件
    ui->labelImgBoard2->setAttribute(Qt::WA_TransparentForMouseEvents, false); //取消屏蔽鼠标点击事件
    ui->labelImgBoard3->setAttribute(Qt::WA_TransparentForMouseEvents, false); //取消屏蔽鼠标点击事件
    ui->labelImgBoard4->setAttribute(Qt::WA_TransparentForMouseEvents, false); //取消屏蔽鼠标点击事件
    ui->labelImgBoard5->setAttribute(Qt::WA_TransparentForMouseEvents, false); //取消屏蔽鼠标点击事件
    ui->labelImgBoard6->setAttribute(Qt::WA_TransparentForMouseEvents, false); //取消屏蔽鼠标点击事件
    ui->labelImgBoard7->setAttribute(Qt::WA_TransparentForMouseEvents, false); //取消屏蔽鼠标点击事件
    ui->labelImgBoard8->setAttribute(Qt::WA_TransparentForMouseEvents, false); //取消屏蔽鼠标点击事件

    ui->btnWorkControlLoad->setEnabled(true);//打开加载按钮
    ui->btnWorkControlSave->setEnabled(true);//打开保存按钮



    this->statusBar()->showMessage("Mode : Work - Control");

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


    ui->pushButtonTestRBoard1->setEnabled(false);
    ui->pushButtonTestRBoard2->setEnabled(false);
    ui->pushButtonTestRBoard3->setEnabled(false);
    ui->pushButtonTestRBoard4->setEnabled(false);
    ui->pushButtonTestRBoard5->setEnabled(false);
    ui->pushButtonTestRBoard6->setEnabled(false);
    ui->pushButtonTestRBoard7->setEnabled(false);
    ui->pushButtonTestRBoard8->setEnabled(false);

    ui->pushButtonTestWBoard1->setEnabled(false);
    ui->pushButtonTestWBoard2->setEnabled(false);
    ui->pushButtonTestWBoard3->setEnabled(false);
    ui->pushButtonTestWBoard4->setEnabled(false);
    ui->pushButtonTestWBoard5->setEnabled(false);
    ui->pushButtonTestWBoard6->setEnabled(false);
    ui->pushButtonTestWBoard7->setEnabled(false);
    ui->pushButtonTestWBoard8->setEnabled(false);

    ui->labelImgBoard1->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard2->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard3->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard4->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard5->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard6->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard7->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard8->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件

    ui->btnWorkControlLoad->setEnabled(false);//关闭加载按钮
    ui->btnWorkControlSave->setEnabled(false);//关闭保存按钮

    ui->btnUpdate_2->setEnabled(true);  //使能升级按钮
    ui->btnUpdate_3->setEnabled(false);  //关闭升级按钮

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
    this->statusBar()->showMessage("Mode: Upgrade - AI File");

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


    ui->pushButtonTestRBoard1->setEnabled(false);
    ui->pushButtonTestRBoard2->setEnabled(false);
    ui->pushButtonTestRBoard3->setEnabled(false);
    ui->pushButtonTestRBoard4->setEnabled(false);
    ui->pushButtonTestRBoard5->setEnabled(false);
    ui->pushButtonTestRBoard6->setEnabled(false);
    ui->pushButtonTestRBoard7->setEnabled(false);
    ui->pushButtonTestRBoard8->setEnabled(false);

    ui->pushButtonTestWBoard1->setEnabled(false);
    ui->pushButtonTestWBoard2->setEnabled(false);
    ui->pushButtonTestWBoard3->setEnabled(false);
    ui->pushButtonTestWBoard4->setEnabled(false);
    ui->pushButtonTestWBoard5->setEnabled(false);
    ui->pushButtonTestWBoard6->setEnabled(false);
    ui->pushButtonTestWBoard7->setEnabled(false);
    ui->pushButtonTestWBoard8->setEnabled(false);

    ui->labelImgBoard1->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard2->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard3->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard4->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard5->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard6->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard7->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard8->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件


    ui->btnUpdate_2->setEnabled(false);  //关闭升级按钮
    ui->btnUpdate_3->setEnabled(false);  //关闭升级按钮

    ui->btnWorkControlLoad->setEnabled(false);//关闭加载按钮
    ui->btnWorkControlSave->setEnabled(false);//关闭保存按钮

    this->statusBar()->showMessage("Mode: Status - Realtime | Monitor: Colse");
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

    ui->pushButtonTestRBoard1->setEnabled(false);
    ui->pushButtonTestRBoard2->setEnabled(false);
    ui->pushButtonTestRBoard3->setEnabled(false);
    ui->pushButtonTestRBoard4->setEnabled(false);
    ui->pushButtonTestRBoard5->setEnabled(false);
    ui->pushButtonTestRBoard6->setEnabled(false);
    ui->pushButtonTestRBoard7->setEnabled(false);
    ui->pushButtonTestRBoard8->setEnabled(false);

    ui->pushButtonTestWBoard1->setEnabled(false);
    ui->pushButtonTestWBoard2->setEnabled(false);
    ui->pushButtonTestWBoard3->setEnabled(false);
    ui->pushButtonTestWBoard4->setEnabled(false);
    ui->pushButtonTestWBoard5->setEnabled(false);
    ui->pushButtonTestWBoard6->setEnabled(false);
    ui->pushButtonTestWBoard7->setEnabled(false);
    ui->pushButtonTestWBoard8->setEnabled(false);


    ui->labelImgBoard1->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard2->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard3->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard4->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard5->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard6->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard7->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件
    ui->labelImgBoard8->setAttribute(Qt::WA_TransparentForMouseEvents, true); //屏蔽鼠标点击事件

    ui->btnWorkControlLoad->setEnabled(false);//关闭加载按钮
    ui->btnWorkControlSave->setEnabled(false);//关闭保存按钮

    ui->btnUpdate_2->setEnabled(false);  //关闭升级按钮
    ui->btnUpdate_3->setEnabled(true);  //使能升级按钮

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
    this->statusBar()->showMessage("Mode: Upgrade - Firmware");
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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
        //qDebug("send_str[%d] = 0x%02x",i,send_str[i]);
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

void MainWindow::on_pushButtonAddrClear_clicked()
{
    ui->lineEditDevAddrBoard1->clear();
    ui->lineEditDevAddrBoard2->clear();
    ui->lineEditDevAddrBoard3->clear();
    ui->lineEditDevAddrBoard4->clear();
    ui->lineEditDevAddrBoard5->clear();
    ui->lineEditDevAddrBoard6->clear();
    ui->lineEditDevAddrBoard7->clear();
    ui->lineEditDevAddrBoard8->clear();
}

void MainWindow::on_pushButtonAddrOk_clicked()
{
    bool ok;
    if(ui->lineEditDevAddrBoard1->text() != "")
    {
        this->board1->writerAddr = ui->lineEditDevAddrBoard1->text().toULongLong(&ok,10);
        this->board1->readAddr = this->board1->writerAddr << 4;
    }
    if(ui->lineEditDevAddrBoard2->text() != "")
    {
        this->board2->writerAddr = ui->lineEditDevAddrBoard2->text().toULongLong(&ok,10);
        this->board2->readAddr = this->board2->writerAddr << 4;
    }

    if(ui->lineEditDevAddrBoard3->text() != "")
    {
        this->board3->writerAddr = ui->lineEditDevAddrBoard3->text().toULongLong(&ok,10);
        this->board3->readAddr = this->board3->writerAddr << 4;
    }
    if(ui->lineEditDevAddrBoard4->text() != "")
    {
        this->board4->writerAddr = ui->lineEditDevAddrBoard4->text().toULongLong(&ok,10);
        this->board4->readAddr = this->board4->writerAddr << 4;
    }
    if(ui->lineEditDevAddrBoard5->text() != "")
    {
        this->board5->writerAddr = ui->lineEditDevAddrBoard5->text().toULongLong(&ok,10);
        this->board5->readAddr = this->board5->writerAddr << 4;
    }
    if(ui->lineEditDevAddrBoard6->text() != "")
    {
        this->board6->writerAddr = ui->lineEditDevAddrBoard6->text().toULongLong(&ok,10);
        this->board6->readAddr = this->board6->writerAddr << 4;
    }
    if(ui->lineEditDevAddrBoard7->text() != "")
    {
        this->board7->writerAddr = ui->lineEditDevAddrBoard7->text().toULongLong(&ok,10);
        this->board7->readAddr = this->board7->writerAddr << 4;
    }
    if(ui->lineEditDevAddrBoard8->text() != "")
    {
        this->board8->writerAddr = ui->lineEditDevAddrBoard8->text().toULongLong(&ok,10);
        this->board8->readAddr = this->board8->writerAddr << 4;
    }
    ui->groupBox->setTitle(  "Board1  addr : " + QString::number(this->board1->writerAddr,10));
    ui->groupBox_2->setTitle("Board2  addr : " + QString::number(this->board2->writerAddr,10));
    ui->groupBox_3->setTitle("Board3  addr : " + QString::number(this->board3->writerAddr,10));
    ui->groupBox_4->setTitle("Board4  addr : " + QString::number(this->board4->writerAddr,10));
    ui->groupBox_5->setTitle("Board5  addr : " + QString::number(this->board5->writerAddr,10));
    ui->groupBox_6->setTitle("Board6  addr : " + QString::number(this->board6->writerAddr,10));
    ui->groupBox_7->setTitle("Board7  addr : " + QString::number(this->board7->writerAddr,10));
    ui->groupBox_8->setTitle("Board8  addr : " + QString::number(this->board8->writerAddr,10));

    ui->groupBox_11->setTitle("Board1  addr : " + QString::number(this->board1->writerAddr,10));
    ui->groupBox_12->setTitle("Board2  addr : " + QString::number(this->board2->writerAddr,10));
    ui->groupBox_13->setTitle("Board3  addr : " + QString::number(this->board3->writerAddr,10));
    ui->groupBox_14->setTitle("Board4  addr : " + QString::number(this->board4->writerAddr,10));
    ui->groupBox_15->setTitle("Board5  addr : " + QString::number(this->board5->writerAddr,10));
    ui->groupBox_16->setTitle("Board6  addr : " + QString::number(this->board6->writerAddr,10));
    ui->groupBox_17->setTitle("Board7  addr : " + QString::number(this->board7->writerAddr,10));
    ui->groupBox_18->setTitle("Board8  addr : " + QString::number(this->board8->writerAddr,10));

    ui->groupBoxImgBorad1->setTitle("Board1  addr : " + QString::number(this->board1->writerAddr,10));
    ui->groupBoxImgBorad2->setTitle("Board2  addr : " + QString::number(this->board2->writerAddr,10));
    ui->groupBoxImgBorad3->setTitle("Board3  addr : " + QString::number(this->board3->writerAddr,10));
    ui->groupBoxImgBorad4->setTitle("Board4  addr : " + QString::number(this->board4->writerAddr,10));
    ui->groupBoxImgBorad5->setTitle("Board5  addr : " + QString::number(this->board5->writerAddr,10));
    ui->groupBoxImgBorad6->setTitle("Board6  addr : " + QString::number(this->board6->writerAddr,10));
    ui->groupBoxImgBorad7->setTitle("Board7  addr : " + QString::number(this->board7->writerAddr,10));
    ui->groupBoxImgBorad8->setTitle("Board8  addr : " + QString::number(this->board8->writerAddr,10));

    this->statusBar()->showMessage(  "Board1 addr: " + QString::number(this->board1->writerAddr,10) + " | "
                                   + "Board2 addr: " + QString::number(this->board2->writerAddr,10) + " | "
                                   + "Board3 addr: " + QString::number(this->board3->writerAddr,10) + " | "
                                   + "Board4 addr: " + QString::number(this->board4->writerAddr,10) + " | "
                                   + "Board5 addr: " + QString::number(this->board5->writerAddr,10) + " | "
                                   + "Board6 addr: " + QString::number(this->board6->writerAddr,10) + " | "
                                   + "Board7 addr: " + QString::number(this->board7->writerAddr,10) + " | "
                                   + "Board8 addr: " + QString::number(this->board8->writerAddr,10) + " | "
                                   );

//    qDebug()<<"board1->readAddr"<<board1->readAddr<<"  "<<board1->writerAddr<<endl;
//    qDebug()<<"board2->readAddr"<<board2->readAddr<<"  "<<board2->writerAddr<<endl;
//    qDebug()<<"board3->readAddr"<<board3->readAddr<<"  "<<board3->writerAddr<<endl;
//    qDebug()<<"board4->readAddr"<<board4->readAddr<<"  "<<board4->writerAddr<<endl;
//    qDebug()<<"board5->readAddr"<<board5->readAddr<<"  "<<board5->writerAddr<<endl;
//    qDebug()<<"board6->readAddr"<<board6->readAddr<<"  "<<board6->writerAddr<<endl;
//    qDebug()<<"board7->readAddr"<<board7->readAddr<<"  "<<board7->writerAddr<<endl;
//    qDebug()<<"board8->readAddr"<<board8->readAddr<<"  "<<board8->writerAddr<<endl;
}

void MainWindow::on_comboBox3Gin1SizeBoard1_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard1->Img3GIn1Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard1->Img3GIn1Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard1->Img3GIn1Size = INPUT_SIZE_FULL;
    }

}

void MainWindow::on_comboBox3Gin2SizeBoard1_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard1->Img3GIn2Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard1->Img3GIn2Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard1->Img3GIn2Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBoxImgBoard1_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard1->ImgType = IMG_IN1_3G;
    }
    else if (index == 1)
    {
        ui->labelImgBoard1->ImgType = IMG_IN2_3G;
    }
    else if (index == 2)
    {
        ui->labelImgBoard1->ImgType = IMG_AI;
    }
    else if (index == 3)
    {
        ui->labelImgBoard1->ImgType = IMG_COLOR;
    }
    else
    {
        ui->labelImgBoard1->ImgType = INPUT_SIZE_1920X1080;
    }
}


void MainWindow::on_pushButtonImgClearBoard1_clicked()
{
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ui->labelImgBoard1->regTable[i][j] = j + i * 4;
        }
    }
    emit ui->labelImgBoard1->regChange((unsigned int *) ui->labelImgBoard1->regTable);
    emit ui->labelImgBoard1->mousePaint();
}



void MainWindow::on_comboBox3Gin1SizeBoard2_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard2->Img3GIn1Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard2->Img3GIn1Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard2->Img3GIn1Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBox3Gin2SizeBoard2_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard2->Img3GIn2Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard2->Img3GIn2Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard2->Img3GIn2Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBoxImgBoard2_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard2->ImgType = IMG_IN1_3G;
    }
    else if (index == 1)
    {
        ui->labelImgBoard2->ImgType = IMG_IN2_3G;
    }
    else if (index == 2)
    {
        ui->labelImgBoard2->ImgType = IMG_AI;
    }
    else if (index == 3)
    {
        ui->labelImgBoard2->ImgType = IMG_COLOR;
    }
    else
    {
        ui->labelImgBoard2->ImgType = INPUT_SIZE_1920X1080;
    }
}

void MainWindow::on_pushButtonImgClearBoard2_clicked()
{
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ui->labelImgBoard2->regTable[i][j] = j + i * 4;
        }
    }
    emit ui->labelImgBoard2->regChange((unsigned int *) ui->labelImgBoard2->regTable);
    emit ui->labelImgBoard2->mousePaint();
}


void MainWindow::on_comboBox3Gin1SizeBoard3_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard3->Img3GIn1Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard3->Img3GIn1Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard3->Img3GIn1Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBox3Gin2SizeBoard3_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard3->Img3GIn2Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard3->Img3GIn2Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard3->Img3GIn2Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBoxImgBoard3_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard3->ImgType = IMG_IN1_3G;
    }
    else if (index == 1)
    {
        ui->labelImgBoard3->ImgType = IMG_IN2_3G;
    }
    else if (index == 2)
    {
        ui->labelImgBoard3->ImgType = IMG_AI;
    }
    else if (index == 3)
    {
        ui->labelImgBoard3->ImgType = IMG_COLOR;
    }
    else
    {
        ui->labelImgBoard3->ImgType = INPUT_SIZE_1920X1080;
    }
}

void MainWindow::on_pushButtonImgClearBoard3_clicked()
{
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ui->labelImgBoard3->regTable[i][j] = j + i * 4;
        }
    }
    emit ui->labelImgBoard3->regChange((unsigned int *) ui->labelImgBoard3->regTable);
    emit ui->labelImgBoard3->mousePaint();
}


void MainWindow::on_comboBox3Gin1SizeBoard4_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard4->Img3GIn1Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard4->Img3GIn1Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard4->Img3GIn1Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBox3Gin2SizeBoard4_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard4->Img3GIn2Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard4->Img3GIn2Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard4->Img3GIn2Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBoxImgBoard4_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard4->ImgType = IMG_IN1_3G;
    }
    else if (index == 1)
    {
        ui->labelImgBoard4->ImgType = IMG_IN2_3G;
    }
    else if (index == 2)
    {
        ui->labelImgBoard4->ImgType = IMG_AI;
    }
    else if (index == 3)
    {
        ui->labelImgBoard4->ImgType = IMG_COLOR;
    }
    else
    {
        ui->labelImgBoard4->ImgType = INPUT_SIZE_1920X1080;
    }
}

void MainWindow::on_pushButtonImgClearBoard4_clicked()
{
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ui->labelImgBoard4->regTable[i][j] = j + i * 4;
        }
    }
    emit ui->labelImgBoard4->regChange((unsigned int *) ui->labelImgBoard4->regTable);
    emit ui->labelImgBoard4->mousePaint();
}


void MainWindow::on_comboBox3Gin1SizeBoard5_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard5->Img3GIn1Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard5->Img3GIn1Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard5->Img3GIn1Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBox3Gin2SizeBoard5_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard5->Img3GIn2Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard5->Img3GIn2Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard5->Img3GIn2Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBoxImgBoard5_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard5->ImgType = IMG_IN1_3G;
    }
    else if (index == 1)
    {
        ui->labelImgBoard5->ImgType = IMG_IN2_3G;
    }
    else if (index == 2)
    {
        ui->labelImgBoard5->ImgType = IMG_AI;
    }
    else if (index == 3)
    {
        ui->labelImgBoard5->ImgType = IMG_COLOR;
    }
    else
    {
        ui->labelImgBoard5->ImgType = INPUT_SIZE_1920X1080;
    }
}

void MainWindow::on_pushButtonImgClearBoard5_clicked()
{
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ui->labelImgBoard5->regTable[i][j] = j + i * 4;
        }
    }
    emit ui->labelImgBoard5->regChange((unsigned int *) ui->labelImgBoard5->regTable);
    emit ui->labelImgBoard5->mousePaint();
}



void MainWindow::on_comboBox3Gin1SizeBoard6_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard6->Img3GIn1Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard6->Img3GIn1Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard6->Img3GIn1Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBox3Gin2SizeBoard6_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard6->Img3GIn2Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard6->Img3GIn2Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard6->Img3GIn2Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBoxImgBoard6_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard6->ImgType = IMG_IN1_3G;
    }
    else if (index == 1)
    {
        ui->labelImgBoard6->ImgType = IMG_IN2_3G;
    }
    else if (index == 2)
    {
        ui->labelImgBoard6->ImgType = IMG_AI;
    }
    else if (index == 3)
    {
        ui->labelImgBoard6->ImgType = IMG_COLOR;
    }
    else
    {
        ui->labelImgBoard6->ImgType = INPUT_SIZE_1920X1080;
    }
}

void MainWindow::on_pushButtonImgClearBoard6_clicked()
{
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ui->labelImgBoard6->regTable[i][j] = j + i * 4;
        }
    }
    emit ui->labelImgBoard6->regChange((unsigned int *) ui->labelImgBoard6->regTable);
    emit ui->labelImgBoard6->mousePaint();
}



void MainWindow::on_comboBox3Gin1SizeBoard7_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard7->Img3GIn1Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard7->Img3GIn1Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard7->Img3GIn1Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBox3Gin2SizeBoard7_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard7->Img3GIn2Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard7->Img3GIn2Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard7->Img3GIn2Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBoxImgBoard7_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard7->ImgType = IMG_IN1_3G;
    }
    else if (index == 1)
    {
        ui->labelImgBoard7->ImgType = IMG_IN2_3G;
    }
    else if (index == 2)
    {
        ui->labelImgBoard7->ImgType = IMG_AI;
    }
    else if (index == 3)
    {
        ui->labelImgBoard7->ImgType = IMG_COLOR;
    }
    else
    {
        ui->labelImgBoard7->ImgType = INPUT_SIZE_1920X1080;
    }
}

void MainWindow::on_pushButtonImgClearBoard7_clicked()
{
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ui->labelImgBoard7->regTable[i][j] = j + i * 4;
        }
    }
    emit ui->labelImgBoard7->regChange((unsigned int *) ui->labelImgBoard7->regTable);
    emit ui->labelImgBoard7->mousePaint();
}


void MainWindow::on_comboBox3Gin1SizeBoard8_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard8->Img3GIn1Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard8->Img3GIn1Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard8->Img3GIn1Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBox3Gin2SizeBoard8_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard8->Img3GIn2Size = INPUT_SIZE_1920X1080;
    }
    else if (index == 1)
    {
        ui->labelImgBoard8->Img3GIn2Size = INPUT_SIZE_960X540;
    }
    else if (index == 2)
    {
        ui->labelImgBoard8->Img3GIn2Size = INPUT_SIZE_FULL;
    }
}

void MainWindow::on_comboBoxImgBoard8_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->labelImgBoard8->ImgType = IMG_IN1_3G;
    }
    else if (index == 1)
    {
        ui->labelImgBoard8->ImgType = IMG_IN2_3G;
    }
    else if (index == 2)
    {
        ui->labelImgBoard8->ImgType = IMG_AI;
    }
    else if (index == 3)
    {
        ui->labelImgBoard8->ImgType = IMG_COLOR;
    }
    else
    {
        ui->labelImgBoard8->ImgType = INPUT_SIZE_1920X1080;
    }
}

void MainWindow::on_pushButtonImgClearBoard8_clicked()
{
    for(int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ui->labelImgBoard8->regTable[i][j] = j + i * 4;
        }
    }
    emit ui->labelImgBoard8->regChange((unsigned int *) ui->labelImgBoard8->regTable);
    emit ui->labelImgBoard8->mousePaint();
}






void MainWindow::on_btnWorkControlLoad_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("./"),"",tr("txt(*.txt)"));

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

    for(int i = 0 ; i < 8; i++)
    {


        QByteArray line = file.readLine();
        if(line[0] == 'B' && line[1] == 'o' && line[2] == 'a' && line[3] == 'r' && line[4] == 'd')  //确定文件正确
        {
            if(line[5] == '1')
            {
                unsigned int arr[4][4];
                char *chline = line.data();
                sscanf(chline,"Board1 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;",
                       &arr[0][0], &arr[0][1], &arr[0][2], &arr[0][3],
                       &arr[1][0], &arr[1][1], &arr[1][2], &arr[1][3],
                       &arr[2][0], &arr[2][1], &arr[2][2], &arr[2][3],
                       &arr[3][0], &arr[3][1], &arr[3][2], &arr[3][3]
                        );

                for(int table_i = 0; table_i < 4; table_i++)
                {
                    for(int table_j = 0; table_j < 4; table_j++)
                    {
                       //qDebug()<<"Board1"<<arr[table_i][table_j];
                       ui->labelImgBoard1->regTable[table_i][table_j] = arr[table_i][table_j];
                    }
                }
                emit ui->labelImgBoard1->regChange((unsigned int *)ui->labelImgBoard1->regTable);
                emit ui->labelImgBoard1->mousePaint();

            }
            if(line[5] == '2')
            {
                unsigned int arr[4][4];
                char *chline = line.data();
                sscanf(chline,"Board2 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;",
                       &arr[0][0], &arr[0][1], &arr[0][2], &arr[0][3],
                       &arr[1][0], &arr[1][1], &arr[1][2], &arr[1][3],
                       &arr[2][0], &arr[2][1], &arr[2][2], &arr[2][3],
                       &arr[3][0], &arr[3][1], &arr[3][2], &arr[3][3]
                        );

                for(int table_i = 0; table_i < 4; table_i++)
                {
                    for(int table_j = 0; table_j < 4; table_j++)
                    {
                       //qDebug()<<"Board2"<<arr[table_i][table_j];
                       ui->labelImgBoard2->regTable[table_i][table_j] = arr[table_i][table_j];
                    }
                }
                emit ui->labelImgBoard2->regChange((unsigned int *)ui->labelImgBoard2->regTable);
                emit ui->labelImgBoard2->mousePaint();
            }
            if(line[5] == '3')
            {
                unsigned int arr[4][4];
                char *chline = line.data();
                sscanf(chline,"Board3 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;",
                       &arr[0][0], &arr[0][1], &arr[0][2], &arr[0][3],
                       &arr[1][0], &arr[1][1], &arr[1][2], &arr[1][3],
                       &arr[2][0], &arr[2][1], &arr[2][2], &arr[2][3],
                       &arr[3][0], &arr[3][1], &arr[3][2], &arr[3][3]
                        );

                for(int table_i = 0; table_i < 4; table_i++)
                {
                    for(int table_j = 0; table_j < 4; table_j++)
                    {
                       //qDebug()<<"Board3"<<arr[table_i][table_j];
                       ui->labelImgBoard3->regTable[table_i][table_j] = arr[table_i][table_j];
                    }
                }
                emit ui->labelImgBoard3->regChange((unsigned int *)ui->labelImgBoard3->regTable);
                emit ui->labelImgBoard3->mousePaint();
            }
            if(line[5] == '4')
            {
                unsigned int arr[4][4];
                char *chline = line.data();
                sscanf(chline,"Board4 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;",
                       &arr[0][0], &arr[0][1], &arr[0][2], &arr[0][3],
                       &arr[1][0], &arr[1][1], &arr[1][2], &arr[1][3],
                       &arr[2][0], &arr[2][1], &arr[2][2], &arr[2][3],
                       &arr[3][0], &arr[3][1], &arr[3][2], &arr[3][3]
                        );

                for(int table_i = 0; table_i < 4; table_i++)
                {
                    for(int table_j = 0; table_j < 4; table_j++)
                    {
                       //qDebug()<<"Board4"<<arr[table_i][table_j];
                       ui->labelImgBoard4->regTable[table_i][table_j] = arr[table_i][table_j];
                    }
                }
                emit ui->labelImgBoard4->regChange((unsigned int *)ui->labelImgBoard4->regTable);
                emit ui->labelImgBoard4->mousePaint();
            }
            if(line[5] == '5')
            {
                unsigned int arr[4][4];
                char *chline = line.data();
                sscanf(chline,"Board5 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;",
                       &arr[0][0], &arr[0][1], &arr[0][2], &arr[0][3],
                       &arr[1][0], &arr[1][1], &arr[1][2], &arr[1][3],
                       &arr[2][0], &arr[2][1], &arr[2][2], &arr[2][3],
                       &arr[3][0], &arr[3][1], &arr[3][2], &arr[3][3]
                        );

                for(int table_i = 0; table_i < 4; table_i++)
                {
                    for(int table_j = 0; table_j < 4; table_j++)
                    {
                       //qDebug()<<"Board5"<<arr[table_i][table_j];
                       ui->labelImgBoard5->regTable[table_i][table_j] = arr[table_i][table_j];
                    }
                }
                emit ui->labelImgBoard5->regChange((unsigned int *)ui->labelImgBoard5->regTable);
                emit ui->labelImgBoard5->mousePaint();
            }
            if(line[5] == '6')
            {
                unsigned int arr[4][4];
                char *chline = line.data();
                sscanf(chline,"Board6 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;",
                       &arr[0][0], &arr[0][1], &arr[0][2], &arr[0][3],
                       &arr[1][0], &arr[1][1], &arr[1][2], &arr[1][3],
                       &arr[2][0], &arr[2][1], &arr[2][2], &arr[2][3],
                       &arr[3][0], &arr[3][1], &arr[3][2], &arr[3][3]
                        );

                for(int table_i = 0; table_i < 4; table_i++)
                {
                    for(int table_j = 0; table_j < 4; table_j++)
                    {
                       //qDebug()<<"Board6"<<arr[table_i][table_j];
                       ui->labelImgBoard6->regTable[table_i][table_j] = arr[table_i][table_j];
                    }
                }
                emit ui->labelImgBoard6->regChange((unsigned int *)ui->labelImgBoard6->regTable);
                emit ui->labelImgBoard6->mousePaint();
            }
            if(line[5] == '7')
            {
                unsigned int arr[4][4];
                char *chline = line.data();
                sscanf(chline,"Board7 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;",
                       &arr[0][0], &arr[0][1], &arr[0][2], &arr[0][3],
                       &arr[1][0], &arr[1][1], &arr[1][2], &arr[1][3],
                       &arr[2][0], &arr[2][1], &arr[2][2], &arr[2][3],
                       &arr[3][0], &arr[3][1], &arr[3][2], &arr[3][3]
                        );

                for(int table_i = 0; table_i < 4; table_i++)
                {
                    for(int table_j = 0; table_j < 4; table_j++)
                    {
                       //qDebug()<<"Board7"<<arr[table_i][table_j];
                       ui->labelImgBoard7->regTable[table_i][table_j] = arr[table_i][table_j];
                    }
                }
                emit ui->labelImgBoard7->regChange((unsigned int *)ui->labelImgBoard7->regTable);
                emit ui->labelImgBoard7->mousePaint();

            }
            if(line[5] == '8')
            {
                unsigned int arr[4][4];
                char *chline = line.data();
                sscanf(chline,"Board8 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;",
                       &arr[0][0], &arr[0][1], &arr[0][2], &arr[0][3],
                       &arr[1][0], &arr[1][1], &arr[1][2], &arr[1][3],
                       &arr[2][0], &arr[2][1], &arr[2][2], &arr[2][3],
                       &arr[3][0], &arr[3][1], &arr[3][2], &arr[3][3]
                        );

                for(int table_i = 0; table_i < 4; table_i++)
                {
                    for(int table_j = 0; table_j < 4; table_j++)
                    {
                       //qDebug()<<"Board8"<<arr[table_i][table_j];
                       ui->labelImgBoard8->regTable[table_i][table_j] = arr[table_i][table_j];
                    }
                }
                emit ui->labelImgBoard8->regChange((unsigned int *)ui->labelImgBoard8->regTable);
                emit ui->labelImgBoard8->mousePaint();

            }

        }

    }


    file.close();
}

void MainWindow::on_btnWorkControlSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("Normal text File (*.txt)"));
    if (fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"open file false";
        return;
    }
    file.flush();
    char str[64] = "";

    sprintf(str,"Board1 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;\r\n",
            ui->labelImgBoard1->regTable[0][0], ui->labelImgBoard1->regTable[0][1], ui->labelImgBoard1->regTable[0][2], ui->labelImgBoard1->regTable[0][3],
            ui->labelImgBoard1->regTable[1][0], ui->labelImgBoard1->regTable[1][1], ui->labelImgBoard1->regTable[1][2], ui->labelImgBoard1->regTable[1][3],
            ui->labelImgBoard1->regTable[2][0], ui->labelImgBoard1->regTable[2][1], ui->labelImgBoard1->regTable[2][2], ui->labelImgBoard1->regTable[2][3],
            ui->labelImgBoard1->regTable[3][0], ui->labelImgBoard1->regTable[3][1], ui->labelImgBoard1->regTable[3][2], ui->labelImgBoard1->regTable[3][3]);
    file.write(str);

    sprintf(str,"Board2 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;\r\n",
            ui->labelImgBoard2->regTable[0][0], ui->labelImgBoard2->regTable[0][1], ui->labelImgBoard2->regTable[0][2], ui->labelImgBoard2->regTable[0][3],
            ui->labelImgBoard2->regTable[1][0], ui->labelImgBoard2->regTable[1][1], ui->labelImgBoard2->regTable[1][2], ui->labelImgBoard2->regTable[1][3],
            ui->labelImgBoard2->regTable[2][0], ui->labelImgBoard2->regTable[2][1], ui->labelImgBoard2->regTable[2][2], ui->labelImgBoard2->regTable[2][3],
            ui->labelImgBoard2->regTable[3][0], ui->labelImgBoard2->regTable[3][1], ui->labelImgBoard2->regTable[3][2], ui->labelImgBoard2->regTable[3][3]);
    file.write(str);

    sprintf(str,"Board3 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;\r\n",
            ui->labelImgBoard3->regTable[0][0], ui->labelImgBoard3->regTable[0][1], ui->labelImgBoard3->regTable[0][2], ui->labelImgBoard3->regTable[0][3],
            ui->labelImgBoard3->regTable[1][0], ui->labelImgBoard3->regTable[1][1], ui->labelImgBoard3->regTable[1][2], ui->labelImgBoard3->regTable[1][3],
            ui->labelImgBoard3->regTable[2][0], ui->labelImgBoard3->regTable[2][1], ui->labelImgBoard3->regTable[2][2], ui->labelImgBoard3->regTable[2][3],
            ui->labelImgBoard3->regTable[3][0], ui->labelImgBoard3->regTable[3][1], ui->labelImgBoard3->regTable[3][2], ui->labelImgBoard3->regTable[3][3]);
    file.write(str);


    sprintf(str,"Board4 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;\r\n",
            ui->labelImgBoard4->regTable[0][0], ui->labelImgBoard4->regTable[0][1], ui->labelImgBoard4->regTable[0][2], ui->labelImgBoard4->regTable[0][3],
            ui->labelImgBoard4->regTable[1][0], ui->labelImgBoard4->regTable[1][1], ui->labelImgBoard4->regTable[1][2], ui->labelImgBoard4->regTable[1][3],
            ui->labelImgBoard4->regTable[2][0], ui->labelImgBoard4->regTable[2][1], ui->labelImgBoard4->regTable[2][2], ui->labelImgBoard4->regTable[2][3],
            ui->labelImgBoard4->regTable[3][0], ui->labelImgBoard4->regTable[3][1], ui->labelImgBoard4->regTable[3][2], ui->labelImgBoard4->regTable[3][3]);
    file.write(str);

    sprintf(str,"Board5 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;\r\n",
            ui->labelImgBoard5->regTable[0][0], ui->labelImgBoard5->regTable[0][1], ui->labelImgBoard5->regTable[0][2], ui->labelImgBoard5->regTable[0][3],
            ui->labelImgBoard5->regTable[1][0], ui->labelImgBoard5->regTable[1][1], ui->labelImgBoard5->regTable[1][2], ui->labelImgBoard5->regTable[1][3],
            ui->labelImgBoard5->regTable[2][0], ui->labelImgBoard5->regTable[2][1], ui->labelImgBoard5->regTable[2][2], ui->labelImgBoard5->regTable[2][3],
            ui->labelImgBoard5->regTable[3][0], ui->labelImgBoard5->regTable[3][1], ui->labelImgBoard5->regTable[3][2], ui->labelImgBoard5->regTable[3][3]);
    file.write(str);

    sprintf(str,"Board6 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;\r\n",
            ui->labelImgBoard6->regTable[0][0], ui->labelImgBoard6->regTable[0][1], ui->labelImgBoard6->regTable[0][2], ui->labelImgBoard6->regTable[0][3],
            ui->labelImgBoard6->regTable[1][0], ui->labelImgBoard6->regTable[1][1], ui->labelImgBoard6->regTable[1][2], ui->labelImgBoard6->regTable[1][3],
            ui->labelImgBoard6->regTable[2][0], ui->labelImgBoard6->regTable[2][1], ui->labelImgBoard6->regTable[2][2], ui->labelImgBoard6->regTable[2][3],
            ui->labelImgBoard6->regTable[3][0], ui->labelImgBoard6->regTable[3][1], ui->labelImgBoard6->regTable[3][2], ui->labelImgBoard6->regTable[3][3]);
    file.write(str);

    sprintf(str,"Board7 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;\r\n",
            ui->labelImgBoard7->regTable[0][0], ui->labelImgBoard7->regTable[0][1], ui->labelImgBoard7->regTable[0][2], ui->labelImgBoard7->regTable[0][3],
            ui->labelImgBoard7->regTable[1][0], ui->labelImgBoard7->regTable[1][1], ui->labelImgBoard7->regTable[1][2], ui->labelImgBoard7->regTable[1][3],
            ui->labelImgBoard7->regTable[2][0], ui->labelImgBoard7->regTable[2][1], ui->labelImgBoard7->regTable[2][2], ui->labelImgBoard7->regTable[2][3],
            ui->labelImgBoard7->regTable[3][0], ui->labelImgBoard7->regTable[3][1], ui->labelImgBoard7->regTable[3][2], ui->labelImgBoard7->regTable[3][3]);
    file.write(str);

    sprintf(str,"Board8 %x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;%x;\r\n",
            ui->labelImgBoard8->regTable[0][0], ui->labelImgBoard8->regTable[0][1], ui->labelImgBoard8->regTable[0][2], ui->labelImgBoard8->regTable[0][3],
            ui->labelImgBoard8->regTable[1][0], ui->labelImgBoard8->regTable[1][1], ui->labelImgBoard8->regTable[1][2], ui->labelImgBoard8->regTable[1][3],
            ui->labelImgBoard8->regTable[2][0], ui->labelImgBoard8->regTable[2][1], ui->labelImgBoard8->regTable[2][2], ui->labelImgBoard8->regTable[2][3],
            ui->labelImgBoard8->regTable[3][0], ui->labelImgBoard8->regTable[3][1], ui->labelImgBoard8->regTable[3][2], ui->labelImgBoard8->regTable[3][3]);
    file.write(str);
    file.close();
}
