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
             ui->lcdNumberFPGATempeBoard1->display(this->protocolHand->MDSP_Board_FPGAtemperature);

             ui->chartViewCurrentBoard1->prepareData(this->protocolHand->MDSP_Board_currents);
             ui->chartView12VBoard1->prepareData(this->protocolHand->MDSP_Board_HV);
             ui->chartView5VBoard1->prepareData(this->protocolHand->MDSP_Board_LV);
             ui->chartViewCavityTempBoard1->prepareData(this->protocolHand->MDSP_Board_temperature);
             ui->chartViewFpgaTempBoard1->prepareData(this->protocolHand->MDSP_Board_FPGAtemperature);




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
             ui->lcdNumberFPGATempeBoard2->display(this->protocolHand->MDSP_Board_FPGAtemperature);

             ui->chartViewCurrentBoard2->prepareData(this->protocolHand->MDSP_Board_currents);
             ui->chartView12VBoard2->prepareData(this->protocolHand->MDSP_Board_HV);
             ui->chartView5VBoard2->prepareData(this->protocolHand->MDSP_Board_LV);
             ui->chartViewCavityTempBoard2->prepareData(this->protocolHand->MDSP_Board_temperature);
             ui->chartViewFpgaTempBoard2->prepareData(this->protocolHand->MDSP_Board_FPGAtemperature);
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
             ui->lcdNumberFPGATempeBoard3->display(this->protocolHand->MDSP_Board_FPGAtemperature);

             ui->chartViewCurrentBoard3->prepareData(this->protocolHand->MDSP_Board_currents);
             ui->chartView12VBoard3->prepareData(this->protocolHand->MDSP_Board_HV);
             ui->chartView5VBoard3->prepareData(this->protocolHand->MDSP_Board_LV);
             ui->chartViewCavityTempBoard3->prepareData(this->protocolHand->MDSP_Board_temperature);
             ui->chartViewFpgaTempBoard3->prepareData(this->protocolHand->MDSP_Board_FPGAtemperature);
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
             ui->lcdNumberFPGATempeBoard4->display(this->protocolHand->MDSP_Board_FPGAtemperature);

             ui->chartViewCurrentBoard4->prepareData(this->protocolHand->MDSP_Board_currents);
             ui->chartView12VBoard4->prepareData(this->protocolHand->MDSP_Board_HV);
             ui->chartView5VBoard4->prepareData(this->protocolHand->MDSP_Board_LV);
             ui->chartViewCavityTempBoard4->prepareData(this->protocolHand->MDSP_Board_temperature);
             ui->chartViewFpgaTempBoard4->prepareData(this->protocolHand->MDSP_Board_FPGAtemperature);
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
             ui->lcdNumberFPGATempeBoard5->display(this->protocolHand->MDSP_Board_FPGAtemperature);

             ui->chartViewCurrentBoard5->prepareData(this->protocolHand->MDSP_Board_currents);
             ui->chartView12VBoard5->prepareData(this->protocolHand->MDSP_Board_HV);
             ui->chartView5VBoard5->prepareData(this->protocolHand->MDSP_Board_LV);
             ui->chartViewCavityTempBoard5->prepareData(this->protocolHand->MDSP_Board_temperature);
             ui->chartViewFpgaTempBoard5->prepareData(this->protocolHand->MDSP_Board_FPGAtemperature);
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
             ui->lcdNumberFPGATempeBoard6->display(this->protocolHand->MDSP_Board_FPGAtemperature);


             ui->chartViewCurrentBoard6->prepareData(this->protocolHand->MDSP_Board_currents);
             ui->chartView12VBoard6->prepareData(this->protocolHand->MDSP_Board_HV);
             ui->chartView5VBoard6->prepareData(this->protocolHand->MDSP_Board_LV);
             ui->chartViewCavityTempBoard6->prepareData(this->protocolHand->MDSP_Board_temperature);
             ui->chartViewFpgaTempBoard6->prepareData(this->protocolHand->MDSP_Board_FPGAtemperature);
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
             ui->lcdNumberFPGATempeBoard7->display(this->protocolHand->MDSP_Board_FPGAtemperature);


             ui->chartViewCurrentBoard7->prepareData(this->protocolHand->MDSP_Board_currents);
             ui->chartView12VBoard7->prepareData(this->protocolHand->MDSP_Board_HV);
             ui->chartView5VBoard7->prepareData(this->protocolHand->MDSP_Board_LV);
             ui->chartViewCavityTempBoard7->prepareData(this->protocolHand->MDSP_Board_temperature);
             ui->chartViewFpgaTempBoard7->prepareData(this->protocolHand->MDSP_Board_FPGAtemperature);
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
             ui->lcdNumberFPGATempeBoard8->display(this->protocolHand->MDSP_Board_FPGAtemperature);


             ui->chartViewCurrentBoard8->prepareData(this->protocolHand->MDSP_Board_currents);
             ui->chartView12VBoard8->prepareData(this->protocolHand->MDSP_Board_HV);
             ui->chartView5VBoard8->prepareData(this->protocolHand->MDSP_Board_LV);
             ui->chartViewCavityTempBoard8->prepareData(this->protocolHand->MDSP_Board_temperature);
             ui->chartViewFpgaTempBoard8->prepareData(this->protocolHand->MDSP_Board_FPGAtemperature);
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

    if(vci->ID == (PGN59940 << 8) + board1->readAddr ||
       vci->ID == (PGN59940 << 8) + board2->readAddr ||
        vci->ID == (PGN59940 << 8) + board3->readAddr ||
        vci->ID == (PGN59940 << 8) + board4->readAddr ||
        vci->ID == (PGN59940 << 8) + board5->readAddr ||
        vci->ID == (PGN59940 << 8) + board6->readAddr ||
        vci->ID == (PGN59940 << 8) + board7->readAddr ||
        vci->ID == (PGN59940 << 8) + board8->readAddr ) //读取FPGA数据
    {
        unsigned int fpga_temp = 0;
        fpga_temp += (unsigned int)vci[0].Data[6] << 8;
        fpga_temp += (unsigned int)vci[0].Data[7] ;

        this->protocolHand->MDSP_Board_FPGAtemperature = (float)fpga_temp * 693 / 1024 - 265;  //FPGA温度计算公式
    }


    if(vci->ID == (PGN60672 << 8) + board1->readAddr ||
            vci->ID == (PGN60672 << 8) + board2->readAddr ||
             vci->ID == (PGN60672 << 8) + board3->readAddr ||
             vci->ID == (PGN60672 << 8) + board4->readAddr ||
             vci->ID == (PGN60672 << 8) + board5->readAddr ||
             vci->ID == (PGN60672 << 8) + board6->readAddr ||
             vci->ID == (PGN60672 << 8) + board7->readAddr ||
             vci->ID == (PGN60672 << 8) + board8->readAddr )
    {
        ui->lineEditUpgradeAddr->setText(QString::number((unsigned int)vci[0].Data[7],16));
    }


    if(vci->ID == (PGN60928 << 8) + board1->readAddr) //IDOG 应答
    {
        QString currentTime =" Board 1  " + QTime::currentTime().toString("HH:mm:ss   ");
        if(vci[0].Data[0] == 0x00)//MCU IDOG应答
        {
            if(vci[0].Data[6] == 0xf0 && vci[0].Data[7] == 0xf0)
            {
                setLED(ui->labMCULEDBoard1, 2, 16);
            }
            else
            {

                ui->textBrowsererrlog->append(currentTime + "Board1 MCU abnormal");
                setLED(ui->labMCULEDBoard1, 3, 16);
            }
        }
        if(vci[0].Data[0] == 0x01)//FPGA IDOG应答
        {
            if(vci[0].Data[6] == 0x80 && vci[0].Data[7] == 0x00)
            {
               // qDebug()<<"FPGA IDOG normal"<<endl;
                setLED(ui->labFPGALEDBoard1, 2, 16);
            }
            else
            {
                if(vci[0].Data[6] != 0x80)  //离线
                {
                    setLED(ui->labFPGALEDBoard1, 0, 16);
                }
                else  //在线
                {
                    if(vci[0].Data[7] & 0x01)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx1-phy err");
                        setLED(ui->labFPGALEDBoard1, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x02)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx2-phy err");
                        setLED(ui->labFPGALEDBoard1, 3, 16);

                    }
                    if(vci[0].Data[7] & 0x04)
                    {
                        //ui->textBrowsererrlog->append(currentTime + "FPGA 12G-rx-phy err");
                        setLED(ui->labFPGALEDBoard1, 2, 16);  // Board1 12G-rx 默认无输入 可忽略错误
                    }
                    if(vci[0].Data[7] & 0x08)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-tx-phy err");
                        setLED(ui->labFPGALEDBoard1, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x10)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA addr-phy err");
                        setLED(ui->labFPGALEDBoard1, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x20)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA system err");
                        setLED(ui->labFPGALEDBoard1, 3, 16);
                    }
                }

            }
        }
        if(vci[0].Data[0] == 0x02)//DSP IDOG应答
        {
            qDebug()<<"DSP IDOG"<<endl;
            setLED(ui->labDSPLEDBoard1, 2, 16);
        }
    }

    if(vci->ID == (PGN60928 << 8) + board2->readAddr) //IDOG 应答
    {
        QString currentTime =" Board 2  " + QTime::currentTime().toString("HH:mm:ss   ");
        if(vci[0].Data[0] == 0x00)//MCU IDOG应答
        {
            if(vci[0].Data[6] == 0xf0 && vci[0].Data[7] == 0xf0)
            {
                setLED(ui->labMCULEDBoard2, 2, 16);
            }
            else
            {

                ui->textBrowsererrlog->append(currentTime + "MCU abnormal");
                setLED(ui->labMCULEDBoard2, 3, 16);
            }
        }
        if(vci[0].Data[0] == 0x01)//FPGA IDOG应答
        {
            if(vci[0].Data[6] == 0x80 && vci[0].Data[7] == 0x00)
            {
               // qDebug()<<"FPGA IDOG normal"<<endl;
                setLED(ui->labFPGALEDBoard2, 2, 16);
            }
            else
            {
                if(vci[0].Data[6] != 0x80)  //离线
                {
                    setLED(ui->labFPGALEDBoard2, 0, 16);
                }
                else  //在线
                {
                    if(vci[0].Data[7] & 0x01)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx1-phy err");
                        setLED(ui->labFPGALEDBoard2, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x02)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx2-phy err");
                        setLED(ui->labFPGALEDBoard2, 3, 16);

                    }
                    if(vci[0].Data[7] & 0x04)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-rx-phy err");
                        setLED(ui->labFPGALEDBoard2, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x08)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-tx-phy err");
                        setLED(ui->labFPGALEDBoard2, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x10)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA addr-phy err");
                        setLED(ui->labFPGALEDBoard2, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x20)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA system err");
                        setLED(ui->labFPGALEDBoard2, 3, 16);
                    }
                }

            }
        }
        if(vci[0].Data[0] == 0x02)//DSP IDOG应答
        {
            qDebug()<<"DSP IDOG"<<endl;
            setLED(ui->labDSPLEDBoard2, 2, 16);
        }
    }

    if(vci->ID == (PGN60928 << 8) + board3->readAddr) //IDOG 应答
    {
        QString currentTime =" Board 3  " + QTime::currentTime().toString("HH:mm:ss   ");
        if(vci[0].Data[0] == 0x00)//MCU IDOG应答
        {
            if(vci[0].Data[6] == 0xf0 && vci[0].Data[7] == 0xf0)
            {
                setLED(ui->labMCULEDBoard3, 2, 16);
            }
            else
            {

                ui->textBrowsererrlog->append(currentTime + "MCU abnormal");
                setLED(ui->labMCULEDBoard3, 3, 16);
            }
        }
        if(vci[0].Data[0] == 0x01)//FPGA IDOG应答
        {
            if(vci[0].Data[6] == 0x80 && vci[0].Data[7] == 0x00)
            {
               // qDebug()<<"FPGA IDOG normal"<<endl;
                setLED(ui->labFPGALEDBoard3, 2, 16);
            }
            else
            {
                if(vci[0].Data[6] != 0x80)  //离线
                {
                    setLED(ui->labFPGALEDBoard3, 0, 16);
                }
                else  //在线
                {
                    if(vci[0].Data[7] & 0x01)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx1-phy err");
                        setLED(ui->labFPGALEDBoard3, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x02)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx2-phy err");
                        setLED(ui->labFPGALEDBoard3, 3, 16);

                    }
                    if(vci[0].Data[7] & 0x04)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-rx-phy err");
                        setLED(ui->labFPGALEDBoard3, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x08)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-tx-phy err");
                        setLED(ui->labFPGALEDBoard3, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x10)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA addr-phy err");
                        setLED(ui->labFPGALEDBoard3, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x20)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA system err");
                        setLED(ui->labFPGALEDBoard3, 3, 16);
                    }
                }

            }
        }
        if(vci[0].Data[0] == 0x02)//DSP IDOG应答
        {
            qDebug()<<"DSP IDOG"<<endl;
            setLED(ui->labDSPLEDBoard3, 2, 16);
        }
    }

    if(vci->ID == (PGN60928 << 8) + board4->readAddr) //IDOG 应答
    {
        QString currentTime =" Board 4  " + QTime::currentTime().toString("HH:mm:ss   ");
        if(vci[0].Data[0] == 0x00)//MCU IDOG应答
        {
            if(vci[0].Data[6] == 0xf0 && vci[0].Data[7] == 0xf0)
            {
                setLED(ui->labMCULEDBoard4, 2, 16);
            }
            else
            {

                ui->textBrowsererrlog->append(currentTime + "MCU abnormal");
                setLED(ui->labMCULEDBoard4, 3, 16);
            }
        }
        if(vci[0].Data[0] == 0x01)//FPGA IDOG应答
        {
            if(vci[0].Data[6] == 0x80 && vci[0].Data[7] == 0x00)
            {
               // qDebug()<<"FPGA IDOG normal"<<endl;
                setLED(ui->labFPGALEDBoard4, 2, 16);
            }
            else
            {
                if(vci[0].Data[6] != 0x80)  //离线
                {
                    setLED(ui->labFPGALEDBoard4, 0, 16);
                }
                else  //在线
                {
                    if(vci[0].Data[7] & 0x01)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx1-phy err");
                        setLED(ui->labFPGALEDBoard4, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x02)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx2-phy err");
                        setLED(ui->labFPGALEDBoard4, 3, 16);

                    }
                    if(vci[0].Data[7] & 0x04)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-rx-phy err");
                        setLED(ui->labFPGALEDBoard4, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x08)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-tx-phy err");
                        setLED(ui->labFPGALEDBoard4, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x10)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA addr-phy err");
                        setLED(ui->labFPGALEDBoard4, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x20)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA system err");
                        setLED(ui->labFPGALEDBoard4, 3, 16);
                    }
                }

            }
        }
        if(vci[0].Data[0] == 0x02)//DSP IDOG应答
        {
            qDebug()<<"DSP IDOG"<<endl;
            setLED(ui->labDSPLEDBoard4, 2, 16);
        }
    }

    if(vci->ID == (PGN60928 << 8) + board5->readAddr) //IDOG 应答
    {
        QString currentTime =" Board 5  " + QTime::currentTime().toString("HH:mm:ss   ");
        if(vci[0].Data[0] == 0x00)//MCU IDOG应答
        {
            if(vci[0].Data[6] == 0xf0 && vci[0].Data[7] == 0xf0)
            {
                setLED(ui->labMCULEDBoard5, 2, 16);
            }
            else
            {

                ui->textBrowsererrlog->append(currentTime + "MCU abnormal");
                setLED(ui->labMCULEDBoard5, 3, 16);
            }
        }
        if(vci[0].Data[0] == 0x01)//FPGA IDOG应答
        {
            if(vci[0].Data[6] == 0x80 && vci[0].Data[7] == 0x00)
            {
               // qDebug()<<"FPGA IDOG normal"<<endl;
                setLED(ui->labFPGALEDBoard5, 2, 16);
            }
            else
            {
                if(vci[0].Data[6] != 0x80)  //离线
                {
                    setLED(ui->labFPGALEDBoard5, 0, 16);
                }
                else  //在线
                {
                    if(vci[0].Data[7] & 0x01)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx1-phy err");
                        setLED(ui->labFPGALEDBoard5, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x02)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx2-phy err");
                        setLED(ui->labFPGALEDBoard5, 3, 16);

                    }
                    if(vci[0].Data[7] & 0x04)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-rx-phy err");
                        setLED(ui->labFPGALEDBoard5, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x08)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-tx-phy err");
                        setLED(ui->labFPGALEDBoard5, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x10)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA addr-phy err");
                        setLED(ui->labFPGALEDBoard5, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x20)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA system err");
                        setLED(ui->labFPGALEDBoard5, 3, 16);
                    }
                }

            }
        }
        if(vci[0].Data[0] == 0x02)//DSP IDOG应答
        {
            qDebug()<<"DSP IDOG"<<endl;
            setLED(ui->labDSPLEDBoard5, 2, 16);
        }
    }

    if(vci->ID == (PGN60928 << 8) + board6->readAddr) //IDOG 应答
    {
        QString currentTime =" Board 6  " + QTime::currentTime().toString("HH:mm:ss   ");
        if(vci[0].Data[0] == 0x00)//MCU IDOG应答
        {
            if(vci[0].Data[6] == 0xf0 && vci[0].Data[7] == 0xf0)
            {
                setLED(ui->labMCULEDBoard6, 2, 16);
            }
            else
            {

                ui->textBrowsererrlog->append(currentTime + "MCU abnormal");
                setLED(ui->labMCULEDBoard6, 3, 16);
            }
        }
        if(vci[0].Data[0] == 0x01)//FPGA IDOG应答
        {
            if(vci[0].Data[6] == 0x80 && vci[0].Data[7] == 0x00)
            {
               // qDebug()<<"FPGA IDOG normal"<<endl;
                setLED(ui->labFPGALEDBoard6, 2, 16);
            }
            else
            {
                if(vci[0].Data[6] != 0x80)  //离线
                {
                    setLED(ui->labFPGALEDBoard6, 0, 16);
                }
                else  //在线
                {
                    if(vci[0].Data[7] & 0x01)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx1-phy err");
                        setLED(ui->labFPGALEDBoard6, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x02)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx2-phy err");
                        setLED(ui->labFPGALEDBoard6, 3, 16);

                    }
                    if(vci[0].Data[7] & 0x04)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-rx-phy err");
                        setLED(ui->labFPGALEDBoard6, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x08)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-tx-phy err");
                        setLED(ui->labFPGALEDBoard6, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x10)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA addr-phy err");
                        setLED(ui->labFPGALEDBoard6, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x20)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA system err");
                        setLED(ui->labFPGALEDBoard6, 3, 16);
                    }
                }

            }
        }
        if(vci[0].Data[0] == 0x02)//DSP IDOG应答
        {
            qDebug()<<"DSP IDOG"<<endl;
            setLED(ui->labDSPLEDBoard6, 2, 16);
        }
    }

    if(vci->ID == (PGN60928 << 8) + board7->readAddr) //IDOG 应答
    {
        QString currentTime =" Board 7  " + QTime::currentTime().toString("HH:mm:ss   ");
        if(vci[0].Data[0] == 0x00)//MCU IDOG应答
        {
            if(vci[0].Data[6] == 0xf0 && vci[0].Data[7] == 0xf0)
            {
                setLED(ui->labMCULEDBoard7, 2, 16);
            }
            else
            {

                ui->textBrowsererrlog->append(currentTime + "MCU abnormal");
                setLED(ui->labMCULEDBoard7, 3, 16);
            }
        }
        if(vci[0].Data[0] == 0x01)//FPGA IDOG应答
        {
            if(vci[0].Data[6] == 0x80 && vci[0].Data[7] == 0x00)
            {
               // qDebug()<<"FPGA IDOG normal"<<endl;
                setLED(ui->labFPGALEDBoard7, 2, 16);
            }
            else
            {
                if(vci[0].Data[6] != 0x80)  //离线
                {
                    setLED(ui->labFPGALEDBoard7, 0, 16);
                }
                else  //在线
                {
                    if(vci[0].Data[7] & 0x01)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx1-phy err");
                        setLED(ui->labFPGALEDBoard7, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x02)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx2-phy err");
                        setLED(ui->labFPGALEDBoard7, 3, 16);

                    }
                    if(vci[0].Data[7] & 0x04)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-rx-phy err");
                        setLED(ui->labFPGALEDBoard7, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x08)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-tx-phy err");
                        setLED(ui->labFPGALEDBoard7, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x10)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA addr-phy err");
                        setLED(ui->labFPGALEDBoard7, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x20)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA system err");
                        setLED(ui->labFPGALEDBoard7, 3, 16);
                    }
                }

            }
        }
        if(vci[0].Data[0] == 0x02)//DSP IDOG应答
        {
            qDebug()<<"DSP IDOG"<<endl;
            setLED(ui->labDSPLEDBoard7, 2, 16);
        }
    }

    if(vci->ID == (PGN60928 << 8) + board8->readAddr) //IDOG 应答
    {
        QString currentTime =" Board 8  " + QTime::currentTime().toString("HH:mm:ss   ");
        if(vci[0].Data[0] == 0x00)//MCU IDOG应答
        {
            if(vci[0].Data[6] == 0xf0 && vci[0].Data[7] == 0xf0)
            {
                setLED(ui->labMCULEDBoard8, 2, 16);
            }
            else
            {

                ui->textBrowsererrlog->append(currentTime + "MCU abnormal");
                setLED(ui->labMCULEDBoard8, 3, 16);
            }
        }
        if(vci[0].Data[0] == 0x01)//FPGA IDOG应答
        {
            if(vci[0].Data[6] == 0x80 && vci[0].Data[7] == 0x00)
            {
               // qDebug()<<"FPGA IDOG normal"<<endl;
                setLED(ui->labFPGALEDBoard8, 2, 16);
            }
            else
            {
                if(vci[0].Data[6] != 0x80)  //离线
                {
                    setLED(ui->labFPGALEDBoard8, 0, 16);
                }
                else  //在线
                {
                    if(vci[0].Data[7] & 0x01)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx1-phy err");
                        setLED(ui->labFPGALEDBoard8, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x02)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 3G-rx2-phy err");
                        setLED(ui->labFPGALEDBoard8, 3, 16);

                    }
                    if(vci[0].Data[7] & 0x04)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-rx-phy err");
                        setLED(ui->labFPGALEDBoard8, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x08)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA 12G-tx-phy err");
                        setLED(ui->labFPGALEDBoard8, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x10)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA addr-phy err");
                        setLED(ui->labFPGALEDBoard8, 3, 16);
                    }
                    if(vci[0].Data[7] & 0x20)
                    {
                        ui->textBrowsererrlog->append(currentTime + "FPGA system err");
                        setLED(ui->labFPGALEDBoard8, 3, 16);
                    }
                }

            }
        }
        if(vci[0].Data[0] == 0x02)//DSP IDOG应答
        {
            qDebug()<<"DSP IDOG"<<endl;
            setLED(ui->labDSPLEDBoard8, 2, 16);
        }
    }
}

