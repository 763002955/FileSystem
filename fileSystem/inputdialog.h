#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
class inputDialog;
}

class inputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit inputDialog(QWidget *parent = 0);
    ~inputDialog();
    void changeLabel(QString mes);
    QString getName();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::inputDialog *ui;
    QString name;
};

#endif // INPUTDIALOG_H
