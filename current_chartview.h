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
    QLineSeries *Series;  //当前序列
    QValueAxis *axisY;
    QDateTimeAxis *TimeAxis; //当前坐标轴
    void createChart();      //创建图表
    void prepareData(double cur);     //创建数据

    int timeRange = 60;  //显示的时间范围
    int showMode = ReadTimeMode;  //显示模式  实时或者历史
    int dataType = CURRENT;  //显示数据类型  电流电压温度等


    double historyMaxData = -100.0f;  //历史最大值
    double historyMinData = 100.0f;  //历史最小值

    double nearestMaxData = -1000.0f;  //当前最大值
    double nearestMinData = 1000.0f;  //当前最小值


    double historyaxisYMin = 0;    //历史最大值坐标
    double historyaxisYMax = 0;   //历史最小值坐标

    double nearestaxisYMin = 0;    //当前最大值坐标
    double nearestaxisYMax = 0;   //当前最小值坐标

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent*event);

signals:

};

#endif // CURRENT_CHARTVIEW_H