void MainWindow::initUi()
{
    this->setWindowTitle("MDSP-CAN Tool V1.0");
    this->statusBar()->showMessage("CAN host is not started");

    ui->horizontalSliderOsdAlphaBoard1->setMinimum(0);
    ui->horizontalSliderOsdAlphaBoard2->setMinimum(0);
    ui->horizontalSliderOsdAlphaBoard3->setMinimum(0);
    ui->horizontalSliderOsdAlphaBoard4->setMinimum(0);
    ui->horizontalSliderOsdAlphaBoard5->setMinimum(0);
    ui->horizontalSliderOsdAlphaBoard6->setMinimum(0);
    ui->horizontalSliderOsdAlphaBoard7->setMinimum(0);
    ui->horizontalSliderOsdAlphaBoard8->setMinimum(0);

    ui->horizontalSliderOsdAlphaBoard1->setMaximum(255);
    ui->horizontalSliderOsdAlphaBoard2->setMaximum(255);
    ui->horizontalSliderOsdAlphaBoard3->setMaximum(255);
    ui->horizontalSliderOsdAlphaBoard4->setMaximum(255);
    ui->horizontalSliderOsdAlphaBoard5->setMaximum(255);
    ui->horizontalSliderOsdAlphaBoard6->setMaximum(255);
    ui->horizontalSliderOsdAlphaBoard7->setMaximum(255);
    ui->horizontalSliderOsdAlphaBoard8->setMaximum(255);

    ui->horizontalSliderOsdAlphaBoard1->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdAlphaBoard2->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdAlphaBoard3->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdAlphaBoard4->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdAlphaBoard5->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdAlphaBoard6->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdAlphaBoard7->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdAlphaBoard8->setSingleStep(1);  // 步长

    ui->spinBoxOsdAlphaBoard1->setMinimum(0);
    ui->spinBoxOsdAlphaBoard2->setMinimum(0);
    ui->spinBoxOsdAlphaBoard3->setMinimum(0);
    ui->spinBoxOsdAlphaBoard4->setMinimum(0);
    ui->spinBoxOsdAlphaBoard5->setMinimum(0);
    ui->spinBoxOsdAlphaBoard6->setMinimum(0);
    ui->spinBoxOsdAlphaBoard7->setMinimum(0);
    ui->spinBoxOsdAlphaBoard8->setMinimum(0);


    ui->spinBoxOsdAlphaBoard1->setMaximum(255);
    ui->spinBoxOsdAlphaBoard2->setMaximum(255);
    ui->spinBoxOsdAlphaBoard3->setMaximum(255);
    ui->spinBoxOsdAlphaBoard4->setMaximum(255);
    ui->spinBoxOsdAlphaBoard5->setMaximum(255);
    ui->spinBoxOsdAlphaBoard6->setMaximum(255);
    ui->spinBoxOsdAlphaBoard7->setMaximum(255);
    ui->spinBoxOsdAlphaBoard8->setMaximum(255);


    ui->horizontalSliderOsdStartXBoard1->setMinimum(0);
    ui->horizontalSliderOsdStartXBoard2->setMinimum(0);
    ui->horizontalSliderOsdStartXBoard3->setMinimum(0);
    ui->horizontalSliderOsdStartXBoard4->setMinimum(0);
    ui->horizontalSliderOsdStartXBoard5->setMinimum(0);
    ui->horizontalSliderOsdStartXBoard6->setMinimum(0);
    ui->horizontalSliderOsdStartXBoard7->setMinimum(0);
    ui->horizontalSliderOsdStartXBoard8->setMinimum(0);

    ui->horizontalSliderOsdStartXBoard1->setMaximum(1919);
    ui->horizontalSliderOsdStartXBoard2->setMaximum(1919);
    ui->horizontalSliderOsdStartXBoard3->setMaximum(1919);
    ui->horizontalSliderOsdStartXBoard4->setMaximum(1919);
    ui->horizontalSliderOsdStartXBoard5->setMaximum(1919);
    ui->horizontalSliderOsdStartXBoard6->setMaximum(1919);
    ui->horizontalSliderOsdStartXBoard7->setMaximum(1919);
    ui->horizontalSliderOsdStartXBoard8->setMaximum(1919);

    ui->horizontalSliderOsdStartXBoard1->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartXBoard2->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartXBoard3->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartXBoard4->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartXBoard5->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartXBoard6->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartXBoard7->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartXBoard8->setSingleStep(1);  // 步长

    ui->spinBoxOsdStartXBoard1->setMinimum(0);
    ui->spinBoxOsdStartXBoard2->setMinimum(0);
    ui->spinBoxOsdStartXBoard3->setMinimum(0);
    ui->spinBoxOsdStartXBoard4->setMinimum(0);
    ui->spinBoxOsdStartXBoard5->setMinimum(0);
    ui->spinBoxOsdStartXBoard6->setMinimum(0);
    ui->spinBoxOsdStartXBoard7->setMinimum(0);
    ui->spinBoxOsdStartXBoard8->setMinimum(0);

    ui->spinBoxOsdStartXBoard1->setMaximum(1919);
    ui->spinBoxOsdStartXBoard2->setMaximum(1919);
    ui->spinBoxOsdStartXBoard3->setMaximum(1919);
    ui->spinBoxOsdStartXBoard4->setMaximum(1919);
    ui->spinBoxOsdStartXBoard5->setMaximum(1919);
    ui->spinBoxOsdStartXBoard6->setMaximum(1919);
    ui->spinBoxOsdStartXBoard7->setMaximum(1919);
    ui->spinBoxOsdStartXBoard8->setMaximum(1919);

    ui->horizontalSliderOsdStartYBoard1->setMinimum(0);
    ui->horizontalSliderOsdStartYBoard2->setMinimum(0);
    ui->horizontalSliderOsdStartYBoard3->setMinimum(0);
    ui->horizontalSliderOsdStartYBoard4->setMinimum(0);
    ui->horizontalSliderOsdStartYBoard5->setMinimum(0);
    ui->horizontalSliderOsdStartYBoard6->setMinimum(0);
    ui->horizontalSliderOsdStartYBoard7->setMinimum(0);
    ui->horizontalSliderOsdStartYBoard8->setMinimum(0);

    ui->horizontalSliderOsdStartYBoard1->setMaximum(1079);
    ui->horizontalSliderOsdStartYBoard2->setMaximum(1079);
    ui->horizontalSliderOsdStartYBoard3->setMaximum(1079);
    ui->horizontalSliderOsdStartYBoard4->setMaximum(1079);
    ui->horizontalSliderOsdStartYBoard5->setMaximum(1079);
    ui->horizontalSliderOsdStartYBoard6->setMaximum(1079);
    ui->horizontalSliderOsdStartYBoard7->setMaximum(1079);
    ui->horizontalSliderOsdStartYBoard8->setMaximum(1079);

    ui->horizontalSliderOsdStartYBoard1->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartYBoard2->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartYBoard3->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartYBoard4->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartYBoard5->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartYBoard6->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartYBoard7->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdStartYBoard8->setSingleStep(1);  // 步长

    ui->spinBoxOsdStartYBoard1->setMinimum(0);
    ui->spinBoxOsdStartYBoard2->setMinimum(0);
    ui->spinBoxOsdStartYBoard3->setMinimum(0);
    ui->spinBoxOsdStartYBoard4->setMinimum(0);
    ui->spinBoxOsdStartYBoard5->setMinimum(0);
    ui->spinBoxOsdStartYBoard6->setMinimum(0);
    ui->spinBoxOsdStartYBoard7->setMinimum(0);
    ui->spinBoxOsdStartYBoard8->setMinimum(0);

    ui->spinBoxOsdStartYBoard1->setMaximum(1079);
    ui->spinBoxOsdStartYBoard2->setMaximum(1079);
    ui->spinBoxOsdStartYBoard3->setMaximum(1079);
    ui->spinBoxOsdStartYBoard4->setMaximum(1079);
    ui->spinBoxOsdStartYBoard5->setMaximum(1079);
    ui->spinBoxOsdStartYBoard6->setMaximum(1079);
    ui->spinBoxOsdStartYBoard7->setMaximum(1079);
    ui->spinBoxOsdStartYBoard8->setMaximum(1079);

    ui->horizontalSliderOsdWidthBoard1->setMinimum(1);
    ui->horizontalSliderOsdWidthBoard2->setMinimum(1);
    ui->horizontalSliderOsdWidthBoard3->setMinimum(1);
    ui->horizontalSliderOsdWidthBoard4->setMinimum(1);
    ui->horizontalSliderOsdWidthBoard5->setMinimum(1);
    ui->horizontalSliderOsdWidthBoard6->setMinimum(1);
    ui->horizontalSliderOsdWidthBoard7->setMinimum(1);
    ui->horizontalSliderOsdWidthBoard8->setMinimum(1);

    ui->horizontalSliderOsdWidthBoard1->setMaximum(1920);
    ui->horizontalSliderOsdWidthBoard2->setMaximum(1920);
    ui->horizontalSliderOsdWidthBoard3->setMaximum(1920);
    ui->horizontalSliderOsdWidthBoard4->setMaximum(1920);
    ui->horizontalSliderOsdWidthBoard5->setMaximum(1920);
    ui->horizontalSliderOsdWidthBoard6->setMaximum(1920);
    ui->horizontalSliderOsdWidthBoard7->setMaximum(1920);
    ui->horizontalSliderOsdWidthBoard8->setMaximum(1920);

    ui->horizontalSliderOsdWidthBoard1->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdWidthBoard2->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdWidthBoard3->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdWidthBoard4->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdWidthBoard5->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdWidthBoard6->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdWidthBoard7->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdWidthBoard8->setSingleStep(1);  // 步长

    ui->spinBoxOsdWidthBoard1->setMinimum(0);
    ui->spinBoxOsdWidthBoard2->setMinimum(0);
    ui->spinBoxOsdWidthBoard3->setMinimum(0);
    ui->spinBoxOsdWidthBoard4->setMinimum(0);
    ui->spinBoxOsdWidthBoard5->setMinimum(0);
    ui->spinBoxOsdWidthBoard6->setMinimum(0);
    ui->spinBoxOsdWidthBoard7->setMinimum(0);
    ui->spinBoxOsdWidthBoard8->setMinimum(0);

    ui->spinBoxOsdWidthBoard1->setMaximum(1920);
    ui->spinBoxOsdWidthBoard2->setMaximum(1920);
    ui->spinBoxOsdWidthBoard3->setMaximum(1920);
    ui->spinBoxOsdWidthBoard4->setMaximum(1920);
    ui->spinBoxOsdWidthBoard5->setMaximum(1920);
    ui->spinBoxOsdWidthBoard6->setMaximum(1920);
    ui->spinBoxOsdWidthBoard7->setMaximum(1920);
    ui->spinBoxOsdWidthBoard8->setMaximum(1920);

    ui->horizontalSliderOsdHeightBoard1->setMinimum(1);
    ui->horizontalSliderOsdHeightBoard2->setMinimum(1);
    ui->horizontalSliderOsdHeightBoard3->setMinimum(1);
    ui->horizontalSliderOsdHeightBoard4->setMinimum(1);
    ui->horizontalSliderOsdHeightBoard5->setMinimum(1);
    ui->horizontalSliderOsdHeightBoard6->setMinimum(1);
    ui->horizontalSliderOsdHeightBoard7->setMinimum(1);
    ui->horizontalSliderOsdHeightBoard8->setMinimum(1);


    ui->horizontalSliderOsdHeightBoard1->setMaximum(1080);
    ui->horizontalSliderOsdHeightBoard2->setMaximum(1080);
    ui->horizontalSliderOsdHeightBoard3->setMaximum(1080);
    ui->horizontalSliderOsdHeightBoard4->setMaximum(1080);
    ui->horizontalSliderOsdHeightBoard5->setMaximum(1080);
    ui->horizontalSliderOsdHeightBoard6->setMaximum(1080);
    ui->horizontalSliderOsdHeightBoard7->setMaximum(1080);
    ui->horizontalSliderOsdHeightBoard8->setMaximum(1080);

    ui->horizontalSliderOsdHeightBoard1->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdHeightBoard2->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdHeightBoard3->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdHeightBoard4->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdHeightBoard5->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdHeightBoard6->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdHeightBoard7->setSingleStep(1);  // 步长
    ui->horizontalSliderOsdHeightBoard8->setSingleStep(1);  // 步长

    ui->spinBoxOsdHeightBoard1->setMinimum(1);
    ui->spinBoxOsdHeightBoard2->setMinimum(1);
    ui->spinBoxOsdHeightBoard3->setMinimum(1);
    ui->spinBoxOsdHeightBoard4->setMinimum(1);
    ui->spinBoxOsdHeightBoard5->setMinimum(1);
    ui->spinBoxOsdHeightBoard6->setMinimum(1);
    ui->spinBoxOsdHeightBoard7->setMinimum(1);
    ui->spinBoxOsdHeightBoard8->setMinimum(1);


    ui->spinBoxOsdHeightBoard1->setMaximum(1080);
    ui->spinBoxOsdHeightBoard2->setMaximum(1080);
    ui->spinBoxOsdHeightBoard3->setMaximum(1080);
    ui->spinBoxOsdHeightBoard4->setMaximum(1080);
    ui->spinBoxOsdHeightBoard5->setMaximum(1080);
    ui->spinBoxOsdHeightBoard6->setMaximum(1080);
    ui->spinBoxOsdHeightBoard7->setMaximum(1080);
    ui->spinBoxOsdHeightBoard8->setMaximum(1080);

    ui->chartViewCurrentBoard1->chart->setTitle("Board1 Current (A)");
    ui->chartViewCurrentBoard2->chart->setTitle("Board2 Current (A)");
    ui->chartViewCurrentBoard3->chart->setTitle("Board3 Current (A)");
    ui->chartViewCurrentBoard4->chart->setTitle("Board4 Current (A)");
    ui->chartViewCurrentBoard5->chart->setTitle("Board5 Current (A)");
    ui->chartViewCurrentBoard6->chart->setTitle("Board6 Current (A)");
    ui->chartViewCurrentBoard7->chart->setTitle("Board7 Current (A)");
    ui->chartViewCurrentBoard8->chart->setTitle("Board8 Current (A)");

    ui->chartView12VBoard1->chart->setTitle("Board1 Voltage 12V (V)");
    ui->chartView12VBoard2->chart->setTitle("Board2 Voltage 12V (V)");
    ui->chartView12VBoard3->chart->setTitle("Board3 Voltage 12V (V)");
    ui->chartView12VBoard4->chart->setTitle("Board4 Voltage 12V (V)");
    ui->chartView12VBoard5->chart->setTitle("Board5 Voltage 12V (V)");
    ui->chartView12VBoard6->chart->setTitle("Board6 Voltage 12V (V)");
    ui->chartView12VBoard7->chart->setTitle("Board7 Voltage 12V (V)");
    ui->chartView12VBoard8->chart->setTitle("Board8 Voltage 12V (V)");


    ui->chartView5VBoard1->chart->setTitle("Board1 Voltage 5V (V)");
    ui->chartView5VBoard2->chart->setTitle("Board2 Voltage 5V (V)");
    ui->chartView5VBoard3->chart->setTitle("Board3 Voltage 5V (V)");
    ui->chartView5VBoard4->chart->setTitle("Board4 Voltage 5V (V)");
    ui->chartView5VBoard5->chart->setTitle("Board5 Voltage 5V (V)");
    ui->chartView5VBoard6->chart->setTitle("Board6 Voltage 5V (V)");
    ui->chartView5VBoard7->chart->setTitle("Board7 Voltage 5V (V)");
    ui->chartView5VBoard8->chart->setTitle("Board8 Voltage 5V (V)");



    ui->chartViewCavityTempBoard1->chart->setTitle("Board1 CavityTemp (℃)");
    ui->chartViewCavityTempBoard2->chart->setTitle("Board2 CavityTemp (℃)");
    ui->chartViewCavityTempBoard3->chart->setTitle("Board3 CavityTemp (℃)");
    ui->chartViewCavityTempBoard4->chart->setTitle("Board4 CavityTemp (℃)");
    ui->chartViewCavityTempBoard5->chart->setTitle("Board5 CavityTemp (℃)");
    ui->chartViewCavityTempBoard6->chart->setTitle("Board6 CavityTemp (℃)");
    ui->chartViewCavityTempBoard7->chart->setTitle("Board7 CavityTemp (℃)");
    ui->chartViewCavityTempBoard8->chart->setTitle("Board8 CavityTemp (℃)");


    ui->chartViewFpgaTempBoard1->chart->setTitle("Board1 FPGA Temp (℃)");
    ui->chartViewFpgaTempBoard2->chart->setTitle("Board2 FPGA Temp (℃)");
    ui->chartViewFpgaTempBoard3->chart->setTitle("Board3 FPGA Temp (℃)");
    ui->chartViewFpgaTempBoard4->chart->setTitle("Board4 FPGA Temp (℃)");
    ui->chartViewFpgaTempBoard5->chart->setTitle("Board5 FPGA Temp (℃)");
    ui->chartViewFpgaTempBoard6->chart->setTitle("Board6 FPGA Temp (℃)");
    ui->chartViewFpgaTempBoard7->chart->setTitle("Board7 FPGA Temp (℃)");
    ui->chartViewFpgaTempBoard8->chart->setTitle("Board8 FPGA Temp (℃)");



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

    ui->lineEditUpgradeAddr->setValidator(aIntValidator);  //更新设备地址只能输入 0 - 8





   // chart->setTitle("Current (A)");
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

    ui->pushButtonUpgradeAddrSet->setEnabled(false); // 关闭读地址功能
    ui->pushButtonUpgradeAddrRead->setEnabled(false);// 关闭设置地址功能

    ui->btnUpdate_2->setEnabled(false);  //关闭升级按钮
    ui->btnUpdate_3->setEnabled(false);  //关闭升级按钮

    setLED(ui->labMCULEDBoard1, 0, 16);
    setLED(ui->labMCULEDBoard2, 0, 16);
    setLED(ui->labMCULEDBoard3, 0, 16);
    setLED(ui->labMCULEDBoard4, 0, 16);
    setLED(ui->labMCULEDBoard5, 0, 16);
    setLED(ui->labMCULEDBoard6, 0, 16);
    setLED(ui->labMCULEDBoard7, 0, 16);
    setLED(ui->labMCULEDBoard8, 0, 16);

    setLED(ui->labFPGALEDBoard1, 0, 16);
    setLED(ui->labFPGALEDBoard2, 0, 16);
    setLED(ui->labFPGALEDBoard3, 0, 16);
    setLED(ui->labFPGALEDBoard4, 0, 16);
    setLED(ui->labFPGALEDBoard5, 0, 16);
    setLED(ui->labFPGALEDBoard6, 0, 16);
    setLED(ui->labFPGALEDBoard7, 0, 16);
    setLED(ui->labFPGALEDBoard8, 0, 16);


    setLED(ui->labDSPLEDBoard1, 0, 16);
    setLED(ui->labDSPLEDBoard2, 0, 16);
    setLED(ui->labDSPLEDBoard3, 0, 16);
    setLED(ui->labDSPLEDBoard4, 0, 16);
    setLED(ui->labDSPLEDBoard5, 0, 16);
    setLED(ui->labDSPLEDBoard6, 0, 16);
    setLED(ui->labDSPLEDBoard7, 0, 16);
    setLED(ui->labDSPLEDBoard8, 0, 16);


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
    ui->labelOverly->pixIN1DetectionBoard[0].load(":/images/a1.png");
    ui->labelOverly->pixIN2DetectionBoard[0].load(":/images/a2.png");
    ui->labelOverly->pixIN1LVDSinBoard[0].load(":/images/l1.png");
    ui->labelOverly->pixIN2LVDSinBoard[0].load(":/images/l2.png");
    ui->labelOverly->pixColorBoard[0].load(":/images/col1.png");

    ui->labelOverly->pix3GIN1Board[1].load(":/images/3.png");
    ui->labelOverly->pix3GIN2Board[1].load(":/images/4.png");
    ui->labelOverly->pixIN1DetectionBoard[1].load(":/images/a3.png");
    ui->labelOverly->pixIN2DetectionBoard[1].load(":/images/a4.png");
    ui->labelOverly->pixIN1LVDSinBoard[1].load(":/images/l3.png");
    ui->labelOverly->pixIN2LVDSinBoard[1].load(":/images/l4.png");
    ui->labelOverly->pixColorBoard[1].load(":/images/col2.png");

    ui->labelOverly->pix3GIN1Board[2].load(":/images/5.png");
    ui->labelOverly->pix3GIN2Board[2].load(":/images/6.png");
    ui->labelOverly->pixIN1DetectionBoard[2].load(":/images/a5.png");
    ui->labelOverly->pixIN2DetectionBoard[2].load(":/images/a6.png");
    ui->labelOverly->pixIN1LVDSinBoard[2].load(":/images/l5.png");
    ui->labelOverly->pixIN2LVDSinBoard[2].load(":/images/l6.png");
    ui->labelOverly->pixColorBoard[2].load(":/images/col3.png");
;
    ui->labelOverly->pix3GIN1Board[3].load(":/images/7.png");
    ui->labelOverly->pix3GIN2Board[3].load(":/images/8.png");
    ui->labelOverly->pixIN1DetectionBoard[3].load(":/images/a7.png");
    ui->labelOverly->pixIN2DetectionBoard[3].load(":/images/a8.png");
    ui->labelOverly->pixIN1LVDSinBoard[3].load(":/images/l7.png");
    ui->labelOverly->pixIN2LVDSinBoard[3].load(":/images/l8.png");
    ui->labelOverly->pixColorBoard[3].load(":/images/col4.png");

    ui->labelOverly->pix3GIN1Board[4].load(":/images/9.png");
    ui->labelOverly->pix3GIN2Board[4].load(":/images/10.png");
    ui->labelOverly->pixIN1DetectionBoard[4].load(":/images/a9.png");
    ui->labelOverly->pixIN2DetectionBoard[4].load(":/images/a10.png");
    ui->labelOverly->pixIN1LVDSinBoard[4].load(":/images/l9.png");
    ui->labelOverly->pixIN2LVDSinBoard[4].load(":/images/l10.png");
    ui->labelOverly->pixColorBoard4.load(":/images/col5.png");

    ui->labelOverly->pix3GIN1Board[5].load(":/images/11.png");
    ui->labelOverly->pix3GIN2Board[5].load(":/images/12.png");
    ui->labelOverly->pixIN1DetectionBoard[5].load(":/images/a11.png");
    ui->labelOverly->pixIN2DetectionBoard[5].load(":/images/a12.png");
    ui->labelOverly->pixIN1LVDSinBoard[5].load(":/images/l11.png");
    ui->labelOverly->pixIN2LVDSinBoard[5].load(":/images/l12.png");
    ui->labelOverly->pixColorBoard[5].load(":/images/col6.png");

    ui->labelOverly->pix3GIN1Board[6].load(":/images/13.png");
    ui->labelOverly->pix3GIN2Board[6].load(":/images/14.png");
    ui->labelOverly->pixIN1DetectionBoard[6].load(":/images/a13.png");
    ui->labelOverly->pixIN2DetectionBoard[6].load(":/images/a14.png");
    ui->labelOverly->pixIN1LVDSinBoard[6].load(":/images/l13.png");
    ui->labelOverly->pixIN2LVDSinBoard[6].load(":/images/l14.png");
    ui->labelOverly->pixColorBoard[6].load(":/images/col7.png");

    ui->labelOverly->pix3GIN1Board[7].load(":/images/15.png");
    ui->labelOverly->pix3GIN2Board[7].load(":/images/16.png");
    ui->labelOverly->pixIN1DetectionBoard[7].load(":/images/a15.png");
    ui->labelOverly->pixIN2DetectionBoard[7].load(":/images/a16.png");
    ui->labelOverly->pixIN1LVDSinBoard[7].load(":/images/l15.png");
    ui->labelOverly->pixIN2LVDSinBoard[7].load(":/images/l16.png");
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



    connect(ui->spinBoxOsdStartXBoard1, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartXBoard1, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartXBoard2, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartXBoard2, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartXBoard3, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartXBoard3, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartXBoard4, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartXBoard4, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartXBoard5, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartXBoard5, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartXBoard6, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartXBoard6, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartXBoard7, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartXBoard7, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartXBoard8, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartXBoard8, SLOT(setValue(int)));


    connect(ui->horizontalSliderOsdStartXBoard1, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartXBoard1, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartXBoard2, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartXBoard2, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartXBoard3, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartXBoard3, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartXBoard4, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartXBoard4, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartXBoard5, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartXBoard5, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartXBoard6, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartXBoard6, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartXBoard7, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartXBoard7, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartXBoard8, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartXBoard8, SLOT(setValue(int)));

    connect(ui->spinBoxOsdStartYBoard1, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartYBoard1, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartYBoard2, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartYBoard2, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartYBoard3, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartYBoard3, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartYBoard4, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartYBoard4, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartYBoard5, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartYBoard5, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartYBoard6, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartYBoard6, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartYBoard7, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartYBoard7, SLOT(setValue(int)));
    connect(ui->spinBoxOsdStartYBoard8, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdStartYBoard8, SLOT(setValue(int)));



    connect(ui->horizontalSliderOsdStartYBoard1, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartYBoard1, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartYBoard2, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartYBoard2, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartYBoard3, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartYBoard3, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartYBoard4, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartYBoard4, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartYBoard5, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartYBoard5, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartYBoard6, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartYBoard6, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartYBoard7, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartYBoard7, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdStartYBoard8, SIGNAL(valueChanged(int)), ui->spinBoxOsdStartYBoard8, SLOT(setValue(int)));

    connect(ui->spinBoxOsdWidthBoard1, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdWidthBoard1, SLOT(setValue(int)));
    connect(ui->spinBoxOsdWidthBoard2, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdWidthBoard2, SLOT(setValue(int)));
    connect(ui->spinBoxOsdWidthBoard3, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdWidthBoard3, SLOT(setValue(int)));
    connect(ui->spinBoxOsdWidthBoard4, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdWidthBoard4, SLOT(setValue(int)));
    connect(ui->spinBoxOsdWidthBoard5, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdWidthBoard5, SLOT(setValue(int)));
    connect(ui->spinBoxOsdWidthBoard6, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdWidthBoard6, SLOT(setValue(int)));
    connect(ui->spinBoxOsdWidthBoard7, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdWidthBoard7, SLOT(setValue(int)));
    connect(ui->spinBoxOsdWidthBoard8, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdWidthBoard8, SLOT(setValue(int)));



    connect(ui->horizontalSliderOsdWidthBoard1, SIGNAL(valueChanged(int)), ui->spinBoxOsdWidthBoard1, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdWidthBoard2, SIGNAL(valueChanged(int)), ui->spinBoxOsdWidthBoard2, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdWidthBoard3, SIGNAL(valueChanged(int)), ui->spinBoxOsdWidthBoard3, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdWidthBoard4, SIGNAL(valueChanged(int)), ui->spinBoxOsdWidthBoard4, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdWidthBoard5, SIGNAL(valueChanged(int)), ui->spinBoxOsdWidthBoard5, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdWidthBoard6, SIGNAL(valueChanged(int)), ui->spinBoxOsdWidthBoard6, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdWidthBoard7, SIGNAL(valueChanged(int)), ui->spinBoxOsdWidthBoard7, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdWidthBoard8, SIGNAL(valueChanged(int)), ui->spinBoxOsdWidthBoard8, SLOT(setValue(int)));

    connect(ui->spinBoxOsdHeightBoard1, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdHeightBoard1, SLOT(setValue(int)));
    connect(ui->spinBoxOsdHeightBoard2, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdHeightBoard2, SLOT(setValue(int)));
    connect(ui->spinBoxOsdHeightBoard3, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdHeightBoard3, SLOT(setValue(int)));
    connect(ui->spinBoxOsdHeightBoard4, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdHeightBoard4, SLOT(setValue(int)));
    connect(ui->spinBoxOsdHeightBoard5, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdHeightBoard5, SLOT(setValue(int)));
    connect(ui->spinBoxOsdHeightBoard6, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdHeightBoard6, SLOT(setValue(int)));
    connect(ui->spinBoxOsdHeightBoard7, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdHeightBoard7, SLOT(setValue(int)));
    connect(ui->spinBoxOsdHeightBoard8, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdHeightBoard8, SLOT(setValue(int)));


    connect(ui->horizontalSliderOsdHeightBoard1, SIGNAL(valueChanged(int)), ui->spinBoxOsdHeightBoard1, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdHeightBoard2, SIGNAL(valueChanged(int)), ui->spinBoxOsdHeightBoard2, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdHeightBoard3, SIGNAL(valueChanged(int)), ui->spinBoxOsdHeightBoard3, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdHeightBoard4, SIGNAL(valueChanged(int)), ui->spinBoxOsdHeightBoard4, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdHeightBoard5, SIGNAL(valueChanged(int)), ui->spinBoxOsdHeightBoard5, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdHeightBoard6, SIGNAL(valueChanged(int)), ui->spinBoxOsdHeightBoard6, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdHeightBoard7, SIGNAL(valueChanged(int)), ui->spinBoxOsdHeightBoard7, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdHeightBoard8, SIGNAL(valueChanged(int)), ui->spinBoxOsdHeightBoard8, SLOT(setValue(int)));

    connect(ui->spinBoxOsdAlphaBoard1, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdAlphaBoard1, SLOT(setValue(int)));
    connect(ui->spinBoxOsdAlphaBoard2, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdAlphaBoard2, SLOT(setValue(int)));
    connect(ui->spinBoxOsdAlphaBoard3, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdAlphaBoard3, SLOT(setValue(int)));
    connect(ui->spinBoxOsdAlphaBoard4, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdAlphaBoard4, SLOT(setValue(int)));
    connect(ui->spinBoxOsdAlphaBoard5, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdAlphaBoard5, SLOT(setValue(int)));
    connect(ui->spinBoxOsdAlphaBoard6, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdAlphaBoard6, SLOT(setValue(int)));
    connect(ui->spinBoxOsdAlphaBoard7, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdAlphaBoard7, SLOT(setValue(int)));
    connect(ui->spinBoxOsdAlphaBoard8, SIGNAL(valueChanged(int)), ui->horizontalSliderOsdAlphaBoard8, SLOT(setValue(int)));

    connect(ui->horizontalSliderOsdAlphaBoard1, SIGNAL(valueChanged(int)), ui->spinBoxOsdAlphaBoard1, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdAlphaBoard2, SIGNAL(valueChanged(int)), ui->spinBoxOsdAlphaBoard2, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdAlphaBoard3, SIGNAL(valueChanged(int)), ui->spinBoxOsdAlphaBoard3, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdAlphaBoard4, SIGNAL(valueChanged(int)), ui->spinBoxOsdAlphaBoard4, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdAlphaBoard5, SIGNAL(valueChanged(int)), ui->spinBoxOsdAlphaBoard5, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdAlphaBoard6, SIGNAL(valueChanged(int)), ui->spinBoxOsdAlphaBoard6, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdAlphaBoard7, SIGNAL(valueChanged(int)), ui->spinBoxOsdAlphaBoard7, SLOT(setValue(int)));
    connect(ui->horizontalSliderOsdAlphaBoard8, SIGNAL(valueChanged(int)), ui->spinBoxOsdAlphaBoard8, SLOT(setValue(int)));

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

    int ID = (PGN57856 << 8) + this->board2->writerAddr;  //写FPGA命令


    //先发送显示格式  显示16画  或者IN1 4K 或者IN2 4K
    unsigned char send_str[8] = {0};
    quint64 regaddr = ui->labelImgBoard2->displayModeRegAddr;
    quint64 regdata = ui->labelImgBoard2->displayModeReg;
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
    regaddr = ui->labelImgBoard2->img3GIn1SizeRegAddr;
    regdata = ui->labelImgBoard2->img3GIn1SizeReg;
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
    regaddr = ui->labelImgBoard2->img3GIn2SizeRegAddr;
    regdata = ui->labelImgBoard2->img3GIn2SizeReg;
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

void MainWindow::writeBoard3FpgaImgconfigReg(unsigned int *regTable)
{

    int ID = (PGN57856 << 8) + this->board3->writerAddr;  //写FPGA命令


    //先发送显示格式  显示16画  或者IN1 4K 或者IN2 4K
    unsigned char send_str[8] = {0};
    quint64 regaddr = ui->labelImgBoard3->displayModeRegAddr;
    quint64 regdata = ui->labelImgBoard3->displayModeReg;
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
    regaddr = ui->labelImgBoard3->img3GIn1SizeRegAddr;
    regdata = ui->labelImgBoard3->img3GIn1SizeReg;
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
    regaddr = ui->labelImgBoard3->img3GIn2SizeRegAddr;
    regdata = ui->labelImgBoard3->img3GIn2SizeReg;
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


void MainWindow::writeBoard4FpgaImgconfigReg(unsigned int *regTable)
{

    int ID = (PGN57856 << 8) + this->board4->writerAddr;  //写FPGA命令


    //先发送显示格式  显示16画  或者IN1 4K 或者IN2 4K
    unsigned char send_str[8] = {0};
    quint64 regaddr = ui->labelImgBoard4->displayModeRegAddr;
    quint64 regdata = ui->labelImgBoard4->displayModeReg;
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
    regaddr = ui->labelImgBoard4->img3GIn1SizeRegAddr;
    regdata = ui->labelImgBoard4->img3GIn1SizeReg;
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
    regaddr = ui->labelImgBoard4->img3GIn2SizeRegAddr;
    regdata = ui->labelImgBoard4->img3GIn2SizeReg;
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


void MainWindow::writeBoard5FpgaImgconfigReg(unsigned int *regTable)
{

    int ID = (PGN57856 << 8) + this->board5->writerAddr;  //写FPGA命令


    //先发送显示格式  显示16画  或者IN1 4K 或者IN2 4K
    unsigned char send_str[8] = {0};
    quint64 regaddr = ui->labelImgBoard5->displayModeRegAddr;
    quint64 regdata = ui->labelImgBoard5->displayModeReg;
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
    regaddr = ui->labelImgBoard5->img3GIn1SizeRegAddr;
    regdata = ui->labelImgBoard5->img3GIn1SizeReg;
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
    regaddr = ui->labelImgBoard5->img3GIn2SizeRegAddr;
    regdata = ui->labelImgBoard5->img3GIn2SizeReg;
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

void MainWindow::writeBoard6FpgaImgconfigReg(unsigned int *regTable)
{

    int ID = (PGN57856 << 8) + this->board6->writerAddr;  //写FPGA命令


    //先发送显示格式  显示16画  或者IN1 4K 或者IN2 4K
    unsigned char send_str[8] = {0};
    quint64 regaddr = ui->labelImgBoard6->displayModeRegAddr;
    quint64 regdata = ui->labelImgBoard6->displayModeReg;
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
    regaddr = ui->labelImgBoard6->img3GIn1SizeRegAddr;
    regdata = ui->labelImgBoard6->img3GIn1SizeReg;
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
    regaddr = ui->labelImgBoard6->img3GIn2SizeRegAddr;
    regdata = ui->labelImgBoard6->img3GIn2SizeReg;
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

void MainWindow::writeBoard7FpgaImgconfigReg(unsigned int *regTable)
{

    int ID = (PGN57856 << 8) + this->board7->writerAddr;  //写FPGA命令


    //先发送显示格式  显示16画  或者IN1 4K 或者IN2 4K
    unsigned char send_str[8] = {0};
    quint64 regaddr = ui->labelImgBoard7->displayModeRegAddr;
    quint64 regdata = ui->labelImgBoard7->displayModeReg;
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
    regaddr = ui->labelImgBoard7->img3GIn1SizeRegAddr;
    regdata = ui->labelImgBoard7->img3GIn1SizeReg;
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
    regaddr = ui->labelImgBoard7->img3GIn2SizeRegAddr;
    regdata = ui->labelImgBoard7->img3GIn2SizeReg;
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

void MainWindow::writeBoard8FpgaImgconfigReg(unsigned int *regTable)
{

    int ID = (PGN57856 << 8) + this->board8->writerAddr;  //写FPGA命令


    //先发送显示格式  显示16画  或者IN1 4K 或者IN2 4K
    unsigned char send_str[8] = {0};
    quint64 regaddr = ui->labelImgBoard8->displayModeRegAddr;
    quint64 regdata = ui->labelImgBoard8->displayModeReg;
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
    regaddr = ui->labelImgBoard8->img3GIn1SizeRegAddr;
    regdata = ui->labelImgBoard8->img3GIn1SizeReg;
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
    regaddr = ui->labelImgBoard8->img3GIn2SizeRegAddr;
    regdata = ui->labelImgBoard8->img3GIn2SizeReg;
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
    ui->pushButtonUpgradeAddrSet->setEnabled(false);
    ui->pushButtonUpgradeAddrRead->setEnabled(false);

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
    ui->pushButtonUpgradeAddrSet->setEnabled(false);
    ui->pushButtonUpgradeAddrRead->setEnabled(false);

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

    ui->pushButtonUpgradeAddrSet->setEnabled(false);
    ui->pushButtonUpgradeAddrRead->setEnabled(false);

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
    ui->pushButtonUpgradeAddrSet->setEnabled(false);
    ui->pushButtonUpgradeAddrRead->setEnabled(false);

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
    ui->pushButtonUpgradeAddrSet->setEnabled(false);
    ui->pushButtonUpgradeAddrRead->setEnabled(false);

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
    else if (index == 4)
    {
        ui->labelImgBoard1->ImgType = IMG_LVDS_IN;
    }
    else
    {
        ui->labelImgBoard1->ImgType = INPUT_SIZE_1920X1080;
    }
}


void MainWindow::on_pushButtonImgClearBoard1_clicked()
{

    ui->labelImgBoard1->resetRegData1();
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
    ui->labelImgBoard2->resetRegData();
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
    ui->labelImgBoard3->resetRegData();
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
    ui->labelImgBoard4->resetRegData();
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
    ui->labelImgBoard5->resetRegData();
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
    ui->labelImgBoard6->resetRegData();
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
    ui->labelImgBoard7->resetRegData();
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
    ui->labelImgBoard8->resetRegData();
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








void MainWindow::on_btnUpdateMode_4_clicked()
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
    ui->btnUpdate_3->setEnabled(false);  //关闭升级按钮
    ui->pushButtonUpgradeAddrSet->setEnabled(true);
    ui->pushButtonUpgradeAddrRead->setEnabled(true);

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
    this->statusBar()->showMessage("Mode: Upgrade - Board Addr");
}

void MainWindow::on_pushButtonUpgradeAddrRead_clicked()
{
    int ID = 0;
    unsigned char send_str[8] = {0};
    send_str[6] = 0x00;  //读
    send_str[7] = 0x00;  //


    ID = (PGN60672 << 8) + this->board1->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board2->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board3->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board4->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board5->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board6->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board7->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board8->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_pushButtonUpgradeAddrSet_clicked()
{
    int ID = 0;
    unsigned char send_str[8] = {0};
    send_str[6] = 0x01;  //写
    bool ok;
    quint64 boardaddr = ui->lineEditUpgradeAddr->text().toULongLong(&ok,16);
    send_str[7] = boardaddr;

    ID = (PGN60672 << 8) + this->board1->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board2->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board3->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board4->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board5->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board6->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board7->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
    ID = (PGN60672 << 8) + this->board8->writerAddr;  //工作模式切换命令
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_pushButtonOpenOsdBoard1_clicked()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board1->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0030;
    quint64 regdata = 0;
    if(ui->pushButtonOpenOsdBoard1->text() == tr("Open"))
    {
        regdata = 1;
        ui->pushButtonOpenOsdBoard1->setText(tr("Close"));
    }
    else if(ui->pushButtonOpenOsdBoard1->text() == tr("Close"))
    {
        regdata = 0;
        ui->pushButtonOpenOsdBoard1->setText(tr("Open"));
    }
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_horizontalSliderOsdStartXBoard1_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board1->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0034;
    quint64 regdata = ui->spinBoxOsdStartXBoard1->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);

}

void MainWindow::on_horizontalSliderOsdStartYBoard1_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board1->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0035;
    quint64 regdata = ui->spinBoxOsdStartYBoard1->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdWidthBoard1_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board1->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0032;
    quint64 regdata = ui->spinBoxOsdWidthBoard1->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdHeightBoard1_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board1->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0033;
    quint64 regdata = ui->spinBoxOsdHeightBoard1->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdAlphaBoard1_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board1->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0036;
    quint64 regdata = ui->spinBoxOsdAlphaBoard1->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_pushButtonOpenOsdBoard2_clicked()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board2->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0030;
    quint64 regdata = 0;
    if(ui->pushButtonOpenOsdBoard2->text() == tr("Open"))
    {
        regdata = 1;
        ui->pushButtonOpenOsdBoard2->setText(tr("Close"));
    }
    else if(ui->pushButtonOpenOsdBoard2->text() == tr("Close"))
    {
        regdata = 0;
        ui->pushButtonOpenOsdBoard2->setText(tr("Open"));
    }
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_horizontalSliderOsdStartXBoard2_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board2->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0034;
    quint64 regdata = ui->spinBoxOsdStartXBoard2->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);

}

void MainWindow::on_horizontalSliderOsdStartYBoard2_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board2->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0035;
    quint64 regdata = ui->spinBoxOsdStartYBoard2->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdWidthBoard2_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board2->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0032;
    quint64 regdata = ui->spinBoxOsdWidthBoard2->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdHeightBoard2_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board2->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0033;
    quint64 regdata = ui->spinBoxOsdHeightBoard2->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdAlphaBoard2_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board2->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0036;
    quint64 regdata = ui->spinBoxOsdAlphaBoard2->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_pushButtonOpenOsdBoard3_clicked()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board3->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0030;
    quint64 regdata = 0;
    if(ui->pushButtonOpenOsdBoard3->text() == tr("Open"))
    {
        regdata = 1;
        ui->pushButtonOpenOsdBoard3->setText(tr("Close"));
    }
    else if(ui->pushButtonOpenOsdBoard3->text() == tr("Close"))
    {
        regdata = 0;
        ui->pushButtonOpenOsdBoard3->setText(tr("Open"));
    }
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_horizontalSliderOsdStartXBoard3_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board3->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0034;
    quint64 regdata = ui->spinBoxOsdStartXBoard3->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);

}

void MainWindow::on_horizontalSliderOsdStartYBoard3_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board3->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0035;
    quint64 regdata = ui->spinBoxOsdStartYBoard3->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdWidthBoard3_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board3->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0032;
    quint64 regdata = ui->spinBoxOsdWidthBoard3->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdHeightBoard3_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board3->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0033;
    quint64 regdata = ui->spinBoxOsdHeightBoard3->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdAlphaBoard3_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board3->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0036;
    quint64 regdata = ui->spinBoxOsdAlphaBoard3->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}



void MainWindow::on_pushButtonOpenOsdBoard4_clicked()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board4->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0030;
    quint64 regdata = 0;
    if(ui->pushButtonOpenOsdBoard4->text() == tr("Open"))
    {
        regdata = 1;
        ui->pushButtonOpenOsdBoard4->setText(tr("Close"));
    }
    else if(ui->pushButtonOpenOsdBoard4->text() == tr("Close"))
    {
        regdata = 0;
        ui->pushButtonOpenOsdBoard4->setText(tr("Open"));
    }
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_horizontalSliderOsdStartXBoard4_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board4->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0034;
    quint64 regdata = ui->spinBoxOsdStartXBoard4->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);

}

