#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  ,m_serialPortNum(0)
  ,systemTimer(new QTimer)
{
    ui->setupUi(this);
    init_mainForm();
    initChartView();
    connect(systemTimer,SIGNAL(timeout()),this,SLOT(readData()));
    systemTimer->setInterval(350);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readData()
{
    qDebug() <<"-------------------------------------m_currentRunType:      " << m_currentRunType;
    switch (m_currentRunType) {
        case GET_CURRENTFLOW:
            on_btn_getCurrentFlow_clicked();
        break;
    case GET_TOTALFLOW:
            on_btn_getTotalFlow_clicked();
        break;
    case GET_TEMPERATURE:
            on_btn_getTemperture_clicked();
        break;
    }

}

void MainWindow::init_mainForm()
{
//    m_customTabWidget_West = new CustomTabWidget_West(this);
//    m_customTabWidget_West->resize(1024,644);
//    m_customTabWidget_West->move(0,96);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("MFC");


//    QTreeWidgetItem *note2 = new QTreeWidgetItem(QStringList("设备2"));
//    ui->treeWidget->addTopLevelItem(note2);
//    QTreeWidgetItem *childtree1 = new QTreeWidgetItem(QStringList("child1"));
//    QTreeWidgetItem *childtree2 = new QTreeWidgetItem(QStringList("child2"));
//    note2->addChild(childtree1);
//    note2->addChild(childtree2);

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox_COM->addItem(serial.portName());
            serial.close();
        }
    }
    m_currentRunStatus = LOG_OFF;
}

void MainWindow::initChartView()
{
    initChartView_currentFlow();
    initChartView_totalFlow();
    initChartView_temperature();
}

