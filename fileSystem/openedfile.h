#ifndef OPENEDFILE_H
#define OPENEDFILE_H
#include"file.h"

class openedFile
{
private:
    File *file;
public:
    openedFile *next;
    openedFile();
    openedFile(File *new_file);
    ~openedFile();
    File *getFile(){ return file; }

};

#endif // OPENEDFILE_H
