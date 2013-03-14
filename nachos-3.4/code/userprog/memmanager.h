#ifndef MEMMANAGER_H
#define MEMMANAGER_H

class Lock;

#include "synch.h"
#include "bitmap.h"

class MemManager
{
 public:
    static MemManager* GetInstance();
    ~MemManager();
    int GetPage();
    bool ClearPage(int which);
    int GetFreePages();
 private:
    MemManager(int numPages);
    BitMap* pages;
    int usedPages;
    Lock* mmLock;
    int totalPages;
    static MemManager* manager;
};

#endif
