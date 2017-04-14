#ifndef FILEWIN_H
#define FILEWIN_H

#include <QWidget>
#include<QMenu>
#include<QPoint>
#include"inputdialog.h"
#include<qtreewidget.h>
#include"filesys.h"
#include"text.h"
#include <QList>
namespace Ui {
class fileWin;
}

class fileWin : public QWidget
{
    Q_OBJECT

public:
    explicit fileWin(QWidget *parent = 0);
    void createRightTable();
    void showContext(QString direct);
    void setTree();
    void showErrorMess(int state);
    bool splitDir(QString total,QString &dir,QString &names);
    ~fileWin();

private:
    Ui::fileWin *ui;
    inputDialog input;
    errorMess mes;
    QMenu *rightMenu;
    QAction *createFile;
    QAction *createFolder;

    QAction *renameFile;
    QAction *openFile;
    QAction *deleteFile;
    QAction *pasteFile;
    QAction *cutFile;
    QAction *copyFile;
    bool max;           //是否处于最大化状态
    QRect location;     //鼠标移动窗体后的坐标位置
    bool        mMoveing;
        QPoint      mMovePosition;

private slots:
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);
    void create_file();
    void create_folder();
    void rename_file();
    void open_file();
    void delete_file();
    void paste_file();
    void cut_file();
    void copy_file();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_goToDirect_clicked();

    void on_backDirect_clicked();

    void on_pushButton_clicked();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseMoveEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent(QMouseEvent *event);

};

#endif // FILEWIN_H
