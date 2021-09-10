#ifndef IMGLABEL_H
#define IMGLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

#define IN1_3G_1920x1080  (0x0080)
#define IN2_3G_1920x1080  (0x008c)
#define IN1_3G_960x540  (0x00c0)
#define IN2_3G_960x540  (0x00c6)
#define COLOR_960x540  (0x00cc)
#define DETECTION_960x540  (0x00cd)

//#define DRAW_WIDTH (480)
//#define DRAW_HIGHT (270)
//#define DRAW_QUAR_WIDTH (120)
//#define DRAW_QUAR_HIGHT (68)
#define DRAW_WIDTH (240)
#define DRAW_HIGHT (136)
#define DRAW_QUAR_WIDTH (60)
#define DRAW_QUAR_HIGHT (34)
enum IMGSIZE
{
    INPUT_SIZE_1920X1080 = 0,
    INPUT_SIZE_960X540 = 1
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
    unsigned int regTable[4][4] = { {0, 1, 2, 3 },
                                    {4, 5, 6, 7 },
                                    {8, 9, 10,11},
                                    {12,13,14,15}};
    unsigned int Img3GIn1Size = INPUT_SIZE_1920X1080;//д╛хо1080P
    unsigned int Img3GIn2Size = INPUT_SIZE_1920X1080;//д╛хо1080P
    unsigned int ImgType = IMG_IN1_3G;//д╛хо3G IN1
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
