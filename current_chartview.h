#ifndef CURRENT_CHARTVIEW_H
#define CURRENT_CHARTVIEW_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
using namespace QtCharts;

enum ShowMode
{
    ReadTimeMode = 0,
    HistoryMode = 1

};


enum DataType
{
    CURRENT = 0,
    VOLTAGE12V = 1,
    VOLTAGE5V = 2,
    CAVITY_TEMPARATURE = 3,
    FPGA_TEMPARATURE = 4

};

class Current_ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit Current_ChartView(QWidget *parent = nullptr);

public:
    QPen *pen;
    QChart *chart;
    QLineSeries *Series;  //��ǰ����
    QValueAxis *axisY;
    QDateTimeAxis *TimeAxis; //��ǰ������
    void createChart();      //����ͼ��
    void prepareData(double cur);     //��������

    int timeRange = 60;  //��ʾ��ʱ�䷶Χ
    int showMode = ReadTimeMode;  //��ʾģʽ  ʵʱ������ʷ
    int dataType = CURRENT;  //��ʾ��������  ������ѹ�¶ȵ�


    double historyMaxData = -100.0f;  //��ʷ���ֵ
    double historyMinData = 100.0f;  //��ʷ��Сֵ

    double nearestMaxData = -1000.0f;  //��ǰ���ֵ
    double nearestMinData = 1000.0f;  //��ǰ��Сֵ


    double historyaxisYMin = 0;    //��ʷ���ֵ����
    double historyaxisYMax = 0;   //��ʷ��Сֵ����

    double nearestaxisYMin = 0;    //��ǰ���ֵ����
    double nearestaxisYMax = 0;   //��ǰ��Сֵ����

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent*event);

signals:

};

#endif // CURRENT_CHARTVIEW_H
