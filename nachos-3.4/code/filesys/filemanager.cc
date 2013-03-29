#include "filemanager.h"

FileManager::FileManager()
{
    fids = new BitMap(MAX_FILES);
    fidLock = new Lock("file manager lock");
}

int
FileManager::GetFID()
{
    if(fids->NumClear() <= 0)
	return -1;
    
    fidLock->Acquire();
    
    int fid = fids->Find();
    
    fidLock->Release();

    return fid;
}

bool
FileManager::ClearFID(int which)
{
    if(fids->NumClear() >= MAX_FILES)
	return false;
    
    fidLock->Acquire();
    fids->Clear(which);
    fidLock->Release();
 
    return true;
}

int
FileManager::GetFreeFids()
{
    int count = -1;

    fidLock->Acquire();
    count = fids->NumClear();
    fidLock->Release();

    return count;
}
