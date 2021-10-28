#ifndef IMGOVERLAYLABEL_H
#define IMGOVERLAYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

#define OVERLY_DETECTION_IN1        (0x0001)  //目标识别  3G in2
#define OVERLY_DETECTION_IN2        (0x0003)  //目标识别  3G in2
#define OVERLY_IN1_3G_1920x1080     (0x0080)
#define OVERLY_IN2_3G_1920x1080     (0x008c)
#define OVERLY_IN1_3G_960x540       (0x00c0)
#define OVERLY_IN2_3G_960x540       (0x00c6)
#define OVERLY_COLOR_960x540        (0x00cc)
#define OVERLY_DETECTION_960x540    (0x00cd)


#define OVERLY_LVDS_IN1            (0x0000)  //lvds  3G in1
#define OVERLY_LVDS_IN2            (0x0001)  //lvds  3G in2
#define OVERLY_LVDS_IN_960x540      (0x00d0)  //显示尺寸540P   lvds输入图像



#define OVERLY_DRAW_WIDTH (480)
#define OVERLY_DRAW_HIGHT (270)
#define OVERLY_DRAW_QUAR_WIDTH (120)
#define OVERLY_DRAW_QUAR_HIGHT (68)


#define OVERLY_SDI_4K_FROM_IN1      (0x0001) //将3G in1 的图像放大至4K
#define OVERLY_SDI_4K_FROM_IN2      (0x0002) //将3G in2 的图像放大至4K
#define OVERLY_SDI_4K_16            (0x0000) //图像显示为16画

class imgoverlayLabel : public QLabel
{
    Q_OBJECT
public:
    unsigned int regTableBoard[8][4][4];
    unsigned int displayModeRegBoard[8];
    unsigned int displayDetectionModeRegBoard[8];
    unsigned int displayLvdsINRegBoard[8];

    unsigned int DrawWindowWidth = OVERLY_DRAW_WIDTH;
    unsigned int DrawWindowHeight = OVERLY_DRAW_HIGHT;
    unsigned int DrawWindowQuarWidth = OVERLY_DRAW_QUAR_WIDTH;
    unsigned int DrawWindowQuarHeight = OVERLY_DRAW_QUAR_HIGHT;

    QPixmap pixBlank;


    QPixmap pix3GIN1Board[8];
    QPixmap pix3GIN1Board1;
    QPixmap pix3GIN1Board2;
    QPixmap pix3GIN1Board3;
    QPixmap pix3GIN1Board4;
    QPixmap pix3GIN1Board5;
    QPixmap pix3GIN1Board6;
    QPixmap pix3GIN1Board7;
    QPixmap pix3GIN1Board8;

    QPixmap pix3GIN2Board[8];
    QPixmap pix3GIN2Board1;
    QPixmap pix3GIN2Board2;
    QPixmap pix3GIN2Board3;
    QPixmap pix3GIN2Board4;
    QPixmap pix3GIN2Board5;
    QPixmap pix3GIN2Board6;
    QPixmap pix3GIN2Board7;
    QPixmap pix3GIN2Board8;

    QPixmap pixColorBoard[8];
    QPixmap pixColorBoard1;
    QPixmap pixColorBoard2;
    QPixmap pixColorBoard3;
    QPixmap pixColorBoard4;
    QPixmap pixColorBoard5;
    QPixmap pixColorBoard6;
    QPixmap pixColorBoard7;
    QPixmap pixColorBoard8;

    QPixmap pixIN1DetectionBoard[8];
    QPixmap pixIN1DetectionBoard1;
    QPixmap pixIN1DetectionBoard2;
    QPixmap pixIN1DetectionBoard3;
    QPixmap pixIN1DetectionBoard4;
    QPixmap pixIN1DetectionBoard5;
    QPixmap pixIN1DetectionBoard6;
    QPixmap pixIN1DetectionBoard7;
    QPixmap pixIN1DetectionBoard8;

    QPixmap pixIN2DetectionBoard[8];
    QPixmap pixIN2DetectionBoard1;
    QPixmap pixIN2DetectionBoard2;
    QPixmap pixIN2DetectionBoard3;
    QPixmap pixIN2DetectionBoard4;
    QPixmap pixIN2DetectionBoard5;
    QPixmap pixIN2DetectionBoard6;
    QPixmap pixIN2DetectionBoard7;
    QPixmap pixIN2DetectionBoard8;

    QPixmap pixIN1LVDSinBoard[8];
    QPixmap pixIN1LVDSinBoard1;
    QPixmap pixIN1LVDSinBoard2;
    QPixmap pixIN1LVDSinBoard3;
    QPixmap pixIN1LVDSinBoard4;
    QPixmap pixIN1LVDSinBoard5;
    QPixmap pixIN1LVDSinBoard6;
    QPixmap pixIN1LVDSinBoard7;
    QPixmap pixIN1LVDSinBoard8;

    QPixmap pixIN2LVDSinBoard[8];
    QPixmap pixIN2LVDSinBoard1;
    QPixmap pixIN2LVDSinBoard2;
    QPixmap pixIN2LVDSinBoard3;
    QPixmap pixIN2LVDSinBoard4;
    QPixmap pixIN2LVDSinBoard5;
    QPixmap pixIN2LVDSinBoard6;
    QPixmap pixIN2LVDSinBoard7;
    QPixmap pixIN2LVDSinBoard8;

public:
    explicit imgoverlayLabel(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:
    void updataImg(void);

};

#endif // IMGOVERLAYLABEL_H