void MainWindow::initChartView_currentFlow()
{
    chart_currentFlow = new QChart();
   m_series_currentFlow = new QLineSeries();
   m_series_temperature = new QLineSeries();

   m_series_currentFlow->setName(QStringLiteral("实时流量"));
   m_series_temperature->setName(QStringLiteral("温度"));

   chart_currentFlow->addSeries(m_series_currentFlow);
   chart_currentFlow->addSeries(m_series_temperature);

   m_dateTimeAxis_currentFlow = new QDateTimeAxis();

   QValueAxis *axisY_1 = new QValueAxis();
   QValueAxis *axisY_2 = new QValueAxis();

   m_dateTimeAxis_currentFlow->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(1800));

   axisY_1->setMin(5.0);
   axisY_1->setMax(6.0);
   axisY_2->setMin(0);
   axisY_2->setMax(100);

   //設置座標軸上的格點
   axisY_1->setTickCount(7);
   axisY_2->setTickCount(11);

   //設置座標軸顯示的名稱
   m_dateTimeAxis_currentFlow->setTitleText("时间");
   axisY_1->setTitleText(QStringLiteral("实时流量"));
   axisY_2->setTitleText(QStringLiteral("温度"));

   //設置座標軸的顏色，粗細，設置網格不顯示
   axisY_1->setLinePenColor(QColor(Qt::darkBlue));
   axisY_1->setGridLineColor(QColor(Qt::darkBlue));
   axisY_2->setLinePenColor(QColor(Qt::darkGreen));
   axisY_2->setGridLineColor(QColor(Qt::darkGreen));
   axisY_1->setGridLineVisible(false);
   axisY_2->setGridLineVisible(false);

   QPen penY1(Qt::darkBlue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
   QPen penY2(Qt::darkGreen, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
   axisY_1->setLinePen(penY1);
   axisY_2->setLinePen(penY2);

   //把座標軸添加到chart中，
   //addAxis函數的第二個參數是設置座標軸的位置，
   //只有四個選項，下方：Qt::AlignBottom，左邊：Qt::AlignLeft，右邊：Qt::AlignRight，上方：Qt::AlignTop
   chart_currentFlow->addAxis(m_dateTimeAxis_currentFlow, Qt::AlignBottom);
   chart_currentFlow->addAxis(axisY_1, Qt::AlignLeft);
   chart_currentFlow->addAxis(axisY_2, Qt::AlignRight);

   //把曲線關聯到座標軸
   m_series_currentFlow->attachAxis(m_dateTimeAxis_currentFlow);
   m_series_currentFlow->attachAxis(axisY_1);
   m_series_temperature->attachAxis(m_dateTimeAxis_currentFlow);
   m_series_temperature->attachAxis(axisY_2);

   m_chartView_currentFlow = new QChartView(chart_currentFlow);
   QGridLayout *baseLayout = new QGridLayout(); //便于显示，创建网格布局

   baseLayout->addWidget(m_chartView_currentFlow, 0, 0);
   ui->widgetWaveForm_current->setLayout(baseLayout);
}

void MainWindow::initChartView_totalFlow()
{
//    chart_totalFlow.setTheme(QChart::ChartThemeBlueIcy);//设置系统主题
//    chart_totalFlow.setTitle("Current Flow");//设置标题
//    chart_totalFlow.setTitleFont(QFont("微软雅黑",9,QFont::Bold));
//    chart_totalFlow.setTitleBrush(QColor(115, 159, 186));
//    chart_totalFlow.legend()->hide();
//    QPen pen(Qt::red);
//    pen.setWidth(1);
//    m_series_totalFlow.setPen(pen);
//    //m_series.append(m_x, m_y);

//    chart_totalFlow.addSeries(&m_series_totalFlow);
//    chart_totalFlow.createDefaultAxes();
//    m_dateTimeAxis_totalFlow.setFormat("hh:mm:ss");
//    chart_totalFlow.setAxisX(&m_dateTimeAxis_totalFlow,&m_series_totalFlow);
//    m_dateTimeAxis_totalFlow.setLabelsAngle(30);
//    QFont font;
//    font.setFamily("Times New Roman");
//    font.setPixelSize(11);
//    m_dateTimeAxis_totalFlow.setLabelsFont(font);
//    m_dateTimeAxis_totalFlow.setTickCount(6);
//    //chart.layout()->setContentsMargins(0, 0, 0, 0);
//    chart_totalFlow.setBackgroundRoundness(1);
//    chart_totalFlow.legend()->hide();
////    chartAxis axis;
//////    axis.X_min = 0;
//////    axis.X_max = 60;
////    axis.Y_min = 5.0;
////    axis.Y_max =6.0;
//    //set_axisX(axis.X_max);
//    refreshAxisX(GET_TOTALFLOW);
////    chart_totalFlow.axisY()->setRange(axis.Y_min,axis.Y_max);

//    m_chartView_totalFlow = new QChartView(&chart_totalFlow);
//    QGridLayout *baseLayout = new QGridLayout(); //便于显示，创建网格布局

//    baseLayout->addWidget(m_chartView_totalFlow, 0, 0);
//    ui->widgetWaveForm_total->setLayout(baseLayout);
}

void MainWindow::initChartView_temperature()
{

}

void MainWindow::refreshAxisX(int type)
{
    switch (type) {
    case GET_CURRENTFLOW:
            chart_currentFlow->axisX()->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(1800));
            m_endTime = QDateTime::currentDateTime().addSecs(1800);
        break;
    case GET_TOTALFLOW:
            //chart_totalFlow->axisX()->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(180));
        break;
    case GET_TEMPERATURE:
            //chart_temperature.axisX()->setRange(QDateTime::currentDateTime(),QDateTime::currentDateTime().addSecs(180));
        break;
    }
}

void MainWindow::refreshTreeWidgetList()
{
    for(int index = 0; index < m_serialPortList.count();index++)
    {
        ui->treeWidget->addTopLevelItem(m_serialPortList[index].serialPort);
        for(int num = 0;num < m_serialPortList[index].deviceList.count();num++)
        {
            m_serialPortList[index].serialPort->addChild(m_serialPortList[index].deviceList[num]);
        }
    }

}

