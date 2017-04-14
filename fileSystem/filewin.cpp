#include "filewin.h"
#include "ui_filewin.h"
#include"inputdialog.h"
#include<QDebug>
#include<QTextCodec>
#include<QDialog>
#include<QMouseEvent>
fileWin::fileWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileWin)
{
    ui->setupUi(this);
    qDebug()<<"file！！！"<<endl;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //自定义右键菜单
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);//选中高亮
    this->createRightTable();
    this->max = false;
    this->location = this->geometry();
    this->setWindowOpacity(1);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setProperty("CanMove",true);
    this->setProperty("Form", true);
    ui->tableWidget->setProperty("CurDir","/");
    setTree();
}

fileWin::~fileWin()
{
    delete ui;
}

void fileWin::showErrorMess(int state)
{
    //显示创建信息
    switch(state)
    {
        case SUCCESS:
            mes.show();
            mes.changeLabel("创建成功");

            break;
        case invalidName:
            mes.show();
            mes.changeLabel("名字不符合规则");
            break;

        case OUT_OF_DISK_CPACITY:
            mes.show();
            mes.changeLabel("磁盘装不下");
            break;

        case SAME_NAME_EXISTS_PROBLEM:
            mes.show();
            mes.changeLabel("重名");
            break;
        case NotExit:
            mes.show();
            mes.changeLabel("不存在的");
            break;

        case FILE_OPENED:
            mes.show();
            mes.changeLabel("文件已打开");
            break;
    }
}

void fileWin::createRightTable()
{
    qDebug()<<"创建右击菜单！！"<<endl;

    rightMenu = new QMenu();

    createFile = new QAction("新建文本文档",this);
    createFolder = new QAction("新建文件夹",this);

    openFile = new QAction("打开",this);
    deleteFile = new QAction("删除",this);

    cutFile = new QAction("剪切",this);
    pasteFile = new QAction("粘贴",this);
    copyFile = new QAction("复制",this);

    renameFile = new QAction("重命名",this);
    deleteFile->setShortcut(QKeySequence::Delete);

    //关联点击事件
    connect(createFile,SIGNAL(triggered()), this, SLOT(create_file()));
    connect(createFolder,SIGNAL(triggered()), this, SLOT(create_folder()));
    connect(openFile,SIGNAL(triggered()), this, SLOT(open_file()));
    connect(deleteFile,SIGNAL(triggered()), this, SLOT(delete_file()));
    connect(cutFile,SIGNAL(triggered()), this, SLOT(cut_file()));
    connect(copyFile,SIGNAL(triggered()), this, SLOT(copy_file()));
    connect(pasteFile,SIGNAL(triggered()), this, SLOT(paste_file()));
    connect(renameFile,SIGNAL(triggered()), this, SLOT(rename_file()));
    qDebug()<<"windows_Form::create_Item_Action end"<<endl;

    rightMenu->addAction(createFile);
}

void fileWin::create_file()
{
    qDebug()<<"create a file slot!"<<endl;

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");


    input.changeLabel("请输入文件名：");
    input.show();
    input.exec();
    int state;
    QString name = input.getName();
    qDebug()<<"name!!!!!"<<name<<name.length()<<endl;


    if(name.length() != 0 && name!="")
    {
        state = fileSys::getFileSys()->createNode(name);
        qDebug()<<"state!!!"<<state<<endl;
    }
    if(name==""||name.length() == 0)
        state=invalidName;
    showErrorMess(state);
    setTree();
}

void fileWin::create_folder()
{
    qDebug()<<"create a folder slot!"<<endl;
    input.changeLabel("请输入文件夹名：");
    input.show();
    input.exec();

    QString name = input.getName();
    name=name.append("/");

    qDebug()<<"name!!!!!"<<name<<name.length()<<endl;
    int state;
    if(name.length() != 0)//尝试创建一个目录
    {
        state = fileSys::getFileSys()->createNode(name);
        qDebug()<<"state!!!"<<state<<endl;
    }
    showErrorMess(state);


    setTree();
}

void fileWin::open_file()
{
    qDebug()<<"open a file slot!"<<endl;

    QString dir = ui->tableWidget->property("CurDir").toString();
    dir.append(rightMenu->property("dir").toString());
    showContext(dir);

}

//删除
void fileWin::delete_file()
{
    qDebug()<<"delete a file slot!"<<endl;
    QString dir = rightMenu->property("dir").toString();
    qDebug()<<"dir:::"<<dir<<endl;
    if(fileSys::getFileSys()->deleteDirectory(dir))
    {
        mes.show();
        mes.changeLabel("sucess");
    }

    else
    {
        mes.show();
        mes.changeLabel("shibai");
    }
    showContext(ui->tableWidget->property("CurDir").toString());
    setTree();
    cout<<"windows_Form::FileDelete end"<<endl;
}

