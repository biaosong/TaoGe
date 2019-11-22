#include "PortManageClass.h"

PortManageClass::PortManageClass(QObject *parent) : QObject(parent)
{

}

QSerialPort *PortManageClass::setSerialPortInfo(PortSettings setting)
{
    QSerialPort* serialPort = new QSerialPort(this);
    serialPort->setPortName(setting.com);
    serialPort->setBaudRate(setting.baudRate.toInt());
    qDebug() << "setting.dataBits:  "<< setting.dataBits;
    switch (setting.dataBits)
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

    switch (setting.parity)
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

    switch (setting.stopBits)
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

    switch (setting.flowControl)
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

QString PortManageClass::getDeviceByName(QList<SerialPortTree> serialPertTree,QTreeWidgetItem *item)
{
    for(int index = 0; index < serialPertTree.count();index++)
    {
        QMap<QString,QTreeWidgetItem *>::const_iterator itor;
        for(itor = serialPertTree[index].deviceMap.constBegin();itor != serialPertTree[index].deviceMap.constEnd();itor++)
        {
            if(itor.value() == item)
            {
                return itor.key();
            }
        }
    }
}
