#ifndef PCBMANAGER_H
#define PCBMANAGER_H

#include "synch.h"
#include "bitmap.h"
#include "list.h"
#include "useropenfile.h"

#define MAX_PID 512

class PCBManager
{
public:
    static PCBManager* GetInstance();    
    ~PCBManager();
    int GetPID();
    bool ClearPID(int which);
    int GetFreePids();
    void* RemovePCB(int pkey);
    UserOpenFile* GetUserFile(int pid, char* fname);
    List* pcbs;
private:
    PCBManager();
    int usedPids;
    BitMap*    pids;
    Lock*      pidLock;
    static PCBManager* manager;
};
#endif
