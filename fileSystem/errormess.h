#ifndef ERRORMESS_H
#define ERRORMESS_H

#include <QDialog>

namespace Ui {
class errorMess;
}

class errorMess : public QDialog
{
    Q_OBJECT

public:
    explicit errorMess(QWidget *parent = 0);
    void changeLabel(QString str);
    ~errorMess();

private:
    Ui::errorMess *ui;
};

#endif // ERRORMESS_H
