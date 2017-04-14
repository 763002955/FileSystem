#include "filesys.h"
#include<string.h>
#include<QDebug>
fileSys::fileSys()
{
    openedFileList = new openedFile();
    direct = directory::getIncetence();
}

fileSys *fileSys::fsystem = new fileSys();//实例化

fileSys *fileSys::getFileSys()
{
    if(fsystem == NULL)
    {
        fsystem = new fileSys();
    }
    return fsystem;
}


bool fileSys::setPresentPath(QString required_path)
{
    string require_path = required_path.toStdString();
    //判断该文件夹是否存在
    if (direct->changeCurrentPath(require_path))
    {
        //更改当前文件夹
        present_path = direct->getCurrentPath();
        return true;
    }
    else
    {
        qDebug() << "the directory cannot be found" << endl;
        return false;
    }
}

int fileSys::createNode(QString path )
{
    qDebug()<<"create a node!!!"<<endl;
    //将QString转换为string
    string name = path.toStdString();
    qDebug()<<"=====name---"<<QString::fromStdString(name)<<endl;
    //先判断名字是否合法,即是否含有非法字符
    string s;
    for(int i=0;i<path.length();i++)
    {
        //依次选取第i个字符
        s=name.substr(i,1);
        //暂时只支持字母和文字
        if((s>="0"&&s<="9")||(s>="a"&&s<="z")||(s>="A"||s<="Z"))
        {

        }
        else
            return invalidName;
    }

    string temp_path = direct->getCurrentPath();
    int state = direct->newNode(temp_path, name);
    qDebug()<<"=====name---"<<QString::fromStdString(name)<<"state---"<<state<<endl;
    return state;
}

//获取当前路径下的子路径
vector<QString> fileSys::getSonPath(QString full_path)
{
    vector<QString> temp_ret;
    string full_path_temp = full_path.toStdString();
    vector<string> string_temp = direct->getSons(full_path_temp);

    vector<string> sort;
    for(int i = 0;i<string_temp.size();i++)
    {
        string temp_name = string_temp[i];
        if(temp_name.substr(temp_name.length()-1,1) == "/")
        {
            sort.push_back(temp_name);
        }
    }
    for(int i = 0;i<string_temp.size();i++)
    {
        string temp_name = string_temp[i];
        if(temp_name.substr(temp_name.length()-1,1) != "/")
        {
            sort.push_back(temp_name);
        }
    }
    string_temp = sort;
    for(int i = 0;i<string_temp.size();i++)
    {
        temp_ret.push_back(QString::fromStdString(string_temp[i]));
    }

    return temp_ret;
}

bool fileSys::openFile(QString name)
{
    string file_name = name.toStdString();
    string file_name_temp = present_path + file_name;
    //该文件不存在
    if (direct->isInputPathExisting(file_name_temp) == false)
    {
        qDebug() << "error:the file do not exist" << endl;
        return false;
    }
    //该文件存在
    else
    {
        //判断该文件是否已经被打开
        if (isFileOpened(present_path, file_name))
        {
            return false;
        }
        //文件未被打开
        else
        {
            File *temp_file = new File(present_path, file_name);
            //新建打开链表的结点
            openedFile *temp = openedFileList;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            //插入到打开文件链表
            openedFile *temp_openedFile = new openedFile(temp_file);
            temp->next = temp_openedFile;
            return true;
        }
    }
}

bool fileSys::isFileOpened(string file_path, string file_name)
{
    openedFile *temp = openedFileList->next;
    //遍历链表中的所有结点，判断该文件是否打开
    while (temp != NULL)
    {
        if (temp->getFile()->getPath() == file_path && temp->getFile()->getName() == file_name)
        {
            //cout << "find" << endl;
            qDebug()<<"not opened!!!!!"<<endl;
            return 1;
        }
        temp = temp->next;
    }
    //cout << "not find" << endl;
    return 0;
}

