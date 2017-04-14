#include "directory.h"
#include<stdlib.h>
#include<iostream>
using namespace std;
typedef struct Node {
    string name;
    Node *child;
    Node *brother;
    Node *father;
}Node;

//实例化一个链表存储文件结构
typedef Node* fileList;
directory *directory::incetence = new directory();


directory::directory()
{
    qDebug()<<"initial direct!"<<endl;
    filelist = new Node;
    filelist->name = "/";
    filelist->brother = NULL;
    filelist->child = NULL;
    filelist->father = NULL;
    direct_path = filelist;
    //readDisk();
    createFileTree();
}

//更改当前路径，若输入的路径不存在则返回false
bool directory::changeCurrentPath(string input_path)
{
    fileList ans = getNodeByInput(input_path);
    if (NULL == ans) {
        return false;
    }
    else {
        direct_path = ans;
        return true;
    }
}

directory *directory::getIncetence()
{
    if(incetence == NULL)
    {
        incetence = new directory();
    }
    return incetence;
}

//从磁盘中读取目录和文件信息
vector<string> directory::readDisk()
{
    //使用容器
    vector<string> string_buffer;
    string buffer;
    ifstream in("Disk.txt");
    if (in.is_open()) {
        for (int i = 0; i <= DISK_SIZE / BLOCK_SIZE + 3; i++) {
            getline(in, buffer);
            string_buffer.push_back(buffer);
            //cout<<"buffer---"<<buffer<<endl;
        }
        in.close();
    }
    return string_buffer;
}

void directory::createFileTree()
{
    //需要先清空原来的链表
    clearList();
    //将读取到vector中的信息转换成链表
    vector<string> list = readDisk();
    string directory = list[DIRECTORY_INFO];

    int ff = 0, fl = 0, cf = 0, cl = 0;
    //父亲名字 ff~fl  孩子名字 cf~cl
    qDebug()<<"create file tree!"<<list.size()<<endl;
    for(int i = 0;i < (int)directory.size();i++)
    {
        qDebug()<<"directory[i]"<<directory[i]<<endl;
         if( directory[i] == '<')
         {
             ff=i+1;
         }
         else if( directory[i] == ',')
         {
             cf=i+1;
             fl=i;

         }
         else if( directory[i] == '>')
         {
             cl=i;
             if( ff < fl && cf < cl)
             {
                 fileList temp = filelist;
                 //得到父亲和孩子节点的路径名
                 string f = directory.substr(ff, fl - ff);
                 string c = directory.substr(cf, cl - cf);
                 //cout<<f<<"   "<<c<<endl;
                 qDebug()<<"f.size"<<f.size()<<endl;

                 for(int j= 0; j<(int)f.size(); j = (int)f.find('/',j)+1)
                 {
                     qDebug()<<"j---"<<j<<endl;
                     string temp_path = f.substr(j, (int)f.find('/', j) - j + 1);
                     qDebug()<<"temp_path"<< QString::fromStdString(temp_path)<<endl;

                     if (j!=0) {
                         temp = temp->child;
                     }

                     qDebug()<<QString::fromStdString(temp->name)<<endl;
                     while (temp!=NULL && temp_path != temp->name)
                         temp = temp->brother;
                 }
                 //父路径节点下无孩子节点时，创建该子节点并赋值
                 qDebug()<<"111"<<endl;
                 if (temp->child == NULL) {
                     temp->child = new Node;
                     temp->child->father = temp;
                     temp = temp->child;
                 }
                 //父路径下有孩子节点时，找到该孩子节点的最后一个兄弟节点，创建该节点的兄弟节点的并赋值

                 else {
                     fileList father_node = temp;
                     temp = temp->child;
                     while (temp->brother!=NULL) {
                         temp = temp->brother;
                     }
                     temp->brother = new Node;
                     temp->brother->father = father_node;
                     temp = temp->brother;
                 }
                 temp->name = c;
                 temp->brother = NULL;
                 temp->child = NULL;
                 qDebug()<<"333"<<endl;
             }
         }
    }
}

void directory::clearList()
{
    //清空fileList
    //中序遍历目录链表，逐个删除
    fileList current = filelist;
    fileList stack[2000];
    int top = 0;
    while (0 != top || NULL != current) {
        if (NULL == current) {
            current = stack[--top];
        }
        else {
            fileList temp = current;
            stack[top++] = current->brother;
            current = current->child;
            if ("/" != temp->name) {
                delete(temp);
            }
            else {
                temp->child = NULL;
                temp->brother = NULL;
            }
        }
    }
}

