#ifndef FILE_H
#define FILE_H

#include<iostream>
using namespace std;

class File
{
private:
    string path;
    string name;
    int property;
public:
    //创建文件对象
    File(string path, string name);
    //读取文件路径
    string getPath(){ return path; }
    //读取文件名字
    string getName(){ return name; }
    //将insert_content的字符串数组插入到该文件尾，每个string占一行，若成功则返回true
    //若插入失败则返回false
    bool insertToFile(string* insert_content, int content_size);

    ~File();
};

#endif // FILE_H