bool fileSys::deleteDirectory(QString full_path)
{
    qDebug()<<"delete directory!!!in file sysy"<<endl;
    string full_name = full_path.toStdString();
    string file_name = full_name;
    qDebug()<<"full_name:"<<QString::fromStdString(full_name)<<"-----"<<QString::fromStdString(file_name.substr(file_name.length()-1.1))<<endl;

    if (file_name.substr(file_name.length()-1.1) == "/")
    {
        full_name = present_path + full_name;
        int state = direct->deleteNode(full_name);
        if (state == SUCCESS)
            return 1;
        else
            return 0;
    }
    else
    {
        qDebug()<<"file_name.substr(file_name.length()-1.1)"<<endl;
        string file_name_temp = present_path + file_name;
        qDebug()<<"full_name:"<<QString::fromStdString(file_name_temp)<<endl;
        qDebug()<<direct->isInputPathExisting(file_name_temp)<<endl;
        //该文件不存在
        if (direct->isInputPathExisting(file_name_temp) == false)
        {
            return false;
        }
        //该文件存在
        else
        {
            qDebug()<<QString::fromStdString(present_path)<<endl;
            qDebug()<<QString::fromStdString(file_name)<<endl;
            qDebug()<<isFileOpened(present_path, file_name)<<endl;
            //判断该文件是否已经被打开
            if (isFileOpened(present_path, file_name))
            {
                qDebug() << "the file has been opened" << endl;
                return false;
            }
            //文件未被打开
            else
            {
                full_name = present_path + file_name;
                qDebug()<<"full_name:"<<QString::fromStdString(full_name)<<endl;
                int state = direct->deleteNode(full_name);
                if (state == SUCCESS)
                    return 1;
                else
                    return 0;
            }
        }
    }
    qDebug()<<"delete directory ovver !!!!"<<endl;
}

void fileSys::setLastPath()
{
    last_path = direct->getCurrentPath();
}

int fileSys::copyOrMove(QString file_name)
{
    //copy
    if(flag == 0)
    {
        return copy(file_name);
    }
    //move
    else if(flag == 1)
    {
        return move(file_name);
    }
    else
    {
        return 0;
    }
}

bool fileSys::rename(QString full_name, QString new_name)
{
    string full_name_temp = full_name.toStdString();
    string new_name_temp = new_name.toStdString();
    new_name_temp = cutSpace(new_name_temp);
    if (isFileOpened(present_path, full_name_temp))
        return 0;

    int state = direct->renameNode(full_name_temp, new_name_temp);

    if (state == SUCCESS)
        return 1;
    else    
        return 0;

}

int fileSys::copy(QString full_name)
{
    //判断是否有源文件进入复制缓冲
    if(last_path == "")
    {
        return NO_DATA_IN_BUFFER;
    }
    string full_name_temp = full_name.toStdString();
    //判断源文件是否被打开
    if (isFileOpened(last_path, full_name_temp))
    {
        cout << "error:the file is opened" << endl;
        return FILE_OPENED;
    }
    string sourse, target;

    sourse = last_path + full_name_temp;
    target = present_path;

    int state = direct->copyNode(sourse, target);
    if (state == SUCCESS)
    {
    }
    else if (state == RIGHT_PROBLEM)
    {
        cout << "error:the operation is denied" << endl;
    }
    else if (state == NotExit)
    {
        cout << "error : target does not exist" << endl;
    }
    else if (state == SAME_NAME_EXISTS_PROBLEM)
    {
        cout << "error:the directory(file) exists" << endl;
    }
    else if (state == OUT_OF_DISK_CPACITY)
    {
        cout << "error::no enough hard disk space" << endl;
    }
    else if (state == TARGET_DIRECTORY_INVALID) {

    }
    else
    {
    }
    return state;
}

int fileSys::move(QString full_name)
{
    //判断是否有源文件进入剪切缓冲
    if(last_path == "")
    {
        return NO_DATA_IN_BUFFER;
    }
    string full_name_temp = full_name.toStdString();
    //判断源文件是否被打开
    if (isFileOpened(last_path, full_name_temp))
    {
        cout << "error:the file is opened" << endl;
        return FILE_OPENED;
    }
    string sourse, target;
    sourse = last_path + full_name_temp;
    target = present_path;
    int state = direct->cutNode(sourse, target);

    return state;
    last_path = "";
}