//获取相对路径对应的目录节点，若该目录节点不存在，则返回NULL
fileList directory::getDirectNode(string input_path)
{
    fileList ans = NULL;
    //若输入路径为绝对路径，则从根目录开始计算
    if (0 < input_path.length() && '/' == input_path[0]) {
        input_path = input_path.substr(1, (int)input_path.size() - 1);
        ans = filelist;
    }
    //否则该路径为相对路径，则从当前路径开始计算
    else {
        ans = direct_path;
    }
    //pos指向子路径开始处，next_pos指向下一子路径开始处
    int pos = 0, next_pos = 0;
    //temp_path表示当前子路径
    string temp_path;
    //标识是否读取了文件名
    bool over = true;
    for (pos = 0; pos <= (int)input_path.size() - 1; pos = next_pos) {
        //读取到文件名
        if (string::npos == input_path.find('/', pos)) {
            temp_path = input_path.substr(pos, (int)input_path.size() - pos);
            over = false;
        }
        //读取到目录名
        else {
            next_pos = (int)input_path.find('/', pos) + 1;
            temp_path = input_path.substr(pos, next_pos - pos);
        }
        //读取到../则指向父路径
        if ("../" == temp_path) {
            if (NULL != ans->father)
                ans = ans->father;
        }
        //根据temp_path获取目录节点
        else {
            if (NULL == ans) {
                return NULL;
            }
            else {
                ans = ans->child;
                while (NULL != ans && temp_path != ans->name)
                    ans = ans->brother;
            }
            if (NULL == ans) {
                return NULL;
            }
        }
        //读取到文件名则跳出
        if (false == over) {
            break;
        }
    }
    return ans;
}

vector<string> directory::getSons(string input_path)
{
    vector<string> ans;
    //获取该文件夹的目录节点
    fileList father_node = getDirectNode(input_path);
    //输出其所有的子节点名称
    if (NULL == father_node) {
        return ans;
    }
    else if (NULL == father_node->child) {
        return ans;
    }
    else {
        fileList current = father_node->child;
        while (NULL != current) {
            ans.push_back(current->name);
            current = current->brother;
        }
    }
    return ans;
}

//获取目录节点的绝对路径，若该目录节点为空，则返回长度为0的字符串
string directory::getCurrentPath()
{

    string ans = getFullPathByNode(direct_path);
    return ans;
}

//获取目录节点的绝对路径，若该目录节点为空，则返回长度为0的字符串
string directory::getFullPathByNode(fileList node)
{
    //若该目录节点为空，则返回长度为0的字符串
    if (NULL == node) {
        return "";
    }
    string ans = "";
    //循环在加入其父的名字，直到根目录
    while (NULL != node) {
        ans = node->name + ans;
        node = node->father;
    }
    return ans;
}

//新建一个文件夹或者文件
int directory::newNode(string father_path, string name)
{
    father_path = getFullPathByInput(father_path);
    fileList father_node = getNodeByInput(father_path);
    if (NULL == father_node) {
        return NotExit;
    }
    fileList current = father_node;
    vector<string> all_file = getSons(father_path);
    for (vector<string>::iterator iter = all_file.begin(); iter != all_file.end(); iter++) {
        if (isSameName(*iter, name)) {
            all_file.clear();
            return SAME_NAME_EXISTS_PROBLEM;
        }
    }
    if (NULL == current->child) {
        current->child = new Node;
        current->child->father = father_node;
        current = current->child;
    }
    else {
        current = current->child;
        while (NULL != current->brother) {
            current = current->brother;
        }
        current->brother = new Node;
        current->brother->father = father_node;
        current = current->brother;
    }
    current->name = name;
    current->child = NULL;
    current->brother = NULL;
    updateFileSys();
    if (string::npos == name.find('/', 0)) {
        createFileInDisk(father_path + name);
        if (SUCCESS == updateFile(father_path + name, "")) {
            return SUCCESS;
        }
        else {
            deleteNode(father_path + name);
            return OUT_OF_DISK_CPACITY;
        }
    }
    else {
        return SUCCESS;
    }
}