void MainWindow::connectHandle()
{

}

QSerialPort *MainWindow::setSerialPortInfo(PortSettings* setting)
{
    QSerialPort* serialPort = new QSerialPort(this);
    serialPort->setPortName(setting->com);
    serialPort->setBaudRate(setting->baudRate.toInt());
    switch (setting->dataBits)
    {
    case 0:
        serialPort->setDataBits(QSerialPort::Data5);
        break;
    case 1:
        serialPort->setDataBits(QSerialPort::Data6);
        break;
    case 2:
        serialPort->setDataBits(QSerialPort::Data7);
        break;
    case 3:
        serialPort->setDataBits(QSerialPort::Data8);
        break;
    case 4:
        serialPort->setDataBits(QSerialPort::UnknownDataBits);
        break;
    default:
        break;
    }

    switch (setting->parity)
    {
    case 0:
        serialPort->setParity(QSerialPort::NoParity);
        break;
    case 1:
        serialPort->setParity(QSerialPort::OddParity);
        break;
    case 2:
        serialPort->setParity(QSerialPort::EvenParity);
        break;
    case 3:
        serialPort->setParity(QSerialPort::SpaceParity);
        break;
    case 4:
        serialPort->setParity(QSerialPort::MarkParity);
        break;
    case 5:
        serialPort->setParity(QSerialPort::UnknownParity);
        break;
    default:
        break;
    }

    switch (setting->stopBits)
    {
    case 0:
        serialPort->setStopBits(QSerialPort::OneStop);
        break;
    case 1:
        serialPort->setStopBits(QSerialPort::OneAndHalfStop);
        break;
    case 2:
        serialPort->setStopBits(QSerialPort::TwoStop);
        break;
    case 3:
        serialPort->setStopBits(QSerialPort::UnknownStopBits);
        break;
    default:
        break;
    }

    switch (setting->flowControl)
    {
    case 0:
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        break;
    case 1:
        serialPort->setFlowControl(QSerialPort::HardwareControl);
        break;
    case 2:
        serialPort->setFlowControl(QSerialPort::SoftwareControl);
        break;
    case 3:
        serialPort->setFlowControl(QSerialPort::UnknownFlowControl);
        break;
    default:
        break;
    }
    return serialPort;
}

///设备连接函数
void MainWindow::deviceConnect(QSerialPort* serialPort)
{
   if (!serialPort->open(QIODevice::ReadWrite))
   {
       QMessageBox::information(this, "提示", "串口连接失败");
   }
   else
   {
       QMessageBox::information(this, "提示", ui->comboBox_COM->currentText() + tr("连接成功"));
   }
   connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::slot_serialReadData);
}

///设备断开连接函数
void MainWindow::deviceDisConnect(QSerialPort* serialPort)
{
    serialPort->setDataTerminalReady(false);
    serialPort->setRequestToSend(false);
    serialPort->close();
}

void MainWindow::slot_serialReadData()
{
    QByteArray receiveDate;
    receiveDate = m_pSerialPort->readAll();
    if (!receiveDate.isEmpty())
    {
        QString strBuf =   receiveDataString;
        strBuf += receiveDate;

        receiveDataString.append(strBuf);
        if(strBuf.contains("@@@")&&strBuf.contains(";FF"))
        {
            refreshRespondUI(strBuf);
        }
    }
    receiveDate.clear();
}