QString fileSys::showContent(QString full_path)
{
    string full_name = full_path.toStdString();
    openedFile *temp = openedFileList->next;
    string temp_full_path;
    while (temp != NULL)
    {
        temp_full_path = temp->getFile()->getPath()+ temp->getFile()->getName();
        if(temp_full_path == full_name)
        {
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        cout << "error:the file is not opened" << endl;
        return "";
    }
    string content = direct->readFileContent(full_name);
    qDebug()<<"context!!!!!"<<QString::fromStdString(content)<<endl;
    for(int i = 0;i < (int)content.length()-1;i++)
    {
        //将回车符变为"\n"正常显示
        if(content.substr(i,1) == "\\" && content.substr(i+1,1) == "n")
            {
                content = content.substr(0,i)+"\n"+content.substr(i+2,content.length()-i-2);
            }
    }
    QString str;
    str = QString::fromStdString(content);
    return str;

}


bool fileSys::changeContent(QString full_path, QString content)
{
    string full_path_temp = full_path.toStdString();
    string content_temp = content.toStdString();
    openedFile *temp = openedFileList->next;
    string tmp;
    while (temp != NULL)
    {
        tmp = temp->getFile()->getPath()+temp->getFile()->getName();
        if(tmp == full_path_temp)
        {
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        cout << "error:the file is not opened" << endl;
        return 0;
    }
    //将存入磁盘的回车符变为“\n”存储
    for(int i = 0;i<content_temp.length();i++)
    {
        if(content_temp.substr(i,1) == "\n")
        {
            content_temp = content_temp.substr(0,i)+"\\n"+content_temp.substr(i+1,content_temp.length()-i-1);
        }
    }
    qDebug()<<"update file!!!"<<QString::fromStdString(full_path_temp)<<" "<<QString::fromStdString(content_temp)<<endl;
    int state = direct->updateFile(full_path_temp,content_temp);
    if (state == SUCCESS)
    {
        return 1;
    }
    else if (state == RIGHT_PROBLEM)
    {
        cout << "error:the operation is denied" << endl;
        return 0;
    }
    else if (state == NotExit)
    {
        cout << "error : target does not exist" << endl;
        return 0;
    }
    else if (state == OUT_OF_DISK_CPACITY)
    {
        cout << "error::no enough hard disk space" << endl;
        return 0;
    }
    else
    {
        return 0;
    }
}

bool fileSys::closeFile(QString path)
{
    string file_path = path.toStdString();
    if (file_path == "quit")
    {
        return 0;
    }
    //遍历打开文件链表
    openedFile *temp_file = openedFileList->next;
    openedFile *last_file = openedFileList;
    string temp;
    while (temp_file != NULL)
    {
        temp = temp_file->getFile()->getPath()+temp_file->getFile()->getName();
        //该文件已被打开
        if(temp == file_path)
        {
            break;
        }
        last_file = temp_file;
        temp_file = temp_file->next;
    }
    if (temp_file == NULL)
    {
        cout << "error:the file do not open" << endl;
        return false;
    }
    else
    {
        last_file->next = temp_file->next;
        return true;
    }
}
string fileSys::cutSpace(string name)
{
    //剪去字符串开头的空格
    while(name.substr(0,1) == " ")
    {
        name = name.substr(1,name.length()-1);
    }
    //判断该字符串是文件夹名还是文件名
    //删去末尾空格
    if(name.substr(name.length()-1,1) == "/")
    {
        while(name.substr(name.length()-2,1) == " ")
        {
            name = name.substr(0,name.length()-2)+"/";
        }
    }
    else
    {
        while(name.substr(name.length()-1,1) == " ")
        {
            name = name.substr(0,name.length()-1);
        }
    }
    return name;
}