void MainWindow::on_horizontalSliderOsdStartYBoard4_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board4->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0035;
    quint64 regdata = ui->spinBoxOsdStartYBoard4->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdWidthBoard4_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board4->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0032;
    quint64 regdata = ui->spinBoxOsdWidthBoard4->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdHeightBoard4_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board4->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0033;
    quint64 regdata = ui->spinBoxOsdHeightBoard4->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdAlphaBoard4_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board4->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0036;
    quint64 regdata = ui->spinBoxOsdAlphaBoard4->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}



void MainWindow::on_pushButtonOpenOsdBoard5_clicked()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board5->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0030;
    quint64 regdata = 0;
    if(ui->pushButtonOpenOsdBoard5->text() == tr("Open"))
    {
        regdata = 1;
        ui->pushButtonOpenOsdBoard5->setText(tr("Close"));
    }
    else if(ui->pushButtonOpenOsdBoard5->text() == tr("Close"))
    {
        regdata = 0;
        ui->pushButtonOpenOsdBoard5->setText(tr("Open"));
    }
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_horizontalSliderOsdStartXBoard5_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board5->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0034;
    quint64 regdata = ui->spinBoxOsdStartXBoard5->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);

}

void MainWindow::on_horizontalSliderOsdStartYBoard5_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board5->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0035;
    quint64 regdata = ui->spinBoxOsdStartYBoard5->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdWidthBoard5_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board5->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0032;
    quint64 regdata = ui->spinBoxOsdWidthBoard5->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdHeightBoard5_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board5->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0033;
    quint64 regdata = ui->spinBoxOsdHeightBoard5->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdAlphaBoard5_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board5->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0036;
    quint64 regdata = ui->spinBoxOsdAlphaBoard5->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}



