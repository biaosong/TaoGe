#include "SetupFileClass.h"

SetupFileClass::SetupFileClass(QObject *parent) : QObject(parent)
{

}

void SetupFileClass::writeJsonFile(QList<SerialPortTree> serialPortTree)
{
    QJsonObject jsonObject;
    for(int index = 0;index < serialPortTree.count();index++)
    {
        QJsonObject subObject;
        subObject.insert("com",QJsonValue(QString("%1").arg(serialPortTree[index].settings.com)));
        subObject.insert("baudRate",QJsonValue(QString("%1").arg(serialPortTree[index].settings.baudRate)));
        subObject.insert("dataBits",QJsonValue(QString("%1").arg(serialPortTree[index].settings.dataBits)));
        subObject.insert("parity",QJsonValue(QString("%1").arg(serialPortTree[index].settings.parity)));
        subObject.insert("stopBits",QJsonValue(QString("%1").arg(serialPortTree[index].settings.stopBits)));
        subObject.insert("flowControl",QJsonValue(QString("%1").arg(serialPortTree[index].settings.flowControl)));
        if(serialPortTree[index].deviceMap.count())
        {
            QJsonArray arrayObject;
            QMap<QString,QTreeWidgetItem *>::const_iterator itor;
            for(itor = serialPortTree[index].deviceMap.constBegin();itor != serialPortTree[index].deviceMap.constEnd();itor++)
            {
                QJsonObject deviceObject;
                deviceObject.insert("deviceName",QJsonValue(QString("%1").arg(itor.value()->text(0))));
                deviceObject.insert("deviceAddress",QJsonValue(QString("%1").arg(itor.key())));
                arrayObject.append(deviceObject);
            }
            subObject.insert("Devices",arrayObject);
        }
        jsonObject.insert(QString("%1").arg(serialPortTree[index].serialPort->text(0)),QJsonValue(subObject));
    }

    //内存中的数据写到文件
    QJsonDocument doc(jsonObject);
    //将json对象转换成字符串
    QByteArray data=doc.toJson();
    QString txtFilePath = QDir::currentPath()+"/Setup";
    if(isDirExist(txtFilePath))
    {
        QFile file(txtFilePath+"/List.json");
        if(!file.open(QIODevice::WriteOnly | QFile::Truncate))
        {
            QMessageBox::about(nullptr, "文件", "文件打开失败");
        }
        QTextStream txtOutput(&file);
        file.write(data);
        file.close();
    }

}

QList<SerialPortTree> SetupFileClass::LoadJsonFile()
{
    QList<SerialPortTree> SerialPortTreeList;
    QString txtFilePath = QDir::currentPath()+"/Setup";
    QFile file(txtFilePath+"/List.json");
    if(file.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
    }
    QByteArray data=file.readAll();
    file.close();

    //使用json文件对象加载字符串
    QJsonParseError json_error;
    QJsonDocument jsonDocument=QJsonDocument::fromJson(data,&json_error);

    if (!jsonDocument.isNull() && (json_error.error ==QJsonParseError::NoError))
    {
        if(jsonDocument.isObject())
        {
            QJsonObject rootObj = jsonDocument.object();
            QStringList keys = rootObj.keys();

            for(int index = 0; index < keys.size(); index++)
            {
                SerialPortTree serialPortTree ;
                QTreeWidgetItem * treePort = new QTreeWidgetItem(QStringList(QString("%1").arg(keys.at(index))));
                serialPortTree.serialPort = treePort;
                ///读取串口
                if(rootObj.contains(keys.at(index)))
                {

                    QJsonValue serialPortObject = rootObj.value(keys.at(index));
                    qDebug() << "serialObject:          " << serialPortObject;
                    ///读取设备
                    if(serialPortObject.toObject().contains("Devices"))
                    {
                        QJsonArray deviceArray = serialPortObject.toObject().value("Devices").toArray();
                        for(int arrayNum=0; arrayNum < deviceArray.size();arrayNum++)
                        {
                            QJsonObject deviceObject = deviceArray[arrayNum].toObject();
                            QTreeWidgetItem * treePort = new QTreeWidgetItem(QStringList(QString("%1").arg(deviceObject.value("deviceName").toString())));
                            serialPortTree.deviceMap.insert(deviceObject.value("deviceAddress").toString(),treePort);
                        }
                    }
                    //PortSettings    *settings = new PortSettings;
                    if(serialPortObject.toObject().contains("com"))
                    {
                        QJsonValue value =  serialPortObject.toObject().value("com");
                        qDebug() << "value-com:          " << value;
                        serialPortTree.settings.com = value.toString();
                    }
                    if(serialPortObject.toObject().contains("baudRate"))
                    {
                        QJsonValue value =  serialPortObject.toObject().value("baudRate");
                        qDebug() << "value-baudRate:          " << value;
                        serialPortTree.settings.baudRate = value.toString();
                    }
                    if(serialPortObject.toObject().contains("dataBits"))
                    {
                        QJsonValue value =  serialPortObject.toObject().value("dataBits");
                        qDebug() << "value-dataBits:          " << value;
                        serialPortTree.settings.dataBits = value.toString().toInt();
                    }
                    if(serialPortObject.toObject().contains("parity"))
                    {
                        QJsonValue value =  serialPortObject.toObject().value("parity");
                        qDebug() << "value-parity:          " << value;
                        serialPortTree.settings.parity = value.toString().toInt();
                    }
                    if(serialPortObject.toObject().contains("stopBits"))
                    {
                        QJsonValue value =  serialPortObject.toObject().value("stopBits");
                        qDebug() << "value-stopBits:          " << value;
                        serialPortTree.settings.stopBits = value.toString().toInt();
                    }
                    if(serialPortObject.toObject().contains("flowControl"))
                    {
                        QJsonValue value =  serialPortObject.toObject().value("flowControl");
                        qDebug() << "value-flowControl:          " << value;
                        serialPortTree.settings.flowControl = value.toString().toInt();
                    }
                }
                SerialPortTreeList.append(serialPortTree);
            }
        }
    }
    return SerialPortTreeList;
}

void SetupFileClass::writeToCsvFileHandle(QMap<QDateTime, double> m_seriesPoint, int fileType)
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

bool SetupFileClass::isDirExist(QString fullPath)
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

QString SetupFileClass::getCurrentDatetimeForFile()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyyMMddhhmmss");
    return current_date;
}

QString SetupFileClass::getCurrentDatetimeForFolder()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd");
    return current_date;
}