//获取一个相对路径的绝对路径，若该路径不存在，则返回长度为0的字符串
string directory::getFullPathByInput(string input_path)
{
    //获取与相对路径对应的目录节点，若该目录节点不存在，则返回NULL
    fileList node = getNodeByInput(input_path);
    //获取目录节点的绝对路径，若该目录节点为NULL，则返回长度为0的字符串
    string ans = getFullPathByNode(node);
    return ans;
}

//获取相对路径对应的目录节点，若该目录节点不存在，则返回NULL
fileList directory::getNodeByInput(string input_path)
{
    fileList ans = NULL;
    //若输入路径为绝对路径，则从根目录开始计算
    if (0 < input_path.length() && '/' == input_path[0]) {
        input_path = input_path.substr(1, (int)input_path.size() - 1);
        ans = filelist;
    }
    //否则该路径为相对路径，则从当前路径开始计算
    else {
        ans = direct_path;
    }
    //pos指向子路径开始处，next_pos指向下一子路径开始处
    int pos = 0, next_pos = 0;
    //temp_path表示当前子路径
    string temp_path;
    //标识是否读取了文件名
    bool over = true;
    for (pos = 0; pos <= (int)input_path.size() - 1; pos = next_pos) {
        //读取到文件名
        if (string::npos == input_path.find('/', pos)) {
            temp_path = input_path.substr(pos, (int)input_path.size() - pos);
            over = false;
        }
        //读取到目录名
        else {
            next_pos = (int)input_path.find('/', pos) + 1;
            temp_path = input_path.substr(pos, next_pos - pos);
        }
        //读取到../则指向父路径
        if ("../" == temp_path) {
            if (NULL != ans->father)
                ans = ans->father;
        }
        //根据temp_path获取目录节点
        else {
            if (NULL == ans) {
                return NULL;
            }
            else {
                ans = ans->child;
                while (NULL != ans && temp_path != ans->name)
                    ans = ans->brother;
            }
            if (NULL == ans) {
                return NULL;
            }
        }
        //读取到文件名则跳出
        if (false == over) {
            break;
        }
    }
    return ans;
}

//判断一个路径是否为文件
bool directory::isFile(string name)
{
    if (0 < name.length() && '/' == name[(int)name.size() - 1]) {
        return false;
    }
    else {
        return true;
    }
}

//将文件夹的最后一个/去掉
string directory::getDirectorySelfName(string name)
{
    //若确实为目录则去掉最后一个斜杠
    if (false == isFile(name)) {
        name = name.substr(0, (int)name.size() - 1);
    }
    return name;
}

//判断两个文件或文件夹是否重名
bool directory::isSameName(string name1, string name2)
{
    if (getDirectorySelfName(name1) == getDirectorySelfName(name2)) {
        return true;
    }
    else {
        return false;
    }
}

//将目录文件读入磁盘
void directory::updateFileSys() {
    //中序遍历目录文件
    string ans = "";
    fileList stack[2000];
    int top = 0;
    fileList current = filelist;
    while (0 != top || NULL != current) {
        if (NULL == current) {
            current = stack[--top];
        }
        else {
            if (NULL != current->child) {
                //将目录对并入目录对串字符串中
                fileList temp = current->child;
                while (NULL != temp) {
                    fileList father_current = current;
                    string father_path = "";
                    while (NULL != father_current) {
                        father_path = father_current->name + father_path;
                        father_current = father_current->father;
                    }
                    ans += ("<" + father_path + "," + temp->name + ">");
                    temp = temp->brother;
                }
            }
            stack[top++] = current->brother;
            current = current->child;
        }
    }
    //将目录对串写入磁盘
    vector<string> buffer = readDisk();
    buffer[0] = ans;
    writeToDisk(buffer);
}

//将全部信息写入磁盘
void directory::writeToDisk(vector<string> buffer)
{
    ofstream out("Disk.txt");
    if (out.is_open()) {
        vector<string>::iterator iter;
        for (iter = buffer.begin(); iter != buffer.end(); iter++) {
            out << *iter << endl;
        }
    }
}


void directory::createFileInDisk(string full_name)
{
    string ans = "<" + full_name + ":>";
    vector<string> buffer = readDisk();
    string temp = buffer[FILE_INDEX];
    temp += ans;
    buffer[FILE_INDEX] = temp;
    string bitmap = buffer[BIT_MAP];
    qDebug()<<"bitmap---"<<QString::fromStdString(bitmap)<<endl;
    writeToDisk(buffer);
}