void MainWindow::on_pushButtonOpenOsdBoard6_clicked()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board6->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0030;
    quint64 regdata = 0;
    if(ui->pushButtonOpenOsdBoard6->text() == tr("Open"))
    {
        regdata = 1;
        ui->pushButtonOpenOsdBoard6->setText(tr("Close"));
    }
    else if(ui->pushButtonOpenOsdBoard6->text() == tr("Close"))
    {
        regdata = 0;
        ui->pushButtonOpenOsdBoard6->setText(tr("Open"));
    }
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_horizontalSliderOsdStartXBoard6_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board6->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0034;
    quint64 regdata = ui->spinBoxOsdStartXBoard6->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);

}

void MainWindow::on_horizontalSliderOsdStartYBoard6_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board6->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0035;
    quint64 regdata = ui->spinBoxOsdStartYBoard6->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdWidthBoard6_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board6->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0032;
    quint64 regdata = ui->spinBoxOsdWidthBoard6->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdHeightBoard6_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board6->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0033;
    quint64 regdata = ui->spinBoxOsdHeightBoard6->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdAlphaBoard6_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board6->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0036;
    quint64 regdata = ui->spinBoxOsdAlphaBoard6->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}



void MainWindow::on_pushButtonOpenOsdBoard7_clicked()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board7->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0030;
    quint64 regdata = 0;
    if(ui->pushButtonOpenOsdBoard7->text() == tr("Open"))
    {
        regdata = 1;
        ui->pushButtonOpenOsdBoard7->setText(tr("Close"));
    }
    else if(ui->pushButtonOpenOsdBoard7->text() == tr("Close"))
    {
        regdata = 0;
        ui->pushButtonOpenOsdBoard7->setText(tr("Open"));
    }
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_horizontalSliderOsdStartXBoard7_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board7->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0034;
    quint64 regdata = ui->spinBoxOsdStartXBoard7->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);

}