//剪切---就是先保留现在的路径
void fileWin::cut_file()
{
    qDebug()<<"cut a file slot!"<<endl;
    fileSys::getFileSys()->setFlagCut();
}

//复制---和剪切预处理一样，都是把当下的路径保存
void fileWin::copy_file()
{
    qDebug()<<"copy a file slot!"<<endl;
    fileSys::getFileSys()->setFlagCopy();
}

void fileWin::paste_file()
{
    qDebug()<<"粘贴 a file slot!"<<endl;

    QString dir = rightMenu->property("dir").toString();

    int state = fileSys::getFileSys()->copyOrMove(dir);
    showErrorMess(state);


    setTree();
    showContext(ui->tableWidget->property("CurDir").toString());

}

//重命名
void fileWin::rename_file()
{
    qDebug()<<"rename a file slot!"<<endl;
    input.changeLabel("请输入新的文件名：");
    input.show();
    input.exec();
    QString names = input.getName();

    QString dir = ui->tableWidget->property("CurDir").toString();
    dir.append(rightMenu->property("dir").toString());
    bool flag;

    bool state = false;
    if(flag && names.length() != 0)
        state = fileSys::getFileSys()->rename(dir,names);
    if(state == false) {
        mes.show();
        mes.changeLabel("重命名失败!");
    }
    showContext(ui->tableWidget->property("CurDir").toString());

}

void fileWin::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    QTableWidgetItem *item = ui->tableWidget->itemAt(pos);
    if (item!=NULL)
    {
        rightMenu->setProperty("dir",ui->tableWidget->property(QString::number(item->row()).toLatin1().data()).toString());

        rightMenu->addAction(openFile);
        rightMenu->addAction(deleteFile);

        rightMenu->addSeparator();

        rightMenu->addAction(copyFile);
        rightMenu->addAction(cutFile);
        rightMenu->addAction(pasteFile);
        rightMenu->addAction(renameFile);

    }
    else
    {
        rightMenu->addAction(createFile);
        rightMenu->addAction(createFolder);
    }
    rightMenu->exec(QCursor::pos());
}

void fileWin::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

    qDebug()<<item->text(0)<<endl;
    showContext(item->data(0,12).toString());
    ui->lineEdit->setText(ui->tableWidget->property("CurDir").toString());

}

void fileWin::showContext(QString direct)//显示文件夹下内容，或者文件内容
{
    qDebug()<<"mulu!..."<<direct<<endl;

    QRegExp file("/$");
    int pos = file.indexIn(direct);

    if(pos > -1)//文件夹
    {
        //记得在双击树的时候，设置当前路径
        if(!fileSys::getFileSys()->setPresentPath(direct))
            return ;

        ui->tableWidget->setProperty("CurDir",direct.toLatin1().data());
        //清空tablewidget
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        //设定tablewidget的行数
        ui->tableWidget->setColumnCount(2);
        vector<QString> meslist = fileSys::getFileSys()->getSonPath(direct);

        //将得到的vector中的值一行一行的添加到tablewidget中
        int goal = meslist.size();
        for(int i = 0;i < goal;i++)
            {
                ui->tableWidget->insertRow(i);

                QTableWidgetItem *names = new QTableWidgetItem();
                QTableWidgetItem *property = new QTableWidgetItem();
                QRegExp file1("/$");
                int pos1 = file1.indexIn(meslist.at(i));
                if(pos1>-1)
                    names->setText(meslist.at(i).section("",0,-3));
                else
                    names->setText(meslist.at(i));

                if(pos1<=-1)
                    property->setText("文件");
                else
                    property->setText("文件夹");

                ui->tableWidget->setItem(i, 0, names);
                ui->tableWidget->setItem(i, 1, property);

                //将当前行与当前文件夹的名字所绑定
                ui->tableWidget->setProperty(QString::number(i).toLatin1().data(),meslist.at(i));
            }
    }

    else//文件
    {
        QString curdir;
        QString filename;
        if(splitDir(direct,curdir,filename)){
            if(fileSys::getFileSys()->setPresentPath(curdir))
            {
                if(!fileSys::getFileSys()->openFile(filename))
                {

                    fileSys::getFileSys()->setPresentPath(ui->tableWidget->property("CurDir").toString());
                }
                else{

                        QString tempdir = fileSys::getFileSys()->showContent(direct);
                        text *mesShow = new text(this,tempdir);
                        mesShow->changeTitle(filename);
                        mesShow->setProperty("id","1");//通过用属性来传递进程号和文件路径
                        mesShow->setProperty("dir",direct);
                        mesShow->show();

                        //打开文件后，返回当前路径
                        fileSys::getFileSys()->setPresentPath(ui->tableWidget->property("CurDir").toString());
                    }


                }

        }

    }
}


