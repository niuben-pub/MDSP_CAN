#ifndef IMGLABEL_H
#define IMGLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>


//寄存器地址
#define HARDWARE_VERSION_REG_ADDR   (0x0001) //硬件版本号寄存器地址
#define DEVICE_STATE_REG_ADDR       (0x0002) //设备状态寄存器地址
#define FPGA_TEMP_REG_ADDR          (0x0003) //FPGA内部温度寄存器地址

#define DETECTION_STATE_REG_ADDR    (0x0060) //FPGA目标识别开关及通道选择寄存器

#define IN1_3G_SIZE_REG_ADDR        (0x0020) //3G IN1 输入视频尺寸寄存器地址
#define IN2_3G_SIZE_REG_ADDR        (0x0021) //3G IN2 输入视频尺寸寄存器地址
#define IN_12G_SWITCH_REG_ADDR      (0x0024) //12G 开关控制寄存器地址
#define DISPLAY_MODE_REG_ADDR       (0x0025) //16画 4k in1 4k in2 显示选择寄存器地址


//寄存器数据

#define DETECTION_OFF       (0x0000)  //目标识别  关闭
#define DETECTION_IN1       (0x0001)  //目标识别  3G in2
#define DETECTION_IN2       (0x0003)  //目标识别  3G in2

#define IN1_3G_1920x1080    (0x0080)  //显示尺寸1080P  3G in1
#define IN2_3G_1920x1080    (0x008c)  //显示尺寸1080P  3G in2
#define IN1_3G_960x540      (0x00c0)  //显示尺寸540P   3G in1
#define IN2_3G_960x540      (0x00c6)  //显示尺寸540P   3G in2
#define COLOR_960x540       (0x00cc)  //显示尺寸540P   彩条
#define DETECTION_960x540   (0x00cd)  //显示尺寸540P   目标识别
#define LVDS_IN_960x540     (0x00d0)  //显示尺寸540P   lvds输入图像

#define IN_3G_SIZE_1920X1080 (0x0001) //3g in的输入尺寸1080p
#define IN_3G_SIZE_960x540   (0x0000) //3g in的输入尺寸540p

#define IN_12G_SWITCH_ON     (0x0001) //12g in的输入打开  背景图为上一快板卡的输出（如果打开但无输入的情况下会出现花屏背景）
#define IN_12G_SWITCH_OFF    (0x0000) //12g in的输入打开  背景显示彩条 4K
#define SDI_4K_FROM_IN1      (0x0001) //将3G in1 的图像放大至4K
#define SDI_4K_FROM_IN2      (0x0002) //将3G in2 的图像放大至4K
#define SDI_4K_16            (0x0000) //图像显示为16画


//#define DRAW_WIDTH (480)
//#define DRAW_HIGHT (270)
//#define DRAW_QUAR_WIDTH (120)
//#define DRAW_QUAR_HIGHT (68)
#define DRAW_WIDTH_FULL (480)
#define DRAW_HIGHT_FULL (272)
#define DRAW_WIDTH (240)
#define DRAW_HIGHT (136)
#define DRAW_QUAR_WIDTH (60)
#define DRAW_QUAR_HIGHT (34)
enum IMGSIZE
{
    INPUT_SIZE_1920X1080 = 0,
    INPUT_SIZE_960X540 = 1,
    INPUT_SIZE_FULL = 2
};

enum IMGTYPE
{
    IMG_IN1_3G = 0,
    IMG_IN2_3G = 1,
    IMG_AI_IN1= 2,
    IMG_AI_IN2= 3,
    IMG_COLOR = 4,
    IMG_LVDS_IN = 5
};
class ImgLabel : public QLabel
{
    Q_OBJECT


public:
    //硬件版本号
    const unsigned int hardwareVersionRegAddr = HARDWARE_VERSION_REG_ADDR;
    unsigned int hardwareVersionReg = 0;
    //设备状态寄存器
    const unsigned int deviceStateRegAddr = DEVICE_STATE_REG_ADDR;
    unsigned int deviceStateReg = 0;
    //fpga内部温度寄存器
    const unsigned int fpgaTempRegAddr = FPGA_TEMP_REG_ADDR;
    unsigned int fpgaTempReg = 0;

    //目标识别开关及通路选择寄存器
    const unsigned int detectionStateRegAddr = DETECTION_STATE_REG_ADDR;
    unsigned int detectionStateReg = DETECTION_OFF;

    //3g in1 图像尺寸寄存器  1 - 1080p  0 - 540p
    const unsigned int img3GIn1SizeRegAddr = IN1_3G_SIZE_REG_ADDR;
    unsigned int img3GIn1SizeReg = IN_3G_SIZE_1920X1080;
    //3g in2 图像尺寸寄存器  1 - 1080p  0 - 540p
    const unsigned int img3GIn2SizeRegAddr = IN2_3G_SIZE_REG_ADDR;
    unsigned int img3GIn2SizeReg = IN_3G_SIZE_1920X1080;
    //12g 输入开关
    const unsigned int in12GSwitchRegAddr = IN_12G_SWITCH_REG_ADDR;
    unsigned int in12GSwitchReg = IN_12G_SWITCH_ON;
    //显示模式寄存器
    const unsigned int displayModeRegAddr = DISPLAY_MODE_REG_ADDR;
    unsigned int displayModeReg = SDI_4K_16;

    //显存地址寄存器
    unsigned int regTable[4][4] = { {0, 0, 0, 0 },
                                    {0, 0, 0, 0 },
                                    {0, 0, 0, 0 },
                                    {0, 0, 0, 0}};



    unsigned int Img3GIn1Size = INPUT_SIZE_1920X1080;//默认1080P
    unsigned int Img3GIn2Size = INPUT_SIZE_1920X1080;//默认1080P
    unsigned int ImgType = IMG_IN1_3G;//默认3G IN1
    unsigned int DrawWindowWidth = DRAW_WIDTH;
    unsigned int DrawWindowHeight = DRAW_HIGHT;
    unsigned int DrawWindowQuarWidth = DRAW_QUAR_WIDTH;
    unsigned int DrawWindowQuarHeight = DRAW_QUAR_HIGHT;

    bool isBoard1 = false;
    QPixmap pixBlank;
    QPixmap pix3GIN1;
    QPixmap pix3GIN2;
    QPixmap pixColor;
    QPixmap pixDetectionIN1;
    QPixmap pixDetectionIN2;



private:
    void InitConnect(void);
public:
    explicit ImgLabel(QWidget *parent = nullptr);
    void resetRegData(void);  //清屏，显示的为12G in 的图像
    void resetRegData1(void);  //清屏，显示的为彩条
    void PrintRegTable(void);
    void handleImgControl(unsigned int zone_x, unsigned int zone_y);
    void clearImg(unsigned int zone_x, unsigned int zone_y);
    virtual void enterEvent(QEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
signals:
    void regChange(unsigned int *regTable);
    void mousePaint(void);
    void imgoverlayupdataImg(void);
public slots:
    void updataImg(void);
};

#endif // IMGLABEL_H
