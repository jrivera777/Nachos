#include "sysopenfile.h"
// #include <stdlib.h>
#include <string.h>

SysOpenFile::SysOpenFile(int id, char* fname, OpenFile* f)
{
    name = new char[strlen(fname)];
    strcpy(name, fname);    
    file = f;
    fid = id;
}
