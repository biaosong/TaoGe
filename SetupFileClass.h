#ifndef SETUPFILECLASS_H
#define SETUPFILECLASS_H

#include <QObject>

#include "common_data.h"

class SetupFileClass : public QObject
{
    Q_OBJECT
public:
    explicit SetupFileClass(QObject *parent = nullptr);

public:
    void writeJsonFile(QList<SerialPortTree> serialPortTree);

    QList<SerialPortTree> LoadJsonFile();

    void writeToCsvFileHandle(QMap<QDateTime,double> m_seriesPoint,int fileType);

    bool isDirExist(QString fullPath);

    QString getCurrentDatetimeForFile();
    QString getCurrentDatetimeForFolder();

signals:

public slots:
};

#endif // SETUPFILECLASS_H
