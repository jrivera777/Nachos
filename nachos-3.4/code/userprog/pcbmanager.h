#ifndef PCBMANAGER_H
#define PCBMANAGER_H

class Lock;
class SynchList;
#include "bitmap.h"
#include "synchlist.h"

#define MAX_PID 256

class PCBManager
{
public:
    static PCBManager* GetInstance();    
    ~PCBManager();
    int GetPID();
    bool ClearPID(int which);
    int GetFreePids();
    SynchList* pcbs;
private:
    PCBManager();
    int usedPids;
    BitMap*    pids;
    Lock*      pidLock;
    static PCBManager* manager;
};
#endif
