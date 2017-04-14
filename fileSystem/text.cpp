#include "text.h"
#include "ui_text.h"
#include<QMouseEvent>
text::text(QWidget *parent, QString Str) :
    QWidget(parent),
    ui(new Ui::text)
{

    //cout<<"in txt"<<endl;
    ui->setupUi(this);
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(CloseOP()));
    ui->textEdit->setPlainText(Str);
    connect(ui->closeWin, SIGNAL(clicked()), this, SLOT(closeWindow()));
}

text::~text()
{
    delete ui;
}


//重写鼠标按下事件
void text::mousePressEvent(QMouseEvent *event)
{

        if (event->button() == Qt::LeftButton)
        {
            sonMoving = true;
            sonMovePosition = event->pos();
        }

}
// 若鼠标左键被按下，移动窗体位置
void text::mouseMoveEvent(QMouseEvent *event)
{
    if (sonMoving)
        move(event->pos() - sonMovePosition + pos());
}

// 设置鼠标未被按下
void text::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    sonMoving = false;
}

void text::closeWindow()
{
    cout<<"try to close text window"<<endl;


        QString dir = this->property("dir").toString();

        if(!fileSys::getFileSys()->changeContent(dir,ui->textEdit->toPlainText()))
        {
            errorMess mes;
            mes.show();
            mes.changeLabel("磁盘大小不足，无法保存，是否继续");
            if(mes.exec())
            {
                fileSys::getFileSys()->closeFile(dir);

                return ;
            }
            this->close();
        }

        fileSys::getFileSys()->closeFile(dir);
        qDebug() << ui->textEdit->toPlainText();

        this->close();


   cout<<"closeop end"<<endl;
}

void text::changeTitle(QString str)
{
    ui->title->setText(str);
}
