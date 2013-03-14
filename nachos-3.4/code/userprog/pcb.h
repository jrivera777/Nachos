#ifndef PCB_H
#define PCB_H

#include "thread.h"
#include "bitmap.h"


class PCB
{
 public:
    PCB(Thread* t, int id, int parent);
    ~PCB();
    int GetPID() {return pid;};
    int GetParentPID() {return p_pid;};
 private:
    int pid;
    int p_pid;
    Thread* thrd;
};
#endif
