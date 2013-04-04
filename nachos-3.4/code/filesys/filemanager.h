#define MAX_FILES 50

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "bitmap.h"
#include "synch.h"
#include "sysopenfile.h"



class Lock;
class FileManager
{
 public:
    FileManager();
    ~FileManager();
    int GetFID();
    bool ClearFID(int which);
    int GetFreeFids();
    int GetSysOpenFile(char* file);
    SysOpenFile* files[MAX_FILES];
    Lock*      fidLock;
 private:
    BitMap*    fids;
};    

#endif
