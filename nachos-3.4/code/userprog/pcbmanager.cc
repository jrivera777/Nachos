#include <string.h>
#include "pcbmanager.h"

PCBManager* PCBManager::manager = NULL;

PCBManager*
PCBManager::GetInstance()
{
    if(!manager)
	manager = new PCBManager();
    return manager;
}

PCBManager::PCBManager()
{
    usedPids = 0;
    pidLock = new Lock("pcbmLock");
    pids = new BitMap(MAX_PID);
    pids->Mark(0); //don't ever use 0 as a process ID
    pcbs = new List();
}

PCBManager::~PCBManager()
{
    delete pidLock;
    delete pcbs;
    delete manager;
}

int
PCBManager::GetPID()
{
    if(usedPids >= MAX_PID)
	return -1;

    pidLock->Acquire();

    int pid = pids->Find();
    
    if(pid >= 0)
	usedPids++;

    pidLock->Release();

    return pid;
}

bool
PCBManager::ClearPID(int which)
{
    if(usedPids <= 0)
	return false;

    pidLock->Acquire();
    pids->Clear(which);
    usedPids--;
    pidLock->Release();

    return true;
}

int
PCBManager::GetFreePids()
{
    int count = -1;

    pidLock->Acquire();
    count = pids->NumClear();
    pidLock->Release();

    return count;
}

void* 
PCBManager::RemovePCB(int pkey)
{
    return pcbs->Remove(pkey);
}
