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
    SysOpenFile* files[MAX_FILES];
 private:
    BitMap*    fids;
    Lock*      fidLock;
};    

#endif
