#include "pcb.h"

PCB::PCB(Thread* t, int id, Thread* par)
{
    pid = id;
    parent = par;
    thrd = t;
    children = new List();
    files = new List();
    pcbLock = new Lock("pcbLock");
    pcbCond = new Condition("pcbCond");
    uids = new BitMap(MAX_FILES);
    uids->Mark(0); //stdin and stdout
    uids->Mark(1);
//     files->SortedInsert(new UserOpenFile("stdin", 0));
//     files->SortedInsert(new UserOpenFile("stdout", 1));
}
PCB::~PCB()
{
    delete children;
    delete files;
    delete pcbLock;
    delete pcbCond;
    delete uids;
}
bool
PCB::isChild(int pkey)
{
    return children->Contains(pkey);
}

void*
PCB::RemoveChild(int pkey)
{
    return children->Remove(pkey);
}

//Remove given PCB's parent id, i.e. make it a zombie process
void
OrphanChild(int item)
{
    PCB* child = (PCB*)item;
    child->SetParent(NULL);
}

//make all children zombie processes
void
PCB::OrphanChildren()
{
    children->Mapcar(&OrphanChild);
}

void*
PCB::GetChild(int pkey)
{
    return children->GetElement(pkey);
}

int
PCB::GetUID()
{
    int uid = -1;

    pcbLock->Acquire();
    uid = uids->Find();
    pcbLock->Release();
    
    return uid;
}

bool
PCB::ClearUID(int which)
{
    if(uids->NumClear() >= MAX_FILES)
	return false;

    pcbLock->Acquire();
    uids->Clear(which);
    pcbLock->Release();

    return true;
}

int
PCB::GetFreeUids()
{
    int count = -1;

    pcbLock->Acquire();
    count = uids->NumClear();
    pcbLock->Release();

    return count;
}
