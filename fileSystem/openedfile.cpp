#include "openedfile.h"

openedFile::openedFile()
{
    file = new File("", "");
    next = NULL;
}

openedFile::openedFile(File *new_file) :file(new_file)
{
    next = NULL;
}


openedFile::~openedFile()
{
}


