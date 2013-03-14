#include "pcb.h"

PCB::PCB(Thread* t, int id, int parent)
{
    pid = id;
    p_pid = parent;
    thrd = t;
}