int directory::updateFile(string input_path, string content)
{
    string full_name = getFullPathByInput(input_path);
    if ("" == full_name) {
        return NotExit;
    }
    //modified_size记录文件需要的块数
    int content_size = (int)content.size();
    int modified_size = (content_size - 1) / BLOCK_SIZE + 1;
    vector<string> buffer = readDisk();
    //temp记录文件索引
    string temp = buffer[FILE_INDEX];
    int pos = (int)temp.find("<" + full_name + ":", 0) + 1;
    //pos指向该文件索引
    pos += (int)full_name.size() + 1;
    qDebug()<<"pos!!!!!!!!"<<pos<<endl;
    //index_int记录文件索引
    vector<int> index_int;
    int i;
    qDebug()<<"du chu lai de buffer::"<<QString::fromStdString(temp)<<endl;
    for (i = pos; '>' != temp[i]; i++) {
        string index_temp = "";
        while (',' != temp[i] && '>' != temp[i]) {
            index_temp += temp[i++];
        }
        index_int.push_back(stringToInt(index_temp));
        qDebug()<<"index_temp:::::::"<<QString::fromStdString(index_temp)<<endl;
        if ('>' == temp[i]) {
            break;
        }
    }
    string temp_buffer = buffer[FILE_INDEX];
    qDebug()<<"    temp_buffer:::::::"<<QString::fromStdString(temp_buffer)<<endl;
    //ipos记录该文件索引的结尾
    int ipos = i + 1;
    if ((int)index_int.size() == modified_size) {
        string ans = "";
        int temp_pos = 0;
        for (vector<int>::iterator iter = index_int.begin(); iter != index_int.end(); iter++) {
            ans = content.substr(temp_pos, BLOCK_SIZE);
            int posi = *iter + FILE_CONTENT;
            buffer[posi] = ans;
            temp_pos += BLOCK_SIZE;
        }
        temp_buffer = buffer[FILE_INDEX];
            qDebug()<<"    temp_buffer:::::::"<<QString::fromStdString(temp_buffer)<<endl;
    }
    else if ((int)index_int.size() < modified_size) {
        string bit_string = buffer[BIT_MAP];
        qDebug()<<"    BITMAP:::::::"<<QString::fromStdString(bit_string)<<endl;
        for (int i = 0; i <= BLOCK_NUM - 1 && (int)index_int.size() < modified_size; i++) {
            if ('0' == bit_string[i]) {
                index_int.push_back(i);
            }
        }
        if ((int)index_int.size() < modified_size) {
            return OUT_OF_DISK_CPACITY;
        }
        else {
            string modified_file = temp.substr(0, pos);
            for (vector<int>::iterator iter = index_int.begin(); iter != index_int.end(); iter++) {
                string index_temp = intToString(*iter);
                modified_file += index_temp + ",";
            }
            modified_file[(int)modified_file.size() - 1] = '>';
            modified_file += temp.substr(ipos, (int)temp.size() - ipos);
            buffer[FILE_INDEX] = modified_file;
            string ans = "";
            int temp_pos = 0;
            for (vector<int>::iterator iter = index_int.begin(); iter != index_int.end(); iter++) {
                ans = content.substr(temp_pos, BLOCK_SIZE);
                bit_string[*iter] = '1';
                int posi = *iter + FILE_CONTENT;
                buffer[posi] = ans;
                temp_pos += BLOCK_SIZE;
            }
            buffer[BIT_MAP] = bit_string;
        }
        temp_buffer = buffer[FILE_INDEX];
            qDebug()<<" W   temp_buffer:::::::"<<QString::fromStdString(temp_buffer)<<endl;
    }
    else {
        string bit_string = buffer[BIT_MAP];
        int times = (int)index_int.size() - modified_size;
        for (int i = 0; i <= times - 1; i++) {
            bit_string[*(index_int.begin())] = '0';
            buffer[*(index_int.begin()) + FILE_CONTENT] = "";
            index_int.erase(index_int.begin());
        }
        string modified_file = temp.substr(0, pos);
        for (vector<int>::iterator iter = index_int.begin(); iter != index_int.end(); iter++) {
            string index_temp = intToString(*iter);
            modified_file += index_temp + ",";
        }
        modified_file[(int)modified_file.size() - 1] = '>';
        modified_file += temp.substr(ipos, (int)temp.size() - ipos);
        buffer[1] = modified_file;
        string ans = "";
        int temp_pos = 0;
        for (vector<int>::iterator iter = index_int.begin(); iter != index_int.end(); iter++) {
            ans = content.substr(temp_pos, BLOCK_SIZE);
            bit_string[*iter] = '1';
            int posi = *iter + FILE_CONTENT;
            buffer[posi] = ans;
            temp_pos += BLOCK_SIZE;
        }
        buffer[BIT_MAP] = bit_string;
    }

    qDebug()<<"      du chu lai de buffer::"<<QString::fromStdString(temp)<<endl;
    writeToDisk(buffer);
    return SUCCESS;
}

