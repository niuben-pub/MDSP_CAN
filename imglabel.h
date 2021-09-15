#ifndef IMGLABEL_H
#define IMGLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>


//�Ĵ�����ַ
#define HARDWARE_VERSION_REG_ADDR   (0x0001) //Ӳ���汾�żĴ�����ַ
#define DEVICE_STATE_REG_ADDR       (0x0002) //�豸״̬�Ĵ�����ַ
#define FPGA_TEMP_REG_ADDR          (0x0003) //FPGA�ڲ��¶ȼĴ�����ַ

#define IN1_3G_SIZE_REG_ADDR        (0x0020) //3G IN1 ������Ƶ�ߴ�Ĵ�����ַ
#define IN2_3G_SIZE_REG_ADDR        (0x0021) //3G IN2 ������Ƶ�ߴ�Ĵ�����ַ
#define IN_12G_SWITCH_REG_ADDR      (0x0024) //12G ���ؿ��ƼĴ�����ַ
#define DISPLAY_MODE_REG_ADDR       (0x0025) //16�� 4k in1 4k in2 ��ʾѡ��Ĵ�����ַ


//�Ĵ�������
#define IN1_3G_1920x1080    (0x0080)  //��ʾ�ߴ�1080P  3G in1
#define IN2_3G_1920x1080    (0x008c)  //��ʾ�ߴ�1080P  3G in2
#define IN1_3G_960x540      (0x00c0)  //��ʾ�ߴ�540P   3G in1
#define IN2_3G_960x540      (0x00c6)  //��ʾ�ߴ�540P   3G in2
#define COLOR_960x540       (0x00cc)  //��ʾ�ߴ�540P   ����
#define DETECTION_960x540   (0x00cd)  //��ʾ�ߴ�540P   Ŀ��ʶ��

#define IN_3G_SIZE_1920X1080 (0x0001) //3g in������ߴ�1080p
#define IN_3G_SIZE_960x540   (0x0000) //3g in������ߴ�540p

#define IN_12G_SWITCH_ON     (0x0001) //12g in�������  ����ͼΪ��һ��忨�����������򿪵������������»���ֻ���������
#define IN_12G_SWITCH_OFF    (0x0000) //12g in�������  ������ʾ���� 4K
#define SDI_4K_FROM_IN1      (0x0001) //��3G in1 ��ͼ��Ŵ���4K
#define SDI_4K_FROM_IN2      (0x0002) //��3G in2 ��ͼ��Ŵ���4K
#define SDI_4K_16            (0x0000) //ͼ����ʾΪ16��


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
    IMG_AI= 2,
    IMG_COLOR = 3
};
class ImgLabel : public QLabel
{
    Q_OBJECT


public:
    //Ӳ���汾��
    const unsigned int hardwareVersionRegAddr = HARDWARE_VERSION_REG_ADDR;
    unsigned int hardwareVersionReg = 0;
    //�豸״̬�Ĵ���
    const unsigned int deviceStateRegAddr = DEVICE_STATE_REG_ADDR;
    unsigned int deviceStateReg = 0;
    //fpga�ڲ��¶ȼĴ���
    const unsigned int fpgaTempRegAddr = FPGA_TEMP_REG_ADDR;
    unsigned int fpgaTempReg = 0;
    //3g in1 ͼ��ߴ�Ĵ���  1 - 1080p  0 - 540p
    const unsigned int img3GIn1SizeRegAddr = IN1_3G_SIZE_REG_ADDR;
    unsigned int img3GIn1SizeReg = IN_3G_SIZE_1920X1080;
    //3g in2 ͼ��ߴ�Ĵ���  1 - 1080p  0 - 540p
    const unsigned int img3GIn2SizeRegAddr = IN2_3G_SIZE_REG_ADDR;
    unsigned int img3GIn2SizeReg = IN_3G_SIZE_1920X1080;
    //12g ���뿪��
    const unsigned int in12GSwitchRegAddr = IN_12G_SWITCH_REG_ADDR;
    unsigned int in12GSwitchReg = IN_12G_SWITCH_OFF;
    //��ʾģʽ�Ĵ���
    const unsigned int displayModeRegAddr = DISPLAY_MODE_REG_ADDR;
    unsigned int displayModeReg = SDI_4K_16;

    //�Դ��ַ�Ĵ���
    unsigned int regTable[4][4] = { {0, 1, 2, 3 },
                                    {4, 5, 6, 7 },
                                    {8, 9, 10,11},
                                    {12,13,14,15}};



    unsigned int Img3GIn1Size = INPUT_SIZE_1920X1080;//Ĭ��1080P
    unsigned int Img3GIn2Size = INPUT_SIZE_1920X1080;//Ĭ��1080P
    unsigned int ImgType = IMG_IN1_3G;//Ĭ��3G IN1
    unsigned int DrawWindowWidth = DRAW_WIDTH;
    unsigned int DrawWindowHeight = DRAW_HIGHT;
    unsigned int DrawWindowQuarWidth = DRAW_QUAR_WIDTH;
    unsigned int DrawWindowQuarHeight = DRAW_QUAR_HIGHT;
    QPixmap pixBlank;
    QPixmap pix3GIN1;
    QPixmap pix3GIN2;
    QPixmap pixColor;
    QPixmap pixDetection;

private:
    void InitConnect(void);
public:
    explicit ImgLabel(QWidget *parent = nullptr);

    void PrintRegTable(void);
    void handleImgControl(unsigned int zone_x, unsigned int zone_y);

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
