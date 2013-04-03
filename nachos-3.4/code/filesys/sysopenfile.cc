#include "sysopenfile.h"
// #include <stdlib.h>
#include <string.h>

SysOpenFile::SysOpenFile(int id, char* fname, OpenFile* f)
{
    name = new char[strlen(fname)+1];
    strcpy(name, fname);    
    file = f;
    fid = id;
}