int directory::deleteNode(string input_path)
{
    qDebug()<<"delete node!!!in dierectory!!!"<<endl;
    if (NULL == getNodeByInput(input_path)) {
        return NotExit;
    }
    string full_path = getFullPathByInput(input_path);
    if (true == isFile(full_path)) {
        return deleteFile(full_path);
    }
    else {
        return deleteFolder(full_path);
    }
}

int directory::deleteFile(string input_path)
{
    qDebug()<<"delete file"<<endl;
    if (NULL == getNodeByInput(input_path)) {
        return NotExit;
    }
    string full_name = getFullPathByInput(input_path);
    //以下是将该文件的内容、索引删除
    vector<string> buffer = readDisk();
    //temp记录文件索引
    string temp = buffer[FILE_INDEX];
    int pos = (int)temp.find(full_name, 0);
    //pos指向该文件索引
    pos += (int)full_name.size() + 1;
    //index_int记录文件索引
    vector<int> index_int;
    int i;
    for (i = pos; '>' != temp[i]; i++) {
        string index_temp = "";
        while (',' != temp[i] && '>' != temp[i]) {
            index_temp += temp[i++];
        }
        index_int.push_back(stringToInt(index_temp));
        if ('>' == temp[i]) {
            break;
        }
    }
    //ipos记录该文件索引的结尾
    int ipos = i + 1;
    pos = (int)temp.find(full_name, 0) - 1;
    string modified_file = temp.substr(0, pos) + temp.substr(ipos, (int)temp.size() - ipos);
    buffer[FILE_INDEX] = modified_file;
    string bit_string = buffer[BIT_MAP];
    qDebug()<<"bitmap::"<<QString::fromStdString(bit_string)<<endl;

    for (vector<int>::iterator iter = index_int.begin(); iter != index_int.end(); iter++) {
        int posi = *iter + FILE_CONTENT;
        buffer[posi] = "";
        bit_string[*iter] = '0';
    }
    buffer[BIT_MAP] = bit_string;
    writeToDisk(buffer);
    //以下是将该文件从目录中删除
    fileList current_directory = getNodeByInput(full_name)->father;
    if (NULL == current_directory) {
        return RIGHT_PROBLEM;
    }
    if (full_name == getFullPathByNode(current_directory->child)) {
        fileList temp = current_directory->child;
        current_directory->child = temp->brother;
        delete(temp);
    }
    else {
        current_directory = current_directory->child;
        while (NULL != current_directory->brother && full_name != getFullPathByNode(current_directory->brother)) {
            current_directory = current_directory->brother;
        }
        fileList temp = current_directory->brother;
        current_directory->brother = temp->brother;
        delete(temp);
    }
    updateFileSys();
    return SUCCESS;
}

int directory::deleteFolder(string input_path)
{
    qDebug()<<"Delete directory in directory!!!"<<endl;
    if (NULL == getNodeByInput(input_path)) {
        return NotExit;
    }
    string full_name = getFullPathByInput(input_path);
    vector<string> all_file = getSons(full_name);
    //文件夹中还有文件
    if ( (int)all_file.size() != 0 ) {
        all_file.clear();
        return FILES_EXIST_PROBLEM;
    }
    else {
        all_file.clear();
        //以下是将该文件从目录中删除
        fileList current_directory = getNodeByInput(full_name)->father;
        if (NULL == current_directory) {
            return RIGHT_PROBLEM;
        }
        if (full_name == getFullPathByNode(current_directory->child)) {
            fileList temp = current_directory->child;
            current_directory->child = temp->brother;
            delete(temp);
        }
        else {
            current_directory = current_directory->child;
            while (NULL != current_directory->brother && full_name != getFullPathByNode(current_directory->brother)) {
                current_directory = current_directory->brother;
            }
            fileList temp = current_directory->brother;
            current_directory->brother = temp->brother;
            delete(temp);
        }
        updateFileSys();
        return SUCCESS;
    }
}

