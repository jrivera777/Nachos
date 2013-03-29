#ifndef SYSOPENFILE_H
#define SYSOPENFILE_H

#include "openfile.h"

class SysOpenFile
{
 public:
    SysOpenFile(int id, char* fname, OpenFile* f);
    ~SysOpenFile();
    int fid;
    int count;
    char* name;
    OpenFile* file;
};

#endif
