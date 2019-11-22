#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "FormCreateNewSerialPort.h"
#include "FormSettingDialog.h"
#include "customtabwidget_west.h"

#include "SetupFileClass.h"
#include "PortManageClass.h"



#include "common_data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void init_mainForm();

    void initPortInfo();

    void refreshTreeWidgetList(QList<SerialPortTree> serialPertTree);

    ///设备连接函数
    void deviceConnect(QSerialPort* serialPort);

    ///设备断开连接函数
    void deviceDisConnect(QSerialPort* serialPort);

    void refreshRespondUI(QString  receiveData);

    void sendCMD(QString strMessage);

    void initChartView();

    void initChartView_currentFlow();

    void initChartView_totalFlow();
    void initChartView_temperature();

    void refreshAxisX(int type);

    void initPortSettings(PortSettings settings);

    void setCurrentFlowAdaptiveCoordinateSystem(QString newReceiveData);

public slots:

    void slot_serialReadData();

    void readData();

    void initTreeList(QList<SerialPortTree> serialPertTree);

private slots:

    void addAddressHandle(QString DeviceName,QString port,QString address);

    void addSerialPortHandle(QString serialPort);

    void on_btn_addDevice_clicked();

    void on_btn_addSerialPort_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_btn_confirm_clicked();

    void on_btn_getCurrentFlow_clicked();

    void on_btn_getFlow_clicked();

    void on_btn_setFlow_clicked();

    void on_btn_getTotalFlow_clicked();

    void on_btn_setTotalFlowToZero_clicked();

    void on_btn_getValveCmd_clicked();

    void on_btn_getTemperture_clicked();


    void on_btn_logOn_clicked();

    void on_btn_logOff_clicked();



    void on_btn_send_clicked();

private:
    Ui::MainWindow *ui;

    FormCreateNewSerialPort                                                     *m_formCreateNewSerialPort;

    FormSettingDialog                                                                *m_formSettingDialog;

    SetupFileClass                                                                       *m_setupFileClass;

    PortManageClass                                                                  *m_portManageClass;

    CustomTabWidget_West                                                       *m_customTabWidget_West;

    QHash<int,QTreeWidgetItem *>                                           m_serialPortHash;
    QList<SerialPortTree>                                                            m_serialPortList;
    ///串口编号
    int                                                                                            m_serialPortNum;


     QTreeWidgetItem *                                                                 currentTreeItem;
     QTreeWidgetItem *                                                                 currentTreeChildItem;

     QByteArray      m_sendBytes;        ///<发送命令
     QSerialPort*    m_pSerialPort;      ///<串口

     int sendType;

     QString m_currentAddress;

     QString receiveDataString;

     QChart *chart_currentFlow;

     QChart *chart_totalFlow;

     QChart *chart_temperature;

     QValueAxis m_axis;
     QDateTimeAxis *m_dateTimeAxis_currentFlow;
     QDateTimeAxis *m_dateTimeAxis_totalFlow;
     QDateTimeAxis *m_dateTimeAxis_temperature;

     QLineSeries *m_series_currentFlow;
     QLineSeries *m_series_totalFlow;
     QLineSeries *m_series_temperature;

     QChartView                *m_chartView_currentFlow;
     QChartView                *m_chartView_totalFlow;
     QChartView                *m_chartView_temperature;


     QValueAxis *axisY_1;

     QTimer                              *systemTimer;

     int                                                m_currentRunType;

     QMap<QDateTime,Flow>           m_currentFlowAndTemperatureMap;

     QMap<QDateTime,double>         m_currentFlowMap;
     QMap<QDateTime,double>         m_temperatureMap;

     QDateTime                                  m_endTime;

     QString                                       m_currentDevice;

     int                                               m_currentRunStatus;

     bool                                            m_firstDevice = false;

     bool                                            m_firstReadCurrentFlow = false;

     double                                        m_currentFlow_Low;
     double                                        m_currentFlow_High;

};

#endif // MAINWINDOW_H
