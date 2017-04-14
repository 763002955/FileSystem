#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <fstream>
#include <io.h>
#include<vector>
#include<string.h>
#include<QString>
#include<QDebug>
#include"main.h"
#include <sstream>
#include"errormess.h"
using namespace std;

typedef struct Node Node;
typedef  Node* fileList;


class directory
{
private:
    const int DISK_SIZE = 128 * 1024;
    //常量：块的大小  单位为B
    const int BLOCK_SIZE = 32;
    //常量：块的数量
    const int DIRECTORY_INFO = 0;
    const int FILE_INDEX = 1;
    const int FILE_CONTENT=3;
    //磁盘中位图所在位置
    const int BIT_MAP = 2;
    //常量：块的数量
    const int BLOCK_NUM = DISK_SIZE / BLOCK_SIZE;
    //常量：磁盘路径
    const string DISK = "Disk.txt";
    fileList filelist;//头结点
    fileList direct_path;//记录目录节点
    static directory *incetence;
public:
    directory();
    //读取disk磁盘获得磁盘存储，文件目录，位图，文件内容等信息
    vector<string> readDisk();
    //根据磁盘中读取的文件以及目录信息，创建文件树
    void createFileTree();
    //清空链表
    void clearList();

    static directory *getIncetence();

    //获得子节点们
    vector<string> getSons(string input_path);
    //获得path对应的目录节点
    fileList getDirectNode(string input_path);
    //获得现在路径
    string getCurrentPath();
    //由输入参数节点 获得 该节点的完整路径
    string getFullPathByNode(fileList node);
    //新建一个文件或目录---即再文件树中创建一个新节点
    int newNode(string father_path, string name);
    //根据输入的部分路径  获得该节点的完整路径
    string getFullPathByInput(string input_path);
    //通过输入的路径 找到该节点
    fileList getNodeByInput(string input_path);
    //判断是否为文件
    bool isFile(string name);
    //目录路径最后有一个/，为了得到目录的名字，去掉/
    string getDirectorySelfName(string name);
    //判断是否重名
    bool isSameName(string name1, string name2);
    //更新磁盘
    void writeToDisk(vector<string> buffer);
    //更新文件系统
    void updateFileSys();
    //在磁盘中新建一个文件
    void createFileInDisk(string full_name);
    //更新文件内容
    int updateFile(string input_path, string content);
    //删除文件
    int deleteFile(string input_path);
    //删除文件夹
    int deleteFolder(string input_path);
    //删除节点---通过判断是否为文件转入删除文件以及删除文件夹两个函数
    int deleteNode(string input_path);
    //字符串转换为数字
    int stringToInt(string temp);
    //更改路径
    bool changeCurrentPath(string input_path);
    bool isInputPathExisting(string input_path);
    string intToString(int temp);
    string readFileContent(string input_path);
    //重命名
    int renameNode(string input_path, string target_name);
    //剪切
    int cutNode(string source_path, string target_path);
    //复制
    int copyNode(string source_path, string target_path);
};

#endif // DIRECTORY_H
