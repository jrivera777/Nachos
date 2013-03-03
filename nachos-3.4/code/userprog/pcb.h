#ifndef PCB_H
#define PCB_H

#include "utility.h"
#include "bitmap.h"

class PCB
{
 public:
    PCB();
    ~PCB();
    int getPID();
    void clearPID();
 private:
    int pid;
    int p_pid;
    Thread* curr;
}
#endif
