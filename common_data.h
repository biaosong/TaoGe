#ifndef COMMON_DATA_H
#define COMMON_DATA_H

#include <QString>
#include <QTreeWidgetItem>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtWidgets/qtreeview.h>
#include <QtWidgets/qtreewidgetitemiterator.h>

#include <QMessageBox>

#include <QtXml>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QtCharts>
enum
{
    LOG_ON = 0,
    LOG_OFF
};

enum
{
    TYPE_FLOW_READ = 0,
    TYPE_FLOW_SET,
    TYPE_VALVECMD_READ,
    TYPE_TEMPERATURE_READ,
    TYPE_TOTALFLOW_READ,
    TYPE_SETZERO,
    TYPE_SETCURRENTFLOW
};

enum{
    GET_CURRENTFLOW = 0,
    GET_TOTALFLOW,
    GET_TEMPERATURE
};

typedef struct _Flow{
    double currentFlow;
    double temperature;
}Flow;

typedef struct _Point{
    float x;
    float y;
}Point;

class PortSettings
{
public:
    QString                                         com = "9600";
    QString                                         baudRate = "COM4";
    int                                         dataBits = 3;
    int                                         parity = 0;
    int                                         stopBits =0;
    int                                         flowControl = 0;
    QString                                         address;
};

class  SerialPortTree
{
public:
    int index;
    QTreeWidgetItem *   serialPort;
    PortSettings    *settings;
    QSerialPort     *SerialPort;
    QList<QTreeWidgetItem *>    deviceList;
};

typedef  struct  ChartAxis
{
    double X_min;
    double Y_min;
    double X_max;
    double Y_max;
}chartAxis;

#endif // COMMON_DATA_H