void MainWindow::refreshRespondUI(QString receiveData)
{
    qDebug() << "-------------------------------------------------------------------:       " << receiveData;
    QString newReceiveData;
    receiveData.replace("@","");
    newReceiveData =  receiveData.remove("000ACK").remove(";FF").trimmed();
    switch (sendType) {
    case TYPE_FLOW_READ:
    {
        ui->lineEdit_getFlow->clear();
        ui->lineEdit_getFlow->setText(newReceiveData);
    break;
     }
    case TYPE_FLOW_SET:
    {
        QMessageBox::information(this, tr("提示"),QString(QStringLiteral("设置%1成功").arg(("流量"))));
    break;
    }
    case TYPE_VALVECMD_READ:
    {
        ui->lineEdit_getValveCmd->clear();
        ui->lineEdit_getValveCmd->setText(newReceiveData);
    break;
    }
    case TYPE_TEMPERATURE_READ:
    {
        ui->lineEdit_getTemperture->clear();
        ui->lineEdit_getTemperture->setText(newReceiveData);
        if(QDateTime::currentDateTime() > m_endTime)
        {
            refreshAxisX(GET_TEMPERATURE);
            m_series_temperature->clear();
        }
        if(newReceiveData.toDouble() >1 &&newReceiveData.toDouble() < 99)
        {
            m_series_temperature->append(QDateTime::currentMSecsSinceEpoch(),newReceiveData.toDouble());
            m_temperatureMap.insert(QDateTime::currentDateTime(),newReceiveData.toDouble());
        }

        //char->axisY()->setRange(newReceiveData.toDouble()-100,newReceiveData.toDouble()+100);
        m_currentRunType = GET_CURRENTFLOW;
    break;
    }
    case TYPE_TOTALFLOW_READ:
    {

        ui->lineEdit_getTotalFlow->clear();
        ui->lineEdit_getTotalFlow->setText(newReceiveData);
        m_currentRunType = GET_TEMPERATURE;
    break;
    }
    case TYPE_SETZERO:
    {
        QMessageBox::information(this, tr("提示"),QString(QStringLiteral("流量%1成功").arg(("置零"))));
    break;
    }
    case TYPE_SETCURRENTFLOW:
    {
        ui->lineEdit_getCurrentFlow->clear();
        ui->lineEdit_getCurrentFlow->setText(newReceiveData);
        if(QDateTime::currentDateTime() > m_endTime)
        {
            refreshAxisX(GET_CURRENTFLOW);
            m_series_currentFlow->clear();
        }
        if(newReceiveData.toDouble() >0.5 &&newReceiveData.toDouble() < 10)
        {
            m_series_currentFlow->append(QDateTime::currentMSecsSinceEpoch(),newReceiveData.toDouble());
            m_currentFlowMap.insert(QDateTime::currentDateTime(),newReceiveData.toDouble());
        }
        m_currentRunType = GET_TOTALFLOW;

    break;
    }
    default:

    break;
    }
}

void MainWindow::addAddressHandle(QString port, QString address)
{
    for(int index = 0; index < m_serialPortList.count();index++)
    {
        if(m_serialPortList[index].serialPort->text(0) == port)
        {
            QTreeWidgetItem *childtree = new QTreeWidgetItem(QStringList(QString("%1").arg(address)));
            m_serialPortList[index].deviceList.append(childtree);
        }
    }
    refreshTreeWidgetList();
    writeJsonFile(m_serialPortList);
}

void MainWindow::addSerialPortHandle(QString serialPort)
{
    SerialPortTree serialPortTree;
    serialPortTree.index = 0;
    serialPortTree.serialPort = new QTreeWidgetItem(QStringList(QString("%1").arg(serialPort)));
    m_serialPortList.append(serialPortTree);
    refreshTreeWidgetList();
    ui->btn_addSerialPort->setEnabled(false);
    ui->btn_addDevice->setEnabled(false);
    ui->btn_confirm->setEnabled(false);

}

void MainWindow::on_btn_addDevice_clicked()
{
    m_formSettingDialog = new FormSettingDialog(m_serialPortList);
    m_formSettingDialog->showNormal();
    connect(m_formSettingDialog,&FormSettingDialog::addAddressSignal,this,&MainWindow::addAddressHandle);
}

