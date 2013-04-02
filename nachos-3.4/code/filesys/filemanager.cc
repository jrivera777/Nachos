#include "filemanager.h"
#include <string.h>

FileManager::FileManager()
{
    fids = new BitMap(MAX_FILES);
    fidLock = new Lock("file manager lock");
    fids->Mark(0); //0, 1 used for stdin and stdout, respectively
    fids->Mark(1);
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
int
FileManager::GetSysOpenFile(char* file)
{
    int i;
    int numFiles = MAX_FILES - GetFreeFids();
    for(i = 2; i < numFiles; i++)
	if(strcmp(files[i]->name, file) == 0)
	    return i;
    
    return -1;
}
