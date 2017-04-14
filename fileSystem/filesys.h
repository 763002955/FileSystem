#ifndef FILESYS_H
#define FILESYS_H

#include "directory.h"
#include <QString>
#include<string.h>
#include"main.h"
#include"openedfile.h"
#include"file.h"
class fileSys
{

private:
    static fileSys *fsystem;
    directory *direct;
    string last_path = "/";//原先的路径（仅剪切和复制需要用到）
    string present_path = "/";//当前路径
    openedFile *openedFileList;
    //记录发生剪切/粘贴操作
    int flag;
public:
    //记录当前路径，并标志该文件进行的是复制操作
    void setFlagCopy(){flag = 0;setLastPath();}
    //记录当前路径，并标志该文件进行的是剪切操作
    void setFlagCut(){flag = 1;setLastPath();}
    //创建节点(文件/文件夹)
    int createNode(QString path );
    static fileSys *getFileSys();
    //获得现在路径
    QString getPresentPath(){ return QString::fromStdString(present_path); }
    //获得子节点路径
    vector<QString> getSonPath(QString full_path);
    //通过输入路径找到该路径下文件或文件夹们
    bool setPresentPath(QString required_path);
    //打开文件
    bool openFile(QString name);
    //判断文件是否打开
    bool isFileOpened(string file_path, string file_name);
    //删除
    bool deleteDirectory(QString full_path);
    QString showContent(QString full_path);
    void setLastPath();
    int copyOrMove(QString file_name);
    int copy(QString full_name);
    int move(QString full_name);
    fileSys();
    bool rename(QString full_name, QString new_name);
    string cutSpace(string name);
    bool changeContent(QString full_path, QString content);
    bool closeFile(QString path);

};

#endif // FILESYS_H
