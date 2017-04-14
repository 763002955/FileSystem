#include "errormess.h"
#include "ui_errormess.h"

errorMess::errorMess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::errorMess)
{
    ui->setupUi(this);
}

errorMess::~errorMess()
{
    delete ui;
}

void errorMess::changeLabel(QString str)
{
    ui->label->setText(str);
}
