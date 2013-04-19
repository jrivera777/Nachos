#ifndef MEMMANAGER_H
#define MEMMANAGER_H

class Lock;
class AddrSpace;

#include "synch.h"
#include "bitmap.h"
#include "addrspace.h"

class CoreMapEntry
{
 public:
    bool allocated;
    AddrSpace* space;
    int vPageNumber;
    bool ioLocked;
};

class MemManager
{
 public:
    static MemManager* GetInstance();
    ~MemManager();
    int GetPage();
    bool ClearPage(int which);
    int GetFreePages();
    CoreMapEntry* entries;
    int replaceIndex;
    int totalPages;
 private:
    MemManager(int numPages);
    BitMap* pages;
    int usedPages;
    Lock* mmLock;
    static MemManager* manager;
};

#endif
