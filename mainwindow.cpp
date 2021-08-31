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
    if(vci->ID == (PGN57600 << 8) + PC_SOURCE_ADDR)
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
             ui->lcdNumberCurrent->display(this->protocolHand->MDSP_Board_currents);
             ui->lcdNumberVoltage12->display(this->protocolHand->MDSP_Board_HV);
             ui->lcdNumberVoltage5->display(this->protocolHand->MDSP_Board_LV);
             ui->lcdNumberTempe->display(this->protocolHand->MDSP_Board_temperature);
         }

    }
}

void MainWindow::initUi()
{
    this->setWindowTitle("MDSP-CAN Tool V1.0");
    ui->tabWidget->setCurrentIndex(0);//设置选中第一个标签
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
    ui->tabWidget_2->tabBar()->setStyle(new SubCustomTabStyle);
    ui->tabWidget_3->tabBar()->setStyle(new SubCustomTabStyle);
    ui->tabWidget_4->tabBar()->setStyle(new SubCustomTabStyle);
    ui->tabWidget_6->tabBar()->setStyle(new SubCustomTabStyle);
    ui->lcdNumberCurrent->setDigitCount(4);
    ui->lcdNumberVoltage12->setDigitCount(4);
    ui->lcdNumberVoltage5->setDigitCount(4);
    ui->lcdNumberTempe->setDigitCount(4);
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

void MainWindow::on_btnUpdate_clicked()
{
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
    int ID = (PGN57344 << 8) + MDSP_SOURCE_ADDR;  //擦除flash 命令
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
    ID = (PGN60160 << 8) + MDSP_SOURCE_ADDR;  //写code 命令
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

void MainWindow::on_btnUpdateMode_clicked()
{
    qDebug()<<"设置工作模式";
    int ID = (PGN56468 << 8) + MDSP_SOURCE_ADDR;  //工作模式切换命令
    unsigned char send_str[8] = {0};
    send_str[7] = UPGRADEMODE;
    canthread->sendData(ID,(unsigned char*)send_str);
}



void MainWindow::on_btnMonitor_clicked()
{
    if(ui->btnMonitor->text() == tr("Open"))
    {
        ui->btnMonitor->setText(tr("Close"));
        //this->canthread->Adc_flag = true;
        this->canthread->canThreadTimer->start();


    }
    else if(ui->btnMonitor->text() == tr("Close"))
    {
        ui->btnMonitor->setText(tr("Open"));
        //this->canthread->Adc_flag = false;
        this->canthread->canThreadTimer->stop();
    }
}