/*
 *@功能:  添加串口按钮点击事件
 *@参数:
 *@返回值:
*/
void MainWindow::on_btn_addSerialPort_clicked()
{
//    QTreeWidgetItem *note = new QTreeWidgetItem(QStringList("未命名串口"));
//    ui->treeWidget->addTopLevelItem(note);
//    if(m_serialPortList.count() == 0)
//    {
//        SerialPortTree serialPortTree;
//        serialPortTree.index = 0;
//        serialPortTree.serialPort = note;
//        m_serialPortList.insert(m_serialPortList.count(),serialPortTree);
//    }else {
//        SerialPortTree serialPortTree;
//        serialPortTree.index = 0;
//        serialPortTree.serialPort = note;
//        m_serialPortList.insert(m_serialPortList.count(),serialPortTree);
//    }
    m_formCreateNewSerialPort = new FormCreateNewSerialPort();
    m_formCreateNewSerialPort->showNormal();
    connect(m_formCreateNewSerialPort,&FormCreateNewSerialPort::addSerialPortSignal,this,&MainWindow::addSerialPortHandle);
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{

    if(item->text(0).contains(QStringLiteral("--串口")))
    {
        currentTreeItem = item;
        ///显示串口界面
       ui->stackedWidget->setCurrentIndex(0);
       ///从配置文件读取串口数据

    }else if(item->text(0).contains(QStringLiteral("--设备")))
    {
        ///显示设备界面
        ui->stackedWidget->setCurrentIndex(1);
        qDebug() << "MainWindow::on_treeWidget_itemClicked:       " << item->parent()->text(0);

        if(currentTreeChildItem == item)
        {

        }
        else {
            if(m_currentRunStatus == LOG_OFF)
            {
                ///获取当前设备串口信息
                for(int index = 0; index < m_serialPortList.count();index++)
                {
                    if(item->parent()->text(0) == m_serialPortList[index].serialPort->text(0))
                    {
                        ///创建连接
                        m_pSerialPort = m_serialPortList[index].SerialPort;//当前串口
    //                    qDebug() << "currentTreeItem---serialPort---com:          " <<  m_serialPortList[index].settings->com;
    //                    qDebug() << "currentTreeItem---serialPort---baudRate:          " <<  m_serialPortList[index].settings->baudRate;
    //                    qDebug() << "currentTreeItem---serialPort---dataBits:          " <<  m_serialPortList[index].settings->dataBits;
                        qDebug() << "++++++++++++++++++++++++++++++++++++++++";
                        deviceConnect(m_serialPortList[index].SerialPort);
                        m_currentAddress = item->text(0).remove("--设备");
                    }
                }
                currentTreeChildItem = item;
                //m_currentDevice = item->text(0);
            }
            else if (m_currentRunStatus == LOG_ON)
            {
                QMessageBox::StandardButton rb = QMessageBox::information(NULL, QStringLiteral("警告"), QStringLiteral("当前设备正在运行，是否切换设备?")
                                                                          , QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                if(rb == QMessageBox::Yes)
                {
                    on_btn_logOff_clicked();
                    m_series_currentFlow->clear();
                    m_series_temperature->clear();
                    deviceDisConnect(m_pSerialPort);
                    ///获取当前设备串口信息
                    for(int index = 0; index < m_serialPortList.count();index++)
                    {
                        if(item->parent()->text(0) == m_serialPortList[index].serialPort->text(0))
                        {
                            ///创建连接
                            m_pSerialPort = m_serialPortList[index].SerialPort;//当前串口
                            deviceConnect(m_serialPortList[index].SerialPort);
                            m_currentAddress = item->text(0).remove("--设备");
                        }
                    }
                    currentTreeChildItem = item;
                    //m_currentDevice = item->text(0);
                }
                else if(rb == QMessageBox::No)
                {

                }
            }

        }
    }
    ///读取串口内容
    ///
    ///
    ///
    ui->btn_confirm->setEnabled(true);
}

void MainWindow::on_btn_confirm_clicked()
{
    ///保存串口设置
    for(int index = 0; index < m_serialPortList.count();index++)
    {
        if(currentTreeItem->text(0) == m_serialPortList[index].serialPort->text(0))
        {
            PortSettings *setting  = new PortSettings;
            setting->com = ui->comboBox_COM->currentText();
            setting->baudRate = ui->comboBox_baudRate->currentText();
            setting->dataBits = ui->comboBox_dataBits->currentIndex();
            setting->parity = ui->comboBox_parity->currentIndex();
            setting->stopBits = ui->comboBox_stopBits->currentIndex();
            setting->flowControl = ui->comboBox_flowControl->currentIndex();
            qDebug() << "setting:       " << setting->baudRate;
            //qDebug() << "setSerialPortInfo:       " << setSerialPortInfo(setting)->readAll();
            m_serialPortList[index].SerialPort = setSerialPortInfo(setting);
            m_serialPortList[index].settings = setting;
        }
    }
    ui->btn_addSerialPort->setEnabled(true);
    ui->btn_addDevice->setEnabled(true);
    writeJsonFile(m_serialPortList);
}

void MainWindow::on_btn_getCurrentFlow_clicked()
{
    receiveDataString.clear();
    sendCMD(QString("@@@%1FX?;FF").arg(m_currentAddress));
    sendType = TYPE_SETCURRENTFLOW;
}

void MainWindow::sendCMD(QString strMessage)
{
    QByteArray sendBytes;
    sendBytes.append(strMessage);

    m_pSerialPort->write(sendBytes);
}

void MainWindow::on_btn_getFlow_clicked()
{
    receiveDataString.clear();
    sendCMD(QString("@@@%1SX?;FF").arg(m_currentAddress));
    sendType = TYPE_FLOW_READ;
}

void MainWindow::on_btn_setFlow_clicked()
{
    QString flowValue = ui->lineEdit_setFlow->text();
    sendCMD(QString("@@@%1SX!%2;FF").arg(m_currentAddress).arg(flowValue));
    sendType = TYPE_FLOW_SET;
}

void MainWindow::on_btn_getTotalFlow_clicked()
{
    receiveDataString.clear();
    sendCMD(QString("@@@%1FT?;FF").arg(m_currentAddress));
    sendType = TYPE_TOTALFLOW_READ;
}

void MainWindow::on_btn_setTotalFlowToZero_clicked()
{
    receiveDataString.clear();
    sendCMD(QString("@@@%1FT!0;FF").arg(m_currentAddress));
    sendType = TYPE_SETZERO;
}

void MainWindow::on_btn_getValveCmd_clicked()
{
    receiveDataString.clear();
    sendCMD(QString("@@@%1VD?;FF").arg(m_currentAddress));
    sendType = TYPE_VALVECMD_READ;
}

void MainWindow::on_btn_getTemperture_clicked()
{
    receiveDataString.clear();
    sendCMD(QString("@@@%1TA?;FF").arg(m_currentAddress));
    sendType = TYPE_TEMPERATURE_READ;
}

void MainWindow::on_btn_logOn_clicked()
{
    m_series_currentFlow->clear();
    m_series_temperature->clear();
    refreshAxisX(GET_CURRENTFLOW);
    refreshAxisX(GET_TOTALFLOW);
    m_currentRunType = GET_CURRENTFLOW;
    m_currentRunStatus = LOG_ON;
    systemTimer->start();
}

void MainWindow::on_btn_logOff_clicked()
{
    systemTimer->stop();
    writeToCsvFileHandle(m_currentFlowMap,GET_CURRENTFLOW);
    writeToCsvFileHandle(m_temperatureMap,GET_TEMPERATURE);
    m_currentRunStatus = LOG_OFF;
    m_currentFlowMap.clear();

}

void MainWindow::writeToCsvFileHandle(QMap<QDateTime, double> m_seriesPoint,int fileType)
{
    //QString txtFilePath = QDir::currentPath().replace("bin","/File/CSV/") + getCurrentDatetimeForFolder();
    QString txtFilePath = QDir::currentPath()+"/File/CSV/" + getCurrentDatetimeForFolder();
    if(isDirExist(txtFilePath))
    {
        QString currentTime = getCurrentDatetimeForFile();
        QFile f;
        switch (fileType) {
        case GET_CURRENTFLOW:
            f.setFileName(txtFilePath+"/" + currentTime +"-currentFlow" + ".csv");
        break;
        case GET_TOTALFLOW:
            f.setFileName(txtFilePath+"/" + currentTime +"-totalFlow" + ".csv");
        break;
        case GET_TEMPERATURE:
            f.setFileName(txtFilePath+"/" + currentTime +"-temperature" + ".csv");
        break;
        }
        //QFile f(txtFilePath+"/" + currentTime  + ".csv");
        if(!f.open(QIODevice::WriteOnly | QFile::Truncate))
        {
            QMessageBox::about(nullptr, "文件", "文件打开失败");
        }
        QTextStream txtOutput(&f);
        QMap<QDateTime, double>::ConstIterator i=m_seriesPoint.constBegin();
        while(i!=m_seriesPoint.constEnd())
        {
            //qDebug()<<i.key()<<": "<<i.value();
             txtOutput << i.key().toString("hh:mm:ss") << "," << i.value() << endl;
            ++i;
        }
        f.close();
    }
}

bool MainWindow::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    else
    {
       bool ok = dir.mkpath(fullPath);//创建多级目录
       return ok;
    }
}

QString MainWindow::getCurrentDatetimeForFile()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyyMMddhhmmss");
    return current_date;
}