//string型转换到int型
int directory::stringToInt(string temp)
{
    stringstream ss;
    ss << temp;
    int ans;
    ss >> ans;
    return ans;
}
//int型转换到string型
string directory::intToString(int temp)
{
    string ans;
    stringstream ss;
    ss << temp;
    ss >> ans;
    return ans;
}

//判断输入的路径是否存在
bool directory::isInputPathExisting(string input_path)
{
    fileList ans = getNodeByInput(input_path);
    if (NULL == ans) {
        return false;
    }
    else {
        return true;
    }
}

string directory::readFileContent(string input_path)
{
    string full_name = getFullPathByInput(input_path);
    if ("" == full_name) {
        return "";
    }
    vector<string> buffer = readDisk();
    string temp = buffer[FILE_INDEX];
    if (string::npos == temp.find(full_name, 0)) {
        return "";
    }
    int pos = (int)temp.find(full_name, 0);
    pos += (int)full_name.size() + 1;
    vector<int> index_int;
    for (int i = pos; '>' != temp[i]; i++) {
        string index_temp = "";
        while (',' != temp[i] && '>' != temp[i]) {
            index_temp += temp[i++];
        }
        index_int.push_back(stringToInt(index_temp));
        if ('>' == temp[i]) {
            break;
        }
    }
    string ans = "";
    for (vector<int>::iterator iter = index_int.begin(); iter != index_int.end(); iter++) {
        int posi = *iter + FILE_CONTENT;
        ans += buffer[posi];
    }
    return ans;
}



int directory::copyNode(string source_path, string target_path)
{
    //确定输入的源文件/文件夹与目标文件夹合法
    if (NULL == getNodeByInput(source_path) || NULL == getNodeByInput(target_path)
        || true == isFile(target_path)) {
        return NotExit;
    }
    //将源文件/文件夹与目的文件夹均变换为绝对路径
    source_path = getFullPathByInput(source_path);
    target_path = getFullPathByInput(target_path);
    //若目的文件夹是源文件夹的子文件夹，则该复制操作无法进行，返回权限错误
    if (string::npos != target_path.find(source_path)) {
        return NO_DATA_IN_BUFFER;
    }
    //对待复制项为文件的情况进行处理
    if (true == isFile(getFullPathByInput(source_path))) {
        fileList source_node = getNodeByInput(source_path);
        string target_full_path = getFullPathByInput(target_path);
        int ans = newNode(target_full_path, source_node->name);
        if (SUCCESS == ans) {
            ans = updateFile(target_full_path + source_node->name, readFileContent(getFullPathByNode(source_node)));
            if (SUCCESS == ans) {
                return ans;
            }
            else {
                deleteNode(target_full_path + source_node->name);
                return ans;
            }
        }
        else {
            deleteNode(target_full_path + source_node->name);
            return ans;
        }
    }
    //对待复制项为文件夹的情况进行处理
    else {
        //获取源文件夹本身与其父亲的节点
        fileList source_node = getNodeByInput(source_path);
        fileList source_father = source_node->father;
        //父亲节点的绝对路径长度
        int source_father_path_size = getFullPathByNode(source_father).size();
        //目的文件夹的绝对路径
        string target_full_path = getFullPathByInput(target_path);
        //首先将空的源文件夹写入目的文件夹中
        int ans = newNode(target_full_path, source_node->name);
        if (SUCCESS != ans) {
            return ans;
        }
        //中序遍历源文件夹节点的子树进行复制
        fileList current = source_node->child;
        fileList stack[STACK_SIZE];
        fileList created_stack[STACK_SIZE];
        int top = 0;
        int created_top = 0;
        while (0 != top || NULL != current) {
            if (NULL == current) {
                current = stack[--top];
            }
            else {
                string t_path = target_full_path + getFullPathByNode(current->father).substr(source_father_path_size);
                ans = newNode(t_path, current->name);
                if (SUCCESS == ans) {
                    if (isFile(t_path + current->name)) {
                        ans = updateFile(t_path + current->name, readFileContent(getFullPathByNode(current)));
                        if (SUCCESS == ans) {
                            created_stack[created_top++] = current;
                            stack[top++] = current->brother;
                            current = current->child;
                        }
                        else {
                            deleteNode(t_path + current->name);
                            break;
                        }
                    }
                }
                else {
                    break;
                }
            }
        }
        if (0 == top) {
            return SUCCESS;
        }
        else {
            for (int i = created_top - 1; i >= 0; i--) {
                current = created_stack[i];
                string t_path = target_full_path + getFullPathByNode(current->father).substr(source_father_path_size);
                deleteNode(t_path + current->name);
            }
            return ans;
        }
    }
}

