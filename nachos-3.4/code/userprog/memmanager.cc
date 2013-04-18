#include "memmanager.h"
#include "machine.h"

MemManager* MemManager::manager = NULL;

MemManager*
MemManager::GetInstance()
{
    if(!manager)
	manager = new MemManager(NumPhysPages);
    
    return manager;
}

MemManager::MemManager(int numPages)
{
    pages = new BitMap(numPages);
    mmLock = new Lock("mmLock");
    usedPages = 0;
    totalPages =  numPages;
    replaceIndex = 0;
    entries = new CoreMapEntry[totalPages];
    for(int i = 0; i < totalPages; i++)
    {
	entries[i].allocated = false;
	entries[i].ioLocked = false;
	entries[i].space = NULL;
	entries[i].vPageNumber = -1;

    }
}

MemManager::~MemManager()
{
    delete pages;
    delete mmLock;
    delete manager;
    delete[] entries;
}

int
MemManager::GetPage()
{
    if(usedPages >= totalPages)
	return -1;
    
    mmLock->Acquire();
    int pageNumber = pages->Find(); //locate next free page
    if(pageNumber >= 0)
	usedPages++; //free page discovered
    entries[pageNumber].vPageNumber = pageNumber;
    entries[pageNumber].allocated = true;
    mmLock->Release();
	   
    return pageNumber;
}

bool
MemManager::ClearPage(int which)
{
    if(usedPages <= 0)
	return false;

    mmLock->Acquire();
    pages->Clear(which);
    usedPages--;
    entries[which].vPageNumber = -1;
    entries[which].allocated = false;
    mmLock->Release();

    return true;
}

int
MemManager::GetFreePages()
{
    int count = -1;

    mmLock->Acquire();
    count = pages->NumClear();
    mmLock->Release();

    return count;
}
