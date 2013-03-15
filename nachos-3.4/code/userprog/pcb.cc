#include "pcb.h"

PCB::PCB(Thread* t, int id, Thread* par)
{
    pid = id;
    parent = par;
    thrd = t;
    children = new List();
    pcbLock = new Lock("pcbLock");
    pcbCond = new Condition("pcbCond");
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
