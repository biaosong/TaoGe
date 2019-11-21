#include "FormSettingDialog.h"
#include "ui_FormSettingDialog.h"

#include <QtWidgets/qtreeview.h>
#include <QtWidgets/qtreewidgetitemiterator.h>

FormSettingDialog::FormSettingDialog(QList<SerialPortTree> itemList,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSettingDialog)
{
    ui->setupUi(this);
    initSerialPort(itemList);
}

FormSettingDialog::~FormSettingDialog()
{
    delete ui;
}

void FormSettingDialog::on_btn_confirm_clicked()
{
    QString currentCom = ui->comboBox_COM->currentText();
    emit addAddressSignal(currentCom,ui->lineEdit->text() + QStringLiteral("--设备"));
    this->close();
}

/*
 *@功能:  初始化串口列表
 *@参数:
 *@返回值:
*/
void FormSettingDialog::initSerialPort(QList<SerialPortTree> itemList)
{
    for(int index = 0 ;index < itemList.count(); index++)
    {
        ui->comboBox_COM->addItem(itemList[index].serialPort->text(0));
    }
}