void fileWin::setTree()
{
    qDebug()<<"in windows_Form::SetTree"<<endl;
    QTreeWidget *treeWidget = ui->treeWidget;
    treeWidget->clear();

    treeWidget->setWindowTitle("QTreeWidget");
    fileSys *fm = fileSys::getFileSys();
    string father_path = "/";
    string current_path = "";
    vector<string> temp_string;
    //设定顶层项
    QTreeWidgetItem *head =new QTreeWidgetItem(QStringList()<<"..");
    head->setData(0,12,"/");
    head->setIcon(0,QIcon(":/windows/windows/dir.png"));
    treeWidget->addTopLevelItem(head);

    QTreeWidgetItemIterator  it (treeWidget);
    vector<QString> temp_string_qs;

    while((*it))
    {
        QTreeWidgetItem *currentChild = (*it);
        father_path = currentChild->data(0,12).toString().toStdString();
        QString father_path_temp = QString::fromStdString(father_path);
        temp_string_qs = fm->getSonPath(father_path_temp);
        temp_string.clear();
        for(int i = 0; i < temp_string_qs.size();i++)
        {
            QString tmp = temp_string_qs[i];
            temp_string.push_back(tmp.toStdString());
            //cout << temp_string[i] << endl;
        }
        for (int i = 0; i < temp_string.size(); i++)
        {
            current_path = father_path+temp_string[i];
            QStringList columItemList;
            QTreeWidgetItem *child;
            QString key,value;
            QIcon temp_png;
            if(temp_string[i].substr(temp_string[i].length()-1,1) == "/")
            {
                key = QString::fromStdString(temp_string[i].substr(0,temp_string[i].length()-1));
                temp_png = QIcon(":/windows/windows/dir.png");
            }
            else
            {
                 key = QString::fromStdString(temp_string[i]);
                 temp_png = QIcon(":/windows/windows/file.png");
            }
            value = QString::fromStdString(current_path);
            columItemList << key;
            child = new QTreeWidgetItem(columItemList);
            child->setData(0,12,value);
            child->setIcon(0,temp_png);
            currentChild->addChild(child);
        }
        it++;
    }
    qDebug()<<"windows_Form::SetTree end"<<endl;
}

bool fileWin::splitDir(QString total,QString &dir,QString &names){
    QRegExp file("(.*/)([^/]*$)");
    int pos = file.indexIn(total);

    if(pos > -1){
        dir = file.cap(1);
        names = file.cap(2);
        return true;
    }
    return false;

}

void fileWin::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    cout<<"in windows_Form::on_tableWidget_doubleClicked"<<endl;
    QString dir = ui->tableWidget->property("CurDir").toString();
    dir.append(ui->tableWidget->property(QString::number(index.row()).toLatin1().data()).toString());
    showContext(dir);
    ui->lineEdit->setText(ui->tableWidget->property("CurDir").toString());
    cout<<"windows_Form::on_tableWidget_doubleClicked end"<<endl;
}

void fileWin::on_goToDirect_clicked()
{
    cout<<"in windows_Form::on_pushButton_3_clicked"<<endl;
    QString dir = ui->lineEdit->text();
    showContext(dir);
    cout<<"windows_Form::on_pushButton_3_clicked"<<endl;
}


void fileWin::on_backDirect_clicked()
{
    cout<<"in windows_Form::on_pushButton_clicked"<<endl;
    fileSys::getFileSys()->setPresentPath("../");
    QString dir = fileSys::getFileSys()->getPresentPath();
    ui->tableWidget->setProperty("CurDir",dir.toLatin1().data());
    ui->lineEdit->setText(dir);
    showContext(dir);
    cout<<"windows_Form::on_pushButton_clicked end"<<endl;
}

//重写鼠标按下事件
void fileWin::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mMovePosition = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

//重写鼠标移动事件
void fileWin::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)按下是左键
    //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (mMoveing && (event->buttons() && Qt::LeftButton)
        && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}
void fileWin::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
}

void fileWin::on_pushButton_clicked()
{
    this->close();
}

