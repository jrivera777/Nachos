#idndef MEMMANAGER_H
#define MEMMANAGER_H

#include "bitmap.h"
#include "synch.h"

#define TOTAL_PAGES 32

class MemManager
{
 public:
    MemManager();
    ~MemManager();
    int GetPage();
    bool ClearPage(int which);
    int GetFreePages();
 private:
    Bitmap* pages;
    int usedPages;
    Lock* mmLock;
}

#endif
