#ifndef PORTMANAGECLASS_H
#define PORTMANAGECLASS_H

#include <QObject>

#include "common_data.h"

class PortManageClass : public QObject
{
    Q_OBJECT
public:
    explicit PortManageClass(QObject *parent = nullptr);

public:
    QSerialPort* setSerialPortInfo(PortSettings setting);

    QString getDeviceByName(QList<SerialPortTree> serialPertTree,QTreeWidgetItem *item);

signals:

public slots:
};

#endif // PORTMANAGECLASS_H
