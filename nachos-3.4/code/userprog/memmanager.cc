#include "memmanager.h"

//Initialize pages, default none used.
MemManager::MemManager()
{
    pages = new Bitmap(TOTAL_PAGES);
    mmLock = new Lock("mmLock");
    usedPages = 0;
}

MemManager::~MemManager()
{
    delete pages;
    delete mmLock;
}

int
MemManager::GetPage()
{
    if(usedPages >= TOTAL_PAGES)
	return -1;
    
    mmLock->Acquire();
    int pageNumber = pages->Find(); //locate next free page
    if(page >= 0)
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
MemManager:GetFreePages()
{
    int count = -1;

    mmLock->Acquire();
    count = pages->NumClear();
    mmLock->Release();

    return count;
}
