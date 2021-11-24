#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ControlCAN.h"
#include <QDebug>
#include "protocolthrend.h"
#include "canthread.h"
#include "boardinfo.h"
#include "imglabel.h"
#include <QTimer>

#include <QtCharts>

#include <QUdpSocket>
using namespace QtCharts;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    void initUi();
    void initImaLabel();
    void initSignalslots();
    void setLED(QLabel* label, int color, int size);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    CANThread *canthread;
    ProtocolThrend *protocolHand;
    QTimer *FlashWriteTimer;  //定时器
    unsigned int FlashWriteTimeSec = 0;

    QString readFlashFileName;
    QFile *file;
    boardinfo *board1;
    boardinfo *board2;
    boardinfo *board3;
    boardinfo *board4;
    boardinfo *board5;
    boardinfo *board6;
    boardinfo *board7;
    boardinfo *board8;







private slots:
    void updateOverlyImgRegArray(void);
    void writeBoard1FpgaImgconfigReg(unsigned int *regTable);
    void writeBoard2FpgaImgconfigReg(unsigned int *regTable);
    void writeBoard3FpgaImgconfigReg(unsigned int *regTable);
    void writeBoard4FpgaImgconfigReg(unsigned int *regTable);
    void writeBoard5FpgaImgconfigReg(unsigned int *regTable);
    void writeBoard6FpgaImgconfigReg(unsigned int *regTable);
    void writeBoard7FpgaImgconfigReg(unsigned int *regTable);
    void writeBoard8FpgaImgconfigReg(unsigned int *regTable);

    void on_btnDefParam_clicked();

    void on_btnFinish_clicked();  //设备启动按钮

    void updataFlashTime(void);

    void displayMonitor(VCI_CAN_OBJ *vci,DWORD dwRel);

    void on_btnStatusBoard1_clicked();

    void on_btnUpdate_2_clicked();

    void on_btnUpdateMode_2_clicked();

    void on_btnStatusBoard1_2_clicked();


    void on_btnUpdateMode_3_clicked();

    void on_btnUpdate_3_clicked();

    void on_pushButtonTestWBoard1_clicked();

    void on_pushButtonTestRBoard1_clicked();

    void on_pushButtonTestWBoard2_clicked();

    void on_pushButtonTestRBoard2_clicked();

    void on_pushButtonTestWBoard3_clicked();

    void on_pushButtonTestRBoard3_clicked();

    void on_pushButtonTestWBoard4_clicked();

    void on_pushButtonTestRBoard4_clicked();

    void on_pushButtonTestWBoard5_clicked();

    void on_pushButtonTestRBoard5_clicked();

    void on_pushButtonTestWBoard6_clicked();

    void on_pushButtonTestRBoard6_clicked();

    void on_pushButtonTestWBoard7_clicked();

    void on_pushButtonTestRBoard7_clicked();

    void on_pushButtonTestWBoard8_clicked();

    void on_pushButtonTestRBoard8_clicked();

    void on_pushButtonAddrClear_clicked();

    void on_pushButtonAddrOk_clicked();

    void on_pushButtonImgClearBoard1_clicked();

    void on_comboBoxImgBoard1_currentIndexChanged(int index);

    void on_comboBox3Gin1SizeBoard1_currentIndexChanged(int index);

    void on_comboBox3Gin2SizeBoard1_currentIndexChanged(int index);

    void on_comboBox3Gin1SizeBoard2_currentIndexChanged(int index);

    void on_comboBox3Gin2SizeBoard2_currentIndexChanged(int index);

    void on_comboBoxImgBoard2_currentIndexChanged(int index);

    void on_pushButtonImgClearBoard2_clicked();

    void on_comboBox3Gin1SizeBoard3_currentIndexChanged(int index);

    void on_comboBox3Gin2SizeBoard3_currentIndexChanged(int index);

    void on_comboBoxImgBoard3_currentIndexChanged(int index);

    void on_pushButtonImgClearBoard3_clicked();

    void on_comboBox3Gin1SizeBoard4_currentIndexChanged(int index);

    void on_comboBox3Gin2SizeBoard4_currentIndexChanged(int index);

    void on_comboBoxImgBoard4_currentIndexChanged(int index);

    void on_pushButtonImgClearBoard4_clicked();

    void on_comboBox3Gin1SizeBoard5_currentIndexChanged(int index);

    void on_comboBox3Gin2SizeBoard5_currentIndexChanged(int index);

    void on_comboBoxImgBoard5_currentIndexChanged(int index);

    void on_pushButtonImgClearBoard5_clicked();

    void on_comboBox3Gin1SizeBoard6_currentIndexChanged(int index);

    void on_comboBox3Gin2SizeBoard6_currentIndexChanged(int index);

    void on_comboBoxImgBoard6_currentIndexChanged(int index);

    void on_pushButtonImgClearBoard6_clicked();

    void on_comboBox3Gin1SizeBoard7_currentIndexChanged(int index);

    void on_comboBox3Gin2SizeBoard7_currentIndexChanged(int index);

    void on_comboBoxImgBoard7_currentIndexChanged(int index);

    void on_pushButtonImgClearBoard7_clicked();

    void on_comboBox3Gin1SizeBoard8_currentIndexChanged(int index);

    void on_comboBox3Gin2SizeBoard8_currentIndexChanged(int index);

    void on_comboBoxImgBoard8_currentIndexChanged(int index);

    void on_pushButtonImgClearBoard8_clicked();

    void on_btnWorkTestMode_clicked();

    void on_btnWorkControlMode_clicked();

    void on_btnWorkControlLoad_clicked();

    void on_btnWorkControlSave_clicked();



    void on_btnUpdateMode_4_clicked();

    void on_pushButtonUpgradeAddrRead_clicked();

    void on_pushButtonUpgradeAddrSet_clicked();

    void on_pushButtonOpenOsdBoard1_clicked();
    void on_pushButtonOpenOsdBoard2_clicked();
    void on_pushButtonOpenOsdBoard3_clicked();
    void on_pushButtonOpenOsdBoard4_clicked();
    void on_pushButtonOpenOsdBoard5_clicked();
    void on_pushButtonOpenOsdBoard6_clicked();
    void on_pushButtonOpenOsdBoard7_clicked();
    void on_pushButtonOpenOsdBoard8_clicked();

    void on_horizontalSliderOsdStartXBoard1_sliderReleased();
    void on_horizontalSliderOsdStartXBoard2_sliderReleased();
    void on_horizontalSliderOsdStartXBoard3_sliderReleased();
    void on_horizontalSliderOsdStartXBoard4_sliderReleased();
    void on_horizontalSliderOsdStartXBoard5_sliderReleased();
    void on_horizontalSliderOsdStartXBoard6_sliderReleased();
    void on_horizontalSliderOsdStartXBoard7_sliderReleased();
    void on_horizontalSliderOsdStartXBoard8_sliderReleased();

    void on_horizontalSliderOsdStartYBoard1_sliderReleased();
    void on_horizontalSliderOsdStartYBoard2_sliderReleased();
    void on_horizontalSliderOsdStartYBoard3_sliderReleased();
    void on_horizontalSliderOsdStartYBoard4_sliderReleased();
    void on_horizontalSliderOsdStartYBoard5_sliderReleased();
    void on_horizontalSliderOsdStartYBoard6_sliderReleased();
    void on_horizontalSliderOsdStartYBoard7_sliderReleased();
    void on_horizontalSliderOsdStartYBoard8_sliderReleased();

    void on_horizontalSliderOsdWidthBoard1_sliderReleased();
    void on_horizontalSliderOsdWidthBoard2_sliderReleased();
    void on_horizontalSliderOsdWidthBoard3_sliderReleased();
    void on_horizontalSliderOsdWidthBoard4_sliderReleased();
    void on_horizontalSliderOsdWidthBoard5_sliderReleased();
    void on_horizontalSliderOsdWidthBoard6_sliderReleased();
    void on_horizontalSliderOsdWidthBoard7_sliderReleased();
    void on_horizontalSliderOsdWidthBoard8_sliderReleased();

    void on_horizontalSliderOsdHeightBoard1_sliderReleased();
    void on_horizontalSliderOsdHeightBoard2_sliderReleased();
    void on_horizontalSliderOsdHeightBoard3_sliderReleased();
    void on_horizontalSliderOsdHeightBoard4_sliderReleased();
    void on_horizontalSliderOsdHeightBoard5_sliderReleased();
    void on_horizontalSliderOsdHeightBoard6_sliderReleased();
    void on_horizontalSliderOsdHeightBoard7_sliderReleased();
    void on_horizontalSliderOsdHeightBoard8_sliderReleased();

    void on_horizontalSliderOsdAlphaBoard1_sliderReleased();
    void on_horizontalSliderOsdAlphaBoard2_sliderReleased();
    void on_horizontalSliderOsdAlphaBoard3_sliderReleased();
    void on_horizontalSliderOsdAlphaBoard4_sliderReleased();
    void on_horizontalSliderOsdAlphaBoard5_sliderReleased();
    void on_horizontalSliderOsdAlphaBoard6_sliderReleased();
    void on_horizontalSliderOsdAlphaBoard7_sliderReleased();
    void on_horizontalSliderOsdAlphaBoard8_sliderReleased();

    void on_btnWorkControlClearall_clicked();

    void on_pushButtonUpgradeOsdBoard1_clicked();
    void on_pushButtonUpgradeOsdBoard2_clicked();
    void on_pushButtonUpgradeOsdBoard3_clicked();
    void on_pushButtonUpgradeOsdBoard4_clicked();
    void on_pushButtonUpgradeOsdBoard5_clicked();
    void on_pushButtonUpgradeOsdBoard6_clicked();
    void on_pushButtonUpgradeOsdBoard7_clicked();
    void on_pushButtonUpgradeOsdBoard8_clicked();

    void on_pushButtonUpgradeOsdColorBoard1_clicked();
    void on_pushButtonUpgradeOsdColorBoard2_clicked();
    void on_pushButtonUpgradeOsdColorBoard3_clicked();
    void on_pushButtonUpgradeOsdColorBoard4_clicked();
    void on_pushButtonUpgradeOsdColorBoard5_clicked();
    void on_pushButtonUpgradeOsdColorBoard6_clicked();
    void on_pushButtonUpgradeOsdColorBoard7_clicked();
    void on_pushButtonUpgradeOsdColorBoard8_clicked();



    void on_pushButton_clicked();










    void on_pushButtonSetNetRegBoard1_clicked();

    void on_pushButtonClearNetRegBoard1_clicked();


    void on_pushButtonSetNetRegBoard2_clicked();

    void on_pushButtonClearNetRegBoard2_clicked();

    void on_pushButtonSetNetRegBoard3_clicked();

    void on_pushButtonClearNetRegBoard3_clicked();

    void on_pushButtonSetNetRegBoard4_clicked();

    void on_pushButtonClearNetRegBoard4_clicked();

    void on_pushButtonSetNetRegBoard5_clicked();

    void on_pushButtonClearNetRegBoard5_clicked();

    void on_pushButtonSetNetRegBoard6_clicked();

    void on_pushButtonClearNetRegBoard6_clicked();

    void on_pushButtonSetNetRegBoard7_clicked();

    void on_pushButtonClearNetRegBoard7_clicked();

    void on_pushButtonSetNetRegBoard8_clicked();

    void on_pushButtonClearNetRegBoard8_clicked();

public:
    void sleep(unsigned int msec);
};

#endif // MAINWINDOW_H
