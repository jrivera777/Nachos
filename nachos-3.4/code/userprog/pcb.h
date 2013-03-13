#ifndef PCB_H
#define PCB_H

#include "utility.h"
#include "bitmap.h"

class PCB
{
 public:
    PCB();
    ~PCB();
    int getPID() {return pid;};
    void clearPID() {return p_pid};;
 private:
    int pid;
    int p_pid;
    Thread* curr;
}
#endif
