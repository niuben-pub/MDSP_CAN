#include "current_chartview.h"
#include <QDebug>
Current_ChartView::Current_ChartView(QWidget *parent) : QChartView(parent)
{
    createChart();
}

void Current_ChartView::createChart()
{
    this->pen = new QPen();
    pen->setWidth(2);
    pen->setColor("#1D9EDF");  //默认蓝色

    this->chart = new QChart();
  //  chart->setTitle("Current (A)");
    chart->legend()->hide();//将图例关闭

    chart->setMargins(QMargins(5,5,5,5));
    setChart(chart);
    setRenderHint(QPainter::Antialiasing);//抗锯齿

    this->Series = new QLineSeries();
    this->Series->setName("Current");
    this->Series->setPen(*this->pen);
    chart->addSeries(Series);


    this->axisY = new QValueAxis;
    axisY->setRange(0.75,1.25);
    //axisY->setTitleText("A");
    axisY->setLabelFormat("%.3f");
    axisY->setTickCount(3);  // 主分隔数
    axisY->setMinorTickCount(4); // 子分隔数

    this->TimeAxis = new QDateTimeAxis();
    this->TimeAxis->setTickCount(7);
    this->TimeAxis->setFormat("hh:mm:ss");
    //this->TimeAxis->setTitleText("Time");
    chart->addAxis(this->TimeAxis, Qt::AlignBottom);
    this->Series->attachAxis(this->TimeAxis);


    chart->addAxis(axisY, Qt::AlignLeft);

    this->Series->attachAxis(axisY);



}

void Current_ChartView::prepareData(double cur)
{

    static QDateTime startTime = QDateTime::currentDateTime();  //记录开始时间

    this->Series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(),cur);


    if(cur > this->historyMaxData)
    {
        this->historyMaxData = cur;
    }

    if(cur < this->historyMinData)
    {
        this->historyMinData = cur;
    }


    if(Series->count() - timeRange > 0)
    {
        for(int i = 0; i < timeRange; i++)
        {
            if(Series->at(Series->count() - timeRange + i).y() > this->nearestMaxData)
            {
                this->nearestMaxData = Series->at(Series->count() - timeRange + i).y();
            }

            if(Series->at(Series->count() - timeRange + i).y() < this->nearestMinData)
            {
                this->nearestMinData = Series->at(Series->count() - timeRange + i).y();
            }
        }

    }
    else
    {
        if(cur > this->nearestMaxData)
        {
            this->nearestMaxData = cur;

        }

        if(cur < this->nearestMinData)
        {
            this->nearestMinData = cur;


        }


    }


    if(ceil(this->historyMaxData) - this->historyMaxData > 0.75 )
    {
        this->historyaxisYMax = ceil(this->historyMaxData) - 0.75;
    }
    else if(ceil(this->historyMaxData) - this->historyMaxData > 0.5 )
    {
        this->historyaxisYMax = ceil(this->historyMaxData) - 0.5;
    }
    else if(ceil(this->historyMaxData) - this->historyMaxData > 0.25 )
    {
        this->historyaxisYMax = ceil(this->historyMaxData) - 0.25;
    }
    else
    {
        this->historyaxisYMax = ceil(this->historyMaxData);
    }


    if(this->historyMinData - floor(this->historyMinData) > 0.75 )
    {
        this->historyaxisYMin = floor(this->historyMinData) + 0.75;
    }
    if(this->historyMinData - floor(this->historyMinData) > 0.5 )
    {
        this->historyaxisYMin = floor(this->historyMinData) + 0.5;
    }
    if(this->historyMinData - floor(this->historyMinData) > 0.25 )
    {
        this->historyaxisYMin = floor(this->historyMinData) + 0.25;
    }
    else
    {
        this->historyaxisYMin = floor(this->historyMinData);
    }


    if(ceil(this->nearestMaxData) - this->nearestMaxData > 0.75 )
    {
        this->nearestaxisYMax = ceil(this->nearestMaxData) - 0.75;
    }
    else if(ceil(this->nearestMaxData) - this->nearestMaxData > 0.5 )
    {
        this->nearestaxisYMax = ceil(this->nearestMaxData) - 0.5;
    }
    else if(ceil(this->nearestMaxData) - this->nearestMaxData > 0.25 )
    {
        this->nearestaxisYMax = ceil(this->nearestMaxData) - 0.25;
    }
    else
    {
        this->nearestaxisYMax = ceil(this->nearestMaxData);
    }


    if(this->nearestMinData - floor(this->nearestMinData) > 0.75 )
    {
        this->nearestaxisYMin = floor(this->nearestMinData) + 0.75;
    }
    if(this->nearestMinData - floor(this->nearestMinData) > 0.5 )
    {
        this->nearestaxisYMin = floor(this->nearestMinData) + 0.5;
    }
    if(this->nearestMinData - floor(this->nearestMinData) > 0.25 )
    {
        this->nearestaxisYMin = floor(this->nearestMinData) + 0.25;
    }
    else
    {
        this->nearestaxisYMin = floor(this->nearestMinData);
    }



    if(this->showMode == ReadTimeMode)
    {
        //时间轴范围
        if(QDateTime::currentDateTime() < startTime.addSecs(timeRange))
        {
            this->TimeAxis->setRange(startTime, startTime.addSecs(timeRange));//时间显示范围
        }
        else
        {
            this->TimeAxis->setRange(QDateTime::currentDateTime().addSecs(-timeRange), QDateTime::currentDateTime());//时间显示范围 60s
        }

        //数据轴范围

        this->axisY->setRange(this->nearestaxisYMin,this->nearestaxisYMax);


    }
    else if(this->showMode == HistoryMode)
    {
        //时间轴范围
        this->TimeAxis->setRange(startTime, QDateTime::currentDateTime());//时间显示范围

        //数据轴范围
        this->axisY->setRange(this->historyaxisYMin, this->historyaxisYMax);
         qDebug()<<"this->historyaxisYMin"<<this->historyMinData<< this->historyMaxData <<endl;

    }






}

void Current_ChartView::mousePressEvent(QMouseEvent *event)
{
     if(event->button() == Qt::LeftButton)
     {
        // qDebug()<<"Current_ChartView LeftButton press"<<endl;
        if(this->showMode == ReadTimeMode)
        {
            this->showMode = HistoryMode;
            pen->setColor("#6153D0");  //紫色
            this->Series->setPen(*this->pen);
        }
        else if(this->showMode == HistoryMode)
        {
            this->showMode = ReadTimeMode;
            pen->setColor("#1D9EDF");  //蓝色
            this->Series->setPen(*this->pen);
        }
     }

     if(event->button() == Qt::RightButton)
     {
        this->timeRange = 60;
     }
}

void Current_ChartView::wheelEvent(QWheelEvent *event)
{
    if(this->showMode == ReadTimeMode)
    {
        if(event->delta() > 0)
        {
            qDebug()<<"QWheelEvent > 0"<<endl;
            timeRange -= 10;
        }
        else if (event->delta() < 0)
        {
            qDebug()<<"QWheelEvent < 0"<<endl;
            timeRange += 10;
        }
    }

}