void MainWindow::on_horizontalSliderOsdStartYBoard7_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board7->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0035;
    quint64 regdata = ui->spinBoxOsdStartYBoard7->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdWidthBoard7_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board7->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0032;
    quint64 regdata = ui->spinBoxOsdWidthBoard7->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdHeightBoard7_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board7->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0033;
    quint64 regdata = ui->spinBoxOsdHeightBoard7->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdAlphaBoard7_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board7->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0036;
    quint64 regdata = ui->spinBoxOsdAlphaBoard7->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}



void MainWindow::on_pushButtonOpenOsdBoard8_clicked()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board8->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0030;
    quint64 regdata = 0;
    if(ui->pushButtonOpenOsdBoard8->text() == tr("Open"))
    {
        regdata = 1;
        ui->pushButtonOpenOsdBoard8->setText(tr("Close"));
    }
    else if(ui->pushButtonOpenOsdBoard8->text() == tr("Close"))
    {
        regdata = 0;
        ui->pushButtonOpenOsdBoard8->setText(tr("Open"));
    }
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}


void MainWindow::on_horizontalSliderOsdStartXBoard8_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board8->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0034;
    quint64 regdata = ui->spinBoxOsdStartXBoard8->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);

}

void MainWindow::on_horizontalSliderOsdStartYBoard8_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board8->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0035;
    quint64 regdata = ui->spinBoxOsdStartYBoard8->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdWidthBoard8_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board8->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0032;
    quint64 regdata = ui->spinBoxOsdWidthBoard8->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdHeightBoard8_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board8->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0033;
    quint64 regdata = ui->spinBoxOsdHeightBoard8->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}

void MainWindow::on_horizontalSliderOsdAlphaBoard8_sliderReleased()
{
    unsigned char send_str[8] = {0};
    int ID = (PGN57856 << 8) + this->board8->writerAddr;  //写FPGA命令
    quint64 regaddr = 0x0036;
    quint64 regdata = ui->spinBoxOsdAlphaBoard8->value();
    quint64 data = (regaddr<<16) + regdata;
    char *p = (char *)(&data);
    for(int i = 0; i < 8; i++)
    {
        send_str[i] = p[7 - i];
    }
    canthread->sendData(ID,(unsigned char*)send_str);
    sleep(10);
}
