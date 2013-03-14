#include "memmanager.h"

MemManager* MemManager::manager = NULL;

MemManager*
MemManager::GetInstance(int numPages)
{
    if(!manager)
	manager = new MemManager(numPages);
    
    return manager;
}

MemManager::MemManager(int numPages)
{
    pages = new BitMap(numPages);
    mmLock = new Lock("mmLock");
    usedPages = 0;
    totalPages =  numPages;
}

MemManager::~MemManager()
{
    delete pages;
    delete mmLock;
    delete manager;
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
