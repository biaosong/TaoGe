#ifndef FORMCREATENEWSERIALPORT_H
#define FORMCREATENEWSERIALPORT_H

#include <QWidget>

namespace Ui {
class FormCreateNewSerialPort;
}

class FormCreateNewSerialPort : public QWidget
{
    Q_OBJECT

public:
    explicit FormCreateNewSerialPort(QWidget *parent = nullptr);
    ~FormCreateNewSerialPort();

signals:
    void addSerialPortSignal(QString serialPortName);

private slots:
    void on_btn_confirm_clicked();

private:
    Ui::FormCreateNewSerialPort *ui;
    QString                                         m_address;
};

#endif // FORMCREATENEWSERIALPORT_H
