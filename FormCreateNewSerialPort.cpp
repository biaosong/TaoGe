#include "FormCreateNewSerialPort.h"
#include "ui_Formcreatenewserialport.h"

FormCreateNewSerialPort::FormCreateNewSerialPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCreateNewSerialPort)
{
    ui->setupUi(this);
}

FormCreateNewSerialPort::~FormCreateNewSerialPort()
{
    delete ui;
}

void FormCreateNewSerialPort::on_btn_confirm_clicked()
{
    emit addSerialPortSignal(ui->serialPort_lineEdit->text()+ QStringLiteral("--串口"));
    this->close();
}

void FormCreateNewSerialPort::on_btn_cancel_clicked()
{
    this->close();
}