QString MainWindow::getCurrentDatetimeForFolder()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd");
    return current_date;
}

void MainWindow::importPortInfo()
{

}

void MainWindow::writeJsonFile(QList<SerialPortTree> serialPortTree)
{
    qDebug() << "0000000000000000000000000000000111111";
    QJsonObject jsonObject;
    qDebug() << "0000000000000000000000000000000222" << serialPortTree.count();
    for(int index = 0;index < serialPortTree.count();index++)
    {
        QJsonObject subObject;
        subObject.insert("com",QJsonValue(QString("%1").arg(serialPortTree[index].settings->com)));
        subObject.insert("baudRate",QJsonValue(QString("%1").arg(serialPortTree[index].settings->baudRate)));
        subObject.insert("dataBits",QJsonValue(QString("%1").arg(serialPortTree[index].settings->dataBits)));
        subObject.insert("parity",QJsonValue(QString("%1").arg(serialPortTree[index].settings->parity)));
        subObject.insert("stopBits",QJsonValue(QString("%1").arg(serialPortTree[index].settings->stopBits)));
        subObject.insert("flowControl",QJsonValue(QString("%1").arg(serialPortTree[index].settings->flowControl)));
        qDebug() << "0000000000000000000000000000000333" << serialPortTree[index].deviceList.count();
        if(serialPortTree[index].deviceList.count())
        {
            QJsonArray arrayObject;
            for(int num = 0 ;num < serialPortTree[index].deviceList.count();num++)
            {
                arrayObject.append(QString("%1").arg(serialPortTree[index].deviceList[num]->text(0)));
            }
            subObject.insert("Devices",arrayObject);
        }
        jsonObject.insert(QString("%1").arg(serialPortTree[index].serialPort->text(0)),QJsonValue(subObject));
    }


    qDebug() << "0000000000000000000000000000000333";

    //内存中的数据写到文件
    QJsonDocument doc(jsonObject);
    //将json对象转换成字符串
    QByteArray data=doc.toJson();
    QString txtFilePath = QDir::currentPath()+"/Setup";
    if(isDirExist(txtFilePath))
    {
        QFile file(txtFilePath+"/List.json");
    //    file.open(QIODevice::WriteOnly);
    //    file.write(data);
    //    file.close();

        if(!file.open(QIODevice::WriteOnly | QFile::Truncate))
        {
            QMessageBox::about(nullptr, "文件", "文件打开失败");
        }
        QTextStream txtOutput(&file);
        file.write(data);
        file.close();
    }

}
