#ifndef PCB_H
#define PCB_H

#include "thread.h"
#include "bitmap.h"
#include "list.h"
#include "synch.h"

class Thread;
class Lock;
class Condition;
class PCB
{
 public:
    PCB(Thread* t, int id, Thread* par);
    ~PCB();
    int GetPID() {return pid;};
    Thread* GetParent() {return parent;};
    Thread* GetThread() {return thrd;};
    void SetParent(Thread* val) { parent = val;}
    List* children;
    Lock* pcbLock;
    Condition* pcbCond;
    bool isChild(int pkey);
    void* GetChild(int pkey);
    void* RemoveChild(int pkey);
    void OrphanChildren();
    int GetExitStatus(){return exitStatus;}
    void SetExitStatus(int val){exitStatus = val;}
 private:
    int pid;
    int exitStatus;
    Thread* thrd;
    Thread* parent;

};
#endif
