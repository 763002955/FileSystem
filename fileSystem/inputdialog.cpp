#include "inputdialog.h"
#include "ui_inputdialog.h"
#include<QDebug>
inputDialog::inputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputDialog)
{
    ui->setupUi(this);
}

inputDialog::~inputDialog()
{
    delete ui;
}

void inputDialog::changeLabel(QString mes)
{
    ui->hintLabel->setText(mes);
    qDebug()<<"mes"<<mes<<endl;

}

QString inputDialog::getName()
{
    return name;
}

void inputDialog::on_buttonBox_accepted()
{
    name = ui->inputLine->text();
    qDebug()<<"name:"<<name<<endl;
    this->close();
}
