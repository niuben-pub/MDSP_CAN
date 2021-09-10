#ifndef IMGOVERLAYLABEL_H
#define IMGOVERLAYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>


#define OVERLY_IN1_3G_1920x1080  (0x0080)
#define OVERLY_IN2_3G_1920x1080  (0x008c)
#define OVERLY_IN1_3G_960x540  (0x00c0)
#define OVERLY_IN2_3G_960x540  (0x00c6)
#define OVERLY_COLOR_960x540  (0x00cc)
#define OVERLY_DETECTION_960x540  (0x00cd)

#define OVERLY_DRAW_WIDTH (480)
#define OVERLY_DRAW_HIGHT (270)
#define OVERLY_DRAW_QUAR_WIDTH (120)
#define OVERLY_DRAW_QUAR_HIGHT (68)

class imgoverlayLabel : public QLabel
{
    Q_OBJECT
public:
    unsigned int regTableBoard[8][4][4];


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

    QPixmap pixDetectionBoard[8];

    QPixmap pixDetectionBoard1;
    QPixmap pixDetectionBoard2;
    QPixmap pixDetectionBoard3;
    QPixmap pixDetectionBoard4;
    QPixmap pixDetectionBoard5;
    QPixmap pixDetectionBoard6;
    QPixmap pixDetectionBoard7;
    QPixmap pixDetectionBoard8;
public:
    explicit imgoverlayLabel(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:
    void updataImg(void);

};

#endif // IMGOVERLAYLABEL_H