int directory::cutNode(string source_path, string target_path)
{
    //确定输入的源文件/文件夹与目标文件夹合法
    if (NULL == getNodeByInput(source_path) || NULL == getNodeByInput(target_path)
        || true == isFile(target_path)) {
        return NotExit;
    }
    //将源文件/文件夹与目的文件夹均变换为绝对路径
    source_path = getFullPathByInput(source_path);
    target_path = getFullPathByInput(target_path);
    //若目的文件夹是源文件夹的子文件夹，则该剪切操作无法进行，返回权限错误
    if (string::npos != target_path.find(source_path)) {
        return NO_DATA_IN_BUFFER;
    }
    //将源文件/文件夹复制到目的文件夹中
    int ans = copyNode(source_path, target_path);
    //若复制不成功，则返回错误信息
    if (SUCCESS != ans) {
        return ans;
    }
    //若复制成功，则需要将源文件/文件夹删除
    else {
        //若第一形参为文件，则直接将该文件删除
        if (true == isFile(getFullPathByInput(source_path))) {
            deleteNode(source_path);
            return SUCCESS;
        }
        //若第一形参为文件夹，则将该文件夹内的所有文件与文件夹以及该文件夹本身均删除
        //获取源文件夹的目录节点
        fileList source_node = getNodeByInput(source_path);
        //中序遍历该文件夹的子树，删除每个文件与文件夹
        fileList current = source_node->child;
        fileList stack[STACK_SIZE];
        fileList cutting_stack[STACK_SIZE];
        int top = 0;
        int cutting_top = 0;
        while (0 != top || NULL != current) {
            if (NULL == current) {
                current = stack[--top];
            }
            else {
                cutting_stack[cutting_top++] = current;
                stack[top++] = current->brother;
                current = current->child;
            }
        }
        for (int i = cutting_top - 1; i >= 0; i--) {
            current = cutting_stack[i];
            deleteNode(getFullPathByNode(current));
        }
        //删除源文件夹本身
        deleteNode(source_path);
        return SUCCESS;
    }
}

int directory::renameNode(string input_path, string target_name)
{
    if (NULL == getNodeByInput(input_path)) {
        return NotExit;
    }
    else {
        vector<string> files = getSons(getFullPathByNode(getNodeByInput(input_path)->father));
        for (vector<string>::iterator iter = files.begin(); iter != files.end(); iter++) {
            cout << *iter  << "------------------------------------------------ " << target_name << endl;

            if (true == isSameName(*iter, target_name)) {
                files.clear();
                return SAME_NAME_EXISTS_PROBLEM;
            }
        }
        files.clear();
        string full_path = getFullPathByInput(input_path);
        if (true == isFile(full_path)) {
            fileList current = getNodeByInput(input_path);
            current->name = target_name;
            updateFileSys();
            vector<string> buffer = readDisk();
            string index_string = buffer[FILE_INDEX];
            int f_pos = (int)index_string.find("<" + full_path + ":", 0) + 1;
            int l_pos = f_pos + (int)full_path.size();
            string ans = index_string.substr(0, f_pos) + getFullPathByNode(current) + index_string.substr(l_pos);
            buffer[FILE_INDEX] = ans;
            writeToDisk(buffer);
            return SUCCESS;
        }
        else {
            fileList current = getNodeByInput(input_path);
            current->name = target_name + "/";
            updateFileSys();
            vector<string> buffer = readDisk();
            string index_string = buffer[FILE_INDEX];
            int f_pos = 0;
            int l_pos = 0;
            while (string::npos != index_string.find("<" + full_path, l_pos)) {
                f_pos = (int)index_string.find("<" + full_path, l_pos) + 1;
                l_pos = f_pos + (int)full_path.size();
                index_string = index_string.substr(0, f_pos) + getFullPathByNode(current) + index_string.substr(l_pos);
            }
            buffer[FILE_INDEX] = index_string;
            writeToDisk(buffer);
            return SUCCESS;
        }
    }
    return 0;
}
