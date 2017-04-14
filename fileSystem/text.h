#ifndef TEXT_H
#define TEXT_H
#include"filewin.h"
#include <QWidget>

namespace Ui {
class text;
}

class text : public QWidget
{
    Q_OBJECT

public:

    explicit text(QWidget *parent, QString Str);
    void changeTitle(QString str);
    ~text();


private:
    Ui::text *ui;
    bool        sonMoving;
    QPoint      sonMovePosition;

private slots:
        void closeWindow();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);


};

#endif // TEXT_H
