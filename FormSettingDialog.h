#ifndef FORMSETTINGDIALOG_H
#define FORMSETTINGDIALOG_H

#include <QWidget>
#include <QDebug>
#include <QTreeWidgetItem>

#include "common_data.h"

namespace Ui {
class FormSettingDialog;
}

class FormSettingDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FormSettingDialog(QList<SerialPortTree> itemList,QWidget *parent = nullptr);
    ~FormSettingDialog();

signals:
    //void portSettingSignal(PortSettings setting);

    void addAddressSignal(QString port,QString address);

private slots:
    void on_btn_confirm_clicked();

public:
    void initSerialPort(QList<SerialPortTree> itemList);

private:
    Ui::FormSettingDialog *ui;
};

#endif // FORMSETTINGDIALOG_H
